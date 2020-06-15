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
 * @file    spk_log_config.h
 *
 * 日誌配置檔案解析處理標頭檔案(非執行緒安全)
 *
 * @version $Id$
 * @since   2005.10.31
 */


#ifndef _SPK_LOG_CONFIG_H
#define _SPK_LOG_CONFIG_H


#include    <sutil/types.h>
#include    <sutil/logger/spk_log_type.h>
#include    <sutil/logger/spk_log_level.h>
#include    <sutil/logger/spk_log_mode.h>


#ifdef __cplusplus
extern "C" {
#endif


/*
 * 常量定義
 */
/** 最大的日誌配置數量 */
#define     SLOGCFG_MAX_CONFIG_COUNT            (32)
/** 最大的日誌記錄器數量 */
#define     SLOGCFG_MAX_APPENDER_NUMBER         (16)
/* -------------------------           */


/*
 * 日誌預設配置定義
 */
#define     SLOGCFG_DEFAULT_MIN_LOG_LEVEL       SLOG_LEVEL_TRACE
#define     SLOGCFG_DEFAULT_MAX_LOG_LEVEL       SLOG_LEVEL_FATAL
#define     SLOGCFG_DEFAULT_MAX_FILE_LENGTH     (300)
#define     SLOGCFG_DEFAULT_MAX_BACKUP_COUNT    (3)
#define     SLOGCFG_MAX_BACKUP_COUNT            (1000)
#define     SLOGCFG_DEFAULT_ASYNC_QUEUE_SIZE    (1000)
#define     SLOGCFG_DEFAULT_ASYNC_SHM_ID        (0)
#define     SLOGCFG_MAX_SECTION_LENGTH          (64)
/* -------------------------           */


/*
 * 配置檔案常量定義
 */
/** 預設的日誌根配置區段 */
#define     SLOGCFG_KEY_DEFAULT_ROOT_SECTION    "log"

/** 預設的日誌根配置 */
#define     SLOGCFG_KEY_DEFAULT_ROOT_CATEGORY   "log.root_category"

/** 多值域的域分隔符 */
#define     SLOGCFG_MULTI_VALUE_DELIMITER       ","
/* -------------------------           */


/*
 * 結構體定義
 */

/**
 * 日誌配置資訊結構
 */
typedef struct _SLogCfgItem {
    /** 日誌配置區段名稱 */
    char                logSection[SLOGCFG_MAX_SECTION_LENGTH];

    /** 日誌模式 */
    char                logMode[SLOG_MAX_MODE_NAME];
    /** 日誌登記的起始級別 */
    char                minLogLevel[SLOG_MAX_LEVEL_NAME];
    /** 日誌登記的最高級別 */
    char                maxLogLevel[SLOG_MAX_LEVEL_NAME];
    /** 日誌檔名稱 */
    char                logFile[SPK_MAX_PATH_LEN];

    /**
     * 日誌檔案最大長度
     * - 日誌檔案最大長度允許配置為0, 表示無最大長度限制
     * - 如果配置值小於 2048 則以兆為單位計算, 否則以位元組為單位計算, 最大檔案長度為2GB
     */
    int32               maxFileLength;
    /** 日誌檔案最大備份數 */
    int32               maxBackupCount;

    /** 非同步日誌的訊息佇列大小 */
    int32               asyncQueueSize;
    /** 非同步日誌的共享記憶體ID (0 表示使用預設值) */
    int32               asyncQueueShmId;
} SLogCfgItemT;


/* 結構體初始化值定義 */
#define NULLOBJ_LOG_CFG_ITEM                    \
        {0}, {0}, {0}, {0}, {0}, \
        0, 0, \
        0, 0
/* -------------------------           */


/**
 * 日誌配置區段
 */
typedef struct _SLogCfgSectionInfo {
    /** 日誌配置的區段名稱 */
    char        section[SLOGCFG_MAX_SECTION_LENGTH];
} SLogCfgSectionInfoT;
/* -------------------------           */


/*
 * 函式宣告
 */

/*
 * 嘗試載入所有的日誌配置區段
 */
int32   SLogCfg_LoadAllConfig(
                const char *pConfigFile,
                SLogCfgItemT *pOutLogConfigList,
                int32 maxLogConfigCount);

/*
 * 解析日誌配置資訊, 讀取相關的日誌分類列表，並載入所有的日誌配置區段
 */
int32   SLogCfg_LoadAllConfigAndCategoryList(
                const char *pConfigFile,
                const char *pRootSection,
                const char *pRootCategoryField,
                SLogCfgItemT *pOutLogConfigList,
                int32 *pLogConfigCount,
                SLogCfgSectionInfoT *pOutLogSectionList,
                int32 *pLogSectionCount,
                const SLogLevelT **ppOutAllowableMinLogLevel);
/* -------------------------           */


#ifdef __cplusplus
}
#endif

#endif  /* _SPK_LOG_CONFIG_H */
