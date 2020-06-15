/////////////////////////////////////////////////////////////////////////
///@author 中泰證券股份有限公司
///@file xtp_quote_api.h
///@brief 定義行情訂閱客戶端介面
/////////////////////////////////////////////////////////////////////////

#ifndef _XTP_QUOTE_API_H_
#define _XTP_QUOTE_API_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "xtp_api_struct.h"

#if defined(ISLIB) && defined(WIN32)
#ifdef LIB_MD_API_EXPORT
#define MD_API_EXPORT __declspec(dllexport)
#else
#define MD_API_EXPORT __declspec(dllimport)
#endif
#else
#define MD_API_EXPORT 
#endif

/*!
* \class XTP::API::QuoteSpi
*
* \brief 行情回撥類
*
* \author 中泰證券股份有限公司
* \date 十月 2015
*/
namespace XTP {
	namespace API {
		class QuoteSpi
		{
		public:

			///當客戶端與行情後臺通訊連線斷開時，該方法被呼叫。
			///@param reason 錯誤原因，請與錯誤程式碼表對應
			///@remark api不會自動重連，當斷線發生時，請使用者自行選擇後續操作。可以在此函式中呼叫Login重新登入。注意使用者重新登入後，需要重新訂閱行情
			virtual void OnDisconnected(int reason) {};


			///錯誤應答
			///@param error_info 當伺服器響應發生錯誤時的具體的錯誤程式碼和錯誤資訊，當error_info為空，或者error_info.error_id為0時，表明沒有錯誤
			///@remark 此函式只有在伺服器發生錯誤時才會呼叫，一般無需使用者處理
			virtual void OnError(XTPRI *error_info) {};

			///訂閱行情應答，包括股票、指數和期權
			///@param ticker 詳細的合約訂閱情況
			///@param error_info 訂閱合約發生錯誤時的錯誤資訊，當error_info為空，或者error_info.error_id為0時，表明沒有錯誤
			///@param is_last 是否此次訂閱的最後一個應答，當為最後一個的時候為true，如果為false，表示還有其他後續訊息響應
			///@remark 每條訂閱的合約均對應一條訂閱應答，需要快速返回，否則會堵塞後續訊息，當堵塞嚴重時，會觸發斷線
			virtual void OnSubMarketData(XTPST *ticker, XTPRI *error_info, bool is_last) {};

			///退訂行情應答，包括股票、指數和期權
			///@param ticker 詳細的合約取消訂閱情況
			///@param error_info 取消訂閱合約時發生錯誤時返回的錯誤資訊，當error_info為空，或者error_info.error_id為0時，表明沒有錯誤
			///@param is_last 是否此次取消訂閱的最後一個應答，當為最後一個的時候為true，如果為false，表示還有其他後續訊息響應
			///@remark 每條取消訂閱的合約均對應一條取消訂閱應答，需要快速返回，否則會堵塞後續訊息，當堵塞嚴重時，會觸發斷線
			virtual void OnUnSubMarketData(XTPST *ticker, XTPRI *error_info, bool is_last) {};

			///深度行情通知，包含買一賣一佇列
			///@param market_data 行情資料
			///@param bid1_qty 買一佇列資料
			///@param bid1_count 買一佇列的有效委託筆數
			///@param max_bid1_count 買一佇列總委託筆數
			///@param ask1_qty 賣一佇列資料
			///@param ask1_count 賣一佇列的有效委託筆數
			///@param max_ask1_count 賣一佇列總委託筆數
			///@remark 需要快速返回，否則會堵塞後續訊息，當堵塞嚴重時，會觸發斷線
			virtual void OnDepthMarketData(XTPMD *market_data, int64_t bid1_qty[], int32_t bid1_count, int32_t max_bid1_count, int64_t ask1_qty[], int32_t ask1_count, int32_t max_ask1_count) {};

			///訂閱行情訂單簿應答，包括股票、指數和期權
			///@param ticker 詳細的合約訂閱情況
			///@param error_info 訂閱合約發生錯誤時的錯誤資訊，當error_info為空，或者error_info.error_id為0時，表明沒有錯誤
			///@param is_last 是否此次訂閱的最後一個應答，當為最後一個的時候為true，如果為false，表示還有其他後續訊息響應
			///@remark 每條訂閱的合約均對應一條訂閱應答，需要快速返回，否則會堵塞後續訊息，當堵塞嚴重時，會觸發斷線
			virtual void OnSubOrderBook(XTPST *ticker, XTPRI *error_info, bool is_last) {};

