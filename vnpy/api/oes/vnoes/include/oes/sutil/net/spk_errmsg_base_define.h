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
 * @file    errmsg_base_define.h
 *
 * 基礎通訊介面錯誤資訊定義
 *
 * @version 1.0 2008/7/16
 * @since   2004.12.23
 */


#ifndef _SPK_ERRMSG_BASE_DEFINE_H
#define _SPK_ERRMSG_BASE_DEFINE_H


#include    <sutil/types.h>


#ifdef __cplusplus
extern "C" {
#endif


/* ===================================================================
 * 常量定義
 * =================================================================== */

/** 錯誤資訊的最大長度 */
#define SPK_MAX_ERRMSG_LEN                  (96)
/* -------------------------           */


/* ===================================================================
 * 結構體定義
 * =================================================================== */

/**
 * 通訊介面錯誤資訊結構體定義
 */
typedef struct _SErrMsg {
    int16           __index;                /**< 序號, 為方便識別而設 */
    uint8           MODULE;                 /**< 模組程式碼 (取值範圍: 0~99) */
    uint8           CODE;                   /**< 明細錯誤號 (取值範圍: 0~99) */
    uint16          __errCode;              /**< 合併後的錯誤編號 (自動計算) */
    int16           __msgSize;              /**< 錯誤資訊長度 (自動計算) */

    /** 錯誤資訊 */
    char            MSG[SPK_MAX_ERRMSG_LEN];
} SErrMsgT;


/* 結構體初始化值定義 */
#define NULLOBJ_SPK_ERRMSG                  \
        0, 0, 0, 0, 0, \
        {0}
/* -------------------------           */


#ifdef __cplusplus
}
#endif

#endif  /* _SPK_ERRMSG_BASE_DEFINE_H */
