//該檔案定義了TapTradeAPI 使用的資料型別和資料結構
#ifndef ITAP_TRADE_API_DATA_TYPE_H
#define ITAP_TRADE_API_DATA_TYPE_H
#include "iTapAPICommDef.h"


namespace ITapTrade
{
#pragma pack(push, 1)


    //=============================================================================
    /**
     *    \addtogroup G_DATATYPE_T_TAPIACCOUNTTYPE    賬號型別
     *    @{
     */
    //=============================================================================
    //! 賬號型別
    typedef TAPICHAR            TAPIAccountType;
    //! 個人客戶
    const TAPIAccountType        TAPI_ACCOUNT_TYPE_PERSON                = 'P';
    //! 機構客戶
    const TAPIAccountType        TAPI_ACCOUNT_TYPE_ORGANIZATION            = 'O';
    //! 代理人
    const TAPIAccountType        TAPI_ACCOUNT_TYPE_AGENT = 'A';
    //!Margin
    const TAPIAccountType        TAPI_ACCOUNT_TYPE_MARGIN = 'M';
    //! Internal
    const TAPIAccountType        TAPI_ACCOUNT_TYPE_HOUSE = 'H';
    //! 股票賬戶
    const TAPIAccountType        TAPI_ACCOUNT_TYPE_STOCK = 'S';
    /** @}*/

    //=============================================================================
    /**
    *    \addtogroup G_DATATYPE_T_TAPIRIGHTIDTYPE    許可權編碼型別
    *    @{
    */
    //=============================================================================
    //! 許可權編碼型別
    typedef TAPIINT32            TAPIRightIDType;
    //! 系統刪單
    const TAPIRightIDType        TAPI_RIGHT_ORDER_DEL    = 30001;
    //! 訂單稽核
    const TAPIRightIDType        TAPI_RIGHT_ORDER_CHECK    = 30002;
    //! 只可查詢
    const TAPIRightIDType        TAPI_RIGHT_ONLY_QRY        = 31000;
    //! 只可開倉
    const TAPIRightIDType        TAPI_RIGHT_ONLY_OPEN    = 31001;
    /** @}*/

    //=============================================================================
    /**
     *    \addtogroup G_DATATYPE_T_TAPIUSERTYPETYPE    登入使用者身份型別
     *    @{
     */
    //=============================================================================
    //! 登入使用者身份型別
    typedef TAPIINT32            TAPIUserTypeType;
    //! 投資者使用者
    const TAPIUserTypeType        TAPI_USERTYPE_CLIENT                    =10000;
    //! 經紀人
    const TAPIUserTypeType        TAPI_USERTYPE_BROKER                    =20000;
    //! 交易員
    const TAPIUserTypeType        TAPI_USERTYPE_TRADER                    =30000;
    //! 風控
    const TAPIUserTypeType        TAPI_USERTYPE_RISK                        =40000;
    //! 管理員
    const TAPIUserTypeType        TAPI_USERTYPE_MANAGER                    =50000;
    //! 行情
    const TAPIUserTypeType        TAPI_USERTYPE_QUOTE                        =60000;
    /** @}*/

    //=============================================================================
    /**
     *    \addtogroup G_DATATYPE_T_TAPIACCOUNTSTATE    賬號狀態
     *    @{
     */
    //=============================================================================
    //! 賬號狀態
    typedef TAPICHAR            TAPIAccountState;
    //! 正常
    const TAPIAccountState        TAPI_ACCOUNT_STATE_NORMAL                = 'N';
    //! 銷戶
    const TAPIAccountState        TAPI_ACCOUNT_STATE_CANCEL                = 'C';
    //! 休眠
    const TAPIAccountState        TAPI_ACCOUNT_STATE_SLEEP               = 'S';
    /** @}*/



    //=============================================================================
    /**
     *    \addtogroup G_DATATYPE_T_TAPIACCOUNTRIGHTTYPE    賬戶交易狀態
     *    @{
     */
    //=============================================================================
    //! 客戶交易狀態型別
    typedef TAPICHAR            TAPIAccountRightType;
    //! 正常交易
    const    TAPIAccountRightType    TAPI_ACCOUNT_TRADING_RIGHT_NORMAL = '0';
    //! 禁止交易
    const    TAPIAccountRightType    TAPI_ACCOUNT_TRADING_RIGHT_NOTRADE = '1';
    //! 只可平倉
    const    TAPIAccountRightType    TAPI_ACCOUNT_TRADING_RIGHT_CLOSE = '2';
    /** @}*/

    //=============================================================================
    /**
     *    \addtogroup G_DATATYPE_T_TAPIORDERTYPETYPE    委託型別
     *    @{
     */
    //=============================================================================
    //! 委託型別
    typedef TAPICHAR                TAPIOrderTypeType;
    //! 市價
    const TAPIOrderTypeType            TAPI_ORDER_TYPE_MARKET                = '1';
    //! 限價
    const TAPIOrderTypeType            TAPI_ORDER_TYPE_LIMIT                = '2';
    //! 市價止損
    const TAPIOrderTypeType            TAPI_ORDER_TYPE_STOP_MARKET            = '3';
    //! 限價止損
    const TAPIOrderTypeType            TAPI_ORDER_TYPE_STOP_LIMIT            = '4';
    //! 期權行權
    const TAPIOrderTypeType            TAPI_ORDER_TYPE_OPT_EXEC            = '5';
    //! 期權棄權
    const TAPIOrderTypeType            TAPI_ORDER_TYPE_OPT_ABANDON            = '6';
    //! 詢價
    const TAPIOrderTypeType            TAPI_ORDER_TYPE_REQQUOT                = '7';
    //! 應價
    const TAPIOrderTypeType            TAPI_ORDER_TYPE_RSPQUOT                = '8';
    //! 冰山單
    const TAPIOrderTypeType            TAPI_ORDER_TYPE_ICEBERG                = '9';
    //! 影子單
    const TAPIOrderTypeType            TAPI_ORDER_TYPE_GHOST                = 'A';
    //港交所競價單
    const TAPIOrderTypeType            TAPI_ORDER_TYPE_HKEX_AUCTION        = 'B';
    //互換
    const TAPIOrderTypeType            TAPI_ORDER_TYPE_SWAP                = 'C';
    /** @}*/

    //=============================================================================
    /**
     *    \addtogroup G_DATATYPE_T_TAPIORDERSOURCETYPE    委託來源
     *    @{
     */
    //=============================================================================
    //! 委託來源
    typedef TAPICHAR                TAPIOrderSourceType;
    //! 自助電子單
    const TAPIOrderSourceType        TAPI_ORDER_SOURCE_SELF_ETRADER            = '1';
    //! 代理電子單
    const TAPIOrderSourceType        TAPI_ORDER_SOURCE_PROXY_ETRADER            = '2';
    //! 外部電子單(外部電子系統下單，本系統錄入)
    const TAPIOrderSourceType        TAPI_ORDER_SOURCE_JTRADER                = '3';
    //! 人工錄入單(外部其他方式下單，本系統錄入)
    const TAPIOrderSourceType        TAPI_ORDER_SOURCE_MANUAL                = '4';
    //! carry單
    const TAPIOrderSourceType        TAPI_ORDER_SOURCE_CARRY                    = '5';
    //! 程式化報單
    const TAPIOrderSourceType        TAPI_ORDER_SOURCE_PROGRAM                = '6';
    //! 交割行權
    const TAPIOrderSourceType        TAPI_ORDER_SOURCE_DELIVERY                = '7';
    //! 期權放棄
    const TAPIOrderSourceType        TAPI_ORDER_SOURCE_ABANDON                = '8';
    //! 通道費
    const TAPIOrderSourceType        TAPI_ORDER_SOURCE_CHANNEL                = '9';
    /** @}*/

    //=============================================================================
    /**
     *    \addtogroup G_DATATYPE_T_TAPITIMEINFORCETYPE    委託有效型別
     *    @{
     */
    //=============================================================================
    //! 委託有效型別
    typedef TAPICHAR                TAPITimeInForceType;
    //! 當日有效
    const TAPITimeInForceType        TAPI_ORDER_TIMEINFORCE_GFD                    = '0';
    //! 取消前有效
    const TAPITimeInForceType        TAPI_ORDER_TIMEINFORCE_GTC                    = '1';
    //! 指定日期前有效
    const TAPITimeInForceType        TAPI_ORDER_TIMEINFORCE_GTD                    = '2';
    //! FAK或IOC
    const TAPITimeInForceType        TAPI_ORDER_TIMEINFORCE_FAK                    = '3';
    //! FOK
    const TAPITimeInForceType        TAPI_ORDER_TIMEINFORCE_FOK                    = '4';
    /** @}*/

    //=============================================================================
    /**
     *    \addtogroup G_DATATYPE_T_TAPISIDETYPE    買賣型別
     *    @{
     */
    //=============================================================================
    //! 買賣型別
    typedef TAPICHAR                TAPISideType;
    //! 無
    const TAPISideType                TAPI_SIDE_NONE                            = 'N';
    //! 買入
    const TAPISideType                TAPI_SIDE_BUY                            = 'B';
    //! 賣出
    const TAPISideType                TAPI_SIDE_SELL                            = 'S';
    /** @}*/

    //=============================================================================
    /**
     *    \addtogroup G_DATATYPE_T_TAPIPOSITIONEFFECTTYPE    開平型別
     *    @{
     */
    //=============================================================================
    //! 開平型別
    typedef TAPICHAR                TAPIPositionEffectType;
    //! 不分開平
    const TAPIPositionEffectType    TAPI_PositionEffect_NONE                = 'N';
    //! 開倉
    const TAPIPositionEffectType    TAPI_PositionEffect_OPEN                = 'O';
    //! 平倉
    const TAPIPositionEffectType    TAPI_PositionEffect_COVER            = 'C';
    //! 平當日
    const TAPIPositionEffectType    TAPI_PositionEffect_COVER_TODAY        = 'T';
    /** @}*/

    //=============================================================================
    /**
     *    \addtogroup G_DATATYPE_T_TAPIHEDGEFLAGTYPE    投機保值型別
     *    @{
     */
    //=============================================================================
    //! 投機保值型別
    typedef TAPICHAR                TAPIHedgeFlagType;
    //! 無
    const TAPIHedgeFlagType            TAPI_HEDGEFLAG_NONE                    = 'N';
    //! 投機
    const TAPIHedgeFlagType            TAPI_HEDGEFLAG_T                    = 'T';
    //! 保值
    const TAPIHedgeFlagType            TAPI_HEDGEFLAG_B                    = 'B';
    //! 套利
    const TAPIHedgeFlagType            TAPI_HEDGEFLAG_L                    = 'L';
    /** @}*/




    //=============================================================================
    /**
     *    \addtogroup G_DATATYPE_T_TAPIORDERSTATETYPE    委託狀態型別
     *    @{
     */
    //=============================================================================
    //! 委託狀態型別
    typedef TAPICHAR                TAPIOrderStateType;
    //! 終端提交
    const TAPIOrderStateType        TAPI_ORDER_STATE_SUBMIT                = '0';
    //! 已受理
    const TAPIOrderStateType        TAPI_ORDER_STATE_ACCEPT                = '1';
    //! 策略待觸發
    const TAPIOrderStateType        TAPI_ORDER_STATE_TRIGGERING            = '2';
    //! 交易所待觸發
    const TAPIOrderStateType        TAPI_ORDER_STATE_EXCTRIGGERING        = '3';
    //! 已排隊
    const TAPIOrderStateType        TAPI_ORDER_STATE_QUEUED                = '4';
    //! 部分成交
    const TAPIOrderStateType        TAPI_ORDER_STATE_PARTFINISHED        = '5';
    //! 完全成交
    const TAPIOrderStateType        TAPI_ORDER_STATE_FINISHED            = '6';
    //! 待撤消(排隊臨時狀態)
    const TAPIOrderStateType        TAPI_ORDER_STATE_CANCELING            = '7';
    //! 待修改(排隊臨時狀態)
    const TAPIOrderStateType        TAPI_ORDER_STATE_MODIFYING            = '8';
    //! 完全撤單
    const TAPIOrderStateType        TAPI_ORDER_STATE_CANCELED            = '9';
    //! 已撤餘單
    const TAPIOrderStateType        TAPI_ORDER_STATE_LEFTDELETED        = 'A';
    //! 指令失敗
    const TAPIOrderStateType        TAPI_ORDER_STATE_FAIL                = 'B';
    //! 策略刪除
    const TAPIOrderStateType        TAPI_ORDER_STATE_DELETED            = 'C';
    //! 已掛起
    const TAPIOrderStateType        TAPI_ORDER_STATE_SUPPENDED            = 'D';
    //! 到期刪除
    const TAPIOrderStateType        TAPI_ORDER_STATE_DELETEDFOREXPIRE    = 'E';
    //! 已生效——詢價成功
    const TAPIOrderStateType        TAPI_ORDER_STATE_EFFECT                = 'F';
    //! 已申請——行權、棄權、套利等申請成功
    const TAPIOrderStateType        TAPI_ORDER_STATE_APPLY                = 'G';
    /** @}*/

