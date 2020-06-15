
/*
 * Copyright 2009-2016 the original author or authors.
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
 * @file    oes_api.h
 *
 * Oes API庫函式實現
 *
 * @version 0.11.1      2016/11/17
 * @version 0.12        2016/11/30
 *          - 增加客戶資訊查詢功能
 *          - 補充整理錯誤號的註釋資訊和部分錯誤號定義
 *          - 增加 OesApi_GetErrorMsg 和 OesApi_GetErrorMsg2 方法
 *          - 在登入報文中增加協議版本號資訊, 並在登入時校驗協議版本號的相容性
 * @version 0.12.1      2016/12/21
 *          - 刪除 OesApi_IsBusinessError 介面，查詢介面不再返回小於 -1000 的錯誤
 *          - 查詢介面返回值變更:
 *              - 單條查詢介面無資料返回 NEG(ENOENT)
 *              - 批量查詢介面無匹配資料時返回 0
 *              - 單條/批量 查詢被伺服器拒絕返回 NEG(EINVAL)，具體錯誤資訊通過日誌列印
 *          - 微調oes_api日誌列印格式
 * @version 0.12.3      2017/01/10
 *          - 精簡API依賴的標頭檔案，並最小化API釋出包中的標頭檔案數量
 *          - 重新命名 protocol_parser/errors/oes_protocol_errors.h ==> errors/oes_errors.h
 *          - 從釋出包中刪除協議解析相關的標頭檔案，客戶端如果需要的話，可以分別釋出
 *          - 單條持倉查詢介面 OesApi_QuerySingleHolding 拆分:
 *              - OesApi_QuerySingleStkHolding 查詢單條股票持倉
 *              - OesApi_QuerySingleOptHolding 查詢單條期權持倉
 *          - OesApi_QuerySingleStkHolding 引數型別變更:
 *              - 引數四的型別變更 OesHoldItemT -> OesStkHoldingItemT(原OesStockHoldInfoT)
 *          - OesApi_QuerySingleOptHolding 引數型別變更:
 *              - 引數四的型別變更 OesHoldItemT -> OesOptHoldingItemT(原OesOptionHoldInfoT)
 *          - 批量持倉查詢介面 OesApi_QueryHolding 拆分:
 *              - OesApi_QueryStkHolding 查詢股票持倉
 *              - OesApi_QueryOptHolding 查詢期權持倉
 *          - OesApi_QueryStkHolding 引數型別變更:
 *              - 引數二的型別變更 OesQryHoldFilterT -> OesQryStkHoldingFilterT
 *              - 引數三 pOnMsgCallback.pMsgBody 返回資料型別變更 OesHoldItemT -> OesStkHoldingItemT
 *          - OesApi_QueryOptHolding 引數型別變更:
 *              - 引數二的型別變更 OesQryHoldFilterT -> OesQryOptHoldingFilterT
 *              - 引數三 pOnMsgCallback.pMsgBody 返回資料型別變更 OesHoldItemT -> OesOptHoldingItemT
 * @version 0.12.6.3    2017/03/24
 *          - 增加oes_api.h中的標頭檔案引用，api使用者不在需要顯式引用sutil庫的標頭檔案
 * @version 0.12.8.2    2017/05/16
 *          - 新增 ‘證券發行資訊查詢(OesApi_QueryIssue)’ 介面，此介面獲取到的
 *            證券發行資訊型別定義為 ‘OesIssueItemT’
 *          - 新增 ‘重複的認購委託(OESERR_SUBSCRIBE_ORD_DUPLICATE)’ 錯誤，錯誤碼為1240
 * @version 0.15.2      2017/07/18
 *          - 新增 ‘傳送出入金委託請求(OesApi_SendFundTrsfReq)’ 介面
 *          - 新增 ‘查詢新股配號、中籤資訊(OesApi_QueryLotWinning)’ 介面
 * @version 0.15.3      2017/08/07
 *          - 登入時oes-server端增加IP、MAC非空的校驗
 * @version 0.15.3.3    2017/08/20
 *          - 新增介面 '重置執行緒級別的日誌記錄器名稱 (OesApi_ResetThreadLoggerName)'，
 *            以支援為當前執行緒設定獨立的日誌檔案
 * @version 0.15.4      2017/08/22
 *          - 增加客戶端環境號 (clEnvId), 涉及到以下函式介面、資料結構、通訊報文的變更:
 *              - 以下介面函式的引數發生變更 (增加引數 clEnvId):
 *                  - 連線並登入到指定的OES節點與服務 (OesApi_Logon)
 *                  - 連線並登入到OES服務叢集 (OesApi_LogonReplicaSet)
 *                  - 連線並登入到OES服務叢集 (OesApi_LogonPeerNodes)
 *                  - 傳送回報同步訊息 (OesApi_SendReportSynchronization)
 *              - 以下通訊報文發生變更 (增加欄位 clEnvId):
 *                  - 登入請求/應答報文 (OesLogonReqT / OesLogonRspT)
 *              - 以下通訊報文發生變更 (增加欄位 subscribeEnvId):
 *                  - 回報同步請求/應答訊息 (OesReportSynchronizationReqT / OesReportSynchronizationRspT)
 *              - 以下資料結構發生變更 (增加欄位 clEnvId):
 *                  - 客戶端會話資訊/連線通道資訊 (OesApiSessionInfoT)
 *                  - 遠端主機配置資訊 (OesApiRemoteCfgT)
 *          - 新增介面 '重置執行緒級別的日誌記錄器名稱 (OesApi_ResetThreadLoggerName)'，
 *            以支援為當前執行緒設定獨立的日誌檔案
 *          - 重新命名介面函式 OesApi_SendFundTrsfReq -> OesApi_SendFundTransferReq
 *          - 新增介面 '獲取API的發行版本號 (OesApi_GetApiVersion)'
 *          - 新增介面 '獲取當前交易日 (OesApi_GetTradingDay)'
 *          - 新增介面 '傳送撤單請求 (OesApi_SendOrderCancelReq)'
 *              - 相比原來的撤單方式, 撤單請求介面支援通過 clEnvId + clSeqNo 進行撤單
 *          - 調整回報介面回撥方法型別定義 F_OESAPI_ONMSG_T -> F_OESAPI_ON_RPT_MSG_T
 *          - 調整查詢介面回撥方法型別定義 F_OESAPI_ONMSG_T -> F_OESAPI_ON_QRY_MSG_T
 *          - 查詢介面回撥方法中增加 OesQryCursorT 型別引數，其中攜帶“是否是最後一條”資訊
 * @version 0.15.4.1    2017/09/25
 *          - 伺服器端刪除了對JSON等通訊協議等支援, 改為只支援二進位制協議
 * @version 0.15.4.2    2017/10/16
 *          - 回報同步請求處理改成非同步應答模式，回報通道增加訊息型別 OESMSG_RPT_REPORT_SYNCHRONIZATION
 * @version 0.15.5      2017/11/03
 *          - 新增介面 '獲取通道繫結clEnvId (OesApi_GetClEnvId)'
 * @version 0.15.5.1    2017/11/17
 *          - 增加 OesApi_IsValidOrdChannel、OesApi_IsValidRptChannel 等介面, 用於判斷通道是否已經連線且有效
 * @version 0.15.5.2    2018/01/29
 *          - 增加 OesApi_GetLastRecvTime、OesApi_GetLastSendTime 介面，用於獲取通道最新發送/接受訊息的時間
 *          - 登入失敗時, 可以通過 errno/SPK_GET_ERRNO() 獲取到具體失敗原因
 * @version 0.15.5.11_u2 2018/11/04
 *          - 新增從成交回報中提取和生成委託回報資訊的輔助函式
 * @version 0.15.5.14   2018/08/01
 *          - 增加 OesApi_HasMoreCachedData 介面, 用於返回已經接收到但尚未被回撥函式處理的快取資料長度
 *          - '登入應答報文(OesLogonRspT)' 結構體中增加欄位:
 *              - 客戶端型別 (clientType)
 *              - 客戶端狀態 (clientStatus)
 *          - 增加設定當前執行緒登入使用者名稱/登入密碼/客戶端環境號的介面
 *              - OesApi_SetThreadUsername
 *              - OesApi_SetThreadPassword
 *              - OesApi_SetThreadEnvId
 *          - 增加返回最近一次API呼叫失敗的錯誤號的介面
 *              - OesApi_GetLastError
 *          - '成交查詢應答報文(OesQryTrdRspT)' 和 '成交回報應答報文(OesTrdCnfmT)' 結構體中增加欄位:
 *              - 證券子型別 (subSecurityType)
 * @version 0.15.5.16   2018/08/31
 *          - 增加 '獲取客戶端總覽資訊 (OesApi_GetClientOverview)' 介面
 *          - 增加 '查詢主櫃資金資訊 (OesApi_QueryCounterCash)' 介面
 *          - 調整 '出入金委託請求 (OesApi_SendFundTransferReq)' 介面, 增加支援僅主櫃和銀行間的銀證轉賬
 *          - '客戶資金資訊(OesCashAssetItemT)' 結構中增加欄位:
 *              - 是否禁止出入金 (isFundTrsfDisabled)
 *          - '證券賬戶資訊(OesInvAcctItemT)' 結構中增加欄位:
 *              - 是否禁止交易 (isTradeDisabled)
 * @version 0.15.6      2018/08/01
 *          - 增加 OesApi_HasMoreCachedData 介面, 用於返回已經接收到但尚未被回撥函式處理的快取資料長度
 *          - 增加修改客戶端登入密碼介面 (OesApi_SendChangePasswordReq)
 *          - 增加設定當前執行緒登入使用者名稱/登入密碼/客戶端環境號的介面
 *              - OesApi_SetThreadUsername
 *              - OesApi_SetThreadPassword
 *              - OesApi_SetThreadEnvId
 *          - 增加批量委託介面 (以批量的形式同時傳送多筆委託申報)
 *              - OesApi_SendBatchOrdersReq
 *              - OesApi_SendBatchOrdersReq2
 *          - 增加設定當前執行緒的API錯誤號 (OesApi_SetLastError)
 *          - 增加返回當前執行緒最近一次API呼叫失敗的錯誤號 (OesApi_GetLastError)
 *          - 新增 ‘市場狀態資訊查詢(OesApi_QueryMarketState)’ 介面，此介面獲取到的
 *            市場狀態資訊型別定義為 ‘OesMarketStateItemT’
 *          - 增加設定/獲取客戶端自定義的裝置序列號的介面
 *              - OesApi_SetCustomizedDriverId
 *              - OesApi_GetCustomizedDriverId
 *          - 查詢現貨產品資訊介面的過濾條件變更:
 *              - 增加 ‘證券類別(securityType)’ 條件
 *              - 增加 ‘證券子類別(subSecurityType)’ 條件
 *          - '登入應答報文(OesLogonRspT)' 結構體中增加欄位:
 *              - 客戶端型別 (clientType)
 *              - 客戶端狀態 (clientStatus)
 *          - 增加返回最近一次API呼叫失敗的錯誤號的介面
 *              - OesApi_GetLastError
 *          - '成交查詢應答報文(OesQryTrdRspT)' 和 '成交回報應答報文(OesTrdCnfmT)' 結構體中增加欄位:
 *              - 證券子型別 (subSecurityType)
 * @version 0.15.7.4    2018/08/15
 *          - 增加 '獲取客戶端總覽資訊 (OesApi_GetClientOverview)' 介面
 *          - 增加 '查詢主櫃資金資訊 (OesApi_QueryCounterCash)' 介面
 *          - 調整 '出入金委託請求 (OesApi_SendFundTransferReq)' 介面, 增加支援僅主櫃和銀行間出入金
 *          - '客戶資金資訊(OesCashAssetItemT)' 結構中增加欄位:
 *              - 是否禁止出入金 (isFundTrsfDisabled)
 *          - '證券賬戶資訊(OesInvAcctItemT)' 結構中增加欄位:
 *              - 是否禁止交易 (isTradeDisabled)
 * @version 0.15.7.6    2018/11/03
 *          - '買賣型別(eOesBuySellTypeT)' 中新增:
 *              - 配股認購 (OES_BS_TYPE_ALLOTMENT)
 *          - 新增 '產品型別 (eOesProductTypeT)' 定義, 作為產品和持倉的高層類別定義
 *          - 在以下結構體中增加 '產品型別 (productType)' 欄位
 *              - 證券資訊(OesStockBaseInfoT/OesStockItemT)
 *              - 證券發行資訊 (OesIssueBaseInfoT/OesIssueItemT)
 *              - 股票持倉資訊 (OesStkHoldingBaseInfoT/OesStkHoldingItemT)
 *              - 委託回報 (OesOrdCnfmT/OesOrdItemT)
 *              - 成交回報 (OesTrdCnfmT/OesTrdItemT)
 *          - 查詢證券發行產品資訊介面(OesApi_QueryIssue)的過濾條件中增加:
 *              - ‘產品型別(productType)’ 條件
 *          - 查詢股票持倉資訊介面(OesApi_QueryStkHolding)的過濾條件中增加:
 *              - ‘產品型別(productType)’ 條件
 *          - '證券子型別(eOesSubSecurityTypeT)'中新增:
 *              - 滬倫通CDR本地交易業務產品(OES_SUB_SECURITY_TYPE_STOCK_HLTCDR)
 * @version 0.15.7.6_RC2 2018/11/22
 *          - 增加 OesApi_InitAllByCfgStruct 介面 (InitAll 的過載方法)
 *          - 增加 OesApi_RecvReportMsg 介面 (一次只接收一條回報訊息)
 *          - 增加設定/獲取當前執行緒訂閱回報使用的客戶端環境號的介面
 *              - OesApi_SetThreadSubscribeEnvId
 *              - OesApi_GetThreadSubscribeEnvId
 * @version 0.15.9_I9   2019/4/15
 *          - 重新實現登入介面 (介面OesApi_Logon)
 *              - 增強安全性處理
 * @since   2016/03/04
 */


