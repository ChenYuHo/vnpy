# 交易風控

交易風控模組屬於事前風控，即在委託在通過交易API介面發出去前，需要檢查其狀態不能超過風控限制，其中包括：
- 委託數量必須大於0
- 單筆委託的數量上限
- 當日總成交數量上限
- 委託流數量上限
- 當前活動委託次數上限
- 當日撤單次數上限

&nbsp;

## 載入啟動

進入VN Trader後，首先登陸介面，如連線CTP；然後在選單欄中點選“功能”->"交易風控“後，會彈出交易風控視窗，如圖。
![](https://vnpy-community.oss-cn-shanghai.aliyuncs.com/forum_experience/yazhang/risk_manager/risk_manager.png)

視窗中顯示的引數，對應的是C:\Users\Administrator\.vntrader裡面risk_manager_setting.json的引數字典，如圖。
![](https://vnpy-community.oss-cn-shanghai.aliyuncs.com/forum_experience/yazhang/risk_manager/data_setting.png)

在“風控執行狀態”的選擇框中點選“啟動”後
- 立刻呼叫RiskManagerEngine類的update_setting()函式讀取risk_manager_setting.json的引數字典並且繫結類的屬性。
- 在日誌中輸出"交易風控功能啟動"。
- 執行check_risk()函式，去檢查每一筆發出去的委託是否符合各種風控要求，若全部滿足後，流控計數+1，委託真正通過API介面傳送出去。

&nbsp;

## 修改引數

交易風控元件允許使用者修改風控引數。由於GUI介面的各引數欄是基於PyQt5的QSpinBox，使用者可以用滑鼠點選上下箭頭來修改，也可以直接鍵盤輸入來修改。

最後點選視窗下方的“儲存”按鈕，對呼叫RiskManagerEngine類的save_setting()函式去更新到risk_manager_setting.json的引數字典中，最後通過update_setting()函式把引數字典繫結到類的屬性。

&nbsp;

## 停止風控

在“風控執行狀態”的選擇框中點選“停止後”後，RiskManagerEngine類的active變成False，check_risk()函式不再檢查委託的風控流控狀態，同時在日誌中輸出"交易風控功能停止"。

