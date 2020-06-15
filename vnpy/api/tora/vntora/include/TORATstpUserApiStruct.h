/////////////////////////////////////////////////////////////////////////
///@company 上海泰琰資訊科技有限公司
///@file TORATstpUserApiStruct.h
///@brief 定義了客戶端介面使用的業務資料結構
///@history 
/////////////////////////////////////////////////////////////////////////

#if !defined(_TORA_TSTPCSTRUCT_H)
#define _TORA_TSTPCSTRUCT_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "TORATstpUserApiDataType.h"

/// fens使用者資訊
struct CTORATstpFensUserInfoField
{
		
	///登入賬戶
	TTORATstpLogInAccountType	LogInAccount;

	///登入賬戶型別
	TTORATstpLogInAccountTypeType	LogInAccountType;


};

/// 價格異常波動行情
struct CTORATstpEffectPriceMarketDataField
{
		
	///交易所程式碼
	TTORATstpExchangeIDType	ExchangeID;

	///合約程式碼
	TTORATstpSecurityIDType	SecurityID;

	///最新價
	TTORATstpPriceType	LastPrice;

	///總成交數量
	TTORATstpLongVolumeType	TotalVolume;

	///成交金額
	TTORATstpMoneyType	Turnover;

	///最後修改時間
	TTORATstpTimeType	UpdateTime;

	///最後修改毫秒
	TTORATstpMillisecType	UpdateMillisec;


};

/// 數量異常波動行情
struct CTORATstpEffectVolumeMarketDataField
{
		
	///交易所程式碼
	TTORATstpExchangeIDType	ExchangeID;

	///合約程式碼
	TTORATstpSecurityIDType	SecurityID;

	///最新價
	TTORATstpPriceType	LastPrice;

	///總成交數量
	TTORATstpLongVolumeType	TotalVolume;

	///成交金額
	TTORATstpMoneyType	Turnover;

	///最後修改時間
	TTORATstpTimeType	UpdateTime;

	///最後修改毫秒
	TTORATstpMillisecType	UpdateMillisec;


};

/// 資金流向資料行情
struct CTORATstpFundsFlowMarketDataField
{
		
	///交易所程式碼
	TTORATstpExchangeIDType	ExchangeID;

	///合約程式碼
	TTORATstpSecurityIDType	SecurityID;

	///最後修改時間
	TTORATstpTimeType	UpdateTime;

	///最後修改毫秒
	TTORATstpMillisecType	UpdateMillisec;

	///散戶買入金額
	TTORATstpMoneyType	RetailBuyTurnover;

	///散戶買入數量
	TTORATstpLongVolumeType	RetailBuyVolume;

	///散戶買入筆數
	TTORATstpLongVolumeType	RetailBuyAmount;

	///散戶賣出金額
	TTORATstpMoneyType	RetailSellTurnover;

	///散戶賣出數量
	TTORATstpLongVolumeType	RetailSellVolume;

	///散戶賣出筆數
	TTORATstpLongVolumeType	RetailSellAmount;

	///中戶買入金額
	TTORATstpMoneyType	MiddleBuyTurnover;

	///中戶買入數量
	TTORATstpLongVolumeType	MiddleBuyVolume;

	///中戶買入筆數
	TTORATstpLongVolumeType	MiddleBuyAmount;

	///中戶賣出金額
	TTORATstpMoneyType	MiddleSellTurnover;

	///中戶賣出數量
	TTORATstpLongVolumeType	MiddleSellVolume;

	///中戶賣出筆數
	TTORATstpLongVolumeType	MiddleSellAmount;

	///大戶買入金額
	TTORATstpMoneyType	LargeBuyTurnover;

	///大戶買入數量
	TTORATstpLongVolumeType	LargeBuyVolume;

	///大戶買入筆數
	TTORATstpLongVolumeType	LargeBuyAmount;

	///大戶賣出金額
	TTORATstpMoneyType	LargeSellTurnover;

	///大戶賣出數量
	TTORATstpLongVolumeType	LargeSellVolume;

	///大戶賣出筆數
	TTORATstpLongVolumeType	LargeSellAmount;

	///機構買入金額
	TTORATstpMoneyType	InstitutionBuyTurnover;

	///機構買入數量
	TTORATstpLongVolumeType	InstitutionBuyVolume;

	///機構買入筆數
	TTORATstpLongVolumeType	InstitutionBuyAmount;

	///機構賣出金額
	TTORATstpMoneyType	InstitutionSellTurnover;

	///機構賣出數量
	TTORATstpLongVolumeType	InstitutionSellVolume;

	///機構賣出筆數
	TTORATstpLongVolumeType	InstitutionSellAmount;


};

/// 登入請求
struct CTORATstpReqUserLoginField
{
		
	///登入賬戶
	TTORATstpLogInAccountType	LogInAccount;

	///登入賬戶型別
	TTORATstpLogInAccountTypeType	LogInAccountType;

	///密碼(密碼認證時必填)
	TTORATstpPasswordType	Password;

	///使用者端產品資訊
	TTORATstpProductInfoType	UserProductInfo;

	///介面端產品資訊
	TTORATstpProductInfoType	InterfaceProductInfo;

	///協議資訊
	TTORATstpProtocolInfoType	ProtocolInfo;

	///Mac地址
	TTORATstpMacAddressType	MacAddress;

	///動態密碼
	TTORATstpPasswordType	OneTimePassword;

	///終端IP地址
	TTORATstpIPAddressType	ClientIPAddress;

	///介面語言
	TTORATstpLangType	Lang;

	///終端資訊
	TTORATstpTerminalInfoType	TerminalInfo;

	///閘道器Mac地址
	TTORATstpMacAddressType	GWMacAddress;

	///閘道器內網IP地址
	TTORATstpIPAddressType	GWInnerIPAddress;

	///閘道器外網IP地址
	TTORATstpIPAddressType	GWOuterIPAddress;

	///經紀公司部門程式碼（以資金賬號方式登入時必填）
	TTORATstpDepartmentIDType	DepartmentID;

	///硬碟序列號
	TTORATstpHDSerialType	HDSerial;

	///認證方式(指紋認證時必填)
	TTORATstpAuthModeType	AuthMode;

	///裝置標識(指紋認證時必填)
	TTORATstpDeviceIDType	DeviceID;

	///裝置序列號(指紋認證時必填)
	TTORATstpDeviceSerialType	DeviceSerial;


};

/// 登入應答
struct CTORATstpRspUserLoginField
{
		
	///登入成功時間
	TTORATstpTimeType	LoginTime;

	///登入賬戶
	TTORATstpLogInAccountType	LogInAccount;

	///登入賬戶型別
	TTORATstpLogInAccountTypeType	LogInAccountType;

	///交易系統名稱
	TTORATstpSystemNameType	SystemName;

	///前置編號
	TTORATstpFrontIDType	FrontID;

	///會話編號
	TTORATstpSessionIDType	SessionID;

	///最大報單引用
	TTORATstpOrderRefType	MaxOrderRef;

	///私有流長度
	TTORATstpVolumeType	PrivateFlowCount;

	///公有流長度
	TTORATstpVolumeType	PublicFlowCount;

	///交易發生的日期
	TTORATstpDateType	TradingDay;

	///使用者程式碼
	TTORATstpUserIDType	UserID;

	///使用者名稱稱
	TTORATstpUserNameType	UserName;

	///使用者型別
	TTORATstpUserTypeType	UserType;

	///經紀公司部門程式碼
	TTORATstpDepartmentIDType	DepartmentID;

	///終端IP地址
	TTORATstpIPAddressType	ClientIPAddress;

	///Mac地址
	TTORATstpMacAddressType	MacAddress;

	///硬碟序列號
	TTORATstpHDSerialType	HDSerial;

	///通訊流量
	TTORATstpCommFluxType	CommFlux;


};

/// 響應資訊
struct CTORATstpRspInfoField
{
		
	///錯誤程式碼
	TTORATstpErrorIDType	ErrorID;

	///錯誤資訊
	TTORATstpErrorMsgType	ErrorMsg;


};

/// 使用者登出
struct CTORATstpUserLogoutField
{
		
	///使用者程式碼
	TTORATstpUserIDType	UserID;


};

/// 強制交易員退出
struct CTORATstpForceUserLogoutField
{
		
	///使用者程式碼
	TTORATstpUserIDType	UserID;


};

/// 重置使用者密碼
struct CTORATstpUserPasswordUpdateField
{
		
	///使用者程式碼
	TTORATstpUserIDType	UserID;

	///舊密碼
	TTORATstpPasswordType	OldPassword;

	///新密碼
	TTORATstpPasswordType	NewPassword;


};

/// 請求錄入裝置序列
struct CTORATstpReqInputDeviceSerialField
{
		
	///使用者程式碼
	TTORATstpUserIDType	UserID;

	///裝置標識
	TTORATstpDeviceIDType	DeviceID;

	///裝置序列號
	TTORATstpDeviceSerialType	DeviceSerial;


};

/// 請求錄入裝置序列應答
struct CTORATstpRspInputDeviceSerialField
{
		
	///使用者程式碼
	TTORATstpUserIDType	UserID;


};

/// 啟用使用者
struct CTORATstpActivateUserField
{
		
	///使用者程式碼
	TTORATstpUserIDType	UserID;


};

/// 使用者會話標識
struct CTORATstpVerifyUserPasswordField
{
		
	///使用者程式碼
	TTORATstpUserIDType	UserID;

	///密碼
	TTORATstpPasswordType	Password;


};

/// 輸入報單
struct CTORATstpInputOrderField
{
		
	///投資者程式碼
	TTORATstpInvestorIDType	InvestorID;

	///合約在系統中的編號
	TTORATstpSecurityIDType	SecurityID;

	///投資者說明的對報單的唯一引用
	TTORATstpOrderRefType	OrderRef;

	///使用者程式碼
	TTORATstpUserIDType	UserID;

	///限價單或市價單
	TTORATstpOrderPriceTypeType	OrderPriceType;

	///1．買2．賣
	TTORATstpDirectionType	Direction;

	///按位元組表示各單個合約的開平方向
	TTORATstpCombOffsetFlagType	CombOffsetFlag;

	///按位元組表示各單個合約的組合套保標誌
	TTORATstpCombHedgeFlagType	CombHedgeFlag;

	///限價單價格
	TTORATstpPriceType	LimitPrice;

	///報單數量
	TTORATstpVolumeType	VolumeTotalOriginal;

	///IOC、GFS、GFD、GTD、GTC、GFA
	TTORATstpTimeConditionType	TimeCondition;

	///AV、MV、CV
	TTORATstpVolumeConditionType	VolumeCondition;

	///當成交量型別為MV時有效
	TTORATstpVolumeType	MinVolume;

	///強平原因
	TTORATstpForceCloseReasonType	ForceCloseReason;

	///請求編號
	TTORATstpRequestIDType	RequestID;

	///使用者強評標誌
	TTORATstpBoolType	UserForceClose;

	///互換單標誌
	TTORATstpBoolType	IsSwapOrder;

	///一個交易所的編號
	TTORATstpExchangeIDType	ExchangeID;

	///目前該欄位存放的是上證所和深圳的股東程式碼。
	TTORATstpShareholderIDType	ShareholderID;

	///投資單元程式碼
	TTORATstpBusinessUnitIDType	BusinessUnitID;

	///資金賬戶
	TTORATstpAccountIDType	AccountID;

	///IP地址
	TTORATstpIPAddressType	IPAddress;

	///Mac地址
	TTORATstpMacAddressType	MacAddress;

	///頭寸型別
	TTORATstpCreditPositionTypeType	CreditPositionType;

	///報單編號
	TTORATstpOrderSysIDType	OrderSysID;

	///終端資訊
	TTORATstpTerminalInfoType	TerminalInfo;

	///長字串附加資訊
	TTORATstpBigsInfoType	BInfo;

	///短字串附加資訊
	TTORATstpShortsInfoType	SInfo;

	///整形附加資訊
	TTORATstpIntInfoType	IInfo;

	///轉入交易單元程式碼(僅在轉託管操作時有效)
	TTORATstpPbuIDType	TransfereePbuID;

	///委託方式
	TTORATstpOperwayType	Operway;

	///條件檢查
	TTORATstpCondCheckType	CondCheck;

	///硬碟序列號
	TTORATstpHDSerialType	HDSerial;


};

/// 報單
struct CTORATstpOrderField
{
		
	///投資者程式碼
	TTORATstpInvestorIDType	InvestorID;

	///合約在系統中的編號
	TTORATstpSecurityIDType	SecurityID;

	///投資者說明的對報單的唯一引用
	TTORATstpOrderRefType	OrderRef;

	///使用者程式碼
	TTORATstpUserIDType	UserID;

	///限價單或市價單
	TTORATstpOrderPriceTypeType	OrderPriceType;

	///1．買2．賣
	TTORATstpDirectionType	Direction;

	///按位元組表示各單個合約的開平方向
	TTORATstpCombOffsetFlagType	CombOffsetFlag;

	///按位元組表示各單個合約的組合套保標誌
	TTORATstpCombHedgeFlagType	CombHedgeFlag;

	///限價單價格
	TTORATstpPriceType	LimitPrice;

	///報單數量
	TTORATstpVolumeType	VolumeTotalOriginal;

	///IOC、GFS、GFD、GTD、GTC、GFA
	TTORATstpTimeConditionType	TimeCondition;

	///AV、MV、CV
	TTORATstpVolumeConditionType	VolumeCondition;

	///當成交量型別為MV時有效
	TTORATstpVolumeType	MinVolume;

	///強平原因
	TTORATstpForceCloseReasonType	ForceCloseReason;

	///請求編號
	TTORATstpRequestIDType	RequestID;

	///本地報單順序號
	TTORATstpOrderLocalIDType	OrderLocalID;

	///交易所程式碼
	TTORATstpExchangeIDType	ExchangeID;

	///交易所下的交易市場，如滬A、滬B市場
	TTORATstpMarketIDType	MarketID;

	///客戶在系統中的編號，編號唯一且遵循交易所制定的編碼規則
	TTORATstpShareholderIDType	ShareholderID;

	///合約在交易所的程式碼
	TTORATstpExchangeInstIDType	ExchangeInstID;

	///交易所交易員程式碼
	TTORATstpTraderIDType	TraderID;

	///報單提交狀態
	TTORATstpOrderSubmitStatusType	OrderSubmitStatus;

	///交易發生的日期
	TTORATstpDateType	TradingDay;

	///報單編號
	TTORATstpOrderSysIDType	OrderSysID;

	///0．全部成交1．部分成交還在佇列中2．部分成交不在佇列中3．未成交還在佇列中4．未成交不在佇列中5．撤單
	TTORATstpOrderStatusType	OrderStatus;

	///0．普通1．報價派生2．組合派生
	TTORATstpOrderTypeType	OrderType;

	///報單完成數量
	TTORATstpVolumeType	VolumeTraded;

	///報單未完成數量
	TTORATstpVolumeType	VolumeTotal;

	///報單日期
	TTORATstpDateType	InsertDate;

	///委託時間
	TTORATstpTimeType	InsertTime;

	///撤銷時間
	TTORATstpTimeType	CancelTime;

	///最後修改交易所交易員程式碼
	TTORATstpTraderIDType	ActiveTraderID;

	///前置編號
	TTORATstpFrontIDType	FrontID;

	///每一位交易員或其它登入者登入系統獲得的會話編號，當前時刻唯一
	TTORATstpSessionIDType	SessionID;

	///說明使用者端使用的軟體產品和版本號
	TTORATstpProductInfoType	UserProductInfo;

	///狀態資訊
	TTORATstpErrorMsgType	StatusMsg;

	///使用者強評標誌
	TTORATstpBoolType	UserForceClose;

	///操作使用者程式碼
	TTORATstpUserIDType	ActiveUserID;

	///投資單元程式碼
	TTORATstpBusinessUnitIDType	BusinessUnitID;

	///資金賬戶
	TTORATstpAccountIDType	AccountID;

	///IP地址
	TTORATstpIPAddressType	IPAddress;

	///Mac地址
	TTORATstpMacAddressType	MacAddress;

	///頭寸型別
	TTORATstpCreditPositionTypeType	CreditPositionType;

	///長字串附加資訊
	TTORATstpBigsInfoType	BInfo;

	///短字串附加資訊
	TTORATstpShortsInfoType	SInfo;

	///整形附加資訊
	TTORATstpIntInfoType	IInfo;

	///轉入交易單元程式碼(僅在轉託管操作時有效)
	TTORATstpPbuIDType	TransfereePbuID;

	///委託方式
	TTORATstpOperwayType	Operway;

	///經紀公司部門程式碼
	TTORATstpDepartmentIDType	DepartmentID;

	///適當性控制業務類別
	TTORATstpProperCtrlBusinessTypeType	ProperCtrlBusinessType;

	///適當性控制通過標示
	TTORATstpProperCtrlPassFlagType	ProperCtrlPassFlag;

	///條件檢查
	TTORATstpCondCheckType	CondCheck;

	///是否預埋
	TTORATstpBoolType	IsCacheOrder;

	///根據成交價格計算出的本筆成交的金額（不包含費用）
	TTORATstpMoneyType	Turnover;

	///回報附加浮點型資料資訊
	TTORATstpFloatInfoType	RtnFloatInfo;

	///回報附加整型資料
	TTORATstpIntInfoType	RtnIntInfo;


};

/// 使用者標識
struct CTORATstpUserRefField
{
		
	///使用者程式碼
	TTORATstpUserIDType	UserID;


};

/// 輸入撤單操作
struct CTORATstpInputOrderActionField
{
		
