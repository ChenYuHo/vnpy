#ifndef TAP_QUOTE_API_DATA_TYPE_H
#define TAP_QUOTE_API_DATA_TYPE_H
//該檔案定義了TapQuoteAPI 使用的資料型別和資料結構

#include "TapAPICommDef.h"

#pragma pack(push, 1)

//=============================================================================
/**
 *	\addtogroup G_DATATYPE_Q_BASIC	行情基本型別
 *	@{
 */
//=============================================================================

//! 行情價格
typedef TAPIREAL64		TAPIQPRICE;
//! 行情量
typedef TAPIUINT64		TAPIQVOLUME;
//! 變化值
typedef TAPIINT64		TAPIQDIFF;	

/** @}*/


//=============================================================================
/**
 *	\addtogroup G_STRUCT_Q	行情結構體定義
 *	@{
 */
//=============================================================================

//! 登入認證資訊
struct TapAPIQuoteLoginAuth
{
	TAPISTR_20			UserNo;					///< 使用者名稱
	TAPIYNFLAG			ISModifyPassword;		///< 是否修改密碼，'Y'表示是，'N'表示否
	TAPISTR_20			Password;				///< 使用者密碼
	TAPISTR_20			NewPassword;			///< 新密碼，如果設定了修改密碼則需要填寫此欄位
	TAPISTR_20			QuoteTempPassword;		///< 行情臨時密碼
	TAPIYNFLAG			ISDDA;					///< 是否需呀動態認證，'Y'表示是，'N'表示否
	TAPISTR_30			DDASerialNo;			///< 動態認證碼
};

//! 登入反饋資訊
struct TapAPIQuotLoginRspInfo
{
	TAPISTR_20					UserNo;							///< 使用者名稱
	TAPIINT32					UserType;						///< 使用者型別
	TAPISTR_20					UserName;						///< 暱稱，GBK編碼格式
	TAPISTR_20					QuoteTempPassword;				///< 行情臨時密碼
	TAPISTR_50					ReservedInfo;					///< 使用者自己設定的預留資訊
	TAPISTR_40					LastLoginIP;					///< 上次登入的地址
	TAPIUINT32					LastLoginProt;					///< 上次登入使用的埠
	TAPIDATETIME				LastLoginTime;					///< 上次登入的時間
	TAPIDATETIME				LastLogoutTime;					///< 上次退出的時間
	TAPIDATE					TradeDate;						///< 當前交易日期
	TAPIDATETIME				LastSettleTime;					///< 上次結算時間
	TAPIDATETIME				StartTime;						///< 系統啟動時間
	TAPIDATETIME				InitTime;						///< 系統初始化時間
};


//! 品種資訊
struct TapAPIQuoteCommodityInfo
{
	TapAPICommodity			Commodity;							///< 品種
	TAPISTR_20				CommodityName;						///< 品種名稱,GBK編碼格式
	TAPISTR_30				CommodityEngName;					///< 品種英文名稱
	TAPIREAL64				ContractSize;						///< 每手乘數
	TAPIREAL64				CommodityTickSize;					///< 最小變動價位
	TAPIINT32				CommodityDenominator;				///< 報價分母
	TAPICHAR                CmbDirect;							///< 組合方向
	TAPIINT32				CommodityContractLen;				///< 品種合約年限
	TAPIYNFLAG				IsDST;								///< 是否夏令時,'Y'為是,'N'為否
	TapAPICommodity			RelateCommodity1;					///< 關聯品種1
	TapAPICommodity			RelateCommodity2;					///< 關聯品種2
};


//! 行情合約資訊
struct TapAPIQuoteContractInfo
{
	TapAPIContract				Contract;							///< 合約
	TAPICHAR					ContractType;                       ///< 合約型別,'1'表示交易行情合約,'2'表示行情合約
	TAPISTR_10					QuoteUnderlyingContract;			///< 行情真實合約
	TAPISTR_70					ContractName;                       ///< 合約名稱
	TAPIDATE					ContractExpDate;                    ///< 合約到期日	
	TAPIDATE					LastTradeDate;                      ///< 最後交易日
	TAPIDATE					FirstNoticeDate;                    ///< 首次通知日
};

