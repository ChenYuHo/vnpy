#ifndef ITAP_API_ERROR_H
#define ITAP_API_ERROR_H

//=============================================================================
/**
 *    \addtogroup G_ERR_INNER_API        ITapAPI內部返回的錯誤碼定義。
 *    @{
 */
//=============================================================================
//! 成功
namespace ITapTrade
{


    //=============================================================================
    /**
    *    \addtogroup G_ERR_LOGIN        登入過程錯誤
    *    @{
    */
    //=============================================================================
    //! 登入過程執行錯誤
    const int            TAPIERROR_LOGIN = 10001;
    //! 登入使用者不存在
    const int            TAPIERROR_LOGIN_USER = 10002;
    //! 需要進行動態認證
    const int            TAPIERROR_LOGIN_DDA = 10003;
    //! 登入使用者未授權
    const int            TAPIERROR_LOGIN_LICENSE = 10004;
    //! 登入模組不正確
    const int            TAPIERROR_LOGIN_MODULE = 10005;
    //! 需要強制修改密碼
    const int            TAPIERROR_LOGIN_FORCE = 10006;
    //! 登入狀態禁止登陸
    const int            TAPIERROR_LOGIN_STATE = 10007;
    //! 登入密碼不正確
    const int            TAPIERROR_LOGIN_PASS = 10008;
    //! 沒有該模組登入許可權
    const int            TAPIERROR_LOGIN_RIGHT = 10009;
    //! 登入數量超限
    const int            TAPIERROR_LOGIN_COUNT = 10010;
    //! 登入使用者不在伺服器標識下可登入使用者列表中
    const int            TAPIERROR_LOGIN_NOTIN_SERVERFLAGUSRES = 10011;
    //! 登入使用者已被凍結
    const int            TAPIERROR_LOGIN_FREEZE = 10012;
    //! 密碼錯誤，使用者凍結
    const int            TAPIERROR_LOGIN_TOFREEZE = 10013;
    //! 客戶狀態不允許登入
    const int            TAPIERROR_LOGIN_ACCOUNTSTATE = 10014;
    //! 需要進行二次認證
    const int            TAPIERROR_LOGIN_SECCERTIFI = 10015;

    //未繫結二次認證資訊
    const int          TAPIERROR_LOGIN_NOSECONDSET = 10016;
    //不受信任的計算機登入
    const int          TAPIERROR_LOGIN_NOTURSTHOST = 10017;
    //!    二次驗證失敗
    const int          TAPITAPIERROR_SECONDCERTIFICATION_FAIL = 14001;
    //!    二次驗證超時
    const int          TAPITAPIERROR_SECONDCERTIFICATION_TIMEOVER = 14002;

    //=============================================================================
    //! 資料庫連線失敗
    const int            TAPIERROR_CONN_DATABASE = 11000;
    //! 資料庫操作失敗
    const int            TAPIERROR_OPER_DATABASE = 11001;
    //! 不允許一對多
    const int            TAPIERROR_NEED_ONETOONE = 11002;
    //! 刪除失敗-存在關聯資訊，
    const int            TAPIERROR_EXIST_RELATEINFO = 11003;
    //! 刪除分組失敗-分組有下屬或在操作員下屬中
    const int            TAPIERROR_EXIST_RELATEINFOOFGROUP = 11004;

    //! 登入使用者密碼修改失敗-原始密碼錯誤
    const int            TAPIERROR_USERPASSWORD_MOD_SOURCE = 12001;
    //! 登入使用者密碼修改失敗-不能與前n次密碼相同
    const int            TAPIERROR_USERPASSWORD_MOD_SAME = 12002;

    //! 登入使用者密碼修改失敗-新密碼不符合密碼複雜度要求
    const int          TAPIERROR_USERPASSWORD_MOD_COMPLEXITY = 12003;

    //! 一個幣種組只能設定一個基幣
    const int            TAPIERROR_CURRENCY_ONLY_ONEBASE = 13001;
    //! 基幣只能是美元或港幣
    const int            TAPIERROR_CURRENCY_ONLY_USDHKD = 13002;


