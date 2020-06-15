/////////////////////////////////////////////////////////////////////////
///@author 中泰證券股份有限公司
///@file xoms_api_struct.h
///@brief 定義交易類相關資料結構
/////////////////////////////////////////////////////////////////////////
#ifndef _XOMS_API_STRUCT_H_
#define _XOMS_API_STRUCT_H_

#include "xtp_api_data_type.h"
#include "stddef.h"
#include "xtp_api_struct_common.h"

#pragma pack(8)

//=====================客戶端介面定義=================================
///新訂單請求
struct XTPOrderInsertInfo
{
    ///XTP系統訂單ID，無需使用者填寫，在XTP系統中唯一
    uint64_t                order_xtp_id;
    ///報單引用，由客戶自定義
    uint32_t	            order_client_id;
    ///合約程式碼 客戶端請求不帶空格，以'\0'結尾
    char                    ticker[XTP_TICKER_LEN];
    ///交易市場
    XTP_MARKET_TYPE         market;
    ///價格
    double                  price;
    ///止損價（保留欄位）
    double                  stop_price;
    ///數量(股票單位為股，逆回購單位為張)
    int64_t                 quantity;
    ///報單價格
    XTP_PRICE_TYPE          price_type;
    union{
		///32位欄位，用來相容老版本api，使用者無需關心
        uint32_t            u32;
        struct {
            ///買賣方向
            XTP_SIDE_TYPE               side;
            ///開平標誌
            XTP_POSITION_EFFECT_TYPE    position_effect;
			///預留欄位1
            uint8_t                     reserved1;
			///預留欄位2
			uint8_t                     reserved2;
        };
    };
	///業務型別
	XTP_BUSINESS_TYPE       business_type;
};


///撤單失敗響應訊息
struct XTPOrderCancelInfo
{
    ///撤單XTPID
    uint64_t                 order_cancel_xtp_id;
    ///原始訂單XTPID
    uint64_t                 order_xtp_id;
};


///報單響應結構體
struct XTPOrderInfo
{
    ///XTP系統訂單ID，在XTP系統中唯一
	uint64_t                order_xtp_id;
	///報單引用，使用者自定義
	uint32_t	            order_client_id;
    ///報單操作引用，使用者自定義（暫未使用）
    uint32_t                order_cancel_client_id;
    ///撤單在XTP系統中的id，在XTP系統中唯一
    uint64_t                order_cancel_xtp_id;
	///合約程式碼
	char                    ticker[XTP_TICKER_LEN];
	///交易市場
	XTP_MARKET_TYPE         market;
	///價格
	double                  price;
	///數量，此訂單的報單數量
	int64_t                 quantity;
	///報單價格條件
	XTP_PRICE_TYPE          price_type;
    union{
		///32位欄位，用來相容老版本api，使用者無需關心
        uint32_t            u32;
        struct {
            ///買賣方向
            XTP_SIDE_TYPE               side;
            ///開平標誌
            XTP_POSITION_EFFECT_TYPE    position_effect;
			///預留欄位1
			uint8_t                     reserved1;
			///預留欄位2
			uint8_t                     reserved2;
        };
    };
	///業務型別
	XTP_BUSINESS_TYPE       business_type;
	///今成交數量，為此訂單累計成交數量
	int64_t                 qty_traded;
	///剩餘數量，當撤單成功時，表示撤單數量
	int64_t                 qty_left;
	///委託時間，格式為YYYYMMDDHHMMSSsss
	int64_t                 insert_time;
	///最後修改時間，格式為YYYYMMDDHHMMSSsss
	int64_t                 update_time;
	///撤銷時間，格式為YYYYMMDDHHMMSSsss
	int64_t                 cancel_time;
	///成交金額，為此訂單的成交總金額
	double                  trade_amount;
	///本地報單編號 OMS生成的單號，不等同於order_xtp_id，為伺服器傳到報盤的單號
	char                    order_local_id[XTP_LOCAL_ORDER_LEN];
	///報單狀態，訂單響應中沒有部分成交狀態的推送，在查詢訂單結果中，會有部分成交狀態
	XTP_ORDER_STATUS_TYPE   order_status;
	///報單提交狀態，OMS內部使用，使用者無需關心
	XTP_ORDER_SUBMIT_STATUS_TYPE   order_submit_status;
	///報單型別
	TXTPOrderTypeType       order_type;
};