#ifndef _OES_API_H
#define _OES_API_H


#include    <oes_global/oes_packets.h>
#include    <oes_api/errors/oes_errors.h>
#include    <sutil/net/spk_general_client_define.h>
#include    <sutil/platform/spk_platforms.h>

/* 為了方便外部使用而額外引入的標頭檔案 *
#include    <sutil/time/spk_times.h>
#include    <sutil/logger/spk_log.h>
*/


#ifdef __cplusplus
extern "C" {
#endif


/* ===================================================================
 * 常量定義
 * =================================================================== */

/** 預設的主配置區段名稱 */
#define OESAPI_CFG_DEFAULT_SECTION              "oes_client"
/** 預設的日誌配置區段名稱 */
#define OESAPI_CFG_DEFAULT_SECTION_LOGGER       "log"
/** 預設的委託申報配置項名稱 */
#define OESAPI_CFG_DEFAULT_KEY_ORD_ADDR         "ordServer"
/** 預設的執行報告配置項名稱 */
#define OESAPI_CFG_DEFAULT_KEY_RPT_ADDR         "rptServer"
/** 預設的查詢服務配置項名稱 */
#define OESAPI_CFG_DEFAULT_KEY_QRY_ADDR         "qryServer"
/** 預設的訊息型別列表等字串分隔符 */
#define OESAPI_DEFAULT_STRING_DELIM             ",;| \t\r\n"
/* -------------------------           */


/* ===================================================================
 * 常量定義, 列舉型別定義
 * =================================================================== */

/**
 * 通道型別定義
 */
typedef enum _eOesApiChannelType {
    OESAPI_CHANNEL_TYPE_ORDER       = 1,        /**< 委託申報通道 */
    OESAPI_CHANNEL_TYPE_REPORT      = 2,        /**< 回報通道 */
    OESAPI_CHANNEL_TYPE_QUERY       = 3         /**< 查詢通道 */
} eOesApiChannelTypeT;
/* -------------------------           */


/* ===================================================================
 * 結構體定義
 * =================================================================== */

/**
 * 客戶端會話資訊（連線通道資訊）定義
 */
typedef SGeneralClientChannelT      OesApiSessionInfoT;


/* 結構體的初始化值定義 */
#define NULLOBJ_OESAPI_SESSION_INFO             \
        NULLOBJ_GENERAL_CLIENT_CHANNEL
/* -------------------------           */


/**
 * 客戶端會話的連線通道組定義（多個連線通道的集合）
 */
typedef SGeneralClientChannelGroupT OesApiChannelGroupT;


/* 結構體的初始化值定義 */
#define NULLOBJ_OESAPI_CHANNEL_GROUP            \
        NULLOBJ_GENERAL_CLIENT_CHANNEL_GROUP
/* -------------------------           */


/**
 * Socket URI地址資訊
 */
typedef SGeneralClientAddrInfoT     OesApiAddrInfoT;


/* 結構體初始化值定義 */
#define NULLOBJ_OESAPI_ADDR_INFO                \
        NULLOBJ_GENERAL_CLIENT_ADDR_INFO
/* -------------------------           */


/**
 * 遠端主機配置資訊
 */
typedef SGeneralClientRemoteCfgT    OesApiRemoteCfgT;


/* 結構體的初始化值定義 */
#define NULLOBJ_OESAPI_REMOTE_CFG               \
        NULLOBJ_GENERAL_CLIENT_REMOTE_CFG
/* -------------------------           */


/**
 * 回報訂閱的訂閱引數資訊
 */
typedef struct _OesApiSubscribeInfo {
    /**
     * 待訂閱的客戶端環境號
     * - 大於0, 區分環境號, 僅訂閱環境號對應的回報資料
     * - 小於等於0, 不區分環境號, 訂閱該客戶下的所有回報資料
     */
    int8                    clEnvId;

    /** 按64位對齊的填充域 */
    uint8                   __filler[3];

    /**
     * 待訂閱的回報訊息種類
     * - 0:      預設回報 (等價於: 0x01,0x02,0x04,0x08,0x10,0x20,0x40)
     * - 0x0001: OES業務拒絕 (未通過風控檢查等)
     * - 0x0002: OES委託已生成 (已通過風控檢查)
     * - 0x0004: 交易所委託回報 (包括交易所委託拒絕、委託確認和撤單完成通知)
     * - 0x0008: 交易所成交回報
     * - 0x0010: 出入金委託執行報告 (包括出入金委託拒絕、出入金委託回報)
     * - 0x0020: 資金變動資訊
     * - 0x0040: 持倉變動資訊
     * - 0x0080: 市場狀態資訊
     * - 0xFFFF: 所有回報
     *
     * @see eOesSubscribeReportTypeT
     */
    int32                   rptTypes;
} OesApiSubscribeInfoT;


/* 結構體的初始化值定義 */
#define NULLOBJ_OESAPI_SUBSCRIBE_INFO           \
        0, {0}, 0
/* -------------------------           */


/**
 * 完整的OES客戶端配置資訊
 */
typedef struct _OesApiClientCfg {
    OesApiRemoteCfgT        ordChannelCfg;      /**< 委託服務配置 */
    OesApiRemoteCfgT        rptChannelCfg;      /**< 回報服務配置 */
    OesApiRemoteCfgT        qryChannelCfg;      /**< 查詢服務配置 */
    OesApiSubscribeInfoT    subscribeInfo;      /**< 回報訂閱引數 */
} OesApiClientCfgT;


/* 結構體的初始化值定義 */
#define NULLOBJ_OESAPI_CLIENT_CFG               \
        {NULLOBJ_OESAPI_REMOTE_CFG}, \
        {NULLOBJ_OESAPI_REMOTE_CFG}, \
        {NULLOBJ_OESAPI_REMOTE_CFG}, \
        {NULLOBJ_OESAPI_SUBSCRIBE_INFO}
/* -------------------------           */


/**
 * OES客戶端執行時環境
 */
typedef struct _OesApiClientEnv {
    OesApiSessionInfoT      ordChannel;         /**< 委託通道的會話資訊 */
    OesApiSessionInfoT      rptChannel;         /**< 回報通道的會話資訊 */
    OesApiSessionInfoT      qryChannel;         /**< 查詢通道的會話資訊 */
} OesApiClientEnvT;


/* 結構體初始化值定義 */
#define NULLOBJ_OESAPI_CLIENT_ENV               \
        {NULLOBJ_OESAPI_SESSION_INFO}, \
        {NULLOBJ_OESAPI_SESSION_INFO}, \
        {NULLOBJ_OESAPI_SESSION_INFO}
/* -------------------------           */


/* ===================================================================
 * 回撥函式的函式原型定義
 * =================================================================== */

/**
 * 回報訊息處理對應的回撥函式的函式原型定義
 *
 * @param   pSessionInfo        會話資訊
 * @param   pMsgHead            訊息頭
 * @param   pMsgBody            訊息體資料
 * @param   pCallbackParams     外部傳入的引數
 * @return  大於等於0，成功；小於0，失敗（錯誤號）
 *
 * @see     eOesMsgTypeT
 */
typedef int32   (*F_OESAPI_ON_RPT_MSG_T) (
                OesApiSessionInfoT *pSessionInfo,
                SMsgHeadT *pMsgHead,
                void *pMsgBody,
                void *pCallbackParams);
/* -------------------------           */


/**
 * 查詢訊息處理對應的回撥函式的函式原型定義
 *
 * @param   pSessionInfo        會話資訊
 * @param   pMsgHead            訊息頭
 * @param   pMsgBody            訊息體資料
 * @param   pQryCursor          指示查詢進度的遊標
 * @param   pCallbackParams     外部傳入的引數
 * @return  大於等於0，成功；小於0，失敗（錯誤號）
 *
 * @see     eOesMsgTypeT
 */
typedef int32   (*F_OESAPI_ON_QRY_MSG_T) (
                OesApiSessionInfoT *pSessionInfo,
                SMsgHeadT *pMsgHead,
                void *pMsgBody,
                OesQryCursorT *pQryCursor,
                void *pCallbackParams);
/* -------------------------           */


/* ===================================================================
 * 委託申報介面
 * =================================================================== */

/*
 * 傳送委託申報請求
 * 以單向非同步訊息的方式傳送委託申報到OES伺服器, OES的實時風控檢查等處理結果將通過回報資料返回
 *
 * - 關於"客戶委託流水號(clSeqNo)"
 *   - 在0.11之前的版本中，"客戶委託流水號" 是由客戶端維護的線性遞增序列，用於標識委託資料的
 *     唯一性，並防止重複申報
 *   - 從0.11版本開始，不再強制要求線性遞增，只要維持在同一客戶端下的唯一性即可
 *   - 客戶端可以通過登入後的會話資訊中的 lastOutMsgSeq 欄位獲取到其最後傳送到OES伺服器的
 *     "客戶委託流水號"
 *   - 當通過撤單請求介面進行撤單時, 可以直接通過待撤訂單的 "客戶委託流水號(clSeqNo)" 進行撤單
 *   - 此外, 當需要同時建立多個委託通道報單時, 可以通過 "客戶端環境號(clEnvId)" 對區分不同的
 *     委託通道, "客戶委託流水號(clSeqNo)" 只要在相同的 "客戶端環境號(clEnvId)" 下唯一即可
 *
 * - 關於"原始訂單的客戶訂單編號(origClOrdId)"
 *   - "客戶訂單編號(clOrdId)", 是由OES伺服器端維護的、在OES內具有唯一性的內部委託編號,
 *     該編號會通過回報資料返回客戶端
 *   - 當通過撤單請求介面進行撤單時, 可以通過待撤訂單的 "客戶委託流水號(clSeqNo)" 或者
 *     "客戶訂單編號(clOrdId)" 進行撤單
 *
 * @param       pOrdChannel     委託通道的會話資訊
 * @param       pOrdReq         待發送的委託申報請求
 * @retval      0               成功
 * @retval      <0              失敗 (負的錯誤號)
 *
 * @exception   NEG(EPIPE)      連線已破裂
 * @exception   Others          由send()系統呼叫返回的錯誤
 */
int32   OesApi_SendOrderReq(
                OesApiSessionInfoT *pOrdChannel,
                const OesOrdReqT *pOrdReq);

/*
 * 傳送撤單請求
 * 以單向非同步訊息的方式傳送委託申報到OES伺服器, OES的實時風控檢查等處理結果將通過回報資料返回
 *
 * - 關於"客戶委託流水號(clSeqNo)"
 *   - 在0.11之前的版本中，"客戶委託流水號" 是由客戶端維護的線性遞增序列，用於標識委託資料的
 *     唯一性，並防止重複申報
 *   - 從0.11版本開始，不再強制要求線性遞增，只要維持在同一客戶端下的唯一性即可
 *   - 客戶端可以通過登入後的會話資訊中的 lastOutMsgSeq 欄位獲取到其最後傳送到OES伺服器的
 *     "客戶委託流水號"
 *   - 當通過撤單請求介面進行撤單時, 可以直接通過待撤訂單的 "客戶委託流水號(clSeqNo)" 進行撤單
 *   - 此外, 當需要同時建立多個委託通道報單時, 可以通過 "客戶端環境號(clEnvId)" 對區分不同的
 *     委託通道, "客戶委託流水號(clSeqNo)" 只要在相同的 "客戶端環境號(clEnvId)" 下唯一即可
 *
 * - 關於"原始訂單的客戶訂單編號(origClOrdId)"
 *   - "客戶訂單編號(clOrdId)", 是由OES伺服器端維護的、在OES內具有唯一性的內部委託編號,
 *     該編號會通過回報資料返回客戶端
 *   - 當通過撤單請求介面進行撤單時, 可以通過待撤訂單的 "客戶委託流水號(clSeqNo)" 或者
 *     "客戶訂單編號(clOrdId)" 進行撤單
 *
 * @param       pOrdChannel     查詢通道的會話資訊
 * @param       pCancelReq      待發送的撤單請求
 * @retval      0               成功
 * @retval      <0              失敗 (負的錯誤號)
 *
 * @exception   NEG(EPIPE)      連線已破裂
 * @exception   Others          由send()系統呼叫返回的錯誤
 */
int32   OesApi_SendOrderCancelReq(
                OesApiSessionInfoT *pOrdChannel,
                const OesOrdCancelReqT *pCancelReq);

/*
 * 批量傳送多條委託請求
 * 以批量的形式同時傳送多筆委託申報, 而風控檢查等處理結果則仍以單筆委託為單位通過回報資料返回
 *
 * - 批量委託的委託請求填充規則與單條委託完全相同, 回報處理規則也與單條委託完全相同:
 *   - 每筆委託請求的 "客戶委託流水號(clSeqNo)" 同樣必須填充, 並需要維持在同一客戶端下的唯一性
 *   - 伺服器端的處理結果則仍將以單筆委託為單位通過回報資料返回
 *
 * @param       pOrdChannel     委託通道的會話資訊
 * @param       ppOrdPtrList    待發送的委託請求列表 (指標陣列)
 * @param       ordCount        待發送的委託請求數量
 * @retval      0               成功
 * @retval      <0              失敗 (負的錯誤號)
 *
 * @exception   NEG(EINVAL)     傳入引數非法
 * @exception   NEG(EPIPE)      連線已破裂
 * @exception   NEG(Others)     由send()系統呼叫返回的錯誤
 * @exception   Others          由send()系統呼叫返回的錯誤
 */
int32   OesApi_SendBatchOrdersReq(
                OesApiSessionInfoT *pOrdChannel,
                const OesOrdReqT *ppOrdPtrList[],
                int32 ordCount);

/*
 * 批量傳送多條委託請求
 * 以批量的形式同時傳送多筆委託申報, 而風控檢查等處理結果則仍以單筆委託為單位通過回報資料返回
 *
 * - 批量委託的委託請求填充規則與單條委託完全相同, 回報處理規則也與單條委託完全相同:
 *   - 每筆委託請求的 "客戶委託流水號(clSeqNo)" 同樣必須填充, 並需要維持在同一客戶端下的唯一性
 *   - 伺服器端的處理結果則仍將以單筆委託為單位通過回報資料返回
 *
 * @param       pOrdChannel     委託通道的會話資訊
 * @param       pOrdReqArray    待發送的委託請求陣列 (連續的儲存空間)
 * @param       ordCount        待發送的委託請求數量
 * @retval      0               成功
 * @retval      <0              失敗 (負的錯誤號)
 *
 * @exception   NEG(EINVAL)     傳入引數非法
 * @exception   NEG(EPIPE)      連線已破裂
 * @exception   NEG(Others)     由send()系統呼叫返回的錯誤
 * @exception   Others          由send()系統呼叫返回的錯誤
 */
int32   OesApi_SendBatchOrdersReq2(
                OesApiSessionInfoT *pOrdChannel,
                OesOrdReqT *pOrdReqArray,
                int32 ordCount);

/*
 * 傳送出入金委託請求
 * 以單向非同步訊息的方式傳送委託申報到OES伺服器, OES的實時風控檢查等處理結果將通過回報資料返回
 *
 * - 關於"客戶委託流水號(clSeqNo)"
 *   - 在0.11之前的版本中，“客戶委託流水號”是由客戶端維護的線性遞增序列，用於標識委託資料的
 *     唯一性，並防止重複申報
 *   - 從0.11版本開始，不再強制要求線性遞增，只要維持在同一客戶端下的唯一性即可
 *   - 客戶端可以通過登入後的會話資訊中的 lastOutMsgSeq 欄位獲取到其最後傳送到OES伺服器的
 *     "客戶委託流水號"
 *
 * @param       pOrdChannel     委託通道的會話資訊
 * @param       pFundTrsfReq    待發送的出入金委託請求
 * @retval      0               成功
 * @retval      <0              失敗 (負的錯誤號)
 *
 * @exception   NEG(EPIPE)      連線已破裂
 * @exception   Others          由send()系統呼叫返回的錯誤
 */
int32   OesApi_SendFundTransferReq(
                OesApiSessionInfoT *pOrdChannel,
                const OesFundTrsfReqT *pFundTrsfReq);

/*
 * 傳送密碼修改請求 (修改客戶端登入密碼)
 * 密碼修改請求將通過委託通道傳送到OES伺服器, 並將採用同步請求/應答的方式直接返回處理結果
 *
 * @param       pOrdChannel     委託通道會話資訊
 * @param[in]   pChangePasswordReq
 *                              待發送的密碼修改請求
 * @param[out]  pOutChangePasswordRsp
 *                              用於輸出測試請求應答的快取區
 * @retval      0               成功
 * @retval      <0              API呼叫失敗 (負的錯誤號)
 * @retval      >0              服務端業務處理失敗 (OES錯誤號)
 *
 * @exception   NEG(EINVAL)     傳入引數非法
 * @exception   NEG(EPIPE)      連線已破裂
 * @exception   NEG(Others)     由send()系統呼叫返回的錯誤
 */
int32   OesApi_SendChangePasswordReq(
                OesApiSessionInfoT *pOrdChannel,
                const OesChangePasswordReqT *pChangePasswordReq,
                OesChangePasswordRspT *pOutChangePasswordRsp);
/* -------------------------           */


/* ===================================================================
 * 執行報告介面
 * =================================================================== */

/*
 * 等待回報訊息到達，並通過回撥函式進行訊息處理
 *
 * @param       pRptChannel     會話資訊
 * @param       timeoutMs       超時時間(毫秒)
 * @param       pRptMsgCallback 進行訊息處理的回撥函式
 *                              - 訊息體的資料型別為 <code>OesRptMsgT</code>
 * @param       pCallbackParams 回撥函式的引數
 * @retval      >=0             成功 (返回回撥函式的返回值)
 * @retval      <0              失敗 (負的錯誤號)
 * @exception   NEG(ETIMEDOUT)  超時
 * @exception   NEG(EPIPE)      連線已破裂
 * @exception   Others          由read()系統呼叫或回撥函式pOnMsgCallback返回的錯誤
 *
 * @see         OesRptMsgT
 * @see         eOesMsgTypeT
 * @see         F_OESAPI_ON_RPT_MSG_T
 */
int32   OesApi_WaitReportMsg(
                OesApiSessionInfoT *pRptChannel,
                int32 timeoutMs,
                F_OESAPI_ON_RPT_MSG_T pRptMsgCallback,
                void *pCallbackParams);

/*
 * 接收(一條)回報訊息
 * 阻塞等待直到完整的接收到一條回報訊息或者到達超時時間
 *
 * @param       pRptChannel     會話資訊
 * @param[out]  pOutMsgHead     訊息頭快取
 * @param[out]  pOutMsgBody     訊息體資料快取
 * @param       bufSize         訊息體資料快取區的大小
 * @param       timeoutMs       超時時間(毫秒)
 * @return      大於等於0，訊息體資料長度; 小於0，錯誤號
 */
int32   OesApi_RecvReportMsg(
                OesApiSessionInfoT *pRptChannel,
                SMsgHeadT *pOutMsgHead,
                OesRspMsgBodyT *pOutMsgBody,
                int32 bufSize,
                int32 timeoutMs);
/* -------------------------           */


/* ===================================================================
 * 查詢介面
 * =================================================================== */

/*
 * 獲取API的發行版本號
 *
 * @retval  API的發行版本號 (如: "0.15.3")
 */
const char *
        OesApi_GetApiVersion();

/*
 * 獲取當前交易日
 *
 * @param   pQryChannel         查詢通道的會話資訊
 * @retval  >=0                 當前交易日 (格式：YYYYMMDD)
 * @retval  <0                  失敗 (負的錯誤號)
 */
int32   OesApi_GetTradingDay(
                OesApiSessionInfoT *pQryChannel);

/*
 * 獲取客戶端總覽資訊
 *
 * @param       pQryChannel     查詢通道的會話資訊
 * @param[out]  pClientOverview 查詢到的客戶端總覽資訊
 * @retval  =0                  查詢成功
 * @retval  <0                  失敗 (負的錯誤號)
 */
int32   OesApi_GetClientOverview(
                OesApiSessionInfoT *pQryChannel,
                OesClientOverviewT *pClientOverview);

/*
 * 查詢單條委託資訊
 *
 * @param       pQryChannel     查詢通道的會話資訊
 * @param       clSeqNo         委託流水號
 * @param[out]  pOrdItem        查詢到的委託資訊
 * @retval      =0              查詢成功
 * @retval      <0              查詢失敗 (負的錯誤號)
 *
 * @see         OesOrdItemT
 */
int32   OesApi_QuerySingleOrder(
                OesApiSessionInfoT *pQryChannel,
                int32 clSeqNo,
                OesOrdItemT *pOrdItem);

/*
 * 查詢單條資金資訊
 *
 * @param       pQryChannel     查詢通道的會話資訊
 * @param       pCashAcctId     資金賬號
 * @param[out]  pCashAssetItem  查詢到的資金資訊
 * @retval      =0              查詢成功
 * @retval      <0              查詢失敗 (負的錯誤號)
 *
 * @see         OesCashAssetItemT
 */
int32   OesApi_QuerySingleCashAsset(
                OesApiSessionInfoT *pQryChannel,
                const char *pCashAcctId,
                OesCashAssetItemT *pCashAssetItem);

/*
 * 查詢單條股票持倉資訊
 *
 * @param       pQryChannel     查詢通道的會話資訊
 * @param       pInvAcctId      股東賬號
 * @param       pSecurityId     證券程式碼
 * @param[out]  pHoldingItem    查詢到的持倉資訊
 * @retval      =0              查詢成功
 * @retval      <0              查詢失敗 (負的錯誤號)
 *
 * @see         OesStkHoldingItemT
 */
int32   OesApi_QuerySingleStkHolding(
                OesApiSessionInfoT *pQryChannel,
                const char *pInvAcctId,
                const char *pSecurityId,
                OesStkHoldingItemT *pHoldingItem);

/*
 * 查詢單條期權持倉資訊
 *
 * @param       pQryChannel     查詢通道的會話資訊
 * @param       pInvAcctId      股東賬號
 * @param       pSecurityId     證券程式碼
 * @param[out]  pHoldingItem    查詢到的持倉資訊
 * @retval      =0              查詢成功
 * @retval      <0              查詢失敗 (負的錯誤號)
 *
 * @see         OesOptHoldingItemT
 */
int32   OesApi_QuerySingleOptHolding(
                OesApiSessionInfoT *pQryChannel,
                const char *pInvAcctId,
                const char *pSecurityId,
                OesOptHoldingItemT *pHoldingItem);

/*
 * 查詢所有委託資訊
 *
 * @param   pQryChannel         查詢通道的會話資訊
 * @param   pQryFilter          查詢過濾條件
 *                              - 傳空指標或者將過濾條件初始化為0，將查詢當前客戶下所有資料
 * @param   pQryMsgCallback     進行訊息處理的回撥函式
 *                              - 訊息體的資料型別為 <code>OesOrdItemT</code>
 * @param   pCallbackParams     回撥函式的引數
 * @retval  >=0                 成功查詢到的記錄數
 * @retval  <0                  失敗 (負的錯誤號)
 *
 * @see     OesOrdItemT
 */
int32   OesApi_QueryOrder(
                OesApiSessionInfoT *pQryChannel,
                const OesQryOrdFilterT *pQryFilter,
                F_OESAPI_ON_QRY_MSG_T pQryMsgCallback,
                void *pCallbackParams);

/*
 * 查詢成交資訊
 *
 * @param   pQryChannel         查詢通道的會話資訊
 * @param   pQryFilter          查詢過濾條件
 *                              - 傳空指標或者將過濾條件初始化為0，將查詢當前客戶下所有資料
 * @param   pQryMsgCallback     進行訊息處理的回撥函式
 *                              - 訊息體的資料型別為 <code>OesTrdItemT</code>
 * @param   pCallbackParams     回撥函式的引數
 * @retval  >=0                 成功查詢到的記錄數
 * @retval  <0                  失敗 (負的錯誤號)
 *
 * @see     OesTrdItemT
 */
int32   OesApi_QueryTrade(
                OesApiSessionInfoT *pQryChannel,
                const OesQryTrdFilterT *pQryFilter,
                F_OESAPI_ON_QRY_MSG_T pQryMsgCallback,
                void *pCallbackParams);

/*
 * 查詢客戶資金資訊
 *
 * @param   pQryChannel         查詢通道的會話資訊
 * @param   pQryFilter          查詢過濾條件
 *                              - 傳空指標或者將過濾條件初始化為0，將查詢當前客戶下所有資料
 * @param   pQryMsgCallback     進行訊息處理的回撥函式
 *                              - 訊息體的資料型別為 <code>OesCashAssetItemT</code>
 * @param   pCallbackParams     回撥函式的引數
 * @retval  >=0                 成功查詢到的記錄數
 * @retval  <0                  失敗 (負的錯誤號)
 *
 * @see     OesCashAssetItemT
 */
int32   OesApi_QueryCashAsset(
                OesApiSessionInfoT *pQryChannel,
                const OesQryCashAssetFilterT *pQryFilter,
                F_OESAPI_ON_QRY_MSG_T pQryMsgCallback,
                void *pCallbackParams);

/*
 * 查詢股票持倉資訊
 *
 * @param   pQryChannel         查詢通道的會話資訊
 * @param   pQryFilter          查詢過濾條件
 *                              - 傳空指標或者將過濾條件初始化為0，將查詢當前客戶下所有資料
 * @param   pQryMsgCallback     進行訊息處理的回撥函式
 *                              - 訊息體的資料型別為 <code>OesStkHoldingItemT</code>
 * @param   pCallbackParams     回撥函式的引數
 * @retval  >=0                 成功查詢到的記錄數
 * @retval  <0                  失敗 (負的錯誤號)
 *
 * @see     OesStkHoldingItemT
 */
int32   OesApi_QueryStkHolding(
                OesApiSessionInfoT *pQryChannel,
                const OesQryStkHoldingFilterT *pQryFilter,
                F_OESAPI_ON_QRY_MSG_T pQryMsgCallback,
                void *pCallbackParams);

/*
 * 查詢期權持倉資訊
 *
 * @param   pQryChannel         查詢通道的會話資訊
 * @param   pQryFilter          查詢過濾條件
 *                              - 傳空指標或者將過濾條件初始化為0，將查詢當前客戶下所有資料
 * @param   pQryMsgCallback     進行訊息處理的回撥函式
 *                              - 訊息體的資料型別為 <code>OesOptHoldingItemT</code>
 * @param   pCallbackParams     回撥函式的引數
 * @retval  >=0                 成功查詢到的記錄數
 * @retval  <0                  失敗 (負的錯誤號)
 *
 * @see     OesOptHoldingItemT
 */
int32   OesApi_QueryOptHolding(
                OesApiSessionInfoT *pQryChannel,
                const OesQryOptHoldingFilterT *pQryFilter,
                F_OESAPI_ON_QRY_MSG_T pQryMsgCallback,
                void *pCallbackParams);

/*
 * 查詢新股配號、中籤資訊
 *
 * @param   pQryChannel         查詢通道的會話資訊
 * @param   pQryFilter          查詢過濾條件
 *                              - 傳空指標或者將過濾條件初始化為0，將查詢當前客戶下所有資料
 * @param   pQryMsgCallback     進行訊息處理的回撥函式
 *                              - 訊息體的資料型別為 <code>OesLotWinningItemT</code>
 * @param   pCallbackParams     回撥函式的引數
 * @retval  >=0                 成功查詢到的記錄數
 * @retval  <0                  失敗 (負的錯誤號)
 *
 * @see     OesLotWinningItemT
 */
int32   OesApi_QueryLotWinning(
                OesApiSessionInfoT *pQryChannel,
                const OesQryLotWinningFilterT *pQryFilter,
                F_OESAPI_ON_QRY_MSG_T pQryMsgCallback,
                void *pCallbackParams);

/*
 * 查詢客戶資訊
 *
 * @param   pQryChannel         查詢通道的會話資訊
 * @param   pQryFilter          查詢過濾條件
 *                              - 傳空指標或者將過濾條件初始化為0，將查詢當前客戶下所有資料
 * @param   pQryMsgCallback     進行訊息處理的回撥函式
 *                              - 訊息體的資料型別為 <code>OesCustItemT</code>
 * @param   pCallbackParams     回撥函式的引數
 * @retval  >=0                 成功查詢到的記錄數
 * @retval  <0                  失敗 (負的錯誤號)
 *
 * @see     OesCustItemT
 */
int32   OesApi_QueryCustInfo(
                OesApiSessionInfoT *pQryChannel,
                const OesQryCustFilterT *pQryFilter,
                F_OESAPI_ON_QRY_MSG_T pQryMsgCallback,
                void *pCallbackParams);

/*
 * 查詢證券賬戶資訊
 *
 * @param   pQryChannel         查詢通道的會話資訊
 * @param   pQryFilter          查詢過濾條件
 *                              - 傳空指標或者將過濾條件初始化為0，將查詢當前客戶下所有資料
 * @param   pQryMsgCallback     進行訊息處理的回撥函式
 *                              - 訊息體的資料型別為 <code>OesInvAcctItemT</code>
 * @param   pCallbackParams     回撥函式的引數
 * @retval  >=0                 成功查詢到的記錄數
 * @retval  <0                  失敗 (負的錯誤號)
 *
 * @see     OesInvAcctItemT
 */
int32   OesApi_QueryInvAcct(
                OesApiSessionInfoT *pQryChannel,
                const OesQryInvAcctFilterT *pQryFilter,
                F_OESAPI_ON_QRY_MSG_T pQryMsgCallback,
                void *pCallbackParams);

/*
 * 查詢佣金資訊
 *
 * @param   pQryChannel         查詢通道的會話資訊
 * @param   pQryFilter          查詢過濾條件
 *                              - 傳空指標或者將過濾條件初始化為0，將查詢當前客戶下所有資料
 * @param   pQryMsgCallback     進行訊息處理的回撥函式
 *                              - 訊息體的資料型別為 <code>OesCommissionRateItemT</code>
 * @param   pCallbackParams     回撥函式的引數
 * @retval  >=0                 成功查詢到的記錄數
 * @retval  <0                  失敗 (負的錯誤號)
 *
 * @see     OesCommissionRateItemT
 */
int32   OesApi_QueryCommissionRate(
                OesApiSessionInfoT *pQryChannel,
                const OesQryCommissionRateFilterT *pQryFilter,
                F_OESAPI_ON_QRY_MSG_T pQryMsgCallback,
                void *pCallbackParams);

/*
 * 查詢出入金流水
 *
 * @param   pQryChannel         查詢通道的會話資訊
 * @param   pQryFilter          查詢過濾條件
 *                              - 傳空指標或者將過濾條件初始化為0，將查詢當前客戶下所有資料
 * @param   pQryMsgCallback     進行訊息處理的回撥函式
 *                              - 訊息體的資料型別為 <code>OesFundTransferSerialItemT</code>
 * @param   pCallbackParams     回撥函式的引數
 * @retval  >=0                 成功查詢到的記錄數
 * @retval  <0                  失敗 (負的錯誤號)
 *
 * @see     OesFundTransferSerialItemT
 */
int32   OesApi_QueryFundTransferSerial(
                OesApiSessionInfoT *pQryChannel,
                const OesQryFundTransferSerialFilterT *pQryFilter,
                F_OESAPI_ON_QRY_MSG_T pQryMsgCallback,
                void *pCallbackParams);

/*
 * 查詢證券發行產品資訊
 *
 * @param   pQryChannel         查詢通道的會話資訊
 * @param   pQryFilter          查詢過濾條件
 *                              - 傳空指標或者將過濾條件初始化為0，將查詢所有資料
 * @param   pQryMsgCallback     進行訊息處理的回撥函式
 *                              - 訊息體的資料型別為 <code>OesIssueItemT</code>
 * @param   pCallbackParams     回撥函式的引數
 * @retval  >=0                 成功查詢到的記錄數
 * @retval  <0                  失敗 (負的錯誤號)
 *
 * @see     OesIssueItemT
 */
int32   OesApi_QueryIssue(
                OesApiSessionInfoT *pQryChannel,
                const OesQryIssueFilterT *pQryFilter,
                F_OESAPI_ON_QRY_MSG_T pQryMsgCallback,
                void *pCallbackParams);

/*
 * 查詢現貨產品資訊
 *
 * @param   pQryChannel         查詢通道的會話資訊
 * @param   pQryFilter          查詢過濾條件
 *                              - 傳空指標或者將過濾條件初始化為0，將查詢所有資料
 * @param   pQryMsgCallback     進行訊息處理的回撥函式
 *                              - 訊息體的資料型別為 <code>OesStockItemT</code>
 * @param   pCallbackParams     回撥函式的引數
 * @retval  >=0                 成功查詢到的記錄數
 * @retval  <0                  失敗 (負的錯誤號)
 *
 * @see     OesStockItemT
 */
int32   OesApi_QueryStock(
                OesApiSessionInfoT *pQryChannel,
                const OesQryStockFilterT *pQryFilter,
                F_OESAPI_ON_QRY_MSG_T pQryMsgCallback,
                void *pCallbackParams);

/*
 * 查詢ETF申贖產品資訊
 *
 * @param   pQryChannel         查詢通道的會話資訊
 * @param   pQryFilter          查詢過濾條件
 *                              - 傳空指標或者將過濾條件初始化為0，將查詢所有資料
 * @param   pQryMsgCallback     進行訊息處理的回撥函式
 *                              - 實際的訊息體資料型別為 <code>OesEtfItemT</code>
 * @param   pCallbackParams     回撥函式的引數
 * @retval  >=0                 成功查詢到的記錄數
 * @retval  <0                  失敗 (負的錯誤號)
 *
 * @see     OesEtfItemT
 */
int32   OesApi_QueryEtf(
                OesApiSessionInfoT *pQryChannel,
                const OesQryEtfFilterT *pQryFilter,
                F_OESAPI_ON_QRY_MSG_T pQryMsgCallback,
                void *pCallbackParams);

/*
 * 查詢ETF成分股資訊
 *
 * @param   pQryChannel         查詢通道的會話資訊
 * @param   pQryFilter          查詢過濾條件
 *                              - 過濾條件中fundId引數必填
 * @param   pQryMsgCallback     進行訊息處理的回撥函式
 *                              - 訊息體的資料型別為 <code>OesEtfComponentItemT</code>
 * @param   pCallbackParams     回撥函式的引數
 * @retval  >=0                 成功查詢到的記錄數
 * @retval  <0                  失敗 (負的錯誤號)
 *
 * @see     OesEtfComponentItemT
 */
int32   OesApi_QueryEtfComponent(
                OesApiSessionInfoT *pQryChannel,
                const OesQryEtfComponentFilterT *pQryFilter,
                F_OESAPI_ON_QRY_MSG_T pQryMsgCallback,
                void *pCallbackParams);

/*
 * 查詢期權產品資訊
 *
 * @param   pQryChannel         查詢通道的會話資訊
 * @param   pQryFilter          查詢過濾條件
 *                              - 傳空指標或者將過濾條件初始化為0，將查詢所有資料
 * @param   pQryMsgCallback     進行訊息處理的回撥函式
 *                              - 訊息體的資料型別為 <code>OesOptionItemT</code>
 * @param   pCallbackParams     回撥函式的引數
 * @retval  >=0                 成功查詢到的記錄數
 * @retval  <0                  失敗 (負的錯誤號)
 *
 * @see     OesOptionItemT
 */
int32   OesApi_QueryOption(
                OesApiSessionInfoT *pQryChannel,
                const OesQryOptionFilterT *pQryFilter,
                F_OESAPI_ON_QRY_MSG_T pQryMsgCallback,
                void *pCallbackParams);

/*
 * 查詢市場狀態資訊
 *
 * @note    目前僅深圳交易所各個交易平臺的市場狀態資訊有效
 *
 * @param   pQryChannel         查詢通道的會話資訊
 * @param   pQryFilter          查詢過濾條件
 *                              - 傳空指標或者將過濾條件初始化為0，將查詢所有資料
 * @param   pQryMsgCallback     進行訊息處理的回撥函式
 *                              - 訊息體的資料型別為 <code>OesMarketStateItemT</code>
 * @param   pCallbackParams     回撥函式的引數
 * @retval  >=0                 成功查詢到的記錄數
 * @retval  <0                  失敗 (負的錯誤號)
 *
 * @see     OesMarketStateItemT
 */
int32   OesApi_QueryMarketState(
                OesApiSessionInfoT *pQryChannel,
                const OesQryMarketStateFilterT *pQryFilter,
                F_OESAPI_ON_QRY_MSG_T pQryMsgCallback,
                void *pCallbackParams);
/* -------------------------           */


/*
 * 查詢主櫃資金資訊
 *
 * @param       pQryChannel     查詢通道的會話資訊
 * @param       pCashAcctId     資金賬號
 * @param[out]  pCounterCashItem
 *                              查詢到的主櫃資金資訊
 * @retval      =0              查詢成功
 * @retval      <0              查詢失敗 (負的錯誤號)
 *
 * @see         OesCounterCashItemT
 */
int32   OesApi_QueryCounterCash(
                OesApiSessionInfoT *pQryChannel,
                const char *pCashAcctId,
                OesCounterCashItemT *pCounterCashItem);


/* ===================================================================
 * 基礎的會話管理函式宣告
 * =================================================================== */

/*
 * 連線並登入到指定的OES節點與服務
 *
 * - 關於"客戶委託流水號(clSeqNo)"
 *   - 在0.11之前的版本中，“客戶委託流水號”是由客戶端維護的線性遞增序列，用於標識委託資料的
 *     唯一性，並防止重複申報
 *   - 從0.11版本開始，不再強制要求線性遞增，只要維持在同一客戶端下的唯一性即可
 *   - 客戶端可以通過登入後的會話資訊中的 lastOutMsgSeq 欄位獲取到其最後傳送到OES伺服器的
 *     "客戶委託流水號"
 *
 * @param[out]  pOutSessionInfo 輸出會話資訊
 * @param       channelType     通道型別
 * @param       pUri            URI地址 (e.g. tcp://127.0.0.1:5100)
 * @param       pUsername       使用者名稱
 * @param       pPassword       密碼
 * @param       clEnvId         客戶端環境號
 *                              - 取值範圍為[0~99], [100~127]為保留區間, 客戶端應避免使用
 *                              - 小於0表示不指定, 將使用配置檔案或執行緒私有變數中設定的值
 * @param       heartBtInt      心跳間隔,單位為秒
 * @param       pSocketOptions  套接字引數 (為空, 則會使用預設引數)
 * @retval      TRUE            成功
 * @retval      FALSE           失敗。此時 errno 將被設定, 可以通過 errno/SPK_GET_ERRNO() 獲取到具體失敗原因
 *
 * @exception   EINVAL          配置異常或傳入引數非法
 * @exception   ECONNREFUSED    連線失敗
 * @exception   ETIMEDOUT       連線超時
 * @exception   EACCES          使用者名稱或密碼錯誤
 * @exception   EMLINK          連線數量超過限制
 * @exception   ESRCH           登入節點非主節點
 * @exception   EFAULT          其他業務錯誤
 */
BOOL    OesApi_Logon(
                OesApiSessionInfoT *pOutSessionInfo,
                eOesApiChannelTypeT channelType,
                const char *pUri,
                const char *pUsername,
                const char *pPassword,
                int8 clEnvId,
                int32 heartBtInt,
                const SSocketOptionConfigT *pSocketOptions);

/*
 * 連線並登入到OES服務叢集 (基於複製集的高可用叢集)
 *
 * - 關於地址列表:
 *   - 待解析的地址列表可是以空格、逗號或分號分割的地址列表字串
 *     - e.g. "tcp://127.0.0.1:5100, tcp://192.168.0.11:5100"
 *   - 同時也可以在每個地址之前，為其指定對應的主機編號
 *     - e.g. "2 tcp://192.168.0.12:5100, 1 tcp://192.168.0.11:5100,
 *             3 tcp://192.168.0.13:5100"
 *
 * @param[out]  pOutSessionInfo 輸出會話資訊
 * @param       channelType     通道型別
 * @param       pUriList        主機地址列表 (以空格、逗號或分號分割的地址列表字串)
 * @param       pUsername       使用者名稱
 * @param       pPassword       密碼
 * @param       clEnvId         客戶端環境號
 *                              - 取值範圍為[0~99], [100~127]為保留區間, 客戶端應避免使用
 *                              - 小於0表示不指定, 將使用配置檔案或執行緒私有變數中設定的值
 * @param       heartBtInt      心跳間隔,單位為秒
 * @param       pSocketOptions  套接字引數 (為空, 則會使用預設引數)
 * @retval      TRUE            成功
 * @retval      FALSE           失敗。此時 errno 將被設定, 可以通過 errno/SPK_GET_ERRNO() 獲取到具體失敗原因
 *
 * @exception   EINVAL          配置異常或傳入引數非法
 * @exception   ECONNREFUSED    連線失敗
 * @exception   ETIMEDOUT       連線超時
 * @exception   EACCES          使用者名稱或密碼錯誤
 * @exception   EMLINK          連線數量超過限制
 * @exception   ENOENT          地址列表中沒有找到有效的節點配置
 * @exception   ESRCH           登入節點非主節點
 * @exception   EFAULT          其他業務錯誤
 */
BOOL    OesApi_LogonReplicaSet(
                OesApiSessionInfoT *pOutSessionInfo,
                eOesApiChannelTypeT channelType,
                const char *pUriList,
                const char *pUsername,
                const char *pPassword,
                int8 clEnvId,
                int32 heartBtInt,
                const SSocketOptionConfigT *pSocketOptions);

/*
 * 連線並登入到OES服務叢集 (基於對等節點的服務叢集)
 *
 * - 關於地址列表:
 *   - 待解析的地址列表可是以空格、逗號或分號分割的地址列表字串
 *     - e.g. "tcp://127.0.0.1:5100, tcp://192.168.0.11:5100"
 *   - 同時也可以在每個地址之前，為其指定對應的主機編號
 *     - e.g. "2 tcp://192.168.0.12:5100, 1 tcp://192.168.0.11:5100,
 *             3 tcp://192.168.0.13:5100"
 *
 * @param[out]  pOutSessionInfo 輸出會話資訊
 * @param       channelType     通道型別
 * @param       pUriList        主機地址列表 (以空格、逗號或分號分割的地址列表字串)
 * @param       pUsername       使用者名稱
 * @param       pPassword       密碼
 * @param       clEnvId         客戶端環境號
 *                              - 取值範圍為[0~99], [100~127]為保留區間, 客戶端應避免使用
 *                              - 小於0表示不指定, 將使用配置檔案或執行緒私有變數中設定的值
 * @param       heartBtInt      心跳間隔,單位為秒
 * @param       pSocketOptions  套接字引數 (為空, 則會使用預設引數)
 * @retval      TRUE            成功
 * @retval      FALSE           失敗。此時 errno 將被設定, 可以通過 errno/SPK_GET_ERRNO() 獲取到具體失敗原因
 *
 * @exception   EINVAL          配置異常或傳入引數非法
 * @exception   ECONNREFUSED    連線失敗
 * @exception   ETIMEDOUT       連線超時
 * @exception   EACCES          使用者名稱或密碼錯誤
 * @exception   EMLINK          連線數量超過限制
 * @exception   ENOENT          地址列表中沒有找到有效的節點配置
 * @exception   ESRCH           登入節點非主節點
 * @exception   EFAULT          其他業務錯誤
 */
BOOL    OesApi_LogonPeerNodes(
                OesApiSessionInfoT *pOutSessionInfo,
                eOesApiChannelTypeT channelType,
                const char *pUriList,
                const char *pUsername,
                const char *pPassword,
                int8 clEnvId,
                int32 heartBtInt,
                const SSocketOptionConfigT *pSocketOptions);

/*
 * 傳送回報同步訊息
 *
 * @param   pRptChannel         會話資訊
 * @param   subscribeEnvId      待訂閱的客戶端環境號
 *                              - 大於0, 區分環境號, 僅訂閱環境號對應的回報資料
 *                              - 小於等於0, 不區分環境號, 訂閱該客戶下的所有回報資料
 * @param   subscribeRptTypes   待訂閱的回報訊息種類 (e.g.
 *                              OES_SUB_RPT_TYPE_ORDER_INSERT
 *                              | OES_SUB_RPT_TYPE_ORDER_REPORT
 *                              | OES_SUB_RPT_TYPE_TRADE_REPORT)
 *                              @see eOesSubscribeReportTypeT
 * @param   lastRptSeqNum       客戶端最後接收到的回報資料的回報編號
 *                              - 等於0, 從頭開始推送回報資料
 *                              - 大於0, 從指定的回報編號開始推送回報資料
 *                              - 小於0, 從最新的資料開始推送回報資料
 * @return  TRUE 成功; FALSE 失敗
 * @note    如果沒有收到該訊息, OES不會向客戶端傳送回報資料
 */
BOOL    OesApi_SendReportSynchronization(
                OesApiSessionInfoT *pRptChannel,
                int8 subscribeEnvId,
                int32 subscribeRptTypes,
                int64 lastRptSeqNum);

/*
 * 傳送心跳訊息
 *
 * @param   pSessionInfo    會話資訊
 * @return  TRUE 成功; FALSE 失敗
 */
BOOL    OesApi_SendHeartbeat(
                OesApiSessionInfoT *pSessionInfo);

/*
 * 傳送委託通道的測試請求訊息
 * 委託通道的測試請求訊息為同步的請求/應答訊息
 *
 * @param   pOrdChannel         委託通道會話資訊
 * @param   pTestReqId          測試請求識別符號 (C32, 可以為空)
 * @param   testReqIdSize       測試請求識別符號的長度
 * @return  TRUE 成功; FALSE 失敗
 */
BOOL    OesApi_TestOrdChannel(
                OesApiSessionInfoT *pOrdChannel,
                const char *pTestReqId,
                int32 testReqIdSize);

/*
 * 傳送委託通道的測試請求訊息
 * 委託通道的測試請求訊息為同步的請求/應答訊息
 *
 * @param       pOrdChannel     委託通道會話資訊
 * @param[in]   pTestReq        待發送的測試請求
 * @param[out]  pOutTestRsp     用於輸出測試請求應答的快取區
 * @return      TRUE 成功; FALSE 失敗
 */
BOOL    OesApi_TestOrdChannel2(
                OesApiSessionInfoT *pOrdChannel,
                OesTestRequestReqT *pTestReq,
                OesTestRequestRspT *pOutTestRsp);

/*
 * 傳送回報通道的測試請求訊息
 * 回報通道的測試請求訊息為非同步的請求/應答訊息
 *
 * @param   pRptChannel         回報通道會話資訊
 * @param   pTestReqId          測試請求識別符號 (C32, 可以為空)
 * @param   testReqIdSize       測試請求識別符號的長度
 * @return  TRUE 成功; FALSE 失敗
 */
BOOL    OesApi_TestRptChannel(
                OesApiSessionInfoT *pRptChannel,
                const char *pTestReqId,
                int32 testReqIdSize);

/*
 * 傳送回報通道的測試請求訊息
 * 回報通道的測試請求訊息為非同步的請求/應答訊息
 *
 * @param       pRptChannel     回報通道會話資訊
 * @param[in]   pTestReq        待發送的測試請求
 * @return      TRUE 成功; FALSE 失敗
 */
BOOL    OesApi_TestRptChannel2(
                OesApiSessionInfoT *pRptChannel,
                OesTestRequestReqT *pTestReq);

/*
 * 傳送登出訊息
 *
 * @param   pSessionInfo        會話資訊
 * @param   isDestory           傳送登出訊息後是否立即釋放相關資源
 * @return  TRUE 成功; FALSE 失敗
 */
BOOL    OesApi_Logout(
                OesApiSessionInfoT *pSessionInfo,
                BOOL isDestory);

/*
 * 直接斷開與伺服器的連線並釋放會話資料
 *
 * @param   pSessionInfo        會話資訊
 */
void    OesApi_Destory(
                OesApiSessionInfoT *pSessionInfo);
/* -------------------------           */


/* ===================================================================
 * 完整的客戶端環境初始化與析構介面宣告
 * =================================================================== */

/*
 * 完整的初始化客戶端環境
 *
 * @param[out]  pOutCliEnv      輸出客戶端環境資訊
 * @param       pCfgFile        配置檔案路徑
 * @param       pLoggerSection  日誌記錄器的配置區段名稱
 * @param       pCfgSection     客戶端配置區段名稱
 * @param       pOrdAddrKey     委託申報服務地址的配置項關鍵字 (為空或配置項未設定則不連線)
 * @param       pRptAddrKey     執行報告回報服務地址的配置項關鍵字 (為空或配置項未設定則不連線)
 * @param       pQryAddrKey     查詢服務地址的配置項關鍵字 (為空或配置項未設定則不連線)
 * @param       lastRptSeqNum   客戶端最後接收到的回報資料的回報編號
 *                              - 等於0, 從頭開始推送回報資料
 *                              - 大於0, 從指定的回報編號開始推送回報資料
 *                              - 小於0, 從最新的資料開始推送回報資料
 * @param[out]  pLastClSeqNo    返回伺服器端最後接收到並校驗通過的"客戶委託流水號"
 *                              - NULL表示忽略該引數
 *                              - 在0.11之前的版本中，“客戶委託流水號”是由客戶端維護的
 *                                線性遞增序列，用於標識委託資料的唯一性，並防止重複申報
 *                              - 從0.11版本開始，不再強制要求線性遞增，只要維持在同一
 *                                客戶端下的唯一性即可
 * @retval      TRUE            成功
 * @retval      FALSE           失敗。此時 errno 將被設定, 可以通過 errno/SPK_GET_ERRNO() 獲取到具體失敗原因
 *
 * @exception   EINVAL          配置異常或傳入引數非法
 * @exception   ECONNREFUSED    連線失敗
 * @exception   ETIMEDOUT       連線超時
 * @exception   EACCES          使用者名稱或密碼錯誤
 * @exception   EMLINK          連線數量超過限制
 * @exception   ENOENT          地址列表中沒有找到有效的節點配置
 * @exception   ESRCH           登入節點非主節點
 * @exception   EFAULT          其他業務錯誤
 *
 * @see         OesApi_InitAllByConvention
 * @see         OesApi_InitAllByCfgStruct
 */
BOOL    OesApi_InitAll(
                OesApiClientEnvT *pOutCliEnv,
                const char *pCfgFile,
                const char *pLoggerSection,
                const char *pCfgSection,
                const char *pOrdAddrKey,
                const char *pRptAddrKey,
                const char *pQryAddrKey,
                int64 lastRptSeqNum,
                int32 *pLastClSeqNo);

/*
 * 按照預設的配置名稱, 完整的初始化客戶端環境
 *
 * @param[out]  pOutCliEnv      輸出客戶端環境資訊
 * @param       pCfgFile        配置檔案路徑
 * @param       lastRptSeqNum   客戶端最後接收到的回報資料的回報編號
 *                              - 等於0, 從頭開始推送回報資料
 *                              - 大於0, 從指定的回報編號開始推送回報資料
 *                              - 小於0, 從最新的資料開始推送回報資料
 * @param[out]  pLastClSeqNo    返回伺服器端最後接收到並校驗通過的"客戶委託流水號"
 *                              - NULL表示忽略該引數
 *                              - 在0.11之前的版本中，“客戶委託流水號”是由客戶端維護的
 *                                線性遞增序列，用於標識委託資料的唯一性，並防止重複申報
 *                              - 從0.11版本開始，不再強制要求線性遞增，只要維持在同一
 *                                客戶端下的唯一性即可
 * @retval      TRUE            成功
 * @retval      FALSE           失敗。此時 errno 將被設定, 可以通過 errno/SPK_GET_ERRNO() 獲取到具體失敗原因
 *
 * @exception   EINVAL          配置異常或傳入引數非法
 * @exception   ECONNREFUSED    連線失敗
 * @exception   ETIMEDOUT       連線超時
 * @exception   EACCES          使用者名稱或密碼錯誤
 * @exception   EMLINK          連線數量超過限制
 * @exception   ENOENT          地址列表中沒有找到有效的節點配置
 * @exception   ESRCH           登入節點非主節點
 * @exception   EFAULT          其他業務錯誤
 *
 * @see         OesApi_InitAll
 * @see         OesApi_InitAllByCfgStruct
 */
BOOL    OesApi_InitAllByConvention(
                OesApiClientEnvT *pOutCliEnv,
                const char *pCfgFile,
                int64 lastRptSeqNum,
                int32 *pLastClSeqNo);

/*
 * 按照配置資訊結構體, 初始化客戶端環境
 *
 * @note        與 OesApi_InitAll 和 OesApi_InitAllByConvention 介面有一處不同,
 *              OesApi_InitAllByCfgStruct 介面不會自動初始化日誌記錄器, 需要在外面
 *              顯式的呼叫 OesApi_InitLogger 來初始化API的日誌記錄器
 *
 * @param[out]  pOutCliEnv      輸出客戶端環境資訊
 * @param       pClientCfg      配置資訊結構體
 * @param       lastRptSeqNum   客戶端最後接收到的回報資料的回報編號
 *                              - 等於0, 從頭開始推送回報資料
 *                              - 大於0, 從指定的回報編號開始推送回報資料
 *                              - 小於0, 從最新的資料開始推送回報資料
 * @param[out]  pLastClSeqNo    返回伺服器端最後接收到並校驗通過的"客戶委託流水號"
 *                              - NULL表示忽略該引數
 *                              - 在0.11之前的版本中，“客戶委託流水號”是由客戶端維護的
 *                                線性遞增序列，用於標識委託資料的唯一性，並防止重複申報
 *                              - 從0.11版本開始，不再強制要求線性遞增，只要維持在同一
 *                                客戶端下的唯一性即可
 * @retval      TRUE            成功
 * @retval      FALSE           失敗。此時 errno 將被設定, 可以通過 errno/SPK_GET_ERRNO() 獲取到具體失敗原因
 *
 * @exception   EINVAL          配置異常或傳入引數非法
 * @exception   ECONNREFUSED    連線失敗
 * @exception   ETIMEDOUT       連線超時
 * @exception   EACCES          使用者名稱或密碼錯誤
 * @exception   EMLINK          連線數量超過限制
 * @exception   ENOENT          地址列表中沒有找到有效的節點配置
 * @exception   ESRCH           登入節點非主節點
 * @exception   EFAULT          其他業務錯誤
 *
 * @see         OesApi_InitAll
 * @see         OesApi_InitAllByConvention
 */
BOOL    OesApi_InitAllByCfgStruct(
                OesApiClientEnvT *pOutCliEnv,
                const OesApiClientCfgT *pClientCfg,
                int64 lastRptSeqNum,
                int32 *pLastClSeqNo);

/*
 * 登出並關閉所有的客戶端會話
 *
 * @param[out]  pCliEnv         客戶端環境資訊
 * @param       isDestory       是否立即釋放相關資源
 * @return      TRUE 成功; FALSE 失敗
 */
void    OesApi_LogoutAll(
                OesApiClientEnvT *pCliEnv, BOOL isDestory);

/*
 * 直接斷開與伺服器的連線並釋放會話資料
 *
 * @param[out]  pCliEnv     客戶端環境資訊
 */
void    OesApi_DestoryAll(
                OesApiClientEnvT *pCliEnv);
/* -------------------------           */


/* ===================================================================
 * 基於配置檔案的輔助介面函式宣告
 * =================================================================== */

/*
 * 初始化日誌記錄器
 *
 * @param   pCfgFile            配置檔案路徑
 * @param   pLoggerSection      日誌記錄器的配置區段名稱(為空則使用預設值)
 * @return  TRUE 成功; FALSE 失敗
 */
BOOL    OesApi_InitLogger(
                const char *pCfgFile,
                const char *pLoggerSection);

/*
 * 重置執行緒級別的日誌記錄器名稱
 *
 * @param   pLogSystemName  執行緒級別的日誌系統名稱
 * @return  TRUE 成功; FALSE 失敗
 */
BOOL    OesApi_ResetThreadLoggerName(
                const char *pLogSystemName);

/*
 * 初始化委託申報通道 (包括完整的配置解析、連線建立和登入過程)
 *
 * @param[out]  pOrdChannel     委託申報通道的會話資訊
 * @param       pCfgFile        配置檔案路徑
 * @param       pCfgSection     客戶端配置區段名稱(為空則使用預設值)
 * @param       pAddrKey        地址列表的配置項關鍵字(為空則使用預設值)
 * @param[out]  pLastClSeqNo    返回伺服器端最後接收到並校驗通過的"客戶委託流水號"
 *                              - NULL表示忽略該引數
 *                              - 在0.11之前的版本中，“客戶委託流水號”是由客戶端維護的
 *                                線性遞增序列，用於標識委託資料的唯一性，並防止重複申報
 *                              - 從0.11版本開始，不再強制要求線性遞增，只要維持在同一
 *                                客戶端下的唯一性即可
 * @retval      TRUE            成功
 * @retval      FALSE           失敗。此時 errno 將被設定, 可以通過 errno/SPK_GET_ERRNO() 獲取到具體失敗原因
 *
 * @exception   EINVAL          配置異常或傳入引數非法
 * @exception   ECONNREFUSED    連線失敗
 * @exception   ETIMEDOUT       連線超時
 * @exception   EACCES          使用者名稱或密碼錯誤
 * @exception   EMLINK          連線數量超過限制
 * @exception   ENOENT          地址列表中沒有找到有效的節點配置
 * @exception   ESRCH           登入節點非主節點
 * @exception   EFAULT          其他業務錯誤
 */
BOOL    OesApi_InitOrdChannel(
                OesApiSessionInfoT *pOrdChannel,
                const char *pCfgFile,
                const char *pCfgSection,
                const char *pAddrKey,
                int32 *pLastClSeqNo);

/*
 * 初始化委託申報通道 (包括完整的連線建立和登入過程)
 *
 * @param[out]  pOrdChannel     委託申報通道的會話資訊
 * @param       pRemoteCfg      遠端主機配置資訊
 * @param[out]  pLastClSeqNo    返回伺服器端最後接收到並校驗通過的"客戶委託流水號"
 *                              - NULL表示忽略該引數
 *                              - 在0.11之前的版本中，“客戶委託流水號”是由客戶端維護的
 *                                線性遞增序列，用於標識委託資料的唯一性，並防止重複申報
 *                              - 從0.11版本開始，不再強制要求線性遞增，只要維持在同一
 *                                客戶端下的唯一性即可
 * @retval      TRUE            成功
 * @retval      FALSE           失敗。此時 errno 將被設定, 可以通過 errno/SPK_GET_ERRNO() 獲取到具體失敗原因
 *
 * @exception   EINVAL          配置異常或傳入引數非法
 * @exception   ECONNREFUSED    連線失敗
 * @exception   ETIMEDOUT       連線超時
 * @exception   EACCES          使用者名稱或密碼錯誤
 * @exception   EMLINK          連線數量超過限制
 * @exception   ENOENT          地址列表中沒有找到有效的節點配置
 * @exception   ESRCH           登入節點非主節點
 * @exception   EFAULT          其他業務錯誤
 */
BOOL    OesApi_InitOrdChannel2(
                OesApiSessionInfoT *pOrdChannel,
                const OesApiRemoteCfgT *pRemoteCfg,
                int32 *pLastClSeqNo);

/*
 * 初始化回報通道 (包括完整的配置解析、連線建立和登入過程)
 *
 * @param[out]  pRptChannel     回報通道的會話資訊
 * @param       pCfgFile        配置檔案路徑
 * @param       pCfgSection     客戶端配置區段名稱(為空則使用預設值)
 * @param       pAddrKey        地址列表的配置項關鍵字(為空則使用預設值)
 * @param       lastRptSeqNum   客戶端最後接收到的回報資料的回報編號
 *                              - 等於0, 從頭開始推送回報資料
 *                              - 大於0, 從指定的回報編號開始推送回報資料
 *                              - 小於0, 從最新的資料開始推送回報資料
 * @retval      TRUE            成功
 * @retval      FALSE           失敗。此時 errno 將被設定, 可以通過 errno/SPK_GET_ERRNO() 獲取到具體失敗原因
 *
 * @exception   EINVAL          配置異常或傳入引數非法
 * @exception   ECONNREFUSED    連線失敗
 * @exception   ETIMEDOUT       連線超時
 * @exception   EACCES          使用者名稱或密碼錯誤
 * @exception   EMLINK          連線數量超過限制
 * @exception   ENOENT          地址列表中沒有找到有效的節點配置
 * @exception   ESRCH           登入節點非主節點
 * @exception   EFAULT          其他業務錯誤
 */
BOOL    OesApi_InitRptChannel(
                OesApiSessionInfoT *pRptChannel,
                const char *pCfgFile,
                const char *pCfgSection,
                const char *pAddrKey,
                int64 lastRptSeqNum);

/*
 * 初始化回報通道 (包括完整的連線建立和登入過程)
 *
 * @param[out]  pRptChannel     回報通道的會話資訊
 * @param       pRemoteCfg      遠端主機配置資訊
 * @param       pSubscribeInfo  回報訂閱配置資訊,包括客戶端環境號和訂閱回報型別
 * @param       lastRptSeqNum   客戶端最後接收到的回報資料的回報編號
 *                              - 等於0, 從頭開始推送回報資料
 *                              - 大於0, 從指定的回報編號開始推送回報資料
 *                              - 小於0, 從最新的資料開始推送回報資料
 * @retval      TRUE            成功
 * @retval      FALSE           失敗。此時 errno 將被設定, 可以通過 errno/SPK_GET_ERRNO() 獲取到具體失敗原因
 *
 * @exception   EINVAL          配置異常或傳入引數非法
 * @exception   ECONNREFUSED    連線失敗
 * @exception   ETIMEDOUT       連線超時
 * @exception   EACCES          使用者名稱或密碼錯誤
 * @exception   EMLINK          連線數量超過限制
 * @exception   ENOENT          地址列表中沒有找到有效的節點配置
 * @exception   ESRCH           登入節點非主節點
 * @exception   EFAULT          其他業務錯誤
 */
BOOL    OesApi_InitRptChannel2(
                OesApiSessionInfoT *pRptChannel,
                const OesApiRemoteCfgT *pRemoteCfg,
                const OesApiSubscribeInfoT *pSubscribeInfo,
                int64 lastRptSeqNum);

/*
 * 初始化查詢通道 (包括完整的配置解析、連線建立和登入過程)
 *
 * @param[out]  pQryChannel     查詢通道的會話資訊
 * @param       pCfgFile        配置檔案路徑
 * @param       pCfgSection     客戶端配置區段名稱(為空則使用預設值)
 * @param       pAddrKey        地址列表的配置項關鍵字(為空則使用預設值)
 * @retval      TRUE            成功
 * @retval      FALSE           失敗。此時 errno 將被設定, 可以通過 errno/SPK_GET_ERRNO() 獲取到具體失敗原因
 *
 * @exception   EINVAL          配置異常或傳入引數非法
 * @exception   ECONNREFUSED    連線失敗
 * @exception   ETIMEDOUT       連線超時
 * @exception   EACCES          使用者名稱或密碼錯誤
 * @exception   EMLINK          連線數量超過限制
 * @exception   ENOENT          地址列表中沒有找到有效的節點配置
 * @exception   ESRCH           登入節點非主節點
 * @exception   EFAULT          其他業務錯誤
 */
BOOL    OesApi_InitQryChannel(
                OesApiSessionInfoT *pQryChannel,
                const char *pCfgFile,
                const char *pCfgSection,
                const char *pAddrKey);

/*
 * 初始化查詢通道 (包括完整的連線建立和登入過程)
 *
 * @param[out]  pQryChannel     查詢通道的會話資訊
 * @param       pRemoteCfg      遠端主機配置資訊
 * @retval      TRUE            成功
 * @retval      FALSE           失敗。此時 errno 將被設定, 可以通過 errno/SPK_GET_ERRNO() 獲取到具體失敗原因
 *
 * @exception   EINVAL          配置異常或傳入引數非法
 * @exception   ECONNREFUSED    連線失敗
 * @exception   ETIMEDOUT       連線超時
 * @exception   EACCES          使用者名稱或密碼錯誤
 * @exception   EMLINK          連線數量超過限制
 * @exception   ENOENT          地址列表中沒有找到有效的節點配置
 * @exception   ESRCH           登入節點非主節點
 * @exception   EFAULT          其他業務錯誤
 */
BOOL    OesApi_InitQryChannel2(
                OesApiSessionInfoT *pQryChannel,
                const OesApiRemoteCfgT *pRemoteCfg);

/*
 * 解析伺服器地址列表字串
 *
 * - 待解析的地址列表可是以空格、逗號或分號分割的地址列表字串
 *   - e.g. "tcp://127.0.0.1:5100, tcp://192.168.0.11:5100"
 * - 同時也可以在每個地址之前，為其指定對應的主機編號
 *   - e.g. "2 tcp://192.168.0.12:5100, 1 tcp://192.168.0.11:5100,
 *          3 tcp://192.168.0.13:5100"
 *
 * @param       pUriList        主機地址列表 (以空格、逗號或分號分割的地址列表字串)
 * @param[out]  pOutAddrList    用於輸出解析後的地址資訊的地址資訊陣列
 * @param       addrListLength  地址資訊列表的陣列長度
 * @return      大於等於0, 解析得到的地址數量; 小於0, 解析失敗
 */
int32   OesApi_ParseAddrListString(
                const char *pUriList,
                OesApiAddrInfoT *pOutAddrList,
                int32 addrListLength);

/*
 * 從配置檔案中解析遠端主機配置
 *
 * @param       pCfgFile            配置檔案路徑
 * @param       pSection            配置區段名稱
 * @param       pAddrKey            地址列表的配置項關鍵字
 * @param[out]  pOutRemoteCfg       輸出遠端主機配置資訊
 * @param[out]  pOutSubscribeInfo   輸出回報訂閱資訊
 * @return      TRUE 成功; FALSE 失敗
 */
BOOL    OesApi_ParseConfigFromFile(
                const char *pCfgFile,
                const char *pSection,
                const char *pAddrKey,
                OesApiRemoteCfgT *pOutRemoteCfg,
                OesApiSubscribeInfoT *pOutSubscribeInfo);

/*
 * 按照預設的配置名稱, 從配置檔案中解析所有配置資訊
 *
 * @param       pCfgFile        配置檔案路徑
 * @param[out]  pOutApiCfg      輸出遠端主機配置資訊
 * @return      TRUE 成功; FALSE 失敗
 */
BOOL    OesApi_ParseAllConfig(
                const char *pCfgFile,
                OesApiClientCfgT *pOutApiCfg);
/* -------------------------           */


/* ===================================================================
 * 用於同時接收多個連線通道資料的通道組介面函式
 * =================================================================== */

/*
 * 初始化(重置)通道組資訊 (用於同時接收多個連線通道的資料)
 *
 * @param[in,out]   pChannelGroup   通道組資訊
 * @return          TRUE, 成功; FALSE 失敗
 */
BOOL    OesApi_InitChannelGroup(
                OesApiChannelGroupT *pChannelGroup);

/*
 * 銷燬通道組資訊 (同時關閉通道組下的所有連線)
 *
 * @param       pChannelGroup   通道組資訊
 * @return      TRUE, 成功; FALSE 失敗
 */
BOOL    OesApi_DestoryChannelGroup(
                OesApiChannelGroupT *pChannelGroup);

/*
 * 將連線資訊新增到通道組
 *
 * @note        在檢測通道組下各連線的I/O事件時，是從後向前進行掃描的，所以建議將更
 *              活躍的連線新增到其它連線的後面
 *
 * @param       pChannelGroup   通道組資訊
 * @param       pChannel        連線資訊
 * @return      TRUE, 成功; FALSE 失敗
 */
BOOL    OesApi_AddToChannelGroup(
                OesApiChannelGroupT *pChannelGroup,
                OesApiSessionInfoT *pChannel);

/*
 * 從通道組中刪除連線
 *
 * @param       pChannelGroup   通道組資訊
 * @param       pTargetChannel  待刪除連線的連線資訊
 * @return      TRUE, 成功; FALSE 失敗
 */
BOOL    OesApi_DeleteFromChannelGroup(
                OesApiChannelGroupT *pChannelGroup,
                OesApiSessionInfoT *pTargetChanne);

/*
 * 獲取通道組中指定下標的連線資訊
 *
 * @param       pChannelGroup   通道組資訊
 * @param       index           下標位置 (如果小於0, 則表示按照先後順序而非下標位置進行返回)
 *                              -  0, 返回 0 號下標位置所對應的會話資訊
 *                              - -1, 返回通道組下第一個有效的會話資訊
 *                              - -2, 返回通道組下第二個有效的會話資訊
 *                              - INT_MIN, 如果超出了通道組的有效會話數量, 則返回最後一個有效的會話資訊
 * @return      連線資訊
 */
OesApiSessionInfoT *
        OesApi_GetFromChannelGroup(
                OesApiChannelGroupT *pChannelGroup,
                int32 index);

/*
 * 獲取通道組中與指定Socket描述符相匹配的連線資訊
 *
 * @param       pChannelGroup   通道組資訊
 * @param       socketFd        Socket描述符
 * @return      連線資訊
 */
OesApiSessionInfoT *
        OesApi_GetFromChannelGroupBySocket(
                OesApiChannelGroupT *pChannelGroup,
                SPK_SOCKET socketFd);

/*
 * 遍歷通道組下的所有通道資訊並執行回撥函式
 *
 * @param       pChannelGroup   通道組資訊
 * @param       fnCallback      待執行的回撥函式
 * @param       pParams         回撥函式的引數
 * @return      0, 成功; 小於 0, errno 取負
 */
int32   OesApi_ForeachInChannelGroup(
                OesApiChannelGroupT *pChannelGroup,
                int32 (*fnCallback)(OesApiSessionInfoT *pChannel, void *pParams),
                void *pParams);

/*
 * 檢測TCP通道組下各連線通道的讀事件，並呼叫回撥函式進行訊息處理
 *
 * @param       pChannelGroup   通道組資訊
 * @param       timeoutMs       超時時間(毫秒)
 * @param       pOnMsgCallback  進行訊息處理的回撥函式
 * @param       pCallbackParams 回撥函式的引數
 * @param[out]  ppFailed        返回處理失敗時所對應的連線資訊
 *                              - 允許為空, 為空則忽略該引數
 *                              - 當因為超時(一定時間內沒有資料)而返回時, 該引數的值為空
 * @return      大於等於0, 成功 (返回回撥函式的返回值);
 *              小於0, 失敗 (負的錯誤號)
 *
 * @exception   NEG(ETIMEDOUT)  超時
 * @exception   NEG(EPIPE)      連線已破裂
 * @exception   Others          由select/read系統呼叫或回撥函式返回的錯誤
 */
int32   OesApi_WaitOnChannelGroup(
                OesApiChannelGroupT *pChannelGroup,
                int32 timeoutMs,
                F_OESAPI_ON_RPT_MSG_T pOnMsgCallback,
                void *pCallbackParams,
                OesApiSessionInfoT **ppFailed);
/* -------------------------           */


/* ===================================================================
 * 錯誤處理等輔助函式
 * =================================================================== */

/*
 * 設定當前執行緒登入OES時使用的登入使用者名稱
 * 不設定或者引數為空的話, 登入時會嘗試使用配置檔案中的配置
 *
 * @param   pUsername           登入使用者名稱
 */
void    OesApi_SetThreadUsername(
                const char *pUsername);

/*
 * 返回當前執行緒登入OES時使用的登入使用者名稱
 *
 * @return  登入使用者名稱
 */
const char *
        OesApi_GetThreadUsername();

/*
 * 設定當前執行緒登入OES時使用的登入密碼
 * 不設定或者引數為空的話, 登入時會嘗試使用配置檔案中的配置
 *
 * @param   pPassword           登入密碼
 *                              - 支援通過密碼字首指定密碼型別, 如 md5:PASSWORD, txt:PASSWORD
 */
void    OesApi_SetThreadPassword(
                const char *pPassword);

/*
 * 設定當前執行緒登入OES時使用的客戶端環境號
 * 不設定或者引數為空的話, 登入時會嘗試使用配置檔案中的配置
 *
 * @param   clEnvId             客戶端環境號
 */
void    OesApi_SetThreadEnvId(
                int8 clEnvId);

/*
 * 返回當前執行緒登入OES時使用的客戶端環境號
 *
 * @return  客戶端環境號
 */
int8    OesApi_GetThreadEnvId();

/*
 * 設定當前執行緒訂閱回報使用的客戶端環境號
 * 不設定或者引數為空的話, 會嘗試使用配置檔案中的配置
 *
 * @param   subscribeEnvId      待訂閱的客戶端環境號
 */
void    OesApi_SetThreadSubscribeEnvId(
                int8 subscribeEnvId);

/*
 * 返回當前執行緒訂閱回報使用的客戶端環境號
 *
 * @return  客戶端環境號
 */
int8    OesApi_GetThreadSubscribeEnvId();

/*
 * 設定客戶端自定義的本地IP和MAC
 *
 * @param   pIpStr              點分十進位制的IP地址字串
 * @param   pMacStr             MAC地址字串 (MAC地址格式 45:38:56:89:78:5A)
 * @return  TRUE 設定成功; FALSE 設定失敗 (引數格式錯誤)
 */
BOOL    OesApi_SetCustomizedIpAndMac(
                const char *pIpStr,
                const char *pMacStr);

/*
 * 設定客戶端自定義的本地IP地址
 *
 * @param   pIpStr              點分十進位制的IP地址字串
 * @return  TRUE 設定成功; FALSE 設定失敗 (引數格式錯誤)
 */
BOOL    OesApi_SetCustomizedIp(
                const char *pIpStr);

/*
 * 設定客戶端自定義的本地MAC地址
 *
 * @param   pMacStr             MAC地址字串 (MAC地址格式 45:38:56:89:78:5A)
 * @return  TRUE 設定成功; FALSE 設定失敗 (引數格式錯誤)
 */
BOOL    OesApi_SetCustomizedMac(
                const char *pMacStr);

/*
 * 獲取客戶端自定義的本地IP
 *
 * @return  客戶端自定義的本地IP
 */
const char *
        OesApi_GetCustomizedIp();

/*
 * 獲取客戶端自定義的本地MAC
 *
 * @return  客戶端自定義的本地MAC
 */
const char *
        OesApi_GetCustomizedMac();

/*
 * 設定客戶端自定義的本地裝置序列號
 *
 * @param   pDriverId           裝置序列號字串
 * @return  TRUE 設定成功; FALSE 設定失敗 (引數格式錯誤)
 */
BOOL    OesApi_SetCustomizedDriverId(
                const char *pDriverId);

/*
 * 獲取客戶端自定義的本地裝置序列號
 *
 * @return  客戶端自定義的本地裝置序列號
 */
const char *
        OesApi_GetCustomizedDriverId();

/*
 * 返回通道對應的客戶端環境號 (clEnvId)
 *
 * @param   pSessionInfo        會話資訊
 * @return  通道對應的客戶端環境號
 */
int8    OesApi_GetClEnvId(
                const OesApiSessionInfoT *pChannel);

/*
 * 獲取通道最新接受訊息時間
 *
 * @param   pSessionInfo        會話資訊
 * @return  通道最新接受訊息時間(單位: 秒)
 */
int64    OesApi_GetLastRecvTime(
                const OesApiSessionInfoT *pChannel);

/*
 * 獲取通道最新發送訊息時間
 *
 * @param   pSessionInfo        會話資訊
 * @return  通道最新發送訊息時間(單位: 秒)
 */
int64    OesApi_GetLastSendTime(
                const OesApiSessionInfoT *pChannel);

/*
 * 返回回報通道是否還有更多已接收但尚未回撥處理完成的資料
 *
 * @param   pRptChannel         會話資訊
 * @return  已接收到但尚未處理完成的資料長度
 * @note    當在回撥函式裡面呼叫時, 該介面返回的資料長度是包含本次回撥資料的
 */
int32   OesApi_HasMoreCachedData(
                const OesApiSessionInfoT *pRptChannel);

/*
 * 返回委託申報通道是否已經連線且有效
 *
 * @param   pOrdChannel         會話資訊
 * @return  TRUE 已連線; FALSE 未連線或連線無效
 */
BOOL    OesApi_IsValidOrdChannel(
                const OesApiSessionInfoT *pOrdChannel);

/*
 * 返回回報通道是否已經連線且有效
 *
 * @param   pRptChannel         會話資訊
 * @return  TRUE 已連線; FALSE 未連線或連線無效
 */
BOOL    OesApi_IsValidRptChannel(
                const OesApiSessionInfoT *pRptChannel);

/*
 * 返回查詢通道是否已經連線且有效
 *
 * @param   pQryChannel         會話資訊
 * @return  TRUE 已連線; FALSE 未連線或連線無效
 */
BOOL    OesApi_IsValidQryChannel(
                const OesApiSessionInfoT *pQryChannel);

/*
 * 返回通道組是否已經連線
 *
 * @param   pChannelGroup       通道組資訊
 * @return  TRUE 已連線; FALSE 未連線或連線無效
 */
BOOL    OesApi_IsValidChannelGroup(
                const OesApiChannelGroupT *pChannelGroup);

/*
 * 返回當前執行緒最近一次API呼叫失敗的錯誤號
 *
 * @return  錯誤號
 */
int32   OesApi_GetLastError();

/*
 * 設定當前執行緒的API錯誤號
 *
 * @param   errCode             錯誤號
 */
void    OesApi_SetLastError(
                int32 errCode);

/*
 * 返回錯誤號對應的錯誤資訊
 *
 * @param   errCode             錯誤號
 * @return  錯誤號對應的錯誤資訊
 */
const char *
        OesApi_GetErrorMsg(
                int32 errCode);

/*
 * 返回訊息頭中的狀態碼所對應的錯誤資訊
 *
 * @param   status              狀態碼
 * @param   detailStatus        明細狀態碼
 * @return  狀態碼所對應的錯誤資訊
 */
const char *
        OesApi_GetErrorMsg2(
                uint8 status,
                uint8 detailStatus);
/* -------------------------           */


/* ===================================================================
 * 其它輔助函式
 * =================================================================== */

/*
 * 從成交回報中提取和生成委託回報資訊
 *
 * @param[in]   pTrdReport      成交回報資訊
 * @param[out]  pOutOrdReport   用於輸出委託回報資訊的快取區
 * @return      提取到的委託回報資訊
 */
OesOrdCnfmT *
        OesHelper_ExtractOrdReportFromTrd(
                const OesTrdCnfmT *pTrdReport,
                OesOrdCnfmT *pOutOrdReport);
/* -------------------------           */


#ifdef __cplusplus
}
#endif

#endif  /* _OES_API_H */
