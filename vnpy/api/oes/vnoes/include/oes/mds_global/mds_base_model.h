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
 * @file    mds_base_model.h
 *
 * MDS系統的基礎領域模型(資料結構)定義
 *
 * - 行情資料的欄位命名風格說明:
 *   - 以大寫字母開頭的欄位, 都是直接來源於交易所的資料;
 *   - 以小寫字母開頭的欄位, 是額外增加的或者經過轉換的資料;
 *   - 以雙下劃線開頭的欄位, 是系統的內部欄位
 *
 * @version 0.8.12      2016/09/13
 * @version 0.12.8      2017/03/07
 *          - 刪除獨立的 MdsMktDataSnapshotEntryMetaT 結構體,
 *            將欄位整合到 MdsMktDataSnapshotHeadT 中, 並刪除原 meta.priceUnit (價格單位) 欄位
 *          - 重新命名 MdsMktDataSnapshotEntryT -> MdsL1SnapshotBodyT
 *          - 重新命名 MdsIndexDataSnapshotEntryT -> MdsIndexSnapshotBodyT
 *          - 重新命名 MdsStockDataSnapshotEntryT -> MdsStockSnapshotBodyT
 *          - 重新命名 MdsStockSnapshotBodyT.PreCloseIOPV -> NAV
 *          - 重定義 MdsStockSnapshotBodyT.PriceLevel[5] -> BidLevels[5] + OfferLevels[5]
 *              - PriceLevel\[(\w+)\].BuyPrice -> BidLevels[\1].Price
 *              - PriceLevel\[(\w+)\].BuyVolume -> BidLevels[\1].OrderQty
 *              - PriceLevel\[(\w+)\].SellPrice -> OfferLevels[\1].Price
 *              - PriceLevel\[(\w+)\].SellVolume -> OfferLevels[\1].OrderQty
 *          - 重新命名 MdsStockSnapshotBodyT.TradeVolume -> TotalVolumeTraded
 *          - 重新命名 MdsIndexSnapshotBodyT.TradeVolume -> TotalVolumeTraded
 *          - 刪除 MdsStockSnapshotBodyT.MDStreamID, MdsIndexSnapshotBodyT.MDStreamID 欄位
 *          - 為'市場狀態'和'證券實時狀態'訊息新增 __exchSendingTime, __mdsRecvTime 欄位,
 *            以方便比對實際的行情延時
 * @version 0.12.8.2    2017/05/16
 *          - 新增 '逐筆資料丟失訊息(MdsL2TickLostT)', 以通知下游系統逐筆資料(逐筆成交/逐筆
 *            委託)發生了資料丟失, 並且無法重建, 將放棄這些丟失的逐筆資料
 *          - 調整證券實時狀態結構體中延遲打點時間戳欄位的欄位位置, 將這些欄位調整到結構體的末尾,
 *            以方便客戶端相容處理
 * @version 0.12.9.7    2017/07/12
 *          - 不再對外發布逐筆丟失訊息(MDS_MSGTYPE_L2_TICK_LOST), 該訊息已廢棄
 * @version 0.15.4.1    2017/09/07
 *          - 預設開啟用於統計延時的打點資訊, 並將打點資訊的時間戳型別改為 timeval32 (STimeval32T) 型別,
 *            同時將行情推送的打點資訊, 從訊息頭遷移到訊息體中 (__pushingTime)
 * @version 0.15.5.10   2018/05/20
 *          - 行情結構體中增加內部頻道號欄位 (相容之前版本), 該欄位僅內部使用, 前端不需要關心和處理
 * @version 0.15.5.11   2018/06/01
 *          - 擴大Level2增量更新訊息中最大已變更價位列表和委託明細的最大數量, 修復因為支援
 *            同時變更的價位數量不足, 導致部分巨幅波動場景下會丟失價位資訊的BUG
 * @version 0.15.7.6_RC1 2018/11/06
 *          - 重新命名 L1快照體(MdsL1SnapshotBodyT) 的初始化巨集名稱
 *            - NULLOBJ_MDS_MKT_DATA_SNAPSHOT_BODY => NULLOBJ_MDS_L1_SNAPSHOT_BODY
 * @version 0.15.8_RC3  2019/01/14
 *          - 刪除已經廢棄的虛擬集合競價訊息的訊息定義和資料型別定義
 *          - 重新命名 securityType => mdProductType, 以避免與交易端的證券型別混淆
 *              - securityType => mdProductType
 *              - eMdsSecurityTypeT => eMdsMdProductTypeT
 * @version 0.15.8_u1   2019/03/22
 *          - 交易所程式碼的列舉型別中增加 '未定義的交易所程式碼 (MDS_EXCH_UNDEFINE)'
 * @version 0.15.8_u6   2019/05/06
 *          - 調整快照頭 MdsMktDataSnapshotHeadT 中的內部欄位定義, 將 __origTickSeq 欄位
 *            拆分為 __origTickSeq + __lastUpdateTime 兩個欄位 (內部使用的欄位, 協議保持相容)
 * @version 0.15.9      2019/03/12
 *          - 為了支援科創板, 擴充套件證券靜態資訊(MdsStockStaticInfoT)的結構體定義, 增加如下欄位:
 *              - 限價買數量上限 (lmtBuyMaxQty)
 *              - 限價買數量下限 (lmtBuyMinQty)
 *              - 限價賣數量上限 (lmtSellMaxQty)
 *              - 限價賣數量下限 (lmtSellMinQty)
 *              - 市價買數量上限 (mktBuyMaxQty)
 *              - 市價買數量下限 (mktBuyMinQty)
 *              - 市價賣數量上限 (mktSellMaxQty)
 *              - 市價賣數量下限 (mktSellMinQty)
 *          - 擴大證券業務開關的最大數量, 該修改可能會對之前版本的API造成影響, 相容性問題如下:
 *              - 會影響到證券實時狀態訊息的延遲計算, 舊版本會讀取到無效的打點時間
 *          - 調整行情資料型別(mdStreamType, eMdsMdStreamTypeT)的取值, 使其可以標識出快
 *            照行情的具體資料型別
 *              - 該修改會存在相容性問題, 客戶端程式可以通過編譯錯誤來識別需要調整的地方 (如
 *                果沒有編譯錯誤就不需要調整)
 *              - 行情資料型別的取值將盡量與訊息型別保持一致, 但以下型別比較特殊
 *                  - 深圳成交量統計指標
 *                  - 上交所 Level1 行情快照-債券
 *                  - 上交所 Level1 行情快照-基金
 *          - 巨集定義 '使用者名稱最大長度 (MDS_MAX_USERNAME_LEN)' 從 40 調整為 32
 *
 * @since   2016/02/11
 */


#ifndef _MDS_BASE_MODEL_H
#define _MDS_BASE_MODEL_H


#include    <sutil/types.h>


