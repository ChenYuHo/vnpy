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
 * @file    mds_qry_packets.h
 *
 * 查詢訊息的報文定義
 *
 * @version 0.8.7 2016/07/30
 * @since   2016/02/10
 */


#ifndef _MDS_QRY_PACKETS_H
#define _MDS_QRY_PACKETS_H


#include    <mds_global/mds_base_model.h>
#include    <sutil/net/spk_global_packet.h>


#ifdef __cplusplus
extern "C" {
#endif


/* ===================================================================
 * 常量定義
 * =================================================================== */

/** 查詢應答報文中的最大證券靜態資訊數量 */
#define MDS_QRYRSP_MAX_STOCK_CNT                (200)
/* -------------------------           */


/* ===================================================================
 * 單條查詢的查詢訊息定義
 * =================================================================== */

/**
 * 證券行情查詢的請求報文
 */
typedef struct _MdsQryMktDataSnapshotReq {
    uint8               exchId;                 /**< 交易所程式碼 @see eMdsExchangeIdT */
    uint8               mdProductType;          /**< 行情類別 (股票/指數/期權) @see eMdsMdProductTypeT */
    uint8               __filler[2];            /**< 按64位對齊的填充域 */
    int32               instrId;                /**< 產品程式碼 */
} MdsQryMktDataSnapshotReqT;


/* 結構體的初始化值定義 */
#define NULLOBJ_MDS_QRY_MKT_DATA_SNAPSHOT_REQ   \
        0, 0, {0}, 0
/* -------------------------           */


/**
 * (深圳)證券實時狀態查詢的請求報文
 */
typedef MdsQryMktDataSnapshotReqT       MdsQrySecurityStatusReqT;


/* 結構體的初始化值定義 */
#define NULLOBJ_MDS_QRY_SECURITY_STATUS_REQ     \
        NULLOBJ_MDS_QRY_MKT_DATA_SNAPSHOT_REQ
/* -------------------------           */


/**
 * (上證)市場狀態查詢的請求報文
 */
typedef struct _MdsQryTrdSessionStatusReq {
    uint8               exchId;                 /**< 交易所程式碼 @see eMdsExchangeIdT */
    uint8               mdProductType;          /**< 行情類別 (股票/指數/期權) @see eMdsMdProductTypeT */
    uint8               __filler[6];            /**< 按64位對齊的填充域 */
} MdsQryTrdSessionStatusReqT;


/* 結構體的初始化值定義 */
#define NULLOBJ_MDS_QRY_TRD_SESSION_STATUS_REQ  \
        0, 0, {0}
/* -------------------------           */


/* ===================================================================
 * 批量查詢的查詢訊息頭定義
 * =================================================================== */

/**
 * 查詢請求的訊息頭定義
 */
typedef struct _MdsQryReqHeadT {
    int32               maxPageSize;            /**< 最大分頁大小 */
    int32               lastPosition;           /**< 查詢起始位置 */
} MdsQryReqHeadT;


/* 結構體的初始化值定義 */
#define NULLOBJ_MDS_QRY_REQ_HEAD                \
        0, 0
/* -------------------------           */


/**
 * 查詢應答的訊息頭定義
 */
typedef struct _MdsQryRspHeadT {
    int32               itemCount;              /**< 查詢到的資訊條目數 */
    int32               lastPosition;           /**< 查詢到的最後一條資訊的位置 */

    int8                isEnd;                  /**< 是否是當前查詢最後一個包 */
    uint8               __filler[7];            /**< 按64位對齊填充域 */

    /** 使用者私有資訊 (由客戶端自定義填充, 並在應答資料中原樣返回) */
    int64               userInfo;
} MdsQryRspHeadT;


/* 結構體的初始化值定義 */
#define NULLOBJ_MDS_QRY_RSP_HEAD                \
        0, 0, 0, {0}, 0
/* -------------------------           */


/**
 * 查詢定位的遊標結構
 */
typedef struct _MdsQryCursor {
    /** 查詢位置 */
    int32               seqNo;

    /** 是否是當前最後一個包 */
    int8                isEnd;
    /** 按64位對齊填充域 */
    int8                __filler[3];

    /** 使用者私有資訊 (由客戶端自定義填充, 並在應答資料中原樣返回) */
    int64               userInfo;
} MdsQryCursorT;


/* 結構體的初始化值定義 */
#define NULLOBJ_MDS_QRY_CURSOR                  \
        0, 0, {0}, 0
/* -------------------------           */


/**
 * 行情查詢請求中的證券程式碼資訊
 */
typedef struct _MdsQrySecurityCodeEntry {
    int32               instrId;                /**< 產品程式碼 */
    uint8               exchId;                 /**< 交易所程式碼 @see eMdsExchangeIdT */
    uint8               mdProductType;          /**< 行情類別 (股票/期權/指數) @see eMdsMdProductTypeT */
    uint8               __filler[2];            /**< 按64位對齊的填充域 */
} MdsQrySecurityCodeEntryT;


/* 結構體的初始化值定義 */
#define NULLOBJ_MDS_QRY_SECURITY_CODE_ENTRY     \
        0, 0, 0, {0}
/* -------------------------           */


/* ===================================================================
 * 證券靜態資訊查詢相關結構體定義
 * =================================================================== */

/**
 * 證券靜態資訊查詢的過濾條件定義
 */
typedef struct _MdsQryStockStaticInfoFilter {
    /** 產品程式碼 C6 / C8 (如: '600000' 等) */
    char                securityId[MDS_MAX_POSTFIXED_INSTR_CODE_LEN];
    uint8               exchId;                 /**< 交易所程式碼 @see eMdsExchangeIdT */
    uint8               oesSecurityType;        /**< 證券型別 (股票/債券/基金/...) @see eOesSecurityTypeT */
    uint8               subSecurityType;        /**< 證券子型別 @see eOesSubSecurityTypeT */
    uint8               __filler[5];            /**< 按64位對齊的填充域 */
    int32               instrId;                /**< 產品程式碼 (轉換為整數型別的產品程式碼)
                                                     如果同時指定 securityId, 則優先使用 securityId */

    /** 使用者私有資訊 (由客戶端自定義填充, 並在應答資料中原樣返回) */
    int64               userInfo;
} MdsQryStockStaticInfoFilterT;


/**
 * 證券靜態資訊查詢的請求報文
 */
typedef struct _MdsQryStockStaticInfoReq {
    /** 查詢請求的訊息頭 */
    MdsQryReqHeadT      reqHead;
    /** 查詢請求的過濾條件 */
    MdsQryStockStaticInfoFilterT
                        qryFilter;
} MdsQryStockStaticInfoReqT;


/**
 * 證券靜態資訊查詢的應答報文
 */
typedef struct _MdsQryStockStaticInfoRsp {
    /** 查詢應答的訊息頭 */
    MdsQryRspHeadT      rspHead;
    /** 證券靜態資訊陣列 (最大大小為 MDS_QRYRSP_MAX_STOCK_CNT) */
    MdsStockStaticInfoT qryItems[1];
} MdsQryStockStaticInfoRspT;


/* 結構體的初始化值定義 */
#define NULLOBJ_MDS_QRY_STOCK_STATIC_INFO_FILTER        \
        {0}, 0, 0, 0, {0}, 0, \
        0

/* 結構體的初始化值定義 */
#define NULLOBJ_MDS_QRY_STOCK_STATIC_INFO_REQ           \
        {NULLOBJ_MDS_QRY_REQ_HEAD}, \
        {NULLOBJ_MDS_QRY_STOCK_STATIC_INFO_FILTER}

/* 結構體的初始化值定義 */
#define NULLOBJ_MDS_QRY_STOCK_STATIC_INFO_RSP           \
        {NULLOBJ_MDS_QRY_RSP_HEAD}, \
        {{NULLOBJ_MDS_STOCK_STATIC_INFO}}
/* -------------------------           */


/* ===================================================================
 * 快照資訊查詢相關結構體定義
 * =================================================================== */

/**
 * 行情快照資訊查詢的過濾條件定義
 */
typedef struct _MdsQrySnapshotListFilter {
    uint8               exchId;                 /**< 交易所程式碼 @see eMdsExchangeIdT */
    uint8               mdProductType;          /**< 行情類別 (股票/期權/指數) @see eMdsMdProductTypeT */
    uint8               oesSecurityType;        /**< 證券型別 (股票/債券/基金/...) @see eOesSecurityTypeT */
    uint8               subSecurityType;        /**< 證券子型別 @see eOesSubSecurityTypeT */
    uint8               mdLevel;                /**< 行情資料級別 (Level1 / Level2) @see eMdsMdLevelT */
    uint8               __filler[11];           /**< 按64位對齊的填充域 */

    /** 使用者私有資訊 (由客戶端自定義填充, 並在應答資料中原樣返回) */
    int64               userInfo;
} MdsQrySnapshotListFilterT;


/**
 * 行情快照資訊查詢的請求報文
 */
typedef struct _MdsQrySnapshotListReq {
    /** 查詢請求的訊息頭 */
    MdsQryReqHeadT      reqHead;
    /** 查詢請求的過濾條件 */
    MdsQrySnapshotListFilterT
                        qryFilter;

    /** 待查詢的證券程式碼數量 */
    int32               securityCodeCnt;
    /**< 按64位對齊的填充域 */
    int32               __filler;
    /** 待查詢的證券程式碼列表 (最大大小為 MDS_QRYRSP_MAX_STOCK_CNT) */
    MdsQrySecurityCodeEntryT
                        securityCodeList[1];
} MdsQrySnapshotListReqT;


/**
 * 行情快照資訊查詢的應答報文
 */
typedef struct _MdsQrySnapshotListRsp {
    /** 查詢應答的訊息頭 */
    MdsQryRspHeadT      rspHead;
    /** 五檔快照資訊陣列 (最大大小為 MDS_QRYRSP_MAX_STOCK_CNT) */
    MdsL1SnapshotT      qryItems[1];
} MdsQrySnapshotListRspT;


/* 結構體的初始化值定義 */
#define NULLOBJ_MDS_QRY_SNAPSHOT_LIST_FILTER            \
        0, 0, 0, 0, 0, {0}, \
        0

/* 結構體的初始化值定義 */
#define NULLOBJ_MDS_QRY_SNAPSHOT_LIST_REQ               \
        {NULLOBJ_MDS_QRY_REQ_HEAD}, \
        {NULLOBJ_MDS_QRY_SNAPSHOT_LIST_FILTER}, \
        0, 0, \
        {{NULLOBJ_MDS_QRY_SECURITY_CODE_ENTRY}}

/* 結構體的初始化值定義 */
#define NULLOBJ_MDS_QRY_SNAPSHOT_LIST_RSP               \
        {NULLOBJ_MDS_QRY_RSP_HEAD}, \
        {{NULLOBJ_MDS_L1_SNAPSHOT}}
/* -------------------------           */


#ifdef __cplusplus
}
#endif

#endif  /* _MDS_QRY_PACKETS_H */
