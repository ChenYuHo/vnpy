/*
 * Copyright 2009-2014 the original author or authors.
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
 * @file    oes_errors.h
 *
 * 通訊介面錯誤資訊定義
 *
 * @version 0.15.6.13   2018/07/16
 *          - 新增錯誤碼定義
 *              - 1029, 密碼未改變（OESERR_PASSWORD_UNCHANGED）
 *              - 1030, 非法的來源分類（OESERR_ILLEGAL_SOURCE_TYPE）
 *              - 1031, 非法的加密型別（OESERR_ILLEGAL_ENCRYPT_TYPE）
 *              - 1032, 非法的客戶端裝置序列號（OESERR_ILLEGAL_DRIVER）
 *              - 1033, 無可用節點（OESERR_NO_AVAILABLE_NODE）
 *              - 1271, 股東賬戶沒有交易存託憑證的許可權（OESERR_NO_CDR_PERM）
 *              - 1272, 股東賬戶沒有交易創新企業股票的許可權（OESERR_NO_INNOVATION_PERM）
 * @version 0.15.5.15   2018/08/14
 *          - 新增錯誤碼定義
 *              - 1273, 非法的出入金轉賬型別（OESERR_ILLEGAL_FUND_TRSF_TYPE）
 * @version 0.15.7.6    2018/10/16
 *          - 新增錯誤碼定義
 *              - 1035, 非法的產品型別（OESERR_ILLEGAL_PRODUCT_TYPE）
 *              - 1274, 股東賬戶沒有交易滬倫通存託憑證的許可權（OESERR_NO_HLTCDR_PERM）
 * @version 0.15.8_RC3  2019/01/14
 *          - 調整錯誤描述
 *              - 1007, 非服務開放時間（OESERR_NOT_TRADING_TIME）
 *              - 1022, 尚不支援或尚未開通此業務（OESERR_NOT_SUPPORT）
 * @version 0.15.9      2019/03/12
 *          - 新增錯誤碼定義
 *              - 1275, 股東賬戶沒有交易科創板的許可權（OESERR_NO_KSH_PERM）
 *              - 1036, 未通過黑白名單檢查（OESERR_WBLIST_CHECK_FAILURE）
 *
 * @since   2015/07/30
 */


#ifndef _OES_PROTOCOL_ERRORS_H
#define _OES_PROTOCOL_ERRORS_H


#include    <sutil/net/spk_errmsg_base_define.h>