#ifdef __cplusplus
extern "C" {
#endif


/* ===================================================================
 * 預編譯巨集處理
 * =================================================================== */

/* 預設開啟用於統計延時的打點資訊 */
#if ! defined (_MDS_DISABLE_LATENCY_STATS) \
        && ! defined (_MDS_ENABLE_LATENCY_STATS)
#   define  _MDS_ENABLE_LATENCY_STATS           1
#elif defined (_MDS_DISABLE_LATENCY_STATS) \
        && defined (_MDS_ENABLE_LATENCY_STATS)
#   undef   _MDS_ENABLE_LATENCY_STATS
#endif
/* -------------------------           */


/* ===================================================================
 * 常量定義 (巨集定義)
 * =================================================================== */

/** 每次的行情訂閱請求中可以同時指定的最大訂閱產品數量 (可以通過追加訂閱的方式訂閱更多的產品) */
#define MDS_MAX_SECURITY_CNT_PER_SUBSCRIBE      (4000)
/** 對於滬/深兩市的期權產品, 限制對每個市場最多允許同時訂閱 2000 只產品 */
#define MDS_MAX_OPTION_CNT_TOTAL_SUBSCRIBED     (2000)

/** 使用者名稱最大長度 */
#define MDS_MAX_USERNAME_LEN                    (32)
/** 密碼最大長度 */
#define MDS_MAX_PASSWORD_LEN                    (40)
/** 協議版本號的最大長度 */
#define MDS_VER_ID_MAX_LEN                      (32)
/** 測試請求識別符號的最大長度 */
#define MDS_MAX_TEST_REQ_ID_LEN                 (32)

/** 點分十進位制的IPv4, 字串的最大長度 */
#define MDS_MAX_IP_LEN                          (16)
/** MAC地址字串的最大長度 */
#define MDS_MAX_MAC_LEN                         (20)
/** MAC地址字串的最大長度(按64位對齊的長度) */
#define MDS_MAX_MAC_ALGIN_LEN                   (24)
/** 裝置序列號字串的最大長度 */
#define MDS_MAX_DRIVER_ID_LEN                   (21)
/** 裝置序列號字串的最大長度(按64位對齊的長度) */
#define MDS_MAX_DRIVER_ID_ALGIN_LEN             (24)

/** 產品程式碼長度(C6/C8) */
#define MDS_MAX_INSTR_CODE_LEN                  (9)
/** 實際的股票產品程式碼長度 */
#define MDS_REAL_STOCK_CODE_LEN                 (6)
/** 實際的期權產品程式碼長度 */
#define MDS_REAL_OPTION_CODE_LEN                (8)
/** 允許帶.SH/.SZ字尾的產品程式碼的最大長度 */
#define MDS_MAX_POSTFIXED_INSTR_CODE_LEN        (12)

/** 產品名稱最大長度 */
#define MDS_MAX_SECURITY_NAME_LEN               (40)

/** 傳送時間欄位(YYYYMMDD-HH:mm:SS.sss (*C21))的最大長度 */
#define MDS_MAX_SENDING_TIME_LEN                (22)
/** 傳送時間欄位(YYYYMMDD-HH:mm:SS.sss (*C21))的實際有效資料長度 */
#define MDS_REAL_SENDING_TIME_LEN               (21)

/** 交易日期欄位(YYYYMMDD (*C8))的最大長度 */
#define MDS_MAX_TRADE_DATE_LEN                  (9)
/** 交易日期欄位(YYYYMMDD (*C8))的實際有效資料長度 */
#define MDS_REAL_TRADE_DATE_LEN                 (8)

/** 最新更新時間欄位(HHMMSSss (*C8))的最大長度 */
#define MDS_MAX_UPDATE_TIME_LEN                 (9)
/** 最新更新時間欄位(HHMMSSss (*C8))的實際有效資料長度 */
#define MDS_REAL_UPDATE_TIME_LEN                (8)

/** 全市場行情狀態欄位(*C8)的最大長度 */
#define MDS_MAX_TRADING_SESSION_ID_LEN          (9)
/** 全市場行情狀態欄位(*C8)的實際有效資料長度 */
#define MDS_REAL_TRADING_SESSION_ID_LEN         (8)

/** 產品實時階段及標誌(C8/C4)的最大長度 */
#define MDS_MAX_TRADING_PHASE_CODE_LEN          (9)
/** 產品實時階段及標誌(C8/C4)的實際有效資料長度 */
#define MDS_REAL_TRADING_PHASE_CODE_LEN         (8)

/** 證券狀態欄位(深圳證券實時狀態訊息 C8)的最大長度 */
#define MDS_MAX_FINANCIAL_STATUS_LEN            (9)
/** 證券狀態欄位(深圳證券實時狀態訊息 C8)的實際有效資料長度 */
#define MDS_REAL_FINANCIAL_STATUS_LEN           (8)

/** 證券業務開關的最大數量(深圳證券實時狀態訊息) */
#define MDS_MAX_SECURITY_SWITCH_CNT             (40)

/** 統一的價格單位 */
#define MDS_UNIFIED_PRICE_UNIT                  (10000)
/** 統一的金額單位 */
#define MDS_UNIFIED_MONEY_UNIT                  (10000)

/** 總成交金額的金額單位 (上證的總成交金額精度原本為2位, 但在此統一整合為4位精度) */
#define MDS_TOTAL_VALUE_TRADED_UNIT             MDS_UNIFIED_MONEY_UNIT
/** 指數的價格單位 */
#define MDS_INDEX_PRICE_UNIT                    MDS_UNIFIED_PRICE_UNIT
/** 股票的價格單位 (上證的股票價格精度原本為3位, 但在此統一整合為4位精度) */
#define MDS_STOCK_PRICE_UNIT                    MDS_UNIFIED_PRICE_UNIT
/** 期權的價格單位 */
#define MDS_OPTION_PRICE_UNIT                   MDS_UNIFIED_PRICE_UNIT

/** 股票程式碼的最大範圍 */
#define MDS_MAX_STOCK_ID_SCOPE                  (1000000)
/** 期權程式碼的最大範圍 */
#define MDS_MAX_OPTION_ID_SCOPE                 (100000000)
/* -------------------------           */


/* ===================================================================
 * Level2 相關的常量定義
 * =================================================================== */

/** Level2增量更新的價位列表最大數量 */
#define MDS_MAX_L2_PRICE_LEVEL_INCREMENTS       (40)

/** Level2披露的買一／賣一委託明細最大數量 */
#define MDS_MAX_L2_DISCLOSE_ORDERS_CNT          (50)

/** Level2增量更新的委託明細最大數量 */
#define MDS_MAX_L2_DISCLOSE_ORDERS_INCREMENTS   (152)
/* -------------------------           */


/* ===================================================================
 * 常量定義 (列舉型別定義)
 * =================================================================== */

/**
 * 交易所程式碼
 */
typedef enum _eMdsExchangeId {
    MDS_EXCH_UNDEFINE                   = 0,    /**< 未定義的交易所程式碼 */
    MDS_EXCH_SSE                        = 1,    /**< 交易所-上交所 */
    MDS_EXCH_SZSE                       = 2,    /**< 交易所-深交所 */
    __MAX_MDS_EXCH,

    __MAX_MDS_EXCH_ALIGNED4             = 4,    /**< 交易所程式碼最大值 (按4位元組對齊的大小) */
    __MAX_MDS_EXCH_ALIGNED8             = 8     /**< 交易所程式碼最大值 (按8位元組對齊的大小) */
} eMdsExchangeIdT;


/**
 * 訊息來源
 */
typedef enum _eMdsMsgSource {
    MDS_MSGSRC_UNDEFINED                = 0,    /**< 訊息來源-未定義 */
    MDS_MSGSRC_EZEI_TCP                 = 1,    /**< 訊息來源-EzEI(TCP) */
    MDS_MSGSRC_EZEI_UDP                 = 2,    /**< 訊息來源-EzEI(UDP) */

    MDS_MSGSRC_VDE_LEVEL2               = 3,    /**< 訊息來源-SSE-VDE-LEVEL2 */
    MDS_MSGSRC_VDE_LEVEL1               = 4,    /**< 訊息來源-SSE-VDE-LEVEL1-FAST */

    MDS_MSGSRC_SZSE_MDGW_BINARY         = 5,    /**< 訊息來源-SZSE-MDGW-Binary(TCP) */
    MDS_MSGSRC_SZSE_MDGW_STEP           = 6,    /**< 訊息來源-SZSE-MDGW-STEP(TCP) */

    MDS_MSGSRC_MDS_TCP                  = 7,    /**< 訊息來源-MDS(TCP) */
    MDS_MSGSRC_MDS_UDP                  = 8,    /**< 訊息來源-MDS(UDP) */

    MDS_MSGSRC_FILE_MKTDT               = 9,    /**< 訊息來源-檔案(mktdt) */

    MDS_MSGSRC_SSE_MDGW_BINARY          = 10,   /**< 訊息來源-SSE-MDGW-Binary(TCP) */
    MDS_MSGSRC_SSE_MDGW_STEP            = 11,   /**< 訊息來源-SSE-MDGW-Binary(TCP) */
    __MAX_MDS_MSGSRC,

    /** 訊息來源-SZSE-MDGW-Binary @deprecated 已過時, 請使用 MDS_MSGSRC_SZSE_MDGW_BINARY */
    MDS_MSGSRC_MDGW_BINARY              = MDS_MSGSRC_SZSE_MDGW_BINARY,
    /** 訊息來源-SZSE-MDGW-STEP @deprecated 已過時, 請使用 MDS_MSGSRC_SZSE_MDGW_STEP */
    MDS_MSGSRC_MDGW_STEP                = MDS_MSGSRC_SZSE_MDGW_STEP
} eMdsMsgSourceT;


/**
 * 行情類別 (和交易端的產品型別不同, 行情資料中的產品型別只是用於區分是現貨行情還是衍生品行情)
 */
typedef enum _eMdsMdProductType {
    MDS_MD_PRODUCT_TYPE_STOCK           = 1,    /**< 股票(基金/債券) */
    MDS_MD_PRODUCT_TYPE_INDEX           = 2,    /**< 指數 */
    MDS_MD_PRODUCT_TYPE_OPTION          = 3,    /**< 期權 */
    __MAX_MDS_MD_PRODUCT_TYPE,

    /* @deprecated 以下定義已過時, 為保持相容而暫時保留 */
    MDS_SECURITY_TYPE_STOCK             = MDS_MD_PRODUCT_TYPE_STOCK,
    MDS_SECURITY_TYPE_INDEX             = MDS_MD_PRODUCT_TYPE_INDEX,
    MDS_SECURITY_TYPE_OPTION            = MDS_MD_PRODUCT_TYPE_OPTION,
    __MAX_MDS_SECURITY_TYPE             = __MAX_MDS_MD_PRODUCT_TYPE
} eMdsMdProductTypeT;


/**
 * 行情資料型別 (僅適用於快照行情, 用於標識 Level1/Level2 快照行情的具體資料型別)
 *
 * @note    行情資料型別的取值將盡量與訊息型別保持一致, 但以下型別比較特殊
 *          - 深圳成交量統計指標
 *          - 上交所 Level1 行情快照-債券
 *          - 上交所 Level1 行情快照-基金
 * @see     eMdsMsgTypeT
 */
typedef enum _eMdsMdStreamType {
    /** Level1 市場行情快照 (10/0x0A) */
    MDS_MD_STREAM_TYPE_L1_SNAPSHOT      = 10,
    /** Level1/Level2 指數行情快照 (11/0x0B) */
    MDS_MD_STREAM_TYPE_INDEX            = 11,
    /** Level1/Level2 期權行情快照 (12/0x0C) */
    MDS_MD_STREAM_TYPE_OPTION           = 12,

    /** 深交所 Level1/Level2 成交量統計指標 (15/0x0F, 結構與指數行情相同) */
    MDS_MD_STREAM_TYPE_SZSE_TRADE_STATS = 15,
    /** 上交所 Level1 行情快照-債券 (16/0x10, 僅適用於上海Level-1行情) */
    MDS_MD_STREAM_TYPE_SSE_L1_BOND      = 16,
    /** 上交所 Level1 行情快照-基金 (17/0x11, 僅適用於上海Level-1行情) */
    MDS_MD_STREAM_TYPE_SSE_L1_FUND      = 17,

    /** Level2 市場行情快照 (20/0x14) */
    MDS_MD_STREAM_TYPE_L2_SNAPSHOT      = 20,
    /** Level2 委託佇列快照 (買一/賣一前五十筆) (21/0x15) */
    MDS_MD_STREAM_TYPE_L2_BEST_ORDERS_SNAPSHOT
                                        = 21,

    /** Level2 快照行情的增量更新訊息 (24/0x18, 僅上海) */
    MDS_MD_STREAM_TYPE_L2_SNAPSHOT_INCREMENTAL
                                        = 24,
   /** Level2 委託佇列快照的增量更新訊息 (25/0x19, 僅上海) */
    MDS_MD_STREAM_TYPE_L2_BEST_ORDERS_INCREMENTAL
                                        = 25,

    /** Level2 市場總覽訊息 (26/0x1A, 僅上海) */
    MDS_MD_STREAM_TYPE_L2_MARKET_OVERVIEW
                                        = 26,
    __MAX_MDS_MD_STREAM_TYPE,

    /* @deprecated 以下定義已過時, 為保持相容而暫時保留 */
    MDS_MD_STREAM_TYPE_BOND             = MDS_MD_STREAM_TYPE_SSE_L1_BOND,
    MDS_MD_STREAM_TYPE_FUND             = MDS_MD_STREAM_TYPE_SSE_L1_FUND,
    MDS_MD_STREAM_TYPE_OTHERS           = MDS_MD_STREAM_TYPE_L2_MARKET_OVERVIEW
} eMdsMdStreamTypeT;


/**
 * 行情資料級別 (Level1 / Level2)
 */
typedef enum _eMdsMdLevel {
    MDS_MD_LEVEL_0                      = 0,    /**< 未設定 */
    MDS_MD_LEVEL_1                      = 1,    /**< Level-1 行情 */
    MDS_MD_LEVEL_2                      = 2,    /**< Level-2 行情 */
    __MAX_MDS_MD_LEVEL
} eMdsMdLevelT;


/**
 * Level2增量更新訊息的價位運算 (1=Add, 2=Update, 3=Delete)
 */
typedef enum _eMdsL2PriceLevelOperator {
    MDS_L2_PX_OPERATOR_ADD              = 1,    /**< L2價位運算 - Add */
    MDS_L2_PX_OPERATOR_UPDATE           = 2,    /**< L2價位運算 - Update */
    MDS_L2_PX_OPERATOR_DELETE           = 3,    /**< L2價位運算 - Delete */
    __MAX_MDS_L2_PX_OPERATOR
} eMdsL2PriceLevelOperatorT;


/**
 * Level2逐筆成交的成交類別
 * - 僅適用於深交所 ('4'=撤銷, 'F'=成交)
 * - 對於上證, 將固定取值為 'F'(成交)
 */
typedef enum _eMdsL2TradeExecType {
    MDS_L2_TRADE_EXECTYPE_CANCELED      = '4',  /**< L2執行型別 - 已撤銷 */
    MDS_L2_TRADE_EXECTYPE_TRADE         = 'F',  /**< L2執行型別 - 已成交 */
} eMdsL2TradeExecTypeT;


/**
 * Level2逐筆成交的內外盤標誌
 * - 僅適用於上證 ('B'=外盤,主動買, 'S'=內盤,主動賣, 'N'=未知)
 * - 對於深交所, 將固定取值為 'N'(未知)
 */
typedef enum _eMdsL2TradeBSFlag {
    MDS_L2_TRADE_BSFLAG_BUY             = 'B',  /**< L2內外盤標誌 - 外盤,主動買 */
    MDS_L2_TRADE_BSFLAG_SELL            = 'S',  /**< L2內外盤標誌 - 內盤,主動賣 */
    MDS_L2_TRADE_BSFLAG_UNKNOWN         = 'N',  /**< L2內外盤標誌 - 未知 */
} eMdsL2TradeBSFlagT;


/**
 * Level2逐筆委託的買賣方向 ('1'=買 '2'=賣 'G'=借入 'F'=出借)
 */
typedef enum _eMdsL2OrderSideT {
    MDS_L2_ORDER_SIDE_BUY               = '1',  /**< L2買賣方向 - 買 */
    MDS_L2_ORDER_SIDE_SELL              = '2',  /**< L2買賣方向 - 賣 */
    MDS_L2_ORDER_SIDE_BORROW            = 'G',  /**< L2買賣方向 - 借入 */
    MDS_L2_ORDER_SIDE_LEND              = 'F'   /**< L2買賣方向 - 出借 */
} eMdsL2OrderSideT;


/**
 * Level2逐筆委託的訂單型別 ('1'=市價 '2'=限價 'U'=本方最優)
 */
typedef enum _eMdsL2OrderType {
    MDS_L2_ORDER_TYPE_MKT               = '1',  /**< L2訂單型別 - 市價 */
    MDS_L2_ORDER_TYPE_LMT               = '2',  /**< L2訂單型別 - 限價 */
    MDS_L2_ORDER_TYPE_SAMEPARTY_BEST    = 'U'   /**< L2訂單型別 - 本方最優 */
} eMdsL2OrderTypeT;


/**
 * 客戶端型別定義 (內部使用)
 */
typedef enum _eMdsClientType {
    MDS_CLIENT_TYPE_UNDEFINED           = 0,    /**< 客戶端型別-未定義 */
    MDS_CLIENT_TYPE_INVESTOR            = 1,    /**< 普通投資人 */
    MDS_CLIENT_TYPE_VIRTUAL             = 2     /**< 虛擬賬戶 (僅開通行情, 不可交易) */
} eMdsClientTypeT;


/**
 * 客戶端狀態定義 (內部使用)
 */
typedef enum _eMdsClientStatus {
    MDS_CLIENT_STATUS_UNACTIVATED       = 0,    /**< 未啟用 (不載入) */
    MDS_CLIENT_STATUS_ACTIVATED         = 1,    /**< 已啟用 (正常載入) */
    MDS_CLIENT_STATUS_PAUSE             = 2,    /**< 已暫停 (正常載入, 不可交易) */
    MDS_CLIENT_STATUS_SUSPENDED         = 3,    /**< 已掛起 (正常載入, 不可交易、不可出入金) */
    MDS_CLIENT_STATUS_CANCELLED         = 4     /**< 已登出 (不載入) */
} eMdsClientStatusT;
/* -------------------------           */


/* ===================================================================
 * Level1 行情訊息定義
 * =================================================================== */

/**
 * 市場狀態訊息(MsgType=h)定義 (僅適用於上海市場, 深圳市場沒有該行情)
 */
typedef struct _MdsTradingSessionStatusMsg {
    uint8               exchId;                 /**< 交易所程式碼(滬/深) @see eMdsExchangeIdT */
    uint8               mdProductType;          /**< 行情類別 (股票/指數/期權) @see eMdsMdProductTypeT */
    int8                __isRepeated;           /**< 是否是重複的行情 (供內部使用, 小於0 表示資料倒流) */
    uint8               __filler1;              /**< 按64位對齊的填充域 */

    int32               tradeDate;              /**< 交易日期 (YYYYMMDD, 通過拆解SendingTime得到, 並非官方資料) */
    int32               updateTime;             /**< 行情時間 (HHMMSSsss, 交易所時間, 通過拆解SendingTime得到, 並非官方資料) */
    int32               __exchSendingTime;      /**< 交易所傳送時間 (HHMMSSsss) */
    int32               __mdsRecvTime;          /**< MDS接收到時間 (HHMMSSsss) */

    int32               TotNoRelatedSym;        /**< 最大產品數目 (包括指數) */

    /**
     * 全市場行情狀態 (*C8)
     * 該欄位為 8 位字串,左起每位表示特定的含義,無定義則填空格。
     * 第 1 位: ‘S’表示全市場啟動期間(開市前), ‘T’表示全市場處於交易期間 (含中間休市), ‘E’表示全市場處於閉市期間。
     * 第 2 位: ‘1’表示開盤集合競價結束標誌, 未結束取‘0’。
     * 第 3 位: ‘1’表示市場行情閉市標誌, 未閉市取‘0’。
     */
    char                TradingSessionID[MDS_MAX_TRADING_SESSION_ID_LEN];

    uint8               __filler3[3];           /**< 按64位對齊的填充域 */
    uint32              __dataVersion;          /**< 行情資料的更新版本號 (當__isRepeated!=0時, 該值僅作為參考值) */
    uint64              __origTickSeq;          /**< 對應的原始行情的序列號(供內部使用) */

#ifdef  _MDS_ENABLE_LATENCY_STATS
    /** 訊息原始接收時間 (從網路接收到資料的最初時間) */
    STimeval32T         __origNetTime;
    /** 訊息實際接收時間 (開始解碼等處理之前的時間) */
    STimeval32T         __recvTime;
    /** 訊息採集處理完成時間 */
    STimeval32T         __collectedTime;
    /** 訊息加工處理完成時間 */
    STimeval32T         __processedTime;
    /** 訊息推送時間 (寫入推送快取以後, 實際網路傳送之前) */
    STimeval32T         __pushingTime;
#endif

} MdsTradingSessionStatusMsgT;


/* 結構體初始化值的尾部填充欄位定義 */
#ifdef  _MDS_ENABLE_LATENCY_STATS
# define    __NULLOBJ_MDS_TRADING_SESSION_STATUS_MSG_TAILER             \
            , {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}
#else
# define    __NULLOBJ_MDS_TRADING_SESSION_STATUS_MSG_TAILER
#endif


/* 結構體的初始化值定義 */
#define NULLOBJ_MDS_TRADING_SESSION_STATUS_MSG                          \
        NULLOBJ_MDS_TRADING_SESSION_STATUS_MSG2(0)

/* 結構體的初始化值定義 */
#define NULLOBJ_MDS_TRADING_SESSION_STATUS_MSG2(EXCH_ID)                \
        (EXCH_ID), 0, 0, 0, \
        0, 0, 0, 0, 0, \
        {0}, \
        {0}, 0, 0 \
        __NULLOBJ_MDS_TRADING_SESSION_STATUS_MSG_TAILER
/* -------------------------           */


/**
 * 證券實時狀態定義 (僅適用於深圳市場, 上海市場沒有該行情)
 */
typedef struct _MdsSecurityStatusMsg {
    uint8               exchId;                 /**< 交易所程式碼(滬/深) @see eMdsExchangeIdT */
    uint8               mdProductType;          /**< 行情類別 (股票/指數/期權) @see eMdsMdProductTypeT */
    int8                __isRepeated;           /**< 是否是重複的行情 (供內部使用, 小於0 表示資料倒流) */
    uint8               __filler1;              /**< 按64位對齊的填充域 */

    int32               tradeDate;              /**< 交易日期 (YYYYMMDD, 通過拆解資料生成時間OrigTime得到) */
    int32               updateTime;             /**< 行情時間 (HHMMSSsss, 交易所時間, 通過拆解資料生成時間OrigTime得到) */
    int32               __exchSendingTime;      /**< 交易所傳送時間 (HHMMSSsss, 目前獲取不到深交所的傳送時間, 固定為 0) */
    int32               __mdsRecvTime;          /**< MDS接收到時間 (HHMMSSsss) */

    int32               instrId;                /**< 產品程式碼 (轉換為整數型別的產品程式碼) */

    /** 產品程式碼 C6 / C8 (如: '000001' 等) */
    char                SecurityID[MDS_MAX_INSTR_CODE_LEN];

    /**
     * 證券狀態 (C8)
     * A=上市公司早間披露提示
     * B=上市公司午間披露提示
     */
    char                FinancialStatus[MDS_MAX_FINANCIAL_STATUS_LEN];

    uint8               __filler2;              /**< 按64位對齊的填充域 */
    uint8               __channelNo;            /**< 內部頻道號 (供內部使用, 取值範圍{1,2,4,8}) */
    uint32              __dataVersion;          /**< 行情資料的更新版本號 (當__isRepeated!=0時, 該值僅作為參考值) */
    uint64              __origTickSeq;          /**< 對應的原始行情的序列號(供內部使用) */

    int32               NoSwitch;               /**< 開關個數 */
    int32               __filler4;              /**< 按64位對齊的填充域 */

    /**
     * 證券業務開關列表
     * 業務開關列表為定長陣列, 陣列的下標位置對應於各個業務開關, 業務開關說明如下:
     *  -  1: 融資買入, 適用於融資標的證券
     *  -  2: 融券賣出, 適用於融券標的證券
     *  -  3: 申購, 適用於 ETF/LOF 等開放式基金, 對於黃金 ETF 是指現金申購
     *  -  4: 贖回, 適用於 ETF/LOF 等開放式基金, 對於黃金 ETF 是指現金贖回開關
     *  -  5: 認購, 適用於網上發行認購程式碼
     *  -  6: 轉股, 適用於處於轉股回售期的可轉債
     *  -  7: 回售, 適用於處於轉股回售期的可轉債
     *  -  8: 行權, 適用於處於行權期的權證或期權
     *  - 10: 買開倉, 適用於期權等衍生品
     *  - 11: 賣開倉, 適用於期權等衍生品
     *  - 12: 黃金ETF實物申購, 適用於黃金 ETF
     *  - 13: 黃金ETF實物贖回, 適用於黃金 ETF
     *  - 14: 預受要約, 適用於處於要約收購期的股票
     *  - 15: 解除要約, 適用於處於要約收購期的股票
     *  - 18: 轉股撤單, 適用於處於轉股回售期的可轉債
     *  - 19: 回售撤單, 適用於處於轉股回售期的可轉債
     *  - 20: 質押, 適用於質押式回購可質押入庫證券
     *  - 21: 解押, 適用於質押式回購可質押入庫證券
     *  - 22: 表決權, 適用於優先股
     *  - 23: 股票質押式回購, 適用於可開展股票質押式回購業務的證券
     *  - 24: 實時分拆, 適用於分級基金
     *  - 25: 實時合併, 適用於分級基金
     *  - 26: 備兌開倉, 適用於期權等衍生品
     *  - 27: 做市商報價, 適用於期權等支援做市商報價的證券
     *  - 28: 港股通整手買
     *  - 29: 港股通整手賣
     *  - 30: 港股通零股買
     *  - 31: 港股通零股賣
     *  - 32: 期權普通轉備兌倉
     *  - 33: 期權備兌轉普通倉
     */
    struct {
        /** 業務開關的使能標誌 (0 未啟用, 1 啟用) */
        uint8           switchFlag;

        /** 開關狀態 (0 關閉, 1 開啟) */
        uint8           switchStatus;
    } switches[MDS_MAX_SECURITY_SWITCH_CNT];

#ifdef  _MDS_ENABLE_LATENCY_STATS
    /** 訊息原始接收時間 (從網路接收到資料的最初時間) */
    STimeval32T         __origNetTime;
    /** 訊息實際接收時間 (開始解碼等處理之前的時間) */
    STimeval32T         __recvTime;
    /** 訊息採集處理完成時間 */
    STimeval32T         __collectedTime;
    /** 訊息加工處理完成時間 */
    STimeval32T         __processedTime;
    /** 訊息推送時間 (寫入推送快取以後, 實際網路傳送之前) */
    STimeval32T         __pushingTime;
#endif

} MdsSecurityStatusMsgT;


/* 結構體初始化值的尾部填充欄位定義 */
#ifdef  _MDS_ENABLE_LATENCY_STATS
# define    __NULLOBJ_MDS_SECURITY_STATUS_MSG_TAILER                    \
            , {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}
#else
# define    __NULLOBJ_MDS_SECURITY_STATUS_MSG_TAILER
#endif


/* 結構體的初始化值定義 */
#define NULLOBJ_MDS_SECURITY_STATUS_MSG                                 \
        0, 0, 0, 0, \
        0, 0, 0, 0, 0, \
        {0}, {0}, \
        0, 0, 0, 0, \
        0, 0, \
        { \
            {0, 0}, {0, 0}, {0, 0}, {0, 0}, \
            {0, 0}, {0, 0}, {0, 0}, {0, 0}, \
            {0, 0}, {0, 0}, {0, 0}, {0, 0}, \
            {0, 0}, {0, 0}, {0, 0}, {0, 0}, \
            {0, 0}, {0, 0}, {0, 0}, {0, 0}, \
            {0, 0}, {0, 0}, {0, 0}, {0, 0}, \
            {0, 0}, {0, 0}, {0, 0}, {0, 0}, \
            {0, 0}, {0, 0}, {0, 0}, {0, 0}, \
            {0, 0}, {0, 0}, {0, 0}, {0, 0}, \
            {0, 0}, {0, 0}, {0, 0}, {0, 0}, \
        } \
        __NULLOBJ_MDS_SECURITY_STATUS_MSG_TAILER
/* -------------------------           */


/* ===================================================================
 * Level1 快照行情定義
 * =================================================================== */

/**
 * 價位資訊定義
 */
typedef struct _MdsPriceLevelEntry {
    int32               Price;                  /**< 委託價格 */
    int32               NumberOfOrders;         /**< 價位總委託筆數 (Level1不揭示該值, 固定為0) */
    int64               OrderQty;               /**< 委託數量 */
} MdsPriceLevelEntryT;


/* 結構體的初始化值定義 */
#define NULLOBJ_MDS_PRICE_LEVEL_ENTRY                                   \
        0, 0, 0
/* -------------------------           */


/**
 * Level1/Level2 快照行情(證券行情全幅訊息)的訊息頭定義
 */
typedef struct _MdsMktDataSnapshotHead {
    uint8               exchId;                 /**< 交易所程式碼(滬/深) @see eMdsExchangeIdT */
    uint8               mdProductType;          /**< 行情類別 (股票/指數/期權) @see eMdsMdProductTypeT */
    int8                __isRepeated;           /**< 是否是重複的行情 (內部使用, 小於0表示資料倒流) */
    uint8               __origMdSource;         /**< 原始行情資料來源 @see eMdsMsgSourceT */

    int32               tradeDate;              /**< 交易日期 (YYYYMMDD, 8位整型數值) */
    int32               updateTime;             /**< 行情時間 (HHMMSSsss, 交易所時間, 只有上海L1可能會通過拆解SendingTime得到) */

    int32               instrId;                /**< 產品程式碼 (轉換為整數型別的產品程式碼) */
    int16               bodyLength;             /**< 實際資料長度 */
    uint8               mdStreamType;           /**< 行情資料型別 @see eMdsMdStreamTypeT */
    uint8               __channelNo;            /**< 內部頻道號 (供內部使用, 取值範圍{1,2,4,8}) */
    uint32              __dataVersion;          /**< 行情資料的更新版本號 */
    uint32              __origTickSeq;          /**< 對應的原始行情的序列號(供內部使用) */
    int32               __lastUpdateTime;       /**< 最近一次重複資料的行情時間(供內部使用) */

#ifdef  _MDS_ENABLE_LATENCY_STATS
    /** 訊息原始接收時間 (從網路接收到資料的最初時間) */
    STimeval32T         __origNetTime;
    /** 訊息實際接收時間 (開始解碼等處理之前的時間) */
    STimeval32T         __recvTime;
    /** 訊息採集處理完成時間 */
    STimeval32T         __collectedTime;
    /** 訊息加工處理完成時間 */
    STimeval32T         __processedTime;
    /** 訊息推送時間 (寫入推送快取以後, 實際網路傳送之前) */
    STimeval32T         __pushingTime;
#endif

} MdsMktDataSnapshotHeadT;


/* 結構體初始化值的尾部填充欄位定義 */
#ifdef  _MDS_ENABLE_LATENCY_STATS
# define    __NULLOBJ_MDS_MKT_DATA_SNAPSHOT_HEAD_TAILER                 \
            , {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}
#else
# define    __NULLOBJ_MDS_MKT_DATA_SNAPSHOT_HEAD_TAILER
#endif


/* 結構體的初始化值定義 */
#define NULLOBJ_MDS_MKT_DATA_SNAPSHOT_HEAD                              \
        NULLOBJ_MDS_MKT_DATA_SNAPSHOT_HEAD3(0, 0, 0)

/* 結構體的初始化值定義 */
#define NULLOBJ_MDS_MKT_DATA_SNAPSHOT_HEAD2(EXCH_ID, MD_SOURCE)         \
        NULLOBJ_MDS_MKT_DATA_SNAPSHOT_HEAD3(EXCH_ID, 0, (MD_SOURCE))

/* 結構體的初始化值定義 */
#define NULLOBJ_MDS_MKT_DATA_SNAPSHOT_HEAD3(EXCH_ID, SECURITY_TYPE,     \
                MD_SOURCE)                                              \
        (EXCH_ID), (SECURITY_TYPE), 0, (MD_SOURCE), \
        0, 0, \
        0, 0, 0, 0, 0, 0, 0 \
        __NULLOBJ_MDS_MKT_DATA_SNAPSHOT_HEAD_TAILER
