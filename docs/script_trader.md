# 指令碼策略
ScriptTrader模組提供了互動式的量化分析和程式化交易功能，又提供以整個策略連續執行的指令碼策略功能。

故其可視為直接利用Python對證券交易客戶端進行操作。它與CTA策略模組的區別在於：
- 突破了單交易所，單標的的限制，
- 可以較方便的實現如股指期貨和一籃子股票之間的對衝策略、跨品種套利、股票市場掃描自動化選股等功能。

&nbsp;

## Jupyter模式

### 載入啟動
Jupyter模式是基於指令碼引擎（ScriptEngine）驅動的。首先開啟Jupyter notebook後，然後載入元件、初始化指令碼引擎。其中：
```
from vnpy.app.script_trader import init_cli_trading
from vnpy.gateway.ctp import CtpGateway
engine = init_cli_trading([CtpGateway])
```

其中：
- 指令碼引擎可以支援同時連線多個介面，如CTP、BITMEX、OES等；
- init_cli_trading(gateways: Sequence[BaseGateway])可以將多個介面類，以列表的形式傳遞給init_cli_trading；
- init_cli_trading可視為vnpy封好的初始化啟動函式，對主引擎、指令碼引擎等各種物件進行了封裝。

&nbsp;

### 連線介面
不同介面需要不同的配置引數，SimNow的配置如下：
```
setting = {
    "使用者名稱": "xxxx",
    "密碼": "xxxx",
    "經紀商程式碼": "9999",
    "交易伺服器":"tcp://180.168.146.187：10101",
    "行情伺服器":"tcp://180.168.146.187：10111",
    "產品名稱":"simnow_xxx_test",
    "授權編碼":"0000000000000000",
    "產品資訊": ""
}
engine.connect_gateway(setting,"CTP")
```

setting配置如下圖所示，其他介面配置可以參考vnpy/gateway目錄下的介面類的default_setting來填寫。

