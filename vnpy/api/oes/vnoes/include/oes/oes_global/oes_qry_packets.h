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
 * @file    oes_qry_packets.h
 *
 * 查詢訊息的報文定義
 *
 * @version 0.11.1      2016/11/17
 * @version 0.12        2016/11/30
 *          - 增加客戶資訊查詢功能
 *          - ETF成分股查詢應答中增加成分股所屬ETF申贖程式碼
 *          - 佣金查詢應答中增加客戶程式碼
 *          - 在登入報文中增加協議版本號資訊, 並在登入時校驗協議版本號的相容性
 * @version 0.12.1      2016/12/19
 *          - 整合查詢訊息中的qryCnt、position等欄位, 成為一個新的結構體 OesQryHeadT
 * @version 0.12.3      2017/01/10
 *          - OesHoldItemT 結構體拆分成 OesStkHoldingItemT、OesOptHoldingItemT兩個結構體
 *          - 持倉查詢相關結構體拆分成股票持倉查詢、期權持倉查詢專用的結構體
 * @version 0.12.3.5    2017/02/20
 *          - 佣金查詢過濾條件中新增一條“證券子型別”的過濾條件
 * @version 0.12.6.2    2017/03/16
 *          - '查詢出入金流水資訊過濾條件' 中重新命名 cashSeqNo => clSeqNo
 *          - 調整查詢到的 '出入金流水資訊' 結構 (與出入金委託執行回報結構一致)
 *          - 調整佣金查詢結果中feeRate欄位的精度, 當佣金計算模式為 '按金額' 時,
 *            feeRate 欄位所代表的比率單位由 '十萬分之一' => '百萬分之一'
 * @version 0.12.8.2    2017/05/09
 *          - 客戶資金資訊(OesCashAssetItemT)中新增欄位 '當前衝正金額(紅衝藍補的資金淨額, reversalAmt)'
 * @version 0.12.8.2    2017/05/16
 *          - 新增 '證券發行資訊查詢' 相關報文定義
 *              - 新增欄位 查詢證券發行資訊過濾條件(OesQryIssueFilterT)
 *              - 新增欄位 證券發行資訊內容(OesIssueItemT)
 *              - 新增欄位 查詢證券發行資訊請求(OesQryIssueReqT)
 *              - 新增欄位 查詢證券發行資訊應答(OesQryIssueRspT)
 * @version 0.12.9_RC1  2017/06/05
 *          - 調整佣金查詢結果中feeRate欄位的精度, 當佣金計算模式為 '按份數' 時,
 *              feeRate 欄位所代表的比率單位由 '萬分之一' => '百萬分之一'
 * @version 0.15.1      2017/06/26
 *          - '委託查詢的過濾條件(OesQryOrdFilterT)' 中
 *              - 新增欄位 委託的起始時間(startTime) 和 委託的結束時間(endTime)
 *          - '成交查詢的過濾條件(OesQryTrdFilterT)' 中
 *              - 新增欄位 成交的起始時間(startTime) 和 成交的結束時間(endTime)
 *          - '持倉查詢的返回資訊(OesStkHoldingItemT)' 中新增欄位 總持倉(sumHld)
 *          - '資金查詢的返回資訊(OesCashAssetItemT)' 中
 *              - 新增欄位 當前餘額(currentBal)
 *              - 欄位重新命名 當前可用餘額(tradeAvlAmt => currentAvailableBal)
 *              - 欄位重新命名 當前可取餘額(withdrawAvlAmt => currentDrawableBal)
 * @version 0.15.2      2017/07/18
 *          - 新增 '新股認購、中籤資訊查詢' 相關報文定義
 *              - 新增欄位 查詢新股認購、中籤資訊過濾條件(OesQryLotWinningFilterT)
 *              - 新增欄位 新股認購、中籤資訊內容(OesLotWinningItemT)
 *              - 新增欄位 查詢新股認購、中籤資訊請求(OesQryLotWinningReqT)
 *              - 新增欄位 查詢新股認購、中籤資訊應答(OesQryLotWinningRspT)
 * @version 0.15.4      2017/09/04
 *          - 查詢請求中訊息頭的型別由 'OesQryHeadT' 改為 'OesQryReqHeadT'
 *          - 查詢應答中訊息頭的型別由 'OesQryHeadT' 改為 'OesQryRspHeadT'
 *          - 刪除 'OesQryHeadT' 型別定義
 *          - '委託資訊查詢結果 (OesOrdItemT)' 中增加欄位:
 *              - 客戶端編號 (clientId)
 *              - 客戶端環境號 (clEnvId)
 *              - 原始訂單的客戶委託流水號 (origClSeqNo)
 *              - 原始訂單的客戶端環境號 (origClEnvId)
 *              - 交易所訂單編號 (exchOrdId)
 *          - '成交資訊查詢結果 (OesTrdItemT)' 中增加欄位:
 *              - 客戶端編號 (clientId)
 *              - 客戶端環境號 (clEnvId)
 *          - '股票持倉資訊 (OesStkHoldingItemT)' 中增加欄位:
 *              - 持倉成本 (costAmount)
 *              - 持倉成本價 (costPrice)
 *          - 整理以下結構體定義, 調整了欄位順序, 並刪除了個別欄位
 *              - 現貨產品資訊查詢結果 (OesStockItemT)
 *              - 期權產品資訊查詢結果 (OesOptionItemT)
 *              - 證券賬戶資訊查詢結果 (OesInvAcctItemT)
 *          - 所有的查詢過濾條件(OesQryXXXFilterT) 中增加 userInfo欄位,
 *              此欄位會在對應的查詢應答訊息(OesQryXXXRspT) 的應答頭中原樣帶回
 * @version 0.15.5      2017/11/03
 *          - 調整查詢應答報文中攜帶查詢資料的最大條目數量
 *          - 調整 '查詢請求訊息頭(OesQryReqHeadT)' 中部分欄位：
 *              - '查詢視窗大小'欄位重新命名 pageSize => maxPageSize
 *              - '查詢起始位置'欄位重新命名 position => lastPosition
 *          - 調整 '查詢應答訊息頭(OesQryRspHeadT)' 中部分欄位：
 *              - '查詢到的資訊條目數'欄位重新命名 itemCnt => itemCount
 *              - '查詢到的最後一條資訊的位置'欄位重新命名 position => lastPosition
 *          - 調整 '查詢應答訊息頭(OesQryRspHeadT)' 中部分欄位：
 *              - '查詢到的資訊條目數'欄位重新命名 itemCnt => itemCount
 *              - '查詢到的最後一條資訊的位置'欄位重新命名 position => lastPosition
 *          - '股票持倉資訊 (OesStkHoldingItemT)' 結構體中增加欄位:
 *              - 證券型別 (securityType)
 *              - 證券子型別 (subSecurityType)
 *          - 調整 '資金資訊(OesCashAssetItemT)' 中部分欄位:
 *              - '當前餘額'欄位重新命名 currentBal => currentTotalBal
 * @version 0.15.5.2    2018/01/29
 *          - 修正 '佣金查詢結果 (OesCommissionRateItemT)' 中 feeRate 欄位精度描述不正確的問題
 * @version 0.15.5.6    2018/04/01
 *          - 新增 '市場狀態資訊查詢' 相關報文定義
 *              - 新增欄位 查詢市場狀態資訊過濾條件(OesQryMarketStateFilterT)
 *              - 新增欄位 市場狀態資訊內容(OesMarketStateItemT)
 *              - 新增欄位 查詢市場狀態資訊請求(OesQryMarketStateReqT)
 *              - 新增欄位 查詢市場狀態資訊應答(OesQryMarketStateRspT)
 * @version 0.15.5.14   2018/08/01
 *          - '現貨產品資訊查詢過濾條件(OesQryStockFilterT)' 中新增欄位:
 *              - 證券類別(securityType)
 *              - 證券子類別(subSecurityType)
 * @version 0.15.5.16   2018/08/31
 *          - 新增 '查詢客戶端總覽資訊' 相關報文定義
 *              - 新增 股東賬戶總覽資訊(OesInvAcctOverviewT)
 *              - 新增 資金賬戶總覽資訊(OesCashAcctOverviewT)
 *              - 新增 客戶總覽資訊(OesCustOverviewT)
 *              - 新增 客戶端總覽資訊(OesClientOverviewT)
 *              - 新增 主櫃資金資訊(OesCounterCashItemT)
 *          - 新增 '查詢主櫃資金資訊' 相關報文定義
 *              - 新增 查詢主櫃資金資訊請求(OesQryCounterCashReqT)
 *              - 新增 查詢主櫃資金資訊應答(OesQryCounterCashRspT)
 *              - 新增 主櫃資金資訊內容(OesCounterCashItemT)
 *          - '客戶資金資訊內容(OesCashAssetItemT)' 中新增 是否禁止出入金(isFundTrsfDisabled) 欄位
 *          - '證券賬戶資訊內容(OesInvAcctItemT)' 中新增 是否禁止交易(isTradeDisabled) 欄位
 * @version 0.15.5.16_u3 2018/09/28
 *          - 調整成交資訊(OesTrdItemT)的結構體欄位
 *              - 調整 v0.15.5.16 版本新增的 '證券子類別(subSecurityType)' 欄位的位置
 *              - 增加 '原始委託數量(origOrdQty)' 和 '原始委託價格(origOrdPrice)' 欄位
 * @version 0.15.6.14   2018/08/01
 *          - '委託查詢的過濾條件(OesQryOrdFilterT)' 中
 *              - 新增欄位 證券類別(securityType) 和 買賣型別(bsType)
 *          - '成交查詢的過濾條件(OesQryTrdFilterT)' 中
 *              - 新增欄位 證券類別(securityType) 和 買賣型別(bsType)
 *          - '股票持倉查詢的過濾條件(OesQryStkHoldingFilterT)' 中
 *              - 新增欄位 證券類別(securityType)
 * @version 0.15.7.6   2018/11/03
 *          - '證券發行資訊查詢的過濾條件(OesQryIssueFilterT)' 中
 *              - 新增欄位 '產品型別 (productType)'
 *          - '查詢股票持倉資訊過濾條件(OesQryStkHoldingFilterT)' 中
 *              - 新增欄位 '產品型別 (productType)'
 * @version 0.15.9      2019/03/12
 *          - 為了支援科創板, 擴充套件以下查詢結果 (相容之前版本的API)
 *              - 證券賬戶資訊 (OesInvAcctItemT) 中增加如下欄位:
 *                  - 科創板權益 (kcSubscriptionQuota)
 *              - 現貨產品資訊 (OesStockItemT) 中增加如下欄位:
 *                  - 限價買數量上限 (lmtBuyMaxQty)
 *                  - 限價買數量下限 (lmtBuyMinQty)
 *                  - 限價賣數量上限 (lmtSellMaxQty)
 *                  - 限價賣數量下限 (lmtSellMinQty)
 *                  - 市價買數量上限 (mktBuyMaxQty)
 *                  - 市價買數量下限 (mktBuyMinQty)
 *                  - 市價賣數量上限 (mktSellMaxQty)
 *                  - 市價賣數量下限 (mktSellMinQty)
 *              - 客戶端總覽資訊中的股東賬戶總覽 (OesInvAcctOverviewT) 中增加如下欄位:
 *                  - 科創板權益 (kcSubscriptionQuota)
 *
 * @since   2015/07/30
 */