    //=============================================================================
    /**
    *    \addtogroup G_ERR_TRADE_SERVICE        交易服務錯誤程式碼定義
    *    @{
    */
    //=============================================================================

    //! 資金賬號不存在
    const int            TAPIERROR_ORDERINSERT_ACCOUNT = 60001;
    //! 資金賬號狀態不正確
    const int            TAPIERROR_ORDERINSERT_ACCOUNT_STATE = 60002;
    //! 資金賬號交易中心不一致
    const int            TAPIERROR_ORDERINSERT_TRADECENT_ERROR = 60003;

    //! 下單無效的合約
    const int            TAPIERROR_ORDERINSERT_CONTRACT = 60011;
    //! LME未準備就緒
    const int            TAPIERROR_ORDERINSERT_LME_NOTREADY = 60012;
    //!不支援的下單型別
    const int            TAPIERROR_ORDERINSERT_ERROR_ORDER_TYPE = 60013;
    //!錯誤的埋單型別
    const int            TAPIERROR_ORDERINSERT_READY_TYPE_ERROR = 60014;
    //!不合法的委託型別
    const int            TAPIERROR_ORDERINSERT_ORDER_TYPE_ERROR = 60015;

    //! 客戶許可權禁止交易
    const int            TAPIERROR_ORDER_NOTRADE_ACCOUNT = 60021;
    //! 客戶品種分組禁止交易
    const int            TAPIERROR_ORDER_NOTRADE_COM_GROUP = 60022;
    //! 客戶合約特設禁止交易
    const int            TAPIERROR_ORDER_NOTRADE_ACC_CONTRACT = 60023;
    //! 系統許可權禁止交易
    const int            TAPIERROR_ORDER_NOTRADE_SYSTEM = 60024;
    //! 客戶許可權只可平倉
    const int            TAPIERROR_ORDER_CLOSE_ACCOUNT = 60025;
    //! 客戶合約特設只可平倉
    const int            TAPIERROR_ORDER_CLOSE_ACC_CONTRACT = 60026;
    //! 系統許可權只可平倉
    const int            TAPIERROR_ORDER_CLOSE_SYSTEM = 60027;
    //! 只可平倉提前天數限制只可平倉
    const int            TAPIERROR_ORDER_CLOSE_DAYS = 60028;
    //! 客戶品種風控許可權禁止交易
    const int            TAPIERROR_ORDER_NOTRADE_RISK = 60029;
    //! 客戶品種風控許可權只可平倉
    const int            TAPIERROR_ORDER_CLOSE_RISK = 60030;

    //! 持倉量超過最大限制
    const int            TAPIERROR_ORDERINSERT_POSITIONMAX = 60031;
    //! 下單超過單筆最大量
    const int            TAPIERROR_ORDERINSERT_ONCEMAX = 60032;
    //! 下單合約無交易路由
    const int            TAPIERROR_ORDERINSERT_TRADEROUTE = 60033;
    //! 委託價格超出偏離範圍
    const int            TAPIERROR_ORDER_IN_MOD_PRICE_ERROR = 60034;
    //! 超過GiveUp最大持倉量
    const int            TAPIERROR_ORDER_IN_GIVEUP_POS_MAX = 60035;


    //! 未登入閘道器
    const int          TAPIERROR_UPPERCHANNEL_NOT_LOGIN = 60041;
    //! 未找到閘道器資訊
    const int          TAPIERROR_UPPERCHANNEL_NOT_FOUND = 60042;

    //! 下單資金不足
    const int            TAPIERROR_ORDERINSERT_NOTENOUGHFUND = 60051;
    //! 手續費引數錯誤
    const int            TAPIERROR_ORDERINSERT_FEE = 60052;
    //! 保證金引數錯誤
    const int            TAPIERROR_ORDERINSERT_MARGIN = 60053;
    //! 總基幣資金不足
    const int            TAPIERROR_ORDERINSERT_BASENOFUND = 60054;