	///投資者程式碼
	TTORATstpInvestorIDType	InvestorID;

	///投資者說明的對報單操作的唯一引用
	TTORATstpOrderRefType	OrderActionRef;

	///投資者說明的對報單的唯一引用
	TTORATstpOrderRefType	OrderRef;

	///請求編號
	TTORATstpRequestIDType	RequestID;

	///前置編號
	TTORATstpFrontIDType	FrontID;

	///每一位交易員或其它登入者登入系統獲得的會話編號，當前時刻唯一
	TTORATstpSessionIDType	SessionID;

	///一個交易所的編號
	TTORATstpExchangeIDType	ExchangeID;

	///報單編號
	TTORATstpOrderSysIDType	OrderSysID;

	///操作標誌
	TTORATstpActionFlagType	ActionFlag;

	///限價單價格
	TTORATstpPriceType	LimitPrice;

	///報單數量變化
	TTORATstpVolumeType	VolumeChange;

	///使用者程式碼
	TTORATstpUserIDType	UserID;

	///合約在系統中的編號
	TTORATstpSecurityIDType	SecurityID;

	///IP地址
	TTORATstpIPAddressType	IPAddress;

	///Mac地址
	TTORATstpMacAddressType	MacAddress;

	///全系統的唯一報單編號。16位，1-2位為交易所標識，3-5位為經紀公司程式碼，6-8位為交易單元標識，後面8位為流水號。
	TTORATstpOrderLocalIDType	CancelOrderLocalID;

	///終端資訊
	TTORATstpTerminalInfoType	TerminalInfo;

	///長字串附加資訊
	TTORATstpBigsInfoType	BInfo;

	///短字串附加資訊
	TTORATstpShortsInfoType	SInfo;

	///整形附加資訊
	TTORATstpIntInfoType	IInfo;

	///委託方式
	TTORATstpOperwayType	Operway;

	///硬碟序列號
	TTORATstpHDSerialType	HDSerial;


};

/// 報單操作
struct CTORATstpOrderActionField
{
		
	///投資者程式碼
	TTORATstpInvestorIDType	InvestorID;

	///投資者說明的對報單操作的唯一引用
	TTORATstpOrderRefType	OrderActionRef;

	///投資者說明的對報單的唯一引用
	TTORATstpOrderRefType	OrderRef;

	///請求編號
	TTORATstpRequestIDType	RequestID;

	///前置編號
	TTORATstpFrontIDType	FrontID;

	///每一位交易員或其它登入者登入系統獲得的會話編號，當前時刻唯一
	TTORATstpSessionIDType	SessionID;

	///一個交易所的編號
	TTORATstpExchangeIDType	ExchangeID;

	///報單編號
	TTORATstpOrderSysIDType	OrderSysID;

	///操作標誌
	TTORATstpActionFlagType	ActionFlag;

	///限價單價格
	TTORATstpPriceType	LimitPrice;

	///報單數量變化
	TTORATstpVolumeType	VolumeChange;

	///操作日期
	TTORATstpDateType	ActionDate;

	///操作時間
	TTORATstpTimeType	ActionTime;

	///交易所交易員程式碼
	TTORATstpTraderIDType	TraderID;

	///本地報單編號
	TTORATstpOrderLocalIDType	OrderLocalID;

	///操作本地編號
	TTORATstpOrderLocalIDType	ActionLocalID;

	///客戶在系統中的編號，編號唯一且遵循交易所制定的編碼規則
	TTORATstpShareholderIDType	ShareholderID;

	///報單操作狀態
	TTORATstpOrderActionStatusType	OrderActionStatus;

	///使用者程式碼
	TTORATstpUserIDType	UserID;

	///狀態資訊
	TTORATstpErrorMsgType	StatusMsg;

	///合約在系統中的編號
	TTORATstpSecurityIDType	SecurityID;

	///IP地址
	TTORATstpIPAddressType	IPAddress;

	///Mac地址
	TTORATstpMacAddressType	MacAddress;

	///長字串附加資訊
	TTORATstpBigsInfoType	BInfo;

	///短字串附加資訊
	TTORATstpShortsInfoType	SInfo;

	///整形附加資訊
	TTORATstpIntInfoType	IInfo;

	///委託方式
	TTORATstpOperwayType	Operway;


};

/// 成交
struct CTORATstpTradeField
{
		
	///投資者程式碼
	TTORATstpInvestorIDType	InvestorID;

	///合約在系統中的編號
	TTORATstpSecurityIDType	SecurityID;

	///使用者程式碼
	TTORATstpUserIDType	UserID;

	///交易所程式碼
	TTORATstpExchangeIDType	ExchangeID;

	///成交編號
	TTORATstpTradeIDType	TradeID;

	///1.買2.賣
	TTORATstpDirectionType	Direction;

	///報單編號
	TTORATstpOrderSysIDType	OrderSysID;

	///交易所下的交易市場，如滬A、滬B市場
	TTORATstpMarketIDType	MarketID;

	///客戶在系統中的編號，編號唯一且遵循交易所制定的編碼規則
	TTORATstpShareholderIDType	ShareholderID;

	///合約在交易所的程式碼
	TTORATstpExchangeInstIDType	ExchangeInstID;

	///1．開倉2．平今3．平昨4．強平
	TTORATstpOffsetFlagType	OffsetFlag;

	///1.投機2.套保
	TTORATstpHedgeFlagType	HedgeFlag;

	///成交價格
	TTORATstpPriceType	Price;

	///成交數量
	TTORATstpVolumeType	Volume;

	///成交日期
	TTORATstpDateType	TradeDate;

	///成交時間
	TTORATstpTimeType	TradeTime;

	///交易員在系統中的編號，編號唯一且遵循交易所制定的編碼規則
	TTORATstpTraderIDType	TraderID;

	///本地報單順序號
	TTORATstpOrderLocalIDType	OrderLocalID;

	///交易發生的日期
	TTORATstpDateType	TradingDay;

	///投資單元程式碼
	TTORATstpBusinessUnitIDType	BusinessUnitID;

	///資金賬戶
	TTORATstpAccountIDType	AccountID;

	///報單引用
	TTORATstpOrderRefType	OrderRef;

	///經紀公司部門程式碼
	TTORATstpDepartmentIDType	DepartmentID;


};

/// 市場狀態
struct CTORATstpMarketStatusField
{
		
	///交易所下的交易市場，如滬A、滬B市場
	TTORATstpMarketIDType	MarketID;

	///市場狀態
	TTORATstpMarketStatusType	MarketStatus;


};

/// 條件單錄入域
struct CTORATstpInputCondOrderField
{
		
	///交易所程式碼
	TTORATstpExchangeIDType	ExchangeID;

	///投資者程式碼
	TTORATstpInvestorIDType	InvestorID;

	///投資單元程式碼
	TTORATstpBusinessUnitIDType	BusinessUnitID;

	///股東賬戶程式碼
	TTORATstpShareholderIDType	ShareholderID;

	///合約程式碼
	TTORATstpSecurityIDType	SecurityID;

	///買賣方向
	TTORATstpDirectionType	Direction;

	///條件單價格型別
	TTORATstpOrderPriceTypeType	OrderPriceType;

	///條件單數量型別
	TTORATstpOrderVolumeTypeType	OrderVolumeType;

	///有效期型別
	TTORATstpTimeConditionType	TimeCondition;

	///成交量型別
	TTORATstpVolumeConditionType	VolumeCondition;

	///報單價格
	TTORATstpPriceType	LimitPrice;

	///報單數量
	TTORATstpVolumeType	VolumeTotalOriginal;

	///組合開平標誌
	TTORATstpCombOffsetFlagType	CombOffsetFlag;

	///組合投機套保標誌
	TTORATstpCombHedgeFlagType	CombHedgeFlag;

	///條件報單引用
	TTORATstpOrderRefType	CondOrderRef;

	///資金賬戶
	TTORATstpAccountIDType	AccountID;

	///使用者程式碼
	TTORATstpUserIDType	UserID;

	///請求編號
	TTORATstpRequestIDType	RequestID;

	///IP地址
	TTORATstpIPAddressType	IPAddress;

	///Mac地址
	TTORATstpMacAddressType	MacAddress;

	///報單編號
	TTORATstpCondOrderIDType	CondOrderID;

	///終端資訊
	TTORATstpTerminalInfoType	TerminalInfo;

	///長字串附加資訊
	TTORATstpBigsInfoType	BInfo;

	///短字串附加資訊
	TTORATstpShortsInfoType	SInfo;

	///整形附加資訊
	TTORATstpIntInfoType	IInfo;

	///委託方式
	TTORATstpOperwayType	Operway;

	///條件檢查
	TTORATstpCondCheckType	CondCheck;

	///條件單觸發條件
	TTORATstpContingentConditionType	ContingentCondition;

	///條件價
	TTORATstpPriceType	ConditionPrice;

	///價格浮動tick數,>0向上浮動,<0向下浮動,=0不浮動
	TTORATstpVolumeType	PriceTicks;

	///數量浮動倍數,必須>=0
	TTORATstpVolumeMultipleType	VolumeMultiple;

	///相關前置編號
	TTORATstpFrontIDType	RelativeFrontID;

	///相關會話編號
	TTORATstpSessionIDType	RelativeSessionID;

	///相關條件引數,可能為OrderRef、OrderSysID、Time和SecurityID
	TTORATstpRelativeCondParamType	RelativeParam;

	///附加條件單觸發條件
	TTORATstpContingentConditionType	AppendContingentCondition;

	///附加條件價
	TTORATstpPriceType	AppendConditionPrice;

	///附加相關前置編號
	TTORATstpFrontIDType	AppendRelativeFrontID;

	///附加相關會話編號
	TTORATstpSessionIDType	AppendRelativeSessionID;

	///附加相關條件引數,可能為OrderRef、OrderSysID、Time和SecurityID
	TTORATstpRelativeCondParamType	AppendRelativeParam;

	///硬碟序列號
	TTORATstpHDSerialType	HDSerial;


};

/// 條件單域
struct CTORATstpConditionOrderField
{
		
	///交易所程式碼
	TTORATstpExchangeIDType	ExchangeID;

	///投資者程式碼
	TTORATstpInvestorIDType	InvestorID;

	///投資單元程式碼
	TTORATstpBusinessUnitIDType	BusinessUnitID;

	///股東賬戶程式碼
	TTORATstpShareholderIDType	ShareholderID;

	///合約程式碼
	TTORATstpSecurityIDType	SecurityID;

	///買賣方向
	TTORATstpDirectionType	Direction;

	///條件單價格型別
	TTORATstpOrderPriceTypeType	OrderPriceType;

	///條件單數量型別
	TTORATstpOrderVolumeTypeType	OrderVolumeType;

	///有效期型別
	TTORATstpTimeConditionType	TimeCondition;

	///成交量型別
	TTORATstpVolumeConditionType	VolumeCondition;

	///報單價格
	TTORATstpPriceType	LimitPrice;

	///報單數量
	TTORATstpVolumeType	VolumeTotalOriginal;

	///組合開平標誌
	TTORATstpCombOffsetFlagType	CombOffsetFlag;

	///組合投機套保標誌
	TTORATstpCombHedgeFlagType	CombHedgeFlag;

	///條件報單引用
	TTORATstpOrderRefType	CondOrderRef;

	///資金賬戶
	TTORATstpAccountIDType	AccountID;

	///使用者程式碼
	TTORATstpUserIDType	UserID;

	///請求編號
	TTORATstpRequestIDType	RequestID;

	///IP地址
	TTORATstpIPAddressType	IPAddress;

	///Mac地址
	TTORATstpMacAddressType	MacAddress;

	///報單編號
	TTORATstpCondOrderIDType	CondOrderID;

	///終端資訊
	TTORATstpTerminalInfoType	TerminalInfo;

	///長字串附加資訊
	TTORATstpBigsInfoType	BInfo;

	///短字串附加資訊
	TTORATstpShortsInfoType	SInfo;

	///整形附加資訊
	TTORATstpIntInfoType	IInfo;

	///委託方式
	TTORATstpOperwayType	Operway;

	///條件檢查
	TTORATstpCondCheckType	CondCheck;

	///條件單觸發條件
	TTORATstpContingentConditionType	ContingentCondition;

	///條件價
	TTORATstpPriceType	ConditionPrice;

	///價格浮動tick數,>0向上浮動,<0向下浮動,=0不浮動
	TTORATstpVolumeType	PriceTicks;

	///數量浮動倍數,必須>=0
	TTORATstpVolumeMultipleType	VolumeMultiple;

	///相關前置編號
	TTORATstpFrontIDType	RelativeFrontID;

	///相關會話編號
	TTORATstpSessionIDType	RelativeSessionID;

	///相關條件引數,可能為OrderRef、OrderSysID、Time和SecurityID
	TTORATstpRelativeCondParamType	RelativeParam;

	///附加條件單觸發條件
	TTORATstpContingentConditionType	AppendContingentCondition;

	///附加條件價
	TTORATstpPriceType	AppendConditionPrice;

	///附加相關前置編號
	TTORATstpFrontIDType	AppendRelativeFrontID;

	///附加相關會話編號
	TTORATstpSessionIDType	AppendRelativeSessionID;

	///附加相關條件引數,可能為OrderRef、OrderSysID、Time和SecurityID
	TTORATstpRelativeCondParamType	AppendRelativeParam;

	///交易發生的日期
	TTORATstpDateType	TradingDay;

	///條件單狀態
	TTORATstpCondOrderStatusType	CondOrderStatus;

	///報單日期
	TTORATstpDateType	InsertDate;

	///委託時間
	TTORATstpTimeType	InsertTime;

	///撤銷時間
	TTORATstpTimeType	CancelTime;

	///撤銷使用者
	TTORATstpUserIDType	CancelUser;

	///前置編號
	TTORATstpFrontIDType	FrontID;

	///每一位交易員或其它登入者登入系統獲得的會話編號，當前時刻唯一
	TTORATstpSessionIDType	SessionID;

	///說明使用者端使用的軟體產品和版本號
	TTORATstpProductInfoType	UserProductInfo;

	///狀態資訊
	TTORATstpErrorMsgType	StatusMsg;

	///經紀公司部門程式碼
	TTORATstpDepartmentIDType	DepartmentID;

	///適當性控制業務類別
	TTORATstpProperCtrlBusinessTypeType	ProperCtrlBusinessType;

	///適當性控制通過標識
	TTORATstpProperCtrlPassFlagType	ProperCtrlPassFlag;

	///觸發日期
	TTORATstpDateType	ActiveDate;

	///觸發時間
	TTORATstpTimeType	ActiveTime;


};

/// 條件單操作錄入
struct CTORATstpInputCondOrderActionField
{
		
	///請求編號
	TTORATstpRequestIDType	RequestID;

	///一個交易所的編號
	TTORATstpExchangeIDType	ExchangeID;

	///條件單操作引用
	TTORATstpOrderRefType	CondOrderActionRef;

	///條件單引用
	TTORATstpOrderRefType	CondOrderRef;

	///前置編號
	TTORATstpFrontIDType	FrontID;

	///會話編號
	TTORATstpSessionIDType	SessionID;

	///報單編號
	TTORATstpCondOrderIDType	CondOrderID;

	///操作標誌
	TTORATstpActionFlagType	ActionFlag;

	///投資者程式碼
	TTORATstpInvestorIDType	InvestorID;

	///合約在系統中的編號
	TTORATstpSecurityIDType	SecurityID;

	///使用者程式碼
	TTORATstpUserIDType	UserID;

	///IP地址
	TTORATstpIPAddressType	IPAddress;

	///Mac地址
	TTORATstpMacAddressType	MacAddress;

	///條件單撤單編號
	TTORATstpCondOrderIDType	CancelCondOrderID;

	///終端資訊
	TTORATstpTerminalInfoType	TerminalInfo;

	///長字串附加資訊
	TTORATstpBigsInfoType	BInfo;

	///短字串附加資訊
	TTORATstpShortsInfoType	SInfo;

	///整形附加資訊
	TTORATstpIntInfoType	IInfo;

	///委託方式
	TTORATstpOperwayType	Operway;

	///硬碟序列號
	TTORATstpHDSerialType	HDSerial;


};

/// 查詢集中交易系統資金請求
struct CTORATstpReqInquiryJZFundField
{
		
	///資金賬戶
	TTORATstpAccountIDType	AccountID;

	///幣種
	TTORATstpCurrencyIDType	CurrencyID;

	///經紀公司部門程式碼
	TTORATstpDepartmentIDType	DepartmentID;


};

/// 查詢集中交易系統資金響應
struct CTORATstpRspInquiryJZFundField
{
		
	///資金賬戶
	TTORATstpAccountIDType	AccountID;

	///幣種
	TTORATstpCurrencyIDType	CurrencyID;

	///可用金額
	TTORATstpMoneyType	UsefulMoney;

	///可取額度
	TTORATstpMoneyType	FetchLimit;

	///經紀公司部門程式碼
	TTORATstpDepartmentIDType	DepartmentID;


};

/// 資金轉移
struct CTORATstpInputTransferFundField
{
		
	///資金賬戶
	TTORATstpAccountIDType	AccountID;

	///幣種
	TTORATstpCurrencyIDType	CurrencyID;

	///申請流水號
	TTORATstpExternalSerialType	ApplySerial;

	///轉移方向
	TTORATstpTransferDirectionType	TransferDirection;

	///轉賬金額
	TTORATstpMoneyType	Amount;

	///經紀公司部門程式碼
	TTORATstpDepartmentIDType	DepartmentID;

	///銀行程式碼(銀證轉賬時必填)
	TTORATstpBankIDType	BankID;

