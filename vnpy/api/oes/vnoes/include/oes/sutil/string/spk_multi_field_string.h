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
 * @file    spk_multi_field_string.h
 *
 * 多域字串(如CSV字串等)處理函式
 *
 * @version $Id$
 * @since   2012/01/05
 */


#ifndef _SPK_MULTI_FIELD_STRING_H
#define _SPK_MULTI_FIELD_STRING_H


#include    <sutil/types.h>


#ifdef __cplusplus
extern "C" {
#endif


/* ===================================================================
 * 多域字串相關函式的定義
 * =================================================================== */

/* 解析多域字串到陣列中 */
int32   SStr_ParseMFStringToArray2(char *pArr[], int32 maxFieldNumber,
            char **ppPtr, const char *pDelimChars, BOOL isReserveSpace);


/* 解析多域字串到陣列中 */
int32   SStr_ParseMFStringToArray(char *pArr[], int32 maxFieldNumber,
            char *pStr, const char *pDelimChars);

/* 解析多域字串到陣列中 */
int32   SStr_ParseMFStringToArrayThroughEnd2(char *pArr[], int32 maxFieldNumber,
            char **ppPtr, char delimChar, char endChar, BOOL isReserveSpace);

/* 解析多域字串到陣列中 */
int32   SStr_ParseMFStringToArrayThroughEnd(char *pArr[], int32 maxFieldNumber,
            char **ppPtr, char delimChar, char endChar);
/* -------------------------           */


#ifdef __cplusplus
}
#endif

#endif  /* _SPK_MULTI_FIELD_STRING_H */