    //! 超過保證金額度
    const int            TAPIERROR_ORDERINSERT_MARGINAMOUNT = 60055;
    //! 總基幣超過開倉比例限制
    const int            TAPIERROR_ORDERINSERT_OPENRATIO = 60056;
    //! 獨立幣種組超過開倉比例限制
    const int            TAPIERROR_ORDERINSERT_GROUP_OPENRATIO = 60057;
    //! 風險陣列引數錯誤
    const int            TAPIERROR_ORDERINSERT_RISKARRAY = 60058;

    //! 撤單無此係統號
    const int          TAPIERROR_ORDERDELETE_NOT_SYSNO = 60061;
    //! 此狀態不允許撤單
    const int          TAPIERROR_ORDERDELETE_NOT_STATE = 60062;
    //! 錄單不允許撤單
    const int          TAPIERROR_ORDERDELETE_NO_INPUT = 60063;

    //! 此狀態不允許改單
    const int            TAPIERROR_ORDERMODIFY_NOT_STATE = 60071;
    //! 人工單不允許改單
    const int            TAPIERROR_ORDERMODIFY_BACK_INPUT = 60072;
    //! 風險報單不允許改單
    const int            TAPIERROR_ORDERMODIFY_RISK_ORDER = 60073;
    //! 成交量大於改單量
    const int            TAPIERROR_ORDERMODIFY_ERROR_QTY = 60074;
    //! 預埋單不允許改單
    const int            TAPIERROR_ORDERMODIFY_ERROR_READY = 60075;

    //! 已刪除報單不能轉移
    const int            TAPIERROR_ORDERINPUT_CANNOTMOVE = 60081;

    //! 錄單重複
    const int            TAPIERROR_ORDERINPUT_REPEAT = 60091;

    //! 合約行情價格修改失敗
    const int            TAPIERROR_CONTRACT_QUOTE = 60101;

    //! 下單超過上手單筆最大量
    const int            TAPIERROR_UPPER_ONCEMAX = 60111;
    //! 下單超過上手最大持倉量
    const int            TAPIERROR_UPPER_POSITIONMAX = 60112;

    //! 開平方式錯誤
    const int            TAPIERROR_ORDERINSERT_CLOSEMODE = 60121;
    //! 委託平倉持倉不足
    const int            TAPIERROR_CLOSE_ORDER = 60122;
    //! 成交平倉失敗
    const int            TAPIERROR_CLOSE_MATCH = 60123;

    //! 未找到本地委託
    const int            TAPIERROR_MOD_DEL_NO_ORDER = 60131;
    //! 與閘道器斷開連線
    const int            TAPIERROR_MOD_DEL_GATEWAY_DISCON = 60132;

    //! 錄單成交重複
    const int            TAPIERROR_MATCHINPUT_REPEAT = 60141;
    //! 錄單成交未找到對應委託
    const int            TAPIERROR_MATCHINPUT_NO_ORDER = 60142;
    //! 錄單成交合約不存在
    const int            TAPIERROR_MATCHINPUT_NO_CONTRACT = 60143;
    //! 錄單成交引數錯誤
    const int            TAPIERROR_MATCHINPUT_PARM_ERROR = 60144;
    //! 錄單成交委託狀態錯誤
    const int            TAPIERROR_MATCHINPUT_OSTATE_ERROR = 60145;

    //! 成交刪除未找到成交
    const int            TAPIERROR_MATCHREMOVE_NO_MATCH = 60151;
    //! 此狀態成交不可刪
    const int            TAPIERROR_MATCHREMOVE_STATE_ERROR = 60152;

    //! 不允許錄入此狀態訂單
    const int            TAPIERROR_ORDERINPUT_STATE_ERROR = 60161;
    //! 錯誤的修改訂單請求
    const int            TAPIERROR_ORDERINPUT_MOD_ERROR = 60162;
    //! 訂單不可刪，存在對應成交
    const int            TAPIERROR_ORDERREMOVE_ERROR = 60163;
    //! 不合法的委託狀態
    const int            TAPIERROR_ORDERINPUT_MOD_STATE_ERROR = 60164;
    //! 此狀態不允許訂單轉移
    const int            TAPIERROR_ORDEREXCHANGE_STATE_ERROR = 60165;
    //! 訂單不允許刪除
    const int            TAPIERROR_ORDERREMOVE_NOT_ERROR = 60166;