	///資金密碼(證券轉銀行時必填)
	TTORATstpPasswordType	AccountPassword;

	///銀行密碼(銀行轉證券時必填)
	TTORATstpPasswordType	BankPassword;


};

/// 倉位轉移
struct CTORATstpInputTransferPositionField
{
		
	///投資者程式碼
	TTORATstpInvestorIDType	InvestorID;

	///投資單元程式碼
	TTORATstpBusinessUnitIDType	BusinessUnitID;

	///交易所程式碼
	TTORATstpExchangeIDType	ExchangeID;

	///目前該欄位存放的是上證所和深圳的股東程式碼。
	TTORATstpShareholderIDType	ShareholderID;

	///合約程式碼
	TTORATstpSecurityIDType	SecurityID;

	///申請流水號
	TTORATstpExternalSerialType	ApplySerial;

	///轉移方向
	TTORATstpTransferDirectionType	TransferDirection;

	///數量
	TTORATstpVolumeType	Volume;

	///轉移持倉型別
	TTORATstpTransferPositionTypeType	TransferPositionType;

	///交易所下的交易市場，如滬A、滬B市場
	TTORATstpMarketIDType	MarketID;


};

/// 資金轉移回報
struct CTORATstpTransferFundField
{
		
	///轉賬流水號(後臺編號)
	TTORATstpSerialType	FundSerial;

	///申請流水號
	TTORATstpExternalSerialType	ApplySerial;

	///前置編號
	TTORATstpFrontIDType	FrontID;

	///會話編號
	TTORATstpSessionIDType	SessionID;

	///資金賬戶程式碼
	TTORATstpAccountIDType	AccountID;

	///幣種程式碼
	TTORATstpCurrencyIDType	CurrencyID;

	///轉移方向
	TTORATstpTransferDirectionType	TransferDirection;

	///資金賬戶當日出入金金額
	TTORATstpMoneyType	Amount;

	///轉移狀態
	TTORATstpTransferStatusType	TransferStatus;

	///操作人員
	TTORATstpUserIDType	OperatorID;

	///操作日期
	TTORATstpDateType	OperateDate;

	///操作時間
	TTORATstpTimeType	OperateTime;

	///經紀公司部門程式碼
	TTORATstpDepartmentIDType	DepartmentID;

	///簽約銀行賬戶
	TTORATstpBankAccountIDType	BankAccountID;

	///銀行程式碼
	TTORATstpBankIDType	BankID;


};

/// 倉位轉移回報
struct CTORATstpTransferPositionField
{
		
	///倉位轉移流水號
	TTORATstpSerialType	PositionSerial;

	///申請流水號
	TTORATstpExternalSerialType	ApplySerial;

	///前置編號
	TTORATstpFrontIDType	FrontID;

	///會話編號
	TTORATstpSessionIDType	SessionID;

	///投資者程式碼
	TTORATstpInvestorIDType	InvestorID;

	///投資單元程式碼
	TTORATstpBusinessUnitIDType	BusinessUnitID;

	///交易所程式碼
	TTORATstpExchangeIDType	ExchangeID;

	///目前該欄位存放的是上證所和深圳的股東程式碼。
	TTORATstpShareholderIDType	ShareholderID;

	///交易所下的交易市場，如滬A、滬B市場
	TTORATstpMarketIDType	MarketID;

	///證券程式碼
	TTORATstpSecurityIDType	SecurityID;

	///交易日
	TTORATstpDateType	TradingDay;

	///轉移方向
	TTORATstpTransferDirectionType	TransferDirection;

	///轉移持倉型別
	TTORATstpTransferPositionTypeType	TransferPositionType;

	///昨日倉位轉入轉出數量。
	TTORATstpVolumeType	HistoryVolume;

	///今日買賣倉位轉入轉出數量。
	TTORATstpVolumeType	TodayBSVolume;

	///今日申贖倉位轉入轉出數量。
	TTORATstpVolumeType	TodayPRVolume;

	///轉移狀態：0：正常，1：已衝正
	TTORATstpTransferStatusType	TransferStatus;

	///操作人員
	TTORATstpUserIDType	OperatorID;

	///操作日期
	TTORATstpDateType	OperateDate;

	///操作時間
	TTORATstpTimeType	OperateTime;


};

/// 訂閱行情
struct CTORATstpSpecificSecurityField
{
		
	///交易所程式碼
	TTORATstpExchangeIDType	ExchangeID;

	///合約程式碼
	TTORATstpSecurityIDType	SecurityID;


};

/// 擔保品轉移請求
struct CTORATstpInputTransferCollateralField
{
		
	///投資者程式碼
	TTORATstpInvestorIDType	InvestorID;

	///投資單元程式碼
	TTORATstpBusinessUnitIDType	BusinessUnitID;

	///交易所程式碼
	TTORATstpExchangeIDType	ExchangeID;

	///目前該欄位存放的是上證所和深圳的股東程式碼。
	TTORATstpShareholderIDType	ShareholderID;

	///合約程式碼
	TTORATstpSecurityIDType	SecurityID;

	///申請流水號
	TTORATstpExternalSerialType	ApplySerial;

	///擔保品劃轉方向
	TTORATstpCollateralDirectionType	CollateralDirection;

	///數量
	TTORATstpVolumeType	Volume;

	///交易所下的交易市場，如滬A、滬B市場
	TTORATstpMarketIDType	MarketID;

	///委託方式
	TTORATstpOperwayType	Operway;


};

/// 查詢銀行賬戶餘額請求
struct CTORATstpReqInquiryBankAccountFundField
{
		
	///經紀公司部門程式碼
	TTORATstpDepartmentIDType	DepartmentID;

	///資金賬戶
	TTORATstpAccountIDType	AccountID;

	///幣種
	TTORATstpCurrencyIDType	CurrencyID;

	///銀行程式碼
	TTORATstpBankIDType	BankID;

	///銀行密碼
	TTORATstpPasswordType	BankPassword;


};

/// 查詢銀行賬戶餘額響應
struct CTORATstpRspInquiryBankAccountFundField
{
		
	///經紀公司部門程式碼
	TTORATstpDepartmentIDType	DepartmentID;

	///資金賬戶
	TTORATstpAccountIDType	AccountID;

	///幣種
	TTORATstpCurrencyIDType	CurrencyID;

	///銀行程式碼
	TTORATstpBankIDType	BankID;

	///簽約銀行賬戶
	TTORATstpBankAccountIDType	BankAccountID;

	///賬戶餘額
	TTORATstpMoneyType	Balance;


};

/// Lev2行情
struct CTORATstpLev2MarketDataField
{
		
	///合約程式碼
	TTORATstpSecurityIDType	SecurityID;

	///行情交易所程式碼
	TTORATstpExchangeIDType	ExchangeID;

	///時間戳
	TTORATstpTimeStampType	DataTimeStamp;

	///昨收盤
	TTORATstpPriceType	PreClosePrice;

	///今開盤
	TTORATstpPriceType	OpenPrice;

	///成交筆數
	TTORATstpLongVolumeType	NumTrades;

	///成交總量
	TTORATstpLongVolumeType	TotalVolumeTrade;

	///成交總金額
	TTORATstpMoneyType	TotalValueTrade;

	///委託買入總量（只有上交所推送）
	TTORATstpLongVolumeType	TotalBidVolume;

	///加權平均委託買價格（只有上交所推送）
	TTORATstpPriceType	AvgBidPrice;

	///委託賣出總量（只有上交所推送）
	TTORATstpLongVolumeType	TotalAskVolume;

	///加權平均委託賣價格（只有上交所推送）
	TTORATstpPriceType	AvgAskPrice;

	///最高價
	TTORATstpPriceType	HighestPrice;

	///最低價
	TTORATstpPriceType	LowestPrice;

	///現價
	TTORATstpPriceType	LastPrice;

	///申買價一
	TTORATstpPriceType	BidPrice1;

	///申買量一
	TTORATstpLongVolumeType	BidVolume1;

	///申賣價一
	TTORATstpPriceType	AskPrice1;

	///申賣量一
	TTORATstpLongVolumeType	AskVolume1;

	///申賣價二
	TTORATstpPriceType	AskPrice2;

	///申賣量二
	TTORATstpLongVolumeType	AskVolume2;

	///申賣價三
	TTORATstpPriceType	AskPrice3;

	///申賣量三
	TTORATstpLongVolumeType	AskVolume3;

	///申買價二
	TTORATstpPriceType	BidPrice2;

	///申買量二
	TTORATstpLongVolumeType	BidVolume2;

	///申買價三
	TTORATstpPriceType	BidPrice3;

	///申買量三
	TTORATstpLongVolumeType	BidVolume3;

	///申賣價四
	TTORATstpPriceType	AskPrice4;

	///申賣量四
	TTORATstpLongVolumeType	AskVolume4;

	///申賣價五
	TTORATstpPriceType	AskPrice5;

	///申賣量五
	TTORATstpLongVolumeType	AskVolume5;

	///申買價四
	TTORATstpPriceType	BidPrice4;

	///申買量四
	TTORATstpLongVolumeType	BidVolume4;

	///申買價五
	TTORATstpPriceType	BidPrice5;

	///申買量五
	TTORATstpLongVolumeType	BidVolume5;

	///申賣價六
	TTORATstpPriceType	AskPrice6;

	///申賣量六
	TTORATstpLongVolumeType	AskVolume6;

	///申賣價七
	TTORATstpPriceType	AskPrice7;

	///申賣量七
	TTORATstpLongVolumeType	AskVolume7;

	///申買價六
	TTORATstpPriceType	BidPrice6;

	///申買量六
	TTORATstpLongVolumeType	BidVolume6;

	///申買價七
	TTORATstpPriceType	BidPrice7;

	///申買量七
	TTORATstpLongVolumeType	BidVolume7;

	///申賣價八
	TTORATstpPriceType	AskPrice8;

	///申賣量八
	TTORATstpLongVolumeType	AskVolume8;

	///申賣價九
	TTORATstpPriceType	AskPrice9;

	///申賣量九
	TTORATstpLongVolumeType	AskVolume9;

	///申買價八
	TTORATstpPriceType	BidPrice8;

	///申買量八
	TTORATstpLongVolumeType	BidVolume8;

	///申買價九
	TTORATstpPriceType	BidPrice9;

	///申買量九
	TTORATstpLongVolumeType	BidVolume9;

	///申買價十
	TTORATstpPriceType	BidPrice10;

	///申買量十
	TTORATstpLongVolumeType	BidVolume10;

	///申賣價十
	TTORATstpPriceType	AskPrice10;

	///申賣量十
	TTORATstpLongVolumeType	AskVolume10;

	///附加資訊1
	TTORATstpIntInfoType	Info1;

	///附加資訊2
	TTORATstpIntInfoType	Info2;

	///附加資訊3
	TTORATstpIntInfoType	Info3;

	///漲停板價(只有深圳行情有效)
	TTORATstpPriceType	UpperLimitPrice;

	///跌停板價(只有深圳行情有效)
	TTORATstpPriceType	LowerLimitPrice;

	///今收盤價(只有上海行情有效)
	TTORATstpPriceType	ClosePrice;

	///行情產品實時狀態
	TTORATstpMDSecurityStatType	MDSecurityStat;


};

/// Lev2指數行情
struct CTORATstpLev2IndexField
{
		
	///交易所程式碼
	TTORATstpExchangeIDType	ExchangeID;

	///合約程式碼
	TTORATstpSecurityIDType	SecurityID;

	///時間戳
	TTORATstpTimeStampType	DataTimeStamp;

	///前收盤指數
	TTORATstpPriceType	PreCloseIndex;

	///今開盤指數
	TTORATstpPriceType	OpenIndex;

	///最高指數
	TTORATstpPriceType	HighIndex;

	///最低指數
	TTORATstpPriceType	LowIndex;

	///最新指數
	TTORATstpPriceType	LastIndex;

	///參與計算相應指數的成交金額（元
	TTORATstpMoneyType	Turnover;

	///參與計算相應指數的交易數量(手)
	TTORATstpLongVolumeType	TotalVolumeTraded;

	///附加資訊1
	TTORATstpIntInfoType	Info1;

	///附加資訊2
	TTORATstpIntInfoType	Info2;

	///附加資訊3
	TTORATstpIntInfoType	Info3;


};

/// Lev2逐筆成交
struct CTORATstpLev2TransactionField
{
		
	///交易所程式碼
	TTORATstpExchangeIDType	ExchangeID;

	///合約程式碼
	TTORATstpSecurityIDType	SecurityID;

	///時間戳
	TTORATstpTimeStampType	TradeTime;

	///成交價格
	TTORATstpPriceType	TradePrice;

	///成交數量
	TTORATstpLongVolumeType	TradeVolume;

	///成交類別
	TTORATstpExecTypeType	ExecType;

	///主序號
	TTORATstpSequenceNoType	MainSeq;

	///子序號
	TTORATstpLongSequenceType	SubSeq;

	///買方委託序號
	TTORATstpLongSequenceType	BuyNo;

	///賣方委託序號
	TTORATstpLongSequenceType	SellNo;

	///附加資訊1
	TTORATstpIntInfoType	Info1;

	///附加資訊2
	TTORATstpIntInfoType	Info2;

	///附加資訊3
	TTORATstpIntInfoType	Info3;


};

/// Lev2逐筆委託
struct CTORATstpLev2OrderDetailField
{
		
	///交易所程式碼
	TTORATstpExchangeIDType	ExchangeID;

	///合約程式碼
	TTORATstpSecurityIDType	SecurityID;

	///時間戳
	TTORATstpTimeStampType	OrderTime;

	///委託價格
	TTORATstpPriceType	Price;

	///委託數量
	TTORATstpLongVolumeType	Volume;

	///委託方向
	TTORATstpLSideType	Side;

	///訂單類別
	TTORATstpLOrderTypeType	OrderType;

	///主序號
	TTORATstpSequenceNoType	MainSeq;

	///子序號
	TTORATstpSequenceNoType	SubSeq;

	///附加資訊1
	TTORATstpIntInfoType	Info1;

	///附加資訊2
	TTORATstpIntInfoType	Info2;

	///附加資訊3
	TTORATstpIntInfoType	Info3;


};

/// 回傳交易資料
struct CTORATstpUploadTradeDataField
{
		
	///交易所程式碼，目前支援 SSE(上海證券交易所)和SZSE(深圳證券交易所)
	TTORATstpExchangeIDType	ExchangeID;

	///交易日
	TTORATstpDateType	TradingDay;

	///是否強制回傳。0=否;1=是
	TTORATstpBoolType	bForce;


};

/// 輸入指定交易登記&撤銷
struct CTORATstpInputDesignationRegistrationField
{
		
	///投資者程式碼
	TTORATstpInvestorIDType	InvestorID;

	///使用者程式碼
	TTORATstpUserIDType	UserID;

	///0．指定登記 1．指定撤銷
	TTORATstpDesignationTypeType	DesignationType;

	///目前該欄位存放的是上證所和深圳的股東程式碼。
	TTORATstpShareholderIDType	ShareholderID;

	///投資單元程式碼
	TTORATstpBusinessUnitIDType	BusinessUnitID;

	///資金賬戶
	TTORATstpAccountIDType	AccountID;

	///報單編號
	TTORATstpOrderSysIDType	OrderSysID;

	///IP地址
	TTORATstpIPAddressType	IPAddress;

	///Mac地址
	TTORATstpMacAddressType	MacAddress;

	///終端資訊
	TTORATstpTerminalInfoType	TerminalInfo;

	///硬碟序列號
	TTORATstpHDSerialType	HDSerial;


};

/// 輸入深證轉託管
struct CTORATstpInputCustodyTransferField
{
		
	///投資者程式碼
	TTORATstpInvestorIDType	InvestorID;

	///使用者程式碼
	TTORATstpUserIDType	UserID;

	///|．新註冊轉託管請求 ~．轉託管撤單
	TTORATstpCustodyTransferTypeType	CustodyTransferType;

	///目前該欄位存放的是上證所和深圳的股東程式碼。
	TTORATstpShareholderIDType	ShareholderID;

	///投資單元程式碼
	TTORATstpBusinessUnitIDType	BusinessUnitID;

	///資金賬戶
	TTORATstpAccountIDType	AccountID;

	///報單編號
	TTORATstpOrderSysIDType	OrderSysID;

	///轉入交易單元程式碼
	TTORATstpPbuIDType	TransfereePbuID;

	///證券程式碼
	TTORATstpSecurityIDType	SecurityID;

	///全系統的唯一報單編號。16位，1-2位為交易所標識，3-5位為經紀公司程式碼，6-8位為交易單元標識，後面8位為流水號。
	TTORATstpOrderLocalIDType	OrignalOrderLocalID;

	///全系統的唯一報單編號。16位，1-2位為交易所標識，3-5位為經紀公司程式碼，6-8位為交易單元標識，後面8位為流水號。
	TTORATstpOrderLocalIDType	OrderLocalID;

	///報單數量
	TTORATstpVolumeType	VolumeTotalOriginal;

	///IP地址
	TTORATstpIPAddressType	IPAddress;

	///Mac地址
	TTORATstpMacAddressType	MacAddress;

	///終端資訊
	TTORATstpTerminalInfoType	TerminalInfo;

	///硬碟序列號
	TTORATstpHDSerialType	HDSerial;


};

/// 交易成交集中度
struct CTORATstpInquiryTradeConcentrationField
{
		
	///交易所程式碼
	TTORATstpExchangeIDType	ExchangeID;

	///交易所下的交易市場，如滬A、滬B市場
	TTORATstpMarketIDType	MarketID;

	///證券程式碼
	TTORATstpSecurityIDType	SecurityID;

