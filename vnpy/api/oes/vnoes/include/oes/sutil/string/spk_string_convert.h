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
 * @file    spk_string_convert.h
 *
 * 字串型別轉換函式
 *
 * @version $Id$
 * @since   2012/01/05
 */


#ifndef _SPK_STRING_CONVERT_H
#define _SPK_STRING_CONVERT_H


#include    <sutil/types.h>
#include    <sutil/compiler.h>
#include    <sutil/platform/spk_platforms.h>
#include    <sutil/string/spk_string_var.h>
#include    <sutil/string/spk_multi_field_string.h>
#include    <sutil/platform/spk_platforms.h>
#include    <sutil/logger/spk_console_masked_log.h>


#ifdef __cplusplus
extern "C" {
#endif


/* ===================================================================
 * 跨平臺相容處理
 * =================================================================== */

#if defined (__WINDOWS__) || defined (__MINGW__)
#   if (defined (_MSC_VER) && _MSC_VER < 1400) \
            || (! defined (_WIN32_WINNT) || _WIN32_WINNT < 0x0600)
#       define  __spk_strtoll           __SPK_WIN32_strtoll
#   else
#       define  __spk_strtoll           _strtoi64
#   endif


/* strtoll */
int64       __SPK_WIN32_strtoll(const char *pStr, char **ppEndPtr, int base);


#else
#   define  __spk_strtoll               strtoll


#endif
/* -------------------------           */


/* ===================================================================
 * 型別轉換函式宣告 (字串 --> 數值型)
 * ("數值型 --> 字串" 類的型別轉換函式定義在後面的 Inline 函式區)
 * =================================================================== */

/*
 * 轉換字串至int32
 */
int32   SStr_Strtoi(const char *pStr, int32 *pValue);

/*
 * 轉換字串至long
 */
int32   SStr_Strtol(const char *pStr, long *pValue);

/*
 * 轉換字串至int64
 */
int32   SStr_Strtoll(const char *pStr, int64 *pValue);

/*
 * 轉換字串至float
 */
int32   SStr_Strtof(const char *pStr, float *pValue);

/*
 * 轉換字串至double
 */
int32   SStr_Strtod(const char *pStr, double *pValue);

/*
 * 轉換字串至long double
 */
int32   SStr_Strtold(const char *pStr, float128 *pValue);

/*
 * 整型數值轉為字串
 */
char*   SStr_ItoStr(char *pBuf, int32 num);

/*
 * 長整型數值轉為字串
 */
char*   SStr_LtoStr(char *pBuf, long num);

/*
 * int64型數值轉為字串
 */
char*   SStr_LltoStr(char *pBuf, int64 num);

/*
 * float128型數值轉為字串
 */
char*   SStr_LdtoStr(char *pBuf, float128 num, int32 scale);

/*
 * float128型數值轉為字串
 */
char*   SStr_FixedLdtoStr(char *pBuf, float128 num, int32 precision,
                int32 scale);

/*
 * 整型數值轉為十六進位制形式的字串
 */
char*   SStr_XtoStr(char *pBuf, int32 num);

/*
 * 校驗字串是否是有效的十進位制整型數值字串
 */
BOOL    SStr_IsDecimalInteger(const char *pStr);

/**
 * 校驗字串是否是有效的十六進位制整型數值字串
 */
BOOL    SStr_IsHexInteger(const char *pStr);

/*
 * 校驗字串是否是有效的整型數值字串
 */
BOOL    SStr_IsInteger(const char *pStr, BOOL isUnitAble);

/*
 * 校驗字串是否是有效的數值型字串
 */
BOOL    SStr_IsNumeric(const char *pStr, BOOL isUnitAble);

/*
 * 轉換帶單位的數值型字串為長整型數值
 */
int64   SStr_ParseUnittedInteger(const char *pStr);

/*
 * 轉換帶單位的數值型字串為長整型數值 (可指定當字串為空時的預設值)
 */
int64   SStr_ParseUnittedInteger2(const char *pStr, int32 defaultValue);

/*
 * 解析BOOL型字串
 */
int32   SStr_ParseBoolean(const char *pStr);

/*
 * 解析BOOL型字串 (可指定當字串為空時的預設值)
 */
int32   SStr_ParseBoolean2(const char *pStr, int32 defaultValue);
/* -------------------------           */


/* ===================================================================
 * 型別轉換相關的 Inline 函式 (數值型 --> 字串)
 * =================================================================== */

/**
 * 解析10進位制數值型字串
 *
 * @param   pValue  待轉換的數值字串
 * @return  轉換後的數值
 */
static __inline long
SStr_StrtoL10(const char *pValue) {
    return strtol(pValue, (char **) NULL, 10);
}


/**
 * 解析10進位制數值型字串
 *
 * @param   pValue  待轉換的數值字串
 * @return  轉換後的數值
 */
static __inline int64
SStr_StrtoLL10(const char *pValue) {
    return __spk_strtoll(pValue, (char **) NULL, 10);
}


/**
 * 解析10進位制數值型字串
 *
 * @param   pValue  待轉換的數值字串
 * @return  轉換後的數值
 */
static __inline int32
SStr_StrtoI10(const char *pValue) {
    return (int32) SStr_StrtoL10(pValue);
}


/**
 * 解析指定長度的10進位制數值型字串
 *
 * @param   pValue  待轉換的數值字串
 * @param   len     數值字串的有效長度
 * @return  轉換後的數值
 */
static __inline long
SStr_FixedStrtoL10(const char *pValue, int32 len) {
    char            __tmpBuf[32];

    SLOG_ASSERT(pValue && len < (int32) sizeof(__tmpBuf));
    memcpy(__tmpBuf, pValue, len);
    __tmpBuf[len] = '\0';

    return strtol(__tmpBuf, (char **) NULL, 10);
}


/**
 * 解析指定長度的10進位制數值型字串
 *
 * @param   pValue  待轉換的數值字串
 * @param   len     數值字串的有效長度
 * @return  轉換後的數值
 */
static __inline int64
SStr_FixedStrtoLL10(const char *pValue, int32 len) {
    char            __tmpBuf[32];

    SLOG_ASSERT(pValue && len < (int32) sizeof(__tmpBuf));
    memcpy(__tmpBuf, pValue, len);
    __tmpBuf[len] = '\0';

    return SStr_StrtoLL10(__tmpBuf);
}


/**
 * 解析指定長度的10進位制數值型字串
 *
 * @param   pValue  待轉換的數值字串
 * @param   len     數值字串的有效長度
 * @return  轉換後的數值
 */
static __inline int32
SStr_FixedStrtoI10(const char *pValue, int32 len) {
    return (int32) SStr_FixedStrtoL10(pValue, len);
}
/* -------------------------           */


#ifdef __cplusplus
}
#endif

#endif  /* _SPK_STRING_CONVERT_H */