/* -------------------------           */


/**
 * Level1/Level2 指數快照行情定義
 */
typedef struct _MdsIndexSnapshotBody {
    /** 產品程式碼 C6 / C8 (如: '000001' 等) */
    char                SecurityID[MDS_MAX_INSTR_CODE_LEN];
    /**
     * 產品實時階段及標誌 C8
     * @see MdsStockSnapshotBodyT.TradingPhaseCode
     */
    char                TradingPhaseCode[MDS_MAX_TRADING_PHASE_CODE_LEN];
    char                __filler[6];            /**< 按64位對齊的填充域 */

    uint64              NumTrades;              /**< 成交筆數 (僅適用於深圳, 上海指數行情中沒有成交筆數資訊) */
    uint64              TotalVolumeTraded;      /**< 成交總量 (@note 上海指數的成交量單位是手, 深圳指數的成交量單位是股) */
    int64               TotalValueTraded;       /**< 成交總金額 (金額單位精確到元后四位, 即: 1元=10000) */

    int64               PrevCloseIdx;           /**< 昨日收盤指數 (價格單位精確到元后四位, 即: 1元=10000) */
    int64               OpenIdx;                /**< 今開盤指數 (價格單位精確到元后四位, 即: 1元=10000) */
    int64               HighIdx;                /**< 最高指數 */
    int64               LowIdx;                 /**< 最低指數 */
    int64               LastIdx;                /**< 最新指數 */
    int64               CloseIdx;               /**< 今收盤指數 (僅上海, 深圳行情沒有單獨的收盤指數) */

    int32               StockNum;               /**< 統計量指標樣本個數 (用於深圳成交量統計指標) */
    int32               __filler1;              /**< 按64位對齊的填充域 */
} MdsIndexSnapshotBodyT;