	///投資者程式碼
	TTORATstpInvestorIDType	InvestorID;

	///投資單元程式碼
	TTORATstpBusinessUnitIDType	BusinessUnitID;

	///資金賬戶
	TTORATstpAccountIDType	AccountID;

	///交易賬戶程式碼
	TTORATstpShareholderIDType	ShareholderID;

	///投資者成交量/成交總量
	TTORATstpRatioType	ConcentrationRatio1;

	///投資者成交金額/成交總金額
	TTORATstpRatioType	ConcentrationRatio2;


};

/// 查詢檔案委託請求
struct CTORATstpInquiryFileOrderField
{
		
	///交易所程式碼
	TTORATstpExchangeIDType	ExchangeID;

	///股東賬戶程式碼
	TTORATstpShareholderIDType	ShareholderID;

	///投資者程式碼
	TTORATstpInvestorIDType	InvestorID;

	///證券程式碼
	TTORATstpSecurityIDType	SecurityID;

	///委託起始流水號
	TTORATstpSequenceNoType	OrderSerialBeg;

	///委託結束流水號
	TTORATstpSequenceNoType	OrderSerialEnd;

	///委託提交狀態
	TTORATstpCommitStatusType	CommitStatus;


};

/// 檔案委託
struct CTORATstpFileOrderField
{
		
	///請求編號
	TTORATstpRequestIDType	RequestID;

	///交易所程式碼
	TTORATstpExchangeIDType	ExchangeID;

	///股東賬戶程式碼
	TTORATstpShareholderIDType	ShareholderID;

	///投資者程式碼
	TTORATstpInvestorIDType	InvestorID;

	///證券程式碼
	TTORATstpSecurityIDType	SecurityID;

	///報單引用
	TTORATstpOrderRefType	OrderRef;

	///檔案報單類別
	TTORATstpFileOrderTypeType	FileOrderType;

	///買賣方向
	TTORATstpDirectionType	Direction;

	///限價單價格
	TTORATstpPriceType	LimitPrice;

	///報單數量
	TTORATstpVolumeType	VolumeTotalOriginal;

	///委託方式
	TTORATstpOperwayType	Operway;

	///報單操作引用
	TTORATstpOrderRefType	OrderActionRef;

	///報單編號
	TTORATstpOrderSysIDType	OrderSysID;

	///委託檢查
	TTORATstpCondCheckType	CondCheck;

	///委託流水號
	TTORATstpSequenceNoType	OrderSerial;

	///檔案委託提交狀態
	TTORATstpCommitStatusType	CommitStatus;

	///檔案委託狀態資訊
	TTORATstpStatusMsgType	StatusMsg;

	///委託時間戳
	TTORATstpBigTimeStampType	TimeStamp;


};

/// 查詢應答域
struct CTORATstpQryRspInfoField
{
		
	///結束標識
	TTORATstpEndFlagType	EndFlag;

	///錯誤程式碼
	TTORATstpErrorIDType	ErrorID;

	///錯誤資訊
	TTORATstpErrorMsgType	ErrorMsg;


};

/// 檔案委託複核請求
struct CTORATstpReviewFileOrderField
{
		
	///交易所程式碼
	TTORATstpExchangeIDType	ExchangeID;

	///股東賬戶程式碼
	TTORATstpShareholderIDType	ShareholderID;

	///投資者程式碼
	TTORATstpInvestorIDType	InvestorID;

	///證券程式碼
	TTORATstpSecurityIDType	SecurityID;

	///委託起始流水號
	TTORATstpSequenceNoType	OrderSerialBeg;

	///委託結束流水號
	TTORATstpSequenceNoType	OrderSerialEnd;


};

/// 檔案提交資訊
struct CTORATstpCommitInfoField
{
		
	///委託流水號
	TTORATstpSequenceNoType	OrderSerial;

	///檔案委託提交狀態
	TTORATstpCommitStatusType	CommitStatus;

	///檔案委託狀態資訊
	TTORATstpStatusMsgType	StatusMsg;


};

/// 請求插入交易通知
struct CTORATstpReqInsTradingNoticeField
{
		
	///通知流水號
	TTORATstpSerialType	NoticeSerial;

	///通知日期
	TTORATstpDateType	InsertDate;

	///通知時間
	TTORATstpTimeType	InsertTime;

	///投資者程式碼
	TTORATstpInvestorIDType	InvestorID;

	///投資單元程式碼
	TTORATstpBusinessUnitIDType	BusinessUnitID;

	///通知訊息內容
	TTORATstpContentType	Content;

	///操作員
	TTORATstpUserIDType	OperatorID;


};

/// 交易通知
struct CTORATstpTradingNoticeField
{
		
	///通知流水號
	TTORATstpSerialType	NoticeSerial;

	///通知日期
	TTORATstpDateType	InsertDate;

	///通知時間
	TTORATstpTimeType	InsertTime;

	///投資者程式碼
	TTORATstpInvestorIDType	InvestorID;

	///投資單元程式碼
	TTORATstpBusinessUnitIDType	BusinessUnitID;

	///通知訊息內容
	TTORATstpContentType	Content;

	///操作員
	TTORATstpUserIDType	OperatorID;


};

/// 裝載檔案委託
struct CTORATstpLoadFileOrderField
{
		
	///投資者程式碼
	TTORATstpInvestorIDType	InvestorID;

	///是否需要複核
	TTORATstpBoolType	bReview;


};

/// 檔案委託資訊
struct CTORATstpFileOrderInfoField
{
		
	///請求編號
	TTORATstpRequestIDType	RequestID;

	///交易所程式碼
	TTORATstpExchangeIDType	ExchangeID;

	///股東賬戶程式碼
	TTORATstpShareholderIDType	ShareholderID;

	///投資者程式碼
	TTORATstpInvestorIDType	InvestorID;

	///證券程式碼
	TTORATstpSecurityIDType	SecurityID;

	///報單引用
	TTORATstpOrderRefType	OrderRef;

	///檔案報單類別
	TTORATstpFileOrderTypeType	FileOrderType;

	///買賣方向
	TTORATstpDirectionType	Direction;

	///限價單價格
	TTORATstpPriceType	LimitPrice;

	///報單數量
	TTORATstpVolumeType	VolumeTotalOriginal;

	///委託方式
	TTORATstpOperwayType	Operway;

	///報單操作引用
	TTORATstpOrderRefType	OrderActionRef;

	///報單編號
	TTORATstpOrderSysIDType	OrderSysID;

	///委託檢查
	TTORATstpCondCheckType	CondCheck;

	///委託流水號
	TTORATstpSequenceNoType	OrderSerial;

	///檔案委託提交狀態
	TTORATstpCommitStatusType	CommitStatus;

	///檔案委託狀態資訊
	TTORATstpStatusMsgType	StatusMsg;


};

/// 查詢最大報單量請求
struct CTORATstpReqInquiryMaxOrderVolumeField
{
		
	///交易所程式碼
	TTORATstpExchangeIDType	ExchangeID;

	///證券程式碼
	TTORATstpSecurityIDType	SecurityID;

	///投資者程式碼
	TTORATstpInvestorIDType	InvestorID;

	///投資單元程式碼
	TTORATstpBusinessUnitIDType	BusinessUnitID;

	///資金賬戶
	TTORATstpAccountIDType	AccountID;

	///交易賬戶程式碼
	TTORATstpShareholderIDType	ShareholderID;

	///買賣方向
	TTORATstpDirectionType	Direction;

	///限價單或市價單
	TTORATstpOrderPriceTypeType	OrderPriceType;

	///按位元組表示各單個合約的開平方向
	TTORATstpCombOffsetFlagType	CombOffsetFlag;

	///按位元組表示各單個合約的組合套保標誌
	TTORATstpCombHedgeFlagType	CombHedgeFlag;

	///IOC、GFS、GFD、GTD、GTC、GFA
	TTORATstpTimeConditionType	TimeCondition;

	///AV、MV、CV
	TTORATstpVolumeConditionType	VolumeCondition;

	///限價單價格
	TTORATstpPriceType	LimitPrice;

	///轉入交易單元程式碼(僅在轉託管操作時有效)
	TTORATstpPbuIDType	TransfereePbuID;

	///最大委託手數
	TTORATstpVolumeType	MaxVolume;


};

/// 查詢最大報單量應答
struct CTORATstpRspInquiryMaxOrderVolumeField
{
		
	///交易所程式碼
	TTORATstpExchangeIDType	ExchangeID;

	///證券程式碼
	TTORATstpSecurityIDType	SecurityID;

	///投資者程式碼
	TTORATstpInvestorIDType	InvestorID;

	///投資單元程式碼
	TTORATstpBusinessUnitIDType	BusinessUnitID;

	///資金賬戶
	TTORATstpAccountIDType	AccountID;

	///交易賬戶程式碼
	TTORATstpShareholderIDType	ShareholderID;

	///買賣方向
	TTORATstpDirectionType	Direction;

	///限價單或市價單
	TTORATstpOrderPriceTypeType	OrderPriceType;

	///按位元組表示各單個合約的開平方向
	TTORATstpCombOffsetFlagType	CombOffsetFlag;

	///按位元組表示各單個合約的組合套保標誌
	TTORATstpCombHedgeFlagType	CombHedgeFlag;

	///IOC、GFS、GFD、GTD、GTC、GFA
	TTORATstpTimeConditionType	TimeCondition;

	///AV、MV、CV
	TTORATstpVolumeConditionType	VolumeCondition;

	///限價單價格
	TTORATstpPriceType	LimitPrice;

	///轉入交易單元程式碼(僅在轉託管操作時有效)
	TTORATstpPbuIDType	TransfereePbuID;

	///最大委託手數
	TTORATstpVolumeType	MaxVolume;


};

/// 外圍系統倉位調撥流水明細
struct CTORATstpPeripheryPositionTransferDetailField
{
		
	///倉位調撥系統流水號
	TTORATstpIntSerialType	PositionSerial;

	///倉位調撥請求流水號
	TTORATstpIntSerialType	ApplySerial;

	///前置編號
	TTORATstpFrontIDType	FrontID;

	///會話編號
	TTORATstpSessionIDType	SessionID;

	///倉位調撥方向
	TTORATstpTransferDirectionType	TransferDirection;

	///交易所程式碼
	TTORATstpExchangeIDType	ExchangeID;

	///交易所下的交易市場，如滬A、滬B市場
	TTORATstpMarketIDType	MarketID;

	///投資者程式碼
	TTORATstpInvestorIDType	InvestorID;

	///投資單元程式碼
	TTORATstpBusinessUnitIDType	BusinessUnitID;

	///現貨系統交易賬戶程式碼
	TTORATstpShareholderIDType	ShareholderID;

	///證券程式碼
	TTORATstpSecurityIDType	SecurityID;

	///今日買賣倉位轉入轉出數量
	TTORATstpVolumeType	TodayBSPos;

	///今日申贖倉位轉入數量
	TTORATstpVolumeType	TodayPRPos;

	///昨日倉位轉入數量
	TTORATstpVolumeType	HistoryPos;

	///交易日期
	TTORATstpDateType	TradingDay;

	///倉位調撥原因
	TTORATstpTransferReasonType	TransferReason;

	///轉移狀態
	TTORATstpTransferStatusType	TransferStatus;

	///操作日期
	TTORATstpDateType	OperateDate;

	///操作時間
	TTORATstpTimeType	OperateTime;

	///衝正日期
	TTORATstpDateType	RepealDate;

	///衝正時間
	TTORATstpTimeType	RepealTime;

	///衝正原因
	TTORATstpTransferReasonType	RepealReason;

	///狀態資訊
	TTORATstpErrorMsgType	StatusMsg;


};

/// 查詢歷史委託
struct CTORATstpQryHistoryOrderField
{
		
	///交易所程式碼
	TTORATstpExchangeIDType	ExchangeID;

	///投資者程式碼
	TTORATstpInvestorIDType	InvestorID;

	///起始日期
	TTORATstpDateType	BegDate;

	///結束日期
	TTORATstpDateType	EndDate;

	///證券程式碼
	TTORATstpSecurityIDType	SecurityID;

	///每頁記錄數
	TTORATstpVolumeType	PageCount;

	///頁定位符
	TTORATstpPageLocateType	PageLocate;


};

/// 查詢歷史響應資訊
struct CTORATstpQryHistoryRspInfoField
{
		
	///錯誤程式碼
	TTORATstpErrorIDType	ErrorID;

	///錯誤資訊
	TTORATstpErrorMsgType	ErrorMsg;

	///分頁是否結束
	TTORATstpBoolType	bPageEnd;


};

/// 歷史委託資訊
struct CTORATstpHistoryOrderField
{
		
	///投資者程式碼
	TTORATstpInvestorIDType	InvestorID;

	///合約在系統中的編號
	TTORATstpSecurityIDType	SecurityID;

	///投資者說明的對報單的唯一引用
	TTORATstpOrderRefType	OrderRef;

	///使用者程式碼
	TTORATstpUserIDType	UserID;

	///限價單或市價單
	TTORATstpOrderPriceTypeType	OrderPriceType;

	///1．買2．賣
	TTORATstpDirectionType	Direction;

	///按位元組表示各單個合約的開平方向
	TTORATstpCombOffsetFlagType	CombOffsetFlag;

	///按位元組表示各單個合約的組合套保標誌
	TTORATstpCombHedgeFlagType	CombHedgeFlag;

	///限價單價格
	TTORATstpPriceType	LimitPrice;

	///報單數量
	TTORATstpVolumeType	VolumeTotalOriginal;

	///IOC、GFS、GFD、GTD、GTC、GFA
	TTORATstpTimeConditionType	TimeCondition;

	///AV、MV、CV
	TTORATstpVolumeConditionType	VolumeCondition;

	///當成交量型別為MV時有效
	TTORATstpVolumeType	MinVolume;

	///強平原因
	TTORATstpForceCloseReasonType	ForceCloseReason;

	///請求編號
	TTORATstpRequestIDType	RequestID;

	///本地報單順序號
	TTORATstpOrderLocalIDType	OrderLocalID;

	///交易所程式碼
	TTORATstpExchangeIDType	ExchangeID;

	///交易所下的交易市場，如滬A、滬B市場
	TTORATstpMarketIDType	MarketID;

	///客戶在系統中的編號，編號唯一且遵循交易所制定的編碼規則
	TTORATstpShareholderIDType	ShareholderID;

	///合約在交易所的程式碼
	TTORATstpExchangeInstIDType	ExchangeInstID;

	///交易所交易員程式碼
	TTORATstpTraderIDType	TraderID;

	///報單提交狀態
	TTORATstpOrderSubmitStatusType	OrderSubmitStatus;

	///交易發生的日期
	TTORATstpDateType	TradingDay;

	///報單編號
	TTORATstpOrderSysIDType	OrderSysID;

	///0．全部成交1．部分成交還在佇列中2．部分成交不在佇列中3．未成交還在佇列中4．未成交不在佇列中5．撤單
	TTORATstpOrderStatusType	OrderStatus;

	///0．普通1．報價派生2．組合派生
	TTORATstpOrderTypeType	OrderType;

	///報單完成數量
	TTORATstpVolumeType	VolumeTraded;

	///報單未完成數量
	TTORATstpVolumeType	VolumeTotal;

	///報單日期
	TTORATstpDateType	InsertDate;

	///委託時間
	TTORATstpTimeType	InsertTime;

	///撤銷時間
	TTORATstpTimeType	CancelTime;

	///最後修改交易所交易員程式碼
	TTORATstpTraderIDType	ActiveTraderID;

	///前置編號
	TTORATstpFrontIDType	FrontID;

	///每一位交易員或其它登入者登入系統獲得的會話編號，當前時刻唯一
	TTORATstpSessionIDType	SessionID;

	///說明使用者端使用的軟體產品和版本號
	TTORATstpProductInfoType	UserProductInfo;

	///狀態資訊
	TTORATstpErrorMsgType	StatusMsg;

	///使用者強評標誌
	TTORATstpBoolType	UserForceClose;

	///操作使用者程式碼
	TTORATstpUserIDType	ActiveUserID;

	///投資單元程式碼
	TTORATstpBusinessUnitIDType	BusinessUnitID;

	///資金賬戶
	TTORATstpAccountIDType	AccountID;

	///IP地址
	TTORATstpIPAddressType	IPAddress;

	///Mac地址
	TTORATstpMacAddressType	MacAddress;

	///頭寸型別
	TTORATstpCreditPositionTypeType	CreditPositionType;

	///長字串附加資訊
	TTORATstpBigsInfoType	BInfo;

	///短字串附加資訊
	TTORATstpShortsInfoType	SInfo;

	///整形附加資訊
	TTORATstpIntInfoType	IInfo;

	///轉入交易單元程式碼(僅在轉託管操作時有效)
	TTORATstpPbuIDType	TransfereePbuID;

	///委託方式
	TTORATstpOperwayType	Operway;

	///經紀公司部門程式碼
	TTORATstpDepartmentIDType	DepartmentID;

	///適當性控制業務類別
	TTORATstpProperCtrlBusinessTypeType	ProperCtrlBusinessType;

	///適當性控制通過標示
	TTORATstpProperCtrlPassFlagType	ProperCtrlPassFlag;

	///條件檢查
	TTORATstpCondCheckType	CondCheck;

	///是否預埋
	TTORATstpBoolType	IsCacheOrder;

	///根據成交價格計算出的本筆成交的金額（不包含費用）
	TTORATstpMoneyType	Turnover;

	///回報附加浮點型資料資訊
	TTORATstpFloatInfoType	RtnFloatInfo;

	///回報附加整型資料
	TTORATstpIntInfoType	RtnIntInfo;