			///退訂行情訂單簿應答，包括股票、指數和期權
			///@param ticker 詳細的合約取消訂閱情況
			///@param error_info 取消訂閱合約時發生錯誤時返回的錯誤資訊，當error_info為空，或者error_info.error_id為0時，表明沒有錯誤
			///@param is_last 是否此次取消訂閱的最後一個應答，當為最後一個的時候為true，如果為false，表示還有其他後續訊息響應
			///@remark 每條取消訂閱的合約均對應一條取消訂閱應答，需要快速返回，否則會堵塞後續訊息，當堵塞嚴重時，會觸發斷線
			virtual void OnUnSubOrderBook(XTPST *ticker, XTPRI *error_info, bool is_last) {};

			///行情訂單簿通知，包括股票、指數和期權
			///@param order_book 行情訂單簿資料，需要快速返回，否則會堵塞後續訊息，當堵塞嚴重時，會觸發斷線
			virtual void OnOrderBook(XTPOB *order_book) {};

			///訂閱逐筆行情應答，包括股票、指數和期權
			///@param ticker 詳細的合約訂閱情況
			///@param error_info 訂閱合約發生錯誤時的錯誤資訊，當error_info為空，或者error_info.error_id為0時，表明沒有錯誤
			///@param is_last 是否此次訂閱的最後一個應答，當為最後一個的時候為true，如果為false，表示還有其他後續訊息響應
			///@remark 每條訂閱的合約均對應一條訂閱應答，需要快速返回，否則會堵塞後續訊息，當堵塞嚴重時，會觸發斷線
			virtual void OnSubTickByTick(XTPST *ticker, XTPRI *error_info, bool is_last) {};

			///退訂逐筆行情應答，包括股票、指數和期權
			///@param ticker 詳細的合約取消訂閱情況
			///@param error_info 取消訂閱合約時發生錯誤時返回的錯誤資訊，當error_info為空，或者error_info.error_id為0時，表明沒有錯誤
			///@param is_last 是否此次取消訂閱的最後一個應答，當為最後一個的時候為true，如果為false，表示還有其他後續訊息響應
			///@remark 每條取消訂閱的合約均對應一條取消訂閱應答，需要快速返回，否則會堵塞後續訊息，當堵塞嚴重時，會觸發斷線
			virtual void OnUnSubTickByTick(XTPST *ticker, XTPRI *error_info, bool is_last) {};

			///逐筆行情通知，包括股票、指數和期權
			///@param tbt_data 逐筆行情資料，包括逐筆委託和逐筆成交，此為共用結構體，需要根據type來區分是逐筆委託還是逐筆成交，需要快速返回，否則會堵塞後續訊息，當堵塞嚴重時，會觸發斷線
			virtual void OnTickByTick(XTPTBT *tbt_data) {};

			///訂閱全市場的股票行情應答
			///@param exchange_id 表示當前全訂閱的市場，如果為XTP_EXCHANGE_UNKNOWN，表示滬深全市場，XTP_EXCHANGE_SH表示為上海全市場，XTP_EXCHANGE_SZ表示為深圳全市場
			///@param error_info 取消訂閱合約時發生錯誤時返回的錯誤資訊，當error_info為空，或者error_info.error_id為0時，表明沒有錯誤
			///@remark 需要快速返回
			virtual void OnSubscribeAllMarketData(XTP_EXCHANGE_TYPE exchange_id, XTPRI *error_info) {};

			///退訂全市場的股票行情應答
			///@param exchange_id 表示當前退訂的市場，如果為XTP_EXCHANGE_UNKNOWN，表示滬深全市場，XTP_EXCHANGE_SH表示為上海全市場，XTP_EXCHANGE_SZ表示為深圳全市場
			///@param error_info 取消訂閱合約時發生錯誤時返回的錯誤資訊，當error_info為空，或者error_info.error_id為0時，表明沒有錯誤
			///@remark 需要快速返回
			virtual void OnUnSubscribeAllMarketData(XTP_EXCHANGE_TYPE exchange_id, XTPRI *error_info) {};

