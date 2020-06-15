#ifndef TAP_API_ERROR_H
#define TAP_API_ERROR_H

//=============================================================================
/**
 *	\addtogroup G_ERR_INNER_API		TapAPI內部返回的錯誤碼定義。
 *	@{
 */
//=============================================================================
//! 成功
const int TAPIERROR_SUCCEED                                            = 0;
//! 連線服務失敗
const int TAPIERROR_ConnectFail                                        = -1;
//! 鏈路認證失敗
const int TAPIERROR_LinkAuthFail                                       = -2;
//! 主機地址不可用
const int TAPIERROR_HostUnavailable                                    = -3;
//! 傳送資料錯誤
const int TAPIERROR_SendDataError                                      = -4;
//! 測試編號不合法
const int TAPIERROR_TestIDError                                        = -5;
//! 沒準備好測試網路
const int TAPIERROR_NotReadyTestNetwork                                = -6;
//! 當前網路測試還沒結束
const int TAPIERROR_CurTestNotOver                                     = -7;
//! 沒用可用的接入前置
const int TAPIERROR_NOFrontAvailable                                   = -8;
//! 資料路徑不可用
const int TAPIERROR_DataPathAvaiable                                   = -9;
//! 重複登入
const int TAPIERROR_RepeatLogin                                        = -10;
//! 內部錯誤	
const int TAPIERROR_InnerError                                         = -11;
//! 上一次請求還沒有結束	
const int TAPIERROR_LastReqNotFinish                                   = -12;
//! 輸入引數非法	
const int TAPIERROR_InputValueError                                    = -13;
//! 授權碼不合法	
const int TAPIERROR_AuthCode_Invalid                                   = -14;
//! 授權碼超期	
const int TAPIERROR_AuthCode_Expired                                   = -15;
//! 授權碼型別不匹配	
const int TAPIERROR_AuthCode_TypeNotMatch                              = -16;
//! API還沒有準備好
const int TAPIERROR_API_NotReady                                       = -17;
//! UDP埠監聽失敗
const int TAPIERROR_UDP_LISTEN_FAILED                                  = -18;
//! UDP正在監聽
const int TAPIERROR_UDP_LISTENING                                      = -19;
//! 介面未實現
const int TAPIERROR_NotImplemented                                     = -20;
//! 每次登陸只允許呼叫一次
const int TAPIERROR_CallOneTimeOnly                                    = -21;
//! 查詢頻率太高
const int TAPIERROR_Frequently                                         = -22;

/** @}*/


//=============================================================================
/**
 *	\addtogroup G_ERR_INPUT_CHECK		輸入引數檢查錯誤
 *	@{
 */