	///頁定位符
	TTORATstpPageLocateType	PageLocate;


};

/// 查詢歷史成交
struct CTORATstpQryHistoryTradeField
{
		
	///交易所程式碼
	TTORATstpExchangeIDType	ExchangeID;

	///投資者程式碼
	TTORATstpInvestorIDType	InvestorID;

	///起始日期
	TTORATstpDateType	BegDate;

	///結束日期
	TTORATstpDateType	EndDate;

	///證券程式碼
	TTORATstpSecurityIDType	SecurityID;

	///每頁記錄數
	TTORATstpVolumeType	PageCount;

	///頁定位符
	TTORATstpPageLocateType	PageLocate;


};

/// 歷史成交資訊
struct CTORATstpHistoryTradeField
{
		
	///投資者程式碼
	TTORATstpInvestorIDType	InvestorID;

	///合約在系統中的編號
	TTORATstpSecurityIDType	SecurityID;

	///使用者程式碼
	TTORATstpUserIDType	UserID;

	///交易所程式碼
	TTORATstpExchangeIDType	ExchangeID;

	///成交編號
	TTORATstpTradeIDType	TradeID;

	///1.買2.賣
	TTORATstpDirectionType	Direction;

	///報單編號
	TTORATstpOrderSysIDType	OrderSysID;

	///交易所下的交易市場，如滬A、滬B市場
	TTORATstpMarketIDType	MarketID;

	///客戶在系統中的編號，編號唯一且遵循交易所制定的編碼規則
	TTORATstpShareholderIDType	ShareholderID;

	///合約在交易所的程式碼
	TTORATstpExchangeInstIDType	ExchangeInstID;

	///1．開倉2．平今3．平昨4．強平
	TTORATstpOffsetFlagType	OffsetFlag;

	///1.投機2.套保
	TTORATstpHedgeFlagType	HedgeFlag;

	///成交價格
	TTORATstpPriceType	Price;

	///成交數量
	TTORATstpVolumeType	Volume;

	///成交日期
	TTORATstpDateType	TradeDate;

	///成交時間
	TTORATstpTimeType	TradeTime;

	///交易員在系統中的編號，編號唯一且遵循交易所制定的編碼規則
	TTORATstpTraderIDType	TraderID;

	///本地報單順序號
	TTORATstpOrderLocalIDType	OrderLocalID;

	///交易發生的日期
	TTORATstpDateType	TradingDay;

	///投資單元程式碼
	TTORATstpBusinessUnitIDType	BusinessUnitID;

	///資金賬戶
	TTORATstpAccountIDType	AccountID;

	///報單引用
	TTORATstpOrderRefType	OrderRef;

	///經紀公司部門程式碼
	TTORATstpDepartmentIDType	DepartmentID;

	///頁定位符
	TTORATstpPageLocateType	PageLocate;


};

/// 查詢交易所
struct CTORATstpQryExchangeField
{
		
	///交易所程式碼，目前支援 SSE(上海證券交易所)和SZSE(深圳證券交易所)
	TTORATstpExchangeIDType	ExchangeID;


};

/// 交易所
struct CTORATstpExchangeField
{
		
	///交易所程式碼
	TTORATstpExchangeIDType	ExchangeID;

	///交易所名稱
	TTORATstpNameType	ExchangeName;

	///交易日
	TTORATstpDateType	TradingDay;


};

/// 查詢PBU
struct CTORATstpQryPBUField
{
		
	///交易單元程式碼
	TTORATstpPbuIDType	PbuID;

	///交易所程式碼
	TTORATstpExchangeIDType	ExchangeID;

	///交易所下的交易市場，如滬A、滬B市場
	TTORATstpMarketIDType	MarketID;


};

/// PBU
struct CTORATstpPBUField
{
		
	///交易單元程式碼
	TTORATstpPbuIDType	PbuID;

	///交易單元名稱
	TTORATstpNameType	PbuName;

	///交易所程式碼
	TTORATstpExchangeIDType	ExchangeID;

	///市場程式碼
	TTORATstpMarketIDType	MarketID;


};

/// 查詢實時行情
struct CTORATstpQryMarketDataField
{
		
	///證券程式碼
	TTORATstpSecurityIDType	SecurityID;

	///交易所程式碼，目前支援 SSE(上海證券交易所)和SZSE(深圳證券交易所)
	TTORATstpExchangeIDType	ExchangeID;


};

/// 實時行情
struct CTORATstpMarketDataField
{
		
	///交易日
	TTORATstpDateType	TradingDay;

	///合約程式碼
	TTORATstpSecurityIDType	SecurityID;

	///交易所程式碼
	TTORATstpExchangeIDType	ExchangeID;

	///合約在交易所的程式碼
	TTORATstpExchangeInstIDType	ExchangeInstID;

	///最新價
	TTORATstpPriceType	LastPrice;

	///昨收盤
	TTORATstpPriceType	PreClosePrice;

	///今開盤
	TTORATstpPriceType	OpenPrice;

	///最高價
	TTORATstpPriceType	HighestPrice;

	///最低價
	TTORATstpPriceType	LowestPrice;

	///數量
	TTORATstpLongVolumeType	Volume;

	///成交金額
	TTORATstpMoneyType	Turnover;

	///持倉量
	TTORATstpLargeVolumeType	OpenInterest;

	///漲停板價
	TTORATstpPriceType	UpperLimitPrice;

	///跌停板價
	TTORATstpPriceType	LowerLimitPrice;

	///最後修改時間
	TTORATstpTimeType	UpdateTime;

	///最後修改毫秒
	TTORATstpMillisecType	UpdateMillisec;

	///申買價一
	TTORATstpPriceType	BidPrice1;

	///申買量一
	TTORATstpLongVolumeType	BidVolume1;

	///申賣價一
	TTORATstpPriceType	AskPrice1;

	///申賣量一
	TTORATstpLongVolumeType	AskVolume1;

	///申買價二
	TTORATstpPriceType	BidPrice2;

	///申買量二
	TTORATstpLongVolumeType	BidVolume2;

	///申賣價二
	TTORATstpPriceType	AskPrice2;

	///申賣量二
	TTORATstpLongVolumeType	AskVolume2;

	///申買價三
	TTORATstpPriceType	BidPrice3;

	///申買量三
	TTORATstpLongVolumeType	BidVolume3;

	///申賣價三
	TTORATstpPriceType	AskPrice3;

	///申賣量三
	TTORATstpLongVolumeType	AskVolume3;

	///申買價四
	TTORATstpPriceType	BidPrice4;

	///申買量四
	TTORATstpLongVolumeType	BidVolume4;

	///申賣價四
	TTORATstpPriceType	AskPrice4;

	///申賣量四
	TTORATstpLongVolumeType	AskVolume4;

	///申買價五
	TTORATstpPriceType	BidPrice5;

	///申買量五
	TTORATstpLongVolumeType	BidVolume5;

	///申賣價五
	TTORATstpPriceType	AskPrice5;

	///申賣量五
	TTORATstpLongVolumeType	AskVolume5;

	///合約名稱
	TTORATstpSecurityNameType	SecurityName;

	///成交筆數
	TTORATstpLongVolumeType	TradingCount;

	///市盈率1
	TTORATstpRatioType	PERatio1;

	///市盈率2
	TTORATstpRatioType	PERatio2;

	///價格升跌1
	TTORATstpPriceType	PriceUpDown1;

	///價格升跌2
	TTORATstpPriceType	PriceUpDown2;

	///收盤價
	TTORATstpPriceType	ClosePrice;

	///證券實時狀態
	TTORATstpMDSecurityStatType	MDSecurityStat;

	///是否風險警示標誌0否1是
	TTORATstpBoolType	HWFlag;


};

/// 查詢證券資訊
struct CTORATstpQrySecurityField
{
		
	///證券程式碼
	TTORATstpSecurityIDType	SecurityID;

	///交易所程式碼，目前支援 SSE(上海證券交易所)和SZSE(深圳證券交易所)
	TTORATstpExchangeIDType	ExchangeID;

	///合約在交易所的程式碼
	TTORATstpExchangeInstIDType	ExchangeInstID;

	///證券市場中的具體品種，如上海股票
	TTORATstpProductIDType	ProductID;


};

/// 證券資訊
struct CTORATstpSecurityField
{
		
	///合約程式碼
	TTORATstpSecurityIDType	SecurityID;

	///交易所程式碼
	TTORATstpExchangeIDType	ExchangeID;

	///合約名稱
	TTORATstpSecurityNameType	SecurityName;

	///合約在交易所的程式碼
	TTORATstpExchangeInstIDType	ExchangeInstID;

	///市場程式碼
	TTORATstpMarketIDType	MarketID;

	///產品程式碼
	TTORATstpProductIDType	ProductID;

	///證券類別程式碼
	TTORATstpSecurityTypeType	SecurityType;

	///申報單位
	TTORATstpOrderUnitType	OrderUnit;

	///買入交易單位
	TTORATstpTradingUnitType	BuyTradingUnit;

	///賣出交易單位
	TTORATstpTradingUnitType	SellTradingUnit;

	///市價單買最大下單量
	TTORATstpVolumeType	MaxMarketOrderBuyVolume;

	///市價單買最小下單量
	TTORATstpVolumeType	MinMarketOrderBuyVolume;

	///限價單買最大下單量
	TTORATstpVolumeType	MaxLimitOrderBuyVolume;

	///限價單買最小下單量
	TTORATstpVolumeType	MinLimitOrderBuyVolume;

	///市價單賣最大下單量
	TTORATstpVolumeType	MaxMarketOrderSellVolume;

	///市價單賣最小下單量
	TTORATstpVolumeType	MinMarketOrderSellVolume;

	///限價單賣最大下單量
	TTORATstpVolumeType	MaxLimitOrderSellVolume;

	///限價單賣最小下單量
	TTORATstpVolumeType	MinLimitOrderSellVolume;

	///數量乘數
	TTORATstpVolumeMultipleType	VolumeMultiple;

	///最小變動價位
	TTORATstpPriceTickType	PriceTick;

	///上市日
	TTORATstpDateType	OpenDate;

	///持倉型別
	TTORATstpPositionTypeType	PositionType;

	///面值
	TTORATstpParValueType	ParValue;

	///證券狀態
	TTORATstpSecurityStatusType	SecurityStatus;

	///債券應計利息
	TTORATstpInterestType	BondInterest;

	///折算率
	TTORATstpRatioType	ConversionRate;

	///是否擔保品
	TTORATstpBoolType	IsCollateral;


};

/// 查詢ETF清單資訊
struct CTORATstpQryETFFileField
{
		
	///交易所程式碼，目前支援 SSE(上海證券交易所)和SZSE(深圳證券交易所)
	TTORATstpExchangeIDType	ExchangeID;

	///ETF二級市場交易程式碼
	TTORATstpSecurityIDType	ETFSecurityID;

	///ETF一級市場申贖程式碼
	TTORATstpSecurityIDType	ETFCreRedSecurityID;


};

/// ETF清單資訊
struct CTORATstpETFFileField
{
		
	///交易日
	TTORATstpDateType	TradingDay;

	///交易所程式碼
	TTORATstpExchangeIDType	ExchangeID;

	///ETF交易程式碼
	TTORATstpSecurityIDType	ETFSecurityID;

	///ETF申贖程式碼
	TTORATstpSecurityIDType	ETFCreRedSecurityID;

	///最小申購贖回單位份數
	TTORATstpVolumeType	CreationRedemptionUnit;

	///最大現金替代比例
	TTORATstpRatioType	Maxcashratio;

	///是否允許申購
	TTORATstpBoolType	CreationStatus;

	///是否允許贖回
	TTORATstpBoolType	RedemptionStatus;

	///預估現金差額
	TTORATstpMoneyType	EstimateCashComponent;

	///前一交易日現金差額
	TTORATstpMoneyType	CashComponent;

	///前一交易日基金單位淨值
	TTORATstpMoneyType	NAV;

	///前一交易日申贖基準單位淨值
	TTORATstpMoneyType	NAVperCU;

	///當日申購贖回基準單位的紅利金額
	TTORATstpMoneyType	DividendPerCU;


};

/// 查詢ETF成份證券資訊
struct CTORATstpQryETFBasketField
{
		
	///交易所程式碼，目前支援 SSE(上海證券交易所)和SZSE(深圳證券交易所)
	TTORATstpExchangeIDType	ExchangeID;

	///ETF二級市場交易程式碼
	TTORATstpSecurityIDType	ETFSecurityID;

	///ETF籃子中的成分證券程式碼
	TTORATstpSecurityIDType	SecurityID;


};

/// ETF成份證券資訊
struct CTORATstpETFBasketField
{
		
	///交易日
	TTORATstpDateType	TradingDay;

	///交易所程式碼
	TTORATstpExchangeIDType	ExchangeID;

	///ETF交易程式碼
	TTORATstpSecurityIDType	ETFSecurityID;

	///ETF成份證券程式碼
	TTORATstpSecurityIDType	SecurityID;

	///證券簡稱
	TTORATstpSecurityNameType	SecurityName;

	///證券數量
	TTORATstpVolumeType	Volume;

	///替代標誌
	TTORATstpETFCurrenceReplaceStatusType	ETFCurrenceReplaceStatus;

	///溢價比例
	TTORATstpRatioType	Premium;

	///申購替代金額
	TTORATstpMoneyType	CreationReplaceAmount;

	///贖回替代金額
	TTORATstpMoneyType	RedemptionReplaceAmount;

	///掛牌市場
	TTORATstpListingMarketType	Market;


};

/// 查詢經紀公司部門資訊
struct CTORATstpQryDepartmentInfoField
{
		
	///經紀公司部門程式碼
	TTORATstpDepartmentIDType	DepartmentID;


};

/// 經紀公司部門資訊
struct CTORATstpDepartmentInfoField
{
		
	///經紀公司部門程式碼
	TTORATstpDepartmentIDType	DepartmentID;

	///經紀公司部門名稱
	TTORATstpNameType	DepartmentName;


};

/// 查詢新股資訊
struct CTORATstpQryIPOInfoField
{
		
	///交易所程式碼
	TTORATstpExchangeIDType	ExchangeID;

	///申購程式碼
	TTORATstpSecurityIDType	SecurityID;


};

/// 新股資訊
struct CTORATstpIPOInfoField
{
		
	///交易所程式碼
	TTORATstpExchangeIDType	ExchangeID;

	///申購程式碼
	TTORATstpSecurityIDType	SecurityID;

	///市場程式碼
	TTORATstpMarketIDType	MarketID;

	///產品程式碼
	TTORATstpProductIDType	ProductID;

	///證券類別程式碼
	TTORATstpSecurityTypeType	SecurityType;

	///網上申購上限
	TTORATstpVolumeType	OnlineLimit;

	///發行價格
	TTORATstpPriceType	Price;

	///幣種程式碼
	TTORATstpCurrencyIDType	CurrencyID;

	///申購證券名稱
	TTORATstpSecurityNameType	SecurityName;

	///新股證券程式碼
	TTORATstpSecurityIDType	UnderlyingSecurityID;

	///新股證券名稱
	TTORATstpSecurityNameType	UnderlyingSecurityName;

	///網上申購最小數量
	TTORATstpVolumeType	OnlineMinVol;

	///網上申購單位數量
	TTORATstpVolumeType	OnlineVolUnit;


};

/// 查詢BrokerUserFunction
struct CTORATstpQryBrokerUserFunctionField
{
		
	///交易使用者程式碼
	TTORATstpUserIDType	UserID;


};

/// BrokerUserFunction
struct CTORATstpBrokerUserFunctionField
{
		
	///使用者程式碼
	TTORATstpUserIDType	UserID;

	///功能程式碼
	TTORATstpFunctionIDType	FunctionID;


};

/// 查詢經紀公司使用者與投資者關係
struct CTORATstpQryBUProxyField
{
		
	///投資者程式碼
	TTORATstpInvestorIDType	InvestorID;

	///交易使用者程式碼
	TTORATstpUserIDType	UserID;

	///投資單元程式碼
	TTORATstpBusinessUnitIDType	BusinessUnitID;


};

/// 經紀公司使用者與投資者關係
struct CTORATstpBUProxyField
{
		
	///投資者程式碼
	TTORATstpInvestorIDType	InvestorID;

	///使用者程式碼
	TTORATstpUserIDType	UserID;

	///投資單元程式碼
	TTORATstpBusinessUnitIDType	BusinessUnitID;


};

/// 查詢User
struct CTORATstpQryUserField
{
		
	///使用者程式碼
	TTORATstpUserIDType	UserID;

	///使用者型別
	TTORATstpUserTypeType	UserType;


};

/// User
struct CTORATstpUserField
{
		
	///使用者程式碼
	TTORATstpUserIDType	UserID;

	///使用者名稱稱
	TTORATstpUserNameType	UserName;

	///使用者型別
	TTORATstpUserTypeType	UserType;

	///是否活躍
	TTORATstpBoolType	IsActive;

	///登入限制
	TTORATstpLoginLimitType	LoginLimit;


};

/// 查詢投資者
struct CTORATstpQryInvestorField
{
		
	///投資者程式碼
	TTORATstpInvestorIDType	InvestorID;


};

/// 投資者
struct CTORATstpInvestorField
{
		
	///投資者程式碼
	TTORATstpInvestorIDType	InvestorID;

	///投資者名稱
	TTORATstpInvestorNameType	InvestorName;

	///證件型別
	TTORATstpIdCardTypeType	IdCardType;

	///證件號碼
	TTORATstpIdCardNoType	IdCardNo;

	///聯絡電話
	TTORATstpTelephoneType	Telephone;

	///通訊地址
	TTORATstpAddressType	Address;

