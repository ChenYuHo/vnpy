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
 * @file    spk_log_instance.h
 *
 * 日誌記錄器例項管理介面的標頭檔案 (非執行緒安全)
 *
 * @version $Id$
 * @since   2005.10.31
 */


#ifndef _SPK_LOG_INSTANCE_H
#define _SPK_LOG_INSTANCE_H


#include    <sutil/types.h>
#include    <sutil/logger/spk_log_level.h>
#include    <sutil/logger/spk_log_mode.h>
#include    <sutil/logger/spk_log_config.h>


#ifdef __cplusplus
extern "C" {
#endif


/* ===================================================================
 * 結構體定義
 * =================================================================== */

/**
 * 日誌記錄器定義
 */
typedef struct _SLogAppender {
    /** 日誌模式 */
    const SLogModeT     *pLogMode;
    /** 日誌登記函式 */
    void                (*fnLogger) (
                        const struct _SLogAppender *pLogAppender,
                        const char *pLogFile,
                        const SLogLevelT *pLevel,
                        const char *pMsg,
                        int32 msgLength);

    void                *pShmAddr;              /**< 非同步日誌佇列的共享記憶體地址 */
    void                *pQueueAccessor;        /**< 非同步日誌佇列的存取器指標 */

    int8                minLogLevel;            /**< 日誌登記的起始級別 */
    int8                maxLogLevel;            /**< 日誌登記的最高級別 */
    uint8               appenderType;           /**< 日誌記錄器型別 */
    uint8               isAsyncLog;             /**< 是否是非同步日誌 */

    int32               maxFileLength;          /**< 日誌檔案最大長度 */
    int32               maxBackupCount;         /**< 日誌檔案最大備份數 */

    int32               appenderIndex;          /**< 日誌記錄器序號 */
    int32               asyncQueueSize;         /**< 非同步日誌的訊息佇列大小 */
    int32               asyncQueueShmId;        /**< 非同步日誌的共享記憶體ID (0 表示使用預設值) */

    /** 日誌配置區段名稱 */
    char                logSection[SLOGCFG_MAX_SECTION_LENGTH];
    /** 日誌檔名稱 */
    char                logFile[SPK_MAX_PATH_LEN];
} SLogAppenderT;


/* 結構體初始化值定義 */
#define NULLOBJ_LOG_APPENDER                    \
        0, 0, \
        0, 0, \
        0, 0, 0, 0, \
        0, 0, \
        0, 0, 0, \
        {0}, {0}
/* -------------------------           */


/* ===================================================================
 * 普通的日誌記錄器(非非同步日誌)函式宣告
 * =================================================================== */

/* 根據配置檔案初始化日誌例項 */
BOOL    SLog_InitLogger(
                const char *pConfigFile,
                const char *pRootSection,
                const char *pLogSystemName);

/* 根據配置檔案初始化日誌例項(可指定配置項名稱) */
BOOL    SLog_InitLoggerExceptive(
                const char *pConfigFile,
                const char *pRootSection,
                const char *pRootCategoryField,
                const char *pLogSystemName);

/* 根據配置結構初始化日誌例項 */
BOOL    SLog_BuildLogInstance(
                const SLogCfgItemT *pLogConfigs,
                int32 logConfigCount,
                const SLogCfgSectionInfoT *pLogSections,
                int32 logSectionCount,
                const char *pLogSystemName,
                const SLogLevelT *pAllowableMinLogLevel);

/* 重新解析、應用日誌配置 */
BOOL    SLog_RebuildLogInstance();

/* 重新解析、應用日誌配置 */
BOOL    SLog_RebuildLogInstance2(
                const char *pLogSystemName);

/* 重新解析、應用日誌配置 */
BOOL    SLog_RebuildThreadInstance();

/* 重新解析、應用日誌配置 */
BOOL    SLog_RebuildThreadInstance2(
                const char *pLogSystemName);

/* 返回日誌系統是否已初始化 */
BOOL    SLog_IsInstanceInitialized();

/* 返回日誌系統名稱 */
const char*
        SLog_GetLogSystemName();

/* 設定日誌系統名稱 */
void    SLog_SetLogSystemName(
                const char *pLogSystemName);

/* 設定執行緒級別的日誌系統名稱 */
void    SLog_SetThreadLogName(
                const char *pLogSystemName);

/* 返回最小日誌登記級別 */
const SLogLevelT*
        SLog_GetMinLogLevel();

/* 設定最小日誌登記級別 */
void    SLog_SetMinLogLevel(
                const SLogLevelT *pMinLogLevel);

/* 返回日誌記錄器所對應的日誌檔案路徑 */
const char*
        SLog_GetLogFile(
                const SLogAppenderT *pAppender);

/* 設定執行緒級別的最小日誌登記級別 */
void    SLog_SetThreadMinLogLevel(
                const SLogLevelT *pMinLogLevel);

/* 返回最小日誌登記級別的級別限定 (通過SetMinLogLevel設定的最小日誌級別將不會低於該限定) */
const SLogLevelT*
        SLog_GetMinLevelLimit();

/* 設定最小日誌登記級別的級別限定 (通過SetMinLogLevel設定的最小日誌級別將不能低於該限定) */
void    SLog_SetMinLevelLimit(
                const SLogLevelT *pMinLogLevel);

/* 判斷指定的日誌級別是否可用 */
BOOL    SLog_IsLogLevelAble(
                const SLogLevelT *pLevel);

/* 返回日誌遮蔽標誌 */
int32   SLog_GetLogMask();

/* 設定日誌遮蔽標誌 */
void    SLog_SetLogMask(int32 logMask);

/* 重置日誌遮蔽標誌 */
void    SLog_ResetLogMask();

/* 關閉所有的日誌遮蔽標誌 (使能所有型別的日誌輸出) */
void    SLog_DisableAllMask();

/* 關閉指定型別的日誌遮蔽標誌 (使能指定型別的日誌輸出) */
void    SLog_DisableSpecifyMask(int32 logMask);

/* 開啟所有的日誌遮蔽標誌 (遮蔽所有型別的日誌輸出) */
void    SLog_EnableAllMask();

/* 開啟指定型別的日誌遮蔽標誌 (遮蔽指定型別的日誌輸出) */
void    SLog_EnableSpecifyMask(int32 logMask);

/* 返回日誌記錄器列表 */
const SLogAppenderT*
        SLog_GetLogAppenderList();

/* 返回指定位置的日誌記錄器 */
const SLogAppenderT*
        SLog_GetLogAppender(int32 index);

/* 檢索並返還與日誌配置區段名稱相匹配的日誌記錄器 */
const SLogAppenderT*
        SLog_GetLogAppenderByName(const char *pSectionName);

/* 返回日誌記錄器個數 */
int32   SLog_GetLogAppenderCount();

/* 返回原始日誌配置項個數 */
int32   SLog_GetOriginalLogConfigItemsCount();

/* 返回指定位置的原始日誌配置項 */
const SLogCfgItemT*
        SLog_GetOriginalLogConfigItem(int32 index);

/* 返回預設的日誌記錄器 */
const SLogAppenderT*
        SLog_GetDefaultLogAppender();

/* 列印日誌配置資訊 */
void    SLog_PrintLogInstanceInfo(FILE *fp);
/* -------------------------           */


/* ===================================================================
 * 非同步日誌相關的函式宣告
 * =================================================================== */

/* 建立所有非同步日誌使用的共享記憶體佇列 */
BOOL    SLog_CreateAsyncLogQueues();

/* 建立所有非同步日誌使用的共享記憶體佇列 */
BOOL    SLog_ReleaseAsyncLogQueues();

/* 啟用所有的非同步日誌記錄器 */
BOOL    SLog_EnableAsyncLogAppenders();

/* 啟用指定的非同步日誌記錄器 */
BOOL    SLog_EnableAsyncLogAppender(SLogAppenderT *pLogAppender);

/* 禁用所有的非同步日誌記錄器 (改為使用普通的日誌檔案模式) */
BOOL    SLog_DisableAsyncLogAppenders();

/* 禁用指定的非同步日誌記錄器 (改為使用普通的日誌檔案模式, 並斷開與日誌佇列的連線) */
BOOL    SLog_DisableAsyncLogAppender(SLogAppenderT *pLogAppender);

/* 禁用指定的非同步日誌記錄器 (改為使用普通的日誌檔案模式) */
BOOL    SLog_DisableAsyncLogAppender2(
                SLogAppenderT *pLogAppender,
                BOOL detachQueue);

/* 建立並啟動所有的非同步日誌記錄器的檔案寫入執行緒 */
int32   SLog_StartAsyncLogWriterThreads(
                volatile int32 *pNormalTerminatedFlag,
                volatile int32 *pExceptionAbortedFlag,
                BOOL isWaitThreadsTerminated);
/* -------------------------           */


/* ===================================================================
 * 隱含的介面函式宣告, 外部不應直接使用這些介面, 而應該使用相應的巨集介面
 * =================================================================== */

/* 日誌登記處理實現宣告 */
void    _SLog_LogImpl(
                const char *pSrcFile,
                int32 fileNameLength,
                int32 srcLine,
                const char *pSrcFunction,
                int32 logMask,
                const SLogLevelT *pLevel,
                const char *fmt, ...);
/* -------------------------           */


/* ===================================================================
 * 隱含的介面函式宣告, 外部不應直接使用這些介面, 而應該使用響應的巨集介面
 * 為不支援變參巨集的系統而設
 * =================================================================== */

/*
 * 日誌登記處理實現宣告 (為不支援變參巨集的系統而設)
 */
void    _SLog_LogSimpleness(const char *fmt, ...);
void    _SLog_LogFullSimpleness(SLogLevelT *level, const char *fmt, ...);
void    _SLog_TraceSimpleness(const char *fmt, ...);
void    _SLog_DebugSimpleness(const char *fmt, ...);
void    _SLog_InfoSimpleness(const char *fmt, ...);
void    _SLog_WarnSimpleness(const char *fmt, ...);
void    _SLog_ErrorSimpleness(const char *fmt, ...);
void    _SLog_BzInfoSimpleness(const char *fmt, ...);
void    _SLog_BzWarnSimpleness(const char *fmt, ...);
void    _SLog_BzErrorSimpleness(const char *fmt, ...);
void    _SLog_FatalSimpleness(const char *fmt, ...);

void    _SLog_LogSimplenessMasked(const char *fmt, ...);
void    _SLog_LogFullSimplenessMasked(SLogLevelT *level, const char *fmt, ...);
void    _SLog_TraceSimplenessMasked(const char *fmt, ...);
void    _SLog_DebugSimplenessMasked(const char *fmt, ...);
void    _SLog_InfoSimplenessMasked(const char *fmt, ...);
void    _SLog_WarnSimplenessMasked(const char *fmt, ...);
void    _SLog_ErrorSimplenessMasked(const char *fmt, ...);
void    _SLog_BzInfoSimplenessMasked(const char *fmt, ...);
void    _SLog_BzWarnSimplenessMasked(const char *fmt, ...);
void    _SLog_BzErrorSimplenessMasked(const char *fmt, ...);
void    _SLog_FatalSimplenessMasked(const char *fmt, ...);

void    _SLog_AssertSimpleness(BOOL EXPR, const char *fmt, ...);
void*   _SLog_AssertSimplenessRV(BOOL EXPR, void *retValue,
                const char *fmt, ...);
/* -------------------------           */


#ifdef __cplusplus
}
#endif

#endif  /* _SPK_LOG_INSTANCE_H */

