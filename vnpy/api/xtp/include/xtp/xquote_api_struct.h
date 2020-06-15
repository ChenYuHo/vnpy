/////////////////////////////////////////////////////////////////////////
///@author 中泰證券股份有限公司
///@file xquote_api_struct.h
///@brief 定義行情類相關資料結構
/////////////////////////////////////////////////////////////////////////
#ifndef _XQUOTE_API_STRUCT_H_
#define _XQUOTE_API_STRUCT_H_

#include <stdint.h>
#include "xtp_api_data_type.h"

#pragma pack(8)

///指定的合約
typedef struct XTPSpecificTickerStruct
{
    ///交易所程式碼
    XTP_EXCHANGE_TYPE exchange_id;
    ///合約程式碼（不包含交易所資訊）例如"600000"，不帶空格，以'\0'結尾
	char	ticker[XTP_TICKER_LEN];
} XTPST;

///股票、基金、債券等額外資料
struct XTPMarketDataStockExData {
    ///委託買入總量(SH,SZ)
    int64_t total_bid_qty;
    ///委託賣出總量(SH,SZ)
    int64_t total_ask_qty;
    ///加權平均委買價格(SH,SZ)
    double ma_bid_price;
    ///加權平均委賣價格(SH,SZ)
    double ma_ask_price;
    ///債券加權平均委買價格(SH)
    double ma_bond_bid_price;
    ///債券加權平均委賣價格(SH)
    double ma_bond_ask_price;
    ///債券到期收益率(SH)
    double yield_to_maturity;
    ///基金實時參考淨值(SH,SZ)
    double iopv;
    ///ETF申購筆數(SH)
    int32_t etf_buy_count;
    ///ETF贖回筆數(SH)
    int32_t etf_sell_count;
    ///ETF申購數量(SH)
    double etf_buy_qty;
    ///ETF申購金額(SH)
    double etf_buy_money;
    ///ETF贖回數量(SH)
    double etf_sell_qty;
    ///ETF贖回金額(SH)
    double etf_sell_money;
    ///權證執行的總數量(SH)
    double total_warrant_exec_qty;
    ///權證跌停價格（元）(SH)
    double warrant_lower_price;
    ///權證漲停價格（元）(SH)
    double warrant_upper_price;
    ///買入撤單筆數(SH)
    int32_t cancel_buy_count;
    ///賣出撤單筆數(SH)
    int32_t cancel_sell_count;
    ///買入撤單數量(SH)
    double cancel_buy_qty;
    ///賣出撤單數量(SH)
    double cancel_sell_qty;
    ///買入撤單金額(SH)
    double cancel_buy_money;
    ///賣出撤單金額(SH)
    double cancel_sell_money;
    ///買入總筆數(SH)
    int64_t total_buy_count;
    ///賣出總筆數(SH)
    int64_t total_sell_count;
    ///買入委託成交最大等待時間(SH)
    int32_t duration_after_buy;
    ///賣出委託成交最大等待時間(SH)
    int32_t duration_after_sell;
    ///買方委託價位數(SH)
    int32_t num_bid_orders;
    ///賣方委託價位數(SH)
    int32_t num_ask_orders;

    ///基金T-1日淨值(SZ)
    double pre_iopv;
    ///預留
    int64_t r1;
    ///預留
    int64_t r2;
};

/// 期權額外資料
struct XTPMarketDataOptionExData {
    ///波段性中斷參考價(SH)
    double  auction_price;
    ///波段性中斷集合競價虛擬匹配量(SH)
    int64_t auction_qty;
    ///最近詢價時間(SH)
    int64_t last_enquiry_time;
};

/////////////////////////////////////////////////////////////////////////
///@brief XTP_MARKETDATA_TYPE是行情快照資料型別
/////////////////////////////////////////////////////////////////////////
enum XTP_MARKETDATA_TYPE {
    XTP_MARKETDATA_ACTUAL = 0, // 現貨(股票/基金/債券等)
    XTP_MARKETDATA_OPTION = 1, // 期權
};