/* 結構體的初始化值定義 */
#define NULLOBJ_MDS_INDEX_SNAPSHOT_BODY                                 \
        {0}, {0}, {0}, \
        0, 0, 0, \
        0, 0, 0, 0, 0, 0, \
        0, 0
/* -------------------------           */


/**
 * Level1 股票快照行情定義
 * 股票(A、B股)、債券、基金、期權
 *
 * 關於集合競價期間的虛擬集合競價行情 (上海L1、深圳L1):
 * - 集合競價期間的虛擬成交價通過買賣盤檔位揭示, 其中買一和賣一都揭示虛擬成交價格和成交數量,
 *   買二或賣二揭示虛擬成交價位上的買剩餘量或賣剩餘量
 */
typedef struct _MdsStockSnapshotBody {
    /** 產品程式碼 C6 / C8 (如: '600000' 等) */
    char                SecurityID[MDS_MAX_INSTR_CODE_LEN];

    /**
     * 產品實時階段及標誌 C8 / C4
     *
     * 上交所股票 (C8):
     *  -# 第 1 位:
     *      - ‘S’表示啟動 (開市前) 時段，‘C’表示集合競價時段，‘T’表示連續交易時段
     *      - ‘B’表示休市時段，‘E’表示閉市時段，‘P’表示產品停牌
     *      - ‘M’表示可恢復交易的熔斷時段 (盤中集合競價)，‘N’表示不可恢復交易的熔斷時段 (暫停交易至閉市)
     *      - ‘D’表示開盤集合競價階段結束到連續競價階段開始之前的時段 (如有的話)
     *      - ‘U’表示收盤集合競價時段。
     *  -# 第 2 位:
     *      - ‘0’表示此產品不可正常交易 (在產品進入停牌、熔斷(暫停交易至閉市)狀態時值為‘0’)，
     *      - ‘1’表示此產品可正常交易 (在產品進入開盤集合競價、連續交易、收盤集合競價、熔斷(盤中集合競價)狀態時值為‘1’)，
     *      - 無意義填空格。
     *      - 閉市後保持該產品閉市前的是否可正常交易狀態。
     *  -# 第 3 位:
     *      - ‘0’表示未上市, ‘1’表示已上市。
     *  -# 第 4 位:
     *      - ‘0’表示此產品在當前時段不接受進行新訂單申報,
     *      - ‘1’表示此產品在當前時段可接受進行新訂單申報。
     *      - 無意義填空格。
     *      - 僅在交易時段有效，在非交易時段無效。
     *
     * 上交所期權 (C4):
     *  -# 第 1 位:
     *      - ‘S’表示啟動(開市前)時段, ‘C’表示集合競價時段, ‘T’表示連續交易時段,
     *      - ‘B’表示休市時段, ‘E’表示閉市時段, ‘V’表示波動性中斷, ‘P’ 表示臨時停牌, ‘U’收盤集合競價。
     *      - ‘M’表示可恢復交易的熔斷(盤中集合競價), ‘N’表示不可恢復交易的熔斷(暫停交易至閉市)
     *  -# 第 2 位:
     *      - ‘0’表示未連續停牌, ‘1’表示連續停牌。(預留,暫填空格)
     *  -# 第 3 位:
     *      - ‘0’表示不限制開倉, ‘1’表示限制備兌開倉, ‘2’表示賣出開倉, ‘3’表示限制賣出開倉、備兌開倉,
     *      - ‘4’表示限制買入開倉, ‘5’表示限制買入開 倉、備兌開倉,‘6’表示限制買入開倉、賣出開倉,
     *      - ‘7’表示限制買入開倉、賣出開倉、備兌開倉
     *  -# 第 4 位:
     *      - ‘0’表示此產品在當前時段不接受進行新訂單申報, ‘1’ 表示此產品在當前時段可接受進行新訂單申報。
     *
     * 深交所 (C8):
     *  -# 第 0 位:
     *      - S=啟動(開市前) O=開盤集合競價 T=連續競價
     *      - B=休市 C=收盤集合競價 E=已閉市 H=臨時停牌
     *      - A=盤後交易 V=波動性中斷
     *  -# 第 1 位:
     *      - 0=正常狀態
     *      - 1=全天停牌
     */
    char                TradingPhaseCode[MDS_MAX_TRADING_PHASE_CODE_LEN];
    char                __filler[6];            /**< 按64位對齊的填充域 */

    uint64              NumTrades;              /**< 成交筆數 */
    uint64              TotalVolumeTraded;      /**< 成交總量 */
    int64               TotalValueTraded;       /**< 成交總金額 (金額單位精確到元后四位, 即: 1元=10000) */

    int32               PrevClosePx;            /**< 昨日收盤價/期權合約昨日結算價 (價格單位精確到元后四位, 即: 1元=10000) */
    int32               OpenPx;                 /**< 今開盤價 (價格單位精確到元后四位, 即: 1元=10000) */
    int32               HighPx;                 /**< 最高價 */
    int32               LowPx;                  /**< 最低價 */
    int32               TradePx;                /**< 成交價 (最新價) */
    int32               ClosePx;                /**< 今收盤價/期權收盤價 (僅上海, 深圳行情沒有單獨的收盤價) */

    int32               IOPV;                   /**< 基金份額參考淨值/ETF申贖的單位參考淨值 (適用於基金) */
    int32               NAV;                    /**< 基金 T-1 日淨值 (適用於基金, 上證Level-2實時行情裡面沒有該欄位) */
    uint64              TotalLongPosition;      /**< 合約總持倉量 (適用於期權) */

    /** 五檔買盤價位資訊 */
    MdsPriceLevelEntryT BidLevels[5];

    /** 五檔賣盤價位資訊 */
    MdsPriceLevelEntryT OfferLevels[5];

} MdsStockSnapshotBodyT;


