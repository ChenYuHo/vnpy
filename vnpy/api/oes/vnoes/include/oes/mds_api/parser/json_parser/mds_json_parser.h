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
 * @file    mds_json_parser.h
 *
 * 行情訂閱服務的訊息解析處理
 *
 * @version 1.0 2016/2/19
 * @since   2016/1/3
 */


#ifndef _MDS_JSON_PARSER_H
#define _MDS_JSON_PARSER_H


#include    <mds_global/mds_mkt_packets.h>
#include    <sutil/net/spk_global_packet.h>
#include    <sutil/types.h>


#ifdef __cplusplus
extern "C" {
#endif


/* ===================================================================
 * 函式宣告
 * =================================================================== */

/* 請求訊息編碼處理（用於向伺服器傳送請求訊息） */
void*   MdsJsonParser_EncodeReq(
                SMsgHeadT *pReqHead,
                const MdsMktReqMsgBodyT *pReqBody,
                char *pBuf,
                int32 bufSize,
                const char *pRemoteInfo);

/* 請求訊息解碼處理（用於接收客戶端的請求訊息） */
MdsMktReqMsgBodyT*
        MdsJsonParser_DecodeReq(
                SMsgHeadT *pReqHead,
                const void *pMsgBody,
                MdsMktReqMsgBodyT *pReqMsgBuf,
                const char *pRemoteInfo);

/* 應答訊息編碼處理（用於向客戶端傳送應答訊息） */
void*   MdsJsonParser_EncodeRsp(
                SMsgHeadT *pRspHead,
                const MdsMktRspMsgBodyT *pRspBody,
                char *pBuf,
                int32 bufSize,
                const char *pRemoteInfo);

/* 應答訊息編碼處理（編碼為精簡的JSON格式） */
void*   MdsJsonParser_EncodeRspSimplify(
                SMsgHeadT *pRspHead,
                const MdsMktRspMsgBodyT *pRspBody,
                char *pBuf,
                int32 bufSize,
                const char *pRemoteInfo);

/* 應答訊息解碼處理（用於接收伺服器端返回的應答訊息） */
MdsMktRspMsgBodyT*
        MdsJsonParser_DecodeRsp(
                SMsgHeadT *pRspHead,
                const void *pMsgBody,
                MdsMktRspMsgBodyT *pRspMsgBuf,
                const char *pRemoteInfo);
/* -------------------------           */


/* ===================================================================
 * 用於具體資料條目的編碼/解碼處理的函式宣告
 * =================================================================== */

/* 證券靜態資訊條目的編碼處理 */
int32   MdsJsonParser_EncodeStockStaticItem(
                const MdsStockStaticInfoT *pItem,
                char *pBuf,
                int32 bufSize);

/* 行情快照條目的編碼處理 */
int32   MdsJsonParser_EncodeSnapshotListItem(
                const MdsL1SnapshotT *pItem,
                char *pBuf,
                int32 bufSize);
/* -------------------------           */


#ifdef __cplusplus
}
#endif

#endif  /* _MDS_JSON_PARSER_H */
