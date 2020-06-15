#ifndef ITAP_TRADE_API_H
#define ITAP_TRADE_API_H

#include "iTapTradeAPIDataType.h"
//#include "TapProtocol.h"

#if defined WIN32 || defined WIN64
#define TAP_CDECL __cdecl
#define TAP_DLLEXPORT __declspec(dllexport)
#else
#define TAP_CDECL
#define TAP_DLLEXPORT
#endif
//TapTradeAPI.h
//檔案定義了TapTradeAPI提供給開發者的對外介面、函式和回撥介面。

//TapTradeAPI 的回撥通知介面。
namespace ITapTrade
{
    class ITapTradeAPINotify
    {
    public:
        /**
        * @brief 連線成功回撥通知
        * @ingroup G_T_Login
        */
        virtual void TAP_CDECL OnConnect() = 0;
        /**
        * @brief    系統登入過程回撥。
        * @details    此函式為Login()登入函式的回撥，呼叫Login()成功後建立了鏈路連線，然後API將向伺服器傳送登入認證資訊，
        *            登入期間的資料傳送情況和登入的回饋資訊傳遞到此回撥函式中。
        * @param[in] errorCode 返回錯誤碼,0表示成功。
        * @param[in] loginRspInfo 登陸應答資訊，如果errorCode!=0，則loginRspInfo=NULL。
        * @attention    該回調返回成功，說明使用者登入成功。但是不代表API準備完畢。
        * @ingroup G_T_Login
        */
        virtual void TAP_CDECL OnRspLogin(ITapTrade::TAPIINT32 errorCode, const ITapTrade::TapAPITradeLoginRspInfo *loginRspInfo) = 0;
        /**
        * @brief    二次認證聯絡方式通知。
        * @details    登入完成後，如果需要二次認證（9.2.7後臺），會收到聯絡方式的通知，可以選擇通知訊息的一個聯絡方式（郵箱或者電話）
        *            請求傳送二次認證授權碼（RequestVertificateCode）。
        * @param[in] errorCode 返回錯誤碼,0表示成功。如果賬戶沒有繫結二次認證聯絡方式，則返回10016錯誤。
        * @param[in] isLast,標識是否是最後一條聯絡資訊。
        * @param[in]  認證方式資訊，如果errorCode!=0，則ContactInfo為空。
        * @attention    該回調返回成功，說明需要二次認證，並且需要選擇一個聯絡方式然後呼叫RequestVertificateCode。
        * @ingroup G_T_Login
        */
        virtual void TAP_CDECL OnRtnContactInfo(ITapTrade::TAPIINT32 errorCode, ITapTrade::TAPIYNFLAG isLast, const ITapTrade::TAPISTR_40 ContactInfo) = 0;

        /**
        * @brief    請求傳送二次認證碼應答。
        * @details    請求獲取二次認證授權碼，後臺傳送郵件或者簡訊，並給出應答，包含傳送序號以及認證碼有效期。
        *            
        * @param[in] sessionID 請求二次認證碼會話ID。
        * @param[in]  errorCode 如果沒有繫結聯絡，返回10016錯誤.
        * @param[in]  rsp二次認證碼有效期，以秒返回，在二次認證有效期內，可以重複設定二次認證碼，但是不能再重新申請二次認證碼。
        * @attention    該回調返回成功，說明需要二次認證，並且需要選擇一個聯絡方式然後呼叫RequestVertificateCode。
        * @ingroup G_T_Login
        */
        virtual void TAP_CDECL OnRspRequestVertificateCode(ITapTrade::TAPIUINT32 sessionID,ITapTrade::TAPIINT32 errorCode, const TapAPIRequestVertificateCodeRsp *rsp) = 0;

        /**
        * @brief    API到期提醒回撥
        * @details    此函式為Login()登入成功後，如果到期日與當前日期小於30天，則進行回撥提醒。
        * @param[in] date 返回API授權到期日。
        * @param[in] days 返回還有幾天授權到期。
        * @attention    該函式回撥，則說明授權在一個月之內到期。否則不產生該回調。
        * @ingroup G_T_Login
        */
        virtual void TAP_CDECL OnExpriationDate(ITapTrade::TAPIDATE date, int days) = 0;

        /**
        * @brief    通知使用者API準備就緒。
        * @details    只有使用者回撥收到此就緒通知時才能進行後續的各種行情資料查詢操作。\n
        *            此回撥函式是API能否正常工作的標誌。
        * @attention 就緒後才可以進行後續正常操作
        * @ingroup G_T_Login
        */
        virtual void TAP_CDECL OnAPIReady(ITapTrade::TAPIINT32 errorCode) = 0;
        /**
        * @brief    API和服務失去連線的回撥
        * @details    在API使用過程中主動或者被動與伺服器服務失去連線後都會觸發此回撥通知使用者與伺服器的連線已經斷開。
        * @param[in] reasonCode 斷開原因程式碼。
        * @ingroup G_T_Disconnect
        */
        virtual void TAP_CDECL OnDisconnect(ITapTrade::TAPIINT32 reasonCode) = 0;
        /**
        * @brief 通知使用者密碼修改結果
        * @param[in] sessionID 修改密碼的會話ID,和ChangePassword返回的會話ID對應。
        * @param[in] errorCode 返回錯誤碼，0表示成功。
        * @ingroup G_T_UserInfo
        */
        virtual void TAP_CDECL OnRspChangePassword(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode) = 0;

        /**
        * @brief 認證賬戶密碼反饋
        * @param[in] sessionID 修改密碼的會話ID,和AuthPassword返回的會話ID對應。
        * @param[in] errorCode 返回錯誤碼，0表示成功。
        * @ingroup G_T_UserInfo
        */
        virtual void TAP_CDECL OnRspAuthPassword(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode) = 0;

        /**
        * @brief    返回系統交易日期和當天LME到期日
        * @param[in] sessionID 請求的會話ID；
        * @param[in] errorCode 錯誤碼。0 表示成功。
        * @param[in] info 指向返回的資訊結構體。當errorCode不為0時，info為空。
        * @attention 不要修改和刪除info所指示的資料；函式呼叫結束，引數不再有效。
        * @ingroup G_T_UserRight
        */

        virtual void TAP_CDECL OnRspQryTradingDate(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, const ITapTrade::TapAPITradingCalendarQryRsp *info) = 0;
        /**
        * @brief 設定使用者預留資訊反饋
        * @param[in] sessionID 設定使用者預留資訊的會話ID
        * @param[in] errorCode 返回錯誤碼，0表示成功。
        * @param[in] info 指向返回的資訊結構體。當errorCode不為0時，info為空。
        * @attention 不要修改和刪除info所指示的資料；函式呼叫結束，引數不再有效。
        * @note 該介面暫未實現
        * @ingroup G_T_UserInfo
        */
        virtual void TAP_CDECL OnRspSetReservedInfo(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, const ITapTrade::TAPISTR_50 info) = 0;