/* 結構體的初始化值定義 */
#define NULLOBJ_MDS_STOCK_SNAPSHOT_BODY                                 \
        {0}, {0}, {0}, \
        0, 0, 0, \
        0, 0, 0, 0, 0, 0, \
        0, 0, 0, \
        { \
            {NULLOBJ_MDS_PRICE_LEVEL_ENTRY}, \
            {NULLOBJ_MDS_PRICE_LEVEL_ENTRY}, \
            {NULLOBJ_MDS_PRICE_LEVEL_ENTRY}, \
            {NULLOBJ_MDS_PRICE_LEVEL_ENTRY}, \
            {NULLOBJ_MDS_PRICE_LEVEL_ENTRY} \
        }, \
        { \
            {NULLOBJ_MDS_PRICE_LEVEL_ENTRY}, \
            {NULLOBJ_MDS_PRICE_LEVEL_ENTRY}, \
            {NULLOBJ_MDS_PRICE_LEVEL_ENTRY}, \
            {NULLOBJ_MDS_PRICE_LEVEL_ENTRY}, \
            {NULLOBJ_MDS_PRICE_LEVEL_ENTRY} \
        }
/* -------------------------           */


/**
 * Level1 證券行情全幅訊息的完整訊息體定義
 */
typedef union _MdsL1SnapshotBody {
    MdsStockSnapshotBodyT           stock;      /**< 股票、債券、基金行情資料 */
    MdsStockSnapshotBodyT           option;     /**< 期權行情資料 */
    MdsIndexSnapshotBodyT           index;      /**< 指數行情資料 */
} MdsL1SnapshotBodyT;


/* 結構體的初始化值定義 */
#define NULLOBJ_MDS_L1_SNAPSHOT_BODY                                    \
        {NULLOBJ_MDS_STOCK_SNAPSHOT_BODY}
/* -------------------------           */


/**
 * 完整的 Level1 證券行情全幅訊息定義
 */
typedef struct _MdsL1Snapshot {
    MdsMktDataSnapshotHeadT         head;       /**< 行情資料的訊息頭 */

    union {
        MdsStockSnapshotBodyT       stock;      /**< 股票、債券、基金行情資料 */
        MdsStockSnapshotBodyT       option;     /**< 期權行情資料 */
        MdsIndexSnapshotBodyT       index;      /**< 指數行情資料 */
    };
} MdsL1SnapshotT;


/* 結構體的初始化值定義 */
#define NULLOBJ_MDS_L1_SNAPSHOT                                         \
        {NULLOBJ_MDS_MKT_DATA_SNAPSHOT_HEAD}, \
        {{NULLOBJ_MDS_STOCK_SNAPSHOT_BODY}}
/* -------------------------           */


/* ===================================================================
 * Level2 快照行情訊息定義
 * =================================================================== */

/**
 * Level2 快照行情定義
 * 股票(A、B股)、債券、基金
 *
 * 關於集合競價期間的虛擬集合競價行情 (上海L2、深圳L2):
 * - 集合競價期間的虛擬成交價通過買賣盤檔位揭示, 其中買一和賣一都揭示虛擬成交價格和成交數量,
 *   買二或賣二揭示虛擬成交價位上的買剩餘量或賣剩餘量
 */
