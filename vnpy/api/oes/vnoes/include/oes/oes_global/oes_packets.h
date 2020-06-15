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
 * @file    oes_packets.h
 *
 * 訂單執行系統訂單接收模組通訊報文定義
 *
 * @version 0.11.1      2016/11/17
 * @version 0.12        2016/11/30
 *          - 在登入報文中增加協議版本號資訊, 並在登入時校驗協議版本號的相容性
 * @version 0.12.3      2017/01/10
 *          - 新增期權持倉查詢的訊息型別
 *          - 調整查詢類訊息型別的取值定義
 * @version 0.12.6.2    2017/03/16
 *          - 重新命名 ‘出入金委託’ 訊息 OESMSG_NONTRD_CASH_TRSF_REQ => OESMSG_NONTRD_FUND_TRSF_REQ
 *          - 新增 ‘出入金委託響應-業務拒絕’、‘出入金委託執行報告’ 兩類回報訊息
 *          - 刪除 ‘出入金管理登入訊息’ 巨集定義
 *          - 重新命名 ‘出入金委託’訊息的結構體定義 OesCashTrsfReqT => OesFundTrsfReqT
 * @version 0.15.2      2017/07/18
 *          - 新增 查詢新股配號、中籤資訊訊息型別定義(OESMSG_QRYMSG_LOT_WINNING)
 * @version 0.15.2.1    2017/07/31
 *          - 出入金業務拒絕訊息型別變更 OesFundTrsfReqT => OesFundTrsfRejectT
 *          - 出入金委託回報的結構體(OesFundTrsfReportT) 中新增欄位 '錯誤碼資訊 (rejReasonInfo)'
 * @version 0.15.4      2017/09/04
 *          - 新增交易類請求訊息 '撤單請求訊息 (OESMSG_ORD_CANCEL_REQUEST)'
 *          - 新增結構體 '撤單請求 (OesOrdCancelReqT)'
 *          - 新增回報訊息型別 '撤單拒絕 (OESMSG_RPT_CANCEL_REJECT)'
 *              - 對應回報訊息 OesRptMsgBodyT.cancelRejectRsp
 *          - 委託拒絕訊息中將不再包含撤單委託, 所有被OES拒絕的撤單請求和撤單委託都將通過新增的撤單拒絕訊息進行回報
 *          - 新增回報訊息型別 '資金變動資訊 (OESMSG_RPT_CASH_ASSET_VARIATION)'
 *              - 對應回報訊息 OesRptMsgBodyT.cashAssetRpt
 *          - 新增回報訊息型別 '持倉變動資訊 (股票) (OESMSG_RPT_STOCK_HOLDING_VARIATION)'
 *              - 對應回報訊息 OesRptMsgBodyT.stkHoldingRpt
 *          - 新增回報訊息型別 '持倉變動資訊 (期權) (OESMSG_RPT_OPTION_HOLDING_VARIATION)'
 *              - 對應回報訊息 OesRptMsgBodyT.optHoldingRpt
 * @version 0.15.4.1    2017/09/07
 *          - 調整回報訊息型別的定義順序和取值
 *              - OESMSG_RPT_ORDER_INSERT, OESMSG_RPT_ORDER_REJECT, OESMSG_RPT_CANCEL_REJECT
 *          - 登入應答報文(OesLogonRspT) 中增加欄位 客戶端環境號(clEnvId)
 * @version 0.15.4.2    2017/10/16
 *          - 新增交易類請求訊息 '測試請求 (OesTestRequestReqT)'
 *          - 新增回報訊息型別 '測試請求的應答 (OesTestRequestRspT)'
 * @version 0.15.5      2017/11/03
 *          - 刪除回報訊息型別 '撤單拒絕 (OESMSG_RPT_CANCEL_REJECT)', 並整合到 '委託拒絕 (OESMSG_RPT_ORDER_REJECT)' 訊息中
 *          - 重新命名回報訊息型別 OESMSG_RPT_ORDER_REJECT => OESMSG_RPT_BUSINESS_REJECT (OES業務拒絕, 委託/撤單未通過風控檢查等)
 *          - 增加可訂閱的回報訊息型別 OES_SUB_RPT_TYPE_BUSINESS_REJECT
 *          - 當前採用的協議版本號(OES_APPL_VER_ID) 升級到 0.15.5
 *          - 相容最低的協議版本號(OES_MIN_APPL_VER_ID) 升級到 0.15.5
 * @version 0.15.5.1    2017/11/15
 *          - 增加數值型別的協議版本號 OES_APPL_VER_VALUE, 以方便比對版本
 * @version 0.15.6      2018/03/28
 *          - 增加修改密碼請求/應答報文和訊息程式碼定義
 *          - 增加批量委託請求報文和訊息程式碼定義
 *          - 登入請求報文(OesLogonReqT) 中增加欄位 客戶端裝置序列號(clientDriverId)
 *          - 增加預設回報訊息型別 OES_SUB_RPT_TYPE_DEFAULT
 *          - 新增回報訊息型別 '市場狀態資訊 (OESMSG_RPT_MARKET_STATE)'
 *              - 對應回報訊息 OesRspMsgBodyT.mktStateRpt
 *          - 回報訊息頭(OesRptMsgHeadT) 中增加欄位 執行型別(execType), 用以區分回報的執行型別(參考eOesExecTypeT定義）
 * @version 0.15.5.13   2018/07/20
 *          - 登入應答報文(OesLogonRspT) 中增加欄位:
 *              - 客戶端型別 (clientType)
 *              - 客戶端狀態 (clientStatus)
 * @version 0.15.5.16   2018/08/31
 *          - 登入應答報文(OesLogonRspT) 中增加欄位:
 *              - 客戶端型別(clientType)
 *              - 客戶端狀態(clientStatus)
 *          - 新增 查詢客戶端總覽資訊(OESMSG_QRYMSG_CLIENT_OVERVIEW) 訊息型別定義
 *          - 新增 查詢客戶主櫃資金資訊(OESMSG_QRYMSG_COUNTER_CASH) 訊息型別定義
 * @version 0.15.5.17   2018/11/23
 *          - 登入應答報文(OesLogonRspT) 中增加欄位:
 *              - 服務端叢集號(setNum)
 * @version 0.15.7.6    2018/11/03
 *          - 新增 OES服務狀態回報訊息型別(OESMSG_RPT_SERVICE_STATE)，暫不支援訂閱推送
 * @version 0.15.9      2018/03/12
 *          - 為了支援科創板, 新增以下查詢訊息型別 (相容之前版本的API)
 *              - 查詢證券賬戶資訊 (OESMSG_QRYMSG_INV_ACCT)
 *              - 查詢現貨產品資訊 (OESMSG_QRYMSG_STOCK)
 *
 * @since   2015/07/30
 */


#ifndef _OES_PACKETS_H
#define _OES_PACKETS_H


#include    <oes_global/oes_base_model.h>
#include    <oes_global/oes_qry_packets.h>
#include    <sutil/net/spk_global_packet.h>


#ifdef __cplusplus
extern "C" {
#endif


/* ===================================================================
 * 協議版本號定義
 * =================================================================== */

/** 當前採用的協議版本號 */
#define OES_APPL_VER_ID                         "0.15.9"

/**
 * 當前採用的協議版本號數值
 * - 版本號數值的格式為 10 位整型數值, 形如: 1AABBCCDDX, 其中:
 *   - AA 為主版本號
 *   - BB 為副版本號
 *   - CC 為釋出號
 *   - DD 為構建號
 *   - X  0, 表示不帶時間戳的正常版本; 1, 表示帶時間戳的延遲測量版本
 */
#define OES_APPL_VER_VALUE                      (1001509001)

/** 相容的最低協議版本號 */
#define OES_MIN_APPL_VER_ID                     "0.15.5"
/* -------------------------           */


/* ===================================================================
 * 訊息程式碼及報文中的列舉型別定義
 * =================================================================== */

/**
 * 通訊訊息的訊息型別定義
 */
typedef enum _eOesMsgType {
    /*
     * 交易類訊息
     */
    OESMSG_ORD_NEW_ORDER                        = 0x01,     /**< 0x01/01  委託申報訊息 */
    OESMSG_ORD_CANCEL_REQUEST                   = 0x02,     /**< 0x02/02  撤單請求訊息 */
    OESMSG_ORD_BATCH_ORDERS                     = 0x03,     /**< 0x03/03  批量委託訊息 */
    __OESMSG_ORD_MAX,                                       /**< 最大的委託訊息型別 */

    /*
     * 執行報告類訊息
     */
    __OESMSG_RPT_MIN                            = 0x0F,     /**< 0x0F/15  最小的執行報告訊息型別 */
    OESMSG_RPT_MARKET_STATE                     = 0x10,     /**< 0x10/16  市場狀態資訊 */
    OESMSG_RPT_REPORT_SYNCHRONIZATION           = 0x11,     /**< 0x11/17  回報同步的應答訊息 */

    OESMSG_RPT_BUSINESS_REJECT                  = 0x12,     /**< 0x12/18  OES業務拒絕 (因未通過風控檢查等原因而被OES拒絕) */
    OESMSG_RPT_ORDER_INSERT                     = 0x13,     /**< 0x13/19  OES委託已生成 (已通過風控檢查) */
    OESMSG_RPT_ORDER_REPORT                     = 0x14,     /**< 0x14/20  交易所委託回報 (包括交易所委託拒絕、委託確認和撤單完成通知) */
    OESMSG_RPT_TRADE_REPORT                     = 0x15,     /**< 0x15/21  交易所成交回報 */

    OESMSG_RPT_FUND_TRSF_REJECT                 = 0x16,     /**< 0x16/22  出入金委託拒絕 */
    OESMSG_RPT_FUND_TRSF_REPORT                 = 0x17,     /**< 0x17/23  出入金委託執行報告 */

    OESMSG_RPT_CASH_ASSET_VARIATION             = 0x18,     /**< 0x18/24  資金變動資訊 */
    OESMSG_RPT_STOCK_HOLDING_VARIATION          = 0x19,     /**< 0x19/25  持倉變動資訊 (股票) */
    OESMSG_RPT_OPTION_HOLDING_VARIATION         = 0x1A,     /**< 0x1A/26  持倉變動資訊 (期權) */
    OESMSG_RPT_SERVICE_STATE                    = 0x1B,     /**< 0x1B/27  OES服務狀態資訊 (暫不支援訂閱推送) */
    __OESMSG_RPT_MAX,                                       /**< 最大的回報訊息型別 */

    /*
     * 非交易類訊息
     */
    __OESMSG_NONTRD_MIN                         = 0x20,     /**< 0x20/32  最小的非交易訊息型別 */
    OESMSG_NONTRD_FUND_TRSF_REQ                 = 0x21,     /**< 0x21/33  出入金委託 */
    OESMSG_NONTRD_CHANGE_PASSWORD               = 0x22,     /**< 0x22/34  修改客戶端登入密碼 */
    __OESMSG_NONTRD_MAX,                                    /**< 最大的非交易訊息型別 */

    /*
     * 查詢類訊息
     */
    __OESMSG_QRYMSG_MIN                         = 0x2F,     /**< 0x2F/47  最小的查詢訊息型別 */
    OESMSG_QRYMSG_CLIENT_OVERVIEW               = 0x30,     /**< 0x30/48  查詢客戶端總覽資訊 */
    OESMSG_QRYMSG_ORD                           = 0x31,     /**< 0x31/49  查詢委託資訊 */
    OESMSG_QRYMSG_TRD                           = 0x32,     /**< 0x32/50  查詢成交資訊 */
    OESMSG_QRYMSG_CASH_ASSET                    = 0x33,     /**< 0x33/51  查詢客戶資金資訊 */
    OESMSG_QRYMSG_STK_HLD                       = 0x34,     /**< 0x34/52  查詢股票持倉資訊 */
    OESMSG_QRYMSG_OPT_HLD                       = 0x35,     /**< 0x35/53  查詢期權持倉資訊 */
    OESMSG_QRYMSG_CUST                          = 0x36,     /**< 0x36/54  查詢客戶資訊 */
    OESMSG_QRYMSG_COMMISSION_RATE               = 0x38,     /**< 0x38/56  查詢客戶佣金資訊 */
    OESMSG_QRYMSG_FUND_TRSF                     = 0x39,     /**< 0x39/57  查詢出入金資訊 */
    OESMSG_QRYMSG_ETF                           = 0x3B,     /**< 0x3B/59  查詢ETF申贖產品資訊 */
    OESMSG_QRYMSG_ETF_COMPONENT                 = 0x3C,     /**< 0x3C/60  查詢ETF成分股資訊 */
    OESMSG_QRYMSG_OPTION                        = 0x3D,     /**< 0x3D/61  查詢期權產品資訊 */
    OESMSG_QRYMSG_ISSUE                         = 0x3E,     /**< 0x3E/62  查詢證券發行資訊 */
    OESMSG_QRYMSG_LOT_WINNING                   = 0x3F,     /**< 0x3F/63  查詢新股配號、中籤資訊 */
    OESMSG_QRYMSG_TRADING_DAY                   = 0x40,     /**< 0x40/64  查詢當前交易日 */
    OESMSG_QRYMSG_MARKET_STATE                  = 0x41,     /**< 0x41/65  查詢市場狀態 */
    OESMSG_QRYMSG_COUNTER_CASH                  = 0x42,     /**< 0x42/66  查詢客戶主櫃資金資訊 */

    OESMSG_QRYMSG_INV_ACCT                      = 0x51,     /**< 0x51/81  查詢證券賬戶資訊 (0x37的更新版本, @since 0.15.9) */
    OESMSG_QRYMSG_STOCK                         = 0x52,     /**< 0x52/82  查詢現貨產品資訊 (0x3A的更新版本, @since 0.15.9) */
    __OESMSG_QRYMSG_MAX,                                    /**< 最大的查詢訊息型別 */

    /*
     * 公共的會話類訊息
     */
    OESMSG_SESS_HEARTBEAT                       = 0xFA,     /**< 0xFA/250 心跳訊息 */
    OESMSG_SESS_TEST_REQUEST                    = 0xFB,     /**< 0xFB/251 測試請求訊息 */
    OESMSG_SESS_LOGIN_EXTEND                    = 0xFC,     /**< 0xFC/252 登入擴充套件訊息 */
    OESMSG_SESS_LOGOUT                          = 0xFE,     /**< 0xFE/254 登出訊息 */

    /*
     * 以下訊息型別定義已廢棄, 只是為了相容之前的版本而暫時保留
     */
    OESMSG_RPT_ORDER_REJECT                     = OESMSG_RPT_BUSINESS_REJECT,

    OESMSG_QRYMSG_INV_ACCT_L001508              = 0x37,     /**< 0x37/55  查詢證券賬戶資訊 (相容 v0.15.8 以及 v0.15.8 之前的版本的訊息型別) */
    OESMSG_QRYMSG_STOCK_L001508                 = 0x3A      /**< 0x3A/58  查詢現貨產品資訊 (相容 v0.15.8 以及 v0.15.8 之前的版本的訊息型別) */

} eOesMsgTypeT;
/* -------------------------           */


/**
 * 可訂閱的回報訊息型別定義
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
 */
typedef enum _eOesSubscribeReportType {
    /** 預設回報 */
    OES_SUB_RPT_TYPE_DEFAULT                    = 0,

    /** OES業務拒絕 (未通過風控檢查等) */
    OES_SUB_RPT_TYPE_BUSINESS_REJECT            = 0x01,

    /** OES委託已生成 (已通過風控檢查) */
    OES_SUB_RPT_TYPE_ORDER_INSERT               = 0x02,

    /** 交易所委託回報 (包括交易所委託拒絕、委託確認和撤單完成通知) */
    OES_SUB_RPT_TYPE_ORDER_REPORT               = 0x04,

    /** 交易所成交回報 */
    OES_SUB_RPT_TYPE_TRADE_REPORT               = 0x08,

    /** 出入金委託執行報告 (包括出入金委託拒絕、出入金委託回報) */
    OES_SUB_RPT_TYPE_FUND_TRSF_REPORT           = 0x10,

    /** 資金變動資訊 */
    OES_SUB_RPT_TYPE_CASH_ASSET_VARIATION       = 0x20,

    /** 持倉變動資訊 */
    OES_SUB_RPT_TYPE_HOLDING_VARIATION          = 0x40,

    /** 市場狀態資訊 */
    OES_SUB_RPT_TYPE_MARKET_STATE               = 0x80,

    /** 所有回報 */
    OES_SUB_RPT_TYPE_ALL                        = 0xFFFF,

    __MAX_OES_SUB_RPT_TYPE                      = 0x7FFFFFFF
} eOesSubscribeReportTypeT;
/* -------------------------           */


/**
 * 可指定的協議約定型別定義
 * - 0:     預設的協議約定型別
 * - 0x80:  約定以壓縮方式傳輸資料
 * - 0xFF:  無任何協議約定
 */
typedef enum _eOesProtocolHintsType {
    /** 預設的協議約定型別 */
    OES_PROT_HINTS_TYPE_DEFAULT                 = 0,

    /** 協議約定以壓縮方式傳輸資料 */
    OES_PROT_HINTS_TYPE_COMPRESS                = 0x80,

    /** 無任何協議約定 */
    OES_PROT_HINTS_TYPE_NONE                    = 0xFF,
    __MAX_OES_PROT_HINTS_TYPE                   = 0xFF
} eOesProtocolHintsTypeT;
/* -------------------------           */


/* ===================================================================
 * 會話訊息報文定義
 * =================================================================== */

/**
 * 回報同步請求訊息
 */
typedef struct _OesReportSynchronizationReq {
    /**
     * 客戶端最後接收到的回報資料的回報編號
     * - 等於0, 從頭開始推送回報資料
     * - 大於0, 從指定的回報編號開始推送回報資料
     * - 小於0, 從最新的資料開始推送回報資料
     */
    int64               lastRptSeqNum;

    /**
     * 待訂閱的客戶端環境號
     * - 大於0, 區分環境號, 僅訂閱環境號對應的回報資料
     * - 小於等於0, 不區分環境號, 訂閱該客戶下的所有回報資料
     */
    int8                subscribeEnvId;

    /** 按64位對齊的填充域 */
    uint8               __filler[3];

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
    int32               subscribeRptTypes;
} OesReportSynchronizationReqT;


/* 結構體的初始化值定義 */
#define NULLOBJ_OES_REPORT_SYNCHRONIZATION_REQ  \
        0, 0, {0}, 0
/* -------------------------           */


/**
 * 回報同步應答訊息
 */
typedef struct _OesReportSynchronizationRsp {
    /** 服務端最後已傳送或已忽略的回報資料的回報編號 */
    int64               lastRptSeqNum;

    /**
     * 待訂閱的客戶端環境號
     * - 大於0, 區分環境號, 僅訂閱環境號對應的回報資料
     * - 小於等於0, 不區分環境號, 訂閱該客戶下的所有回報資料
     */
    int8                subscribeEnvId;

    /** 按64位對齊的填充域 */
    uint8               __filler[3];

    /** 已訂閱的回報訊息種類 */
    int32               subscribeRptTypes;
} OesReportSynchronizationRspT;


/* 結構體的初始化值定義 */
#define NULLOBJ_OES_REPORT_SYNCHRONIZATION_RSP  \
        0, 0, {0}, 0
/* -------------------------           */


/**
 * 測試請求報文
 */
typedef struct _OesTestRequestReq {
    /** 測試請求識別符號 */
    char                testReqId[OES_MAX_TEST_REQ_ID_LEN];

    /** 傳送時間 (timeval結構或形如'YYYYMMDD-HH:mm:SS.sss'的字串) */
    char                sendTime[OES_MAX_SENDING_TIME_LEN];

    /** 按64位對齊的填充域 */
    char                __filler[2];
} OesTestRequestReqT;


/* 結構體的初始化值定義 */
#define NULLOBJ_OES_TEST_REQUEST_REQ            \
        {0}, {0}, {0}
/* -------------------------           */


/**
 * 測試請求的應答報文
 */
typedef struct _OesTestRequestRsp {
    /** 測試請求識別符號 */
    char                testReqId[OES_MAX_TEST_REQ_ID_LEN];

    /** 測試請求的原始傳送時間 (timeval結構或形如'YYYYMMDD-HH:mm:SS.sss'的字串) */
    char                origSendTime[OES_MAX_SENDING_TIME_LEN];

    /** 按64位對齊的填充域 */
    char                __filler1[2];

    /** 測試請求應答的傳送時間 (timeval結構或形如'YYYYMMDD-HH:mm:SS.sss'的字串) */
    char                respTime[OES_MAX_SENDING_TIME_LEN];

    /** 按64位對齊的填充域 */
    char                __filler2[2];

#ifdef  _OES_EXPORT_LATENCY_STATS
    /** 訊息實際接收時間 (開始解碼等處理之前的時間) */
    STimeval32T         __recvTime;
    /** 訊息採集處理完成時間 */
    STimeval32T         __collectedTime;
    /** 訊息推送時間 (寫入推送快取以後, 實際網路傳送之前) */
    STimeval32T         __pushingTime;
#endif

} OesTestRequestRspT;


/* 結構體初始化值的尾部填充欄位定義 */
#ifdef  _OES_EXPORT_LATENCY_STATS
# define    __NULLOBJ_OES_TEST_REQUEST_RSP_TAILER       \
            , {0, 0}, {0, 0}, {0, 0}
#else
# define    __NULLOBJ_OES_TEST_REQUEST_RSP_TAILER
#endif


/* 結構體的初始化值定義 */
#define NULLOBJ_OES_TEST_REQUEST_RSP                    \
        {0}, {0}, {0}, {0}, {0} \
        __NULLOBJ_OES_TEST_REQUEST_RSP_TAILER
/* -------------------------           */


/**
 * 修改密碼請求報文
 */
typedef struct _OesChangePasswordReq {
    /** 加密方法 */
    int32               encryptMethod;
    /** 按64位對齊的填充域 */
    int32               __filler;

    /** 登入使用者名稱 */
    char                username[OES_CLIENT_NAME_MAX_LEN];

    /** 使用者私有資訊 (由客戶端自定義填充, 並在回報資料中原樣返回) */
    union {
        uint64          u64;                    /**< uint64 型別的使用者私有資訊 */
        int64           i64;                    /**< int64 型別的使用者私有資訊 */
        uint32          u32[2];                 /**< uint32[2] 型別的使用者私有資訊 */
        int32           i32[2];                 /**< int32[2] 型別的使用者私有資訊 */
        char            c8[8];                  /**< char[8] 型別的使用者私有資訊 */
    } userInfo;

    /** 之前的登入密碼 */
    char                oldPassword[OES_PWD_MAX_LEN];

    /** 新的登入密碼 */
    char                newPassword[OES_PWD_MAX_LEN];
} OesChangePasswordReqT;


/* 結構體的初始化值定義 */
#define NULLOBJ_OES_CHANGE_PASSWORD_REQ         \
        0, 0, \
        {0}, {0}, \
        {0}, {0}
/* -------------------------           */


/**
 * 修改密碼應答報文
 */
typedef struct _OesChangePasswordRsp {
    /** 加密方法 */
    int32               encryptMethod;
    /** 按64位對齊的填充域 */
    int32               __filler;

    /** 登入使用者名稱 */
    char                username[OES_CLIENT_NAME_MAX_LEN];

    /** 使用者私有資訊 (由客戶端自定義填充, 並在應答資料中原樣返回) */
    union {
        uint64          u64;                    /**< uint64 型別的使用者私有資訊 */
        int64           i64;                    /**< int64 型別的使用者私有資訊 */
        uint32          u32[2];                 /**< uint32[2] 型別的使用者私有資訊 */
        int32           i32[2];                 /**< int32[2] 型別的使用者私有資訊 */
        char            c8[8];                  /**< char[8] 型別的使用者私有資訊 */
    } userInfo;

    /** 客戶端編號 */
    int16               clientId;
    /** 客戶端環境號 */
    int8                clEnvId;
    /** 按64位對齊的填充域 */
    int8                __filler2;

    /** 發生日期 (格式為 YYYYMMDD, 形如 20160830) */
    int32               transDate;
    /** 發生時間 (格式為 HHMMSSsss, 形如 141205000) */
    int32               transTime;
    /** 拒絕原因 */
    int32               rejReason;
} OesChangePasswordRspT;


/* 結構體的初始化值定義 */
#define NULLOBJ_OES_CHANGE_PASSWORD_RSP         \
        0, 0, \
        {0}, {0}, \
        0, 0, 0, \
        0, 0, 0
/* -------------------------           */


/**
 * 批量委託請求的訊息頭
 */
typedef struct _OesBatchOrdersHead {
    /** 本批次的委託請求數量 */
    int32               itemCount;
    /** 按64位對齊的填充域 */
    int32               __filler;
} OesBatchOrdersHeadT;


/**
 * 批量委託請求的完整請求報文
 * (只有請求報文, 沒有獨立的應答報文)
 */
typedef struct _OesBatchOrdersReq {
    /** 批量委託請求的批次訊息頭 */
    OesBatchOrdersHeadT batchHead;

    /** 委託請求列表 */
    OesOrdReqT          items[1];
} OesBatchOrdersReqT;


/* 結構體的初始化值定義 */
#define NULLOBJ_OES_BATCH_ORDERS_HEAD           \
        0, 0

/* 結構體的初始化值定義 */
#define NULLOBJ_OES_BATCH_ORDERS_REQ            \
        {NULLOBJ_OES_BATCH_ORDERS_HEAD}, \
        {{NULLOBJ_OES_ORD_REQ}}
/* -------------------------           */


/* ===================================================================
 * 回報訊息定義
 * =================================================================== */

/**
 * 回報訊息的訊息頭定義
 */
typedef struct _OesRptMsgHead {
    int64               rptSeqNum;              /**< 執行報告的訊息編號 */

    uint8               rptMsgType;             /**< 回報訊息的訊息程式碼 @see eOesMsgTypeT */
    uint8               execType;               /**< 執行型別 @see eOesExecTypeT */
    int16               bodyLength;             /**< 回報訊息的訊息體大小 */

    int32               ordRejReason;           /**< 訂單/撤單被拒絕原因 */
} OesRptMsgHeadT;


/* 結構體的初始化值定義 */
#define NULLOBJ_OES_RPT_MSG_HEAD                \
        0, 0, 0, 0, 0
/* -------------------------           */


/**
 * 回報訊息的訊息體定義
 */
typedef union _OesRptMsgBody {
    OesOrdCnfmT         ordInsertRsp;           /**< OES委託響應-委託已生成 */
    OesOrdRejectT       ordRejectRsp;           /**< OES委託響應-業務拒絕 */

    OesOrdCnfmT         ordCnfm;                /**< 交易所委託回報 */
    OesTrdCnfmT         trdCnfm;                /**< 交易所成交回報 */

    OesFundTrsfRejectT  fundTrsfRejectRsp;      /**< 出入金委託拒絕 */
    OesFundTrsfReportT  fundTrsfCnfm;           /**< 出入金執行報告 */

    OesCashAssetItemT   cashAssetRpt;           /**< 資金變動資訊 */
    OesStkHoldingItemT  stkHoldingRpt;          /**< 持倉變動資訊 (股票) */
    OesOptHoldingItemT  optHoldingRpt;          /**< 持倉變動資訊 (期權) */

} OesRptMsgBodyT;


/* 結構體的初始化值定義 */
#define NULLOBJ_OES_RPT_MSG_BODY                \
        {NULLOBJ_OES_ORD_CNFM}
/* -------------------------           */


/**
 * 完整的回報訊息定義
 */
typedef struct _OesRptMsg {
    OesRptMsgHeadT      rptHead;
    OesRptMsgBodyT      rptBody;
} OesRptMsgT;


/* 結構體的初始化值定義 */
#define NULLOBJ_OES_RPT_MSG                     \
        {NULLOBJ_OES_RPT_MSG_HEAD}, \
        {NULLOBJ_OES_RPT_MSG_BODY}
/* -------------------------           */


/* ===================================================================
 * 彙總的請求/應答訊息定義 (除了查詢訊息以外的所有其它訊息)
 * =================================================================== */

/**
 * 彙總的請求訊息的訊息體定義
 */
typedef union _OesReqMsgBody {
    /** 委託申報請求報文 */
    OesOrdReqT          ordReq;

    /** 撤單請求請求報文 */
    OesOrdCancelReqT    ordCancelReq;

    /** 批量委託請求報文 */
    OesBatchOrdersReqT  batchOrdersReq;

    /** 出入金請求報文 */
    OesFundTrsfReqT     fundTrsfReq;

    /** 修改密碼請求報文 */
    OesChangePasswordReqT
                        changePasswordReq;

    /** 測試請求報文 */
    OesTestRequestReqT  testRequestReq;

    /** 回報同步請求報文 */
    OesReportSynchronizationReqT
                        rptSyncReq;
} OesReqMsgBodyT;


/* 結構體的初始化值定義 */
#define NULLOBJ_OES_REQ_MSG_BODY                \
        {NULLOBJ_OES_ORD_REQ}
/* -------------------------           */


/**
 * 彙總的應答訊息的訊息體定義
 */
typedef union _OesRspMsgBody {
    /** 執行報告回報訊息 */
    OesRptMsgT          rptMsg;

    /** 市場狀態訊息 */
    OesMarketStateInfoT mktStateRpt;

    /** 修改密碼應答報文 */
    OesChangePasswordRspT
                        changePasswordRsp;

    /** 測試請求的應答報文 */
    OesTestRequestRspT  testRequestRsp;

    /** 回報同步應答報文 */
    OesReportSynchronizationRspT
                        reportSynchronizationRsp;
} OesRspMsgBodyT;


/* 結構體的初始化值定義 */
#define NULLOBJ_OES_RSP_MSG_BODY                \
        {NULLOBJ_OES_RPT_MSG}
/* -------------------------           */


#ifdef __cplusplus
}
#endif

#endif  /* _OES_PACKETS_H */
