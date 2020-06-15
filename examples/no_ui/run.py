import multiprocessing
from time import sleep
from datetime import datetime, time
from logging import INFO

from vnpy.event import EventEngine
from vnpy.trader.setting import SETTINGS
from vnpy.trader.engine import MainEngine

from vnpy.gateway.ctp import CtpGateway
from vnpy.app.cta_strategy import CtaStrategyApp
from vnpy.app.cta_strategy.base import EVENT_CTA_LOG


SETTINGS["log.active"] = True
SETTINGS["log.level"] = INFO
SETTINGS["log.console"] = True


ctp_setting = {
    "使用者名稱": "",
    "密碼": "",
    "經紀商程式碼": "",
    "交易伺服器": "",
    "行情伺服器": "",
    "產品名稱": "",
    "授權編碼": "",
    "產品資訊": ""
}


def run_child():
    """
    Running in the child process.
    """
    SETTINGS["log.file"] = True

    event_engine = EventEngine()
    main_engine = MainEngine(event_engine)
    main_engine.add_gateway(CtpGateway)
    cta_engine = main_engine.add_app(CtaStrategyApp)
    main_engine.write_log("主引擎建立成功")

    log_engine = main_engine.get_engine("log")
    event_engine.register(EVENT_CTA_LOG, log_engine.process_log_event)
    main_engine.write_log("註冊日誌事件監聽")

    main_engine.connect(ctp_setting, "CTP")
    main_engine.write_log("連線CTP介面")

    sleep(10)

    cta_engine.init_engine()
    main_engine.write_log("CTA策略初始化完成")

    cta_engine.init_all_strategies()
    sleep(60)   # Leave enough time to complete strategy initialization
    main_engine.write_log("CTA策略全部初始化")

    cta_engine.start_all_strategies()
    main_engine.write_log("CTA策略全部啟動")

    while True:
        sleep(1)


def run_parent():
    """
    Running in the parent process.
    """
    print("啟動CTA策略守護父程序")

    # Chinese futures market trading period (day/night)
    DAY_START = time(8, 45)
    DAY_END = time(15, 30)

    NIGHT_START = time(20, 45)
    NIGHT_END = time(2, 45)

    child_process = None

    while True:
        current_time = datetime.now().time()
        trading = False

        # Check whether in trading period
        if (
            (current_time >= DAY_START and current_time <= DAY_END)
            or (current_time >= NIGHT_START)
            or (current_time <= NIGHT_END)
        ):
            trading = True

        # Start child process in trading period
        if trading and child_process is None:
            print("啟動子程序")
            child_process = multiprocessing.Process(target=run_child)
            child_process.start()
            print("子程序啟動成功")

        # 非記錄時間則退出子程序
        if not trading and child_process is not None:
            print("關閉子程序")
            child_process.terminate()
            child_process.join()
            child_process = None
            print("子程序關閉成功")

        sleep(5)


if __name__ == "__main__":
    run_parent()
