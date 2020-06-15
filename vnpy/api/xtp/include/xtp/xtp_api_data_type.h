/////////////////////////////////////////////////////////////////////////
///@author 中泰證券股份有限公司
///@file xtp_api_data_type.h
///@brief 定義相容資料基本型別
/////////////////////////////////////////////////////////////////////////
#ifndef _XTP_API_DATA_TYPE_H_
#define _XTP_API_DATA_TYPE_H_

#pragma pack(8)

/// 存放版本號的字串長度
#define XTP_VERSION_LEN 16
/// 版本號型別
typedef char XTPVersionType[XTP_VERSION_LEN];
/// 可交易日字串長度
#define XTP_TRADING_DAY_LEN 9
/// 存放證券程式碼的字串長度
#define XTP_TICKER_LEN 16
/// 存放證券名稱的字串長度
#define XTP_TICKER_NAME_LEN 64
/// 本地報單編號的字串長度
#define XTP_LOCAL_ORDER_LEN         11
/// 交易所單號的字串長度
#define XTP_ORDER_EXCH_LEN          17
/// 成交執行編號的字串長度
#define XTP_EXEC_ID_LEN             18
/// 交易所交易員程式碼字串長度
#define XTP_BRANCH_PBU_LEN          7
/// 使用者資金賬戶的字串長度
#define XTP_ACCOUNT_NAME_LEN        16
/// 信用業務合約負債編號長度
#define XTP_CREDIT_DEBT_ID_LEN      33

/////////////////////////////////////////////////////////////////////////
///@brief XTP_LOG_LEVEL是日誌輸出級別型別
/////////////////////////////////////////////////////////////////////////
typedef enum XTP_LOG_LEVEL {
	XTP_LOG_LEVEL_FATAL, ///<嚴重錯誤級別
	XTP_LOG_LEVEL_ERROR, ///<錯誤級別
	XTP_LOG_LEVEL_WARNING, ///<警告級別
	XTP_LOG_LEVEL_INFO,   ///<info級別
	XTP_LOG_LEVEL_DEBUG,  ///<debug級別
	XTP_LOG_LEVEL_TRACE   ///<trace級別
}XTP_LOG_LEVEL;

/////////////////////////////////////////////////////////////////////////
///@brief XTP_PROTOCOL_TYPE是通訊傳輸協議方式
/////////////////////////////////////////////////////////////////////////
typedef enum XTP_PROTOCOL_TYPE
{
	XTP_PROTOCOL_TCP = 1,	///<採用TCP方式傳輸
	XTP_PROTOCOL_UDP		///<採用UDP方式傳輸(僅行情介面支援)
}XTP_PROTOCOL_TYPE;



/////////////////////////////////////////////////////////////////////////
///@brief XTP_EXCHANGE_TYPE是交易所型別
/////////////////////////////////////////////////////////////////////////
typedef enum XTP_EXCHANGE_TYPE
{
	XTP_EXCHANGE_SH = 1,	///<上證
	XTP_EXCHANGE_SZ,		///<深證
    XTP_EXCHANGE_UNKNOWN	///<不存在的交易所型別
}XTP_EXCHANGE_TYPE;

//////////////////////////////////////////////////////////////////////////
///@brief XTP_MARKET_TYPE市場型別
//////////////////////////////////////////////////////////////////////////
typedef enum XTP_MARKET_TYPE
{
    XTP_MKT_INIT = 0,///<初始化值或者未知
    XTP_MKT_SZ_A = 1,///<深圳A股
    XTP_MKT_SH_A,    ///<上海A股
    XTP_MKT_UNKNOWN   ///<未知交易市場型別
}XTP_MARKET_TYPE;


/////////////////////////////////////////////////////////////////////////
///@brief XTP_PRICE_TYPE是價格型別
/////////////////////////////////////////////////////////////////////////
typedef enum XTP_PRICE_TYPE
{
	XTP_PRICE_LIMIT = 1,           ///<限價單-滬 / 深 / 滬期權（除普通股票業務外，其餘業務均使用此種類型）
	XTP_PRICE_BEST_OR_CANCEL,      ///<即時成交剩餘轉撤銷，市價單-深 / 滬期權
	XTP_PRICE_BEST5_OR_LIMIT,      ///<最優五檔即時成交剩餘轉限價，市價單-滬
	XTP_PRICE_BEST5_OR_CANCEL,     ///<最優5檔即時成交剩餘轉撤銷，市價單-滬深
	XTP_PRICE_ALL_OR_CANCEL,       ///<全部成交或撤銷,市價單-深 / 滬期權
	XTP_PRICE_FORWARD_BEST,        ///<本方最優，市價單-深
	XTP_PRICE_REVERSE_BEST_LIMIT,  ///<對方最優剩餘轉限價，市價單-深 / 滬期權
	XTP_PRICE_LIMIT_OR_CANCEL,	   ///<期權限價申報FOK
	XTP_PRICE_TYPE_UNKNOWN,		   ///<未知或者無效價格型別
}XTP_PRICE_TYPE;



