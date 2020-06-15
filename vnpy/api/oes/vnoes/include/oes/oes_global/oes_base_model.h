/*
 * Copyright 2009-2015 the original author or authors.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/**
 * @file    oes_base_model.h
 *
 * 訂單執行系統的基礎領域模型(資料結構)定義
 *
 * @version 0.11.1      2016/11/17
 * @version 0.12        2016/11/30
 *          - 增加預設佣金模板配置; 為佣金模板配置項增加通配設定
 *          - 增加所有者(OwnerType)配置, 並替換原股東賬戶中的 optAcctLevel 欄位
 *          - 重新命名欄位 etfId ==> fundId
 *          - 成交回報資訊中增加累計成交金額、累計交易費用欄位
 *          - 委託確認資訊中增加累計成交金額、累計交易費用、凍結金額、凍結費用欄位
 *          - 在登入報文中增加協議版本號資訊, 並在登入時校驗協議版本號的相容性
 * @version 0.12.1      2016/12/19
 *          - 刪除已不被使用的列舉定義 eOesEtfSubFlagSzT
 *          - 修改委託請求中ordType的資料字典 eOesOrdTypeShT eOesOrdTypeSzT
 *          - 委託請求、委託確認、成交回報中的userInfo聯合體中加入i64、i32型別欄位
 * @version 0.12.3      2017/01/10
 *          - 股票持倉基礎資訊結構體與期權持倉基礎資訊接結構體拆分
 *          - 刪除 eOesHoldTypeT 列舉型別定義
 * @version 0.12.3.5    2017/02/20
 *          - 遷移報撤比相關的巨集定義
 *          - 刪除賣清倉閾值的巨集定義
 *          - 新增債券、基金的證券型別, 調整ETF證券型別巨集定義的取值
 *          - 新增證券子型別定義
 *          - 委託確認、成交回報中增加延遲統計欄位
 *          - 現貨產品基礎資訊中增加“證券子型別”欄位, 並且重新命名“買入單位”、“賣出單位”欄位
 *          - ETF產品基礎資訊中增加“證券型別”、“證券子型別”欄位
 *          - ETF成分股基礎資訊中增加“證券子型別”欄位
 *          - 期權產品基礎資訊中增加“證券子型別”欄位
 * @version 0.12.6.2    2017/03/16
 *          - 調整 ‘買賣型別’ 中期權標的鎖定(OES_BS_TYPE_UF)、期權標的解鎖(OES_BS_TYPE_UU)、
 *              指定登記(OES_BS_TYPE_SSE_DESIGNATION)、指定撤消(OES_BS_TYPE_SSE_RECALL_DESIGNATION)、
 *              託管註冊(OES_BS_TYPE_SZSE_DESIGNATION)、託管撤消(OES_BS_TYPE_SZSE_CANCEL_DESIGNATION)
 *              的巨集值
 *          - 新增 逆回購(OES_BS_TYPE_CS) 買賣型別
 *          - 調整 ‘費用計算模式’ 的巨集定義 eOesCalFeeModeT => eOesCalcFeeModeT
 *              - 調整 OES_CAL_FEE_MODE_AMOUNT => OES_CALC_FEE_MODE_AMOUNT
 *              - 調整 OES_CAL_FEE_MODE_QTY => OES_CALC_FEE_MODE_QTY
 *              - 新增 OES_CALC_FEE_MODE_ORD (按筆數計算費用)
 *          - 重新命名 ‘出入金方向’ 的巨集定義 eOesCashDirectT => eOesFundTrsfDirectT
 *              - 調整 OES_CASH_DIRECT_IN => OES_FUND_TRSF_DIRECT_IN
 *              - 調整 OES_CASH_DIRECT_OUT => OES_FUND_TRSF_DIRECT_OUT
 *          - 重新命名 ‘出入金委託狀態’ 的巨集定義
 *              - 調整 OES_CASH_TRSF_STS_RECV => OES_FUND_TRSF_STS_RECV
 *              - 調整 OES_CASH_TRSF_STS_DCLR => OES_FUND_TRSF_STS_DCLR
 *              - 調整 OES_CASH_TRSF_STS_DONE => OES_FUND_TRSF_STS_DONE
 *              - 調整 OES_CASH_TRSF_STS_INVALID_OES => OES_FUND_TRSF_STS_INVALID_OES
 *              - 調整 OES_CASH_TRSF_STS_INVALID_COUNTER => OES_FUND_TRSF_STS_INVALID_COUNTER
 *          - 調整 ‘產品級別’(eOesSecurityLevelT) 中的列舉值
 *          - 刪除 無用的‘訂單時間型別’(eOesOrdTimeTypeT) 的列舉定義
 *          - 刪除 無用的‘權利類別’(eOesRightTypeT) 的列舉定義
 *          - ‘出入金委託基礎資訊’ 中增加 使用者私有資訊(userInfo) 欄位
 *          - 增加 ‘出入金委託回報基礎資訊’
 * @version 0.12.8      2017/04/17
 *          - 調整 ‘委託確認資訊(OesOrdCnfmT)’ 中部分欄位的位置
 *          - 新增 ‘委託確認資訊(OesOrdCnfmT)’ 中增加深圳多交易閘道器特性相關OES內部欄位
 *            __tgwSetIdx、__tgwIdx、__declaredTgwIdx
 *          - 新增 ‘成交確認資訊(OesTrdCnfmT)’ 中增加深圳多交易閘道器特性相關OES內部欄位
 *            __tgwSetIdx
 * @version 0.12.8.1    2017/04/24
 *          - 重新命名 ‘委託確認資訊(OesOrdCnfmT)’、‘成交確認資訊(OesTrdCnfmT)’ 中
 *            __tgwSetIdx => __tgwGroupIdx
 * @version 0.12.8.2    2017/05/16
 *          - 新增 ‘買賣型別’ 新股認購(OES_BS_TYPE_SUBSCRIPTION)
 *          - 重新命名 如下‘買賣型別’ 定義, 原始買賣型別將被廢棄
 *              - 買入 OES_BS_TYPE_B => OES_BS_TYPE_BUY
 *              - 賣出 OES_BS_TYPE_S => OES_BS_TYPE_SELL
 *              - 申購 OES_BS_TYPE_KB => OES_BS_TYPE_CREATION
 *              - 贖回 OES_BS_TYPE_KS => OES_BS_TYPE_REDEMPTION
 *              - 融資買入 OES_BS_TYPE_CB => OES_BS_TYPE_CREDIT_BUY
 *              - 融券賣出, 質押式逆回購 OES_BS_TYPE_CS => OES_BS_TYPE_CREDIT_SELL
 *              - 期權買入開倉 OES_BS_TYPE_BO => OES_BS_TYPE_BUY_OPEN
 *              - 期權買入平倉 OES_BS_TYPE_BC => OES_BS_TYPE_BUY_CLOSE
 *              - 期權賣出開倉 OES_BS_TYPE_SO => OES_BS_TYPE_SELL_OPEN
 *              - 期權賣出平倉 OES_BS_TYPE_SC => OES_BS_TYPE_SELL_CLOSE
 *              - 期權備兌開倉 OES_BS_TYPE_CO => OES_BS_TYPE_COVERED_OPEN
 *              - 期權備兌平倉 OES_BS_TYPE_CC => OES_BS_TYPE_COVERED_CLOSE
 *              - 期權行權 OES_BS_TYPE_TE => OES_BS_TYPE_OPTION_EXERCISE
 *              - 期權標的鎖定 OES_BS_TYPE_UF => OES_BS_TYPE_UNDERLYING_FREEZE
 *              - 期權標的解鎖 OES_BS_TYPE_UU => OES_BS_TYPE_UNDERLYING_UNFREEZE
 *          - 新增 ‘證券發行基礎資訊’
 *          - 新增 ‘產品基礎資訊(OesStockBaseInfoT)’ 中新增欄位
 *              - 新增 是否需要適當性管理(isQualificationRequired)
 *              - 新增 是否支援當日迴轉交易(isDayTrading)
 *              - 新增 每百元面值債券應計利息(bondInterest), 精確到元后8位
 *          - 刪除 ‘產品基礎資訊(OesStockBaseInfoT)’ 中刪除欄位
 *              - 刪除 賣出資金是否可用(cashRealBack)
 *              - 刪除 買入股是否可賣出(hldnRealBack)
 *          - 新增 ‘股東賬戶基礎資訊(OesInvAcctBaseInfoT)’ 中新增欄位 新股認購限額(subscriptionQuota)
 *          - 新增 ‘委託確認資訊(OesOrdCnfmT)’ 中新增欄位
 *              - 新增 凍結利息(frzInterest)
 *              - 新增 已發生利息(cumInterest)
 *          - 新增 ‘成交確認資訊(OesTrdCnfmT)’ 中新增欄位
 *              - 新增 已發生利息(cumInterest)
 * @version 0.15.1      2017/06/26
 *          - ‘現貨產品基礎資訊(OesStockBaseInfoT)’ 中
 *              - 調整欄位 isQualificationRequired => qualificationClass,
 *                  取值請參考 eOesQualificationClassT
 *              - 新增欄位 產品風險等級(securityRiskLevel), 取值請參考 eOesSecurityRiskLevelT
 *              - 新增欄位 逆回購期限(repoExpirationDays)
 *              - 新增欄位 佔款天數(cashHoldDays) 欄位
 *          - ‘客戶資金基礎資訊(OesCashAssetBaseInfoT)’ 中
 *              - 欄位重新命名 期初餘額(originalBal => beginningBal)
 *              - 新增欄位 期初可用餘額(beginningAvailableBal)
 *              - 新增欄位 期初可取餘額(beginningDrawableBal)
 *              - 新增欄位 當前衝正金額(紅衝藍補的資金淨額, reversalAmt)
 *          - ‘客戶基礎資訊(OesCustBaseInfoT)’ 中
 *              - 新增欄位 風險等級(riskLevel)
 *              - 新增欄位 原始風險等級(originRiskLevel)
 *          - ‘證券賬戶基礎資訊(OesInvAcctBaseInfoT)’ 中
 *              - 調整欄位 '(券賬戶許可權限制, acctLimit)'
 *                  - 型別 uint32 => uint64
 *                  - 重新命名 acctLimit => Limits
 *              - 調整欄位 '(股東許可權/客戶許可權, acctRight)'
 *                  - 型別 uint32 => uint64
 *                  - 重新命名 acctRight => permissions
 *              - 新增欄位 適當性管理分類(qualificationClass)
 *          - ‘股票持倉基礎資訊(OesStkHoldingBaseInfoT)’ 中
 *              - 新增欄位 手動凍結持倉(管理員凍結持倉淨額, manualFrzHld)
 *          - 新增交易許可權的列舉值定義 eOesTradingPermissionT, eOesTradingLimitT
 *          - 交易許可權的元資料定義 OesTradingPermissionEntryT
 *          - 重新命名列舉型別 eOesExchangeTypeT => eOesExchangeIdT
 * @version 0.15.2      2017/07/18
 *          - 新增 OES中籤、配號記錄型別(eOesLotTypeT)
 *          - 新增 OES配號失敗原因(eOesLotRejReasonT)
 *          - 出入金委託狀態(eOesFundTrsfStatusT) 中新增如下狀態
 *              - 指令已報到主櫃前待回滾(OES_FUND_TRSF_STS_DCLR_ROLLBACK)
 *              - 指令已報到主櫃後待回滾(OES_FUND_TRSF_STS_DONE_ROLLBACK)
 *              - 出入金指令完成, 等待事務結束(OES_FUND_TRSF_STS_WAIT_DONE)
 *          - 新增 新股配號、中籤記錄資訊結構體定義(OesLotWinningBaseInfoT)
 * @version 0.15.2.1    2017/07/31
 *          - 新增 出入金業務拒絕的回報結構定義(OesFundTrsfRejectReportT)
 *          - 出入金委託回報的結構體(OesFundTrsfReportT) 中
 *              - 新增欄位 錯誤資訊(rejReasonInfo)
 *          - 重新命名 ‘出入金委託狀態’ 的巨集定義
 *              - 調整 OES_FUND_TRSF_STS_RECV => OES_FUND_TRSF_STS_UNDECLARED
 *              - 調整 OES_FUND_TRSF_STS_DCLR => OES_FUND_TRSF_STS_DECLARED
 *              - 調整 OES_FUND_TRSF_STS_DCLR_ROLLBACK => OES_FUND_TRSF_STS_UNDECLARED_ROLLBACK
 *              - 調整 OES_FUND_TRSF_STS_DONE_ROLLBACK => OES_FUND_TRSF_STS_DECLARED_ROLLBACK
 * @version 0.15.2.2    2017/08/07
 *          - 新增 出入金執行的掛起狀態(OES_FUND_TRSF_STS_SUSPENDED)
 *          - 出入金拒絕回報訊息中調整‘錯誤資訊’欄位命名 rejReasonInfo => errorInfo
 *          - 出入金執行回報訊息中調整‘錯誤資訊’欄位命名 rejReasonInfo => errorInfo
 * @version 0.15.3      2017/08/14
 *          - 新增 投資者分類(eOesInvestorClassT) 列舉定義
 *          - 新股配號、中籤記錄資訊(OesLotWinningBaseInfoT) 中
 *              - 刪除 客戶程式碼(custId) 欄位
 *              - 新增 證券名稱(securityName) 欄位
 *          - 證券發行基礎資訊(OesIssueBaseInfoT) 中
 *              - 新增 發行起始日(startDate) 欄位
 *              - 新增 發行結束日(endDate) 欄位
 *          - 客戶基礎資訊(OesCustBaseInfoT) 中
 *              - 新增 機構標誌(institutionFlag) 欄位
 *              - 新增 投資者分類(investorClass) 欄位
 *          - 證券賬戶基礎資訊(OesInvAcctBaseInfoT) 中
 *              - 刪除 適當性管理分類(qualificationClass) 欄位
 * @version 0.15.4      2017/09/04
 *          - '委託確認資訊 (OesOrdCnfmT)' 中增加欄位:
 *              - 客戶端編號 (clientId)
 *              - 客戶端環境號 (clEnvId)
 *              - 原始訂單的客戶委託流水號 (origClSeqNo)
 *              - 原始訂單的客戶端環境號 (origClEnvId)
 *              - 交易所訂單編號 (exchOrdId)
 *          - '成交回報資訊 (OesTrdCnfmT)' 中增加欄位:
 *              - 客戶端編號 (clientId)
 *              - 客戶端環境號 (clEnvId)
 *          - '股票持倉基礎資訊 (OesStkHoldingBaseInfoT)' 中增加欄位:
 *              - 持倉成本 (costAmount)
 *          - 整理以下結構體定義, 調整了欄位順序, 並刪除了個別欄位
 *              - 現貨產品基礎資訊 (OesStockBaseInfoT)
 *              - 期權產品基礎資訊 (OesOptionBaseInfoT)
 *              - 證券賬戶基礎資訊 (OesInvAcctBaseInfoT)
 *          - 重新命名 '出入金拒絕 (OesFundTrsfRejectReportT)' => OesFundTrsfRejectT
 *          - 調整列舉型別 '出入金委託狀態 (eOesFundTrsfStatusT)' 的取值
 * @version 0.15.4.1    2017/09/19
 *          - 為委託拒絕、撤單拒絕、出入金拒絕分別定義獨立的回報訊息結構體, 並各自增加委託日期和委託時間欄位
 *              - 委託拒絕 (OesOrdRejectT)
 *              - 撤單拒絕 (OesOrdCancelRejectT)
 *              - 出入金拒絕 (OesFundTrsfRejectT)
 *          - '出入金基礎資訊 (OesFundTrsfBaseInfoT)'中
 *              - 新增 是否僅調撥 (isAllotOnly) 欄位
 *          - '出入金委託回報的結構體(OesFundTrsfReportT)' 中
 *              - 新增 是否僅調撥 (isAllotOnly) 欄位
 *              - 新增 資金調撥流水號 (allotSerialNo) 欄位
 *          - '股票持倉基礎資訊 (OesStkHoldingBaseInfoT)'中
 *              - 刪除 持倉成本 (costAmount) 欄位
 *              - 新增 日初總持倉成本 (originalCostAmt) 欄位
 *              - 新增 日中累計買入金額 (totalBuyAmt) 欄位
 *              - 新增 日中累計賣出金額 (totalSellAmt) 欄位
 *              - 新增 日中累計買入費用 (totalBuyFee) 欄位
 *              - 新增 日中累計賣出費用 (totalSellFee) 欄位
 *          - '股票持倉查詢結果 (OesStkHoldingItemT)' 中
 *              - 刪除 持倉成本 (costAmount) 欄位
 *              - 新增 日初總持倉成本 (originalCostAmt) 欄位
 *              - 新增 日中累計買入金額 (totalBuyAmt) 欄位
 *              - 新增 日中累計賣出金額 (totalSellAmt) 欄位
 *              - 新增 日中累計買入費用 (totalBuyFee) 欄位
 *              - 新增 日中累計賣出費用 (totalSellFee) 欄位
 *          - '出入金回報和查詢結果 (OesFundTrsfReportT/OesFundTransferSerialItemT)' 中
 *              - 新增 主櫃錯誤碼 (counterErrCode) 欄位
 *                發生主櫃錯誤時記錄具體的主櫃錯誤碼, 而錯誤原因(rejReason)欄位將統一設定為: OESERR_COUNTER_ERR
 *          - '委託回報和查詢結果 (OesOrdCnfmT/OesOrdItemT)' 中
 *              - 新增 交易所錯誤碼 (exchErrCode) 欄位
 *                發生交易所錯誤時記錄具體的交易所錯誤碼, 而錯誤原因(ordRejReason)欄位將統一設定為: OESERR_EXCHANGE_ERR
 *          - 調整固定費用和佣金的費率單位, 將精度從百萬分之一修改為千萬分之一
 *              - OES_FEE_RATE_UNIT 從 1000000 修改為 10000000
 *          - 預設開啟用於統計延時的打點資訊, 並將打點資訊的時間戳型別改為 timeval32 (STimeval32T) 型別,
 *            同時將回報推送的打點資訊, 從訊息頭遷移到訊息體中 (__pushingTime)
 * @version 0.15.4.2    2017/10/16
 *          - 為委託拒絕、撤單拒絕回報訊息結構增加錯誤原因(ordRejReason)欄位
 * @version 0.15.4.3    2017/10/27
 *          - '委託拒絕 (OesOrdRejectT)' 結構體中增加欄位:
 *              - 客戶端編號 (clientId)
 *              - 客戶端環境號 (clEnvId)
 *          - '撤單拒絕(OesOrdCancelRejectT)' 結構體中新增欄位:
 *              - 客戶端編號 (clientId)
 *              - 客戶端環境號 (clEnvId)
 *          - '出入金拒絕 (OesFundTrsfRejectT)' 結構體中增加欄位:
 *              - 客戶端編號 (clientId)
 *              - 客戶端環境號 (clEnvId)
 * @version 0.15.5      2017/11/03
 *          - 調整委託狀態 eOesOrdStatusT:
 *              - 刪除 'OES_ORD_STATUS_DECLARING (正報)' 狀態
 *              - 重新命名 OES_ORD_STATUS_NORMAL => OES_ORD_STATUS_NEW (新訂單)
 *          - 刪除結構體 '撤單拒絕 (OesOrdCancelRejectT)', 並將內容整合到 '委託拒絕 (OesOrdRejectT)' 結構體中
 *          - '委託拒絕 (OesOrdRejectT)' 結構體中增加欄位:
 *              - 原始訂單的客戶委託流水號 (origClSeqNo)
 *              - 原始訂單的客戶端環境號 (origClEnvId)
 *          - '股票持倉基礎資訊 (OesStkHoldingBaseInfoT)' 結構體中增加欄位:
 *              - 證券型別 (securityType)
 *              - 證券子型別 (subSecurityType)
 *          - '委託請求 (OesOrdReqT)' 和 '撤單請求(OesOrdCancelReqT)' 結構體中增加用於統計延時的時間戳
 *            欄位 __ordReqOrigSendTime, 該欄位由API在傳送時自動填充, 並在委託回報中攜帶回客戶端
 *          - 委託請求/撤單請求中增加用於統計延時的時間戳欄位 __ordReqOrigSendTime,
 *            該欄位由API在傳送時自動填充, 並在委託回報中攜帶回客戶端
 *          - 調整產品風險等級 eOesSecurityRiskLevelT 中 OES_RISK_LEVEL_VERY_LOW 欄位含義:
 *              - 重定義 "極低風險" => "最低風險"
 *          - 調整客戶狀態/證券帳戶/資金賬戶狀態 eOesAcctStatusT:
 *              - 刪除 OES_ACCT_STATUS_CLOSE    (銷戶) 等
 *              - 增加 OES_ACCT_STATUS_DISABLED (非正常)
 *          - 刪除 eOesSourceTypeT 定義
 * @version 0.15.5.2    2018/01/07
 *          - 修復 'ETF證券基礎資訊 (OesEtfBaseInfoT)' 中 '前一交易 (preTradingDay)'
 *            欄位的拼寫錯誤
 *          - 新增 ‘出入金金額單位’ 的巨集定義(OES_FUND_TRSF_UNIT)
 * @version 0.15.5.6    2018/04/01
 *          - 新增 交易平臺型別定義(eOesPlatformIdT)
 *          - 新增 市場狀態資訊結構定義(OesMarketStateInfoT)
 * @version 0.15.5.12   2018/06/29
 *          - 新增 存託憑證對應的證券子型別 (OES_SUB_SECURITY_TYPE_STOCK_CDR)
 *          - 股東賬戶交易許可權列舉(eOesTradingPermissionT)中新增
 *              - 存託憑證交易許可權 (OES_PERMIS_CDR)
 *              - 創新企業股票交易許可權 (OES_PERMIS_INNOVATION)
 * @version 0.15.5.14   2018/08/01
 *          - 刪除委託資訊中已不再使用的欄位 __tgwIdx、__declaredTgwIdx (協議保持相容)
 *          - 重新命名欄位 __tgwGroupIdx => __tgwGrpNo (協議保持相容)
 *          - 證券子類別列舉(eOesSubSecurityTypeT) 中新增 存託憑證(OES_SUB_SECURITY_TYPE_STOCK_CDR) 子類別定義
 *          - 賬戶許可權列舉(eOesTradingPermissionT) 中:
 *              - 新增 存託憑證交易許可權(OES_PERMIS_CDR) 定義
 *              - 新增 創新企業股票交易許可權(OES_PERMIS_INNOVATION) 定義
 *          - 出入金回報及查詢結構體(OesFundTrsfReportT, OesFundTransferSerialItemT)中新增
 *            內部欄位 '是否已轉賬到主櫃(__hasCounterTransfered)'
 *          - 調整委託確認結構體中的內部欄位定義, 調整了__declareFlag欄位的位置, 並增加了__recNum欄位
 *          - 新增 客戶端狀態定義(eOesClientStatusT) 列舉型別, 僅內部使用
 * @version 0.15.5.16   2018/08/31
 *          - 成交基礎資訊(OesTrdBaseInfoT) 中新增 證券子類別(subSecurityType) 欄位
 *          - 客戶資金基礎資訊(OesCashAssetBaseInfoT) 中新增 是否禁止出入金(isFundTrsfDisabled) 欄位
 *          - 證券賬戶基礎資訊(OesInvAcctBaseInfoT) 中新增 是否禁止交易(isTradeDisabled) 欄位
 *          - 新增 ‘出入金轉賬型別’ 定義(eOesFundTrsfTypeT)
 *          - 出入金請求(OesFundTrsfReqT) 中 '是否僅調撥(isAllotOnly)'欄位含義調整為出入金轉賬型別
 *            取值在相容原來基礎上增加型別 '主櫃和銀行之間轉賬', 參見 'eOesFundTrsfTypeT' 定義
 *          - 出入金執行回報及查詢結構(OesFundTrsfReportT / OesFundTrsfRejectT / OesFundTransferSerialItemT)
 *            中 '是否僅調撥(isAllotOnly)' 欄位取值也同步調整
 * @version 0.15.5.16_u3 2018/09/28
 *          - 調整成交基礎資訊(OesTrdBaseInfoT)和成交回報資訊(OesTrdCnfmT)的結構體欄位
 *              - 調整 v0.15.5.16 版本新增的 '證券子類別(subSecurityType)' 欄位的位置
 *              - 增加 '原始委託數量(origOrdQty)' 和 '原始委託價格(origOrdPrice)' 欄位
 * @version 0.15.6.13   2018/07/16
 *          - 新增 OES執行型別定義 (eOesExecTypeT)
 * @version 0.15.7.4_u4 2018/11/26
 *          - 調整成交基礎資訊(OesTrdBaseInfoT)和成交回報資訊(OesTrdCnfmT)的結構體欄位
 *              - 增加 __isTrsfInCashAvailable 欄位, 以標識ETF贖回得到的替代資金是否當日可用
 * @version 0.15.7.6    2018/11/03
 *          - 新增買賣型別
 *              - 配股認購 (OES_BS_TYPE_ALLOTMENT)
 *          - 新增 '產品型別 (eOesProductTypeT)' 定義, 作為產品和持倉的高層類別定義
 *          - 在以下結構體中增加 '產品型別 (productType)' 欄位
 *              - 證券資訊 (OesStockBaseInfoT/OesStockItemT)
 *              - 證券發行資訊 (OesIssueBaseInfoT/OesIssueItemT)
 *              - 股票持倉資訊 (OesStkHoldingBaseInfoT/OesStkHoldingItemT)
 *              - 委託回報 (OesOrdCnfmT/OesOrdItemT)
 *              - 成交回報 (OesTrdCnfmT/OesTrdItemT)
 *          - 新增證券子型別
 *              - 滬倫通CDR本地交易業務產品(OES_SUB_SECURITY_TYPE_STOCK_HLTCDR)
 * @version 0.15.7.6_RC2 2018/11/05
 *          - 調整交易所訂單編號(exchOrdId)的欄位長度, 從char[20]調整為char[17]
 *          - 再次調整委託確認結構體中 __declareFlag 欄位的位置
 * @version 0.15.8      2018/09/27
 *          - 委託回報和成交回報中新增供OES內部使用的 '交易閘道器平臺分割槽號(__tgwPartitionNo)' 欄位 (協議保持相容)
 * @version 0.15.9      2019/03/12
 *          - 新增證券子型別
 *              - 科創板股票 (OES_SUB_SECURITY_TYPE_STOCK_KSH)
 *              - 科創板存託憑證 (OES_SUB_SECURITY_TYPE_STOCK_KCDR)
 *          - 為了支援科創板, 擴充套件以下資料結構 (相容之前版本的API)
 *              - 證券賬戶基礎資訊 (OesInvAcctBaseInfoT) 中增加如下欄位:
 *                  - 科創板權益 (kcSubscriptionQuota)
 *              - 現貨產品基礎資訊 (OesStockBaseInfoT) 中增加如下欄位:
 *                  - 限價買數量上限 (lmtBuyMaxQty)
 *                  - 限價買數量下限 (lmtBuyMinQty)
 *                  - 限價賣數量上限 (lmtSellMaxQty)
 *                  - 限價賣數量下限 (lmtSellMinQty)
 *                  - 市價買數量上限 (mktBuyMaxQty)
 *                  - 市價買數量下限 (mktBuyMinQty)
 *                  - 市價賣數量上限 (mktSellMaxQty)
 *                  - 市價賣數量下限 (mktSellMinQty)
 *          - 重構漲跌停價格、價格檔位欄位命名, 為這些欄位增加新的別名 (相容之前版本的API)
 *                  - ceilPrice => upperLimitPrice
 *                  - floorPrice => lowerLimitPrice
 *                  - priceUnit => priceTick
 *          - 調整上證委託型別 (eOesOrdTypeShT)
 *              - 增加 '對手方最優價格申報 (OES_ORD_TYPE_SH_MTL_BEST)' 型別 (僅適用於科創板)
 *              - 增加 '本方最優價格申報 (OES_ORD_TYPE_SH_MTL_SAMEPATY_BEST)' 型別 (僅適用於科創板)
 *          - 股東賬戶交易許可權列舉(eOesTradingPermissionT)中新增
 *              - 科創板交易許可權 (OES_PERMIS_KSH)
 *
 * @since   2015/07/30
 */


