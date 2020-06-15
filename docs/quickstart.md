# 基本使用


## 啟動程式

### 圖形模式
登陸VN Station後，點選VN Trade Lite快速進入VN Trader（只有CTP介面）；或者點選VN Trader Pro先選擇如下圖的底層介面和上層應用，再進入VN Trader。

![](https://vnpy-community.oss-cn-shanghai.aliyuncs.com/forum_experience/yazhang/quick_start/VnTrader_Pro.png "enter image title here")



### 指令碼模式

在資料夾example\trader中找到run.py檔案(不是vnstudio下的，需要在github上單獨下載）。按住“Shift” + 滑鼠右鍵進入cmd視窗，輸入下面命令進入如圖VN Trader
```
python run.py 
```
![](https://vnpy-community.oss-cn-shanghai.aliyuncs.com/forum_experience/yazhang/quick_start/Vntrader.PNG "enter image title here")

&nbsp;

## 連線介面
### SimNow模擬

以SinNow模擬交易賬號登陸CTP介面為例：點選選單欄的“系統”->“連線CTP”後，彈出如上圖所示CTP介面的配置對話方塊，輸入以下內容後即可登入：
- 使用者名稱username：111111 （6位純數字賬號）
- 密碼password：1111111  （需要修改一次密碼用於盤後測試）
- 經紀商編號brokerid：9999 （SimNow預設經紀商編號）
- 交易伺服器地址td_address：218.202.237.33 :10102 （盤中測試）
- 行情伺服器地址md_address：218.202.237.33 :10112 （盤中測試）
- 授權碼auth_code：0000000000000000（16個0）
- 名稱app_id：simnow_client_test

連線成功以後，日誌元件會立刻輸出陸成功相關資訊，同時使用者也可以看到賬號資訊，持倉資訊，合約查詢等相關資訊。

&nbsp;

## 訂閱行情
在交易元件輸入交易所和合約程式碼，並且按“Enter”鍵即可訂閱器行情。如訂閱IF股指期貨，交易所：CFFEX，名稱：IF905；鐵礦石期貨，交易所：DCE，名稱：i1905。

此時行情元件會顯示最新行情資訊；交易元件會顯示合約名稱，並且在下方顯示深度行情報價：如最新價、買一價、賣一價。（數字貨幣品種可以顯示十檔行情）

注意：訂閱行情填寫的程式碼格式可以由選單欄的”幫助“->“查詢合約”裡查到
![](https://vnpy-community.oss-cn-shanghai.aliyuncs.com/forum_experience/yazhang/quick_start/subcribe_contract.png "enter image title here")



&nbsp;

## 委託交易
交易元件適用於手動交易。除了在行情訂閱中輸入的交易所和合約程式碼以外，還需要填寫以下5個欄位：委託方向、開平倉型別、委託型別、委託價格和委託數量。（若委託型別為市價單，委託價格可不填。）

發出委託同時本地快取委託相關資訊，並且顯示到委託元件和活動元件，其委託狀態為“提交中”，然後等待委託回報。

交易所收到使用者傳送的委託，將其插入中央訂單簿來進行撮合成交，並推送委託回報給使用者：
- 若委託還未成交，委託元件和活動元件只會更新時間和委託狀態這兩欄位，委託狀態變成“未成交”；
- 若委託立刻成交，委託相關資訊會從活動元件移除，新增至成交元件，委託狀態變成“全部成交”。




&nbsp;

## 資料監控

資料監控由以下元件構成，並且附帶2個輔助功能：選定以下任一元件，滑鼠右鍵可以選擇“調整列寬”（特別適用於螢幕解析度較低），或者選擇“儲存資料”（csv格式）

![](https://vnpy-community.oss-cn-shanghai.aliyuncs.com/forum_experience/yazhang/quick_start/2_optiones.png "enter image title here")


### 行情元件
用於對訂閱的行情進行實時監控，如下圖，監控內容可以分成3類：

- 合約資訊：合約程式碼、交易所、合約名稱

- 行情資訊：最新價、成交量、開盤價、最高價、最低價、收盤價、買一價、買一量、賣一價、賣一量

- 其他資訊：資料推送時間、介面

![](https://vnpy-community.oss-cn-shanghai.aliyuncs.com/forum_experience/yazhang/quick_start/subcribe_contract_module.png "enter image title here")


### 活動元件
活動元件用於存放還未成交的委託，如限價單或者沒有立刻成交的市價單，委託狀態永遠是“提交中”。在該元件中滑鼠雙擊任一委託可以完成撤單操作。

![](https://vnpy-community.oss-cn-shanghai.aliyuncs.com/forum_experience/yazhang/quick_start/active_order.png "enter image title here")

### 成交元件
成交元件用於存放已成交的委託，需要注意3個欄位資訊：價格、數量、時間。他們都是交易所推送過來的成交資訊，而不是委託資訊。

注意：有些介面會獨立推送成交資訊，如CTP介面；有些介面則需要從委託資訊裡面提取成交相關欄位，如Tiger介面。

![](https://vnpy-community.oss-cn-shanghai.aliyuncs.com/forum_experience/yazhang/quick_start/trade.png "enter image title here")



### 委託元件
委託元件用於存放使用者發出的所有委託資訊，其委託狀態可以是提交中、已撤銷、部分成交、全部成交、拒單等等。

![](https://vnpy-community.oss-cn-shanghai.aliyuncs.com/forum_experience/yazhang/quick_start/order.png "enter image title here")


### 持倉元件
持倉元件用於記錄其歷史持倉。其中需要了解以下欄位含義
- 方向：期貨品種具有多空方向；而股票品種方向為“淨”持倉。
- 昨倉：其出現衍生於上期所特有的平今、平昨模式的需要
- 數量：總持倉，即今倉 + 昨倉
- 均價：歷史成交的平均價格（某些巨型委託，會發生多次部分成交，需要計算平均價格）
- 盈虧：持倉盈虧：多倉情況下，盈利 = 當前價格 - 均價；空倉則反之。
  
若平倉離場，持倉數量清零，浮動盈虧變成實際盈虧從而影響賬號餘額變化。故以下欄位：數量、昨倉、凍結、均價、盈虧均為“0”，如下圖。

![](https://vnpy-community.oss-cn-shanghai.aliyuncs.com/forum_experience/yazhang/quick_start/query_position.png "enter image title here")

### 資金元件
資金元件顯示了賬號的基礎資訊，如下圖需要注意3個欄位資訊：
- 可用資金：可以用於委託的現金
- 凍結：委託操作凍結的金額（與保證金不是一個概念）
- 餘額：總資金，即可用資金 + 保證金 + 浮動盈虧 

注意：若全部平倉，浮動盈虧變成實際盈虧，保證金和浮動盈虧清零，總資金等於可用資金

![](https://vnpy-community.oss-cn-shanghai.aliyuncs.com/forum_experience/yazhang/quick_start/query_account.png "enter image title here")



### 日誌元件
日誌元件用於顯示介面登陸資訊以及委託報錯資訊，如下圖。

![](https://vnpy-community.oss-cn-shanghai.aliyuncs.com/forum_experience/yazhang/quick_start/write_log.png "enter image title here")



&nbsp;

## 應用模組

vn.py官方提供了開箱即用的量化交易應用模組，在選單欄中點選“功能”，即顯示應用模組，如下圖：

![](https://vnpy-community.oss-cn-shanghai.aliyuncs.com/forum_experience/yazhang/quick_start/application.png "enter image title here")

&nbsp;

## 全域性配置

在選單欄中點選“配置”，可以進行全域性配置：如配置GUI介面字型的大小，型別，資料庫種類，RQData的賬戶密碼（用於初始化RQData客戶端，下載歷史資料，或者盤起載入資料來初始化策略），設定email來發送資訊。

其email的設定如下：
email.server: SMTP郵件伺服器地址
email.port: SMTP郵件伺服器埠號
email.username: 郵箱使用者名稱
email.password: 郵箱密碼
email.sender: 傳送者郵箱
email.receiver: 接收者郵箱

