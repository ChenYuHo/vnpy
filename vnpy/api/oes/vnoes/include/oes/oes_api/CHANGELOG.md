# OES-API Change Log    {#changelog}

OES_0.15.9_RC1 / 2019-04-28
==============================================

  * 新增證券子型別
    - 科創板股票 (OES_SUB_SECURITY_TYPE_STOCK_KSH)
    - 科創板存託憑證 (OES_SUB_SECURITY_TYPE_STOCK_KCDR)
  * 為了支援科創板, 擴充套件以下資料結構以及相應的查詢結果 (相容之前版本的API)
    - 證券賬戶基礎資訊 (OesInvAcctBaseInfoT, OesInvAcctItemT) 中增加如下欄位:
        - 科創板權益 (kcSubscriptionQuota)
  * 現貨產品基礎資訊 (OesStockBaseInfoT, OesStockItemT) 中增加如下欄位:
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
  * 重構漲跌停價格、價格檔位欄位命名, 為這些欄位增加新的別名 (相容之前版本的API)
    - ceilPrice => upperLimitPrice
    - floorPrice => lowerLimitPrice
    - priceUnit => priceTick
  * 調整上證委託型別 (eOesOrdTypeShT)
    - 增加 '對手方最優價格申報 (OES_ORD_TYPE_SH_MTL_BEST)' 型別 (僅適用於科創板)
    - 增加 '本方最優價格申報 (OES_ORD_TYPE_SH_MTL_SAMEPATY_BEST)' 型別 (僅適用於科創板)
  * 股東賬戶交易許可權列舉(eOesTradingPermissionT)中新增
    - 科創板交易許可權 (OES_PERMIS_KSH)
  * 新增錯誤碼
    - 1275, 股東賬戶沒有交易科創板的許可權
    - 1036, 未通過黑白名單檢查

OES_0.15.8 / 2019-02-22
==============================================

  * fix: 修復API無法支援取值大於1024的檔案描述符的問題（因為select的限制，當檔案描述符的取值大於1024時，會導致堆疊溢位）

OES_0.15.8_RC3 / 2019-01-14
==============================================

  * 委託回報和成交回報中新增供OES內部使用的 '交易閘道器平臺分割槽號(__tgwPartitionNo)' 欄位 (協議保持相容)
  * 調整錯誤描述
    - 1007, 非服務開放時間（OESERR_NOT_TRADING_TIME）
    - 1022, 尚不支援或尚未開通此業務（OESERR_NOT_SUPPORT）

OES_0.15.7.6_RC2 / 2018-11-22
==============================================

  * 增加 '按照配置資訊結構體初始化客戶端環境' 介面
    - OesApi_InitAllByCfgStruct
  * 增加 '一次只接收一條回報訊息' 介面
    - OesApi_RecvReportMsg
  * 增加 '設定/獲取當前執行緒訂閱回報使用的客戶端環境號' 介面
    - OesApi_SetThreadSubscribeEnvId
    - OesApi_GetThreadSubscribeEnvId

OES_0.15.7.6 / 2018-11-03
==============================================

  * '買賣型別(eOesBuySellTypeT)' 中新增:
    - '配股認購 (OES_BS_TYPE_ALLOTMENT)' 型別
  * 新增 '產品型別 (eOesProductTypeT)' 定義, 作為產品和持倉的高層類別定義
  * 在以下結構體中增加 '產品型別 (productType)' 欄位
    - 證券資訊(OesStockBaseInfoT/OesStockItemT)
    - 證券發行資訊 (OesIssueBaseInfoT/OesIssueItemT)
    - 股票持倉資訊 (OesStkHoldingBaseInfoT/OesStkHoldingItemT)
    - 委託回報 (OesOrdCnfmT/OesOrdItemT)
    - 成交回報 (OesTrdCnfmT/OesTrdItemT)
  * 證券發行產品資訊查詢介面(OesApi_QueryIssue)的過濾條件中增加:
    - ‘產品型別(productType)’ 條件
  * 股票持倉資訊查詢介面(OesApi_QueryStkHolding)的過濾條件中增加:
    - ‘產品型別(productType)’ 條件
  * '證券子型別(eOesSubSecurityTypeT)'中新增:
    - 滬倫通CDR本地交易業務產品(OES_SUB_SECURITY_TYPE_STOCK_HLTCDR)
  * 新增錯誤碼定義
    - 1035, 非法的產品型別（OESERR_ILLEGAL_PRODUCT_TYPE）
    - 1274, 股東賬戶沒有交易滬倫通存託憑證的許可權（OESERR_NO_HLTCDR_PERM）

OES_0.15.7.5 / 2018-08-31
==============================================

  * 修復Windows平臺下 OesApi_GetErrorMsg 介面返回的錯誤資訊不準確的問題

OES_0.15.7.4 / 2018-09-28
==============================================

  * fix: 修復當多個執行緒同時初始化API日誌時, 會導致日誌資訊重複輸出的問題
  * 查詢委託資訊介面的過濾條件變更:
    - 增加 '證券類別(securityType)' 查詢條件
    - 增加 '買賣型別(bsType)' 查詢條件
  * 查詢成交資訊介面的過濾條件變更:
    - 增加 '證券類別(securityType)' 查詢條件
    - 增加 '買賣型別(bsType)' 查詢條件
  * 股票持倉查詢介面的過濾條件變更:
    - 增加 '證券類別(securityType)' 查詢條件
  * 成交回報資訊(OesTrdCnfmT/OesQryTrdRspT)中增加欄位:
    - 證券子型別 (subSecurityType)
    - 原始委託數量 (origOrdQty)
    - 原始委託價格 (origOrdPrice)
  * 增加 '獲取客戶端總覽資訊 (OesApi_GetClientOverview)' 介面
  * 增加 '查詢主櫃資金資訊 (OesApi_QueryCounterCash)' 介面
  * 調整 '出入金委託請求 (OesApi_SendFundTransferReq)' 介面, 增加支援僅主櫃和銀行間出入金
  * '客戶資金資訊(OesCashAssetItemT)' 結構中增加欄位:
    - 是否禁止出入金 (isFundTrsfDisabled)
  * '證券賬戶資訊(OesInvAcctItemT)' 結構中增加欄位:
    - 是否禁止交易 (isTradeDisabled)
  * '成交查詢應答報文(OesQryTrdRspT)' 和 '成交回報應答報文(OesTrdCnfmT)' 結構體中增加欄位:
    - 證券子型別 (subSecurityType)
  * '登入應答報文(OesLogonRspT)' 結構體中增加欄位:
    - 客戶端型別 (clientType)
    - 客戶端狀態 (clientStatus)