//=============================================================================
//! 輸入資料為NULL
const int TAPIERROR_INPUTERROR_NULL                                    = -10000;
//! 輸入錯誤的:TAPIYNFLAG
const int TAPIERROR_INPUTERROR_TAPIYNFLAG                              = -10001;
//! 輸入錯誤的:TAPILOGLEVEL
const int TAPIERROR_INPUTERROR_TAPILOGLEVEL                            = -10002;
//! 輸入錯誤的:TAPICommodityType
const int TAPIERROR_INPUTERROR_TAPICommodityType                       = -10003;
//! 輸入錯誤的:TAPICallOrPutFlagType
const int TAPIERROR_INPUTERROR_TAPICallOrPutFlagType                   = -10004;
//! 輸入錯誤的:TAPIAccountType
const int TAPIERROR_INPUTERROR_TAPIAccountType                         = -12001;
//! 輸入錯誤的:TAPIAccountState
const int TAPIERROR_INPUTERROR_TAPIAccountState                        = -12003;
//! 輸入錯誤的:TAPIAccountFamilyType
const int TAPIERROR_INPUTERROR_TAPIAccountFamilyType                   = -12004;
//! 輸入錯誤的:TAPIOrderTypeType
const int TAPIERROR_INPUTERROR_TAPIOrderTypeType                       = -12005;
//! 輸入錯誤的:TAPIOrderSourceType
const int TAPIERROR_INPUTERROR_TAPIOrderSourceType                     = -12006;
//! 輸入錯誤的:TAPITimeInForceType
const int TAPIERROR_INPUTERROR_TAPITimeInForceType                     = -12007;
//! 輸入錯誤的:TAPISideType
const int TAPIERROR_INPUTERROR_TAPISideType                            = -12008;
//! 輸入錯誤的:TAPIPositionEffectType
const int TAPIERROR_INPUTERROR_TAPIPositionEffectType                  = -12009;
//! 輸入錯誤的:TAPIHedgeFlagType
const int TAPIERROR_INPUTERROR_TAPIHedgeFlagType                       = -12010;
//! 輸入錯誤的:TAPIOrderStateType
const int TAPIERROR_INPUTERROR_TAPIOrderStateType                      = -12011;
//! 輸入錯誤的:TAPICalculateModeType
const int TAPIERROR_INPUTERROR_TAPICalculateModeType                   = -12012;
//! 輸入錯誤的:TAPIMatchSourceType
const int TAPIERROR_INPUTERROR_TAPIMatchSourceType                     = -12013;
//! 輸入錯誤的:TAPIOpenCloseModeType
const int TAPIERROR_INPUTERROR_TAPIOpenCloseModeType                   = -12014;
//! 輸入錯誤的:TAPIFutureAlgType
const int TAPIERROR_INPUTERROR_TAPIFutureAlgType                       = -12015;
//! 輸入錯誤的:TAPIOptionAlgType
const int TAPIERROR_INPUTERROR_TAPIOptionAlgType                       = -12016;
//! 輸入錯誤的:TAPIBankAccountLWFlagType
const int TAPIERROR_INPUTERROR_TAPIBankAccountLWFlagType               = -12017;
//! 輸入錯誤的:TAPIMarginCalculateModeType
const int TAPIERROR_INPUTERROR_TAPIMarginCalculateModeType             = -12021;
//! 輸入錯誤的:TAPIOptionMarginCalculateModeType
const int TAPIERROR_INPUTERROR_TAPIOptionMarginCalculateModeType       = -12022;
//! 輸入錯誤的:TAPICmbDirectType
const int TAPIERROR_INPUTERROR_TAPICmbDirectType                       = -12023;
//! 輸入錯誤的:TAPIDeliveryModeType
const int TAPIERROR_INPUTERROR_TAPIDeliveryModeType                    = -12024;
//! 輸入錯誤的:TAPIContractTypeType
const int TAPIERROR_INPUTERROR_TAPIContractTypeType                    = -12025;
//! 輸入錯誤的:TAPITacticsTypeType
const int TAPIERROR_INPUTERROR_TAPITacticsTypeType                     = -12035;
//! 輸入錯誤的:TAPIORDERACT
const int TAPIERROR_INPUTERROR_TAPIORDERACT                            = -12036;
//! 輸入錯誤的:TAPITriggerConditionType
const int TAPIERROR_INPUTERROR_TAPITriggerConditionType                = -12041;
//! 輸入錯誤的:TAPITriggerPriceTypeType
const int TAPIERROR_INPUTERROR_TAPITriggerPriceTypeType                = -12042;
//! 輸入錯誤的:TAPITradingStateType 
const int TAPIERROR_INPUTERROR_TAPITradingStateType                    = -12043;
//! 輸入錯誤的:TAPIMarketLevelType 
const int TAPIERROR_INPUTERROR_TAPIMarketLevelType                     = -12044;
//! 輸入錯誤的:TAPIOrderQryTypeType 
const int TAPIERROR_INPUTERROR_TAPIOrderQryTypeType                    = -12045;

/** @}*/

//=============================================================================
/**
 *	\addtogroup G_ERR_DISCONNECT_REASON	網路斷開錯誤程式碼定義
 *	@{
 */
//=============================================================================
//! 主動斷開
const int TAPIERROR_DISCONNECT_CLOSE_INIT                              = 1;
//! 被動斷開
const int TAPIERROR_DISCONNECT_CLOSE_PASS                              = 2;
//! 讀錯誤
const int TAPIERROR_DISCONNECT_READ_ERROR                              = 3;
//! 寫錯誤
const int TAPIERROR_DISCONNECT_WRITE_ERROR                             = 4;
//! 緩衝區滿
const int TAPIERROR_DISCONNECT_BUF_FULL                                = 5;
//! 非同步操作錯誤
const int TAPIERROR_DISCONNECT_IOCP_ERROR                              = 6;
//! 解析資料錯誤
const int TAPIERROR_DISCONNECT_PARSE_ERROR                             = 7;
//! 連線超時
const int TAPIERROR_DISCONNECT_CONNECT_TIMEOUT                         = 8;
//! 初始化失敗
const int TAPIERROR_DISCONNECT_INIT_ERROR                              = 9;
//! 已經連線
const int TAPIERROR_DISCONNECT_HAS_CONNECTED                           = 10;
//! 工作執行緒已結束
const int TAPIERROR_DISCONNECT_HAS_EXIT                                = 11;
//! 操作正在進行，請稍後重試
const int TAPIERROR_DISCONNECT_TRY_LATER                               = 12;
//! 心跳檢測失敗
const int TAPIERROR_DISCONNECT_HEARTBEAT_FAILED                        = 13;

