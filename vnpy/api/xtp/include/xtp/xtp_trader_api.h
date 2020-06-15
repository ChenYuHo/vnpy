/////////////////////////////////////////////////////////////////////////
///@author 中泰證券股份有限公司
///@file xtp_trader_api.h
///@brief 定義客戶端交易介面
/////////////////////////////////////////////////////////////////////////

#ifndef _XTP_TRADER_API_H_
#define _XTP_TRADER_API_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "xtp_api_struct.h"

#if defined(ISLIB) && defined(WIN32)
#ifdef LIB_TRADER_API_EXPORT
#define TRADER_API_EXPORT __declspec(dllexport)
#else
#define TRADER_API_EXPORT __declspec(dllimport)
#endif
#else
#define TRADER_API_EXPORT 
#endif

/*!
* \class XTP::API::TraderSpi
*
* \brief 交易介面響應類
*
* \author 中泰證券股份有限公司
* \date 十月 2015
*/
namespace XTP {
	namespace API {

		class TraderSpi
		{
		public:

			///當客戶端的某個連線與交易後臺通訊連線斷開時，該方法被呼叫。
			///@param reason 錯誤原因，請與錯誤程式碼表對應
			///@param session_id 資金賬戶對應的session_id，登入時得到
			///@remark 使用者主動呼叫logout導致的斷線，不會觸發此函式。api不會自動重連，當斷線發生時，請使用者自行選擇後續操作，可以在此函式中呼叫Login重新登入，並更新session_id，此時使用者收到的資料跟斷線之前是連續的
			virtual void OnDisconnected(uint64_t session_id, int reason) {};

			///錯誤應答
			///@param error_info 當伺服器響應發生錯誤時的具體的錯誤程式碼和錯誤資訊,當error_info為空，或者error_info.error_id為0時，表明沒有錯誤
			///@remark 此函式只有在伺服器發生錯誤時才會呼叫，一般無需使用者處理
			virtual void OnError(XTPRI *error_info) {};

			///報單通知
			///@param order_info 訂單響應具體資訊，使用者可以通過order_info.order_xtp_id來管理訂單，通過GetClientIDByXTPID() == client_id來過濾自己的訂單，order_info.qty_left欄位在訂單為未成交、部成、全成、廢單狀態時，表示此訂單還沒有成交的數量，在部撤、全撤狀態時，表示此訂單被撤的數量。order_info.order_cancel_xtp_id為其所對應的撤單ID，不為0時表示此單被撤成功
			///@param error_info 訂單被拒絕或者發生錯誤時錯誤程式碼和錯誤資訊，當error_info為空，或者error_info.error_id為0時，表明沒有錯誤
			///@param session_id 資金賬戶對應的session_id，登入時得到
			///@remark 每次訂單狀態更新時，都會被呼叫，需要快速返回，否則會堵塞後續訊息，當堵塞嚴重時，會觸發斷線，在訂單未成交、全部成交、全部撤單、部分撤單、已拒絕這些狀態時會有響應，對於部分成交的情況，請由訂單的成交回報來自行確認。所有登入了此使用者的客戶端都將收到此使用者的訂單響應
			virtual void OnOrderEvent(XTPOrderInfo *order_info, XTPRI *error_info, uint64_t session_id) {};

			///成交通知
			///@param trade_info 成交回報的具體資訊，使用者可以通過trade_info.order_xtp_id來管理訂單，通過GetClientIDByXTPID() == client_id來過濾自己的訂單。對於上交所，exec_id可以唯一標識一筆成交。當發現2筆成交回報擁有相同的exec_id，則可以認為此筆交易自成交了。對於深交所，exec_id是唯一的，暫時無此判斷機制。report_index+market欄位可以組成唯一標識表示成交回報。
			///@param session_id 資金賬戶對應的session_id，登入時得到
			///@remark 訂單有成交發生的時候，會被呼叫，需要快速返回，否則會堵塞後續訊息，當堵塞嚴重時，會觸發斷線。所有登入了此使用者的客戶端都將收到此使用者的成交回報。相關訂單為部成狀態，需要使用者通過成交回報的成交數量來確定，OnOrderEvent()不會推送部成狀態。
			virtual void OnTradeEvent(XTPTradeReport *trade_info, uint64_t session_id) {};

			///撤單出錯響應
			///@param cancel_info 撤單具體資訊，包括撤單的order_cancel_xtp_id和待撤單的order_xtp_id
			///@param error_info 撤單被拒絕或者發生錯誤時錯誤程式碼和錯誤資訊，需要快速返回，否則會堵塞後續訊息，當堵塞嚴重時，會觸發斷線，當error_info為空，或者error_info.error_id為0時，表明沒有錯誤
			///@param session_id 資金賬戶對應的session_id，登入時得到
			///@remark 此響應只會在撤單發生錯誤時被回撥
			virtual void OnCancelOrderError(XTPOrderCancelInfo *cancel_info, XTPRI *error_info, uint64_t session_id) {};

			///請求查詢報單響應
			///@param order_info 查詢到的一個報單
			///@param error_info 查詢報單時發生錯誤時，返回的錯誤資訊，當error_info為空，或者error_info.error_id為0時，表明沒有錯誤
			///@param request_id 此訊息響應函式對應的請求ID
			///@param is_last 此訊息響應函式是否為request_id這條請求所對應的最後一個響應，當為最後一個的時候為true，如果為false，表示還有其他後續訊息響應
			///@param session_id 資金賬戶對應的session_id，登入時得到
			///@remark 由於支援分時段查詢，一個查詢請求可能對應多個響應，需要快速返回，否則會堵塞後續訊息，當堵塞嚴重時，會觸發斷線
			virtual void OnQueryOrder(XTPQueryOrderRsp *order_info, XTPRI *error_info, int request_id, bool is_last, uint64_t session_id) {};

