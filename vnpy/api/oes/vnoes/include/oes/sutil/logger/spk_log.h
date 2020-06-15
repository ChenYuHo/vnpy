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
 * @file    spk_log.h
 *
 * 預設的日誌處理程式的標頭檔案 (預設開啟控制檯日誌)
 *
 * @version $Id$
 * @since   2008.8.14
 */


#ifndef _SPK_CONSOLE_ENABLED_LOG_H
/*
#define _SPK_CONSOLE_ENABLED_LOG_H
*/


#include    <sutil/types.h>
#include    <sutil/logger/spk_log_type.h>


/*
 * 日誌遮蔽標誌
 * 編譯時可通過指定 SLOG_MASK 巨集定製
 */
#undef      SLOG_MASK_FLAG
#define     SLOG_MASK_FLAG          (0)
/* -------------------------           */


#include    <sutil/logger/_spk_log.h>
#include    <sutil/logger/spk_log_instance.h>


#endif  /* _SPK_CONSOLE_ENABLED_LOG_H */