///報單成交結構體
struct XTPTradeReport
{
    ///XTP系統訂單ID，此成交回報相關的訂單ID，在XTP系統中唯一
    uint64_t                 order_xtp_id;
    ///報單引用
    uint32_t                 order_client_id;
    ///合約程式碼
    char                     ticker[XTP_TICKER_LEN];
    ///交易市場
    XTP_MARKET_TYPE          market;
    ///訂單號，引入XTPID後，該欄位實際和order_xtp_id重複。介面中暫時保留。
    uint64_t                 local_order_id;
    ///成交編號，深交所唯一，上交所每筆交易唯一，當發現2筆成交回報擁有相同的exec_id，則可以認為此筆交易自成交
    char                     exec_id[XTP_EXEC_ID_LEN];
    ///價格，此次成交的價格
    double                   price;
    ///數量，此次成交的數量，不是累計數量
    int64_t                  quantity;
    ///成交時間，格式為YYYYMMDDHHMMSSsss
    int64_t                  trade_time;
    ///成交金額，此次成交的總金額 = price*quantity
    double                   trade_amount;
    ///成交序號 --回報記錄號，對於單個賬戶來說，每個交易所唯一,report_index+market欄位可以組成唯一標識表示成交回報，對於多賬戶來說，不唯一
    uint64_t                 report_index;
    ///報單編號 --交易所單號，上交所為空，深交所有此欄位
    char                     order_exch_id[XTP_ORDER_EXCH_LEN];
    ///成交型別  --成交回報中的執行型別
    TXTPTradeTypeType        trade_type;
    union{
		///32位欄位，用來相容老版本api，使用者無需關心
        uint32_t            u32;
        struct {
            ///買賣方向
            XTP_SIDE_TYPE               side;
            ///開平標誌
            XTP_POSITION_EFFECT_TYPE    position_effect;
			///預留欄位1
			uint8_t                     reserved1;
			///預留欄位2
			uint8_t                     reserved2;
        };
    };
	///業務型別
	XTP_BUSINESS_TYPE        business_type;
    ///交易所交易員程式碼 
    char                     branch_pbu[XTP_BRANCH_PBU_LEN];
};


//////////////////////////////////////////////////////////////////////////
///報單查詢
//////////////////////////////////////////////////////////////////////////
///報單查詢請求-條件查詢
struct XTPQueryOrderReq
{
    ///證券程式碼，可以為空，如果為空，則預設查詢時間段內的所有成交回報
    char      ticker[XTP_TICKER_LEN];
    ///格式為YYYYMMDDHHMMSSsss，為0則預設當前交易日0點
    int64_t   begin_time;
    ///格式為YYYYMMDDHHMMSSsss，為0則預設當前時間
    int64_t   end_time;  
};

///報單查詢響應結構體
typedef struct XTPOrderInfo XTPQueryOrderRsp;


//////////////////////////////////////////////////////////////////////////
///成交回報查詢
//////////////////////////////////////////////////////////////////////////
///查詢成交報告請求-根據執行編號查詢（保留欄位）
struct XTPQueryReportByExecIdReq
{
    ///XTP訂單系統ID
    uint64_t  order_xtp_id;  
    ///成交執行編號
    char  exec_id[XTP_EXEC_ID_LEN];
};

///查詢成交回報請求-查詢條件
struct XTPQueryTraderReq
{
    ///證券程式碼，可以為空，如果為空，則預設查詢時間段內的所有成交回報
    char      ticker[XTP_TICKER_LEN];
    ///開始時間，格式為YYYYMMDDHHMMSSsss，為0則預設當前交易日0點
    int64_t   begin_time; 
    ///結束時間，格式為YYYYMMDDHHMMSSsss，為0則預設當前時間
    int64_t   end_time;  
};

///成交回報查詢響應結構體
typedef struct XTPTradeReport  XTPQueryTradeRsp;