			///訂閱全市場的股票行情訂單簿應答
			///@param exchange_id 表示當前全訂閱的市場，如果為XTP_EXCHANGE_UNKNOWN，表示滬深全市場，XTP_EXCHANGE_SH表示為上海全市場，XTP_EXCHANGE_SZ表示為深圳全市場
			///@param error_info 取消訂閱合約時發生錯誤時返回的錯誤資訊，當error_info為空，或者error_info.error_id為0時，表明沒有錯誤
			///@remark 需要快速返回
			virtual void OnSubscribeAllOrderBook(XTP_EXCHANGE_TYPE exchange_id, XTPRI *error_info) {};

			///退訂全市場的股票行情訂單簿應答
			///@param exchange_id 表示當前退訂的市場，如果為XTP_EXCHANGE_UNKNOWN，表示滬深全市場，XTP_EXCHANGE_SH表示為上海全市場，XTP_EXCHANGE_SZ表示為深圳全市場
			///@param error_info 取消訂閱合約時發生錯誤時返回的錯誤資訊，當error_info為空，或者error_info.error_id為0時，表明沒有錯誤
			///@remark 需要快速返回
			virtual void OnUnSubscribeAllOrderBook(XTP_EXCHANGE_TYPE exchange_id, XTPRI *error_info) {};

			///訂閱全市場的股票逐筆行情應答
			///@param exchange_id 表示當前全訂閱的市場，如果為XTP_EXCHANGE_UNKNOWN，表示滬深全市場，XTP_EXCHANGE_SH表示為上海全市場，XTP_EXCHANGE_SZ表示為深圳全市場
			///@param error_info 取消訂閱合約時發生錯誤時返回的錯誤資訊，當error_info為空，或者error_info.error_id為0時，表明沒有錯誤
			///@remark 需要快速返回
			virtual void OnSubscribeAllTickByTick(XTP_EXCHANGE_TYPE exchange_id, XTPRI *error_info) {};

			///退訂全市場的股票逐筆行情應答
			///@param exchange_id 表示當前退訂的市場，如果為XTP_EXCHANGE_UNKNOWN，表示滬深全市場，XTP_EXCHANGE_SH表示為上海全市場，XTP_EXCHANGE_SZ表示為深圳全市場
			///@param error_info 取消訂閱合約時發生錯誤時返回的錯誤資訊，當error_info為空，或者error_info.error_id為0時，表明沒有錯誤
			///@remark 需要快速返回
			virtual void OnUnSubscribeAllTickByTick(XTP_EXCHANGE_TYPE exchange_id, XTPRI *error_info) {};


			///查詢可交易合約的應答
			///@param ticker_info 可交易合約資訊
			///@param error_info 查詢可交易合約時發生錯誤時返回的錯誤資訊，當error_info為空，或者error_info.error_id為0時，表明沒有錯誤
			///@param is_last 是否此次查詢可交易合約的最後一個應答，當為最後一個的時候為true，如果為false，表示還有其他後續訊息響應
			virtual void OnQueryAllTickers(XTPQSI* ticker_info, XTPRI *error_info, bool is_last) {};

			///查詢合約的最新價格資訊應答
			///@param ticker_info 合約的最新價格資訊
			///@param error_info 查詢合約的最新價格資訊時發生錯誤時返回的錯誤資訊，當error_info為空，或者error_info.error_id為0時，表明沒有錯誤
			///@param is_last 是否此次查詢的最後一個應答，當為最後一個的時候為true，如果為false，表示還有其他後續訊息響應
			virtual void OnQueryTickersPriceInfo(XTPTPI* ticker_info, XTPRI *error_info, bool is_last) {};

			///訂閱全市場的期權行情應答
			///@param exchange_id 表示當前全訂閱的市場，如果為XTP_EXCHANGE_UNKNOWN，表示滬深全市場，XTP_EXCHANGE_SH表示為上海全市場，XTP_EXCHANGE_SZ表示為深圳全市場
			///@param error_info 取消訂閱合約時發生錯誤時返回的錯誤資訊，當error_info為空，或者error_info.error_id為0時，表明沒有錯誤
			///@remark 需要快速返回
			virtual void OnSubscribeAllOptionMarketData(XTP_EXCHANGE_TYPE exchange_id, XTPRI *error_info) {};

