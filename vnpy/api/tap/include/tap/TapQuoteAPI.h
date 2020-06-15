#ifndef TAP_QUOTE_API_H
#define TAP_QUOTE_API_H

#include "TapQuoteAPIDataType.h"

#ifdef _WIN32
#define TAP_CDECL  __cdecl
#define TAP_DLLEXPORT __declspec(dllexport)
#else
#define TAP_CDECL
#define TAP_DLLEXPORT
#endif

//TapQuoteAPI.h
//檔案定義了TapQuoteAPI提供給開發者的對外介面、函式和回撥介面。

//TapQuoteAPI 的回撥通知介面。
class ITapQuoteAPINotify
{
public:
	/**
	* @brief	系統登入過程回撥。
	* @details	此函式為Login()登入函式的回撥，呼叫Login()成功後建立了鏈路連線，然後API將向伺服器傳送登入認證資訊，
	*			登入期間的資料傳送情況和登入的回饋資訊傳遞到此回撥函式中。
	* @param[in] errorCode 返回錯誤碼,0表示成功。
	* @param[in] info 登陸應答資訊，如果errorCode!=0，則info=NULL。
	* @attention	該回調返回成功，說明使用者登入成功。但是不代表API準備完畢。需要等到OnAPIReady才能進行查詢與訂閱請求。
	* @ingroup G_Q_Login
	*/
	virtual void TAP_CDECL OnRspLogin(TAPIINT32 errorCode, const TapAPIQuotLoginRspInfo *info) = 0;
	/**
	* @brief	通知使用者API準備就緒。
	* @details	只有使用者回撥收到此就緒通知時才能進行後續的各種行情資料查詢操作。\n
	*			此回撥函式是API能否正常工作的標誌。
	* @attention  就緒後才可以進行後續正常操作
	* @ingroup G_Q_Login
	*/
	virtual void TAP_CDECL OnAPIReady() = 0;
	/**
	* @brief	API和服務失去連線的回撥
	* @details	在API使用過程中主動或者被動與伺服器服務失去連線後都會觸發此回撥通知使用者與伺服器的連線已經斷開。
	* @param[in] reasonCode 斷開原因程式碼。具體原因請參見錯誤碼列表 \n
	* @ingroup G_Q_Disconnect
	*/
	virtual void TAP_CDECL OnDisconnect(TAPIINT32 reasonCode) = 0;
	/**
	* @brief	返回所有品種資訊。
	* @details	此回撥介面用於向用戶返回得到的所有品種資訊。
	* @param[in] sessionID 請求的會話ID
	* @param[in] errorCode 錯誤碼，當errorCode!=0時,info為NULL；
	* @param[in] isLast 標示是否是最後一批資料；
	* @param[in] info 返回的資訊陣列的起始指標。
	* @attention  不要修改和刪除info所指示的資料；函式呼叫結束，引數不再有效。
	* @ingroup G_Q_Commodity
	*/
	virtual void TAP_CDECL OnRspQryCommodity(TAPIUINT32 sessionID, TAPIINT32 errorCode, TAPIYNFLAG isLast, const TapAPIQuoteCommodityInfo *info) = 0;
	/**
	* @brief 返回系統中合約資訊
	* @param[in] sessionID 請求的會話ID；
	* @param[in] errorCode 錯誤碼，當errorCode!=0時,info為NULL；
	* @param[in] isLast 標示是否是最後一批資料；
	* @param[in] info		指向返回的資訊結構體。當errorCode不為0時，info為空。
	* @attention 不要修改和刪除info所指示的資料；函式呼叫結束，引數不再有效。
	* @ingroup G_Q_Contract
	*/
	virtual void TAP_CDECL OnRspQryContract(TAPIUINT32 sessionID, TAPIINT32 errorCode, TAPIYNFLAG isLast, const TapAPIQuoteContractInfo *info) = 0;
	/**
	* @brief	返回訂閱行情的全文。
	* @details	此回撥介面用來返回訂閱行情的全文。全文為當前時間的行情資訊。
	* @param[in] sessionID 請求的會話ID；
	* @param[in] isLast 標示是否是最後一批資料；
	* @param[in] errorCode 錯誤碼，當errorCode!=0時,info為NULL；
	* @param[in] info		指向返回的資訊結構體。當errorCode不為0時，info為空。
	* @attention  不要修改和刪除info所指示的資料；函式呼叫結束，引數不再有效。
	* @ingroup G_Q_Quote
	*/
	virtual void TAP_CDECL OnRspSubscribeQuote(TAPIUINT32 sessionID, TAPIINT32 errorCode, TAPIYNFLAG isLast, const TapAPIQuoteWhole *info) = 0;
	/**
	* @brief 退訂指定合約的行情的結果回撥
	* @param[in] sessionID 請求的會話ID；
	* @param[in] errorCode 錯誤碼，當errorCode!=0時,info為NULL；
	* @param[in] isLast 標示是否是最後一批資料；
	* @param[in] info		指向返回的資訊結構體。當errorCode不為0時，info為空。
	* @attention  不要修改和刪除info所指示的資料；函式呼叫結束，引數不再有效。
	* @ingroup G_Q_Quote
	*/
	virtual void TAP_CDECL OnRspUnSubscribeQuote(TAPIUINT32 sessionID, TAPIINT32 errorCode, TAPIYNFLAG isLast, const TapAPIContract *info) = 0;
	/**
	* @brief	返回訂閱行情的變化內容。
	* @details	此回撥介面用來通知使用者行情資訊產生了變化，並向用戶提交新的行情全文。
	* @param[in] info 最新的行情全文內容
	* @attention 不要修改和刪除Quote指示的資料；函式呼叫結束，引數不再有效。
	* @ingroup G_Q_Quote
	*/
	virtual void TAP_CDECL OnRtnQuote(const TapAPIQuoteWhole *info) = 0;
};