typedef struct _MdsL2StockSnapshotBody {
    /** 產品程式碼 C6 / C8 (如: '600000' 等) */
    char                SecurityID[MDS_MAX_INSTR_CODE_LEN];

    /**
     * 產品實時階段及標誌 C8 / C4
     *
     * 上交所股票 (C8):
     *  -# 第 1 位:
     *      - ‘S’表示啟動 (開市前) 時段, ‘C’表示集合競價時段, ‘T’表示連續交易時段
     *      - ‘B’表示休市時段, ‘E’表示閉市時段, ‘P’表示產品停牌
     *      - ‘M’表示可恢復交易的熔斷時段 (盤中集合競價), ‘N’表示不可恢復交易的熔斷時段 (暫停交易至閉市)
     *      - ‘D’表示開盤集合競價階段結束到連續競價階段開始之前的時段 (如有) 。
     *  -# 第 2 位:
     *      - ‘0’表示此產品不可正常交易,
     *      - ‘1’表示此產品可正常交易,
     *      - 無意義填空格。
     *  -# 第 3 位:
     *      - ‘0’表示未上市, ‘1’表示已上市。
     *  -# 第 4 位:
     *      - ‘0’表示此產品在當前時段不接受進行新訂單申報,
     *      - ‘1’ 表示此產品在當前時段可接受進行新訂單申報。
     *      - 無意義填空格。
     *
     * 上交所期權 (C4):
     *  -# 第 1 位:
     *      - ‘S’表示啟動(開市前)時段, ‘C’表示集合競價時段, ‘T’表示連續交易時段,
     *      - ‘B’表示休市時段, ‘E’表示閉市時段, ‘V’表示波動性中斷, ‘P’ 表示臨時停牌, ‘U’收盤集合競價。
     *      - ‘M’表示可恢復 交易的熔斷(盤中集合競價), ‘N’表示不可恢復交易的熔斷(暫停交易至閉市)
     *  -# 第 2 位:
     *      - ‘0’表示未連續停牌, ‘1’表示連續停牌。(預留,暫填空格)
     *  -# 第 3 位:
     *      - ‘0’表示不限制開倉, ‘1’表示限制備兌開倉, ‘2’表示賣出開倉, ‘3’表示限制賣出開倉、備兌開倉,
     *      - ‘4’表示限制買入開倉, ‘5’表示限制買入開 倉、備兌開倉,‘6’表示限制買入開倉、賣出開倉,
     *      - ‘7’表示限制買入開倉、賣出開倉、備兌開倉
     *  -# 第 4 位:
     *      - ‘0’表示此產品在當前時段不接受進行新訂單申報, ‘1’ 表示此產品在當前時段可接受進行新訂單申報。
     *
     * 深交所 (C8):
     *  -# 第 0 位:
     *      - S=啟動(開市前) O=開盤集合競價 T=連續競價
     *      - B=休市 C=收盤集合競價 E=已閉市 H=臨時停牌
     *      - A=盤後交易 V=波動性中斷
     *  -# 第 1 位:
     *      - 0=正常狀態
     *      - 1=全天停牌
     */
    char                TradingPhaseCode[MDS_MAX_TRADING_PHASE_CODE_LEN];
    char                __filler[6];            /**< 按64位對齊的填充域 */

    uint64              NumTrades;              /**< 成交筆數 */
    uint64              TotalVolumeTraded;      /**< 成交總量 */
    int64               TotalValueTraded;       /**< 成交總金額 (金額單位精確到元后四位, 即: 1元=10000) */

    int32               PrevClosePx;            /**< 昨日收盤價/期權合約昨日結算價 (價格單位精確到元后四位, 即: 1元=10000) */
    int32               OpenPx;                 /**< 今開盤價 (價格單位精確到元后四位, 即: 1元=10000) */
    int32               HighPx;                 /**< 最高價 */
    int32               LowPx;                  /**< 最低價 */
    int32               TradePx;                /**< 成交價 */
    int32               ClosePx;                /**< 今收盤價/期權收盤價 (僅上海, 深圳行情沒有單獨的收盤價) */

    int32               IOPV;                   /**< 基金份額參考淨值/ETF申贖的單位參考淨值 (適用於基金) */
    int32               NAV;                    /**< 基金 T-1 日淨值 (適用於基金) */
    uint64              TotalLongPosition;      /**< 合約總持倉量 (適用於期權) */

    int64               TotalBidQty;            /**< 委託買入總量 */
    int64               TotalOfferQty;          /**< 委託賣出總量 */
    int32               WeightedAvgBidPx;       /**< 加權平均委買價格 */
    int32               WeightedAvgOfferPx;     /**< 加權平均委賣價格 */
    int32               BidPriceLevel;          /**< 買方委託價位數 (實際的委託價位總數, 僅上海) */
    int32               OfferPriceLevel;        /**< 賣方委託價位數 (實際的委託價位總數, 僅上海) */

    /** 十檔買盤價位資訊 */
    MdsPriceLevelEntryT BidLevels[10];

    /** 十檔賣盤價位資訊 */
    MdsPriceLevelEntryT OfferLevels[10];

} MdsL2StockSnapshotBodyT;


/* 結構體的初始化值定義 */
#define NULLOBJ_MDS_L2_STOCK_SNAPSHOT_BODY                              \
        {0}, {0}, {0}, \
        0, 0, 0, \
        0, 0, 0, 0, 0, 0, \
        0, 0, 0, \
        0, 0, 0, 0, 0, 0, \
        { \
            {NULLOBJ_MDS_PRICE_LEVEL_ENTRY}, \
            {NULLOBJ_MDS_PRICE_LEVEL_ENTRY}, \
            {NULLOBJ_MDS_PRICE_LEVEL_ENTRY}, \
            {NULLOBJ_MDS_PRICE_LEVEL_ENTRY}, \
            {NULLOBJ_MDS_PRICE_LEVEL_ENTRY}, \
            {NULLOBJ_MDS_PRICE_LEVEL_ENTRY}, \
            {NULLOBJ_MDS_PRICE_LEVEL_ENTRY}, \
            {NULLOBJ_MDS_PRICE_LEVEL_ENTRY}, \
            {NULLOBJ_MDS_PRICE_LEVEL_ENTRY}, \
            {NULLOBJ_MDS_PRICE_LEVEL_ENTRY} \
        }, \
        { \
            {NULLOBJ_MDS_PRICE_LEVEL_ENTRY}, \
            {NULLOBJ_MDS_PRICE_LEVEL_ENTRY}, \
            {NULLOBJ_MDS_PRICE_LEVEL_ENTRY}, \
            {NULLOBJ_MDS_PRICE_LEVEL_ENTRY}, \
            {NULLOBJ_MDS_PRICE_LEVEL_ENTRY}, \
            {NULLOBJ_MDS_PRICE_LEVEL_ENTRY}, \
            {NULLOBJ_MDS_PRICE_LEVEL_ENTRY}, \
            {NULLOBJ_MDS_PRICE_LEVEL_ENTRY}, \
            {NULLOBJ_MDS_PRICE_LEVEL_ENTRY}, \
            {NULLOBJ_MDS_PRICE_LEVEL_ENTRY} \
        }
/* -------------------------           */


/**
 * Level2 快照行情的增量更新訊息定義 (增量更新訊息僅適用於上海L2)
 * 股票(A、B股)、債券、基金
 *
 * 關於增量更新訊息補充說明如下：
 * -# 增量更新只有上交所Level2快照有，深交所行情裡面沒有
 *    - 上交所的L2快照的更新頻率為：每3秒傳送一次增量更新訊息（如果行情有變化的話），
 *      每60秒傳送一次全量快照（無論行情有無變化）。
 * -# 增量和全量快照的推送時點是一樣的，增量並不會比全量更快，只是資訊角度不一樣
 *    - 在對下游系統進行推送時，增量快照和完整快照在推送時間上是沒有區別的；
 *    - MDS會先對交易所發下來的增量更新訊息進行整合，然後根據訂閱條件向下遊推送完整快照或增量更新訊息。
 * -# 沒有特別需求的話，不需要訂閱增量更新訊息，增量訊息處理起來比較麻煩
 */
typedef struct _MdsL2StockSnapshotIncremental {
    uint64              NumTrades;              /**< 成交筆數 */
    uint64              TotalVolumeTraded;      /**< 成交總量 */
    int64               TotalValueTraded;       /**< 成交總金額 (金額單位精確到元后四位, 即: 1元=10000) */

    int32               OpenPx;                 /**< 今開盤價 (價格單位精確到元后四位, 即: 1元=10000) */
    int32               TradePx;                /**< 成交價 */
    int32               ClosePx;                /**< 今收盤價/期權收盤價 (僅上海, 深圳行情沒有單獨的收盤價) */
    int32               IOPV;                   /**< 基金份額參考淨值/ETF申贖的單位參考淨值 (適用於基金) */

    int64               TotalBidQty;            /**< 委託買入總量 */
    int64               TotalOfferQty;          /**< 委託賣出總量 */
    int32               WeightedAvgBidPx;       /**< 加權平均委買價格 */
    int32               WeightedAvgOfferPx;     /**< 加權平均委賣價格 */
    int32               BidPriceLevel;          /**< 買方委託價位數 (實際的委託價位總數, 僅上海) */
    int32               OfferPriceLevel;        /**< 賣方委託價位數 (實際的委託價位總數, 僅上海) */

    /** 最優申買價 */
    int32               BestBidPrice;
    /** 增量更新訊息中是否已經包含了最優申買價位 */
    uint8               HasContainedBestBidLevel;
    /** 買盤價位數量 (不包括已刪除且大於最優申買價的價位) */
    uint8               NoBidLevel;
    /** 買盤價位列表中是否有從佇列尾部刪除的價位 */
    uint8               __hasDeletedAtBidTail;
    /** 按64位對齊的填充域 */
    uint8               __filler1;

    /** 最優申賣價 */
    int32               BestOfferPrice;
    /** 增量更新訊息中是否已經包含了最優申買價位 */
    uint8               HasContainedBestOfferLevel;
    /** 賣盤價位數量 (不包括已刪除且小於最優申賣價的價位) */
    uint8               NoOfferLevel;
    /** 賣盤價位列表中是否有從佇列尾部刪除的價位 */
    uint8               __hasDeletedAtOfferTail;
    /** 按64位對齊的填充域 */
    uint8               __filler2;

    /**
     * (發生變更的價位列表中) 各個價位的運算操作
     * - 1 = Add
     * - 2 = Update
     * - 3 = Delete
     * @see eMdsL2PriceLevelOperatorT
     */
    uint8               PriceLevelOperator[MDS_MAX_L2_PRICE_LEVEL_INCREMENTS];

    /** 發生變更的價位列表 (該欄位為變長陣列, 實際元素數量為: NoBidLevel + NoOfferLevel) */
    MdsPriceLevelEntryT PriceLevels[MDS_MAX_L2_PRICE_LEVEL_INCREMENTS];

} MdsL2StockSnapshotIncrementalT;


/* 結構體的初始化值定義 */
#define NULLOBJ_MDS_L2_STOCK_SNAPSHOT_INCREMENTAL_BODY                  \
        0, 0, 0, \
        0, 0, 0, 0, \
        0, 0, 0, 0, 0, 0, \
        0, 0, 0, 0, 0, \
        0, 0, 0, 0, 0, \
        {0}, \
        { \
            {NULLOBJ_MDS_PRICE_LEVEL_ENTRY} \
        }
