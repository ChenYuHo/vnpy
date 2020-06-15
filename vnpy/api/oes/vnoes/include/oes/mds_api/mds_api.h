/*
 * Copyright 2016 the original author or authors.
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
 * @file    mds_api.h
 *
 * MDS（行情資料服務系統）介面庫
 *
 * @version 0.8.13      2016/10/24
 * @version 0.12        2016/11/30
 *          - 重構錯誤號定義, 使錯誤號從1000開始
 *          - 增加 MdsApi_GetErrorMsg 和 MdsApi_GetErrorMsg2 方法
 *          - 在登入報文中增加協議版本號資訊, 並在登入時校驗協議版本號的相容性
 * @version 0.12.1      2016/12/21
 *          - 查詢介面重新命名
 *              - MdsApi_QryMktDataSnapshot -> MdsApi_QueryMktDataSnapshot
 *              - MdsApi_QrySecurityStatus -> MdsApi_QuerySecurityStatus
 *              - MdsApi_QryTrdSessionStatus -> MdsApi_QueryTrdSessionStatus
 *          - 刪除 MdsApi_IsBusinessError 介面, 查詢介面不再返回小於 -1000 的錯誤
 *          - 查詢介面返回值變更:
 *              - 無資料返回 NEG(ENOENT)
 *              - 查詢被伺服器拒絕返回 NEG(EINVAL), 具體錯誤資訊通過日誌列印
 *          - 微調mds_api日誌列印格式
 * @version 0.12.3      2017/1/8
 *          - 精簡API依賴的標頭檔案, 並最小化API釋出包中的標頭檔案數量
 *          - 重新命名 protocol_parser/errors/mds_protocol_errors.h -> errors/mds_errors.h
 *          - 新增輔助實現實時行情訂閱功能的介面
 *              - MdsApi_ResubscribeMarketData
 *              - MdsHelper_ClearSubscribeRequestEntries
 *              - MdsHelper_AddSubscribeRequestEntry
 * @version 0.12.6.3    2017/03/24
 *          - 增加mds_api.h中的標頭檔案引用, api使用者不在需要顯式引用sutil庫的標頭檔案
 * @version 0.12.8      2017/04/20
 *          - 重新命名 MdsApi_SubscribeMarketData -> MdsApi_SyncSubscribeOnLogon
 *          - 重新命名 MdsApi_ResubscribeMarketData -> MdsApi_SubscribeMarketData
 *          - 新增輔助的行情訂閱介面
 *              - MdsApi_SubscribeByString
 *              - MdsApi_SubscribeByStringAndPrefixes
 *              - MdsHelper_SetSubscribeRequestMode
 *              - MdsHelper_SetSubscribeRequestTickType
 *              - MdsHelper_SetSubscribeRequestDataTypes
 * @version 0.15.3.3    2017/08/20
 *          - 新增介面 '重置執行緒級別的日誌記錄器名稱 (MdsApi_ResetThreadLoggerName)',
 *            以支援為當前執行緒設定獨立的日誌檔案
 * @version 0.15.4      2017/08/21
 *          - 新增介面 '獲取API的發行版本號 (MdsApi_GetApiVersion)'
 * @version 0.15.4.1    2017/09/25
 *          - 伺服器端刪除了對JSON等通訊協議等支援, 改為只支援二進位制協議
 * @version 0.15.5      2017/11/11
 *          - 調整介面 MdsApi_InitAll, 以支援同時初始化多個組播通道
 * @version 0.15.5.1    2017/11/17
 *          - 增加 MdsApi_IsValidTcpChannel、MdsApi_IsValidUdpChannel 等介面, 用於判斷通道是否已經連線且有效
 * @version 0.15.5.2    2018/01/29
 *          - 增加 MdsApi_GetLastRecvTime、MdsApi_GetLastSendTime 介面, 用於獲取通道最新發送/接受訊息的時間
 *          - 登入失敗時, 可以通過 errno/SPK_GET_ERRNO() 獲取到具體失敗原因
 * @version 0.15.5.3    2018/01/24
 *          - 調整介面 MdsApi_InitAll, 增加一個函式引數 (pUdpTick2AddrKey), 以支援分別訂閱逐筆成交和逐筆委託的行情組播
 * @version 0.15.5.9    2018/05/05
 *          - 增加可以處理壓縮過的訊息的 WaitOnMsg 介面:
 *              - MdsApi_WaitOnMsgCompressible
 *              - MdsApi_WaitOnTcpChannelGroupCompressible
 *              - 與不帶 Compressible 字尾的介面相比, 帶 Compressible 字尾的介面會自動檢測和處理壓縮過的訊息,
 *                但也會因此帶來微小的效能損失。如果對延遲不是極端敏感的話, 可以直接使用帶 Compressible 字尾的接
 *                口, 以方便相容不同的模式。
 * @version 0.15.5.12   2018/06/21
 *          - 增加 MdsApi_HasMoreCachedData 介面, 用於返回已經接收到但尚未被回撥函式處理的快取資料長度
 * @version 0.15.5.16   2018/08/23
 *          - 重構 SubscribeByString 介面
 *              - 支援訂閱所有產品的行情或不訂閱任何產品的行情
 *              - 支援通過 .SH 或 .SZ 字尾為證券程式碼指定其所屬的交易所
 *              - 新增 MdsHelper_SetTickTypeOnSubscribeByString 介面, 以設定SubscribeByString預設使用的資料模式 (TickType)
 *              - 增量訂閱時, 允許不指定 dataType (小於0) 而繼承之前訂閱的資料型別
 * @version 0.15.6      2018/03/21
 *          - 增加設定當前執行緒登入使用者名稱/登入密碼的介面
 *              - MdsApi_SetThreadUsername
 *              - MdsApi_SetThreadPassword
 *          - 增加返回最近一次API呼叫失敗的錯誤號的介面
 *              - MdsApi_GetLastError
 *              - MdsApi_SetLastError
 * @version 0.15.7.6    2018/11/03
 *          - 增加查詢證券(股票/債券/基金)靜態資訊的介面
 *              - MdsApi_QueryStockStaticInfo
 * @version 0.15.7.6_RC2 2018/11/11
 *          - 新增批量查詢行情快照介面
 *              - MdsApi_QuerySnapshotList
 *          - 增加 MdsApi_InitAllByCfgStruct 介面
 * @version 0.15.9_I9   2019/04/15
 *          - 增加修改客戶端登入密碼介面
 *              - MdsApi_SendChangePasswordReq
 *          - 增加設定/獲取客戶端自定義的本地IP/MAC地址的介面
 *              - MdsApi_SetCustomizedIp
 *              - MdsApi_GetCustomizedIp
 *              - MdsApi_SetCustomizedMac
 *              - MdsApi_GetCustomizedMac
 *          - 增加設定/獲取客戶端自定義的裝置序列號的介面
 *              - MdsApi_SetCustomizedDriverId
 *              - MdsApi_GetCustomizedDriverId
 *          - 重新實現登入介面 (介面MdsApi_Logon)
 *              - 增加採集IP、MAC等資訊, 增強安全性處理
 *          - 調整L2逐筆資料的行情組播頻道
 *              - 劃分為兩個頻道, 按照頻道號混合推送逐筆成交和逐筆委託, 取代之前逐筆成交/逐筆委託分別推送的方式
 *              - API及配置檔案保持相容, 但頻道內容發生了變化
 *
 * @since   2016/03/02
 */


#ifndef _MDS_API_H
#define _MDS_API_H


#include    <mds_global/mds_mkt_packets.h>
#include    <mds_api/errors/mds_errors.h>
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
#define MDSAPI_CFG_DEFAULT_SECTION              "mds_client"
/** 預設的日誌配置區段名稱 */
#define MDSAPI_CFG_DEFAULT_SECTION_LOGGER       "log"
/** 預設的TCP行情訂閱服務配置項名稱 */
#define MDSAPI_CFG_DEFAULT_KEY_TCP_ADDR         "tcpServer"
/** 預設的行情查詢服務配置項名稱 */
#define MDSAPI_CFG_DEFAULT_KEY_QRY_ADDR         "qryServer"

/** UDP行情訂閱服務配置項名稱 (L1快照/指數/期權) */
#define MDSAPI_CFG_DEFAULT_KEY_UDP_ADDR_L1      "udpServer.L1"
/** UDP行情訂閱服務配置項名稱 (L2快照) */
#define MDSAPI_CFG_DEFAULT_KEY_UDP_ADDR_L2      "udpServer.L2"

 /** UDP行情訂閱服務配置項名稱 (L2逐筆-頻道1) */
 #define MDSAPI_CFG_DEFAULT_KEY_UDP_ADDR_TICK1  "udpServer.Tick1"
 /** UDP行情訂閱服務配置項名稱 (L2逐筆-頻道1) */
 #define MDSAPI_CFG_DEFAULT_KEY_UDP_ADDR_TICK2  "udpServer.Tick2"

