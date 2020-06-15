# CTA策略模組


## 模組構成

CTA策略模組主要由7部分構成，如下圖：

- base：定義了CTA模組中用到的一些基礎設定，如引擎型別（回測/實盤）、回測模式（K線/Tick）、本地停止單的定義以及停止單狀態（等待中/已撤銷/已觸發）。
  
- template：定義了CTA策略模板（包含訊號生成和委託管理）、CTA訊號（僅負責訊號生成）、目標倉位演算法（僅負責委託管理，適用於拆分巨型委託，降低衝擊成本）。
- strategies: 官方提供的cta策略示例，包含從最基礎的雙均線策略，到通道突破型別的布林帶策略，到跨時間週期策略，再到把訊號生成和委託管理獨立開來的多訊號策略。(使用者自定義的策略也可以放在strategies資料夾內執行)
- backesting：包含回測引擎和引數優化。其中回測引擎定義了資料載入、委託撮合機制、計算與統計相關盈利指標、結果繪圖等函式。
- converter：定義了針對上期所品種平今/平昨模式的委託轉換模組；對於其他品種使用者也可以通過可選引數lock切換至鎖倉模式。
- engine：定義了CTA策略實盤引擎，其中包括：RQData客戶端初始化和資料載入、策略的初始化和啟動、推送Tick訂閱行情到策略中、掛撤單操作、策略的停止和移除等。
- ui：基於PyQt5的GUI圖形應用。

