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
 * @file    mds_mkt_packets.h
 *
 * 行情繫統通訊報文定義
 *
 * @version 0.8.12      2016/09/13
 * @version 0.12        2016/11/30
 *          - 在登入報文中增加協議版本號資訊, 並在登入時校驗協議版本號的相容性
 * @version 0.12.8      2017/03/07
 *          - 重新定義訊息型別的取值
 *          - 將證券行情全幅訊息拆分為'Level1市場行情快照'、'指數行情快照'、'期權行情快照'三個訊息:
 *              - MDS_MSGTYPE_MARKET_DATA_SNAPSHOT_FULL_REFRESH
 *              - MDS_MSGTYPE_INDEX_SNAPSHOT_FULL_REFRESH
 *              - MDS_MSGTYPE_OPTION_SNAPSHOT_FULL_REFRESH
 *          - 調整訂閱型別 (TickType) 的列舉型別定義和取值
 *              - 重定義 MDS_TICK_TYPE_LATEST_ONLY -> MDS_TICK_TYPE_LATEST_SIMPLIFIED
 *                  - 只訂閱最新的行情快照資料, 並忽略和跳過已經過時的資料 (推送的資料量最小, 不會重複傳送最新快照)
 *              - 重定義 MDS_TICK_TYPE_ALL_TICK -> MDS_TICK_TYPE_ALL_INCREMENTS
 *                  - 訂閱所有時點的行情快照資料 (需要注意的是, 在該模式下將會額外發送Level2行情快照的增量更新訊息)
 *              - 新增 MDS_TICK_TYPE_LATEST_TIMELY
 *                  - 只訂閱最新的行情快照資料, 並立即傳送最新資料 (會更及時的獲取到交易活躍的最新行情, 但會重複傳送最新快照)
 *          - 為了方便使用, 擴大每個訂閱請求中能同時指定的產品數量至: 4000
 *          - 重新定義了行情訂閱訊息
 *              - 訂閱模式 (@see eMdsSubscribeModeT)
 *              - 市場和證券型別訂閱標誌 (@see eMdsMktSubscribeFlagT)
 *              - 資料模式 (@see eMdsSubscribedTickTypeT)
 *              - 資料種類 (@see eMdsSubscribeDataTypeT)
 *              - 開始時間 (-1: 從頭開始獲取, 0: 從最新位置開始獲取實時行情, >0: 從指定的起始時間開始獲取)
 *              - 在推送實時行情資料之前, 是否需要推送已訂閱產品的初始的行情快照
 *          - 調整了行情訂閱的應答訊息, 將返回各市場的實際訂閱結果, 即實際已訂閱的產品數量
 * @version 0.15.5.1    2017/11/15
 *          - 增加數值型別的協議版本號 MDS_APPL_VER_VALUE, 以方便比對版本
 * @version 0.15.5.9    2018/05/03
 *          - 增加僅內部使用的訊息型別 MDS_MSGTYPE_COMPRESSED_PACKETS (壓縮的資料包)
 * @version 0.15.5.10   2018/05/24
 *          - 行情訂閱條件和訂閱配置中增加 '待訂閱的內部頻道號', 該欄位僅內部使用, 前端不需要關心和處理 (相容之前版本)
 *          - 行情訂閱條件和訂閱配置中增加 '逐筆資料的過期時間型別 tickExpireType' (相容之前版本)
 *          - 協議版本號升級 => 0.15.5.10 (相容之前版本)
 * @version 0.15.5.11   2018/06/01
 *          - 協議版本號升級 => 0.15.5.11。協議本身與之前的版本不相容, 但將通過如下方式相容之前的API:
 *            - 如果使用的是舊版本的API, 那麼伺服器端將不再推送增量更新訊息 (只推送全量快照), 以此來保持相容
 *            - 如果需要使用增量更新訊息的話, 就需要更新到最新版本的API, 否則不需要更新API
 * @version 0.15.5.16   2018/08/23
 *          - 增加可訂閱的資料種類 (DataType), 以支援單獨訂閱指數行情和期權行情
 *              - MDS_SUB_DATA_TYPE_INDEX_SNAPSHOT, 與L1_SNAPSHOT的區別在於, INDEX_SNAPSHOT可以單獨訂閱指數行情
 *              - MDS_SUB_DATA_TYPE_OPTION_SNAPSHOT, 與L1_SNAPSHOT的區別在於, OPTION_SNAPSHOT可以單獨訂閱期權行情
 * @version 0.15.5.17   2018/11/23
 *          - 登入應答 MdsLogonRspT 增加'服務端叢集號'欄位 setNum
 * @version 0.15.6      2018/05/18
 *          - 調整行情訂閱訊息中可訂閱的資料種類 (DataType) 的列舉型別定義和取值
 *              - 新增 MDS_SUB_DATA_TYPE_DEFAULT (預設資料型別)
 * @version 0.15.8_RC3  2019/01/14
 *          - 刪除已經廢棄的虛擬集合競價訊息的訊息定義和資料型別定義
 * @version 0.15.9      2019/03/21
 *          - 增加修改客戶端登入密碼請求報文和訊息程式碼定義
 *
 * @since   2016/01/03
 */


#ifndef _MDS_MKT_PACKETS_H
#define _MDS_MKT_PACKETS_H


#include    <mds_global/mds_base_model.h>
#include    <mds_global/mds_qry_packets.h>
#include    <sutil/net/spk_global_packet.h>


