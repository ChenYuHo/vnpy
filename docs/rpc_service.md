# RPC服務
全域性鎖GIL的存在導致Python只能利用CPU單核的算力。其單程序架構的不足之處如圖所示：

![](https://static.vnpy.com/upload/temp/3f51a477-36db-41d4-9632-75067ba24be7.png)

使用多程序分散式的程式架構可以突破該限制。但每個程序之間的資料，在作業系統內預設是獨立隔離的，無法直接訪問。
RPC服務正好能解決這個痛點：RPC全稱Remote-Procedure-Call，中文“遠端過程呼叫”，是最常用的跨程序通訊方式之一。在vnpy中，一個特定程序連線交易介面充當Server的角色，在本地物理機或者區域網內部進行事件的推送，推送給其他獨立的Client程序，如圖。

![](https://static.vnpy.com/upload/temp/a67e561d-d94d-43f4-9d40-bb929ed6e0e5.png)

&nbsp;

## RPC伺服器

### 載入模組
RPC服務模組處於vnpy/app/rpc_service資料夾中，裡面定義了RPC引擎物件，用於將一個特定的vnpy程序包裝成RPC伺服器，從而進行推送服務端所有事件和處理客戶端請求。

可通過下面2種模式載入RPC模組：
- 圖形模式：登入VN Station，在上層應用介面勾選RpcService，如圖。
  
![](https://static.vnpy.com/upload/temp/62edff53-74d0-4cab-9041-cc209d0b394f.png)

&nbsp;

- 指令碼模式：使用run.py啟動Vn Trader，在匯入模組時額外寫下面程式碼：
```
from vnpy.app.rpc_service import RpcServiceApp
from vnpy.gateway.ctp import CtpGateway
main_engine.add_app(RpcServiceApp)
main_engine.add_gateway(CtpGateway)
```

&nbsp;


### 啟動執行
進入Vn Trader，先連線交易介面，如CTP，然後點選選單欄“功能”->“Rpc服務”，進入如圖RPC服務點選“啟動”即可。注意：RPC服務不僅支援同一物理機多程序通訊，還支援區域網內部通訊，若在同一臺機器上執行，無需修改任何引數。

![](https://static.vnpy.com/upload/temp/44b7223c-a232-4002-9e1f-2067f5e7c30a.png)

&nbsp;

## RPC客戶端

### 載入介面
RPC客戶端同樣提供2種不同的載入模式：
- 圖形模式：登入VN Station，在底層介面介面勾選RPC服務，如圖。

![](https://static.vnpy.com/upload/temp/659a156c-2bf2-4053-bd91-2c383aff24b2.png)

&nbsp;

- 指令碼模式：使用run.py啟動Vn Trader，在匯入模組時額外寫下面程式碼：

```
from vnpy.gateway.rpc import RpcGateway
main_engine.add_gateway(RpcGateway)
```

&nbsp;

### 連線使用
從客戶端的視角看，RpcGateway就是如CTP一般的介面，省去了額外輸入賬戶等資訊的步驟。因為統一在服務端已經完成，只需要和伺服器端進行連線即可。

進入VnTrader，點選選單欄”系統“->”連線RPC“，在如圖彈出的視窗中點選”連線“即可。

![](https://static.vnpy.com/upload/temp/988fc191-2762-48cb-b0fb-77384dc543f9.png)

&nbsp;

## 參考樣例
參考樣例位於examples/server_client目錄下，其中包括伺服器程序和客戶端程序。

### 伺服器程序
樣例提供了run_server.py檔案，裡面定義了main_ui和main_terminal函式，分別用於GUI模式和無介面模式啟動，可以根據需要修改這兩個函式，然後選擇執行某一個函式即可。

- GUI模式：GUI模式啟動和上面提到的run.py啟動完全一致，只是run_server.py已經預設載入了RPC模組，使用者只需修改載入的外部交易介面即可。

- 無介面模式：需要提前配置好連線CTP等交易介面所需的個人資訊，如圖：
  
![](https://static.vnpy.com/upload/temp/69010fa2-98c4-47ae-b055-d6709d744385.png)

&nbsp;

### 客戶端程序
樣例提供了run_client.py，和上述提到的run.py啟動VnTrader方式完全一致，只是這裡已經預設載入了Rpc介面。