//////////////////////////////////////////////////////////////////////////
///賬戶資金查詢響應結構體
//////////////////////////////////////////////////////////////////////////
struct XTPQueryAssetRsp
{
    ///總資產（現貨賬戶/期權賬戶參考公式：總資產 = 可用資金 + 證券資產（目前為0）+ 預扣的資金），（信用賬戶參考公式：總資產 = 可用資金 + 融券賣出所得資金餘額 + 證券資產+ 預扣的資金）
    double total_asset;
    ///可用資金
    double buying_power;
    ///證券資產（保留欄位，目前為0）
    double security_asset;
    ///累計買入成交證券佔用資金（僅限現貨賬戶/期權賬戶，信用賬戶暫不可用）
    double fund_buy_amount;
    ///累計買入成交交易費用（僅限現貨賬戶/期權賬戶，信用賬戶暫不可用）
    double fund_buy_fee;
    ///累計賣出成交證券所得資金（僅限現貨賬戶/期權賬戶，信用賬戶暫不可用）
    double fund_sell_amount;
    ///累計賣出成交交易費用（僅限現貨賬戶/期權賬戶，信用賬戶暫不可用）
    double fund_sell_fee;
    ///XTP系統預扣的資金（包括買賣股票時預扣的交易資金+預扣手續費）
    double withholding_amount;
    ///賬戶型別
    XTP_ACCOUNT_TYPE account_type;

    ///凍結的保證金（僅限期權賬戶）
    double frozen_margin;
    ///行權凍結資金（僅限期權賬戶）
    double frozen_exec_cash;
    ///行權費用（僅限期權賬戶）
    double frozen_exec_fee;
    ///墊付資金（僅限期權賬戶）
    double pay_later;
    ///預墊付資金（僅限期權賬戶）
    double preadva_pay;
    ///昨日餘額（僅限期權賬戶）
    double orig_banlance;
    ///當前餘額（僅限期權賬戶）
    double banlance;
    ///當天出入金（僅限期權賬戶）
    double deposit_withdraw;
    ///當日交易資金軋差（僅限期權賬戶）
    double trade_netting;
    ///資金資產（僅限期權賬戶）
    double captial_asset;

    ///強鎖資金（僅限期權賬戶）
    double force_freeze_amount;
    ///可取資金（僅限期權賬戶）
    double preferred_amount;

    // 信用業務新增欄位開始（數量1）
    ///融券賣出所得資金餘額（僅限信用賬戶，只能用於買券還券）
    double repay_stock_aval_banlance;

    // 信用業務新增欄位結束（數量1）

    ///(保留欄位)
    uint64_t unknown[43 - 12 - 1];
};



//////////////////////////////////////////////////////////////////////////
///查詢股票持倉情況
//////////////////////////////////////////////////////////////////////////
struct XTPQueryStkPositionRsp
{
    ///證券程式碼
    char                ticker[XTP_TICKER_LEN];
    ///證券名稱
    char                ticker_name[XTP_TICKER_NAME_LEN];
    ///交易市場
    XTP_MARKET_TYPE     market;
    ///總持倉
    int64_t             total_qty;
    ///可賣持倉
    int64_t				sellable_qty;
    ///持倉成本
    double              avg_price;
    ///浮動盈虧（保留欄位）
    double              unrealized_pnl;
    ///昨日持倉
    int64_t             yesterday_position;
    ///今日申購贖回數量（申購和贖回數量不可能同時存在，因此可以共用一個欄位）
    int64_t				purchase_redeemable_qty;

    /// 持倉方向
	XTP_POSITION_DIRECTION_TYPE      position_direction;
	///保留欄位1
	uint32_t			reserved1;
    /// 可行權合約
    int64_t             executable_option;
    /// 可鎖定標的
    int64_t             lockable_position;
    /// 可行權標的
    int64_t             executable_underlying;
    /// 已鎖定標的
    int64_t             locked_position;
    /// 可用已鎖定標的
    int64_t             usable_locked_position;


    ///(保留欄位)
    uint64_t unknown[50 - 6];
};


/////////////////////////////////////////////////////////////////////////
///資金內轉流水通知
/////////////////////////////////////////////////////////////////////////
struct XTPFundTransferNotice
{
    ///資金內轉編號
    uint64_t	            serial_id;
    ///內轉型別
    XTP_FUND_TRANSFER_TYPE	transfer_type;
    ///金額
    double	                amount;
    ///操作結果 
    XTP_FUND_OPER_STATUS    oper_status;
    ///操作時間
    uint64_t	            transfer_time;
};



