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
 * @file    spk_string_var.h
 *
 * 字串變數處理, 用於替換字串(如, 配置資訊等)中的字串變數
 * 以字元'@'起始的字串變數被作為應用內部預定義變數處理
 * 以字元'$'起始的字串變數被作為上下文環境變數和系統預定義變數處理（優先使用內部預定義變數）
 *
 * 支援如下樣式的字串變數:
 * - ${var}
 * - ${var=string}  Use string and assign string to var
 * - ${var:-string} Use var if set, otherwise use string
 * - ${var:=string} Use var if set, otherwise use string and assign string to var
 * - ${var:+string} Use string if var if set, otherwise use nothing
 * - ${var:!string} Use string if var if unset, otherwise use nothing
 *
 * 以及字串變數的巢狀如:
 * - ${VAR:=${VAR2:+string_${VAR3:-string}_string}}
 *
 * @version 1.1 2015/04/10
 * @since   2012/01/05
 */


#ifndef _SPK_STRING_VAR_H
#define _SPK_STRING_VAR_H


#include    <sutil/types.h>


#ifdef __cplusplus
extern "C" {
#endif


/*
 * 常量定義
 */
#define STRVAR_MAX_NAME_LENGTH      (128)       /**< 巨集名稱最大長度 */
#define STRVAR_PREFIX_MIXED         '$'
#define STRVAR_PREFIX_BUILDIN       '@'
#define STRVAR_LEFT_BOUND           '{'
#define STRVAR_RIGHT_BOUND          '}'
#define STRVAR_MIDDLE_BOUND         ':'
/* -------------------------           */


/*
 * 字串變數取值函式原型定義
 */

/**
 * 字串變數取值函式原型
 */
typedef const char* (*F_STRVAR_GETTER_T) (void);

/**
 * 可接受引數的巨集取值函式原型
 */
typedef void (*F_STRVAR_SETTER_T) (const char *pValue);
/* -------------------------           */


/**
 * 預定義的字串變數定義結構
 *
 */
typedef struct _SStrVar {
    /** 字串變數名稱 */
    char                name[STRVAR_MAX_NAME_LENGTH];

    /** 字串變數取值函式 */
    F_STRVAR_GETTER_T   pValueGetter;

    /** 字串變數設定函式 */
    F_STRVAR_SETTER_T   pValueSetter;
} SStrVarT;


/* 結構體初始化值定義 */
#define NULLOBJ_SSTR_VAR                \
        {0}, 0, 0
/* -------------------------           */


/*
 * 函式宣告
 */

/* 通過變數名稱返回字串變數定義 */
const SStrVarT*
        SStr_GetVarItemByName(
                const SStrVarT *pVarItems,
                int32 varItemsNumber,
                const char *pVarName);

/* 通過變數名稱返回字串變數的值 */
const char*
        SStr_GetVarValueByName(
                const SStrVarT *pVarItems,
                int32 varItemsNumber,
                const char *pVarName,
                BOOL isSystemEnvAble);

/* 設定字串變數的值 */
void    SStr_SetVarValueByName(
                const SStrVarT *pVarItems,
                int32 varItemsNumber,
                const char *pVarName,
                const char *pVarValue,
                BOOL isSystemEnvAble);

/* 替換所有的字串變數 */
char*   SStr_ReplaceAllVar(
                char *pBuf,
                const char *pTarget);

/* 替換所有的字串變數 */
char*   SStr_ReplaceAllVar2(
                char *pBuf,
                const char *pTarget,
                const SStrVarT *pVarItems,
                int32 varItemsNumber);

/* 替換所有的字串變數 */
char*   SStr_ReplaceAllVar3(
                char *pBuf,
                const char *pTarget,
                const SStrVarT *pVarItems,
                int32 varItemsNumber,
                BOOL isSystemEnvAble);
/* -------------------------           */


#ifdef __cplusplus
}
#endif

#endif  /* _SPK_STRING_VAR_H */