        /**
        * @brief    返回使用者資訊
        * @details    此回撥介面向用戶返回查詢的資金賬號的詳細資訊。使用者有必要將得到的賬號編號儲存起來，然後在後續的函式呼叫中使用。
        * @param[in] sessionID 請求的會話ID；
        * @param[in] errorCode 錯誤碼。0 表示成功。
        * @param[in] isLast 標示是否是最後一批資料；
        * @param[in] info 指向返回的資訊結構體。當errorCode不為0時，info為空。
        * @attention 不要修改和刪除info所指示的資料；函式呼叫結束，引數不再有效。
        * @ingroup G_T_AccountInfo
        */
        virtual void TAP_CDECL OnRspQryAccount(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIUINT32 errorCode, ITapTrade::TAPIYNFLAG isLast, const ITapTrade::TapAPIAccountInfo *info) = 0;
        /**
        * @brief 返回資金賬戶的資金資訊
        * @param[in] sessionID 請求的會話ID；
        * @param[in] errorCode 錯誤碼。0 表示成功。
        * @param[in] isLast     標示是否是最後一批資料；
        * @param[in] info        指向返回的資訊結構體。當errorCode不為0時，info為空。
        * @attention 不要修改和刪除info所指示的資料；函式呼叫結束，引數不再有效。
        * @ingroup G_T_AccountDetails
        */
        virtual void TAP_CDECL OnRspQryFund(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, ITapTrade::TAPIYNFLAG isLast, const ITapTrade::TapAPIFundData *info) = 0;
        /**
        * @brief    使用者資金變化通知
        * @details    使用者的委託成交後會引起資金資料的變化，因此需要向用戶實時反饋。
        * @param[in] info        指向返回的資訊結構體。當errorCode不為0時，info為空。
        * @note 如果不關注此項內容，可以設定Login時的NoticeIgnoreFlag以遮蔽。
        * @attention 不要修改和刪除info所指示的資料；函式呼叫結束，引數不再有效。
        * @ingroup G_T_AccountDetails
        */
        virtual void TAP_CDECL OnRtnFund(const ITapTrade::TapAPIFundData *info) = 0;
        /**
        * @brief 返回系統中的交易所資訊
        * @param[in] sessionID 請求的會話ID；
        * @param[in] errorCode 錯誤碼。0 表示成功。
        * @param[in] isLast     標示是否是最後一批資料；
        * @param[in] info        指向返回的資訊結構體。當errorCode不為0時，info為空。
        * @attention 不要修改和刪除info所指示的資料；函式呼叫結束，引數不再有效。
        * @ingroup G_T_TradeSystem
        */
        virtual void TAP_CDECL OnRspQryExchange(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, ITapTrade::TAPIYNFLAG isLast, const ITapTrade::TapAPIExchangeInfo *info) = 0;
        /**
        * @brief    返回系統中品種資訊
        * @details    此回撥介面用於向用戶返回得到的所有品種資訊。
        * @param[in] sessionID 請求的會話ID，和GetAllCommodities()函式返回對應；
        * @param[in] errorCode 錯誤碼。0 表示成功。
        * @param[in] isLast     標示是否是最後一批資料；
        * @param[in] info        指向返回的資訊結構體。當errorCode不為0時，info為空。
        * @attention 不要修改和刪除info所指示的資料；函式呼叫結束，引數不再有效。
        * @ingroup G_T_Commodity
        */
        virtual void TAP_CDECL OnRspQryCommodity(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, ITapTrade::TAPIYNFLAG isLast, const ITapTrade::TapAPICommodityInfo *info) = 0;
        /**
        * @brief 返回系統中合約資訊
        * @param[in] sessionID 請求的會話ID；
        * @param[in] errorCode 錯誤碼。0 表示成功。
        * @param[in] isLast     標示是否是最後一批資料；
        * @param[in] info        指向返回的資訊結構體。當errorCode不為0時，info為空。
        * @attention 不要修改和刪除info所指示的資料；函式呼叫結束，引數不再有效。
        * @ingroup G_T_Contract
        */
        virtual void TAP_CDECL OnRspQryContract(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, ITapTrade::TAPIYNFLAG isLast, const ITapTrade::TapAPITradeContractInfo *info) = 0;
        /**
        * @brief    返回新增合約資訊
        * @details    向用戶推送新的合約。主要用來處理在交易時間段中伺服器添加了新合約時，向用戶傳送這個合約的資訊。
        * @param[in] info        指向返回的資訊結構體。當errorCode不為0時，info為空。
        * @attention 不要修改和刪除info所指示的資料；函式呼叫結束，引數不再有效。
        * @ingroup G_T_Contract
        */
        virtual void TAP_CDECL OnRtnContract(const ITapTrade::TapAPITradeContractInfo *info) = 0;
                /**
        * @brief    訂單操作應答
        * @details    下單、撤單、改單應答。下單都會有次應答回撥，如果下單請求結構中沒有填寫合約或者資金賬號，則僅返回錯誤號。
                 * 撤單、改單錯誤由應答和OnRtnOrder，成功僅返回OnRtnOrder回撥。
                 * sessionID標識請求對應的sessionID，以便確定該筆應答對應的請求。
                 * 
        * @param[in] sessionID 請求的會話ID；
        * @param[in] errorCode 錯誤碼。0 表示成功。
        * @param[in] info 訂單應答具體型別，包含訂單操作型別和訂單資訊指標。
                 * 訂單資訊指標部分情況下可能為空，如果為空，可以通過SessiuonID找到對應請求獲取請求型別。
        * @attention 不要修改和刪除info所指示的資料；函式呼叫結束，引數不再有效。
        * @ingroup G_T_TradeActions
        */
        virtual void TAP_CDECL OnRspOrderAction(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, const ITapTrade::TapAPIOrderActionRsp *info) = 0;
        /**
        * @brief 返回新委託。新下的或者其他地方下的推送過來的。
        * @details    伺服器接收到客戶下的委託內容後就會儲存起來等待觸發，同時向用戶回饋一個
        *            新委託資訊說明伺服器正確處理了使用者的請求，返回的資訊中包含了全部的委託資訊，
        *            同時有一個用來標示此委託的委託號。
        * @param[in] info 指向返回的資訊結構體。當errorCode不為0時，info為空。
        * @note 如果不關注此項內容，可以設定Login時的NoticeIgnoreFlag以遮蔽。
        * @attention 不要修改和刪除info所指示的資料；函式呼叫結束，引數不再有效。
        * @ingroup G_T_TradeActions
        */
        virtual void TAP_CDECL OnRtnOrder(const ITapTrade::TapAPIOrderInfoNotice *info) = 0;
        /**
        * @brief    返回查詢的委託資訊
        * @details    返回使用者查詢的委託的具體資訊。
        * @param[in] sessionID 請求的會話ID；
        * @param[in] errorCode 錯誤碼。0 表示成功。
        * @param[in] isLast 標示是否是最後一批資料；
        * @param[in] info 指向返回的資訊結構體。當errorCode不為0時，info為空。
        * @attention 不要修改和刪除info所指示的資料；函式呼叫結束，引數不再有效。
        * @ingroup G_T_TradeInfo
        */
        virtual void TAP_CDECL OnRspQryOrder(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, ITapTrade::TAPIYNFLAG isLast, const ITapTrade::TapAPIOrderInfo *info) = 0;
        /**
        * @brief 返回查詢的委託變化流程資訊
        * @param[in] sessionID 請求的會話ID；
        * @param[in] errorCode 錯誤碼，當errorCode==0時，info指向返回的委託變化流程結構體，不然為NULL；
        * @param[in] isLast 標示是否是最後一批資料；
        * @param[in] info 返回的委託變化流程指標。
        * @attention 不要修改和刪除info所指示的資料；函式呼叫結束，引數不再有效。
        * @ingroup G_T_TradeInfo
        */
        virtual void TAP_CDECL OnRspQryOrderProcess(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, ITapTrade::TAPIYNFLAG isLast, const ITapTrade::TapAPIOrderInfo *info) = 0;
        /**
        * @brief 返回查詢的成交資訊
        * @param[in] sessionID 請求的會話ID；
        * @param[in] errorCode 錯誤碼。0 表示成功。
        * @param[in] isLast     標示是否是最後一批資料；
        * @param[in] info        指向返回的資訊結構體。當errorCode不為0時，info為空。
        * @attention 不要修改和刪除info所指示的資料；函式呼叫結束，引數不再有效。
        * @ingroup G_T_TradeInfo
        */
        virtual void TAP_CDECL OnRspQryFill(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, ITapTrade::TAPIYNFLAG isLast, const ITapTrade::TapAPIFillInfo *info) = 0;
        /**
        * @brief    推送來的成交資訊
        * @details    使用者的委託成交後將向用戶推送成交資訊。
        * @param[in] info        指向返回的資訊結構體。當errorCode不為0時，info為空。
        * @note 如果不關注此項內容，可以設定Login時的NoticeIgnoreFlag以遮蔽。
        * @attention 不要修改和刪除info所指示的資料；函式呼叫結束，引數不再有效。
        * @ingroup G_T_TradeActions
        */
        virtual void TAP_CDECL OnRtnFill(const ITapTrade::TapAPIFillInfo *info) = 0;
        /**
        * @brief 返回查詢的持倉
        * @param[in] sessionID 請求的會話ID；
        * @param[in] errorCode 錯誤碼。0 表示成功。
        * @param[in] isLast     標示是否是最後一批資料；
        * @param[in] info        指向返回的資訊結構體。當errorCode不為0時，info為空。
        * @attention 不要修改和刪除info所指示的資料；函式呼叫結束，引數不再有效。
        * @ingroup G_T_TradeInfo
        */
        virtual void TAP_CDECL OnRspQryPosition(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, ITapTrade::TAPIYNFLAG isLast, const ITapTrade::TapAPIPositionInfo *info) = 0;
        /**
        * @brief 持倉變化推送通知
        * @param[in] info        指向返回的資訊結構體。當errorCode不為0時，info為空。
        * @note 如果不關注此項內容，可以設定Login時的NoticeIgnoreFlag以遮蔽。
        * @attention 不要修改和刪除info所指示的資料；函式呼叫結束，引數不再有效。
        * @ingroup G_T_TradeActions
        */
        virtual void TAP_CDECL OnRtnPosition(const ITapTrade::TapAPIPositionInfo *info) = 0;
        /**
        * @brief 返回查詢的持倉彙總
        * @param[in] sessionID 請求的會話ID；
        * @param[in] errorCode 錯誤碼。0 表示成功。
        * @param[in] isLast     標示是否是最後一批資料；
        * @param[in] info        指向返回的資訊結構體。當errorCode不為0時，info為空。
        * @attention 不要修改和刪除info所指示的資料；函式呼叫結束，引數不再有效。
        * @ingroup G_T_TradeInfo
        */
        virtual void TAP_CDECL OnRspQryPositionSummary(TAPIUINT32 sessionID, TAPIINT32 errorCode, TAPIYNFLAG isLast, const TapAPIPositionSummary *info) = 0;
        
