""""""

from collections import defaultdict
from vnpy.trader.object import OrderRequest, LogData
from vnpy.event import Event, EventEngine, EVENT_TIMER
from vnpy.trader.engine import BaseEngine, MainEngine
from vnpy.trader.event import EVENT_TRADE, EVENT_ORDER, EVENT_LOG
from vnpy.trader.constant import Status
from vnpy.trader.utility import load_json, save_json


APP_NAME = "RiskManager"


class RiskManagerEngine(BaseEngine):
    """"""
    setting_filename = "risk_manager_setting.json"

    def __init__(self, main_engine: MainEngine, event_engine: EventEngine):
        """"""
        super().__init__(main_engine, event_engine, APP_NAME)

        self.active = False

        self.order_flow_count = 0
        self.order_flow_limit = 50

        self.order_flow_clear = 1
        self.order_flow_timer = 0

        self.order_size_limit = 100

        self.trade_count = 0
        self.trade_limit = 1000

        self.order_cancel_limit = 500
        self.order_cancel_counts = defaultdict(int)

        self.active_order_limit = 50

        self.load_setting()
        self.register_event()
        self.patch_send_order()

    def patch_send_order(self):
        """
        Patch send order function of MainEngine.
        """
        self._send_order = self.main_engine.send_order
        self.main_engine.send_order = self.send_order

    def send_order(self, req: OrderRequest, gateway_name: str):
        """"""
        result = self.check_risk(req, gateway_name)
        if not result:
            return ""

        return self._send_order(req, gateway_name)

    def update_setting(self, setting: dict):
        """"""
        self.active = setting["active"]
        self.order_flow_limit = setting["order_flow_limit"]
        self.order_flow_clear = setting["order_flow_clear"]
        self.order_size_limit = setting["order_size_limit"]
        self.trade_limit = setting["trade_limit"]
        self.active_order_limit = setting["active_order_limit"]
        self.order_cancel_limit = setting["order_cancel_limit"]

        if self.active:
            self.write_log("交易風控功能啟動")
        else:
            self.write_log("交易風控功能停止")

    def get_setting(self):
        """"""
        setting = {
            "active": self.active,
            "order_flow_limit": self.order_flow_limit,
            "order_flow_clear": self.order_flow_clear,
            "order_size_limit": self.order_size_limit,
            "trade_limit": self.trade_limit,
            "active_order_limit": self.active_order_limit,
            "order_cancel_limit": self.order_cancel_limit,
        }
        return setting

    def load_setting(self):
        """"""
        setting = load_json(self.setting_filename)
        if not setting:
            return

        self.update_setting(setting)

    def save_setting(self):
        """"""
        setting = self.get_setting()
        save_json(self.setting_filename, setting)

    def register_event(self):
        """"""
        self.event_engine.register(EVENT_TRADE, self.process_trade_event)
        self.event_engine.register(EVENT_TIMER, self.process_timer_event)
        self.event_engine.register(EVENT_ORDER, self.process_order_event)

    def process_order_event(self, event: Event):
        """"""
        order = event.data
        if order.status != Status.CANCELLED:
            return
        self.order_cancel_counts[order.symbol] += 1

    def process_trade_event(self, event: Event):
        """"""
        trade = event.data
        self.trade_count += trade.volume

    def process_timer_event(self, event: Event):
        """"""
        self.order_flow_timer += 1

        if self.order_flow_timer >= self.order_flow_clear:
            self.order_flow_count = 0
            self.order_flow_timer = 0

    def write_log(self, msg: str):
        """"""
        log = LogData(msg=msg, gateway_name="RiskManager")
        event = Event(type=EVENT_LOG, data=log)
        self.event_engine.put(event)

    def check_risk(self, req: OrderRequest, gateway_name: str):
        """"""
        if not self.active:
            return True

        # Check order volume
        if req.volume <= 0:
            self.write_log("委託數量必須大於0")
            return False

        if req.volume > self.order_size_limit:
            self.write_log(
                f"單筆委託數量{req.volume}，超過限制{self.order_size_limit}")
            return False

        # Check trade volume
        if self.trade_count >= self.trade_limit:
            self.write_log(
                f"今日總成交合約數量{self.trade_count}，超過限制{self.trade_limit}")
            return False

        # Check flow count
        if self.order_flow_count >= self.order_flow_limit:
            self.write_log(
                f"委託流數量{self.order_flow_count}，超過限制每{self.order_flow_clear}秒{self.order_flow_limit}次")
            return False

        # Check all active orders
        active_order_count = len(self.main_engine.get_all_active_orders())
        if active_order_count >= self.active_order_limit:
            self.write_log(
                f"當前活動委託次數{active_order_count}，超過限制{self.active_order_limit}")
            return False

        # Check order cancel counts
        if req.symbol in self.order_cancel_counts and self.order_cancel_counts[req.symbol] >= self.order_cancel_limit:
            self.write_log(
                f"當日{req.symbol}撤單次數{self.order_cancel_counts[req.symbol]}，超過限制{self.order_cancel_limit}")
            return False

        # Add flow count if pass all checks
        self.order_flow_count += 1
        return True