			///退訂全市場的期權行情應答
			///@param exchange_id 表示當前退訂的市場，如果為XTP_EXCHANGE_UNKNOWN，表示滬深全市場，XTP_EXCHANGE_SH表示為上海全市場，XTP_EXCHANGE_SZ表示為深圳全市場
			///@param error_info 取消訂閱合約時發生錯誤時返回的錯誤資訊，當error_info為空，或者error_info.error_id為0時，表明沒有錯誤
			///@remark 需要快速返回
			virtual void OnUnSubscribeAllOptionMarketData(XTP_EXCHANGE_TYPE exchange_id, XTPRI *error_info) {};

			///訂閱全市場的期權行情訂單簿應答
			///@param exchange_id 表示當前全訂閱的市場，如果為XTP_EXCHANGE_UNKNOWN，表示滬深全市場，XTP_EXCHANGE_SH表示為上海全市場，XTP_EXCHANGE_SZ表示為深圳全市場
			///@param error_info 取消訂閱合約時發生錯誤時返回的錯誤資訊，當error_info為空，或者error_info.error_id為0時，表明沒有錯誤
			///@remark 需要快速返回
			virtual void OnSubscribeAllOptionOrderBook(XTP_EXCHANGE_TYPE exchange_id, XTPRI *error_info) {};

			///退訂全市場的期權行情訂單簿應答
			///@param exchange_id 表示當前退訂的市場，如果為XTP_EXCHANGE_UNKNOWN，表示滬深全市場，XTP_EXCHANGE_SH表示為上海全市場，XTP_EXCHANGE_SZ表示為深圳全市場
			///@param error_info 取消訂閱合約時發生錯誤時返回的錯誤資訊，當error_info為空，或者error_info.error_id為0時，表明沒有錯誤
			///@remark 需要快速返回
			virtual void OnUnSubscribeAllOptionOrderBook(XTP_EXCHANGE_TYPE exchange_id, XTPRI *error_info) {};

			///訂閱全市場的期權逐筆行情應答
			///@param exchange_id 表示當前全訂閱的市場，如果為XTP_EXCHANGE_UNKNOWN，表示滬深全市場，XTP_EXCHANGE_SH表示為上海全市場，XTP_EXCHANGE_SZ表示為深圳全市場
			///@param error_info 取消訂閱合約時發生錯誤時返回的錯誤資訊，當error_info為空，或者error_info.error_id為0時，表明沒有錯誤
			///@remark 需要快速返回
			virtual void OnSubscribeAllOptionTickByTick(XTP_EXCHANGE_TYPE exchange_id, XTPRI *error_info) {};

			///退訂全市場的期權逐筆行情應答
			///@param exchange_id 表示當前退訂的市場，如果為XTP_EXCHANGE_UNKNOWN，表示滬深全市場，XTP_EXCHANGE_SH表示為上海全市場，XTP_EXCHANGE_SZ表示為深圳全市場
			///@param error_info 取消訂閱合約時發生錯誤時返回的錯誤資訊，當error_info為空，或者error_info.error_id為0時，表明沒有錯誤
			///@remark 需要快速返回
			virtual void OnUnSubscribeAllOptionTickByTick(XTP_EXCHANGE_TYPE exchange_id, XTPRI *error_info) {};
		};
	}
}

#ifndef WINDOWS
#if __GNUC__ >= 4
#pragma GCC visibility push(default)
#endif
#endif