#ifdef __cplusplus
extern "C" {
#endif


/* ===================================================================
 * 協議版本號定義
 * =================================================================== */

/** 當前採用的協議版本號 */
#define MDS_APPL_VER_ID                         "0.15.9"

/**
 * 當前採用的協議版本號數值
 * - 版本號數值的格式為 10 位整型數值, 形如: 1AABBCCDDX, 其中:
 *   - AA 為主版本號
 *   - BB 為副版本號
 *   - CC 為釋出號
 *   - DD 為構建號
 *   - X  0, 表示不帶時間戳的正常版本; 1, 表示帶時間戳的延遲測量版本
 */
#define MDS_APPL_VER_VALUE                      (1001509001)

/** 相容的最低協議版本號 */
#define MDS_MIN_APPL_VER_ID                     "0.15.5"
/* -------------------------           */


/* ===================================================================
 * 訊息程式碼及報文中的列舉型別定義
 * =================================================================== */

/**
 * 通訊訊息的訊息型別定義
 */
typedef enum _eMdsMsgType {
    /*
     * 會話類訊息
     */
    /** 心跳訊息 (1/0x01) */
    MDS_MSGTYPE_HEARTBEAT                           = 1,
    /** 測試請求訊息 (2/0x02) */
    MDS_MSGTYPE_TEST_REQUEST                        = 2,
    /** 登出訊息 (4/0x04) */
    MDS_MSGTYPE_LOGOUT                              = 4,
    /** 證券行情訂閱訊息 (5/0x05) */
    MDS_MSGTYPE_MARKET_DATA_REQUEST                 = 5,
    /** 壓縮的資料包 (6/0x06, 內部使用) */
    MDS_MSGTYPE_COMPRESSED_PACKETS                  = 6,

    /** 最大的會話訊息型別 */
    __MDS_MSGTYPE_SESSION_MAX,

    /*
     * Level1 行情訊息
     */
    /** Level1 市場行情快照 (10/0x0A) */
    MDS_MSGTYPE_MARKET_DATA_SNAPSHOT_FULL_REFRESH   = 10,
    /** Level1/Level2 指數行情快照 (11/0x0B) */
    MDS_MSGTYPE_INDEX_SNAPSHOT_FULL_REFRESH         = 11,
    /** Level1/Level2 期權行情快照 (12/0x0C) */
    MDS_MSGTYPE_OPTION_SNAPSHOT_FULL_REFRESH        = 12,

    /** 市場狀態訊息 (13/0x0D, 僅上海) */
    MDS_MSGTYPE_TRADING_SESSION_STATUS              = 13,
    /** 證券狀態訊息 (14/0x0E, 僅深圳) */
    MDS_MSGTYPE_SECURITY_STATUS                     = 14,
    /** 最大的Level-1行情訊息型別 */
    __MDS_MSGTYPE_L1_MAX,

    /*
     * Level2 行情訊息
     */
    /** Level2 市場行情快照 (20/0x14) */
    MDS_MSGTYPE_L2_MARKET_DATA_SNAPSHOT             = 20,
    /** Level2 委託佇列快照 (買一/賣一前五十筆) (21/0x15) */
    MDS_MSGTYPE_L2_BEST_ORDERS_SNAPSHOT             = 21,

    /** Level2 逐筆成交行情 (22/0x16) */
    MDS_MSGTYPE_L2_TRADE                            = 22,
    /** Level2 逐筆委託行情 (23/0x17, 僅深圳) */
    MDS_MSGTYPE_L2_ORDER                            = 23,

    /** Level2 快照行情的增量更新訊息 (24/0x18, 僅上海) */
    MDS_MSGTYPE_L2_MARKET_DATA_INCREMENTAL          = 24,
    /** Level2 委託佇列快照的增量更新訊息 (25/0x19, 僅上海) */
    MDS_MSGTYPE_L2_BEST_ORDERS_INCREMENTAL          = 25,

    /** Level2 市場總覽訊息 (26/0x1A, 僅上海) */
    MDS_MSGTYPE_L2_MARKET_OVERVIEW                  = 26,
    /** Level2 虛擬集合競價訊息 (27/0x1B, @deprecated 已廢棄) */
    MDS_MSGTYPE_L2_VIRTUAL_AUCTION_PRICE            = 27,
    /** 最大的Level-2行情訊息型別 */
    __MDS_MSGTYPE_L2_MAX,

    /*
     * 指令類訊息
     */
    /** 修改客戶端登入密碼 (60/0x3C) */
    MDS_MSGTYPE_CMD_CHANGE_PASSWORD                 = 60,
    /** 最大的指令訊息型別 */
    __MDS_MSGTYPE_CMD_MAX,

    /*
     * 查詢類訊息
     */
    /** 查詢證券行情 (80/0x50) */
    MDS_MSGTYPE_QRY_MARKET_DATA_SNAPSHOT            = 80,
    /** 查詢(深圳)證券狀態 (81/0x51) */
    MDS_MSGTYPE_QRY_SECURITY_STATUS                 = 81,
    /** 查詢(上證)市場狀態 (82/0x52) */
    MDS_MSGTYPE_QRY_TRADING_SESSION_STATUS          = 82,

    /** 批量查詢證券(股票/債券/基金)靜態資訊 (85/0x55) */
    MDS_MSGTYPE_QRY_STOCK_STATIC_INFO               = 85,
    /** 批量查詢行情快照列表 (86/0x56) */
    MDS_MSGTYPE_QRY_SNAPSHOT_LIST                   = 86,
    /** 最大的查詢訊息型別 */
    __MDS_MSGTYPE_QRY_MAX,

} eMdsMsgTypeT;
/* -------------------------           */


/**
 * 訂閱模式 (SubMode) 定義
 * - 0: (Set) 重新訂閱, 設定為訂閱列表中的股票
 * - 1: (Append) 追加訂閱, 增加訂閱列表中的股票
 * - 2: (Delete) 刪除訂閱, 刪除訂閱列表中的股票
 */
typedef enum _eMdsSubscribeMode {
    /** 重新訂閱, 設定為訂閱列表中的股票 */
    MDS_SUB_MODE_SET                            = 0,

    /** 追加訂閱, 增加訂閱列表中的股票 */
    MDS_SUB_MODE_APPEND                         = 1,

    /** 刪除訂閱, 刪除訂閱列表中的股票 */
    MDS_SUB_MODE_DELETE                         = 2,

    __MAX_MDS_SUB_MODE
} eMdsSubscribeModeT;
/* -------------------------           */


/**
 * 市場-產品型別訂閱標誌 (SubFlag) 定義
 * -  0: (Default) 根據訂閱列表訂閱產品行情
 * -  1: (All) 訂閱該市場和證券型別下的所有產品行情 (為相容之前的版本, 也可以賦值為 -1)
 * -  2: (Disable) 禁用該市場下的所有產品行情
 */
typedef enum _eMdsMktSubscribeFlag {
    /** 根據訂閱列表訂閱產品行情 */
    MDS_MKT_SUB_FLAG_DEFAULT                    = 0,

    /** 訂閱該市場和證券型別下的所有產品行情 */
    MDS_MKT_SUB_FLAG_ALL                        = 1,

    /** 禁用該市場下的所有產品行情 */
    MDS_MKT_SUB_FLAG_DISABLE                    = 2,

    __MAX_MDS_MKT_SUB_FLAG
} eMdsMktSubscribeFlagT;
/* -------------------------           */


/**
 * 資料模式 (TickType) 定義 (僅對快照行情生效)
 * 訂閱最新的行情快照還是所有時點的行情快照
 * -  0: (LatestSimplified) 只訂閱最新的行情快照資料, 並忽略和跳過已經過時的資料
 *       - 該模式推送的資料量最小, 沒有重複資料, 也不會重複傳送最新快照
 *       - 該模式在時延和頻寬方面都相對優秀, 如果沒有特殊需求, 推薦使用該模式即可
 * -  1: (LatestTimely) 只訂閱最新的行情快照資料, 並立即傳送最新資料
 *       - 只要有行情更新事件, 便立即推送該產品的最新行情, 但也會因此重複傳送多次相同的最新行情
 *       - 如果某些產品的交易很活躍, 而客戶端處理又比較耗時的話, 那麼該模式可能會更及時的獲取到
 *         這些產品的最新行情
 *       - 此外, 因為與 AllIncrements 模式下的資料一一對應, 可以方便與增量更新訊息進行比對測試
 *       - 通常情況下, 推薦使用 LatestSimplified 模式即可
 * -  2: (AllIncrements) 訂閱所有時點的行情快照資料 (包括Level2增量更新訊息)
 *       - 該模式會推送所有時點的行情資料, 包括Level2行情快照的增量更新訊息
 *       - 如果需要獲取全量的行情明細, 或者需要直接使用Level2的增量更新訊息, 可以使用該模式
 */
typedef enum _eMdsSubscribedTickType {
    /** 只訂閱最新的行情快照資料, 並忽略和跳過已經過時的資料 (推送的資料量最小, 不會重複傳送最新快照) */
    MDS_TICK_TYPE_LATEST_SIMPLIFIED             = 0,

    /** 只訂閱最新的行情快照資料, 並立即傳送最新資料 (會更及時的獲取到交易活躍的最新行情, 但會重複傳送最新快照) */
    MDS_TICK_TYPE_LATEST_TIMELY                 = 1,

    /** 訂閱所有時點的行情快照資料 (包括Level2增量更新訊息) */
    MDS_TICK_TYPE_ALL_INCREMENTS                = 2,

    __MAX_MDS_TICK_TYPE
} eMdsSubscribedTickTypeT;
/* -------------------------           */


/**
 * 逐筆資料的過期時間定義 (僅對逐筆資料生效)
 */
typedef enum _eMdsSubscribedTickExpireType {
    /** 不過期 */
    MDS_TICK_EXPIRE_TYPE_NONE                   = 0,

    /** 立即過期 (1秒, 如果逐筆資料時間落後於最新快照時間1秒, 則視為過期並跳過該逐筆資料) */
    MDS_TICK_EXPIRE_TYPE_IMMEDIATE              = 1,

    /** 及時過期 (3秒, 如果逐筆資料時間落後於最新快照時間3秒, 則視為過期並跳過該逐筆資料) */
    MDS_TICK_EXPIRE_TYPE_TIMELY                 = 2,

    /** 超時過期 (30秒, 如果逐筆資料時間落後於最新快照時間30秒, 則視為過期並跳過該逐筆資料) */
    MDS_TICK_EXPIRE_TYPE_TIMEOUT                = 3,

    __MAX_MDS_TICK_EXPIRE_TYPE
} eMdsSubscribedTickExpireTypeT;
/* -------------------------           */


/**
 * 可訂閱的資料種類 (DataType) 定義
 * - 0:      預設資料種類 (所有)
 * - 0x0001: L1快照/指數/期權
 * - 0x0002: L2快照
 * - 0x0004: L2委託佇列
 * - 0x0008: L2逐筆成交
 * - 0x0010: L2逐筆委託 (深圳)
 * - 0x0040: L2市場總覽 (上海)
 * - 0x0100: 市場狀態 (上海)
 * - 0x0200: 證券實時狀態 (深圳)
 * - 0x0400: 指數行情 (與0x0001的區別在於, 0x0400可以單獨訂閱指數行情)
 * - 0x0800: 期權行情 (與0x0001的區別在於, 0x0800可以單獨訂閱期權行情)
 * - 0xFFFF: 所有資料種類
 */
typedef enum _eMdsSubscribeDataType {
    /** 預設資料種類 (所有種類) */
    MDS_SUB_DATA_TYPE_DEFAULT                   = 0,

    /** L1快照/指數/期權 (L1快照行情 + 指數行情 + 期權行情) */
    MDS_SUB_DATA_TYPE_L1_SNAPSHOT               = 0x0001,

    /** L2快照 */
    MDS_SUB_DATA_TYPE_L2_SNAPSHOT               = 0x0002,

    /** L2委託佇列 */
    MDS_SUB_DATA_TYPE_L2_BEST_ORDERS            = 0x0004,

    /** L2逐筆成交 */
    MDS_SUB_DATA_TYPE_L2_TRADE                  = 0x0008,

    /** L2逐筆委託 (*深圳, 0x10/16) */
    MDS_SUB_DATA_TYPE_L2_ORDER                  = 0x0010,

    /** L2市場總覽 (*上海, 0x40/64) */
    MDS_SUB_DATA_TYPE_L2_MARKET_OVERVIEW        = 0x0040,

    /** 市場狀態 (*上海, 0x100/256) */
    MDS_SUB_DATA_TYPE_TRADING_SESSION_STATUS    = 0x0100,

    /** 證券實時狀態 (*深圳, 0x200/512) */
    MDS_SUB_DATA_TYPE_SECURITY_STATUS           = 0x0200,

    /** 指數行情 (與L1_SNAPSHOT的區別在於, INDEX_SNAPSHOT可以單獨訂閱指數行情) */
    MDS_SUB_DATA_TYPE_INDEX_SNAPSHOT            = 0x0400,

    /** 期權行情 (與L1_SNAPSHOT的區別在於, OPTION_SNAPSHOT可以單獨訂閱期權行情) */
    MDS_SUB_DATA_TYPE_OPTION_SNAPSHOT           = 0x0800,

    /** 空資料種類 (可用於不指定任何數量種類的情況) */
    MDS_SUB_DATA_TYPE_NONE                      = 0x8000,

    /** 所有資料種類 */
    MDS_SUB_DATA_TYPE_ALL                       = 0xFFFF,

    __MAX_MDS_SUB_DATA_TYPE                     = 0x7FFFFFFF
} eMdsSubscribeDataTypeT;
/* -------------------------           */


/**
 * 可訂閱的內部資料頻道定義 (供內部使用, 尚未對外開放)
 */
typedef enum _eMdsSubscribedChannelNo {
    /** 預設頻道 (所有頻道) */
    MDS_CHANNEL_NO_DEFAULT                      = 0,

    /** 頻道1 */
    MDS_CHANNEL_NO_ONE                          = 0x01,
    /** 頻道2 */
    MDS_CHANNEL_NO_TWO                          = 0x02,
    /** 頻道3 */
    MDS_CHANNEL_NO_THREE                        = 0x04,
    /** 頻道4 */
    MDS_CHANNEL_NO_FOUR                         = 0x08,

    /** 所有頻道 */
    MDS_CHANNEL_NO_ALL                          = 0x0F,
    /** 空資料頻道 (可用於不訂閱任何頻道的情況) */
    MDS_CHANNEL_NO_NONE                         = 0x80
} eMdsTickChannelNoT;
/* -------------------------           */


/**
 * 可指定的協議約定型別定義
 * - 0:     預設的協議約定型別
 * - 0x80:  約定以壓縮方式傳輸資料
 * - 0xFF:  無任何協議約定
 */
typedef enum _eMdsProtocolHintsType {
    /** 預設的協議約定型別 */
    MDS_PROT_HINTS_TYPE_DEFAULT                 = 0,

    /** 協議約定以壓縮方式傳輸資料 */
    MDS_PROT_HINTS_TYPE_COMPRESS                = 0x80,

    /** 無任何協議約定 */
    MDS_PROT_HINTS_TYPE_NONE                    = 0xFF,
    __MAX_MDS_PROT_HINTS_TYPE                   = 0xFF
} eMdsProtocolHintsTypeT;
/* -------------------------           */


/* ===================================================================
 * 會話訊息報文定義
 * =================================================================== */

/**
 * 行情訂閱請求的訂閱產品條目
 */
typedef struct _MdsMktDataRequestEntry {
    uint8               exchId;                 /**< 交易所程式碼 @see eMdsExchangeIdT */
    uint8               mdProductType;          /**< 證券型別 @see eMdsMdProductTypeT */
    uint8               __filler[2];            /**< 按64位對齊的填充域 */
    int32               instrId;                /**< 產品程式碼 */
} MdsMktDataRequestEntryT;


/* 結構體的初始化值定義 */
#define NULLOBJ_MDS_MKT_DATA_REQUEST_ENTRY      \
        0, 0, {0}, 0
/* -------------------------           */


/**
 * 行情訂閱請求報文
 *
 * - 對於可同時訂閱產品數量有如下限制:
 *   - 每個訂閱請求中最多能同時指定 4000 只產品, 可以通過追加訂閱的方式訂閱更多數量的產品
 *   - 對於滬/深兩市的現貨產品沒有總訂閱數量的限制, 可以訂閱任意數量的產品
 *   - 對於滬/深兩市的期權產品, 限制對每個市場最多允許同時訂閱 2000 只期權產品
 *
 * @see MdsMktDataRequestEntryT
 */
typedef struct _MdsMktDataRequestReq {
    /**
     * 訂閱模式
     * - 0: (Set) 重新訂閱, 設定為訂閱列表中的股票
     * - 1: (Append) 追加訂閱, 增加訂閱列表中的股票
     * - 2: (Delete) 刪除訂閱, 刪除訂閱列表中的股票
     *
     * @see eMdsSubscribeModeT
     */
    uint8               subMode;

    /**
     * 資料模式, 訂閱最新的行情快照還是所有時點的資料
     * -  0: (LatestSimplified) 只訂閱最新的行情快照資料, 並忽略和跳過已經過時的資料
     *       - 該模式推送的資料量最小, 沒有重複資料, 也不會重複傳送最新快照
     *       - 該模式在時延和頻寬方面都相對優秀, 如果沒有特殊需求, 推薦使用該模式即可
     * -  1: (LatestTimely) 只訂閱最新的行情快照資料, 並立即傳送最新資料
     *       - 只要有行情更新事件, 便立即推送該產品的最新行情, 但也會因此重複傳送多次相同的最新行情
     *       - 如果某些產品的交易很活躍, 而客戶端處理又比較耗時的話, 那麼該模式可能會更及時的獲取到
     *         這些產品的最新行情
     *       - 此外, 因為與 AllIncrements 模式下的資料一一對應, 可以方便與增量更新訊息進行比對測試
     *       - 通常情況下, 推薦使用 LatestSimplified 模式即可
     * -  2: (AllIncrements) 訂閱所有時點的行情快照資料 (包括Level2增量更新訊息)
     *       - 該模式會推送所有時點的行情資料, 包括Level2行情快照的增量更新訊息
     *       - 如果需要獲取全量的行情明細, 或者需要直接使用Level2的增量更新訊息, 可以使用該模式
     *
     * @see eMdsSubscribedTickTypeT
     */
    uint8               tickType;

    /**
     * 上證股票(債券/基金)產品的訂閱標誌
     * -  0: (Default) 根據訂閱列表訂閱產品行情
     * -  1: (All) 訂閱該市場和證券型別下的所有產品行情 (為相容之前的版本, 也可以賦值為 -1)
     * -  2: (Disable) 禁用該市場下的所有股票/債券/基金行情
     *
     * @see eMdsMktSubscribeFlagT
     */
    int8                sseStockFlag;

    /**
     * 上證指數產品的訂閱標誌
     * -  0: (Default) 根據訂閱列表訂閱產品行情
     * -  1: (All) 訂閱該市場和證券型別下的所有產品行情
     * -  2: (Disable) 禁用該市場下的所有指數行情
     *
     * @see eMdsMktSubscribeFlagT
     */
    int8                sseIndexFlag;

    /**
     * 上證期權產品的訂閱標誌
     * -  0: (Default) 根據訂閱列表訂閱產品行情
     * -  1: (All) 訂閱該市場和證券型別下的所有產品行情
     * -  2: (Disable) 禁用該市場下的所有期權行情
     *
     * @see eMdsMktSubscribeFlagT
     */
    int8                sseOptionFlag;

    /**
     * 深圳股票(債券/基金)產品的訂閱標誌
     * -  0: (Default) 根據訂閱列表訂閱產品行情
     * -  1: (All) 訂閱該市場和證券型別下的所有產品行情
     * -  2: (Disable) 禁用該市場下的所有股票/債券/基金行情
     *
     * @see eMdsMktSubscribeFlagT
     */
    int8                szseStockFlag;

    /**
     * 深圳指數產品的訂閱標誌
     * -  0: (Default) 根據訂閱列表訂閱產品行情
     * -  1: (All) 訂閱該市場和證券型別下的所有產品行情
     * -  2: (Disable) 禁用該市場下的所有指數行情
     *
     * @see eMdsMktSubscribeFlagT
     */
    int8                szseIndexFlag;

    /**
     * 深圳期權產品的訂閱標誌
     * -  0: (Default) 根據訂閱列表訂閱產品行情
     * -  1: (All) 訂閱該市場和證券型別下的所有產品行情
     * -  2: (Disable) 禁用該市場下的所有期權行情
     *
     * @see eMdsMktSubscribeFlagT
     */
    int8                szseOptionFlag;

    /**
     * 在推送實時行情資料之前, 是否需要推送已訂閱產品的初始的行情快照
     * 該引數只在初始訂閱時有效, 會話過程中的實時訂閱將不支援該引數, 也不會再次推送初始行情快照
     * -  0: 不需要
     * -  1: 需要, 即確保客戶端可以至少收到一幅已訂閱產品的快照行情 (如果有的話)
     */
    uint8               isRequireInitialMktData;

    /** 待訂閱的內部頻道號 (供內部使用, 尚未對外開放) */
    uint8               __channelNos;

    /**
     * 逐筆資料的過期時間型別
     * -  0: 不過期
     * -  1: 立即過期 (1秒, 若落後於快照1秒則視為過期)
     * -  2: 及時過期 (3秒)
     * -  3: 超時過期 (30秒)
     *
     * @see     eMdsSubscribedTickExpireTypeT
     * @note    因為存在不可控的網路因素, 所以做不到百分百的精確過濾, 如果對資料的
     *          時效性有精確要求, 就需要在前端對資料再進行一次過濾
     */
    uint8               tickExpireType;

    /** 按64位對齊的填充域 */
    uint8               __filler;

    /**
     * 訂閱的資料種類
     * - 0:      預設資料種類 (所有)
     * - 0x0001: L1快照/指數/期權
     * - 0x0002: L2快照
     * - 0x0004: L2委託佇列
     * - 0x0008: L2逐筆成交
     * - 0x0010: L2逐筆委託 (深圳)
     * - 0x0040: L2市場總覽 (上海)
     * - 0x0100: 市場狀態 (上海)
     * - 0x0200: 證券實時狀態 (深圳)
     * - 0x0400: 指數行情 (與0x0001的區別在於, 0x0400可以單獨訂閱指數行情)
     * - 0x0800: 期權行情 (與0x0001的區別在於, 0x0800可以單獨訂閱期權行情)
     * - 0xFFFF: 所有資料
     *
     * @see eMdsSubscribeDataTypeT
     */
    int32               dataTypes;

    /**
     * 請求訂閱的行情資料的起始時間 (格式為: HHMMSS 或 HHMMSSsss)
     * - -1: 從頭開始獲取
     * -  0: 從最新位置開始獲取實時行情
     * - >0: 從指定的起始時間開始獲取 (HHMMSS / HHMMSSsss)
     * - 對於應答資料, 若為 0 則表示當前沒有比起始時間更加新的行情資料
     */
    int32               beginTime;

    /**
     * 本次訂閱的產品數量 (訂閱列表中的產品數量)
     * - 該欄位表示後續報文為subSecurityCnt個訂閱產品條目結構體, 通過這樣的方式可以實現同
     *   時訂閱多隻產品的行情快照
     * - 每個訂閱請求中最多能同時指定 4000 只產品, 可以通過追加訂閱的方式訂閱更多數量的產品
     * - 訂閱產品總數量的限制如下:
     *   - 對於滬/深兩市的現貨產品沒有訂閱數量限制, 可以訂閱任意數量的產品
     *   - 對於滬/深兩市的期權產品, 限制對每個市場最多允許同時訂閱 2000 只期權產品
     *
     * @see MdsMktDataRequestEntryT
     */
    int32               subSecurityCnt;

    /*
     * 後續報文為 subSecurityCnt 個訂閱產品條目結構體
     * @see MdsMktDataRequestEntryT
     */

} MdsMktDataRequestReqT;


/* 結構體的初始化值定義 */
#define NULLOBJ_MDS_MKT_DATA_REQUEST_REQ        \
        0, 0, \
        0, 0, 0, 0, 0, 0, \
        0, 0, 0, 0, \
        0, 0, 0
/* -------------------------           */


/**
 * 完整的行情訂閱請求報文快取
 */
typedef struct _MdsMktDataRequestReqBuf {
    /** 行情訂閱請求 */
    MdsMktDataRequestReqT           mktDataRequestReq;

    /* 訂閱產品列表 */
    MdsMktDataRequestEntryT         entries[MDS_MAX_SECURITY_CNT_PER_SUBSCRIBE];
} MdsMktDataRequestReqBufT;


/* 結構體的初始化值定義 */
#define NULLOBJ_MDS_MKT_DATA_REQUEST_REQ_BUF    \
        {NULLOBJ_MDS_MKT_DATA_REQUEST_REQ}, \
        {{NULLOBJ_MDS_MKT_DATA_REQUEST_ENTRY}}
/* -------------------------           */


/**
 * 行情訂閱請求的應答報文
 */
typedef struct _MdsMktDataRequestRsp {
    /**
     * 訂閱模式
     * - 0: (Set) 重新訂閱, 設定為訂閱列表中的股票
     * - 1: (Append) 追加訂閱, 增加訂閱列表中的股票
     * - 2: (Delete) 刪除訂閱, 刪除訂閱列表中的股票
     *
     * @see eMdsSubscribeModeT
     */
    uint8               subMode;

    /**
     * 資料模式, 訂閱最新的行情快照還是所有時點的資料
     * -  0: (LatestSimplified) 只訂閱最新的行情快照資料, 並忽略和跳過已經過時的資料
     *       - 該模式推送的資料量最小, 沒有重複資料, 也不會重複傳送最新快照
     *       - 該模式在時延和頻寬方面都相對優秀, 如果沒有特殊需求, 推薦使用該模式即可
     * -  1: (LatestTimely) 只訂閱最新的行情快照資料, 並立即傳送最新資料
     *       - 只要有行情更新事件, 便立即推送該產品的最新行情, 但也會因此重複傳送多次相同的最新行情
     *       - 如果某些產品的交易很活躍, 而客戶端處理又比較耗時的話, 那麼該模式可能會更及時的獲取到
     *         這些產品的最新行情
     *       - 此外, 因為與 AllIncrements 模式下的資料一一對應, 可以方便與增量更新訊息進行比對測試
     *       - 通常情況下, 推薦使用 LatestSimplified 模式即可
     * -  2: (AllIncrements) 訂閱所有時點的行情快照資料 (包括Level2增量更新訊息)
     *       - 該模式會推送所有時點的行情資料, 包括Level2行情快照的增量更新訊息
     *       - 如果需要獲取全量的行情明細, 或者需要直接使用Level2的增量更新訊息, 可以使用該模式
     *
     * @see eMdsSubscribedTickTypeT
     */
    uint8               tickType;

    /**
     * 在推送實時行情資料之前, 是否需要推送已訂閱產品的初始的行情快照
     * 該引數只在初始訂閱時有效, 會話過程中的實時訂閱將不支援該引數, 也不會再次推送初始行情快照
     */
    uint8               isRequireInitialMktData;

    /** 訂閱的內部頻道號 (供內部使用, 尚未對外開放) */
    uint8               __channelNos;

    /**
     * 逐筆資料的過期時間型別
     * -  0: 不過期
     * -  1: 立即過期 (1秒, 若落後於快照1秒則視為過期)
     * -  2: 及時過期 (3秒)
     * -  3: 超時過期 (30秒)
     *
     * @see     eMdsSubscribedTickExpireTypeT
     * @note    因為存在不可控的網路因素, 所以做不到百分百的精確過濾, 如果對資料的
     *          時效性有精確要求, 就需要在前端對資料再進行一次過濾
     */
    uint8               tickExpireType;

    /** 按64位對齊的填充域 */
    uint8               __filler[3];

    /**
     * 訂閱的資料種類
     * - 0:      預設資料種類 (所有)
     * - 0x0001: L1快照/指數/期權
     * - 0x0002: L2快照
     * - 0x0004: L2委託佇列
     * - 0x0008: L2逐筆成交
     * - 0x0010: L2逐筆委託 (深圳)
     * - 0x0040: L2市場總覽 (上海)
     * - 0x0100: 市場狀態 (上海)
     * - 0x0200: 證券實時狀態 (深圳)
     * - 0x0400: 指數行情 (與0x0001的區別在於, 0x0400可以單獨訂閱指數行情)
     * - 0x0800: 期權行情 (與0x0001的區別在於, 0x0800可以單獨訂閱期權行情)
     * - 0xFFFF: 所有資料
     *
     * @see eMdsSubscribeDataTypeT
     */
    int32               dataTypes;

    /**
     * 請求訂閱的行情資料的起始時間 (格式為: HHMMSS 或 HHMMSSsss)
     * - -1: 從頭開始獲取
     * -  0: 從最新位置開始獲取實時行情
     * - >0: 從指定的起始時間開始獲取 (HHMMSS / HHMMSSsss)
     * - 對於應答資料, 若為 0 則表示當前沒有比起始時間更加新的行情資料
     */
    int32               beginTime;

    /**
     * 上證股票(債券/基金)產品的訂閱結果 (實際已訂閱的產品數量)
     * - -1: 訂閱了所有產品;
     * -  0: 未訂閱或已禁用;
     * - >0: 已訂閱的產品數量(按照訂閱列表成功訂閱的產品數量)
     */
    int32               sseStockSubscribed;

    /**
     * 上證指數產品的訂閱結果 (實際已訂閱的產品數量)
     * - -1: 訂閱了所有產品;
     * -  0: 未訂閱或已禁用;
     * - >0: 已訂閱的產品數量(按照訂閱列表成功訂閱的產品數量)
     */
    int32               sseIndexSubscribed;

    /**
     * 上證期權產品的訂閱結果 (實際已訂閱的產品數量)
     * - -1: 訂閱了所有產品;
     * -  0: 未訂閱或已禁用;
     * - >0: 已訂閱的產品數量(按照訂閱列表成功訂閱的產品數量)
     */
    int32               sseOptionSubscribed;

    /**
     * 深圳股票(債券/基金)產品的訂閱結果 (實際已訂閱的產品數量)
     * - -1: 訂閱了所有產品;
     * -  0: 未訂閱或已禁用;
     * - >0: 已訂閱的產品數量(按照訂閱列表成功訂閱的產品數量)
     */
    int32               szseStockSubscribed;

    /**
     * 深圳指數產品的訂閱結果 (實際已訂閱的產品數量)
     * - -1: 訂閱了所有產品;
     * -  0: 未訂閱或已禁用;
     * - >0: 已訂閱的產品數量(按照訂閱列表成功訂閱的產品數量)
     */
    int32               szseIndexSubscribed;

    /**
     * 深圳期權產品的訂閱結果 (實際已訂閱的產品數量)
     * - -1: 訂閱了所有產品;
     * -  0: 未訂閱或已禁用;
     * - >0: 已訂閱的產品數量(按照訂閱列表成功訂閱的產品數量)
     */
    int32               szseOptionSubscribed;

} MdsMktDataRequestRspT;


/* 結構體的初始化值定義 */
#define NULLOBJ_MDS_MKT_DATA_REQUEST_RSP        \
        0, 0, 0, 0, 0, {0}, \
        0, 0, \
        0, 0, 0, 0, 0, 0
/* -------------------------           */


/**
 * 測試請求報文
 */
typedef struct _MdsTestRequestReq {
    /** 測試請求識別符號 */
    char                testReqId[MDS_MAX_TEST_REQ_ID_LEN];

    /** 傳送時間 (timeval結構或形如'YYYYMMDD-HH:mm:SS.sss'的字串) */
    char                sendTime[MDS_MAX_SENDING_TIME_LEN];

    /** 按64位對齊的填充域 */
    char                __filler[2];
} MdsTestRequestReqT;


/* 結構體的初始化值定義 */
#define NULLOBJ_MDS_TEST_REQUEST_REQ            \
        {0}, {0}, {0}
/* -------------------------           */


/**
 * 測試請求的應答報文
 */
typedef struct _MdsTestRequestRsp {
    /** 測試請求識別符號 */
    char                testReqId[MDS_MAX_TEST_REQ_ID_LEN];

    /** 測試請求的原始傳送時間 (timeval結構或形如'YYYYMMDD-HH:mm:SS.sss'的字串) */
    char                origSendTime[MDS_MAX_SENDING_TIME_LEN];

    /** 按64位對齊的填充域 */
    char                __filler1[2];

    /** 測試請求應答的傳送時間 (timeval結構或形如'YYYYMMDD-HH:mm:SS.sss'的字串) */
    char                respTime[MDS_MAX_SENDING_TIME_LEN];

    /** 按64位對齊的填充域 */
    char                __filler2[2];

#ifdef  _MDS_ENABLE_LATENCY_STATS
    /** 訊息實際接收時間 (開始解碼等處理之前的時間) */
    STimeval32T         __recvTime;
    /** 訊息採集處理完成時間 */
    STimeval32T         __collectedTime;
    /** 訊息推送時間 (寫入推送快取以後, 實際網路傳送之前) */
    STimeval32T         __pushingTime;
#endif

} MdsTestRequestRspT;


/* 結構體初始化值的尾部填充欄位定義 */
#ifdef  _MDS_ENABLE_LATENCY_STATS
# define    __NULLOBJ_MDS_TEST_REQUEST_RSP_TAILER       \
            , {0, 0}, {0, 0}, {0, 0}
#else
# define    __NULLOBJ_MDS_TEST_REQUEST_RSP_TAILER
#endif


/* 結構體的初始化值定義 */
#define NULLOBJ_MDS_TEST_REQUEST_RSP                    \
        {0}, {0}, {0}, {0}, {0} \
        __NULLOBJ_MDS_TEST_REQUEST_RSP_TAILER
/* -------------------------           */


/**
 * 修改登入密碼請求報文
 */
typedef struct _MdsChangePasswordReq {
    /** 加密方法 */
    int32               encryptMethod;
    /** 按64位對齊的填充域 */
    int32               __filler;

    /** 登入使用者名稱 */
    char                username[MDS_MAX_USERNAME_LEN];

    /** 使用者私有資訊 (由客戶端自定義填充, 並在回報資料中原樣返回) */
    union {
        uint64          u64;                    /**< uint64 型別的使用者私有資訊 */
        int64           i64;                    /**< int64 型別的使用者私有資訊 */
        uint32          u32[2];                 /**< uint32[2] 型別的使用者私有資訊 */
        int32           i32[2];                 /**< int32[2] 型別的使用者私有資訊 */
        char            c8[8];                  /**< char[8] 型別的使用者私有資訊 */
    } userInfo;

    /** 之前的登入密碼 */
    char                oldPassword[MDS_MAX_PASSWORD_LEN];

    /** 新的登入密碼 */
    char                newPassword[MDS_MAX_PASSWORD_LEN];
} MdsChangePasswordReqT;


/* 結構體的初始化值定義 */
#define NULLOBJ_MDS_CHANGE_PASSWORD_REQ         \
        0, 0, \
        {0}, {0}, \
        {0}, {0}
/* -------------------------           */


/**
 * 修改登入密碼應答報文
 */
typedef struct _MdsChangePasswordRsp {
    /** 加密方法 */
    int32               encryptMethod;
    /** 按64位對齊的填充域 */
    int32               __filler;

    /** 登入使用者名稱 */
    char                username[MDS_MAX_USERNAME_LEN];

    /** 使用者私有資訊 (由客戶端自定義填充, 並在應答資料中原樣返回) */
    union {
        uint64          u64;                    /**< uint64 型別的使用者私有資訊 */
        int64           i64;                    /**< int64 型別的使用者私有資訊 */
        uint32          u32[2];                 /**< uint32[2] 型別的使用者私有資訊 */
        int32           i32[2];                 /**< int32[2] 型別的使用者私有資訊 */
        char            c8[8];                  /**< char[8] 型別的使用者私有資訊 */
    } userInfo;

    /** 按64位對齊的填充域 */
    int32               __filler2;
    /** 發生日期 (格式為 YYYYMMDD, 形如 20160830) */
    int32               transDate;
    /** 發生時間 (格式為 HHMMSSsss, 形如 141205000) */
    int32               transTime;
    /** 拒絕原因 */
    int32               rejReason;
} MdsChangePasswordRspT;


/* 結構體的初始化值定義 */
#define NULLOBJ_MDS_CHANGE_PASSWORD_RSP         \
        0, 0, \
        {0}, {0}, \
        0, 0, 0, 0
/* -------------------------           */


/* ===================================================================
 * 彙總的請求/應答訊息定義
 * =================================================================== */

/**
 * 彙總的請求訊息的訊息體定義
 */
typedef union _MdsMktReqMsgBody {
    /** 完整的行情訂閱請求報文快取 */
    MdsMktDataRequestReqBufT        wholeMktDataReqBuf;
    /** 行情訂閱請求報文 */
    MdsMktDataRequestReqT           mktDataRequestReq;
    /** 測試請求報文 */
    MdsTestRequestReqT              testRequestReq;

    /** 證券行情查詢請求 */
    MdsQryMktDataSnapshotReqT       qryMktDataSnapshotReq;
    /** (深圳)證券實時狀態查詢請求 */
    MdsQrySecurityStatusReqT        qrySecurityStatusReq;
    /** (上證)市場狀態查詢請求 */
    MdsQryTrdSessionStatusReqT      qryTrdSessionStatusReq;
    /** 證券靜態資訊批量查詢請求 */
    MdsQryStockStaticInfoReqT       qryStockStaticInfoReq;
    /** 行情快照批量查詢請求 */
    MdsQrySnapshotListReqT          qrySnapshotListReq;

    /** 修改登入密碼請求 */
    MdsChangePasswordReqT           changePasswordReq;
} MdsMktReqMsgBodyT;


/* 結構體的初始化值定義 */
#define NULLOBJ_MDS_MKT_REQ_MSG_BODY            \
        {NULLOBJ_MDS_MKT_DATA_REQUEST_REQ_BUF}
/* -------------------------           */


/**
 * 彙總的應答訊息的訊息體定義
 */
typedef union _MdsMktRspMsgBody {
    /*
     * 會話訊息
     */
    /** 行情訂閱請求的應答報文 */
    MdsMktDataRequestRspT           mktDataRequestRsp;
    /** 測試請求的應答報文 */
    MdsTestRequestRspT              testRequestRsp;

    /*
     * 行情訊息
     */
    /** 證券行情全幅訊息 */
    MdsMktDataSnapshotT             mktDataSnapshot;
    /** Level2 逐筆成交行情 */
    MdsL2TradeT                     trade;
    /** Level2 逐筆委託行情 */
    MdsL2OrderT                     order;

    /** 市場狀態訊息 */
    MdsTradingSessionStatusMsgT     trdSessionStatus;
    /** 證券實時狀態訊息 */
    MdsSecurityStatusMsgT           securityStatus;

    /*
     * 查詢訊息
     */
    /** 證券靜態資訊查詢的應答資料 */
    MdsQryStockStaticInfoRspT       qryStockStaticInfoRsp;
    /** 行情快照批量查詢的應答資料 */
    MdsQrySnapshotListRspT          qrySnapshotListRsp;

    /*
     * 指令訊息
     */
    /** 修改登入密碼的應答資料 */
    MdsChangePasswordRspT           changePasswordRsp;
} MdsMktRspMsgBodyT;


/* 結構體的初始化值定義 */
#define NULLOBJ_MDS_MKT_RSP_MSG_BODY            \
        {NULLOBJ_MDS_MKT_DATA_REQUEST_RSP}
/* -------------------------           */


/* ===================================================================
 * 組播訊息的報文頭定義
 * =================================================================== */

/**
 * 組播訊息的報文頭
 * 組播報文的組成結構為:
 * - 報文頭
 * - 報文體
 *   - 訊息頭 1 + 訊息體 1
 *   - 訊息頭 2 + 訊息體 2
 *   - 訊息頭 3 + 訊息體 3
 *   - ...
 *   - 目前一個組播報文中最多包含3條行情訊息
 */
typedef struct _MdsUdpPktHead {
    int32               msgCnt;                 /**< 報文中包含的訊息數量 */
    int32               pktSiz;                 /**< 報文體資料大小 */
    uint64              pktSeq;                 /**< 報文順序號 */

#ifdef  _MDS_TRACE_UDP_SENDING_TIME
    STimeval32T         __sendingTime;          /**< 訊息實際傳送時間 */
#endif
} MdsUdpPktHeadT;


/* 訊息頭尾部填充欄位的初始化值定義 */
#ifdef  _MDS_TRACE_UDP_SENDING_TIME
#   define  __NULLOBJ_MDS_UDP_HEAD_TAILER       \
            , {0, 0}
#else
#   define  __NULLOBJ_MDS_UDP_HEAD_TAILER
#endif


/* 結構體的初始化值定義 */
#define NULLOBJ_MDS_UDP_PKT_HEAD                \
        0, 0, 0 \
        __NULLOBJ_MDS_UDP_HEAD_TAILER
/* -------------------------           */


#ifdef __cplusplus
}
#endif

#endif  /* _MDS_MKT_PACKETS_H */