			///請求查詢成交響應
			///@param trade_info 查詢到的一個成交回報
			///@param error_info 查詢成交回報發生錯誤時返回的錯誤資訊，當error_info為空，或者error_info.error_id為0時，表明沒有錯誤
			///@param request_id 此訊息響應函式對應的請求ID
			///@param is_last 此訊息響應函式是否為request_id這條請求所對應的最後一個響應，當為最後一個的時候為true，如果為false，表示還有其他後續訊息響應
			///@param session_id 資金賬戶對應的session_id，登入時得到
			///@remark 由於支援分時段查詢，一個查詢請求可能對應多個響應，需要快速返回，否則會堵塞後續訊息，當堵塞嚴重時，會觸發斷線
			virtual void OnQueryTrade(XTPQueryTradeRsp *trade_info, XTPRI *error_info, int request_id, bool is_last, uint64_t session_id) {};

			///請求查詢投資者持倉響應
			///@param position 查詢到的一隻股票的持倉情況
			///@param error_info 查詢賬戶持倉發生錯誤時返回的錯誤資訊，當error_info為空，或者error_info.error_id為0時，表明沒有錯誤
			///@param request_id 此訊息響應函式對應的請求ID
			///@param is_last 此訊息響應函式是否為request_id這條請求所對應的最後一個響應，當為最後一個的時候為true，如果為false，表示還有其他後續訊息響應
			///@param session_id 資金賬戶對應的session_id，登入時得到
			///@remark 由於使用者可能持有多個股票，一個查詢請求可能對應多個響應，需要快速返回，否則會堵塞後續訊息，當堵塞嚴重時，會觸發斷線
			virtual void OnQueryPosition(XTPQueryStkPositionRsp *position, XTPRI *error_info, int request_id, bool is_last, uint64_t session_id) {};

			///請求查詢資金賬戶響應，需要快速返回，否則會堵塞後續訊息，當堵塞嚴重時，會觸發斷線
			///@param asset 查詢到的資金賬戶情況
			///@param error_info 查詢資金賬戶發生錯誤時返回的錯誤資訊，當error_info為空，或者error_info.error_id為0時，表明沒有錯誤
			///@param request_id 此訊息響應函式對應的請求ID
			///@param is_last 此訊息響應函式是否為request_id這條請求所對應的最後一個響應，當為最後一個的時候為true，如果為false，表示還有其他後續訊息響應
			///@param session_id 資金賬戶對應的session_id，登入時得到
			///@remark 需要快速返回，否則會堵塞後續訊息，當堵塞嚴重時，會觸發斷線
			virtual void OnQueryAsset(XTPQueryAssetRsp *asset, XTPRI *error_info, int request_id, bool is_last, uint64_t session_id) {};

			///請求查詢分級基金資訊響應，需要快速返回，否則會堵塞後續訊息，當堵塞嚴重時，會觸發斷線
			///@param fund_info 查詢到的分級基金情況
			///@param error_info 查詢分級基金髮生錯誤時返回的錯誤資訊，當error_info為空，或者error_info.error_id為0時，表明沒有錯誤
			///@param request_id 此訊息響應函式對應的請求ID
			///@param is_last 此訊息響應函式是否為request_id這條請求所對應的最後一個響應，當為最後一個的時候為true，如果為false，表示還有其他後續訊息響應
			///@param session_id 資金賬戶對應的session_id，登入時得到
			///@remark 需要快速返回，否則會堵塞後續訊息，當堵塞嚴重時，會觸發斷線
			virtual void OnQueryStructuredFund(XTPStructuredFundInfo *fund_info, XTPRI *error_info, int request_id, bool is_last, uint64_t session_id) {};

			///請求查詢資金劃撥訂單響應，需要快速返回，否則會堵塞後續訊息，當堵塞嚴重時，會觸發斷線
			///@param fund_transfer_info 查詢到的資金賬戶情況
			///@param error_info 查詢資金賬戶發生錯誤時返回的錯誤資訊，當error_info為空，或者error_info.error_id為0時，表明沒有錯誤
			///@param request_id 此訊息響應函式對應的請求ID
			///@param is_last 此訊息響應函式是否為request_id這條請求所對應的最後一個響應，當為最後一個的時候為true，如果為false，表示還有其他後續訊息響應
			///@param session_id 資金賬戶對應的session_id，登入時得到
			///@remark 需要快速返回，否則會堵塞後續訊息，當堵塞嚴重時，會觸發斷線
			virtual void OnQueryFundTransfer(XTPFundTransferNotice *fund_transfer_info, XTPRI *error_info, int request_id, bool is_last, uint64_t session_id) {};

			///資金劃撥通知
			///@param fund_transfer_info 資金劃撥通知的具體資訊，使用者可以通過fund_transfer_info.serial_id來管理訂單，通過GetClientIDByXTPID() == client_id來過濾自己的訂單。
			///@param error_info 資金劃撥訂單被拒絕或者發生錯誤時錯誤程式碼和錯誤資訊，當error_info為空，或者error_info.error_id為0時，表明沒有錯誤。當資金劃撥方向為一號兩中心節點之間劃撥，且error_info.error_id=11000384時，error_info.error_msg為結點中可用於劃撥的資金（以整數為準），使用者需進行stringToInt的轉化，可據此填寫合適的資金，再次發起劃撥請求
			///@param session_id 資金賬戶對應的session_id，登入時得到
			///@remark 當資金劃撥訂單有狀態變化的時候，會被呼叫，需要快速返回，否則會堵塞後續訊息，當堵塞嚴重時，會觸發斷線。所有登入了此使用者的客戶端都將收到此使用者的資金劃撥通知。
			virtual void OnFundTransfer(XTPFundTransferNotice *fund_transfer_info, XTPRI *error_info, uint64_t session_id) {};