/** @}*/

//=============================================================================
/**
 *	\addtogroup G_ERR_LOGIN	登陸過程返回的錯誤程式碼定義
 *	@{
 */
//=============================================================================
//! 登入過程執行錯誤
const int TAPIERROR_LOGIN                                              = 10001;
//! 登入使用者不存在
const int TAPIERROR_LOGIN_USER                                         = 10002;
//! 需要進行動態認證
const int TAPIERROR_LOGIN_DDA                                          = 10003;
//! 登入使用者未授權
const int TAPIERROR_LOGIN_LICENSE                                      = 10004;
//! 登入模組不正確
const int TAPIERROR_LOGIN_MODULE                                       = 10005;
//! 需要強制修改密碼
const int TAPIERROR_LOGIN_FORCE                                        = 10006;
//! 登入狀態禁止登陸
const int TAPIERROR_LOGIN_STATE                                        = 10007;
//! 登入密碼不正確
const int TAPIERROR_LOGIN_PASS                                         = 10008;
//! 沒有該模組登入許可權
const int TAPIERROR_LOGIN_RIGHT                                        = 10009;
//! 登入數量超限
const int TAPIERROR_LOGIN_COUNT                                        = 10010;
//! 登入使用者不在伺服器標識下可登入使用者列表中
const int TAPIERROR_LOGIN_NOTIN_SERVERFLAGUSRES                        = 10011;
//! 登陸使用者不在有效期
const int TAPIERROR_LOGIN_USER_EXPIRED                                 = 10012;
//! 登陸使用者無下屬客戶
const int TAPIERROR_LOGIN_NO_ACCOUNT                                   = 10013;
//! 登入使用者是子帳號且授權中未包含機構通標記
const int TAPIERROR_LOGIN_NO_JGT                                       = 10014;
//! 登入使用者密碼錯誤次數超限，禁止登陸
const int TAPIERROR_LOGIN_ERROR_TIMES                                  = 10015;
//! 登入使用者授權型別錯誤
const int TAPIERROR_LOGIN_ERROR_AUTHTYPE                               = 10016;
//! 登入使用者授權到期或到期日錯誤
const int TAPIERROR_LOGIN_ERROR_AUTHEXPIRED                            = 10017;
//! 登入使用者密碼超過有效天數
const int TAPIERROR_LOGIN_ERROR_PASSWDEXPIRED                          = 10018;

/** @}*/

//=============================================================================
/**
 *	\addtogroup G_ERR_MANAGE 管理業務處理返回錯誤碼	
 *	@{
 */
//==============================================================================
//! 登入使用者資訊查詢失敗
const int TAPIERROR_USERINFO_QRY                                       = 10101;
//! 登入使用者下屬所有許可權查詢失敗
const int TAPIERROR_USERALLRIGHT_QRY                                   = 11001;
//! 登入使用者下屬所有資金賬號查詢失敗
const int TAPIERROR_USERALLACCOUNT_QRY                                 = 11501;
//! 登入使用者密碼修改失敗
const int TAPIERROR_USERPASSWORD_MOD                                   = 11701;
//! 登入使用者密碼修改失敗——原始密碼錯誤
const int TAPIERROR_USERPASSWORD_MOD_SOURCE                            = 11702;
//! 登入使用者密碼修改失敗——不能與前n次密碼相同
const int TAPIERROR_USERPASSWORD_MOD_SAME                              = 11703;
//! 新密碼不符合密碼複雜度要求
const int TAPIERROR_USERPASSWORD_MOD_COMPLEXITY                        = 11704;
//! 資金賬號資訊查詢失敗
const int TAPIERROR_ACCOUNTINFO_QRY                                    = 20201;
//! 客戶交易編碼查詢失敗
const int TAPIERROR_TRADENO_QRY                                        = 20701;
//! 合約資訊查詢失敗
const int TAPIERROR_CONTRACTINFO_QRY                                   = 22801;
//! 特殊期權標的查詢失敗
const int TAPIERROR_SPECIALOPTIONFUTURE_QRY                            = 22901;
//! 品種委託型別查詢失敗
const int TAPIERROR_COMMODITYORDERTYPE_QRY                             = 25501;
//! 品種委託時間有效性查詢失敗
const int TAPIERROR_ORDERTIMEINFORCE_QRY                               = 25601;
//! 使用者下單頻率查詢失敗
const int TAPIERROR_USER_ORDER_FREQUENCE_QRY                           = 28901;