/////////////////////////////////////////////////////////////////////////
///@brief XTP_SIDE_TYPE是買賣方向型別
/////////////////////////////////////////////////////////////////////////
typedef uint8_t XTP_SIDE_TYPE;

///買（新股申購，ETF買，配股，信用交易中擔保品買）
#define XTP_SIDE_BUY            1
///賣（逆回購，ETF賣，信用交易中擔保品賣）
#define XTP_SIDE_SELL           2
///申購
#define XTP_SIDE_PURCHASE       7
///贖回
#define XTP_SIDE_REDEMPTION     8
///拆分
#define XTP_SIDE_SPLIT          9
///合併
#define XTP_SIDE_MERGE          10
///改版之後的side的備兌，暫不支援
#define XTP_SIDE_COVER          11
///改版之後的side鎖定（對應開平標識為開）/解鎖（對應開平標識為平）
#define XTP_SIDE_FREEZE         12
/// 融資買入
#define XTP_SIDE_MARGIN_TRADE	21
/// 融券賣出
#define XTP_SIDE_SHORT_SELL		22
/// 賣券還款
#define XTP_SIDE_REPAY_MARGIN	23
/// 買券還券
#define XTP_SIDE_REPAY_STOCK	24
/// 現金還款（不放在普通訂單協議，另加請求和查詢協議）
//#define XTP_SIDE_CASH_REPAY_MARGIN	25
/// 現券還券
#define XTP_SIDE_STOCK_REPAY_STOCK	26
/// 餘券劃轉
#define XTP_SIDE_SURSTK_TRANS       27
/// 擔保品轉入
#define XTP_SIDE_GRTSTK_TRANSIN     28
/// 擔保品轉出
#define XTP_SIDE_GRTSTK_TRANSOUT    29

///未知或者無效買賣方向
#define XTP_SIDE_UNKNOWN        30



/////////////////////////////////////////////////////////////////////////
///@brief XTP_POSITION_EFFECT_TYPE是開平標識型別
/////////////////////////////////////////////////////////////////////////
typedef uint8_t XTP_POSITION_EFFECT_TYPE;

/// 初始值或未知值開平標識，現貨適用
#define XTP_POSITION_EFFECT_INIT                0
/// 開
#define XTP_POSITION_EFFECT_OPEN                1
/// 平
#define XTP_POSITION_EFFECT_CLOSE               2
/// 強平
#define XTP_POSITION_EFFECT_FORCECLOSE          3
/// 平今
#define XTP_POSITION_EFFECT_CLOSETODAY          4
/// 平昨
#define XTP_POSITION_EFFECT_CLOSEYESTERDAY      5
/// 強減
#define XTP_POSITION_EFFECT_FORCEOFF            6
/// 本地強平
#define XTP_POSITION_EFFECT_LOCALFORCECLOSE     7
/// 信用業務追保強平
#define XTP_POSITION_EFFECT_CREDIT_FORCE_COVER  8
/// 信用業務清償強平
#define XTP_POSITION_EFFECT_CREDIT_FORCE_CLEAR  9
/// 信用業務合約到期強平
#define XTP_POSITION_EFFECT_CREDIT_FORCE_DEBT   10
/// 信用業務無條件強平
#define XTP_POSITION_EFFECT_CREDIT_FORCE_UNCOND 11
/// 未知的開平標識型別
#define XTP_POSITION_EFFECT_UNKNOWN             12


/////////////////////////////////////////////////////////////////////////
///@brief XTP_ORDER_ACTION_STATUS_TYPE是報單操作狀態型別
/////////////////////////////////////////////////////////////////////////
typedef enum XTP_ORDER_ACTION_STATUS_TYPE
{
	XTP_ORDER_ACTION_STATUS_SUBMITTED = 1,	///<已經提交
	XTP_ORDER_ACTION_STATUS_ACCEPTED,		///<已經接受
	XTP_ORDER_ACTION_STATUS_REJECTED		///<已經被拒絕
}XTP_ORDER_ACTION_STATUS_TYPE;