//! 行情全文
struct TapAPIQuoteWhole
{
	TapAPIContract				Contract;						///< 合約
	TAPISTR_10					CurrencyNo;						///< 幣種編號
	TAPICHAR					TradingState;					///< 交易狀態。1,集合競價;2,集合競價撮合;3,連續交易;4,交易暫停;5,閉市
	TAPIDTSTAMP					DateTimeStamp;					///< 時間戳
	TAPIQPRICE					QPreClosingPrice;				///< 昨收盤價
	TAPIQPRICE					QPreSettlePrice;				///< 昨結算價
	TAPIQVOLUME					QPrePositionQty;				///< 昨持倉量
	TAPIQPRICE					QOpeningPrice;					///< 開盤價
	TAPIQPRICE					QLastPrice;						///< 最新價
	TAPIQPRICE					QHighPrice;						///< 最高價
	TAPIQPRICE					QLowPrice;						///< 最低價
	TAPIQPRICE					QHisHighPrice;					///< 歷史最高價
	TAPIQPRICE					QHisLowPrice;					///< 歷史最低價
	TAPIQPRICE					QLimitUpPrice;					///< 漲停價
	TAPIQPRICE					QLimitDownPrice;				///< 跌停價
	TAPIQVOLUME					QTotalQty;						///< 當日總成交量
	TAPIQPRICE					QTotalTurnover;					///< 當日成交金額
	TAPIQVOLUME					QPositionQty;					///< 持倉量
	TAPIQPRICE					QAveragePrice;					///< 均價
	TAPIQPRICE					QClosingPrice;					///< 收盤價
	TAPIQPRICE					QSettlePrice;					///< 結算價
	TAPIQVOLUME					QLastQty;						///< 最新成交量
	TAPIQPRICE					QBidPrice[20];					///< 買價1-20檔
	TAPIQVOLUME					QBidQty[20];					///< 買量1-20檔
	TAPIQPRICE					QAskPrice[20];					///< 賣價1-20檔
	TAPIQVOLUME					QAskQty[20];					///< 賣量1-20檔
	TAPIQPRICE					QImpliedBidPrice;				///< 隱含買價
	TAPIQVOLUME					QImpliedBidQty;					///< 隱含買量
	TAPIQPRICE					QImpliedAskPrice;				///< 隱含賣價
	TAPIQVOLUME					QImpliedAskQty;					///< 隱含賣量
	TAPIQPRICE					QPreDelta;						///< 昨虛實度
	TAPIQPRICE					QCurrDelta;						///< 今虛實度
	TAPIQVOLUME					QInsideQty;						///< 內盤量
	TAPIQVOLUME					QOutsideQty;					///< 外盤量
	TAPIQPRICE					QTurnoverRate;					///< 換手率
	TAPIQVOLUME					Q5DAvgQty;						///< 五日均量
	TAPIQPRICE					QPERatio;						///< 市盈率
	TAPIQPRICE					QTotalValue;					///< 總市值
	TAPIQPRICE					QNegotiableValue;				///< 流通市值
	TAPIQDIFF					QPositionTrend;					///< 持倉走勢
	TAPIQPRICE					QChangeSpeed;					///< 漲速
	TAPIQPRICE					QChangeRate;					///< 漲幅
	TAPIQPRICE					QChangeValue;					///< 漲跌值
	TAPIQPRICE					QSwing;							///< 振幅
	TAPIQVOLUME					QTotalBidQty;					///< 委買總量
	TAPIQVOLUME					QTotalAskQty;					///< 委賣總量
	TapAPIContract				UnderlyContract;				///< 虛擬合約對應的真實合約
};


/** @}*/





#pragma pack(pop)

#endif