        /**
        * @brief 持倉彙總變化推送通知
        * @param[in] info        指向返回的資訊結構體。當errorCode不為0時，info為空。
        * @note 如果不關注此項內容，可以設定Login時的NoticeIgnoreFlag以遮蔽。
        * @attention 不要修改和刪除info所指示的資料；函式呼叫結束，引數不再有效。
        * @ingroup G_T_TradeActions
        */
        virtual void TAP_CDECL OnRtnPositionSummary(const TapAPIPositionSummary *info) = 0;
        /**
        * @brief 持倉盈虧通知
        * @param[in] info        指向返回的資訊結構體。當errorCode不為0時，info為空。
        * @note 如果不關注此項內容，可以設定Login時的NoticeIgnoreFlag以遮蔽。
        * @attention 不要修改和刪除info所指示的資料；函式呼叫結束，引數不再有效。
        * @ingroup G_T_TradeActions
        */
        virtual void TAP_CDECL OnRtnPositionProfit(const ITapTrade::TapAPIPositionProfitNotice *info) = 0;


        /**
        * @brief 返回系統中的幣種資訊
        * @param[in] sessionID 請求的會話ID；
        * @param[in] errorCode 錯誤碼。0 表示成功。
        * @param[in] isLast     標示是否是最後一批資料；
        * @param[in] info        指向返回的資訊結構體。當errorCode不為0時，info為空。
        * @attention 不要修改和刪除info所指示的資料；函式呼叫結束，引數不再有效。
        * @ingroup G_T_TradeSystem
        */
        virtual void TAP_CDECL OnRspQryCurrency(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, ITapTrade::TAPIYNFLAG isLast, const ITapTrade::TapAPICurrencyInfo *info) = 0;

        /**
        * @brief    交易訊息通知
        * @details    返回查詢的使用者資金狀態資訊。資訊說明了使用者的資金狀態，使用者需要仔細檢視這些資訊。
        * @param[in] sessionID 請求的會話ID；
        * @param[in] errorCode 錯誤碼。0 表示成功。
        * @param[in] isLast     標示是否是最後一批資料；
        * @param[in] info        指向返回的資訊結構體。當errorCode不為0時，info為空。
        * @attention 不要修改和刪除info所指示的資料；函式呼叫結束，引數不再有效。
        * @ingroup G_T_AccountDetails
        */
        virtual void TAP_CDECL OnRspQryTradeMessage(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, ITapTrade::TAPIYNFLAG isLast, const ITapTrade::TapAPITradeMessage *info) = 0;
        /**
        * @brief    交易訊息通知
        * @details    使用者在交易過程中可能因為資金、持倉、平倉的狀態變動使賬戶處於某些危險狀態，或者某些重要的資訊需要向用戶通知。
        * @param[in] info        指向返回的資訊結構體。當errorCode不為0時，info為空。
        * @attention 不要修改和刪除info所指示的資料；函式呼叫結束，引數不再有效。
        * @ingroup G_T_AccountDetails
        */
        virtual void TAP_CDECL OnRtnTradeMessage(const ITapTrade::TapAPITradeMessage *info) = 0;
        /**
        * @brief 歷史委託查詢應答
        * @param[in] sessionID 請求的會話ID；
        * @param[in] errorCode 錯誤碼。0 表示成功。
        * @param[in] isLast     標示是否是最後一批資料
        * @param[in] info        指向返回的資訊結構體。當errorCode不為0時，info為空。
        * @attention 不要修改和刪除info所指示的資料；函式呼叫結束，引數不再有效。
        * @ingroup G_T_HisInfo
        */
        virtual void TAP_CDECL OnRspQryHisOrder(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, ITapTrade::TAPIYNFLAG isLast, const ITapTrade::TapAPIHisOrderQryRsp *info) = 0;
        /**
        * @brief 歷史委託流程查詢應答
        * @param[in] sessionID 請求的會話ID；
        * @param[in] errorCode 錯誤碼。0 表示成功。
        * @param[in] isLast     標示是否是最後一批資料
        * @param[in] info        指向返回的資訊結構體。當errorCode不為0時，info為空。
        * @attention 不要修改和刪除info所指示的資料；函式呼叫結束，引數不再有效。
        * @ingroup G_T_HisInfo
        */
        virtual void TAP_CDECL OnRspQryHisOrderProcess(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, ITapTrade::TAPIYNFLAG isLast, const ITapTrade::TapAPIHisOrderProcessQryRsp *info) = 0;
        /**
        * @brief 歷史成交查詢應答
        * @param[in] sessionID 請求的會話ID；
        * @param[in] errorCode 錯誤碼。0 表示成功。
        * @param[in] isLast     標示是否是最後一批資料
        * @param[in] info        指向返回的資訊結構體。當errorCode不為0時，info為空。
        * @attention 不要修改和刪除info所指示的資料；函式呼叫結束，引數不再有效。
        * @ingroup G_T_HisInfo
        */
        virtual void TAP_CDECL OnRspQryHisMatch(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, ITapTrade::TAPIYNFLAG isLast, const ITapTrade::TapAPIHisMatchQryRsp *info) = 0;
        /**
        * @brief 歷史持倉查詢應答
        * @param[in] sessionID 請求的會話ID；
        * @param[in] errorCode 錯誤碼。0 表示成功。
        * @param[in] isLast     標示是否是最後一批資料
        * @param[in] info        指向返回的資訊結構體。當errorCode不為0時，info為空。
        * @attention 不要修改和刪除info所指示的資料；函式呼叫結束，引數不再有效。
        * @ingroup G_T_HisInfo
        */
        virtual void TAP_CDECL OnRspQryHisPosition(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, ITapTrade::TAPIYNFLAG isLast, const ITapTrade::TapAPIHisPositionQryRsp *info) = 0;
        /**
        * @brief 歷史交割查詢應答
        * @param[in] sessionID 請求的會話ID；
        * @param[in] errorCode 錯誤碼。0 表示成功。
        * @param[in] isLast     標示是否是最後一批資料
        * @param[in] info        指向返回的資訊結構體。當errorCode不為0時，info為空。
        * @attention 不要修改和刪除info所指示的資料；函式呼叫結束，引數不再有效。
        * @ingroup G_T_HisInfo
        */
        virtual void TAP_CDECL OnRspQryHisDelivery(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, ITapTrade::TAPIYNFLAG isLast, const ITapTrade::TapAPIHisDeliveryQryRsp *info) = 0;
        /**
        * @brief 資金調整查詢應答
        * @param[in] sessionID 請求的會話ID；
        * @param[in] errorCode 錯誤碼。0 表示成功。
        * @param[in] isLast     標示是否是最後一批資料
        * @param[in] info        指向返回的資訊結構體。當errorCode不為0時，info為空。
        * @attention 不要修改和刪除info所指示的資料；函式呼叫結束，引數不再有效。
        * @ingroup G_T_HisInfo
        */
        virtual void TAP_CDECL OnRspQryAccountCashAdjust(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, ITapTrade::TAPIYNFLAG isLast, const ITapTrade::TapAPIAccountCashAdjustQryRsp *info) = 0;
        /**
        * @brief 查詢使用者賬單應答 Add:2013.12.11
        * @param[in] sessionID 請求的會話ID；
        * @param[in] errorCode 錯誤碼。0 表示成功。
        * @param[in] info        指向返回的資訊結構體。當errorCode不為0時，info為空。
        * @attention 不要修改和刪除info所指示的資料；函式呼叫結束，引數不再有效。
        * @ingroup G_T_Bill
        */
        virtual void TAP_CDECL OnRspQryBill(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, ITapTrade::TAPIYNFLAG isLast, const ITapTrade::TapAPIBillQryRsp *info) = 0;
        /**
        * @brief 查詢賬戶手續費計算引數 Add:2017.01.14
        * @param[in] sessionID 請求的會話ID；
        * @param[in] errorCode 錯誤碼。0 表示成功。
        * @param[in] info        指向返回的資訊結構體。當errorCode不為0時，info為空。
        * @attention 不要修改和刪除info所指示的資料；函式呼叫結束，引數不再有效。
        * @ingroup G_T_Rent
        */
        virtual void TAP_CDECL OnRspQryAccountFeeRent(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, ITapTrade::TAPIYNFLAG isLast, const ITapTrade::TapAPIAccountFeeRentQryRsp *info) = 0;
        /**
        * @brief 查詢賬戶保證金計算引數 Add:2017.01.14
        * @param[in] sessionID 請求的會話ID；
        * @param[in] errorCode 錯誤碼。0 表示成功。
        * @param[in] info        指向返回的資訊結構體。當errorCode不為0時，info為空。
        * @attention 不要修改和刪除info所指示的資料；函式呼叫結束，引數不再有效。
        * @ingroup G_T_Rent
        */
        virtual void TAP_CDECL OnRspQryAccountMarginRent(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, ITapTrade::TAPIYNFLAG isLast, const ITapTrade::TapAPIAccountMarginRentQryRsp *info) = 0;

