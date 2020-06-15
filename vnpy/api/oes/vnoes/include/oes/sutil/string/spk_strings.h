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
 * @file    spk_strings.h
 *
 * 字串處理函式的標頭檔案(執行緒安全)
 *
 * @version $Id$
 * @since   2012/01/05
 */


#ifndef _SPK_STRINGS_H
#define _SPK_STRINGS_H


#include    <sutil/types.h>
#include    <sutil/compiler.h>
#include    <sutil/cmnlib.h>
#include    <sutil/platform/spk_platforms.h>
#include    <sutil/string/spk_string_convert.h>
#include    <sutil/string/spk_string_var.h>
#include    <sutil/string/spk_multi_field_string.h>
#include    <sutil/string/spk_fixed_snprintf.h>
#include    <sutil/string/spk_strverscmp.h>
#include    <sutil/logger/spk_console_masked_log.h>


#ifdef __cplusplus
extern "C" {
#endif


/* ===================================================================
 * 跨平臺相容處理
 * =================================================================== */

#if defined (__WINDOWS__)
#   undef   snprintf
#   define  snprintf                SStr_Snprintf
#endif
/* -------------------------           */


/* ===================================================================
 * 函式宣告
 * =================================================================== */

/*
 * compare two strings, and end with endChar
 */
int32   SStr_Strchcmp(const char *s1, const char *s2, int32 endChar);

/*
 * compare two strings ignoring case
 */
int32   SStr_Strncasecmp(const char *s1, const char *s2, int32 n);

/*
 * 替換目標字串中的待替換字串
 */
char*   SStr_Replace(char *pBuf, const char *pTarget, const char *pOldStr,
            const char *pNewStr);

/*
 * 替換目標字串中的待替換字串(可指定替換個數)
 */
char*   SStr_ReplaceAppointed(char *pBuf, const char *pTarget,
            const char *pOldStr, const char *pNewStr, int32 n);

/*
 * 取得被前、字尾包裹的字串
 */
char*   SStr_GetWrappedString(char *pBuf, const char *pTarget,
            const char *pPrefix, const char *pPostfix);

/*
 * 構造被前、字尾包裹的字串
 */
char*   SStr_BuildWrappedString(char *pBuf, const char *pTarget,
            int32 targetLen, const char *pPrefix, const char *pPostfix);

/*
 * 返回字串是否是以指定的字串起始的
 */
BOOL    SStr_IsStartWith(const char *pStr, const char *pStartWith,
            const char *pAnyChar, int32 n);

/*
 * 返回字串是否是以指定的字串起始的
 */
BOOL    SStr_IsStartWith2(const char *pStr, const char *pStartWith,
            const char *pAnyChar, int32 n, const char **ppAfterMatched);

/*
 * 返回字串是否是以指定的字串起始的 (忽略大小寫)
 */
BOOL    SStr_IsIgnoreCaseStartWith(const char *pStr, const char *pStartWith,
            const char *pAnyChar, int32 n);

/*
 * 返回字串是否是以指定的字串起始的 (忽略大小寫)
 */
BOOL    SStr_IsIgnoreCaseStartWith2(const char *pStr, const char *pStartWith,
            const char *pAnyChar, int32 n, const char **ppAfterMatched);

/*
 * 返回字串是否是以指定的字串結尾的
 */
BOOL    SStr_IsEndsWith(const char *pStr, const char *pEndsWith);

/*
 * 返回字串是否是以指定的字串結尾的 (忽略大小寫)
 */
BOOL    SStr_IsIgnoreCaseEndsWith(const char *pStr, const char *pEndsWith);

/*
 * 統計字串中指定字元出現的次數
 */
int32   SStr_TotalChars(const char *pStr, const char *pChars);
/* -------------------------           */


/* ===================================================================
 * Inline 函式
 * =================================================================== */

/**
 * check a char is any of a set of characters
 */
static __inline BOOL
SStr_IsAnyChar(const char ch, const char *accept) {
    SLOG_ASSERT(accept);
    while (*accept) {
        if (*accept++ == ch) {
            return TRUE;
        }
    }
    return FALSE;
}


/**
 * check a char is any of a set of characters
 */
static __inline BOOL
SStr_IsAnyChar2(const char ch, const char *accept, int len) {
    SLOG_ASSERT(accept);
    while (*accept && len--) {
        if (*accept++ == ch) {
            return TRUE;
        }
    }
    return FALSE;
}


/**
 * search a string for any of a set of characters
 *
 * The strpbrk() function locates the first occurrence in the string s of any
 * of the characters in the string accept.
 *
 * @return  returns a pointer to the character in s that matches one of the
 *          characters in accept, or NULL if no such character is found.
 * @see     strpbrk()
 */
static __inline char *
SStr_Strpbrk(const char *s, const char *accept) {
    if (unlikely(! s)) {
        return (char *) NULL;
    }

    while (*s) {
        if (SStr_IsAnyChar(*s, accept)) {
            return (char *) s;
        }
        ++s;
    }
    return (char *) NULL;
}


/**
 * search a string for any of a set of characters reverse
 *
 * @return  returns a pointer to the character in s that matches one of the
 *          characters in accept, or NULL if no such character is found.
 */
static __inline char *
SStr_StrpbrkReverse(const char *s, const char *accept) {
    int32   endPos = 0;

    if (unlikely(! s)) {
        return (char *) NULL;
    }

    endPos = strlen(s) - 1;
    while (endPos >= 0) {
        if (SStr_IsAnyChar(s[endPos], accept)) {
            return (char *) &s[endPos];
        }
        endPos--;
    }
    return (char *) NULL;
}


/**
 * extract token from string, and return the end of token
 *
 * 注意：
 * 對於theEnd的處理，要注意是否已考慮到對以下兩種特殊情況的處理：
 * 1、delim位於字串首。這時*theEnd == return
 * 2、若字串不是以delim結尾的，當最後一次返回時，*theEnd == NULL
 */
static __inline char*
SStr_Strsep2(char **ppString, char **ppTokenEnd, const char *pDelim) {
    char    *pBegin = (char *) NULL;
    char    *pEnd = (char *) NULL;

    SLOG_ASSERT(ppString && pDelim && *pDelim);

    pBegin = *ppString;
    if (unlikely(! pBegin || ! *pBegin)) {
        *ppString = NULL;
        if (ppTokenEnd) {
            *ppTokenEnd = NULL;
        }
        return (char *) pBegin;
    }

    if (pDelim[1] == '\0') {
        if (*pBegin == pDelim[0]) {
            pEnd = pBegin;
        } else {
            pEnd = strchr(pBegin + 1, pDelim[0]);
        }
    } else {
        pEnd = SStr_Strpbrk(pBegin, pDelim);
    }

    if (pEnd) {
        *ppString = pEnd + 1;

        if (ppTokenEnd) {
            *ppTokenEnd = pEnd;
        } else {
            *pEnd = '\0';
        }
    } else {
        *ppString = NULL;

        if (ppTokenEnd) {
            *ppTokenEnd = NULL;
        }
    }

    return pBegin;
}


/**
 * extract token from string
 *
 * If *stringp is  NULL, the strsep() function returns NULL and does
 * nothing else.  Otherwise, this function finds the first token in the
 * string *stringp, where tokens are delimited by symbols in the string
 * delim. This token is terminated with a '\0' character (by overwriting
 * the delimiter) and *stringp  is updated to point past the token.
 * In case no delimiter was found, the token is taken to be the entire
 * string *stringp, and *stringp is made NULL.
 *
 * @return  The strsep() function returns a pointer to the token, that is,
 *          it returns the original value of *stringp.
 * @see     strsep()
 */
static __inline char*
SStr_Strsep(char **stringp, const char *delim) {
    return SStr_Strsep2(stringp, (char **) NULL, delim);
}


/**
 * 返回字串是否是空字串
 *
 * @param   pStr    待校驗字串
 * @return  TRUE, 為空; FALSE, 不為空
 */
static __inline BOOL
SStr_IsEmpty(const char *pStr) {
    return (! (pStr && *pStr));
}


/**
 * 返回字串是否是空字串
 *
 * @param   pStr    待校驗字串
 * @return  TRUE, 為空; FALSE, 不為空
 */
static __inline BOOL
SStr_IsBlank(const char *pStr) {
    if (pStr) {
        while (*pStr) {
            if (! SPK_ISSPACE(*pStr)) {
                return FALSE;
            }
            pStr++;
        }
    }
    return TRUE;
}


/**
 * 返回字串是否全是有效的ASCII可見字元 (不能包含空格和不可見字元等)
 *
 * @param   pStr    待校驗字串
 * @return  TRUE, 有效; FALSE, 無效
 */
static __inline BOOL
SStr_IsVisibleAsciiString(const char *pStr) {
    if (unlikely(SStr_IsEmpty(pStr))) {
        return FALSE;
    }

    while (*pStr) {
        if (unlikely(*pStr < '!' || *pStr > '~')) {
            return FALSE;
        }
        pStr++;
    }

    return TRUE;
}


/**
 * 返回字串是否是有效的MD5字串
 * (字母+數字)
 *
 * @param   pStr    待校驗字串
 * @return  TRUE, 有效; FALSE, 無效
 */
static __inline BOOL
SStr_IsValidMd5String(const char *pStr) {
    static const int32  _MD5_STRING_LENGTH = 32;
    int32               i = 0;

    if (unlikely(SStr_IsEmpty(pStr))) {
        return FALSE;
    }

    while (pStr[i]) {
        if (unlikely(! SPK_ISALNUM(pStr[i]))) {
            return FALSE;
        }
        i++;
    }

    return i == _MD5_STRING_LENGTH ? TRUE : FALSE;
}


/**
 * 返回字串是否是有效的密碼串
 * (字母+數字, 以及 '@._-' 這幾個郵箱地址相關的特殊字元)
 *
 * @param   pStr    待校驗字串
 * @return  TRUE, 有效; FALSE, 無效
 */
static __inline BOOL
SStr_IsValidPasswdString(const char *pStr) {
    if (unlikely(SStr_IsEmpty(pStr))) {
        return FALSE;
    }

    while (*pStr) {
        if (unlikely(! SPK_ISALNUM(*pStr)
                && ! SStr_IsAnyChar(*pStr, "@._-"))) {
            return FALSE;
        }
        pStr++;
    }

    return TRUE;
}


/**
 * 校驗密碼強度
 * (只能包含字母+數字, 以及 '@._-' 這幾個郵箱地址相關的特殊字元)
 * (若指定密碼強度或密碼最小長度, 須符合對應限制條件)
 *
 * @param   pStr          待校驗字串
 * @param   strength      密碼強度, 0表示無限制
 * @param   minLength     密碼最小長度, 0表示無限制
 * @return  等於0: 有效; 大於0: 密碼強度弱; 小於0: 密碼包含無效字元
 */
static __inline int32
SStr_CheckPasswdStrength(const char *pStr, int32 strength, int32 minLength) {
    static const int32  _STRONGEST_PASSWD_STRENGTH = 4;
    int32               uppercaseCnt = 0;
    int32               lowercaseCnt = 0;
    int32               digitCnt = 0;
    int32               symbolCnt = 0;
    int32               totalLength = 0;
    int32               strengthLevel = 0;

    if (unlikely(SStr_IsEmpty(pStr))) {
        return NEG(EINVAL);
    }

    while (*pStr) {
        if (SPK_ISUPPER(*pStr)) {
            uppercaseCnt++;
        } else if (SPK_ISLOWER(*pStr)) {
            lowercaseCnt++;
        } else if (SPK_ISDIGIT(*pStr)) {
            digitCnt++;
        } else if (SStr_IsAnyChar(*pStr, "@._-")) {
            symbolCnt++;
        } else {
            return NEG(EINVAL);
        }
        pStr++;
    }

    totalLength = uppercaseCnt + lowercaseCnt + digitCnt + symbolCnt;
    strengthLevel = (uppercaseCnt > 0 ? 1 : 0)
            + (lowercaseCnt > 0 ? 1 : 0)
            + (digitCnt > 0 ? 1 : 0)
            + (symbolCnt > 0 ? 1 : 0);
    if (unlikely((minLength > 0 && totalLength < minLength)
            || strengthLevel < SPK_MIN(strength, _STRONGEST_PASSWD_STRENGTH))) {
        return EINVAL;
    }

    return 0;
}


/**
 * 若字串為空則返回指定的值
 */
static __inline const char*
SStr_SwitchBlankStr(const char *s, const char *v) {
    return SStr_IsBlank(s) ? v : s;
}


/**
 * 返回跳過左端空格後的字串
 *
 * @param   pStr    字串
 * @return  跳過左端空格後的字串指標
 */
static __inline const char*
SStr_Ltrim(const char *pStr) {
    if (unlikely(! pStr)) {
        return (const char *) NULL;
    }

    while (SPK_ISSPACE(*pStr)) {
        pStr++;
    }
    return pStr;
}


/**
 * 跳過字串起始的空格和'0'
 *
 * @param   pStr    字串
 * @return  跳過左端空格和'0'後的字串指標
 */
static __inline const char*
SStr_LtrimZero(const char *pStr) {
    char        ch = 0;
    char        prev = 0;

    if (unlikely(! pStr)) {
        return (const char *) NULL;
    }

    while ((ch = *pStr) == '0' || SPK_ISSPACE(ch)) {
        pStr++;
        prev = ch;
    }

    if ((*pStr == 'x' || *pStr == '.') && prev == '0') {
        pStr--;
    }
    return pStr;
}


/**
 * 去除字串右端的空格
 *
 * @param   pStr    字串
 * @return  去除空格後的字串
 */
static __inline char*
SStr_RtrimRude(char *pStr) {
    int32   endPos = 0;

    if (unlikely(! pStr)) {
        return (char *) NULL;
    }

    endPos = strlen(pStr) - 1;
    while (endPos >= 0 && SPK_ISSPACE(pStr[endPos])) {
        endPos--;
    }

    pStr[++endPos] = '\0';
    return pStr;
}


/**
 * 去除字串前後端的空格
 *
 * @param   pStr    字串
 * @return  去除空格後的字串
 */
static __inline char*
SStr_TrimRude(char *pStr) {
    return SStr_RtrimRude((char *) SStr_Ltrim(pStr));
}


/**
 * 返回轉換為大寫後的字串
 */
static __inline char*
SStr_ToUpper(char *pStr) {
    char    *pPtr = pStr;

    if (unlikely(! pStr)) {
        return (char *) NULL;
    }

    while (*pPtr) {
        *pPtr = SPK_TOUPPER((int32) *pPtr);
        pPtr++;
    }
    return pStr;
}


/**
 * 返回轉換為大寫後的字串
 */
static __inline char*
SStr_ToUpperR(char *pBuf, const char *pStr) {
    int32   j = 0;

    SLOG_ASSERT(pBuf);
    if (unlikely(! pStr)) {
        *pBuf = '\0';
        return pBuf;
    }

    while (pStr[j]) {
        pBuf[j] = SPK_TOUPPER((int32) pStr[j]);
        j++;
    }
    pBuf[j] = '\0';

    return pBuf;
}


/**
 * 返回轉換為小寫後的字串
 */
static __inline char*
SStr_ToLower(char *pStr) {
    char    *pPtr = pStr;

    if (unlikely(! pStr)) {
        return (char *) NULL;
    }

    while (*pPtr != '\0') {
        *pPtr = SPK_TOLOWER((int32) *pPtr);
        pPtr++;
    }
    return pStr;
}


/**
 * 返回轉換為小寫後的字串
 */
static __inline char*
SStr_ToLowerR(char *pBuf, const char *pStr) {
    char    *pPtr = pBuf;
    int32   j = 0;

    SLOG_ASSERT(pBuf);
    if (unlikely(! pStr)) {
        *pBuf = '\0';
        return pBuf;
    }

    while (pStr[j]) {
        pPtr[j] = SPK_TOLOWER((int32) pStr[j]);
        j++;
    }

    pPtr[j] = '\0';
    return pPtr;
}


/**
 * 拷貝指定長度的字串
 * <p>需保證快取有足夠的空間(maxStrlen + 1)</p>
 *
 * @param   maxStrlen   最大有效字元長度(不包括結尾的'\0')，即buf的長度需至少
 *                      為 maxStrlen + 1
 */
static __inline char*
SStr_StrCopy(char *pBuf, const char *pStr, int32 maxStrlen) {
    SLOG_ASSERT(pBuf);

    if (likely(pStr && maxStrlen > 0)) {
        strncpy(pBuf, pStr, maxStrlen);
        pBuf[maxStrlen] = '\0';
    } else {
        *pBuf = '\0';
    }
    return pBuf;
}


/**
 * 從字串中拷貝指定位置的子字串
 *
 * @param[out]  pBuf        用於輸出資料的快取區指標
 * @param       pStr        待拷貝的字串
 * @param       from        子字串的開始位置 (從0開始計數, 小於等於0則從頭開始複製)
 * @param       subLen      子字串的長度 (小於等於0表示從末尾開始計數的子字串結束位置)
 *                          - 大於0, 子字串的長度
 *                          - 等於0, 複製從 from 至末尾的所有字元
 *                          - 小於0, 末尾開始計數的子字串結束位置
 * @return      返回複製到字串
 */
static __inline char*
SStr_SubStrCopy(char *pBuf, const char *pStr, int32 from, int32 subLen) {
    int32               totalLen = 0;

    SLOG_ASSERT(pBuf);
    if (unlikely(SStr_IsEmpty(pStr))) {
        *pBuf = '\0';
        return pBuf;
    }

    totalLen = strlen(pStr);
    if (from < 0) {
        from = 0;
    } else if (unlikely(from >= totalLen)) {
        *pBuf = '\0';
        return pBuf;
    }

    if (subLen <= 0) {
        subLen = (totalLen + subLen) - from;
    } else {
        subLen = SPK_MIN(subLen, totalLen - from);
    }

    if (likely(subLen > 0)) {
        SStr_StrCopy(pBuf, pStr + from, subLen);
    } else {
        *pBuf = '\0';
    }
    return pBuf;
}


/**
 * 連線兩個字串到新字串中
 * <p>需保證快取有足夠的空間(maxStrlen + 1)</p>
 *
 * @param   maxStrlen   最大有效字元長度(不包括結尾的'\0')，即buf的長度需至少
 *                      為 maxStrlen + 1
 */
static __inline char*
SStr_StrCat(char *pBuf, const char *s1, const char *s2, int32 maxStrlen) {
    SLOG_ASSERT(pBuf);

    if (likely(s1)) {
        SStr_StrCopy(pBuf, s1, maxStrlen);
    } else {
        *pBuf = '\0';
    }

    if (likely(s2)) {
        return strncat(pBuf, s2, maxStrlen - strlen(pBuf));
    }
    return pBuf;
}


/**
 * 連線字串並將字串指標移動到新字串末尾
 *
 * @return 原字串地址
 */
static __inline char*
SStr_StrCatP(char **ppString, const char *s) {
    char    *pBegin = (char *) NULL;
    char    *pEnd = (char *) NULL;

    if (unlikely(! ppString || ! *ppString)) {
        return (char *) NULL;
    } else if (unlikely(! s)) {
        return *ppString;
    } else {
        pBegin = pEnd = *ppString;
    }

    while (*pEnd) {
        pEnd++;
    }

    while (*s) {
        *pEnd++ = *s++;
    }

    *pEnd = '\0';
    *ppString = pEnd;

    return pBegin;
}


/**
 * 連線字元和字串
 * <p>需保證快取有足夠的空間(maxStrlen + 1)</p>
 *
 * @param   maxStrlen   引數 pStr 的最大字串長度，buf的長度需至少為 maxStrlen + 1
 */
static __inline char*
SStr_StrCatChStr(char *pBuf, char ch, const char *pStr, int32 maxStrlen) {
    SLOG_ASSERT(pBuf && pStr);

    *pBuf = ch;
    memcpy(pBuf + 1, pStr, maxStrlen);

    pBuf[maxStrlen + 1] = '\0';
    return pBuf;
}


/**
 * 拷貝字串並去除空格
 * <p>需保證快取有足夠的空間(maxStrlen + 1)</p>
 *
 * @param   maxStrlen   最大有效字元長度(不包括結尾的'\0')，即buf的長度需至少
 *                      為 maxStrlen + 1
 */
static __inline char*
SStr_StrTrimCopy(char *pBuf, const char *pStr, int32 maxStrlen) {
    char    *pPtr = pBuf;

    SLOG_ASSERT(pPtr);
    if (unlikely(SStr_IsEmpty(pStr))) {
        *pBuf = '\0';
        return pBuf;
    }

    while (SPK_ISSPACE(*pStr)) {
        pStr++;
    }

    while (*pStr && maxStrlen-- != 0) {
        *pPtr++ = *pStr++;
    }

    do {
        *pPtr-- = '\0';
    } while (pPtr >= pBuf && SPK_ISSPACE(*pPtr));

    pPtr++;
    *pPtr = '\0';

    return pBuf;
}


/**
 * 先拷貝字串再去除空格
 * <p>需保證快取有足夠的空間(maxStrlen + 1)</p>
 *
 * @param   maxStrlen   最大有效字元長度(不包括結尾的'\0')，即buf的長度需至少
 *                      為 maxStrlen + 1
 */
static __inline char*
SStr_StrFixedLengthTrimCopy(char *pBuf, const char *pStr, int32 maxStrlen) {
    char    *pPtr = pBuf;

    SLOG_ASSERT(pPtr);
    if (unlikely(! pStr)) {
        *pBuf = '\0';
        return pBuf;
    }

    while (SPK_ISSPACE(*pStr) && maxStrlen != 0) {
        pStr++;
        maxStrlen--;
    }

    while (*pStr && maxStrlen-- != 0) {
        *pPtr++ = *pStr++;
    }

    do {
        pPtr--;
    } while (pPtr >= pBuf && SPK_ISSPACE(*pPtr));

    pPtr++;
    *pPtr = '\0';

    return pBuf;
}


/**
 * 以右對齊的方式拷貝字串並去除空格
 * <p>需保證快取有足夠的空間(maxlen + 1)</p>
 *
 * @param   alignedLen  最大有效字元長度(不包括結尾的'\0')，即buf的長度需至少
 *                      為 alignedLen + 1
 */
static __inline char*
SStr_StrRightAlignmentCopy(char *pBuf, const char *pStr, int32 alignedLen,
        char leftFiller) {
    const char  *pPtr = (const char *) NULL;
    int32       len = alignedLen;

    if (unlikely(alignedLen <= 0)) {
        return SStr_StrTrimCopy(pBuf, pStr, alignedLen);
    }

    SLOG_ASSERT(pBuf);
    if (unlikely(! pStr)) {
        *pBuf = '\0';
        return pBuf;
    }

    while (SPK_ISSPACE(*pStr)) {
        pStr++;
    }

    pPtr = pStr;
    while (*pPtr && len != 0) {
        pPtr++;
        len--;
    }

    do {
        pPtr--;
        len++;
    } while (len <= alignedLen && SPK_ISSPACE(*pPtr));
    len--;

    memset(pBuf, leftFiller, len);
    memcpy(pBuf + len, pStr, alignedLen - len);

    pBuf[alignedLen] = '\0';
    return pBuf;
}


/**
 * 跳過空字元
 */
static __inline char*
SStr_SkipSpaces(char **ppStr) {
    SLOG_ASSERT(ppStr);

    while (SPK_ISSPACE(**ppStr)) {
        (*ppStr) ++;
    }
    return *ppStr;
}


/**
 * 從字串末端反向跳過空字元
 */
static __inline void
SStr_SkipSpacesReverse(char **ppEnd, char *pBegin) {
    char    *pOriginEnd;

    SLOG_ASSERT(ppEnd);

    pOriginEnd = *ppEnd;
    while (*ppEnd > pBegin && SPK_ISSPACE(**ppEnd)) {
        (*ppEnd) --;
    }

    if (*ppEnd < pOriginEnd) {
        *((*ppEnd) + 1) = '\0';
    }

    if (SPK_ISSPACE(**ppEnd)) {
        **ppEnd = '\0';
    } else {
        (*ppEnd) ++;
    }
}


/**
 * 跳過所有字元直到指定的字串末尾
 *
 * @param   ppStr       <in/out: char**> 待處理字串的指標的指標
 * @param   pSkipKey    <char*> 待跳過的字串指標
 * @return  小於0, 未找到指定的字串; 大於等於0, 已跳過字串的起始位置(相對值)
 */
static __inline int32
SStr_SkipString(char **ppStr, const char *pSkipKey) {
    char    *pStrFound = (char*) NULL;
    int32   offset = 0;

    SLOG_ASSERT(ppStr && pSkipKey);

    if (! (pStrFound = strstr(*ppStr, pSkipKey))) {
        return NEG(ENOENT);
    }

    offset = pStrFound - *ppStr;
    *ppStr = pStrFound + strlen(pSkipKey);

    return offset;
}


/**
 * 替換字串中的指定字元
 *
 * @param   pStr    待處理的字串
 * @return  已替換的字元數量
 */
static __inline int32
SStr_ReplaceChar(char *pStr, const char c1, const char c2, int32 n) {
    int32   count = 0;

    SLOG_ASSERT(pStr);

    while (*pStr && n) {
        if (*pStr == c1) {
            *pStr = c2;
            n--;
            count++;
        }
        pStr ++;
    }
    return count;
}


/**
 * 從後面開始替換字串中的指定字元
 *
 * @param   pStr    待處理的字串
 * @return
 */
static __inline int32
SStr_ReplaceCharReverse(char *pStr, const char c1, const char c2, int32 n) {
    int32   endPos = 0;
    int32   count = 0;

    SLOG_ASSERT(pStr);

    endPos = strlen(pStr) - 1;
    while (endPos >= 0 && n) {
        if (pStr[endPos] == c1) {
            pStr[endPos] = c2;
            n--;
            count++;
        }
        endPos--;
    }
    return count;
}
/* -------------------------           */


#ifdef __cplusplus
}
#endif

#endif  /* _SPK_STRINGS_H */