    //=============================================================================
    /**
     *    \addtogroup G_DATATYPE_T_TAPICALCULATEMODETYPE    計算方式
     *    @{
     */
    //=============================================================================
    //! 計算方式
    typedef TAPICHAR               TAPICalculateModeType;
    
    //!比例+定額（僅限手續費）大於0.01部分為定額，小於0.01部分為比例，如：0.001為比例收取1%。
    const TAPICalculateModeType        TAPI_CALULATE_MODE_COMBINE                = '0';
    //! 比例
    const TAPICalculateModeType        TAPI_CALCULATE_MODE_PERCENTAGE          = '1';
    //! 定額
    const TAPICalculateModeType        TAPI_CALCULATE_MODE_QUOTA               = '2';
    //! 差值比例    
    const TAPICalculateModeType        TAPI_CALCULATE_MODE_CHAPERCENTAGE        = '3';
    //! 差值定額
    const TAPICalculateModeType        TAPI_CALCULATE_MODE_CHAQUOTA            = '4';
    //! 折扣
    const TAPICalculateModeType        TAPI_CALCULATE_MODE_DISCOUNT            = '5';
    /** @}*/

    //=============================================================================
    /**
     *    \addtogroup G_DATATYPE_T_TAPIMATCHSOURCETYPE    成交來源
     *    @{
     */
    //=============================================================================
    //! 成交來源
    typedef TAPICHAR                TAPIMatchSourceType;
    //! 全部
    const TAPIMatchSourceType        TAPI_MATCH_SOURCE_ALL                   = '0';
    //! 自助電子單
    const TAPIMatchSourceType        TAPI_MATCH_SOURCE_SELF_ETRADER          = '1';
    //! 代理電子單
    const TAPIMatchSourceType        TAPI_MATCH_SOURCE_PROXY_ETRADER         = '2';
    //! 外部電子單
    const TAPIMatchSourceType        TAPI_MATCH_SOURCE_JTRADER                = '3';
    //! 人工錄入單
    const TAPIMatchSourceType        TAPI_MATCH_SOURCE_MANUAL                = '4';
    //! carry單
    const TAPIMatchSourceType        TAPI_MATCH_SOURCE_CARRY                    = '5';
    //! 程式化單
    const TAPIMatchSourceType        TAPI_MATCH_SOURCE_PROGRAM                = '6';
    //! 交割行權
    const TAPIMatchSourceType        TAPI_MATCH_SOURCE_DELIVERY                = '7';
    //! 期權放棄
    const TAPIMatchSourceType        TAPI_MATCH_SOURCE_ABANDON                = '8';
    //! 通道費
    const TAPIMatchSourceType        TAPI_MATCH_SOURCE_CHANNEL                = '9';
    //! 易盛API
    const TAPIMatchSourceType        TAPI_MATCH_SOURCE_ESUNNY_API            = 'A';
    /** @}*/

    //=============================================================================
    /**
     *    \addtogroup G_DATATYPE_T_TAPIOPENCLOSEMODETYPE    開平方式
     *    @{
     */
    //=============================================================================
    //! 開平方式
    typedef TAPICHAR                TAPIOpenCloseModeType;
    //! 不區分開平
    const TAPIOpenCloseModeType        TAPI_CLOSE_MODE_NONE                = 'N';
    //! 平倉未了結
    const TAPIOpenCloseModeType        TAPI_CLOSE_MODE_UNFINISHED            = 'U';
    //! 區分開倉和平倉
    const TAPIOpenCloseModeType        TAPI_CLOSE_MODE_OPENCOVER            = 'C';
    //! 區分開倉、平倉和平今
    const TAPIOpenCloseModeType        TAPI_CLOSE_MODE_CLOSETODAY            = 'T';
    /** @}*/

    //=============================================================================
    /**
     *    \addtogroup G_DATATYPE_T_TAPIFUTUREALGTYPE    期貨演算法
     *    @{
     */
    //=============================================================================
    //! 期貨演算法
    typedef TAPICHAR                TAPIFutureAlgType;
    //! 逐筆
    const TAPIFutureAlgType            TAPI_FUTURES_ALG_ZHUBI                  = '1';
    //! 盯市
    const TAPIFutureAlgType            TAPI_FUTURES_ALG_DINGSHI                = '2';
    /** @}*/

    //=============================================================================
    /**
     *    \addtogroup G_DATATYPE_T_TAPIOPTIONALGTYPE    期權演算法
     *    @{
     */
    //=============================================================================
    //! 期權演算法
    typedef TAPICHAR                TAPIOptionAlgType;
    //! 期貨方式
    const TAPIOptionAlgType         TAPI_OPTION_ALG_FUTURES                 = '1';
    //! 期權方式
    const TAPIOptionAlgType         TAPI_OPTION_ALG_OPTION                  = '2';
    /** @}*/


    //=============================================================================
    /**
    *    \addtogroup G_DATATYPE_T_CONTACTINFO    二次認證授權碼傳送型別
    *    @{
    */
    //=============================================================================
    //! 二次認證授權碼認證方式
    typedef TAPICHAR                TAPISendType;
    //! 簡訊認證
    const TAPISendType         SENDTYPE_SMS = 'S';
    //! 郵件認證
    const TAPISendType         SENDTYPE_MAIL = 'M';
    /** @}*/


    //=============================================================================
    /**
     *    \addtogroup G_DATATYPE_T_TAPIBANKACCOUNTLWFLAGTYPE    本外幣標識
     *    @{
     */
    //=============================================================================
    //! 本外幣標識
    typedef TAPICHAR                TAPIBankAccountLWFlagType;
    //! 境內人民幣賬戶
    const TAPIBankAccountLWFlagType    TAPI_LWFlag_L                    = 'L';
    //! 客戶境內外幣賬戶
    const TAPIBankAccountLWFlagType    TAPI_LWFlag_W                    = 'W';
    /** @}*/


    //=============================================================================
    /**
    *    \addtogroup G_DATATYPE_T_TAPICASHADJUSTTYPETYPE    資金調整型別
    *    @{
    */
    //=============================================================================
    //! 資金調整型別
    typedef TAPICHAR                        TAPICashAdjustTypeType;
    //! 手續費調整
    const TAPICashAdjustTypeType            TAPI_CASHINOUT_MODE_FEEADJUST = '0';
    //! 盈虧調整
    const TAPICashAdjustTypeType            TAPI_CASHINOUT_MODE_YKADJUST = '1';
    //! 質押資金
    const TAPICashAdjustTypeType            TAPI_CASHINOUT_MODE_PLEDGE = '2';
    //! 利息收入
    const TAPICashAdjustTypeType            TAPI_CASHINOUT_MODE_INTERESTREVENUE = '3';
    //! 代扣費用
    const TAPICashAdjustTypeType            TAPI_CASHINOUT_MODE_COLLECTIONCOST = '4';
    //! 其它
    const TAPICashAdjustTypeType            TAPI_CASHINOUT_MODE_OTHER = '5';
    //! 公司間撥賬
    const TAPICashAdjustTypeType            TAPI_CASHINOUT_MODE_COMPANY = '6';
    /** @}*/



    //=============================================================================
    /**
     *    \addtogroup G_DATATYPE_T_TAPIMARGINCALCULATEMODETYPE    期貨保證金方式
     *    @{
     */
    //=============================================================================
    //! 期貨保證金方式
    typedef TAPICHAR                TAPIMarginCalculateModeType;
    //! 分筆
    const TAPIMarginCalculateModeType TAPI_DEPOSITCALCULATE_MODE_FEN     = '1';
    //! 鎖倉
    const TAPIMarginCalculateModeType TAPI_DEPOSITCALCULATE_MODE_SUO     = '2';
    /** @}*/

    //=============================================================================
    /**
     *    \addtogroup G_DATATYPE_T_TAPIOPTIONMARGINCALCULATEMODETYPE    期權保證金公式
     *    @{
     */
    //=============================================================================
    //! 期權保證金公式,據此判斷該品種期權採用何種內建計算公式計算保證金
    typedef TAPICHAR                TAPIOptionMarginCalculateModeType;
    /** @}*/

    //=============================================================================
    /**
     *    \addtogroup G_DATATYPE_T_TAPICMBDIRECTTYPE    組合方向
     *    @{
     */
    //=============================================================================
    //! 組合方向,品種兩腿組合合約的買賣方向和第幾腿相同
    typedef TAPICHAR                TAPICmbDirectType;
    //! 和第一腿一致
    const TAPICmbDirectType         TAPI_CMB_DIRECT_FIRST                    = '1';
    //! 和第二腿一致
    const TAPICmbDirectType         TAPI_CMB_DIRECT_SECOND                   = '2';
    /** @}*/

    //=============================================================================
    /**
     *    \addtogroup G_DATATYPE_T_TAPIDELIVERYMODETYPE    交割行權方式
     *    @{
     */
    //=============================================================================
    //! 交割行權方式,期貨和期權了結的方式
    typedef TAPICHAR                TAPIDeliveryModeType;
    //! 實物交割
    const TAPIDeliveryModeType        TAPI_DELIVERY_MODE_GOODS            = 'G';
    //! 現金交割
    const TAPIDeliveryModeType        TAPI_DELIVERY_MODE_CASH                = 'C';
    //! 期權行權
    const TAPIDeliveryModeType        TAPI_DELIVERY_MODE_EXECUTE            = 'E';
    //! 期權放棄
    const TAPIDeliveryModeType        TAPI_DELIVERY_MODE_ABANDON            = 'A';
    //! 港交所行權
    const TAPIDeliveryModeType        TAPI_DELIVERY_MODE_HKF                = 'H';
    /** @}*/

    //=============================================================================
    /**
     *    \addtogroup G_DATATYPE_T_TAPICONTRACTTYPETYPE    合約型別
     *    @{
     */
    //=============================================================================
    //! 合約型別
    typedef TAPICHAR                TAPIContractTypeType;
    //! 交易行情合約
    const TAPIContractTypeType        TAPI_CONTRACT_TYPE_TRADEQUOTE        ='1';
    //! 行情合約
    const TAPIContractTypeType        TAPI_CONTRACT_TYPE_QUOTE            ='2';
    /** @}*/

    //=============================================================================
    /**
     *    \addtogroup G_DATATYPE_T_TAPITACTICSTYPETYPE    策略單型別
     *    @{
     */
    //=============================================================================
    //! 策略單型別
    typedef TAPICHAR                    TAPITacticsTypeType;
    //! 無
    const TAPITacticsTypeType            TAPI_TACTICS_TYPE_NONE                = 'N';
    //! 預備單(埋單)
    const TAPITacticsTypeType            TAPI_TACTICS_TYPE_READY                = 'M';
    //! 自動單
    const TAPITacticsTypeType            TAPI_TACTICS_TYPE_ATUO                = 'A';
    //! 條件單
    const TAPITacticsTypeType            TAPI_TACTICS_TYPE_CONDITION            = 'C';
    /** @}*/

    //=============================================================================
    /**
     *    \addtogroup G_DATATYPE_T_TAPIORDERACT    訂單操作型別
     *    @{
     */
    //=============================================================================
    //! 訂單操作型別
    typedef TAPICHAR        TAPIORDERACT;
    //! 報單
    const TAPIORDERACT APIORDER_INSERT            = '1';
    //! 改單
    const TAPIORDERACT APIORDER_MODIFY            = '2';
    //! 撤單
    const TAPIORDERACT APIORDER_DELETE            = '3';
    //! 掛起
    const TAPIORDERACT APIORDER_SUSPEND            = '4';
    //! 啟用
    const TAPIORDERACT APIORDER_ACTIVATE        = '5';
    //! 刪除
    const TAPIORDERACT APIORDER_SYSTEM_DELETE    = '6';
    /** @}*/

