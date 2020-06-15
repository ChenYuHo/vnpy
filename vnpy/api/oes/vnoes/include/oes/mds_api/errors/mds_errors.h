/*
 * Copyright 2016 the original author or authors.
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
 * @file    mds_errors.h
 *
 * 通訊介面錯誤資訊定義
 *
 * @version 0.15.6.13   2018/07/16
 *          - 新增錯誤碼定義
 *              - 1031, 非法的加密型別（MDSERR_ILLEGAL_ENCRYPT_TYPE）
 *              - 1033, 無可用節點（MDSERR_NO_AVAILABLE_NODE）
 * @version 0.15.7.6    2018/10/16
 *          - 新增錯誤碼定義
 *              - 1035, 非法的產品型別（MDSERR_ILLEGAL_PRODUCT_TYPE）
 * @version 0.15.8_RC3  2019/01/14
 *          - 調整錯誤描述
 *              - 1007, 非服務開放時間（MDSERR_NOT_TRADING_TIME）
 *              - 1022, 尚不支援或尚未開通此業務（MDSERR_NOT_SUPPORT）
 * @version 0.15.9      2019/03/18
 *          - 新增錯誤碼定義
 *              - 1029, 密碼未改變（MDSERR_PASSWORD_UNCHANGED）
 *              - 1030, 非法的來源分類（MDSERR_ILLEGAL_SOURCE_TYPE）
 *              - 1032, 非法的客戶端裝置序列號 (MDSERR_ILLEGAL_DRIVER)
 *              - 1034, 密碼強度不足（MDSERR_PASSWORD_WEAK_STRENGTH）
 *              - 1036, 未通過黑白名單檢查 (MDSERR_WBLIST_CHECK_FAILURE)
 *
 * @since   2016/1/3
 */


#ifndef _MDS_PROTOCOL_ERRORS_H
#define _MDS_PROTOCOL_ERRORS_H


#include    <sutil/net/spk_errmsg_base_define.h>