			///請求查詢ETF清單檔案的響應，需要快速返回，否則會堵塞後續訊息，當堵塞嚴重時，會觸發斷線
			///@param etf_info 查詢到的ETF清單檔案情況
			///@param error_info 查詢ETF清單檔案發生錯誤時返回的錯誤資訊，當error_info為空，或者error_info.error_id為0時，表明沒有錯誤
			///@param request_id 此訊息響應函式對應的請求ID
			///@param is_last 此訊息響應函式是否為request_id這條請求所對應的最後一個響應，當為最後一個的時候為true，如果為false，表示還有其他後續訊息響應
			///@param session_id 資金賬戶對應的session_id，登入時得到
			///@remark 需要快速返回，否則會堵塞後續訊息，當堵塞嚴重時，會觸發斷線
			virtual void OnQueryETF(XTPQueryETFBaseRsp *etf_info, XTPRI *error_info, int request_id, bool is_last, uint64_t session_id) {};

			///請求查詢ETF股票籃的響應，需要快速返回，否則會堵塞後續訊息，當堵塞嚴重時，會觸發斷線
			///@param etf_component_info 查詢到的ETF合約的相關成分股資訊
			///@param error_info 查詢ETF股票籃發生錯誤時返回的錯誤資訊，當error_info為空，或者error_info.error_id為0時，表明沒有錯誤
			///@param request_id 此訊息響應函式對應的請求ID
			///@param is_last 此訊息響應函式是否為request_id這條請求所對應的最後一個響應，當為最後一個的時候為true，如果為false，表示還有其他後續訊息響應
			///@param session_id 資金賬戶對應的session_id，登入時得到
			///@remark 需要快速返回，否則會堵塞後續訊息，當堵塞嚴重時，會觸發斷線
			virtual void OnQueryETFBasket(XTPQueryETFComponentRsp *etf_component_info, XTPRI *error_info, int request_id, bool is_last, uint64_t session_id) {};

			///請求查詢今日新股申購資訊列表的響應，需要快速返回，否則會堵塞後續訊息，當堵塞嚴重時，會觸發斷線
			///@param ipo_info 查詢到的今日新股申購的一隻股票資訊
			///@param error_info 查詢今日新股申購資訊列表發生錯誤時返回的錯誤資訊，當error_info為空，或者error_info.error_id為0時，表明沒有錯誤
			///@param request_id 此訊息響應函式對應的請求ID
			///@param is_last 此訊息響應函式是否為request_id這條請求所對應的最後一個響應，當為最後一個的時候為true，如果為false，表示還有其他後續訊息響應
			///@param session_id 資金賬戶對應的session_id，登入時得到
			///@remark 需要快速返回，否則會堵塞後續訊息，當堵塞嚴重時，會觸發斷線
			virtual void OnQueryIPOInfoList(XTPQueryIPOTickerRsp *ipo_info, XTPRI *error_info, int request_id, bool is_last, uint64_t session_id) {};

			///請求查詢使用者新股申購額度資訊的響應，需要快速返回，否則會堵塞後續訊息，當堵塞嚴重時，會觸發斷線
			///@param quota_info 查詢到的使用者某個市場的今日新股申購額度資訊
			///@param error_info 查查詢使用者新股申購額度資訊發生錯誤時返回的錯誤資訊，當error_info為空，或者error_info.error_id為0時，表明沒有錯誤
			///@param request_id 此訊息響應函式對應的請求ID
			///@param is_last 此訊息響應函式是否為request_id這條請求所對應的最後一個響應，當為最後一個的時候為true，如果為false，表示還有其他後續訊息響應
			///@param session_id 資金賬戶對應的session_id，登入時得到
			///@remark 需要快速返回，否則會堵塞後續訊息，當堵塞嚴重時，會觸發斷線
			virtual void OnQueryIPOQuotaInfo(XTPQueryIPOQuotaRsp *quota_info, XTPRI *error_info, int request_id, bool is_last, uint64_t session_id) {};

			///請求查詢期權合約的響應，需要快速返回，否則會堵塞後續訊息，當堵塞嚴重時，會觸發斷線
			///@param option_info 查詢到的期權合約情況
			///@param error_info 查詢期權合約發生錯誤時返回的錯誤資訊，當error_info為空，或者error_info.error_id為0時，表明沒有錯誤
			///@param request_id 此訊息響應函式對應的請求ID
			///@param is_last 此訊息響應函式是否為request_id這條請求所對應的最後一個響應，當為最後一個的時候為true，如果為false，表示還有其他後續訊息響應
			///@param session_id 資金賬戶對應的session_id，登入時得到
			///@remark 需要快速返回，否則會堵塞後續訊息，當堵塞嚴重時，會觸發斷線
			virtual void OnQueryOptionAuctionInfo(XTPQueryOptionAuctionInfoRsp *option_info, XTPRI *error_info, int request_id, bool is_last, uint64_t session_id) {};

			///融資融券業務中現金直接還款的響應
			///@param cash_repay_info 現金直接還款通知的具體資訊，使用者可以通過cash_repay_info.xtp_id來管理訂單，通過GetClientIDByXTPID() == client_id來過濾自己的訂單。
			///@param error_info 現金還款發生錯誤時返回的錯誤資訊，當error_info為空，或者error_info.error_id為0時，表明沒有錯誤
			///@param session_id 資金賬戶對應的session_id，登入時得到
			///@remark 需要快速返回，否則會堵塞後續訊息，當堵塞嚴重時，會觸發斷線
			virtual void OnCreditCashRepay(XTPCrdCashRepayRsp *cash_repay_info, XTPRI *error_info, uint64_t session_id) {};

