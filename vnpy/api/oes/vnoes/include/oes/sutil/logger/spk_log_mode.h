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
 * @file    spk_log_mode.h
 *
 * 日誌模式定義標頭檔案
 *
 * @version $Id$
 * @since   2004.12.23
 */


#ifndef _SPK_LOG_MODE_H
#define _SPK_LOG_MODE_H


#include    <sutil/types.h>
#include    <sutil/compiler.h>
#include    <sutil/logger/spk_log_type.h>


#ifdef __cplusplus
extern "C" {
#endif


/*
 * 常量定義
 */
/** 日誌內容的最大長度 */
#define     SLOG_MAX_INFO_SIZE      (SPK_MAX_BLOCK_SIZE)
/* TODO 日誌內容的最大長度
#define     SLOG_MAX_INFO_SIZE      (PIPE_BUF)
*/

/** 日誌模式名稱的長度 */
#define     SLOG_MAX_MODE_NAME      (32)
/* -------------------------           */


/**
 * 日誌模式結構體定義
 */
typedef struct _SLogMode {
    uint8               mode;                       /**< 日誌模式程式碼 */
    uint8               appenderType;               /**< 日誌記錄器型別 */
    uint8               isAsyncLog;                 /**< 是否是非同步日誌 */
    uint8               __filler1[5];               /**< 按64位對齊的填充域 */

    void                *logFn;                     /**< 日誌實現函式 */
    void                *__filler2;                 /**< 按64位對齊的填充域 */
    char                name[SLOG_MAX_MODE_NAME];   /**< 日誌模式名稱 */
} SLogModeT;
/* -------------------------           */


/**
 * 日誌級別定義表
 */
extern  SLogModeT __SPK_DLL_IMPORT      __SPK_slogModes[];


/*
 * 日誌級別常量定義
 */
/** 日誌模式 - 檔案日誌 - 等同FILE_ROLLING */
#define SLOG_MODE_FILE                  (&__SPK_slogModes[0])

/** 日誌模式 - 檔案日誌 - 輪換, 不區分具體日期 */
#define SLOG_MODE_FILE_ROLLING          (&__SPK_slogModes[1])

/** 日誌模式 - 檔案日誌 - 每天N個日誌檔案(N >= 1) */
#define SLOG_MODE_FILE_DAILY_ROLLING    (&__SPK_slogModes[2])

/** 日誌模式 - 檔案日誌 - 每天一個日誌檔案 */
#define SLOG_MODE_FILE_DAILY            (&__SPK_slogModes[3])

/** 日誌模式 - 控制檯日誌 - 等同CONSOLE_STDOUT */
#define SLOG_MODE_CONSOLE               (&__SPK_slogModes[4])

/** 日誌模式 - 控制檯日誌 - 輸出到stdout */
#define SLOG_MODE_CONSOLE_STDOUT        (&__SPK_slogModes[5])

/** 日誌模式 - 控制檯日誌 - 輸出到stderr */
#define SLOG_MODE_CONSOLE_STDERR        (&__SPK_slogModes[6])

/** 日誌模式 - 非同步檔案日誌 */
#define SLOG_MODE_ASYNC_FILE            (&__SPK_slogModes[7])
/* -------------------------           */


/*
 * 函式定義
 */

/*
 * 返回名稱對應的日誌模式
 */
const SLogModeT*
        SLog_GetLogMode(const char *modeName);

/*
 * 返回日誌模式對應的日誌記錄器型別是否是檔案記錄器
 */
BOOL    SLog_IsFileLogAppender(const SLogModeT *logMode);

/*
 * 返回日誌模式對應的日誌記錄器型別是否是非同步日誌記錄器
 */
BOOL    SLog_IsAsyncLogAppender(const SLogModeT *logMode);
/* -------------------------           */


#ifdef __cplusplus
}
#endif

#endif  /* _SPK_LOG_MODE_H */