    //=============================================================================
    /**
     *    \addtogroup G_DATATYPE_T_TAPITRIGGERCONDITIONTYPE    觸發條件型別
     *    @{
     */
    //=============================================================================
    //! 觸發條件型別
    typedef TAPICHAR                TAPITriggerConditionType;
    //! 無
    const TAPITriggerConditionType    TAPI_TRIGGER_CONDITION_NONE            = 'N';
    //! 大於等於
    const TAPITriggerConditionType    TAPI_TRIGGER_CONDITION_GREAT        = 'G';
    //! 小於等於
    const TAPITriggerConditionType    TAPI_TRIGGER_CONDITION_LITTLE        = 'L';
    /** @}*/

    //=============================================================================
    /**
     *    \addtogroup G_DATATYPE_T_TAPITRIGGERPRICETYPETYPE    觸發價格型別
     *    @{
     */
    //=============================================================================
    //! 觸發價格型別
    typedef TAPICHAR                TAPITriggerPriceTypeType;
    //! 無
    const TAPITriggerPriceTypeType    TAPI_TRIGGER_PRICE_NONE                = 'N';
    //! 買價
    const TAPITriggerPriceTypeType    TAPI_TRIGGER_PRICE_BUY                = 'B';
    //! 賣價
    const TAPITriggerPriceTypeType    TAPI_TRIGGER_PRICE_SELL                = 'S';
    //! 最新價
    const TAPITriggerPriceTypeType    TAPI_TRIGGER_PRICE_LAST                = 'L';
    /** @}*/


    //=============================================================================
    /**
     *    \addtogroup G_DATATYPE_T_TAPITRADINGSTATETYPE    交易狀態
     *    @{
     */
    //=============================================================================
    //! 交易狀態
    typedef TAPICHAR               TAPITradingStateType;
    //! 集合競價
    const TAPITradingStateType      TAPI_TRADE_STATE_BID                = '1';
    //! 集合競價撮合
    const TAPITradingStateType      TAPI_TRADE_STATE_MATCH              = '2';
    //! 連續交易
    const TAPITradingStateType      TAPI_TRADE_STATE_CONTINUOUS         = '3';
    //! 交易暫停
    const TAPITradingStateType      TAPI_TRADE_STATE_PAUSED             = '4';
    //! 閉市
    const TAPITradingStateType      TAPI_TRADE_STATE_CLOSE              = '5';
    //! 閉市處理時間
    const TAPITradingStateType      TAPI_TRADE_STATE_DEALLAST           = '6';
    //! 閘道器未連
    const TAPITradingStateType        TAPI_TRADE_STATE_GWDISCONNECT        = '0';
    //! 未知狀態
    const TAPITradingStateType        TAPI_TRADE_STATE_UNKNOWN            = 'N';
    //! 正初始化
    const TAPITradingStateType        TAPI_TRADE_STATE_INITIALIZE            = 'I';
    //! 準備就緒
    const TAPITradingStateType        TAPI_TRADE_STATE_READY                = 'R';
    /** @}*/



    //=============================================================================
    /**
     *    \addtogroup G_DATATYPE_T_TAPINOTICEIGNOREFLAGTYPE    忽略後臺推送通知標記
     *    @{
     */
    //=============================================================================
    //! 忽略後臺推送通知標記
    typedef TAPIUINT32              TAPINoticeIgnoreFlagType;
    //! 推送所有資訊
    const TAPINoticeIgnoreFlagType TAPI_NOTICE_IGNORE_NONE                = 0x00000000;
    //! 忽略所有推送
    const TAPINoticeIgnoreFlagType TAPI_NOTICE_IGNORE_ALL                = 0xFFFFFFFF;
    //! 忽略資金推送:OnRtnFund
    const TAPINoticeIgnoreFlagType TAPI_NOTICE_IGNORE_FUND                = 0x00000001;
    //! 忽略委託推送:OnRtnOrder
    const TAPINoticeIgnoreFlagType TAPI_NOTICE_IGNORE_ORDER                = 0x00000002;
    //! 忽略成交推送:OnRtnFill
    const TAPINoticeIgnoreFlagType TAPI_NOTICE_IGNORE_FILL                = 0x00000004;
    //! 忽略持倉推送:OnRtnPosition
    const TAPINoticeIgnoreFlagType TAPI_NOTICE_IGNORE_POSITION            = 0x00000008;
    //! 忽略平倉推送:OnRtnClose
    const TAPINoticeIgnoreFlagType TAPI_NOTICE_IGNORE_CLOSE                = 0x00000010;
    //! 忽略持倉盈虧推送:OnRtnPositionProfit
    const TAPINoticeIgnoreFlagType TAPI_NOTICE_IGNORE_POSITIONPROFIT    = 0x00000020;
    /** @}*/


    //=============================================================================
    /**
     *    \addtogroup G_DATATYPE_T_TAPIORDERQRYTYPETYPE    委託查詢型別
     *    @{
     */
    //=============================================================================
    //! 委託查詢型別
    typedef TAPICHAR              TAPIOrderQryTypeType;
    //! 返回所有委託
    const TAPIOrderQryTypeType TAPI_ORDER_QRY_TYPE_ALL                = 'A';
    //! 只返回未結束的委託
    const TAPIOrderQryTypeType TAPI_ORDER_QRY_TYPE_UNENDED            = 'U';
    /** @}*/



    //! ------------------------------------------------------------------------------------------

    //! 登入認證資訊
    struct TapAPITradeLoginAuth
    {
            TAPISTR_20                    UserNo;                    ///< 使用者名稱
            TAPIYNFLAG                    ISModifyPassword;        ///< 是否修改密碼    
            TAPISTR_20                    Password;                ///< 密碼
            TAPISTR_20                    NewPassword;            ///< 新密碼
    };

    //! 登入反饋資訊
    struct TapAPITradeLoginRspInfo
    {
            TAPISTR_20                    UserNo;                            ///< 使用者編號
            TAPIUserTypeType            UserType;                        ///< 使用者型別
            TAPISTR_20                    UserName;                        ///< 使用者名稱
            TAPISTR_50                    ReservedInfo;                    ///< 預留資訊
            TAPISTR_40                    LastLoginIP;                    ///< 上次登入IP
            TAPIUINT32                    LastLoginProt;                    ///< 上次登入埠
            TAPIDATETIME                LastLoginTime;                    ///< 上次登入時間
            TAPIDATETIME                LastLogoutTime;                    ///< 上次退出時間
            TAPIDATE                    TradeDate;                        ///< 當前交易日期
            TAPIDATETIME                LastSettleTime;                    ///< 上次結算時間
            TAPIDATETIME                StartTime;                        ///< 系統啟動時間
            TAPIDATETIME                InitTime;                        ///< 系統初始化時間
    };
    //!請求二次認證授權碼應答
    struct  TapAPIRequestVertificateCodeRsp
    {
        TAPISecondSerialIDType SecondSerialID;                            ///< 二次認證授權碼序號
        TAPIINT32 Effective;                                            ///< 二次認證授權碼有效期（分）。
    };

    //! 賬號相關資訊查詢請求
    struct TapAPIAccQryReq
    {
    };

    //! 資金賬號資訊
    struct TapAPIAccountInfo
    {
            TAPISTR_20              AccountNo;                              ///< 資金賬號
            TAPIAccountType            AccountType;                            ///< 賬號型別
            TAPIAccountState        AccountState;                           ///< 賬號狀態
            TAPIAccountRightType        AccountTradeRight;                    ///<交易狀態
            TAPISTR_10                CommodityGroupNo;                        ///<可交易品種組.
            TAPISTR_20                AccountShortName;                       ///< 賬號簡稱
            TAPISTR_20                AccountEnShortName;                        ///<賬號英文簡稱
    };

    //! 客戶下單請求結構
    struct TapAPINewOrder
    {
            TAPISTR_20                    AccountNo;                        ///< 客戶資金帳號，必填

            TAPISTR_10                    ExchangeNo;                        ///< 交易所編號，必填
            TAPICommodityType            CommodityType;                    ///< 品種型別，必填
            TAPISTR_10                    CommodityNo;                    ///< 品種編碼型別，必填
            TAPISTR_10                    ContractNo;                        ///< 合約1，必填
            TAPISTR_10                    StrikePrice;                    ///< 執行價格1，期權填寫
            TAPICallOrPutFlagType        CallOrPutFlag;                    ///< 看張看跌1 預設N
            TAPISTR_10                    ContractNo2;                    ///< 合約2，預設空
            TAPISTR_10                    StrikePrice2;                    ///< 執行價格2，預設空
            TAPICallOrPutFlagType        CallOrPutFlag2;                    ///< 看張看跌2 預設N

            TAPIOrderTypeType            OrderType;                        ///< 委託型別 必填
            TAPIOrderSourceType            OrderSource;                    ///< 委託來源，預設程式單。
            TAPITimeInForceType            TimeInForce;                    ///< 委託有效型別,預設當日有效
            TAPIDATETIME                ExpireTime;                        ///< 有效日期(GTD情況下使用)

            TAPIYNFLAG                    IsRiskOrder;                    ///< 是否風險報單，預設非風險保單
            TAPISideType                OrderSide;                        ///< 買入賣出
            TAPIPositionEffectType        PositionEffect;                    ///< 開平標誌1,預設N
            TAPIPositionEffectType        PositionEffect2;                ///< 開平標誌2，預設N
            TAPISTR_50                    InquiryNo;                        ///< 詢價號
            TAPIHedgeFlagType            HedgeFlag;                        ///< 投機保值，預設N
            TAPIREAL64                    OrderPrice;                        ///< 委託價格1
            TAPIREAL64                    OrderPrice2;                    ///< 委託價格2，做市商應價使用
            TAPIREAL64                    StopPrice;                        ///< 觸發價格
            TAPIUINT32                    OrderQty;                        ///< 委託數量，必填
            TAPIUINT32                    OrderMinQty;                    ///< 最小成交量，預設1

            TAPIUINT32                    MinClipSize;                    ///< 冰山單最小隨機量
            TAPIUINT32                    MaxClipSize;                    ///< 冰山單最大隨機量

            TAPIINT32                    RefInt;                            ///< 整型參考值
            TAPIREAL64                    RefDouble;                        ///<浮點參考值
            TAPISTR_50                    RefString;                        ///< 字串參考值

            TAPIClientIDType            ClientID;                        ///<客戶子賬號，如果存在子賬號，則自行上報子賬號
            TAPITacticsTypeType            TacticsType;                    ///< 策略單型別，預設N
            TAPITriggerConditionType    TriggerCondition;                ///< 觸發條件，預設N
            TAPITriggerPriceTypeType    TriggerPriceType;                ///< 觸發價格型別，預設N
            TAPIYNFLAG                    AddOneIsValid;                    ///< 是否T+1有效,預設T+1有效。
    public:
        TapAPINewOrder()
        {
            memset(this, 0, sizeof(TapAPINewOrder));
            CallOrPutFlag = TAPI_CALLPUT_FLAG_NONE;
            CallOrPutFlag2 = TAPI_CALLPUT_FLAG_NONE;
            OrderSource = TAPI_ORDER_SOURCE_PROGRAM;
            TimeInForce=TAPI_ORDER_TIMEINFORCE_GFD;
            IsRiskOrder = APIYNFLAG_NO;
            PositionEffect = TAPI_PositionEffect_NONE;
            PositionEffect2 = TAPI_PositionEffect_NONE;
            HedgeFlag = TAPI_HEDGEFLAG_NONE;
            OrderMinQty = 1;
            TacticsType = TAPI_TACTICS_TYPE_NONE;
            TriggerCondition = TAPI_TRIGGER_CONDITION_NONE;
            TriggerPriceType = TAPI_TRIGGER_PRICE_NONE;
            AddOneIsValid = APIYNFLAG_YES;
        }
    };


    //! 委託完整資訊
    struct TapAPIOrderInfo
    {
            TAPISTR_20                    AccountNo;                        ///< 客戶資金帳號

            TAPISTR_10                    ExchangeNo;                        ///< 交易所編號
            TAPICommodityType            CommodityType;                    ///< 品種型別
            TAPISTR_10                    CommodityNo;                    ///< 品種編碼型別
            TAPISTR_10                    ContractNo;                        ///< 合約1
            TAPISTR_10                    StrikePrice;                    ///< 執行價格1
            TAPICallOrPutFlagType        CallOrPutFlag;                    ///< 看張看跌1
            TAPISTR_10                    ContractNo2;                    ///< 合約2
            TAPISTR_10                    StrikePrice2;                    ///< 執行價格2
            TAPICallOrPutFlagType        CallOrPutFlag2;                    ///< 看張看跌2

