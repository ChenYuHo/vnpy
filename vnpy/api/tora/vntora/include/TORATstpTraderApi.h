/////////////////////////////////////////////////////////////////////////
///@company 上海泰琰資訊科技有限公司
///@file TORATstpTraderApi.h
///@brief 定義了客戶端介面
///@history 
/////////////////////////////////////////////////////////////////////////

#if !defined(TORA_TSTPTRADERAPI_H)
#define TORA_TSTPTRADERAPI_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "TORATstpUserApiStruct.h"

#ifdef TRADER_API_EXPORT
#ifdef WINDOWS
#define TRADER_API_DLL_EXPORT __declspec(dllexport)
#else
#define TRADER_API_DLL_EXPORT __attribute__ ((visibility("default")))
#endif
#else
#define TRADER_API_DLL_EXPORT 
#endif

class CTORATstpTraderSpi
{
public:
	///當客戶端與交易後臺建立起通訊連線時（還未登入前），該方法被呼叫。
	virtual void OnFrontConnected(){};
	
	///當客戶端與交易後臺通訊連線斷開時，該方法被呼叫。當發生這個情況後，API會自動重新連線，客戶端可不做處理。
	///@param nReason 錯誤原因
	///        -3 連線已斷開
	///        -4 網路讀失敗
	///        -5 網路寫失敗
	///        -6 訂閱流錯誤
	///        -7 流序號錯誤
	///        -8 錯誤的心跳報文
	///        -9 錯誤的報文
	virtual void OnFrontDisconnected(int nReason){};
				
	///錯誤應答
	virtual void OnRspError(CTORATstpRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};
	
		
	//登入應答	
	virtual void OnRspUserLogin(CTORATstpRspUserLoginField *pRspUserLoginField, CTORATstpRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};
			
	//登出應答	
	virtual void OnRspUserLogout(CTORATstpUserLogoutField *pUserLogoutField, CTORATstpRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};
			
	//修改密碼應答	
	virtual void OnRspUserPasswordUpdate(CTORATstpUserPasswordUpdateField *pUserPasswordUpdateField, CTORATstpRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};
			
	//請求錄入裝置序列應答	
	virtual void OnRspInputDeviceSerial(CTORATstpRspInputDeviceSerialField *pRspInputDeviceSerialField, CTORATstpRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};
			
	//報單錄入應答	
	virtual void OnRspOrderInsert(CTORATstpInputOrderField *pInputOrderField, CTORATstpRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};
			
	//報單回報
	virtual void OnRtnOrder(CTORATstpOrderField *pOrder) {};
			
	//報單錯誤回報
	virtual void OnErrRtnOrderInsert(CTORATstpInputOrderField *pInputOrder, CTORATstpRspInfoField *pRspInfo) {};
				
	//撤單應答	
	virtual void OnRspOrderAction(CTORATstpInputOrderActionField *pInputOrderActionField, CTORATstpRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};
			
	//撤單錯誤回報
	virtual void OnErrRtnOrderAction(CTORATstpOrderActionField *pOrderAction, CTORATstpRspInfoField *pRspInfo) {};
				
	//成交回報
	virtual void OnRtnTrade(CTORATstpTradeField *pTrade) {};
			
	//推送市場狀態
	virtual void OnRtnMarketStatus(CTORATstpMarketStatusField *pMarketStatus) {};
		
	//條件單錄入請求響應	
	virtual void OnRspCondOrderInsert(CTORATstpInputCondOrderField *pInputCondOrderField, CTORATstpRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};
			
	//條件單通知
	virtual void OnRtnCondOrder(CTORATstpConditionOrderField *pConditionOrder) {};
			
	//條件單錄入錯誤回報
	virtual void OnErrRtnCondOrderInsert(CTORATstpInputCondOrderField *pInputCondOrder, CTORATstpRspInfoField *pRspInfo) {};
				
	//條件單操作請求響應	
	virtual void OnRspCondOrderAction(CTORATstpInputCondOrderActionField *pInputCondOrderActionField, CTORATstpRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};
			
	//條件單撤單操作錯誤回報
	virtual void OnErrRtnCondOrderAction(CTORATstpInputCondOrderActionField *pInputCondOrderAction, CTORATstpRspInfoField *pRspInfo) {};
				
	//查詢集中交易系統資金響應	
	virtual void OnRspInquiryJZFund(CTORATstpRspInquiryJZFundField *pRspInquiryJZFundField, CTORATstpRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};
			
