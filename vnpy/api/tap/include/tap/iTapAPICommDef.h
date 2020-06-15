#ifndef ITAP_API_COMM_DEF_H
#define ITAP_API_COMM_DEF_H

#pragma pack(push, 1)

//=============================================================================
/**
 *    \addtogroup G_DATATYPE_CHARS    基本字串型別定義
 *    @{
 */
//=============================================================================
namespace ITapTrade
{
    //! 長度為10的字串
    typedef char    TAPISTR_10[11];
    //! 長度為20的字串
    typedef char    TAPISTR_20[21];
    //! 長度為30的字串
    typedef char    TAPISTR_30[31];
    //! 長度為40的字串
    typedef char    TAPISTR_40[41];
    //! 長度為50的字串
    typedef char    TAPISTR_50[51];
    //! 長度為70的字串
    typedef char    TAPISTR_70[71];
    //! 長度為100的字串
    typedef char    TAPISTR_100[101];
    //! 長度為300的字串
    typedef char    TAPISTR_300[301];
    //! 長度為500的字串
    typedef char    TAPISTR_500[501];
    //! 長度為2000的字串
    typedef char    TAPISTR_2000[2001];

    //! Authorization Code
    typedef char    TAPIAUTHCODE[513];

    //! MAC地址型別.
    typedef char    TAPIMACTYPE[13];
    //! 二次認證序號
    typedef char    TAPISecondSerialIDType[5];


    //! 單字元定義，可用於定義其他型別
    typedef char                TAPICHAR;

    //子賬戶型別
    typedef char    TAPIClientIDType[16];
    /** @}*/


    //=============================================================================
    /**
     *    \addtogroup G_DATATYPE_NUMBER    基本數值型別定義
     *    @{
     */
    //=============================================================================

    //! int 32
    typedef int                    TAPIINT32;
    //! unsigned 32
    typedef unsigned int        TAPIUINT32;
    //! int 64
    typedef long long            TAPIINT64;
    //! unsigned 64
    typedef unsigned long long    TAPIUINT64;
    //! unsigned 16
    typedef unsigned short        TAPIUINT16;
    //! unsigned 8
    typedef unsigned char        TAPIUINT8;
    //! real 64
    typedef double                TAPIREAL64;

    /** @}*/

    //=============================================================================
    /**
     *    \addtogroup G_DATATYPE_YNFLAG    是否標示
     *    @{
     */
    //=============================================================================
    //! 是否標示
    typedef TAPICHAR            TAPIYNFLAG;
    //! 是
    const TAPIYNFLAG            APIYNFLAG_YES    ='Y';
    //! 否
    const TAPIYNFLAG            APIYNFLAG_NO    ='N';

    /** @}*/

    //=============================================================================
    /**
    *    \addtogroup G_DATATYPE_PASSWORDTYEP    密碼型別標識
    *    @{
    */
    //=============================================================================
    //! 密碼型別
    typedef TAPICHAR            TAPIPasswordType;
    //! 交易密碼
    const TAPIPasswordType            APIPASSWORD_TRADE = 'T';
    //! 電話密碼
    const TAPIPasswordType            APIPASSWORD_PHONE = 'P';

    /** @}*/

    //=============================================================================
    /**
     *    \addtogroup G_DATATYPE_DATETIME    日期時間型別定義
     *    @{
     */
    //=============================================================================

    //! 時間戳型別(格式 yyyy-MM-dd hh:nn:ss.xxx)
    typedef char    TAPIDTSTAMP[24];
    //! 日期和時間型別(格式 yyyy-MM-dd hh:nn:ss)
    typedef char    TAPIDATETIME[20];
    //! 日期型別(格式 yyyy-MM-dd)
    typedef char    TAPIDATE[11];
    //! 時間型別(格式 hh:nn:ss)
    typedef char    TAPITIME[9];
    /** @}*/

    //=============================================================================
    /**
     *    \addtogroup G_DATATYPE_LOG_LEVEL    日誌級別
     *    @{
     */
    //=============================================================================
    //! 日誌級別
    typedef TAPICHAR            TAPILOGLEVEL;
    //! 無
    const TAPILOGLEVEL            APILOGLEVEL_NONE    ='N';
    //! Error
    const TAPILOGLEVEL            APILOGLEVEL_ERROR    ='E';
    //! Warning
    const TAPILOGLEVEL            APILOGLEVEL_WARNING    ='W';
    //! Debug
    const TAPILOGLEVEL            APILOGLEVEL_DEBUG    ='D';
    /** @}*/

    //=============================================================================
    /**
    *    \addtogroup G_DATATYPE_OPTION_TYPE    期權型別
    *    @{
    */
    //=============================================================================

    typedef TAPICHAR                    TAPIOptionType;
    //!美式期權 + 權利金方式
    const TAPIOptionType                TAPI_OPTION_TYPE_AMERICAN = 'A';
    //!美式期權 + 期貨方式
    const TAPIOptionType                TAPI_OPTION_TYPE_AMERICAN2 = 'B';
    //!歐式期權 + 權利金方式
    const TAPIOptionType                TAPI_OPTION_TYPE_EUROPEAN = 'E';
    //!歐式期權 + 期貨方式
    const TAPIOptionType                TAPI_OPTION_TYPE_EUROPEAN2 = 'F';
    /** @}*/