/*!
* \class XTP::API::QuoteApi
*
* \brief 行情訂閱介面類
*
* \author 中泰證券股份有限公司
* \date 十月 2015
*/
namespace XTP {
	namespace API {
		class MD_API_EXPORT QuoteApi
		{
		public:
			///建立QuoteApi
			///@param client_id （必須輸入）用於區分同一使用者的不同客戶端，由使用者自定義
			///@param save_file_path （必須輸入）存貯訂閱資訊檔案的目錄，請設定一個有可寫許可權的真實存在的路徑
			///@param log_level 日誌輸出級別
			///@return 創建出的UserApi
			///@remark 如果一個賬戶需要在多個客戶端登入，請使用不同的client_id，系統允許一個賬戶同時登入多個客戶端，但是對於同一賬戶，相同的client_id只能保持一個session連線，後面的登入在前一個session存續期間，無法連線
			static QuoteApi *CreateQuoteApi(uint8_t client_id, const char *save_file_path, XTP_LOG_LEVEL log_level=XTP_LOG_LEVEL_DEBUG);

			///刪除介面物件本身
			///@remark 不再使用本介面物件時,呼叫該函式刪除介面物件
			virtual void Release() = 0;


			///獲取當前交易日
			///@return 獲取到的交易日
			///@remark 只有登入成功後,才能得到正確的交易日
			virtual const char *GetTradingDay() = 0;

			///獲取API的發行版本號
			///@return 返回api發行版本號
			virtual const char* GetApiVersion() = 0;

			///獲取API的系統錯誤
			///@return 返回的錯誤資訊，可以在Login、Logout、訂閱、取消訂閱失敗時呼叫，獲取失敗的原因
			///@remark 可以在呼叫api介面失敗時呼叫，例如login失敗時
			virtual XTPRI *GetApiLastError() = 0;

			///設定採用UDP方式連線時的接收緩衝區大小
			///@remark 需要在Login之前呼叫，預設大小和最小設定均為64MB。此快取大小單位為MB，請輸入2的次方數，例如128MB請輸入128。
			virtual void SetUDPBufferSize(uint32_t buff_size) = 0;


			///註冊回撥介面
			///@param spi 派生自回撥介面類的例項，請在登入之前設定
			virtual void RegisterSpi(QuoteSpi *spi) = 0;

			///設定心跳檢測時間間隔，單位為秒
			///@param interval 心跳檢測時間間隔，單位為秒
			///@remark 此函式必須在Login之前呼叫
			virtual void SetHeartBeatInterval(uint32_t interval) = 0;

			///訂閱行情，包括股票、指數和期權。
			///@return 訂閱介面呼叫是否成功，“0”表示介面呼叫成功，非“0”表示介面調用出錯
			///@param ticker 合約ID陣列，注意合約程式碼必須以'\0'結尾，不包含空格 
			///@param count 要訂閱/退訂行情的合約個數
			///@param exchange_id 交易所程式碼
			///@remark 可以一次性訂閱同一證券交易所的多個合約，無論使用者因為何種問題需要重新登入行情伺服器，都需要重新訂閱行情
			virtual int SubscribeMarketData(char *ticker[], int count, XTP_EXCHANGE_TYPE exchange_id) = 0;

			///退訂行情，包括股票、指數和期權。
			///@return 取消訂閱介面呼叫是否成功，“0”表示介面呼叫成功，非“0”表示介面調用出錯
			///@param ticker 合約ID陣列，注意合約程式碼必須以'\0'結尾，不包含空格  
			///@param count 要訂閱/退訂行情的合約個數
			///@param exchange_id 交易所程式碼
			///@remark 可以一次性取消訂閱同一證券交易所的多個合約，需要與訂閱行情介面配套使用
			virtual int UnSubscribeMarketData(char *ticker[], int count, XTP_EXCHANGE_TYPE exchange_id) = 0;

			///訂閱行情訂單簿，包括股票、指數和期權。
			///@return 訂閱行情訂單簿介面呼叫是否成功，“0”表示介面呼叫成功，非“0”表示介面調用出錯
			///@param ticker 合約ID陣列，注意合約程式碼必須以'\0'結尾，不包含空格 
			///@param count 要訂閱/退訂行情訂單簿的合約個數
			///@param exchange_id 交易所程式碼
			///@remark 可以一次性訂閱同一證券交易所的多個合約，無論使用者因為何種問題需要重新登入行情伺服器，都需要重新訂閱行情(僅支援深交所)
			virtual int SubscribeOrderBook(char *ticker[], int count, XTP_EXCHANGE_TYPE exchange_id) = 0;