        /**
        * @brief 港交所做市商雙邊報價應答 Add:2017.08.29
        * @param[in] sessionID 請求的會話ID；
        * @param[in] errorCode 錯誤碼。0 表示成功。
        * @param[in] info        指向返回的資訊結構體。當errorCode不為0時，info為空。
        * @attention 不要修改和刪除info所指示的資料；函式呼叫結束，引數不再有效。
        * @ingroup G_T_HKMarket
        */
        virtual void TAP_CDECL OnRspHKMarketOrderInsert(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode,  const ITapTrade::TapAPIOrderMarketInsertRsp *info) = 0;

        /**
        * @brief 港交所做市商雙邊撤單應答 Add:2017.08.29
        * @param[in] sessionID 請求的會話ID；
        * @param[in] errorCode 錯誤碼。0 表示成功。
        * @param[in] info        指向返回的資訊結構體。當errorCode不為0時，info為空。
        * @attention 不要修改和刪除info所指示的資料；函式呼叫結束，引數不再有效。
        * @ingroup G_T_HKMarket
        */
        virtual void TAP_CDECL OnRspHKMarketOrderDelete(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, const ITapTrade::TapAPIOrderMarketDeleteRsp *info) = 0;

        /**
        * @brief 港交所詢價通知 Add:2017.08.29
        * @param[in] info        指向返回的資訊結構體。當errorCode不為0時，info為空。
        * @attention 不要修改和刪除info所指示的資料；函式呼叫結束，引數不再有效。
        * @ingroup G_T_HKMarket
        */
        virtual void TAP_CDECL OnHKMarketQuoteNotice( const ITapTrade::TapAPIOrderQuoteMarketNotice *info) = 0;


        /**
        * @brief 訂單刪除應答 Add:2017.12.05
        * @param[in] sessionID 請求的會話ID；
        * @param[in] errorCode 錯誤碼。0 表示成功。
        * @param[in] info        指向返回的資訊結構體。當errorCode不為0時，info為空。
        * @attention 不要修改和刪除info所指示的資料；函式呼叫結束，引數不再有效。
        * @ingroup G_T_LocalAction
        */
        virtual void TAP_CDECL OnRspOrderLocalRemove(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, const ITapTrade::TapAPIOrderLocalRemoveRsp *info) = 0;

        /**
        * @brief 訂單錄入應答 Add:2017.12.05
        * @param[in] sessionID 請求的會話ID；
        * @param[in] errorCode 錯誤碼。0 表示成功。
        * @param[in] info        指向返回的資訊結構體。當errorCode不為0時，info為空。
        * @attention 不要修改和刪除info所指示的資料；函式呼叫結束，引數不再有效。
        * @ingroup G_T_LocalAction
        */
        virtual void TAP_CDECL OnRspOrderLocalInput(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, const ITapTrade::TapAPIOrderLocalInputRsp *info) = 0;

        /**
        * @brief 訂單修改應答 Add:2017.12.05
        * @param[in] sessionID 請求的會話ID；
        * @param[in] errorCode 錯誤碼。0 表示成功。
        * @param[in] info        指向返回的資訊結構體。當errorCode不為0時，info為空。
        * @attention 不要修改和刪除info所指示的資料；函式呼叫結束，引數不再有效。
        * @ingroup G_T_LocalAction
        */
        virtual void TAP_CDECL OnRspOrderLocalModify(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, const ITapTrade::TapAPIOrderLocalModifyRsp *info) = 0;

        /**
        * @brief 訂單轉移應答 Add:2017.12.05
        * @param[in] sessionID 請求的會話ID；
        * @param[in] errorCode 錯誤碼。0 表示成功。
        * @param[in] info        指向返回的資訊結構體。當errorCode不為0時，info為空。
        * @attention 不要修改和刪除info所指示的資料；函式呼叫結束，引數不再有效。
        * @ingroup G_T_LocalAction
        */
        virtual void TAP_CDECL OnRspOrderLocalTransfer(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, const ITapTrade::TapAPIOrderLocalTransferRsp *info) = 0;

        /**
        * @brief 成交錄入應答 Add:2017.12.05
        * @param[in] sessionID 請求的會話ID；
        * @param[in] errorCode 錯誤碼。0 表示成功。
        * @param[in] info        指向返回的資訊結構體。當errorCode不為0時，info為空。
        * @attention 不要修改和刪除info所指示的資料；函式呼叫結束，引數不再有效。
        * @ingroup G_T_LocalAction
        */
        virtual void TAP_CDECL OnRspFillLocalInput(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, const ITapTrade::TapAPIFillLocalInputRsp *info) = 0;

        /**
        * @brief 訂單刪除應答 Add:2017.12.05
        * @param[in] sessionID 請求的會話ID；
        * @param[in] errorCode 錯誤碼。0 表示成功。
        * @param[in] info        指向返回的資訊結構體。當errorCode不為0時，info為空。
        * @attention 不要修改和刪除info所指示的資料；函式呼叫結束，引數不再有效。
        * @ingroup G_T_LocalAction
        */
        virtual void TAP_CDECL OnRspFillLocalRemove(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, const ITapTrade::TapAPIFillLocalRemoveRsp *info) = 0;



    };



