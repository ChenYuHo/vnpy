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
 * @file    spk_log_level.h
 *
 * 日誌級別定義標頭檔案
 *
 * @version $Id$
 * @since   2004.4.26
 */


#ifndef _SPK_LOG_LEVEL_H
#define _SPK_LOG_LEVEL_H


#include    <sutil/types.h>


#ifdef __cplusplus
extern "C" {
#endif


/*
 * 常量定義
 */
#define     SLOG_MAX_LEVEL_NAME         (32)        /**< 日誌級別名稱的長度 */
/* -------------------------           */


/**
 * 日誌級別結構體定義
 */
typedef struct _SLogLevel {
    int8                level;                      /**< 日誌級別程式碼 */
    int8                __filler[7];                /**< 日誌級別程式碼 */

    char                name[SLOG_MAX_LEVEL_NAME];  /**< 日誌級別名稱 */
} SLogLevelT;
/* -------------------------           */


/**
 * 日誌級別定義表
 */
extern  SLogLevelT __SPK_DLL_IMPORT     __SPK_slogLevels[];


/*
 * 日誌級別常量定義
 */
#define     SLOG_LEVEL_TRACE            (&__SPK_slogLevels[0])
#define     SLOG_LEVEL_DEBUG            (&__SPK_slogLevels[1])
#define     SLOG_LEVEL_INFO             (&__SPK_slogLevels[2])
#define     SLOG_LEVEL_WARN             (&__SPK_slogLevels[3])
#define     SLOG_LEVEL_ERROR            (&__SPK_slogLevels[4])

#define     SLOG_LEVEL_BZ_INFO          (&__SPK_slogLevels[5])
#define     SLOG_LEVEL_BZ_WARN          (&__SPK_slogLevels[6])
#define     SLOG_LEVEL_BZ_ERROR         (&__SPK_slogLevels[7])
#define     SLOG_LEVEL_FATAL            (&__SPK_slogLevels[8])
#define     SLOG_LEVEL_NONE             (&__SPK_slogLevels[9])
/* -------------------------           */


/**
 * 日誌級別值定義
 */
typedef enum _eSLogLevelValue {
    SLOG_LEVEL_VALUE_TRACE      = 0,                /**< 日誌級別-跟蹤資訊 */
    SLOG_LEVEL_VALUE_DEBUG      = 1,                /**< 日誌級別-除錯資訊 */
    SLOG_LEVEL_VALUE_INFO       = 2,                /**< 日誌級別-提示資訊 */
    SLOG_LEVEL_VALUE_WARN       = 3,                /**< 日誌級別-警告資訊 */
    SLOG_LEVEL_VALUE_ERROR      = 4,                /**< 日誌級別-錯誤資訊 */

    SLOG_LEVEL_VALUE_BZ_INFO    = 5,                /**< 日誌級別-業務提示 */
    SLOG_LEVEL_VALUE_BZ_WARN    = 6,                /**< 日誌級別-業務警告 */
    SLOG_LEVEL_VALUE_BZ_ERROR   = 7,                /**< 日誌級別-業務錯誤 */
    SLOG_LEVEL_VALUE_FATAL      = 8,                /**< 日誌級別-致命錯誤 */
    SLOG_LEVEL_VALUE_NONE       = 9,                /**< 日誌級別-遮蔽所有日誌 */
    __SLOG_LEVEL_VALUE_MAX
} eSLogLevelValueT;
/* -------------------------           */


/*
 * 函式定義
 */

/*
 * 返回名稱對應的日誌級別
 */
const SLogLevelT*   SLog_GetLogLevel(const char *levelName);

/*
 * 返回日誌級別值所對應的日誌級別
 */
const SLogLevelT*   SLog_GetLogLevelByValue(int8 levelValue);
/* -------------------------           */


#ifdef __cplusplus
}
#endif

#endif  /* _SPK_LOG_LEVEL_H */