//TapQuoteAPI 對外功能介面。包含了使用者可以呼叫的功能函式。
class ITapQuoteAPI
{
public:
	/**
	* @brief	設定API的回撥介面物件。
	* @details	系統對API的通知將通過設定的回撥物件通知給使用者。
	*			ITapQuoteAPINofify是API的回撥介面，使用者需要繼承實現此介面類物件來完成使用者需要的功能。
	*			如果使用者沒有設定回撥介面，則API不會向用戶返回任何有用的資訊。\n
	*			ITapQuoteAPINotify類的詳細內容請檢視TapQuoteAPI.h 檔案。
	* @param[in] apiNotify 實現了ITapQuoteAPINotify介面的物件指標。
	* @operationtype 同步操作
	* @ingroup G_Q_Login
	*/
	virtual TAPIINT32 TAP_CDECL SetAPINotify(ITapQuoteAPINotify *apiNotify) = 0;
	/**
	* @brief 設定伺服器的IP地址和埠。等到呼叫Login時真正發起連線。
	* @param[in] IP   IP地址
	* @param[in] port 埠號
	* @operationtype 同步操作
	* @ingroup G_Q_Login
	*/
	virtual TAPIINT32 TAP_CDECL SetHostAddress(const TAPICHAR *IP, TAPIUINT16 port) = 0;
	/**
	* @brief	發起登入請求。API將先連線服務，建立鏈路，發起登入認證。
	* @details	在使用函式函式前使用者需要完成伺服器的設定SetHostAddress()，並且建立TapAPIQuoteLoginAuth型別的使用者資訊，
	*			並且需要設定好回撥介面。\n
	*			連線建立後的使用者驗證回饋資訊通過回撥OnLogin()返回給使用者。\n
	*			登入成功後API會自動進行API的初始化，API向伺服器請求基礎資料，查詢完以後會通過回撥OnAPIReady()
	*			指示使用者API初始化完成，可以進行後續的操作了。
	* @param[in] loginAuth 登入驗證資訊結構指標。包含登入需要的驗證資訊。
	* @retval 0 登入成功，API開始準備後臺資料
	* @retval 非0 錯誤碼
	* @attention 登入成功與否要根據OnLogin回撥判斷。
	* @operationtype 非同步操作
	* @warning	Login()函式呼叫成功只是代表於伺服器建立了鏈路連線，只有回撥OnLogin()的返回能指示使用者是否成功登入了。
	* @ingroup G_Q_Login
	*/
	virtual TAPIINT32 TAP_CDECL Login(const TapAPIQuoteLoginAuth *loginAuth) = 0;
	/**
	* @brief	斷開和伺服器的鏈路連線。
	* @details	呼叫函式後API將登出並斷開與伺服器的連線。
	* @operationtype 非同步操作
	* @ingroup G_Q_Disconnect
	*/
	virtual TAPIINT32 TAP_CDECL Disconnect() = 0;
	/**
	* @brief 得到所有品種
	* @param[out] sessionID 返回請求的會話ID。
	* @retval 0 請求成功
	* @retval 非0 錯誤碼
	* @operationtype 非同步操作
	* @ingroup G_Q_Commodity
	*/
	virtual TAPIINT32 TAP_CDECL QryCommodity(TAPIUINT32 *sessionID) = 0;
	/**
	* @brief	查詢系統中指定品種的合約資訊
	* @details	使用此函式前需要先QryCommodity()取得品種資訊，
	*			然後選擇需要的品種將資訊填入TapAPICommodity結構體中完成查詢請求。
	* @param[out] sessionID 返回請求的會話ID;
	* @param[in] qryReq 查詢系統中指定品種的合約資訊請求的結構體指標;\n
	*				    該引數各欄位為可選欄位，可以用以下方法查詢：\n
	*					1.全部留空：查所有合約\n
	*					2.僅交易所編碼有效：查該交易所下所有品種的合約\n
	*					3.交易所編碼和品種型別有效：查該交易所下指定品種型別的合約\n
	*					4.交易所編碼、品種型別和品種編碼都有效：查該品種下的所有合約
	* @retval 0 請求成功
	* @retval 非0 錯誤碼
	* @operationtype 非同步操作
	* @ingroup G_Q_Contract
	*/
	virtual TAPIINT32 TAP_CDECL QryContract(TAPIUINT32 *sessionID, const TapAPICommodity *qryReq) = 0;
	/**
	* @brief	訂閱指定合約的行情
	* @details	函式向伺服器請求contract描述的合約的行情資訊，行情訂閱成功後伺服器將持續向用戶推送行情資訊，
	*			直到使用者退訂行情資訊或者斷開於伺服器的通訊。\n
	*			呼叫此函式前先獲取合約資訊，然後從合約資訊中取出合約填入contract。\n
	* @param[out] sessionID 返回請求的會話ID。
	* @param[in] contract 指定合約。
	* @retval 0 請求成功
	* @retval 非0 錯誤碼
	* @operationtype 非同步操作
	* @ingroup G_Q_Quote
	*/
	virtual TAPIINT32 TAP_CDECL SubscribeQuote(TAPIUINT32 *sessionID, const TapAPIContract *contract) = 0;
	/**
	* @brief	退訂指定合約的行情
	* @details	退訂已經訂閱的行情資訊。
	* @param[out] sessionID 返回請求的會話ID；
	* @param[in]	contract 指定合約。
	* @retval 0 請求成功
	* @retval 非0 錯誤碼
	* @operationtype 非同步操作
	* @ingroup G_Q_Quote
	*/
	virtual TAPIINT32 TAP_CDECL UnSubscribeQuote(TAPIUINT32 *sessionID, const TapAPIContract *contract) = 0;
};