/////////////////////////////////////////////////////////////////////////
///資金內轉流水查詢請求與響應
/////////////////////////////////////////////////////////////////////////
struct XTPQueryFundTransferLogReq {
    ///資金內轉編號
    uint64_t	serial_id;

};

/////////////////////////////////////////////////////////////////////////
///資金內轉流水記錄結構體
/////////////////////////////////////////////////////////////////////////
typedef struct XTPFundTransferNotice XTPFundTransferLog;

//////////////////////////////////////////////////////////////////////////
///查詢分級基金資訊結構體
//////////////////////////////////////////////////////////////////////////
struct XTPQueryStructuredFundInfoReq
{
	XTP_EXCHANGE_TYPE   exchange_id;  ///<交易所程式碼，不可為空
	char                sf_ticker[XTP_TICKER_LEN];   ///<分級基金母基金程式碼，可以為空，如果為空，則預設查詢所有的分級基金
};

//////////////////////////////////////////////////////////////////////////
///查詢分級基金資訊響應結構體
//////////////////////////////////////////////////////////////////////////
struct XTPStructuredFundInfo
{
    XTP_EXCHANGE_TYPE   exchange_id;  ///<交易所程式碼
	char                sf_ticker[XTP_TICKER_LEN];   ///<分級基金母基金程式碼
	char                sf_ticker_name[XTP_TICKER_NAME_LEN]; ///<分級基金母基金名稱
    char                ticker[XTP_TICKER_LEN];   ///<分級基金子基金程式碼
    char                ticker_name[XTP_TICKER_NAME_LEN]; ///<分級基金子基金名稱
	XTP_SPLIT_MERGE_STATUS	split_merge_status;   ///<基金允許拆分合並狀態
    uint32_t            ratio; ///<拆分合並比例
    uint32_t            min_split_qty;///<最小拆分數量
    uint32_t            min_merge_qty; ///<最小合併數量
    double              net_price;///<基金淨值
};


//////////////////////////////////////////////////////////////////////////
///查詢股票ETF合約基本情況--請求結構體,
///請求引數為多條件引數:1,不填則返回所有市場的ETF合約資訊。
///                  2,只填寫market,返回該交易市場下結果
///                   3,填寫market及ticker引數,只返回該etf資訊。
//////////////////////////////////////////////////////////////////////////
struct XTPQueryETFBaseReq
{
    ///交易市場
    XTP_MARKET_TYPE    market;
    ///ETF買賣程式碼
    char               ticker[XTP_TICKER_LEN];
};

//////////////////////////////////////////////////////////////////////////
///查詢股票ETF合約基本情況--響應結構體
//////////////////////////////////////////////////////////////////////////
typedef struct XTPQueryETFBaseRsp
{
    XTP_MARKET_TYPE     market;                             ///<交易市場
    char                etf[XTP_TICKER_LEN];                ///<etf程式碼,買賣,申贖統一使用該程式碼
    char                subscribe_redemption_ticker[XTP_TICKER_LEN];    ///<etf申購贖回程式碼
    int32_t             unit;                               ///<最小申購贖回單位對應的ETF份數,例如上證"50ETF"就是900000
    int32_t             subscribe_status;                   ///<是否允許申購,1-允許,0-禁止
    int32_t             redemption_status;                  ///<是否允許贖回,1-允許,0-禁止
    double              max_cash_ratio;                     ///<最大現金替代比例,小於1的數值   TODO 是否採用double
    double              estimate_amount;                    ///<T日預估金額
    double              cash_component;                     ///<T-X日現金差額
    double              net_value;                          ///<基金單位淨值
    double              total_amount;                       ///<最小申贖單位淨值總金額=net_value*unit
}XTPQueryETFBaseRsp;



//////////////////////////////////////////////////////////////////////////
///查詢股票ETF合約成分股資訊--請求結構體,請求引數為:交易市場+ETF買賣程式碼
//////////////////////////////////////////////////////////////////////////
typedef struct XTPQueryETFComponentReq
{
    ///交易市場
    XTP_MARKET_TYPE     market;
    ///ETF買賣程式碼
    char                ticker[XTP_TICKER_LEN];
}XTPQueryETFComponentReq;