    //TapTradeAPI 對外功能介面。包含了使用者可以呼叫的功能函式。
    class ITapTradeAPI
    {
    public:
        /**
        * @brief    設定API的回撥介面物件。
        * @details    系統對API的通知將通過設定的回撥物件通知給使用者。
        *            ITapTradeAPINotify是API的回撥介面，使用者需要繼承實現此介面類物件來完成使用者需要的功能。
        *            如果使用者沒有設定回撥介面，則API不會向用戶返回任何有用的資訊。\n
        *            ITapTradeAPINotify類的詳細內容請檢視TapTradeAPI.h 檔案。
        * @param[in] apiNotify 實現了ITapTradeAPINotify介面的物件指標。
        * @operationtype 同步操作
        * @ingroup G_T_Login
        */
        virtual ITapTrade::TAPIINT32 TAP_CDECL SetAPINotify(ITapTrade::ITapTradeAPINotify *pSpi) = 0;
        /**
        * @brief 設定伺服器的IP地址和埠。
        * @param[in] IP   IP地址
        * @param[in] port 埠號
        * @operationtype 同步操作
        * @ingroup G_T_Login
        */
        virtual ITapTrade::TAPIINT32 TAP_CDECL SetHostAddress(const ITapTrade::TAPICHAR *IP, ITapTrade::TAPIUINT16 port,bool bSSL=false) = 0;
        /**
        * @brief    發起登入請求。API將先連線服務，建立鏈路，發起登入認證。
        * @details    在使用函式前使用者需要完成伺服器的設定SetHostAddress()，並且建立TapAPITradeLoginAuth型別的使用者資訊，
        *            並且需要設定好回撥介面。\n
        *            登入過程中建立連線的返回資訊通過回撥OnConnect返回給使用者。\n
        *            連線建立後的使用者驗證回饋資訊通過回撥OnLogin()返回給使用者。\n
        *            登入成功後API會自動進行API的初始化，API向伺服器請求基礎資料，查詢完以後會通過回撥OnAPIReady()
        *            指示使用者API初始化完成，可以進行後續的操作了。
        * @param[in] loginAuth 登入驗證資訊結構指標。包含登入需要的驗證資訊。
        * @retval 0 登入成功，API開始準備後臺資料
        * @retval 非0 錯誤碼
        * @operationtype 非同步操作
        * @note TapAPITradeLoginAuth中的NoticeIgnoreFlag用於標記是否忽略特定的通知回撥。\n
        *       例如：不需要接收OnRtnFund和OnRtnPositionProfit,可以這麼設定：\n
        *       NoticeIgnoreFlag = TAPI_NOTICE_IGNORE_FUND | TAPI_NOTICE_IGNORE_POSITIONPROFIT;
        * @attention Login()函式呼叫成功只是代表於伺服器建立了鏈路連線，只有回撥OnLogin()的返回能指示使用者是否成功登入了。
        * @ingroup G_T_Login
        */
        virtual ITapTrade::TAPIINT32 TAP_CDECL Login(const ITapTrade::TapAPITradeLoginAuth *loginAuth) = 0;

        /**
        * @brief    請求傳送二次認證認證碼
        * @details    此函式需要9.2.7後臺，根據回掉函式OnRtnContactInfo中的聯絡方式，選擇其中一個請求二次認證嗎，
        *            收到正確應答後可以通過SetVertificateCode 設定二次認證授權碼完成登陸過程。
        * @param[out] sessionID本次請求的會話ID。
        * @param[in]  ContractInfo,要接收二次認證嗎的郵箱或者電話。
        * @attention 該函式呼叫需要在登陸應答後返回10003錯誤，API會回撥客戶二次 認證的聯絡方式，使用者選擇其中一個聯絡方式（郵箱或者電話）請求二次認證。再通過設定二次認證授權碼完成登陸。
        */
        virtual ITapTrade::TAPIINT32 TAP_CDECL RequestVertificateCode(ITapTrade::TAPIUINT32 *sessionID,ITapTrade::TAPISTR_40 ContactInfo) = 0;
        /**
        * @brief    設定二次認證資訊。
        * @details    登入完成後，如果系統配置需要進行二次認證碼輸入，則登入後會提示需要進行二次認證。
        *            此時呼叫該函式輸入二次認證來完成登入。
        *            登入完成後不允許再呼叫此函式。其他原因引起的登入失敗也不能呼叫次函式，否則會返回對應的錯誤資訊。
        *            呼叫此介面後，會返回登入應答成功與否的標記，如果成功表示登入完成，可以等待OnAPIReady API完成回撥。
        *            如果超時，回撥完成後API會主動斷開連結，需要再次進行登入操作。
        *            如果驗證碼錯誤，則可以再次呼叫此函式輸入正確的驗證碼進行驗證。
        * @param[in] VertificateCode二次認證碼。
        * @retval 0 傳送認證碼成功
        * @retval 非0 錯誤碼
        * @operationtype 非同步操作
        * @ingroup G_T_Login
        */
        virtual ITapTrade::TAPIINT32 TAP_CDECL SetVertificateCode(TAPISTR_10 VertificateCode) = 0;
        
        /**
        * @brief    斷開和伺服器的鏈路連線。
        * @details    呼叫函式後API將登出並斷開與伺服器的連線。
        * @operationtype 同步操作
        * @ingroup G_T_Disconnect
        */
        virtual ITapTrade::TAPIINT32 TAP_CDECL Disconnect() = 0;
        /**
        * @brief    修改密碼。
        * @details    成功後用戶密碼將被設定成newPassword。
        * @param[out]    sessionID 返回此次修改密碼的會話ID;
        * @param[in]    req 請求修改密碼的結構體指標
        * @retval 0 成功
        * @retval 非0 錯誤碼
        * @operationtype 非同步操作
        * @ingroup G_T_UserInfo
        */
        virtual ITapTrade::TAPIINT32 TAP_CDECL ChangePassword(ITapTrade::TAPIUINT32 *sessionID, const ITapTrade::TapAPIChangePasswordReq *req) = 0;


        /**
        * @brief    認證密碼。
        * @details    交易員認證某個賬戶密碼是否正確。
        * @param[out]    sessionID 返回此次修改密碼的會話ID;
        * @param[in]    req 請求認證密碼的結構體指標
        * @retval 0 成功
        * @retval 非0 錯誤碼
        * @operationtype 非同步操作
        * @ingroup G_T_UserInfo
        */
        virtual ITapTrade::TAPIINT32 TAP_CDECL AuthPassword(ITapTrade::TAPIUINT32 *sessionID, const ITapTrade::TapAPIAuthPasswordReq *req) = 0;


        /**
        * @brief    判斷登入使用者是否具有某許可權。
        * @details    使用者的許可權在使用者登入時已經傳遞給API，所以此函式執行的是本地的查詢。
        * @param[in] rightID 許可權ID。
        * @retval 0 不具有許可權
        * @retval 非0 具有許可權
        * @operationtype 同步操作
        * @ingroup G_T_UserRight
        */
        virtual ITapTrade::TAPIINT32 TAP_CDECL HaveCertainRight(ITapTrade::TAPIRightIDType rightID) = 0;