			///請求查詢融資融券業務中的現金直接還款報單的響應
			///@param cash_repay_info 查詢到的某一筆現金直接還款通知的具體資訊
			///@param error_info 查詢現金直接報單發生錯誤時返回的錯誤資訊，當error_info為空，或者error_info.error_id為0時，表明沒有錯誤
			///@param request_id 此訊息響應函式對應的請求ID
			///@param is_last 此訊息響應函式是否為request_id這條請求所對應的最後一個響應，當為最後一個的時候為true，如果為false，表示還有其他後續訊息響應
			///@param session_id 資金賬戶對應的session_id，登入時得到
			///@remark 需要快速返回，否則會堵塞後續訊息，當堵塞嚴重時，會觸發斷線
			virtual void OnQueryCreditCashRepayInfo(XTPCrdCashRepayInfo *cash_repay_info, XTPRI *error_info, int request_id, bool is_last, uint64_t session_id) {};

			///請求查詢信用賬戶額外資訊的響應，需要快速返回，否則會堵塞後續訊息，當堵塞嚴重時，會觸發斷線
			///@param fund_info 查詢到的信用賬戶額外資訊情況
			///@param error_info 查詢信用賬戶額外資訊發生錯誤時返回的錯誤資訊，當error_info為空，或者error_info.error_id為0時，表明沒有錯誤
			///@param request_id 此訊息響應函式對應的請求ID
			///@param session_id 資金賬戶對應的session_id，登入時得到
			///@remark 需要快速返回，否則會堵塞後續訊息，當堵塞嚴重時，會觸發斷線
			virtual void OnQueryCreditFundInfo(XTPCrdFundInfo *fund_info, XTPRI *error_info, int request_id, uint64_t session_id) {};

			///請求查詢信用賬戶負債資訊的響應，需要快速返回，否則會堵塞後續訊息，當堵塞嚴重時，會觸發斷線
			///@param debt_info 查詢到的信用賬戶合約負債情況
			///@param error_info 查詢信用賬戶負債資訊發生錯誤時返回的錯誤資訊，當error_info為空，或者error_info.error_id為0時，表明沒有錯誤
			///@param request_id 此訊息響應函式對應的請求ID
			///@param is_last 此訊息響應函式是否為request_id這條請求所對應的最後一個響應，當為最後一個的時候為true，如果為false，表示還有其他後續訊息響應
			///@param session_id 資金賬戶對應的session_id，登入時得到
			///@remark 需要快速返回，否則會堵塞後續訊息，當堵塞嚴重時，會觸發斷線
			virtual void OnQueryCreditDebtInfo(XTPCrdDebtInfo *debt_info, XTPRI *error_info, int request_id, bool is_last, uint64_t session_id) {};

			///請求查詢信用賬戶指定證券負債未還資訊響應，需要快速返回，否則會堵塞後續訊息，當堵塞嚴重時，會觸發斷線
			///@param debt_info 查詢到的信用賬戶指定證券負債未還資訊情況
			///@param error_info 查詢信用賬戶指定證券負債未還資訊發生錯誤時返回的錯誤資訊，當error_info為空，或者error_info.error_id為0時，表明沒有錯誤
			///@param request_id 此訊息響應函式對應的請求ID
			///@param is_last 此訊息響應函式是否為request_id這條請求所對應的最後一個響應，當為最後一個的時候為true，如果為false，表示還有其他後續訊息響應
			///@param session_id 資金賬戶對應的session_id，登入時得到
			///@remark 需要快速返回，否則會堵塞後續訊息，當堵塞嚴重時，會觸發斷線
			virtual void OnQueryCreditTickerDebtInfo(XTPCrdDebtStockInfo *debt_info, XTPRI *error_info, int request_id, bool is_last, uint64_t session_id) {};

			///請求查詢信用賬戶待還資金的響應，需要快速返回，否則會堵塞後續訊息，當堵塞嚴重時，會觸發斷線
			///@param remain_amount 查詢到的信用賬戶待還資金
			///@param error_info 查詢信用賬戶待還資金髮生錯誤時返回的錯誤資訊，當error_info為空，或者error_info.error_id為0時，表明沒有錯誤
			///@param request_id 此訊息響應函式對應的請求ID
			///@param session_id 資金賬戶對應的session_id，登入時得到
			///@remark 需要快速返回，否則會堵塞後續訊息，當堵塞嚴重時，會觸發斷線
			virtual void OnQueryCreditAssetDebtInfo(double remain_amount, XTPRI *error_info, int request_id, uint64_t session_id) {};

			///請求查詢信用賬戶可融券頭寸資訊的響應，需要快速返回，否則會堵塞後續訊息，當堵塞嚴重時，會觸發斷線
			///@param assign_info 查詢到的信用賬戶可融券頭寸資訊
			///@param error_info 查詢信用賬戶可融券頭寸資訊發生錯誤時返回的錯誤資訊，當error_info為空，或者error_info.error_id為0時，表明沒有錯誤
			///@param request_id 此訊息響應函式對應的請求ID
			///@param is_last 此訊息響應函式是否為request_id這條請求所對應的最後一個響應，當為最後一個的時候為true，如果為false，表示還有其他後續訊息響應
			///@param session_id 資金賬戶對應的session_id，登入時得到
			///@remark 需要快速返回，否則會堵塞後續訊息，當堵塞嚴重時，會觸發斷線
			virtual void OnQueryCreditTickerAssignInfo(XTPClientQueryCrdPositionStkInfo *assign_info, XTPRI *error_info, int request_id, bool is_last, uint64_t session_id) {};

