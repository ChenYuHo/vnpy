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
 * @file    data_buffer_define.h
 *
 * 可動態分配的資料快取
 *
 * @version 1.0 2008/12/1
 * @since   2008/12/1
 */


#ifndef _SPK_DATA_BUFFER_DEFINE_H
#define _SPK_DATA_BUFFER_DEFINE_H


#include    <sutil/types.h>


#ifdef __cplusplus
extern "C" {
#endif


/* ===================================================================
 * 常量定義
 * =================================================================== */

/** 最小快取大小 */
#define SPK_MIN_DATA_BUFFER_SIZE        (4 * 1024)
/** 最大快取大小 */
#define SPK_MAX_DATA_BUFFER_SIZE        (32 * 1024 * 1024)
/* -------------------------           */


/* ===================================================================
 * 結構體定義
 * =================================================================== */

/**
 * 支援動態記憶體分配的資料快取定義
 */
typedef struct _SDataBuffer {
    int32               dataSize;                       /**< 有效資料長度 */
    int32               const bufSize;                  /**< 快取區總大小 */
    char                * const buffer;                 /**< 快取區指標 */
    void                *__ref;                         /**< 反向引用指標 */
} SDataBufferT;


/**
 * 支援動態記憶體分配的資料快取的結構體別名 (為了消除某些情況下的編譯警告)
 */
struct _SDataBufferVar {
    int32               dataSize;                       /**< 有效資料長度 */
    int32               bufSize;                        /**< 快取區總大小 */
    char                *buffer;                        /**< 快取區指標 */
    void                *__ref;                         /**< 反向引用指標 */
};


/* 結構體初始化值定義 */
#define NULLOBJ_SPK_DATA_BUFFER                         \
        0, 0, (char*) NULL, NULL
/* -------------------------           */


#ifdef __cplusplus
}
#endif

#endif  /* _SPK_DATA_BUFFER_DEFINE_H */