//////////////////////////////////////////////////////////////////////////
///查詢股票ETF合約成分股資訊--響應結構體
//////////////////////////////////////////////////////////////////////////
struct XTPQueryETFComponentRsp
{
    ///交易市場
    XTP_MARKET_TYPE     market;
    ///ETF程式碼
    char                ticker[XTP_TICKER_LEN];
    ///成份股程式碼
    char                component_ticker[XTP_TICKER_LEN];
    ///成份股名稱
    char                component_name[XTP_TICKER_NAME_LEN];
    ///成份股數量
    int64_t             quantity;
    ///成份股交易市場
    XTP_MARKET_TYPE     component_market;
    ///成份股替代標識
    ETF_REPLACE_TYPE    replace_type;
    ///溢價比例
    double              premium_ratio;
    ///成分股替代標識為必須現金替代時候的總金額
    double              amount;

};

//////////////////////////////////////////////////////////////////////////
///查詢當日可申購新股資訊
//////////////////////////////////////////////////////////////////////////
struct XTPQueryIPOTickerRsp {
    ///交易市場
    XTP_MARKET_TYPE     market;
    ///申購程式碼
    char                ticker[XTP_TICKER_LEN];
    ///申購股票名稱
    char                ticker_name[XTP_TICKER_NAME_LEN]; 
    ///申購價格
    double              price;
    ///申購單元         
    int32_t             unit;
    ///最大允許申購數量
    int32_t             qty_upper_limit;
};


//////////////////////////////////////////////////////////////////////////
///查詢使用者申購額度
//////////////////////////////////////////////////////////////////////////
struct XTPQueryIPOQuotaRsp {
    ///交易市場
    XTP_MARKET_TYPE     market;
    ///可申購額度
    int32_t             quantity;
};

//////////////////////////////////////////////////////////////////////////
///查詢期權競價交易業務參考資訊--請求結構體,請求引數為:交易市場+8位期權程式碼
//////////////////////////////////////////////////////////////////////////
struct XTPQueryOptionAuctionInfoReq {
    ///交易市場
    XTP_MARKET_TYPE     market;
    ///8位期權合約程式碼
    char                ticker[XTP_TICKER_LEN];
};

//////////////////////////////////////////////////////////////////////////
///查詢期權競價交易業務參考資訊
//////////////////////////////////////////////////////////////////////////
struct XTPQueryOptionAuctionInfoRsp {
    char                ticker[XTP_TICKER_LEN];             ///<合約編碼，報單ticker採用本欄位
    XTP_MARKET_TYPE     security_id_source;                 ///<證券程式碼源
    char                symbol[XTP_TICKER_NAME_LEN];        ///<合約簡稱
    char                contract_id[XTP_TICKER_NAME_LEN];   ///<合約交易程式碼
    char                underlying_security_id[XTP_TICKER_LEN]; ///<基礎證券程式碼
	XTP_MARKET_TYPE     underlying_security_id_source;      ///<基礎證券程式碼源

    uint32_t            list_date;                          ///<上市日期，格式為YYYYMMDD
    uint32_t            last_trade_date;                    ///<最後交易日，格式為YYYYMMDD
    XTP_TICKER_TYPE     ticker_type;                        ///<證券類別
    int32_t             day_trading;                        ///<是否支援當日迴轉交易，1-允許，0-不允許

    XTP_OPT_CALL_OR_PUT_TYPE    call_or_put;                ///<認購或認沽
    uint32_t            delivery_day;                       ///<行權交割日，格式為YYYYMMDD
    uint32_t            delivery_month;                     ///<交割月份，格式為YYYYMM

    XTP_OPT_EXERCISE_TYPE_TYPE  exercise_type;              ///<行權方式
    uint32_t            exercise_begin_date;                ///<行權起始日期，格式為YYYYMMDD
    uint32_t            exercise_end_date;                  ///<行權結束日期，格式為YYYYMMDD
    double              exercise_price;                     ///<行權價格