			///融資融券業務中請求查詢指定餘券資訊的響應，需要快速返回，否則會堵塞後續訊息，當堵塞嚴重時，會觸發斷線
			///@param stock_info 查詢到的餘券資訊
			///@param error_info 查詢信用賬戶餘券資訊發生錯誤時返回的錯誤資訊，當error_info為空，或者error_info.error_id為0時，表明沒有錯誤
			///@param request_id 此訊息響應函式對應的請求ID
			///@param session_id 資金賬戶對應的session_id，登入時得到
			///@remark 需要快速返回，否則會堵塞後續訊息，當堵塞嚴重時，會觸發斷線
			virtual void OnQueryCreditExcessStock(XTPClientQueryCrdSurplusStkRspInfo* stock_info, XTPRI *error_info, int request_id, uint64_t session_id) {};

		};
	}
}

#ifndef WINDOWS
#if __GNUC__ >= 4
#pragma GCC visibility push(default)
#endif
#endif

/*!
* \class XTP::API::TraderApi
*
* \brief 交易介面類
*
* \author 中泰證券股份有限公司
* \date 十月 2015
*/
namespace XTP {
	namespace API {

		class TRADER_API_EXPORT TraderApi
		{
		public:
			///建立TraderApi
			///@param client_id （必須輸入）客戶端id，用於區分同一使用者的不同客戶端，由使用者自定義
			///@param save_file_path （必須輸入）存貯訂閱資訊檔案的目錄，請設定一個真實存在的有可寫許可權的路徑
			///@param log_level 日誌輸出級別
			///@return 創建出的UserApi
			///@remark 如果一個賬戶需要在多個客戶端登入，請使用不同的client_id，系統允許一個賬戶同時登入多個客戶端，但是對於同一賬戶，相同的client_id只能保持一個session連線，後面的登入在前一個session存續期間，無法連線。系統不支援過夜，請確保每天開盤前重新啟動
			static TraderApi *CreateTraderApi(uint8_t client_id, const char *save_file_path, XTP_LOG_LEVEL log_level = XTP_LOG_LEVEL_DEBUG);

			///刪除介面物件本身
			///@remark 不再使用本介面物件時,呼叫該函式刪除介面物件
			virtual void Release() = 0;

			///獲取當前交易日
			///@return 獲取到的交易日
			///@remark 只有登入成功後,才能得到正確的交易日
			virtual const char *GetTradingDay() = 0;

			///註冊回撥介面
			///@param spi 派生自回撥介面類的例項，請在登入之前設定
			virtual void RegisterSpi(TraderSpi *spi) = 0;

			///獲取API的系統錯誤
			///@return 返回的錯誤資訊，可以在Login、InsertOrder、CancelOrder返回值為0時呼叫，獲取失敗的原因
			///@remark 可以在呼叫api介面失敗時呼叫，例如login失敗時
			virtual XTPRI *GetApiLastError() = 0;

			///獲取API的發行版本號
			///@return 返回api發行版本號
			virtual const char* GetApiVersion() = 0;

			///通過報單在xtp系統中的ID獲取下單的客戶端id
			///@return 返回客戶端id，可以用此方法過濾自己下的訂單
			///@param order_xtp_id 報單在xtp系統中的ID
			///@remark 由於系統允許同一使用者在不同客戶端上登入操作，每個客戶端通過不同的client_id進行區分
			virtual uint8_t GetClientIDByXTPID(uint64_t order_xtp_id) = 0;

			///通過報單在xtp系統中的ID獲取相關資金賬戶名
			///@return 返回資金賬戶名
			///@param order_xtp_id 報單在xtp系統中的ID
			///@remark 只有資金賬戶登入成功後,才能得到正確的資訊
			virtual const char* GetAccountByXTPID(uint64_t order_xtp_id) = 0;

			///訂閱公共流。
			///@param resume_type 公共流（訂單響應、成交回報）重傳方式  
			///        XTP_TERT_RESTART:從本交易日開始重傳
			///        XTP_TERT_RESUME:(保留欄位，此方式暫未支援)從上次收到的續傳
			///        XTP_TERT_QUICK:只傳送登入後公共流的內容
			///@remark 該方法要在Login方法前呼叫。若不呼叫則不會收到公共流的資料。注意在使用者斷線後，如果不登出就login()，公共流訂閱方式不會起作用。使用者只會收到斷線後的所有訊息。如果先logout()再login()，那麼公共流訂閱方式會起作用，使用者收到的資料會根據使用者的選擇方式而定。
			virtual void SubscribePublicTopic(XTP_TE_RESUME_TYPE resume_type) = 0;

			///設定軟體開發版本號
			///@param version 使用者開發軟體版本號，非api發行版本號，長度不超過15位，以'\0'結尾
			///@remark 此函式必須在Login之前呼叫，標識的是客戶端版本號，而不是API的版本號，由使用者自定義
			virtual void SetSoftwareVersion(const char* version) = 0;

			///設定軟體開發Key
			///@param key 使用者開發軟體Key，使用者申請開戶時給予，以'\0'結尾
			///@remark 此函式必須在Login之前呼叫
			virtual void SetSoftwareKey(const char* key) = 0;

			///設定心跳檢測時間間隔，單位為秒
			///@param interval 心跳檢測時間間隔，單位為秒
			///@remark 此函式必須在Login之前呼叫
			virtual void SetHeartBeatInterval(uint32_t interval) = 0;