	//資金轉移請求應答	
	virtual void OnRspTransferFund(CTORATstpInputTransferFundField *pInputTransferFundField, CTORATstpRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};
			
	//資金轉移回報
	virtual void OnRtnTransferFund(CTORATstpTransferFundField *pTransferFund) {};
		
	//資金轉移錯誤回報
	virtual void OnErrRtnTransferFund(CTORATstpInputTransferFundField *pInputTransferFund, CTORATstpRspInfoField *pRspInfo) {};
			
	//倉位轉移回報
	virtual void OnRtnTransferPosition(CTORATstpTransferPositionField *pTransferPosition) {};
		
	//倉位轉移錯誤回報
	virtual void OnErrRtnTransferPosition(CTORATstpInputTransferPositionField *pInputTransferPosition, CTORATstpRspInfoField *pRspInfo) {};
			
	//擔保品劃轉響應	
	virtual void OnRspTransferCollateral(CTORATstpInputTransferCollateralField *pInputTransferCollateralField, CTORATstpRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};
			
	//查詢銀行賬戶餘額響應	
	virtual void OnRspInquiryBankAccountFund(CTORATstpRspInquiryBankAccountFundField *pRspInquiryBankAccountFundField, CTORATstpRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};
			
	//交易成交集中度查詢響應	
	virtual void OnRspInquiryTradeConcentration(CTORATstpInquiryTradeConcentrationField *pInquiryTradeConcentrationField, CTORATstpRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};
			
	//交易通知
	virtual void OnRtnTradingNotice(CTORATstpTradingNoticeField *pTradingNotice) {};
		
	//查詢最大委託量應答	
	virtual void OnRspInquiryMaxOrderVolume(CTORATstpRspInquiryMaxOrderVolumeField *pRspInquiryMaxOrderVolumeField, CTORATstpRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};
			
	//外圍系統倉位轉移回報
	virtual void OnRtnPeripheryTransferPosition(CTORATstpPeripheryPositionTransferDetailField *pPeripheryPositionTransferDetail) {};
			
	//查詢歷史委託響應	
	virtual void OnRspInquiryHistoryOrder(CTORATstpHistoryOrderField *pHistoryOrderField, CTORATstpRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};
			
	//查詢歷史成交響應	
	virtual void OnRspInquiryHistoryTrade(CTORATstpHistoryTradeField *pHistoryTradeField, CTORATstpRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};
		
