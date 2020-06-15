# OES-API Update Guide    {#update_guide}

OES_0.15.9 / 2019-05-31
-----------------------------------

### 1. API更新概要

  1.  服務端相容 v0.15.5.1 版本API, 客戶可以選擇不升級 (建議升級, 以支援科創版業務)
  2.  fix: 修復API無法支援取值大於1024的檔案描述符的問題
  3.  新增證券子型別
      - 科創板股票 (OES_SUB_SECURITY_TYPE_STOCK_KSH)
      - 科創板存託憑證 (OES_SUB_SECURITY_TYPE_STOCK_KCDR)
      - 滬倫通CDR (OES_SUB_SECURITY_TYPE_STOCK_HLTCDR)
  4.  新增配股認購對應的買賣型別 OES_BS_TYPE_ALLOTMENT, 以支援配股業務
  5.  新增產品型別屬性的定義, 並在如下結構中體現:
      - 證券資訊 (OesStockBaseInfoT/OesStockItemT)
      - 證券發行資訊 (OesIssueBaseInfoT/OesIssueItemT)
      - 股票持倉資訊 (OesStkHoldingBaseInfoT/OesStkHoldingItemT)
      - 委託回報 (OesOrdCnfmT/OesOrdItemT)
      - 成交回報 (OesTrdCnfmT/OesTrdItemT)
      - 證券發行資訊查詢介面(OesApi_QueryIssue)的過濾條件
      - 股票持倉資訊查詢介面(OesApi_QueryStkHolding)的過濾條件
  6.  為了支援科創板, 擴充套件以下資料結構以及相應的查詢結果 (相容之前版本的API)
      - 證券賬戶基礎資訊 (OesInvAcctBaseInfoT, OesInvAcctItemT) 中增加如下欄位:
          - 科創板權益 (kcSubscriptionQuota)
      - 現貨產品基礎資訊 (OesStockBaseInfoT, OesStockItemT) 中增加如下欄位:
          - 限價買數量上限 (lmtBuyMaxQty)
          - 限價買數量下限 (lmtBuyMinQty)
          - 限價賣數量上限 (lmtSellMaxQty)
          - 限價賣數量下限 (lmtSellMinQty)
          - 市價買數量上限 (mktBuyMaxQty)
          - 市價買數量下限 (mktBuyMinQty)
          - 市價賣數量上限 (mktSellMaxQty)
          - 市價賣數量下限 (mktSellMinQty)
      - 客戶端總覽資訊中的股東賬戶總覽 (OesInvAcctOverviewT) 中增加如下欄位:
          - 科創板權益 (kcSubscriptionQuota)
  7.  重構漲跌停價格、價格檔位欄位命名, 為這些欄位增加新的別名 (相容之前版本的API)
      - ceilPrice => upperLimitPrice
      - floorPrice => lowerLimitPrice
      - priceUnit => priceTick
  8.  調整上證委託型別 (eOesOrdTypeShT)
      - 增加 '對手方最優價格申報 (OES_ORD_TYPE_SH_MTL_BEST)' 型別 (僅適用於科創板)
      - 增加 '本方最優價格申報 (OES_ORD_TYPE_SH_MTL_SAMEPATY_BEST)' 型別 (僅適用於科創板)
  9.  股東賬戶交易許可權列舉(eOesTradingPermissionT)中新增
      - 科創板交易許可權 (OES_PERMIS_KSH)
  10. 新增錯誤碼1035、1036、1274、1275, 調整錯誤碼1007、1022的描述資訊
      | 錯誤碼 | 描述
      | ---- | ---------------
      | 1007 | 非服務開放時間
      | 1022 | 尚不支援或尚未開通此業務
      | 1035 | 非法的產品型別
      | 1036 | 未通過黑白名單檢查
      | 1274 | 股東賬戶沒有交易滬倫通存託憑證的許可權
      | 1275 | 股東賬戶沒有交易科創板的許可權