//-----------------------------TapQuoteAPI匯出函式------------------------------------


#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

/**
* @brief	建立TapQuoteAPI的介面物件。
* @details	建立整個行情API的介面
* @param[in] appInfo 應用程式相關資訊。
* @param[in] iResult 建立介面的錯誤碼。
* @retval NULL	建立失敗。
* @retval !NULL	實現了ITapQuoteAPI介面的物件指標。
* @ingroup G_Q_API
*/
TAP_DLLEXPORT ITapQuoteAPI *TAP_CDECL CreateTapQuoteAPI(const TapAPIApplicationInfo *appInfo, TAPIINT32 &iResult);
/**
* @brief	銷燬通過CreateTapQuoteAPI函式建立的ITapQuoteAPI物件。
* @param[in] apiObj ITapQuoteAPI物件指標。
* @ingroup G_Q_API
*/
TAP_DLLEXPORT void TAP_CDECL FreeTapQuoteAPI(ITapQuoteAPI *apiObj);
/**
* @brief	獲取TapQuoteAPI的版本資訊
* @ingroup G_Q_API
*/
TAP_DLLEXPORT const TAPICHAR *TAP_CDECL GetTapQuoteAPIVersion();
/**
* @brief	設定API自身儲存資料目錄
* @details	呼叫函式的同時會在path描述的目錄下開啟以年月日（格式TapQuoteAPI[YYYYMMDD].log)命名的檔案，\n
*			沒有此檔案的情況下會試圖建立此檔案。\n
*			檔案中儲存的資料為API接收到的重要資料和API的使用和錯誤日誌。
* @param[in] path 目錄。必須可用，目錄符號Window下為”\\”或者”/”, Linux下為”/”。
* @retval 0 成功
* @retval 非0 錯誤碼
* @operationtype 同步操作
* @ingroup G_Q_LogConfig
*/
TAP_DLLEXPORT TAPIINT32 TAP_CDECL SetTapQuoteAPIDataPath(const TAPICHAR *path);
/**
* @brief	設定API的日誌級別
* @details	設定日誌的輸出級別，只有當實際日誌級別與此處設定的級別相同或更高時，才會將日誌寫入SetTapQuoteAPIDataPath()函式開啟的日誌檔案。\n
* @param[in]	level 日誌級別：\n
*					APILOGLEVEL_NONE	：不記錄日誌\n
*					APILOGLEVEL_ERROR	：記錄Error日誌\n
*					APILOGLEVEL_WARNING	：記錄Error和Warning日誌\n
*					APILOGLEVEL_DEBUG	：記錄Error、Warning和Debug日誌\n
* @retval 0 設定成功
* @retval 非0 錯誤碼
* @operationtype 同步操作
* @ingroup G_Q_LogConfig
*/
TAP_DLLEXPORT TAPIINT32 TAP_CDECL SetTapQuoteAPILogLevel(TAPILOGLEVEL level);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // TAP_QUOTE_API_H