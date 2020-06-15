/////////////////////////////////////////////////////////////////////////
///@company 上海泰琰資訊科技有限公司
///@file TORATstpMdApi.h
///@brief 定義了客戶端介面
///@history 
/////////////////////////////////////////////////////////////////////////

#if !defined(_TORA_TSTPMDAPI_H)
#define _TORA_TSTPMDAPI_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "TORATstpUserApiStruct.h"


#ifdef MD_API_EXPORT
#ifdef WINDOWS
#define MD_API_DLL_EXPORT __declspec(dllexport)
#else
#define MD_API_DLL_EXPORT __attribute__ ((visibility("default")))
#endif
#else
#define MD_API_DLL_EXPORT 
#endif

class CTORATstpMdSpi
{
public:
	///當客戶端與交易後臺建立起通訊連線時（還未登入前），該方法被呼叫。
	virtual void OnFrontConnected(){};
	
	///當客戶端與交易後臺通訊連線斷開時，該方法被呼叫。當發生這個情況後，API會自動重新連線，客戶端可不做處理。
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

	///登入請求響應
	virtual void OnRspUserLogin(CTORATstpRspUserLoginField *pRspUserLogin, CTORATstpRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///登出請求響應
	virtual void OnRspUserLogout(CTORATstpUserLogoutField *pUserLogout, CTORATstpRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///訂閱行情應答
	virtual void OnRspSubMarketData(CTORATstpSpecificSecurityField *pSpecificSecurity, CTORATstpRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///取消訂閱行情應答
	virtual void OnRspUnSubMarketData(CTORATstpSpecificSecurityField *pSpecificSecurity, CTORATstpRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///訂閱特定行情應答
	virtual void OnRspSubSpecialMarketData(CTORATstpSpecificSecurityField *pSpecificSecurity, CTORATstpRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///取消訂閱特定行情應答
	virtual void OnRspUnSubSpecialMarketData(CTORATstpSpecificSecurityField *pSpecificSecurity, CTORATstpRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///訂閱資金流向行情應答
	virtual void OnRspSubFundsFlowMarketData(CTORATstpSpecificSecurityField *pSpecificSecurity, CTORATstpRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///取消訂閱資金流向行情應答
	virtual void OnRspUnSubFundsFlowMarketData(CTORATstpSpecificSecurityField *pSpecificSecurity, CTORATstpRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///深度行情通知
	virtual void OnRtnDepthMarketData(CTORATstpMarketDataField *pDepthMarketData) {};

	///深度行情通知
	virtual void OnRtnSpecialMarketData(CTORATstpSpecialMarketDataField *pSpecialMarketData) {};

	///價格波動異常行情通知
	virtual void OnRtnEffectPriceMarketData(CTORATstpEffectPriceMarketDataField *pEffectPriceMarketData) {};

	///數量波動異常行情通知
	virtual void OnRtnEffectVolumeMarketData(CTORATstpEffectVolumeMarketDataField *pEffectVolumeMarketData) {};

	///資金流向行情通知
	virtual void OnRtnFundsFlowMarketData(CTORATstpFundsFlowMarketDataField *pFundsFlowMarketData) {};
};

class MD_API_DLL_EXPORT CTORATstpMdApi
{
public:
	///建立MdApi
	///@return 創建出的MdApi
	static CTORATstpMdApi *CreateTstpMdApi();
	
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
	///@remark 網路地址的格式為：“protocol://ipaddress:port”，如：”tcp://127.0.0.1:15001”。 
	///@remark “tcp”代表傳輸協議，“127.0.0.1”代表伺服器地址。”15001”代表伺服器埠號。
	virtual void RegisterDeriveServer(char *pszDeriveAddress) = 0;

	///註冊回撥介面
	///@param pSpi 派生自回撥介面類的例項
	virtual void RegisterSpi(CTORATstpMdSpi *pSpi) = 0;
	
	///訂閱行情。
	///@param ppInstrumentID 合約ID  
	///@param nCount 要訂閱/退訂行情的合約個數
	///@remark 
	virtual int SubscribeMarketData(char **ppSecurityID, int nCount, TTORATstpExchangeIDType ExchageID) = 0;

	///退訂行情。
	///@param ppInstrumentID 合約ID  
	///@param nCount 要訂閱/退訂行情的合約個數
	///@remark 
	virtual int UnSubscribeMarketData(char **ppSecurityID, int nCount, TTORATstpExchangeIDType ExchageID) = 0;

	///訂閱特定行情。
	///@param ppInstrumentID 合約ID  
	///@param nCount 要訂閱/退訂行情的合約個數
	///@remark 
	virtual int SubscribeSpecialMarketData(char **ppSecurityID, int nCount, TTORATstpExchangeIDType ExchageID) = 0;

	///退訂特定行情。
	///@param ppInstrumentID 合約ID  
	///@param nCount 要訂閱/退訂行情的合約個數
	///@remark 
	virtual int UnSubscribeSpecialMarketData(char **ppSecurityID, int nCount, TTORATstpExchangeIDType ExchageID) = 0;

	///訂閱資金流向行情。
	///@param ppInstrumentID 合約ID
	///@param nCount 要訂閱/退訂行情的合約個數
	///@remark
	virtual int SubscribeFundsFlowMarketData(char *ppInstrumentID[], int nCount, TTORATstpExchangeIDType ExchageID) = 0;

	///退訂資金流向行情。
	///@param ppInstrumentID 合約ID
	///@param nCount 要訂閱/退訂行情的合約個數
	///@remark
	virtual int UnSubscribeFundsFlowMarketData(char *ppInstrumentID[], int nCount, TTORATstpExchangeIDType ExchageID) = 0;

	///使用者登入請求
	virtual int ReqUserLogin(CTORATstpReqUserLoginField *pReqUserLoginField, int nRequestID) = 0;
	

	///登出請求
	virtual int ReqUserLogout(CTORATstpUserLogoutField *pUserLogout, int nRequestID) = 0;
protected:
	~CTORATstpMdApi(){};
};
#endif