#ifndef _OES_BASE_MODEL_H
#define _OES_BASE_MODEL_H


#include    <sutil/types.h>


#ifdef __cplusplus
extern "C" {
#endif


/* ===================================================================
 * 預編譯巨集處理
 * =================================================================== */

/* 預設開啟用於統計延時的打點資訊 */
#if ! defined (_OES_DISABLE_LATENCY_STATS) \
        && ! defined (_OES_EXPORT_LATENCY_STATS)
#   define  _OES_EXPORT_LATENCY_STATS       1
#elif defined (_OES_DISABLE_LATENCY_STATS) \
        && defined (_OES_EXPORT_LATENCY_STATS)
#   undef   _OES_EXPORT_LATENCY_STATS
#endif
/* -------------------------           */


/* ===================================================================
 * 常量定義
 * =================================================================== */

/** 客戶端名稱最大長度 */
#define OES_CLIENT_NAME_MAX_LEN             (32)
/** 客戶端說明最大長度 */
#define OES_CLIENT_DESC_MAX_LEN             (32)
/** 客戶端標籤最大長度 */
#define OES_CLIENT_TAG_MAX_LEN              (32)
/** 密碼最大長度 */
#define OES_PWD_MAX_LEN                     (40)
/** 協議版本號的最大長度 */
#define OES_VER_ID_MAX_LEN                  (32)
/** 系統支援的最大客戶端環境號數量 */
#define OES_MAX_CLIENT_ENVID_COUNT          (128)
/** 批量委託的每批次最大委託數量 */
#define OES_MAX_BATCH_ORDERS_COUNT          (500)

/** 客戶程式碼最大長度 */
#define OES_CUST_ID_MAX_LEN                 (16)
/** 客戶程式碼真實長度 */
#define OES_CUST_ID_REAL_LEN                (12)
/** 客戶名稱最大長度 */
#define OES_CUST_NAME_MAX_LEN               (64)

/** 資金賬戶程式碼最大長度 */
#define OES_CASH_ACCT_ID_MAX_LEN            (16)
/** 資金賬戶程式碼的實際長度 */
#define OES_CASH_ACCT_ID_REAL_LEN           (12)

/** 股東賬戶程式碼最大長度 */
#define OES_INV_ACCT_ID_MAX_LEN             (16)
/** 股東賬戶程式碼實際長度 */
#define OES_INV_ACCT_ID_REAL_LEN            (10)

/** 營業部程式碼最大長度 */
#define OES_BRANCH_ID_MAX_LEN               (8)
/** 營業部程式碼實際長度 */
#define OES_BRANCH_ID_REAL_LEN              (6)

/** 銀行程式碼最大長度 */
#define OES_BANK_NO_MAX_LEN                 (8)
/** 銀行程式碼實際使用長度 */
#define OES_BANK_NO_REAL_LEN                (4)

/** PBU域長度 */
#define OES_PBU_MAX_LEN                     (8)
/** PBU實際長度 */
#define OES_PBU_REAL_LEN                    (6)

/** 證券程式碼的最大長度 */
#define OES_SECURITY_ID_MAX_LEN             (16)
/** 實際的股票產品程式碼長度 */
#define OES_STOCK_ID_REAL_LEN               (6)
/** 實際的期權產品程式碼長度 */
#define OES_OPTION_ID_REAL_LEN              (8)

/** 市場描述字串最大長度 */
#define OES_MKT_DESC_STR_MAX_LEN            (32)

/** 產品名稱長度 */
#define OES_SECURITY_NAME_MAX_LEN           (24)
/** 產品名稱實際長度 */
#define OES_SECURITY_NAME_REAL_LEN          (20)

/** 產品關聯程式碼長度 */
#define OES_SECURITY_LINK_CODE_MAX_LEN      (16)
/** 產品關聯程式碼實際長度 */
#define OES_SECURITY_LINK_CODE_REAL_LEN     (8)

/** 交易所訂單編號的最大長度 */
#define OES_EXCH_ORDER_ID_MAX_LEN           (17)
/** 交易所訂單編號的實際長度 (上證) */
#define OES_EXCH_ORDER_ID_SSE_LEN           (8)
/** 交易所訂單編號的實際長度 (深證) */
#define OES_EXCH_ORDER_ID_SZSE_LEN          (16)

/** 點分十進位制的IPv4, 字串的最大長度 */
#define OES_MAX_IP_LEN                      (16)
/** MAC地址字串的最大長度 */
#define OES_MAX_MAC_LEN                     (20)
/** MAC地址字串的最大長度(按64位對齊的長度) */
#define OES_MAX_MAC_ALGIN_LEN               (24)
/** 裝置序列號字串的最大長度 */
#define OES_MAX_DRIVER_ID_LEN               (21)
/** 裝置序列號字串的最大長度(按64位對齊的長度) */
#define OES_MAX_DRIVER_ID_ALGIN_LEN         (24)

/** 測試請求識別符號的最大長度 */
#define OES_MAX_TEST_REQ_ID_LEN             (32)
/** 傳送時間欄位(YYYYMMDD-HH:mm:SS.sss (*C21))的最大長度 */
#define OES_MAX_SENDING_TIME_LEN            (22)
/** 傳送時間欄位(YYYYMMDD-HH:mm:SS.sss (*C21))的實際有效資料長度 */
#define OES_REAL_SENDING_TIME_LEN           (21)

/** 系統支援的最大許可權數量 */
#define OES_MAX_TRADING_PERMISSION_COUNT    (64)
/** 許可權說明(中文名稱)的最大長度 */
#define OES_MAX_PERMISSION_MEMO_LEN         (64)

/** 錯誤描述資訊長度 */
#define OES_MAX_ERROR_INFO_LEN              (64)

/** 主櫃調撥流水號資訊長度 */
#define OES_MAX_ALLOT_SERIALNO_LEN          (64)

/** 費用 (佣金/固定費用) 的費率單位 */
#define OES_FEE_RATE_UNIT                   (10000000)
/** ETF使用的資金百分比單位 */
#define OES_ETF_CASH_RATIO_UNIT             (100000)
/** 資金的轉換單位 */
#define OES_CASH_UNIT                       (10000)
/** 債券每百元應計利息的轉換單位 */
#define OES_BOND_INTEREST_UNIT              (100000000)
/** 期權保證金轉換單位 */
#define OES_MARGIN_UNIT                     (100)

/** 最大買賣價格, 委託價格不能等於或超過此價格 */
#define OES_MAX_BS_PRICE                    (10000 * OES_CASH_UNIT)

/** 出入金的金額單位 */
#define OES_FUND_TRSF_UNIT                  (100)

/** 期權看漲方向限額 */
#define OES_HOLD_LIMIT_QUOTA_UP             (500)
/** 期權看跌方向限額 */
#define OES_HOLD_LIMIT_QUOTA_DOWN           (500)
/* -------------------------           */


/* ===================================================================
 * 列舉型別定義 (1. 市場相關)
 * =================================================================== */

/**
 * 交易所程式碼定義
 */
typedef enum _eOesExchangeId {
    OES_EXCH_UNDEFINE                       = 0,        /**< 未定義的交易所程式碼 */
    OES_EXCH_SSE                            = 1,        /**< 上海證券交易所 */
    OES_EXCH_SZSE                           = 2,        /**< 深圳證券交易所 */
    __MAX_OES_EXCH,

    /** 上海證券交易所 @deprecated 已過時, 請使用 OES_EXCH_SSE */
    OES_EXCHANGE_TYPE_SSE                   = OES_EXCH_SSE,
    /** 深圳證券交易所 @deprecated 已過時, 請使用 OES_EXCH_SZSE */
    OES_EXCHANGE_TYPE_SZSE                  = OES_EXCH_SZSE,

    __OES_EXCH_ID_MAX_ALIGNED4              = 4,        /**< 交易所程式碼最大值 (按4位元組對齊的大小) */
    __OES_EXCH_ID_MAX_ALIGNED8              = 8         /**< 交易所程式碼最大值 (按8位元組對齊的大小) */
} eOesExchangeIdT;


/**
 * 市場型別定義
 */
typedef enum _eOesMarketId {
    OES_MKT_UNDEFINE                        = 0,        /**< 未定義的市場型別 */
    OES_MKT_SH_ASHARE                       = 1,        /**< 上海A股 */
    OES_MKT_SZ_ASHARE                       = 2,        /**< 深圳A股 */
    OES_MKT_SH_OPTION                       = 3,        /**< 上海期權 */
    __OES_MKT_ID_MAX,                                   /**< 市場型別最大值 */

    /** 未定義的市場型別 @deprecated 已過時, 請使用 OES_MKT_UNDEFINE  */
    OES_MKT_ID_UNDEFINE                     = OES_MKT_UNDEFINE,
    /** 上海A股 @deprecated 已過時, 請使用 OES_MKT_SH_ASHARE */
    OES_MKT_ID_SH_A                         = OES_MKT_SH_ASHARE,
    /** 深圳A股 @deprecated 已過時, 請使用 OES_MKT_SZ_ASHARE */
    OES_MKT_ID_SZ_A                         = OES_MKT_SZ_ASHARE,
    /** 上海期權 @deprecated 已過時, 請使用 OES_MKT_SH_OPTION */
    OES_MKT_ID_SH_OPT                       = OES_MKT_SH_OPTION,

    __OES_MKT_ID_MAX_ALIGNED4               = 4,        /**< 市場型別最大值 (按4位元組對齊的大小) */
    __OES_MKT_ID_MAX_ALIGNED8               = 8         /**< 市場型別最大值 (按8位元組對齊的大小) */
} eOesMarketIdT;


/**
 * 交易平臺型別定義
 */
typedef enum _eOesPlatformId {
    OES_PLATFORM_UNDEFINE                   = 0,        /**< 未定義的交易平臺型別 */
    OES_PLATFORM_CASH_AUCTION               = 1,        /**< 現貨集中競價交易平臺 */
    OES_PLATFORM_FINANCIAL_SERVICES         = 2,        /**< 綜合金融服務平臺 */
    OES_PLATFORM_NON_TRADE                  = 3,        /**< 非交易處理平臺 */
    OES_PLATFORM_DERIVATIVE_AUCTION         = 4,        /**< 衍生品集中競價交易平臺 */
    __OES_PLATFORM_ID_MAX,                              /**< 平臺號的最大值 */
    __OES_PLATFORM_ID_MAX_ALIGNED8          = 8         /**< 平臺號的最大值 (按8位元組對齊的大小) */
} eOesPlatformIdT;


/**
 * 市場狀態定義
 */
typedef enum _eOesMarketState {
    OES_MKT_STATE_UNDEFINE                  = 0,        /**< 未定義的市場狀態 */
    OES_MKT_STATE_PRE_OPEN                  = 1,        /**< 未開放 (PreOpen) */
    OES_MKT_STATE_OPEN_UP_COMING            = 2,        /**< 即將開放 (OpenUpComing) */
    OES_MKT_STATE_OPEN                      = 3,        /**< 開放 (Open) */
    OES_MKT_STATE_HALT                      = 4,        /**< 暫停開放 (Halt) */
    OES_MKT_STATE_CLOSE                     = 5,        /**< 關閉 (Close) */
    __OES_MKT_STATE_MAX                                 /**< 市場狀態最大值 */
} eOesMarketStateT;


/**
 * OES 競價時段定義
 */
typedef enum _eOesTrdSessType {
    OES_TRD_SESS_TYPE_O                     = 0,        /**< 開盤集合競價時段 */
    OES_TRD_SESS_TYPE_T                     = 1,        /**< 連續競價時段 */
    OES_TRD_SESS_TYPE_C                     = 2,        /**< 收盤集合競價 */
    __OES_TRD_SESS_TYPE_MAX                             /**< 時段型別最大值 (時段型別數量) */
} eOesTrdSessTypeT;
/* -------------------------           */


/* ===================================================================
 * 列舉型別定義 (2. 產品相關)
 * =================================================================== */

/**
 * 產品型別 (high-level category)
 */
typedef enum _eOesProductType {
    OES_PRODUCT_TYPE_UNDEFINE               = 0,        /**< 未定義的產品型別 */
    OES_PRODUCT_TYPE_EQUITY                 = 1,        /**< 普通股票/存託憑證/債券/基金/科創板 */
    OES_PRODUCT_TYPE_BOND_STD               = 2,        /**< 逆回購標準券 */
    OES_PRODUCT_TYPE_IPO                    = 3,        /**< 新股認購 */
    OES_PRODUCT_TYPE_ALLOTMENT              = 4,        /**< 配股認購 */
    OES_PRODUCT_TYPE_OPTION                 = 5,        /**< 期權 */

    __OES_PRODUCT_TYPE_MAX,                             /**< 產品型別最大值 */
} eOesProductTypeT;


/**
 * 證券類別
 */
typedef enum _eOesSecurityType {
    OES_SECURITY_TYPE_UNDEFINE              = 0,        /**< 未定義的證券型別 */
    OES_SECURITY_TYPE_STOCK                 = 1,        /**< 股票 */
    OES_SECURITY_TYPE_BOND                  = 2,        /**< 債券 */
    OES_SECURITY_TYPE_ETF                   = 3,        /**< ETF */
    OES_SECURITY_TYPE_FUND                  = 4,        /**< 基金 */
    OES_SECURITY_TYPE_OPTION                = 5,        /**< 期權 */
    __OES_SECURITY_TYPE_MAX,                            /**< 證券型別最大值 */

    __OES_SECURITY_TYPE_NOT_SUPPORT         = 100       /**< 不支援的證券類別 */
} eOesSecurityTypeT;


/**
 * 證券子類別
 */
typedef enum _eOesSubSecurityType {
    OES_SUB_SECURITY_TYPE_UNDEFINE          = 0,        /**< 未定義的證券子型別 */

    __OES_SUB_SECURITY_TYPE_STOCK_MIN       = 10,       /**< 股票類證券子型別最小值 */
    OES_SUB_SECURITY_TYPE_STOCK_ASH         = 11,       /**< A股股票, A Share */
    OES_SUB_SECURITY_TYPE_STOCK_SME         = 12,       /**< 中小板股票, Small & Medium Enterprise (SME) Board */
    OES_SUB_SECURITY_TYPE_STOCK_GEM         = 13,       /**< 創業板股票, Growth Enterprise Market (GEM) */
    OES_SUB_SECURITY_TYPE_STOCK_KSH         = 14,       /**< 科創板股票 */
    OES_SUB_SECURITY_TYPE_STOCK_KCDR        = 15,       /**< 科創板存託憑證 */
    OES_SUB_SECURITY_TYPE_STOCK_CDR         = 16,       /**< 存託憑證, Chinese Depository Receipt (CDR) */
    OES_SUB_SECURITY_TYPE_STOCK_HLTCDR      = 17,       /**< 滬倫通CDR本地交易業務產品 */
    __OES_SUB_SECURITY_TYPE_STOCK_MAX,                  /**< 股票類證券子型別最大值 */

    __OES_SUB_SECURITY_TYPE_BOND_MIN        = 20,       /**< 債券類證券子型別最小值 */
    OES_SUB_SECURITY_TYPE_BOND_GBF          = 21,       /**< 國債 */
    OES_SUB_SECURITY_TYPE_BOND_CBF          = 22,       /**< 企業債 */
    OES_SUB_SECURITY_TYPE_BOND_CPF          = 23,       /**< 公司債 */
    OES_SUB_SECURITY_TYPE_BOND_CCF          = 24,       /**< 可轉換債券 */
    OES_SUB_SECURITY_TYPE_BOND_FBF          = 25,       /**< 金融機構發行債券 */
    OES_SUB_SECURITY_TYPE_BOND_PRP          = 26,       /**< 債券質押式回購 */
    OES_SUB_SECURITY_TYPE_BOND_STD          = 27,       /**< 債券標準券 */
    __OES_SUB_SECURITY_TYPE_BOND_MAX,                   /**< 債券類證券子型別最大值 */

    __OES_SUB_SECURITY_TYPE_ETF_MIN         = 30,       /**< ETF類證券子型別最小值 */
    OES_SUB_SECURITY_TYPE_ETF_SINGLE_MKT    = 31,       /**< 單市場股票ETF */
    OES_SUB_SECURITY_TYPE_ETF_CROSS_MKT     = 32,       /**< 跨市場股票ETF */
    OES_SUB_SECURITY_TYPE_ETF_BOND          = 33,       /**< 實物債券ETF */
    OES_SUB_SECURITY_TYPE_ETF_CURRENCY      = 34,       /**< 貨幣ETF */
    OES_SUB_SECURITY_TYPE_ETF_CROSS_BORDER  = 35,       /**< 跨境ETF */
    OES_SUB_SECURITY_TYPE_ETF_GOLD          = 36,       /**< 黃金ETF */
    __OES_SUB_SECURITY_TYPE_ETF_MAX,                    /**< ETF類證券子型別最大值 */

    __OES_SUB_SECURITY_TYPE_FUND_MIN        = 40,       /**< 基金類證券子型別最小值 */
    OES_SUB_SECURITY_TYPE_FUND_LOF          = 41,       /**< LOF基金 */
    OES_SUB_SECURITY_TYPE_FUND_CEF          = 42,       /**< 封閉式基金, Close-end Fund */
    OES_SUB_SECURITY_TYPE_FUND_OEF          = 43,       /**< 開放式基金, Open-end Fund */
    OES_SUB_SECURITY_TYPE_FUND_GRADED       = 44,       /**< 分級子基金 */
    __OES_SUB_SECURITY_TYPE_FUND_MAX,                   /**< 基金類證券子型別最大值 */

    __OES_SUB_SECURITY_TYPE_OPTION_MIN      = 50,       /**< 期權類證券子型別最小值 */
    OES_SUB_SECURITY_TYPE_OPTION_ETF        = 51,       /**< ETF期權 */
    OES_SUB_SECURITY_TYPE_OPTION_STOCK      = 52,       /**< 個股期權 */
    __OES_SUB_SECURITY_TYPE_OPTION_MAX,                 /**< 期權類證券子型別最大值 */

    __OES_SUB_SECURITY_TYPE_MAX             = __OES_SUB_SECURITY_TYPE_OPTION_MAX
} eOesSubSecurityTypeT;


/**
 * 證券級別
 */
typedef enum _eOesSecurityLevel {
    OES_SECURITY_LEVEL_UNDEFINE             = 0,
    OES_SECURITY_LEVEL_N                    = 1,        /**< 正常證券 */
    OES_SECURITY_LEVEL_XST                  = 2,        /**< *ST股 */
    OES_SECURITY_LEVEL_ST                   = 3,        /**< ST股 */
    OES_SECURITY_LEVEL_P                    = 4,        /**< 退市整理證券 */
    OES_SECURITY_LEVEL_T                    = 5,        /**< 退市轉讓證券 */
    OES_SECURITY_LEVEL_U                    = 6,        /**< 優先股 */
    OES_SECURITY_LEVEL_B                    = 7,        /**< B級基金 */
    __OES_SECURITY_LEVEL_MAX
} eOesSecurityLevelT;


/**
 * 證券風險等級
 */
typedef enum _eOesSecurityRiskLevel {
    OES_RISK_LEVEL_VERY_LOW                 = 0,        /**< 最低風險 */
    OES_RISK_LEVEL_LOW                      = 1,        /**< 低風險 */
    OES_RISK_LEVEL_MEDIUM_LOW               = 2,        /**< 中低風險 */
    OES_RISK_LEVEL_MEDIUM                   = 3,        /**< 中風險 */
    OES_RISK_LEVEL_MEDIUM_HIGH              = 4,        /**< 中高風險 */
    OES_RISK_LEVEL_HIGH                     = 5,        /**< 高風險 */
    OES_RISK_LEVEL_VERY_HIGH                = 6,        /**< 極高風險 */
    __OES_RISK_LEVEL_MAX
} eOesSecurityRiskLevelT;


/**
 * 證券停復牌標識類別
 */
typedef enum _eOesSecuritySuspFlag {
    OES_SUSPFLAG_NONE                       = 0x0,      /**< 無停牌標識 */
    OES_SUSPFLAG_EXCHANGE                   = 0x1,      /**< 交易所連續停牌 */
    OES_SUSPFLAG_BROKER                     = 0x2,      /**< 券商人工停牌 */
    __OES_SUSPFLAG_OTHER
} eOesSecuritySuspFlagT;


/**
 * OES中籤、配號記錄型別
 */
typedef enum _eOesLotType {
    OES_LOT_TYPE_UNDEFINE                   = 0,        /**< 未定義的中籤、配號記錄型別 */
    OES_LOT_TYPE_FAILED                     = 1,        /**< 配號失敗記錄 */
    OES_LOT_TYPE_ASSIGNMENT                 = 2,        /**< 配號成功記錄 */
    OES_LOT_TYPE_LOTTERY                    = 3,        /**< 中籤記錄 */
    __OES_LOT_TYPE_MAX                                  /**< 中籤、配號記錄型別最大值 */
} eOesLotTypeT;


/**
 * OES配號失敗原因
 */
typedef enum _eOesLotRejReason {
    OES_LOT_REJ_REASON_DUPLICATE            = 1,        /**< 配號失敗-重複申購 */
    OES_LOT_REJ_REASON_INVALID_DUPLICATE    = 2,        /**< 配號失敗-違規重複 */
    OES_LOT_REJ_REASON_OFFLINE_FIRST        = 3,        /**< 配號失敗-網下在先 */
    OES_LOT_REJ_REASON_BAD_RECORD           = 4,        /**< 配號失敗-不良記錄 */
    OES_LOT_REJ_REASON_UNKNOW               = 5         /**< 配號失敗-未知原因 */
} eOesLotRejReasonT;
/* -------------------------           */


/* ===================================================================
 * 列舉型別定義 (3. 訂單相關)
 * =================================================================== */

/**
 * 訂單執行狀態定義
 */
typedef enum _eOesOrdStatus {
    OES_ORD_STATUS_UNDEFINE                 = 0,        /**< 未定義 */
    OES_ORD_STATUS_NEW                      = 1,        /**< 新訂單 */

    OES_ORD_STATUS_DECLARED                 = 2,        /**< 已確認 */
    OES_ORD_STATUS_PARTIALLY_FILLED         = 3,        /**< 部分成交 */

    __OES_ORD_STATUS_FINAL_MIN              = 4,        /**< 訂單終結狀態判斷標誌 */
    OES_ORD_STATUS_CANCEL_DONE              = 5,        /**< 撤單指令已執行 (適用於撤單請求, 並做為撤單請求的終結狀態) */
    OES_ORD_STATUS_PARTIALLY_CANCELED       = 6,        /**< 部分撤單 (部分成交, 剩餘撤單) */
    OES_ORD_STATUS_CANCELED                 = 7,        /**< 已撤單 */
    OES_ORD_STATUS_FILLED                   = 8,        /**< 已成交 (全部成交) */
    __OES_ORD_STATUS_VALID_MAX,

    __OES_ORD_STATUS_INVALID_MIN            = 10,       /**< 廢單判斷標誌 */
    OES_ORD_STATUS_INVALID_OES              = 11,       /**< OES內部廢單 */
    OES_ORD_STATUS_INVALID_SH_F             = 12,       /**< 上證後臺判斷該訂單為廢單 */
    OES_ORD_STATUS_INVALID_SH_E             = 13,       /**< 上證前臺判斷該訂單為廢單 */
    OES_ORD_STATUS_INVALID_SH_COMM          = 14,       /**< 通訊故障 */
    OES_ORD_STATUS_INVALID_SZ_F             = 15,       /**< 深證前臺廢單 */
    OES_ORD_STATUS_INVALID_SZ_E             = 16,       /**< 深證後臺廢單 */
    OES_ORD_STATUS_INVALID_SZ_REJECT        = 17,       /**< 深證業務拒絕 */
    OES_ORD_STATUS_INVALID_SZ_TRY_AGAIN     = 18,       /**< 深證平臺未開放(需嘗試重報) */
    __OES_ORD_STATUS_INVALID_MAX,

    /*
     * 以下訂單狀態定義已廢棄, 只是為了相容之前的版本而暫時保留
     */
    OES_ORD_STATUS_NORMAL                   = OES_ORD_STATUS_NEW,
    OES_ORD_STATUS_DECLARING                = OES_ORD_STATUS_NEW,
    __OES_ORD_STATUS_INVALID_OES            = OES_ORD_STATUS_INVALID_OES

} eOesOrdStatusT;


/**
 * 委託型別
 *
 * 部分縮寫解釋如下:
 *  - LMT (Limit)           : 限價
 *  - MTL (Market To Limit) : 剩餘轉限價(市價)
 *  - FAK (Fill and Kill)   : 剩餘轉撤銷(市價)
 *  - FOK (Fill or Kill)    : 全部成交或全部撤銷(市價/限價)
 *
 * 上海A股支援型別:
 *      1. OES_ORD_TYPE_LMT
 *      2. OES_ORD_TYPE_MTL_BEST_5
 *      3. OES_ORD_TYPE_FAK_BEST_5
 *
 * 上海期權支援市價型別:
 *      1. OES_ORD_TYPE_LMT
 *      2. OES_ORD_TYPE_LMT_FOK
 *      3. OES_ORD_TYPE_FOK
 *
 * 深圳A股支援市價型別:
 *      1. OES_ORD_TYPE_LMT
 *      2. OES_ORD_TYPE_MTL_BEST
 *      3. OES_ORD_TYPE_MTL_SAMEPARTY_BEST
 *      4. OES_ORD_TYPE_FAK_BEST_5
 *      5. OES_ORD_TYPE_FAK
 *      6. OES_ORD_TYPE_FOK
 */
typedef enum _eOesOrdType {
    OES_ORD_TYPE_LMT                        = 0,        /**< 限價 */
    OES_ORD_TYPE_LMT_FOK                    = 1,        /**< 限價FOK */
    __OES_ORD_TYPE_LMT_MAX,

    OES_ORD_TYPE_MTL_BEST_5                 = 10,       /**< 最優五檔即時成交剩餘轉限價 */
    OES_ORD_TYPE_MTL_BEST                   = 11,       /**< 對手方最優價格申報 */
    OES_ORD_TYPE_MTL_SAMEPARTY_BEST         = 12,       /**< 本方最優價格申報 */
    __OES_ORD_TYPE_MTL_MAX,

    OES_ORD_TYPE_FAK_BEST_5                 = 20,       /**< 最優五檔即時成交剩餘撤銷 */
    OES_ORD_TYPE_FAK                        = 21,       /**< 即時成交剩餘撤銷 */
    __OES_ORD_TYPE_FAK_MAX,

    OES_ORD_TYPE_FOK                        = 30,       /**< 市價全部成交或全部撤銷 */
    __OES_ORD_TYPE_FOK_MAX,
    __OES_ORD_TYPE_MAX,
    __OES_ORD_TYPE_MAX_ALIGNED              = 32        /**< 委託型別最大值 (按8位元組對齊的大小) */
} eOesOrdTypeT;


/**
 * 上證委託型別
 *
 * 部分縮寫解釋如下:
 *  - LMT (Limit)           : 限價
 *  - MTL (Market To Limit) : 剩餘轉限價(市價)
 *  - FAK (Fill and Kill)   : 剩餘轉撤銷(市價)
 *  - FOK (Fill or Kill)    : 全部成交或全部撤銷(市價/限價)
 */
typedef enum _eOesOrdTypeSh {
    /** 限價, 0 */
    OES_ORD_TYPE_SH_LMT                     = OES_ORD_TYPE_LMT,
    /** 限價FOK(僅適用於期權), 1 */
    OES_ORD_TYPE_SH_LMT_FOK                 = OES_ORD_TYPE_LMT_FOK,

    /** 最優五檔即時成交剩餘轉限價, 10 */
    OES_ORD_TYPE_SH_MTL_BEST_5              = OES_ORD_TYPE_MTL_BEST_5,
    /** 對手方最優價格申報(僅適用於科創板), 11 */
    OES_ORD_TYPE_SH_MTL_BEST                = OES_ORD_TYPE_MTL_BEST,
    /** 本方最優價格申報(僅適用於科創板), 12 */
    OES_ORD_TYPE_SH_MTL_SAMEPARTY_BEST      = OES_ORD_TYPE_MTL_SAMEPARTY_BEST,
    /** 最優五檔即時成交剩餘撤銷, 20 */
    OES_ORD_TYPE_SH_FAK_BEST_5              = OES_ORD_TYPE_FAK_BEST_5,
    /** 市價FOK(僅適用於期權), 30 */
    OES_ORD_TYPE_SH_FOK                     = OES_ORD_TYPE_FOK
} eOesOrdTypeShT;


/**
 * 深證委託型別
 *
 * 部分縮寫解釋如下:
 *  - LMT (Limit)           : 限價
 *  - MTL (Market To Limit) : 剩餘轉限價(市價)
 *  - FAK (Fill and Kill)   : 剩餘轉撤銷(市價)
 *  - FOK (Fill or Kill)    : 全部成交或全部撤銷(市價/限價)
 */
typedef enum _eOesOrdTypeSz {
    /** 限價, 0 */
    OES_ORD_TYPE_SZ_LMT                     = OES_ORD_TYPE_LMT,
    /** 限價全額成交或撤銷申報(僅適用於期權), 1 */
    OES_ORD_TYPE_SZ_LMT_FOK                 = OES_ORD_TYPE_LMT_FOK,

    /** 對手方最優價格申報, 11 */
    OES_ORD_TYPE_SZ_MTL_BEST                = OES_ORD_TYPE_MTL_BEST,
    /** 本方最優價格申報, 12 */
    OES_ORD_TYPE_SZ_MTL_SAMEPARTY_BEST      = OES_ORD_TYPE_MTL_SAMEPARTY_BEST,
    /** 最優五檔即時成交剩餘撤銷, 20 */
    OES_ORD_TYPE_SZ_FAK_BEST_5              = OES_ORD_TYPE_FAK_BEST_5,
    /** 即時成交剩餘撤銷申報, 21 */
    OES_ORD_TYPE_SZ_FAK                     = OES_ORD_TYPE_FAK,
    /** 市價全額成交或撤銷申報, 30 */
    OES_ORD_TYPE_SZ_FOK                     = OES_ORD_TYPE_FOK
} eOesOrdTypeSzT;


/**
 * 買賣型別
 */
typedef enum _eOesBuySellType {
    OES_BS_TYPE_UNDEFINE                    = 0,        /**< 未定義的買賣型別 */

    OES_BS_TYPE_BUY                         = 1,        /**< 買入 */
    OES_BS_TYPE_SELL                        = 2,        /**< 賣出 */
    OES_BS_TYPE_CREATION                    = 3,        /**< 申購 */
    OES_BS_TYPE_REDEMPTION                  = 4,        /**< 贖回 */
    OES_BS_TYPE_CREDIT_BUY                  = 5,        /**< 融資買入 */
    OES_BS_TYPE_CREDIT_SELL                 = 6,        /**< 融券賣出, 質押式逆回購 */
    OES_BS_TYPE_SUBSCRIPTION                = 7,        /**< 新股認購 */
    OES_BS_TYPE_ALLOTMENT                   = 8,        /**< 配股認購 */
    __OES_BS_TYPE_MAX_SPOT,                             /**< 現貨交易的買賣型別最大值 */
    /* -------------------------           */

    __OES_BS_TYPE_MIN_OPTION                = 10,       /**< 期權交易的買賣型別最小值 */
    OES_BS_TYPE_BUY_OPEN                    = 11,       /**< 期權買入開倉 */
    OES_BS_TYPE_BUY_CLOSE                   = 12,       /**< 期權買入平倉 */
    OES_BS_TYPE_SELL_OPEN                   = 13,       /**< 期權賣出開倉 */
    OES_BS_TYPE_SELL_CLOSE                  = 14,       /**< 期權賣出平倉 */
    OES_BS_TYPE_COVERED_OPEN                = 15,       /**< 期權備兌開倉 */
    OES_BS_TYPE_COVERED_CLOSE               = 16,       /**< 期權備兌平倉 */
    OES_BS_TYPE_OPTION_EXERCISE             = 17,       /**< 期權行權 */
    OES_BS_TYPE_UNDERLYING_FREEZE           = 18,       /**< 期權標的鎖定 */
    OES_BS_TYPE_UNDERLYING_UNFREEZE         = 19,       /**< 期權標的解鎖 */
    __OES_BS_TYPE_MAX_OPTION,                           /**< 期權交易的買賣型別最大值 */
    /* -------------------------           */

    OES_BS_TYPE_CANCEL                      = 30,       /**< 撤單 */
    __OES_BS_TYPE_MAX_TRADING,                          /**< 對外開放的交易類業務的買賣型別最大值 */
    /* -------------------------           */

    __OES_BS_TYPE_MIN_MGR                   = 40,       /**< 管理端非交易指令的買賣型別最小值 */
    OES_BS_TYPE_SSE_DESIGNATION             = 41,       /**< 指定登記 */
    OES_BS_TYPE_SSE_RECALL_DESIGNATION      = 42,       /**< 指定撤消 */
    OES_BS_TYPE_SZSE_DESIGNATION            = 43,       /**< 託管註冊 */
    OES_BS_TYPE_SZSE_CANCEL_DESIGNATION     = 44,       /**< 託管撤消 */
    __OES_BS_TYPE_MAX_MGR,                              /**< 管理端非交易指令的買賣型別最大值 */

    __OES_BS_TYPE_MAX                       = __OES_BS_TYPE_MAX_MGR,
    /* -------------------------           */

    /*
     * 以下買賣型別定義即將被廢棄
     */
    OES_BS_TYPE_B                           = OES_BS_TYPE_BUY,
    OES_BS_TYPE_S                           = OES_BS_TYPE_SELL,
    OES_BS_TYPE_KB                          = OES_BS_TYPE_CREATION,
    OES_BS_TYPE_KS                          = OES_BS_TYPE_REDEMPTION,
    OES_BS_TYPE_CB                          = OES_BS_TYPE_CREDIT_BUY,
    OES_BS_TYPE_CS                          = OES_BS_TYPE_CREDIT_SELL,

    OES_BS_TYPE_BO                          = OES_BS_TYPE_BUY_OPEN,
    OES_BS_TYPE_BC                          = OES_BS_TYPE_BUY_CLOSE,
    OES_BS_TYPE_SO                          = OES_BS_TYPE_SELL_OPEN,
    OES_BS_TYPE_SC                          = OES_BS_TYPE_SELL_CLOSE,
    OES_BS_TYPE_CO                          = OES_BS_TYPE_COVERED_OPEN,
    OES_BS_TYPE_CC                          = OES_BS_TYPE_COVERED_CLOSE,
    OES_BS_TYPE_TE                          = OES_BS_TYPE_OPTION_EXERCISE,
    OES_BS_TYPE_UF                          = OES_BS_TYPE_UNDERLYING_FREEZE,
    OES_BS_TYPE_UU                          = OES_BS_TYPE_UNDERLYING_UNFREEZE

} eOesBuySellTypeT;


/**
 * 訂單的買賣方向 (內部使用)
 */
typedef enum _eOesOrdDir {
    OES_ORD_DIR_BUY                         = 0,        /**< 買 */
    OES_ORD_DIR_SELL                        = 1,        /**< 賣 */
    __OES_ORD_DIR_MAX                                   /**< 買賣方向最大值 */
} eOesOrdDirT;


/**
 * ETF成交回報記錄的成交型別
 * 上證介面規範 (IS103_ETFInterface_CV14_20130123) 中規定如下:
 * - 二級市場記錄表示一筆申購/贖回交易連續記錄的開始,對一筆申購/贖回交易而言,有且只有一條;
 * - 一級市場記錄不再表示對應申購/贖回交易連續記錄的結束,對一筆申購/贖回交易而言,有且只有一條。
 */
typedef enum _eOesEtfTrdCnfmType {
    OES_ETF_TRDCNFM_TYPE_NONE               = 0,        /**< 無意義 */
    OES_ETF_TRDCNFM_TYPE_ETF_FIRST          = 1,        /**< 二級市場記錄 */
    OES_ETF_TRDCNFM_TYPE_CMPOENT            = 2,        /**< 成份股記錄 */
    OES_ETF_TRDCNFM_TYPE_CASH               = 3,        /**< 資金記錄 */
    OES_ETF_TRDCNFM_TYPE_ETF_LAST           = 4,        /**< 一級市場記錄 */
    __OES_ETF_TRDCNFM_TYPE_MAX                          /**< ETF成交型別的最大值 */
} eOesEtfTrdCnfmTypeT;


/**
 * ETF成分股現金替代標誌
 */
typedef enum _eOesEtfSubFlag {
    OES_ETF_SUBFLAG_FORBID_SUB              = 0,        /**< 禁止現金替代 (必須有證券) */
    OES_ETF_SUBFLAG_ALLOW_SUB               = 1,        /**< 可以進行現金替代(先用證券,
                                                             如證券不足可用現金替代) */
    OES_ETF_SUBFLAG_MUST_SUB                = 2,        /**< 必須用現金替代 */
    OES_ETF_SUBFLAG_SZ_REFUND_SUB           = 3,        /**< 該證券為深市證券, 退補現金替代 */
    OES_ETF_SUBFLAG_SZ_MUST_SUB             = 4,        /**< 該證券為深市證券, 必須現金替代 */
    OES_ETF_SUBFLAG_OTHER_REFUND_SUB        = 5,        /**< 非滬深市場成分證券退補現金替代 */
    OES_ETF_SUBFLAG_OTHER_MUST_SUB          = 6         /**< 非滬深市場成份證券必須現金替代 */
} eOesEtfSubFlagT;


/**
 * OES執行型別
 */
typedef enum _eOesExecType {
    OES_EXECTYPE_UNDEFINE                   = 0,        /**< 未定義的執行型別 */
    OES_EXECTYPE_INSERT                     = 1,        /**< 已接收 (OES已接收) */
    OES_EXECTYPE_CONFIRMED                  = 2,        /**< 已確認 (交易所已確認/出入金主櫃檯已確認) */
    OES_EXECTYPE_CANCELLED                  = 3,        /**< 已撤單 (原始委託的撤單完成回報) */
    OES_EXECTYPE_AUTO_CANCELLED             = 4,        /**< 自動撤單 (市價委託發生自動撤單後的委託回報) */
    OES_EXECTYPE_REJECT                     = 5,        /**< 拒絕 (OES拒絕/交易所廢單/出入金主櫃檯拒絕) */
    OES_EXECTYPE_TRADE                      = 6,        /**< 成交 (成交回報) */
    __OES_EXECTYPE_MAX                                  /**< 執行型別最大值 */
} eOesExecTypeT;
/* -------------------------           */


/* ===================================================================
 * 列舉型別定義 (4. 資金/費用/出入金相關)
 * =================================================================== */

/**
 * 貨幣型別
 */
typedef enum _eOesCurrType {
    OES_CURR_TYPE_RMB                       = 0,        /**< 人民幣 */
    OES_CURR_TYPE_HKD                       = 1,        /**< 港幣 */
    OES_CURR_TYPE_USD                       = 2,        /**< 美元 */
    __OES_CURR_TYPE_MAX                                 /**< 貨幣種類最大值 */
} eOesCurrTypeT;


/**
 * 費用識別符號
 */
typedef enum _eOesFeeType {
    OES_FEE_TYPE_EXCHANGE_STAMP             = 0x1,      /**< 交易所固定費用-印花稅 */
    OES_FEE_TYPE_EXCHANGE_TRANSFER          = 0x2,      /**< 交易所固定費用-過戶費 */
    OES_FEE_TYPE_EXCHANGE_SETTLEMENT        = 0x3,      /**< 交易所固定費用-結算費 */
    OES_FEE_TYPE_EXCHANGE_TRADE_RULE        = 0x4,      /**< 交易所固定費用-交易規費 */
    OES_FEE_TYPE_EXCHANGE_EXCHANGE          = 0x5,      /**< 交易所固定費用-經手費 */
    OES_FEE_TYPE_EXCHANGE_ADMINFER          = 0x6,      /**< 交易所固定費用-證管費 */
    OES_FEE_TYPE_EXCHANGE_OTHER             = 0x7,      /**< 交易所固定費用-其他費 */
    __OES_FEE_TYPE_EXCHANGE_MAX,                        /**< 交易所固定費用最大值 */

    OES_FEE_TYPE_BROKER_BACK_END            = 0x11      /**< 券商佣金-後臺費用 */
} eOesFeeTypeT;


/**
 * 費用 (佣金/固定費用) 計算模式
 */
typedef enum _eOesCalcFeeMode {
    OES_CALC_FEE_MODE_AMOUNT                = 0,        /**< 按金額 */
    OES_CALC_FEE_MODE_QTY                   = 1,        /**< 按份額 */
    OES_CALC_FEE_MODE_ORD                   = 2         /**< 按筆數 */
} eOesCalcFeeModeT;


/**
 * 出入金方向定義
 */
typedef enum _eOesFundTrsfDirect {
    OES_FUND_TRSF_DIRECT_IN                 = 0,        /**< 轉入OES (入金) */
    OES_FUND_TRSF_DIRECT_OUT                = 1         /**< 轉出OES (出金) */
} eOesFundTrsfDirectT;


/**
 * 出入金轉賬型別定義
 */
typedef enum _eOesFundTrsfType {
    OES_FUND_TRSF_TYPE_OES_BANK             = 0,        /**< OES和銀行之間轉賬 */
    OES_FUND_TRSF_TYPE_OES_COUNTER          = 1,        /**< OES和主櫃之間劃撥資金 */
    OES_FUND_TRSF_TYPE_COUNTER_BANK         = 2,        /**< 主櫃和銀行之間轉賬 */
    __OES_FUND_TRSF_TYPE_MAX                            /**< 出入金轉賬型別最大值 */
} eOesFundTrsfTypeT;


/**
 * 出入金委託狀態
 */
typedef enum _eOesFundTrsfStatus {
    OES_FUND_TRSF_STS_UNDECLARED            = 0,        /**< 尚未上報到主櫃 */
    OES_FUND_TRSF_STS_DECLARED              = 1,        /**< 已上報到主櫃 */
    OES_FUND_TRSF_STS_WAIT_DONE             = 2,        /**< 主櫃處理完成, 等待事務結束 */
    OES_FUND_TRSF_STS_DONE                  = 3,        /**< 出入金處理完成 */

    __OES_FUND_TRSF_STS_ROLLBACK_MIN        = 5,        /**< 廢單判斷標誌 */
    OES_FUND_TRSF_STS_UNDECLARED_ROLLBACK   = 6,        /**< 待回滾(未上報到主櫃前) */
    OES_FUND_TRSF_STS_DECLARED_ROLLBACK     = 7,        /**< 待回滾(已上報到主櫃後) */

    __OES_FUND_TRSF_STS_INVALID_MIN         = 10,       /**< 廢單判斷標誌 */
    OES_FUND_TRSF_STS_INVALID_OES           = 11,       /**< OES內部判斷為廢單 */
    OES_FUND_TRSF_STS_INVALID_COUNTER       = 12,       /**< 主櫃判斷為廢單 */
    OES_FUND_TRSF_STS_SUSPENDED             = 13        /**< 掛起狀態 (主櫃的出入金執行狀態未知, 待人工干預處理) */
} eOesFundTrsfStatusT;


/* ===================================================================
 * 列舉型別定義 (5. 投資人/賬戶/許可權相關)
 * =================================================================== */

/**
 * 賬戶類別定義
 * 資金賬戶類別與證券賬戶類別定義相同
 */
typedef enum _eOesAcctType {
    OES_ACCT_TYPE_NORMAL                    = 0,        /**< 普通賬戶 */
    OES_ACCT_TYPE_CREDIT                    = 1,        /**< 信用賬戶 */
    OES_ACCT_TYPE_OPTION                    = 2,        /**< 衍生品賬戶 */
    __OES_ACCT_TYPE_MAX                                 /**< 賬戶類別最大值 */
} eOesAcctTypeT;


/**
 * 資金型別定義
 * @see eOesAcctTypeT
 */
typedef enum _eOesCashType {
    /** 普通賬戶資金/現貨資金 */
    OES_CASH_TYPE_SPOT                      = OES_ACCT_TYPE_NORMAL,
    /** 信用賬戶資金/信用資金 */
    OES_CASH_TYPE_CREDIT                    = OES_ACCT_TYPE_CREDIT,
    /** 衍生品賬戶資金/期權保證金 */
    OES_CASH_TYPE_OPTION                    = OES_ACCT_TYPE_OPTION,
    /** 資金型別最大值 */
    __OES_CASH_TYPE_MAX                     = __OES_ACCT_TYPE_MAX,

    /** 相容性定義, 即將廢棄 */
    OES_CASH_TYPE_CRE                       = OES_CASH_TYPE_CREDIT,
    OES_CASH_TYPE_OPT                       = OES_CASH_TYPE_OPTION,
} eOesCashTypeT;


/**
 * 客戶狀態/證券帳戶/資金賬戶狀態
 */
typedef enum _eOesAcctStatus {
    OES_ACCT_STATUS_NORMAL                  = 0,        /**< 正常 */
    OES_ACCT_STATUS_DISABLED                = 1,        /**< 非正常 */
    OES_ACCT_STATUS_LOCKED                  = 2         /**< 已鎖定 */
} eOesAcctStatusT;


/**
 * 交易許可權的列舉值定義
 */
typedef enum _eOesTradingPermission {
    OES_PERMIS_MARKET_ORDER                 = (1 << 1),     /**< 市價委託 */
    OES_PERMIS_STRUCTURED_FUND              = (1 << 2),     /**< 分級基金適當性 */
    OES_PERMIS_BOND_QUALIFIED_INVESTOR      = (1 << 3),     /**< 債券合格投資者 */
    OES_PERMIS_XXX4                         = (1 << 4),     /**< 融資行權 */

    OES_PERMIS_DELISTING                    = (1 << 5),     /**< 退市整理股票 */
    OES_PERMIS_RISK_WARNING                 = (1 << 6),     /**< 風險警示股票 */

    OES_PERMIS_SINGLE_MARKET_ETF            = (1 << 7),     /**< 單市場ETF申贖 */
    OES_PERMIS_CROSS_BORDER_ETF             = (1 << 8),     /**< 跨境ETF申贖 */
    OES_PERMIS_CROSS_MARKET_ETF             = (1 << 9),     /**< 跨市場ETF申贖 */
    OES_PERMIS_CURRENCY_ETF                 = (1 << 10),    /**< 貨幣基金申贖 */

    OES_PERMIS_STOCK_PLEDGE_REPURCHASE      = (1 << 11),    /**< 股票質押式回購 */
    OES_PERMIS_PLEDGE_REPURCHASE            = (1 << 12),    /**< 質押回購 */

    OES_PERMIS_GEM                          = (1 << 13),    /**< 創業板交易 */
    OES_PERMIS_SH_HK_STOCK_CONNECT          = (1 << 14),    /**< 滬港通 */
    OES_PERMIS_SZ_HK_STOCK_CONNECT          = (1 << 15),    /**< 深港通 */

    OES_PERMIS_HLTCDR                       = (1 << 16),    /**< 滬倫通存託憑證 */
    OES_PERMIS_CDR                          = (1 << 17),    /**< 存託憑證 */
    OES_PERMIS_INNOVATION                   = (1 << 18),    /**< 創新企業股票 */
    OES_PERMIS_KSH                          = (1 << 19),    /**< 科創板交易 */

    __OES_PERMIS_ALL                        = 0xFFFFFFFF    /**< 全部許可權 */
} eOesTradingPermissionT;


/**
 * 交易限制的列舉值定義
 */
typedef enum _eOesTradingLimit {
    OES_LIMIT_BUY                           = (1 << 1),     /**< 禁止買入 */
    OES_LIMIT_SELL                          = (1 << 2),     /**< 禁止賣出 */
    OES_LIMIT_RECALL_DESIGNATION            = (1 << 3),     /**< 禁撤銷指定 */
    OES_LIMIT_DESIGNATION                   = (1 << 4),     /**< 禁止轉託管 */

    OES_LIMIT_REPO                          = (1 << 5),     /**< 禁止回購融資 */
    OES_LIMIT_REVERSE_REPO                  = (1 << 6),     /**< 禁止回購融券 */
    OES_LIMIT_SUBSCRIPTION                  = (1 << 7),     /**< 禁止普通申購 (新股認購) */
    OES_LIMIT_CREDIT_BUY                    = (1 << 8),     /**< 禁止融資買入 */
    OES_LIMIT_CREDIT_SELL                   = (1 << 9),     /**< 禁止融券賣出 */

    __OES_LIMIT_ALL                         = 0xFFFFFFFF    /**< 全部限制 */
} eOesTradingLimitT;


/**
 * 投資者適當性管理分類
 */
typedef enum _eOesQualificationClass {
    OES_QUALIFICATION_PUBLIC_INVESTOR           = 0,        /**< 公眾投資者 */
    OES_QUALIFICATION_QUALIFIED_INVESTOR        = 1,        /**< 合格投資者(個人投資者) */
    OES_QUALIFICATION_QUALIFIED_INSTITUTIONAL   = 2         /**< 合格投資者(機構投資者) */
} eOesQualificationClassT;


/**
 * 投資者分類
 *
 * A類專業投資者: 滿足《證券期貨投資者適當性管理辦法》第八條 (一)、 (二)、 (三) 點,
 *      比如證券公司、期貨公司、基金管理公司、商業銀行、保險公司、發行的理財產品等
 * B類專業投資者: 滿足《證券期貨投資者適當性管理辦法》第八條 (四)、 (五) 點,
 *      可以是法人或者其他組織、自然人, 滿足一定的淨資產和金融資產的要求, 具有相關的投資經驗
 * C類專業投資者: 滿足《證券期貨投資者適當性管理辦法》第十一條 (一)、 (二) 點,
 *      由普通投資者主動申請轉化而來, 滿足一定的淨資產和金融資產的要求, 具有相關的投資經驗
 */
typedef enum _eOesInvestorClass {
    OES_INVESTOR_CLASS_NORMAL               = 0,        /**< 普通投資者 */
    OES_INVESTOR_CLASS_PROFESSIONAL_A       = 1,        /**< A類專業投資者 */
    OES_INVESTOR_CLASS_PROFESSIONAL_B       = 2,        /**< B類專業投資者 */
    OES_INVESTOR_CLASS_PROFESSIONAL_C       = 3         /**< C類專業投資者 */
} eOesInvestorClassT;


/**
 * 客戶型別定義
 */
typedef enum _eOesCustType {
    OES_CUST_TYPE_PERSONAL                  = 0,        /**< 個人 */
    OES_CUST_TYPE_INSTITUTION               = 1,        /**< 機構 */
    OES_CUST_TYPE_PROPRIETARY               = 2,        /**< 自營 */
    OES_CUST_TYPE_PRODUCT                   = 3,        /**< 產品 */
    OES_CUST_TYPE_MKT_MAKER                 = 4,        /**< 做市商 */
    OES_CUST_TYPE_OTHERS                    = 5,        /**< 其他 */
    __OES_CUST_TYPE_MAX                                 /**< 客戶型別的最大值 */
} eOesCustTypeT;


/**
 * 所有者型別 (內部使用)
 */
typedef enum _eOesOwnerType {
    OES_OWNER_TYPE_PERSONAL                 = 1,        /**< 個人投資者 */
    OES_OWNER_TYPE_EXCHANGE                 = 101,      /**< 交易所 */
    OES_OWNER_TYPE_MEMBER                   = 102,      /**< 會員 */
    OES_OWNER_TYPE_INSTITUTION              = 103,      /**< 機構投資者 */
    OES_OWNER_TYPE_PROPRIETARY              = 104,      /**< 自營 */
    OES_OWNER_TYPE_MKT_MAKER                = 105,      /**< 做市商 */
    OES_OWNER_TYPE_SETTLEMENT               = 106,      /**< 結算結構 */
    __OES_OWNER_TYPE_MAX                                /**< 所有者型別的最大值 */
} eOesOwnerTypeT;


/**
 * 客戶端型別定義 (內部使用)
 */
typedef enum _eOesClientType {
    OES_CLIENT_TYPE_UNDEFINED               = 0,        /**< 客戶端型別-未定義 */
    OES_CLIENT_TYPE_INVESTOR                = 1,        /**< 普通投資人 */
    OES_CLIENT_TYPE_VIRTUAL                 = 2         /**< 虛擬賬戶 (僅開通行情, 不可交易) */
} eOesClientTypeT;


/**
 * 客戶端狀態定義 (內部使用)
 */
typedef enum _eOesClientStatus {
    OES_CLIENT_STATUS_UNACTIVATED           = 0,        /**< 未啟用 (不載入) */
    OES_CLIENT_STATUS_ACTIVATED             = 1,        /**< 已啟用 (正常載入) */
    OES_CLIENT_STATUS_PAUSE                 = 2,        /**< 已暫停 (正常載入, 不可交易) */
    OES_CLIENT_STATUS_SUSPENDED             = 3,        /**< 已掛起 (正常載入, 不可交易、不可出入金) */
    OES_CLIENT_STATUS_CANCELLED             = 4         /**< 已登出 (不載入) */
} eOesClientStatusT;
/* -------------------------           */


/* ===================================================================
 * 列舉型別定義 (6. 期權相關)
 * =================================================================== */

/**
 * 期權合約型別
 */
typedef enum _eOesOptContractType {
    OES_OPT_CONTRACT_TYPE_CALL              = 0,        /**< 認購 */
    OES_OPT_CONTRACT_TYPE_PUT               = 1,        /**< 認沽 */
    __OES_OPT_CONTRACT_TYPE_MAX                         /**< 合約型別最大值 */
} eOesOptContractTypeT;


/**
 * 權利類別
 */
typedef enum _eOesOptInvLevel {
    OES_OPT_INV_LEVEL_B                     = 0,        /**< 期權一級權利 */
    OES_OPT_INV_LEVEL_L                     = 1,        /**< 期權二級權利 */
    OES_OPT_INV_LEVEL_A                     = 2,        /**< 期權三級權利 */
    __OES_OPT_INV_LEVEL_MAX                             /**< 期權投資人級別最大值 */
} eOesOptInvLevelT;


/**
 * 期權產品開倉型別
 */
typedef enum _eOpenFlagType {
    OPEN_FLAG_TYPE_ALLOW                    = 0,        /**< 允許 */
    OPEN_FLAG_TYPE_FORBID                   = 1,        /**< 禁止 */
    __OPEN_FLAG_TYPE_MAX                                /**< 合約型別最大值 */
} eOpenFlagTypeT;


/**
 * 開倉標識
 */
typedef enum _eOesOptionOpenFlag {
    OES_OPTION_OPEN_FLAG_ALLOW              = 0,        /**< 允許開倉 */
    OES_OPTION_OPEN_FLAG_FORBID             = 1         /**< 禁止開倉 */
} eOesOptionOpenFlagT;


/**
 * 倉位影響
 */
typedef enum _eOesPositionEff {
    OES_POSITION_INVALID                    = 0,        /**< 無效值 */
    OES_POSITION_OPEN                       = 1,        /**< 開倉 */
    OES_POSITION_CLOSE                      = 2         /**< 平倉 */
} eOesPositionEffT;


/**
 * 期權行權型別
 */
typedef enum _eOesOptionType {
    OES_OPTION_TYPE_E                       = 0,        /**< 歐式 */
    OES_OPTION_TYPE_A                       = 1,        /**< 美式 */
    __OES_OPTION_TYPE_MAX                               /**< 行權型別最大值 */
} eOesOptionTypeT;
/* -------------------------           */


/* ===================================================================
 * 委託資訊的結構體定義
 * =================================================================== */

/**
 * 委託資訊的基礎內容定義
 */
#define __OES_ORD_BASE_INFO_PKT                         \
        /** 客戶委託流水號 (由客戶端維護的遞增流水, 用於識別重複的委託申報) */ \
        int32           clSeqNo; \
        /** 市場程式碼 @see eOesMarketIdT */ \
        uint8           mktId; \
        /** 訂單型別 @see eOesOrdTypeShT eOesOrdTypeSzT */ \
        uint8           ordType; \
        /** 買賣型別 @see eOesBuySellTypeT */ \
        uint8           bsType; \
        /** 按64位對齊的填充域 */ \
        uint8           __ORD_BASE_INFO_filler; \
        \
        /** 證券賬戶 */ \
        char            invAcctId[OES_INV_ACCT_ID_MAX_LEN]; \
        /** 證券程式碼 */ \
        char            securityId[OES_SECURITY_ID_MAX_LEN]; \
        \
        /** 委託數量 */ \
        int32           ordQty; \
        /** 委託價格, 單位精確到元后四位, 即1元 = 10000 */ \
        int32           ordPrice; \
        /** 原始訂單(待撤銷的訂單)的客戶訂單編號 */ \
        int64           origClOrdId; \
        \
        /** 使用者私有資訊 (由客戶端自定義填充, 並在回報資料中原樣返回) */ \
        union { \
            uint64      u64;                /**< uint64 型別的使用者私有資訊 */ \
            int64       i64;                /**< int64 型別的使用者私有資訊 */ \
            uint32      u32[2];             /**< uint32[2] 型別的使用者私有資訊 */ \
            int32       i32[2];             /**< int32[2] 型別的使用者私有資訊 */ \
            char        c8[8];              /**< char[8] 型別的使用者私有資訊 */ \
        } userInfo


/* 結構體的初始化值定義 */
#define __NULLOBJ_OES_ORD_BASE_INFO_PKT                 \
        0, 0, 0, 0, 0, \
        {0}, {0}, \
        0, 0, 0, \
        {0}
/* -------------------------           */


/**
 * 撤單請求的基礎內容定義
 */
#define __OES_ORD_CANCEL_BASE_INFO_PKT                  \
        /** 客戶委託流水號 (由客戶端維護的遞增流水, 用於識別重複的委託申報, 必填) */ \
        int32           clSeqNo; \
        /** 市場程式碼 (必填) @see eOesMarketIdT */ \
        uint8           mktId; \
        /** 按64位對齊的填充域 */ \
        uint8           __ORD_CANCEL_BASE_INFO_filler1[3]; \
        \
        /** 證券賬戶 (選填, 若不為空則校驗待撤訂單是否匹配) */ \
        char            invAcctId[OES_INV_ACCT_ID_MAX_LEN]; \
        /** 證券程式碼 (選填, 若不為空則校驗待撤訂單是否匹配) */ \
        char            securityId[OES_SECURITY_ID_MAX_LEN]; \
        \
        /** 原始訂單(待撤銷的訂單)的客戶委託流水號 (若使用 origClOrdId, 則不必填充該欄位) */ \
        int32           origClSeqNo; \
        /** 原始訂單(待撤銷的訂單)的客戶端環境號 (小於等於0, 則使用當前會話的 clEnvId) */ \
        int8            origClEnvId; \
        /** 按64位對齊的填充域 */ \
        uint8           __ORD_CANCEL_BASE_INFO_filler2[3]; \
        /** 原始訂單(待撤銷的訂單)的客戶訂單編號 (若使用 origClSeqNo, 則不必填充該欄位) */ \
        int64           origClOrdId; \
        \
        /** 使用者私有資訊 (由客戶端自定義填充, 並在回報資料中原樣返回) */ \
        union { \
            uint64      u64;                /**< uint64 型別的使用者私有資訊 */ \
            int64       i64;                /**< int64 型別的使用者私有資訊 */ \
            uint32      u32[2];             /**< uint32[2] 型別的使用者私有資訊 */ \
            int32       i32[2];             /**< int32[2] 型別的使用者私有資訊 */ \
            char        c8[8];              /**< char[8] 型別的使用者私有資訊 */ \
        } userInfo


/* 結構體的初始化值定義 */
#define __NULLOBJ_OES_ORD_CANCEL_BASE_INFO_PKT          \
        0, 0, {0}, \
        {0}, {0}, \
        0, 0, {0}, 0, \
        {0}
/* -------------------------           */


/**
 * 附加到請求訊息末尾的, 用於延遲測量的打點資訊欄位 (是否啟用取決於構建配置)
 */
#define __OES_ORD_REQ_LATENCY_FIELDS_IMPL               \
        /** 委託請求的客戶端原始傳送時間 (OES內部使用, 由API在傳送時自動填充) */ \
        STimeval32T     __ordReqOrigSendTime


/* 結構體的初始化值定義 */
#define __NULLOBJ_OES_ORD_REQ_LATENCY_FIELDS_IMPL       \
        {0, 0}
/* -------------------------           */


/**
 * 附加到回報訊息末尾的, 用於延遲測量的打點資訊欄位 (是否啟用取決於構建配置)
 */
#define __OES_ORD_CNFM_LATENCY_FIELDS_IMPL              \
        /** 委託請求的初始接收時間 */ \
        STimeval32T     __ordReqOrigRecvTime; \
        /** 委託請求的入隊時間 */ \
        STimeval32T     __ordReqCollectedTime; \
        /** 委託請求的實際處理開始時間 */ \
        STimeval32T     __ordReqActualDealTime; \
        /** 委託請求的處理完成時間 */ \
        STimeval32T     __ordReqProcessedTime; \
        \
        /** 委託確認的開始採集時間 */ \
        STimeval32T     __ordCnfmOrigRecvTime; \
        /** 委託確認的採集完成時間 */ \
        STimeval32T     __ordCnfmCollectedTime; \
        /** 委託確認的實際處理開始時間 */ \
        STimeval32T     __ordCnfmActualDealTime; \
        /** 委託確認的處理完成時間 */ \
        STimeval32T     __ordCnfmProcessedTime; \
        \
        /** 初始報盤時間 */ \
        STimeval32T     __ordDeclareTime; \
        /** 報盤完成時間 */ \
        STimeval32T     __ordDeclareDoneTime; \
        \
        /** 訊息推送時間 (寫入推送快取以後, 實際網路傳送之前) */ \
        STimeval32T     __pushingTime


/* 結構體的初始化值定義 */
#define __NULLOBJ_OES_ORD_CNFM_LATENCY_FIELDS_IMPL      \
        {0, 0}, {0, 0}, {0, 0}, {0, 0}, \
        {0, 0}, {0, 0}, {0, 0}, {0, 0}, \
        {0, 0}, {0, 0}, \
        {0, 0}
/* -------------------------           */


#if defined (_OES_EXPORT_LATENCY_STATS)

/**
 * 委託請求中的時間戳欄位定義 (用於記錄打點資訊以統計延遲)
 */
#   define  __OES_ORD_REQ_LATENCY_FIELDS                \
            ; \
            __OES_ORD_REQ_LATENCY_FIELDS_IMPL


/**
 * 委託回報中的時間戳欄位定義 (用於記錄打點資訊以統計延遲)
 */
#   define  __OES_ORD_CNFM_LATENCY_FIELDS               \
            ; \
            __OES_ORD_CNFM_LATENCY_FIELDS_IMPL


/* 結構體的初始化值定義 */
#   define  __NULLOBJ_OES_ORD_REQ_LATENCY_FIELDS        \
            , \
            __NULLOBJ_OES_ORD_REQ_LATENCY_FIELDS_IMPL

#   define  __NULLOBJ_OES_ORD_CNFM_LATENCY_FIELDS       \
            , \
            __NULLOBJ_OES_ORD_CNFM_LATENCY_FIELDS_IMPL

#else

#   define  __OES_ORD_REQ_LATENCY_FIELDS
#   define  __OES_ORD_CNFM_LATENCY_FIELDS

#   define  __NULLOBJ_OES_ORD_REQ_LATENCY_FIELDS
#   define  __NULLOBJ_OES_ORD_CNFM_LATENCY_FIELDS

#endif  /* _OES_EXPORT_LATENCY_STATS */
/* -------------------------           */


/**
 * 委託確認基礎資訊的內容定義
 */
#define __OES_ORD_CNFM_BASE_INFO_PKT                    \
        __OES_ORD_BASE_INFO_PKT \
        __OES_ORD_REQ_LATENCY_FIELDS; \
        \
        /** 客戶訂單編號 (在OES內具有唯一性的內部委託編號) */ \
        int64           clOrdId; \
        /** 客戶端編號 */ \
        int16           clientId; \
        /** 客戶端環境號 */ \
        int8            clEnvId; \
        /** 原始訂單(待撤銷的訂單)的客戶端環境號 (僅適用於撤單委託) */ \
        int8            origClEnvId; \
        /** 原始訂單(待撤銷的訂單)的客戶委託流水號 (僅適用於撤單委託) */ \
        int32           origClSeqNo; \
        \
        /** 委託日期 (格式為 YYYYMMDD, 形如 20160830) */ \
        int32           ordDate; \
        /** 委託時間 (格式為 HHMMSSsss, 形如 141205000) */ \
        int32           ordTime; \
        /** 委託確認時間 (格式為 HHMMSSsss, 形如 141206000) */ \
        int32           ordCnfmTime; \
        \
        /** 訂單當前狀態 @see eOesOrdStatusT */ \
        uint8           ordStatus; \
        /** 委託確認狀態 (交易所返回的回報狀態，僅供參考)  @see eOesOrdStatusT */ \
        uint8           ordCnfmSts; \
        /** 證券型別 @see eOesSecurityTypeT */ \
        uint8           securityType; \
        /** 證券子型別 @see eOesSubSecurityTypeT */ \
        uint8           subSecurityType; \
        \
        /** 平臺號 (OES內部使用) @see eOesPlatformIdT */ \
        uint8           __platformId; \
        /** 交易閘道器組序號 (OES內部使用) */ \
        uint8           __tgwGrpNo; \
        /** 交易閘道器平臺分割槽號 (OES內部使用) */ \
        uint8           __tgwPartitionNo; \
        /** 產品型別 @see eOesProductTypeT */ \
        uint8           productType; \
        /** 交易所訂單編號 (深交所的訂單編號是16位的非數字字串) */ \
        char            exchOrdId[OES_EXCH_ORDER_ID_MAX_LEN]; \
        /** 已報盤標誌 (OES內部使用) */ \
        uint8           __declareFlag; \
        /** 按64位對齊填充域 */ \
        uint8           __ORD_CNFM_BASE_INFO_filler[2]; \
        \
        /** 委託當前凍結的交易金額 */ \
        int64           frzAmt; \
        /** 委託當前凍結的利息 */ \
        int64           frzInterest; \
        /** 委託當前凍結的交易費用 */ \
        int64           frzFee; \
        /** 委託累計已發生的交易金額 */ \
        int64           cumAmt; \
        /** 委託累計已發生的利息 */ \
        int64           cumInterest; \
        /** 委託累計已發生的交易費用 */ \
        int64           cumFee; \
        \
        /** 累計執行數量 (累計成交數量) */ \
        int32           cumQty; \
        /** 已撤單數量 */ \
        int32           canceledQty; \
        \
        /** 訂單/撤單拒絕原因 */ \
        int32           ordRejReason; \
        /** 交易所錯誤碼 */ \
        int32           exchErrCode; \
        /** PBU程式碼 (席位號) */ \
        int32           pbuId; \
        /** 營業部程式碼 */ \
        int32           branchId; \
        /** 回報記錄號 (OES內部使用) */ \
        int32           __rowNum; \
        /** OIW委託編號 (OES內部使用) */ \
        uint32          __recNum \
        \
        __OES_ORD_CNFM_LATENCY_FIELDS


/* 結構體的初始化值定義 */
#define __NULLOBJ_OES_ORD_CNFM_BASE_INFO_PKT            \
        __NULLOBJ_OES_ORD_BASE_INFO_PKT \
        __NULLOBJ_OES_ORD_REQ_LATENCY_FIELDS, \
        0, 0, 0, 0, 0, \
        0, 0, 0, \
        0, 0, 0, 0, \
        0, 0, 0, 0, {0}, 0, {0}, \
        0, 0, 0, 0, 0, 0, \
        0, 0, \
        0, 0, 0, 0, 0, 0 \
        __NULLOBJ_OES_ORD_CNFM_LATENCY_FIELDS
/* -------------------------           */


/**
 * 委託請求的結構體定義
 */
typedef struct _OesOrdReq {
    __OES_ORD_BASE_INFO_PKT
    __OES_ORD_REQ_LATENCY_FIELDS;
} OesOrdReqT;


/* 結構體的初始化值定義 */
#define NULLOBJ_OES_ORD_REQ                             \
        __NULLOBJ_OES_ORD_BASE_INFO_PKT \
        __NULLOBJ_OES_ORD_REQ_LATENCY_FIELDS
/* -------------------------           */


/**
 * 撤單請求的結構體定義
 */
typedef struct _OesOrdCancelReq {
    __OES_ORD_CANCEL_BASE_INFO_PKT
    __OES_ORD_REQ_LATENCY_FIELDS;
} OesOrdCancelReqT;


/* 結構體的初始化值定義 */
#define NULLOBJ_OES_ORD_CANCEL_REQ                      \
        __NULLOBJ_OES_ORD_CANCEL_BASE_INFO_PKT \
        __NULLOBJ_OES_ORD_REQ_LATENCY_FIELDS
/* -------------------------           */


/**
 * 委託拒絕(OES業務拒絕)的結構體定義
 */
typedef struct _OesOrdReject {
    __OES_ORD_BASE_INFO_PKT
    __OES_ORD_REQ_LATENCY_FIELDS;

    /** 原始訂單(待撤銷的訂單)的客戶委託流水號 (僅適用於撤單請求) */
    int32               origClSeqNo;
    /** 原始訂單(待撤銷的訂單)的客戶端環境號 (僅適用於撤單請求) */
    int8                origClEnvId;
    /** 客戶端環境號 */
    int8                clEnvId;
    /** 客戶端編號 */
    int16               clientId;

    /** 委託日期 (格式為 YYYYMMDD, 形如 20160830) */
    int32               ordDate;
    /** 委託時間 (格式為 HHMMSSsss, 形如 141205000) */
    int32               ordTime;

    /** 訂單拒絕原因 */
    int32               ordRejReason;
    /** 按64位對齊的填充域 */
    int32               __filler;
} OesOrdRejectT;


/* 結構體的初始化值定義 */
#define NULLOBJ_OES_ORD_REJECT                          \
        __NULLOBJ_OES_ORD_BASE_INFO_PKT \
        __NULLOBJ_OES_ORD_REQ_LATENCY_FIELDS, \
        0, 0, 0, 0, \
        0, 0, \
        0, 0
/* -------------------------           */


/**
 * 委託確認的結構體定義
 */
typedef struct _OesOrdCnfm {
    __OES_ORD_CNFM_BASE_INFO_PKT;
} OesOrdCnfmT;


/* 結構體的初始化值定義 */
#define NULLOBJ_OES_ORD_CNFM                            \
        __NULLOBJ_OES_ORD_CNFM_BASE_INFO_PKT
/* -------------------------           */


/* ===================================================================
 * 成交基礎資訊的結構體定義
 * =================================================================== */

/**
 * 成交基礎資訊的內容定義
 */
#define __OES_TRD_BASE_INFO_PKT                         \
        /** 交易所成交編號 (以下的6個欄位是成交資訊的聯合索引欄位) */ \
        int64           exchTrdNum; \
        /** 市場程式碼 @see eOesMarketIdT */ \
        uint8           mktId; \
        /** 買賣型別 (取值範圍: 買/賣, 申購/贖回(僅深圳)) @see eOesBuySellTypeT */ \
        uint8           trdSide; \
        /** 平臺號 (OES內部使用) @see eOesPlatformIdT */ \
        uint8           __platformId; \
        /** 成交型別 (OES內部使用) @see eOesEtfTrdCnfmTypeT */ \
        uint8           __trdCnfmType; \
        /** ETF成交回報順序號 (OES內部使用), 為區分ETF成交記錄而設定 (以訂單為單位) */ \
        uint32          __etfTrdCnfmSeq; \
        \
        /** 股東賬戶程式碼 */ \
        char            invAcctId[OES_INV_ACCT_ID_MAX_LEN]; \
        /** 產品程式碼 */ \
        char            securityId[OES_SECURITY_ID_MAX_LEN]; \
        \
        /** 成交日期 (格式為 YYYYMMDD, 形如 20160830) */ \
        int32           trdDate; \
        /** 成交時間 (格式為 HHMMSSsss, 形如 141205000) */ \
        int32           trdTime; \
        /** 成交數量 */ \
        int32           trdQty; \
        /** 成交價格 (單位精確到元后四位, 即: 1元=10000) */ \
        int32           trdPrice; \
        /** 成交金額 (單位精確到元后四位, 即: 1元=10000) */ \
        int64           trdAmt; \
        \
        /** 客戶訂單編號 */ \
        int64           clOrdId; \
        /** 累計執行數量 */ \
        int32           cumQty; \
        /** 回報記錄號 (OES內部使用) */ \
        int32           __rowNum; \
        \
        /** 交易閘道器組序號 (OES內部使用) */ \
        uint8           __tgwGrpNo; \
        /** ETF贖回得到的替代資金是否當日可用 (OES內部使用) */ \
        uint8           __isTrsfInCashAvailable; \
        /** 交易閘道器平臺分割槽號 (OES內部使用) */ \
        uint8           __tgwPartitionNo; \
        /** 產品型別 @see eOesProductTypeT */ \
        uint8           productType; \
        /** 原始委託數量 */ \
        int32           origOrdQty; \
        \
        /** PBU程式碼 (席位號) */ \
        int32           pbuId; \
        /** 營業部程式碼 */ \
        int32           branchId


/* 結構體的初始化值定義 */
#define __NULLOBJ_OES_TRD_BASE_INFO_PKT                 \
        0, 0, 0, 0, 0, 0, \
        {0}, {0}, \
        0, 0, 0, 0, 0, \
        0, 0, 0, \
        0, 0, 0, 0, 0, \
        0, 0
/* -------------------------           */


/**
 * 附加的用於延遲測量的打點資訊欄位, 是否啟用取決於構建配置
 */
#define __OES_TRD_BASE_LATENCY_FIELDS                   \
        /** 成交確認的開始採集時間 */ \
        STimeval32T     __trdCnfmOrigRecvTime; \
        /** 成交確認的採集完成時間 */ \
        STimeval32T     __trdCnfmCollectedTime; \
        /** 成交確認的實際處理開始時間 */ \
        STimeval32T     __trdCnfmActualDealTime; \
        /** 成交確認的處理完成時間 */ \
        STimeval32T     __trdCnfmProcessedTime; \
        \
        /** 訊息推送時間 (寫入推送快取以後, 實際網路傳送之前) */ \
        STimeval32T     __pushingTime


/* 結構體的初始化值定義 */
#define __NULLOBJ_OES_TRD_BASE_LATENCY_FIELDS           \
        {0, 0}, {0, 0}, {0, 0}, {0, 0}, \
        {0, 0}
/* -------------------------           */


#if defined (_OES_EXPORT_LATENCY_STATS)

/**
 * 成交回報中的時間戳欄位定義 (用於記錄打點資訊以統計延遲)
 */
#   define  __OES_TRD_CNFM_LATENCY_FIELDS               \
            ; \
            __OES_TRD_BASE_LATENCY_FIELDS


/* 結構體的初始化值定義 */
#   define  __NULLOBJ_OES_TRD_CNFM_LATENCY_FIELDS       \
            , \
            __NULLOBJ_OES_TRD_BASE_LATENCY_FIELDS

#else

#   define  __OES_TRD_CNFM_LATENCY_FIELDS
#   define  __NULLOBJ_OES_TRD_CNFM_LATENCY_FIELDS

#endif  /* _OES_EXPORT_LATENCY_STATS */
/* -------------------------           */


/**
 * 成交回報資訊的內容定義
 */
#define __OES_TRD_CNFM_BASE_INFO_PKT                    \
        __OES_TRD_BASE_INFO_PKT; \
        \
        /** 客戶委託流水號 */ \
        int32           clSeqNo; \
        /** 客戶端編號 */ \
        int16           clientId; \
        /** 客戶端環境號 */ \
        int8            clEnvId; \
        /** 證券子類別 (為保持相容而位置凌亂, 後續會做調整) @see eOesSubSecurityTypeT */ \
        uint8           subSecurityType; \
        \
        /** 訂單當前狀態 @see eOesOrdStatusT */ \
        uint8           ordStatus; \
        /** 訂單型別 @see eOesOrdTypeShT eOesOrdTypeSzT */ \
        uint8           ordType; \
        /** 買賣型別 @see eOesBuySellTypeT */ \
        uint8           ordBuySellType; \
        /** 證券型別 @see eOesSecurityTypeT */ \
        uint8           securityType; \
        /** 原始委託價格, 單位精確到元后四位, 即1元 = 10000 */ \
        int32           origOrdPrice; \
        \
        /** 累計成交金額 */ \
        int64           cumAmt; \
        /** 累計成交利息 */ \
        int64           cumInterest; \
        /** 累計交易費用 */ \
        int64           cumFee; \
        \
        /** 使用者私有資訊 (由客戶端自定義填充, 並在回報資料中原樣返回) */ \
        union { \
            uint64      u64;                /**< uint64 型別的使用者私有資訊 */ \
            int64       i64;                /**< int64 型別的使用者私有資訊 */ \
            uint32      u32[2];             /**< uint32[2] 型別的使用者私有資訊 */ \
            int32       i32[2];             /**< int32[2] 型別的使用者私有資訊 */ \
            char        c8[8];              /**< char[8] 型別的使用者私有資訊 */ \
        } userInfo \
        \
        __OES_TRD_CNFM_LATENCY_FIELDS


/* 結構體的初始化值定義 */
#define __NULLOBJ_OES_TRD_CNFM_BASE_INFO_PKT            \
        __NULLOBJ_OES_TRD_BASE_INFO_PKT, \
        0, 0, 0, 0, \
        0, 0, 0, 0, 0, \
        0, 0, 0, \
        {0} \
        __NULLOBJ_OES_TRD_CNFM_LATENCY_FIELDS
/* -------------------------           */


/**
 * 成交基礎資訊的結構體定義
 */
typedef struct _OesTrdBaseInfo {
    __OES_TRD_BASE_INFO_PKT;
} OesTrdBaseInfoT;


/* 結構體的初始化值定義 */
#define NULLOBJ_OES_TRD_BASE_INFO                       \
        __NULLOBJ_OES_TRD_BASE_INFO_PKT
/* -------------------------           */


/**
 * 成交回報結構體定義
 */
typedef struct _OesTrdCnfm {
    __OES_TRD_CNFM_BASE_INFO_PKT;
} OesTrdCnfmT;


/* 結構體的初始化值定義 */
#define NULLOBJ_OES_TRD_CNFM                            \
        __NULLOBJ_OES_TRD_CNFM_BASE_INFO_PKT
/* -------------------------           */


/* ===================================================================
 * 新股配號、中籤記錄資訊 (OesLotWinningBaseInfo) 定義
 * =================================================================== */

/**
 * 新股配號、中籤記錄資訊的內容定義
 */
#define __OES_LOT_WINNING_BASE_INFO_PKT                 \
        /** 證券賬戶 */ \
        char            invAcctId[OES_INV_ACCT_ID_MAX_LEN]; \
        /** 配號程式碼/中籤程式碼 */ \
        char            securityId[OES_SECURITY_ID_MAX_LEN]; \
        /** 市場程式碼 @see eOesMarketIdT */ \
        uint8           mktId; \
        /** 記錄型別 @see eOesLotTypeT */ \
        uint8           lotType; \
        /**
         * 失敗原因, 當且僅當 lotType 為 OES_LOT_TYPE_FAILED 時此欄位有效
         * @see eOesLotRejReasonT
         */ \
        uint8           rejReason; \
        /** 按64位對齊填充域 */ \
        int8            __LOT_WINNING_BASE_INFO_filler; \
        /** 配號日期/中籤日期 (格式為 YYYYMMDD, 形如 20160830) */ \
        int32           lotDate; \
        \
        /** 證券名稱 */ \
        char            securityName[OES_SECURITY_NAME_MAX_LEN]; \
        \
        /** 配號首個號碼。當為中籤記錄時此欄位固定為0 */ \
        int64           assignNum; \
        /** 配號成功數量/中籤股數 */ \
        int32           lotQty; \
        /** 最終發行價, 單位精確到元后四位, 即1元 = 10000。當為配號記錄時此欄位值固定為0 */ \
        int32           lotPrice; \
        /** 中籤金額, 單位精確到元后四位, 即1元 = 10000。當為配號記錄時此欄位值固定為0 */ \
        int64           lotAmt


/* 結構體的初始化值定義 */
#define __NULLOBJ_OES_LOT_WINNING_BASE_INFO_PKT         \
        {0}, {0}, \
        0, 0, 0, 0, 0, \
        {0}, \
        0, 0, 0, 0
/* -------------------------           */


/**
 * 新股配號、中籤記錄資訊定義
 */
typedef struct _OesLotWinningBaseInfo {
    __OES_LOT_WINNING_BASE_INFO_PKT;
} OesLotWinningBaseInfoT;


/* 結構體的初始化值定義 */
#define NULLOBJ_OES_LOT_WINNING_BASE_INFO               \
        __NULLOBJ_OES_LOT_WINNING_BASE_INFO_PKT
/* -------------------------           */


/* ===================================================================
 * 出入金資訊的結構體定義
 * =================================================================== */

/**
 * 出入金委託基礎資訊的內容定義
 */
#define __OES_FUND_TRSF_BASE_INFO_PKT                   \
        /** 客戶委託流水號 (由客戶端維護的遞增流水) */ \
        int32           clSeqNo; \
        /** 劃轉方向 @see eOesFundTrsfDirectT */ \
        uint8           direct; \
        /** 出入金轉賬型別 @see eOesFundTrsfTypeT*/ \
        uint8           isAllotOnly; \
        /** 按64位對齊填充域 */ \
        uint8           __FUND_TRSF_BASE_filler[2]; \
        \
        /** 資金賬戶程式碼 */ \
        char            cashAcctId[OES_CASH_ACCT_ID_MAX_LEN]; \
        /** 交易密碼 */ \
        char            trdPasswd[OES_PWD_MAX_LEN]; \
        /**
         * 轉賬密碼(轉賬方向為轉入(銀行轉證券), 此密碼為銀行密碼.
         * 轉賬方向為轉出(證券轉銀行), 此密碼為資金密碼
         */ \
        char            trsfPasswd[OES_PWD_MAX_LEN]; \
        \
        /** 發生金額 (都是正數), 單位精確到元后四位, 即1元 = 10000 */ \
        int64           occurAmt; \
        \
        /** 使用者私有資訊 (由客戶端自定義填充, 並在回報資料中原樣返回) */ \
        union { \
            uint64      u64;                /**< uint64 型別的使用者私有資訊 */ \
            int64       i64;                /**< int64 型別的使用者私有資訊 */ \
            uint32      u32[2];             /**< uint32[2] 型別的使用者私有資訊 */ \
            int32       i32[2];             /**< int32[2] 型別的使用者私有資訊 */ \
            char        c8[8];              /**< char[8] 型別的使用者私有資訊 */ \
        } userInfo


/* 結構體的初始化值定義 */
#define __NULLOBJ_OES_FUND_TRSF_BASE_INFO_PKT           \
        0, 0, 0, {0}, \
        {0}, {0}, {0}, \
        0, {0}
/* -------------------------           */


/**
 * 出入金委託的基礎資訊結構體定義
 */
typedef struct _OesFundTrsfBaseInfo {
    __OES_FUND_TRSF_BASE_INFO_PKT;
} OesFundTrsfBaseInfoT;


/* 結構體的初始化值定義 */
#define NULLOBJ_OES_FUND_TRSF_BASE_INFO                 \
        __NULLOBJ_OES_FUND_TRSF_BASE_INFO_PKT
/* -------------------------           */


/**
 * 出入金請求定義
 */
typedef struct _OesFundTrsfReq {
    __OES_FUND_TRSF_BASE_INFO_PKT;
} OesFundTrsfReqT;


/* 結構體的初始化值定義 */
#define NULLOBJ_OES_FUND_TRSF_REQ                       \
        __NULLOBJ_OES_FUND_TRSF_BASE_INFO_PKT
/* -------------------------           */


/**
 * 出入金拒絕的回報結構定義 (因風控檢查未通過而被OES拒絕)
 */
typedef struct _OesFundTrsfReject {
    __OES_FUND_TRSF_BASE_INFO_PKT;

    /** 委託日期 (格式為 YYYYMMDD, 形如 20160830) */
    int32               ordDate;
    /** 委託時間 (格式為 HHMMSSsss, 形如 141205000) */
    int32               ordTime;

    /** 客戶端編號 */
    int16               clientId;
    /** 客戶端環境號 */
    int8                clEnvId;
    /** 64位對齊的填充域 */
    int8                __filler;
    /** 錯誤碼 */
    int32               rejReason;

    /** 錯誤資訊 */
    char                errorInfo[OES_MAX_ERROR_INFO_LEN];
} OesFundTrsfRejectT;


/* 結構體的初始化值定義 */
#define NULLOBJ_OES_FUND_TRSF_REJECT                    \
        __NULLOBJ_OES_FUND_TRSF_BASE_INFO_PKT, \
        0, 0, \
        0, 0, 0, 0, {0}
/* -------------------------           */


/**
 * 出入金委託執行狀態回報的結構體定義
 */
typedef struct _OesFundTrsfReport {
    /** 客戶委託流水號 (由客戶端維護的遞增流水) */
    int32               clSeqNo;
    /** 客戶端編號 */
    int16               clientId;
    /** 客戶端環境號 */
    int8                clEnvId;
    /** 劃轉方向 @see eOesFundTrsfDirectT */
    uint8               direct;
    /** 資金賬戶程式碼 */
    char                cashAcctId[OES_CASH_ACCT_ID_MAX_LEN];

    /** 發生金額 (都是正數), 單位精確到元后四位, 即1元 = 10000 */
    int64               occurAmt;
    /** 使用者私有資訊 (由客戶端自定義填充, 並在回報資料中原樣返回) */
    union {
        uint64          u64;                /**< uint64 型別的使用者私有資訊 */
        int64           i64;                /**< int64 型別的使用者私有資訊 */
        uint32          u32[2];             /**< uint32[2] 型別的使用者私有資訊 */
        int32           i32[2];             /**< int32[2] 型別的使用者私有資訊 */
        char            c8[8];              /**< char[8] 型別的使用者私有資訊 */
    } userInfo;

    /** OES出入金委託編號 (在OES內具有唯一性的內部出入金委託編號) */
    int32               fundTrsfId;
    /** 櫃檯出入金委託編號 */
    int32               counterEntrustNo;

    /** 出入金委託日期 (格式為 YYYYMMDD, 形如 20160830) */
    int32               operDate;
    /** 出入金委託時間 (格式為 HHMMSSsss, 形如 141205000) */
    int32               operTime;
    /** 上報櫃檯時間 (格式為 HHMMSSsss, 形如 141205000) */
    int32               dclrTime;
    /** 櫃檯執行結果採集時間 (格式為 HHMMSSsss, 形如 141205000) */
    int32               doneTime;

    /** 出入金轉賬型別 @see eOesFundTrsfTypeT*/
    uint8               isAllotOnly;
    /** 出入金委託執行狀態 @see eOesFundTrsfStatusT */
    uint8               trsfStatus;
    /** 是否有轉賬到主櫃 */
    uint8               __hasCounterTransfered;
    /** 按64位對齊填充域 */
    uint8               __filler;

    /** 錯誤原因 */
    int32               rejReason;
    /** 主櫃錯誤碼 */
    int32               counterErrCode;
    /** 按64位對齊填充域 */
    uint32              __filler2;
    /** 資金調撥流水號 */
    char                allotSerialNo[OES_MAX_ALLOT_SERIALNO_LEN];
    /** 錯誤資訊 */
    char                errorInfo[OES_MAX_ERROR_INFO_LEN];
} OesFundTrsfReportT;


/* 結構體的初始化值定義 */
#define NULLOBJ_OES_FUND_TRSF_REPORT                    \
        0, 0, 0, 0, {0}, \
        0, {0}, \
        0, 0, \
        0, 0, 0, 0, \
        0, 0, 0, 0, \
        0, 0, 0, {0}, {0}
/* -------------------------           */


/* ===================================================================
 * 證券發行資訊的結構體定義
 * =================================================================== */

/**
 * 證券發行基礎資訊的內容定義
 */
#define __OES_ISSUE_BASE_INFO_PKT                       \
        /** 證券發行程式碼 */ \
        char                securityId[OES_SECURITY_ID_MAX_LEN]; \
        /** 市場程式碼 @see eOesMarketIdT */ \
        uint8               mktId; \
        \
        /** 證券型別 @see eOesSecurityTypeT */ \
        uint8               securityType; \
        /** 證券子型別 @see eOesSubSecurityTypeT */ \
        uint8               subSecurityType; \
        /** 是否允許撤單 */ \
        uint8               isCancelAble; \
        /** 是否允許重複認購 */ \
        uint8               isReApplyAble; \
        /** 產品型別 @see eOesProductTypeT */ \
        uint8               productType; \
        /** 按64位對齊填充域 */ \
        uint8               __ISSUE_BASE_filler[2]; \
        \
        /** 證券名稱 */ \
        char                securityName[OES_SECURITY_NAME_MAX_LEN]; \
        /** 證券程式碼 (正股程式碼) */ \
        char                underlyingSecurityId[OES_SECURITY_ID_MAX_LEN]; \
        \
        /** 發行起始日 */ \
        int32               startDate; \
        /** 發行結束日 */ \
        int32               endDate; \
        /** 總髮行量 */ \
        int64               issueQty; \
        \
        /** 委託份數單位 */ \
        int32               qtyUnit; \
        /** 委託最大份數 */ \
        int32               ordMaxQty; \
        /** 委託最小份數 */ \
        int32               ordMinQty; \
        \
        /** 發行價格 */ \
        int32               issuePrice; \
        union { \
            /** 申購價格上限 (單位精確到元后四位, 即1元 = 10000) */ \
            int32           upperLimitPrice; \
            /** 申購價格上限 @deprecated 已廢棄, 為了相容舊版本而保留 */ \
            int32           ceilPrice; \
        }; \
        union { \
            /** 申購價格下限 (單位精確到元后四位, 即1元 = 10000) */ \
            int32           lowerLimitPrice; \
            /** 申購價格下限 @deprecated 已廢棄, 為了相容舊版本而保留 */ \
            int32           floorPrice; \
        }


#define __NULLOBJ_OES_ISSUE_BASE_INFO_PKT               \
        {0}, 0, \
        0, 0, 0, 0, 0, {0}, \
        {0}, {0}, \
        0, 0, 0, \
        0, 0, 0, \
        0, {0}, {0}
/* -------------------------           */


/**
 * 證券發行基礎資訊的結構體定義
 */
typedef struct _OesIssueBaseInfo {
    __OES_ISSUE_BASE_INFO_PKT;
} OesIssueBaseInfoT;


/* 結構體的初始化值定義 */
#define NULLOBJ_OES_ISSUE_BASE_INFO                     \
        __NULLOBJ_OES_ISSUE_BASE_INFO_PKT
/* -------------------------           */


/* ===================================================================
 * 現貨產品基礎資訊的結構體定義
 * =================================================================== */

/**
 * OES競價的限價引數配置
 */
typedef struct _OesPriceLimit {
    union {
        /** 漲停價 (單位精確到元后四位, 即1元 = 10000) */
        int32           upperLimitPrice;
        /** 漲停價 @deprecated 已廢棄, 為了相容舊版本而保留 */
        int32           ceilPrice;
    };

    union {
        /** 跌停價 (單位精確到元后四位, 即1元 = 10000) */
        int32           lowerLimitPrice;
        /** 跌停價 @deprecated 已廢棄, 為了相容舊版本而保留 */
        int32           floorPrice;
    };
} OesPriceLimitT;


/* 結構體的初始化值定義 */
#define NULLOBJ_OES_PRICE_LIMIT                         \
        {0}, {0}
/* -------------------------           */


/**
 * 現貨產品基礎資訊的內容定義
 * @since   0.15.9  2019/03/12
 */
#define __OES_STOCK_BASE_INFO_PKT                       \
        /** 產品程式碼 */ \
        char                securityId[OES_SECURITY_ID_MAX_LEN]; \
        /** 市場程式碼 @see eOesMarketIdT */ \
        uint8               mktId; \
        \
        /** 產品型別 @see eOesProductTypeT */ \
        uint8               productType; \
        /** 證券型別 @see eOesSecurityTypeT */ \
        uint8               securityType; \
        /** 證券子型別 @see eOesSubSecurityTypeT */ \
        uint8               subSecurityType; \
        /** 證券級別 @see eOesSecurityLevelT */ \
        uint8               securityLevel; \
        /** 證券風險等級 @see eOesSecurityRiskLevelT */ \
        uint8               securityRiskLevel; \
        /** 幣種 @see eOesCurrTypeT */ \
        uint8               currType; \
        /** 投資者適當性管理分類 @see eOesQualificationClassT */ \
        uint8               qualificationClass; \
        \
        /** 是否支援當日迴轉交易 0: 不支援; 其他: 支援 */ \
        uint8               isDayTrading; \
        /** 連續停牌標識 @see eOesSecuritySuspFlagT */ \
        uint8               suspFlag; \
        /** 臨時停牌標識 (TRUE 已停牌, FALSE 未停牌) */ \
        uint8               temporarySuspFlag; \
        /** 填充字元  滿足64位對齊 */ \
        uint8               __STOCK_BASE_filler[5]; \
        \
        /** 買入單位 */ \
        int32               buyQtyUnit; \
        union { \
            /** 單筆限價買委託數量上限 */ \
            int32           lmtBuyMaxQty; \
            /** 單筆限價買委託數量上限 @deprecated 已廢棄, 為了相容舊版本而保留 */ \
            int32           buyOrdMaxQty; \
        }; \
        union { \
            /** 單筆限價買委託數量下限 */ \
            int32           lmtBuyMinQty; \
            /** 單筆限價買委託數量下限 @deprecated 已廢棄, 為了相容舊版本而保留 */ \
            int32           buyOrdMinQty; \
        }; \
        /** 單筆市價買委託數量上限 */ \
        int32               mktBuyMaxQty; \
        /** 單筆市價買委託數量下限 */ \
        int32               mktBuyMinQty; \
        \
        /** 賣出單位 */ \
        int32               sellQtyUnit; \
        union { \
            /** 單筆限價賣委託數量上限 */ \
            int32           lmtSellMaxQty; \
            /** 單筆限價賣委託數量上限 @deprecated 已廢棄, 為了相容舊版本而保留 */ \
            int32           sellOrdMaxQty; \
        }; \
        union { \
            /** 單筆限價賣委託數量下限 */ \
            int32           lmtSellMinQty; \
            /** 單筆限價賣委託數量下限 @deprecated 已廢棄, 為了相容舊版本而保留 */ \
            int32           sellOrdMinQty; \
        }; \
        /** 單筆市價賣委託數量上限 */ \
        int32               mktSellMaxQty; \
        /** 單筆市價賣委託數量下限 */ \
        int32               mktSellMinQty; \
        \
        union { \
            /** 最小報價單位 (單位精確到元后四位, 即1元 = 10000) */ \
            int32           priceTick; \
            /** 最小報價單位 @deprecated 已廢棄, 為了相容舊版本而保留 */ \
            int32           priceUnit; \
        }; \
        /** 昨日收盤價，單位精確到元后四位，即1元 = 10000 */ \
        int32               prevClose; \
        /** 面值, 單位精確到元后四位, 即1元 = 10000 */ \
        int64               parPrice; \
        /** 債券的每百元應計利息額, 單位精確到元后八位, 即應計利息1元 = 100000000 */ \
        int64               bondInterest; \
        \
        /** 逆回購期限 */ \
        int32               repoExpirationDays; \
        /** 佔款天數 */ \
        int32               cashHoldDays; \
        \
        /** 競價限價引數表, 陣列下標為當前時段標誌 @see eOesTrdSessTypeT */ \
        OesPriceLimitT      priceLimit[__OES_TRD_SESS_TYPE_MAX]; \
        \
        /** 產品名稱 */ \
        char                securityName[OES_SECURITY_NAME_MAX_LEN]; \
        /** ETF申贖程式碼 (ETF程式碼所對應的一級市場程式碼) */ \
        char                fundId[OES_SECURITY_ID_MAX_LEN]; \
        /** 預留的備用欄位 */ \
        char                __STOCK_BASE_reserve[32]


/* 結構體的初始化值定義 */
#define __NULLOBJ_OES_STOCK_BASE_INFO_PKT               \
        {0}, 0, \
        0, 0, 0, 0, 0, 0, 0, \
        0, 0, 0, {0}, \
        0, {0}, {0}, 0, 0, \
        0, {0}, {0}, 0, 0, \
        {0}, 0, 0, 0, \
        0, 0, \
        {{NULLOBJ_OES_PRICE_LIMIT}}, \
        {0}, {0}, {0}
/* -------------------------           */


/**
 * 現貨產品基礎資訊的結構體定義
 */
typedef struct _OesStockBaseInfo {
    __OES_STOCK_BASE_INFO_PKT;
} OesStockBaseInfoT;


/* 結構體的初始化值定義 */
#define NULLOBJ_OES_STOCK_BASE_INFO                     \
        __NULLOBJ_OES_STOCK_BASE_INFO_PKT
/* -------------------------           */


/* ===================================================================
 * Etf申贖產品基礎資訊的結構體定義
 * =================================================================== */

/**
 * Etf申贖產品基礎資訊定義
 */
#define __OES_ETF_BASE_INFO_PKT                         \
        /** Etf申贖程式碼 */ \
        char                fundId[OES_SECURITY_ID_MAX_LEN]; \
        /** Etf買賣程式碼 */ \
        char                securityId[OES_SECURITY_ID_MAX_LEN]; \
        /** 市場程式碼 @see eOesMarketIdT */ \
        uint8               mktId; \
        \
        /** 證券型別 @see eOesSecurityTypeT */ \
        uint8               securityType; \
        /** 證券子型別 @see eOesSubSecurityTypeT */ \
        uint8               subSecurityType; \
        /** 是否需要釋出IOPV  1: 是; 0: 否 */ \
        uint8               isPublishIOPV; \
        \
        /** 交易所/基金公司的允許申購標誌  1: 是; 0: 否 */ \
        uint8               isCreationAble; \
        /** 交易所/基金公司的允許贖回標誌  1: 是; 0: 否 */ \
        uint8               isRedemptionAble; \
        /** 券商管理端的禁止交易標誌  1: 是; 0: 否  */ \
        uint8               isDisabled; \
        /** 按64位對齊填充域 */ \
        uint8               __ETF_BASE_filler; \
        \
        /** 成分證券數目 */ \
        int32               componentCnt; \
        /** 每個籃子 (最小申購、贖回單位) 對應的ETF份數, 即申購贖回單位 */ \
        int32               creRdmUnit; \
        /** 最大現金替代比例, 單位精確到十萬分之一, 即替代比例50% = 50000 */ \
        int32               maxCashRatio; \
        /** 前一日基金的單位淨值, 單位精確到元后四位, 即1元 = 10000 */ \
        int32               nav; \
        \
        /** 前一日最小申贖單位淨值, 單位精確到元后四位, 即1元 = 10000 */ \
        int64               navPerCU; \
        /** 紅利金額, 單位精確到元后四位, 即1元 = 10000 */ \
        int64               dividendPerCU; \
        \
        /** 當前交易日, 格式YYYYMMDD */ \
        int32               tradingDay; \
        /** 前一交易日, 格式YYYYMMDD */ \
        int32               preTradingDay; \
        /** 每個籃子的預估現金差額, 單位精確到元后四位, 即1元 = 10000 */ \
        int64               estiCashCmpoent; \
        /** 前一日現金差額, 單位精確到元后四位, 即1元 = 10000 */ \
        int64               cashCmpoent; \
        /** 單個賬戶當日累計申購總額限制 */ \
        int64               creationLimit; \
        /** 單個賬戶當日累計贖回總額限制 */ \
        int64               redemLimit; \
        /** 單個賬戶當日淨申購總額限制 */ \
        int64               netCreationLimit; \
        /** 單個賬戶當日淨贖回總額限制 */ \
        int64               netRedemLimit


/* 結構體的初始化值定義 */
#define __NULLOBJ_OES_ETF_BASE_INFO_PKT                 \
        {0}, {0}, 0, \
        0, 0, 0, \
        0, 0, 0, 0, \
        0, 0, 0, 0, \
        0, 0, \
        0, 0, 0, 0, \
        0, 0, 0, 0
/* -------------------------           */


/**
 * ETF申贖產品基礎資訊的結構體定義
 */
typedef struct _OesEtfBaseInfo {
    __OES_ETF_BASE_INFO_PKT;
} OesEtfBaseInfoT;


/* 結構體的初始化值定義 */
#define NULLOBJ_OES_ETF_BASE_INFO                       \
        __NULLOBJ_OES_ETF_BASE_INFO_PKT
/* -------------------------           */


/* ===================================================================
 * Etf成分股基礎資訊的結構體定義
 * =================================================================== */

/**
 * Etf成分股基礎資訊定義
 */
#define __OES_ETF_COMPONENT_BASE_INFO_PKT               \
        /** 成分股所屬ETF的基金程式碼 */ \
        char                fundId[OES_SECURITY_ID_MAX_LEN]; \
        /** Etf成分股程式碼 */ \
        char                securityId[OES_SECURITY_ID_MAX_LEN]; \
        /** 市場程式碼 @see eOesMarketIdT */ \
        uint8               mktId; \
        /** 現金替代標識 @see eOesEtfSubFlagT */ \
        uint8               subFlag; \
        /** 證券型別 @see eOesSecurityTypeT */ \
        uint8               securityType; \
        /** 證券子型別 @see eOesSubSecurityTypeT */ \
        uint8               subSecurityType; \
        \
        /** 昨日收盤價格, 單位精確到元后四位, 即1元 = 10000 */ \
        int32               prevClose; \
        /** 成分證券數量 */ \
        int32               qty; \
        /** 溢價比例, 單位精確到十萬分之一, 即溢價比例10% = 10000 */ \
        int32               premiumRate; \
        \
        /** 申購替代金額, 單位精確到元后四位, 即1元 = 10000 */ \
        int64               creationSubCash; \
        /** 贖回替代金額, 單位精確到元后四位, 即1元 = 10000 */ \
        int64               redemptionCashSub


/* 結構體的初始化值定義 */
#define __NULLOBJ_OES_ETF_COMPONENT_BASE_INFO_PKT       \
        {0}, {0}, \
        0, 0, 0, 0, \
        0, 0, 0, \
        0, 0
/* -------------------------           */


/**
 * Etf成分股基礎資訊的結構體定義
 */
typedef struct _OesEtfComponentBaseInfo {
    __OES_ETF_COMPONENT_BASE_INFO_PKT;
} OesEtfComponentBaseInfoT;


/* 結構體的初始化值定義 */
#define NULLOBJ_OES_ETF_COMPONENT_BASE_INFO             \
        __NULLOBJ_OES_ETF_COMPONENT_BASE_INFO_PKT
/* -------------------------           */


/* ===================================================================
 * 期權產品基礎資訊的結構體定義
 * =================================================================== */

/**
 * 期權產品基礎資訊的內容定義
 */
#define __OES_OPTION_BASE_INFO_PKT          \
        /** 期權合約程式碼 */ \
        char                securityId[OES_SECURITY_ID_MAX_LEN]; \
        /** 市場程式碼 @see eOesMarketIdT */ \
        uint8               mktId; \
        \
        /** 證券型別 @see eOesSecurityTypeT */ \
        uint8               securityType; \
        /** 證券子型別 @see eOesSubSecurityTypeT */ \
        uint8               subSecurityType; \
        /** 合約型別 @see eOesOptContractTypeT */ \
        uint8               contractType; \
        /** 開倉標識 @see eOesOptionOpenFlagT */ \
        uint8               openFlag; \
        /** 行權型別 @see eOesOptionTypeT */ \
        uint8               optionType; \
        /** 連續停牌標識 @see eOesSecuritySuspFlagT */ \
        uint8               suspFlag; \
        /** 臨時停牌標識 (TRUE 已停牌, FALSE 未停牌) */ \
        uint8               temporarySuspFlag; \
        \
        /** 經過除權除息調整後的合約單位 */ \
        int32               contractMultiplierUnit; \
        /** 經過除權除息調整後的期權行權價, 單位精確到元后四位, 即1元 = 10000 */ \
        int32               excPrice; \
        \
        /** 期權首個交易日, 格式為YYYYMMDD */ \
        int32               startDate; \
        /** 期權最後交易/行權日, 格式為YYYYMMDD */ \
        int32               endDate; \
        /** 期權行權日, 格式為YYYYMMDD */ \
        int32               execDate; \
        /** 期權到期日, 格式為YYYYMMDD */ \
        int32               expDate; \
        \
        /** 合約前收盤價, 單位精確到元后四位, 即1元 = 10000 */ \
        int32               closePrice; \
        /** 合約前結算價, 單位精確到元后四位, 即1元 = 10000 */ \
        int32               settlPrice; \
        /** 一手等於幾張合約 */ \
        int32               roundLot; \
        /** 最小報價單位 */ \
        int32               tickSize; \
        /** 漲停價, 單位精確到元后四位, 即1元 = 10000 */ \
        int32               ceilPrice; \
        /** 跌停價, 單位精確到元后四位, 即1元 = 10000 */ \
        int32               floorPrice; \
        \
        /** 當日持有一張合約所需保證金, 單位精確到元后四位, 即1元 = 10000 */ \
        int64               marginUnit; \
        /** 未平倉合約張數 */ \
        int64               leavesQty; \
        \
        /** 單筆限價申報的申報張數上限 */ \
        int32               lmtOrdMaxQty; \
        /** 單筆限價申報的申報張數下限 */ \
        int32               lmtOrdMinQty; \
        /** 單筆市價申報的申報張數上限 */ \
        int32               mktOrdMaxQty; \
        /** 單筆市價申報的申報張數下限 */ \
        int32               mktOrdMinQty; \
        \
        /* 標的證券程式碼 */ \
        char                underlyingSecurityId[OES_SECURITY_ID_MAX_LEN]; \
        /** 市場程式碼 @see eOesMarketIdT */ \
        uint8               underlyingMktId; \
        /** 證券型別 @see eOesSecurityTypeT */ \
        uint8               underlyingSecuType; \
        /** 臨近到期日期  1: 臨近到期日; 0: 非臨近到期日 */ \
        uint8               closeEndDateFlag; \
        /** 按64位對齊填充域 */ \
        uint8               __OPTION_BASE_filler1; \
        /** 標的前收盤價, 單位精確到元后四位, 即1元 = 10000 */ \
        int32               underlyingClosePrice; \
        \
        /** 期權合約名稱 */ \
        char                securityName[OES_SECURITY_NAME_MAX_LEN]


#define __NULLOBJ_OES_OPTION_BASE_INFO_PKT              \
        {0}, 0, \
        0, 0, 0, 0, 0, 0, 0, \
        0, 0, \
        0, 0, 0, 0, \
        0, 0, 0, 0, 0, 0, \
        0, 0, \
        0, 0, 0, 0, \
        {0}, 0, 0, 0, 0, 0, \
        {0}
/* -------------------------           */


/**
 * 期權產品基礎資訊的結構體定義
 */
typedef struct _OesOptionBaseInfo {
    __OES_OPTION_BASE_INFO_PKT;
} OesOptionBaseInfoT;


/* 結構體的初始化值定義 */
#define NULLOBJ_OES_OPTION_BASE_INFO                    \
        __NULLOBJ_OES_OPTION_BASE_INFO_PKT
/* -------------------------           */


/* ===================================================================
 * 客戶資金資訊結構體定義
 * =================================================================== */

/**
 * 客戶資金資訊內容定義
 */
#define __OES_CASH_ASSET_BASE_INFO_PKT                  \
        /** 資金賬戶程式碼 */ \
        char                cashAcctId[OES_CASH_ACCT_ID_MAX_LEN]; \
        /** 客戶程式碼 */ \
        char                custId[OES_CUST_ID_MAX_LEN]; \
        \
        /** 幣種 @see eOesCurrTypeT */ \
        uint8               currType; \
        /** 資金帳戶類別(冗餘自資金賬戶) @see eOesCashTypeT */ \
        uint8               cashType; \
        /** 資金帳戶狀態(冗餘自資金賬戶) @see eOesAcctStatusT */ \
        uint8               cashAcctStatus; \
        /** 是否禁止出入金 (僅供API查詢使用) */ \
        uint8               isFundTrsfDisabled; \
        /** 按64位對齊的填充域 */ \
        uint8               __CASH_ASSET_BASE_filler[4]; \
        \
        /** 期初餘額, 單位精確到元后四位, 即1元 = 10000 */ \
        int64               beginningBal; \
        /** 期初可用餘額, 單位精確到元后四位, 即1元 = 10000 */ \
        int64               beginningAvailableBal; \
        /** 期初可取餘額, 單位精確到元后四位, 即1元 = 10000 */ \
        int64               beginningDrawableBal; \
        \
        /** 不可用資金餘額(既不可交易又不可提取), 單位精確到元后四位, 即1元 = 10000 */ \
        int64               disableBal; \
        /** 當前衝正金額(紅衝藍補的資金淨額), 取值可以為負數(表示資金調出), 單位精確到元后四位(即1元 = 10000) */ \
        int64               reversalAmt; \
        /** 手動凍結資金, 取值在0和當前資產之間, 單位精確到元后四位(即1元 = 10000) */ \
        int64               manualFrzAmt; \
        \
        /** 日中累計存入資金金額, 單位精確到元后四位, 即1元 = 10000 */ \
        int64               totalDepositAmt; \
        /** 日中累計提取資金金額, 單位精確到元后四位, 即1元 = 10000 */ \
        int64               totalWithdrawAmt; \
        /** 當前提取凍結資金金額, 單位精確到元后四位, 即1元 = 10000 */ \
        int64               withdrawFrzAmt; \
        \
        /** 日中累計 賣/贖回 獲得的可用資金金額, 單位精確到元后四位, 即1元 = 10000 */ \
        int64               totalSellAmt; \
        /** 日中累計 買/申購/逆回購 使用資金金額，單位精確到元后四位，即1元 = 10000 */ \
        int64               totalBuyAmt; \
        /** 當前交易凍結金額, 單位精確到元后四位, 即1元 = 10000 */ \
        int64               buyFrzAmt; \
        \
        /** 日中累計交易費用金額, 單位精確到元后四位, 即1元 = 10000 */ \
        int64               totalFeeAmt; \
        /** 當前凍結交易費用金額, 單位精確到元后四位, 即1元 = 10000 */ \
        int64               feeFrzAmt; \
        \
        /** 當前維持的保證金金額, 單位精確到元后四位, 即1元 = 10000 */ \
        int64               marginAmt; \
        /** 當前凍結的保證金金額, 單位精確到元后四位, 即1元 = 10000 */ \
        int64               marginFrzAmt


#define __NULLOBJ_OES_CASH_ASSET_BASE_INFO_PKT          \
        {0}, {0}, \
        0, 0, 0, 0, {0}, \
        0, 0, 0, \
        0, 0, 0, \
        0, 0, 0, \
        0, 0, 0, \
        0, 0, \
        0, 0
/* -------------------------           */


/**
 * 客戶資金基礎資訊結構體定義
 */
typedef struct _OesCashAssetBaseInfo {
    __OES_CASH_ASSET_BASE_INFO_PKT;
} OesCashAssetBaseInfoT;


/* 結構體的初始化值定義 */
#define NULLOBJ_OES_CASH_ASSET_BASE_INFO                \
        __NULLOBJ_OES_CASH_ASSET_BASE_INFO_PKT
/* -------------------------           */


/* ===================================================================
 * 客戶基礎資訊的結構體定義
 * =================================================================== */

/**
 * 客戶基礎資訊的內容定義
 */
#define __OES_CUST_BASE_INFO_PKT                        \
        /** 客戶程式碼 */ \
        char                custId[OES_CUST_ID_MAX_LEN]; \
        \
        /** 客戶型別 */ \
        uint8               custType; \
        /** 客戶狀態 0 正常, 非0 不正常 */ \
        uint8               status; \
        /** OES風險等級 @see eOesSecurityRiskLevelT */ \
        uint8               riskLevel; \
        /** 客戶原始風險等級 */ \
        uint8               originRiskLevel; \
        /** 機構標誌 (TRUE 機構投資者, FALSE 個人投資者) */ \
        uint8               institutionFlag; \
        /** 投資者分類 @see eOesInvestorClassT */ \
        uint8               investorClass; \
        /** 按64位對齊填充域 */ \
        uint8               __CUST_BASE_filler1[2]; \
        \
        /** 營業部程式碼 */ \
        int32               branchId; \
        /** 按64位對齊填充域 */ \
        uint32              __CUST_BASE_filler2


#define __NULLOBJ_OES_CUST_BASE_INFO_PKT                \
        {0}, \
        0, 0, 0, 0, 0, 0, {0}, \
        0, 0
/* -------------------------           */


/**
 * 客戶基礎資訊的結構體定義
 */
typedef struct _OesCustBaseInfo {
    __OES_CUST_BASE_INFO_PKT;
} OesCustBaseInfoT;


/* 結構體的初始化值定義 */
#define NULLOBJ_OES_CUST_BASE_INFO                      \
        __NULLOBJ_OES_CUST_BASE_INFO_PKT
/* -------------------------           */


/* ===================================================================
 * 證券賬戶基礎資訊的結構體定義
 * =================================================================== */

/**
 * 證券賬戶基礎資訊的內容定義
 * @since   0.15.9  2019/03/12
 */
#define __OES_INV_ACCT_BASE_INFO_PKT                    \
        /** 股東賬戶程式碼 */ \
        char                invAcctId[OES_INV_ACCT_ID_MAX_LEN]; \
        /** 市場 @see eOesMarketIdT */ \
        uint8               mktId; \
        \
        /** 賬戶型別 @see eOesAcctTypeT */ \
        uint8               acctType; \
        /** 賬戶狀態 @see eOesAcctStatusT */ \
        uint8               status; \
        /** 股東賬戶的所有者型別 @see eOesOwnerTypeT */ \
        uint8               ownerType; \
        /** 期權投資者級別 @see eOesOptInvLevelT */ \
        uint8               optInvLevel; \
        /** 是否禁止交易 (僅供API查詢使用) */ \
        uint8               isTradeDisabled; \
        /** 按64位對齊填充域 */ \
        uint8               __INV_ACCT_BASE_filler[2]; \
        \
        /** 證券賬戶許可權限制 @see eOesTradingLimitT */ \
        uint64              limits; \
        /** 股東許可權/客戶許可權 @see eOesTradingPermissionT */ \
        uint64              permissions; \
        \
        /** 席位號 */ \
        int32               pbuId; \
        /** 按64位對齊填充域 */ \
        int32               __INV_ACCT_BASE_filler2; \
        /** 主機板權益 (新股/配股認購限額) */ \
        int32               subscriptionQuota; \
        /** 科創板權益 (新股/配股認購限額) */ \
        int32               kcSubscriptionQuota; \
        \
        /** 預留的備用欄位 */ \
        char                __INV_ACCT_BASE_reserve[32]


/* 結構體的初始化值定義 */
#define __NULLOBJ_OES_INV_ACCT_BASE_INFO_PKT            \
        {0}, 0, \
        0, 0, 0, 0, 0, {0}, \
        0, 0, \
        0, 0, 0, 0, \
        {0}
/* -------------------------           */


/**
 * 證券賬戶基礎資訊的結構體定義
 */
typedef struct _OesInvAcctBaseInfo {
    __OES_INV_ACCT_BASE_INFO_PKT;
} OesInvAcctBaseInfoT;


/* 結構體的初始化值定義 */
#define NULLOBJ_OES_INV_ACCT_BASE_INFO                  \
        __NULLOBJ_OES_INV_ACCT_BASE_INFO_PKT
/* -------------------------           */


/* ===================================================================
 * 股票持倉資訊的結構體定義
 * =================================================================== */

/**
 * 股票持倉基礎資訊的內容定義
 */
#define __OES_STK_HOLDING_BASE_INFO_PKT                 \
        /** 賬戶程式碼 */ \
        char                invAcctId[OES_INV_ACCT_ID_MAX_LEN]; \
        /** 產品程式碼 */ \
        char                securityId[OES_SECURITY_ID_MAX_LEN]; \
        /** 市場程式碼 @see eOesMarketIdT */ \
        uint8               mktId; \
        /** 證券型別 @see eOesSecurityTypeT */ \
        uint8               securityType; \
        /** 證券子型別 @see eOesSubSecurityTypeT */ \
        uint8               subSecurityType; \
        /** 產品型別 @see eOesProductTypeT */ \
        uint8               productType; \
        /** 按64位對齊的填充域 */ \
        uint8               __HOLD_BASE_filler[4]; \
        \
        /** 日初持倉 */ \
        int64               originalHld; \
        /** 日初總持倉成本 (日初持倉成本價 = 日初總持倉成本 / 日初持倉) */ \
        int64               originalCostAmt; \
        \
        /** 日中累計買入持倉 */ \
        int64               totalBuyHld; \
        /** 日中累計賣出持倉 */ \
        int64               totalSellHld; \
        /** 當前賣出凍結持倉 */ \
        int64               sellFrzHld; \
        /** 手動凍結持倉 */ \
        int64               manualFrzHld; \
        \
        /** 日中累計買入金額 */ \
        int64               totalBuyAmt; \
        /** 日中累計賣出金額 */ \
        int64               totalSellAmt; \
        /** 日中累計買入費用 */ \
        int64               totalBuyFee; \
        /** 日中累計賣出費用 */ \
        int64               totalSellFee; \
        \
        /**
         * 日中累計轉換獲得持倉, ETF申贖業務使用
         * - 成分股持倉場景, 轉換獲得指贖回時獲得的成分股持倉;
         * - ETF證券持倉場景, 轉換獲得指申購時獲得的ETF證券股持倉;
         */ \
        int64               totalTrsfInHld; \
        /**
         * 日中累計轉換付出持倉, ETF申贖業務使用
         * - 成分股持倉場景, 轉換付出指申購時使用的成分股持倉;
         * - ETF證券持倉場景, 轉換付出指贖回時使用的ETF證券股持倉;
         */ \
        int64               totalTrsfOutHld; \
        /** 當前轉換付出凍結持倉 */ \
        int64               trsfOutFrzHld; \
        \
        /** 當前已鎖定持倉 */ \
        int64               lockHld; \
        /** 當前鎖定凍結持倉數量 */ \
        int64               lockFrzHld; \
        /** 當前解鎖定凍結持倉數量 */ \
        int64               unlockFrzHld; \
        \
        /** 當前備兌凍結的現貨持倉數量 */ \
        int64               coveredFrzHld; \
        /** 當前已備兌使用的現貨持倉數量 */ \
        int64               coveredHld


/* 結構體的初始化值定義 */
#define __NULLOBJ_OES_STK_HOLDING_BASE_INFO_PKT         \
        {0}, {0}, \
        0, 0, 0, 0, {0}, \
        0, 0, \
        0, 0, 0, 0, \
        0, 0, 0, 0, \
        0, 0, 0, \
        0, 0, 0, \
        0, 0
/* -------------------------           */


/**
 * 股票持倉基礎資訊的結構體定義
 */
typedef struct _OesStkHoldingBaseInfo {
    __OES_STK_HOLDING_BASE_INFO_PKT;
} OesStkHoldingBaseInfoT;


/* 結構體的初始化值定義 */
#define NULLOBJ_OES_STK_HOLDING_BASE_INFO               \
        __NULLOBJ_OES_STK_HOLDING_BASE_INFO_PKT
/* -------------------------           */


/* ===================================================================
 * 期權持倉資訊的結構體定義
 * =================================================================== */

/**
 * 期權持倉基礎資訊的內容定義
 */
#define __OES_OPT_HOLDING_BASE_INFO_PKT                 \
        /** 賬戶程式碼 */ \
        char                invAcctId[OES_INV_ACCT_ID_MAX_LEN]; \
        /** 產品程式碼 */ \
        char                securityId[OES_SECURITY_ID_MAX_LEN]; \
        /** 市場程式碼 @see eOesMarketIdT */ \
        uint8               mktId; \
        /** 按64位對齊的填充域 */ \
        uint8               __HOLD_BASE_filler[7]; \
        \
        /** 權利倉 */ \
        int64               hldA; \
        /** 義務倉 */ \
        int64               hldB; \
        /** 當日備兌倉 */ \
        int64               hldC; \
        /** 非當日備兌倉 */ \
        int64               hldC2; \
        /** 權利倉凍結 */ \
        int64               hldRA; \
        /** 義務倉凍結 */ \
        int64               hldRB; \
        /** 備兌倉凍結 */ \
        int64               hldRC


/* 結構體的初始化值定義 */
#define __NULLOBJ_OES_OPT_HOLDING_BASE_INFO_PKT         \
        {0}, {0}, 0, {0}, \
        0, 0, 0, \
        0, 0, 0, 0
/* -------------------------           */


/**
 * 期權持倉基礎資訊的結構體定義
 */
typedef struct _OesOptHoldingBaseInfo {
    __OES_OPT_HOLDING_BASE_INFO_PKT;
} OesOptHoldingBaseInfoT;


/* 結構體的初始化值定義 */
#define NULLOBJ_OES_OPT_HOLDING_BASE_INFO               \
        __NULLOBJ_OES_OPT_HOLDING_BASE_INFO_PKT
/* -------------------------           */


/* ===================================================================
 * 市場狀態資訊的結構體定義
 * =================================================================== */

/**
 * 市場狀態資訊的結構體定義
 */
typedef struct _OesMarketStateInfo {
    uint8               exchId;             /**< 交易所程式碼 @see eOesExchangeIdT */
    uint8               platformId;         /**< 交易平臺型別 @see eOesPlatformIdT */
    uint8               mktId;              /**< 市場程式碼 @see eOesMarketIdT */
    uint8               mktState;           /**< 市場狀態 @see eOesMarketStateT */
    uint8               __filler[4];        /**< 按64位對齊的填充域 */
} OesMarketStateInfoT;


/* 結構體的初始化值定義 */
#define NULLOBJ_OES_MARKET_STATE_INFO                   \
        0, 0, 0, 0, {0}
/* -------------------------           */


/* ===================================================================
 * 交易許可權和交易限制的結構體定義
 * =================================================================== */

/**
 * 交易許可權的元資料定義 (用於許可權配置)
 */
typedef struct _OesTradingPermissionEntry {
    uint8               permissionNo;       /**< 許可權號 */
    uint8               isDisabled;         /**< 失效標誌 */
    char                counterAlias;       /**< 預設的主櫃許可權別名 (對應於主櫃匯出的許可權程式碼) */
    uint8               __filler[5];        /**< 按64位對齊填充域 */
    uint64              permissionCode;     /**< 許可權程式碼 (內部使用, 許可權號對應的位域值) */

    /** 適用的市場 @see eOesMarketIdT */
    uint8               applicableMarkets[__OES_MKT_ID_MAX_ALIGNED8];

    /** 許可權說明 (中文名稱 UTF-8) */
    char                permissionMemo[OES_MAX_PERMISSION_MEMO_LEN];
} OesTradingPermissionEntryT;


/* 結構體的初始化值定義 */
#define NULLOBJ_OES_TRADING_PERMISSION_ENTRY            \
        0, 0, 0, {0}, 0, \
        {0}, {0}
/* -------------------------           */


#ifdef __cplusplus
}
#endif

#endif  /* _OES_BASE_MODEL_H */
