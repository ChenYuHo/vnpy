#ifndef TAP_API_COMM_DEF_H
#define TAP_API_COMM_DEF_H

#pragma pack(push, 1)

//=============================================================================
/**
 *	\addtogroup G_DATATYPE_CHARS	基本字串型別定義
 *	@{
 */
//=============================================================================

//! 長度為10的字串
typedef char	TAPISTR_10[11];
//! 長度為20的字串
typedef char	TAPISTR_20[21];
//! 長度為30的字串
typedef char	TAPISTR_30[31];
//! 長度為40的字串
typedef char	TAPISTR_40[41];
//! 長度為50的字串
typedef char	TAPISTR_50[51];
//! 長度為70的字串
typedef char	TAPISTR_70[71];
//! 長度為100的字串
typedef char	TAPISTR_100[101];
//! 長度為300的字串
typedef char	TAPISTR_300[301];
//! 長度為500的字串
typedef char	TAPISTR_500[501];
//! 長度為2000的字串
typedef char	TAPISTR_2000[2001];

//! Authorization Code
typedef char	TAPIAUTHCODE[513];


//! 單字元定義，可用於定義其他型別
typedef char				TAPICHAR;
/** @}*/


//=============================================================================
/**
 *	\addtogroup G_DATATYPE_NUMBER	基本數值型別定義
 *	@{
 */
//=============================================================================

//! int 32
typedef int					TAPIINT32;
//! unsigned 32
typedef unsigned int		TAPIUINT32;
//! int 64
typedef long long			TAPIINT64;
//! unsigned 64
typedef unsigned long long	TAPIUINT64;
//! unsigned 16
typedef unsigned short		TAPIUINT16;
//! unsigned 8
typedef unsigned char		TAPIUINT8;
//! real 64
typedef double				TAPIREAL64;

/** @}*/

//=============================================================================
/**
 *	\addtogroup G_DATATYPE_YNFLAG	是否標示
 *	@{
 */
//=============================================================================
//! 是否標示
typedef TAPICHAR			TAPIYNFLAG;
//! 是
const TAPIYNFLAG			APIYNFLAG_YES	='Y';
//! 否
const TAPIYNFLAG			APIYNFLAG_NO	='N';

/** @}*/



//=============================================================================
/**
 *	\addtogroup G_DATATYPE_DATETIME	日期時間型別定義
 *	@{
 */
//=============================================================================

//! 時間戳型別(格式 yyyy-MM-dd hh:nn:ss.xxx)
typedef char	TAPIDTSTAMP[24];
//! 日期和時間型別(格式 yyyy-MM-dd hh:nn:ss)
typedef char	TAPIDATETIME[20];
//! 日期型別(格式 yyyy-MM-dd)
typedef char	TAPIDATE[11];
//! 時間型別(格式 hh:nn:ss)
typedef char	TAPITIME[9];
/** @}*/

//=============================================================================
/**
 *	\addtogroup G_DATATYPE_LOG_LEVEL	日誌級別
 *	@{
 */
//=============================================================================
//! 日誌級別
typedef TAPICHAR			TAPILOGLEVEL;
//! 無
const TAPILOGLEVEL			APILOGLEVEL_NONE	='N';
//! Error
const TAPILOGLEVEL			APILOGLEVEL_ERROR	='E';
//! Warning
const TAPILOGLEVEL			APILOGLEVEL_WARNING	='W';
//! Debug
const TAPILOGLEVEL			APILOGLEVEL_DEBUG	='D';
/** @}*/


//=============================================================================
/**
 *	\addtogroup G_DATATYPE_COMMODITY_TYPE	品種型別
 *	@{
 */
//=============================================================================