/** UDP行情訂閱服務配置項名稱 (L2逐筆成交) @deprecated 已廢棄, 效果等同於L2逐筆-頻道1 */
#define MDSAPI_CFG_DEFAULT_KEY_UDP_ADDR_TICK_TRADE          \
        "udpServer.TickTrade"
/** UDP行情訂閱服務配置項名稱 (L2逐筆委託) @deprecated 已廢棄, 效果等同於L2逐筆-頻道2 */
#define MDSAPI_CFG_DEFAULT_KEY_UDP_ADDR_TICK_ORDER          \
        "udpServer.TickOrder"

/** 預設的UDP行情訂閱服務配置項名稱 */
#define MDSAPI_CFG_DEFAULT_KEY_UDP_ADDR                     \
        MDSAPI_CFG_DEFAULT_KEY_UDP_ADDR_L1

/** 預設的心跳間隔 (30 秒) */
#define MDSAPI_DEFAULT_HEARTBEAT_INTERVAL                   \
        GENERAL_CLI_DEFAULT_HEARTBEAT_INTERVAL
/** 預設的UDP連線的心跳間隔 (30 秒) */
#define MDSAPI_DEFAULT_UDP_HEARTBEAT_INTERVAL               \
        GENERAL_CLI_DEFAULT_UDP_HEARTBEAT_INTERVAL

/** 預設的證券程式碼列表等字串分隔符 */
#define MDSAPI_DEFAULT_STRING_DELIM                         \
        ",;| \t\r\n"
/* -------------------------           */


/* ===================================================================
 * 常量定義, 列舉型別定義
 * =================================================================== */

/**
 * 通道型別定義
 */
typedef enum _eMdsApiChannelType {
    MDSAPI_CHANNEL_TYPE_TCP         = 11,       /**< TCP行情訂閱通道 */
    MDSAPI_CHANNEL_TYPE_UDP         = 12,       /**< UDP行情組播通道 */
    MDSAPI_CHANNEL_TYPE_QUERY       = 13        /**< 行情查詢通道 */
} eMdsApiChannelTypeT;
/* -------------------------           */


/* ===================================================================
 * 結構體定義
 * =================================================================== */

/**
 * 客戶端會話資訊（連線通道資訊）定義
 */
typedef SGeneralClientChannelT      MdsApiSessionInfoT;


/* 結構體的初始化值定義 */
#define NULLOBJ_MDSAPI_SESSION_INFO             \
        NULLOBJ_GENERAL_CLIENT_CHANNEL
/* -------------------------           */


/**
 * 客戶端會話的連線通道組定義（多個連線通道的集合）
 */
typedef SGeneralClientChannelGroupT MdsApiChannelGroupT;


/* 結構體的初始化值定義 */
#define NULLOBJ_MDSAPI_CHANNEL_GROUP            \
        NULLOBJ_GENERAL_CLIENT_CHANNEL_GROUP
/* -------------------------           */


/**
 * Socket URI地址資訊
 */
typedef SGeneralClientAddrInfoT     MdsApiAddrInfoT;


/* 結構體初始化值定義 */
#define NULLOBJ_MDSAPI_ADDR_INFO                \
        NULLOBJ_GENERAL_CLIENT_ADDR_INFO
/* -------------------------           */


/**
 * 遠端主機配置資訊
 */
typedef SGeneralClientRemoteCfgT    MdsApiRemoteCfgT;


/* 結構體的初始化值定義 */
#define NULLOBJ_MDSAPI_REMOTE_CFG               \
        NULLOBJ_GENERAL_CLIENT_REMOTE_CFG
/* -------------------------           */


/**
 * MDS行情訂閱資訊配置
 */
typedef MdsMktDataRequestReqBufT    MdsApiSubscribeInfoT;


/* 結構體的初始化值定義 */
#define NULLOBJ_MDSAPI_SUBSCRIBE_INFO           \
        NULLOBJ_MDS_MKT_DATA_REQUEST_REQ_BUF
/* -------------------------           */


/**
 * 完整的MDS客戶端配置資訊
 */
typedef struct _MdsApiClientCfg {
    MdsApiRemoteCfgT        tcpChannelCfg;      /**< TCP行情訂閱服務配置 */
    MdsApiRemoteCfgT        qryChannelCfg;      /**< 行情查詢服務配置 */

    MdsApiRemoteCfgT        udpL1ChannelCfg;    /**< L1快照行情組播服務配置 */
    MdsApiRemoteCfgT        udpL2ChannelCfg;    /**< L2快照行情組播服務配置 */
    union {
        MdsApiRemoteCfgT    udpTick1ChannelCfg; /**< L2逐筆資料(頻道1)組播服務配置 */
        MdsApiRemoteCfgT    udpTradeChannelCfg; /**< @deprecated 已廢棄, 為了保持相容而暫時保留 */
    };
    union {
        MdsApiRemoteCfgT    udpTick2ChannelCfg; /**< L2逐筆資料(頻道2)組播服務配置 */
        MdsApiRemoteCfgT    udpOrderChannelCfg; /**< @deprecated 已廢棄, 為了保持相容而暫時保留 */
    };

    MdsApiSubscribeInfoT    subscribeInfo;      /**< TCP行情的行情訂閱資訊 */
} MdsApiClientCfgT;


/* 結構體的初始化值定義 */
#define NULLOBJ_MDSAPI_CLIENT_CFG               \
        {NULLOBJ_MDSAPI_REMOTE_CFG}, \
        {NULLOBJ_MDSAPI_REMOTE_CFG}, \
        {NULLOBJ_MDSAPI_REMOTE_CFG}, \
        {NULLOBJ_MDSAPI_REMOTE_CFG}, \
        {{NULLOBJ_MDSAPI_REMOTE_CFG}}, \
        {{NULLOBJ_MDSAPI_REMOTE_CFG}}, \
        {NULLOBJ_MDSAPI_SUBSCRIBE_INFO}
/* -------------------------           */


/**
 * MDS客戶端執行時環境
 */
typedef struct _MdsApiClientEnv {
    MdsApiSessionInfoT      tcpChannel;         /**< TCP行情訂閱通道的會話資訊 */
    MdsApiSessionInfoT      qryChannel;         /**< 行情查詢通道的會話資訊 */

    MdsApiSessionInfoT      udpL1Channel;       /**< L1快照行情組播通道的會話資訊 */
    MdsApiSessionInfoT      udpL2Channel;       /**< L2快照行情組播通道的會話資訊 */
    union {
        MdsApiSessionInfoT  udpTick1Channel;    /**< L2逐筆資料(頻道1)組播通道的會話資訊 */
        MdsApiSessionInfoT  udpTradeChannel;    /**< @deprecated 已廢棄, 為了保持相容而暫時保留 */
    };
    union {
        MdsApiSessionInfoT  udpTick2Channel;    /**< L2逐筆資料(頻道2)組播通道的會話資訊 */
        MdsApiSessionInfoT  udpOrderChannel;    /**< @deprecated 已廢棄, 為了保持相容而暫時保留 */
    };

    MdsApiChannelGroupT     udpChannelGroup;    /**< 用於管理多個行情組播會話的通道組資訊 */
} MdsApiClientEnvT;


/* 結構體的初始化值定義 */
#define NULLOBJ_MDSAPI_CLIENT_ENV               \
        {NULLOBJ_MDSAPI_SESSION_INFO}, \
        {NULLOBJ_MDSAPI_SESSION_INFO}, \
        {NULLOBJ_MDSAPI_SESSION_INFO}, \
        {NULLOBJ_MDSAPI_SESSION_INFO}, \
        {{NULLOBJ_MDSAPI_SESSION_INFO}}, \
        {{NULLOBJ_MDSAPI_SESSION_INFO}}, \
        {NULLOBJ_MDSAPI_CHANNEL_GROUP}
/* -------------------------           */


/* ===================================================================
 * 回撥函式的函式原型定義
 * =================================================================== */

/**
 * 對接收到的訊息進行訊息處理的回撥函式的函式原型定義
 *
 * @param   pSessionInfo        會話資訊
 * @param   pMsgHead            訊息頭
 * @param   pMsgBody            訊息體資料
 * @param   pCallbackParams     外部傳入的引數
 * @return  大於等於0, 成功；小於0, 失敗（錯誤號）
 *
 * @see     eMdsMsgTypeT
 */