### 2. 服務端更新概要

  1. 支援配股申購業務
  2. 支援對客戶設定禁止買入和限制賣出某支證券
  3. 支援逆回購閉市時間延後到15:30
  4. 支援科創板業務
  5. 修復其他系統缺陷, 完善安全機制

### 3. 科創板市價委託保護限價說明

  1. 在進行科創板市價委託交易時, 保護限價填在委託請求中的ordPrice欄位內 (對於主機板的市價委託, 委託請求中的ordPrice欄位無意義)
  2. 對於上市前五日、無漲跌幅限制的科創板證券, 市價委託的保護限價必填, 且保護限價需符合價格變動單位
  3. 對於上市五日後、有漲跌幅限制的科創板證券, 市價委託的保護限價可填寫有效值或者0
     - 對於市價買委託, 委託請求中ordPrice填0將使用漲停價作為其保護限價
     - 對於市價賣委託, 委託請求中ordPrice填0將使用跌停價作為其保護限價
  4. 對於有漲跌幅限制的科創板證券:
     - 當市價買委託的保護限價高於漲停價時, 將使用漲停價凍結交易資金, 委託正常處理
     - 當市價買委託的保護限價低於漲停價時, 將使用保護限價凍結交易資金
     - 當市價買委託的保護限價低於跌停價時, 委託將被拒絕
     - 當市價賣委託的保護限價低於跌停價時, 委託正常處理
     - 當市價賣委託的保護限價高於漲停價時, 委託將被拒絕


---

OES_0.15.7.4 / 2018-09-28
-----------------------------------

### 1. API更新概要

  1. 服務端相容 v0.15.5.1 版本API，客戶可以選擇不升級 (建議升級)
  2. fix: 修復當多個執行緒同時初始化API日誌時, 會導致日誌資訊重複輸出的問題
  3. API新增如下介面
    | API                          | 描述
    | ---------------------------- | ---------------
    | OesApi_SendBatchOrdersReq    | 批量委託
    | OesApi_SendBatchOrdersReq2   | 批量委託
    | OesApi_SendChangePasswordReq | 修改客戶端登入密碼，僅支援15:00之後修改
    | OesApi_SetLastError          | 設定當前執行緒的API錯誤號
    | OesApi_GetLastError          | 獲取當前執行緒最近一次API呼叫失敗的錯誤號
    | OesApi_SetCustomizedDriverId | 獲取已設定的裝置序列號
    | OesApi_GetCustomizedDriverId | 設定裝置序列號
    | OesApi_GetClientOverview     | 獲取客戶端總覽資訊
    | OesApi_QueryCounterCash      | 查詢主櫃資金資訊(僅支援部分主櫃檯)
    | OesApi_QueryMarketState      | 查詢市場狀態(目前僅能獲取到深圳市場狀態)
    | OesApi_HasMoreCachedData     | 獲取回報通道中尚未被回撥函式處理的快取資料長度
    | OesApi_SetThreadUsername     | 設定當前執行緒的登入使用者名稱
    | OesApi_SetThreadPassword     | 設定當前執行緒的登入密碼
    | OesApi_SetThreadEnvId        | 設定當前執行緒的客戶端環境號
  4. 回報通道新增一類推送訊息: 市場狀態推送(目前僅推送深圳市場的狀態)，預設訂閱條件不會訂閱此訊息
  5. 新增存託憑證對應的證券子類別 OES_SUB_SECURITY_TYPE_STOCK_CDR
  6. 回報的訊息頭結構(OesRptMsgHeadT)中增加 execType 欄位，用於表明回報執行型別(參考eOesExecTypeT定義)。
  7. 查詢證券資訊介面(OesApi_QueryStock)中新增過濾條件“證券類別”、“證券子類別”
  8. 查詢委託介面(OesApi_QueryOrder)中新增過濾條件“證券類別”、“買賣型別”
  9. 查詢成交介面(OesApi_QueryTrade)中新增過濾條件“證券類別”、“買賣型別”
  10. 查詢股票持倉介面(OesApi_QueryStkHolding)中新增過濾條件“證券類別”
  11. 調整出入金委託請求介面, 支援銀行和主櫃之間的銀證轉賬
  12. 客戶資金資訊中增加是否禁止出入金的標識
  13. 客戶股東資訊中增加是否禁止交易的標識
  14. 成交資訊中增加證券子型別、原始委託數量、原始委託價格
  15. 新增部分錯誤碼
    | 錯誤碼 | 描述
    | ---- | ---------------
    | 1029 | 密碼未改變
    | 1030 | 非法的來源分類
    | 1031 | 非法的加密型別
    | 1032 | 非法的客戶端裝置序列號
    | 1033 | 無可用節點
    | 1271 | 股東賬戶沒有交易存託憑證的許可權
    | 1272 | 股東賬戶沒有交易創新企業股票的許可權
    | 1273 | 非法的出入金轉賬型別

