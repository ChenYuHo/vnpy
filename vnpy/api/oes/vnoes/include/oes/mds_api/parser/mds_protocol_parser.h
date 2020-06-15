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
 * @file    mds_protocol_parser.h
 *
 * 協議轉換處理
 *
 * @version 1.0 2016/2/20
 * @since   2016/1/3
 */


#ifndef _MDS_PROTOCOL_PARSER_H
#define _MDS_PROTOCOL_PARSER_H


#include    <mds_global/mds_mkt_packets.h>
#include    <sutil/net/spk_global_packet.h>


#ifdef __cplusplus
extern "C" {
#endif


/* ===================================================================
 * 訊息編碼/解碼函式宣告
 * =================================================================== */

/*
 * 請求訊息編碼處理（編碼為JSON等格式，用於向伺服器傳送請求訊息）
 */
void*               MdsParser_EncodeReq(
                            SMsgHeadT *pReqHead,
                            const MdsMktReqMsgBodyT *pReqBody,
                            char *pBuf,
                            int32 bufSize,
                            const char *pRemoteInfo);

/*
 * 請求訊息解碼處理（解碼為二進位制結構體，用於接收客戶端的請求訊息）
 */
MdsMktReqMsgBodyT*  MdsParser_DecodeReq(
                            SMsgHeadT *pReqHead,
                            const void *pMsgBody,
                            MdsMktReqMsgBodyT *pReqMsgBuf,
                            const char *pRemoteInfo);

/*
 * 應答訊息編碼處理（編碼為JSON等格式，用於向客戶端傳送應答訊息）
 */
void*               MdsParser_EncodeRsp(
                            SMsgHeadT *pRspHead,
                            const MdsMktRspMsgBodyT *pRspBody,
                            char *pBuf,
                            int32 bufSize,
                            const char *pRemoteInfo,
                            BOOL isCopyBinary);

/*
 * 應答訊息解碼處理（解碼為二進位制結構體，用於接收伺服器端返回的應答訊息）
 */
MdsMktRspMsgBodyT*  MdsParser_DecodeRsp(
                            SMsgHeadT *pRspHead,
                            const void *pMsgBody,
                            MdsMktRspMsgBodyT *pRspMsgBuf,
                            const char *pRemoteInfo);

/*
 * 返回字串形式的行情資料型別
 */
const char*         MdsParser_GetMdStreamIdString(
                            uint8 exchId,
                            uint8 mdStreamType);
/* -------------------------           */


#ifdef __cplusplus
}
#endif

#endif  /* _MDS_PROTOCOL_PARSER_H */