/* -------------------------           */


/**
 * Level2 委託佇列資訊 (買一／賣一前五十筆委託明細)
 */
typedef struct _MdsL2BestOrdersSnapshotBody {
    /** 產品程式碼 C6 / C8 (如: '600000' 等) */
    char                SecurityID[MDS_MAX_INSTR_CODE_LEN];
    uint8               __filler[5];            /**< 按64位對齊的填充域 */
    uint8               NoBidOrders;            /**< 買一價位的揭示委託筆數 */
    uint8               NoOfferOrders;          /**< 賣一價位的揭示委託筆數 */

    uint64              TotalVolumeTraded;      /**< 成交總量 (來自快照行情的冗餘欄位) */
    int32               BestBidPrice;           /**< 最優申買價 */
    int32               BestOfferPrice;         /**< 最優申賣價 */

    /** 買一價位的委託明細(前50筆) */
    int32               BidOrderQty[MDS_MAX_L2_DISCLOSE_ORDERS_CNT];

    /** 賣一價位的委託明細(前50筆) */
    int32               OfferOrderQty[MDS_MAX_L2_DISCLOSE_ORDERS_CNT];

} MdsL2BestOrdersSnapshotBodyT;


/* 結構體的初始化值定義 */
#define NULLOBJ_MDS_L2_BEST_ORDERS_SNAPSHOT_BODY                        \
        {0}, {0}, \
        0, 0, \
        0, 0, 0, \
        {0}, \
        {0}
/* -------------------------           */


/**
 * Level2 委託佇列的增量更新資訊 (買一／賣一前五十筆委託明細, 增量更新訊息僅適用於上海L2)
 */
typedef struct _MdsL2BestOrdersSnapshotIncremental {
    /** 成交總量 (來自快照行情的冗餘欄位) */
    uint64              TotalVolumeTraded;

    /** 最優申買價 */
    int32               BestBidPrice;
    /** 增量更新訊息中是否已經包含了最優申買價位 */
    uint8               HasContainedBestBidLevel;
    /** 當前最優申買價下被連續刪除掉的訂單筆數 */
    uint8               ContinualDeletedBidOrders;
    /** 買盤需要更新的筆數 (不包括被連續刪除掉的訂單) */
    uint8               NoBidOrders;
    /** 按64位對齊的填充域 */
    uint8               __filler1;

    /** 最優申賣價 */
    int32               BestOfferPrice;
    /** 增量更新訊息中是否已經包含了最優申買價位 */
    uint8               HasContainedBestOfferLevel;
    /** 當前最優申賣價下被連續刪除掉的訂單筆數 */
    uint8               ContinualDeletedOfferOrders;
    /** 賣盤需要更新的筆數 (不包括被連續刪除掉的訂單) */
    uint8               NoOfferOrders;
    /** 按64位對齊的填充域 */
    uint8               __filler2;

    /**
     * (發生變更的委託明細中) 待更新或刪除的訂單位置 (即需要刪除和更新的上一次訂單的位置)
     * - 訂單位置從 0 開始
     * - 小於0, 表示刪除該位置的訂單
     * - 大於等於0, 表示更新該位置的訂單
     * - CHAR_MAX, 表示新增
     */
    int8                OperatorEntryID[MDS_MAX_L2_DISCLOSE_ORDERS_INCREMENTS];

    /** 發生變更的委託明細 (該欄位為變長陣列, 實際元素數量為: NoBidOrders + NoOfferOrders) */
    int32               OrderQty[MDS_MAX_L2_DISCLOSE_ORDERS_INCREMENTS];

} MdsL2BestOrdersSnapshotIncrementalT;


/* 結構體的初始化值定義 */
#define NULLOBJ_MDS_L2_BEST_ORDERS_SNAPSHOT_INCREMENTAL                 \
        0, \
        0, 0, 0, 0, \
        0, 0, 0, 0, \
        {0}, \
        {0}
/* -------------------------           */


/**
 * Level2 市場總覽訊息定義
 */
typedef struct _MdsL2MarketOverview {
    int32               OrigDate;               /**< 市場日期 (YYYYMMDD) */
    int32               OrigTime;               /**< 市場時間 (HHMMSSss0, 實際精度為百分之一秒(HHMMSSss)) */

    int32               __exchSendingTime;      /**< 交易所傳送時間 (HHMMSS000, 實際精度為秒(HHMMSS)) */
    int32               __mdsRecvTime;          /**< MDS接收到時間 (HHMMSSsss) */
} MdsL2MarketOverviewT;


/* 結構體的初始化值定義 */
#define NULLOBJ_MDS_L2_MARKET_OVERVIEW                                  \
        0, 0, \
        0, 0
/* -------------------------           */


/**
 * Level2 快照行情的完整訊息體定義
 */
typedef union _MdsL2SnapshotBody {
    /** Level2 快照行情(股票、債券、基金、期權) */
    MdsL2StockSnapshotBodyT                 l2Stock;
    /** Level2 快照行情的增量更新訊息 */
    MdsL2StockSnapshotIncrementalT          l2StockIncremental;

    /** Level2 委託佇列(買一／賣一前五十筆委託明細) */
    MdsL2BestOrdersSnapshotBodyT            l2BestOrders;
    /** Level2 委託佇列(買一／賣一前五十筆委託明細)的增量更新訊息 */
    MdsL2BestOrdersSnapshotIncrementalT     l2BestOrdersIncremental;

    /** 指數行情資料 */
    MdsIndexSnapshotBodyT                   index;

    /** Level2 市場總覽 (僅上證) */
    MdsL2MarketOverviewT                    l2MarketOverview;
} MdsL2SnapshotBodyT;


/* 結構體的初始化值定義 */
#define NULLOBJ_MDS_L2_SNAPSHOT_BODY                                    \
        {NULLOBJ_MDS_L2_STOCK_SNAPSHOT_BODY}
/* -------------------------           */


/**
 * (對外發布的) 完整的 Level1/Level2 快照行情定義
 */
typedef struct _MdsMktDataSnapshot {
    /** 行情資料的訊息頭 */
    MdsMktDataSnapshotHeadT                 head;

    union {
        /** Level2 快照行情(股票、債券、基金) */
        MdsL2StockSnapshotBodyT             l2Stock;
        /** Level2 快照行情的增量更新訊息 */
        MdsL2StockSnapshotIncrementalT      l2StockIncremental;

        /** Level2 委託佇列(買一／賣一前五十筆委託明細) */
        MdsL2BestOrdersSnapshotBodyT        l2BestOrders;
        /** Level2 委託佇列(買一／賣一前五十筆委託明細)的增量更新訊息 */
        MdsL2BestOrdersSnapshotIncrementalT l2BestOrdersIncremental;

        /** Level1 股票、債券、基金行情資料 */
        MdsStockSnapshotBodyT               stock;

        /** Level1/Level2 期權行情資料 */
        MdsStockSnapshotBodyT               option;

        /** Level1/Level2 指數行情資料 */
        MdsIndexSnapshotBodyT               index;

        /** Level2 市場總覽 (僅上證) */
        MdsL2MarketOverviewT                l2MarketOverview;
    };
} MdsMktDataSnapshotT;


/* 結構體的初始化值定義 */
#define NULLOBJ_MDS_MKT_DATA_SNAPSHOT                                   \
        {NULLOBJ_MDS_MKT_DATA_SNAPSHOT_HEAD}, \
        {{NULLOBJ_MDS_L2_STOCK_SNAPSHOT_BODY}}


/* 結構體大小定義 */
#define DATASIZE_MDS_L2_STOCK_SNAPSHOT                                  \
        (sizeof(MdsMktDataSnapshotHeadT) + sizeof(MdsL2StockSnapshotBodyT))

#define DATASIZE_MDS_L2_BEST_ORDERS_SNAPSHOT                            \
        (sizeof(MdsMktDataSnapshotHeadT) + sizeof(MdsL2BestOrdersSnapshotBodyT))

#define DATASIZE_MDS_STOCK_SNAPSHOT                                     \
        (sizeof(MdsMktDataSnapshotHeadT) + sizeof(MdsStockSnapshotBodyT))

#define DATASIZE_MDS_OPTION_SNAPSHOT                                    \
        (sizeof(MdsMktDataSnapshotHeadT) + sizeof(MdsStockSnapshotBodyT))

#define DATASIZE_MDS_INDEX_SNAPSHOT                                     \
        (sizeof(MdsMktDataSnapshotHeadT) + sizeof(MdsIndexSnapshotBodyT))

#define DATASIZE_MDS_L2_MARKET_OVERVIEW                                 \
        (sizeof(MdsMktDataSnapshotHeadT) + sizeof(MdsL2MarketOverviewT))
/* -------------------------           */


/* ===================================================================
 * Level2 逐筆成交/逐筆委託行情訊息定義
 * =================================================================== */

/**
 * Level2 逐筆成交行情定義
 */