    //! 做市商雙邊撤單未找到委託
    const int            TAPIERROR_ORDERMARKET_DELETE_NOTFOUND = 60171;
    //! 做市商雙邊撤單客戶不一致
    const int            TAPIERROR_ORDERMARKET_DEL_ACCOUNT_NE = 60172;
    //! 做市商雙邊撤單品種不一致
    const int            TAPIERROR_ORDERMARKET_DEL_COMMODITY_NE = 60173;
    //! 做市商雙邊撤單合約不一致
    const int            TAPIERROR_ORDERMARKET_DEL_CONTRACT_NE = 60174;
    //! 做市商雙邊撤單買賣方向相同
    const int            TAPIERROR_ORDERMARKET_DEL_SIDE_EQ = 60175;
    //! 做市商雙邊撤單買賣方向錯誤
    const int            TAPIERROR_ORDERMARKET_DEL_SIDE_ERROR = 60176;
    //! 做市商單邊檢查未通過
    const int            TAPIERROR_ORDERMARKET_OTHER_SIDE_ERROR = 60177;

    //! 埋單啟用失敗，訂單未找到
    const int            TAPIERROR_ORDERACTIVATE_NOTFOUND_ERROR = 60181;
    //! 埋單啟用失敗，非有效狀態
    const int            TAPIERROR_ORDERACTIVATE_STATE_ERROR = 60182;
    //=============================================================================
    /**
    *    \addtogroup G_ERR_GATE_WAY        閘道器錯誤程式碼定義
    *    @{
    */
    //=============================================================================

    //! 閘道器未就緒，未連線上手
    const int            TAPIERROR_GW_NOT_READY = 80001;
    //! 品種錯誤
    const int            TAPIERROR_GW_INVALID_COMMODITY = 80002;
    //! 合約錯誤
    const int            TAPIERROR_GW_INVALID_CONTRACT = 80003;
    //! 報單欄位有誤
    const int            TAPIERROR_GW_INVALID_FIELD = 80004;
    //! 價格不合法
    const int            TAPIERROR_GW_INVALID_PRICE = 80005;
    //! 數量不合法
    const int            TAPIERROR_GW_INVALID_VOLUME = 80006;
    //! 報單型別不合法
    const int            TAPIERROR_GW_INVALID_TYPE = 80007;
    //! 委託模式不合法
    const int            TAPIERROR_GW_INVALID_MODE = 80008;
    //! 委託不存在（改單、撤單）
    const int            TAPIERROR_GW_ORDER_NOT_EXIST = 80009;
    //! 傳送報單失敗
    const int            TAPIERROR_GW_SEND_FAIL = 80010;
    //! 被上手拒絕
    const int            TAPIERROR_GW_REJ_BYUPPER = 80011;

    //=============================================================================
    /**
    *    \addtogroup G_ERR_FRONT_SERVICE        前置返回錯誤
    *    @{
    */
    //=============================================================================

    //! 前置不允許該模組登入
    const int            TAPIERROR_TRADEFRONT_MODULETYPEERR = 90001;
    //! 一次請求太多資料
    const int            TAPIERROR_TRADEFRONT_TOOMANYDATA = 90002;
    //! 前置沒有所要資料
    const int            TAPIERROR_TRADEFRONT_NODATA = 90003;
    //! 所查詢的操作員資訊不存在
    const int            TAPIERROT_TRADEFRONT_NOUSER = 90004;

    //! 前置與交易斷開
    const int            TAPIERROR_TRADEFRONT_DISCONNECT_TRADE = 90011;
    //! 前置與管理斷開
    const int            TAPIERROR_TRADEFRONT_DISCONNECT_MANAGE = 90012;