typedef int32   (*F_MDSAPI_ONMSG_T) (
                MdsApiSessionInfoT *pSessionInfo,
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
 * @return  大於等於0, 成功；小於0, 失敗（錯誤號）
 *
 * @see     eMdsMsgTypeT
 */
typedef int32   (*F_MDSAPI_ON_QRY_MSG_T) (
                MdsApiSessionInfoT *pSessionInfo,
                SMsgHeadT *pMsgHead,
                void *pMsgBody,
                MdsQryCursorT *pQryCursor,
                void *pCallbackParams);
/* -------------------------           */


/* ===================================================================
 * 基於TCP協議的行情服務介面函式宣告
 * =================================================================== */

/*
 * 連線並登入到行情伺服器
 *
 * @param[out]  pOutSessionInfo 輸出會話資訊
 * @param       channelType     通道型別
 * @param       pUri            URI地址 (e.g. tcp://127.0.0.1:5100)
 * @param       pUsername       使用者名稱
 * @param       pPassword       密碼
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
BOOL    MdsApi_Logon(
                MdsApiSessionInfoT *pOutSessionInfo,
                eMdsApiChannelTypeT channelType,
                const char *pUri,
                const char *pUsername,
                const char *pPassword,
                int32 heartBtInt,
                const SSocketOptionConfigT *pSocketOptions);

/*
 * 連線並登入到行情服務叢集 (基於複製集的高可用叢集)
 *
 * - 待解析的地址列表可是以空格、逗號或分號分割的地址列表字串
 *   - e.g. "tcp://127.0.0.1:5100, tcp://192.168.0.11:5100"
 * - 同時也可以在每個地址之前, 為其指定對應的主機編號
 *   - e.g. "2 tcp://192.168.0.12:5100, 1 tcp://192.168.0.11:5100,
 *          3 tcp://192.168.0.13:5100"
 *
 * @param[out]  pOutSessionInfo 輸出會話資訊
 * @param       channelType     通道型別
 * @param       pUriList        主機地址列表 (以空格、逗號或分號分割的地址列表字串)
 * @param       pUsername       使用者名稱
 * @param       pPassword       密碼
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
BOOL    MdsApi_LogonReplicaSet(
                MdsApiSessionInfoT *pOutSessionInfo,
                eMdsApiChannelTypeT channelType,
                const char *pUriList,
                const char *pUsername,
                const char *pPassword,
                int32 heartBtInt,
                const SSocketOptionConfigT *pSocketOptions);

/*
 * 連線並登入到行情服務叢集 (基於對等節點的行情叢集)
 *
 * - 待解析的地址列表可是以空格、逗號或分號分割的地址列表字串
 *   - e.g. "tcp://127.0.0.1:5100, tcp://192.168.0.11:5100"
 * - 同時也可以在每個地址之前, 為其指定對應的主機編號
 *   - e.g. "2 tcp://192.168.0.12:5100, 1 tcp://192.168.0.11:5100,
 *          3 tcp://192.168.0.13:5100"
 *
 * @param[out]  pOutSessionInfo 輸出會話資訊
 * @param       channelType     通道型別
 * @param       pUriList        主機地址列表 (以空格、逗號或分號分割的地址列表字串)
 * @param       pUsername       使用者名稱
 * @param       pPassword       密碼
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
BOOL    MdsApi_LogonPeerNodes(
                MdsApiSessionInfoT *pOutSessionInfo,
                eMdsApiChannelTypeT channelType,
                const char *pUriList,
                const char *pUsername,
                const char *pPassword,
                int32 heartBtInt,
                const SSocketOptionConfigT *pSocketOptions);

/*
 * 傳送證券行情訂閱訊息, 並同步等待應答訊息的返回 (僅適用於連線建立後的初次訂閱)
 *
 * @param   pTcpChannel         會話資訊
 * @param   pMktDataRequestReq  行情訂閱請求資訊
 * @param   pEntries            產品訂閱列表
 * @return  TRUE 成功; FALSE 失敗
 */
BOOL    MdsApi_SyncSubscribeOnLogon(
                MdsApiSessionInfoT *pSessionInfo,
                const MdsMktDataRequestReqT *pMktDataRequestReq,
                const MdsMktDataRequestEntryT *pEntries);

/*
 * 以非同步的方式傳送證券行情實時訂閱請求, 以重新訂閱、追加訂閱或刪除訂閱行情資料
 *
 * @param   pTcpChannel         會話資訊
 * @param   pMktDataRequestReq  行情訂閱請求資訊
 * @param   pEntries            產品訂閱列表
 * @return  TRUE 成功; FALSE 失敗
 */
BOOL    MdsApi_SubscribeMarketData(
                MdsApiSessionInfoT *pSessionInfo,
                const MdsMktDataRequestReqT *pMktDataRequestReq,
                const MdsMktDataRequestEntryT *pEntries);

/*
 * 直接根據字串形式的證券程式碼列表訂閱行情資訊
 *
 * @note    為相容之前的版本, 該介面無法指定 tickType 訂閱引數, 預設會按照 tickType=0 的模式訂閱行情。
 *          可以通過 <code>MdsHelper_SetTickTypeOnSubscribeByString</code> 介面為其指定
 *          tickType 引數, 後續的 SubscribeByString 呼叫都會使用該 tickType 引數。
 *
 * @param   pTcpChannel         會話資訊
 * @param   pSecurityListStr    證券程式碼列表字串
 *                              - 證券程式碼支援以 .SH 或 .SZ 為字尾來指定其所屬的交易所
 *                              - 空字串 "", 表示不訂閱任何產品的行情
 *                              - 空指標 NULL, 表示訂閱所有產品的行情
 * @param   pDelim              證券程式碼列表的分隔符 (e.g. ",;| \t")
 *                              - 如果為空, 則使用預設的分隔符:
 *                                ',' 或 ';' 或 '|' 或 ' ' 或 '\t'
 * @param   exchangeId          證券程式碼所屬的交易所程式碼 (如果證券程式碼沒有 .SH 或 .SZ 字尾的話)
 * @param   mdProductType       行情類別 (股票(基金、債券)/指數/期權)
 * @param   subMode             訂閱模式 (重新訂閱/追加訂閱/刪除訂閱)
 * @param   dataTypes           訂閱的資料種類 (e.g. MDS_SUB_DATA_TYPE_L1_SNAPSHOT
 *                              | MDS_SUB_DATA_TYPE_L2_SNAPSHOT
 *                              | MDS_SUB_DATA_TYPE_L2_BEST_ORDERS
 *                              | MDS_SUB_DATA_TYPE_L2_TRADE)
 *                              @see eMdsSubscribeDataTypeT
 * @return  TRUE 成功; FALSE 失敗
 *
 * @see     MdsHelper_SetTickTypeOnSubscribeByString
 */
BOOL    MdsApi_SubscribeByString(
                MdsApiSessionInfoT *pTcpChannel,
                const char *pSecurityListStr,
                const char *pDelim,
                eMdsExchangeIdT exchangeId,
                eMdsMdProductTypeT mdProductType,
                eMdsSubscribeModeT subMode,
                int32 dataTypes);

/*
 * 根據字串指標陣列形式的證券程式碼列表訂閱行情資訊
 *
 * @note    為相容之前的版本, 該介面無法指定 tickType 訂閱引數, 預設會按照 tickType=0 的模式訂閱行情。
 *          可以通過 <code>MdsHelper_SetTickTypeOnSubscribeByString</code> 介面為其指定
 *          tickType 引數, 後續的 SubscribeByString 呼叫都會使用該 tickType 引數。
 *
 * @param   pTcpChannel         會話資訊
 * @param   ppSecurityArray     證券程式碼列表的指標陣列
 *                              - 證券程式碼支援以 .SH 或 .SZ 為字尾來指定其所屬的交易所
 *                              - 空陣列 (指標非空, 但 securityCount == 0), 表示不訂閱任何產品的行情
 *                              - 空指標 NULL, 表示訂閱所有產品的行情
 * @param   securityCount       證券程式碼數量
 * @param   exchangeId          證券程式碼所屬的交易所程式碼 (如果證券程式碼沒有 .SH 或 .SZ 字尾的話)
 * @param   mdProductType       行情類別 (股票(基金、債券)/指數/期權)
 * @param   subMode             訂閱模式 (重新訂閱/追加訂閱/刪除訂閱)
 * @param   dataTypes           訂閱的資料種類 (e.g. MDS_SUB_DATA_TYPE_L1_SNAPSHOT
 *                              | MDS_SUB_DATA_TYPE_L2_SNAPSHOT
 *                              | MDS_SUB_DATA_TYPE_L2_BEST_ORDERS
 *                              | MDS_SUB_DATA_TYPE_L2_TRADE)
 *                              @see eMdsSubscribeDataTypeT
 * @return  TRUE 成功; FALSE 失敗
 *
 * @see     MdsHelper_SetTickTypeOnSubscribeByString
 */
BOOL    MdsApi_SubscribeByString2(
                MdsApiSessionInfoT *pTcpChannel,
                const char *ppSecurityArray[],
                int32 securityCount,
                eMdsExchangeIdT exchangeId,
                eMdsMdProductTypeT mdProductType,
                eMdsSubscribeModeT subMode,
                int32 dataTypes);

/*
 * 直接根據字串形式的證券程式碼列表和證券程式碼字首列表訂閱行情資訊
 *
 * @note    為相容之前的版本, 該介面無法指定 tickType 訂閱引數, 預設會按照 tickType=0 的模式訂閱行情。
 *          可以通過 <code>MdsHelper_SetTickTypeOnSubscribeByString</code> 介面為其指定
 *          tickType 引數, 後續的 SubscribeByString 呼叫都會使用該 tickType 引數。
 *
 * @param   pTcpChannel         會話資訊
 * @param   pSecurityListStr    證券程式碼列表字串
 *                              - 證券程式碼支援以 .SH 或 .SZ 為字尾來指定其所屬的交易所
 *                              - 空字串 "", 表示不訂閱任何產品的行情
 *                              - 空指標 NULL, 表示訂閱所有產品的行情
 * @param   pDelim              證券程式碼列表的分隔符 (e.g. ",;| \t")
 *                              - 如果為空, 則使用預設的分隔符:
 *                                ',' 或 ';' 或 '|' 或 ' ' 或 '\t'
 * @param   pSseCodePrefixes    以逗號或空格分隔的上海證券程式碼字首列表, e.g.
 *                              - "6, 300, 301" 將匹配證券程式碼列表中所有以 '6' 或 '300'
 *                                或 '301' 起始的證券程式碼
 *                              - 若為NULL或空字串, 則不會匹配任何證券程式碼
 *                              - 上海證券程式碼字首參考:
 *                                  - "009, 01, 02, "               //國債
 *                                  - "10, 11, 12, 13, 18, 19, "    //債券 (企業債、可轉債等)
 *                                  - "20, "                        //債券 (回購)
 *                                  - "5, "                         //基金
 *                                  - "6, "                         //A股
 *                                  - "000"                         //指數
 * @param   pSzseCodePrefixes   以逗號或空格分隔的深圳證券程式碼字首列表
 *                              - 若為NULL或空字串, 則不會匹配任何證券程式碼
 *                              - 證券程式碼字首可以和上海相同, 此時匹配的證券程式碼會同時對上海
 *                                和深圳兩個市場進行訂閱
 *                              - 深圳證券程式碼字首參考:
 *                                  - "00, "                        //股票
 *                                  - "10, 11, 12, 13, "            //債券
 *                                  - "15, 16, 17, 18, "            //基金
 *                                  - "30, "                        //創業板
 *                                  - "39"                          //指數
 * @param   mdProductType       行情類別 (股票(基金、債券)/指數/期權)
 * @param   subMode             訂閱模式 (重新訂閱/追加訂閱/刪除訂閱)
 * @param   dataTypes           訂閱的資料種類 (e.g. MDS_SUB_DATA_TYPE_L1_SNAPSHOT
 *                              | MDS_SUB_DATA_TYPE_L2_SNAPSHOT
 *                              | MDS_SUB_DATA_TYPE_L2_BEST_ORDERS
 *                              | MDS_SUB_DATA_TYPE_L2_TRADE)
 *                              @see eMdsSubscribeDataTypeT
 * @return  TRUE 成功; FALSE 失敗
 *
 * @see     MdsHelper_SetTickTypeOnSubscribeByString
 */
BOOL    MdsApi_SubscribeByStringAndPrefixes(
                MdsApiSessionInfoT *pTcpChannel,
                const char *pSecurityListStr,
                const char *pDelim,
                const char *pSseCodePrefixes,
                const char *pSzseCodePrefixes,
                eMdsMdProductTypeT mdProductType,
                eMdsSubscribeModeT subMode,
                int32 dataTypes);

/*
 * 根據字串指標陣列形式的證券程式碼列表以及證券程式碼字首列表訂閱行情資訊
 *
 * @note    為相容之前的版本, 該介面無法指定 tickType 訂閱引數, 預設會按照 tickType=0 的模式訂閱行情。
 *          可以通過 <code>MdsHelper_SetTickTypeOnSubscribeByString</code> 介面為其指定
 *          tickType 引數, 後續的 SubscribeByString 呼叫都會使用該 tickType 引數。
 *
 * @param   pTcpChannel         會話資訊
 * @param   ppSecurityArray     證券程式碼列表的指標陣列
 *                              - 證券程式碼支援以 .SH 或 .SZ 為字尾來指定其所屬的交易所
 *                              - 空字串 "", 表示不訂閱任何產品的行情
 *                              - 空指標 NULL, 表示訂閱所有產品的行情
 * @param   securityCount       證券程式碼數量
 * @param   pSseCodePrefixes    以逗號或空格分隔的上海證券程式碼字首列表, e.g.
 *                              - "6, 300, 301" 將匹配證券程式碼列表中所有以 '6' 或 '300'
 *                                或 '301' 起始的證券程式碼
 *                              - 若為NULL或空字串, 則不會匹配任何證券程式碼
 *                              - 上海證券程式碼字首參考:
 *                                  - "009, 01, 02, "               //國債
 *                                  - "10, 11, 12, 13, 18, 19, "    //債券 (企業債、可轉債等)
 *                                  - "20, "                        //債券 (回購)
 *                                  - "5, "                         //基金
 *                                  - "6, "                         //A股
 *                                  - "000"                         //指數
 * @param   pSzseCodePrefixes   以逗號或空格分隔的深圳證券程式碼字首列表
 *                              - 若為NULL或空字串, 則不會匹配任何證券程式碼
 *                              - 證券程式碼字首可以和上海相同, 此時匹配的證券程式碼會同時對上海
 *                                和深圳兩個市場進行訂閱
 *                              - 深圳證券程式碼字首參考:
 *                                  - "00, "                        //股票
 *                                  - "10, 11, 12, 13, "            //債券
 *                                  - "15, 16, 17, 18, "            //基金
 *                                  - "30, "                        //創業板
 *                                  - "39"                          //指數
 * @param   mdProductType       行情類別 (股票(基金、債券)/指數/期權)
 * @param   subMode             訂閱模式 (重新訂閱/追加訂閱/刪除訂閱)
 * @param   dataTypes           訂閱的資料種類 (e.g. MDS_SUB_DATA_TYPE_L1_SNAPSHOT
 *                              | MDS_SUB_DATA_TYPE_L2_SNAPSHOT
 *                              | MDS_SUB_DATA_TYPE_L2_BEST_ORDERS
 *                              | MDS_SUB_DATA_TYPE_L2_TRADE)
 *                              @see eMdsSubscribeDataTypeT
 * @return  TRUE 成功; FALSE 失敗
 *
 * @see     MdsHelper_SetTickTypeOnSubscribeByString
 */
BOOL    MdsApi_SubscribeByStringAndPrefixes2(
                MdsApiSessionInfoT *pTcpChannel,
                const char *ppSecurityArray[],
                int32 securityCount,
                const char *pSseCodePrefixes,
                const char *pSzseCodePrefixes,
                eMdsMdProductTypeT mdProductType,
                eMdsSubscribeModeT subMode,
                int32 dataTypes);

/*
 * 傳送心跳訊息
 *
 * @param   pSessionInfo        會話資訊
 * @return  TRUE 成功; FALSE 失敗
 */
BOOL    MdsApi_SendHeartbeat(
                MdsApiSessionInfoT *pSessionInfo);

/*
 * 傳送測試請求訊息
 *
 * @param   pSessionInfo        會話資訊
 * @param   pTestReqId          測試請求識別符號 (C32, 可以為空)
 * @param   testReqIdSize       測試請求識別符號的長度
 * @return  TRUE 成功; FALSE 失敗
 */
BOOL    MdsApi_SendTestRequest(
                MdsApiSessionInfoT *pSessionInfo,
                const char *pTestReqId,
                int32 testReqIdSize);

/*
 * 傳送登出訊息
 *
 * @param   pSessionInfo        會話資訊
 * @param   isDestory           傳送登出訊息後是否立即釋放相關資源
 * @return  TRUE 成功; FALSE 失敗
 */
BOOL    MdsApi_Logout(
                MdsApiSessionInfoT *pSessionInfo,
                BOOL isDestory);

/*
 * 直接斷開與伺服器的連線並釋放會話資料
 *
 * @param   pSessionInfo        會話資訊
 */
void    MdsApi_Destory(
                MdsApiSessionInfoT *pSessionInfo);

/*
 * 阻塞接收MDS行情訊息, 並呼叫回撥函式進行訊息處理
 * 阻塞等待直到完整的訊息接收完成或超時
 *
 * @param   pTcpChannel         會話資訊
 * @param   timeoutMs           超時時間(毫秒)
 * @param   pOnMsgCallback      進行訊息處理的回撥函式
 * @param   pCallbackParams     回撥函式的引數
 * @return  大於等於0, 成功 (返回回撥函式的返回值);
 *          小於0, 失敗 (負的錯誤號)
 *
 * @exception   NEG(ETIMEDOUT)  超時
 * @exception   NEG(EPIPE)      連線已破裂
 * @exception   Others          由read()系統呼叫或回撥函式pOnMsgCallback返回的錯誤
 */
int32   MdsApi_WaitOnMsg(
                MdsApiSessionInfoT *pTcpChannel,
                int32 timeoutMs,
                F_MDSAPI_ONMSG_T pOnMsgCallback,
                void *pCallbackParams);

/*
 * 阻塞接收MDS行情訊息, 並呼叫回撥函式進行訊息處理 (可以處理壓縮過的訊息)
 *
 * - 與不帶 Compressible 字尾的介面相比, 帶 Compressible 字尾的介面會自動檢測和處理壓縮過的
 *   訊息, 但也會因此帶來微小的效能損失。
 * - 如果對延遲不是極端敏感的話, 可以直接使用帶 Compressible 字尾的介面, 以方便相容不同的模式。
 *
 * @param   pTcpChannel         會話資訊
 * @param   timeoutMs           超時時間(毫秒)
 * @param   pOnMsgCallback      進行訊息處理的回撥函式
 * @param   pCallbackParams     回撥函式的引數
 * @return  大於等於0, 成功 (返回回撥函式的返回值);
 *          小於0, 失敗 (負的錯誤號)
 *
 * @exception   NEG(ETIMEDOUT)  超時
 * @exception   NEG(EPIPE)      連線已破裂
 * @exception   Others          由read()系統呼叫或回撥函式pOnMsgCallback返回的錯誤
 */
int32   MdsApi_WaitOnMsgCompressible(
                MdsApiSessionInfoT *pTcpChannel,
                int32 timeoutMs,
                F_MDSAPI_ONMSG_T pOnMsgCallback,
                void *pCallbackParams);
/* -------------------------           */


/* ===================================================================
 * 查詢介面函式宣告
 * =================================================================== */

/*
 * 獲取API的發行版本號
 *
 * @return  API的發行版本號 (如: "0.15.3")
 */
const char *
        MdsApi_GetApiVersion();

/*
 * 查詢證券行情快照
 *
 * @param       pQryChannel     會話資訊
 * @param       exchangeId      交易所程式碼
 * @param       mdProductType   行情類別
 * @param       instrId         產品程式碼
 * @param[out]  pRspBuf         用於輸出查詢結果的應答資料快取
 * @retval      =0              查詢成功
 * @retval      <0              查詢失敗 (負的錯誤號)
 * @exception   NEG(ENOENT)     未檢索到待查詢的資料
 *
 * @see         eMdsExchangeIdT
 * @see         eMdsMdProductTypeT
 */
int32   MdsApi_QueryMktDataSnapshot(
                MdsApiSessionInfoT *pQryChannel,
                eMdsExchangeIdT exchangeId,
                eMdsMdProductTypeT mdProductType,
                int32 instrId,
                MdsMktDataSnapshotT *pRspBuf);

/*
 * 查詢(深圳)證券實時狀態
 *
 * @param       pQryChannel     會話資訊
 * @param       exchangeId      交易所程式碼
 * @param       mdProductType   行情類別
 * @param       instrId         產品程式碼
 * @param[out]  pRspBuf         用於輸出查詢結果的應答資料快取
 * @retval      =0              查詢成功
 * @retval      <0              查詢失敗 (負的錯誤號)
 * @exception   NEG(ENOENT)     未檢索到待查詢的資料
 *
 * @see         eMdsExchangeIdT
 * @see         eMdsMdProductTypeT
 */
int32   MdsApi_QuerySecurityStatus(
                MdsApiSessionInfoT *pQryChannel,
                eMdsExchangeIdT exchangeId,
                eMdsMdProductTypeT mdProductType,
                int32 instrId,
                MdsSecurityStatusMsgT *pRspBuf);

/*
 * 查詢(上證)市場狀態
 *
 * @param       pQryChannel     會話資訊
 * @param       exchangeId      交易所程式碼
 * @param       mdProductType   行情類別
 * @param       instrId         產品程式碼
 * @param[out]  pRspBuf         用於輸出查詢結果的應答資料快取
 * @retval      =0              查詢成功
 * @retval      <0              查詢失敗 (負的錯誤號)
 * @exception   NEG(ENOENT)     未檢索到待查詢的資料
 *
 * @see         eMdsExchangeIdT
 * @see         eMdsMdProductTypeT
 */
int32   MdsApi_QueryTrdSessionStatus(
                MdsApiSessionInfoT *pQryChannel,
                eMdsExchangeIdT exchangeId,
                eMdsMdProductTypeT mdProductType,
                MdsTradingSessionStatusMsgT *pRspBuf);

/*
 * 批量查詢證券(股票/債券/基金)靜態資訊
 *
 * @param   pQryChannel         會話資訊
 * @param   pQryFilter          查詢過濾條件
 *                              - 傳空指標或者將過濾條件初始化為0，將查詢所有資料
 * @param   pQryMsgCallback     進行訊息處理的回撥函式
 *                              - 訊息體的資料型別為 <code>MdsStockStaticInfoT</code>
 * @param   pCallbackParams     回撥函式的引數
 * @retval  >=0                 成功查詢到的記錄數
 * @retval  <0                  失敗 (負的錯誤號)
 *
 * @see     MdsStockStaticInfoT
 */
int32   MdsApi_QueryStockStaticInfo(
                MdsApiSessionInfoT *pQryChannel,
                const MdsQryStockStaticInfoFilterT *pQryFilter,
                F_MDSAPI_ON_QRY_MSG_T pQryMsgCallback,
                void *pCallbackParams);

/*
 * 批量查詢行情快照
 *
 * @param   pQryChannel         會話資訊
 * @param   pSecurityListStr    證券程式碼列表字串 (證券程式碼的最大數量限制為 200)
 *                              - 證券程式碼支援以 .SH 或 .SZ 為字尾來指定其所屬的交易所
 *                              - 空字串 "" 或 NULL, 表示查詢所有產品的行情 (不包括指數和期權)
 * @param   pDelim              證券程式碼列表的分隔符 (e.g. ",;| \t")
 *                              - 如果為空, 則使用預設的分隔符:
 *                                ',' 或 ';' 或 '|' 或 ' ' 或 '\t'
 * @param   pQryFilter          查詢過濾條件
 *                              - 傳空指標或者將過濾條件初始化為0，代表過濾條件不生效
 * @param   pQryMsgCallback     進行訊息處理的回撥函式
 *                              - 訊息體的資料型別為 <code>MdsL1SnapshotT</code>
 * @param   pCallbackParams     回撥函式的引數
 * @retval  >=0                 成功查詢到的記錄數
 * @retval  <0                  失敗 (負的錯誤號)
 *
 * @see     MdsL1SnapshotT
 */
int32   MdsApi_QuerySnapshotList(
                MdsApiSessionInfoT *pQryChannel,
                const char *pSecurityListStr,
                const char *pDelim,
                const MdsQrySnapshotListFilterT *pQryFilter,
                F_MDSAPI_ON_QRY_MSG_T pQryMsgCallback,
                void *pCallbackParams);

/*
 * 批量查詢行情快照 (根據字串指標陣列形式的證券程式碼列表)
 *
 * @param   pQryChannel         會話資訊
 * @param   ppSecurityArray     證券程式碼列表的指標陣列 (證券程式碼的最大數量限制為 200)
 *                              - 證券程式碼支援以 .SH 或 .SZ 為字尾來指定其所屬的交易所
 *                              - 空指標NULL或程式碼數量為0, 表示查詢所有產品的行情 (不包括指數和期權)
 * @param   securityCount       證券程式碼數量
 * @param   pQryFilter          查詢過濾條件
 *                              - 傳空指標或者將過濾條件初始化為0，代表過濾條件不生效
 * @param   pQryMsgCallback     進行訊息處理的回撥函式
 *                              - 訊息體的資料型別為 <code>MdsL1SnapshotT</code>
 * @param   pCallbackParams     回撥函式的引數
 * @retval  >=0                 成功查詢到的記錄數
 * @retval  <0                  失敗 (負的錯誤號)
 *
 * @see     MdsL1SnapshotT
 */
int32   MdsApi_QuerySnapshotList2(
                MdsApiSessionInfoT *pQryChannel,
                const char *ppSecurityArray[],
                int32 securityCount,
                const MdsQrySnapshotListFilterT *pQryFilter,
                F_MDSAPI_ON_QRY_MSG_T pQryMsgCallback,
                void *pCallbackParams);
/* -------------------------           */


/* ===================================================================
 * 密碼修改指令介面函式宣告
 * =================================================================== */

/*
 * 傳送密碼修改請求 (修改客戶端登入密碼)
 * 密碼修改請求通過查詢通道傳送到MDS伺服器, 並將採用同步請求/應答的方式直接返回處理結果
 *
 * @param       pQryChannel     會話資訊
 * @param[in]   pChangePasswordReq
 *                              待發送的密碼修改請求
 * @param[out]  pOutChangePasswordRsp
 *                              用於輸出測試請求應答的快取區
 * @retval      0               成功
 * @retval      <0              API呼叫失敗 (負的錯誤號)
 * @retval      >0              服務端業務處理失敗 (MDS錯誤號)
 *
 * @exception   NEG(EINVAL)     傳入引數非法
 * @exception   NEG(EPIPE)      連線已破裂
 * @exception   NEG(Others)     由send()系統呼叫返回的錯誤
 */
int32   MdsApi_SendChangePasswordReq(
                MdsApiSessionInfoT *pQryChannel,
                const MdsChangePasswordReqT *pChangePasswordReq,
                MdsChangePasswordRspT *pOutChangePasswordRsp);
/* -------------------------           */


/* ===================================================================
 * 基於UDP協議的行情服務介面函式宣告
 * =================================================================== */

/*
 * 建立與行情伺服器的UDP(組播)連線
 *
 * @param[out]  pOutSessionInfo 輸出會話資訊
 * @param       pUri            URI地址 (e.g. udp-mcast://239.1.150.100:5300)
 * @param       pSocketOptions  套接字引數 (為空, 則會使用預設引數)
 * @return      TRUE 成功; FALSE 失敗
 */
BOOL    MdsApi_ConnectToUdpMcast(
                MdsApiSessionInfoT *pOutSessionInfo,
                const char *pUri,
                const SSocketOptionConfigT *pSocketOptions);

/*
 * 阻塞接收MDS-UDP行情訊息, 並呼叫回撥函式進行訊息處理
 * 阻塞等待直到完整的訊息接收完成或超時
 *
 * @param       pUdpChannel     會話資訊
 * @param       timeoutMs       超時時間(毫秒)
 * @param       pOnMsgCallback  進行訊息處理的回撥函式
 * @param       pCallbackParams 回撥函式的引數
 * @return      大於等於0, 成功 (返回回撥函式的返回值);
 *              小於0, 失敗 (負的錯誤號)
 *
 * @exception   NEG(ETIMEDOUT)  超時
 * @exception   NEG(EPIPE)      連線已破裂
 * @exception   Others          由read()系統呼叫或回撥函式pOnMsgCallback返回的錯誤
 */
int32   MdsApi_WaitOnUdpMsg(
                MdsApiSessionInfoT *pUdpChannel,
                int32 timeoutMs,
                F_MDSAPI_ONMSG_T pOnMsgCallback,
                void *pCallbackParams);
/* -------------------------           */


/* ===================================================================
 * 完整的行情客戶端環境的統一初始化和析構介面宣告
 * =================================================================== */

/*
 * 完整的初始化行情客戶端環境
 *
 * @param[out]  pOutCliEnv      輸出行情客戶端環境資訊
 * @param       pCfgFile        配置檔案路徑
 * @param       pLoggerSection  日誌記錄器的配置區段名稱
 * @param       pCfgSection     行情客戶端配置區段名稱
 * @param       pTcpAddrKey     TCP行情訂閱地址的配置項關鍵字 (為空或配置項未設定則不連線)
 * @param       pQryAddrKey     行情查詢服務地址的配置項關鍵字 (為空或配置項未設定則不連線)
 * @param       pUdpL1AddrKey   L1快照行情組播地址的配置項關鍵字 (為空或配置項未設定則不連線)
 * @param       pUdpL2AddrKey   L2快照行情組播地址的配置項關鍵字 (為空或配置項未設定則不連線)
 * @param       pUdpTick1AddrKey
 *                              L2逐筆資料(頻道1)組播地址的配置項關鍵字 (為空或配置項未設定則不連線)
 * @param       pUdpTick2AddrKey
 *                              L2逐筆資料(頻道2)組播地址的配置項關鍵字 (為空或配置項未設定則不連線)
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
 * @see         MdsApi_InitAllByConvention
 * @see         MdsApi_InitAllByCfgStruct
 */
BOOL    MdsApi_InitAll(
                MdsApiClientEnvT *pOutCliEnv,
                const char *pCfgFile,
                const char *pLoggerSection,
                const char *pCfgSection,
                const char *pTcpAddrKey,
                const char *pQryAddrKey,
                const char *pUdpL1AddrKey,
                const char *pUdpL2AddrKey,
                const char *pUdpTick1AddrKey,
                const char *pUdpTick2AddrKey);

/*
 * 按照預設的配置名稱, 完整的初始化行情客戶端環境
 *
 * @param[out]  pOutCliEnv      輸出行情客戶端環境資訊
 * @param       pCfgFile        配置檔案路徑
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
 * @see         MdsApi_InitAll
 * @see         MdsApi_InitAllByCfgStruct
 */
BOOL    MdsApi_InitAllByConvention(
                MdsApiClientEnvT *pOutCliEnv,
                const char *pCfgFile);

/*
 * 按照配置資訊結構體, 初始化客戶端環境
 *
 * @note        與 MdsApi_InitAll 和 MdsApi_InitAllByConvention 介面有一處不同,
 *              MdsApi_InitAllByCfgStruct 介面不會自動初始化日誌記錄器, 需要在外面
 *              顯式的呼叫 MdsApi_InitLogger 來初始化API的日誌記錄器
 *
 * @param[out]  pOutCliEnv      輸出行情客戶端環境資訊
 * @param       pClientCfg      配置資訊結構體
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
 * @see         MdsApi_InitAll
 * @see         MdsApi_InitAllByConvention
 */
BOOL    MdsApi_InitAllByCfgStruct(
                MdsApiClientEnvT *pOutCliEnv,
                const MdsApiClientCfgT *pClientCfg);

/*
 * 登出並關閉所有的行情客戶端會話
 *
 * @param[out]  pCliEnv         行情客戶端環境資訊
 * @param       isDestory       是否立即釋放相關資源
 * @return      TRUE 成功; FALSE 失敗
 */
void    MdsApi_LogoutAll(MdsApiClientEnvT *pCliEnv, BOOL isDestory);

/*
 * 直接斷開與伺服器的連線並釋放會話資料
 *
 * @param[out]  pCliEnv         行情客戶端環境資訊
 */
void    MdsApi_DestoryAll(
                MdsApiClientEnvT *pCliEnv);
/* -------------------------           */


/* ===================================================================
 * 基於配置檔案的輔助介面函式宣告
 * =================================================================== */

/*
 * 初始化日誌記錄器
 *
 * @param       pCfgFile        配置檔案路徑
 * @param       pLoggerSection  日誌記錄器的配置區段名稱(為空則使用預設值)
 * @return      TRUE 成功; FALSE 失敗
 */
BOOL    MdsApi_InitLogger(
                const char *pCfgFile,
                const char *pLoggerSection);

/*
 * 重置執行緒級別的日誌記錄器名稱
 *
 * @param   pLogSystemName  執行緒級別的日誌系統名稱
 * @return  TRUE 成功; FALSE 失敗
 */
BOOL    MdsApi_ResetThreadLoggerName(
                const char *pLogSystemName);

/*
 * 初始化基於TCP協議的行情訂閱通道 (包括完整的配置解析、連線建立、登入和行情訂閱過程)
 *
 * @param[out]  pTcpChannel     TCP行情訂閱通道的會話資訊
 * @param       pCfgFile        配置檔案路徑
 * @param       pCfgSection     行情客戶端配置區段名稱(為空則使用預設值)
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
BOOL    MdsApi_InitTcpChannel(
                MdsApiSessionInfoT *pTcpChannel,
                const char *pCfgFile,
                const char *pCfgSection,
                const char *pAddrKey);

/*
 * 初始化基於TCP協議的行情訂閱通道 (包括完整的連線建立、登入和行情訂閱過程)
 *
 * @param[out]  pTcpChannel     TCP行情訂閱通道的會話資訊
 * @param       pRemoteCfg      遠端主機配置資訊
 * @param       pSubscribeInfo  行情訂閱配置資訊
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
BOOL    MdsApi_InitTcpChannel2(
                MdsApiSessionInfoT *pTcpChannel,
                const MdsApiRemoteCfgT *pRemoteCfg,
                const MdsApiSubscribeInfoT *pSubscribeInfo);

/*
 * 初始化行情查詢通道 (包括完整的配置解析、連線建立和登入過程)
 *
 * @param[out]  pQryChannel     行情查詢通道的會話資訊
 * @param       pCfgFile        配置檔案路徑
 * @param       pCfgSection     行情客戶端配置區段名稱(為空則使用預設值)
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
BOOL    MdsApi_InitQryChannel(
                MdsApiSessionInfoT *pQryChannel,
                const char *pCfgFile,
                const char *pCfgSection,
                const char *pAddrKey);

/*
 * 初始化行情查詢通道 (包括完整的連線建立和登入過程)
 *
 * @param[out]  pQryChannel     行情查詢通道的會話資訊
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
BOOL    MdsApi_InitQryChannel2(
                MdsApiSessionInfoT *pQryChannel,
                const MdsApiRemoteCfgT *pRemoteCfg);

/*
 * 初始化基於UDP協議的行情訂閱通道 (包括完整的配置解析和連線建立過程)
 *
 * @param[out]  pUdpChannel     UDP行情訂閱通道的會話資訊
 * @param       pCfgFile        配置檔案路徑
 * @param       pCfgSection     行情客戶端配置區段名稱(為空則使用預設值)
 * @param       pAddrKey        地址列表的配置項關鍵字(為空則使用預設值)
 * @retval      TRUE            成功
 * @retval      FALSE           失敗。此時 errno 將被設定, 可以通過 errno/SPK_GET_ERRNO() 獲取到具體失敗原因
 *
 * @exception   EINVAL          配置異常或傳入引數非法
 * @exception   ENOENT          地址列表中沒有找到有效的節點配置
 * @exception   Others          由系統呼叫返回的錯誤
 */
BOOL    MdsApi_InitUdpChannel(
                MdsApiSessionInfoT *pUdpChannel,
                const char *pCfgFile,
                const char *pCfgSection,
                const char *pAddrKey);

/*
 * 初始化基於UDP協議的行情訂閱通道 (包括完整的連線建立過程)
 *
 * @param[out]  pUdpChannel     UDP行情訂閱通道的會話資訊
 * @param       pRemoteCfg      遠端主機配置資訊
 * @retval      TRUE            成功
 * @retval      FALSE           失敗。此時 errno 將被設定, 可以通過 errno/SPK_GET_ERRNO() 獲取到具體失敗原因
 *
 * @exception   EINVAL          配置異常或傳入引數非法
 * @exception   ENOENT          地址列表中沒有找到有效的節點配置
 * @exception   Others          由系統呼叫返回的錯誤
 */
BOOL    MdsApi_InitUdpChannel2(
                MdsApiSessionInfoT *pUdpChannel,
                const MdsApiRemoteCfgT *pRemoteCfg);

/*
 * 解析伺服器地址列表字串
 *
 * - 待解析的地址列表可是以空格、逗號或分號分割的地址列表字串
 *   - e.g. "tcp://127.0.0.1:5100, tcp://192.168.0.11:5100"
 * - 同時也可以在每個地址之前, 為其指定對應的主機編號
 *   - e.g. "2 tcp://192.168.0.12:5100, 1 tcp://192.168.0.11:5100,
 *          3 tcp://192.168.0.13:5100"
 *
 * @param       pUriList        主機地址列表 (以空格、逗號或分號分割的地址列表字串)
 * @param[out]  pOutAddrList    用於輸出解析後的地址資訊的地址資訊陣列
 * @param       addrListLength  地址資訊列表的陣列長度
 * @return      大於等於0, 解析得到的地址數量; 小於0, 解析失敗
 */
int32   MdsApi_ParseAddrListString(
                const char *pUriList,
                MdsApiAddrInfoT *pOutAddrList,
                int32 addrListLength);

/*
 * 解析客戶端配置檔案
 *
 * @param       pCfgFile        配置檔案路徑
 * @param       pSection        配置區段名稱
 * @param       pAddrKey        地址列表的配置項關鍵字
 * @param[out]  pOutRemoteCfg   輸出遠端主機配置資訊
 * @param[out]  pOutSubscribeInfo   輸出行情訂閱資訊
 * @return      TRUE 成功; FALSE 失敗
 */
BOOL    MdsApi_ParseConfigFromFile(
                const char *pCfgFile,
                const char *pSection,
                const char *pAddrKey,
                MdsApiRemoteCfgT *pOutRemoteCfg,
                MdsApiSubscribeInfoT *pOutSubscribeInfo);

/*
 * 按照預設的配置名稱, 從配置檔案中解析所有配置資訊
 *
 * @param       pCfgFile        配置檔案路徑
 * @param[out]  pOutApiCfg      輸出遠端主機配置資訊
 * @return      TRUE 成功; FALSE 失敗
 */
BOOL    MdsApi_ParseAllConfig(
                const char *pCfgFile,
                MdsApiClientCfgT *pOutApiCfg);
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
BOOL    MdsApi_InitChannelGroup(
                MdsApiChannelGroupT *pChannelGroup);

/*
 * 銷燬通道組資訊 (同時關閉通道組下的所有連線)
 *
 * @param       pChannelGroup   通道組資訊
 * @return      TRUE, 成功; FALSE 失敗
 */
BOOL    MdsApi_DestoryChannelGroup(
                MdsApiChannelGroupT *pChannelGroup);

/*
 * 將連線資訊新增到通道組
 *
 * @note        在檢測通道組下各連線的I/O事件時, 是從後向前進行掃描的, 所以建議將更
 *              活躍的連線新增到其它連線的後面
 *
 * @param       pChannelGroup   通道組資訊
 * @param       pChannel        連線資訊
 * @return      TRUE, 成功; FALSE 失敗
 */
BOOL    MdsApi_AddToChannelGroup(
                MdsApiChannelGroupT *pChannelGroup,
                MdsApiSessionInfoT *pChannel);

/*
 * 從通道組中刪除連線
 *
 * @param       pChannelGroup   通道組資訊
 * @param       pTargetChannel  待刪除連線的連線資訊
 * @return      TRUE, 成功; FALSE 失敗
 */
BOOL    MdsApi_DeleteFromChannelGroup(
                MdsApiChannelGroupT *pChannelGroup,
                MdsApiSessionInfoT *pTargetChanne);

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
MdsApiSessionInfoT *
        MdsApi_GetFromChannelGroup(
                MdsApiChannelGroupT *pChannelGroup,
                int32 index);

/*
 * 獲取通道組中與指定Socket描述符相匹配的連線資訊
 *
 * @param       pChannelGroup   通道組資訊
 * @param       socketFd        Socket描述符
 * @return      連線資訊
 */
MdsApiSessionInfoT *
        MdsApi_GetFromChannelGroupBySocket(
                MdsApiChannelGroupT *pChannelGroup,
                SPK_SOCKET socketFd);

/*
 * 遍歷通道組下的所有通道資訊並執行回撥函式
 *
 * @param       pChannelGroup   通道組資訊
 * @param       fnCallback      待執行的回撥函式
 * @param       pParams         回撥函式的引數
 * @return      0, 成功; 小於 0, errno 取負
 */
int32   MdsApi_ForeachInChannelGroup(
                MdsApiChannelGroupT *pChannelGroup,
                int32 (*fnCallback)(MdsApiSessionInfoT *pChannel, void *pParams),
                void *pParams);

/*
 * 檢測TCP通道組下各連線通道的讀事件, 並呼叫回撥函式進行訊息處理
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
int32   MdsApi_WaitOnTcpChannelGroup(
                MdsApiChannelGroupT *pChannelGroup,
                int32 timeoutMs,
                F_MDSAPI_ONMSG_T pOnMsgCallback,
                void *pCallbackParams,
                MdsApiSessionInfoT **ppFailed);

/*
 * 檢測TCP通道組下各連線通道的讀事件, 並呼叫回撥函式進行訊息處理 (可以處理壓縮過的訊息)
 *
 * - 與不帶 Compressible 字尾的介面相比, 帶 Compressible 字尾的介面會自動檢測和處理壓縮過的
 *   訊息, 但也會因此帶來微小的效能損失。
 * - 如果對延遲不是極端敏感的話, 可以直接使用帶 Compressible 字尾的介面, 以方便相容不同的模式。
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
int32   MdsApi_WaitOnTcpChannelGroupCompressible(
                MdsApiChannelGroupT *pChannelGroup,
                int32 timeoutMs,
                F_MDSAPI_ONMSG_T pOnMsgCallback,
                void *pCallbackParams,
                MdsApiSessionInfoT **ppFailed);

/*
 * 檢測UDP通道組下各連線通道的讀事件, 並呼叫回撥函式進行訊息處理
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
int32   MdsApi_WaitOnUdpChannelGroup(
                MdsApiChannelGroupT *pChannelGroup,
                int32 timeoutMs,
                F_MDSAPI_ONMSG_T pOnMsgCallback,
                void *pCallbackParams,
                MdsApiSessionInfoT **ppFailed);
/* -------------------------           */


/* ===================================================================
 * 錯誤處理等輔助函式
 * =================================================================== */

/*
 * 設定當前執行緒登入MDS時使用的登入使用者名稱
 * 不設定或者引數為空的話, 登入時會嘗試使用配置檔案中的配置
 *
 * @param   pUsername           登入使用者名稱
 */
void    MdsApi_SetThreadUsername(
                const char *pUsername);

/*
 * 返回當前執行緒登入MDS時使用的登入使用者名稱
 *
 * @return  登入使用者名稱
 */
const char *
        MdsApi_GetThreadUsername();

/*
 * 設定當前執行緒登入MDS時使用的登入密碼
 * 不設定或者引數為空的話, 登入時會嘗試使用配置檔案中的配置
 *
 * @param   pPassword           登入密碼
 *                              - 支援通過密碼字首指定密碼型別, 如 md5:PASSWORD, txt:PASSWORD
 */
void    MdsApi_SetThreadPassword(
                const char *pPassword);

/*
 * 設定客戶端自定義的本地IP地址
 *
 * @param   pIpStr              點分十進位制的IP地址字串
 * @return  TRUE 設定成功; FALSE 設定失敗 (引數格式錯誤)
 */
BOOL    MdsApi_SetCustomizedIp(
                const char *pIpStr);

/*
 * 設定客戶端自定義的本地MAC地址
 *
 * @param   pMacStr             MAC地址字串 (MAC地址格式 45:38:56:89:78:5A)
 * @return  TRUE 設定成功; FALSE 設定失敗 (引數格式錯誤)
 */
BOOL    MdsApi_SetCustomizedMac(
                const char *pMacStr);

/*
 * 獲取客戶端自定義的本地IP
 *
 * @return  客戶端自定義的本地IP
 */
const char *
        MdsApi_GetCustomizedIp();

/*
 * 獲取客戶端自定義的本地MAC
 *
 * @return  客戶端自定義的本地MAC
 */
const char *
        MdsApi_GetCustomizedMac();

/*
 * 設定客戶端自定義的本地裝置序列號
 *
 * @param   pDriverId           裝置序列號字串
 * @return  TRUE 設定成功; FALSE 設定失敗 (引數格式錯誤)
 */
BOOL    MdsApi_SetCustomizedDriverId(
                const char *pDriverId);

/*
 * 獲取客戶端自定義的本地裝置序列號
 *
 * @return  客戶端自定義的本地裝置序列號
 */
const char *
        MdsApi_GetCustomizedDriverId();

/*
 * 獲取通道最新接受訊息時間
 *
 * @param   pSessionInfo        會話資訊
 * @return  通道最新接受訊息時間(單位: 秒)
 */
int64   MdsApi_GetLastRecvTime(
                const MdsApiSessionInfoT *pSessionInfo);

/*
 * 獲取通道最新發送訊息時間
 *
 * @param   pSessionInfo        會話資訊
 * @return  通道最新發送訊息時間(單位: 秒)
 */
int64   MdsApi_GetLastSendTime(
                const MdsApiSessionInfoT *pSessionInfo);

/*
 * 返回行情訂閱通道是否還有更多已接收但尚未回撥處理完成的資料
 *
 * @param   pTcpChannel         會話資訊
 * @return  已接收到但尚未處理完成的資料長度
 * @note    當在回撥函式裡面呼叫時, 該介面返回的資料長度是包含本次回撥資料的
 */
int32   MdsApi_HasMoreCachedData(
                const MdsApiSessionInfoT *pTcpChannel);

/*
 * 返回基於TCP協議的行情訂閱通道是否已經連線且有效
 *
 * @param   pTcpChannel         會話資訊
 * @return  TRUE 已連線; FALSE 未連線或連線無效
 */
BOOL    MdsApi_IsValidTcpChannel(
                const MdsApiSessionInfoT *pTcpChannel);

/*
 * 返回行情查詢通道是否已經連線且有效
 *
 * @param   pQryChannel         會話資訊
 * @return  TRUE 已連線; FALSE 未連線或連線無效
 */
BOOL    MdsApi_IsValidQryChannel(
                const MdsApiSessionInfoT *pQryChannel);

/*
 * 返回基於UDP協議的行情組播通道是否已經連線且有效
 *
 * @param   pUdpChannel         會話資訊
 * @return  TRUE 已連線; FALSE 未連線或連線無效
 */
BOOL    MdsApi_IsValidUdpChannel(
                const MdsApiSessionInfoT *pUdpChannel);

/*
 * 返回通道組是否已經連線
 *
 * @param   pChannelGroup       通道組資訊
 * @return  TRUE 已連線; FALSE 未連線或連線無效
 */
BOOL    MdsApi_IsValidChannelGroup(
                const MdsApiChannelGroupT *pChannelGroup);

/*
 * 返回當前執行緒最近一次API呼叫失敗的錯誤號
 *
 * @return  錯誤號
 */
int32   MdsApi_GetLastError();

/*
 * 設定當前執行緒的API錯誤號
 *
 * @param   errCode             錯誤號
 */
void    MdsApi_SetLastError(
                int32 errCode);

/*
 * 返回錯誤號對應的錯誤資訊
 *
 * @param   errCode             錯誤號
 * @return  錯誤號對應的錯誤資訊
 */
const char *
        MdsApi_GetErrorMsg(
                int32 errCode);

/*
 * 返回訊息頭中的狀態碼所對應的錯誤資訊
 *
 * @param   status              狀態碼
 * @param   detailStatus        明細狀態碼
 * @return  狀態碼所對應的錯誤資訊
 */
const char *
        MdsApi_GetErrorMsg2(
                uint8 status,
                uint8 detailStatus);
/* -------------------------           */


/* ===================================================================
 * 輔助的訂閱請求資訊維護函式
 * =================================================================== */

/*
 * 設定SubscribeByString介面預設使用的資料模式 (TickType)
 *
 * 為相容之前的版本, SubscribeByString 系列的介面無法指定 tickType 訂閱引數。
 * 可以通過該介面為其指定 tickType 引數, 後續的 SubscribeByString 呼叫都會使用該 tickType 引數。
 *
 * @param   tickType            資料模式 (TickType) @see eMdsSubscribedTickTypeT
 *
 * @see     MdsApi_SubscribeByString
 * @see     MdsApi_SubscribeByString2
 * @see     MdsApi_SubscribeByStringAndPrefixes
 * @see     MdsApi_SubscribeByStringAndPrefixes2
 */
void    MdsHelper_SetTickTypeOnSubscribeByString(
                eMdsSubscribedTickTypeT tickType);

/*
 * 清空訂閱資訊中的產品列表
 *
 * @param   pSubscribeInfo      訂閱資訊
 */
void    MdsHelper_ClearSubscribeRequestEntries(
                MdsApiSubscribeInfoT *pSubscribeInfo);

/*
 * 設定訂閱模式
 *
 * @param   pSubscribeInfo      訂閱資訊
 * @param   subMode             訂閱模式 @see eMdsSubscribeModeT
 */
void    MdsHelper_SetSubscribeRequestMode(
                MdsApiSubscribeInfoT *pSubscribeInfo,
                eMdsSubscribeModeT subMode);

/*
 * 設定資料模式 (TickType)
 *
 * @param   pSubscribeInfo      訂閱資訊
 * @param   tickType            資料模式 (TickType) @see eMdsSubscribedTickTypeT
 */
void    MdsHelper_SetSubscribeRequestTickType(
                MdsApiSubscribeInfoT *pSubscribeInfo,
                eMdsSubscribedTickTypeT tickType);

/*
 * 設定訂閱的資料種類
 *
 * @param   pSubscribeInfo      訂閱資訊
 * @param   dataTypes           訂閱的資料種類 (e.g. MDS_SUB_DATA_TYPE_L1_SNAPSHOT
 *                              | MDS_SUB_DATA_TYPE_L2_SNAPSHOT
 *                              | MDS_SUB_DATA_TYPE_L2_BEST_ORDERS
 *                              | MDS_SUB_DATA_TYPE_L2_TRADE)
 *                              @see eMdsSubscribeDataTypeT
 */
void    MdsHelper_SetSubscribeRequestDataTypes(
                MdsApiSubscribeInfoT *pSubscribeInfo,
                int32 dataTypes);

/*
 * 設定指定市場和證券型別的訂閱標誌
 *
 * @param   pSubscribeInfo      訂閱資訊
 * @param   exchangeId          交易所程式碼  @see eMdsExchangeIdT
 *                              - MDS_EXCH_SSE, 上交所
 *                              - MDS_EXCH_SZSE, 深交所
 * @param   mdProductType       行情類別  @see eMdsMdProductTypeT
 *                              - MDS_MD_PRODUCT_TYPE_STOCK, 股票（含債券、基金等現貨產品）
 *                              - MDS_MD_PRODUCT_TYPE_INDEX, 指數
 *                              - MDS_MD_PRODUCT_TYPE_OPTION, 期權（衍生品）
 * @param   subFlag             訂閱標誌 @see eMdsMktSubscribeFlagT
 *                              -  0: (Default) 根據訂閱列表訂閱產品行情
 *                              -  1: (All) 訂閱該市場和證券型別下的所有產品行情
 *                              -  2: (Disable) 禁用該市場下的所有產品行情
 */
void    MdsHelper_SetSubscribeRequestSubFlag(
                MdsApiSubscribeInfoT *pSubscribeInfo,
                eMdsExchangeIdT exchangeId,
                eMdsMdProductTypeT mdProductType,
                eMdsMktSubscribeFlagT subFlag);

/*
 * 新增待訂閱產品到訂閱資訊中
 *
 * @param   pSubscribeInfo      訂閱資訊
 * @param   exchangeId          交易所程式碼  @see eMdsExchangeIdT
 *                              - MDS_EXCH_SSE, 上交所
 *                              - MDS_EXCH_SZSE, 深交所
 * @param   mdProductType       行情類別  @see eMdsMdProductTypeT
 *                              - MDS_MD_PRODUCT_TYPE_STOCK, 股票（含債券、基金等現貨產品）
 *                              - MDS_MD_PRODUCT_TYPE_INDEX, 指數
 *                              - MDS_MD_PRODUCT_TYPE_OPTION, 期權（衍生品）
 * @param   securityId          證券程式碼 (轉換為整型數值的證券程式碼)
 * @return  大於等於0, 成功 (返回已新增到訂閱列表中的產品數量);
 *          小於0, 失敗 (負的錯誤號)
 */
int32   MdsHelper_AddSubscribeRequestEntry(
                MdsApiSubscribeInfoT *pSubscribeInfo,
                eMdsExchangeIdT exchangeId,
                eMdsMdProductTypeT mdProductType,
                int32 securityId);
/* -------------------------           */


#ifdef __cplusplus
}
#endif

#endif  /* _MDS_API_H */