			///退訂行情訂單簿，包括股票、指數和期權。
			///@return 取消訂閱行情訂單簿介面呼叫是否成功，“0”表示介面呼叫成功，非“0”表示介面調用出錯
			///@param ticker 合約ID陣列，注意合約程式碼必須以'\0'結尾，不包含空格  
			///@param count 要訂閱/退訂行情訂單簿的合約個數
			///@param exchange_id 交易所程式碼
			///@remark 可以一次性取消訂閱同一證券交易所的多個合約，需要與訂閱行情訂單簿介面配套使用
			virtual int UnSubscribeOrderBook(char *ticker[], int count, XTP_EXCHANGE_TYPE exchange_id) = 0;

			///訂閱逐筆行情，包括股票、指數和期權。
			///@return 訂閱逐筆行情介面呼叫是否成功，“0”表示介面呼叫成功，非“0”表示介面調用出錯
			///@param ticker 合約ID陣列，注意合約程式碼必須以'\0'結尾，不包含空格  
			///@param count 要訂閱/退訂行情訂單簿的合約個數
			///@param exchange_id 交易所程式碼
			///@remark 可以一次性訂閱同一證券交易所的多個合約，無論使用者因為何種問題需要重新登入行情伺服器，都需要重新訂閱行情
			virtual int SubscribeTickByTick(char *ticker[], int count, XTP_EXCHANGE_TYPE exchange_id) = 0;

			///退訂逐筆行情，包括股票、指數和期權。
			///@return 取消訂閱逐筆行情介面呼叫是否成功，“0”表示介面呼叫成功，非“0”表示介面調用出錯
			///@param ticker 合約ID陣列，注意合約程式碼必須以'\0'結尾，不包含空格  
			///@param count 要訂閱/退訂行情訂單簿的合約個數
			///@param exchange_id 交易所程式碼
			///@remark 可以一次性取消訂閱同一證券交易所的多個合約，需要與訂閱逐筆行情介面配套使用
			virtual int UnSubscribeTickByTick(char *ticker[], int count, XTP_EXCHANGE_TYPE exchange_id) = 0;

			///訂閱全市場的股票行情
			///@return 訂閱全市場行情介面呼叫是否成功，“0”表示介面呼叫成功，非“0”表示介面調用出錯
			///@param exchange_id 表示當前全訂閱的市場，如果為XTP_EXCHANGE_UNKNOWN，表示滬深全市場，XTP_EXCHANGE_SH表示為上海全市場，XTP_EXCHANGE_SZ表示為深圳全市場
			///@remark 需要與全市場退訂行情介面配套使用
			virtual int SubscribeAllMarketData(XTP_EXCHANGE_TYPE exchange_id = XTP_EXCHANGE_UNKNOWN) = 0;

			///退訂全市場的股票行情
			///@return 退訂全市場行情介面呼叫是否成功，“0”表示介面呼叫成功，非“0”表示介面調用出錯
			///@param exchange_id 表示當前退訂的市場，如果為XTP_EXCHANGE_UNKNOWN，表示滬深全市場，XTP_EXCHANGE_SH表示為上海全市場，XTP_EXCHANGE_SZ表示為深圳全市場
			///@remark 需要與訂閱全市場行情介面配套使用
			virtual int UnSubscribeAllMarketData(XTP_EXCHANGE_TYPE exchange_id = XTP_EXCHANGE_UNKNOWN) = 0;

			///訂閱全市場的股票行情訂單簿
			///@return 訂閱全市場行情訂單簿介面呼叫是否成功，“0”表示介面呼叫成功，非“0”表示介面調用出錯
			///@param exchange_id 表示當前全訂閱的市場，如果為XTP_EXCHANGE_UNKNOWN，表示滬深全市場，XTP_EXCHANGE_SH表示為上海全市場，XTP_EXCHANGE_SZ表示為深圳全市場
			///@remark 需要與全市場退訂行情訂單簿介面配套使用
			virtual int SubscribeAllOrderBook(XTP_EXCHANGE_TYPE exchange_id = XTP_EXCHANGE_UNKNOWN) = 0;