            TAPIOrderTypeType            OrderType;                        ///< 委託型別
            TAPIOrderSourceType            OrderSource;                    ///< 委託來源
            TAPITimeInForceType            TimeInForce;                    ///< 委託有效型別
            TAPIDATETIME                ExpireTime;                        ///< 有效日期(GTD情況下使用)

            TAPIYNFLAG                    IsRiskOrder;                    ///< 是否風險報單
            TAPISideType                OrderSide;                        ///< 買入賣出
            TAPIPositionEffectType        PositionEffect;                    ///< 開平標誌1
            TAPIPositionEffectType        PositionEffect2;                ///< 開平標誌2
            TAPISTR_50                    InquiryNo;                        ///< 詢價號
            TAPIHedgeFlagType            HedgeFlag;                        ///< 投機保值
            TAPIREAL64                    OrderPrice;                        ///< 委託價格1
            TAPIREAL64                    OrderPrice2;                    ///< 委託價格2，做市商應價使用
            TAPIREAL64                    StopPrice;                        ///< 觸發價格
            TAPIUINT32                    OrderQty;                        ///< 委託數量
            TAPIUINT32                    OrderMinQty;                    ///< 最小成交量

            TAPIINT32                    RefInt;                            ///< 整型參考值
            TAPIREAL64                    RefDouble;                        ///< 浮點參考值
            TAPISTR_50                    RefString;                                      ///< 字串參考值

            TAPIUINT32                    MinClipSize;                    ///< 冰山單最小隨機量
            TAPIUINT32                    MaxClipSize;                    ///< 冰山單最大隨機量
            TAPISTR_50                    LicenseNo;                        ///< 軟體授權號



            TAPICHAR                    ServerFlag;                        ///< 伺服器標識
            TAPISTR_20                    OrderNo;                        ///< 委託編碼
            TAPISTR_50                  ClientOrderNo;                    ///< 客戶端本地委託編號
            TAPIClientIDType            ClientID;                                           ///< 客戶子賬號.
            TAPITacticsTypeType            TacticsType;                    ///< 策略單型別
            TAPITriggerConditionType    TriggerCondition;                ///< 觸發條件
            TAPITriggerPriceTypeType    TriggerPriceType;                ///< 觸發價格型別
            TAPIYNFLAG                    AddOneIsValid;                    ///< 是否T+1有效

            TAPISTR_40                    ClientLocalIP;                    ///< 終端本地IP
            TAPIMACTYPE                    ClientMac;                        ///< 終端本地Mac地址
            TAPISTR_40                    ClientIP;                        ///< 終端網路地址.

            TAPIUINT32                    OrderStreamID;                    ///< 委託流水號
            TAPISTR_10                    UpperNo;                        ///< 上手號
            TAPISTR_10                    UpperChannelNo;                    ///< 上手通道號

            TAPISTR_20                    OrderLocalNo;                    ///< 本地號
            TAPIUINT32                    UpperStreamID;                    ///< 上手流號

            TAPISTR_50                    OrderSystemNo;                    ///< 系統號
            TAPISTR_50                    OrderExchangeSystemNo;            ///< 交易所繫統號 
            TAPISTR_50                    OrderParentSystemNo;            ///< 父單系統號

            TAPISTR_20                    OrderInsertUserNo;                ///< 下單人
            TAPIDATETIME                OrderInsertTime;                ///< 下單時間
            TAPISTR_20                    OrderCommandUserNo;                ///< 錄單操作人
            TAPISTR_20                    OrderUpdateUserNo;                ///< 委託更新人
            TAPIDATETIME                OrderUpdateTime;                ///< 委託更新時間

            TAPIOrderStateType            OrderState;                        ///< 委託狀態

            TAPIREAL64                    OrderMatchPrice;                ///< 成交價1
            TAPIREAL64                    OrderMatchPrice2;                ///< 成交價2
            TAPIUINT32                    OrderMatchQty;                    ///< 成交量1
            TAPIUINT32                    OrderMatchQty2;                    ///< 成交量2

            TAPIUINT32                    ErrorCode;                        ///< 最後一次操作錯誤資訊碼
            TAPISTR_50                    ErrorText;                        ///< 錯誤資訊

            TAPIYNFLAG                    IsBackInput;                    ///< 是否為錄入委託單
            TAPIYNFLAG                    IsDeleted;                        ///< 委託成交刪除標
            TAPIYNFLAG                    IsAddOne;                        ///< 是否為T+1單

    };

    //! 報單通知結構
    struct TapAPIOrderInfoNotice
    {
            TAPIUINT32                    SessionID;                        ///< 會話ID
            TAPIUINT32                    ErrorCode;                         ///< 錯誤碼
            TapAPIOrderInfo*            OrderInfo;                        ///< 委託完整資訊
    };

    //! 報單操作應答結構
    struct TapAPIOrderActionRsp
    {
            TAPIORDERACT                ActionType;                        ///< 操作型別
            TapAPIOrderInfo*            OrderInfo;                        ///< 委託資訊
    };


    //! 客戶改單請求
    //!必填項有ServerFlag，OrderNo,以及委託價和委託量，止損價。其他欄位咱們沒有用。
    struct TapAPIAmendOrder
    {
        TapAPINewOrder              ReqData;                        ///< 報單請求資料
        TAPICHAR                    ServerFlag;                        ///< 伺服器標識
        TAPISTR_20                  OrderNo;                        ///< 委託編號
    public:
        TapAPIAmendOrder()
        {
            memset(this, 0, sizeof(TapAPIAmendOrder));
        }
    };

    //! 客戶撤單請求結構
    //!必填項是ServerFlag和OrderNo.
    struct TapAPIOrderCancelReq
    {
            TAPIINT32                    RefInt;                            ///< 整型參考值
            TAPIREAL64                    RefDouble;                        ///< 浮點參考值
            TAPISTR_50                    RefString;                        ///< 字串參考值
            TAPICHAR                    ServerFlag;                        ///< 伺服器標識
            TAPISTR_20                    OrderNo;                        ///< 委託編碼
    };

    //! 掛起委託請求結構
    typedef TapAPIOrderCancelReq TapAPIOrderDeactivateReq;

    //! 啟用委託請求結構
    typedef TapAPIOrderCancelReq TapAPIOrderActivateReq;

    //! 刪除委託請求結構
    typedef TapAPIOrderCancelReq TapAPIOrderDeleteReq;

    //! 委託查詢請求結構
    struct TapAPIOrderQryReq
    {
            TAPISTR_20                    AccountNo;                        ///< 資金賬號

            TAPISTR_10                    ExchangeNo;                        ///< 交易所編號
            TAPICommodityType            CommodityType;                    ///< 品種型別
            TAPISTR_10                    CommodityNo;                    ///< 品種編碼型別
            TAPIOrderTypeType            OrderType;                        ///< 委託型別
            TAPIOrderSourceType            OrderSource;                    ///< 委託來源
            TAPITimeInForceType            TimeInForce;                    ///< 委託有效型別
            TAPIDATETIME                ExpireTime;                        ///< 有效日期(GTD情況下使用)

            TAPIYNFLAG                    IsRiskOrder;                    ///< 是否風險報單

            TAPICHAR                    ServerFlag;                        ///< 伺服器標識
            TAPISTR_20                  OrderNo;                        ///< 委託編號

            TAPIYNFLAG                    IsBackInput;                    ///< 是否為錄入委託單
            TAPIYNFLAG                    IsDeleted;                        ///< 委託成交刪除標
            TAPIYNFLAG                    IsAddOne;                        ///< 是否為T+1單
    };

    //! 委託流程查詢
    struct TapAPIOrderProcessQryReq
    {
            TAPICHAR                    ServerFlag;                        ///< 伺服器標識
            TAPISTR_20                    OrderNo;                        ///< 委託編碼
    };

    //! 成交查詢請求結構
    struct TapAPIFillQryReq
    {
        TAPISTR_20                    AccountNo;                        ///< 客戶資金帳號

        TAPISTR_10                    ExchangeNo;                        ///< 交易所編號
        TAPICommodityType            CommodityType;                    ///< 品種型別
        TAPISTR_10                    CommodityNo;                    ///< 品種編碼型別
        TAPISTR_10                    ContractNo;                        ///< 合約1
        TAPISTR_10                    StrikePrice;                    ///< 執行價格
        TAPICallOrPutFlagType        CallOrPutFlag;                    ///< 看張看跌

        TAPIMatchSourceType            MatchSource;                    ///< 委託來源
        TAPISideType                MatchSide;                        ///< 買入賣出
        TAPIPositionEffectType              PositionEffect;                    ///< 開平標誌1

        TAPICHAR                    ServerFlag;                        ///< 伺服器標識
        TAPISTR_20                    OrderNo;                        ///< 委託編碼
        TAPISTR_10                    UpperNo;                        ///< 上手號
        TAPIYNFLAG                    IsDeleted;                        ///< 委託成交刪除標
        TAPIYNFLAG                    IsAddOne;                        ///< 是否為T+1單
    };

    //! 成交資訊
    struct TapAPIFillInfo
    {
            TAPISTR_20                    AccountNo;                        ///< 客戶資金帳號

            TAPISTR_10                    ExchangeNo;                        ///< 交易所編號
            TAPICommodityType            CommodityType;                    ///< 品種型別
            TAPISTR_10                    CommodityNo;                    ///< 品種編碼型別
            TAPISTR_10                    ContractNo;                        ///< 合約1
            TAPISTR_10                    StrikePrice;                    ///< 執行價格
            TAPICallOrPutFlagType        CallOrPutFlag;                    ///< 看張看跌

            TAPIMatchSourceType            MatchSource;                    ///< 委託來源
            TAPISideType                MatchSide;                        ///< 買入賣出
            TAPIPositionEffectType              PositionEffect;                    ///< 開平標誌1

            TAPICHAR                    ServerFlag;                        ///< 伺服器標識
            TAPISTR_20                    OrderNo;                        ///< 委託編碼
            TAPISTR_50                    OrderSystemNo;                    ///< 系統號

            TAPISTR_20                    MatchNo;                        ///< 本地成交號
            TAPISTR_70                    UpperMatchNo;                    ///< 上手成交號
            TAPISTR_70                    ExchangeMatchNo;                ///< 交易所成交號

            TAPIDATETIME                MatchDateTime;                    ///< 成交時間
            TAPIDATETIME                UpperMatchDateTime;                ///< 上手成交時間

            TAPISTR_10                    UpperNo;                        ///< 上手號

            TAPIREAL64                    MatchPrice;                        ///< 成交價
            TAPIUINT32                    MatchQty;                        ///< 成交量

            TAPIYNFLAG                    IsDeleted;                        ///< 委託成交刪除標
            TAPIYNFLAG                    IsAddOne;                        ///< 是否為T+1單

            TAPISTR_10                    FeeCurrencyGroup;                ///< 客戶手續費幣種組
            TAPISTR_10                    FeeCurrency;                    ///< 客戶手續費幣種
            TAPIREAL64                    FeeValue;                        ///< 手續費
            TAPIYNFLAG                    IsManualFee;                    ///< 人工客戶手續費標記

            TAPIREAL64                    ClosePrositionPrice;                    ///< 指定價格平倉
    };

    //! 平倉查詢請求結構
    struct TapAPICloseQryReq
    {
            TAPISTR_20                    AccountNo;                        ///< 客戶資金帳號

            TAPISTR_10                    ExchangeNo;                        ///< 交易所編號
            TAPICommodityType            CommodityType;                    ///< 品種型別
            TAPISTR_10                    CommodityNo;                    ///< 品種編碼型別
    };

    //! 平倉資訊
    struct TapAPICloseInfo
    {
            TAPISTR_20                    AccountNo;                        ///< 客戶資金帳號

            TAPISTR_10                    ExchangeNo;                        ///< 交易所編號
            TAPICommodityType            CommodityType;                    ///< 品種型別
            TAPISTR_10                    CommodityNo;                    ///< 品種編碼型別
            TAPISTR_10                    ContractNo;                        ///< 合約
            TAPISTR_10                    StrikePrice;                    ///< 執行價格
            TAPICallOrPutFlagType        CallOrPutFlag;                    ///< 看張看跌