	///開戶日期
	TTORATstpDateType	OpenDate;

	///手機
	TTORATstpMobileType	Mobile;

	///委託方式
	TTORATstpOperwaysType	Operways;

	///客戶風險等級
	TTORATstpCRiskLevelType	CRiskLevel;

	///專業投資者類別
	TTORATstpProfInvestorTypeType	ProfInvestorType;


};

/// 查詢交易編碼
struct CTORATstpQryShareholderAccountField
{
		
	///投資者程式碼
	TTORATstpInvestorIDType	InvestorID;

	///交易所程式碼
	TTORATstpExchangeIDType	ExchangeID;

	///交易所下的交易市場，如滬A、滬B市場
	TTORATstpMarketIDType	MarketID;

	///股東程式碼
	TTORATstpShareholderIDType	ShareholderID;

	///普通，信用，衍生品等
	TTORATstpClientIDTypeType	TradingCodeClass;


};

/// 交易編碼
struct CTORATstpShareholderAccountField
{
		
	///投資者程式碼
	TTORATstpInvestorIDType	InvestorID;

	///交易所程式碼
	TTORATstpExchangeIDType	ExchangeID;

	///客戶程式碼
	TTORATstpShareholderIDType	ShareholderID;

	///交易編碼型別
	TTORATstpClientIDTypeType	ClientIDType;

	///市場程式碼
	TTORATstpMarketIDType	MarketID;


};

/// 查詢投資單元
struct CTORATstpQryBusinessUnitField
{
		
	///投資者程式碼
	TTORATstpInvestorIDType	InvestorID;


};

/// 投資單元
struct CTORATstpBusinessUnitField
{
		
	///投資者程式碼
	TTORATstpInvestorIDType	InvestorID;

	///投資單元程式碼
	TTORATstpBusinessUnitIDType	BusinessUnitID;

	///投資單元名稱
	TTORATstpBusinessUnitNameType	BusinessUnitName;


};

/// 查詢投資單元與交易賬戶關係
struct CTORATstpQryBusinessUnitAndTradingAcctField
{
		
	///投資者程式碼
	TTORATstpInvestorIDType	InvestorID;

	///投資單元程式碼
	TTORATstpBusinessUnitIDType	BusinessUnitID;

	///證券市場中的具體品種，如上海股票
	TTORATstpProductIDType	ProductID;

	///資金賬戶
	TTORATstpAccountIDType	AccountID;

	///幣種
	TTORATstpCurrencyIDType	CurrencyID;


};

/// 投資單元與交易賬戶關係
struct CTORATstpBusinessUnitAndTradingAcctField
{
		
	///經紀公司程式碼
	TTORATstpInvestorIDType	InvestorID;

	///投資單元程式碼
	TTORATstpBusinessUnitIDType	BusinessUnitID;

	///交易所程式碼
	TTORATstpExchangeIDType	ExchangeID;

	///市場程式碼
	TTORATstpMarketIDType	MarketID;

	///客戶程式碼
	TTORATstpShareholderIDType	ShareholderID;

	///產品程式碼
	TTORATstpProductIDType	ProductID;

	///資金賬戶程式碼
	TTORATstpAccountIDType	AccountID;

	///資金賬戶程式碼
	TTORATstpCurrencyIDType	CurrencyID;

	///使用者程式碼
	TTORATstpUserIDType	UserID;


};

/// 查詢報單
struct CTORATstpQryOrderField
{
		
	///投資者程式碼
	TTORATstpInvestorIDType	InvestorID;

	///合約在系統中的編號
	TTORATstpSecurityIDType	SecurityID;

	///交易所程式碼
	TTORATstpExchangeIDType	ExchangeID;

	///交易所下的交易市場，如滬A、滬B市場
	TTORATstpMarketIDType	MarketID;

	///客戶在系統中的編號，編號唯一且遵循交易所制定的編碼規則
	TTORATstpShareholderIDType	ShareholderID;

	///報單編號
	TTORATstpOrderSysIDType	OrderSysID;

	///Insert Time
	TTORATstpTimeType	InsertTimeStart;

	///Insert Time
	TTORATstpTimeType	InsertTimeEnd;

	///投資單元程式碼
	TTORATstpBusinessUnitIDType	BusinessUnitID;

	///長字串附加資訊
	TTORATstpBigsInfoType	BInfo;

	///短字串附加資訊
	TTORATstpShortsInfoType	SInfo;

	///整形附加資訊
	TTORATstpIntInfoType	IInfo;

	///是否可撤
	TTORATstpBoolType	IsCancel;


};

/// 查詢撤單
struct CTORATstpQryOrderActionField
{
		
	///投資者程式碼
	TTORATstpInvestorIDType	InvestorID;

	///一個交易所的編號
	TTORATstpExchangeIDType	ExchangeID;

	///交易所下的交易市場，如滬A、滬B市場
	TTORATstpMarketIDType	MarketID;

	///客戶在系統中的編號，編號唯一且遵循交易所制定的編碼規則
	TTORATstpShareholderIDType	ShareholderID;

	///長字串附加資訊
	TTORATstpBigsInfoType	BInfo;

	///短字串附加資訊
	TTORATstpShortsInfoType	SInfo;

	///整形附加資訊
	TTORATstpIntInfoType	IInfo;


};

/// 查詢成交
struct CTORATstpQryTradeField
{
		
	///投資者程式碼
	TTORATstpInvestorIDType	InvestorID;

	///合約在系統中的編號
	TTORATstpSecurityIDType	SecurityID;

	///交易所程式碼
	TTORATstpExchangeIDType	ExchangeID;

	///交易所下的交易市場，如滬A、滬B市場
	TTORATstpMarketIDType	MarketID;

	///客戶在系統中的編號，編號唯一且遵循交易所制定的編碼規則
	TTORATstpShareholderIDType	ShareholderID;

	///成交編號
	TTORATstpTradeIDType	TradeID;

	///Insert Time
	TTORATstpTimeType	TradeTimeStart;

	///Insert Time
	TTORATstpTimeType	TradeTimeEnd;

	///投資單元程式碼
	TTORATstpBusinessUnitIDType	BusinessUnitID;


};

/// 查詢資金賬戶
struct CTORATstpQryTradingAccountField
{
		
	///投資者程式碼
	TTORATstpInvestorIDType	InvestorID;

	///幣種
	TTORATstpCurrencyIDType	CurrencyID;

	///資金賬戶
	TTORATstpAccountIDType	AccountID;

	///1：普通，2：信用，3：衍生品
	TTORATstpAccountTypeType	AccountType;

	///經紀公司部門程式碼
	TTORATstpDepartmentIDType	DepartmentID;


};

/// 資金賬戶
struct CTORATstpTradingAccountField
{
		
	///資金賬戶程式碼
	TTORATstpAccountIDType	AccountID;

	///可用資金
	TTORATstpMoneyType	Available;

	///可取資金
	TTORATstpMoneyType	WithdrawQuota;

	///幣種程式碼
	TTORATstpCurrencyIDType	CurrencyID;

	///入金金額
	TTORATstpMoneyType	Deposit;

	///出金金額
	TTORATstpMoneyType	Withdraw;

	///凍結的保證金
	TTORATstpMoneyType	FrozenMargin;

	///凍結的資金
	TTORATstpMoneyType	FrozenCash;

	///凍結的手續費
	TTORATstpMoneyType	FrozenCommission;

	///當前保證金總額
	TTORATstpMoneyType	CurrMargin;

	///手續費
	TTORATstpMoneyType	Commission;

	///資金賬戶型別
	TTORATstpAccountTypeType	AccountType;

	///資金賬戶所屬投資者程式碼
	TTORATstpInvestorIDType	AccountOwner;

	///部門程式碼
	TTORATstpDepartmentIDType	DepartmentID;

	///銀行程式碼
	TTORATstpBankIDType	BankID;

	///銀行賬戶
	TTORATstpBankAccountIDType	BankAccountID;


};

/// 查詢投資者持倉
struct CTORATstpQryPositionField
{
		
	///投資者程式碼
	TTORATstpInvestorIDType	InvestorID;

	///證券程式碼
	TTORATstpSecurityIDType	SecurityID;

	///交易所程式碼
	TTORATstpExchangeIDType	ExchangeID;

	///交易所下的交易市場，如滬A、滬B市場
	TTORATstpMarketIDType	MarketID;

	///交易賬戶程式碼
	TTORATstpShareholderIDType	ShareholderID;

	///投資單元程式碼
	TTORATstpBusinessUnitIDType	BusinessUnitID;


};

/// 投資者持倉
struct CTORATstpPositionField
{
		
	///合約程式碼
	TTORATstpSecurityIDType	SecurityID;

	///投資者程式碼
	TTORATstpInvestorIDType	InvestorID;

	///投資單元程式碼
	TTORATstpBusinessUnitIDType	BusinessUnitID;

	///交易所程式碼
	TTORATstpExchangeIDType	ExchangeID;

	///市場程式碼
	TTORATstpMarketIDType	MarketID;

	///客戶程式碼
	TTORATstpShareholderIDType	ShareholderID;

	///交易日
	TTORATstpDateType	TradingDay;

	///昨日持倉
	TTORATstpVolumeType	HistoryPos;

	///昨日持倉凍結
	TTORATstpVolumeType	HistoryPosFrozen;

	///今日買賣持倉
	TTORATstpVolumeType	TodayBSPos;

	///今日買賣持倉凍結
	TTORATstpVolumeType	TodayBSFrozen;

	///今日申贖持倉
	TTORATstpVolumeType	TodayPRPos;

	///今日申贖持倉凍結
	TTORATstpVolumeType	TodayPRFrozen;

	///持倉成本
	TTORATstpMoneyType	TotalPosCost;

	///今日拆分合並持倉
	TTORATstpVolumeType	TodaySMPos;

	///今日拆分合並持倉凍結
	TTORATstpVolumeType	TodaySMPosFrozen;

	///融資倉位
	TTORATstpVolumeType	MarginBuyPos;

	///融券倉位
	TTORATstpVolumeType	ShortSellPos;

	///上次餘額(盤中不變)
	TTORATstpVolumeType	PrePosition;

	///股份可用
	TTORATstpVolumeType	AvailablePosition;

	///股份餘額
	TTORATstpVolumeType	CurrentPosition;

	///最新價
	TTORATstpPriceType	LastPrice;


};

/// 查詢基礎交易費用
struct CTORATstpQryTradingFeeField
{
		
	///交易所程式碼，目前支援 SSE(上海證券交易所)和SZSE(深圳證券交易所)
	TTORATstpExchangeIDType	ExchangeID;


};

/// 基礎交易費用
struct CTORATstpTradingFeeField
{
		
	///交易所程式碼
	TTORATstpExchangeIDType	ExchangeID;

	///產品程式碼
	TTORATstpProductIDType	ProductID;

	///證券類別程式碼
	TTORATstpSecurityTypeType	SecurityType;

	///合約程式碼
	TTORATstpSecurityIDType	SecurityID;

	///業務類別
	TTORATstpBizClassType	BizClass;

	///印花稅按金額收取比例
	TTORATstpRatioType	StampTaxRatioByAmt;

	///印花稅按面值收取比例
	TTORATstpRatioType	StampTaxRatioByPar;

	///印花稅按筆收取金額
	TTORATstpMoneyType	StampTaxFeePerOrder;

	///印花稅最低收取金額
	TTORATstpMoneyType	StampTaxFeeMin;

	///印花稅最高收取金額
	TTORATstpMoneyType	StampTaxFeeMax;

	///過戶費按金額收取比例
	TTORATstpRatioType	TransferRatioByAmt;

	///過戶費按面值收取比例
	TTORATstpRatioType	TransferRatioByPar;

	///過戶費按筆收取金額
	TTORATstpMoneyType	TransferFeePerOrder;

	///過戶費最低收取金額
	TTORATstpMoneyType	TransferFeeMin;

	///過戶費最高收取金額
	TTORATstpMoneyType	TransferFeeMax;

	///經手費按金額收取比例
	TTORATstpRatioType	HandlingRatioByAmt;

	///經手費按面值收取比例
	TTORATstpRatioType	HandlingRatioByPar;

	///經手費按筆收取金額
	TTORATstpMoneyType	HandlingFeePerOrder;

	///經手費最低收取金額
	TTORATstpMoneyType	HandlingFeeMin;

	///經手費最高收取金額
	TTORATstpMoneyType	HandlingFeeMax;

	///證管費按金額收取比例
	TTORATstpRatioType	RegulateRatioByAmt;

	///證管費按面值收取比例
	TTORATstpRatioType	RegulateRatioByPar;

	///證管費按筆收取金額
	TTORATstpMoneyType	RegulateFeePerOrder;

	///證管費最低收取金額
	TTORATstpMoneyType	RegulateFeeMin;

	///證管費最高收取金額
	TTORATstpMoneyType	RegulateFeeMax;

	///過戶費按數量收取金額
	TTORATstpMoneyType	TransferFeeByVolume;

	///經手費按數量收取金額
	TTORATstpMoneyType	HandlingFeeByVolume;

	///結算費按金額收取比例
	TTORATstpRatioType	SettlementRatioByAmt;

	///結算費按面值收取比例
	TTORATstpRatioType	SettlementRatioByPar;

	///結算費按筆收取金額
	TTORATstpMoneyType	SettlementFeePerOrder;

	///結算費按數量收取金額
	TTORATstpMoneyType	SettlementFeeByVolume;

	///結算費最低收取金額
	TTORATstpMoneyType	SettlementFeeMin;

	///結算費最高收取金額
	TTORATstpMoneyType	SettlementFeeMax;


};

/// 查詢佣金費率
struct CTORATstpQryInvestorTradingFeeField
{
		
	///投資者程式碼
	TTORATstpInvestorIDType	InvestorID;

	///交易所程式碼，目前支援 SSE(上海證券交易所)和SZSE(深圳證券交易所)
	TTORATstpExchangeIDType	ExchangeID;

	///經紀公司部門程式碼
	TTORATstpDepartmentIDType	DepartmentID;


};

/// 佣金費率
struct CTORATstpInvestorTradingFeeField
{
		
	///投資者程式碼
	TTORATstpInvestorIDType	InvestorID;

	///交易所程式碼
	TTORATstpExchangeIDType	ExchangeID;

	///產品程式碼
	TTORATstpProductIDType	ProductID;

	///證券類別程式碼
	TTORATstpSecurityTypeType	SecurityType;

	///合約程式碼
	TTORATstpSecurityIDType	SecurityID;

	///業務類別
	TTORATstpBizClassType	BizClass;

	///佣金型別
	TTORATstpBrokerageTypeType	BrokerageType;

	///佣金按金額收取比例
	TTORATstpRatioType	RatioByAmt;

	///佣金按面值收取比例
	TTORATstpRatioType	RatioByPar;

	///佣金按筆收取金額
	TTORATstpMoneyType	FeePerOrder;

	///佣金最低收取金額
	TTORATstpMoneyType	FeeMin;

	///佣金最高收取金額
	TTORATstpMoneyType	FeeMax;

	///佣金按數量收取金額
	TTORATstpMoneyType	FeeByVolume;

	///經紀公司部門程式碼
	TTORATstpDepartmentIDType	DepartmentID;


};

/// 查詢新股申購額度
struct CTORATstpQryIPOQuotaField
{
		
	///投資者程式碼
	TTORATstpInvestorIDType	InvestorID;

	///交易所程式碼
	TTORATstpExchangeIDType	ExchangeID;

	///市場程式碼
	TTORATstpMarketIDType	MarketID;

	///交易賬戶程式碼
	TTORATstpShareholderIDType	ShareholderID;


};

/// 新股申購額度
struct CTORATstpIPOQuotaField
{
		
	///投資者程式碼
	TTORATstpInvestorIDType	InvestorID;

	///交易所程式碼
	TTORATstpExchangeIDType	ExchangeID;

	///市場程式碼
	TTORATstpMarketIDType	MarketID;

	///客戶程式碼
	TTORATstpShareholderIDType	ShareholderID;

	///可申購額度
	TTORATstpLongVolumeType	MaxVolume;


};

/// 查詢市場
struct CTORATstpQryMarketField
{
		
	///交易所程式碼，目前支援 SSE(上海證券交易所)和SZSE(深圳證券交易所)
	TTORATstpExchangeIDType	ExchangeID;

	///交易所下的交易市場，如滬A、滬B市場
	TTORATstpMarketIDType	MarketID;


};

/// 市場
struct CTORATstpMarketField
{
		
	///市場程式碼
	TTORATstpMarketIDType	MarketID;

	///市場名稱
	TTORATstpNameType	MarketName;

	///交易所程式碼
	TTORATstpExchangeIDType	ExchangeID;


};

/// 查詢報單明細資金
struct CTORATstpQryOrderFundDetailField
{
		
	///投資者程式碼
	TTORATstpInvestorIDType	InvestorID;

	///證券程式碼
	TTORATstpSecurityIDType	SecurityID;

	///交易所程式碼
	TTORATstpExchangeIDType	ExchangeID;

	///系統報單編號
	TTORATstpOrderSysIDType	OrderSysID;

	///Insert Time
	TTORATstpTimeType	InsertTimeStart;

	///Insert Time
	TTORATstpTimeType	InsertTimeEnd;

	///投資單元程式碼
	TTORATstpBusinessUnitIDType	BusinessUnitID;


};

/// 報單明細資金
struct CTORATstpOrderFundDetailField
{
		
	///投資者程式碼
	TTORATstpInvestorIDType	InvestorID;

	///合約程式碼
	TTORATstpSecurityIDType	InstrumentID;

	///交易所程式碼
	TTORATstpExchangeIDType	ExchangeID;

