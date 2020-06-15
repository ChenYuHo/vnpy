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
 * @file    oes_protocol_parser.h
 *
 * 協議轉換處理
 *
 * @version 1.2 2016/10/24
 * @since   2014/12/23
 */


#ifndef _OES_PROTOCOL_PARSER_H
#define _OES_PROTOCOL_PARSER_H


#include    <oes_global/oes_packets.h>
#include    <sutil/net/spk_global_packet.h>


#ifdef __cplusplus
extern "C" {
#endif


/* ===================================================================
 * 編碼/解碼函式宣告 （非查詢訊息）
 * =================================================================== */

/*
 * 請求訊息解碼處理（解碼為二進位制結構體，用於接收客戶端的請求訊息）
 */
OesReqMsgBodyT* OesParser_DecodeReq(
                        SMsgHeadT *pReqHead,
                        const void *pMsgBody,
                        OesReqMsgBodyT *pReqMsgBuf,
                        const char *pRemoteInfo);

/*
 * 應答訊息編碼處理（編碼為JSON等格式，用於向客戶端傳送應答訊息）
 */
void*           OesParser_EncodeRsp(
                        SMsgHeadT *pRspHead,
                        const OesRspMsgBodyT *pRspBody,
                        char *pBuf,
                        int32 bufSize,
                        const char *pRemoteInfo,
                        BOOL isCopyBinary);

/*
 * 為執行報告回報特別定製的應答訊息編碼處理（編碼為JSON等格式，用於向客戶端傳送應答訊息）
 */
void*           OesParser_EncodeRptSpecial(
                        SMsgHeadT *pRspHead,
                        const OesRptMsgHeadT *pRptMsgHead,
                        const OesRptMsgBodyT *pRptMsgBody,
                        char *pBuf,
                        int32 bufSize,
                        const char *pRemoteInfo,
                        BOOL isCopyBinary);
/* -------------------------           */


/* ===================================================================
 * 編碼/解碼函式宣告 （查詢訊息）
 * =================================================================== */

/*
 * 查詢服務接收訊息的解析處理
 */
OesQryReqMsgT*  OesParser_DecodeQueryReq(
                        SMsgHeadT *pReqHead,
                        const char *pMsgBody,
                        OesQryReqMsgT *pQryReq,
                        const char *pRemoteInfo);

/*
 * 查詢服務構造應答訊息處理
 */
void*           OesParser_EncodeQueryRsp(
                        SMsgHeadT *pRspHead,
                        const OesQryRspMsgT *pQryRsp,
                        char *pBuf, int32 bufSize,
                        const char *pRemoteInfo);
/* -------------------------           */


#ifdef __cplusplus
}
#endif

#endif  /* _OES_PROTOCOL_PARSER_H */