//! 品種型別
typedef TAPICHAR               TAPICommodityType;
//! 無
const TAPICommodityType		TAPI_COMMODITY_TYPE_NONE				= 'N';
//! 現貨
const TAPICommodityType		TAPI_COMMODITY_TYPE_SPOT				= 'P';
//! 期貨
const TAPICommodityType		TAPI_COMMODITY_TYPE_FUTURES				= 'F';
//! 期權
const TAPICommodityType		TAPI_COMMODITY_TYPE_OPTION				= 'O';
//! 跨期套利
const TAPICommodityType		TAPI_COMMODITY_TYPE_SPREAD_MONTH		= 'S';
//! 跨品種套利
const TAPICommodityType		TAPI_COMMODITY_TYPE_SPREAD_COMMODITY	= 'M';
//! 看漲垂直套利
const TAPICommodityType		TAPI_COMMODITY_TYPE_BUL					= 'U';
//! 看跌垂直套利
const TAPICommodityType		TAPI_COMMODITY_TYPE_BER					= 'E';
//! 跨式套利
const TAPICommodityType		TAPI_COMMODITY_TYPE_STD					= 'D';
//! 寬跨式套利
const TAPICommodityType		TAPI_COMMODITY_TYPE_STG					= 'G';
//! 備兌組合
const TAPICommodityType		TAPI_COMMODITY_TYPE_PRT					= 'R';
//! 看漲水平期權
const TAPICommodityType		TAPI_COMMODITY_TYPE_BLT		    		= 'L';
//! 看跌水平期權
const TAPICommodityType		TAPI_COMMODITY_TYPE_BRT		    		= 'Q';
//! 外匯——直接匯率
const TAPICommodityType		TAPI_COMMODITY_TYPE_DIRECTFOREX			= 'X';
//! 外匯——間接匯率
const TAPICommodityType		TAPI_COMMODITY_TYPE_INDIRECTFOREX		= 'I';
//! 外匯——交叉匯率
const TAPICommodityType		TAPI_COMMODITY_TYPE_CROSSFOREX			= 'C';
//! 指數
const TAPICommodityType		TAPI_COMMODITY_TYPE_INDEX				= 'Z';
//! 股票
const TAPICommodityType		TAPI_COMMODITY_TYPE_STOCK				= 'T';
//! 現貨延期
const TAPICommodityType		TAPI_COMMODITY_TYPE_SPOT_TRADINGDEFER   = 'Y';
//! 中金所對鎖組合
const TAPICommodityType		TAPI_COMMODITY_TYPE_FUTURE_LOCK	    	= 'J';
//! 中金所EFP
const TAPICommodityType		TAPI_COMMODITY_TYPE_EFP			    	= 'A';

/** @}*/


//=============================================================================
/**
 *	\addtogroup G_DATATYPE_CALL_OR_PUT	看漲看跌標示
 *	@{
 */
//=============================================================================

//! 看漲看跌標示
typedef TAPICHAR			TAPICallOrPutFlagType;
//! 買權
const TAPICallOrPutFlagType		TAPI_CALLPUT_FLAG_CALL				= 'C';
//! 賣權
const TAPICallOrPutFlagType		TAPI_CALLPUT_FLAG_PUT				= 'P';
//! 無
const TAPICallOrPutFlagType		TAPI_CALLPUT_FLAG_NONE				= 'N';

/** @}*/


//! Application資訊
struct TapAPIApplicationInfo
{
	TAPIAUTHCODE            AuthCode;								///< 授權碼
	TAPISTR_300				KeyOperationLogPath;					///< 關鍵操作日誌路徑
};


//! 品種編碼結構
struct TapAPICommodity
{
	TAPISTR_10              ExchangeNo;                             ///< 交易所編碼
	TAPICommodityType		CommodityType;                          ///< 品種型別
	TAPISTR_10				CommodityNo;                            ///< 品種編號
};

//! 合約編碼結構
struct TapAPIContract
{
	TapAPICommodity			Commodity;								///< 品種
	TAPISTR_10				ContractNo1;                            ///< 合約程式碼1
	TAPISTR_10				StrikePrice1;                           ///< 執行價1
	TAPICallOrPutFlagType	CallOrPutFlag1;                         ///< 看漲看跌標示1
	TAPISTR_10				ContractNo2;                            ///< 合約程式碼2
	TAPISTR_10				StrikePrice2;                           ///< 執行價2
	TAPICallOrPutFlagType	CallOrPutFlag2;                         ///< 看漲看跌標示2
};

//! 交易所資訊
struct TapAPIExchangeInfo
{
	TAPISTR_10				ExchangeNo;								///< 交易所編碼
	TAPISTR_20				ExchangeName;							///< 交易所名稱
};

//! 修改密碼請求
struct TapAPIChangePasswordReq
{
	TAPISTR_20				OldPassword;							///< 舊密碼
	TAPISTR_20				NewPassword;							///< 新密碼
};

#pragma pack(pop)

#endif