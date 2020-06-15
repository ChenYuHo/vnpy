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
 * @file    _spk_log.h
 *
 * 日誌處理程式的標頭檔案
 *
 * <p>相關縮寫: <ul>
 * <li>slog: simple logger</li>
 * </ul></p>
 *
 * <p>相關的預定義巨集: <ul>
 * <li>NO_LOG: 關閉所有日誌</li>
 * <li>NO_DEBUG: 關閉 DEBUG 和 TRACE 級別的日誌</li>
 * <li>NO_TRACE: 關閉 TRACE 級別的日誌</li>
 * <li>NO_VA_MACRO: 不支援變參巨集</li>
 * <li>_CHECK_LOG_FORMAT: 在編譯時檢查格式化字串的格式</li>
 * </ul></p>
 *
 * @version $Id$
 * @since   2004/4/26
 */


#ifndef __SPK_LOGGER_H
#define __SPK_LOGGER_H


#include    <sutil/types.h>
#include    <sutil/compiler.h>
#include    <sutil/logger/spk_log_type.h>
#include    <sutil/logger/spk_log_level.h>
#include    <sutil/logger/spk_log_instance.h>


#ifdef __cplusplus
extern "C" {
#endif


/*
 * 日誌編譯標誌
 */

/**
 * 是否支援變參巨集
 */
#if defined (NO_VA_MACRO) || (defined (_MSC_VER) && _MSC_VER < 1400)
#   define  _VA_MACRO_ABLE          (0)
#else
#   define  _VA_MACRO_ABLE          (1)
#endif

/**
 * 日誌開啟標誌
 */
#if defined (NO_LOG)
#   define  _LOG_ABLE               (0)
#else
#   define  _LOG_ABLE               (1)
#endif

/**
 * 是否允許登記級別為DEBUG的日誌資訊
 */
#if defined (NO_DEBUG) || ! _LOG_ABLE
#   define  _LOG_DEBUG_ABLE         (0)
#else
#   define  _LOG_DEBUG_ABLE         (1)
#endif

/**
 * 是否允許登記級別為TRACE的日誌資訊
 */
#if defined (NO_TRACE) || ! _LOG_ABLE || ! _LOG_DEBUG_ABLE
#   define  _LOG_TRACE_ABLE         (0)
#else
#   define  _LOG_TRACE_ABLE         (1)
#endif
/* -------------------------           */


/**
 * 預設的日誌遮蔽標誌
 * 可通過日誌遮蔽標誌來阻止登記指定型別的日誌資訊
 */
#define DEFAULT_LOG_MASK            (0x0)
#define DEFAULT_NO_VA_LOG_MASK      DEFAULT_LOG_MASK
/* -------------------------           */


/* ===================================================================
 * 介面函式宣告
 * =================================================================== */

#if ! _LOG_DEBUG_ABLE
#   define SLog_IsDebugAble()       (FALSE)
#else
#   define SLog_IsDebugAble()       (SLog_IsLogLevelAble(SLOG_LEVEL_DEBUG))
#endif

#if ! _LOG_TRACE_ABLE
#   define SLog_IsTraceAble()       (FALSE)
#else
#   define SLog_IsTraceAble()       (SLog_IsLogLevelAble(SLOG_LEVEL_TRACE))
#endif
/* -------------------------           */


#ifdef __cplusplus
}
#endif

#endif  /* __SPK_LOGGER_H */


/* ===================================================================
 * 日誌巨集定義
 * =================================================================== */

/*
 * 根據日誌遮蔽標誌判斷是否需要重置日誌巨集
 * 編譯時可通過指定 SLOG_MASK 巨集定製
 */
#if defined(SLOG_MASK)
#   undef   _SLOG_MASK
#   define  _SLOG_MASK      SLOG_MASK
#elif defined(SLOG_MASK_FLAG)
#   undef   _SLOG_MASK
#   define  _SLOG_MASK      SLOG_MASK_FLAG
#else
#   undef   _SLOG_MASK
#   define  _SLOG_MASK      DEFAULT_LOG_MASK
#endif


#if ! defined(_SLOG_MASK)
#   define  _SLOG_MASK      DEFAULT_LOG_MASK
#endif


#if defined(__SLOG_LOGGER_MACROS_H)
#   undef   __SLOG_LOGGER_MACROS_H