    int64_t             qty_unit;                           ///<數量單位，對於某一證券申報的委託，其委託數量欄位必須為該證券數量單位的整數倍
    int64_t             contract_unit;                      ///<合約單位
    int64_t             contract_position;                  ///<合約持倉量

    double              prev_close_price;                   ///<合約前收盤價
    double              prev_clearing_price;                ///<合約前結算價

    int64_t             lmt_buy_max_qty;                    ///<限價買最大量
    int64_t             lmt_buy_min_qty;                    ///<限價買最小量
    int64_t             lmt_sell_max_qty;                   ///<限價賣最大量
    int64_t             lmt_sell_min_qty;                   ///<限價賣最小量
    int64_t             mkt_buy_max_qty;                    ///<市價買最大量
    int64_t             mkt_buy_min_qty;                    ///<市價買最小量
    int64_t             mkt_sell_max_qty;                   ///<市價賣最大量
    int64_t             mkt_sell_min_qty;                   ///<市價賣最小量

    double              price_tick;                         ///<最小報價單位
    double              upper_limit_price;                  ///<漲停價
    double              lower_limit_price;                  ///<跌停價
    double              sell_margin;                        ///<今賣開每張保證金
    double              margin_ratio_param1;                ///<交易所保證金比例計算引數一
    double              margin_ratio_param2;                ///<交易所保證金比例計算引數二

    uint64_t            unknown[20];                        ///<（保留欄位）
};


//////////////////////////////////////////////////////////////////////////
///融資融券直接還款響應資訊
//////////////////////////////////////////////////////////////////////////
struct XTPCrdCashRepayRsp
{
    int64_t xtp_id;             ///< 直接還款操作的XTPID
    double  request_amount;     ///< 直接還款的申請金額
    double  cash_repay_amount;  ///< 實際還款使用金額
};

//////////////////////////////////////////////////////////////////////////
///融資融券現金還息費響應資訊
//////////////////////////////////////////////////////////////////////////
struct XTPCrdCashRepayDebtInterestFeeRsp
{
	int64_t xtp_id;             ///< 直接還款操作的XTPID
	double  request_amount;     ///< 直接還款的申請金額
	double  cash_repay_amount;  ///< 實際還款使用金額
	char	debt_compact_id[XTP_CREDIT_DEBT_ID_LEN]; ///< 指定的負債合約編號
	char	unknow[32];			///< 保留欄位
};

//////////////////////////////////////////////////////////////////////////
///單條融資融券直接還款記錄資訊
//////////////////////////////////////////////////////////////////////////
struct XTPCrdCashRepayInfo
{
    int64_t                     xtp_id;             ///< 直接還款操作的XTPID
    XTP_CRD_CR_STATUS           status;             ///< 直接還款處理狀態
    double                      request_amount;     ///< 直接還款的申請金額
    double                      cash_repay_amount;  ///< 實際還款使用金額
    XTP_POSITION_EFFECT_TYPE    position_effect;    ///< 強平標誌
	XTPRI						error_info;			///< 直接還款發生錯誤時的錯誤資訊
};

//////////////////////////////////////////////////////////////////////////
///單條融資融券負債記錄資訊
//////////////////////////////////////////////////////////////////////////
typedef struct XTPCrdDebtInfo
{
    int32_t             debt_type;              ///< 負債合約型別
    char                debt_id[33];            ///< 負債合約編號
    int64_t             position_id;            ///< 負債對應兩融頭寸編號
    uint64_t            order_xtp_id;           ///< 生成負債的訂單編號，非當日負債無此項
    int32_t             debt_status;            ///< 負債合約狀態
    XTP_MARKET_TYPE     market;                 ///< 市場
    char                ticker[XTP_TICKER_LEN]; ///< 證券程式碼
    uint64_t            order_date;             ///< 委託日期
    uint64_t            end_date;               ///< 負債截止日期
    uint64_t            orig_end_date;          ///< 負債原始截止日期
    bool                is_extended;            ///< 當日是否接收到展期請求
    double              remain_amt;             ///< 未償還金額
    int64_t             remain_qty;             ///< 未償還融券數量
    double              remain_principal;       ///< 未償還本金金額
	int64_t				due_right_qty;			///< 應償還權益數量
	int64_t				unknown[2];				///< 保留欄位
}XTPCrdDebtInfo;