### 2. 服務端更新概要

  1. 支援修改密碼
  2. 支援批量委託
  3. 支援CDR交易、創新企業股票交易
  4. 在監控管理端新增應急撤單功能
  5. 系統增加盤前開工和盤後收工操作。開工前（9:00）可以查詢資料，但不受理交易和出入金。收工後（15:10）不受理交易，但可以執行出入金、修改密碼和查詢資料。
  6. 修復系統缺陷，完善管理功能和故障恢復處理


---

OES_0.15.5.16 / 2018-09-28
-----------------------------------

### 1. API更新概要

  1. 服務端相容 v0.15.5.1 版本API, 客戶可以選擇不升級 (建議升級)
  2. fix: 修復當多個執行緒同時初始化API日誌時, 會導致日誌資訊重複輸出的問題
  3. 增加 OesApi_HasMoreCachedData 介面, 用於返回已經接收到但尚未被回撥函式處理的快取資料長度
  4. 增加 OesApi_GetLastError 介面, 用於返回最近一次API呼叫失敗的錯誤號
  5. 增加 OesApi_QueryCounterCash 介面, 用於查詢主櫃的資金資訊 (僅支援部分主櫃)
  6. 增加 OesApi_GetClientOverview 介面, 用於查詢客戶端總覽資訊
  7. 增加設定當前執行緒登入使用者名稱/登入密碼/客戶端環境號的介面
  8. 查詢現貨產品資訊介面的過濾條件中新增證券型別、證券子型別的過濾條件
  9. 調整出入金委託請求介面, 支援銀行和主櫃之間的銀證轉賬
  10. 客戶資金資訊中增加是否禁止出入金的標識
  11. 客戶股東資訊中增加是否禁止交易的標識
  12. 成交資訊中增加證券子型別、原始委託數量、原始委託價格

### 2. 服務端更新概要

  1. 支援CDR交易、創新企業股票交易
  2. 新增監控管理端的應急撤單功能
  3. 修復系統缺陷, 完善管理功能和故障恢復處理


---

OES_0.15.5.11 / 2018-06-20
-----------------------------------

### 1. API更新概要

  1. API沒有變化
  2. 服務端相容 v0.15.5.1 版本API, 客戶可以選擇不升級 (建議升級)

### 2. 服務端更新概要

  1. 修復系統缺陷
  2. 完善容錯處理
  3. 其它功能性更新


---

OES_0.15.5.4 / 2018-02-22
-----------------------------------

### 1. API更新概要

  1. 服務端相容 v0.15.5.1 版本API, 客戶可以選擇不升級
  2. fix: 解決在Windows下的相容性問題
  3. fix: 修正註釋資訊中的錯誤 ('佣金查詢結果 (OesCommissionRateItemT)' 中 feeRate 欄位精度描述不正確)
  4. API將優先使用自動獲取到的ip/mac資訊，只有自動獲取到的ip/mac資訊非法時，才會使用客戶自設的ip/mac
  5. 修正ETF產品資訊中的欄位拼寫錯誤 (preTrdaingDay => preTradingDay)
  6. 增加 OesApi_GetLastRecvTime、OesApi_GetLastSendTime 介面, 用於獲取通道最新發送/接受訊息的時間
  7. 登入失敗時, 可以通過 errno/SPK_GET_ERRNO() 獲取到具體失敗原因