#ifndef _OES_QRY_PACKETS_H
#define _OES_QRY_PACKETS_H


#include    <oes_global/oes_base_model.h>
#include    <sutil/net/spk_global_packet.h>


#ifdef __cplusplus
extern "C" {
#endif


/* ===================================================================
 * 常量定義
 * =================================================================== */

/** 每條查詢應答報文中委託資訊的最大數量 */
#define OES_MAX_ORD_ITEM_CNT_PER_PACK               (30)

/** 每條查詢應答報文中成交資訊的最大數量 */
#define OES_MAX_TRD_ITEM_CNT_PER_PACK               (30)

/** 每條查詢應答報文中客戶資金資訊的最大數量 */
#define OES_MAX_CASH_ASSET_ITEM_CNT_PER_PACK        (30)

/** 每條查詢應答報文中持倉資訊的最大數量 */
#define OES_MAX_HOLDING_ITEM_CNT_PER_PACK           (30)

/** 每條查詢應答報文中客戶資訊的最大數量 */
#define OES_MAX_CUST_ITEM_CNT_PER_PACK              (30)

/** 每條查詢應答報文中證券賬戶資訊的最大數量 */
#define OES_MAX_INV_ACCT_ITEM_CNT_PER_PACK          (30)

/** 每條查詢應答報文中客戶佣金資訊的最大數量 */
#define OES_MAX_COMMS_RATE_ITEM_CNT_PER_PACK        (50)

/** 每條查詢應答報文中出入金流水記錄的最大數量 */
#define OES_MAX_FUND_TRSF_ITEM_CNT_PER_PACK         (30)

/** 每條查詢應答報文中新股認購、中籤資訊的最大數量 */
#define OES_MAX_LOG_WINNING_ITEM_CNT_PER_PACK       (30)

/** 每條查詢應答報文中證券發行資訊的最大數量 */
#define OES_MAX_ISSUE_ITEM_CNT_PER_PACK             (30)

/** 每條查詢應答報文中現貨產品資訊的最大數量 */
#define OES_MAX_STOCK_ITEM_CNT_PER_PACK             (30)

/** 每條查詢應答報文中ETF申贖產品資訊的最大數量 */
#define OES_MAX_ETF_ITEM_CNT_PER_PACK               (30)

/** 每條查詢應答報文中ETF成分股的最大數量 */
#define OES_MAX_ETF_COMPONENT_ITEM_CNT_PER_PACK     (30)

/** 每條查詢應答報文中期權產品的最大數量 */
#define OES_MAX_OPTION_ITEM_CNT_PER_PACK            (30)

/** 每條查詢應答報文中市場狀態的最大數量 */
#define OES_MAX_MKT_STATE_ITEM_CNT_PER_PACK         (30)

/** 客戶端對應的最大客戶數量 */
#define OES_MAX_CUST_PER_CLIENT                     (1)
/* -------------------------           */


/* ===================================================================
 * 查詢訊息頭相關結構體定義
 * =================================================================== */

/**
 * 查詢定位的遊標結構
 */
typedef struct _OesQryCursor {
    /** 查詢位置 */
    int32               seqNo;

    /** 是否是當前最後一個包 */
    int8                isEnd;
    /** 按64位對齊填充域 */
    int8                __filler[3];

    /** 使用者私有資訊 (由客戶端自定義填充, 並在應答資料中原樣返回) */
    int64               userInfo;
} OesQryCursorT;


/* 結構體的初始化值定義 */
#define NULLOBJ_OES_QRY_CURSOR                      \
        0, 0, {0}, 0
/* -------------------------           */


/**
 * 查詢請求的訊息頭定義
 */
typedef struct _OesQryReqHead {
    /** 查詢視窗大小 */
    int32               maxPageSize;
    /** 查詢起始位置 */
    int32               lastPosition;
} OesQryReqHeadT;


/* 結構體的初始化值定義 */
#define NULLOBJ_OES_QRY_REQ_HEAD                    \
        0, 0
/* -------------------------           */


/**
 * 查詢應答的訊息頭定義
 */
typedef struct _OesQryRspHead {
    /** 查詢到的資訊條目數 */
    int32               itemCount;
    /** 查詢到的最後一條資訊的位置 */
    int32               lastPosition;

    /** 是否是當前查詢最後一個包 */
    int8                isEnd;
    /** 按64位對齊填充域 */
    uint8               __filler[7];

    /** 使用者私有資訊 (由客戶端自定義填充, 並在應答資料中原樣返回) */
    int64               userInfo;
} OesQryRspHeadT;


/* 結構體的初始化值定義 */
#define NULLOBJ_OES_QRY_RSP_HEAD                    \
        0, 0, 0, {0}, 0
/* -------------------------           */


/* ===================================================================
 * 查詢委託資訊相關結構體定義
 * =================================================================== */

/**
 * 查詢委託資訊過濾條件
 */
typedef struct _OesQryOrdFilter {
    /** 客戶程式碼, 可選項 */
    char                custId[OES_CUST_ID_MAX_LEN];
    /** 證券賬戶程式碼, 可選項 */
    char                invAcctId[OES_INV_ACCT_ID_MAX_LEN];

    /**
     * 市場程式碼, 可選項。如無需此過濾條件請使用 OES_MKT_ID_UNDEFINE
     * @see eOesMarketIdT
     */
    uint8               mktId;
    /** 是否僅查詢未關閉委託 (包括未全部成交或撤銷的委託) */
    uint8               isUnclosedOnly;
    /** 客戶端環境號 */
    int8                clEnvId;
    /** 證券類別  @see eOesSecurityTypeT */
    uint8               securityType;
    /** 買賣型別  @see eOesBuySellTypeT */
    uint8               bsType;
    /** 按64位對齊填充域 */
    uint8               __filler[3];

    /** 客戶委託編號, 可選項 */
    int64               clOrdId;
    /** 客戶委託流水號, 可選項 */
    int64               clSeqNo;

    /** 查詢委託的起始時間 (格式為 HHMMSSsss, 比如 141205000 表示 14:12:05.000) */
    int32               startTime;
    /** 查詢委託的結束時間 (格式為 HHMMSSsss, 比如 141205000 表示 14:12:05.000) */
    int32               endTime;

    /** 使用者私有資訊 (由客戶端自定義填充, 並在應答資料中原樣返回) */
    int64               userInfo;
} OesQryOrdFilterT;


/* 結構體的初始化值定義 */
#define NULLOBJ_OES_QRY_ORD_FILTER                  \
        {0}, {0}, \
        0, 0, 0, 0, 0, {0}, \
        0, 0, \
        0, 0, 0
/* -------------------------           */


/**
 * 查詢到的委託資訊內容
 */
typedef OesOrdCnfmT     OesOrdItemT;


/* 結構體的初始化值定義 */
#define NULLOBJ_OES_ORD_ITEM                        \
        NULLOBJ_OES_ORD_CNFM
/* -------------------------           */


/**
 * 查詢委託資訊請求
 */
typedef struct _OesQryOrdReq {
    /** 查詢請求訊息頭 */
    OesQryReqHeadT      reqHead;
    /** 查詢過濾條件 */
    OesQryOrdFilterT    qryFilter;
} OesQryOrdReqT;


/* 結構體的初始化值定義 */
#define NULLOBJ_OES_QRY_ORD_REQ                     \
        {NULLOBJ_OES_QRY_REQ_HEAD}, \
        {NULLOBJ_OES_QRY_ORD_FILTER}
/* -------------------------           */


/**
 * 查詢委託資訊應答
 */
typedef struct _OesQryOrdRsp {
    /** 查詢應答訊息頭 */
    OesQryRspHeadT      rspHead;
    /** 委託資訊陣列 */
    OesOrdItemT         qryItems[OES_MAX_ORD_ITEM_CNT_PER_PACK];
} OesQryOrdRspT;


/* 結構體的初始化值定義 */
#define NULLOBJ_OES_QRY_ORD_RSP                     \
        {NULLOBJ_OES_QRY_RSP_HEAD}, \
        {{NULLOBJ_OES_ORD_ITEM}}
/* -------------------------           */


/* ===================================================================
 * 查詢成交資訊相關結構體定義
 * =================================================================== */

/**
 * 查詢成交資訊過濾條件
 */
typedef struct _OesQryTrdFilter {
    /** 客戶程式碼, 可選項 */
    char                custId[OES_CUST_ID_MAX_LEN];
    /** 證券賬戶程式碼, 可選項 */
    char                invAcctId[OES_INV_ACCT_ID_MAX_LEN];

    /**
     * 市場程式碼, 可選項。如無需此過濾條件請使用 OES_MKT_ID_UNDEFINE
     * @see eOesMarketIdT
     */
    uint8               mktId;
    /** 客戶端環境號 */
    int8                clEnvId;
    /** 證券類別  @see eOesSecurityTypeT */
    uint8               securityType;
    /** 買賣型別  @see eOesBuySellTypeT */
    uint8               bsType;
    /** 按64位對齊填充域 */
    uint32              __filler;

    /** 內部委託編號, 可選項 */
    int64               clOrdId;
    /** 客戶委託流水號, 可選項 */
    int64               clSeqNo;

    /** 成交開始時間 (格式為 HHMMSSsss, 形如 141205000) */
    int32               startTime;
    /** 成交結束時間 */
    int32               endTime;

    /** 使用者私有資訊 (由客戶端自定義填充, 並在應答資料中原樣返回) */
    int64               userInfo;
} OesQryTrdFilterT;


/* 結構體的初始化值定義 */
#define NULLOBJ_OES_QRY_TRD_FILTER                  \
        {0}, {0}, \
        0, 0, 0, 0, 0, \
        0, 0, \
        0, 0, 0
/* -------------------------           */


/**
 * 查詢到的成交資訊內容
 */
typedef OesTrdCnfmT     OesTrdItemT;


/* 結構體的初始化值定義 */
#define NULLOBJ_OES_TRD_ITEM                        \
        NULLOBJ_OES_TRD_CNFM
/* -------------------------           */


/**
 * 查詢成交資訊請求
 */
typedef struct _OesQryTrdReq {
    /** 查詢請求訊息頭 */
    OesQryReqHeadT      reqHead;
    /** 查詢過濾條件 */
    OesQryTrdFilterT    qryFilter;
} OesQryTrdReqT;


/* 結構體的初始化值定義 */
#define NULLOBJ_OES_QRY_TRD_REQ                     \
        {NULLOBJ_OES_QRY_REQ_HEAD}, \
        {NULLOBJ_OES_QRY_TRD_FILTER}


/**
 * 查詢成交資訊應答
 */
typedef struct _OesQryTrdRsp {
    /** 查詢應答訊息頭 */
    OesQryRspHeadT      rspHead;
    /** 成交資訊陣列 */
    OesTrdItemT         qryItems[OES_MAX_TRD_ITEM_CNT_PER_PACK];
} OesQryTrdRspT;


/* 結構體的初始化值定義 */
#define NULLOBJ_OES_QRY_TRD_RSP                     \
        {NULLOBJ_OES_QRY_RSP_HEAD}, \
        {{NULLOBJ_OES_TRD_ITEM}}
/* -------------------------           */


/* ===================================================================
 * 查詢客戶資金資訊相關結構體定義
 * =================================================================== */

/**
 * 查詢客戶資金資訊過濾條件
 */
typedef struct _OesQryCashAssetFilter {
    /** 客戶程式碼, 可選項 */
    char                custId[OES_CUST_ID_MAX_LEN];
    /** 資金賬戶程式碼, 可選項 */
    char                cashAcctId[OES_CASH_ACCT_ID_MAX_LEN];

    /** 使用者私有資訊 (由客戶端自定義填充, 並在應答資料中原樣返回) */
    int64               userInfo;
} OesQryCashAssetFilterT;


/* 結構體的初始化值定義 */
#define NULLOBJ_OES_QRY_CASH_ASSET_FILTER           \
        {0}, {0}, 0
/* -------------------------           */


/**
 * 客戶資金資訊內容
 */
typedef struct _OesCashAssetItem {
    __OES_CASH_ASSET_BASE_INFO_PKT;

    /**
     * 當前餘額, 包括當前可用餘額和在途凍結資金在內的彙總值
     * 可用餘額請參考“當前可用餘額(currentAvailableBal)”欄位
     */
    int64               currentTotalBal;
    /** 當前可用餘額 */
    int64               currentAvailableBal;
    /** 當前可取餘額 */
    int64               currentDrawableBal;
} OesCashAssetItemT;


/* 結構體的初始化值定義 */
#define NULLOBJ_OES_CASH_ASSET_ITEM                 \
        __NULLOBJ_OES_CASH_ASSET_BASE_INFO_PKT, \
        0, 0, 0
/* -------------------------           */


/**
 * 查詢客戶資金資訊請求
 */
typedef struct _OesQryCashAssetReq {
    /** 查詢請求訊息頭 */
    OesQryReqHeadT          reqHead;
    /** 查詢過濾條件 */
    OesQryCashAssetFilterT  qryFilter;
} OesQryCashAssetReqT;


/* 結構體的初始化值定義 */
#define NULLOBJ_OES_QRY_CASH_ASSET_REQ              \
        {NULLOBJ_OES_QRY_REQ_HEAD}, \
        {NULLOBJ_OES_QRY_CASH_ASSET_FILTER}
/* -------------------------           */


/**
 * 查詢客戶資金資訊應答
 */
typedef struct _OesQryCashAssetRsp {
    /** 查詢應答訊息頭 */
    OesQryRspHeadT      rspHead;
    /** 客戶資金資訊陣列 */
    OesCashAssetItemT   qryItems[OES_MAX_CASH_ASSET_ITEM_CNT_PER_PACK];
} OesQryCashAssetRspT;


/* 結構體的初始化值定義 */
#define NULLOBJ_OES_QRY_CASH_ASSET_RSP              \
        {NULLOBJ_OES_QRY_RSP_HEAD}, \
        {{NULLOBJ_OES_CASH_ASSET_ITEM}}
/* -------------------------           */


/* ===================================================================
 * 查詢資金資訊相關結構體定義
 * =================================================================== */

/**
 * 主櫃資金資訊內容
 */
typedef struct _OesCounterCashItem {
    /** 資金賬戶程式碼 */
    char                cashAcctId[OES_CASH_ACCT_ID_MAX_LEN];
    /** 客戶程式碼 */
    char                custId[OES_CUST_ID_MAX_LEN];
    /** 客戶姓名 */
    char                custName[OES_CUST_NAME_MAX_LEN];
    /** 銀行程式碼 */
    char                bankId[OES_BANK_NO_MAX_LEN];

    uint8               cashType;               /**< 資金賬戶類別 @see eOesCashTypeT */
    uint8               cashAcctStatus;         /**< 資金賬戶狀態 @see eOesAcctStatusT */
    uint8               currType;               /**< 幣種類型 @see eOesCurrTypeT */
    uint8               isFundTrsfDisabled;     /**< 出入金是否禁止標識 */
    uint8               __filler[4];            /**< 按64位對齊填充域 */

    int64               counterAvailableBal;    /**< 主櫃可用餘額，單位精確到元后四位，即1元 = 10000 */
    int64               counterDrawableBal;     /**< 主櫃可取餘額，單位精確到元后四位，即1元 = 10000 */
    int64               counterCashUpdateTime;  /**< 主櫃資金更新時間 (seconds since the Epoch) */

    int64               __reserve[4];           /**< 保留欄位 */
} OesCounterCashItemT;


/* 結構體的初始化值定義 */
#define NULLOBJ_OES_COUNTER_CASH_ITEM               \
        {0}, {0}, {0}, {0}, \
        0, 0, 0, 0, {0}, \
        0, 0, 0, {0}
/* -------------------------           */


/**
 * 查詢主櫃資金資訊請求
 */
typedef struct _OesQryCounterCashReq {
    /** 資金賬號, 必輸項 */
    char                cashAcctId[OES_CASH_ACCT_ID_MAX_LEN];
} OesQryCounterCashReqT;


/* 結構體的初始化值定義 */
#define NULLOBJ_OES_QRY_COUNTER_CASH_REQ            \
        {0}
/* -------------------------           */


/**
 * 查詢主櫃資金資訊應答
 */
typedef struct _OesQryCounterCashRsp {
    /** 主櫃資金資訊 */
    OesCounterCashItemT counterCashItem;
} OesQryCounterCashRspT;


/* 結構體的初始化值定義 */
#define NULLOBJ_OES_QRY_COUNTER_CASH_RSP            \
        {NULLOBJ_OES_COUNTER_CASH_ITEM}
/* -------------------------           */


/* ===================================================================
 * 查詢股票持倉資訊相關結構體定義
 * =================================================================== */

/**
 * 查詢股票持倉資訊過濾條件
 */
typedef struct _OesQryStkHoldingFilter {
    /** 客戶程式碼, 可選項 */
    char                custId[OES_CUST_ID_MAX_LEN];
    /** 證券賬戶程式碼, 可選項 */
    char                invAcctId[OES_INV_ACCT_ID_MAX_LEN];
    /** 證券程式碼, 可選項 */
    char                securityId[OES_SECURITY_ID_MAX_LEN];

    /** 市場程式碼  @see eOesMarketIdT */
    uint8               mktId;
    /** 證券類別  @see eOesSecurityTypeT */
    uint8               securityType;
    /** 產品型別 @see eOesProductTypeT */
    uint8               productType;
    /** 按64位對齊填充域 */
    uint8               __filler[5];

    /** 使用者私有資訊 (由客戶端自定義填充, 並在應答資料中原樣返回) */
    int64               userInfo;
} OesQryStkHoldingFilterT;


/* 結構體的初始化值定義 */
#define NULLOBJ_OES_QRY_STK_HOLDING_FILTER          \
        {0}, {0}, {0}, \
        0, 0, 0, {0}, 0
/* -------------------------           */


/**
 * 查詢到的股票持倉資訊內容
 */
typedef struct _OesStkHoldingItem {
    __OES_STK_HOLDING_BASE_INFO_PKT;

    /** 當前可賣持倉 */
    int64               sellAvlHld;
    /** 當前可轉換付出持倉 */
    int64               trsfOutAvlHld;
    /** 當前可鎖定持倉 */
    int64               lockAvlHld;
    /** 當前可用於備兌的現貨持倉, 可解鎖的鎖定持倉數量與此相同 */
    int64               coveredAvlHld;
    /**
     * 總持倉, 包括當前可用持倉、不可交易持倉和在途凍結持倉在內的彙總值
     * 可賣持倉請參考“當前可賣持倉(sellAvlHld)”欄位
     */
    int64               sumHld;
    /** 持倉成本價 */
    int64               costPrice;
} OesStkHoldingItemT;


/* 結構體的初始化值定義 */
#define NULLOBJ_OES_STK_HOLDING_ITEM                \
        __NULLOBJ_OES_STK_HOLDING_BASE_INFO_PKT, \
        0, 0, 0, 0, 0, 0
/* -------------------------           */


/**
 * 查詢股票持倉資訊請求
 */
typedef struct _OesQryStkHoldingReq {
    /** 查詢請求訊息頭 */
    OesQryReqHeadT              reqHead;
    /** 查詢過濾條件 */
    OesQryStkHoldingFilterT     qryFilter;
} OesQryStkHoldingReqT;


/* 結構體的初始化值定義 */
#define NULLOBJ_OES_QRY_STK_HOLDING_REQ             \
        {NULLOBJ_OES_QRY_REQ_HEAD}, \
        {NULLOBJ_OES_QRY_STK_HOLDING_FILTER}
/* -------------------------           */


/**
 * 查詢股票持倉資訊應答
 */
typedef struct _OesQryStkHoldingRsp {
    /** 查詢應答訊息頭 */
    OesQryRspHeadT          qryHead;
    /** 持倉資訊陣列 */
    OesStkHoldingItemT      qryItems[OES_MAX_HOLDING_ITEM_CNT_PER_PACK];
} OesQryStkHoldingRspT;


/* 結構體的初始化值定義 */
#define NULLOBJ_OES_QRY_STK_HOLDING_RSP             \
        {NULLOBJ_OES_QRY_RSP_HEAD}, \
        {{NULLOBJ_OES_STK_HOLDING_ITEM}}
/* -------------------------           */


/* ===================================================================
 * 查詢期權持倉資訊相關結構體定義
 * =================================================================== */

/**
 * 查詢期權持倉資訊過濾條件
 */
typedef OesQryStkHoldingFilterT     OesQryOptHoldingFilterT;


/* 結構體的初始化值定義 */
#define NULLOBJ_OES_QRY_OPT_HOLDING_FILTER          \
        NULLOBJ_OES_QRY_STK_HOLDING_FILTER
/* -------------------------           */


/**
 * 查詢到的期權持倉資訊內容
 */
typedef struct _OesOptHoldingItem {
    __OES_OPT_HOLDING_BASE_INFO_PKT;
} OesOptHoldingItemT;


/* 結構體的初始化值定義 */
#define NULLOBJ_OES_OPT_HOLDING_ITEM                \
        __NULLOBJ_OES_OPT_HOLDING_BASE_INFO_PKT
/* -------------------------           */


/**
 * 查詢期權持倉資訊請求
 */
typedef struct _OesQryOptHoldingReq {
    /** 查詢請求訊息頭 */
    OesQryReqHeadT              reqHead;
    /** 查詢過濾條件 */
    OesQryOptHoldingFilterT     qryFilter;
} OesQryOptHoldingReqT;


/* 結構體的初始化值定義 */
#define NULLOBJ_OES_QRY_OPT_HOLDING_REQ             \
        {NULLOBJ_OES_QRY_REQ_HEAD}, \
        {NULLOBJ_OES_QRY_OPT_HOLDING_FILTER}
/* -------------------------           */


/**
 * 查詢期權持倉資訊應答
 */
typedef struct _OesQryHoldRsp {
    /** 查詢應答訊息頭 */
    OesQryRspHeadT          rspHead;
    /** 持倉資訊陣列 */
    OesOptHoldingItemT      qryItems[OES_MAX_HOLDING_ITEM_CNT_PER_PACK];
} OesQryOptHoldingRspT;


/* 結構體的初始化值定義 */
#define NULLOBJ_OES_QRY_OPT_HOLDING_RSP             \
        {NULLOBJ_OES_QRY_RSP_HEAD}, \
        {{NULLOBJ_OES_OPT_HOLDING_ITEM}}
/* -------------------------           */



/* ===================================================================
 * 查詢客戶資訊相關結構體定義
 * =================================================================== */

/**
 * 查詢客戶資訊過濾條件
 */
typedef struct _OesQryCustFilter {
    /** 客戶程式碼, 可選項 */
    char                custId[OES_CUST_ID_MAX_LEN];

    /** 使用者私有資訊 (由客戶端自定義填充, 並在應答資料中原樣返回) */
    int64               userInfo;
} OesQryCustFilterT;


/* 結構體的初始化值定義 */
#define NULLOBJ_OES_QRY_CUST_FILTER                 \
        {0}, 0
/* -------------------------           */


/**
 * 客戶資訊內容
 */
typedef OesCustBaseInfoT    OesCustItemT;


/* 結構體的初始化值定義 */
#define NULLOBJ_OES_CUST_ITEM                       \
        NULLOBJ_OES_CUST_BASE_INFO
/* -------------------------           */


/**
 * 查詢客戶資訊請求
 */
typedef struct _OesQryCustReq {
    /** 查詢請求訊息頭 */
    OesQryReqHeadT      reqHead;
    /** 查詢過濾條件 */
    OesQryCustFilterT   qryFilter;
} OesQryCustReqT;


/* 結構體的初始化值定義 */
#define NULLOBJ_OES_QRY_CUST_REQ                    \
        {NULLOBJ_OES_QRY_REQ_HEAD}, \
        {NULLOBJ_OES_QRY_CUST_FILTER}
/* -------------------------           */


/**
 * 查詢客戶資訊應答
 */
typedef struct _OesQryCustRsp {
    /** 查詢應答訊息頭 */
    OesQryRspHeadT      rspHead;
    /** 客戶資訊陣列 */
    OesCustItemT        qryItems[OES_MAX_CUST_ITEM_CNT_PER_PACK];
} OesQryCustRspT;


/* 結構體的初始化值定義 */
#define NULLOBJ_OES_QRY_CUST_RSP                    \
        {NULLOBJ_OES_QRY_RSP_HEAD}, \
        {{NULLOBJ_OES_CUST_ITEM}}
/* -------------------------           */


/* ===================================================================
 * 查詢證券賬戶資訊相關結構體定義
 * =================================================================== */

/**
 * 查詢證券賬戶資訊過濾條件
 */
typedef struct _OesQryInvAcctFilter {
    /** 客戶程式碼, 可選項 */
    char                custId[OES_CUST_ID_MAX_LEN];
    /** 證券賬戶程式碼, 可選項 */
    char                invAcctId[OES_INV_ACCT_ID_MAX_LEN];

    /**
     * 市場程式碼, 可選項。如無需此過濾條件請使用 OES_MKT_ID_UNDEFINE
     * @see eOesMarketIdT
     */
    uint8               mktId;
    /** 按64位對齊填充域 */
    uint8               __filler[7];

    /** 使用者私有資訊 (由客戶端自定義填充, 並在應答資料中原樣返回) */
    int64               userInfo;
} OesQryInvAcctFilterT;


/* 結構體的初始化值定義 */
#define NULLOBJ_OES_QRY_INV_ACCT_FILTER             \
        {0}, {0}, \
        0, {0}, 0
/* -------------------------           */


/**
 * 證券賬戶內容
 */
typedef struct _OesInvAcctItem {
    __OES_INV_ACCT_BASE_INFO_PKT;

    /** 客戶程式碼 */
    char                custId[OES_CUST_ID_MAX_LEN];
} OesInvAcctItemT;


/* 結構體的初始化值定義 */
#define NULLOBJ_OES_INV_ACCT_ITEM                   \
        __NULLOBJ_OES_INV_ACCT_BASE_INFO_PKT, \
        {0}
/* -------------------------           */


/**
 * 查詢證券賬戶資訊請求
 */
typedef struct _OesQryInvAcctReq {
    /** 查詢請求訊息頭 */
    OesQryReqHeadT          reqHead;
    /** 查詢過濾條件 */
    OesQryInvAcctFilterT    qryFilter;
} OesQryInvAcctReqT;


/* 結構體的初始化值定義 */
#define NULLOBJ_OES_QRY_INV_ACCT_REQ                \
        {NULLOBJ_OES_QRY_REQ_HEAD}, \
        {NULLOBJ_OES_QRY_INV_ACCT_FILTER}
/* -------------------------           */


/**
 * 查詢證券賬戶資訊應答
 */
typedef struct _OesQryInvAcctRsp {
    /** 查詢應答訊息頭 */
    OesQryRspHeadT      rspHead;
    /** 證券賬戶資訊陣列 */
    OesInvAcctItemT     qryItems[OES_MAX_INV_ACCT_ITEM_CNT_PER_PACK];
} OesQryInvAcctRspT;


/* 結構體的初始化值定義 */
#define NULLOBJ_OES_QRY_INV_ACCT_RSP                \
        {NULLOBJ_OES_QRY_RSP_HEAD}, \
        {{NULLOBJ_OES_INV_ACCT_ITEM}}
/* -------------------------           */


/* ===================================================================
 * 查詢客戶端總覽資訊相關結構體定義
 * =================================================================== */

/**
 * 股東賬戶總覽資訊內容
 */
typedef struct _OesInvAcctOverview {
    /** 股東賬戶程式碼 */
    char                invAcctId[OES_INV_ACCT_ID_MAX_LEN];
    /** 市場 @see eOesMarketIdT */
    uint8               mktId;

    /** 賬戶型別 @see eOesAcctTypeT */
    uint8               acctType;
    /** 賬戶狀態 @see eOesAcctStatusT */
    uint8               status;
    /** 股東賬戶的所有者型別 @see eOesOwnerTypeT */
    uint8               ownerType;
    /** 期權投資者級別 @see eOesOptInvLevelT */
    uint8               optInvLevel;
    /** 是否禁止交易 (僅供API查詢使用) */
    uint8               isTradeDisabled;
    /** 按64位對齊填充域 */
    uint8               __INV_ACCT_BASE_filler[2];

    /** 證券賬戶許可權限制 @see eOesTradingLimitT */
    uint64              limits;
    /** 股東許可權/客戶許可權 @see eOesTradingPermissionT */
    uint64              permissions;

    /** 席位號 */
    int32               pbuId;
    /** 主機板權益 (新股/配股認購限額) */
    int32               subscriptionQuota;

    /** 客戶程式碼 */
    char                custId[OES_CUST_ID_MAX_LEN];

    uint8               isValid;                /**< 股東賬戶是否有效標識 */
    uint8               __filler[3];            /**< 按64位位元組對齊的填充域 */
    int32               kcSubscriptionQuota;    /**< 科創板權益 (新股/配股認購限額) */

    int32               trdOrdCnt;              /**< 當日累計有效交易類委託筆數統計 */
    int32               nonTrdOrdCnt;           /**< 當日累計有效非交易類委託筆數統計 */
    int32               cancelOrdCnt;           /**< 當日累計有效撤單筆數統計 */
    int32               oesRejectOrdCnt;        /**< 當日累計被OES拒絕的委託筆數統計 */
    int32               exchRejectOrdCnt;       /**< 當日累計被交易所拒絕的委託筆數統計 */
    int32               trdCnt;                 /**< 當日累計成交筆數統計 */

    int64               __reserve;              /**< 備用欄位 */
} OesInvAcctOverviewT;


/* 結構體的初始化值定義 */
#define NULLOBJ_OES_INV_ACCT_OVERVIEW                       \
        {0}, 0, \
        0, 0, 0, 0, 0, {0}, \
        0, 0, \
        0, 0, \
        {0}, \
        0, {0}, 0, \
        0, 0, 0, 0, 0, 0, \
        0
/* -------------------------           */


/**
 * 資金賬戶總覽資訊內容
 */
typedef struct _OesCashAcctOverview {
    /** 資金賬戶程式碼 */
    char                cashAcctId[OES_CASH_ACCT_ID_MAX_LEN];
    /** 客戶程式碼 */
    char                custId[OES_CUST_ID_MAX_LEN];
    /** 銀行程式碼 */
    char                bankId[OES_BANK_NO_MAX_LEN];

    uint8               isValid;                /**< 資金賬戶是否有效標識 */
    uint8               cashType;               /**< 資金賬戶類別 @see eOesCashTypeT */
    uint8               cashAcctStatus;         /**< 資金賬戶狀態 @see eOesAcctStatusT */
    uint8               currType;               /**< 幣種類型 @see eOesCurrTypeT */
    uint8               isFundTrsfDisabled;     /**< 出入金是否禁止標識 */
    uint8               __filler[3];            /**< 按64位對齊的填充域 */

    int64               __reserve;              /**< 備用欄位 */
} OesCashAcctOverviewT;


/* 結構體的初始化值定義 */
#define NULLOBJ_OES_CASH_ACCT_OVERVIEW                       \
        {0}, {0}, {0}, \
        0, 0, 0, 0, 0, {0}, \
        0
/* -------------------------           */


/**
 * 客戶總覽資訊內容
 */
typedef struct _OesCustOverview {
    __OES_CUST_BASE_INFO_PKT;

    /** 客戶姓名 */
    char                    custName[OES_CUST_NAME_MAX_LEN];

    OesCashAcctOverviewT    spotCashAcct;           /**< 普通資金賬戶資訊 */
    OesCashAcctOverviewT    creditCashAcct;         /**< 信用資金賬戶資訊 */
    OesCashAcctOverviewT    optionCashAcct;         /**< 衍生品資金賬戶資訊 */

    OesInvAcctOverviewT     shSpotInvAcct;          /**< 上海現貨股東賬戶資訊 */
    OesInvAcctOverviewT     shOptionInvAcct;        /**< 上海衍生品股東賬戶資訊 */
    OesInvAcctOverviewT     szSpotInvAcct;          /**< 深圳現貨股東賬戶資訊 */
    OesInvAcctOverviewT     szOptionInvAcct;        /**< 深圳衍生品股東賬戶資訊 */

    int64                   __reserve;              /**< 備用欄位 */
} OesCustOverviewT;


/* 結構體的初始化值定義 */
#define NULLOBJ_OES_CUST_OVERVIEW                       \
        __NULLOBJ_OES_CUST_BASE_INFO_PKT, {0}, \
        {NULLOBJ_OES_CASH_ACCT_OVERVIEW}, \
        {NULLOBJ_OES_CASH_ACCT_OVERVIEW}, \
        {NULLOBJ_OES_CASH_ACCT_OVERVIEW}, \
        {NULLOBJ_OES_INV_ACCT_OVERVIEW}, \
        {NULLOBJ_OES_INV_ACCT_OVERVIEW}, \
        {NULLOBJ_OES_INV_ACCT_OVERVIEW}, \
        {NULLOBJ_OES_INV_ACCT_OVERVIEW}, \
        0
/* -------------------------           */


/**
 * 客戶端總覽資訊內容
 */
typedef struct _OesClientOverview {
    int16               clientId;               /**< 客戶端編號 */
    uint8               clientType;             /**< 客戶端型別  @see eOesClientTypeT */
    uint8               clientStatus;           /**< 客戶端狀態  @see eOesClientStatusT */
    uint8               isApiForbidden;         /**< API禁用標識 */
    uint8               isBlockTrader;          /**< 是否大宗交易標識 */
    uint8               __filler[2];            /**< 按64位位元組對齊的填充域 */
    int64               logonTime;              /**< 客戶端登入(委託接收服務)時間 */

    /** 客戶端名稱 */
    char                clientName[OES_CLIENT_NAME_MAX_LEN];
    /** 客戶端說明 */
    char                clientMemo[OES_CLIENT_DESC_MAX_LEN];

    int32               sseStkPbuId;            /**< 上海現貨/信用賬戶對應的PBU程式碼 */
    int32               sseOptPbuId;            /**< 上海衍生品賬戶對應的PBU程式碼 */
    uint8               sseQualificationClass;  /**< 上海股東賬戶的投資者適當性管理分類 @see eOesQualificationClassT */
    uint8               __filler2[7];           /**< 按64位對齊填充域 */

    int32               szseStkPbuId;           /**< 深圳現貨/信用賬戶對應的PBU程式碼 */
    int32               szseOptPbuId;           /**< 深圳衍生品賬戶對應的PBU程式碼 */
    uint8               szseQualificationClass; /**< 深圳股東賬戶的投資者適當性管理分類 @see eOesQualificationClassT */
    uint8               __filler3[7];           /**< 按64位對齊填充域 */

    int32               currOrdConnected;       /**< 當前已連線的委託通道數量 */
    int32               currRptConnected;       /**< 當前已連線的回報通道數量 */
    int32               currQryConnected;       /**< 當前已連線的查詢通道數量 */
    int32               maxOrdConnect;          /**< 委託通道允許的最大同時連線數量 */
    int32               maxRptConnect;          /**< 回報通道允許的最大同時連線數量 */
    int32               maxQryConnect;          /**< 查詢通道允許的最大同時連線數量 */

    int32               ordTrafficLimit;        /**< 委託通道的流量控制 */
    int32               qryTrafficLimit;        /**< 查詢通道的流量控制 */
    int64               __reserve;              /**< 備用欄位 */

    int32               associatedCustCnt;      /**< 客戶端關聯的客戶數量 */
    int32               __filler4;              /**< 按64位位元組對齊的填充域 */

    /** 客戶端關聯的客戶列表 */
    OesCustOverviewT    custItems[OES_MAX_CUST_PER_CLIENT];
} OesClientOverviewT;


/* 結構體的初始化值定義 */
#define NULLOBJ_OES_CLIENT_OVERVIEW                       \
        0, 0, 0, 0, 0, {0}, 0, \
        {0}, {0}, \
        0, 0, 0, {0}, \
        0, 0, 0, {0}, \
        0, 0, 0, 0, 0, 0, \
        0, 0, 0, \
        0, 0, \
        {{NULLOBJ_OES_CUST_OVERVIEW}}
/* -------------------------           */


/* ===================================================================
 * 查詢客戶佣金資訊相關結構體定義
 * =================================================================== */

/**
 * 查詢客戶佣金資訊過濾條件
 */
typedef struct _OesQryCommissionRateFilter {
    /** 客戶程式碼, 可選項 */
    char                custId[OES_CUST_ID_MAX_LEN];

    /**
     * 市場程式碼, 可選項。如無需此過濾條件請使用 OES_MKT_ID_UNDEFINE
     * @see eOesMarketIdT
     */
    uint8               mktId;
    /**
     * 證券類別, 可選項。如無需此過濾條件請使用 OES_SECURITY_TYPE_UNDEFINE
     * @see eOesSecurityTypeT
     */
    uint8               securityType;
    /**
     * 買賣型別, 可選項。如無需此過濾條件請使用 OES_BS_TYPE_UNDEFINE
     * @see eOesBuySellTypeT
     */
    uint8               bsType;
    /** 按64位對齊填充域 */
    uint8               __filler[5];

    /** 使用者私有資訊 (由客戶端自定義填充, 並在應答資料中原樣返回) */
    int64               userInfo;
} OesQryCommissionRateFilterT;


/* 結構體的初始化值定義 */
#define NULLOBJ_OES_QRY_COMMISSION_RATE_FILTER      \
        {0}, 0, 0, 0, {0}, 0
/* -------------------------           */


/**
 * 客戶佣金資訊內容定義
 */
typedef struct _OesCommissionRateItem {
    /** 客戶程式碼 */
    char                custId[OES_CUST_ID_MAX_LEN];
    /** 證券程式碼 */
    char                securityId[OES_SECURITY_ID_MAX_LEN];

    /** 市場 @see eOesMarketIdT */
    uint8               mktId;
    /** 證券類別 @see eOesSecurityTypeT */
    uint8               securityType;
    /** 證券子類別 @see eOesSubSecurityTypeT */
    uint8               subSecurityType;
    /** 買賣型別 @see eOesBuySellTypeT */
    uint8               bsType;

    /** 費用標識 @see eOesFeeTypeT */
    uint8               feeType;
    /** 幣種 @see eOesCurrTypeT */
    uint8               currType;
    /** 計算模式 @see eOesCalcFeeModeT */
    uint8               calcFeeMode;
    /** 按64位對齊填充域 */
    uint8               __filler;

    /** 費率, 單位精確到千萬分之一, 即費率0.02% = 2000 */
    int64               feeRate;
    /** 最低費用, 大於0時有效 (單位：萬分之一元) */
    int32               minFee;
    /** 最高費用, 大於0時有效 (單位：萬分之一元) */
    int32               maxFee;
} OesCommissionRateItemT;


/* 結構體的初始化值定義 */
#define NULLOBJ_OES_COMMISSION_RATE_ITEM            \
        {0}, {0}, \
        0, 0, 0, 0, \
        0, 0, 0, 0, \
        0, 0, 0
/* -------------------------           */


/**
 * 查詢客戶佣金資訊請求
 */
typedef struct _OesQryCommissionRateReq {
    /** 查詢請求訊息頭 */
    OesQryReqHeadT              reqHead;
    /** 查詢過濾條件 */
    OesQryCommissionRateFilterT qryFilter;
} OesQryCommissionRateReqT;


/* 結構體的初始化值定義 */
#define NULLOBJ_OES_QRY_COMMISSION_RATE_REQ         \
        {NULLOBJ_OES_QRY_REQ_HEAD}, \
        {NULLOBJ_OES_QRY_COMMISSION_RATE_FILTER}
/* -------------------------           */


/**
 * 查詢客戶佣金資訊應答
 */
typedef struct _OesQryCommissionRateRsp {
    /** 查詢應答訊息頭 */
    OesQryRspHeadT          rspHead;
    /** 客戶佣金資訊陣列 */
    OesCommissionRateItemT  qryItems[OES_MAX_COMMS_RATE_ITEM_CNT_PER_PACK];
} OesQryCommissionRateRspT;


/* 結構體的初始化值定義 */
#define NULLOBJ_OES_QRY_COMMISSION_RATE_RSP         \
        {NULLOBJ_OES_QRY_RSP_HEAD}, \
        {{NULLOBJ_OES_COMMISSION_RATE_ITEM}}
/* -------------------------           */


/* ===================================================================
 * 查詢出入金流水資訊相關結構體定義
 * =================================================================== */

/**
 * 查詢出入金流水資訊過濾條件
 */
typedef struct _OesQryFundTransferSerialFilter {
    /** 客戶程式碼, 可選項 */
    char                custId[OES_CUST_ID_MAX_LEN];
    /** 資金賬戶程式碼, 可選項 */
    char                cashAcctId[OES_CASH_ACCT_ID_MAX_LEN];

    /** 出入金流水號, 可選項 */
    int32               clSeqNo;
    /** 客戶端環境號 */
    int8                clEnvId;
    /** 按64位對齊填充域 */
    uint8               __filler[3];

    /** 使用者私有資訊 (由客戶端自定義填充, 並在應答資料中原樣返回) */
    int64               userInfo;
} OesQryFundTransferSerialFilterT;


/* 結構體的初始化值定義 */
#define NULLOBJ_OES_QRY_FUND_TRANSFER_SERIAL_FILTER \
        {0}, {0}, 0, 0, {0}, 0
/* -------------------------           */


/**
 * 查詢出入金流水資訊應答
 */
typedef OesFundTrsfReportT      OesFundTransferSerialItemT;


/* 結構體的初始化值定義 */
#define NULLOBJ_OES_FUND_TRANSFER_SERIAL_ITEM       \
        NULLOBJ_OES_FUND_TRSF_REPORT
/* -------------------------           */


/**
 * 查詢出入金流水資訊請求
 */
typedef struct _OesQryFundTransferSerialReq {
    /** 查詢請求訊息頭 */
    OesQryReqHeadT                  reqHead;
    /** 查詢過濾條件 */
    OesQryFundTransferSerialFilterT qryFilter;
} OesQryFundTransferSerialReqT;


/* 結構體的初始化值定義 */
#define NULLOBJ_OES_QRY_FUND_TRANSFER_SERIAL_REQ    \
        {NULLOBJ_OES_QRY_REQ_HEAD}, \
        {NULLOBJ_OES_QRY_FUND_TRANSFER_SERIAL_FILTER}
/* -------------------------           */


/**
 * 查詢出入金流水資訊應答
 */
typedef struct _OesQryFundTransferSerialRsp {
    /** 查詢應答訊息頭 */
    OesQryRspHeadT              rspHead;
    /** 出入金流水資訊陣列 */
    OesFundTransferSerialItemT  qryItems[OES_MAX_FUND_TRSF_ITEM_CNT_PER_PACK];
} OesQryFundTransferSerialRspT;


/* 結構體的初始化值定義 */
#define NULLOBJ_OES_QRY_FUND_TRANSFER_SERIAL_RSP    \
        {NULLOBJ_OES_QRY_RSP_HEAD}, \
        {{NULLOBJ_OES_FUND_TRANSFER_SERIAL_ITEM}}
/* -------------------------           */


/* ===================================================================
 * 查詢新股配號、中籤資訊相關結構體定義
 * =================================================================== */

/**
 * 查詢新股配號、中籤資訊過濾條件
 */
typedef struct _OesQryLotWinningFilter {
    /** 客戶程式碼, 可選項 */
    char                custId[OES_CUST_ID_MAX_LEN];
    /** 證券賬戶程式碼, 可選項 */
    char                invAcctId[OES_INV_ACCT_ID_MAX_LEN];

    /**
     * 市場程式碼, 可選項。如無需此過濾條件請使用 OES_MKT_ID_UNDEFINE
     * @see eOesMarketIdT
     */
    uint8               mktId;
    /**
     * 查詢記錄型別, 可選項。如無需此過濾條件請使用 OES_LOT_TYPE_UNDEFINE
     * @see eOesLotTypeT
     */
    uint8               lotType;
    /** 按64位對齊填充域 */
    uint8               __filler[6];

    /** 查詢起始日期 (格式為 YYYYMMDD) */
    int32               startDate;
    /** 查詢結束日期 (格式為 YYYYMMDD) */
    int32               endDate;

    /** 使用者私有資訊 (由客戶端自定義填充, 並在應答資料中原樣返回) */
    int64               userInfo;
} OesQryLotWinningFilterT;


/* 結構體的初始化值定義 */
#define NULLOBJ_OES_QRY_LOT_WINNING_FILTER          \
        {0}, {0}, \
        0, 0, {0}, \
        0, 0, 0
/* -------------------------           */


/**
 * 新股配號、中籤資訊內容
 */
typedef OesLotWinningBaseInfoT      OesLotWinningItemT;


/* 結構體的初始化值定義 */
#define NULLOBJ_OES_LOT_WINNING_ITEM                \
        NULLOBJ_OES_LOT_WINNING_BASE_INFO
/* -------------------------           */


/**
 * 查詢新股認購、中籤資訊請求
 */
typedef struct _OesQryLotWinningReq {
    /** 查詢請求訊息頭 */
    OesQryReqHeadT              reqHead;
    /** 查詢過濾條件 */
    OesQryLotWinningFilterT     qryFilter;
} OesQryLotWinningReqT;


/* 結構體的初始化值定義 */
#define NULLOBJ_OES_QRY_LOT_WINNING_REQ             \
        {NULLOBJ_OES_QRY_REQ_HEAD}, \
        {NULLOBJ_OES_QRY_LOT_WINNING_FILTER}
/* -------------------------           */


/**
 * 查詢新股配號、中籤資訊應答
 */
typedef struct _OesQryLotWinningRsp {
    /** 查詢應答訊息頭 */
    OesQryRspHeadT          rspHead;
    /** 新股認購、中籤資訊陣列 */
    OesLotWinningItemT      qryItems[OES_MAX_LOG_WINNING_ITEM_CNT_PER_PACK];
} OesQryLotWinningRspT;


/* 結構體的初始化值定義 */
#define NULLOBJ_OES_QRY_LOT_WINNING_RSP             \
        {NULLOBJ_OES_QRY_RSP_HEAD}, \
        {{NULLOBJ_OES_LOT_WINNING_ITEM}}
/* -------------------------           */


/* ===================================================================
 * 查詢證券發行資訊相關結構體定義
 * =================================================================== */

/**
 * 查詢證券發行資訊過濾條件
 */
typedef struct _OesQryIssueFilter {
    /** 證券發行程式碼, 可選項 */
    char                securityId[OES_SECURITY_ID_MAX_LEN];

    /**
     * 市場程式碼, 可選項。如無需此過濾條件請使用 OES_MKT_UNDEFINE
     * @see eOesMarketIdT
     */
    uint8               mktId;

    /**
     * 產品型別, 預設型別為 OES_PRODUCT_TYPE_IPO
     * @see eOesProductTypeT
     */
    uint8               productType;

    /** 按64位對齊填充域 */
    uint8               __filler[6];

    /** 使用者私有資訊 (由客戶端自定義填充, 並在應答資料中原樣返回) */
    int64               userInfo;
} OesQryIssueFilterT;


/* 結構體的初始化值定義 */
#define NULLOBJ_OES_QRY_ISSUE_FILTER                \
        {0}, 0, 0, {0}, 0
/* -------------------------           */


/**
 * 證券發行資訊內容
 */
typedef OesIssueBaseInfoT   OesIssueItemT;


/* 結構體的初始化值定義 */
#define NULLOBJ_OES_ISSUE_ITEM                      \
        NULLOBJ_OES_ISSUE_BASE_INFO
/* -------------------------           */


/**
 * 查詢證券發行資訊請求
 */
typedef struct _OesQryIssueReq {
    /** 查詢請求訊息頭 */
    OesQryReqHeadT      reqHead;
    /** 查詢過濾條件 */
    OesQryIssueFilterT  qryFilter;
} OesQryIssueReqT;


/* 結構體的初始化值定義 */
#define NULLOBJ_OES_QRY_ISSUE_REQ                   \
        {NULLOBJ_OES_QRY_REQ_HEAD}, \
        {NULLOBJ_OES_QRY_ISSUE_FILTER}
/* -------------------------           */


/**
 * 查詢證券發行資訊應答
 */
typedef struct _OesQryIssueRsp {
    /** 查詢應答訊息頭 */
    OesQryRspHeadT      rspHead;
    /** 證券發行資訊陣列 */
    OesIssueItemT       qryItems[OES_MAX_ISSUE_ITEM_CNT_PER_PACK];
} OesQryIssueRspT;


/* 結構體的初始化值定義 */
#define NULLOBJ_OES_QRY_ISSUE_RSP                   \
        {NULLOBJ_OES_QRY_RSP_HEAD}, \
        {{NULLOBJ_OES_ISSUE_ITEM}}
/* -------------------------           */


/* ===================================================================
 * 查詢現貨產品資訊相關結構體定義
 * =================================================================== */

/**
 * 查詢現貨產品資訊過濾條件
 */
typedef struct _OesQryStockFilter {
    /** 證券程式碼, 可選項 */
    char                securityId[OES_SECURITY_ID_MAX_LEN];

    /**
     * 市場程式碼, 可選項。如無需此過濾條件請使用 OES_MKT_ID_UNDEFINE
     * @see eOesMarketIdT
     */
    uint8               mktId;
    /** 證券類別  @see eOesSecurityTypeT */
    uint8               securityType;
    /** 證券子類別  @see eOesSubSecurityTypeT */
    uint8               subSecurityType;
    /** 按64位對齊填充域 */
    uint8               __filler[5];

    /** 使用者私有資訊 (由客戶端自定義填充, 並在應答資料中原樣返回) */
    int64               userInfo;
} OesQryStockFilterT;


/* 結構體的初始化值定義 */
#define NULLOBJ_OES_QRY_STOCK_FILTER                \
        {0}, 0, 0, 0, {0}, 0
/* -------------------------           */


/**
 * 現貨產品資訊內容
 */
typedef OesStockBaseInfoT       OesStockItemT;


/* 結構體的初始化值定義 */
#define NULLOBJ_OES_STOCK_ITEM                      \
        NULLOBJ_OES_STOCK_BASE_INFO
/* -------------------------           */


/**
 * 查詢現貨產品資訊請求
 */
typedef struct _OesQryStockReq {
    /** 查詢請求訊息頭 */
    OesQryReqHeadT      reqHead;
    /** 查詢過濾條件 */
    OesQryStockFilterT  qryFilter;
} OesQryStockReqT;


/* 結構體的初始化值定義 */
#define NULLOBJ_OES_QRY_STOCK_REQ                   \
        {NULLOBJ_OES_QRY_REQ_HEAD}, \
        {NULLOBJ_OES_QRY_STOCK_FILTER}
/* -------------------------           */


/**
 * 查詢現貨產品資訊應答
 */
typedef struct _OesQryStockRsp {
    /** 查詢應答訊息頭 */
    OesQryRspHeadT      rspHead;
    /** 現貨產品資訊陣列 */
    OesStockItemT       qryItems[OES_MAX_STOCK_ITEM_CNT_PER_PACK];
} OesQryStockRspT;


/* 結構體的初始化值定義 */
#define NULLOBJ_OES_QRY_STOCK_RSP                   \
        {NULLOBJ_OES_QRY_RSP_HEAD}, \
        {{NULLOBJ_OES_STOCK_ITEM}}
/* -------------------------           */


/* ===================================================================
 * 查詢ETF申贖產品資訊相關結構體定義
 * =================================================================== */

/**
 * 查詢ETF申贖產品資訊過濾條件
 */
typedef struct _OesQryEtfFilter {
    /** 基金程式碼, 可選項 */
    char                fundId[OES_SECURITY_ID_MAX_LEN];

    /**
     * 市場程式碼, 可選項。如無需此過濾條件請使用 OES_MKT_ID_UNDEFINE
     * @see eOesMarketIdT
     */
    uint8               mktId;
    /** 按64位對齊填充域 */
    uint8               __filler[7];

    /** 使用者私有資訊 (由客戶端自定義填充, 並在應答資料中原樣返回) */
    int64               userInfo;
} OesQryEtfFilterT;


/* 結構體的初始化值定義 */
#define NULLOBJ_OES_QRY_ETF_FILTER                  \
        {0}, 0, {0}, 0
/* -------------------------           */


/**
 * ETF申贖產品資訊內容
 */
typedef OesEtfBaseInfoT     OesEtfItemT;


/* 結構體的初始化值定義 */
#define NULLOBJ_OES_ETF_ITEM                        \
        NULLOBJ_OES_ETF_BASE_INFO
/* -------------------------           */


/**
 * 查詢ETF申贖產品資訊請求
 */
typedef struct _OesQryEtfReq {
    /** 查詢請求訊息頭 */
    OesQryReqHeadT      reqHead;
    /** 查詢過濾條件 */
    OesQryEtfFilterT    qryFilter;
} OesQryEtfReqT;


/* 結構體的初始化值定義 */
#define NULLOBJ_OES_QRY_ETF_REQ                     \
        {NULLOBJ_OES_QRY_REQ_HEAD}, \
        {NULLOBJ_OES_QRY_ETF_FILTER}
/* -------------------------           */


/**
 * 查詢ETF申贖產品資訊應答
 */
typedef struct _OesQryEtfRsp {
    /** 查詢應答訊息頭 */
    OesQryRspHeadT      rspHead;
    /** ETF申贖產品資訊陣列 */
    OesEtfItemT         qryItems[OES_MAX_ETF_ITEM_CNT_PER_PACK];
} OesQryEtfRspT;


/* 結構體的初始化值定義 */
#define NULLOBJ_OES_QRY_ETF_RSP                     \
        {NULLOBJ_OES_QRY_RSP_HEAD}, \
        {{NULLOBJ_OES_ETF_ITEM}}
/* -------------------------           */


/* ===================================================================
 * 查詢Etf成分股資訊相關結構體定義
 * =================================================================== */

/**
 * 查詢Etf成分股資訊過濾條件
 */
typedef struct _OesQryEtfComponentFilter {
    /** ETF基金程式碼, 必填項 */
    char                fundId[OES_SECURITY_ID_MAX_LEN];

    /** 使用者私有資訊 (由客戶端自定義填充, 並在應答資料中原樣返回) */
    int64               userInfo;
} OesQryEtfComponentFilterT;


/* 結構體的初始化值定義 */
#define NULLOBJ_OES_QRY_ETF_COMPONENT_FILTER        \
        {0}, 0
/* -------------------------           */


/**
 * EtfComponent成分股資訊內容
 */
typedef struct _OesEtfComponentItem {
    /** Etf成分股程式碼 */
    char                securityId[OES_SECURITY_ID_MAX_LEN];
    /** 市場程式碼 @see eOesMarketIdT */
    uint8               mktId;
    /** 現金替代標識 @see eOesEtfSubFlagT */
    uint8               subFlag;
    /** 證券型別 @see eOesSecurityTypeT */
    uint8               securityType;
    /** 證券子型別 @see eOesSubSecurityTypeT */
    uint8               subSecurityType;

    /** 昨日收盤價格 */
    int32               prevClose;
    /** 成分證券數量 */
    int32               qty;
    /** 溢價比例, 單位精確到十萬分之一, 即溢價比例10% = 10000 */
    int32               premiumRate;

    /** 申購替代金額, 單位精確到元后四位, 即1元 = 10000 */
    int64               creationSubCash;
    /** 贖回替代金額, 單位精確到元后四位, 即1元 = 10000 */
    int64               redemptionCashSub;
    /** 成分股所屬ETF的基金程式碼 */
    char                fundId[OES_SECURITY_ID_MAX_LEN];
} OesEtfComponentItemT;


/* 結構體的初始化值定義 */
#define NULLOBJ_OES_ETF_COMPONENET_ITEM             \
        {0}, 0, 0, 0, 0, \
        0, 0, 0, \
        0, 0, {0}
/* -------------------------           */


/**
 * 查詢EtfComponent成分股資訊請求
 */
typedef struct _OesQryEtfComponentReq {
    /** 查詢請求訊息頭 */
    OesQryReqHeadT              reqHead;
    /** 查詢過濾條件 */
    OesQryEtfComponentFilterT   qryFilter;
} OesQryEtfComponentReqT;


/* 結構體的初始化值定義 */
#define NULLOBJ_OES_QRY_ETF_COMPONENT_REQ           \
        {NULLOBJ_OES_QRY_REQ_HEAD}, \
        {NULLOBJ_OES_QRY_ETF_COMPONENT_FILTER}
/* -------------------------           */


/**
 * 查詢EtfComponent成分股資訊應答
 */
typedef struct _OesQryEtfComponentRsp {
    /** 查詢應答訊息頭 */
    OesQryRspHeadT      rspHead;
    /** EtfComponent成分股資訊陣列 */
    OesEtfComponentItemT
                        qryItems[OES_MAX_ETF_COMPONENT_ITEM_CNT_PER_PACK];
} OesQryEtfComponentRspT;


/* 結構體的初始化值定義 */
#define NULLOBJ_OES_QRY_ETF_COMPONENT_RSP           \
        {NULLOBJ_OES_QRY_RSP_HEAD}, \
        {{NULLOBJ_OES_ETF_COMPONENET_ITEM}}
/* -------------------------           */


/* ===================================================================
 * 查詢期權產品資訊相關結構體定義
 * =================================================================== */

/**
 * 查詢期權產品資訊過濾條件
 */
typedef struct _OesQryOptionFilter {
    /** 證券程式碼, 可選項 */
    char                securityId[OES_SECURITY_ID_MAX_LEN];

    /**
     * 市場程式碼, 可選項。如無需此過濾條件請使用 OES_MKT_ID_UNDEFINE
     * @see eOesMarketIdT
     */
    uint8               mktId;
    /** 按64位對齊填充域 */
    uint8               __filler[7];

    /** 使用者私有資訊 (由客戶端自定義填充, 並在應答資料中原樣返回) */
    int64               userInfo;
} OesQryOptionFilterT;


/* 結構體的初始化值定義 */
#define NULLOBJ_OES_QRY_OPTION_FILTER               \
        {0}, 0, {0}, 0
/* -------------------------           */


/**
 * 期權產品資訊內容
 */
typedef OesOptionBaseInfoT      OesOptionItemT;


/* 結構體的初始化值定義 */
#define NULLOBJ_OES_OPTION_ITEM                     \
        NULLOBJ_OES_OPTION_BASE_INFO
/* -------------------------           */


/**
 * 查詢期權產品資訊請求
 */
typedef struct _OesQryOptionReq {
    /** 查詢請求訊息頭 */
    OesQryReqHeadT      reqHead;
    /** 查詢過濾條件 */
    OesQryOptionFilterT qryFilter;
} OesQryOptionReqT;


/* 結構體的初始化值定義 */
#define NULLOBJ_OES_QRY_OPTION_REQ                  \
        {NULLOBJ_OES_QRY_REQ_HEAD}, \
        {NULLOBJ_OES_QRY_OPTION_FILTER}
/* -------------------------           */


/**
 * 查詢期權產品資訊應答
 */
typedef struct _OesQryOptionRsp {
    /** 查詢應答訊息頭 */
    OesQryRspHeadT      rspHead;
    /** 期權產品資訊陣列 */
    OesOptionItemT      qryItems[OES_MAX_OPTION_ITEM_CNT_PER_PACK];
} OesQryOptionRspT;


/* 結構體的初始化值定義 */
#define NULLOBJ_OES_QRY_OPTION_RSP                  \
        {NULLOBJ_OES_QRY_RSP_HEAD}, \
        {{NULLOBJ_OES_OPTION_ITEM}}
/* -------------------------           */


/* ===================================================================
 * 查詢當前交易日資訊相關結構體定義
 * =================================================================== */

/**
 * 查詢當前交易日資訊應答
 */
typedef struct _OesQryTradingDayRsp {
    /** 交易日 */
    int32               tradingDay;
    /** 按64位對齊填充域 */
    int32               __filler;
} OesQryTradingDayRspT;


/* 結構體的初始化值定義 */
#define NULLOBJ_OES_QRY_TRADING_DAY_RSP             \
        0, 0
/* -------------------------           */


/* ===================================================================
 * 查詢市場狀態資訊相關結構體定義
 * =================================================================== */

/**
 * 查詢市場狀態資訊過濾條件
 */
typedef struct _OesQryMarketStateFilter {
    /**
     * 交易所程式碼 (可選項, 為 0 則匹配所有交易所)
     * @see eOesExchangeIdT
     */
    uint8               exchId;

    /**
     * 交易平臺程式碼 (可選項, 為 0 則匹配所有交易平臺)
     * @see eOesPlatformIdT
     */
    uint8               platformId;

    /** 按64位對齊填充域 */
    uint8               __filler[6];

    /** 使用者私有資訊 (由客戶端自定義填充, 並在應答資料中原樣返回) */
    int64               userInfo;
} OesQryMarketStateFilterT;


/* 結構體的初始化值定義 */
#define NULLOBJ_OES_QRY_MARKET_STATE_FILTER             \
        0, 0, {0}, 0
/* -------------------------           */


/**
 * 市場狀態資訊內容
 *
 */
typedef OesMarketStateInfoT     OesMarketStateItemT;


/* 結構體的初始化值定義 */
#define NULLOBJ_OES_MARKET_STATE_ITEM                   \
        NULLOBJ_OES_MARKET_STATE_INFO
/* -------------------------           */


/**
 * 查詢市場狀態資訊請求
 */
typedef struct _OesQryMarketStateReq {
    /** 查詢請求訊息頭 */
    OesQryReqHeadT          reqHead;
    /** 查詢過濾條件 */
    OesQryMarketStateFilterT
                            qryFilter;
} OesQryMarketStateReqT;


/* 結構體的初始化值定義 */
#define NULLOBJ_OES_QRY_MARKET_STATE_REQ                \
        {NULLOBJ_OES_QRY_REQ_HEAD}, \
        {NULLOBJ_OES_QRY_MARKET_STATE_FILTER}
/* -------------------------           */


/**
 * 查詢市場狀態資訊應答
 */
typedef struct _OesQryMarketStateRsp {
    /** 查詢應答訊息頭 */
    OesQryRspHeadT          rspHead;
    /** 市場狀態資訊陣列 */
    OesMarketStateItemT     qryItems[OES_MAX_MKT_STATE_ITEM_CNT_PER_PACK];
} OesQryMarketStateRspT;


/* 結構體的初始化值定義 */
#define NULLOBJ_OES_QRY_MARKET_STATE_RSP                \
        {NULLOBJ_OES_QRY_RSP_HEAD}, \
        {{NULLOBJ_OES_MARKET_STATE_ITEM}}
/* -------------------------           */


/* ===================================================================
 * 統一的查詢訊息定義
 * =================================================================== */

/**
 * 統一的查詢請求訊息定義
 */
typedef union _OesQryReqMsg {
    OesQryOrdReqT                   qryOrd;             /**< 查詢委託資訊請求 */
    OesQryTrdReqT                   qryTrd;             /**< 查詢成交資訊請求 */
    OesQryCashAssetReqT             qryCashAsset;       /**< 查詢客戶資金資訊請求 */
    OesQryStkHoldingReqT            qryStkHolding;      /**< 查詢股票持倉資訊請求 */
    OesQryOptHoldingReqT            qryOptHolding;      /**< 查詢期權持倉資訊請求 */
    OesQryCustReqT                  qryCust;            /**< 查詢客戶資訊請求 */
    OesQryInvAcctReqT               qryInvAcct;         /**< 查詢證券賬戶請求 */
    OesQryCommissionRateReqT        qryComms;           /**< 查詢客戶佣金資訊請求 */
    OesQryFundTransferSerialReqT    qryFundTrsf;        /**< 查詢出入金資訊請求 */
    OesQryLotWinningReqT            qryLotWinning;      /**< 查詢新股配號、中籤資訊請求 */
    OesQryIssueReqT                 qryIssue;           /**< 查詢證券發行資訊請求 */
    OesQryStockReqT                 qryStock;           /**< 查詢現貨產品資訊請求 */
    OesQryEtfReqT                   qryEtf;             /**< 查詢ETF申贖產品資訊請求 */
    OesQryEtfComponentReqT          qryEtfComponent;    /**< 查詢ETF成分股資訊請求 */
    OesQryOptionReqT                qryOption;          /**< 查詢期權產品資訊請求 */
    OesQryMarketStateReqT           qryMktState;        /**< 查詢市場狀態資訊請求 */
    OesQryCounterCashReqT           qryCounterCash;     /**< 查詢主櫃資金資訊請求 */
} OesQryReqMsgT;


/* 結構體的初始化值定義 */
#define NULLOBJ_OES_QRY_REQ_MSG                         \
        {NULLOBJ_OES_QRY_ORD_REQ}
/* -------------------------           */


/**
 * 統一的查詢應答訊息定義
 */
typedef union _OesQryRspMsg {
    OesQryOrdRspT                   ordRsp;             /**< 查詢委託資訊應答 */
    OesQryTrdRspT                   trdRsp;             /**< 查詢成交資訊應答 */
    OesQryCashAssetRspT             cashAssetRsp;       /**< 查詢客戶資金資訊應答 */
    OesQryStkHoldingRspT            stkHoldingRsp;      /**< 查詢股票持倉資訊應答 */
    OesQryOptHoldingRspT            optHoldingRsp;      /**< 查詢期權持倉資訊應答 */
    OesQryCustRspT                  custRsp;            /**< 查詢客戶資訊應答W */
    OesQryInvAcctRspT               invAcctRsp;         /**< 查詢證券賬戶應答 */
    OesQryCommissionRateRspT        commsRateRsp;       /**< 查詢客戶佣金資訊應答 */
    OesQryFundTransferSerialRspT    fundTrsfRsp;        /**< 查詢出入金流水資訊應答 */
    OesQryLotWinningRspT            lotWinningRsp;      /**< 查詢新股配號、中籤資訊應答 */
    OesQryIssueRspT                 issueRsp;           /**< 查詢證券發行資訊應答 */
    OesQryStockRspT                 stockRsp;           /**< 查詢現貨產品資訊應答 */
    OesQryEtfRspT                   etfRsp;             /**< 查詢ETF申贖產品資訊應答 */
    OesQryEtfComponentRspT          etfComponentRsp;    /**< 查詢ETF成分股資訊應答 */
    OesQryOptionRspT                optionRsp;          /**< 查詢期權產品資訊應答 */
    OesQryTradingDayRspT            tradingDay;         /**< 查詢當前交易日資訊應答 */
    OesQryMarketStateRspT           mktStateRsp;        /**< 查詢市場狀態資訊應答 */
    OesClientOverviewT              clientOverview;     /**< 客戶端總覽資訊 */
    OesQryCounterCashRspT           counterCashRsp;     /**< 客戶主櫃資金資訊 */
} OesQryRspMsgT;


/* 結構體的初始化值定義 */
#define NULLOBJ_OES_QRY_RSP_MSG                         \
        {NULLOBJ_OES_QRY_ORD_RSP}
/* -------------------------           */


#ifdef __cplusplus
}
#endif

#endif  /* _OES_QRY_PACKETS_H */