	//查詢交易所
	virtual void OnRspQryExchange(CTORATstpExchangeField *pExchange, CTORATstpRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {}; 
			
	//查詢實時行情
	virtual void OnRspQryMarketData(CTORATstpMarketDataField *pMarketData, CTORATstpRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {}; 
			
	//查詢證券資訊
	virtual void OnRspQrySecurity(CTORATstpSecurityField *pSecurity, CTORATstpRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {}; 
			
	//查詢ETF清單資訊
	virtual void OnRspQryETFFile(CTORATstpETFFileField *pETFFile, CTORATstpRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {}; 
			
	//查詢ETF成份證券資訊
	virtual void OnRspQryETFBasket(CTORATstpETFBasketField *pETFBasket, CTORATstpRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {}; 
			
	//查詢新股資訊
	virtual void OnRspQryIPOInfo(CTORATstpIPOInfoField *pIPOInfo, CTORATstpRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {}; 
			
	//查詢代理關係
	virtual void OnRspQryBUProxy(CTORATstpBUProxyField *pBUProxy, CTORATstpRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {}; 
			
	//查詢User
	virtual void OnRspQryUser(CTORATstpUserField *pUser, CTORATstpRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {}; 
			
	//查詢投資者
	virtual void OnRspQryInvestor(CTORATstpInvestorField *pInvestor, CTORATstpRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {}; 
			
	//查詢股東賬戶
	virtual void OnRspQryShareholderAccount(CTORATstpShareholderAccountField *pShareholderAccount, CTORATstpRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {}; 
			
	//報單查詢
	virtual void OnRspQryOrder(CTORATstpOrderField *pOrder, CTORATstpRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {}; 
			
	//查詢撤單
	virtual void OnRspQryOrderAction(CTORATstpOrderActionField *pOrderAction, CTORATstpRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {}; 
			
	//成交查詢
	virtual void OnRspQryTrade(CTORATstpTradeField *pTrade, CTORATstpRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {}; 
			
	//資金賬戶查詢
	virtual void OnRspQryTradingAccount(CTORATstpTradingAccountField *pTradingAccount, CTORATstpRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {}; 
			
	//投資者持倉查詢
	virtual void OnRspQryPosition(CTORATstpPositionField *pPosition, CTORATstpRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {}; 
			
	//查詢基礎交易費用
	virtual void OnRspQryTradingFee(CTORATstpTradingFeeField *pTradingFee, CTORATstpRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {}; 
			
	//查詢佣金費率
	virtual void OnRspQryInvestorTradingFee(CTORATstpInvestorTradingFeeField *pInvestorTradingFee, CTORATstpRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {}; 
			
	//查詢新股申購額度
	virtual void OnRspQryIPOQuota(CTORATstpIPOQuotaField *pIPOQuota, CTORATstpRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {}; 
			
	//查詢市場
	virtual void OnRspQryMarket(CTORATstpMarketField *pMarket, CTORATstpRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {}; 
			
	//報單明細資金查詢
	virtual void OnRspQryOrderFundDetail(CTORATstpOrderFundDetailField *pOrderFundDetail, CTORATstpRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {}; 
			
	//查詢資金轉移流水
	virtual void OnRspQryFundTransferDetail(CTORATstpFundTransferDetailField *pFundTransferDetail, CTORATstpRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {}; 
			
	//查詢持倉轉移流水
	virtual void OnRspQryPositionTransferDetail(CTORATstpPositionTransferDetailField *pPositionTransferDetail, CTORATstpRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {}; 
			
	//請求投資者質押持倉查詢響應
	virtual void OnRspQryPledgePosition(CTORATstpPledgePositionField *pPledgePosition, CTORATstpRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {}; 
			
	//請求證券質押資訊查詢響應
	virtual void OnRspQryPledgeInfo(CTORATstpPledgeInfoField *pPledgeInfo, CTORATstpRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {}; 
			
	//請求可轉債資訊查詢響應
	virtual void OnRspQryConversionBondInfo(CTORATstpConversionBondInfoField *pConversionBondInfo, CTORATstpRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {}; 
			
	//請求債券回售資訊查詢響應
	virtual void OnRspQryBondPutbackInfo(CTORATstpBondPutbackInfoField *pBondPutbackInfo, CTORATstpRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {}; 
			
	//請求標準券額度查詢響應
	virtual void OnRspQryStandardBondPosition(CTORATstpStandardBondPositionField *pStandardBondPosition, CTORATstpRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {}; 
			
	//查詢實時特別行情響應
	virtual void OnRspQrySpecialMarketData(CTORATstpSpecialMarketDataField *pSpecialMarketData, CTORATstpRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {}; 
			
	//查詢未到期債券質押回購委託響應
	virtual void OnRspQryPrematurityRepoOrder(CTORATstpPrematurityRepoOrderField *pPrematurityRepoOrder, CTORATstpRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {}; 
			
	//查詢股東引數響應
	virtual void OnRspQryShareholderParam(CTORATstpShareholderParamField *pShareholderParam, CTORATstpRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {}; 
			
	//查詢外圍系統倉位調撥流水
	virtual void OnRspQryPeripheryPositionTransferDetail(CTORATstpPeripheryPositionTransferDetailField *pPeripheryPositionTransferDetail, CTORATstpRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {}; 
			
	//查詢投資者條件單限制引數響應
	virtual void OnRspQryInvestorCondOrderLimitParam(CTORATstpInvestorCondOrderLimitParamField *pInvestorCondOrderLimitParam, CTORATstpRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {}; 
			
	//查詢條件單響應
	virtual void OnRspQryCondOrder(CTORATstpCondOrderField *pCondOrder, CTORATstpRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {}; 
			
	//查詢條件單撤單響應
	virtual void OnRspQryCondOrderAction(CTORATstpCondOrderActionField *pCondOrderAction, CTORATstpRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {}; 
			
	//查詢交易通知響應
	virtual void OnRspQryTradingNotice(CTORATstpTradingNoticeField *pTradingNotice, CTORATstpRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {}; 
			
	//查詢新股申購配號結果響應
	virtual void OnRspQryIPONumberResult(CTORATstpIPONumberResultField *pIPONumberResult, CTORATstpRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {}; 
			
	//查詢新股申購中籤結果響應
	virtual void OnRspQryIPOMatchNumberResult(CTORATstpIPOMatchNumberResultField *pIPOMatchNumberResult, CTORATstpRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {}; 
			
};

class TRADER_API_DLL_EXPORT CTORATstpTraderApi
{
public:
	///建立TraderApi
	///@param pszFlowPath 存貯訂閱資訊檔案的目錄，預設為當前目錄
	///@param bEncrpyt 網路資料是否加密傳輸，預設不加密
	///@return 創建出的TraderApi
	
	static CTORATstpTraderApi *CreateTstpTraderApi(const char *pszFlowPath = "", bool bEncrypt = false);
	
	///獲取API版本號
	///@return 版本號
	static const char* GetApiVersion();
	
	///刪除介面物件本身
	///@remark 不再使用本介面物件時,呼叫該函式刪除介面物件
	virtual void Release() = 0;
	
	///初始化
	///@remark 初始化執行環境,只有呼叫後,接口才開始工作
	virtual void Init() = 0;
	
	///等待介面執行緒結束執行
	///@return 執行緒退出程式碼
	virtual int Join() = 0;
	
	///註冊前置機網路地址
	///@param pszFrontAddress：前置機網路地址。
	///@remark 網路地址的格式為：“protocol://ipaddress:port”，如：”tcp://127.0.0.1:17001”。 
	///@remark “tcp”代表傳輸協議，“127.0.0.1”代表伺服器地址。”17001”代表伺服器埠號。
	virtual void RegisterFront(char *pszFrontAddress) = 0;

	///註冊名字伺服器網路地址
	///@param pszNsAddress：名字伺服器網路地址。
	///@remark 網路地址的格式為：“protocol://ipaddress:port”，如：”tcp://127.0.0.1:12001”。 
	///@remark “tcp”代表傳輸協議，“127.0.0.1”代表伺服器地址。”12001”代表伺服器埠號。
	///@remark RegisterNameServer優先於RegisterFront
	virtual void RegisterNameServer(char *pszNsAddress) = 0;
	
	///註冊衍生服務伺服器網路地址
	///@param pszNsAddress：衍生服務伺服器網路地址。
	///@remark 網路地址的格式為：“protocol://ipaddress:port”，如：”tcp://127.0.0.1:16001”。 
	///@remark “tcp”代表傳輸協議，“127.0.0.1”代表伺服器地址。”16001”代表伺服器埠號。
	virtual void RegisterDeriveServer(char *pszDeriveAddress) = 0;

	///註冊回撥介面
	///@param pSpi 派生自回撥介面類的例項
	virtual void RegisterSpi(CTORATstpTraderSpi *pSpi) = 0;
	
	///訂閱私有流。
	///@param nResumeType 私有流重傳方式  
	///        TORA_TERT_RESTART:從本交易日開始重傳
	///        TORA_TERT_RESUME:從上次收到的續傳
	///        TORA_TERT_QUICK:只傳送登入後私有流的內容
	///@remark 該方法要在Init方法前呼叫。若不呼叫則不會收到私有流的資料。
	virtual void SubscribePrivateTopic(TORA_TE_RESUME_TYPE nResumeType) = 0;
	
	///訂閱公共流。
	///@param nResumeType 公共流重傳方式  
	///        TORA_TERT_RESTART:從本交易日開始重傳
	///        TORA_TERT_RESUME:從上次收到的續傳
	///        TORA_TERT_QUICK:只傳送登入後公共流的內容
	///@remark 該方法要在Init方法前呼叫。若不呼叫則不會收到公共流的資料。
	virtual void SubscribePublicTopic(TORA_TE_RESUME_TYPE nResumeType) = 0;
	
	
	//登入請求		
	virtual int ReqUserLogin(CTORATstpReqUserLoginField *pReqUserLoginField, int nRequestID) = 0;
	
	//登出請求		
	virtual int ReqUserLogout(CTORATstpUserLogoutField *pUserLogoutField, int nRequestID) = 0;
	
	//修改密碼請求		
	virtual int ReqUserPasswordUpdate(CTORATstpUserPasswordUpdateField *pUserPasswordUpdateField, int nRequestID) = 0;
	
	//請求錄入裝置序列		
	virtual int ReqInputDeviceSerial(CTORATstpReqInputDeviceSerialField *pReqInputDeviceSerialField, int nRequestID) = 0;
	
	//報單錄入請求		
	virtual int ReqOrderInsert(CTORATstpInputOrderField *pInputOrderField, int nRequestID) = 0;
	
	//撤單請求		
	virtual int ReqOrderAction(CTORATstpInputOrderActionField *pInputOrderActionField, int nRequestID) = 0;
	
	//條件單錄入請求		
	virtual int ReqCondOrderInsert(CTORATstpInputCondOrderField *pInputCondOrderField, int nRequestID) = 0;
	
	//條件單操作請求		
	virtual int ReqCondOrderAction(CTORATstpInputCondOrderActionField *pInputCondOrderActionField, int nRequestID) = 0;
	
	//查詢集中交易系統資金請求		
	virtual int ReqInquiryJZFund(CTORATstpReqInquiryJZFundField *pReqInquiryJZFundField, int nRequestID) = 0;
	
	//資金轉移請求		
	virtual int ReqTransferFund(CTORATstpInputTransferFundField *pInputTransferFundField, int nRequestID) = 0;
	
	//擔保品劃轉請求		
	virtual int ReqTransferCollateral(CTORATstpInputTransferCollateralField *pInputTransferCollateralField, int nRequestID) = 0;
	
	//查詢銀行賬戶餘額請求		
	virtual int ReqInquiryBankAccountFund(CTORATstpReqInquiryBankAccountFundField *pReqInquiryBankAccountFundField, int nRequestID) = 0;
	
	//查詢交易成交集中度		
	virtual int ReqInquiryTradeConcentration(CTORATstpInquiryTradeConcentrationField *pInquiryTradeConcentrationField, int nRequestID) = 0;
	
	//查詢最大委託量請求		
	virtual int ReqInquiryMaxOrderVolume(CTORATstpReqInquiryMaxOrderVolumeField *pReqInquiryMaxOrderVolumeField, int nRequestID) = 0;
	
	//查詢歷史委託請求		
	virtual int ReqInquiryHistoryOrder(CTORATstpQryHistoryOrderField *pQryHistoryOrderField, int nRequestID) = 0;
	
	//查詢歷史成交請求		
	virtual int ReqInquiryHistoryTrade(CTORATstpQryHistoryTradeField *pQryHistoryTradeField, int nRequestID) = 0;
	
	//查詢交易所		
	virtual int ReqQryExchange(CTORATstpQryExchangeField *pQryExchangeField, int nRequestID) = 0;
	
	//查詢實時行情		
	virtual int ReqQryMarketData(CTORATstpQryMarketDataField *pQryMarketDataField, int nRequestID) = 0;
	
	//查詢證券資訊		
	virtual int ReqQrySecurity(CTORATstpQrySecurityField *pQrySecurityField, int nRequestID) = 0;
	
	//查詢ETF清單資訊		
	virtual int ReqQryETFFile(CTORATstpQryETFFileField *pQryETFFileField, int nRequestID) = 0;
	
	//查詢ETF成份證券資訊		
	virtual int ReqQryETFBasket(CTORATstpQryETFBasketField *pQryETFBasketField, int nRequestID) = 0;
	
	//查詢新股資訊		
	virtual int ReqQryIPOInfo(CTORATstpQryIPOInfoField *pQryIPOInfoField, int nRequestID) = 0;
	
	//查詢代理關係		
	virtual int ReqQryBUProxy(CTORATstpQryBUProxyField *pQryBUProxyField, int nRequestID) = 0;
	
	//查詢User		
	virtual int ReqQryUser(CTORATstpQryUserField *pQryUserField, int nRequestID) = 0;
	
	//查詢投資者		
	virtual int ReqQryInvestor(CTORATstpQryInvestorField *pQryInvestorField, int nRequestID) = 0;
	
	//查詢股東賬戶		
	virtual int ReqQryShareholderAccount(CTORATstpQryShareholderAccountField *pQryShareholderAccountField, int nRequestID) = 0;
	
	//報單查詢		
	virtual int ReqQryOrder(CTORATstpQryOrderField *pQryOrderField, int nRequestID) = 0;
	
	//查詢撤單		
	virtual int ReqQryOrderAction(CTORATstpQryOrderActionField *pQryOrderActionField, int nRequestID) = 0;
	
	//成交查詢		
	virtual int ReqQryTrade(CTORATstpQryTradeField *pQryTradeField, int nRequestID) = 0;
	
	//資金賬戶查詢		
	virtual int ReqQryTradingAccount(CTORATstpQryTradingAccountField *pQryTradingAccountField, int nRequestID) = 0;
	
	//投資者持倉查詢		
	virtual int ReqQryPosition(CTORATstpQryPositionField *pQryPositionField, int nRequestID) = 0;
	
	//查詢基礎交易費用		
	virtual int ReqQryTradingFee(CTORATstpQryTradingFeeField *pQryTradingFeeField, int nRequestID) = 0;
	
	//查詢佣金費率		
	virtual int ReqQryInvestorTradingFee(CTORATstpQryInvestorTradingFeeField *pQryInvestorTradingFeeField, int nRequestID) = 0;
	
	//查詢新股申購額度		
	virtual int ReqQryIPOQuota(CTORATstpQryIPOQuotaField *pQryIPOQuotaField, int nRequestID) = 0;
	
	//查詢市場		
	virtual int ReqQryMarket(CTORATstpQryMarketField *pQryMarketField, int nRequestID) = 0;
	
	//報單明細資金查詢		
	virtual int ReqQryOrderFundDetail(CTORATstpQryOrderFundDetailField *pQryOrderFundDetailField, int nRequestID) = 0;
	
	//查詢資金轉移流水		
	virtual int ReqQryFundTransferDetail(CTORATstpQryFundTransferDetailField *pQryFundTransferDetailField, int nRequestID) = 0;
	
	//查詢持倉轉移流水		
	virtual int ReqQryPositionTransferDetail(CTORATstpQryPositionTransferDetailField *pQryPositionTransferDetailField, int nRequestID) = 0;
	
	//請求投資者質押持倉查詢		
	virtual int ReqQryPledgePosition(CTORATstpQryPledgePositionField *pQryPledgePositionField, int nRequestID) = 0;
	
	//請求證券質押資訊查詢		
	virtual int ReqQryPledgeInfo(CTORATstpQryPledgeInfoField *pQryPledgeInfoField, int nRequestID) = 0;
	
	//請求可轉債資訊查詢		
	virtual int ReqQryConversionBondInfo(CTORATstpQryConversionBondInfoField *pQryConversionBondInfoField, int nRequestID) = 0;
	
	//請求債券回售資訊查詢		
	virtual int ReqQryBondPutbackInfo(CTORATstpQryBondPutbackInfoField *pQryBondPutbackInfoField, int nRequestID) = 0;
	
	//請求標準券額度查詢		
	virtual int ReqQryStandardBondPosition(CTORATstpQryStandardBondPositionField *pQryStandardBondPositionField, int nRequestID) = 0;
	
	//查詢實時特別行情		
	virtual int ReqQrySpecialMarketData(CTORATstpQrySpecialMarketDataField *pQrySpecialMarketDataField, int nRequestID) = 0;
	
	//查詢未到期債券質押回購委託		
	virtual int ReqQryPrematurityRepoOrder(CTORATstpQryPrematurityRepoOrderField *pQryPrematurityRepoOrderField, int nRequestID) = 0;
	
	//查詢股東引數		
	virtual int ReqQryShareholderParam(CTORATstpQryShareholderParamField *pQryShareholderParamField, int nRequestID) = 0;
	
	//查詢外圍系統倉位調撥流水		
	virtual int ReqQryPeripheryPositionTransferDetail(CTORATstpQryPeripheryPositionTransferDetailField *pQryPeripheryPositionTransferDetailField, int nRequestID) = 0;
	
	//查詢投資者條件單限制引數請求		
	virtual int ReqQryInvestorCondOrderLimitParam(CTORATstpQryInvestorCondOrderLimitParamField *pQryInvestorCondOrderLimitParamField, int nRequestID) = 0;
	
	//查詢條件單請求		
	virtual int ReqQryCondOrder(CTORATstpQryCondOrderField *pQryCondOrderField, int nRequestID) = 0;
	
	//查詢條件單撤單請求		
	virtual int ReqQryCondOrderAction(CTORATstpQryCondOrderActionField *pQryCondOrderActionField, int nRequestID) = 0;
	
	//查詢交易通知請求		
	virtual int ReqQryTradingNotice(CTORATstpQryTradingNoticeField *pQryTradingNoticeField, int nRequestID) = 0;
	
	//查詢新股申購配號結果		
	virtual int ReqQryIPONumberResult(CTORATstpQryIPONumberResultField *pQryIPONumberResultField, int nRequestID) = 0;
	
	//查詢新股申購中籤結果		
	virtual int ReqQryIPOMatchNumberResult(CTORATstpQryIPOMatchNumberResultField *pQryIPOMatchNumberResultField, int nRequestID) = 0;
	
	
protected:
	~CTORATstpTraderApi(){};
};

#endif