### 2. 服務端更新概要

  1. fix: 優化回報推送，改善推送服務的公平性
  2. fix: 修復在委託確認時沒有回填 exchOrdId 的問題
  3. 服務端將拒絕來自本地迴環地址以及非法IP/MAC地址的登入


---

OES_0.15.5 / 2017-11-12
-----------------------------------

### 1. 更新概要

  1. API中增加客戶端環境號(clEnvId)，不同客戶端環境號(clEnvId)下的委託順序號(clSeqNo)序列互不影響
  2. 增加獨立的撤單介面，支援通過 clEnvId+clSeqNo 進行撤單
  3. 回報通道支援訊息訂閱功能，預設情況下訂閱所有型別的回報訊息
  4. 回報訊息新增兩類：資金變動通知、持倉變動通知
  5. 撤單委託執行成功後，補充被撤委託的狀態推送
  6. 查詢介面回撥方法型別定義調整，查詢回撥介面中增加 isEnd 標誌
  7. 持倉資訊中增加持倉成本相關欄位，將影響持倉查詢返回結構和持倉變動通知結構
  8. API退出時在日誌中輸出延遲統計資訊

### 2. 詳細更新內容

#### 2.1 API中增加客戶端環境號(clEnvId)

  - clEnvId 是客戶端環境號，用於區分不同客戶端例項上報的委託。即可以為每個客戶端例項分配不同的 clEnvId，這樣這些客戶端例項就可以各自維護自己的 clSeqNo 而不會相互干擾
  - 不同客戶端例項可以使用同一 clEnvId 登入服務端。此時這些使用了同一 clEnvId 的客戶端例項共享同一個 clSeqNo 序列
  - clEnvId 客戶端的取值範圍是 __[0~99]__ ([100~127] 為保留區間，客戶端應避免使用)
  - 可以通過 OesApi_GetClEnvId() 介面獲得本客戶端例項繫結的 clEnvId
  - 服務端維護的委託資訊中，會記錄傳送此委託的源客戶端例項所繫結的 clEnvId。委託回報訊息(OesOrdCnfmT.clEnvId) 和 委託查詢應答(OesOrdItemT.clEnvId) 會攜帶此資訊
  - 配置檔案相關設定請參考 oes_client_sample.conf 中 [oes_client].clEnvId 引數的設定

#### 2.2 增加獨立的撤單介面

  - 增加獨立的撤單介面 OesApi_SendOrderCancelReq()
  - 介面中 pCancelReq 引數的 pCancelReq->mktId 必填
  - 介面中 pCancelReq 引數的 pCancelReq->invAcctId、pCancelReq->securityId 選填。如果填寫則會與被撤委託作匹配
  - 仍保留通過被撤委託 clOrdId 的方式進行撤單。倘若介面中 pCancelReq->origClOrdId > 0，則優先通過pCancelReq->origClOrdId 來匹配被撤委託進行撤單
  - 在通過被撤委託 clEnvId+clSeqNo 進行撤單的場景，倘若介面中 pCancelReq->origClEnvId = 0，則預設使用當前客戶端例項繫結的 clEnvId 作為被撤委託的 clEnvId 進行撤單。也就是說，對於本客戶端例項發出的委託進行撤單，撤單時 pCancelReq->origClEnvId 可以寫0； __如果要對其他客戶端例項發出的委託進行撤單，需要準確寫撤單介面中的 pCancelReq->origClEnvId 欄位__