        /**
        * @brief    查詢系統日曆。
        * @details    獲取當前交易日，上次結算日，LME到期日，和上日LME到期日
        * @param[out]    sessionID 返回請求的會話ID;
        * @retval 0 請求成功
        * @retval 非0 錯誤碼
        * @operationtype 非同步操作
        * @note 該介面暫未實現
        * @ingroup G_T_UserRight
        */
        virtual ITapTrade::TAPIINT32 TAP_CDECL QryTradingDate(ITapTrade::TAPIUINT32 *sessionID) = 0;
        /**
        * @brief    設定使用者預留資訊。
        * @details    使用者可以設定一個長度為50以內的字元資訊，下次登入後可以得到這個資訊。
        *            這個功能主要是用來讓使用者確認是自己的賬號，主要是用來進行防偽。
        * @param[out]    sessionID 返回請求的會話ID;
        * @param[in] info    預留資訊字串指標
        * @retval 0 請求成功
        * @retval 非0 錯誤碼
        * @operationtype 非同步操作
        * @note 該介面暫未實現
        * @ingroup G_T_UserInfo
        */
        virtual ITapTrade::TAPIINT32 TAP_CDECL SetReservedInfo(ITapTrade::TAPIUINT32 *sessionID, const ITapTrade::TAPISTR_50 info) = 0;
        /**
        * @brief 查詢使用者下屬的資金賬號
        * @details    TapAPIAccQryReq是包含資金賬號結構的結構體，使用者需要例項化此結構體，
        *            但是不需要填寫，這個結構體主要是用來提醒使用者儲存資金賬號，資金賬號
        *            在後續的函式呼叫中很多函式都需要使用到。
        * @param[out]    sessionID 返回請求的會話ID;
        * @param[in]    qryReq 查詢使用者下屬的資金賬號的結構體指標
        * @retval 0 請求成功
        * @retval 非0 錯誤碼
        * @operationtype 非同步操作
        * @ingroup G_T_AccountInfo
        */
        virtual ITapTrade::TAPIINT32 TAP_CDECL QryAccount(ITapTrade::TAPIUINT32 *sessionID, const ITapTrade::TapAPIAccQryReq *qryReq) = 0;
        /**
        * @brief    查詢客戶資金
        * @details    TapAPIFundReq需要QryAccount()獲取的資金賬號。
        *            函式的回撥將返回資金賬號的資金資訊。\n
        * @param[out] sessionID 返回請求的會話ID;
        * @param[in] qryReq    查詢客戶資金請求的結構體指標
        * @retval 0 請求成功
        * @retval 非0 錯誤碼
        * @operationtype 非同步操作
        * @ingroup G_T_AccountDetails
        * @attention 每次登陸，該介面只能進行一次呼叫。建議初始化時呼叫一次，後續的通知通過OnRtnFund取得。
        */
        virtual ITapTrade::TAPIINT32 TAP_CDECL QryFund(ITapTrade::TAPIUINT32 *sessionID, const ITapTrade::TapAPIFundReq *qryReq) = 0;
        /**
        * @brief 查詢交易系統交易所資訊
        * @param[out] sessionID 返回請求的會話ID;
        * @retval 0 請求成功
        * @retval 非0 錯誤碼
        * @operationtype 非同步操作
        * @ingroup G_T_TradeSystem
        */
        virtual ITapTrade::TAPIINT32 TAP_CDECL QryExchange(ITapTrade::TAPIUINT32 *sessionID) = 0;
        /**
        * @brief    查詢系統品種資訊
        * @details    函式請求獲取所有的品種資訊。
        * @param[out] sessionID 返回請求的會話ID;
        * @retval 0 請求成功
        * @retval 非0 錯誤碼
        * @operationtype 非同步操作
        * @ingroup G_T_Commodity
        */
        virtual ITapTrade::TAPIINT32 TAP_CDECL QryCommodity(ITapTrade::TAPIUINT32 *sessionID) = 0;
        /**
        * @brief    查詢系統中指定品種的合約資訊
        * @details    使用此函式前需要先Qrycommodity()取得品種資訊，
        *            然後選擇需要的品種將資訊填入TapAPICommodity結構體中完成查詢請求。
        *            或者TapAPICommodity不填，則返回所有資訊。
        * @param[out] sessionID 返回請求的會話ID;
        * @param[in] qryReq 查詢系統中指定品種的合約資訊請求的結構體指標;\n
        *                    該引數各欄位為可選欄位，可以用以下方法查詢：\n
        *                    1.全部留空：查所有合約\n
        *                    2.僅交易所編碼有效：查該交易所下所有品種的合約\n
        *                    3.交易所編碼和品種型別有效：查該交易所下指定品種型別的合約\n
        *                    4.交易所編碼、品種型別和品種編碼都有效：查該品種下的所有合約
        * @retval 0 請求成功
        * @retval 非0 錯誤碼
        * @operationtype 非同步操作
        * @ingroup G_T_Contract
        */
        virtual ITapTrade::TAPIINT32 TAP_CDECL QryContract(ITapTrade::TAPIUINT32 *sessionID, const ITapTrade::TapAPICommodity *qryReq) = 0;

        /**
        * @brief    下單
        * @details    使用者下單的操作函式。
        *            使用者的下單操作會造成使用者的資金、持倉、平倉、資金、風控標記等多種資料的變化，所以使用者下的單成交後，
        *            會有多個回撥通知來向用戶展示資料的變化。
        * @param[out]    sessionID 返回請求的會話ID;
        * @param[out]    ClientOrderNo 返回客戶本地委託號。
        * @param[in]    order 新的委託
        * @retval 0 請求成功
        * @retval 非0 錯誤碼
        * @operationtype 非同步操作
        * @ingroup G_T_TradeActions
        */
        virtual ITapTrade::TAPIINT32 TAP_CDECL InsertOrder(ITapTrade::TAPIUINT32 *sessionID,ITapTrade::TAPISTR_50 *ClientOrderNo, const ITapTrade::TapAPINewOrder *order) = 0;

        /**
        * @brief    撤單
        * @details    使用者委託沒有完全成交之前撤銷剩餘的委託。
        * @param[out]    sessionID 返回請求的會話ID;
        * @param[in]    order 撤銷的委託
        * @retval 0 請求成功
        * @retval 非0 錯誤碼
        * @operationtype 非同步操作
        * @ingroup G_T_TradeActions
        */
        virtual ITapTrade::TAPIINT32 TAP_CDECL CancelOrder(ITapTrade::TAPIUINT32 *sessionID, const ITapTrade::TapAPIOrderCancelReq *order) = 0;

        /**
        * @brief    改單
        * @details    使用者的委託沒有完全成交之前可以進行改單操作來修改剩餘的未成交的委託。\n
        *            使用者填寫新的委託來修改原來的未成交的部分。報單的修改會對比已經成交的部分來扣除成交部分。
        * @param[out]    sessionID 返回請求的會話ID;
        * @param[in]    order 修改的委託
        * @retval 0 請求成功
        * @retval 非0 錯誤碼
        * @operationtype 非同步操作
        * @ingroup G_T_TradeActions
        */
        virtual ITapTrade::TAPIINT32 TAP_CDECL AmendOrder(ITapTrade::TAPIUINT32 *sessionID, const ITapTrade::TapAPIAmendOrder *order) = 0;

        /**
        * @brief 訂單啟用
        * @details 使用者的埋單需要傳送時需要進行啟用。或者港交所已掛起的訂單。
        * @param[out]    sessionID 返回請求的會話ID;
        * @param[in]    order 要啟用的訂單
        * @retval 0 請求成功
        * @retval 非0 錯誤碼
        * @operationtype 非同步操作
        * @ingroup G_T_TradeActions
        */
        virtual TAPIINT32 TAP_CDECL ActivateOrder(TAPIUINT32 * sessionID, const TapAPIOrderActivateReq * order) = 0;
        
        /**
        * @brief    查詢委託資訊
        * @details    返回當前的委託資訊，可以查詢所有委託，也可以查詢所有未結束的委託。\n
        * @retval 0 請求成功
        * @retval 非0 錯誤碼
        * @operationtype 非同步操作
        * @ingroup G_T_TradeInfo
        * @attention 每次登陸，該介面只能進行一次呼叫。建議初始化時呼叫一次，後續的通知通過OnRtnOrder取得。
        */
        virtual ITapTrade::TAPIINT32 TAP_CDECL QryOrder(ITapTrade::TAPIUINT32 *sessionID, const ITapTrade::TapAPIOrderQryReq *qryReq) = 0;
        /**
        * @brief    查詢委託變化流程
        * @details    查詢使用者的委託的變化流程，查詢將返回委託的每一次的變化。
        * @param[out] sessionID 返回請求的會話ID;
        * @param[in] qryReq 委託流程查詢資訊結構體指標。
        * @retval 0 請求成功
        * @retval 非0 錯誤碼
        * @operationtype 非同步操作
        * @ingroup G_T_TradeInfo
        */
        virtual ITapTrade::TAPIINT32 TAP_CDECL QryOrderProcess(ITapTrade::TAPIUINT32 *sessionID, const ITapTrade::TapAPIOrderProcessQryReq *qryReq) = 0;
        /**
        * @brief 查詢成交資訊
        * @details    查詢系統中成交的資訊。
        * @param[out] sessionID 返回請求的會話ID;
        * @param[in] qryReq 成交查詢資訊結構體指標。
        * @retval 0 請求成功
        * @retval 非0 錯誤碼
        * @operationtype 非同步操作
        * @ingroup G_T_TradeInfo
        * @attention 每次登陸，該介面只能進行一次呼叫。建議初始化時呼叫一次，後續的通知通過OnRtnFill取得。
        */
        virtual ITapTrade::TAPIINT32 TAP_CDECL QryFill(ITapTrade::TAPIUINT32 *sessionID, const ITapTrade::TapAPIFillQryReq *qryReq) = 0;
        /**
        * @brief    查詢使用者持倉
        * @details    查詢使用者的所有持倉資訊。
        * @param[out] sessionID 返回請求的會話ID;
        * @param[in] qryReq    查詢使用者持倉請求的結構體指標
        * @retval 0 請求成功
        * @retval 非0 錯誤碼
        * @operationtype 非同步操作
        * @ingroup G_T_TradeInfo
        * @attention 每次登陸，該介面只能進行一次呼叫。建議初始化時呼叫一次，後續的通知通過OnRtnPosition取得。
        */
        virtual ITapTrade::TAPIINT32 TAP_CDECL QryPosition(ITapTrade::TAPIUINT32 *sessionID, const ITapTrade::TapAPIPositionQryReq *qryReq) = 0;