            TAPISideType                CloseSide;                        ///< 平倉一邊的買入賣出
            TAPIUINT32                    CloseQty;                        ///< 平倉成交量
            TAPIREAL64                    OpenPrice;                        ///< 開倉成交價
            TAPIREAL64                    ClosePrice;                        ///< 平倉成交價

            TAPISTR_20                    OpenMatchNo;                    ///< 本地成交號
            TAPIDATETIME                OpenMatchDateTime;                ///< 成交時間
            TAPISTR_20                    CloseMatchNo;                    ///< 本地成交號
            TAPIDATETIME                CloseMatchDateTime;                ///< 成交時間

            TAPIUINT32                  CloseStreamId;                    ///< 平倉流號

            TAPISTR_10                    CommodityCurrencyGroup;            ///< 品種幣種組
            TAPISTR_10                    CommodityCurrency;                ///< 品種幣種

            TAPIREAL64                    CloseProfit;                    ///< 平倉盈虧
    };

    //! 持倉查詢請求結構
    struct TapAPIPositionQryReq
    {
            TAPISTR_20 AccountNo;
    };



    //! 持倉資訊
    struct TapAPIPositionInfo
    {
            TAPISTR_20                    AccountNo;                        ///< 客戶資金帳號

            TAPISTR_10                    ExchangeNo;                        ///< 交易所編號
            TAPICommodityType            CommodityType;                    ///< 品種型別
            TAPISTR_10                    CommodityNo;                    ///< 品種編碼型別
            TAPISTR_10                    ContractNo;                        ///< 合約1
            TAPISTR_10                    StrikePrice;                    ///< 執行價格
            TAPICallOrPutFlagType        CallOrPutFlag;                    ///< 看張看跌

            TAPISideType                MatchSide;                        ///< 買入賣出
            TAPIHedgeFlagType            HedgeFlag;                        ///< 投機保值

            TAPISTR_70                    PositionNo;                        ///< 本地持倉號，伺服器編寫

            TAPICHAR                    ServerFlag;                        ///< 伺服器標識
            TAPISTR_20                    OrderNo;                        ///< 委託編碼
            TAPISTR_20                    MatchNo;                        ///< 本地成交號
            TAPISTR_10                    UpperNo;                        ///< 上手號


            TAPIREAL64                    PositionPrice;                    ///< 持倉價
            TAPIUINT32                    PositionQty;                    ///< 持倉量

        TAPIUINT32                  PositionStreamId;                ///< 持倉流號

            TAPISTR_10                    CommodityCurrencyGroup;            ///< 品種幣種組
            TAPISTR_10                    CommodityCurrency;                ///< 品種幣種

            TAPIREAL64                    CalculatePrice;                    ///< 當前計算價格

            TAPIREAL64                    AccountInitialMargin;            ///< 客戶初始保證金
            TAPIREAL64                    AccountMaintenanceMargin;        ///< 客戶維持保證金
            TAPIREAL64                    UpperInitialMargin;                ///< 上手初始保證金
            TAPIREAL64                    UpperMaintenanceMargin;            ///< 上手維持保證金

            TAPIREAL64                    PositionProfit;                    ///< 持倉盈虧
            TAPIREAL64                    LMEPositionProfit;                ///< LME持倉盈虧
            TAPIREAL64                    OptionMarketValue;                ///< 期權市值
            TAPIYNFLAG                    IsHistory;                        ///< 是否為昨倉。
    };

    //! 客戶持倉盈虧
    struct TapAPIPositionProfit
    {
            TAPISTR_70                    PositionNo;                        ///< 本地持倉號，伺服器編寫
            TAPIUINT32                    PositionStreamId;                ///< 持倉流號
            TAPIREAL64                    PositionProfit;                    ///< 持倉盈虧
            TAPIREAL64                    LMEPositionProfit;                ///< LME持倉盈虧
            TAPIREAL64                    OptionMarketValue;                ///< 期權市值
            TAPIREAL64                    CalculatePrice;                    ///< 計算價格
    };

    //! 客戶持倉盈虧通知
    struct TapAPIPositionProfitNotice
    {
            TAPIYNFLAG                    IsLast;                            ///< 是否最後一包
            TapAPIPositionProfit*        Data;                            ///< 客戶持倉盈虧資訊
    };

    struct TapAPIPositionSummary
    {
        TAPISTR_20                    AccountNo;                        ///< 客戶資金帳號

        TAPISTR_10                    ExchangeNo;                        ///< 交易所編號
        TAPICommodityType            CommodityType;                    ///< 品種型別
        TAPISTR_10                    CommodityNo;                    ///< 品種編碼型別
        TAPISTR_10                    ContractNo;                        ///< 合約1
        TAPISTR_10                    StrikePrice;                    ///< 執行價格
        TAPICallOrPutFlagType        CallOrPutFlag;                    ///< 看張看跌

        TAPISideType                MatchSide;                        ///< 買入賣出
        TAPIREAL64                    PositionPrice;                    ///< 持倉均價。
        TAPIUINT32                    PositionQty;                    ///< 持倉量
        TAPIUINT32                    HisPositionQty;                    ///< 歷史持倉量
    };



    //! 資金查詢請求
    struct TapAPIFundReq
    {
            TAPISTR_20                    AccountNo;                        ///< 客戶資金帳號
    };
    //! 資金賬號資金資訊
    struct TapAPIFundData
    {
            TAPISTR_20                    AccountNo;                        ///< 客戶資金賬號

            TAPISTR_10                    CurrencyGroupNo;                ///< 幣種組號
            TAPISTR_10                    CurrencyNo;                        ///< 幣種號(為空表示幣種組基幣資金)
            TAPIREAL64                    TradeRate;                        ///< 交易匯率
            TAPIFutureAlgType            FutureAlg;                      ///< 期貨演算法
            TAPIOptionAlgType            OptionAlg;                      ///< 期權演算法

            TAPIREAL64                    PreBalance;                        ///< 上日結存
            TAPIREAL64                    PreUnExpProfit;                    ///< 上日未到期平盈
            TAPIREAL64                    PreLMEPositionProfit;            ///< 上日LME持倉平盈
            TAPIREAL64                    PreEquity;                        ///< 上日權益
            TAPIREAL64                    PreAvailable1;                    ///< 上日可用
            TAPIREAL64                    PreMarketEquity;                ///< 上日市值權益

            TAPIREAL64                    CashInValue;                    ///< 入金
            TAPIREAL64                    CashOutValue;                    ///< 出金
            TAPIREAL64                    CashAdjustValue;                ///< 資金調整
            TAPIREAL64                    CashPledged;                    ///< 質押資金
            TAPIREAL64                    FrozenFee;                        ///< 凍結手續費
            TAPIREAL64                    FrozenDeposit;                    ///< 凍結保證金
            TAPIREAL64                    AccountFee;                        ///< 客戶手續費包含交割手續費
            TAPIREAL64                    SwapInValue;                    ///< 匯入資金
            TAPIREAL64                    SwapOutValue;                    ///< 匯出資金
            TAPIREAL64                    PremiumIncome;                    ///< 權利金收取
            TAPIREAL64                    PremiumPay;                        ///< 權利金支付
            TAPIREAL64                    CloseProfit;                    ///< 平倉盈虧
            TAPIREAL64                    FrozenFund;                        ///< 凍結資金
            TAPIREAL64                    UnExpProfit;                    ///< 未到期平盈
            TAPIREAL64                    ExpProfit;                        ///< 到期平倉盈虧
            TAPIREAL64                    PositionProfit;                    ///< 不含LME持倉盈虧
            TAPIREAL64                    LmePositionProfit;                ///< LME持倉盈虧
            TAPIREAL64                    OptionMarketValue;                ///< 期權市值
            TAPIREAL64                    AccountIntialMargin;            ///< 客戶初始保證金
            TAPIREAL64                    AccountMaintenanceMargin;        ///< 客戶維持保證金
            TAPIREAL64                    UpperInitalMargin;                ///< 上手初始保證金
            TAPIREAL64                    UpperMaintenanceMargin;            ///< 上手維持保證金
            TAPIREAL64                    Discount;                        ///< LME貼現

            TAPIREAL64                    Balance;                        ///< 當日結存
            TAPIREAL64                    Equity;                            ///< 當日權益
            TAPIREAL64                    Available;                        ///< 當日可用
            TAPIREAL64                    CanDraw;                        ///< 可提取
            TAPIREAL64                    MarketEquity;                    ///< 賬戶市值
            TAPIREAL64                    AuthMoney;                      ///< 授信資金
    };

    //! 交易品種資訊
    struct TapAPICommodityInfo
    {
            TAPISTR_10                            ExchangeNo;                        //交易所編碼
            TAPICommodityType                    CommodityType;                    //品種型別
            TAPISTR_10                            CommodityNo;                    //品種編號

            TAPISTR_20                            CommodityName;                    //品種名稱
            TAPISTR_30                            CommodityEngName;                //品種英文名稱

            TAPISTR_10                            RelateExchangeNo;
            TAPICommodityType                    RelateCommodityType;
            TAPISTR_10                            RelateCommodityNo;

            TAPISTR_10                            RelateExchangeNo2;
            TAPICommodityType                    RelateCommodityType2;
            TAPISTR_10                            RelateCommodityNo2;

            TAPISTR_10                            CurrencyGroupNo;
            TAPISTR_10                            TradeCurrency;                    //交易幣種
            TAPIREAL64                            ContractSize;                    //每手乘數
            TAPIOpenCloseModeType                OpenCloseMode;                    //開平方式
            TAPIREAL64                            StrikePriceTimes;                //執行價格倍數

            TAPIREAL64                            CommodityTickSize;                //最小變動價位
            TAPIINT32                            CommodityDenominator;            //報價分母
            TAPICmbDirectType                    CmbDirect;                        //組合方向
            TAPIDeliveryModeType                DeliveryMode;                    //交割行權方式
            TAPIINT32                            DeliveryDays;                    //交割日偏移
            TAPITIME                            AddOneTime;                        //T+1分割時間
            TAPIINT32                            CommodityTimeZone;                //品種時區
            TAPIYNFLAG                            IsAddOne;                        //是否處於T+1時段。


    };

    //! 交易合約資訊
    struct TapAPITradeContractInfo
    {
            TAPISTR_10              ExchangeNo;                             ///< 交易所編碼
            TAPICommodityType        CommodityType;                          ///< 品種型別
            TAPISTR_10              CommodityNo;                            ///< 品種編號
            TAPISTR_10              ContractNo1;                            ///< 合約程式碼1
            TAPISTR_10              StrikePrice1;                           ///< 執行價1
            TAPICallOrPutFlagType    CallOrPutFlag1;                         ///< 看漲看跌標示1
            TAPISTR_10              ContractNo2;                            ///< 合約程式碼2
            TAPISTR_10              StrikePrice2;                           ///< 執行價2
            TAPICallOrPutFlagType    CallOrPutFlag2;                         ///< 看漲看跌標示2
            TAPIContractTypeType    ContractType;                           ///< 合約型別
            TAPISTR_10                QuoteUnderlyingContract;                ///< 行情真實合約
            TAPISTR_70              ContractName;                           ///< 合約名稱
            TAPIDATE                ContractExpDate;                        ///< 合約到期日    
            TAPIDATE                LastTradeDate;                          ///< 最後交易日
            TAPIDATE                FirstNoticeDate;                        ///< 首次通知日
    };


    //! 交易幣種資訊
    struct TapAPICurrencyInfo
    {
            TAPISTR_10                    CurrencyNo;                        ///< 幣種編號
            TAPISTR_10                    CurrencyGroupNo;                ///< 幣種組編號
            TAPIREAL64                    TradeRate;                        ///< 交易匯率
            TAPIREAL64                    TradeRate2;                        ///< 交易匯率2

            TAPIFutureAlgType            FutureAlg;                        ///< 逐筆'1',盯市 '2'
            TAPIOptionAlgType            OptionAlg;                        ///< 期權演算法,期貨方式'1',期權方式'2'
    };
    //=============================================================================
    /**
    *    \addtogroup G_DATATYPE_T_TAPIMSGRECEIVERTYPE    訊息接收者型別
    *    @{
    */
    //=============================================================================
    //! 訊息接收者型別
    typedef TAPICHAR                TAPIMsgReceiverType;
    //! 單資金賬號客戶
    const TAPIMsgReceiverType        TAPI_MSG_RECEIVER_ACCOUNTNO = '1';
    //! 資金賬號分組
    const TAPIMsgReceiverType        TAPI_MSG_RECEIVER_ACCOUNTGROUPNO = '2';
    //! 符合屬性的資金賬號
    const TAPIMsgReceiverType        TAPI_MSG_RECEIVER_ATTRIBUTE = '3';
    //! 指定登入使用者
    const TAPIMsgReceiverType        TAPI_MSG_RECEIVER_USERNO = '4';
    /** @}*/