#ifdef __cplusplus
extern "C" {
#endif


/*
 * 通訊介面錯誤定義表
 */
extern  SErrMsgT __SPK_DLL_IMPORT               __ERRS_mdsApiErrors[];
/* -------------------------           */


/*
 * 通用錯誤定義
 */
/** 1001, 報文格式錯誤 */
#define MDSERR_MSG_FORMAT                       (&__ERRS_mdsApiErrors[0])
/** 1002, 當前主機不是主節點 */
#define MDSERR_NOT_LEADER                       (&__ERRS_mdsApiErrors[1])
/** 1003, 主存庫操作失敗 */
#define MDSERR_SDB_FAILURE                      (&__ERRS_mdsApiErrors[2])
/** 1004, 基礎資料不匹配，無法更新資料 */
#define MDSERR_UPDATE_EPERM                     (&__ERRS_mdsApiErrors[3])
/** 1005, 功能尚不支援/協議版本不相容 */
#define MDSERR_INCOMPATIBLE_PROTOCOL_VERSION    (&__ERRS_mdsApiErrors[4])
/** 1006, 資料不存在 */
#define MDSERR_NOT_FOUND                        (&__ERRS_mdsApiErrors[5])
/** 1007, 非服務開放時間 */
#define MDSERR_NOT_TRADING_TIME                 (&__ERRS_mdsApiErrors[6])
/** 1008, 非法的定位遊標 */
#define MDSERR_ILLEGAL_POSITION                 (&__ERRS_mdsApiErrors[7])
/** 1009, 非法的客戶端登入使用者名稱稱 */
#define MDSERR_ILLEGAL_CLIENT_NAME              (&__ERRS_mdsApiErrors[8])
/** 1010, 非法的證券程式碼 */
#define MDSERR_ILLEGAL_SECURITY_ID              (&__ERRS_mdsApiErrors[9])
/** 1011, 非法的客戶程式碼 */
#define MDSERR_ILLEGAL_CUST_ID                  (&__ERRS_mdsApiErrors[10])
/** 1012, 非法的客戶端型別 */
#define MDSERR_ILLEGAL_CLIENT_TYPE              (&__ERRS_mdsApiErrors[11])
/** 1013, 客戶端已被禁用 */
#define MDSERR_CLIENT_DISABLED                  (&__ERRS_mdsApiErrors[12])
/** 1014, 客戶端密碼不正確 */
#define MDSERR_CLIENT_PASSWORD_INVALID          (&__ERRS_mdsApiErrors[13])
/** 1015, 客戶端重複登入 */
#define MDSERR_CLIENT_REPEATED_LOGON            (&__ERRS_mdsApiErrors[14])
/** 1016, 客戶端連線數量過多 */
#define MDSERR_CLIENT_CONNECTIONS_LIMIT         (&__ERRS_mdsApiErrors[15])
/** 1017, 客戶端未經授權操作他人賬戶 */
#define MDSERR_CLIENT_NOT_AUTHORIZED            (&__ERRS_mdsApiErrors[16])
/** 1018, 資料超出修改範圍 */
#define MDSERR_DATA_OUTOF_RANGE                 (&__ERRS_mdsApiErrors[17])
/** 1019, 非法的應用系統名稱 */
#define MDSERR_ILLEGAL_APPNAME                  (&__ERRS_mdsApiErrors[18])
/** 1020, 請求條件有衝突 */
#define MDSERR_CONFLICT_REQ_CONDITION           (&__ERRS_mdsApiErrors[19])
/** 1021, 客戶端IP/MAC地址格式錯誤 */
#define MDSERR_ILLEGAL_IP_MAC_FORMAT            (&__ERRS_mdsApiErrors[20])
/** 1022, 尚不支援或尚未開通此業務 */
#define MDSERR_NOT_SUPPORT                      (&__ERRS_mdsApiErrors[21])
/** 1026, 流量超出限制範圍 */
#define MDSERR_TRAFFIC_CONTROL_OUTOF_RANGE      (&__ERRS_mdsApiErrors[25])
/** 1027, 禁止使用API登入 */
#define MDSERR_API_FORBIDDEN                    (&__ERRS_mdsApiErrors[26])
/** 1029, 密碼未改變 */
#define MDSERR_PASSWORD_UNCHANGED               (&__ERRS_mdsApiErrors[28])
/** 1030, 非法的來源分類 */
#define MDSERR_ILLEGAL_SOURCE_TYPE              (&__ERRS_mdsApiErrors[29])
/** 1031, 非法的加密型別 */
#define MDSERR_ILLEGAL_ENCRYPT_TYPE             (&__ERRS_mdsApiErrors[30])
/** 1032, 非法的客戶端裝置序列號 */
#define MDSERR_ILLEGAL_DRIVER                   (&__ERRS_mdsApiErrors[31])
/** 1033, 無可用節點 */
#define MDSERR_NO_AVAILABLE_NODE                (&__ERRS_mdsApiErrors[32])
/** 1034, 密碼強度不足 */
#define MDSERR_PASSWORD_WEAK_STRENGTH           (&__ERRS_mdsApiErrors[33])
/** 1035, 非法的產品型別 */
#define MDSERR_ILLEGAL_PRODUCT_TYPE             (&__ERRS_mdsApiErrors[34])
/** 1036, 未通過黑白名單檢查 */
#define MDSERR_WBLIST_CHECK_FAILURE             (&__ERRS_mdsApiErrors[35])
/* -------------------------           */


/*
 * MDS相關錯誤
 */
/** 1301, 行情訂閱失敗 */
#define MDSERR_SUBSCRIBE_FAILED                 (&__ERRS_mdsApiErrors[40])
/* -------------------------           */


#ifdef __cplusplus

}
#endif

#endif  /* _MDS_PROTOCOL_ERRORS_H */