	///交易日
	TTORATstpDateType	TradingDay;

	///系統報單編號
	TTORATstpOrderSysIDType	OrderSysID;

	///投資單元程式碼
	TTORATstpBusinessUnitIDType	BusinessUnitID;

	///資金賬戶程式碼
	TTORATstpAccountIDType	AccountID;

	///初始凍結金額
	TTORATstpMoneyType	TotalFrozen;

	///總費用
	TTORATstpMoneyType	TotalFee;

	///印花稅
	TTORATstpMoneyType	StampTaxFee;

	///經手費
	TTORATstpMoneyType	HandlingFee;

	///過戶費
	TTORATstpMoneyType	TransferFee;

	///證管費
	TTORATstpMoneyType	RegulateFee;

	///佣金
	TTORATstpMoneyType	BrokerageFee;

	///結算費
	TTORATstpMoneyType	SettlementFee;

	///初始凍結費用合計
	TTORATstpMoneyType	TotalFeeFrozen;

	///報單初始凍結金額
	TTORATstpMoneyType	OrderAmount;


};

/// 查詢資金轉移流水
struct CTORATstpQryFundTransferDetailField
{
		
	///資金賬戶程式碼
	TTORATstpAccountIDType	AccountID;

	///幣種
	TTORATstpCurrencyIDType	CurrencyID;

	///轉移方向
	TTORATstpTransferDirectionType	TransferDirection;

	///經紀公司部門程式碼
	TTORATstpDepartmentIDType	DepartmentID;


};

/// 資金轉移流水
struct CTORATstpFundTransferDetailField
{
		
	///轉賬流水號
	TTORATstpSerialType	FundSerial;

	///申請流水號
	TTORATstpExternalSerialType	ApplySerial;

	///前置編號
	TTORATstpFrontIDType	FrontID;

	///會話編號
	TTORATstpSessionIDType	SessionID;

	///資金賬戶程式碼
	TTORATstpAccountIDType	AccountID;

	///幣種
	TTORATstpCurrencyIDType	CurrencyID;

	///轉移方向
	TTORATstpTransferDirectionType	TransferDirection;

	///出入金金額
	TTORATstpMoneyType	Amount;

	///轉移狀態
	TTORATstpTransferStatusType	TransferStatus;

	///操作來源
	TTORATstpOperateSourceType	OperateSource;

	///操作人員
	TTORATstpUserIDType	OperatorID;

	///操作日期
	TTORATstpDateType	OperateDate;

	///操作時間
	TTORATstpTimeType	OperateTime;

	///狀態資訊
	TTORATstpErrorMsgType	StatusMsg;

	///經紀公司部門程式碼
	TTORATstpDepartmentIDType	DepartmentID;

	///銀行程式碼
	TTORATstpBankIDType	BankID;

	///簽約銀行賬戶
	TTORATstpBankAccountIDType	BankAccountID;


};

/// 查詢持倉轉移流水
struct CTORATstpQryPositionTransferDetailField
{
		
	///目前該欄位存放的是上證所和深圳的股東程式碼。
	TTORATstpShareholderIDType	ShareholderID;

	///證券程式碼
	TTORATstpSecurityIDType	SecurityID;

	///轉移方向
	TTORATstpTransferDirectionType	TransferDirection;


};

/// 持倉轉移流水
struct CTORATstpPositionTransferDetailField
{
		
	///流水號
	TTORATstpSerialType	PositionSerial;

	///申請流水號
	TTORATstpExternalSerialType	ApplySerial;

	///前置編號
	TTORATstpFrontIDType	FrontID;

	///會話編號
	TTORATstpSessionIDType	SessionID;

	///投資者程式碼
	TTORATstpInvestorIDType	InvestorID;

	///交易所程式碼
	TTORATstpExchangeIDType	ExchangeID;

	///交易賬戶程式碼
	TTORATstpShareholderIDType	ShareholderID;

	///市場程式碼
	TTORATstpMarketIDType	MarketID;

	///證券程式碼
	TTORATstpSecurityIDType	SecurityID;

	///交易日期
	TTORATstpDateType	TradingDay;

	///轉移方向
	TTORATstpTransferDirectionType	TransferDirection;

	///轉移持倉型別
	TTORATstpTransferPositionTypeType	TransferPositionType;

	///轉移狀態
	TTORATstpTransferStatusType	TransferStatus;

	///昨日倉位數量
	TTORATstpVolumeType	HistoryVolume;

	///今日買賣倉位數量
	TTORATstpVolumeType	TodayBSVolume;

	///今日申贖倉位數量
	TTORATstpVolumeType	TodayPRVolume;

	///操作人員
	TTORATstpUserIDType	OperatorID;

	///操作日期
	TTORATstpDateType	OperateDate;

	///操作時間
	TTORATstpTimeType	OperateTime;

	///投資單元程式碼
	TTORATstpBusinessUnitIDType	BusinessUnitID;

	///狀態資訊
	TTORATstpErrorMsgType	StatusMsg;


};

/// 查詢投資者質押持倉
struct CTORATstpQryPledgePositionField
{
		
	///投資者程式碼
	TTORATstpInvestorIDType	InvestorID;

	///證券程式碼
	TTORATstpSecurityIDType	SecurityID;

	///交易所程式碼
	TTORATstpExchangeIDType	ExchangeID;

	///交易所下的交易市場，如滬A、滬B市場
	TTORATstpMarketIDType	MarketID;

	///交易賬戶程式碼
	TTORATstpShareholderIDType	ShareholderID;

	///投資單元程式碼
	TTORATstpBusinessUnitIDType	BusinessUnitID;


};

/// 投資者質押持倉
struct CTORATstpPledgePositionField
{
		
	///合約程式碼
	TTORATstpSecurityIDType	SecurityID;

	///投資者程式碼
	TTORATstpInvestorIDType	InvestorID;

	///投資單元程式碼
	TTORATstpBusinessUnitIDType	BusinessUnitID;

	///交易所程式碼
	TTORATstpExchangeIDType	ExchangeID;

	///市場程式碼
	TTORATstpMarketIDType	MarketID;

	///客戶程式碼
	TTORATstpShareholderIDType	ShareholderID;

	///交易日
	TTORATstpDateType	TradingDay;

	///昨日質押持倉
	TTORATstpVolumeType	HisPledgePos;

	///昨日質押持倉凍結
	TTORATstpVolumeType	HisPledgePosFrozen;

	///今日入庫的質押持倉
	TTORATstpVolumeType	TodayPledgePos;

	///今日入庫的質押持倉凍結
	TTORATstpVolumeType	TodayPledgePosFrozen;

	///昨日質押入庫的現券總量
	TTORATstpVolumeType	PreTotalPledgePos;

	///昨日質押入庫的現券可用數量
	TTORATstpVolumeType	preAvailablePledgePos;


};

/// 查詢證券質押資訊
struct CTORATstpQryPledgeInfoField
{
		
	///交易所程式碼
	TTORATstpExchangeIDType	ExchangeID;

	///證券程式碼
	TTORATstpSecurityIDType	SecurityID;


};

/// 證券質押資訊
struct CTORATstpPledgeInfoField
{
		
	///交易所程式碼
	TTORATstpExchangeIDType	ExchangeID;

	///市場程式碼
	TTORATstpMarketIDType	MarketID;

	///證券程式碼
	TTORATstpSecurityIDType	SecurityID;

	///質押申報程式碼
	TTORATstpSecurityIDType	PledgeOrderID;

	///標準券程式碼
	TTORATstpSecurityIDType	StandardBondID;

	///是否可入庫
	TTORATstpBoolType	AllowPledgeIn;

	///是否可出庫
	TTORATstpBoolType	AllowPledgeOut;

	///標準券折算率/折算值
	TTORATstpRatioType	ConversionRate;

	///每次可以入庫的最小交易單位
	TTORATstpTradingUnitType	PledgeInTradingUnit;

	///每次可以出庫的最小交易單位
	TTORATstpTradingUnitType	PledgeOutTradingUnit;

	///證券可以入庫的最大數量
	TTORATstpVolumeType	PledgeInVolMax;

	///證券可以入庫的最小數量
	TTORATstpVolumeType	PledgeInVolMin;

	///證券可以出庫的最大數量
	TTORATstpVolumeType	PledgeOutVolMax;

	///證券可以出庫的最小數量
	TTORATstpVolumeType	PledgeOutVolMin;

	///當日質押入庫的質押券是否能出庫
	TTORATstpBoolType	IsTodayToPlegeOut;

	///是否可撤單
	TTORATstpBoolType	IsCancelOrder;


};

/// 查詢可轉債資訊
struct CTORATstpQryConversionBondInfoField
{
		
	///交易所程式碼
	TTORATstpExchangeIDType	ExchangeID;

	///證券程式碼
	TTORATstpSecurityIDType	SecurityID;


};

/// 可轉債資訊
struct CTORATstpConversionBondInfoField
{
		
	///交易所程式碼
	TTORATstpExchangeIDType	ExchangeID;

	///市場程式碼
	TTORATstpMarketIDType	MarketID;

	///證券程式碼
	TTORATstpSecurityIDType	SecurityID;

	///轉股申報程式碼
	TTORATstpSecurityIDType	ConvertOrderID;

	///轉股價格
	TTORATstpPriceType	ConvertPrice;

	///每次可以轉股最小交易單位
	TTORATstpTradingUnitType	ConvertVolUnit;

	///證券可以轉股的最大數量
	TTORATstpVolumeType	ConvertVolMax;

	///證券可以轉股的最小數量
	TTORATstpVolumeType	ConvertVolMin;

	///轉股開始日期
	TTORATstpDateType	BeginDate;

	///轉股截至日期
	TTORATstpDateType	EndDate;

	///是否可撤單
	TTORATstpBoolType	IsSupportCancel;


};

/// 查詢債券回售資訊
struct CTORATstpQryBondPutbackInfoField
{
		
	///交易所程式碼
	TTORATstpExchangeIDType	ExchangeID;

	///證券程式碼
	TTORATstpSecurityIDType	SecurityID;


};

/// 債券回售資訊
struct CTORATstpBondPutbackInfoField
{
		
	///交易所程式碼
	TTORATstpExchangeIDType	ExchangeID;

	///市場程式碼
	TTORATstpMarketIDType	MarketID;

	///證券程式碼
	TTORATstpSecurityIDType	SecurityID;

	///回售申報程式碼
	TTORATstpSecurityIDType	PutbackOrderID;

	///回售價格
	TTORATstpPriceType	PutbackPrice;

	///每次可以回售最小交易單位
	TTORATstpTradingUnitType	PutbackVolUnit;

	///債券可以回售的最大數量
	TTORATstpVolumeType	PutbackVolMax;

	///債券可以回售的最小數量
	TTORATstpVolumeType	PutbackVolMin;

	///回售開始日期
	TTORATstpDateType	BeginDate;

	///回售截至日期
	TTORATstpDateType	EndDate;

	///是否可撤單
	TTORATstpBoolType	IsSupportCancel;


};

/// 查詢投資者標準券額度
struct CTORATstpQryStandardBondPositionField
{
		
	///投資者程式碼
	TTORATstpInvestorIDType	InvestorID;

	///證券程式碼
	TTORATstpSecurityIDType	SecurityID;

	///交易所程式碼
	TTORATstpExchangeIDType	ExchangeID;

	///交易所下的交易市場，如滬A、滬B市場
	TTORATstpMarketIDType	MarketID;

	///交易賬戶程式碼
	TTORATstpShareholderIDType	ShareholderID;

	///投資單元程式碼
	TTORATstpBusinessUnitIDType	BusinessUnitID;


};

/// 投資者標準券額度
struct CTORATstpStandardBondPositionField
{
		
	///合約程式碼
	TTORATstpSecurityIDType	SecurityID;

	///投資者程式碼
	TTORATstpInvestorIDType	InvestorID;

	///投資單元程式碼
	TTORATstpBusinessUnitIDType	BusinessUnitID;

	///交易所程式碼
	TTORATstpExchangeIDType	ExchangeID;

	///市場程式碼
	TTORATstpMarketIDType	MarketID;

	///客戶程式碼
	TTORATstpShareholderIDType	ShareholderID;

	///交易日
	TTORATstpDateType	TradingDay;

	///標準券可用額度
	TTORATstpPositionVolumeType	AvailablePosition;

	///標準券可用額度凍結
	TTORATstpPositionVolumeType	AvailablePosFrozen;

	///標準券額度總量
	TTORATstpPositionVolumeType	TotalPosition;


};

/// 查詢指定交易登記&撤銷報單
struct CTORATstpQryDesignationRegistrationField
{
		
	///投資者程式碼
	TTORATstpInvestorIDType	InvestorID;

	///目前該欄位存放的是上證所和深圳的股東程式碼。
	TTORATstpShareholderIDType	ShareholderID;

	///全系統的唯一報單編號。16位，1-2位為交易所標識，3-5位為經紀公司程式碼，6-8位為交易單元標識，後面8位為流水號。
	TTORATstpOrderSysIDType	OrderSysID;

	///Insert Time
	TTORATstpTimeType	InsertTimeStart;

	///Insert Time
	TTORATstpTimeType	InsertTimeEnd;

	///投資單元程式碼
	TTORATstpBusinessUnitIDType	BusinessUnitID;


};

/// 指定交易登記&撤銷報單
struct CTORATstpDesignationRegistrationField
{
		
	///投資者程式碼
	TTORATstpInvestorIDType	InvestorID;

	///使用者程式碼
	TTORATstpUserIDType	UserID;

	///買賣方向
	TTORATstpDesignationTypeType	DesignationType;

	///本地報單編號
	TTORATstpOrderLocalIDType	OrderLocalID;

	///客戶程式碼
	TTORATstpShareholderIDType	ShareholderID;

	///交易單元程式碼
	TTORATstpPbuIDType	PbuID;

	///報單提交狀態
	TTORATstpOrderSubmitStatusType	OrderSubmitStatus;

	///交易日
	TTORATstpDateType	TradingDay;

	///報單編號
	TTORATstpOrderSysIDType	OrderSysID;

	///報單狀態
	TTORATstpOrderStatusType	OrderStatus;

	///報單日期
	TTORATstpDateType	InsertDate;

	///委託時間
	TTORATstpTimeType	InsertTime;

	///狀態資訊
	TTORATstpErrorMsgType	StatusMsg;

	///投資單元程式碼
	TTORATstpBusinessUnitIDType	BusinessUnitID;

	///資金賬戶程式碼
	TTORATstpAccountIDType	AccountID;

	///幣種
	TTORATstpCurrencyIDType	CurrencyID;

	///經紀公司部門程式碼
	TTORATstpDepartmentIDType	DepartmentID;


};

/// 深證轉託管報單表
struct CTORATstpQryCustodyTransferField
{
		
	///投資者程式碼
	TTORATstpInvestorIDType	InvestorID;

	///目前該欄位存放的是上證所和深圳的股東程式碼。
	TTORATstpShareholderIDType	ShareholderID;

	///全系統的唯一報單編號。16位，1-2位為交易所標識，3-5位為經紀公司程式碼，6-8位為交易單元標識，後面8位為流水號。
	TTORATstpOrderSysIDType	OrderSysID;

	///Insert Time
	TTORATstpTimeType	InsertTimeStart;

	///Insert Time
	TTORATstpTimeType	InsertTimeEnd;

	///投資單元程式碼
	TTORATstpBusinessUnitIDType	BusinessUnitID;

	///證券程式碼
	TTORATstpSecurityIDType	SecurityID;


};

/// 轉託管報單表
struct CTORATstpCustodyTransferField
{
		
	///投資者程式碼
	TTORATstpInvestorIDType	InvestorID;

	///使用者程式碼
	TTORATstpUserIDType	UserID;

	///轉託管型別
	TTORATstpCustodyTransferTypeType	CustodyTransferType;

	///本地報單編號
	TTORATstpOrderLocalIDType	OrderLocalID;

	///客戶程式碼
	TTORATstpShareholderIDType	ShareholderID;

	///交易單元程式碼
	TTORATstpPbuIDType	PbuID;

	///報單提交狀態
	TTORATstpOrderSubmitStatusType	OrderSubmitStatus;

	///交易日
	TTORATstpDateType	TradingDay;

	///報單編號
	TTORATstpOrderSysIDType	OrderSysID;

	///報單狀態
	TTORATstpOrderStatusType	OrderStatus;

	///報單日期
	TTORATstpDateType	InsertDate;

	///委託時間
	TTORATstpTimeType	InsertTime;

	///狀態資訊
	TTORATstpErrorMsgType	StatusMsg;

	///投資單元程式碼
	TTORATstpBusinessUnitIDType	BusinessUnitID;

	///資金賬戶程式碼
	TTORATstpAccountIDType	AccountID;

	///幣種
	TTORATstpCurrencyIDType	CurrencyID;

	///經紀公司部門程式碼
	TTORATstpDepartmentIDType	DepartmentID;

	///轉入交易單元程式碼
	TTORATstpPbuIDType	TransfereePbuID;

	///合約程式碼
	TTORATstpSecurityIDType	SecurityID;

	///本地撤單編號,被主動撤單的轉託管的原始編號
	TTORATstpOrderLocalIDType	OrignalOrderLocalID;

	///報單數量
	TTORATstpVolumeType	VolumeTotalOriginal;

	///撤銷時間
	TTORATstpTimeType	CancelTime;

	///撤銷交易單元程式碼
	TTORATstpPbuIDType	ActiveTraderID;

	///撤銷操作員
	TTORATstpUserIDType	ActiveUserID;


};

/// 查詢實時特別行情
struct CTORATstpQrySpecialMarketDataField
{
		