#### 2.3 回報通道支援訊息訂閱功能

  - 預設情況下，訂閱所有型別的回報訊息
  - 配置檔案相關設定請參考oes_client_sample.conf 中 [oes_client].rpt.subcribeRptTypes  引數的設定

#### 2.4 新增資金變動、持倉變動通知

  - 回報新增兩個推送訊息：OESMSG_RPT_CASH_ASSET_VARIATION (資金變動通知)、OESMSG_RPT_STOCK_HOLDING_VARIATION (持倉變動通知)
  - 當因委託請求、委託成交、委託撤單而引起可用資金、可用持倉變動時，會觸發回報通道的資金變動/持倉變動通知
  - 以一筆買委託為例，OES服務端將會依次推送如下訊息：
    1. OESMSG_RPT_ORDER_INSERT 訊息 (新委託觸發)
    2. OESMSG_RPT_CASH_ASSET_VARIATION 訊息（因資金凍結觸發）
    3. OESMSG_RPT_ORDER_REPORT 訊息（因交易所委託回報觸發）
    4. OESMSG_RPT_TRADE_REPORT 訊息（因交易所成交回報觸發）
    5. OESMSG_RPT_CASH_ASSET_VARIATION 訊息（因成交引起資金扣減觸發）
    6. OESMSG_RPT_STOCK_HOLDING_VARIATION 訊息（因成交引起持倉增加觸發）

#### 2.5 補充被撤委託的狀態推送

  - 以一筆買委託被成功撤單為例，回報通道會依次推送如下回報訊息：
    1. 撤單委託的 OESMSG_RPT_ORDER_INSERT 訊息
    2. 撤單委託的 OESMSG_RPT_ORDER_REPORT 訊息
    3. __被撤__ 委託的 OESMSG_RPT_ORDER_REPORT 訊息
    5. OESMSG_RPT_CASH_ASSET_VARIATION 訊息（因釋放凍結資金觸發）

#### 2.6 查詢介面回撥方法型別定義調整

  - 調整查詢介面回撥方法型別定義 F_OESAPI_ONMSG_T => F_OESAPI_ON_QRY_MSG_T
  - 查詢介面回撥方法中增加引數 OesQryCursorT *pQryCursor，使用 pQryCursor->isEnd 判斷是否是查詢的最後一條

#### 2.7 持倉資訊中增加持倉成本相關欄位

  - '股票持倉資訊 (OesStkHoldingItemT)' 結構體中增加欄位:
    1. 日初總持倉成本 (originalCostAmt)
    2. 日中累計買入金額 (totalBuyAmt)
    3. 日中累計賣出金額 (totalSellAmt)
    4. 日中累計買入費用 (totalBuyFee)
    5. 日中累計賣出費用 (totalSellFee)
    6. 持倉成本價 (costPrice)

#### 2.8 回報介面回撥方法型別定義調整

  - 回報介面回撥方法型別定義調整 F_OESAPI_ONMSG_T => F_OESAPI_ON_RPT_MSG_T
  - 回報介面回撥方法實際引數列表沒有變化

#### 2.9 其他調整

  - 委託回報資訊中增加獨立的交易所錯誤碼欄位
    1. 原錯誤碼欄位 OesOrdCnfmT.ordRejReason 保持不變
    2. 當委託被交易所打回廢單後，OesOrdCnfmT.ordRejReason 釋義為 “交易所拒絕”，此時具體錯誤原因需要參考 OesOrdCnfmT.exchErrCode，此欄位攜帶交易所定義的錯誤碼
  - 委託狀態定義調整
    1. 刪除 'OES_ORD_STATUS_DECLARING (正報)' 狀態
    2. 重新命名 OES_ORD_STATUS_NORMAL => OES_ORD_STATUS_NEW (新訂單)
    3. 保留 OES_ORD_STATUS_NORMAL 定義作為版本切換間的相容
  - 回報訊息型別定義調整
    1. 重新命名回報訊息型別 OESMSG_RPT_ORDER_REJECT => OESMSG_RPT_BUSINESS_REJECT (OES業務拒絕, 委託/撤單未通過風控檢查等)
    2. 保留 OESMSG_RPT_ORDER_REJECT 定義作為版本切換間的相容
  - 調整 '資金資訊(OesCashAssetItemT)' 中部分欄位:
    3. '當前餘額'欄位重新命名 currentBal => currentTotalBal
  - 新增API介面 '獲取API的發行版本號 (OesApi_GetApiVersion)'
  - 新增API介面 '獲取當前交易日 (OesApi_GetTradingDay)'
  - 調整佣金查詢結果中feeRate欄位的精度，當佣金計算模式為 ‘按金額’ 時，feeRate 欄位所代表的比率精度由 '百萬分之一' => '千萬分之一'