/** @}*/

//=============================================================================
/**
 *	\addtogroup G_ERR_TRADE 交易業務處理返回錯誤碼	
 *	@{
 */
//==============================================================================
//! 資金賬號不存在
const int TAPIERROR_ORDERINSERT_ACCOUNT                                = 60001;
//! 資金賬號狀態不正確
const int TAPIERROR_ORDERINSERT_ACCOUNT_STATE		                   = 60002;
//! 資金賬號無委託方向交易許可權
const int TAPIERROR_ORDERINSERT_SIDE_TRADE                             = 60003;
//! 資金賬號無期權交易許可權
const int TAPIERROR_ORDERINSERT_OPTIONS_TRADE                          = 60004;
//! 資金賬號無品種交易許可權
const int TAPIERROR_ORDERINSERT_COMMODITY_TRADE                        = 60005;
//! 資金賬號無開倉許可權
const int TAPIERROR_ORDERINSERT_OPEN_RIGHT                             = 60006;
//! 資金賬號風控項檢查失敗
const int TAPIERROR_ORDERINSERT_RISK_CHECK                             = 60007;
//! 下單無效的合約
const int TAPIERROR_ORDERINSERT_CONTRACT                               = 60011;
//! 下單合約無交易路由
const int TAPIERROR_ORDERINSERT_TRADEROUTE                             = 60021;
//! 持倉量超過最大限制
const int TAPIERROR_ORDERINSERT_POSITIONMAX                            = 60022;
//! 禁止交易
const int TAPIERROR_ORDER_NOTRADE                                      = 60023;
//! 只可平倉
const int TAPIERROR_ORDER_CLOSE                                        = 60024;
//! 下單資金不足
const int TAPIERROR_ORDERINSERT_NOTENOUGHFUND                          = 60031;
//! 不支援的訂單型別
const int TAPIERROR_ORDERINSERT_ORDERTYPE                              = 60032;
//! 不支援的時間有效型別
const int TAPIERROR_ORDERINSERT_TIMEINFORCE                            = 60033;
//! 不支援的策略單型別
const int TAPIERROR_ORDERINSERT_NO_TACTICS                             = 60034;
//! 平倉數量超過已有持倉量
const int TAPIERROR_ORDERINSERT_POSITION_CANNOT_CLOSE                  = 60035;
//! 下單自動稽核失敗
const int TAPIERROR_ORDERINSERT_AUTOCHECK_FAIL                         = 60036;
//! LME未準備就緒
const int TAPIERROR_ORDERINSERT_LME_NOTREADY                           = 60037;
//! 平倉方式錯誤
const int TAPIERROR_ORDERINSERT_CLOSEMODE                              = 60038;
//! 下單對應的父賬號資金不足
const int TAPIERROR_ORDERINSERT_PARENTNOTENOUGHFUND                    = 60039;
//! 互換單的合約格式錯誤
const int TAPIERROR_SWAP_CONTRACT                                      = 60040;
//! 當前客戶不能使用此賬號交易
const int TAPIERROR_USERNO_NOTHAS_ACCOUNT                              = 60051;
//! 上手通道狀態不正常
const int TAPIERROR_UPPERCHANNEL_BROKEN                                = 60052;
//! 上手通道未開通EXIST
const int TAPIERROR_UPPERCHANNEL_NOT_EXIST                             = 60053;
//! 撤單無此係統號
const int TAPIERROR_ORDERDELETE_NOT_SYSNO                              = 60061;
//! 此狀態不允許撤單
const int TAPIERROR_ORDERDELETE_NOT_STATE                              = 60062;
//! 此狀態不允許啟用
const int TAPIERROR_ORDERACTIVE_NOT_STATE                              = 60063;
//! 此狀態禁止稽核
const int TAPIERROR_ORDERCHECK_NOT_STATE                               = 60071;
//! 訂單稽核失敗
const int TAPIERROR_ORDERCHECK_FAIL                                    = 60072;
//! 此狀態不允許改單
const int TAPIERROR_ORDERMODIFY_NOT_STATE                              = 60081;
//! 人工單不允許改單
const int TAPIERROR_ORDERMODIFY_BACK_INPUT                             = 60082;
//! 手續費引數錯誤
const int TAPIERROR_ORDERINSERT_FEE                                    = 60091;
//! 保證金引數錯誤
const int TAPIERROR_ORDERINSERT_MARGIN                                 = 60092;
//! 操作賬號只可查詢
const int TAPIERROR_ORDER_NO_PERMIT                                    = 60100;
//! 非做市商不能應價
const int TAPIERROR_RSPQUOTE_NO_PERMIT                                 = 60101;
//! 即使子帳號又是做市商不能應價
const int TAPIERROR_RSPQUOTE_CHILD_NO_PERMIT                           = 60102;
//! 下單找不到交易編碼
const int TAPIERROR_TRADENO_NOT_FIND                                   = 60103;
//! 操作賬號只可開倉
const int TAPIERROR_ORDER_NO_CLOSE                                     = 60104;
//! 操作賬號沒有上期掛單查詢許可權
const int TAPIERROR_QRY_QUOTE_NO_PERMIT                                = 60105;
//! 限期有效單不能小於當前交易日
const int TAPIERROR_EXPIREDATE_NO_PERMIT                               = 60106;
//! 該編碼不允許申請或拆分組合
const int TAPIERROR_CMB_NO_PERMIT                                      = 60107;
//! 非本伺服器標記下的賬號不允許操作
const int TAPIERROR_ORDERSERVER_NO_PERMIT                              = 60108;
//! 行權或棄權量超過可用量
const int TAPIERROR_POSITION_CANNOT_EXEC_OR_ABANDON                    = 60109;
//! 沒有訂單稽核許可權
const int TAPIERROR_ORDERCHECK_NO_PERMIT                               = 60110;
//! 超過當日最大開倉量
const int TAPIERROR_ORDERMAXOPENVOL_NO_PERMIT                          = 60111;
//! 非大連應價單不允許兩筆委託量不一致
const int TAPIERROR_ORDER_QTY_NO_PERMIT                                = 60115;
//! 申請不允許重複提交
const int TAPIERROR_ORDER_APPLY_NO_PERMIT                              = 60117;
//! 超過賬號下單頻率限制
const int TAPIERROR_ORDER_FREQ_OVERRUN                                 = 60118;
//! 組合表不存在的組合方向或投保標誌
const int TAPIERROR_COMB_NO_SIDEORHEDGE                                = 60119;
//! 訂單操作頻率過高
const int TAPIERROR_ORDER_FREQUENCY                                    = 61001;
//! 委託查詢返回前不能進行下次查詢
const int TAPIERROR_ORDER_QUERYING                                     = 61002;

