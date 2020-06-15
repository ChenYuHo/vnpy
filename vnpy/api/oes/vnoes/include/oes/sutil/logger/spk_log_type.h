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
 * @file    spk_log_type.h
 *
 * 日誌型別定義
 *
 * @version $Id$
 * @since   2008.8.14
 */


#ifndef _SPK_LOG_TYPE_H
#define _SPK_LOG_TYPE_H


#include    <sutil/types.h>


#ifdef __cplusplus
extern "C" {
#endif


/**
 * 日誌記錄器型別定義
 */
#define     SLOG_TYPE_FILE          (0x01)          /**< 檔案日誌 */
#define     SLOG_TYPE_CONSOLE       (0x02)          /**< 控制檯日誌 */
/* -------------------------           */


/**
 * 日誌遮蔽標誌
 * 可通過日誌遮蔽標誌來阻止登記指定型別的日誌資訊
 */
#define     SLOG_MASK_NONE          (0)
#define     SLOG_MASK_ALL           (0xFFFF)

#define     SLOG_MASK_FILE          SLOG_TYPE_FILE
#define     SLOG_MASK_CONSOLE       SLOG_TYPE_CONSOLE
/* -------------------------           */


#ifdef __cplusplus
}
#endif

#endif  /* _SPK_LOG_TYPE_H */