![](https://static.vnpy.com/upload/temp/82dd7cfd-6a98-4908-a770-582cfb7e69bc.jpg)


&nbsp;

### 查詢資料
這裡介紹一下連線上交易介面併成功訂閱資料後的資料儲存：
- 底層介面不停向主引擎推送新的資料；
- 主引擎裡維護著一個ticks字典用於快取不同標的的最新tick資料（僅能快取最新的）；
- use_df的作用是轉換成DataFrame格式，便於資料分析。

&nbsp;

### 訂閱行情
subscribe()函式用於訂閱行情資訊，若需要訂閱一籃子合約的行情，可以使用列表格式。
```
engine.subscribe(vt_symbols = ["rb1909.SHFE","rb1910.SHFE"])
```

&nbsp;

## 指令碼策略模式

### 載入啟動
- 若使用指令碼策略模式，需要提前編寫相關指令碼策略檔案，如demo_arbitrage.py,
- 然後開啟VnTrader,在選單欄"功能"處開啟"指令碼策略",在跳出的指令碼策略視窗最上方開啟/Path-To-demo_arbitrage.py/demo_arbitrage.py，然後
- 點選如下圖的“啟動”。
![](https://static.vnpy.com/upload/temp/bf6b06f8-26e9-466b-b3e0-5b3a6f99e6ba.jpg)

&nbsp;

### 指令碼策略
指令碼策略檔案編寫需要遵循一定格式,下面提供使用模板，其作用為：
- 訂閱兩個品種的行情；
- 打印合約資訊；
- 每隔3秒獲取最新行情。
```
from time import sleep
from vnpy.app.script_trader import ScriptEngine

def run(engine: ScriptEngine):
    """"""
    vt_symbols = ["IF1912.CFFEX", "rb2001.SHFE"]

    # 訂閱行情
    engine.subscribe(vt_symbols)

    # 獲取合約資訊
    for vt_symbol in vt_symbols:
        contract = engine.get_contract(vt_symbol)
        msg = f"合約資訊，{contract}"
        engine.write_log(msg)

    # 持續執行，使用strategy_active來判斷是否要退出程式
    while engine.strategy_active:
        # 輪詢獲取行情
        for vt_symbol in vt_symbols:
            tick = engine.get_tick(vt_symbol)
            msg = f"最新行情, {tick}"
            engine.write_log(msg)

        # 等待3秒進入下一輪
        sleep(3)
```

&nbsp;

### 執行控制
engine.strategy_active用於控制While迴圈，可視作是指令碼策略的開關：
- 點選“啟動”按鈕，啟動While迴圈，執行指令碼策略；
- 點選“停止”按鈕，退出While迴圈，停止指令碼策略。

&nbsp;

## 函式功能說明

### 單條查詢

get_tick：查詢單個標的最新tick，use_df為可選引數，用於把返回的類物件轉化成DataFrame格式，便於資料分析。
```
tick = engine.get_tick(vt_symbol="rb1910.SHFE",use_df=False)
```

其中：
- vt_symbol：為本地合約程式碼，格式是合約品種+交易所，如rb1910.SHFE。
- use_df：為bool變數，預設False，返回TickData類物件，否則返回相應DataFrame，如圖。

![](https://static.vnpy.com/upload/temp/d00ca165-1266-4812-afaa-f6723745d6a4.png)

&nbsp;

get_order：根據vt_orderid查詢委託單的詳細資訊。
```
order = engine.get_order(vt_orderid='CTP.3_-9351590_1',use_df=False)
```

其中，vt_orderid為本地委託號，在委託下單時，會自動返回該委託的vt_orderid：
- 以"CTP.3_-9351590_1"為例，它由ctp介面的name,frontid,sessionid,order_ref構成；
- frontid和sessionid在vnpy連線上CTP介面後由CTP回撥產生；
- order_ref是vnpy內部維護的用於區分order的一個變數。

![](https://static.vnpy.com/upload/temp/ae9f6d7f-49da-41e4-a862-825bf146118d.png)

&nbsp;

get_contract：根據本地vt_symbol來查詢對應合約物件的詳細資訊。
```
contract = engine.get_contract(vt_symbol="rb1910.SHFE",use_df=False)
```

![](https://static.vnpy.com/upload/temp/4111776b-91fd-44e6-8b2c-289961862a3a.jpg)

&nbsp;

get_bars：查詢歷史資料。（需要初始化RQData客戶端）
```
bars = engine.get_bars(vt_symbol="rb1910.SHFE",start_date="20190101",
                        interval=Interval.MINUTE,use_df=False)
```

其中：
- vt_symbol：本地合約程式碼。
- start_date：起始日期，格式必須為"%Y%m%d"。
- interval：K線週期，包括：分鐘、小時、日、周
- bars：包含了一系列BarData資料的列表物件，其BarData的定義如下：
```
@dataclass
class BarData(BaseData):

    symbol: str
    exchange: Exchange
    datetime: datetime
    interval: Interval = None
    volume: float = 0
    open_interest: float = 0
    open_price: float = 0
    high_price: float = 0
    low_price: float = 0
    close_price: float = 0

    def __post_init__(self):
        self.vt_symbol = f"{self.symbol}.{self.exchange.value}"
```

&nbsp;

get_position：根據vt_positionid來查詢持倉情況，返回物件包含介面名稱、交易所、合約程式碼、數量、凍結數量等。
```
position = engine.get_position(vt_positionid='rb1909.SHFE.Direction.LONG')
```
注意，vt_positionid為vnpy內部對於一筆特定持倉的唯一持倉編號，格式為"vt_symbol.Direction.LONG",其中持倉方向可選多倉、空倉和淨持倉，如圖。

![](https://static.vnpy.com/upload/temp/4c585dac-0ac9-4fd8-9926-ddc104512359.jpg)

&nbsp;

### 多條查詢
get_ticks：查詢多個合約最新tick。
```
ticks = engine.get_ticks(vt_symbols=['rb1910.SHFE','rb1909.SHFE'],use_df = True)
```

vt_symbols是列表格式，裡面包含多個vt_symbol，如圖。

![](https://static.vnpy.com/upload/temp/311e1ee8-1a3d-496f-833f-bbb7a3a624ab.png)

&nbsp;

get_orders：根據查詢多個vt_orderid查詢其詳細資訊。vt_orderids為列表，裡面包含多個vt_orderid
```
orders = engine.get_orders([orderid_one,orderid_two],use_df=True)
```


&nbsp;

get_trades：根據給定的一個vt_orderid返回這次報單過程中的所有TradeData物件。vt_orderid是本地委託號，每一個委託OrderData，由於部分成交關係，可以對應多筆成交TradeData。
```
trades = engine.get_trades(vt_orderid = your_vt_orderid,use_df = True)
```

&nbsp;

### 全量查詢

在全量查詢中，唯一引數是use_df，預設為False，返回的是一個包含相應資料的List物件,例如ContractData，AccountData，PositionData。

- get_all_contracts：預設返回一個list，包含了全市場的ContractData，如果use_df=True則返回相應的DataFrame；
- get_all_active_orders：活動委託指的是等待委託完全成交，故其狀態包含“已提交的、未成交的、部分成交”；函式將返回包含一系列OrderData的列表物件；
- get_all_accounts：預設返回包含AccountData的列表物件；
- get_all_position：預設返回包含PositionData的列表物件，如圖。

![](https://static.vnpy.com/upload/temp/5d698a27-545b-46bb-9d16-428a8ccb7956.png)

&nbsp;

### 交易委託

以委託買入為例，engine.buy()函式入參包括：
- vt_symbol：本地合約程式碼（字串格式）
- price：報單價格（浮點數型別）;
- volume：報單數量（浮點數型別）;
- order_type：OrderType列舉常量，預設為限價單（OrderType.LIMIT），同時支援停止單（OrderType.STOP）、FAK（OrderType.FAK）、FOK（OrderType.FOK）、市價單（OrderType.MARKET），不同交易所支援報單方式不完全一致。
```
engine.buy(vt_symbol = "rb1910.SHFE", price = 3200, volume = 1, order_type=OrderType.LIMIT)
```

執行交易委託後會返回本地委託號vt_orderid，撤單也是基於該本地委託號的
```
engine.cancel_order(vt_orderid = 'CTP.3_-9351590_1')
```

&nbsp;

### 資訊輸出
write_log()函式可用於記錄買賣時的交易情況，將資訊輸出在指令碼策略視窗下方空白欄裡。

&nbsp;

send_email()函式用於實時通過email通知使用者策略執行情況：
- 先在vt_setting.json下配置email相關資訊；
- 郵件標題為“指令碼策略引擎通知”；
- msg為字串格式，表示郵件正文內容，如圖。
```
engine.send_email(msg = "Your Msg")
```

![](https://static.vnpy.com/upload/temp/8dd8d6b0-6c04-4cb4-a426-ad43d11a13eb.png)

使用郵箱前需要開通SMTP服務。
- email.server：郵件伺服器地址，vnpy預設填寫好了QQ郵箱伺服器地址，不用改可以直接用，如果需要使用其他郵箱，需要自行查詢一下其他的伺服器地址。
- email.port：郵件伺服器埠號，vnpm預設填好了QQ郵箱伺服器埠，可直接用。
- email.username：填寫郵箱地址即可，如xxxx@qq.com。
- email.password：對於QQ郵箱，此處不是郵箱密碼，而是開通SMTP後系統生成的一個授權碼。
- email.sendert：email.username。
- email.receiver：接受郵件的郵箱地址，比如xxxx@outlook.com。