///行情
typedef struct XTPMarketDataStruct
{
    // 程式碼
    ///交易所程式碼
    XTP_EXCHANGE_TYPE exchange_id;
    ///合約程式碼（不包含交易所資訊），不帶空格，以'\0'結尾
    char	ticker[XTP_TICKER_LEN];

    // 價格
	///最新價
	double	last_price;
	///昨收盤
	double	pre_close_price;
	///今開盤
	double	open_price;
	///最高價
	double	high_price;
	///最低價
	double	low_price;
    ///今收盤
    double	close_price;

    // 期權資料
    ///昨日持倉量(張)(目前未填寫)
    int64_t pre_total_long_positon;
    ///持倉量(張)
	int64_t	total_long_positon;
    ///昨日結算價
    double	pre_settl_price;
    ///今日結算價
	double	settl_price;

	// 漲跌停
	///漲停價
	double	upper_limit_price;
	///跌停價
	double	lower_limit_price;
	///預留
	double	pre_delta;
	///預留
	double	curr_delta;

    /// 時間類，格式為YYYYMMDDHHMMSSsss
    int64_t data_time;

    // 量額資料
    ///數量，為總成交量（單位股，與交易所一致）
    int64_t	qty;
    ///成交金額，為總成交金額（單位元，與交易所一致）
    double	turnover;
    ///當日均價=(turnover/qty)
    double	avg_price;

    // 買賣盤
    ///十檔申買價
    double bid[10];
    ///十檔申賣價
    double	ask[10];
    ///十檔申買量
    int64_t	bid_qty[10];
    ///十檔申賣量
    int64_t	ask_qty[10];

    // 額外資料
    ///成交筆數
    int64_t trades_count;
    ///當前交易狀態說明
    char ticker_status[8];
    ///資料
    union {
        XTPMarketDataStockExData  stk;
        XTPMarketDataOptionExData opt;
    };
    ///決定了union是哪種資料型別
    XTP_MARKETDATA_TYPE data_type;
    ///預留
    int32_t r4;
} XTPMD;


///股票行情靜態資訊
typedef struct XTPQuoteStaticInfo {
    ///交易所程式碼
    XTP_EXCHANGE_TYPE exchange_id;
    ///合約程式碼（不包含交易所資訊），不帶空格，以'\0'結尾
    char    ticker[XTP_TICKER_LEN];
    /// 合約名稱
    char    ticker_name[XTP_TICKER_NAME_LEN];
    /// 合約型別
	XTP_TICKER_TYPE ticker_type;
    ///昨收盤
    double  pre_close_price;
    ///漲停板價
    double  upper_limit_price;
    ///跌停板價
    double  lower_limit_price;
	///最小變動價位
	double  price_tick;
    /// 合約最小交易量(買)
    int32_t  buy_qty_unit;
    /// 合約最小交易量(賣)
	int32_t sell_qty_unit;
} XTPQSI;


///定單薄
typedef struct OrderBookStruct {
    ///交易所程式碼
    XTP_EXCHANGE_TYPE exchange_id;
    ///合約程式碼（不包含交易所資訊），不帶空格，以'\0'結尾
    char    ticker[XTP_TICKER_LEN];

    ///最新價
    double last_price;
    ///數量，為總成交量
    int64_t qty;
    ///成交金額，為總成交金額
    double  turnover;
    ///成交筆數
    int64_t trades_count;

    // 買賣盤
    ///十檔申買價
    double bid[10];
    ///十檔申賣價
    double  ask[10];
    ///十檔申買量
    int64_t bid_qty[10];
    ///十檔申賣量
    int64_t ask_qty[10];
    /// 時間類
    int64_t data_time;
} XTPOB;

////////////////////////////////// 逐筆資料


///逐筆委託(僅適用深交所)
struct XTPTickByTickEntrust {
    ///頻道程式碼
    int32_t channel_no;
    ///委託序號(在同一個channel_no內唯一，從1開始連續)
    int64_t seq;
    ///委託價格
    double  price;
    ///委託數量
    int64_t qty;
    ///'1':買; '2':賣; 'G':借入; 'F':出借
    char  side;
    ///訂單類別: '1': 市價; '2': 限價; 'U': 本方最優
    char ord_type;
};

///逐筆成交
struct XTPTickByTickTrade {
    ///頻道程式碼
    int32_t channel_no;
    ///委託序號(在同一個channel_no內唯一，從1開始連續)
    int64_t seq;
    ///成交價格
    double price;
    ///成交量
    int64_t qty;
    ///成交金額(僅適用上交所)
    double money;
    ///買方訂單號
    int64_t bid_no;
    ///賣方訂單號
    int64_t ask_no;
    /// SH: 內外盤標識('B':主動買; 'S':主動賣; 'N':未知)
    /// SZ: 成交標識('4':撤; 'F':成交)
    char trade_flag;
};

///逐筆資料資訊
typedef struct XTPTickByTickStruct {
    ///交易所程式碼
    XTP_EXCHANGE_TYPE exchange_id;
    ///合約程式碼（不包含交易所資訊），不帶空格，以'\0'結尾
    char ticker[XTP_TICKER_LEN];
    ///預留
    int64_t seq;
    ///委託時間 or 成交時間
    int64_t data_time;
    ///委託 or 成交
    XTP_TBT_TYPE type;

    union {
        XTPTickByTickEntrust entrust;
        XTPTickByTickTrade     trade;
    };
} XTPTBT;


///供查詢的最新資訊
typedef struct XTPTickerPriceInfo {
    ///交易所程式碼
    XTP_EXCHANGE_TYPE exchange_id;
    ///合約程式碼（不包含交易所資訊），不帶空格，以'\0'結尾
    char ticker[XTP_TICKER_LEN];
    ///最新價
    double last_price;
} XTPTPI;

#pragma pack()

#endif