---

OES_0.15.3 / 2017-08-14
-----------------------------------

### 更新內容

  1. 現貨產品基礎資訊(OesStockBaseInfoT) 中
    - 調整欄位 isQualificationRequired => qualificationClass,
        取值請參考 eOesQualificationClassT
    - 新增欄位 產品風險等級(securityRiskLevel)，取值請參考 eOesSecurityRiskLevelT
    - 新增欄位 逆回購期限(repoExpirationDays)
    - 新增欄位 佔款天數(cashHoldDays) 欄位
  2. 客戶資金基礎資訊(OesCashAssetBaseInfoT) 中
    - 欄位重新命名 期初餘額(originalBal => beginningBal)
    - 新增欄位 期初可用餘額(beginningAvailableBal)
    - 新增欄位 期初可取餘額(beginningDrawableBal)
    - 新增欄位 當前衝正金額(紅衝藍補的資金淨額, reversalAmt)
    - 新增欄位 當前餘額(currentBal)
    - 欄位重新命名 當前可用餘額(tradeAvlAmt => currentAvailableBal)
    - 欄位重新命名 當前可取餘額(withdrawAvlAmt => currentDrawableBal)
  3. 客戶基礎資訊(OesCustBaseInfoT) 中
    - 新增 機構標誌(institutionFlag) 欄位
    - 新增 投資者分類(investorClass) 欄位
  4. 證券賬戶基礎資訊(OesInvAcctBaseInfoT) 中
    - 調整欄位 '(股東賬戶許可權限制, acctLimit)'
        - 型別 uint32 => uint64
        - 重新命名 acctLimit => Limits
    - 調整欄位 '(股東許可權/客戶許可權, acctRight)'
        - 型別 uint32 => uint64
        - 重新命名 acctRight => permissions
  5. API介面中新增 傳送出入金委託請求(OesApi_SendFundTrsfReq) 介面
  6. API介面中新增 查詢新股配號、中籤資訊(OesApi_QueryLotWinning) 介面
  7. 新增 ‘新股認購、中籤資訊查詢’ 相關報文定義
    - 新增欄位 查詢新股認購、中籤資訊過濾條件(OesQryLotWinningFilterT)
    - 新增欄位 新股認購、中籤資訊內容(OesLotWinningItemT)
    - 新增欄位 查詢新股認購、中籤資訊請求(OesQryLotWinningReqT)
    - 新增欄位 查詢新股認購、中籤資訊應答(OesQryLotWinningRspT)
  8. 出入金業務拒絕訊息型別變更 OesFundTrsfReqT => OesFundTrsfRejectT
  9. 出入金委託回報的結構體(OesFundTrsfReportT) 中新增欄位 錯誤碼資訊(errorInfo)
  10. 出入金委託狀態(eOesFundTrsfStatusT) 中
    - 調整巨集定義 OES_FUND_TRSF_STS_RECV => OES_FUND_TRSF_STS_UNDECLARED
    - 調整巨集定義 OES_FUND_TRSF_STS_DCLR => OES_FUND_TRSF_STS_DECLARED
    - 新增狀態 指令已報到主櫃前待回滾(OES_FUND_TRSF_STS_UNDECLARED_ROLLBACK)
    - 新增狀態 指令已報到主櫃後待回滾(OES_FUND_TRSF_STS_DECLARED_ROLLBACK)
    - 新增狀態 出入金指令完成，等待事務結束(OES_FUND_TRSF_STS_WAIT_DONE)
    - 新增狀態 出入金執行的掛起狀態(OES_FUND_TRSF_STS_SUSPENDED)
  11. 許可權不足交易失敗時的錯誤碼細分(詳情請見 README 錯誤碼錶部分)


