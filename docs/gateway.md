# 交易介面

## 如何連線

從gateway資料夾上引入介面程式，通過add_gateway()函式調動，最終展示到圖形化操作介面VN Trader中。

在選單欄中點選"系統"->"連線CTP”按鈕會彈出如圖賬號配置視窗，輸入賬號、密碼等相關資訊即連線介面，並立刻進行查詢工作: 如查詢賬號資訊、查詢持倉、查詢委託資訊、查詢成交資訊等。

![](https://vnpy-community.oss-cn-shanghai.aliyuncs.com/forum_experience/yazhang/gateway/login.png)

&nbsp;

### 載入需要用的介面

載入介面示例在根目錄"tests\trader"資料夾的run.py檔案中。
- 從gateway資料夾引入介面類檔案，如from vnpy.gateway.ctp import CtpGateway;
- 建立事件引擎物件並且通過add_gateway()函式新增介面程式;
- 建立圖形化物件main_window，以VN Trader操作介面展示出來。


```
from vnpy.gateway.ctp import CtpGateway

def main():
    """"""
    qapp = create_qapp()
    main_engine = MainEngine(event_engine)
    main_engine.add_gateway(CtpGateway)
    main_window = MainWindow(main_engine, event_engine)
    main_window.showMaximized()
    qapp.exec()
```

&nbsp;


### 配置和連線

開啟cmd視窗，使用命令“Python run.py"即可進入VN Trader操作介面。在左上方的選單欄中點選"系統"->"連線CTP”按鈕會彈出賬號配置視窗，輸入賬號、密碼等相關資訊即連線介面。

連線介面的流程首先是初始化賬戶資訊，然後呼叫connet()函式來連線交易埠和行情埠。
- 交易埠：查詢使用者相關資訊（如賬戶資金、持倉、委託記錄、成交記錄）、查詢可交易合約資訊、掛撤單操作；
- 行情埠：接收訂閱的行情資訊推送、接收使用者相關資訊（如賬戶資金更新、持倉更新、委託推送、成交推送）更新的回撥推送。


&nbsp;


### 修改json配置檔案

介面配置相關儲存在json檔案中，放在如圖C盤使用者目錄下的.vntrader資料夾內。

![](https://vnpy-community.oss-cn-shanghai.aliyuncs.com/forum_experience/yazhang/gateway/.vntrader.png)

所以要修改介面配置檔案，使用者即可以在圖形化介面VN Trader內修改，也可以直接在.vntrader修改json檔案。
另外將json配置檔案分離於vnpy的好處在於：避免每次升級都要重新配置json檔案。


&nbsp;


### 檢視可交易的合約

先登入介面，然後在選單欄中點選"幫助"->"查詢合約”按鈕會空白的“查詢合約”視窗。點選“查詢”按鈕後才會顯示查詢結果，如圖。

![](https://vnpy-community.oss-cn-shanghai.aliyuncs.com/forum_experience/yazhang/gateway/query_contract.png)



&nbsp;

## 介面分類

| 介面     |                    型別                    |
| -------- | :----------------------------------------: |
| CTP      |                    期貨                    |
| MINI     |                    期貨                    |
| FEMAS    |                    期貨                    |
| XTP      | 國內股票、指數、基金、債券、期權、融資融券 |
| OES      |                  國內股票                  |
| TORA     |                  國內股票                  |
| IB       |            外盤股票、期貨、期權            |
| TAP      |               外盤期貨、期權               |
| FUTU     |            國內股票、港股、美股            |
| TIGER    |            國內股票、港股、美股            |
| ALPACA   |                    美股                    |
| BITFINEX |                  數字貨幣                  |
| BITMEX   |                  數字貨幣                  |
| BINANCE  |                  數字貨幣                  |
| OKEX     |                  數字貨幣                  |
| OKEXF    |                  數字貨幣                  |
| HUOBI    |                  數字貨幣                  |
| HUOBIF   |                  數字貨幣                  |
| ONETOKEN |                  數字貨幣                  |
| RPC      |                  RPC服務                   |



&nbsp;


## 介面詳解

### CTP

#### 如何載入

run.py檔案提供了介面載入示例：先從gateway上呼叫ctpGateway類；然後通過add_gateway()函式新增到main_engine上。
```
from vnpy.gateway.ctp import CtpGateway
main_engine.add_gateway(CtpGateway)
```

&nbsp;

#### 相關欄位

- 使用者名稱：username
- 密碼：password：
- 經紀商編號：brokerid
- 交易伺服器地址：td_address
- 行情伺服器地址：md_address
- 產品名稱：product_info
- 授權編碼：auth_code
  
&nbsp;

#### 獲取賬號

- 模擬賬號：從SimNow網站上獲取。只需輸入手機號碼和簡訊驗證即可。（簡訊驗證有時只能在工作日正常工作時段收到）SimNow的使用者名稱為6位純數字，經紀商編號為9999，並且提供2套環境用於盤中模擬交易以及盤後的測試。
  
- 實盤賬號：在期貨公司開戶，通過聯絡客戶經理可以開通。使用者名稱為純數字，經紀商編號也是4位純數字。（每個期貨公司的經紀商編號都不同）另外，實盤賬號也可以開通模擬交易功能，同樣需要聯絡客戶經理。


&nbsp;

### MINI

#### 如何載入

先從gateway上呼叫MiniGateway類；然後通過add_gateway()函式新增到main_engine上。
```
from vnpy.gateway.mini import MiniGateway
main_engine.add_gateway(MiniGateway)
```

&nbsp;

#### 相關欄位

- 使用者名稱：username
- 密碼：password：
- 經紀商編號：brokerid
- 交易伺服器地址：td_address
- 行情伺服器地址：md_address
- 產品名稱：product_info
- 授權編碼：auth_code
  
&nbsp;

#### 獲取賬號

在期貨公司開戶，通過聯絡客戶經理可以開通。使用者名稱為純數字，經紀商編號也是4位純數字。（每個期貨公司的經紀商編號都不同）另外，實盤賬號也可以開通模擬交易功能，同樣需要聯絡客戶經理。


&nbsp;

### 飛馬（FEMAS）

#### 如何載入

先從gateway上呼叫FemasGateway類；然後通過add_gateway()函式新增到main_engine上。
```
from vnpy.gateway.femas import FemasGateway
main_engine.add_gateway(FemasGateway)
```

&nbsp;

#### 相關欄位

- 使用者名稱：username
- 密碼：password：
- 經紀商編號：brokerid
- 交易伺服器地址：td_address
- 行情伺服器地址：md_address
- 產品名稱：product_info
- 授權編碼：auth_code
  
&nbsp;

#### 獲取賬號

在期貨公司開戶，通過聯絡客戶經理可以開通。使用者名稱為純數字，經紀商編號也是4位純數字。（每個期貨公司的經紀商編號都不同）另外，實盤賬號也可以開通模擬交易功能，同樣需要聯絡客戶經理。


&nbsp;



### 中泰櫃檯(XTP)

#### 如何載入

先從gateway上呼叫XtpGateway類；然後通過add_gateway()函式新增到main_engine上。
```
from vnpy.gateway.xtp import XtpGateway
main_engine.add_gateway(XtpGateway)
```

&nbsp;


#### 相關欄位

- 賬號：
- 密碼：
- 客戶號": 1
- 行情地址：
- 行情埠": 0
- 交易地址：
- 交易埠": 0
- 行情協議: ["TCP", "UDP"]
- 授權碼：

&nbsp;


#### 獲取賬號

測試賬號請聯絡中泰證券申請。

#### 其他特點

XTP是首家提供融資融券的極速櫃檯。

&nbsp;


### 寬睿櫃檯(OES)

#### 如何載入

先從gateway上呼叫OesGateway類；然後通過add_gateway()函式新增到main_engine上。
```
from vnpy.gateway.oes import OesGateway
main_engine.add_gateway(OesGateway)
```

&nbsp;


#### 相關欄位

- 使用者名稱：username
- 密碼：password
- 硬碟序列號：hdd_serial
- 交易委託伺服器：td_ord_server
- 交易回報伺服器：td_rpt_server
- 交易查詢伺服器：td_qry_server
- 行情推送伺服器：md_tcp_server
- 行情查詢伺服器：md_qry_server

&nbsp;


#### 獲取賬號

測試賬號請聯絡寬睿科技申請

&nbsp;

#### 其他特點

寬睿櫃檯提供內網UDP低延時組播行情以及實時成交資訊推送。

&nbsp;


### 華鑫奇點(TORA)

#### 如何載入

先從gateway上呼叫ToraGateway類；然後通過add_gateway()函式新增到main_engine上。
```
from vnpy.gateway.tota import ToraGateway
main_engine.add_gateway(OesGateway)
```

&nbsp;

#### 相關欄位

- 賬號: username
- 密碼: password
- 交易伺服器: td_address
- 行情伺服器: md_address

&nbsp;

#### 獲取賬號

測試賬號請聯絡華鑫證券申請


&nbsp;

### 盈透證券(IB)

#### 如何載入

先從gateway上呼叫IbGateway類；然後通過add_gateway()函式新增到main_engine上。
```
from vnpy.gateway.ib import IbGateway
main_engine.add_gateway(IbGateway)
```

&nbsp;


#### 相關欄位

- TWS地址：127.0.0.1
- TWS埠：7497
- 客戶號：1


&nbsp;


#### 獲取賬號

在盈透證券開戶並且入金後可以獲得API接入許可權。擁有實盤賬號後才可以申請開通模擬交易賬號。

&nbsp;

#### 其他特點

可交易品種幾乎覆蓋全球的股票、期權、期權；手續費相對較低。

注意IB介面的合約程式碼較為特殊，請前往官網的產品查詢板塊查詢，VN Trader中使用的是盈透證券對於每個合約在某一交易所的唯一識別符號ConId來作為合約程式碼，而非Symbol或者LocalName。

&nbsp;


### 易盛外盤(TAP)

#### 如何載入

先從gateway上呼叫TapGateway類；然後通過add_gateway()函式新增到main_engine上。
```
from vnpy.gateway.tap import TapGateway
main_engine.add_gateway(TapGateway)
```

&nbsp;


#### 相關欄位

- 授權碼：auth code
- 行情賬號：quote username
- 行情密碼：quote password
- 行情地址：123.15.58.21
- 行情埠：7171



&nbsp;


#### 獲取賬號

在TAP開戶並且入金後可以獲得API接入許可權。

&nbsp;


### 富途證券(FUTU)

#### 如何載入

先從gateway上呼叫FutuGateway類；然後通過add_gateway()函式新增到main_engine上。
```
from vnpy.gateway.futu import FutuGateway
main_engine.add_gateway(FutuGateway)
```

&nbsp;


#### 相關欄位

- 地址：127.0.0.1
- 密碼：
- 埠：11111
- 市場：HK 或 US
- 環境：TrdEnv.REAL 或 TrdEnv.SIMULATE


&nbsp;


#### 獲取賬號

在富途證券開戶並且入金後可以獲得API接入許可權。擁有實盤賬號後才可以申請開通模擬交易賬號。






&nbsp;

### 老虎證券(TIGER)


#### 如何載入

先從gateway上呼叫TigerGateway類；然後通過add_gateway()函式新增到main_engine上。
```
from vnpy.gateway.tiger import TigerGateway
main_engine.add_gateway(TigerGateway)
```

&nbsp;


#### 相關欄位

- 使用者ID：tiger_id
- 環球賬戶：account
- 標準賬戶：standard_account
- 祕鑰：private_key



&nbsp;


#### 獲取賬號

在老虎證券開戶並且入金後可以獲得API接入許可權。擁有實盤賬號後才可以申請開通模擬交易賬號。


&nbsp;


### ALPACA

#### 如何載入
先從gateway上呼叫AlpacaGateway類；然後通過add_gateway()函式新增到main_engine上。
```
from vnpy.gateway.alpaca import AlpacaGateway
main_engine.add_gateway(AlpacaGateway)
```

&nbsp;

#### 相關欄位
- KEY ID: key
- Secret Key: secret
- 會話數: 10
- 伺服器:["REAL", "PAPER"]
#### 獲取賬號
在OKEX官網開戶並且入金後可以獲得API接入許可權。
#### 其他特點

&nbsp;


### BITMEX

#### 如何載入

先從gateway上呼叫BitmexGateway類；然後通過add_gateway()函式新增到main_engine上。
```
from vnpy.gateway.bitmex import BitmexGateway
main_engine.add_gateway(BitmexGateway)
```

&nbsp;


#### 相關欄位

- 使用者ID：ID
- 密碼：Secret
- 會話數：3
- 伺服器：REAL 或 TESTNET
- 代理地址：
- 代理埠：



&nbsp;


#### 獲取賬號

在BITMEX官網開戶並且入金後可以獲得API接入許可權。



&nbsp;

### OKEX現貨（OKEX）


#### 如何載入

先從gateway上呼叫OkexGateway類；然後通過add_gateway()函式新增到main_engine上。
```
from vnpy.gateway.okex import OkexGateway
main_engine.add_gateway(OkexGateway)
```

&nbsp;


#### 相關欄位

- API祕鑰：API Key
- 密碼祕鑰：Secret Key
- 會話數：3
- 密碼：passphrase
- 代理地址：
- 代理埠：



&nbsp;


#### 獲取賬號

在OKEX官網開戶並且入金後可以獲得API接入許可權。



&nbsp;


### OKEX期貨（OKEXF）


#### 如何載入

先從gateway上呼叫OkexfGateway類；然後通過add_gateway()函式新增到main_engine上。
```
from vnpy.gateway.okexf import OkexfGateway
main_engine.add_gateway(OkexfGateway)
```

&nbsp;


#### 相關欄位

- API祕鑰：API Key
- 密碼祕鑰：Secret Key
- 會話數：3
- 密碼：passphrase
- 槓桿：Leverage
- 代理地址：
- 代理埠：



&nbsp;


#### 獲取賬號

在OKEX官網開戶並且入金後可以獲得API接入許可權。


&nbsp;

### 火幣(HUOBI)

#### 如何載入

先從gateway上呼叫HuobiGateway類；然後通過add_gateway()函式新增到main_engine上。
```
from vnpy.gateway.huobi import HuobiGateway
main_engine.add_gateway(HuobiGateway)
```

&nbsp;


#### 相關欄位

- API祕鑰：API Key
- 密碼祕鑰：Secret Key
- 會話數：3
- 代理地址：
- 代理埠：



&nbsp;


#### 獲取賬號

在火幣官網開戶並且入金後可以獲得API接入許可權。


&nbsp;



### 火幣合約(HUOBIF)

#### 如何載入

先從gateway上呼叫HuobifGateway類；然後通過add_gateway()函式新增到main_engine上。
```
from vnpy.gateway.huobif import HuobifGateway
main_engine.add_gateway(HuobifGateway)
```

&nbsp;


#### 相關欄位

- API祕鑰：API Key
- 密碼祕鑰：Secret Key
- 會話數：3
- 代理地址：
- 代理埠：



&nbsp;


#### 獲取賬號

在火幣官網開戶並且入金後可以獲得API接入許可權。


&nbsp;

### BITFINEX

#### 如何載入

先從gateway上呼叫BitFinexGateway類；然後通過add_gateway()函式新增到main_engine上。
```
from vnpy.gateway.bitfinex import BitfinexGateway
main_engine.add_gateway(BitfinexGateway)
```

&nbsp;


#### 相關欄位

- 使用者ID：ID
- 密碼：Secret
- 會話數：3
- 代理地址：
- 代理埠：



&nbsp;


#### 獲取賬號

在BITFINEX官網開戶並且入金後可以獲得API接入許可權。



&nbsp;


### ONETOKEN

#### 如何載入

先從gateway上呼叫OnetokenGateway類；然後通過add_gateway()函式新增到main_engine上。
```
from vnpy.gateway.onetoken import OnetokenGateway
main_engine.add_gateway(OnetokenGateway)
```

&nbsp;


#### 相關欄位

- Key祕鑰：OT Key
- 密碼祕鑰：OT Secret
- 會話數：3
- 交易所：["BINANCE", "BITMEX", "OKEX", "OKEF", "HUOBIP", "HUOBIF"]
- 賬號：
- 代理地址：
- 代理埠：



&nbsp;


#### 獲取賬號

在Onetoken官網開戶並且入金後可以獲得API接入許可權。



&nbsp;

&nbsp;

### BINANCE

#### 如何載入

先從gateway上呼叫BinanceGateway類；然後通過add_gateway()函式新增到main_engine上。
```
from vnpy.gateway.binance import BinanceGateway
main_engine.add_gateway(BinanceGateway)
```

&nbsp;


#### 相關欄位

- Key祕鑰
- secret
- session_number(會話數)：3
- proxy_host
- proxy_port

&nbsp;


#### 獲取賬號

在BINANCE官網開戶並且入金後可以獲得API接入許可權。

&nbsp;


### RPC

#### 如何載入

RPC的載入涉及到服務端和客戶端
- 服務端：執行vntrader時載入rpc_service模組
    ```
    from vnpy.app.rpc_service import RpcService
    ```
    啟動vntrader後，首先連線外部交易交易如CTP，然後點選選單欄"功能"->"RPC服務"，點選"啟動"
- 客戶端：執行vntrader時載入RpcGateway
    ```
    from vnpy.gateway.rpc import RpcGateway
    ```
    啟動vntrader後，連線rpc介面即可。

#### 相關欄位
在服務端和客戶端，使用預設填好的引數即可

#### 獲取賬號
使用rpc無須額外申請賬號，只需要一個外部介面賬號

#### 其他特點
rpc服務支援同一外部介面資料在本地多程序分發，比如在服務端連線了ctp介面，訂閱了rb1910後，客戶端多個程序會自動訂閱來自服務端分發的訂閱資料# 交易介面