	///證券程式碼
	TTORATstpSecurityIDType	SecurityID;

	///交易所程式碼，目前支援 SSE(上海證券交易所)和SZSE(深圳證券交易所)
	TTORATstpExchangeIDType	ExchangeID;


};

/// 實時特別行情
struct CTORATstpSpecialMarketDataField
{
		
	///交易日
	TTORATstpDateType	TradingDay;

	///交易所程式碼
	TTORATstpExchangeIDType	ExchangeID;

	///合約程式碼
	TTORATstpSecurityIDType	SecurityID;

	///證券名稱
	TTORATstpSecurityNameType	SecurityName;

	///移動平均價
	TTORATstpPriceType	MovingAvgPrice;

	///移動平均價的取樣數量
	TTORATstpVolumeType	MovingAvgPriceSamplingNum;

	///最後修改時間
	TTORATstpTimeType	UpdateTime;

	///最後修改毫秒
	TTORATstpMillisecType	UpdateMillisec;


};

/// 查詢未到期債券質押回購委託
struct CTORATstpQryPrematurityRepoOrderField
{
		
	///投資者程式碼
	TTORATstpInvestorIDType	InvestorID;

	///證券程式碼
	TTORATstpSecurityIDType	SecurityID;

	///交易所程式碼
	TTORATstpExchangeIDType	ExchangeID;

	///交易所下的交易市場，如滬A、滬B市場
	TTORATstpMarketIDType	MarketID;

	///交易賬戶程式碼
	TTORATstpShareholderIDType	ShareholderID;

	///投資單元程式碼
	TTORATstpBusinessUnitIDType	BusinessUnitID;

	///報單編號
	TTORATstpOrderLocalIDType	OrderLocalID;

	///證券品種程式碼
	TTORATstpProductIDType	ProductID;

	///證券類別程式碼
	TTORATstpSecurityTypeType	SecurityType;

	///報單類別
	TTORATstpDirectionType	Direction;

	///成交編號
	TTORATstpTradeIDType	TradeID;


};

/// 未到期債券質押回購委託
struct CTORATstpPrematurityRepoOrderField
{
		
	///交易所程式碼
	TTORATstpExchangeIDType	ExchangeID;

	///市場程式碼
	TTORATstpMarketIDType	MarketID;

	///投資者程式碼
	TTORATstpInvestorIDType	InvestorID;

	///交易賬戶程式碼
	TTORATstpShareholderIDType	ShareholderID;

	///投資單元程式碼
	TTORATstpBusinessUnitIDType	BusinessUnitID;

	///成交日期
	TTORATstpDateType	TradeDay;

	///到期日期
	TTORATstpDateType	ExpireDay;

	///報單編號
	TTORATstpOrderLocalIDType	OrderLocalID;

	///證券程式碼
	TTORATstpSecurityIDType	SecurityID;

	///證券名稱
	TTORATstpSecurityNameType	SecurityName;

	///證券品種程式碼
	TTORATstpProductIDType	ProductID;

	///證券類別程式碼
	TTORATstpSecurityTypeType	SecurityType;

	///報單類別
	TTORATstpDirectionType	Direction;

	///成交數量
	TTORATstpVolumeType	VolumeTraded;

	///成交價格
	TTORATstpPriceType	Price;

	///成交金額
	TTORATstpMoneyType	Turnover;

	///成交編號
	TTORATstpTradeIDType	TradeID;

	///購回應收金額
	TTORATstpMoneyType	RepoTotalMoney;

	///利息金額
	TTORATstpMoneyType	InterestAmount;


};

/// 查詢股東引數
struct CTORATstpQryShareholderParamField
{
		
	///市場程式碼
	TTORATstpMarketIDType	MarketID;

	///股東賬戶程式碼
	TTORATstpShareholderIDType	ShareholderID;

	///普通，信用，衍生品等
	TTORATstpClientIDTypeType	TradingCodeClass;

	///產品類別
	TTORATstpProductIDType	ProductID;

	///證券類別
	TTORATstpSecurityTypeType	SecurityType;

	///證券程式碼
	TTORATstpSecurityIDType	SecurityID;

	///引數型別
	TTORATstpParamTypeType	ParamType;

	///交易所程式碼
	TTORATstpExchangeIDType	ExchangeID;


};

/// 股東引數
struct CTORATstpShareholderParamField
{
		
	///交易所程式碼
	TTORATstpExchangeIDType	ExchangeID;

	///市場程式碼
	TTORATstpMarketIDType	MarketID;

	///交易賬戶程式碼
	TTORATstpShareholderIDType	ShareholderID;

	///賬戶型別
	TTORATstpClientIDTypeType	TradingCodeClass;

	///證券品種
	TTORATstpProductIDType	ProductID;

	///證券類別
	TTORATstpSecurityTypeType	SecurityType;

	///證券程式碼
	TTORATstpSecurityIDType	SecurityID;

	///股東引數型別
	TTORATstpParamTypeType	ParamType;

	///股東引數值
	TTORATstpParameterCharValType	ParamValue;


};

/// 查詢外圍系統倉位調撥流水
struct CTORATstpQryPeripheryPositionTransferDetailField
{
		
	///投資者程式碼
	TTORATstpInvestorIDType	InvestorID;

	///現貨系統交易賬戶程式碼
	TTORATstpShareholderIDType	ShareholderID;

	///證券程式碼
	TTORATstpSecurityIDType	SecurityID;

	///倉位調撥方向
	TTORATstpTransferDirectionType	TransferDirection;

	///投資單元程式碼
	TTORATstpBusinessUnitIDType	BusinessUnitID;


};

/// 查詢投資者條件單限制引數
struct CTORATstpQryInvestorCondOrderLimitParamField
{
		
	///投資者程式碼
	TTORATstpInvestorIDType	InvestorID;


};

/// 投資者條件單限制引數
struct CTORATstpInvestorCondOrderLimitParamField
{
		
	///投資者程式碼
	TTORATstpInvestorIDType	InvestorID;

	///最大條件單數
	TTORATstpVolumeType	MaxCondOrderLimitCnt;

	///當前條件單數
	TTORATstpVolumeType	CurrCondOrderCnt;


};

/// 查詢條件單
struct CTORATstpQryCondOrderField
{
		
	///投資者程式碼
	TTORATstpInvestorIDType	InvestorID;

	///證券程式碼
	TTORATstpSecurityIDType	SecurityID;

	///交易所程式碼，目前支援 SSE(上海證券交易所)和SZSE(深圳證券交易所)
	TTORATstpExchangeIDType	ExchangeID;

	///客戶在系統中的編號，編號唯一且遵循交易所制定的編碼規則
	TTORATstpShareholderIDType	ShareholderID;

	///報單編號
	TTORATstpCondOrderIDType	CondOrderID;

	///Insert Time
	TTORATstpTimeType	InsertTimeStart;

	///Insert Time
	TTORATstpTimeType	InsertTimeEnd;

	///投資單元程式碼
	TTORATstpBusinessUnitIDType	BusinessUnitID;

	///長字串附加資訊
	TTORATstpBigsInfoType	BInfo;

	///短字串附加資訊
	TTORATstpShortsInfoType	SInfo;

	///整形附加資訊
	TTORATstpIntInfoType	IInfo;


};

/// 條件單
struct CTORATstpCondOrderField
{
		
	///交易所程式碼
	TTORATstpExchangeIDType	ExchangeID;

	///投資者程式碼
	TTORATstpInvestorIDType	InvestorID;

	///投資單元程式碼
	TTORATstpBusinessUnitIDType	BusinessUnitID;

	///股東賬戶程式碼
	TTORATstpShareholderIDType	ShareholderID;

	///合約程式碼
	TTORATstpSecurityIDType	SecurityID;

	///買賣方向
	TTORATstpDirectionType	Direction;

	///條件單價格型別
	TTORATstpOrderPriceTypeType	OrderPriceType;

	///條件單數量型別
	TTORATstpOrderVolumeTypeType	OrderVolumeType;

	///有效期型別
	TTORATstpTimeConditionType	TimeCondition;

	///成交量型別
	TTORATstpVolumeConditionType	VolumeCondition;

	///報單價格
	TTORATstpPriceType	LimitPrice;

	///報單數量
	TTORATstpVolumeType	VolumeTotalOriginal;

	///組合開平標誌
	TTORATstpCombOffsetFlagType	CombOffsetFlag;

	///組合投機套保標誌
	TTORATstpCombHedgeFlagType	CombHedgeFlag;

	///條件報單引用
	TTORATstpOrderRefType	CondOrderRef;

	///資金賬戶程式碼
	TTORATstpAccountIDType	AccountID;

	///使用者程式碼
	TTORATstpUserIDType	UserID;

	///請求編號
	TTORATstpRequestIDType	RequestID;

	///IP地址
	TTORATstpIPAddressType	IPAddress;

	///Mac地址
	TTORATstpMacAddressType	MacAddress;

	///條件報單編號
	TTORATstpCondOrderIDType	CondOrderID;

	///終端資訊
	TTORATstpTerminalInfoType	TerminalInfo;

	///長字串附加資訊
	TTORATstpBigsInfoType	BInfo;

	///短字串附加資訊
	TTORATstpShortsInfoType	SInfo;

	///整形附加資訊
	TTORATstpIntInfoType	IInfo;

	///委託方式
	TTORATstpOperwayType	Operway;

	///條件檢查
	TTORATstpCondCheckType	CondCheck;

	///觸發條件
	TTORATstpContingentConditionType	ContingentCondition;

	///條件價
	TTORATstpPriceType	ConditionPrice;

	///價格浮動tick數
	TTORATstpVolumeType	PriceTicks;

	///數量浮動倍數
	TTORATstpVolumeMultipleType	VolumeMultiple;

	///相關前置編號
	TTORATstpFrontIDType	RelativeFrontID;

	///相關會話編號
	TTORATstpSessionIDType	RelativeSessionID;

	///相關條件引數
	TTORATstpRelativeCondParamType	RelativeParam;

	///附加觸發條件
	TTORATstpContingentConditionType	AppendContingentCondition;

	///附加條件價
	TTORATstpPriceType	AppendConditionPrice;

	///附加相關前置編號
	TTORATstpFrontIDType	AppendRelativeFrontID;

	///附加相關會話編號
	TTORATstpSessionIDType	AppendRelativeSessionID;

	///附加相關條件引數
	TTORATstpRelativeCondParamType	AppendRelativeParam;

	///交易日
	TTORATstpDateType	TradingDay;

	///條件單狀態
	TTORATstpCondOrderStatusType	CondOrderStatus;

	///報單日期
	TTORATstpDateType	InsertDate;

	///委託時間
	TTORATstpTimeType	InsertTime;

	///撤銷時間
	TTORATstpTimeType	CancelTime;

	///撤銷使用者
	TTORATstpUserIDType	CancelUser;

	///前置編號
	TTORATstpFrontIDType	FrontID;

	///會話編號
	TTORATstpSessionIDType	SessionID;

	///使用者端產品資訊
	TTORATstpProductInfoType	UserProductInfo;

	///狀態資訊
	TTORATstpErrorMsgType	StatusMsg;

	///經紀公司部門程式碼
	TTORATstpDepartmentIDType	DepartmentID;

	///適當性控制業務類別
	TTORATstpProperCtrlBusinessTypeType	ProperCtrlBusinessType;

	///適當性控制通過標示
	TTORATstpProperCtrlPassFlagType	ProperCtrlPassFlag;

	///觸發日期
	TTORATstpDateType	ActiveDate;

	///觸發時間
	TTORATstpTimeType	ActiveTime;


};

/// 查詢條件單撤單
struct CTORATstpQryCondOrderActionField
{
		
	///投資者程式碼
	TTORATstpInvestorIDType	InvestorID;

	///一個交易所的編號
	TTORATstpExchangeIDType	ExchangeID;

	///股東賬戶程式碼
	TTORATstpShareholderIDType	ShareholderID;

	///長字串附加資訊
	TTORATstpBigsInfoType	BInfo;

	///短字串附加資訊
	TTORATstpShortsInfoType	SInfo;

	///整形附加資訊
	TTORATstpIntInfoType	IInfo;


};

/// 條件單撤單
struct CTORATstpCondOrderActionField
{
		
	///交易所程式碼
	TTORATstpExchangeIDType	ExchangeID;

	///請求編號
	TTORATstpRequestIDType	RequestID;

	///條件單操作引用
	TTORATstpOrderRefType	CondOrderActionRef;

	///條件單引用
	TTORATstpOrderRefType	CondOrderRef;

	///前置編號
	TTORATstpFrontIDType	FrontID;

	///會話編號
	TTORATstpSessionIDType	SessionID;

	///條件單編號
	TTORATstpCondOrderIDType	CondOrderID;

	///操作標誌
	TTORATstpActionFlagType	ActionFlag;

	///投資者程式碼
	TTORATstpInvestorIDType	InvestorID;

	///合約程式碼
	TTORATstpSecurityIDType	SecurityID;

	///使用者程式碼
	TTORATstpUserIDType	UserID;

	///條件單撤單編號
	TTORATstpCondOrderIDType	CancelCondOrderID;

	///IP地址
	TTORATstpIPAddressType	IPAddress;

	///MAC地址
	TTORATstpMacAddressType	MacAddress;

	///終端資訊
	TTORATstpTerminalInfoType	TerminalInfo;

	///長字串附加資訊
	TTORATstpBigsInfoType	BInfo;

	///短字串附加資訊
	TTORATstpShortsInfoType	SInfo;

	///整形附加資訊
	TTORATstpIntInfoType	IInfo;

	///委託方式
	TTORATstpOperwayType	Operway;

	///投資單元程式碼
	TTORATstpBusinessUnitIDType	BusinessUnitID;

	///股東賬戶程式碼
	TTORATstpShareholderIDType	ShareholderID;

	///操作日期
	TTORATstpDateType	ActionDate;

	///操作時間
	TTORATstpTimeType	ActionTime;


};

/// 查詢BrokerUserRole
struct CTORATstpQryBrokerUserRoleField
{
		
	///角色編號
	TTORATstpRoleIDType	RoleID;


};

/// BrokerUserRole
struct CTORATstpBrokerUserRoleField
{
		
	///角色編號
	TTORATstpRoleIDType	RoleID;

	///角色描述
	TTORATstpRoleDescriptionType	RoleDescription;

	///功能許可權集合
	TTORATstpFunctionsType	Functions;


};

/// 查詢BrokerUserRoleAssignment
struct CTORATstpQryBrokerUserRoleAssignmentField
{
		
	///交易使用者程式碼
	TTORATstpUserIDType	UserID;


};

/// BrokerUserRoleAssignment
struct CTORATstpBrokerUserRoleAssignmentField
{
		
	///使用者程式碼
	TTORATstpUserIDType	UserID;

	///角色編號
	TTORATstpRoleIDType	RoleID;

	///角色描述
	TTORATstpRoleDescriptionType	RoleDescription;


};

/// 查詢交易通知
struct CTORATstpQryTradingNoticeField
{
		
	///投資者程式碼
	TTORATstpInvestorIDType	InvestorID;

	///Insert Date
	TTORATstpDateType	InsertDateStart;

	///Insert Date
	TTORATstpDateType	InsertDateEnd;

	///Insert Time
	TTORATstpTimeType	InsertTimeStart;

	///Insert Time
	TTORATstpTimeType	InsertTimeEnd;


};

/// 查詢新股申購配號結果
struct CTORATstpQryIPONumberResultField
{
		
	///申購程式碼
	TTORATstpSecurityIDType	SecurityID;

	///交易所程式碼
	TTORATstpExchangeIDType	ExchangeID;

	///股東程式碼
	TTORATstpShareholderIDType	ShareholderID;


};

/// 新股申購配號結果
struct CTORATstpIPONumberResultField
{
		
	///交易所程式碼
	TTORATstpExchangeIDType	ExchangeID;

	///證券程式碼
	TTORATstpSecurityIDType	SecurityID;

	///日期
	TTORATstpDateType	Day;

	///申購證券名稱
	TTORATstpSecurityNameType	SecurityName;

	///股東程式碼
	TTORATstpShareholderIDType	ShareholderID;

	///證券類別程式碼
	TTORATstpSecurityTypeType	SecurityType;

	///起始配號
	TTORATstpIPONumberIDType	BeginNumberID;

	///配號數量
	TTORATstpVolumeType	Volume;


};

/// 查詢新股申購中籤結果
struct CTORATstpQryIPOMatchNumberResultField
{
		
	///申購程式碼
	TTORATstpSecurityIDType	SecurityID;

	///交易所程式碼
	TTORATstpExchangeIDType	ExchangeID;

	///股東程式碼
	TTORATstpShareholderIDType	ShareholderID;

	///中籤配號
	TTORATstpIPONumberIDType	MatchNumberID;


};

/// 新股申購中籤結果
struct CTORATstpIPOMatchNumberResultField
{
		
	///交易所程式碼
	TTORATstpExchangeIDType	ExchangeID;

	///證券程式碼
	TTORATstpSecurityIDType	SecurityID;

	///日期
	TTORATstpDateType	Day;

	///申購證券名稱
	TTORATstpSecurityNameType	SecurityName;

	///股東程式碼
	TTORATstpShareholderIDType	ShareholderID;

	///證券類別程式碼
	TTORATstpSecurityTypeType	SecurityType;

	///中籤配號
	TTORATstpIPONumberIDType	MatchNumberID;

	///此中籤號擁有的證券數量
	TTORATstpVolumeType	Volume;

	///申購價格
	TTORATstpPriceType	Price;

	///申購金額
	TTORATstpMoneyType	Amout;


};

#endif