        /**
        * @brief    查詢使用者持倉彙總
        * @details    查詢使用者的所有持倉資訊。
        * @param[out] sessionID 返回請求的會話ID;
        * @param[in] qryReq    查詢使用者持倉請求的結構體指標
        * @retval 0 請求成功
        * @retval 非0 錯誤碼
        * @operationtype 非同步操作
        * @ingroup G_T_TradeInfo
        * @attention 每次登陸，該介面只能進行一次呼叫。建議初始化時呼叫一次，後續的通知通過OnRtnPosition取得。
        */
        virtual ITapTrade::TAPIINT32 TAP_CDECL QryPositionSummary(ITapTrade::TAPIUINT32 *sessionID, const ITapTrade::TapAPIPositionQryReq *qryReq) = 0;

        /**
        * @brief 獲取交易所用幣種的資訊
        * @param[out] sessionID 返回請求的會話ID;
        * @retval 0 請求成功
        * @retval 非0 錯誤碼
        * @operationtype 非同步操作
        * @ingroup G_T_TradeSystem
        */
        virtual ITapTrade::TAPIINT32 TAP_CDECL QryCurrency(ITapTrade::TAPIUINT32 *sessionID) = 0;
        /**
        * @brief 客戶資金調整查詢請求
        * @param[out] sessionID 返回請求的會話ID;
        * @param[in]    Req    客戶資金調整查詢請求的結構體指標
        * @retval 0 請求成功
        * @retval 非0 錯誤碼
        * @operationtype 非同步操作
        * @ingroup G_T_HisInfo
        */
        virtual ITapTrade::TAPIINT32 TAP_CDECL QryAccountCashAdjust(ITapTrade::TAPIUINT32 *sessionID, const ITapTrade::TapAPIAccountCashAdjustQryReq *qryReq) = 0;
        /**
        * @brief    獲取交易或風控訊息
        * @details    此函式用來主動獲取賬號的交易或者風控訊息。交易或者風控訊息用來標識賬號的狀態。
        * @param[out] sessionID 返回請求的會話ID;
        * @param[in] qryReq 獲取交易或風控訊息請求的結構體指標;
        * @retval 0 請求成功
        * @retval 非0 錯誤碼
        * @operationtype 非同步操作
        說明：易盛保留介面
        * @ingroup G_T_AccountDetails
        */
        virtual ITapTrade::TAPIINT32 TAP_CDECL QryTradeMessage(ITapTrade::TAPIUINT32 *sessionID, const ITapTrade::TapAPITradeMessageReq *qryReq) = 0;
        /**
        * @brief 查詢使用者賬單
        * @param[out]    sessionID 返回請求的會話ID;
        * @param[in]    qryReq    查詢帳單請求的結構體指標
        * @retval 0 請求成功
        * @retval 非0 錯誤碼
        * @operationtype 非同步操作
        * @ingroup G_T_Bill
        */
        virtual ITapTrade::TAPIINT32 TAP_CDECL QryBill(ITapTrade::TAPIUINT32 *sessionID, const ITapTrade::TapAPIBillQryReq *qryReq) = 0;
        /**
        * @brief 歷史委託查詢請求
        * @param[out]    sessionID 返回請求的會話ID;
        * @param[in]    Req    歷史委託查詢請求的結構體指標
        * @retval 0 請求成功
        * @retval 非0 錯誤碼
        * @operationtype 非同步操作
        * @ingroup G_T_HisInfo
        */
        virtual ITapTrade::TAPIINT32 TAP_CDECL QryHisOrder(ITapTrade::TAPIUINT32 *sessionID, const ITapTrade::TapAPIHisOrderQryReq *qryReq) = 0;
        /**
        * @brief 歷史委託流程查詢請求
        * @param[out] sessionID 返回請求的會話ID;
        * @param[in]    Req    歷史委託流程查詢請求的結構體指標
        * @retval 0 請求成功
        * @retval 非0 錯誤碼
        * @operationtype 非同步操作
        * @ingroup G_T_HisInfo
        */
        virtual ITapTrade::TAPIINT32 TAP_CDECL QryHisOrderProcess(ITapTrade::TAPIUINT32 *sessionID, const ITapTrade::TapAPIHisOrderProcessQryReq *qryReq) = 0;
        /**
        * @brief 歷史成交查詢請求
        * @param[out] sessionID 返回請求的會話ID;
        * @param[in]    Req    歷史成交查詢請求的結構體指標
        * @retval 0 請求成功
        * @retval 非0 錯誤碼
        * @operationtype 非同步操作
        * @ingroup G_T_HisInfo
        */
        virtual ITapTrade::TAPIINT32 TAP_CDECL QryHisMatch(ITapTrade::TAPIUINT32 *sessionID, const ITapTrade::TapAPIHisMatchQryReq *qryReq) = 0;
        /**
        * @brief 歷史持倉查詢請求
        * @param[out] sessionID 返回請求的會話ID;
        * @param[in]    Req    歷史持倉查詢請求的結構體指標
        * @retval 0 請求成功
        * @retval 非0 錯誤碼
        * @operationtype 非同步操作
        * @ingroup G_T_HisInfo
        */
        virtual ITapTrade::TAPIINT32 TAP_CDECL QryHisPosition(ITapTrade::TAPIUINT32 *sessionID, const ITapTrade::TapAPIHisPositionQryReq *qryReq) = 0;
        /**
        * @brief 歷史交割查詢請求
        * @param[out] sessionID 返回請求的會話ID;
        * @param[in]    Req    歷史交割查詢請求的結構體指標
        * @retval 0 請求成功
        * @retval 非0 錯誤碼
        * @operationtype 非同步操作
        * @ingroup G_T_HisInfo
        */
        virtual ITapTrade::TAPIINT32 TAP_CDECL QryHisDelivery(ITapTrade::TAPIUINT32 *sessionID, const ITapTrade::TapAPIHisDeliveryQryReq *qryReq) = 0;

        /**
        * @brief 客戶手續費計算引數查詢請求
        * @param[out] sessionID 返回請求的會話ID;
        * @param[in]    Req    客戶手續費計算引數查詢請求結構
        * @retval 0 請求成功
        * @retval 非0 錯誤碼
        * @operationtype 非同步操作
        * @ingroup G_T_Rent
        */
        virtual ITapTrade::TAPIINT32 TAP_CDECL QryAccountFeeRent(ITapTrade::TAPIUINT32 *sessionID, const ITapTrade::TapAPIAccountFeeRentQryReq *qryReq) = 0;
        /**
        * @brief 客戶保證金計算引數查詢請求
        * @param[out] sessionID 返回請求的會話ID;
        * @param[in]    Req    客戶保證金計算引數查詢請求結構
        * @retval 0 請求成功
        * @retval 非0 錯誤碼
        * @operationtype 非同步操作
        * @ingroup G_T_Rent
        */
        virtual ITapTrade::TAPIINT32 TAP_CDECL QryAccountMarginRent(ITapTrade::TAPIUINT32 *sessionID, const ITapTrade::TapAPIAccountMarginRentQryReq *qryReq) = 0;
        /**
        * @brief 港交所做市商雙邊報價指令
        * @param[out] sessionID 返回當前請求的SessionID;
        * @param[out] ClientBuyOrderNo返回港交所雙邊報價中買單的客戶本地委託號;
        * @param[out] ClientSellOrderNo返回港交所雙邊報價中賣單的客戶本地委託號;
        * @param[in] order雙邊報價請求結構;
        * @retval 0 請求成功
        * @retval 非0 錯誤碼
        * @operationtype 非同步操作
        * @ingroup G_T_HKMarket
        */
        virtual ITapTrade::TAPIINT32 TAP_CDECL InsertHKMarketOrder(TAPIUINT32 *sessionID, TAPISTR_50 *ClientBuyOrderNo, TAPISTR_50 *ClientSellOrderNo, const TapAPIOrderMarketInsertReq *order) = 0;