OES_0.15.6.13 / 2018-07-16
==============================================

  * 增加修改客戶端登入密碼介面 (OesApi_SendChangePasswordReq)
  * 增加設定當前執行緒登入使用者名稱/登入密碼/客戶端環境號的介面
    - OesApi_SetThreadUsername
    - OesApi_SetThreadPassword
    - OesApi_SetThreadEnvId
  * 增加批量委託介面 (以批量的形式同時傳送多筆委託申報)
    - OesApi_SendBatchOrdersReq
    - OesApi_SendBatchOrdersReq2
  * 增加返回當前執行緒最近一次API呼叫失敗的錯誤號的介面
    - OesApi_GetLastError
    - OesApi_SetLastError
  * 新增 '市場狀態資訊查詢(OesApi_QueryMarketState)' 介面，此介面獲取到的市場狀態資訊型別定義為 'OesMarketStateItemT'
  * 增加設定/獲取客戶端自定義的裝置序列號的介面
    - OesApi_SetCustomizedDriverId
    - OesApi_GetCustomizedDriverId
  * 查詢現貨產品資訊介面的過濾條件變更:
    - 增加 '證券類別(securityType)' 查詢條件
    - 增加 '證券子類別(subSecurityType)' 查詢條件
  * 回報訊息頭(OesRptMsgHeadT) 中增加欄位 執行型別(execType), 用以區分回報的執行型別(參考eOesExecTypeT定義）
  * 增加預設回報訊息型別 OES_SUB_RPT_TYPE_DEFAULT
  * 新增回報訊息型別 '市場狀態資訊 (OESMSG_RPT_MARKET_STATE)'
  * 登入請求報文(OesLogonReqT) 中增加欄位 客戶端裝置序列號(clientDriverId)
  * 新增 交易平臺型別定義(eOesPlatformIdT)
  * 新增 市場狀態資訊結構定義(OesMarketStateInfoT)
  * 新增 存託憑證對應的證券子型別 (OES_SUB_SECURITY_TYPE_STOCK_CDR)
  * 股東賬戶交易許可權列舉(eOesTradingPermissionT)中新增
    - 存託憑證交易許可權 (OES_PERMIS_CDR)
    - 創新企業股票交易許可權 (OES_PERMIS_INNOVATION)
  * 增加 OesApi_HasMoreCachedData 介面, 用於返回已經接收到但尚未被回撥函式處理的快取資料長度
  * 新增錯誤號詳見 oes_errors.h

OES_0.15.5.17 / 2018-08-31
==============================================

  * 修復Windows平臺下 OesApi_GetErrorMsg 介面返回的錯誤資訊不準確的問題

OES_0.15.5.16 / 2018-09-28
==============================================

  * fix: 修復當多個執行緒同時初始化API日誌時, 會導致日誌資訊重複輸出的問題
  * 增加 '獲取客戶端總覽資訊 (OesApi_GetClientOverview)' 介面
  * 增加 '查詢主櫃資金資訊 (OesApi_QueryCounterCash)' 介面
  * 調整 '出入金委託請求 (OesApi_SendFundTransferReq)' 介面, 增加支援僅主櫃和銀行間出入金
  * '客戶資金資訊(OesCashAssetItemT)' 結構中增加欄位:
    - 是否禁止出入金 (isFundTrsfDisabled)
  * '證券賬戶資訊(OesInvAcctItemT)' 結構中增加欄位:
    - 是否禁止交易 (isTradeDisabled)
  * '成交查詢應答報文(OesQryTrdRspT)' 和 '成交回報資訊(OesTrdCnfmT)' 結構體中增加欄位:
    - 證券子型別 (subSecurityType)
    - 原始委託數量 (origOrdQty)
    - 原始委託價格 (origOrdPrice)
  * '登入應答報文(OesLogonRspT)' 結構體中增加欄位:
    - 客戶端型別 (clientType)
    - 客戶端狀態 (clientStatus)
  * 增加設定當前執行緒登入使用者名稱/登入密碼/客戶端環境號的介面
    - OesApi_SetThreadUsername
    - OesApi_SetThreadPassword
    - OesApi_SetThreadEnvId
  * 增加返回最近一次API呼叫失敗的錯誤號的介面
    - OesApi_GetLastError
  * '現貨產品資訊查詢過濾條件(OesQryStockFilterT)' 中新增欄位:
    - 證券類別(securityType)
    - 證券子類別(subSecurityType)
  * 增加 OesApi_HasMoreCachedData 介面, 用於返回已經接收到但尚未被回撥函式處理的快取資料長度
  * 證券子類別列舉(eOesSubSecurityTypeT) 中新增 存託憑證(OES_SUB_SECURITY_TYPE_STOCK_CDR) 子類別定義
  * 賬戶許可權列舉(eOesTradingPermissionT) 中:
    - 新增 存託憑證交易許可權(OES_PERMIS_CDR) 定義
    - 新增 創新企業股票交易許可權(OES_PERMIS_INNOVATION) 定義

OES_0.15.5.4 / 2018-02-22
==============================================

  * API將優先使用自動獲取到的ip/mac資訊，只有自動獲取到的ip/mac資訊非法時，才會使用客戶自設的ip/mac
  * 服務端將拒絕來自本地迴環地址以及非法ip/mac地址的登入
  * 修正ETF產品資訊中的欄位拼寫錯誤
    - 修正 'ETF證券基礎資訊 (OesEtfBaseInfoT)' 中 '前一交易日 (preTradingDay)' 欄位的拼寫錯誤
    - 修正 'ETF申贖產品資訊 (OesEtfItemT)' 中 '前一交易日 (preTradingDay)' 欄位的拼寫錯誤
  * Merge OES_0.15.5.2
    - fix: 解決在Windows下的相容性問題
    - fix: 修正註釋資訊中的錯誤 ('佣金查詢結果 (OesCommissionRateItemT)' 中 feeRate 欄位精度描述不正確)
    - 增加 OesApi_GetLastRecvTime、OesApi_GetLastSendTime 介面, 用於獲取通道最新發送/接受訊息的時間
    - 登入失敗時, 可以通過 errno/SPK_GET_ERRNO() 獲取到具體失敗原因

OES_0.15.5.2 / 2018-01-29 (解決Windows相容性問題的API更新版本)
==============================================

  * fix: 解決在Windows下的相容性問題。包括:
    - fix: 在Windows下, API的Socket非阻塞模式有問題, 只能工作在阻塞模式下
    - fix: 在Windows下, 當沒有行情資料時, 行情訂閱的傳送處理會長時間夯住, 直到有心跳訊息觸發才返回
    - fix: 在Windows下, 當在除錯模式下執行時, 如果網路連線異常的話, 在退出時(關閉socket連線時)就會報異常
    - fix: 在Windows下, 不能自動獲取IP和MAC地址, 需要顯式的設定客戶端本地的IP和MAC
  * fix: 修正註釋資訊中的錯誤 ('佣金查詢結果 (OesCommissionRateItemT)' 中 feeRate 欄位精度描述不正確)
  * 增加 OesApi_GetLastRecvTime、OesApi_GetLastSendTime 介面, 用於獲取通道最新發送/接受訊息的時間
  * 登入失敗時, 可以通過 errno/SPK_GET_ERRNO() 獲取到具體失敗原因

OES_0.15.5.1 / 2017-11-22
==============================================

  * 增加數值型別的協議版本號 OES_APPL_VER_VALUE, 以方便比對版本
  * 增加 OesApi_IsValidOrdChannel、OesApi_IsValidRptChannel 等介面, 用於判斷通道是否已經連線且有效

OES_0.15.5 / 2017-11-03
==============================================

  * 當前採用的協議版本號(OES_APPL_VER_ID) 升級到 0.15.5
  * 相容最低的協議版本號(OES_MIN_APPL_VER_ID) 升級到 0.15.5
  * 調整委託狀態 eOesOrdStatusT:
        - 刪除 'OES_ORD_STATUS_DECLARING (正報)' 狀態
        - 重新命名 OES_ORD_STATUS_NORMAL => OES_ORD_STATUS_NEW (新訂單)
  * 刪除結構體 '撤單拒絕 (OesOrdCancelRejectT)', 並將內容整合到 '委託拒絕 (OesOrdRejectT)' 結構體中
  * '委託拒絕 (OesOrdRejectT)' 結構體中增加欄位:
        - 客戶端編號 (clientId)
        - 客戶端環境號 (clEnvId)
        - 原始訂單的客戶委託流水號 (origClSeqNo)
        - 原始訂單的客戶端環境號 (origClEnvId)
  * '出入金拒絕 (OesFundTrsfRejectT)' 結構體中增加欄位:
        - 客戶端編號 (clientId)
        - 客戶端環境號 (clEnvId)
  * '股票持倉基礎資訊 (OesStkHoldingBaseInfoT)' 結構體中增加欄位:
        - 證券型別 (securityType)
        - 證券子型別 (subSecurityType)
  * '委託請求 (OesOrdReqT)' 和 '撤單請求(OesOrdCancelReqT)' 結構體中增加用於統計延時的時間戳
  * 欄位 __ordReqOrigSendTime, 該欄位由API在傳送時自動填充, 並在委託回報中攜帶回客戶端
  * 委託請求/撤單請求中增加用於統計延時的時間戳欄位 __ordReqOrigSendTime,
  * 該欄位由API在傳送時自動填充, 並在委託回報中攜帶回客戶端
  * 調整產品風險等級 eOesSecurityRiskLevelT 中 OES_RISK_LEVEL_VERY_LOW 欄位含義:
        - 重定義 "極低風險" => "最低風險"
  * 調整客戶狀態/證券帳戶/資金賬戶狀態 eOesAcctStatusT:
        - 刪除 OES_ACCT_STATUS_CLOSE    (銷戶) 等
        - 增加 OES_ACCT_STATUS_DISABLED (非正常)
  * 刪除 eOesSourceTypeT 定義
  * 刪除回報訊息型別 '撤單拒絕 (OESMSG_RPT_CANCEL_REJECT)', 並整合到 '委託拒絕 (OESMSG_RPT_ORDER_REJECT)' 訊息中
  * 重新命名回報訊息型別 OESMSG_RPT_ORDER_REJECT => OESMSG_RPT_BUSINESS_REJECT (OES業務拒絕, 委託/撤單未通過風控檢查等)
  * 增加可訂閱的回報訊息型別 OES_SUB_RPT_TYPE_BUSINESS_REJECT
  * 調整查詢應答報文中攜帶查詢資料的最大條目數量
  * 調整 '查詢請求訊息頭(OesQryReqHeadT)' 部分欄位：
        - '查詢視窗大小'欄位重新命名 pageSize => maxPageSize
        - '查詢起始位置'欄位重新命名 position => lastPosition
  * 調整 '查詢應答訊息頭(OesQryRspHeadT)' 部分欄位：
        - '查詢到的資訊條目數'欄位重新命名 itemCnt => itemCount
        - '查詢到的最後一條資訊的位置'欄位重新命名 position => lastPosition
  * 調整 '查詢應答訊息頭(OesQryRspHeadT)' 部分欄位：
        - '查詢到的資訊條目數'欄位重新命名 itemCnt => itemCount
        - '查詢到的最後一條資訊的位置'欄位重新命名 position => lastPosition
  * '股票持倉資訊 (OesStkHoldingItemT)' 結構體中增加欄位:
        - 證券型別 (securityType)
        - 證券子型別 (subSecurityType)
  * 調整 '資金資訊(OesCashAssetItemT)' 中部分欄位:
        - '當前餘額'欄位重新命名 currentBal => currentTotalBal

OES_0.15.4.3 / 2017-10-27
==============================================

  * '委託拒絕的結構體(OesOrdRejectT)' 中
        - 新增欄位 客戶端編號 (clientId)
        - 新增欄位 客戶端環境號 (clEnvId)
  * '撤單拒絕的結構體(OesOrdCancelRejectT)' 中
        - 新增欄位 客戶端編號 (clientId)
        - 新增欄位 客戶端環境號 (clEnvId)
  * '出入金拒絕的結構體(OesFundTrsfRejectT)' 中
        - 新增欄位 客戶端編號 (clientId)
        - 新增欄位 客戶端環境號 (clEnvId)

OES_0.15.4.2 / 2017-10-16
==============================================

  * 為委託拒絕、撤單拒絕回報訊息結構增加錯誤原因(ordRejReason)欄位
  * 新增交易類請求訊息 '測試請求 (OesTestRequestReqT)'
  * 新增回報訊息型別 '測試請求的應答 (OesTestRequestRspT)'

OES_0.15.4.1 / 2017-09-19
==============================================

  * '出入金基礎資訊 (OesFundTrsfBaseInfoT)'中
        - 新增欄位 是否僅調撥 (isAllotOnly)
  * '出入金委託回報的結構體(OesFundTrsfReportT)' 中
        - 新增欄位 是否僅調撥 (isAllotOnly)
        - 新增欄位 資金調撥流水號 (allotSerialNo)
  * '股票持倉基礎資訊 (OesStkHoldingBaseInfoT)'中
        - 刪除欄位 持倉成本 (costAmount)
        - 新增欄位 日初總持倉成本 (originalCostAmt)
        - 新增欄位 日中累計買入金額 (totalBuyAmt)
        - 新增欄位 日中累計賣出金額 (totalSellAmt)
        - 新增欄位 日中累計買入費用 (totalBuyFee)
        - 新增欄位 日中累計賣出費用 (totalSellFee)
  * '股票持倉查詢結果 (OesStkHoldingItemT)' 中
        - 刪除欄位 持倉成本 (costAmount)
        - 新增欄位 日初總持倉成本 (originalCostAmt)
        - 新增欄位 日中累計買入金額 (totalBuyAmt)
        - 新增欄位 日中累計賣出金額 (totalSellAmt)
        - 新增欄位 日中累計買入費用 (totalBuyFee)
        - 新增欄位 日中累計賣出費用 (totalSellFee)
  * '出入金回報和查詢結果 (OesFundTrsfReportT/OesFundTransferSerialItemT)' 中
        - 新增欄位 主櫃錯誤碼 (counterErrCode)
            發生主櫃錯誤時記錄主櫃錯誤碼，錯誤原因(rejReason)欄位值為'OESERR_COUNTER_ERR'
  * '委託回報和查詢結果 (OesOrdCnfmT/OesOrdItemT)' 中
        - 新增欄位 交易所錯誤碼 (exchErrCode)
            發生交易所錯誤時記錄交易所錯誤碼，錯誤原因(ordRejReason)欄位值為'OESERR_EXCHANGE_ERR'
  * 委託回報、成交回報中增加計時打點資訊
  * 委託查詢、成交查詢應答結構中增加打點計時資訊
  * 調整費用（佣金/固定費用）的費率支援精度，從百萬分之一修改為千萬分之一
        - OES_FEE_RATE_UNIT 從1000000修改為10000000
  * 調整回報訊息型別的定義順序和取值
        - OESMSG_RPT_ORDER_INSERT, OESMSG_RPT_ORDER_REJECT, OESMSG_RPT_CANCEL_REJECT

OES_0.15.4 / 2017-09-04
==============================================

  * 新增交易類訊息 '撤單請求訊息 (OESMSG_ORD_CANCEL_REQUEST)'
  * 新增結構體 '撤單請求 (OesOrdCancelReqT)'
  * 新增回報訊息型別 '撤單拒絕 (OESMSG_RPT_CANCEL_REJECT)'，
   對應回報訊息 OesRptMsgBodyT::cancelRejectRsp
  * 委託拒絕訊息中將不再包含撤單委託, 所有被OES拒絕的撤單請求和撤單委託都將通過新增的撤單拒絕訊息進行回報
  * 新增回報訊息型別 '資金變動資訊 (OESMSG_RPT_CASH_ASSET_VARIATION)'，
   對應回報訊息 OesRptMsgBodyT::cashAssetRpt
  * 新增回報訊息型別 '持倉變動資訊 (股票) (OESMSG_RPT_STOCK_HOLDING_VARIATION)'，
   對應回報訊息 OesRptMsgBodyT::stkHoldingRpt
  * 新增回報訊息型別 '持倉變動資訊 (期權) (OESMSG_RPT_OPTION_HOLDING_VARIATION)'，
   對應回報訊息 OesRptMsgBodyT::optHoldingRpt
  * '委託確認資訊 (OesOrdCnfmT)' 中增加欄位:
        - 客戶端編號 (clientId)
        - 客戶端環境號 (clEnvId)
        - 原始訂單的客戶委託流水號 (origClSeqNo)
        - 原始訂單的客戶端環境號 (origClEnvId)
        - 交易所訂單編號 (exchOrdId)
        - 委託回報的結構體大小增加了24位元組, 欄位偏移位置也發生了變化
  * '成交回報資訊 (OesTrdCnfmT)' 中增加欄位:
        - 客戶端編號 (clientId)
        - 客戶端環境號 (clEnvId)
        - 成交回報的結構體大小增加了8位元組, 欄位偏移位置也發生了變化
  * '股票持倉基礎資訊 (OesStkHoldingBaseInfoT)' 中增加欄位:
        - 持倉成本 (costAmount)
  * 整理以下結構體定義, 調整了欄位順序, 並刪除了個別欄位
        - 現貨產品基礎資訊 (OesStockBaseInfoT)
        - 期權產品基礎資訊 (OesOptionBaseInfoT)
        - 證券賬戶基礎資訊 (OesInvAcctBaseInfoT)
  * 重新命名 '出入金拒絕 (OesFundTrsfRejectReportT)' => OesFundTrsfRejectT
  * 調整列舉型別 '出入金委託狀態 (eOesFundTrsfStatusT)' 的取值
  * 查詢請求中訊息頭的型別由 'OesQryHeadT' 改為 'OesQryReqHeadT'
  * 查詢應答中訊息頭的型別由 'OesQryHeadT' 改為 'OesQryRspHeadT'
  * 刪除 'OesQryHeadT' 型別定義
  * '委託資訊查詢結果 (OesOrdItemT)' 中增加欄位:
        - 客戶端編號 (clientId)
        - 客戶端環境號 (clEnvId)
        - 原始訂單的客戶委託流水號 (origClSeqNo)
        - 原始訂單的客戶端環境號 (origClEnvId)
        - 交易所訂單編號 (exchOrdId)
  * '成交資訊查詢結果 (OesTrdItemT)' 中增加欄位:
        - 客戶端編號 (clientId)
        - 客戶端環境號 (clEnvId)
  * '股票持倉查詢結果 (OesStkHoldingItemT)' 中增加欄位:
        - 持倉成本 (costAmount)
        - 持倉成本價 (costPrice)
  * 整理以下結構體定義, 調整了欄位順序, 並刪除了個別欄位
        - 現貨產品資訊查詢結果 (OesStockItemT)
        - 期權產品資訊查詢結果 (OesOptionItemT)
        - 證券賬戶資訊查詢結果 (OesInvAcctItemT)
  * API中增加客戶端環境號 (clEnvId), 涉及到以下函式介面、資料結構、通訊報文的變更:
        - 以下介面函式的引數發生變更 (增加引數 clEnvId):
            - 連線並登入到指定的OES節點與服務 (OesApi_Logon)
            - 連線並登入到OES服務叢集 (OesApi_LogonReplicaSet)
            - 連線並登入到OES服務叢集 (OesApi_LogonPeerNodes)
            - 傳送回報同步訊息 (OesApi_SendReportSynchronization)
        - 以下通訊報文發生變更 (增加欄位 clEnvId):
            - 登入請求/應答報文 (OesLogonReqT / OesLogonRspT)
        - 以下通訊報文發生變更 (增加欄位 subscribeEnvId):
            - 回報同步請求/應答訊息 (OesReportSynchronizationReqT / OesReportSynchronizationRspT)
        - 以下資料結構發生變更 (增加欄位 clEnvId):
            - 客戶端會話資訊/連線通道資訊 (OesApiSessionInfoT)
            - 遠端主機配置資訊 (OesApiRemoteCfgT)
  * API中新增介面 '重置執行緒級別的日誌記錄器名稱 (OesApi_ResetThreadLoggerName)'，
   以支援為當前執行緒設定獨立的日誌檔案
  * 重新命名介面函式 OesApi_SendFundTrsfReq => OesApi_SendFundTransferReq
  * 新增介面 '獲取API的發行版本號 (OesApi_GetApiVersion)'
  * 新增介面 '獲取當前交易日 (OesApi_GetTradingDay)'
  * 新增介面 '傳送撤單請求 (OesApi_SendOrderCancelReq)'
        - 相比原來的撤單方式, 撤單請求介面支援通過 clEnvId + clSeqNo 進行撤單
  * 調整回報介面回撥方法型別定義 F_OESAPI_ONMSG_T => F_OESAPI_ON_RPT_MSG_T
  * 調整查詢介面回撥方法型別定義 F_OESAPI_ONMSG_T => F_OESAPI_ON_QRY_MSG_T
  * 查詢介面回撥方法中增加 OesQryCursorT 型別引數，其中攜帶“是否是最後一條”資訊
  * 所有的查詢過濾條件(OesQryXXXFilterT) 中增加 userInfo欄位，
   此欄位會在對應的查詢應答訊息(OesQryXXXRspT) 的應答頭中原樣帶回

OES_0.15.3 / 2017-08-14
==============================================

  * 當前採用的協議版本號(OES_APPL_VER_ID) 升級到 0.15.3
  * 相容最低的協議版本號(OES_MIN_APPL_VER_ID) 升級到 0.15.3
  * 新增 投資者分類(eOesInvestorClassT) 列舉定義
  * 新股配號、中籤記錄資訊(OesLotWinningBaseInfoT) 中
        - 刪除 客戶程式碼(custId) 欄位
        - 新增 證券名稱(securityName) 欄位
  * 證券發行基礎資訊(OesIssueBaseInfoT) 中
        - 新增 發行起始日(startDate) 欄位
        - 新增 發行結束日(endDate) 欄位
  * 客戶基礎資訊(OesCustBaseInfoT) 中
        - 新增 機構標誌(institutionFlag) 欄位
        - 新增 投資者分類(investorClass) 欄位
  * 證券賬戶基礎資訊(OesInvAcctBaseInfoT) 中刪除 適當性管理分類(qualificationClass) 欄位
  * Merge OES_0.12.9.12
    - fix: 針對Windows平臺, 因為GNULib的recv方法在多執行緒時有問題, 會出現不同的 Socket 互相干擾和序列執行的現象, 所以暫時切換回使用只能工作於阻塞模式的read/write方法
    - 已知問題:
      - 在Windows下, API的Socket非阻塞模式有問題, 暫時只能工作在阻塞模式下
  * Merge OES_0.12.9.11
    - fix: 重構跨平臺處理, 完善API對Windows平臺的支援
    - fix: 修復在Windows下，Socket未能正確設定為非阻塞模式的BUG
      - fix: 修復在Windows下，因為errno不相容導致網路處理失敗的BUG
      - fix: 修復在Windows下，因為檔案路徑處理方式不相容，導致日誌初始化失敗的BUG
      - fix: 修復在Windows下，個別函式不相容導致編譯警告和執行錯誤的問題
      - fix: 修復因為中文字元編碼不一致導致在Windows下編譯失敗的問題
      - refactor: 在API標頭檔案中預設引用 spk_platforms.h 標頭檔案
      - refactor: 重構API樣例程式碼和樣例配置檔案

OES_0.15.2.2 / 2017-08-07
==============================================

  * 登入時oes-server端增加IP、MAC非空的校驗
  * 新增 出入金執行的掛起狀態(OES_FUND_TRSF_STS_SUSPENDED)
  * 出入金拒絕回報訊息中調整'錯誤碼資訊'欄位命名 rejReasonInfo => errorInfo
  * 出入金執行回報訊息中調整'錯誤碼資訊'欄位命名 rejReasonInfo => errorInfo

OES_0.15.2.1 / 2017-07-31
==============================================

  * 當前採用的協議版本號(OES_APPL_VER_ID) 升級到 0.15.2
  * 相容最低的協議版本號(OES_MIN_APPL_VER_ID) 升級到 0.15.2
  * 新增 出入金業務拒絕的回報結構定義(OesFundTrsfRejectT)
  * 出入金業務拒絕訊息型別變更 OesFundTrsfReqT => OesFundTrsfRejectT
  * 出入金委託回報的結構體(OesFundTrsfReportT) 中新增欄位 錯誤碼資訊(rejReasonInfo)
  * 重新命名 '出入金委託狀態' 的巨集定義
        - 調整 OES_FUND_TRSF_STS_RECV => OES_FUND_TRSF_STS_UNDECLARED
        - 調整 OES_FUND_TRSF_STS_DCLR => OES_FUND_TRSF_STS_DECLARED
        - 調整 OES_FUND_TRSF_STS_DCLR_ROLLBACK => OES_FUND_TRSF_STS_UNDECLARED_ROLLBACK
        - 調整 OES_FUND_TRSF_STS_DONE_ROLLBACK => OES_FUND_TRSF_STS_DECLARED_ROLLBACK
  * 許可權不足交易失敗時的錯誤碼細分(詳情請見 README 錯誤碼錶部分)

OES_0.15.2 / 2017-07-18
==============================================

  * API介面中新增 傳送出入金委託請求(OesApi_SendFundTrsfReq) 介面
  * API介面中新增 查詢新股配號、中籤資訊(OesApi_QueryLotWinning) 介面
  * 新增 '新股認購、中籤資訊查詢' 相關報文定義
        - 新增欄位 查詢新股認購、中籤資訊過濾條件(OesQryLotWinningFilterT)
        - 新增欄位 新股認購、中籤資訊內容(OesLotWinningItemT)
        - 新增欄位 查詢新股認購、中籤資訊請求(OesQryLotWinningReqT)
        - 新增欄位 查詢新股認購、中籤資訊應答(OesQryLotWinningRspT)
  * 新增 OES中籤、配號記錄型別(eOesLotTypeT)
  * 新增 OES配號失敗原因(eOesLotRejReasonT)
  * 出入金委託狀態(eOesFundTrsfStatusT) 中新增如下狀態
        - 指令已報到主櫃前待回滾(OES_FUND_TRSF_STS_UNDECLARED_ROLLBACK)
        - 指令已報到主櫃後待回滾(OES_FUND_TRSF_STS_DECLARED_ROLLBACK)
        - 出入金指令完成，等待事務結束(OES_FUND_TRSF_STS_WAIT_DONE)

OES_0.15.1 / 2017-06-26
==============================================

  * 當前採用的協議版本號(OES_APPL_VER_ID) 升級到 0.15.1
  * 相容最低的協議版本號(OES_MIN_APPL_VER_ID) 升級到 0.15.1
  * '現貨產品基礎資訊(OesStockBaseInfoT)' 中
        - 調整欄位 isQualificationRequired => qualificationClass,
            取值請參考 eOesQualificationClassT
        - 新增欄位 產品風險等級(securityRiskLevel)，取值請參考 eOesSecurityRiskLevelT
        - 新增欄位 逆回購期限(repoExpirationDays)
        - 新增欄位 佔款天數(cashHoldDays) 欄位
  * '客戶資金基礎資訊(OesCashAssetBaseInfoT)'與'資金查詢的返回資訊(OesCashAssetItemT)' 中
        - 欄位重新命名 期初餘額(originalBal => beginningBal)
        - 新增欄位 期初可用餘額(beginningAvailableBal)
        - 新增欄位 期初可取餘額(beginningDrawableBal)
        - 新增欄位 當前衝正金額(紅衝藍補的資金淨額, reversalAmt)
  * '客戶基礎資訊(OesCustBaseInfoT)' 中
        - 新增欄位 風險等級(riskLevel)
        - 新增欄位 原始風險等級(originRiskLevel)
  * '證券賬戶基礎資訊(OesInvAcctBaseInfoT)' 中
        - 調整欄位 '(券賬戶許可權限制, acctLimit)'
            - 型別 uint32 => uint64
            - 重新命名 acctLimit => Limits
        - 調整欄位 '(股東許可權/客戶許可權, acctRight)'
            - 型別 uint32 => uint64
            - 重新命名 acctRight => permissions
        - 新增欄位 適當性管理分類(qualificationClass)
  * '股票持倉基礎資訊(OesStkHoldingBaseInfoT)'與'持倉查詢的返回資訊(OesStkHoldingItemT)' 中
        - 新增欄位 手動凍結持倉(管理員凍結持倉淨額, manualFrzHld)
  * '委託查詢的過濾條件(OesQryOrdFilterT)' 中
        - 新增欄位 委託的起始時間(startTime) 和 委託的結束時間(endTime)
  * '成交查詢的過濾條件(OesQryTrdFilterT)' 中
        - 新增欄位 成交的起始時間(startTime) 和 成交的結束時間(endTime)
  * '持倉查詢的返回資訊(OesStkHoldingItemT)' 中新增欄位 總持倉(sumHld)
  * '資金查詢的返回資訊(OesCashAssetItemT)' 中
        - 新增欄位 當前餘額(currentBal)
        - 欄位重新命名 當前可用餘額(tradeAvlAmt => currentAvailableBal)
        - 欄位重新命名 當前可取餘額(withdrawAvlAmt => currentDrawableBal)
  * 新增交易許可權的列舉值定義 eOesTradingPermissionT, eOesTradingLimitT
  * 交易許可權的元資料定義 OesTradingPermissionEntryT
  * 重新命名列舉型別 eOesExchangeTypeT => eOesExchangeIdT

OES_0.12.9.12 / 2017-08-13
==============================================

  * fix: 針對Windows平臺, 因為GNULib的recv方法在多執行緒時有問題, 會出現不同的 Socket 互相干擾和序列執行的現象, 所以暫時切換回使用只能工作於阻塞模式的read/write方法
  * 已知問題:
    - 在Windows下, API的Socket非阻塞模式有問題, 暫時只能工作在阻塞模式下

OES_0.12.9.11 / 2017-08-12
==============================================

  * 重構跨平臺處理, 完善API對Windows平臺的支援
    - fix: 修復在Windows下，Socket未能正確設定為非阻塞模式的BUG
    - fix: 修復在Windows下，因為errno不相容導致網路處理失敗的BUG
    - fix: 修復在Windows下，因為檔案路徑處理方式不相容，導致日誌初始化失敗的BUG
    - fix: 修復在Windows下，個別函式不相容導致編譯警告和執行錯誤的問題
    - fix: 修復因為中文字元編碼不一致導致在Windows下編譯失敗的問題
    - refactor: 重構跨平臺處理, 完善對Windows平臺的支援, 並在API標頭檔案中預設引用spk_platforms.h
    - refactor: 重構API樣例程式碼和樣例配置檔案

OES_0.12.9_RC1  2017-06-05
==============================================

  * 當前採用的協議版本號(OES_APPL_VER_ID) 升級到 0.12.9
  * 調整佣金查詢結果中feeRate欄位的精度，當佣金計算模式為 '按份數' 時，
   feeRate 欄位所代表的比率單位由 '萬分之一' *> '百萬分之一'

OES_0.12.8.2 / 2017-05-16
==============================================

  * 新增 '買賣型別' 新股認購(OES_BS_TYPE_SUBSCRIPTION)
  * 重新命名 如下'買賣型別' 定義，原始買賣型別將被廢棄
        - 買入 OES_BS_TYPE_B => OES_BS_TYPE_BUY
        - 賣出 OES_BS_TYPE_S => OES_BS_TYPE_SELL
        - 申購 OES_BS_TYPE_KB => OES_BS_TYPE_CREATION
        - 贖回 OES_BS_TYPE_KS => OES_BS_TYPE_REDEMPTION
        - 融資買入 OES_BS_TYPE_CB => OES_BS_TYPE_CREDIT_BUY
        - 融券賣出，質押式逆回購 OES_BS_TYPE_CS => OES_BS_TYPE_CREDIT_SELL
        - 期權買入開倉 OES_BS_TYPE_BO => OES_BS_TYPE_BUY_OPEN
        - 期權買入平倉 OES_BS_TYPE_BC => OES_BS_TYPE_BUY_CLOSE
        - 期權賣出開倉 OES_BS_TYPE_SO => OES_BS_TYPE_SELL_OPEN
        - 期權賣出平倉 OES_BS_TYPE_SC => OES_BS_TYPE_SELL_CLOSE
        - 期權備兌開倉 OES_BS_TYPE_CO => OES_BS_TYPE_COVERED_OPEN
        - 期權備兌平倉 OES_BS_TYPE_CC => OES_BS_TYPE_COVERED_CLOSE
        - 期權行權 OES_BS_TYPE_TE => OES_BS_TYPE_OPTION_EXERCISE
        - 期權標的鎖定 OES_BS_TYPE_UF => OES_BS_TYPE_UNDERLYING_FREEZE
        - 期權標的解鎖 OES_BS_TYPE_UU => OES_BS_TYPE_UNDERLYING_UNFREEZE
  * 新增 '證券發行基礎資訊(OesIssueBaseInfoT)'
  * '產品基礎資訊(OesStockBaseInfoT)' 中新增欄位
        - 新增 是否需要適當性管理(isQualificationRequired)
        - 新增 是否支援當日迴轉交易(isDayTrading)
        - 新增 每百元面值債券應計利息(bondInterest)，精確到元后8位
  * '產品基礎資訊(OesStockBaseInfoT)' 中刪除欄位
        - 刪除 賣出資金是否可用(cashRealBack)
        - 刪除 買入股是否可賣出(hldnRealBack)
  * '股東賬戶基礎資訊(OesInvAcctBaseInfoT)' 中新增欄位 新股認購限額(subscriptionQuota)
  * '委託確認資訊(OesOrdCnfmT)' 中新增欄位
        - 新增 凍結利息(frzInterest)
        - 新增 已發生利息(cumInterest)
  * '成交確認資訊(OesTrdCnfmT)' 中新增欄位 已發生利息(cumInterest)
  * 新增 '證券發行資訊查詢' 相關報文定義
        - 新增 查詢證券發行資訊過濾條件(OesQryIssueFilterT)
        - 新增 證券發行資訊內容(OesIssueItemT)
        - 新增 查詢證券發行資訊請求(OesQryIssueReqT)
        - 新增 查詢證券發行資訊應答(OesQryIssueRspT)

OES_0.12.8.1 / 2017-04-24
==============================================

  * 相容最低的協議版本號(OES_MIN_APPL_VER_ID) 升級到 0.12.8
  * 重新命名 '委託確認資訊(OesOrdCnfmT)'、'成交確認資訊(OesTrdCnfmT)' 中
   __tgwSetIdx => __tgwGrpNo

OES_0.12.8 / 2017-04-17
==============================================

  * 當前協議版本號升級到 0.12.8，相容最低的協議版本號維持在 0.12.6
  * 調整 '委託確認資訊(OesOrdCnfmT)' 中部分欄位的位置
  * 新增 '委託確認資訊(OesOrdCnfmT)' 中增加深圳多交易閘道器特性相關OES內部欄位 __tgwSetIdx
  * 新增 '成交確認資訊(OesTrdCnfmT)' 中增加深圳多交易閘道器特性相關OES內部欄位 __tgwSetIdx

OES_0.12.6.3 / 2017-03-24
==============================================

  * 在mds_api.h、oes_api.h中增加sutil庫標頭檔案的引用，api使用者不在需要顯式引用sutil庫的標頭檔案

OES_0.12.6.2 / 2017-03-16
==============================================

  * 重新命名 '出入金委託' 訊息 OESMSG_NONTRD_CASH_TRSF_REQ => OESMSG_NONTRD_FUND_TRSF_REQ
  * 新增 '出入金委託響應-業務拒絕'、'出入金委託執行報告' 兩類回報訊息
  * 刪除 '出入金管理登入訊息' 巨集定義
  * 重新命名 '出入金委託'訊息的結構體定義  OesCashTrsfReqT => OesFundTrsfReqT
  * '查詢出入金流水資訊過濾條件' 中重新命名 cashSeqNo —> clSeqNo
  * 調整查詢到的 '出入金流水資訊' 結構 (與出入金委託執行回報結構一致)
  * 調整佣金查詢結果中feeRate欄位的精度，當佣金計算模式為 '按金額' 時，
   feeRate 欄位所代表的比率單位由 '十萬分之一' => '百萬分之一'
  * 調整 '買賣型別' 中期權標的鎖定(OES_BS_TYPE_UF)、期權標的解鎖(OES_BS_TYPE_UU)、
   指定登記(OES_BS_TYPE_SSE_DESIGNATION)、指定撤消(OES_BS_TYPE_SSE_RECALL_DESIGNATION)、
   託管註冊(OES_BS_TYPE_SZSE_DESIGNATION)、託管撤消(OES_BS_TYPE_SZSE_CANCEL_DESIGNATION)
   的巨集值
  * 新增 逆回購(OES_BS_TYPE_CS) 買賣型別
  * 調整 '費用計算模式' 的巨集定義 eOesCalFeeModeT => eOesCalcFeeModeT
        - 調整 OES_CAL_FEE_MODE_AMOUNT => OES_CALC_FEE_MODE_AMOUNT
        - 調整 OES_CAL_FEE_MODE_QTY => OES_CALC_FEE_MODE_QTY
        - 新增 OES_CALC_FEE_MODE_ORD (按筆數計算費用)
  * 重新命名 '出入金方向' 的巨集定義 eOesCashDirectT => eOesFundTrsfDirectT
        - 調整 OES_CASH_DIRECT_IN => OES_FUND_TRSF_DIRECT_IN
        - 調整 OES_CASH_DIRECT_OUT => OES_FUND_TRSF_DIRECT_OUT
  * 重新命名 '出入金委託狀態' 的巨集定義
        - 調整 OES_CASH_TRSF_STS_RECV => OES_FUND_TRSF_STS_UNDECLARED
        - 調整 OES_CASH_TRSF_STS_DCLR => OES_FUND_TRSF_STS_DECLARED
        - 調整 OES_CASH_TRSF_STS_DONE => OES_FUND_TRSF_STS_DONE
        - 調整 OES_CASH_TRSF_STS_INVALID_OES => OES_FUND_TRSF_STS_INVALID_OES
        - 調整 OES_CASH_TRSF_STS_INVALID_COUNTER => OES_FUND_TRSF_STS_INVALID_COUNTER
  * 調整 '產品級別'(eOesSecurityLevelT) 中的列舉值
  * 刪除 無用的'訂單時間型別'(eOesOrdTimeTypeT) 的列舉定義
  * 刪除 無用的'權利類別'(eOesRightTypeT) 的列舉定義
  * '出入金委託基礎資訊' 中增加 使用者私有資訊(userInfo) 欄位
  * 增加 '出入金委託回報基礎資訊'

OES_0.12.3.5 / 2017-02-20
==============================================

  * 遷移報撤比相關的巨集定義
  * 刪除賣清倉閾值的巨集定義
  * 新增債券、基金的證券型別，調整ETF證券型別巨集定義的取值
  * 新增證券子型別定義
  * 委託確認、成交回報中增加延遲統計欄位
  * 現貨產品基礎資訊中增加“證券子型別”欄位，並且重新命名“買入單位”、“賣出單位”欄位
  * ETF產品基礎資訊中增加“證券型別”、“證券子型別”欄位
  * ETF成分股基礎資訊中增加“證券子型別”欄位
  * 期權產品基礎資訊中增加“證券子型別”欄位

OES_0.12.3 / 2017-01-10
==============================================

  * 精簡API依賴的標頭檔案，並最小化API釋出包中的標頭檔案數量
  * 重新命名 protocol_parser/errors/oes_protocol_errors.h ==> errors/oes_errors.h
  * 刪除 eOesHoldTypeT 列舉型別定義
  * OesHoldItemT 結構體拆分成 OesStkHoldingItemT、OesOptHoldingItemT兩個結構體
  * 單條持倉查詢介面 OesApi_QuerySingleHolding 拆分:
        - OesApi_QuerySingleStkHolding 查詢單條股票持倉
        - OesApi_QuerySingleOptHolding 查詢單條期權持倉
  * OesApi_QuerySingleStkHolding 引數型別變更:
        - 引數四的型別變更 OesHoldItemT => OesStkHoldingItemT(原OesStockHoldInfoT)
  * OesApi_QuerySingleOptHolding 引數型別變更:
        - 引數四的型別變更 OesHoldItemT => OesOptHoldingItemT(原OesOptionHoldInfoT)
  * 批量持倉查詢介面 OesApi_QueryHolding 拆分:
        - OesApi_QueryStkHolding 查詢股票持倉
        - OesApi_QueryOptHolding 查詢期權持倉
  * OesApi_QueryStkHolding 引數型別變更:
        - 引數二的型別變更 OesQryHoldFilterT => OesQryStkHoldingFilterT
        - 引數三 pOnMsgCallback.pMsgBody 返回資料型別變更 OesHoldItemT => OesStkHoldingItemT
  * OesApi_QueryOptHolding 引數型別變更:
        - 引數二的型別變更 OesQryHoldFilterT => OesQryOptHoldingFilterT
        - 引數三 pOnMsgCallback.pMsgBody 返回資料型別變更 OesHoldItemT => OesOptHoldingItemT

OES_0.12.1 / 2016-12-21
==============================================

  * 刪除 OesApi_IsBusinessError 介面，查詢介面不再返回小於 -1000 的錯誤
  * 查詢介面返回值變更:
        - 單條查詢介面無資料返回 NEG(ENOENT)
        - 批量查詢介面無匹配資料時返回 0
        - 單條/批量 查詢被伺服器拒絕返回 NEG(EINVAL)，具體錯誤資訊通過日誌列印
  * 微調oes_api日誌列印格式
  * 刪除已不被使用的列舉定義 eOesEtfSubFlagSzT
  * 修改委託請求中ordType的資料字典 eOesOrdTypeShT eOesOrdTypeSzT
  * 委託請求、委託確認、成交回報中的userInfo聯合體中加入i64、i32型別欄位
  * 整合查詢訊息中的qryCnt、position等欄位，成為一個新的結構體 OesQryHeadT

OES_0.12 / 2016-12-06
==============================================

  * 增加客戶資訊查詢功能
  * 補充整理錯誤號的註釋資訊和部分錯誤號定義
  * 增加 OesApi_GetErrorMsg 和 OesApi_GetErrorMsg2 方法
  * 在登入報文中增加協議版本號資訊, 並在登入時校驗協議版本號的相容性
  * 增加客戶資訊查詢功能
  * ETF成分股查詢應答中增加成分股所屬ETF申贖程式碼
  * 佣金查詢應答中增加客戶程式碼
  * 增加預設佣金模板配置；為佣金模板配置項增加通配設定
  * 增加所有者(OwnerType)配置，並替換原股東賬戶中的 optAcctLevel 欄位
  * 重新命名欄位 etfId ==> fundId
  * 成交回報資訊中增加累計成交金額、累計交易費用欄位
  * 委託確認資訊中增加累計成交金額、累計交易費用、凍結金額、凍結費用欄位