/////////////////////////////////////////////////////////////////////////
///@brief XTP_ORDER_STATUS_TYPE是報單狀態型別
/////////////////////////////////////////////////////////////////////////
typedef enum XTP_ORDER_STATUS_TYPE
{
    XTP_ORDER_STATUS_INIT = 0,///<初始化
    XTP_ORDER_STATUS_ALLTRADED = 1,           ///<全部成交
    XTP_ORDER_STATUS_PARTTRADEDQUEUEING,  ///<部分成交
    XTP_ORDER_STATUS_PARTTRADEDNOTQUEUEING, ///<部分撤單
    XTP_ORDER_STATUS_NOTRADEQUEUEING,   ///<未成交
    XTP_ORDER_STATUS_CANCELED,  ///<已撤單
    XTP_ORDER_STATUS_REJECTED,  ///<已拒絕
    XTP_ORDER_STATUS_UNKNOWN  ///<未知訂單狀態
}XTP_ORDER_STATUS_TYPE;

/////////////////////////////////////////////////////////////////////////
///@brief XTP_ORDER_SUBMIT_STATUS_TYPE是報單提交狀態型別
/////////////////////////////////////////////////////////////////////////
typedef enum XTP_ORDER_SUBMIT_STATUS_TYPE
{
    XTP_ORDER_SUBMIT_STATUS_INSERT_SUBMITTED = 1, ///<訂單已經提交
    XTP_ORDER_SUBMIT_STATUS_INSERT_ACCEPTED,///<訂單已經被接受
    XTP_ORDER_SUBMIT_STATUS_INSERT_REJECTED,///<訂單已經被拒絕
    XTP_ORDER_SUBMIT_STATUS_CANCEL_SUBMITTED,///<撤單已經提交
    XTP_ORDER_SUBMIT_STATUS_CANCEL_REJECTED,///<撤單已經被拒絕
    XTP_ORDER_SUBMIT_STATUS_CANCEL_ACCEPTED ///<撤單已經被接受
}XTP_ORDER_SUBMIT_STATUS_TYPE;


/////////////////////////////////////////////////////////////////////////
///@brief XTP_TE_RESUME_TYPE是公有流（訂單響應、成交回報）重傳方式
/////////////////////////////////////////////////////////////////////////
typedef enum XTP_TE_RESUME_TYPE
{
	XTP_TERT_RESTART = 0,	///<從本交易日開始重傳
	XTP_TERT_RESUME,		///<從從上次收到的續傳（暫未支援）
	XTP_TERT_QUICK			///<只傳送登入後公有流（訂單響應、成交回報）的內容
}XTP_TE_RESUME_TYPE;


//////////////////////////////////////////////////////////////////////////
///@brief ETF_REPLACE_TYPE現金替代標識定義
//////////////////////////////////////////////////////////////////////////
typedef enum ETF_REPLACE_TYPE
{
    ERT_CASH_FORBIDDEN = 0,             ///<禁止現金替代
    ERT_CASH_OPTIONAL,                  ///<可以現金替代
    ERT_CASH_MUST,                      ///<必須現金替代
    ERT_CASH_RECOMPUTE_INTER_SZ,        ///<深市退補現金替代
    ERT_CASH_MUST_INTER_SZ,             ///<深市必須現金替代
    ERT_CASH_RECOMPUTE_INTER_OTHER,     ///<非滬深市場成分證券退補現金替代
    ERT_CASH_MUST_INTER_OTHER,          ///<表示非滬深市場成份證券必須現金替代
    EPT_INVALID                         ///<無效值
}ETF_REPLACE_TYPE;


//////////////////////////////////////////////////////////////////////////
///@brief XTP_TICKER_TYPE證券型別
//////////////////////////////////////////////////////////////////////////
typedef enum XTP_TICKER_TYPE
{
	XTP_TICKER_TYPE_STOCK = 0,            ///<普通股票
	XTP_TICKER_TYPE_INDEX,                ///<指數
	XTP_TICKER_TYPE_FUND,                 ///<基金
	XTP_TICKER_TYPE_BOND,                 ///<債券
	XTP_TICKER_TYPE_OPTION,               ///<期權
	XTP_TICKER_TYPE_UNKNOWN               ///<未知型別
	
}XTP_TICKER_TYPE;