    //=============================================================================
    /**
     *    \addtogroup G_DATATYPE_COMMODITY_TYPE    品種型別
     *    @{
     */
    //=============================================================================

    //! 品種型別
    typedef TAPICHAR               TAPICommodityType;
    //! 無
    const TAPICommodityType        TAPI_COMMODITY_TYPE_NONE                = 'N';
    //! 現貨
    const TAPICommodityType        TAPI_COMMODITY_TYPE_SPOT                = 'P';
    //! 期貨
    const TAPICommodityType        TAPI_COMMODITY_TYPE_FUTURES                = 'F';
    //! 期權
    const TAPICommodityType        TAPI_COMMODITY_TYPE_OPTION                = 'O';
    //! 跨期套利
    const TAPICommodityType        TAPI_COMMODITY_TYPE_SPREAD_MONTH        = 'S';
    //! 跨品種套利
    const TAPICommodityType        TAPI_COMMODITY_TYPE_SPREAD_COMMODITY    = 'M';
    //! 看漲垂直套利
    const TAPICommodityType        TAPI_COMMODITY_TYPE_BUL                    = 'U';
    //! 看跌垂直套利
    const TAPICommodityType        TAPI_COMMODITY_TYPE_BER                    = 'E';
    //! 跨式套利
    const TAPICommodityType        TAPI_COMMODITY_TYPE_STD                    = 'D';
    //! 寬跨式套利
    const TAPICommodityType        TAPI_COMMODITY_TYPE_STG                    = 'G';
    //! 備兌組合
    const TAPICommodityType        TAPI_COMMODITY_TYPE_PRT                    = 'R';
    //! 外匯——直接匯率
    const TAPICommodityType        TAPI_COMMODITY_TYPE_DIRECTFOREX            = 'X';
    //! 外匯——間接匯率
    const TAPICommodityType        TAPI_COMMODITY_TYPE_INDIRECTFOREX        = 'I';
    //! 外匯——交叉匯率
    const TAPICommodityType        TAPI_COMMODITY_TYPE_CROSSFOREX            = 'C';
    //! 指數
    const TAPICommodityType        TAPI_COMMODITY_TYPE_INDEX                = 'Z';
    //! 股票
    const TAPICommodityType        TAPI_COMMODITY_TYPE_STOCK                = 'T';

    /** @}*/


    //=============================================================================
    /**
     *    \addtogroup G_DATATYPE_CALL_OR_PUT    看漲看跌標示
     *    @{
     */
    //=============================================================================

    //! 看漲看跌標示
    typedef TAPICHAR            TAPICallOrPutFlagType;
    //! 買權
    const TAPICallOrPutFlagType        TAPI_CALLPUT_FLAG_CALL                = 'C';
    //! 賣權
    const TAPICallOrPutFlagType        TAPI_CALLPUT_FLAG_PUT                = 'P';
    //! 無
    const TAPICallOrPutFlagType        TAPI_CALLPUT_FLAG_NONE                = 'N';

    /** @}*/


    //! Application資訊
    struct TapAPIApplicationInfo
    {
            TAPIAUTHCODE            AuthCode;                                ///< 授權碼
            TAPISTR_300                KeyOperationLogPath;                    ///< 關鍵操作日誌路徑
    };


    //! 品種編碼結構
    struct TapAPICommodity
    {
            TAPISTR_10              ExchangeNo;                             ///< 交易所編碼
            TAPICommodityType        CommodityType;                          ///< 品種型別
            TAPISTR_10                CommodityNo;                            ///< 品種編號
    };

    //! 合約編碼結構
    struct TapAPIContract
    {
            TapAPICommodity            Commodity;                                ///< 品種
            TAPISTR_10                ContractNo1;                            ///< 合約程式碼1
            TAPISTR_10                StrikePrice1;                           ///< 執行價1
            TAPICallOrPutFlagType    CallOrPutFlag1;                         ///< 看漲看跌標示1
            TAPISTR_10                ContractNo2;                            ///< 合約程式碼2
            TAPISTR_10                StrikePrice2;                           ///< 執行價2
            TAPICallOrPutFlagType    CallOrPutFlag2;                         ///< 看漲看跌標示2

    };

    //! 交易所資訊
    struct TapAPIExchangeInfo
    {
            TAPISTR_10                ExchangeNo;                                ///< 交易所編碼
            TAPISTR_20                ExchangeName;                            ///< 交易所名稱
    };

    //! 修改密碼請求
    struct TapAPIChangePasswordReq
    {
            TAPISTR_20                    AccountNo;
            TAPIPasswordType            PasswordType;                            ///<密碼型別
            TAPISTR_20                    OldPassword;                            ///< 舊密碼
            TAPISTR_20                    NewPassword;                            ///< 新密碼
    };
    //!    認證密碼請求
    struct TapAPIAuthPasswordReq
    {
        TAPISTR_20                        AccountNo;                                ///<客戶賬號
        TAPIPasswordType                PasswordType;                            ///<密碼型別
        TAPISTR_20                        Password;                                ///<賬戶密碼
    };


    #pragma pack(pop)
}
#endif