    //=============================================================================
    /**
    *    \addtogroup G_DATATYPE_T_TAPIMSGLEVELTYPE    訊息級別
    *    @{
    */
    //=============================================================================
    //! 訊息級別
    typedef TAPICHAR                TAPIMsgLevelType;
    //! 普通
    const TAPIMsgLevelType            TAPI_MSG_LEVEL_NORMAL = '1';
    //! 重要
    const TAPIMsgLevelType            TAPI_MSG_LEVEL_IMPORTANT = '2';
    //! 緊急
    const TAPIMsgLevelType            TAPI_MSG_LEVEL_IMERGENCY = '3';
    /** @}*/


    //=============================================================================
    /**
    *    \addtogroup G_DATATYPE_T_TAPIMSGTYPETYPE    訊息型別
    *    @{
    */
    //=============================================================================
    //! 訊息型別
    typedef TAPICHAR                TAPIMsgTypeType;
    //! 管理
    const TAPIMsgTypeType            TAPI_Msg_TYPE_MANAGER = '1';
    //! 風險
    const TAPIMsgTypeType            TAPI_Msg_TYPE_RISKCONTROL = '2';
    /** @}*/


    //=============================================================================
    /**
    *    \addtogroup G_DATATYPE_T_TAPIBILLTYPETYPE    賬單型別
    *    @{
    */
    //=============================================================================
    //! 賬單型別
    typedef TAPICHAR                        TAPIBillTypeType;
    //! 日賬單
    const TAPIBillTypeType                    TAPI_BILL_DATE = 'D';
    //! 月賬單
    const TAPIBillTypeType                    TAPI_BILL_MONTH = 'M';
    /** @}*/

    //=============================================================================
    /**
    *    \addtogroup G_DATATYPE_T_TAPIBILLFILETYPETYPE    帳單檔案型別
    *    @{
    */
    //=============================================================================
    //! 帳單檔案型別
    typedef TAPICHAR                        TAPIBillFileTypeType;
    //! txt格式檔案
    const TAPIBillFileTypeType                TAPI_BILL_FILE_TXT = 'T';
    //! pdf格式檔案
    const TAPIBillFileTypeType                TAPI_BILL_FILE_PDF = 'F';
    /** @}*/



    //! 交易或風控訊息查詢請求結構
    struct TapAPITradeMessageReq
    {
            TAPISTR_20                    AccountNo;
            TAPISTR_20                    AccountAttributeNo;
            TAPIDATETIME                BenginSendDateTime;
            TAPIDATETIME                EndSendDateTime;
    };





    //! 交易訊息傳送應答結構
    struct TapAPITradeMessage
    {
            TAPIUINT32                SerialID;                        ///< 流號

            TAPISTR_20                AccountNo;                        ///< 客戶資金賬號

            TAPIDATETIME            TMsgValidDateTime;                ///< 訊息有效時間
            TAPISTR_50                TMsgTitle;                        ///< 訊息標題
            TAPISTR_500                TMsgContent;                    ///< 訊息內容
            TAPIMsgTypeType            TMsgType;                        ///< 訊息型別
            TAPIMsgLevelType        TMsgLevel;                        ///< 訊息級別

            TAPIYNFLAG                IsSendBySMS;                    ///< 是否傳送簡訊
            TAPIYNFLAG                IsSendByEMail;                    ///< 是否傳送郵件
            TAPISTR_20                Sender;                            ///<傳送者
            TAPIDATETIME            SendDateTime;                    ///< 傳送時間
    };

    //! 客戶賬單查詢請求結構
    struct TapAPIBillQryReq
    {
            TAPISTR_20                UserNo;
            TAPIBillTypeType        BillType;
            TAPIDATE                BillDate;
            TAPIBillFileTypeType    BillFileType;
    };

    //! 客戶賬單查詢應答結構
    struct TapAPIBillQryRsp
    {
            TapAPIBillQryReq        Reqdata;
            TAPIINT32                BillLen;
            TAPICHAR                BillText[1];    ///< 變長賬單內容，長度由BillLen指定
    };

    //! 歷史委託查詢請求結構
    struct TapAPIHisOrderQryReq
    {
            TAPISTR_20            AccountNo;                            ///< 客戶資金賬號
            TAPISTR_20            AccountAttributeNo;                    ///< 客戶屬性號
            TAPIDATE            BeginDate;                            ///< 開始時間 (必填)
            TAPIDATE            EndDate;                            ///< 結束時間 (必填)
    };

    struct TapAPIHisOrderQryRsp
    {
            TAPIDATE                    Date;                                ///< 日期
            TAPISTR_20                    AccountNo;                            ///< 客戶資金賬號

            TAPISTR_10                    ExchangeNo;                            ///< 交易所編號
            TAPICommodityType            CommodityType;                        ///< 品種型別
            TAPISTR_10                    CommodityNo;                        ///< 品種編碼型別
            TAPISTR_10                    ContractNo;                            ///< 合約
            TAPISTR_10                    StrikePrice;                        ///< 執行價格
            TAPICallOrPutFlagType        CallOrPutFlag;                        ///< 看張看跌
            TAPISTR_10                    ContractNo2;                        ///< 合約2
            TAPISTR_10                    StrikePrice2;                        ///< 執行價格2
            TAPICallOrPutFlagType        CallOrPutFlag2;                        ///< 看張看跌2

            TAPIOrderTypeType            OrderType;                            ///< 委託型別
            TAPIOrderSourceType            OrderSource;                        ///< 委託來源
            TAPITimeInForceType            TimeInForce;                        ///< 委託有效型別
            TAPIDATETIME                ExpireTime;                            ///< 有效日期(GTD情況下使用)
            TAPIYNFLAG                    IsRiskOrder;                        ///< 是否風險報單
            TAPISideType                OrderSide;                            ///< 買入賣出
            TAPIPositionEffectType        PositionEffect;                        ///< 開平標誌
            TAPIPositionEffectType        PositionEffect2;                    ///< 開平標誌2
            TAPISTR_50                    InquiryNo;                            ///< 詢價號
            TAPIHedgeFlagType            HedgeFlag;                            ///< 投機保值
            TAPIREAL64                    OrderPrice;                            ///< 委託價格
            TAPIREAL64                    OrderPrice2;                        ///< 委託價格2，做市商應價使用
            TAPIREAL64                    StopPrice;                            ///< 觸發價格
            TAPIUINT32                    OrderQty;                            ///< 委託數量
            TAPIUINT32                    OrderMinQty;                        ///< 最小成交量
            TAPIUINT32                    OrderCanceledQty;                    ///< 撤單數量

            TAPIINT32                    RefInt;                                ///< 整型參考值
            TAPIREAL64                    RefDouble;                            ///<浮點參考型。
            TAPISTR_50                    RefString;                            ///< 字串參考值

            TAPICHAR                    ServerFlag;                            ///< 伺服器標識
            TAPISTR_20                    OrderNo;                                            ///< 委託編碼
            TAPIUINT32                    OrderStreamID;                        ///< 委託流水號

            TAPISTR_10                    UpperNo;                            ///< 上手號
            TAPISTR_10                    UpperChannelNo;                        ///< 上手通道編號
            TAPISTR_20                    OrderLocalNo;                        ///< 本地號
            TAPIUINT32                    UpperStreamID;                        ///< 上手流號

            TAPISTR_50                    OrderSystemNo;                        ///< 系統號
            TAPISTR_50                    OrderExchangeSystemNo;                ///< 交易所繫統號
            TAPISTR_50                    OrderParentSystemNo;                ///< 父單系統號 

            TAPISTR_20                    OrderInsertUserNo;                    ///< 下單人
            TAPIDATETIME                OrderInsertTime;                    ///< 下單時間
            TAPISTR_20                    OrderCommandUserNo;                    ///< 指令下達人
            TAPISTR_20                    OrderUpdateUserNo;                    ///< 委託更新人
            TAPIDATETIME                OrderUpdateTime;                    ///< 委託更新時間

            TAPIOrderStateType            OrderState;                            ///< 委託狀態

            TAPIREAL64                    OrderMatchPrice;                    ///< 成交價
            TAPIREAL64                    OrderMatchPrice2;                    ///< 成交價2
            TAPIUINT32                    OrderMatchQty;                        ///< 成交量
            TAPIUINT32                    OrderMatchQty2;                        ///< 成交量2

            TAPIUINT32                    ErrorCode;                            ///< 最後一次操作錯誤資訊碼
            TAPISTR_50                    ErrorText;                            ///< 錯誤資訊

            TAPIYNFLAG                    IsBackInput;                        ///< 是否為錄入委託單
            TAPIYNFLAG                    IsDeleted;                            ///< 委託成交刪除標記
            TAPIYNFLAG                    IsAddOne;                            ///< 是否為T+1單
            TAPIYNFLAG                    AddOneIsValid;                        ///< 是否T+1有效

            TAPIUINT32                    MinClipSize;                        ///< 冰山單最小隨機量
            TAPIUINT32                    MaxClipSize;                        ///< 冰山單最大隨機量
            TAPISTR_50                    LicenseNo;                            ///< 軟體授權號

            TAPITacticsTypeType            TacticsType;                        ///< 策略單型別    
            TAPITriggerConditionType    TriggerCondition;                    ///< 觸發條件
            TAPITriggerPriceTypeType    TriggerPriceType;                    ///< 觸發價格型別
    };

    //! 歷史成交查詢請求結構
    struct TapAPIHisMatchQryReq
    {
            TAPISTR_20                AccountNo;                            ///< 客戶資金賬號
            TAPISTR_20                AccountAttributeNo;                    ///< 客戶屬性號
            TAPIDATE                BeginDate;                            ///< 開始日期，必填
            TAPIDATE                EndDate;                            ///< 結束日期，必填
            TAPICHAR                CountType;                            ///< 統計型別
    };

    //! 歷史成交查詢應答結構
    //! key1=SerialID
    //! key2=ExchangeNo+MatchCmbNo+MatchNo+MatchSide
    struct TapAPIHisMatchQryRsp
    {

            TAPIDATE                SettleDate;                            ///< 結算日期
            TAPIDATE                TradeDate;                            ///<交易日期
            TAPISTR_20                AccountNo;                            ///< 客戶資金賬號

            TAPISTR_10                ExchangeNo;                            ///< 市場或者交易所程式碼
            TAPICommodityType        CommodityType;                        ///< 品種型別
            TAPISTR_10                CommodityNo;                        ///< 品種號
            TAPISTR_10                ContractNo;                            ///< 合約號
            TAPISTR_10                StrikePrice;                        ///< 執行價
            TAPICallOrPutFlagType    CallOrPutFlag;                        ///< 看漲看跌標誌

            TAPIMatchSourceType        MatchSource;                        ///< 成交來源    
            TAPISideType            MatchSide;                            ///< 買賣方向
            TAPIPositionEffectType    PositionEffect;                        ///< 開平標誌
            TAPIHedgeFlagType        HedgeFlag;                            ///< 投機保值
            TAPIREAL64                MatchPrice;                            ///< 成交價
            TAPIUINT32                MatchQty;                            ///< 成交量

            TAPISTR_20                OrderNo;                            ///< 委託號
            TAPISTR_20                MatchNo;                            ///< 成交序號
            TAPIUINT32                MatchStreamID;                        ///< 成交流水號

            TAPISTR_10                UpperNo;                            ///< 上手號
            TAPISTR_20                MatchCmbNo;                            ///< 組合號
            TAPISTR_70                ExchangeMatchNo;                    ///< 成交編號(交易所成交號)
            TAPIUINT32                MatchUpperStreamID;                    ///< 上手流水號

            TAPISTR_10                CommodityCurrencyGroup;
            TAPISTR_10                CommodityCurrency;                    //品種幣種        

            TAPIREAL64                Turnover;                            ///< 成交金額
            TAPIREAL64                PremiumIncome;                        ///< 權利金收入
            TAPIREAL64                PremiumPay;                            ///< 權利金支出