//////////////////////////////////////////////////////////////////////////
///融資融券特有帳戶資料
//////////////////////////////////////////////////////////////////////////
typedef struct XTPCrdFundInfo
{
    double maintenance_ratio;       ///< 維持擔保品比例
    double all_asset;               ///< 總資產
    double all_debt;                ///< 總負債
    double line_of_credit;          ///< 兩融授信額度
    double guaranty;                ///< 兩融保證金可用數
    double position_amount;         ///< 融資頭寸可用金額，內部介面，正式版本需要刪除
}XTPCrdFundInfo;

//////////////////////////////////////////////////////////////////////////
///融資融券指定證券上的負債未還數量請求結構體
//////////////////////////////////////////////////////////////////////////
typedef struct XTPClientQueryCrdDebtStockReq
{
    XTP_MARKET_TYPE market;                 ///< 市場
    char            ticker[XTP_TICKER_LEN]; ///< 證券程式碼
}XTPClientQueryCrdDebtStockReq;

//////////////////////////////////////////////////////////////////////////
///融資融券指定證券上的負債未還資訊
//////////////////////////////////////////////////////////////////////////
typedef struct XTPCrdDebtStockInfo
{
    XTP_MARKET_TYPE market;                     ///< 市場
    char            ticker[XTP_TICKER_LEN];     ///< 證券程式碼
    int64_t         remain_quantity;            ///< 負債未還數量
    int64_t         order_withhold_quantity;    ///< 掛單未成還券數量
}XTPCrdDebtStockInfo;

//////////////////////////////////////////////////////////////////////////
///融券頭寸證券查詢請求結構體
//////////////////////////////////////////////////////////////////////////
typedef struct XTPClientQueryCrdPositionStockReq
{
    XTP_MARKET_TYPE market;                 ///< 證券市場
    char            ticker[XTP_TICKER_LEN]; ///< 證券程式碼
}XTPClientQueryCrdPositionStockReq;

//////////////////////////////////////////////////////////////////////////
///融券頭寸證券資訊
//////////////////////////////////////////////////////////////////////////
typedef struct XTPClientQueryCrdPositionStkInfo 
{
    XTP_MARKET_TYPE market;                 ///< 證券市場
    char            ticker[XTP_TICKER_LEN]; ///< 證券程式碼
    int64_t         limit_qty;              ///< 融券限量
    int64_t         yesterday_qty;          ///< 昨日日融券數量
    int64_t         left_qty;               ///< 剩餘可融券數量
    int64_t         frozen_qty;             ///< 凍結融券數量
}XTPClientQueryCrdPositionStkInfo;


//////////////////////////////////////////////////////////////////////////
/// 信用業務餘券查詢請求結構體
//////////////////////////////////////////////////////////////////////////
typedef struct XTPClientQueryCrdSurplusStkReqInfo
{
    XTP_MARKET_TYPE market;                 ///< 證券市場
    char            ticker[XTP_TICKER_LEN]; ///< 證券程式碼
}XTPClientQueryCrdSurplusStkReqInfo;

//////////////////////////////////////////////////////////////////////////
///信用業務餘券資訊
//////////////////////////////////////////////////////////////////////////
typedef struct XTPClientQueryCrdSurplusStkRspInfo
{
    XTP_MARKET_TYPE market;                 ///< 證券市場
    char            ticker[XTP_TICKER_LEN]; ///< 證券程式碼
    int64_t         transferable_quantity;  ///< 可劃轉數量
    int64_t         transferred_quantity;   ///< 已劃轉數量
}XTPClientQueryCrdSurplusStkRspInfo;


//////////////////////////////////////////////////////////////////////////
/// 信用業務負債展期資訊
//////////////////////////////////////////////////////////////////////////

typedef struct XTPClientCrdExtendDebtInfo
{
    uint64_t    xtp_id;                             ///< 訂單編號
    char        debt_id[XTP_CREDIT_DEBT_ID_LEN];    ///< 待展期負債合約編號
}XTPClientCrdExtendDebtInfo;

#pragma pack()
#endif //_XOMS_API_STRUCT_H_