---

OES_0.12.9 / 2017-06-06
-----------------------------------

### 更新內容

  1. 使用API發起新股認購時，認購委託的bsType需要填成 ‘OES_BS_TYPE_SUBSCRIPTION’
  2. 可以使用API的查詢股東賬戶介面(OesApi_QueryInvAcct)獲取該股東賬戶的新股認購額度(OesInvAcctItemT.subscriptionQuota)
  3. 可以使用API的查詢證券發行產品資訊介面(OesApi_QueryIssue)獲取當日可認購的新股資訊(OesIssueItemT)
  4. 可以使用API的查詢現貨產品資訊介面(OesApi_QueryStock)獲取債券的每百元應計利息額(OesStockItemT.bondInterest)，
    此欄位精確到元后八位，即123400000相當於一元二角三分四釐
  5. 買賣國債委託涉及的利息，可以參考‘委託確認資訊(OesOrdCnfmT)’中的‘凍結利息(frzInterest)’、‘已發生利息(cumInterest)’欄位
  6. 買賣國債成交涉及的利息，可以參考‘成交確認資訊(OesTrdCnfmT)’中的‘已發生利息(cumInterest)’欄位
  7. ‘買賣型別’的巨集定義重新命名，具體請參考OES_0.12.8.2版本修改歷史。原始巨集定義將在下一個版本之後被廢棄


---

OES_0.12.7 / 2017-04-13
-----------------------------------

### 1. 主要更新內容
  1. 使用API發逆回購委託時，逆回購委託的bsType需要賦值成 ‘OES_BS_TYPE_CS’，而不是普通的‘賣出’。
  2. 使用API發逆回購委託時，ordQty 欄位代表的單位是‘張’而不是‘手’。
  3. 回報通道增加兩類訊息：‘出入金委託響應-業務拒絕（OESMSG_RPT_FUND_TRSF_REJECT）’
    和‘出入金委託執行報告(OESMSG_RPT_FUND_TRSF_REPORT)’ 。
    - 出入金委託業務拒絕回報訊息的回報訊息體結構為 OesFundTrsfReqT，
    - 出入金委託執行報告回報訊息的回報訊息體結構為 OesFundTrsfReportT，
    - 如果不在oes系統內做出入金可以忽略這兩類回報訊息
  4. 在mds_api.h、oes_api.h中增加sutil庫標頭檔案的引用，API使用者只需引用mds_api.h、oes_api.h，
    不再需要顯式引用sutil庫的標頭檔案

### 2. 其他調整：
  1. 不再有獨立的出入金通道，client的配置中可以去掉62**埠的配置了
  2. 調整佣金查詢結果中feeRate欄位的精度，當佣金計算模式為 ‘按金額’ 時，
     feeRate 欄位所代表的比率精度由 '十萬分之一' => '百萬分之一'
  3. ‘費用計算模式’ 的巨集定義名稱的調整 eOesCalFeeModeT => eOesCalcFeeModeT
  4. 新增債券、基金的證券類別，調整ETF證券類別巨集定義的取值
  5. 新增證券子類別定義
  6. 現貨產品基礎資訊中增加“證券子類別”欄位，並且重新命名“買入單位”、“賣出單位”欄位
  7. ETF產品基礎資訊中增加“證券類別”、“證券子類別”欄位
  8. ETF成分股基礎資訊中增加“證券子類別”欄位