            TAPIREAL64                AccountFee;                            ///< 客戶手續費
            TAPISTR_10                AccountFeeCurrencyGroup;
            TAPISTR_10                AccountFeeCurrency;                    ///< 客戶手續費幣種
            TAPIYNFLAG                IsManualFee;                        ///< 人工客戶手續費標記
            TAPIREAL64                AccountOtherFee;                    //客戶其他費用

            TAPIREAL64                UpperFee;                            ///< 上手手續費
            TAPISTR_10                UpperFeeCurrencyGroup;
            TAPISTR_10                UpperFeeCurrency;                    ///< 上手手續費幣種
            TAPIYNFLAG                IsUpperManualFee;                    ///< 人工上手手續費標記
            TAPIREAL64                UpperOtherFee;                        //上手其他費用

            TAPIDATETIME            MatchDateTime;                        ///< 成交時間
            TAPIDATETIME            UpperMatchDateTime;                    ///< 上手成交時間

            TAPIREAL64                CloseProfit;                        ///< 平倉盈虧
            TAPIREAL64                ClosePrice;                            ///< 指定平倉價格；

            TAPIUINT32                CloseQty;                            ///< 平倉量

            TAPISTR_10                SettleGroupNo;                        ///<結算分組
            TAPISTR_20                OperatorNo;                            ///< 操作員
            TAPIDATETIME            OperateTime;                        ///< 操作時間


    };

    //! 歷史委託流程查詢請求結構
    struct TapAPIHisOrderProcessQryReq
    {
            TAPIDATE                Date;
            TAPISTR_20                OrderNo;
    };

    //! 歷史委託流程查詢應答資料結構
    typedef TapAPIHisOrderQryRsp        TapAPIHisOrderProcessQryRsp;

 
    //=============================================================================
    /**
    *    \addtogroup G_DATATYPE_SETTLEFLAG    結算型別
    *    @{
    */
    //=============================================================================
    //! 賬單型別
    typedef TAPICHAR                        TAPISettleFlagType;
    //! 自動結算
    const TAPISettleFlagType                    SettleFlag_AutoSettle = '0';
    //! 人工結算
    const TAPISettleFlagType                    SettleFlagh_Manual= '2';
    /** @}*/   
    
    //! 歷史持倉查詢請求結構
    struct TapAPIHisPositionQryReq
    {
            TAPISTR_20                AccountNo;                        ///< 客戶資金賬號
            //TAPISTR_20                AccountAttributeNo;                ///< 客戶屬性號
            TAPIDATE                Date;                            ///< 日期
            //TAPICHAR                CountType;                        ///< 統計型別
            TAPISettleFlagType                  SettleFlag;                                             ///<資料型別
    };

    //! 歷史持倉查詢資料應答結構
    //! key1=SerialID
    //! key2=結算日期+交易所+組號編號+持倉編號+買賣方向
    struct TapAPIHisPositionQryRsp
    {
            TAPIDATE                SettleDate;                            ///< 結算日期
            TAPIDATE                OpenDate;                            ///< 開倉日期

            TAPISTR_20                AccountNo;                            ///< 客戶資金賬號

            TAPISTR_10                ExchangeNo;                            ///< 市場或者交易所程式碼
            TAPICommodityType        CommodityType;                        ///< 品種型別
            TAPISTR_10                CommodityNo;                        ///< 品種編碼
            TAPISTR_10                ContractNo;                            ///< 合約號
            TAPISTR_10                StrikePrice;                        ///< 執行價
            TAPICallOrPutFlagType    CallOrPutFlag;                        ///< 看漲看跌標誌

            TAPISideType            MatchSide;                            ///< 買賣方向
            TAPIHedgeFlagType        HedgeFlag;                            ///< 投機保值
            TAPIREAL64                PositionPrice;                        ///< 持倉價格
            TAPIUINT32                PositionQty;                        ///< 持倉量

            TAPISTR_20                OrderNo;                            ///< 
            TAPISTR_70                PositionNo;                            ///< 持倉編號

            TAPISTR_10                UpperNo;                            ///< 上手號    

            TAPISTR_10                CurrencyGroup;                        ///< 品種幣種組
            TAPISTR_10                Currency;                            ///< 品種幣種

            TAPIREAL64                PreSettlePrice;                        ///< 上日結算價格
            TAPIREAL64                SettlePrice;                        ///< 結算價格
            TAPIREAL64                PositionDProfit;                    ///< 持倉盈虧(盯市)
            TAPIREAL64                LMEPositionProfit;                    ///< LME持倉盈虧
            TAPIREAL64                OptionMarketValue;                    ///< 期權市值

            TAPIREAL64                AccountInitialMargin;                ///< 客戶初始保證金
            TAPIREAL64                AccountMaintenanceMargin;            ///< 客戶維持保證金
            TAPIREAL64                UpperInitialMargin;                    ///< 上手初始保證金
            TAPIREAL64                UpperMaintenanceMargin;                ///< 上手維持保證金

            TAPISTR_10                SettleGroupNo;                        ///< 結算分組
    };

    //! 交割查詢請求結構
    struct TapAPIHisDeliveryQryReq
    {
            TAPISTR_20                AccountNo;                            ///< 客戶資金賬號
            TAPISTR_20                AccountAttributeNo;                    ///< 客戶屬性號
            TAPIDATE                BeginDate;                            ///< 開始日期（必填）
            TAPIDATE                EndDate;                            ///< 結束日期（必填）
            TAPICHAR                CountType;                            ///< 統計型別
    };

    //! 交割查詢應答資料結構
    //! key1=SerialID
    struct TapAPIHisDeliveryQryRsp
    {
            TAPIDATE                DeliveryDate;                        ///< 交割日期
            TAPIDATE                OpenDate;                            ///< 開倉日期
            TAPISTR_20                AccountNo;                            ///< 客戶資金賬號

            TAPISTR_10                ExchangeNo;                            ///< 市場號或交易所程式碼
            TAPICommodityType       CommodityType;                        ///< 品種型別
            TAPISTR_10                CommodityNo;                        ///< 品種編碼
            TAPISTR_10                ContractNo;                            ///< 合約編碼
            TAPISTR_10                StrikePrice;                        ///< 執行價
            TAPICallOrPutFlagType    CallOrPutFlag;                        ///< 看漲看跌標誌

            TAPIMatchSourceType        MatchSource;                        ///< 成交來源
            TAPISideType            OpenSide;                            ///< 開倉方向
            TAPIREAL64                OpenPrice;                            ///< 開倉價格
            TAPIREAL64                DeliveryPrice;                        ///< 交割價格
            TAPIUINT32                DeliveryQty;                        ///< 交割量
            TAPIUINT32                FrozenQty;                            ///< 凍結量

            TAPISTR_20                OpenNo;                                ///< 開倉成交號
            TAPISTR_10                UpperNo;                            ///< 上手編號

            TAPISTR_10                CommodityCurrencyGroupy;            ///< 品種幣種
            TAPISTR_10                CommodityCurrency;                    ///< 品種幣種
            TAPIREAL64                PreSettlePrice;                        ///< 上日結算價
            TAPIREAL64                DeliveryProfit;                        ///< 交割盈虧

            TAPIREAL64                AccountFrozenInitialMargin;            ///< 客戶初始凍結保證金
            TAPIREAL64                AccountFrozenMaintenanceMargin;        ///< 客戶維持凍結保證金
            TAPIREAL64                UpperFrozenInitialMargin;            ///< 上手初始凍結保證金
            TAPIREAL64                UpperFrozenMaintenanceMargin;        ///< 上手維持凍結保證金

            TAPISTR_10                AccountFeeCurrencyGroup;
            TAPISTR_10                AccountFeeCurrency;                    ///< 客戶手續費幣種
            TAPIREAL64                AccountDeliveryFee;                    ///< 客戶交割手續費 
            TAPISTR_10                UpperFeeCurrencyGroup;
            TAPISTR_10                UpperFeeCurrency;                    ///< 上手手續費幣種
            TAPIREAL64                UpperDeliveryFee;                    ///< 上手交割手續費

            TAPIDeliveryModeType    DeliveryMode;                        ///< 交割行權方式
            TAPISTR_20                OperatorNo;                            ///< 操作員
            TAPIDATETIME            OperateTime;                        ///< 操作時間
            TAPISTR_20                SettleGourpNo;                        ///< 結算分組
    };

    //! 客戶資金調整查詢請求結構
    struct TapAPIAccountCashAdjustQryReq
    {
            TAPIUINT32                SerialID;
            TAPISTR_20                AccountNo;
            TAPISTR_20                AccountAttributeNo;                ///< 客戶屬性
            TAPIDATE                BeginDate;                        ///< 必填
            TAPIDATE                EndDate;                        ///< 必填
    };

    //! 客戶資金調整查詢應答結構
    struct TapAPIAccountCashAdjustQryRsp
    {
            TAPIDATE                    Date;                            ///< 日期
            TAPISTR_20                    AccountNo;                        ///< 客戶資金賬號

            TAPICashAdjustTypeType        CashAdjustType;                    ///< 資金調整型別
            TAPISTR_10                    CurrencyGroupNo;                    //幣種組號
            TAPISTR_10                    CurrencyNo;                        ///< 幣種號
            TAPIREAL64                    CashAdjustValue;                ///< 資金調整金額
            TAPISTR_100                    CashAdjustRemark;                ///< 資金調整備註

            TAPIDATETIME                OperateTime;                    ///< 操作時間
            TAPISTR_20                    OperatorNo;                        ///< 操作員

            TAPISTR_10                    AccountBank;                    ///< 客戶銀行
            TAPISTR_20                    BankAccount;                    ///< 客戶銀行賬號
            TAPIBankAccountLWFlagType    AccountLWFlag;                    ///< 客戶本外幣標識
            TAPISTR_10                    CompanyBank;                    ///< 公司銀行
            TAPISTR_20                    InternalBankAccount;            ///< 公司銀行賬戶
            TAPIBankAccountLWFlagType    CompanyLWFlag;                    ///< 公司本外幣標識
    };
    //! 客戶賬戶手續費計算引數查詢請求結構
    struct TapAPIAccountFeeRentQryReq
    {
        TAPISTR_20                        AccountNo;
    };
    //! 客戶賬戶手續費計算引數查詢應答結構
    struct TapAPIAccountFeeRentQryRsp
    {
        TAPISTR_20                        AccountNo;
        TAPISTR_10                        ExchangeNo;
        TAPICommodityType                CommodityType;
        TAPISTR_10                        CommodityNo;
        TAPIMatchSourceType                MatchSource;
        TAPICalculateModeType            CalculateMode;
        TAPISTR_10                        CurrencyGroupNo;                
        TAPISTR_10                        CurrencyNo;                        
        TAPIREAL64                        OpenCloseFee;
        TAPIREAL64                        CloseTodayFee;
    };
    //! 客戶賬戶保證金計算引數查詢結構
    struct TapAPIAccountMarginRentQryReq
    {
        TAPISTR_20                        AccountNo;
        TAPISTR_10                        ExchangeNo;
        TAPICommodityType                CommodityType;
        TAPISTR_10                        CommodityNo;
        //TAPISTR_10                        ContractNo;//暫時先不對外開放。
    };

    //! 客戶賬戶保證金計算引數查詢應答
    struct  TapAPIAccountMarginRentQryRsp
    {
        TAPISTR_20                        AccountNo;
        TAPISTR_10                        ExchangeNo;
        TAPICommodityType                CommodityType;
        TAPISTR_10                        CommodityNo;
        TAPISTR_10                        ContractNo;
        TAPISTR_10                        StrikePrice;
        TAPICallOrPutFlagType            CallOrPutFlag;
        TAPICalculateModeType            CalculateMode;
        TAPISTR_10                        CurrencyGroupNo;
        TAPISTR_10                        CurrencyNo;
        TAPIREAL64                        InitialMargin;
        TAPIREAL64                        MaintenanceMargin;
        TAPIREAL64                        SellInitialMargin;
        TAPIREAL64                        SellMaintenanceMargin;
        TAPIREAL64                        LockMargin;
    };
    //! 港交所做市商詢價通知。
    struct TapAPIOrderQuoteMarketNotice
    {
        TAPISTR_10                        ExchangeNo;                ///< 交易所編號
        TAPICommodityType                CommodityType;            ///< 品種型別
        TAPISTR_10                        CommodityNo;            ///< 品種編號
        TAPISTR_10                        ContractNo;                ///< 合約
        TAPISTR_10                        StrikePrice;            ///< 執行價
        TAPICallOrPutFlagType            CallOrPutFlag;            ///< 看漲看跌
        TAPISideType                    OrderSide;                ///< 買賣方向
        TAPIUINT32                        OrderQty;                ///< 委託量
    };