    //! 下屬資金賬號不存在
    const int            TAPIERROR_TRADEFRONT_ACCOUNT = 90021;
    //! 該操作員不允許交易
    const int            TAPIERROR_TRADEFRONT_ORDER = 90022;
    //! 查詢頻率過快
    const int            TAPIERROR_TRADEFRONT_FREQUENCY = 90023;
    //! 該授權不予許登入
    const int            TAPIERROR_TRADEFRONT_RUFUSE = 90024;
    //! 自成交驗證不通過
    const int            TAPIERROR_TRADEFRONT_SELFMATCH = 90025;
    
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
    const int TAPIERROR_CallOneTimeOnly                                        = -21;
    //! 超過下單頻率。
    const int TAPIERROR_ORDER_FREQUENCY                                        = -22;
    //! 查詢頻率太快。
    const int TAPIERROR_RENTQRY_TOOFAST                                        = -23;

    //! 不符合呼叫條件。
    const int TAPIERROR_CALL_NOCONDITION                                    = -24;


    //! 改單撤單時沒有找到對應訂單。
    const int TAPIERROR_ORDER_NOTFOUND                                        = -25;

    //! 日誌路徑為空。
    const int TAPIERROR_LOGPATH_EMPTY                                        = -26;
    //! 開啟日誌檔案失敗
    const int TAPIERROR_LOGPATH_FAILOPEN                                    = -27;
    //! 沒有交易員登入許可權
    const int TAPIERROR_RIGHT_TRADER = -28;
    //! 沒有訂單錄入或者成交錄入
    const int TAPIERROR_RIGHT_ORDERINPUT = -29;
    //! 沒有訂單修改和訂單刪除許可權，成交刪除許可權
    const int TAPIERROR_RIGHT_LOCALOPERATION = -30;
    //! 沒有訂單轉移許可權
    const int TAPIERROR_RIGHT_ORDERTRANSFER = -31;
    //! 成交錄入時系統號為空
    const int TAPIERROR_FILLINPUT_SYSTEMNO = -32;
    //! 成交刪除時成交號為空。
    const int TAPIERROR_FILLREMOVE_MATCHNO = -33;

    //! 成交刪除時沒有找到對應的成交
    const int TAPIERROR_FILLREQMOVE_NOFUND = -34;

    //! 訂單修改時客戶賬號變動。
    const int TAPIERROR_LOCALMODIFY_ACCOUNT = -35;

    //! 訂單轉移時客戶賬號沒有變動
    const int TAPIERROR_LOCALTRANSFER_ACCOUNT = -36;

    //! 修改的電話密碼位數不對或者包含特殊字元。
    const int TAPIERROR_INPUTERROR_PHONE = -37;

    //!    未繫結的二次認證資訊
    const int TAPIERROR_ERROR_CONTACT = -38;

    //! 二次認證有效期內不能再申請二次認證碼
    const int TAPIERROR_ERROR_REJESTVERTIFICATE = -39;

    //! 沒有設定客戶密碼的許可權。
    const int TAPIERROR_RIGHT_SETPASSWORD = -40;
    //! 風險保單單客戶無法撤銷或更改
    const int TAPIERROR_RISK_OPERERROR = -41;
    //! 改單是客戶賬號填寫與訂單客戶賬號不一致
    const int TAPIERROR_ORDER_MODACCOUNT = -42;

    /** @}*/