			///使用者登入請求
			///@return session_id表明此資金賬號登入是否成功，“0”表示登入失敗，可以呼叫GetApiLastError()來獲取錯誤程式碼，非“0”表示登入成功，此時需要記錄下這個返回值session_id，與登入的資金賬戶對應
			///@param ip 伺服器地址，類似“127.0.0.1”
			///@param port 伺服器埠號
			///@param user 登入使用者名稱
			///@param password 登入密碼
			///@param sock_type “1”代表TCP，“2”代表UDP，目前暫時只支援TCP
			///@remark 此函式為同步阻塞式，不需要非同步等待登入成功，當函式返回即可進行後續操作，此api可支援多個賬戶連線，但是同一個賬戶同一個client_id只能有一個session連線，後面的登入在前一個session存續期間，無法連線
			virtual uint64_t Login(const char* ip, int port, const char* user, const char* password, XTP_PROTOCOL_TYPE sock_type) = 0;


			///登出請求
			///@return 登出是否成功，“0”表示登出成功，“-1”表示登出失敗
			///@param session_id 資金賬戶對應的session_id,登入時得到
			virtual int Logout(uint64_t session_id) = 0;

			///報單錄入請求
			///@return 報單在XTP系統中的ID,如果為‘0’表示報單傳送失敗，此時使用者可以呼叫GetApiLastError()來獲取錯誤程式碼，非“0”表示報單傳送成功，使用者需要記錄下返回的order_xtp_id，它保證一個交易日內唯一，不同的交易日不保證唯一性
			///@param order 報單錄入資訊，其中order.order_client_id欄位是使用者自定義欄位，使用者輸入什麼值，訂單響應OnOrderEvent()返回時就會帶回什麼值，類似於備註，方便使用者自己定位訂單。當然，如果你什麼都不填，也是可以的。order.order_xtp_id欄位無需使用者填寫，order.ticker必須不帶空格，以'\0'結尾
			///@param session_id 資金賬戶對應的session_id,登入時得到
			///@remark 交易所接收訂單後，會在報單響應函式OnOrderEvent()中返回報單未成交的狀態，之後所有的訂單狀態改變（除了部成狀態）都會通過報單響應函式返回
			virtual uint64_t InsertOrder(XTPOrderInsertInfo *order, uint64_t session_id) = 0;

			///報單操作請求
			///@return 撤單在XTP系統中的ID,如果為‘0’表示撤單傳送失敗，此時使用者可以呼叫GetApiLastError()來獲取錯誤程式碼，非“0”表示撤單傳送成功，使用者需要記錄下返回的order_cancel_xtp_id，它保證一個交易日內唯一，不同的交易日不保證唯一性
			///@param order_xtp_id 需要撤銷的委託單在XTP系統中的ID
			///@param session_id 資金賬戶對應的session_id,登入時得到
			///@remark 如果撤單成功，會在報單響應函式OnOrderEvent()裡返回原單部撤或者全撤的訊息，如果不成功，會在OnCancelOrderError()響應函式中返回錯誤原因
			virtual uint64_t CancelOrder(const uint64_t order_xtp_id, uint64_t session_id) = 0;

			///根據報單ID請求查詢報單
			///@return 查詢是否成功，“0”表示成功，非“0”表示出錯，此時使用者可以呼叫GetApiLastError()來獲取錯誤程式碼
			///@param order_xtp_id 需要查詢的報單在xtp系統中的ID，即InsertOrder()成功時返回的order_xtp_id
			///@param session_id 資金賬戶對應的session_id，登入時得到
			///@param request_id 用於使用者定位查詢響應的ID，由使用者自定義
			virtual int QueryOrderByXTPID(const uint64_t order_xtp_id, uint64_t session_id, int request_id) = 0;

			///請求查詢報單
			///@return 查詢是否成功，“0”表示成功，非“0”表示出錯，此時使用者可以呼叫GetApiLastError()來獲取錯誤程式碼
			///@param query_param 需要查詢的訂單相關篩選條件，其中合約程式碼可以為空，則預設所有存在的合約程式碼，如果不為空，請不帶空格，並以'\0'結尾，其中起始時間格式為YYYYMMDDHHMMSSsss，為0則預設當前交易日0點，結束時間格式為YYYYMMDDHHMMSSsss，為0則預設當前時間
			///@param session_id 資金賬戶對應的session_id，登入時得到
			///@param request_id 用於使用者定位查詢響應的ID，由使用者自定義
			///@remark 該方法支援分時段查詢，如果股票程式碼為空，則預設查詢時間段內的所有報單，否則查詢時間段內所有跟股票程式碼相關的報單，此函式查詢出的結果可能對應多個查詢結果響應。此函式不建議輪詢使用，當報單量過多時，容易造成使用者線路擁堵，導致api斷線
			virtual int QueryOrders(const XTPQueryOrderReq *query_param, uint64_t session_id, int request_id) = 0;

			///根據委託編號請求查詢相關成交
			///@return 查詢是否成功，“0”表示成功，非“0”表示出錯，此時使用者可以呼叫GetApiLastError()來獲取錯誤程式碼
			///@param order_xtp_id 需要查詢的委託編號，即InsertOrder()成功時返回的order_xtp_id
			///@param session_id 資金賬戶對應的session_id，登入時得到
			///@param request_id 用於使用者定位查詢響應的ID，由使用者自定義
			///@remark 此函式查詢出的結果可能對應多個查詢結果響應
			virtual int QueryTradesByXTPID(const uint64_t order_xtp_id, uint64_t session_id, int request_id) = 0;