/** @}*/

//=============================================================================
/**
 *	\addtogroup G_ERR_QUOTE 行情業務處理返回錯誤碼	
 *	@{
 */
//=============================================================================
//! 超過行情最大總訂閱數
const int TAPIERROR_SUBSCRIBEQUOTE_MAX                                 = 72001;
//! 超過該交易所行情最大訂閱數
const int TAPIERROR_SUBSCRIBEQUOTE_EXCHANGE_MAX                        = 72002;
//! 沒有該行情的訂閱許可權
const int TAPIERROR_SUBSCRIBEQUOTE_NO_RIGHT                            = 72101;
//! 沒有該交易所下行情的訂閱許可權
const int TAPIERROR_SUBSCRIBEQUOTE_NO_EXCHANGE_RIGHT                   = 72102;
//! 品種不存在
const int TAPIERROR_SUBSCRIBEQUOTE_COMMODITY_NOT_EXIST                 = 72103;
//! 合約可能不存在
const int TAPIERROR_SUBSCRIBEQUOTE_CONTRACT_MAY_NOT_EXIST              = 72104;
//! 不支援的行情協議
const int TAPIERROR_QUOTEFRONT_UNKNOWN_PROTOCOL                        = 83001;

/** @}*/


#endif //! TAP_API_ERROR_H