			///退訂全市場的股票行情訂單簿
			///@return 退訂全市場行情訂單簿介面呼叫是否成功，“0”表示介面呼叫成功，非“0”表示介面調用出錯
			///@param exchange_id 表示當前退訂的市場，如果為XTP_EXCHANGE_UNKNOWN，表示滬深全市場，XTP_EXCHANGE_SH表示為上海全市場，XTP_EXCHANGE_SZ表示為深圳全市場
			///@remark 需要與訂閱全市場行情訂單簿介面配套使用
			virtual int UnSubscribeAllOrderBook(XTP_EXCHANGE_TYPE exchange_id = XTP_EXCHANGE_UNKNOWN) = 0;

			///訂閱全市場的股票逐筆行情
			///@return 訂閱全市場逐筆行情介面呼叫是否成功，“0”表示介面呼叫成功，非“0”表示介面調用出錯
			///@param exchange_id 表示當前全訂閱的市場，如果為XTP_EXCHANGE_UNKNOWN，表示滬深全市場，XTP_EXCHANGE_SH表示為上海全市場，XTP_EXCHANGE_SZ表示為深圳全市場
			///@remark 需要與全市場退訂逐筆行情介面配套使用
			virtual int SubscribeAllTickByTick(XTP_EXCHANGE_TYPE exchange_id = XTP_EXCHANGE_UNKNOWN) = 0;

			///退訂全市場的股票逐筆行情
			///@return 退訂全市場逐筆行情介面呼叫是否成功，“0”表示介面呼叫成功，非“0”表示介面調用出錯
			///@param exchange_id 表示當前退訂的市場，如果為XTP_EXCHANGE_UNKNOWN，表示滬深全市場，XTP_EXCHANGE_SH表示為上海全市場，XTP_EXCHANGE_SZ表示為深圳全市場
			///@remark 需要與訂閱全市場逐筆行情介面配套使用
			virtual int UnSubscribeAllTickByTick(XTP_EXCHANGE_TYPE exchange_id = XTP_EXCHANGE_UNKNOWN) = 0;

			///使用者登入請求
			///@return 登入是否成功，“0”表示登入成功，“-1”表示連線伺服器出錯，此時使用者可以呼叫GetApiLastError()來獲取錯誤程式碼，“-2”表示已存在連線，不允許重複登入，如果需要重連，請先logout，“-3”表示輸入有錯誤
			///@param ip 伺服器ip地址，類似“127.0.0.1”
			///@param port 伺服器埠號
			///@param user 登陸使用者名稱
			///@param password 登陸密碼
			///@param sock_type “1”代表TCP，“2”代表UDP
			///@remark 此函式為同步阻塞式，不需要非同步等待登入成功，當函式返回即可進行後續操作，此api只能有一個連線
			virtual int Login(const char* ip, int port, const char* user, const char* password, XTP_PROTOCOL_TYPE sock_type) = 0;


			///登出請求
			///@return 登出是否成功，“0”表示登出成功，非“0”表示登出出錯，此時使用者可以呼叫GetApiLastError()來獲取錯誤程式碼
			///@remark 此函式為同步阻塞式，不需要非同步等待登出，當函式返回即可進行後續操作
			virtual int Logout() = 0;

			///獲取當前交易日可交易合約
			///@return 查詢是否成功，“0”表示查詢成功，非“0”表示查詢不成功
			///@param exchange_id 交易所程式碼
			virtual int QueryAllTickers(XTP_EXCHANGE_TYPE exchange_id) = 0;

			///獲取合約的最新價格資訊
			///@return 查詢是否成功，“0”表示查詢成功，非“0”表示查詢不成功
			///@param ticker 合約ID陣列，注意合約程式碼必須以'\0'結尾，不包含空格  
			///@param count 要查詢的合約個數
			///@param exchange_id 交易所程式碼
			virtual int QueryTickersPriceInfo(char *ticker[], int count, XTP_EXCHANGE_TYPE exchange_id) = 0;

			///獲取所有合約的最新價格資訊
			///@return 查詢是否成功，“0”表示查詢成功，非“0”表示查詢不成功
			virtual int QueryAllTickersPriceInfo() = 0;