    //=============================================================================
    /**
     *    \addtogroup G_ERR_INPUT_CHECK        輸入引數檢查錯誤
     *    @{
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
    //! 輸入錯誤的:TAPIBucketDateFlag
    const int TAPIERROR_INPUTERROR_TAPIBucketDateFlag                      = -11001;
    //! 輸入錯誤的:TAPIHisQuoteType
    const int TAPIERROR_INPUTERROR_TAPIHisQuoteType                        = -11002;
    //! 輸入錯誤的:TAPIAccountType
    const int TAPIERROR_INPUTERROR_TAPIAccountType                         = -12001;
    //! 輸入錯誤的:TAPIUserTypeType
    const int TAPIERROR_INPUTERROR_TAPIUserTypeType                        = -12002;
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
    //! 輸入錯誤的:TAPIBankAccountStateType
    const int TAPIERROR_INPUTERROR_TAPIBankAccountStateType                = -12018;
    //! 輸入錯誤的:TAPIBankAccountSwapStateType
    const int TAPIERROR_INPUTERROR_TAPIBankAccountSwapStateType            = -12019;
    //! 輸入錯誤的:TAPIBankAccountTransferStateType
    const int TAPIERROR_INPUTERROR_TAPIBankAccountTransferStateType        = -12020;
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
    //! 輸入錯誤的:TAPIPartyTypeType
    const int TAPIERROR_INPUTERROR_TAPIPartyTypeType                       = -12026;
    //! 輸入錯誤的:TAPIPartyCertificateTypeType
    const int TAPIERROR_INPUTERROR_TAPIPartyCertificateTypeType            = -12027;
    //! 輸入錯誤的:TAPIMsgReceiverType
    const int TAPIERROR_INPUTERROR_TAPIMsgReceiverType                     = -12028;
    //! 輸入錯誤的:TAPIMsgTypeType
    const int TAPIERROR_INPUTERROR_TAPIMsgTypeType                         = -12029;
    //! 輸入錯誤的:TAPIMsgLevelType
    const int TAPIERROR_INPUTERROR_TAPIMsgLevelType                        = -12030;
    //! 輸入錯誤的:TAPITransferDirectType
    const int TAPIERROR_INPUTERROR_TAPITransferDirectType                  = -12031;
    //! 輸入錯誤的:TAPITransferStateType
    const int TAPIERROR_INPUTERROR_TAPITransferStateType                   = -12032;
    //! 輸入錯誤的:TAPITransferTypeType
    const int TAPIERROR_INPUTERROR_TAPITransferTypeType                    = -12033;
    //! 輸入錯誤的:TAPITransferDeviceIDType
    const int TAPIERROR_INPUTERROR_TAPITransferDeviceIDType                = -12034;
    //! 輸入錯誤的:TAPITacticsTypeType
    const int TAPIERROR_INPUTERROR_TAPITacticsTypeType                     = -12035;
    //! 輸入錯誤的:TAPIORDERACT
    const int TAPIERROR_INPUTERROR_TAPIORDERACT                            = -12036;
    //! 輸入錯誤的:TAPIBillTypeType
    const int TAPIERROR_INPUTERROR_TAPIBillTypeType                        = -12037;
    //! 輸入錯誤的:TAPIBillFileTypeType
    const int TAPIERROR_INPUTERROR_TAPIBillFileTypeType                    = -12038;
    //! 輸入錯誤的:TAPIOFFFlagType
    const int TAPIERROR_INPUTERROR_TAPIOFFFlagType                         = -12039;
    //! 輸入錯誤的:TAPICashAdjustTypeType
    const int TAPIERROR_INPUTERROR_TAPICashAdjustTypeType                  = -12040;
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
    //! 輸入錯誤的: ClientID，ClientID包含特殊字元。
    const int TAPIERROR_INPUTERROR_TAPIClientID                            = -12046;
    //! 歷史行情查詢引數不合法
    const int TAPIERROR_INPUTERROR_QryHisQuoteParam                        = -13001;
    //! 價格和數量中包含NAN或者INF不合法的數值
    const int TAPIERROR_INPUTERROR_TAPIIncludeNAN                            = -13002;
    //! 輸入錯誤的到期日
    const  int TAPIERROR_INPUTERROR_TAPIExpireTime                            = -12047;
    //! 錯誤的密碼型別
    const int TAPIERROR_INPUTERROR_TAPIPasswordType                            = -12048;
        //! 錯誤的結算資料型別
        const int TAPIERROR_INPUTERROR_TAPISettleFlagType                                               =-12049;


    /** @}*/

    //=============================================================================
    /**
     *    \addtogroup G_ERR_DISCONNECT_REASON    網路斷開錯誤程式碼定義
     *    @{
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

    /** @}*/
}
#endif //! TAP_API_ERROR_H