//////////////////////////////////////////////////////////////////////////
///@brief XTP_BUSINESS_TYPE證券業務型別
//////////////////////////////////////////////////////////////////////////
typedef enum XTP_BUSINESS_TYPE
{
	XTP_BUSINESS_TYPE_CASH = 0,            ///<普通股票業務（股票買賣，ETF買賣等）
	XTP_BUSINESS_TYPE_IPOS,                ///<新股申購業務（對應的price type需選擇限價型別）
	XTP_BUSINESS_TYPE_REPO,                ///<回購業務 ( 對應的price type填為限價，side填為賣 )
	XTP_BUSINESS_TYPE_ETF,                 ///<ETF申贖業務
	XTP_BUSINESS_TYPE_MARGIN,              ///<融資融券業務（暫未支援）
	XTP_BUSINESS_TYPE_DESIGNATION,         ///<轉託管（未支援）
	XTP_BUSINESS_TYPE_ALLOTMENT,		   ///<配股業務（對應的price type需選擇限價型別,side填為買）
	XTP_BUSINESS_TYPE_STRUCTURED_FUND_PURCHASE_REDEMPTION,	   ///<分級基金申贖業務
	XTP_BUSINESS_TYPE_STRUCTURED_FUND_SPLIT_MERGE,	   ///<分級基金拆分合並業務
	XTP_BUSINESS_TYPE_MONEY_FUND,		   ///<貨幣基金業務（暫未支援）
    XTP_BUSINESS_TYPE_OPTION,              ///<期權業務
    XTP_BUSINESS_TYPE_EXECUTE,             ///<行權
    XTP_BUSINESS_TYPE_FREEZE,              ///<鎖定解鎖，暫不支援
	XTP_BUSINESS_TYPE_UNKNOWN              ///<未知型別

}XTP_BUSINESS_TYPE;

//////////////////////////////////////////////////////////////////////////
///@brief XTP_ACCOUNT_TYPE賬戶型別
//////////////////////////////////////////////////////////////////////////
typedef enum XTP_ACCOUNT_TYPE
{
    XTP_ACCOUNT_NORMAL = 0,	///<普通賬戶
    XTP_ACCOUNT_CREDIT,		///<信用賬戶
    XTP_ACCOUNT_DERIVE,		///<衍生品賬戶
    XTP_ACCOUNT_UNKNOWN		///<未知賬戶型別
}XTP_ACCOUNT_TYPE;


/////////////////////////////////////////////////////////////////////////
///@brief XTP_FUND_TRANSFER_TYPE是資金流轉方向型別
/////////////////////////////////////////////////////////////////////////
typedef enum XTP_FUND_TRANSFER_TYPE
{
    XTP_FUND_TRANSFER_OUT = 0,		///<轉出 從XTP轉出到櫃檯
    XTP_FUND_TRANSFER_IN,	        ///<轉入 從櫃檯轉入XTP
    XTP_FUND_INTER_TRANSFER_OUT,    ///<跨節點轉出 從本XTP節點1，轉出到對端XTP節點2，XTP伺服器之間劃撥，只能跨賬戶使用者使用
    XTP_FUND_INTER_TRANSFER_IN,     ///<跨節點轉入 從對端XTP節點2，轉入到本XTP節點1，XTP伺服器之間劃撥，只能跨賬戶使用者使用
    XTP_FUND_TRANSFER_UNKNOWN		///<未知型別
}XTP_FUND_TRANSFER_TYPE;

/////////////////////////////////////////////////////////////////////////
///@brief XTP_FUND_OPER_STATUS櫃檯資金操作結果
/////////////////////////////////////////////////////////////////////////
typedef enum XTP_FUND_OPER_STATUS {
    XTP_FUND_OPER_PROCESSING = 0,	///<XTP已收到，正在處理中
    XTP_FUND_OPER_SUCCESS,			///<成功
    XTP_FUND_OPER_FAILED,			///<失敗
    XTP_FUND_OPER_SUBMITTED,		///<已提交到集中櫃檯處理
    XTP_FUND_OPER_UNKNOWN			///<未知
}XTP_FUND_OPER_STATUS;