#ifdef __cplusplus
extern "C" {
#endif


/**
 * 通訊介面錯誤定義表
 */
extern  SErrMsgT __SPK_DLL_IMPORT               __ERRS_oesApiErrors[];
/* -------------------------           */


/*
 * 通用錯誤定義
 */
/** 1001, 報文格式錯誤 */
#define OESERR_MSG_FORMAT                       (&__ERRS_oesApiErrors[0])
/** 1002, 當前主機不是主節點 */
#define OESERR_NOT_LEADER                       (&__ERRS_oesApiErrors[1])
/** 1003, 主存庫操作失敗 */
#define OESERR_SDB_FAILURE                      (&__ERRS_oesApiErrors[2])
/** 1004, 基礎資料不匹配，無法更新資料 */
#define OESERR_UPDATE_EPERM                     (&__ERRS_oesApiErrors[3])
/** 1005, 協議版本不相容 */
#define OESERR_INCOMPATIBLE_PROTOCOL_VERSION    (&__ERRS_oesApiErrors[4])
/** 1006, 資料不存在 */
#define OESERR_NOT_FOUND                        (&__ERRS_oesApiErrors[5])
/** 1007, 非服務開放時間 */
#define OESERR_NOT_TRADING_TIME                 (&__ERRS_oesApiErrors[6])
/** 1008, 非法的定位遊標 */
#define OESERR_ILLEGAL_POSITION                 (&__ERRS_oesApiErrors[7])
/** 1009, 非法的客戶端登入使用者名稱稱 */
#define OESERR_ILLEGAL_CLIENT_NAME              (&__ERRS_oesApiErrors[8])
/** 1010, 非法的證券程式碼 */
#define OESERR_ILLEGAL_SECURITY_ID              (&__ERRS_oesApiErrors[9])
/** 1011, 非法的客戶程式碼 */
#define OESERR_ILLEGAL_CUST_ID                  (&__ERRS_oesApiErrors[10])
/** 1012, 非法的客戶端型別 */
#define OESERR_ILLEGAL_CLIENT_TYPE              (&__ERRS_oesApiErrors[11])
/** 1013, 客戶端已被禁用 */
#define OESERR_CLIENT_DISABLED                  (&__ERRS_oesApiErrors[12])
/** 1014, 客戶端密碼不正確 */
#define OESERR_CLIENT_PASSWORD_INVALID          (&__ERRS_oesApiErrors[13])
/** 1015, 客戶端重複登入 */
#define OESERR_CLIENT_REPEATED_LOGON            (&__ERRS_oesApiErrors[14])
/** 1016, 客戶端連線數量過多 */
#define OESERR_CLIENT_CONNECTIONS_LIMIT         (&__ERRS_oesApiErrors[15])
/** 1017, 客戶端未經授權操作他人賬戶 */
#define OESERR_CLIENT_NOT_AUTHORIZED            (&__ERRS_oesApiErrors[16])
/** 1018, 資料超出修改範圍 */
#define OESERR_DATA_OUTOF_RANGE                 (&__ERRS_oesApiErrors[17])
/** 1019, 非法的應用系統名稱 */
#define OESERR_ILLEGAL_APPNAME                  (&__ERRS_oesApiErrors[18])
/** 1020, 請求條件有衝突 */
#define OESERR_CONFLICT_REQ_CONDITION           (&__ERRS_oesApiErrors[19])
/** 1021, 非法的客戶端IP/MAC地址格式 */
#define OESERR_ILLEGAL_IP_MAC_FORMAT            (&__ERRS_oesApiErrors[20])
/** 1022, 尚不支援此業務 */
#define OESERR_NOT_SUPPORT                      (&__ERRS_oesApiErrors[21])
/** 1023, 非法的客戶端環境號 */
#define OESERR_ILLEGAL_CLIENT_ENV_ID            (&__ERRS_oesApiErrors[22])
/** 1024, 交易所錯誤 */
#define OESERR_EXCHANGE_ERR                     (&__ERRS_oesApiErrors[23])
/** 1025, 主櫃錯誤 */
#define OESERR_COUNTER_ERR                      (&__ERRS_oesApiErrors[24])
/** 1026, 流量超出限制範圍 */
#define OESERR_TRAFFIC_CONTROL_OUTOF_RANGE      (&__ERRS_oesApiErrors[25])
/** 1027, 禁止使用API登入 */
#define OESERR_API_FORBIDDEN                    (&__ERRS_oesApiErrors[26])
/** 1028, 非法的私募基金產品程式碼 */
#define OESERR_ILLEGAL_PRIVATE_FUND_ID          (&__ERRS_oesApiErrors[27])
/** 1029, 密碼未改變 */
#define OESERR_PASSWORD_UNCHANGED               (&__ERRS_oesApiErrors[28])
/** 1030, 非法的來源分類 */
#define OESERR_ILLEGAL_SOURCE_TYPE              (&__ERRS_oesApiErrors[29])
/** 1031, 非法的加密型別 */
#define OESERR_ILLEGAL_ENCRYPT_TYPE             (&__ERRS_oesApiErrors[30])
/** 1032, 非法的客戶端裝置序列號 */
#define OESERR_ILLEGAL_DRIVER                   (&__ERRS_oesApiErrors[31])
/** 1033, 無可用節點 */
#define OESERR_NO_AVAILABLE_NODE                (&__ERRS_oesApiErrors[32])
/** 1034, 密碼強度不足 */
#define OESERR_PASSWORD_WEAK_STRENGTH           (&__ERRS_oesApiErrors[33])
/** 1035, 非法的產品型別 */
#define OESERR_ILLEGAL_PRODUCT_TYPE             (&__ERRS_oesApiErrors[34])
/** 1036, 未通過黑白名單檢查 */
#define OESERR_WBLIST_CHECK_FAILURE             (&__ERRS_oesApiErrors[35])
/* -------------------------           */


/*
 * 主櫃檯相關錯誤
 */
/** 1101, 登入櫃檯失敗 */
#define OESERR_COUNTER_LOGON_FAILED             (&__ERRS_oesApiErrors[40])
/** 1102, 上報至櫃檯失敗 */
#define OESERR_COUNTER_DLCR_FAILED              (&__ERRS_oesApiErrors[40 + 1])
/** 1103, 從櫃檯獲取狀態失敗 */
#define OESERR_COUNTER_FETCH_FAILED             (&__ERRS_oesApiErrors[40 + 2])
/* -------------------------           */


/*
 * OES相關錯誤
 */
/** 1201, 非法的證券賬戶程式碼 */
#define OESERR_ILLEGAL_INV_ACCT_ID              (&__ERRS_oesApiErrors[60])
/** 1202, 非法的資金賬戶程式碼 */
#define OESERR_ILLEGAL_CASH_ACCT_ID             (&__ERRS_oesApiErrors[60 + 1])
/** 1203, 非法的出入金方向 */
#define OESERR_ILLEGAL_CASH_DIRECTION           (&__ERRS_oesApiErrors[60 + 2])
/** 1204, 非法的市場程式碼 */
#define OESERR_ILLEGAL_MARKET_ID                (&__ERRS_oesApiErrors[60 + 3])
/** 1205, 非法的證券類別 */
#define OESERR_ILLEGAL_SECURITY_TYPE            (&__ERRS_oesApiErrors[60 + 4])
/** 1206, 非法的買賣型別 */
#define OESERR_ILLEGAL_BUY_SELL_TYPE            (&__ERRS_oesApiErrors[60 + 5])
/** 1207, 非法的幣種 */
#define OESERR_ILLEGAL_CURR_TYPE                (&__ERRS_oesApiErrors[60 + 6])
/** 1208, 非法的委託型別 */
#define OESERR_ILLEGAL_ORDER_TYPE               (&__ERRS_oesApiErrors[60 + 7])
/** 1209, 無效的賬戶狀態 */
#define OESERR_ILLEGAL_ACCT_STATUS              (&__ERRS_oesApiErrors[60 + 8])
/** 1210, 未找到委託資訊 */
#define OESERR_ORD_NOT_FOUND                    (&__ERRS_oesApiErrors[60 + 9])
/** 1211, 未找到持倉資訊 */
#define OESERR_HOLDING_NOT_FOUND                (&__ERRS_oesApiErrors[60 + 10])
/** 1212, 未找到出入金流水 */
#define OESERR_FUND_TRSF_NOT_FOUND              (&__ERRS_oesApiErrors[60 + 11])
/** 1213, 流水號重複 */
#define OESERR_SEQNO_DUPLICATE                  (&__ERRS_oesApiErrors[60 + 12])
/** 1214, 當前時段不能報價 */
#define OESERR_ORDER_SESSION_CLOSE              (&__ERRS_oesApiErrors[60 + 13])
/** 1215, 沒有操作許可權 */
#define OESERR_ORDER_NO_RIGHT                   (&__ERRS_oesApiErrors[60 + 14])
/** 1216, 可用/可取資餘額不足 */
#define OESERR_ORDER_CASH_NOT_ENOUGH            (&__ERRS_oesApiErrors[60 + 15])
/** 1217, 可用持倉不足 */
#define OESERR_ORDER_HOLDING_NOT_ENOUGH         (&__ERRS_oesApiErrors[60 + 16])
/** 1218, 委託數量不在合法區間內 */
#define OESERR_ORDER_QTY_RANGE                  (&__ERRS_oesApiErrors[60 + 17])
/** 1219, 非數量單位的整數倍 */
#define OESERR_ORDER_QTY_UNIT                   (&__ERRS_oesApiErrors[60 + 18])
/** 1220, 非法的PBU程式碼 */
#define OESERR_ILLEGAL_PBU_ID                   (&__ERRS_oesApiErrors[60 + 19])
/** 1221, 價格不在合法區間內 */
#define OESERR_ORDER_PRICE_RANGE                (&__ERRS_oesApiErrors[60 + 20])
/** 1222, 非價格單位的整數倍 */
#define OESERR_ORDER_PRICE_UNIT                 (&__ERRS_oesApiErrors[60 + 21])
/** 1223, 無漲停價市價委託失敗 */
#define OESERR_ORDER_NO_CEIL_PRICE              (&__ERRS_oesApiErrors[60 + 22])
/** 1224, 當前時段不支援市價委託 */
#define OESERR_ORDER_DISAGREE_SESSION           (&__ERRS_oesApiErrors[60 + 23])
/** 1225, 無效的訂單狀態 */
#define OESERR_ORDER_ILLEGAL_STATUS             (&__ERRS_oesApiErrors[60 + 24])
/** 1226, 撤單資訊與原始委託不符 */
#define OESERR_ORDER_MISMATCH_ORG               (&__ERRS_oesApiErrors[60 + 25])
/** 1227, 重複撤單 */
#define OESERR_ORDER_CANCEL_DUPLICATE           (&__ERRS_oesApiErrors[60 + 26])
/** 1228, 未通過限倉檢查 */
#define OESERR_ORDER_HOLDING_QUOTA              (&__ERRS_oesApiErrors[60 + 27])
/** 1229, 未通過限購檢查 */
#define OESERR_ORDER_CASH_QUOTA                 (&__ERRS_oesApiErrors[60 + 28])
/** 1230, 超過了ETF最大現金替代比例 */
#define OESERR_ORDER_ETF_CASH_RATIO             (&__ERRS_oesApiErrors[60 + 29])
/** 1231, 非行權日 */
#define OESERR_ORDER_NOT_EXEC_DATE              (&__ERRS_oesApiErrors[60 + 30])
/** 1232, 證券停牌 */
#define OESERR_ORDER_INSTR_SUSP                 (&__ERRS_oesApiErrors[60 + 31])
/** 1233, 合約限制開倉 */
#define OESERR_ORDER_INSTR_OPEN_LIMIT           (&__ERRS_oesApiErrors[60 + 32])
/** 1234, 當日累計申購或贖回數量超過限額 */
#define OESERR_ORDER_CRE_RED_QUOTA              (&__ERRS_oesApiErrors[60 + 33])
/** 1235, 當日累計淨申購或淨贖回數量超過限額 */
#define OESERR_ORDER_NET_CRE_RED_QUOTA          (&__ERRS_oesApiErrors[60 + 34])
/** 1236, 找不到前收盤價 */
#define OESERR_ORDER_NO_PREV_CLOSE              (&__ERRS_oesApiErrors[60 + 35])
/** 1237, 超過報撤比限制 */
#define OESERR_ORDER_EXCEED_CANCEL_RATE         (&__ERRS_oesApiErrors[60 + 36])
/** 1238, 委託請求過於頻繁 */
#define OESERR_ORDER_REQ_TOO_OFTEN              (&__ERRS_oesApiErrors[60 + 37])
/** 1239, 非法的出入金轉賬金額 */
#define OESERR_ILLEGAL_FUND_TRSF_AMOUNT         (&__ERRS_oesApiErrors[60 + 38])
/** 1240, 重複的認購委託 */
#define OESERR_SUBSCRIPTION_DUPLICATE           (&__ERRS_oesApiErrors[60 + 39])
/** 1241, 認購委託份數超過認購額度 */
#define OESERR_SUBSCRIPTION_QUOTA_EXCEED        (&__ERRS_oesApiErrors[60 + 40])
/** 1242, 出入金筆數超過限制 */
#define OESERR_FUND_TRSF_CNT_LIMIT              (&__ERRS_oesApiErrors[60 + 41])
/** 1243, 禁止同時做多筆出入金 */
#define OESERR_FORBID_CONCURRENT_FUND_TRSF      (&__ERRS_oesApiErrors[60 + 42])
/** 1244, 非法的新股配號、中籤記錄型別 */
#define OESERR_ILLEGAL_LOT_TYPE                 (&__ERRS_oesApiErrors[60 + 43])
/** 1245, 限制股東賬戶進行買交易 */
#define OESERR_BUY_LIMIT                        (&__ERRS_oesApiErrors[60 + 44])
/** 1246, 限制股東賬戶進行賣交易 */
#define OESERR_SELL_LIMIT                       (&__ERRS_oesApiErrors[60 + 45])
/** 1247, 限制股東賬戶進行逆回購交易 */
#define OESERR_PLEDGED_REPO_LIMIT               (&__ERRS_oesApiErrors[60 + 46])
/** 1248, 限制股東賬戶進行新股認購交易 */
#define OESERR_SUBSCRIPTION_LIMIT               (&__ERRS_oesApiErrors[60 + 47])
/** 1249, 股東賬戶沒有市價委託交易的許可權 */
#define OESERR_NO_MARKET_ORDER_PERM             (&__ERRS_oesApiErrors[60 + 48])
/** 1250, 股東賬戶沒有交易創業板證券的許可權 */
#define OESERR_NO_GEM_PERM                      (&__ERRS_oesApiErrors[60 + 49])
/** 1251, 股東賬戶沒有交易分級基金的許可權 */
#define OESERR_NO_STRUCTURED_FUND_PERM          (&__ERRS_oesApiErrors[60 + 50])
/** 1252, 股東賬戶沒有債券合格投資者的許可權 */
#define OESERR_NO_BOND_QUALIFIED_INV_PERM       (&__ERRS_oesApiErrors[60 + 51])
/** 1253, 客戶風險評級低於交易證券需求的風險等級 */
#define OESERR_HIGHER_RISK_LEVEL_REQUIRED       (&__ERRS_oesApiErrors[60 + 52])
/** 1254, 股東賬戶沒有交易風險警示證券的許可權 */
#define OESERR_NO_RISK_WARNING_PERM             (&__ERRS_oesApiErrors[60 + 53])
/** 1255, 股東賬戶沒有交易退市整理證券的許可權 */
#define OESERR_NO_DELISTING_PERM                (&__ERRS_oesApiErrors[60 + 54])
/** 1256, 股東賬戶沒有交易單市場ETF的許可權 */
#define OESERR_NO_SINGLE_MARKET_ETF_PERM        (&__ERRS_oesApiErrors[60 + 55])
/** 1257, 股東賬戶沒有交易跨市場ETF的許可權 */
#define OESERR_NO_CROSS_MARKET_ETF_PERM         (&__ERRS_oesApiErrors[60 + 56])
/** 1258, 股東賬戶沒有交易貨幣基金ETF的許可權 */
#define OESERR_NO_CURRENCY_ETF_PERM             (&__ERRS_oesApiErrors[60 + 57])
/** 1259, 股東賬戶沒有交易跨境ETF的許可權 */
#define OESERR_NO_CROSS_BORDER_ETF_PERM         (&__ERRS_oesApiErrors[60 + 58])
/** 1260, 僅允許合格投資者投資該證券 */
#define OESERR_QUALIFIED_INVESTOR_ONLY          (&__ERRS_oesApiErrors[60 + 59])
/** 1261, 僅允許合格機構投資者投資該證券 */
#define OESERR_QUALIFIED_INSTITUTION_ONLY       (&__ERRS_oesApiErrors[60 + 60])
/** 1262, 出入金執行異常，待人工干預 */
#define OESERR_FUND_TRSF_WAIT_MANUAL_INTERVENE  (&__ERRS_oesApiErrors[60 + 61])
/** 1263, 交易日不在證券的發行期內 */
#define OESERR_NOT_ISSUE_DATE                   (&__ERRS_oesApiErrors[60 + 62])
/** 1264, 該ETF禁止申購 */
#define OESERR_ETF_FORBID_CREATION              (&__ERRS_oesApiErrors[60 + 63])
/** 1265, 該ETF禁止贖回 */
#define OESERR_ETF_FORBID_REDEMPTION            (&__ERRS_oesApiErrors[60 + 64])
/** 1266, 限制股東賬戶進行撤指定 */
#define OESERR_RECALL_DESIGNATION_LIMIT         (&__ERRS_oesApiErrors[60 + 65])
/** 1267, 限制股東賬戶進行轉託管 */
#define OESERR_DESIGNATION_LIMIT                (&__ERRS_oesApiErrors[60 + 66])
/** 1268, 機構客戶/主櫃業務不支援銀行轉帳 */
#define OESERR_NOT_SUPPORT_BANK_TRSF            (&__ERRS_oesApiErrors[60 + 67])
/** 1269, 禁止私募基金產品交易此證券 */
#define OESERR_SECURITY_IN_FUND_BLACKLIST       (&__ERRS_oesApiErrors[60 + 68])
/** 1270, 禁止客戶交易此證券 */
#define OESERR_SECURITY_IN_CUST_BLACKLIST       (&__ERRS_oesApiErrors[60 + 69])
/** 1271, 股東賬戶沒有交易存託憑證的許可權 */
#define OESERR_NO_CDR_PERM                      (&__ERRS_oesApiErrors[60 + 70])
/** 1272, 股東賬戶沒有交易創新企業股票的許可權 */
#define OESERR_NO_INNOVATION_PERM               (&__ERRS_oesApiErrors[60 + 71])
/** 1273, 非法的出入金轉賬型別 */
#define OESERR_ILLEGAL_FUND_TRSF_TYPE           (&__ERRS_oesApiErrors[60 + 72])
/** 1274, 股東賬戶沒有交易滬倫通存託憑證的許可權 */
#define OESERR_NO_HLTCDR_PERM                   (&__ERRS_oesApiErrors[60 + 73])
/** 1275, 股東賬戶沒有交易科創板的許可權 */
#define OESERR_NO_KSH_PERM                      (&__ERRS_oesApiErrors[60 + 74])
/* -------------------------           */


#ifdef __cplusplus

}
#endif

#endif  /* _OES_PROTOCOL_ERRORS_H */
