/*
 * Copyright 2009-2014 the original author or authors.
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
 * @file    oes_query_json_parser.h
 *
 * 查詢訊息解析
 *
 * @version $Id$
 * @since   2014/12/26
 */


#ifndef _OES_QUERY_JSON_PARSER_H
#define _OES_QUERY_JSON_PARSER_H


#include    <oes_global/oes_packets.h>
#include    <sutil/net/spk_global_packet.h>
#include    <sutil/types.h>


#ifdef __cplusplus
extern "C" {
#endif


/* ===================================================================
 * 函式宣告
 * =================================================================== */

/* 查詢服務接收到的請求訊息解析處理 */
OesQryReqMsgT *
        OesJsonParser_DecodeQueryReq(
                SMsgHeadT *pReqHead,
                const char *pMsgBody,
                OesQryReqMsgT *pQryReq,
                const char *pRemoteInfo);

/* 查詢服務構造應答訊息處理 */
void *  OesJsonParser_EncodeQueryRsp(
                SMsgHeadT *pRspHead,
                const OesQryRspMsgT *pQryRsp,
                char *pBuf,
                int32 bufSize,
                const char *pRemoteInfo);
/* -------------------------           */


/* ===================================================================
 * 用於具體資料條目編/解碼處理的函式宣告
 * =================================================================== */

/* 編碼查詢應答條目 */
void*   OesJsonParser_EncodeQueryRspItem(
                SMsgHeadT *pRspHead,
                const void *pQryRspItem,
                char *pBuf,
                int32 bufSize);

/* 客戶端總覽資訊序列化 */
int32 JsonParser_EncodeClientOverview(
                const OesClientOverviewT *pRspItem,
                char *pBuf,
                int32 bufSize);

/* 單條委託查詢結果序列化 */
int32   JsonParser_EncodeOrdItem(
                const OesOrdItemT *pRspItem,
                char *pBuf,
                int32 bufSize);

/* 單條成交查詢結果序列化 */
int32   JsonParser_EncodeTrdItem(
                const OesTrdItemT *pRspItem,
                char *pBuf,
                int32 bufSize);

/* 單條資金查詢結果序列化 */
int32   JsonParser_EncodeCashAssetItem(
                const OesCashAssetItemT *pRspItem,
                char *pBuf,
                int32 bufSize);

/* 單條股東帳戶資訊查詢結果序列化 */
int32   JsonParser_EncodeInvAcctItem(
                const OesInvAcctItemT *pRspItem,
                char *pBuf,
                int32 bufSize);

/* 單條佣金資訊查詢結果序列化 */
int32   JsonParser_EncodeCommissionRateItem(
                const OesCommissionRateItemT *pRspItem,
                char *pBuf,
                int32 bufSize);

/* 單條出入金流水查詢結果序列化 */
int32   JsonParser_EncodeFundTransferSerialItem(
                const OesFundTransferSerialItemT *pRspItem,
                char *pBuf,
                int32 bufSize);

/* 股票持倉查詢編碼單條回報處理 */
int32   JsonParser_EncodeStkHoldingItem(
                const OesStkHoldingItemT *pRspItem,
                char *pBuf,
                int32 bufSize);

/* 期權持倉查詢編碼單條回報處理 */
int32   JsonParser_EncodeOptHoldingItem(
                const OesOptHoldingItemT *pRspItem,
                char *pBuf,
                int32 bufSize);

/* 期權持倉查詢編碼單條回報處理 */
int32   JsonParser_EncodeLotWinningItem(
                const OesLotWinningItemT *pRspItem,
                char *pBuf,
                int32 bufSize);

/* 單條證券發行資訊查詢結果序列化 */
int32   JsonParser_EncodeIssueItem(
                const OesIssueItemT *pRspItem,
                char *pBuf,
                int32 bufSize);

/* 單條股票產品資訊查詢結果序列化 */
int32   JsonParser_EncodeStockItem(
                const OesStockItemT *pRspItem,
                char *pBuf,
                int32 bufSize);

/* 客戶資訊查詢編碼單條回報處理 */
int32   JsonParser_EncodeCustItem(
                const OesCustItemT *pRspItem,
                char *pBuf,
                int32 bufSize);

/* 單條ETF產品資訊查詢結果序列化 */
int32   JsonParser_EncodeEtfItem(
                const OesEtfItemT *pRspItem,
                char *pBuf,
                int32 bufSize);

/* 單條ETF成分股資訊查詢結果序列化 */
int32   JsonParser_EncodeEtfComponentItem(
                const OesEtfComponentItemT *pRspItem,
                char *pBuf,
                int32 bufSize);

/* 單條期權產品資訊查詢結果序列化 */
int32   JsonParser_EncodeOptionItem(
                const OesOptionItemT *pRspItem,
                char *pBuf,
                int32 bufSize);

/* 單條市場狀態資訊查詢結果序列化 */
int32   JsonParser_EncodeMktStatusItem(
                const OesMarketStateItemT *pRspItem,
                char *pBuf,
                int32 bufSize);

/* 單條主櫃資金查詢結果序列化 */
int32   JsonParser_EncodeCounterCashItem(
                const OesCounterCashItemT *pRspItem,
                char *pBuf,
                int32 bufSize);
/* -------------------------           */


#ifdef __cplusplus
}
#endif

#endif  /* _OES_QUERY_JSON_PARSER_H */