    //! 做市商下單請求結構
    struct TapAPIOrderMarketInsertReq
    {
        TAPISTR_20                AccountNo;                    ///< 客戶資金帳號
        TAPISTR_10                ExchangeNo;                    ///< 交易所編號
        TAPICommodityType        CommodityType;                ///< 品種型別
        TAPISTR_10                CommodityNo;                ///< 品種編碼型別
        TAPISTR_10                ContractNo;                    ///< 合約
        TAPISTR_10                StrikePrice;                    ///< 執行價格
        TAPICallOrPutFlagType        CallOrPutFlag;                ///< 看張看跌
        TAPIOrderTypeType        OrderType;                    ///< 委託型別
        TAPITimeInForceType        TimeInForce;                    ///< 有效型別
        TAPIDATETIME            ExpireTime;                        ///< 有效期
        TAPIOrderSourceType        OrderSource;                    ///< 委託來源    
        TAPIPositionEffectType    BuyPositionEffect;                ///< 買開平標誌
        TAPIPositionEffectType    SellPositionEffect;                ///< 賣開平標誌

        TAPIYNFLAG                AddOneIsValid;                    ///< 是否T+1有效
        TAPIREAL64                OrderBuyPrice;                ///< 買委託價
        TAPIREAL64                OrderSellPrice;                ///< 賣委託價    
        TAPIUINT32                OrderBuyQty;                    ///< 買委託量
        TAPIUINT32                OrderSellQty;                    ///< 賣委託量
        TAPISTR_50                ClientBuyOrderNo;            ///< 本地委託編號
        TAPISTR_50                ClientSellOrderNo;                ///< 本地委託編號
        TAPIINT32                RefInt;                        ///< 整型參考值
        TAPIREAL64                RefDouble;                    ///< 浮點參考值
        TAPISTR_50                RefString;                    ///< 字串參考值
        TAPISTR_100                Remark;                        ///< 備註
    };

    //! 客戶做市商應答請求結構
    struct TapAPIOrderMarketInsertRsp
    {
        TAPISTR_20                            AccountNo;                        ///< 客戶資金帳號

        TAPISTR_10                            ExchangeNo;                        ///< 交易所編號
        TAPICommodityType                    CommodityType;                    ///< 品種型別
        TAPISTR_10                            CommodityNo;                    ///< 品種編碼型別
        TAPISTR_10                            ContractNo;                        ///< 合約
        TAPISTR_10                            StrikePrice;                    ///< 執行價格
        TAPICallOrPutFlagType                CallOrPutFlag;                    ///< 看張看跌

        TAPIOrderTypeType                    OrderType;                        ///< 委託型別
        TAPITimeInForceType                    TimeInForce;                    ///< 委託有效型別
        TAPIDATETIME                        ExpireTime;                        ///< 有效日期(GTD情況下使用)
        TAPIOrderSourceType                    OrderSource;                    ///< 委託來源

        TAPIPositionEffectType                BuyPositionEffect;                ///< 買開平標誌
        TAPIPositionEffectType                SellPositionEffect;                ///< 賣開平標誌

        TAPIREAL64                            OrderBuyPrice;                    ///< 買委託價
        TAPIREAL64                            OrderSellPrice;                    ///< 賣委託價

        TAPIUINT32                            OrderBuyQty;                    ///< 買委託量
        TAPIUINT32                            OrderSellQty;                    ///< 賣委託量

        TAPICHAR                            ServerFlag;                        ///< 交易服務標識
        TAPISTR_20                            OrderBuyNo;                        ///< 買委託號
        TAPISTR_20                            OrderSellNo;                    ///< 賣委託號

        TAPIYNFLAG                            AddOneIsValid;                    ///< 是否T+1有效

        TAPISTR_20                            OrderMarketUserNo;                ///< 下單人
        TAPIDATETIME                        OrderMarketTime;                ///< 下單時間

        TAPIINT32                            RefInt;                            ///< 整型參考值
        TAPIREAL64                            RefDouble;                        ///< 浮點參考值
        TAPISTR_50                            RefString;                        ///< 字串參考值

        TAPISTR_50                            ClientBuyOrderNo;                ///< 買本地委託編號
        TAPISTR_50                            ClientSellOrderNo;                ///< 賣本地委託編號

        TAPIUINT32                            ErrorCode;                        ///< 錯誤資訊碼
        TAPISTR_50                            ErrorText;                        ///< 錯誤資訊
            
        TAPISTR_40                            ClientLocalIP;                    ///< 終端本地IP地址（客戶端填寫）
        TAPIMACTYPE                            ClientMac;                        ///< 終端本地Mac地址（客戶端填寫）

        TAPISTR_40                            ClientIP;                        ///< 前置記錄的終端IP地址（前置填寫）

        TAPISTR_100                            Remark;                            ///< 備註
    };
    //! 港交所做市商雙邊撤單請求
    struct TapAPIOrderMarketDeleteReq
    {
        TAPICHAR                ServerFlag;
        TAPISTR_20                OrderBuyNo;                    ///< 買委託號
        TAPISTR_20                OrderSellNo;                    ///< 賣委託號
    };
    typedef TapAPIOrderMarketInsertRsp TapAPIOrderMarketDeleteRsp;


    //! 訂單刪除請求結構

    struct TapAPIOrderLocalRemoveReq
    {
        TAPICHAR                ServerFlag;
        TAPISTR_20                OrderNo;                    
    };

    //! 訂單刪除應答結構
    struct TapAPIOrderLocalRemoveRsp
    {
        TapAPIOrderLocalRemoveReq req;
        TAPISTR_40                            ClientLocalIP;                    //終端本地IP地址（客戶端填寫）
        TAPIMACTYPE                            ClientMac;                        //終端本地Mac地址（客戶端填寫）

        TAPISTR_40                            ClientIP;                        //前置記錄的終端IP地址（前置填寫）
    };

    //! 訂單錄入請求結構
    struct TapAPIOrderLocalInputReq
    {
        TAPISTR_20                    AccountNo;                        ///< 客戶資金帳號

        TAPISTR_10                    ExchangeNo;                        ///< 交易所編號
        TAPICommodityType            CommodityType;                    ///< 品種型別
        TAPISTR_10                    CommodityNo;                    ///< 品種編碼型別
        TAPISTR_10                    ContractNo;                        ///< 合約1
        TAPISTR_10                    StrikePrice;                    ///< 執行價格1
        TAPICallOrPutFlagType        CallOrPutFlag;                    ///< 看張看跌1
        TAPISTR_10                    ContractNo2;                    ///< 合約2
        TAPISTR_10                    StrikePrice2;                    ///< 執行價格2
        TAPICallOrPutFlagType        CallOrPutFlag2;                    ///< 看張看跌2

        TAPIOrderTypeType            OrderType;                        ///< 委託型別
        TAPIOrderSourceType            OrderSource;                    ///< 委託來源
        TAPITimeInForceType            TimeInForce;                    ///< 委託有效型別
        TAPIDATETIME                ExpireTime;                        ///< 有效日期(GTD情況下使用)

        TAPIYNFLAG                    IsRiskOrder;                    ///< 是否風險報單
        TAPISideType                OrderSide;                        ///< 買入賣出
        TAPIPositionEffectType        PositionEffect;                    ///< 開平標誌1
        TAPIPositionEffectType        PositionEffect2;                ///< 開平標誌2
        TAPISTR_50                    InquiryNo;                        ///< 詢價號
        TAPIHedgeFlagType            HedgeFlag;                        ///< 投機保值
        TAPIREAL64                    OrderPrice;                        ///< 委託價格1
        TAPIREAL64                    OrderPrice2;                    ///< 委託價格2，做市商應價使用
        TAPIREAL64                    StopPrice;                        ///< 觸發價格
        TAPIUINT32                    OrderQty;                        ///< 委託數量
        TAPIUINT32                    OrderMinQty;                    ///< 最小成交量
        TAPISTR_50                    OrderSystemNo;                    ///< 系統號
        TAPISTR_50                    OrderExchangeSystemNo;            ///< 交易所繫統號

        TAPISTR_10                    UpperNo;                        ///< 上手號
        TAPIREAL64                    OrderMatchPrice;                ///< 成交價1
        TAPIREAL64                    OrderMatchPrice2;                ///< 成交價2
        TAPIUINT32                    OrderMatchQty;                    ///< 成交量1
        TAPIUINT32                    OrderMatchQty2;                    ///< 成交量2

        TAPIOrderStateType            OrderState;                        ///< 委託狀態

        TAPIYNFLAG                    IsAddOne;                        ///< 是否為T+1單
    };
    typedef TapAPIOrderInfo TapAPIOrderLocalInputRsp;

    struct TapAPIOrderLocalModifyReq
    {
        TapAPIOrderLocalInputReq    req;
        TAPICHAR                    ServerFlag;                        ///< 伺服器標識
        TAPISTR_20                    OrderNo;                        ///< 委託編碼
    };

    typedef TapAPIOrderInfo TapAPIOrderLocalModifyRsp;

    struct TapAPIOrderLocalTransferReq
    {
        TAPISTR_20                    AccountNo;                        ///< 客戶資金帳號
        TAPICHAR                    ServerFlag;                        ///< 伺服器標識
        TAPISTR_20                    OrderNo;                        ///< 委託編碼
    };

    typedef TapAPIOrderInfo TapAPIOrderLocalTransferRsp;


    struct TapAPIFillLocalInputReq
    {
        TAPISTR_20                    AccountNo;                        ///< 客戶資金帳號

        TAPISTR_10                    ExchangeNo;                        ///< 交易所編號
        TAPICommodityType            CommodityType;                    ///< 品種型別
        TAPISTR_10                    CommodityNo;                    ///< 品種編碼型別
        TAPISTR_10                    ContractNo;                        ///< 合約1
        TAPISTR_10                    StrikePrice;                    ///< 執行價格
        TAPICallOrPutFlagType        CallOrPutFlag;                    ///< 看張看跌

    
        TAPISideType                MatchSide;                        ///< 買入賣出
        TAPIPositionEffectType      PositionEffect;                    ///< 開平標誌1
        TAPIHedgeFlagType            HedgeFlag;                        ///< 投機保值
        TAPIREAL64                    MatchPrice;                        ///< 成交價
        TAPIUINT32                    MatchQty;                        ///< 成交量

        TAPISTR_50                    OrderSystemNo;                    ///< 系統號


        
        TAPISTR_70                    UpperMatchNo;                    ///< 上手成交號
        TAPIDATETIME                MatchDateTime;                    ///< 成交時間
        TAPIDATETIME                UpperMatchDateTime;                ///< 上手成交時間
        TAPISTR_10                    UpperNo;                        ///< 上手號

        TAPIYNFLAG                    IsAddOne;                        ///< 是否為T+1單

        TAPISTR_10                    FeeCurrencyGroup;                ///< 客戶手續費幣種組
        TAPISTR_10                    FeeCurrency;                    ///< 客戶手續費幣種
        TAPIREAL64                    FeeValue;                        ///< 手續費
        TAPIYNFLAG                    IsManualFee;                    ///< 人工客戶手續費標記

        TAPIREAL64                    ClosePositionPrice;                    ///< 指定價格平倉
    };
    typedef  TapAPIFillLocalInputReq TapAPIFillLocalInputRsp;


    //! 客戶錄單成交刪除請求結構
    struct    TapAPIFillLocalRemoveReq
    {
        TAPICHAR                    ServerFlag;                        ///< 伺服器標識
        TAPISTR_20                    MatchNo;                        ///< 本地成交號
    };
    //! 客戶錄單成交刪除應答結構
    typedef TapAPIFillLocalRemoveReq    TapAPIFillLocalRemoveRsp;

    //! 系統交易日查詢應答
    struct TapAPITradingCalendarQryRsp
    {
        TAPIDATE CurrTradeDate;                                        ///< 當前交易日
        TAPIDATE LastSettlementDate;                                ///< 上次結算日
        TAPIDATE PromptDate;                                        ///< LME到期日
        TAPIDATE LastPromptDate;                                    ///< 上日LME到期日
    };


#pragma pack(pop)
}
#endif //TAP_TRADE_API_DATA_TYPE_H