/////////////////////////////////////////////////////////////////////////
///@brief XTP_SPLIT_MERGE_STATUS是一個基金當天拆分合並狀態型別
/////////////////////////////////////////////////////////////////////////
typedef enum XTP_SPLIT_MERGE_STATUS {
	XTP_SPLIT_MERGE_STATUS_ALLOW = 0,	///<允許拆分和合並
	XTP_SPLIT_MERGE_STATUS_ONLY_SPLIT,	///<只允許拆分，不允許合併
	XTP_SPLIT_MERGE_STATUS_ONLY_MERGE,	///<只允許合併，不允許拆分
	XTP_SPLIT_MERGE_STATUS_FORBIDDEN	///<不允許拆分合並
}XTP_SPLIT_MERGE_STATUS;

/////////////////////////////////////////////////////////////////////////
///@brief XTP_TBT_TYPE是一個逐筆回報型別
/////////////////////////////////////////////////////////////////////////
typedef enum XTP_TBT_TYPE {
	XTP_TBT_ENTRUST = 1,	///<逐筆委託
	XTP_TBT_TRADE = 2,		///<逐筆成交
}XTP_TBT_TYPE;

/////////////////////////////////////////////////////////////////////////
///@brief XTP_OPT_CALL_OR_PUT_TYPE是一個認沽或認購型別
/////////////////////////////////////////////////////////////////////////
typedef enum XTP_OPT_CALL_OR_PUT_TYPE {
	XTP_OPT_CALL = 1,	    ///<認購
	XTP_OPT_PUT = 2,		///<認沽
}XTP_OPT_CALL_OR_PUT_TYPE;

/////////////////////////////////////////////////////////////////////////
///@brief XTP_OPT_EXERCISE_TYPE_TYPE是一個行權方式型別
/////////////////////////////////////////////////////////////////////////
typedef enum XTP_OPT_EXERCISE_TYPE_TYPE {
	XTP_OPT_EXERCISE_TYPE_EUR = 1,	    ///<歐式
	XTP_OPT_EXERCISE_TYPE_AME = 2,		///<美式
}XTP_OPT_EXERCISE_TYPE_TYPE;

/////////////////////////////////////////////////////////////////////////
///@brief XTP_POSITION_DIRECTION_TYPE是一個持倉方向型別
/////////////////////////////////////////////////////////////////////////
typedef enum XTP_POSITION_DIRECTION_TYPE {
	XTP_POSITION_DIRECTION_NET = 0,	    ///<淨
	XTP_POSITION_DIRECTION_LONG,		///<多（期權則為權利方）
    XTP_POSITION_DIRECTION_SHORT,       ///<空（期權則為義務方）
    XTP_POSITION_DIRECTION_COVERED,     ///<備兌（期權則為備兌義務方）
}XTP_POSITION_DIRECTION_TYPE;

/////////////////////////////////////////////////////////////////////////
///@brief XTP_CRD_CASH_REPAY_STATUS是一個融資融券直接還款狀態型別
/////////////////////////////////////////////////////////////////////////
typedef enum XTP_CRD_CR_STATUS {
    XTP_CRD_CR_INIT = 0,        ///< 初始、未處理狀態
    XTP_CRD_CR_SUCCESS,         ///< 已成功處理狀態
    XTP_CRD_CR_FAILED,          ///< 處理失敗狀態
} XTP_CRD_CR_STATUS;


/////////////////////////////////////////////////////////////////////////
///TXTPTradeTypeType是成交型別型別
/////////////////////////////////////////////////////////////////////////
typedef char TXTPTradeTypeType;

///普通成交
#define XTP_TRDT_COMMON '0'
///現金替代
#define XTP_TRDT_CASH '1'
///一級市場成交
#define XTP_TRDT_PRIMARY '2'
///跨市場資金成交
#define XTP_TRDT_CROSS_MKT_CASH '3'


/////////////////////////////////////////////////////////////////////////
///TXTPOrderTypeType是報單型別型別
/////////////////////////////////////////////////////////////////////////
typedef char TXTPOrderTypeType;

///正常
#define XTP_ORDT_Normal '0'
///報價衍生
#define XTP_ORDT_DeriveFromQuote '1'
///組合衍生
#define XTP_ORDT_DeriveFromCombination '2'
///組合報單
#define XTP_ORDT_Combination '3'
///條件單
#define XTP_ORDT_ConditionalOrder '4'
///互換單
#define XTP_ORDT_Swap '5'


#pragma pack()

#endif