#   undef   SLOG_LOG
#   undef   SLOG_TRACE
#   undef   SLOG_DEBUG
#   undef   SLOG_INFO
#   undef   SLOG_WARN
#   undef   SLOG_ERROR
#   undef   SLOG_BZ_INFO
#   undef   SLOG_BZ_WARN
#   undef   SLOG_BZ_ERROR
#   undef   SLOG_FATAL

#   undef   SLOG_ASSERT
#   undef   SLOG_ASSERT_RV
#   undef   SLOG_ASSERT_NV
#endif


#ifndef __SLOG_LOGGER_MACROS_H
#define __SLOG_LOGGER_MACROS_H


#ifdef __cplusplus
extern "C" {
#endif


/*
 * 日誌函式(巨集函式)定義
 */
#if _VA_MACRO_ABLE

#   if _LOG_TRACE_ABLE
        /**
         * SLOG_TRACE, 跟蹤資訊登記巨集函式
         * 以級別LOG_TRACE登記日誌
         *
         * <pre>
         * SLOG_TRACE("log info");
         * SLOG_TRACE("log info, a is:%s; b is: %d", a, b);
         * </pre>
         */
#       define  SLOG_TRACE(...)     \
                _SLog_LogImpl(__FILE__, sizeof(__FILE__), __LINE__, \
                        __FUNCTION__, _SLOG_MASK, SLOG_LEVEL_TRACE, __VA_ARGS__)
#   else
#       define  SLOG_TRACE(...)
#   endif

#   if _LOG_DEBUG_ABLE
        /**
         * SLOG_DEBUG, 除錯資訊登記巨集函式
         * 以級別LOG_DEBUG登記日誌
         *
         * <pre>
         * SLOG_DEBUG("log info");
         * SLOG_DEBUG("log info, a is:%s; b is: %d", a, b);
         * </pre>
         */
#       define  SLOG_DEBUG(...)     \
                _SLog_LogImpl(__FILE__, sizeof(__FILE__), __LINE__, \
                        __FUNCTION__, _SLOG_MASK, SLOG_LEVEL_DEBUG, __VA_ARGS__)
#   else
#       define  SLOG_DEBUG(...)
#   endif

#   if _LOG_ABLE
        /**
         * SLOG_LOG, 日誌登記巨集函式, 為簡化日誌函式的使用而設
         * 可在呼叫時指定日誌遮蔽標誌和日誌登記級別
         *
         * <pre>
         * SLOG_LOG(level, "log info");
         * SLOG_LOG(level, "log info, a is:%s; b is: %d", a, b);
         * </pre>
         */
#       define  SLOG_LOG(...)       \
                _SLog_LogImpl(__FILE__, sizeof(__FILE__), __LINE__, \
                        __FUNCTION__, _SLOG_MASK, __VA_ARGS__)

        /**
         * SLOG_INFO, 提示資訊登記巨集函式
         * 以級別LOG_INFO登記日誌
         *
         * <pre>
         * SLOG_INFO("log info");
         * SLOG_INFO("log info, a is:%s; b is: %d", a, b);
         * </pre>
         */
#       define  SLOG_INFO(...)      \
                _SLog_LogImpl(__FILE__, sizeof(__FILE__), __LINE__, \
                        __FUNCTION__, _SLOG_MASK, SLOG_LEVEL_INFO, __VA_ARGS__)

        /**
         * SLOG_WARN, 警告資訊登記巨集函式
         * 以級別LOG_WARN登記日誌
         *
         * <pre>
         * SLOG_WARN("log info");
         * SLOG_WARN("log info, a is:%s; b is: %d", a, b);
         * </pre>
         */
#       define  SLOG_WARN(...)      \
                _SLog_LogImpl(__FILE__, sizeof(__FILE__), __LINE__, \
                        __FUNCTION__, _SLOG_MASK, SLOG_LEVEL_WARN, __VA_ARGS__)

        /**
         * SLOG_ERROR, 錯誤資訊登記巨集函式
         * 以級別LOG_ERROR登記日誌
         *
         * <pre>
         * SLOG_ERROR("log info");
         * SLOG_ERROR("log info, a is:%s; b is: %d", a, b);
         * </pre>
         */
#       define  SLOG_ERROR(...)     \
                _SLog_LogImpl(__FILE__, sizeof(__FILE__), __LINE__, \
                        __FUNCTION__, _SLOG_MASK, SLOG_LEVEL_ERROR, __VA_ARGS__)

        /**
         * SLOG_BZ_INFO, 業務提示資訊登記巨集函式
         * 以級別BZ_INFO登記日誌
         *
         * <pre>
         * SLOG_BZ_INFO("log info");
         * SLOG_BZ_INFO("log info, a is:%s; b is: %d", a, b);
         * </pre>
         */
#       define  SLOG_BZ_INFO(...)   \
                _SLog_LogImpl(__FILE__, sizeof(__FILE__), __LINE__, \
                        __FUNCTION__, _SLOG_MASK, SLOG_LEVEL_BZ_INFO, \
                        __VA_ARGS__)

        /**
         * SLOG_BZ_WARN, 業務警告資訊登記巨集函式
         * 以級別BZ_WARN登記日誌
         *
         * <pre>
         * SLOG_BZ_WARN("log info");
         * SLOG_BZ_WARN("log info, a is:%s; b is: %d", a, b);
         * </pre>
         */
#       define  SLOG_BZ_WARN(...)   \
                _SLog_LogImpl(__FILE__, sizeof(__FILE__), __LINE__, \
                        __FUNCTION__, _SLOG_MASK, SLOG_LEVEL_BZ_WARN, \
                        __VA_ARGS__)

        /**
         * SLOG_BZ_ERROR, 業務錯誤資訊登記巨集函式
         * 以級別BZ_ERROR登記日誌
         *
         * <pre>
         * SLOG_BZ_ERROR("log info");
         * SLOG_BZ_ERROR("log info, a is:%s; b is: %d", a, b);
         * </pre>
         */
#       define  SLOG_BZ_ERROR(...)  \
                _SLog_LogImpl(__FILE__, sizeof(__FILE__), __LINE__, \
                        __FUNCTION__, _SLOG_MASK, SLOG_LEVEL_BZ_ERROR, \
                        __VA_ARGS__)

        /**
         * SLOG_FATAL, 致命錯誤資訊登記巨集函式
         * 以級別LOG_FATAL登記日誌
         *
         * <pre>
         * SLOG_FATAL("log info");
         * SLOG_FATAL("log info, a is:%s; b is: %d", a, b);
         * </pre>
         */
#       define  SLOG_FATAL(...)     \
                _SLog_LogImpl(__FILE__, sizeof(__FILE__), __LINE__, \
                        __FUNCTION__, _SLOG_MASK, SLOG_LEVEL_FATAL, __VA_ARGS__)

#   else    /* _LOG_ABLE */
#       define  SLOG_LOG(...)
#       define  SLOG_INFO(...)
#       define  SLOG_WARN(...)
#       define  SLOG_ERROR(...)
#       define  SLOG_BZ_INFO(...)
#       define  SLOG_BZ_WARN(...)
#       define  SLOG_BZ_ERROR(...)
#       define  SLOG_FATAL(...)
#   endif   /* _LOG_ABLE */

#else       /* _VA_MACRO_ABLE */

#   if _LOG_ABLE
#       ifdef _SLOG_MASK
#           define      SLOG_LOG        _SLog_LogFullSimplenessMasked
#           define      SLOG_INFO       _SLog_InfoSimplenessMasked
#           define      SLOG_WARN       _SLog_WarnSimplenessMasked
#           define      SLOG_ERROR      _SLog_ErrorSimplenessMasked
#           define      SLOG_BZ_INFO    _SLog_BzInfoSimplenessMasked
#           define      SLOG_BZ_WARN    _SLog_BzWarnSimplenessMasked
#           define      SLOG_BZ_ERROR   _SLog_BzErrorSimplenessMasked
#           define      SLOG_FATAL      _SLog_FatalSimplenessMasked
#       else
#           define      SLOG_LOG        _SLog_LogFullSimpleness
#           define      SLOG_INFO       _SLog_InfoSimpleness
#           define      SLOG_WARN       _SLog_WarnSimpleness
#           define      SLOG_ERROR      _SLog_ErrorSimpleness
#           define      SLOG_BZ_INFO    _SLog_BzInfoSimpleness
#           define      SLOG_BZ_WARN    _SLog_BzWarnSimpleness
#           define      SLOG_BZ_ERROR   _SLog_BzErrorSimpleness
#           define      SLOG_FATAL      _SLog_FatalSimpleness
#       endif

#       if _LOG_TRACE_ABLE
#           ifdef _SLOG_MASK
#               define  SLOG_TRACE      _SLog_TraceSimplenessMasked
#           else
#               define  SLOG_TRACE      _SLog_TraceSimpleness
#           endif
#       else
#           define      SLOG_TRACE
#       endif

#       if _LOG_DEBUG_ABLE
#           ifdef _SLOG_MASK
#               define  SLOG_DEBUG      _SLog_DebugSimplenessMasked
#           else
#               define  SLOG_DEBUG      _SLog_DebugSimpleness
#           endif
#       else
#           define      SLOG_DEBUG
#       endif
#   else    /* _LOG_ABLE */
#       define          SLOG_LOG
#       define          SLOG_TRACE
#       define          SLOG_DEBUG
#       define          SLOG_INFO
#       define          SLOG_WARN
#       define          SLOG_ERROR
#       define          SLOG_BZ_INFO
#       define          SLOG_BZ_WARN
#       define          SLOG_BZ_ERROR
#       define          SLOG_FATAL
#   endif   /* _LOG_ABLE */

#   ifndef __FUNCTION__
#       define  __FUNCTION__    ""
#   endif

#endif      /* _VA_MACRO_ABLE */
/* -------------------------           */


/* ===================================================================
 * 為了在編譯時檢查格式化字串而設定的日誌函式替換巨集
 * =================================================================== */

#if defined(_CHECK_LOG_FORMAT)
#   undef   SLOG_TRACE
#   undef   SLOG_DEBUG
#   undef   SLOG_INFO
#   undef   SLOG_WARN
#   undef   SLOG_ERROR
#   undef   SLOG_BZ_INFO
#   undef   SLOG_BZ_WARN
#   undef   SLOG_BZ_ERROR
#   undef   SLOG_FATAL

#   define  SLOG_TRACE      printf
#   define  SLOG_DEBUG      printf
#   define  SLOG_INFO       printf
#   define  SLOG_WARN       printf
#   define  SLOG_ERROR      printf
#   define  SLOG_BZ_INFO    printf
#   define  SLOG_BZ_WARN    printf
#   define  SLOG_BZ_ERROR   printf
#   define  SLOG_FATAL      printf
#endif
/* -------------------------           */


/* ===================================================================
 * ASSERT 定義
 * =================================================================== */

#if ! defined(NDEBUG)

/**
 * assert, 若未定義 NDEBUG, 則記錄錯誤日誌並結束程序
 */
#   define  SLOG_ASSERT(EXPR)                       \
        do { \
            if (unlikely(! (EXPR) )) { \
                SLOG_ERROR("[ERROR] ASSERT: (" __STRING(EXPR) ")"); \
                assert((EXPR)); \
            } \
        } while (0)

/**
 * assert, 若未定義 NDEBUG, 則記錄錯誤日誌並結束程序
 */
#if _VA_MACRO_ABLE
#   define  SLOG_ASSERT2(EXPR, ...)                 \
        do { \
            if (unlikely(! (EXPR) )) { \
                SLOG_ERROR("[ERROR] ASSERT: (" __STRING(EXPR) ") - " \
                        __VA_ARGS__); \
                assert((EXPR)); \
            } \
        } while (0)
#else   /* _VA_MACRO_ABLE */
#   define  SLOG_ASSERT2                _SLog_AssertSimpleness
#endif

#else

#if _VA_MACRO_ABLE
#   define  SLOG_ASSERT(EXPR)
#   define  SLOG_ASSERT2(EXPR, ...)
#else   /* _VA_MACRO_ABLE */
#   define  SLOG_ASSERT(EXPR)
#   define  SLOG_ASSERT2
#endif

#endif
/* -------------------------           */


#if defined(ENABLE_SOFT_ASSERT)

/**
 * 記錄錯誤日誌並直接從函式返回指定的值
 */
#   define  SLOG_ASSERT_RV(EXPR, RETURN_VAL)                \
        do { \
            if (unlikely(! (EXPR) )) { \
                SLOG_ERROR("[ERROR] ASSERT: (" __STRING(EXPR) ")"); \
                return (RETURN_VAL); \
            } \
        } while (0)

/**
 * 記錄錯誤日誌並直接從函式返回指定的值
 */
# if _VA_MACRO_ABLE
#   define  SLOG_ASSERT_RV2(EXPR, RETURN_VAL, ...)          \
        do { \
            if (unlikely(! (EXPR) )) { \
                SLOG_ERROR("[ERROR] ASSERT: (" __STRING(EXPR) ") - " \
                        __VA_ARGS__); \
                return (RETURN_VAL); \
            } \
        } while (0)
# else  /* _VA_MACRO_ABLE */
#   define  SLOG_ASSERT_RV2             _SLog_AssertSimplenessRV
# endif

/**
 * 記錄錯誤日誌並直接從void函式返回
 */
#   define  SLOG_ASSERT_NV(EXPR)                            \
        do { \
            if (unlikely(! (EXPR) )) { \
                SLOG_ERROR("[ERROR] ASSERT: (" __STRING(EXPR) ")"); \
                return; \
            } \
        } while (0)

/**
 * 記錄錯誤日誌並直接從void函式返回
 */
# if _VA_MACRO_ABLE
#   define  SLOG_ASSERT_NV2(EXPR, ...)                      \
        do { \
            if (unlikely(! (EXPR) )) { \
                SLOG_ERROR("[ERROR] ASSERT: (" __STRING(EXPR) ") - " \
                        __VA_ARGS__); \
                return; \
            } \
        } while (0)
# else  /* _VA_MACRO_ABLE */
#   define  SLOG_ASSERT_NV2             _SLog_AssertSimpleness
# endif

#elif ! defined(NDEBUG)                 /* elif ENABLE_SOFT_ASSERT */

/**
 * assert, 若未定義 NDEBUG, 則記錄錯誤日誌並結束程序
 */
#   define  SLOG_ASSERT_RV(EXPR, RETURN_VAL)                \
        do { \
            if (unlikely(! (EXPR) )) { \
                SLOG_ERROR("[ERROR] ASSERT: (" __STRING(EXPR) ")"); \
                assert((EXPR)); \
            } \
        } while (0)

/**
 * assert, 若未定義 NDEBUG, 則記錄錯誤日誌並結束程序
 */
# if _VA_MACRO_ABLE
#   define  SLOG_ASSERT_RV2(EXPR, RETURN_VAL, ...)          \
        do { \
            if (unlikely(! (EXPR) )) { \
                SLOG_ERROR("[ERROR] ASSERT: (" __STRING(EXPR) ") - " \
                        __VA_ARGS__); \
                assert((EXPR)); \
            } \
        } while (0)
# else  /* _VA_MACRO_ABLE */
#   define  SLOG_ASSERT_RV2             _SLog_AssertSimplenessRV
# endif

/**
 * assert, 若未定義 NDEBUG, 則記錄錯誤日誌並結束程序
 */
#   define  SLOG_ASSERT_NV(EXPR)                            \
            SLOG_ASSERT_RV((EXPR), 0)

/**
 * assert, 若未定義 NDEBUG, 則記錄錯誤日誌並結束程序
 */
# if _VA_MACRO_ABLE
#   define  SLOG_ASSERT_NV2(EXPR, ...)                      \
            SLOG_ASSERT_RV2((EXPR), 0, __VA_ARGS__)
# else  /* _VA_MACRO_ABLE */
#   define  SLOG_ASSERT_NV2             _SLog_AssertSimpleness
# endif

#else                                   /* else ENABLE_SOFT_ASSERT */

# if _VA_MACRO_ABLE
#   define  SLOG_ASSERT_RV(EXPR, RETURN_VAL)
#   define  SLOG_ASSERT_RV2(EXPR, RETURN_VAL, ...)

#   define  SLOG_ASSERT_NV(EXPR)
#   define  SLOG_ASSERT_NV2(EXPR, ...)
# else  /* _VA_MACRO_ABLE */
#   define  SLOG_ASSERT_RV(EXPR, RETURN_VAL)
#   define  SLOG_ASSERT_RV2

#   define  SLOG_ASSERT_NV(EXPR)
#   define  SLOG_ASSERT_NV2
# endif

#endif
/* -------------------------           */


#ifdef __cplusplus
}
#endif

#endif  /* __SLOG_LOGGER_MACROS_H */