			///訂閱全市場的期權行情
			///@return 訂閱全市期權場行情介面呼叫是否成功，“0”表示介面呼叫成功，非“0”表示介面調用出錯
			///@param exchange_id 表示當前全訂閱的市場，如果為XTP_EXCHANGE_UNKNOWN，表示滬深全市場，XTP_EXCHANGE_SH表示為上海全市場，XTP_EXCHANGE_SZ表示為深圳全市場
			///@remark 需要與全市場退訂期權行情介面配套使用
			virtual int SubscribeAllOptionMarketData(XTP_EXCHANGE_TYPE exchange_id = XTP_EXCHANGE_UNKNOWN) = 0;

			///退訂全市場的期權行情
			///@return 退訂全市場期權行情介面呼叫是否成功，“0”表示介面呼叫成功，非“0”表示介面調用出錯
			///@param exchange_id 表示當前退訂的市場，如果為XTP_EXCHANGE_UNKNOWN，表示滬深全市場，XTP_EXCHANGE_SH表示為上海全市場，XTP_EXCHANGE_SZ表示為深圳全市場
			///@remark 需要與訂閱全市場期權行情介面配套使用
			virtual int UnSubscribeAllOptionMarketData(XTP_EXCHANGE_TYPE exchange_id = XTP_EXCHANGE_UNKNOWN) = 0;

			///訂閱全市場的期權行情訂單簿
			///@return 訂閱全市場期權行情訂單簿介面呼叫是否成功，“0”表示介面呼叫成功，非“0”表示介面調用出錯
			///@param exchange_id 表示當前全訂閱的市場，如果為XTP_EXCHANGE_UNKNOWN，表示滬深全市場，XTP_EXCHANGE_SH表示為上海全市場，XTP_EXCHANGE_SZ表示為深圳全市場
			///@remark 需要與全市場退訂期權行情訂單簿介面配套使用
			virtual int SubscribeAllOptionOrderBook(XTP_EXCHANGE_TYPE exchange_id = XTP_EXCHANGE_UNKNOWN) = 0;

			///退訂全市場的期權行情訂單簿
			///@return 退訂全市場期權行情訂單簿介面呼叫是否成功，“0”表示介面呼叫成功，非“0”表示介面調用出錯
			///@param exchange_id 表示當前退訂的市場，如果為XTP_EXCHANGE_UNKNOWN，表示滬深全市場，XTP_EXCHANGE_SH表示為上海全市場，XTP_EXCHANGE_SZ表示為深圳全市場
			///@remark 需要與訂閱全市場期權行情訂單簿介面配套使用
			virtual int UnSubscribeAllOptionOrderBook(XTP_EXCHANGE_TYPE exchange_id = XTP_EXCHANGE_UNKNOWN) = 0;

			///訂閱全市場的期權逐筆行情
			///@return 訂閱全市場期權逐筆行情介面呼叫是否成功，“0”表示介面呼叫成功，非“0”表示介面調用出錯
			///@param exchange_id 表示當前全訂閱的市場，如果為XTP_EXCHANGE_UNKNOWN，表示滬深全市場，XTP_EXCHANGE_SH表示為上海全市場，XTP_EXCHANGE_SZ表示為深圳全市場
			///@remark 需要與全市場退訂期權逐筆行情介面配套使用
			virtual int SubscribeAllOptionTickByTick(XTP_EXCHANGE_TYPE exchange_id = XTP_EXCHANGE_UNKNOWN) = 0;

			///退訂全市場的期權逐筆行情
			///@return 退訂全市場期權逐筆行情介面呼叫是否成功，“0”表示介面呼叫成功，非“0”表示介面調用出錯
			///@param exchange_id 表示當前退訂的市場，如果為XTP_EXCHANGE_UNKNOWN，表示滬深全市場，XTP_EXCHANGE_SH表示為上海全市場，XTP_EXCHANGE_SZ表示為深圳全市場
			///@remark 需要與訂閱全市場期權逐筆行情介面配套使用
			virtual int UnSubscribeAllOptionTickByTick(XTP_EXCHANGE_TYPE exchange_id = XTP_EXCHANGE_UNKNOWN) = 0;


		protected:
			~QuoteApi() {};
		};
	}
}

#ifndef WINDOWS
#if __GNUC__ >= 4
#pragma GCC visibility pop
#endif
#endif


#endif