        /**
        * @brief 港交所做市商雙邊撤單指令
        * @param[out] sessionID 返回當前請求的sessionID。
        * @param[in] order 港交所做市商撤單指令請求結構。 
        * @retval 0 請求成功
        * @retval 非0 錯誤碼
        * @operationtype 非同步操作
        * @ingroup G_T_HKMarket
        */
        virtual ITapTrade::TAPIINT32 TAP_CDECL CancelHKMarketOrder(TAPIUINT32 *sessionID, const TapAPIOrderMarketDeleteReq *order) = 0;

        /**
        * @brief 訂單刪除指令
        * @param[out] sessionID 返回當前請求的sessionID。
        * @param[in] order 要訂單刪除的訂單。
        * @retval 0 請求成功
        * @retval 非0 錯誤碼
        * @operationtype 非同步操作
        * @ingroup G_T_LocalActions
        */
        virtual ITapTrade::TAPIINT32 TAP_CDECL OrderLocalRemove(TAPIUINT32 *sessionID, const TapAPIOrderLocalRemoveReq *order) = 0;
        /**
        * @brief 訂單錄入指令
        * @param[out] sessionID 返回當前請求的sessionID。
        * @param[in] order 訂單錄入請求資訊。
        * @retval 0 請求成功
        * @retval 非0 錯誤碼
        * @operationtype 非同步操作
        * @ingroup G_T_LocalActions
        */
        virtual  ITapTrade::TAPIINT32 TAP_CDECL OrderLocalInput(TAPIUINT32 *sessionID, const TapAPIOrderLocalInputReq *order) = 0;
        /**
        * @brief 訂單修改指令
        * @param[out] sessionID 返回當前請求的sessionID。
        * @param[in] order 訂單修改請求結構
        * @retval 0 請求成功
        * @retval 非0 錯誤碼
        * @operationtype 非同步操作
        * @ingroup G_T_LocalActions
        */
        virtual  ITapTrade::TAPIINT32 TAP_CDECL OrderLocalModify(TAPIUINT32 *sessionID, const TapAPIOrderLocalModifyReq *order) = 0;
        /**
        * @brief  訂單轉移指令
        * @param[out] sessionID 返回當前請求的sessionID。
        * @param[in] 訂單轉移請求資訊。
        * @retval 0 請求成功
        * @retval 非0 錯誤碼
        * @operationtype 非同步操作
        * @ingroup G_T_LocalActions
        */
        virtual  ITapTrade::TAPIINT32 TAP_CDECL OrderLocalTransfer(TAPIUINT32 *sessionID, const TapAPIOrderLocalTransferReq *order) = 0;
        /**
        * @brief 成交錄入指令
        * @param[out] sessionID 返回當前請求的sessionID。
        * @param[in] 要錄入的成交資訊
        * @retval 0 請求成功
        * @retval 非0 錯誤碼
        * @operationtype 非同步操作
        * @ingroup G_T_LocalActions
        */
        virtual ITapTrade::TAPIINT32 TAP_CDECL FillLocalInput(TAPIUINT32 *sessionID, const TapAPIFillLocalInputReq *fill) = 0;
        /**
        * @brief 成交刪除指令
        * @param[out] sessionID 返回當前請求的sessionID。
        * @param[in] 成交刪除請求資訊
        * @retval 0 請求成功
        * @retval 非0 錯誤碼
        * @operationtype 非同步操作
        * @ingroup G_T_LocalActions
        */
        virtual ITapTrade::TAPIINT32 TAP_CDECL FillLocalRemove(TAPIUINT32 *sessionID, const TapAPIFillLocalRemoveReq *fill) = 0;
    };
};

    //-----------------------------TapTradeAPI匯出函式------------------------------------


    #ifdef __cplusplus
    extern "C" {
    #endif // __cplusplus

    /**
    * @brief    建立TapTradeAPI的介面物件。
    * @details    建立整個交易API的介面
    * @param[in] appInfo 應用程式相關資訊。
    * @param[in] iResult 建立介面的錯誤碼。
    * @retval NULL    建立失敗，具體原因可通過輸出引數iResult判斷。
    * @retval !NULL    實現了ITapTradeAPI介面的物件指標。
    * @ingroup G_T_API
    */
        TAP_DLLEXPORT ITapTrade::ITapTradeAPI *TAP_CDECL CreateITapTradeAPI(const ITapTrade::TapAPIApplicationInfo *appInfo, ITapTrade::TAPIINT32 &iResult);
    /**
    * @brief    銷燬通過CreateTapTradeAPI函式建立的ITapTradeAPI物件。
    * @param[in] apiObj ITapTradeAPI物件指標。
    * @ingroup G_T_API
    */
        TAP_DLLEXPORT void TAP_CDECL FreeITapTradeAPI(ITapTrade::ITapTradeAPI *apiObj);
    /**
    * @brief    獲取TapTradeAPI的版本資訊
    * @ingroup G_T_API
    */
        TAP_DLLEXPORT const ITapTrade::TAPICHAR *TAP_CDECL GetITapTradeAPIVersion();
    /**
    * @brief    設定API自身儲存資料目錄
    * @details    呼叫函式的同時會在path描述的目錄下開啟以年月日（格式TapTradeAPI[YYYYMMDD].log)命名的檔案，\n
    *            沒有此檔案的情況下會試圖建立此檔案。\n
    *            檔案中儲存的資料為API接收到的重要資料和API的使用和錯誤日誌。
    * @param[in] path 目錄。必須可用，目錄符號Window下為”\\”或者”/”, Linux下為”/”。
    * @retval 0 成功
    * @retval 非0 錯誤碼
    * @operationtype 同步操作
    * @ingroup G_T_LogConfig
    */
        TAP_DLLEXPORT ITapTrade::TAPIINT32 TAP_CDECL SetITapTradeAPIDataPath(const ITapTrade::TAPICHAR *path);
    /**
    * @brief    設定API的日誌級別
    * @details    設定日誌的輸出級別，只有當實際日誌級別與此處設定的級別相同或更高時，才會將日誌寫入SetTapTradeAPIDataPath()函式開啟的日誌檔案。\n
    * @param[in]    level 日誌級別：\n
    *                    APILOGLEVEL_NONE    ：不記錄日誌\n
    *                    APILOGLEVEL_ERROR    ：記錄Error日誌\n
    *                    APILOGLEVEL_WARNING    ：記錄Error和Warning日誌\n
    *                    APILOGLEVEL_DEBUG    ：記錄Error、Warning和Debug日誌\n
    * @retval 0 設定成功
    * @retval 非0 錯誤碼
    * @operationtype 同步操作
    * @ingroup G_T_LogConfig
    */
        TAP_DLLEXPORT ITapTrade::TAPIINT32 TAP_CDECL SetITapTradeAPILogLevel(ITapTrade::TAPILOGLEVEL level);

        /**
        * @brief    根據錯誤碼獲取錯誤資訊。在建立完API指標後即可呼叫，否則返回空值。
        * @details    根據錯誤碼可以獲取到對應的錯誤資訊，
        * @param[in]    errorCode 錯誤碼
        * @retval 返回錯誤描述資訊
        * @operationtype 同步操作
        * @ingroup G_T_Error
        */

        TAP_DLLEXPORT const char  * TAP_CDECL GetITapErrorDescribe(ITapTrade::TAPIINT32 errorCode);

    #ifdef __cplusplus
    }
    #endif // __cplusplus


#endif // TAP_TRADE_API_H