			///請求查詢已成交
			///@return 查詢是否成功，“0”表示成功，非“0”表示出錯，此時使用者可以呼叫GetApiLastError()來獲取錯誤程式碼
			///@param query_param 需要查詢的成交回報篩選條件，其中合約程式碼可以為空，則預設所有存在的合約程式碼，如果不為空，請不帶空格，並以'\0'結尾，其中起始時間格式為YYYYMMDDHHMMSSsss，為0則預設當前交易日0點，結束時間格式為YYYYMMDDHHMMSSsss，為0則預設當前時間
			///@param session_id 資金賬戶對應的session_id,登入時得到
			///@param request_id 用於使用者定位查詢響應的ID，由使用者自定義
			///@remark 該方法支援分時段查詢，如果股票程式碼為空，則預設查詢時間段內的所有成交回報，否則查詢時間段內所有跟股票程式碼相關的成交回報，此函式查詢出的結果可能對應多個查詢結果響應。此函式不建議輪詢使用，當報單量過多時，容易造成使用者線路擁堵，導致api斷線
			virtual int QueryTrades(XTPQueryTraderReq *query_param, uint64_t session_id, int request_id) = 0;

			///請求查詢投資者持倉
			///@return 查詢是否成功，“0”表示成功，非“0”表示出錯，此時使用者可以呼叫GetApiLastError()來獲取錯誤程式碼
			///@param ticker 需要查詢的持倉合約程式碼，可以為空，如果不為空，請不帶空格，並以'\0'結尾
			///@param session_id 資金賬戶對應的session_id,登入時得到
			///@param request_id 用於使用者定位查詢響應的ID，由使用者自定義
			///@remark 該方法如果使用者提供了合約程式碼，則會查詢此合約的持倉資訊，如果合約程式碼為空，則預設查詢所有持倉資訊
			virtual int QueryPosition(const char *ticker, uint64_t session_id, int request_id) = 0;

			///請求查詢資產
			///@return 查詢是否成功，“0”表示成功，非“0”表示出錯，此時使用者可以呼叫GetApiLastError()來獲取錯誤程式碼
			///@param session_id 資金賬戶對應的session_id,登入時得到
			///@param request_id 用於使用者定位查詢響應的ID，由使用者自定義
			virtual int QueryAsset(uint64_t session_id, int request_id) = 0;

			///請求查詢分級基金
			///@return 查詢是否成功，“0”表示成功，非“0”表示出錯，此時使用者可以呼叫GetApiLastError()來獲取錯誤程式碼
			///@param query_param 需要查詢的分級基金篩選條件，其中母基金程式碼可以為空，則預設所有存在的母基金，如果不為空，請不帶空格，並以'\0'結尾，其中交易市場不能為空
			///@param session_id 資金賬戶對應的session_id,登入時得到
			///@param request_id 用於使用者定位查詢響應的ID，由使用者自定義
			///@remark 此函式查詢出的結果可能對應多個查詢結果響應
			virtual int QueryStructuredFund(XTPQueryStructuredFundInfoReq *query_param, uint64_t session_id, int request_id) = 0;

			///資金劃撥請求
			///@return 資金劃撥訂單在XTP系統中的ID,如果為‘0’表示訊息傳送失敗，此時使用者可以呼叫GetApiLastError()來獲取錯誤程式碼，非“0”表示訊息傳送成功，使用者需要記錄下返回的serial_id，它保證一個交易日內唯一，不同的交易日不保證唯一性
			///@param fund_transfer 資金劃撥的請求資訊
			///@param session_id 資金賬戶對應的session_id,登入時得到
			///@remark 此函式支援一號兩中心節點之間的資金劃撥，注意資金劃撥的方向。
			virtual uint64_t FundTransfer(XTPFundTransferReq *fund_transfer, uint64_t session_id) = 0;

			///請求查詢資金劃撥
			///@return 查詢是否成功，“0”表示成功，非“0”表示出錯，此時使用者可以呼叫GetApiLastError()來獲取錯誤程式碼
			///@param query_param 需要查詢的資金劃撥訂單篩選條件，其中serial_id可以為0，則預設所有資金劃撥訂單，如果不為0，則請求特定的資金劃撥訂單
			///@param session_id 資金賬戶對應的session_id,登入時得到
			///@param request_id 用於使用者定位查詢響應的ID，由使用者自定義
			virtual int QueryFundTransfer(XTPQueryFundTransferLogReq *query_param, uint64_t session_id, int request_id) = 0;

			///請求查詢ETF清單檔案
			///@return 查詢是否成功，“0”表示成功，非“0”表示出錯，此時使用者可以呼叫GetApiLastError()來獲取錯誤程式碼
			///@param query_param 需要查詢的ETF清單檔案的篩選條件，其中合約程式碼可以為空，則預設所有存在的ETF合約程式碼，market欄位也可以為初始值，則預設所有市場的ETF合約
			///@param session_id 資金賬戶對應的session_id,登入時得到
			///@param request_id 用於使用者定位查詢響應的ID，由使用者自定義
			virtual int QueryETF(XTPQueryETFBaseReq *query_param, uint64_t session_id, int request_id) = 0;

			///請求查詢ETF股票籃
			///@return 查詢是否成功，“0”表示成功，非“0”表示出錯，此時使用者可以呼叫GetApiLastError()來獲取錯誤程式碼
			///@param query_param 需要查詢股票籃的的ETF合約，其中合約程式碼不可以為空，market欄位也必須指定
			///@param session_id 資金賬戶對應的session_id,登入時得到
			///@param request_id 用於使用者定位查詢響應的ID，由使用者自定義
			virtual int QueryETFTickerBasket(XTPQueryETFComponentReq *query_param, uint64_t session_id, int request_id) = 0;

			///請求查詢今日新股申購資訊列表
			///@return 查詢是否成功，“0”表示成功，非“0”表示出錯，此時使用者可以呼叫GetApiLastError()來獲取錯誤程式碼
			///@param session_id 資金賬戶對應的session_id,登入時得到
			///@param request_id 用於使用者定位查詢響應的ID，由使用者自定義
			virtual int QueryIPOInfoList(uint64_t session_id, int request_id) = 0;