typedef struct _MdsL2Trade {
    uint8               exchId;                 /**< 交易所程式碼(滬/深) @see eMdsExchangeIdT */
    uint8               mdProductType;          /**< 行情類別 (股票/指數/期權) @see eMdsMdProductTypeT */
    int8                __isRepeated;           /**< 是否是重複的行情 (內部使用, 小於0表示資料倒流) */
    uint8               __filler1;              /**< 按64位對齊的填充域 */

    int32               tradeDate;              /**< 交易日期 (YYYYMMDD, 非官方資料) */
    int32               TransactTime;           /**< 成交時間 (HHMMSSsss) */

    int32               instrId;                /**< 產品程式碼 (轉換為整數型別的產品程式碼) */
    int32               ChannelNo;              /**< 成交通道/頻道程式碼 [0..9999] */
    int32               ApplSeqNum;             /**< 成交序號/訊息記錄號 (從1開始, 按頻道連續) */

    /** 產品程式碼 C6 / C8 (如: '600000' 等) */
    char                SecurityID[MDS_MAX_INSTR_CODE_LEN];

    /**
     * 成交類別 (僅適用於深交所, '4'=撤銷, 'F'=成交)
     * 對於上證, 將固定設定為 'F'(成交)
     * @see eMdsL2TradeExecTypeT
     */
    char                ExecType;

    /**
     * 內外盤標誌 (僅適用於上證, 'B'=外盤,主動買, 'S'=內盤,主動賣, 'N'=未知)
     * 對於深交所, 將固定設定為 'N'(未知)
     * @see eMdsL2TradeBSFlagT
     */
    char                TradeBSFlag;

    uint8               __filler3[4];           /**< 按64位對齊的填充域 */
    uint8               __channelNo;            /**< 內部頻道號 (供內部使用, 取值範圍{1,2,4,8}) */
    uint64              __origTickSeq;          /**< 對應的原始行情的序列號 (內部使用) */

    int32               TradePrice;             /**< 成交價格 (價格單位精確到元后四位, 即: 1元=10000) */
    int32               TradeQty;               /**< 成交數量 (上海債券的數量單位為: 手) */
    int64               TradeMoney;             /**< 成交金額 (金額單位精確到元后四位, 即: 1元=10000) */

    int64               BidApplSeqNum;          /**< 買方訂單號 (從 1 開始計數, 0 表示無對應委託) */
    int64               OfferApplSeqNum;        /**< 賣方訂單號 (從 1 開始計數, 0 表示無對應委託) */

#ifdef  _MDS_ENABLE_LATENCY_STATS
    /** 訊息原始接收時間 (從網路接收到資料的最初時間) */
    STimeval32T         __origNetTime;
    /** 訊息實際接收時間 (開始解碼等處理之前的時間) */
    STimeval32T         __recvTime;
    /** 訊息採集處理完成時間 */
    STimeval32T         __collectedTime;
    /** 訊息加工處理完成時間 */
    STimeval32T         __processedTime;
    /** 訊息推送時間 (寫入推送快取以後, 實際網路傳送之前) */
    STimeval32T         __pushingTime;
#endif

} MdsL2TradeT;


/* 結構體初始化值的尾部填充欄位定義 */
#ifdef  _MDS_ENABLE_LATENCY_STATS
# define    __NULLOBJ_MDS_L2_TRADE_TAILER                               \
            , {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}
#else
# define    __NULLOBJ_MDS_L2_TRADE_TAILER
#endif


/* 結構體的初始化值定義 */
#define NULLOBJ_MDS_L2_TRADE                                            \
        0, 0, 0, 0, \
        0, 0, \
        0, 0, 0, \
        {0}, 0, 0, \
        {0}, 0, 0, \
        0, 0, 0, \
        0, 0 \
        __NULLOBJ_MDS_L2_TRADE_TAILER
/* -------------------------           */


/**
 * Level2 逐筆委託行情定義 (僅適用於深交所)
 */
typedef struct _MdsL2Order {
    uint8               exchId;                 /**< 交易所程式碼(滬/深) @see eMdsExchangeIdT */
    uint8               mdProductType;          /**< 行情類別 (股票/指數/期權) @see eMdsMdProductTypeT */
    int8                __isRepeated;           /**< 是否是重複的行情 (內部使用, 小於0表示資料倒流) */
    uint8               __filler1;              /**< 按64位對齊的填充域 */

    int32               tradeDate;              /**< 交易日期 YYYYMMDD (自然日) */
    int32               TransactTime;           /**< 委託時間 HHMMSSsss */

    int32               instrId;                /**< 產品程式碼 (轉換為整數型別的產品程式碼) */
    int32               ChannelNo;              /**< 頻道程式碼 [0..9999] */
    int32               ApplSeqNum;             /**< 委託序號 (從1開始, 按頻道連續) */

    /** 產品程式碼 C6 / C8 (如: '000001' 等) */
    char                SecurityID[MDS_MAX_INSTR_CODE_LEN];

    /** 買賣方向 ('1'=買 '2'=賣 'G'=借入 'F'=出借) */
    char                Side;

    /** 訂單型別 ('1'=市價 '2'=限價 'U'=本方最優) */
    char                OrderType;

    uint8               __filler3[4];           /**< 按64位對齊的填充域 */
    uint8               __channelNo;            /**< 內部頻道號 (供內部使用, 取值範圍{1,2,4,8}) */
    uint64              __origTickSeq;          /**< 對應的原始行情的序列號 (內部使用) */

    int32               Price;                  /**< 委託價格 (價格單位精確到元后四位, 即: 1元=10000) */
    int32               OrderQty;               /**< 委託數量 */

#ifdef  _MDS_ENABLE_LATENCY_STATS
    /** 訊息原始接收時間 (從網路接收到資料的最初時間) */
    STimeval32T         __origNetTime;
    /** 訊息實際接收時間 (開始解碼等處理之前的時間) */
    STimeval32T         __recvTime;
    /** 訊息採集處理完成時間 */
    STimeval32T         __collectedTime;
    /** 訊息加工處理完成時間 */
    STimeval32T         __processedTime;
    /** 訊息推送時間 (寫入推送快取以後, 實際網路傳送之前) */
    STimeval32T         __pushingTime;
#endif

} MdsL2OrderT;


/* 結構體初始化值的尾部填充欄位定義 */
#ifdef  _MDS_ENABLE_LATENCY_STATS
# define    __NULLOBJ_MDS_L2_ORDER_TAILER                               \
            , {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}
#else
# define    __NULLOBJ_MDS_L2_ORDER_TAILER
#endif


/* 結構體的初始化值定義 */
#define NULLOBJ_MDS_L2_ORDER                                            \
        0, 0, 0, 0, \
        0, 0, \
        0, 0, 0, \
        {0}, 0, 0, \
        {0}, 0, 0, \
        0, 0 \
        __NULLOBJ_MDS_L2_ORDER_TAILER
/* -------------------------           */


/* ===================================================================
 * 彙總的行情資料定義
 * =================================================================== */

/**
 * 完整的行情資料訊息體定義
 */
typedef union _MdsWholeMktMsgBody {
    /** 快照行情 (Level1 快照 / Level2 快照 / 指數行情 / 期權行情) */
    MdsMktDataSnapshotT             mktDataSnapshot;

    /** Level2 逐筆成交行情 */
    MdsL2TradeT                     trade;
    /** Level2 逐筆委託行情 */
    MdsL2OrderT                     order;

    /** 市場狀態訊息 (僅適用於上交所) */
    MdsTradingSessionStatusMsgT     trdSessionStatus;
    /** 證券實時狀態訊息 (僅適用於深交所) */
    MdsSecurityStatusMsgT           securityStatus;
} MdsWholeMktMsgBodyT;


/* 結構體的初始化值定義 */
#define NULLOBJ_MDS_WHOLE_MKT_MSG_BODY          \
        {NULLOBJ_MDS_MKT_DATA_REQUEST_RSP}
/* -------------------------           */


/* ===================================================================
 * 產品資訊等靜態資料定義
 * =================================================================== */

/**
 * 證券資訊(股票/基金/債券)的靜態資料結構體定義
 */
typedef struct _MdsStockStaticInfo {
    /** 產品程式碼 C6 / C8 (如: '600000' 等) */
    char                securityId[MDS_MAX_INSTR_CODE_LEN];
    uint8               exchId;                 /**< 交易所程式碼 (滬/深) @see eMdsExchangeIdT */
    uint8               mdProductType;          /**< 行情類別 (股票/期權/指數) @see eMdsMdProductTypeT */
    uint8               oesSecurityType;        /**< 證券型別 (股票/債券/基金/...) @see eOesSecurityTypeT */
    uint8               subSecurityType;        /**< 證券子型別 @see eOesSubSecurityTypeT */
    uint8               __filler[7];            /**< 按64位對齊的填充域 */
    int32               instrId;                /**< 產品程式碼 (轉換為整數型別的產品程式碼) */

    int32               buyQtyUnit;             /**< 買入單位 */
    union {
        int32           lmtBuyMaxQty;           /**< 單筆限價買委託數量上限 */
        int32           buyOrdMaxQty;           /**< 單筆限價買委託數量上限 @deprecated 已廢棄, 為了相容舊版本而保留 */
    };
    union {
        int32           lmtBuyMinQty;           /**< 單筆限價買委託數量下限 */
        int32           buyOrdMinQty;           /**< 單筆限價買委託數量下限 @deprecated 已廢棄, 為了相容舊版本而保留 */
    };
    int32               mktBuyMaxQty;           /**< 單筆市價買委託數量上限 */
    int32               mktBuyMinQty;           /**< 單筆市價買委託數量下限 */

    int32               sellQtyUnit;            /**< 賣出單位 */
    union {
        int32           lmtSellMaxQty;          /**< 單筆限價賣委託數量上限 */
        int32           sellOrdMaxQty;          /**< 單筆限價賣委託數量上限 @deprecated 已廢棄, 為了相容舊版本而保留 */
    };
    union {
        int32           lmtSellMinQty;          /**< 單筆限價賣委託數量下限 */
        int32           sellOrdMinQty;          /**< 單筆限價賣委託數量下限 @deprecated 已廢棄, 為了相容舊版本而保留 */
    };
    int32               mktSellMaxQty;          /**< 單筆市價賣委託數量上限 */
    int32               mktSellMinQty;          /**< 單筆市價賣委託數量下限 */

    int32               prevClose;              /**< 昨日收盤價 (價格單位精確到元后四位, 即: 1元=10000) */
    int32               priceTick;              /**< 價格檔位 (價格單位精確到元后四位, 即: 1元=10000) */
    int32               limitUpPrice;           /**< 上漲限價 (價格單位精確到元后四位, 即: 1元=10000) */
    int32               limitDownPrice;         /**< 下跌限價 (價格單位精確到元后四位, 即: 1元=10000) */

    int64               parPrice;               /**< 面值 (價格單位精確到元后四位, 即: 1元=10000) */
    int64               bondInterest;           /**< 債券的每百元應計利息額 (單位精確到元后八位) */

    /** 產品名稱 (UTF-8 編碼) */
    char                securityName[MDS_MAX_SECURITY_NAME_LEN];
    char                __reserve[32];          /**< 預留的備用欄位 */
} MdsStockStaticInfoT;


/* 結構體的初始化值定義 */
#define NULLOBJ_MDS_STOCK_STATIC_INFO                                   \
        {0}, 0, 0, 0, 0, {0}, 0, \
        0, {0}, {0}, 0, 0, \
        0, {0}, {0}, 0, 0, \
        0, 0, 0, 0, \
        0, 0, \
        {0}, {0}
/* -------------------------           */


#ifdef __cplusplus
}
#endif

#endif  /* _MDS_BASE_MODEL_H */