![](https://vnpy-community.oss-cn-shanghai.aliyuncs.com/forum_experience/yazhang/cta_strategy/seix_elementos.png "enter image title here")

&nbsp;

## 資料載入

在實盤中，RQData通過實時載入資料進行策略的初始化。該功能主要在CTA實盤引擎engine.py內實現。
下面介紹具體流程：
- 在選單欄點選“配置”，進入全域性配置頁面輸入RQData賬號密碼；或者直接配置json檔案，即在使用者目錄下.vntrader資料夾找到vt_setting.json，如圖。
  
![](https://vnpy-community.oss-cn-shanghai.aliyuncs.com/forum_experience/yazhang/cta_strategy/RQData_setting.png "enter image title here")

- 初始化RQData客戶端：從vt_setting.json中讀取RQData的賬戶、密碼到rq_client.init()函式進行初始化

```
    def init_rqdata(self):
        """
        Init RQData client.
        """
        username = SETTINGS["rqdata.username"]
        password = SETTINGS["rqdata.password"]
        if not username or not password:
            return

        import rqdatac
        
        self.rq_client = rqdatac
        self.rq_client.init(username, password,
                            ('rqdatad-pro.ricequant.com', 16011))
```


- RQData載入實盤資料：輸入vt_symbol後，首先會轉換成符合RQData格式的rq_symbol，通過get_price()函式下載資料，並且插入到資料庫中。
  
```
    def query_bar_from_rq(
        self, vt_symbol: str, interval: Interval, start: datetime, end: datetime
    ):
        """
        Query bar data from RQData.
        """
        symbol, exchange_str = vt_symbol.split(".")
        rq_symbol = to_rq_symbol(vt_symbol)
        if rq_symbol not in self.rq_symbols:
            return None
        
        end += timedelta(1)     # For querying night trading period data

        df = self.rq_client.get_price(
            rq_symbol,
            frequency=interval.value,
            fields=["open", "high", "low", "close", "volume"],
            start_date=start,
            end_date=end
        )

        data = []
        for ix, row in df.iterrows():
            bar = BarData(
                symbol=symbol,
                exchange=Exchange(exchange_str),
                interval=interval,
                datetime=row.name.to_pydatetime(),
                open_price=row["open"],
                high_price=row["high"],
                low_price=row["low"],
                close_price=row["close"],
                volume=row["volume"],
                gateway_name="RQ"
            )
            data.append(bar)
```

&nbsp;

## 策略開發
CTA策略模板提供完整的訊號生成和委託管理功能，使用者可以基於該模板自行開發策略。新策略可以放在使用者執行的檔案內（推薦），如在c:\users\administrator.vntrader目錄下建立strategies資料夾；可以放在根目錄下vnpy\app\cta_strategy\strategies資料夾內。
注意：策略檔案命名是以下劃線模式，如boll_channel_strategy.py；而策略類命名採用的是駝峰式，如BollChannelStrategy。

下面通過BollChannelStrategy策略示例，來展示策略開發的具體步驟：

### 引數設定

定義策略引數並且初始化策略變數。策略引數為策略類的公有屬性，使用者可以通過建立新的例項來呼叫或者改變策略引數。

如針對rb1905品種，使用者可以建立基於BollChannelStrategy的策略示例，如RB_BollChannelStrategy，boll_window可以由18改成30。

建立策略例項的方法有效地實現了一個策略跑多個品種，並且其策略引數可以通過品種的特徵進行調整。
```
    boll_window = 18
    boll_dev = 3.4
    cci_window = 10
    atr_window = 30
    sl_multiplier = 5.2
    fixed_size = 1

    boll_up = 0
    boll_down = 0
    cci_value = 0
    atr_value = 0

    intra_trade_high = 0
    intra_trade_low = 0
    long_stop = 0
    short_stop = 0
```

### 類的初始化
初始化分3步：
- 通過super( )的方法繼承CTA策略模板，在__init__( )函式傳入CTA引擎、策略名稱、vt_symbol、引數設定。
- 呼叫K線生成模組:通過時間切片來把Tick資料合成1分鐘K線資料，然後更大的時間週期數據，如15分鐘K線。
- 呼叫K線時間序列管理模組：基於K線資料，如1分鐘、15分鐘，來生成相應的技術指標。
  
```
    def __init__(self, cta_engine, strategy_name, vt_symbol, setting):
        """"""
        super(BollChannelStrategy, self).__init__(
            cta_engine, strategy_name, vt_symbol, setting
        )

        self.bg = BarGenerator(self.on_bar, 15, self.on_15min_bar)
        self.am = ArrayManager()
```

### 策略的初始化、啟動、停止
通過“CTA策略”元件的相關功能按鈕實現。

注意：函式load_bar(10)，代表策略初始化需要載入10個交易日的歷史資料。該歷史資料可以是Tick資料，也可以是K線資料。在策略初始化時候，會呼叫K線時間序列管理器計算並快取相關的計算指標，但是並不觸發交易。

```
    def on_init(self):
        """
        Callback when strategy is inited.
        """
        self.write_log("策略初始化")
        self.load_bar(10)

    def on_start(self):
        """
        Callback when strategy is started.
        """
        self.write_log("策略啟動")

    def on_stop(self):
        """
        Callback when strategy is stopped.
        """
        self.write_log("策略停止")
```
### Tick資料回報
策略訂閱某品種合約行情，交易所會推送Tick資料到該策略上。

由於BollChannelStrategy是基於15分鐘K線來生成交易訊號的，故收到Tick資料後，需要用到K線生成模組裡面的update_tick函式，通過時間切片的方法，聚合成1分鐘K線資料，並且推送到on_bar函式。

```
    def on_tick(self, tick: TickData):
        """
        Callback of new tick data update.
        """
        self.bg.update_tick(tick)
```

### K線資料回報

收到推送過來的1分鐘K線資料後，通過K線生成模組裡面的update_bar函式，以分鐘切片的方法，合成15分鐘K線資料，並且推送到on_15min_bar函式。
```
    def on_bar(self, bar: BarData):
        """
        Callback of new bar data update.
        """
        self.bg.update_bar(bar)
```

### 15分鐘K線資料回報

負責CTA訊號的生成，由3部分組成：
- 清空未成交委託：為了防止之前下的單子在上一個15分鐘沒有成交，但是下一個15分鐘可能已經調整了價格，就用cancel_all()方法立刻撤銷之前未成交的所有委託，保證策略在當前這15分鐘開始時的整個狀態是清晰和唯一的。
- 呼叫K線時間序列管理模組：基於最新的15分鐘K線資料來計算相應計算指標，如布林帶通道上下軌、CCI指標、ATR指標
- 訊號計算：通過持倉的判斷以及結合CCI指標、布林帶通道、ATR指標在通道突破點掛出停止單委託（buy/sell)，同時設定離場點(short/cover)。

注意：CTA策略具有低勝率和高盈虧比的特定：在難以提升勝率的情況下，研究提高策略盈虧比有利於策略盈利水平的上升。

```
    def on_15min_bar(self, bar: BarData):
        """"""
        self.cancel_all()

        am = self.am
        am.update_bar(bar)
        if not am.inited:
            return

        self.boll_up, self.boll_down = am.boll(self.boll_window, self.boll_dev)
        self.cci_value = am.cci(self.cci_window)
        self.atr_value = am.atr(self.atr_window)

        if self.pos == 0:
            self.intra_trade_high = bar.high_price
            self.intra_trade_low = bar.low_price

            if self.cci_value > 0:
                self.buy(self.boll_up, self.fixed_size, True)
            elif self.cci_value < 0:
                self.short(self.boll_down, self.fixed_size, True)

        elif self.pos > 0:
            self.intra_trade_high = max(self.intra_trade_high, bar.high_price)
            self.intra_trade_low = bar.low_price

            self.long_stop = self.intra_trade_high - self.atr_value * self.sl_multiplier
            self.sell(self.long_stop, abs(self.pos), True)

        elif self.pos < 0:
            self.intra_trade_high = bar.high_price
            self.intra_trade_low = min(self.intra_trade_low, bar.low_price)

            self.short_stop = self.intra_trade_low + self.atr_value * self.sl_multiplier
            self.cover(self.short_stop, abs(self.pos), True)

        self.put_event()
```

### 委託回報、成交回報、停止單回報

在策略中可以直接pass，其具體邏輯應用交給回測/實盤引擎負責。
```
    def on_order(self, order: OrderData):
        """
        Callback of new order data update.
        """
        pass

    def on_trade(self, trade: TradeData):
        """
        Callback of new trade data update.
        """
        self.put_event()

    def on_stop_order(self, stop_order: StopOrder):
        """
        Callback of stop order update.
        """
        pass
```




&nbsp;

## 回測研究
backtesting.py定義了回測引擎，下面主要介紹相關功能函式，以及回測引擎應用示例：

### 載入策略

把CTA策略邏輯，對應合約品種，以及引數設定（可在策略檔案外修改）載入到回測引擎中。
```
    def add_strategy(self, strategy_class: type, setting: dict):
        """"""
        self.strategy_class = strategy_class
        self.strategy = strategy_class(
            self, strategy_class.__name__, self.vt_symbol, setting
        )
```
&nbsp;

### 載入歷史資料

負責載入對應品種的歷史資料，大概有4個步驟：
- 根據資料型別不同，分成K線模式和Tick模式；
- 通過select().where()方法，有條件地從資料庫中選取資料，其篩選標準包括：vt_symbol、 回測開始日期、回測結束日期、K線週期（K線模式下）；
- order_by(DbBarData.datetime)表示需要按照時間順序載入資料；
- 載入資料是以迭代方式進行的，資料最終存入self.history_data。

```
    def load_data(self):
        """"""
        self.output("開始載入歷史資料")

        if self.mode == BacktestingMode.BAR:
            s = (
                DbBarData.select()
                .where(
                    (DbBarData.vt_symbol == self.vt_symbol) 
                    & (DbBarData.interval == self.interval) 
                    & (DbBarData.datetime >= self.start) 
                    & (DbBarData.datetime <= self.end)
                )
                .order_by(DbBarData.datetime)
            )
            self.history_data = [db_bar.to_bar() for db_bar in s]
        else:
            s = (
                DbTickData.select()
                .where(
                    (DbTickData.vt_symbol == self.vt_symbol) 
                    & (DbTickData.datetime >= self.start) 
                    & (DbTickData.datetime <= self.end)
                )
                .order_by(DbTickData.datetime)
            )
            self.history_data = [db_tick.to_tick() for db_tick in s]

        self.output(f"歷史資料載入完成，資料量：{len(self.history_data)}")
```
&nbsp;

### 撮合成交

載入CTA策略以及相關歷史資料後，策略會根據最新的資料來計算相關指標。若符合條件會生成交易訊號，發出具體委託（buy/sell/short/cover），並且在下一根K線成交。

根據委託型別的不同，回測引擎提供2種撮合成交機制來儘量模模擬實交易環節：

- 限價單撮合成交：（以買入方向為例）先確定是否發生成交，成交標準為委託價>= 下一根K線的最低價；然後確定成交價格，成交價格為委託價與下一根K線開盤價的最小值。

- 停止單撮合成交：（以買入方向為例）先確定是否發生成交，成交標準為委託價<= 下一根K線的最高價；然後確定成交價格，成交價格為委託價與下一根K線開盤價的最大值。

&nbsp;

下面展示在引擎中限價單撮合成交的流程：
- 確定會撮合成交的價格；
- 遍歷限價單字典中的所有限價單，推送委託進入未成交佇列的更新狀態；
- 判斷成交狀態，若出現成交，推送成交資料和委託資料；
- 從字典中刪除已成交的限價單。

```
    def cross_limit_order(self):
        """
        Cross limit order with last bar/tick data.
        """
        if self.mode == BacktestingMode.BAR:
            long_cross_price = self.bar.low_price
            short_cross_price = self.bar.high_price
            long_best_price = self.bar.open_price
            short_best_price = self.bar.open_price
        else:
            long_cross_price = self.tick.ask_price_1
            short_cross_price = self.tick.bid_price_1
            long_best_price = long_cross_price
            short_best_price = short_cross_price

        for order in list(self.active_limit_orders.values()):
            # Push order update with status "not traded" (pending)
            if order.status == Status.SUBMITTING:
                order.status = Status.NOTTRADED
                self.strategy.on_order(order)

            # Check whether limit orders can be filled.
            long_cross = (
                order.direction == Direction.LONG 
                and order.price >= long_cross_price 
                and long_cross_price > 0
            )

            short_cross = (
                order.direction == Direction.SHORT 
                and order.price <= short_cross_price 
                and short_cross_price > 0
            )

            if not long_cross and not short_cross:
                continue

            # Push order udpate with status "all traded" (filled).
            order.traded = order.volume
            order.status = Status.ALLTRADED
            self.strategy.on_order(order)

            self.active_limit_orders.pop(order.vt_orderid)

            # Push trade update
            self.trade_count += 1

            if long_cross:
                trade_price = min(order.price, long_best_price)
                pos_change = order.volume
            else:
                trade_price = max(order.price, short_best_price)
                pos_change = -order.volume

            trade = TradeData(
                symbol=order.symbol,
                exchange=order.exchange,
                orderid=order.orderid,
                tradeid=str(self.trade_count),
                direction=order.direction,
                offset=order.offset,
                price=trade_price,
                volume=order.volume,
                time=self.datetime.strftime("%H:%M:%S"),
                gateway_name=self.gateway_name,
            )
            trade.datetime = self.datetime

            self.strategy.pos += pos_change
            self.strategy.on_trade(trade)

            self.trades[trade.vt_tradeid] = trade
```

&nbsp;

### 計算策略盈虧情況

基於收盤價、當日持倉量、合約規模、滑點、手續費率等計算總盈虧與淨盈虧，並且其計算結果以DataFrame格式輸出，完成基於逐日盯市盈虧統計。

下面展示盈虧情況的計算過程

- 浮動盈虧 = 持倉量 \*（當日收盤價 - 昨日收盤價）\*  合約規模
- 實際盈虧 = 持倉變化量  \* （當時收盤價 - 開倉成交價）\* 合約規模
- 總盈虧 = 浮動盈虧 + 實際盈虧
- 淨盈虧 = 總盈虧 - 總手續費 - 總滑點

```
    def calculate_pnl(
        self,
        pre_close: float,
        start_pos: float,
        size: int,
        rate: float,
        slippage: float,
    ):
        """"""
        self.pre_close = pre_close

        # Holding pnl is the pnl from holding position at day start
        self.start_pos = start_pos
        self.end_pos = start_pos
        self.holding_pnl = self.start_pos * \
            (self.close_price - self.pre_close) * size

        # Trading pnl is the pnl from new trade during the day
        self.trade_count = len(self.trades)

        for trade in self.trades:
            if trade.direction == Direction.LONG:
                pos_change = trade.volume
            else:
                pos_change = -trade.volume

            turnover = trade.price * trade.volume * size

            self.trading_pnl += pos_change * \
                (self.close_price - trade.price) * size
            self.end_pos += pos_change
            self.turnover += turnover
            self.commission += turnover * rate
            self.slippage += trade.volume * size * slippage

        # Net pnl takes account of commission and slippage cost
        self.total_pnl = self.trading_pnl + self.holding_pnl
        self.net_pnl = self.total_pnl - self.commission - self.slippage
```
&nbsp;



### 計算策略統計指標
calculate_statistics函式是基於逐日盯市盈虧情況（DateFrame格式）來計算衍生指標，如最大回撤、年化收益、盈虧比、夏普比率等。

```
            df["balance"] = df["net_pnl"].cumsum() + self.capital
            df["return"] = np.log(df["balance"] / df["balance"].shift(1)).fillna(0)
            df["highlevel"] = (
                df["balance"].rolling(
                    min_periods=1, window=len(df), center=False).max()
            )
            df["drawdown"] = df["balance"] - df["highlevel"]
            df["ddpercent"] = df["drawdown"] / df["highlevel"] * 100

            # Calculate statistics value
            start_date = df.index[0]
            end_date = df.index[-1]

            total_days = len(df)
            profit_days = len(df[df["net_pnl"] > 0])
            loss_days = len(df[df["net_pnl"] < 0])

            end_balance = df["balance"].iloc[-1]
            max_drawdown = df["drawdown"].min()
            max_ddpercent = df["ddpercent"].min()

            total_net_pnl = df["net_pnl"].sum()
            daily_net_pnl = total_net_pnl / total_days

            total_commission = df["commission"].sum()
            daily_commission = total_commission / total_days

            total_slippage = df["slippage"].sum()
            daily_slippage = total_slippage / total_days

            total_turnover = df["turnover"].sum()
            daily_turnover = total_turnover / total_days

            total_trade_count = df["trade_count"].sum()
            daily_trade_count = total_trade_count / total_days

            total_return = (end_balance / self.capital - 1) * 100
            annual_return = total_return / total_days * 240
            daily_return = df["return"].mean() * 100
            return_std = df["return"].std() * 100

            if return_std:
                sharpe_ratio = daily_return / return_std * np.sqrt(240)
            else:
                sharpe_ratio = 0
```
&nbsp;

### 統計指標繪圖
通過matplotlib繪製4幅圖：
- 資金曲線圖
- 資金回撤圖
- 每日盈虧圖
- 每日盈虧分佈圖

```
    def show_chart(self, df: DataFrame = None):
        """"""
        if not df:
            df = self.daily_df
        
        if df is None:
            return

        plt.figure(figsize=(10, 16))

        balance_plot = plt.subplot(4, 1, 1)
        balance_plot.set_title("Balance")
        df["balance"].plot(legend=True)

        drawdown_plot = plt.subplot(4, 1, 2)
        drawdown_plot.set_title("Drawdown")
        drawdown_plot.fill_between(range(len(df)), df["drawdown"].values)

        pnl_plot = plt.subplot(4, 1, 3)
        pnl_plot.set_title("Daily Pnl")
        df["net_pnl"].plot(kind="bar", legend=False, grid=False, xticks=[])

        distribution_plot = plt.subplot(4, 1, 4)
        distribution_plot.set_title("Daily Pnl Distribution")
        df["net_pnl"].hist(bins=50)

        plt.show()
```

&nbsp;

### 單策略回測示例

- 匯入回測引擎和CTA策略
- 設定回測相關引數，如：品種、K線週期、回測開始和結束日期、手續費、滑點、合約規模、起始資金
- 載入策略和資料到引擎中，執行回測。
- 計算基於逐日統計盈利情況，計算統計指標，統計指標繪圖。


```
from vnpy.app.cta_strategy.backtesting import BacktestingEngine
from vnpy.app.cta_strategy.strategies.boll_channel_strategy import (
    BollChannelStrategy,
)
from datetime import datetime

engine = BacktestingEngine()
engine.set_parameters(
    vt_symbol="IF88.CFFEX",
    interval="1m",
    start=datetime(2018, 1, 1),
    end=datetime(2019, 1, 1),
    rate=3.0/10000,
    slippage=0.2,
    size=300,
    pricetick=0.2,
    capital=1_000_000,
)

engine.add_strategy(AtrRsiStrategy, {})
engine.load_data()
engine.run_backtesting()
df = engine.calculate_result()
engine.calculate_statistics()
engine.show_chart()
```

&nbsp;

### 投資組合回測示例

投資組合回測是基於單策略回測的，其關鍵是每個策略都對應著各自的BacktestingEngine物件，下面介紹具體流程：

- 建立回測函式run_backtesting()，這樣每新增一個策略就建立其BacktestingEngine物件。
```
from vnpy.app.cta_strategy.backtesting import BacktestingEngine, OptimizationSetting
from vnpy.app.cta_strategy.strategies.atr_rsi_strategy import AtrRsiStrategy
from vnpy.app.cta_strategy.strategies.boll_channel_strategy import BollChannelStrategy
from datetime import datetime

def run_backtesting(strategy_class, setting, vt_symbol, interval, start, end, rate, slippage, size, pricetick, capital):
    engine = BacktestingEngine()
    engine.set_parameters(
        vt_symbol=vt_symbol,
        interval=interval,
        start=start,
        end=end,
        rate=rate,
        slippage=slippage,
        size=size,
        pricetick=pricetick,
        capital=capital    
    )
    engine.add_strategy(strategy_class, setting)
    engine.load_data()
    engine.run_backtesting()
    df = engine.calculate_result()
    return df
```

&nbsp;

- 分別進行單策略回測，得到各自的DataFrame，(該DataFrame包含交易時間、今倉、昨倉、手續費、滑點、當日淨盈虧、累計淨盈虧等基本資訊，但是不包括最大回撤，夏普比率等統計資訊),然後把DataFrame相加並且去除空值後即得到投資組合的DataFrame。

```
df1 = run_backtesting(
    strategy_class=AtrRsiStrategy, 
    setting={}, 
    vt_symbol="IF88.CFFEX",
    interval="1m", 
    start=datetime(2019, 1, 1), 
    end=datetime(2019, 4, 30),
    rate=0.3/10000,
    slippage=0.2,
    size=300,
    pricetick=0.2,
    capital=1_000_000,
    )

df2 = run_backtesting(
    strategy_class=BollChannelStrategy, 
    setting={'fixed_size': 16}, 
    vt_symbol="RB88.SHFE",
    interval="1m", 
    start=datetime(2019, 1, 1), 
    end=datetime(2019, 4, 30),
    rate=1/10000,
    slippage=1,
    size=10,
    pricetick=1,
    capital=1_000_000,
    )

dfp = df1 + df2
dfp =dfp.dropna() 
```

&nbsp;


- 建立show_portafolio()函式，同樣也是建立新的BacktestingEngine物件，對傳入的DataFrame計算如夏普比率等統計指標，並且畫圖。故該函式不僅能顯示單策略回測效果，也能展示投資組合回測效果。
```
def show_portafolio(df):
    engine = BacktestingEngine()
    engine.calculate_statistics(df)
    engine.show_chart(df)

show_portafolio(dfp)
```

&nbsp;

## 引數優化
引數優化模組主要由3部分構成：

### 引數設定

- 設定引數優化區間：如boll_window設定起始值為18，終止值為24，步進為2，這樣就得到了[18, 20, 22, 24] 這4個待優化的引數了。
- 設定優化目標欄位：如夏普比率、盈虧比、總收益率等。
- 隨機生成引數對組合：使用迭代工具產生引數對組合，然後把引數對組合打包到一個個字典組成的列表中

```
class OptimizationSetting:
    """
    Setting for runnning optimization.
    """

    def __init__(self):
        """"""
        self.params = {}
        self.target_name = ""

    def add_parameter(
        self, name: str, start: float, end: float = None, step: float = None
    ):
        """"""
        if not end and not step:
            self.params[name] = [start]
            return

        if start >= end:
            print("引數優化起始點必須小於終止點")
            return

        if step <= 0:
            print("引數優化步進必須大於0")
            return

        value = start
        value_list = []

        while value <= end:
            value_list.append(value)
            value += step

        self.params[name] = value_list

    def set_target(self, target_name: str):
        """"""
        self.target_name = target_name

    def generate_setting(self):
        """"""
        keys = self.params.keys()
        values = self.params.values()
        products = list(product(*values))

        settings = []
        for p in products:
            setting = dict(zip(keys, p))
            settings.append(setting)

        return settings
```

&nbsp;

### 引數對組合回測

多程序優化時，每個程序都會執行optimize函式，輸出引數對組合以及目標優化欄位的結果。其步驟如下：
- 呼叫回測引擎
- 輸入回測相關設定
- 輸入引數對組合到策略中
- 執行回測
- 返回回測結果，包括：引數對組合、目標優化欄位數值、策略統計指標

```
def optimize(
    target_name: str,
    strategy_class: CtaTemplate,
    setting: dict,
    vt_symbol: str,
    interval: Interval,
    start: datetime,
    rate: float,
    slippage: float,
    size: float,
    pricetick: float,
    capital: int,
    end: datetime,
    mode: BacktestingMode,
):
    """
    Function for running in multiprocessing.pool
    """
    engine = BacktestingEngine()
    engine.set_parameters(
        vt_symbol=vt_symbol,
        interval=interval,
        start=start,
        rate=rate,
        slippage=slippage,
        size=size,
        pricetick=pricetick,
        capital=capital,
        end=end,
        mode=mode
    )

    engine.add_strategy(strategy_class, setting)
    engine.load_data()
    engine.run_backtesting()
    engine.calculate_result()
    statistics = engine.calculate_statistics()

    target_value = statistics[target_name]
    return (str(setting), target_value, statistics)
```

&nbsp;

### 多程序優化

- 根據CPU的核數來建立程序：若CPU為4核，則建立4個程序
- 在每個程序都呼叫apply_async( )的方法執行引數對組合回測，其回測結果新增到results中 （apply_async是非同步非阻塞的，即不用等待當前程序執行完畢，隨時根據系統排程來進行程序切換。）
- pool.close()與pool.join()用於程序跑完任務後，去關閉程序。
- 對results的內容通過目標優化欄位標準進行排序，輸出結果。

```
        pool = multiprocessing.Pool(multiprocessing.cpu_count())

        results = []
        for setting in settings:
            result = (pool.apply_async(optimize, (
                target_name,
                self.strategy_class,
                setting,
                self.vt_symbol,
                self.interval,
                self.start,
                self.rate,
                self.slippage,
                self.size,
                self.pricetick,
                self.capital,
                self.end,
                self.mode
            )))
            results.append(result)

        pool.close()
        pool.join()

        # Sort results and output
        result_values = [result.get() for result in results]
        result_values.sort(reverse=True, key=lambda result: result[1])

        for value in result_values:
            msg = f"引數：{value[0]}, 目標：{value[1]}"
            self.output(msg)

        return result_values
```

&nbsp;

## 實盤執行
在實盤環境，使用者可以基於編寫好的CTA策略來建立新的例項，一鍵初始化、啟動、停止策略。


### 建立策略例項
使用者可以基於編寫好的CTA策略來建立新的例項，策略例項的好處在於同一個策略可以同時去執行多個品種合約，並且每個例項的引數可以是不同的。
在建立例項的時候需要填寫如圖的例項名稱、合約品種、引數設定。注意：例項名稱不能重名；合約名稱是vt_symbol的格式，如IF1905.CFFEX。

![](https://vnpy-community.oss-cn-shanghai.aliyuncs.com/forum_experience/yazhang/cta_strategy/add_strategy.png)

建立策略流程如下：
- 檢查策略例項重名
- 新增策略配置資訊(strategy_name, vt_symbol, setting)到strategies字典上
- 新增該策略要訂閱行情的合約資訊到symbol_strategy_map字典中；
- 把策略配置資訊儲存到json檔案內；
- 在圖形化介面更新狀態資訊。

```
    def add_strategy(
        self, class_name: str, strategy_name: str, vt_symbol: str, setting: dict
    ):
        """
        Add a new strategy.
        """
        if strategy_name in self.strategies:
            self.write_log(f"建立策略失敗，存在重名{strategy_name}")
            return

        strategy_class = self.classes[class_name]

        strategy = strategy_class(self, strategy_name, vt_symbol, setting)
        self.strategies[strategy_name] = strategy

        # Add vt_symbol to strategy map.
        strategies = self.symbol_strategy_map[vt_symbol]
        strategies.append(strategy)

        # Update to setting file.
        self.update_strategy_setting(strategy_name, setting)

        self.put_strategy_event(strategy)
```

&nbsp;

### 初始化策略
- 呼叫策略類的on_init()回撥函式,並且載入歷史資料；
- 恢復上次退出之前的策略狀態；
- 從.vntrader/cta_strategy_data.json內讀取策略引數，最新的技術指標，以及持倉數量；
- 呼叫介面的subcribe()函式訂閱指定行情資訊；
- 策略初始化狀態變成True，並且更新到日誌上。
  
```
    def _init_strategy(self):
        """
        Init strategies in queue.
        """
        while not self.init_queue.empty():
            strategy_name = self.init_queue.get()
            strategy = self.strategies[strategy_name]

            if strategy.inited:
                self.write_log(f"{strategy_name}已經完成初始化，禁止重複操作")
                continue

            self.write_log(f"{strategy_name}開始執行初始化")

            # Call on_init function of strategy
            self.call_strategy_func(strategy, strategy.on_init)

            # Restore strategy data(variables)
            data = self.strategy_data.get(strategy_name, None)
            if data:
                for name in strategy.variables:
                    value = data.get(name, None)
                    if value:
                        setattr(strategy, name, value)

            # Subscribe market data
            contract = self.main_engine.get_contract(strategy.vt_symbol)
            if contract:
                req = SubscribeRequest(
                    symbol=contract.symbol, exchange=contract.exchange)
                self.main_engine.subscribe(req, contract.gateway_name)
            else:
                self.write_log(f"行情訂閱失敗，找不到合約{strategy.vt_symbol}", strategy)

            # Put event to update init completed status.
            strategy.inited = True
            self.put_strategy_event(strategy)
            self.write_log(f"{strategy_name}初始化完成")
        
        self.init_thread = None
```

&nbsp;

### 啟動策略
- 檢查策略初始化狀態；
- 檢查策略啟動狀態，避免重複啟動；
- 呼叫策略類的on_start()函式啟動策略；
- 策略啟動狀態變成True，並且更新到圖形化介面上。

```
    def start_strategy(self, strategy_name: str):
        """
        Start a strategy.
        """
        strategy = self.strategies[strategy_name]
        if not strategy.inited:
            self.write_log(f"策略{strategy.strategy_name}啟動失敗，請先初始化")
            return

        if strategy.trading:
            self.write_log(f"{strategy_name}已經啟動，請勿重複操作")
            return

        self.call_strategy_func(strategy, strategy.on_start)
        strategy.trading = True

        self.put_strategy_event(strategy)
```

&nbsp;

### 停止策略
- 檢查策略啟動狀態；
- 呼叫策略類的on_stop()函式停止策略；
- 更新策略啟動狀態為False；
- 對所有為成交的委託（市價單/限價單/本地停止單）進行撤單操作；
- 把策略引數，最新的技術指標，以及持倉數量儲存到.vntrader/cta_strategy_data.json內；
- 在圖形化介面更新策略狀態。

```
    def stop_strategy(self, strategy_name: str):
        """
        Stop a strategy.
        """
        strategy = self.strategies[strategy_name]
        if not strategy.trading:
            return

        # Call on_stop function of the strategy
        self.call_strategy_func(strategy, strategy.on_stop)

        # Change trading status of strategy to False
        strategy.trading = False

        # Cancel all orders of the strategy
        self.cancel_all(strategy)

        # Sync strategy variables to data file
        self.sync_strategy_data(strategy)

        # Update GUI
        self.put_strategy_event(strategy)
```

&nbsp;

### 編輯策略
- 重新配置策略引數字典setting；
- 更新引數字典到策略中；
- 在影象化介面更新策略狀態。

```
    def edit_strategy(self, strategy_name: str, setting: dict):
        """
        Edit parameters of a strategy.
        """
        strategy = self.strategies[strategy_name]
        strategy.update_setting(setting)

        self.update_strategy_setting(strategy_name, setting)
        self.put_strategy_event(strategy)
```

&nbsp;

### 移除策略
- 檢查策略狀態，只有停止策略後從可以移除策略；
- 從json檔案移除策略配置資訊(strategy_name, vt_symbol, setting)；
- 從symbol_strategy_map字典中移除該策略訂閱的合約資訊；
- 從strategy_orderid_map字典移除活動委託記錄；
- 從strategies字典移除該策略的相關配置資訊。

```
    def remove_strategy(self, strategy_name: str):
        """
        Remove a strategy.
        """
        strategy = self.strategies[strategy_name]
        if strategy.trading:
            self.write_log(f"策略{strategy.strategy_name}移除失敗，請先停止")
            return

        # Remove setting
        self.remove_strategy_setting(strategy_name)

        # Remove from symbol strategy map
        strategies = self.symbol_strategy_map[strategy.vt_symbol]
        strategies.remove(strategy)

        # Remove from active orderid map
        if strategy_name in self.strategy_orderid_map:
            vt_orderids = self.strategy_orderid_map.pop(strategy_name)

            # Remove vt_orderid strategy map
            for vt_orderid in vt_orderids:
                if vt_orderid in self.orderid_strategy_map:
                    self.orderid_strategy_map.pop(vt_orderid)

        # Remove from strategies
        self.strategies.pop(strategy_name)

        return True
```

&nbsp;

### 鎖倉操作

使用者在編寫策略時，可以通過填寫lock欄位來讓策略完成鎖倉操作，即禁止平今，通過反向開倉來代替。

- 在cta策略模板template中，可以看到如下具體委託函式都有lock欄位，並且預設為False。

```
    def buy(self, price: float, volume: float, stop: bool = False, lock: bool = False):
        """
        Send buy order to open a long position.
        """
        return self.send_order(Direction.LONG, Offset.OPEN, price, volume, stop, lock)

    def sell(self, price: float, volume: float, stop: bool = False, lock: bool = False):
        """
        Send sell order to close a long position.
        """
        return self.send_order(Direction.SHORT, Offset.CLOSE, price, volume, stop, lock)

    def short(self, price: float, volume: float, stop: bool = False, lock: bool = False):
        """
        Send short order to open as short position.
        """
        return self.send_order(Direction.SHORT, Offset.OPEN, price, volume, stop, lock)

    def cover(self, price: float, volume: float, stop: bool = False, lock: bool = False):
        """
        Send cover order to close a short position.
        """
        return self.send_order(Direction.LONG, Offset.CLOSE, price, volume, stop, lock)

    def send_order(
        self,
        direction: Direction,
        offset: Offset,
        price: float,
        volume: float,
        stop: bool = False,
        lock: bool = False
    ):
        """
        Send a new order.
        """
        if self.trading:
            vt_orderids = self.cta_engine.send_order(
                self, direction, offset, price, volume, stop, lock
            )
            return vt_orderids
        else:
            return []
```

&nbsp;

- 設定lock=True後，cta實盤引擎send_order()函式發生響應，並且呼叫其最根本的委託函式send_server_order()去處理鎖倉委託轉換。首先是建立原始委託original_req，然後呼叫converter檔案裡面OffsetConverter類的convert_order_request來進行相關轉換。

```
    def send_order(
        self,
        strategy: CtaTemplate,
        direction: Direction,
        offset: Offset,
        price: float,
        volume: float,
        stop: bool,
        lock: bool
    ):
        """
        """
        contract = self.main_engine.get_contract(strategy.vt_symbol)
        if not contract:
            self.write_log(f"委託失敗，找不到合約：{strategy.vt_symbol}", strategy)
            return ""

        if stop:
            if contract.stop_supported:
                return self.send_server_stop_order(strategy, contract, direction, offset, price, volume, lock)
            else:
                return self.send_local_stop_order(strategy, direction, offset, price, volume, lock)
        else:
            return self.send_limit_order(strategy, contract, direction, offset, price, volume, lock)

    def send_limit_order(
        self,
        strategy: CtaTemplate,
        contract: ContractData,
        direction: Direction,
        offset: Offset,
        price: float,
        volume: float,
        lock: bool
    ):
        """
        Send a limit order to server.
        """
        return self.send_server_order(
            strategy,
            contract,
            direction,
            offset,
            price,
            volume,
            OrderType.LIMIT,
            lock
        )

    def send_server_order(
        self,
        strategy: CtaTemplate,
        contract: ContractData,
        direction: Direction,
        offset: Offset,
        price: float,
        volume: float,
        type: OrderType,
        lock: bool
    ):
        """
        Send a new order to server.
        """
        # Create request and send order.
        original_req = OrderRequest(
            symbol=contract.symbol,
            exchange=contract.exchange,
            direction=direction,
            offset=offset,
            type=type,
            price=price,
            volume=volume,
        )

        # Convert with offset converter
        req_list = self.offset_converter.convert_order_request(original_req, lock)

        # Send Orders
        vt_orderids = []

        for req in req_list:
            vt_orderid = self.main_engine.send_order(
                req, contract.gateway_name)
            vt_orderids.append(vt_orderid)

            self.offset_converter.update_order_request(req, vt_orderid)
            
            # Save relationship between orderid and strategy.
            self.orderid_strategy_map[vt_orderid] = strategy
            self.strategy_orderid_map[strategy.strategy_name].add(vt_orderid)

        return vt_orderids        
```

&nbsp;

- 在convert_order_request_lock()函式中，先計算今倉的量和昨可用量；然後進行判斷：若有今倉，只能開倉（鎖倉）；無今倉時候，若平倉量小於等於昨可用，全部平昨，反之，先平昨，剩下的反向開倉。

```
    def convert_order_request_lock(self, req: OrderRequest):
        """"""
        if req.direction == Direction.LONG:
            td_volume = self.short_td
            yd_available = self.short_yd - self.short_yd_frozen
        else:
            td_volume = self.long_td
            yd_available = self.long_yd - self.long_yd_frozen

        # If there is td_volume, we can only lock position
        if td_volume:
            req_open = copy(req)
            req_open.offset = Offset.OPEN
            return [req_open]
        # If no td_volume, we close opposite yd position first
        # then open new position
        else:
            open_volume = max(0,  req.volume - yd_available)
            req_list = []

            if yd_available:
                req_yd = copy(req)
                if self.exchange == Exchange.SHFE:
                    req_yd.offset = Offset.CLOSEYESTERDAY
                else:
                    req_yd.offset = Offset.CLOSE
                req_list.append(req_yd)

            if open_volume:
                req_open = copy(req)
                req_open.offset = Offset.OPEN
                req_open.volume = open_volume
                req_list.append(req_open)

            return req_list

```