			///請求查詢使用者新股申購額度資訊
			///@return 查詢是否成功，“0”表示成功，非“0”表示出錯，此時使用者可以呼叫GetApiLastError()來獲取錯誤程式碼
			///@param session_id 資金賬戶對應的session_id,登入時得到
			///@param request_id 用於使用者定位查詢響應的ID，由使用者自定義
			virtual int QueryIPOQuotaInfo(uint64_t session_id, int request_id) = 0;

			///請求查詢期權合約
			///@return 查詢是否成功，“0”表示成功，非“0”表示出錯，此時使用者可以呼叫GetApiLastError()來獲取錯誤程式碼
			///@param query_param 需要查詢的期權合約的篩選條件，可以為NULL（為NULL表示查詢所有的期權合約）
			///@param session_id 資金賬戶對應的session_id,登入時得到
			///@param request_id 用於使用者定位查詢響應的ID，由使用者自定義
			virtual int QueryOptionAuctionInfo(XTPQueryOptionAuctionInfoReq *query_param, uint64_t session_id, int request_id) = 0;

			///融資融券業務中現金直接還款請求
			///@return 現金直接還款訂單在XTP系統中的ID,如果為‘0’表示訊息傳送失敗，此時使用者可以呼叫GetApiLastError()來獲取錯誤程式碼，非“0”表示訊息傳送成功，使用者需要記錄下返回的serial_id，它保證一個交易日內唯一，不同的交易日不保證唯一性
			///@param amount 現金還款的金額
			///@param session_id 資金賬戶對應的session_id,登入時得到
			virtual uint64_t CreditCashRepay(double amount, uint64_t session_id) = 0;

			///請求查詢融資融券業務中的現金直接還款報單
			///@return 查詢是否成功，“0”表示成功，非“0”表示出錯，此時使用者可以呼叫GetApiLastError()來獲取錯誤程式碼
			///@param session_id 資金賬戶對應的session_id,登入時得到
			///@param request_id 用於使用者定位查詢響應的ID，由使用者自定義
			virtual int QueryCreditCashRepayInfo(uint64_t session_id, int request_id) = 0;


			///請求查詢信用賬戶特有資訊，除資金賬戶以外的資訊
			///@return 查詢是否成功，“0”表示成功，非“0”表示出錯，此時使用者可以呼叫GetApiLastError()來獲取錯誤程式碼
			///@param session_id 資金賬戶對應的session_id,登入時得到
			///@param request_id 用於使用者定位查詢響應的ID，由使用者自定義
			virtual int QueryCreditFundInfo(uint64_t session_id, int request_id) = 0;

			///請求查詢信用賬戶負債合約資訊
			///@return 查詢是否成功，“0”表示成功，非“0”表示出錯，此時使用者可以呼叫GetApiLastError()來獲取錯誤程式碼
			///@param session_id 資金賬戶對應的session_id,登入時得到
			///@param request_id 用於使用者定位查詢響應的ID，由使用者自定義
			virtual int QueryCreditDebtInfo(uint64_t session_id, int request_id) = 0;

			///請求查詢指定證券負債未還資訊
			///@return 查詢是否成功，“0”表示成功，非“0”表示出錯，此時使用者可以呼叫GetApiLastError()來獲取錯誤程式碼
			///@param query_param 需要查詢的指定證券，篩選條件中ticker可以全填0，如果不為0，請不帶空格，並以'\0'結尾
			///@param session_id 資金賬戶對應的session_id,登入時得到
			///@param request_id 用於使用者定位查詢響應的ID，由使用者自定義
			virtual int QueryCreditTickerDebtInfo(XTPClientQueryCrdDebtStockReq *query_param, uint64_t session_id, int request_id) = 0;

			///請求查詢信用賬戶待還資金資訊
			///@return 查詢是否成功，“0”表示成功，非“0”表示出錯，此時使用者可以呼叫GetApiLastError()來獲取錯誤程式碼
			///@param session_id 資金賬戶對應的session_id,登入時得到
			///@param request_id 用於使用者定位查詢響應的ID，由使用者自定義
			virtual int QueryCreditAssetDebtInfo(uint64_t session_id, int request_id) = 0;

			///請求查詢信用賬戶可融券頭寸資訊
			///@return 查詢是否成功，“0”表示成功，非“0”表示出錯，此時使用者可以呼叫GetApiLastError()來獲取錯誤程式碼
			///@param query_param 需要查詢的證券，篩選條件中ticker可以全填0，如果不為0，請不帶空格，並以'\0'結尾
			///@param session_id 資金賬戶對應的session_id,登入時得到
			///@param request_id 用於使用者定位查詢響應的ID，由使用者自定義
			virtual int QueryCreditTickerAssignInfo(XTPClientQueryCrdPositionStockReq *query_param, uint64_t session_id, int request_id) = 0;

			////融資融券業務中請求查詢指定證券的餘券
			///@return 查詢是否成功，“0”表示成功，非“0”表示出錯，此時使用者可以呼叫GetApiLastError()來獲取錯誤程式碼
			///@param query_param 需要查詢的餘券資訊，不可以為空，需要明確指定
			///@param session_id 資金賬戶對應的session_id,登入時得到
			///@param request_id 用於使用者定位查詢響應的ID，由使用者自定義
			///@remark 該方法中使用者必須提供了證券程式碼和所在市場
			virtual int QueryCreditExcessStock(XTPClientQueryCrdSurplusStkReqInfo *query_param, uint64_t session_id, int request_id) = 0;


		protected:
			~TraderApi() {};
		};

			}
}

#ifndef WINDOWS
#if __GNUC__ >= 4
#pragma GCC visibility pop
#endif
#endif


#endif
