/*
 * Copyright 2009-2016 the original author or authors.
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
 * @file    global_packet.h
 *
 * 全域性報文定義
 *
 * @version 1.0         2009/10/18
 * @version 1.5         2018/05/03
 *          - 新增新的訊息標誌:
 *              - SMSG_MSGFLAG_NESTED       巢狀的組合訊息 (訊息體由一到多條包含訊息頭的完整訊息組成)
 *              - SMSG_MSGFLAG_COMPRESSED   訊息體已壓縮
 *          - 新增通用的輔助巨集定義
 * @since   2009/10/18
 */


#ifndef _SPK_GLOBAL_PACKET_H
#define _SPK_GLOBAL_PACKET_H


#include    <sutil/types.h>


#ifdef __cplusplus
extern "C" {
#endif


/* ===================================================================
 * 訊息標誌定義
 * =================================================================== */

/**
 * 協議型別，用於在訊息標誌中標識訊息的協議型別
 */
typedef enum _eSMsgProtocolType {
    SMSG_PROTO_BINARY           = 0x00,     /**< 協議型別-二進位制 */
    SMSG_PROTO_JSON             = 0x01,     /**< 協議型別-JSON */
    SMSG_PROTO_FIX              = 0x02,     /**< 協議型別-FIX */
    SMSG_PROTO_PROTOBUF         = 0x03,     /**< 協議型別-ProtocolBuffers */
    __MAX_SMSG_PROTO_TYPE
} eSMsgProtocolTypeT;
/* -------------------------           */


/**
 * 訊息標誌，用於在訊息標誌中標識訊息的請求/應答型別
 * 與協議型別複用相同的欄位，通過高4位/低4位進行區分
 */
typedef enum _eSMsgFlag {
    SMSG_MSGFLAG_NONE           = 0x00,     /**< 訊息標誌-無 */
    SMSG_MSGFLAG_REQ            = 0x00,     /**< 訊息標誌-請求訊息 */
    SMSG_MSGFLAG_RSP            = 0x50,     /**< 訊息標誌-應答訊息 TODO refactor => 0x10 */
    SMSG_MSGFLAG_NESTED         = 0x20,     /**< 訊息標誌-巢狀的組合訊息 (訊息體由一到多條包含訊息頭的完整訊息組成) */
    SMSG_MSGFLAG_COMPRESSED     = 0x80,     /**< 訊息標誌-訊息體已壓縮 */

    SMSG_MSGFLAG_MASK_RSPFLAG   = 0xF0,     /**< 訊息標誌掩碼-請求/應答標誌的掩碼 */
    SMSG_MSGFLAG_MASK_PROTOCOL  = 0x0F      /**< 訊息標誌掩碼-協議型別的掩碼 */
} eSMsgFlagT;
/* -------------------------           */


/* ===================================================================
 * 通用訊息頭定義
 * =================================================================== */

/**
 * 通用訊息頭
 * @see eSMsgFlagT
 */
typedef struct _SMsgHead {
    uint8               msgFlag;            /**< 訊息標誌 @see eSMsgFlagT */
    uint8               msgId;              /**< 訊息程式碼 */
    uint8               status;             /**< 狀態碼 */
    uint8               detailStatus;       /**< 明細狀態程式碼 (@note 當訊息為巢狀的組合訊息時, 複用該欄位記錄訊息體中的訊息條數) */
    int32               msgSize;            /**< 訊息大小 */
} SMsgHeadT;


/* 訊息頭尾部填充欄位的初始化值定義 (@deprecated 已廢棄, 為了相容而暫時保留) */
#define __NULLOBJ_SPK_MSG_HEAD_TAILER


/* 結構體初始化值定義 */
#define NULLOBJ_SPK_MSG_HEAD                \
        0, 0, 0, 0, 0
/* -------------------------           */


/* ===================================================================
 * 通用的輔助巨集定義
 * =================================================================== */

/**
 * 返回訊息的協議型別
 *
 * @param   msgFlag 訊息標誌
 * @return  訊息的協議型別 @see eSMsgProtocolTypeT
 */
#define SPK_GET_MSG_PROTOCOL_TYPE(msgFlag)          \
        ( (msgFlag) & SMSG_MSGFLAG_MASK_PROTOCOL )


/**
 * 返回訊息的協議型別是否是'BINARY'型別
 *
 * @param   msgFlag 訊息標誌
 * @return  TRUE 是'BINARY'型別; FALSE 不是'BINARY'型別
 */
#define SPK_IS_MSG_PROTOCOL_BINARY(msgFlag)         \
        ( SPK_GET_MSG_PROTOCOL_TYPE(msgFlag) == SMSG_PROTO_BINARY )


/**
 * 返回訊息的協議型別是否是'JSON'型別
 *
 * @param   msgFlag 訊息標誌
 * @return  TRUE 是'JSON'型別; FALSE 不是'JSON'型別
 */
#define SPK_IS_MSG_PROTOCOL_JSON(msgFlag)           \
        ( SPK_GET_MSG_PROTOCOL_TYPE(msgFlag) == SMSG_PROTO_JSON )
/* -------------------------           */


/**
 * 返回訊息是否是應答訊息
 *
 * @param   msgFlag 訊息標誌
 * @return  TRUE 是應答訊息; FALSE 不是應答訊息
 */
#define SPK_HAS_MSG_FLAG_RSP(msgFlag)               \
        ( ((msgFlag) & SMSG_MSGFLAG_RSP) == SMSG_MSGFLAG_RSP )


/**
 * 返回訊息是否是巢狀的組合訊息 (訊息體由一到多條包含訊息頭的完整訊息組成)
 *
 * @param   msgFlag 訊息標誌
 * @return  TRUE 是巢狀的組合訊息; FALSE 不是巢狀的組合訊息
 */
#define SPK_HAS_MSG_FLAG_NESTED(msgFlag)            \
        ( ((msgFlag) & SMSG_MSGFLAG_NESTED) == SMSG_MSGFLAG_NESTED )


/**
 * 返回訊息是否已壓縮
 *
 * @param   msgFlag 訊息標誌
 * @return  TRUE 已壓縮; FALSE 未壓縮
 */
#define SPK_HAS_MSG_FLAG_COMPRESSED(msgFlag)        \
        ( ((msgFlag) & SMSG_MSGFLAG_COMPRESSED) == SMSG_MSGFLAG_COMPRESSED )
/* -------------------------           */


#ifdef __cplusplus
}
#endif

#endif  /* _SPK_GLOBAL_PACKET_H */
