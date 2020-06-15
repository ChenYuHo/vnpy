/////////////////////////////////////////////////////////////////////////
///@company 上海泰琰資訊科技有限公司
///@file TORATstpUserApiStruct.h
///@brief 定義了客戶端介面使用的業務資料結構
///@history 
/////////////////////////////////////////////////////////////////////////

#ifndef _TORA_TSTPDATATYPE_H
#define _TORA_TSTPDATATYPE_H

#include <limits.h>
#include <float.h>

#define INT_NULL_VAL INT_MAX

#define FLOAT_NULL_VAL DBL_MAX

#define CHAR_NULL_VAL 0

#define WORD_NULL_VAL SHRT_MAX

#ifdef WINDOWS
#define LONG_NULL_VAL _I64_MAX
#else
#define LONG_NULL_VAL  LLONG_MAX
#endif

#define POINT_NULL_VAL NULL

inline void set_null(int &v)
{
	v = INT_NULL_VAL;
}

inline bool is_null(int v)
{
	return v == INT_NULL_VAL;
}

inline void set_null(double &v)
{
	v = FLOAT_NULL_VAL;
}

inline bool is_null(double v)
{
	return v == FLOAT_NULL_VAL;
}

inline void set_null(char &v)
{
	v = CHAR_NULL_VAL;
}

inline bool is_null(char v)
{
	return v == CHAR_NULL_VAL;
}

inline void set_null(short &v)
{
	v = WORD_NULL_VAL;
}

inline bool is_null(short v)
{
	return v == WORD_NULL_VAL;
}

#ifdef WINDOWS
inline void set_null(__int64 &v)
#else
inline void set_null(long long &v)
#endif
{
	v = LONG_NULL_VAL;
}

#ifdef WINDOWS
inline bool is_null(__int64 v)
#else
inline bool is_null(long long v)
#endif
{
	return v == LONG_NULL_VAL;
}

inline void set_null(char *v)
{
	v[0] = '\0';
}

inline bool is_null(const char *v)
{
	const char *p=v;
	while (*p)
	{
		if (*p!=' ')
		{
			return false;
		}
		p++;
	}
	return true;
}

enum TORA_TE_RESUME_TYPE
{
	TORA_TERT_RESTART = 0,
	TORA_TERT_RESUME,
	TORA_TERT_QUICK
};


/////////////////////////////////////////////////////////////////////////
/// TTORATstpDateType是一個日期型別
/////////////////////////////////////////////////////////////////////////
typedef char TTORATstpDateType[9];

/////////////////////////////////////////////////////////////////////////
/// TTORATstpTimeType是一個時間型別
/////////////////////////////////////////////////////////////////////////
typedef char TTORATstpTimeType[9];

/////////////////////////////////////////////////////////////////////////
/// TTORATstpMillisecType是一個時間（毫秒）型別
/////////////////////////////////////////////////////////////////////////
typedef int TTORATstpMillisecType;

/////////////////////////////////////////////////////////////////////////
/// TTORATstpPriceType是一個價格型別
/////////////////////////////////////////////////////////////////////////
typedef double TTORATstpPriceType;

/////////////////////////////////////////////////////////////////////////
/// TTORATstpRatioType是一個比率型別
/////////////////////////////////////////////////////////////////////////
typedef double TTORATstpRatioType;

/////////////////////////////////////////////////////////////////////////
/// TTORATstpMoneyType是一個資金型別
/////////////////////////////////////////////////////////////////////////
typedef double TTORATstpMoneyType;

/////////////////////////////////////////////////////////////////////////
/// TTORATstpVolumeType是一個數量型別
/////////////////////////////////////////////////////////////////////////
typedef int TTORATstpVolumeType;

/////////////////////////////////////////////////////////////////////////
/// TTORATstpLargeVolumeType是一個大額數量型別
/////////////////////////////////////////////////////////////////////////
typedef double TTORATstpLargeVolumeType;

/////////////////////////////////////////////////////////////////////////
/// TTORATstpBoolType是一個布林型型別
/////////////////////////////////////////////////////////////////////////
typedef int TTORATstpBoolType;

/////////////////////////////////////////////////////////////////////////
/// TTORATstpSequenceNoType是一個流水號型別
/////////////////////////////////////////////////////////////////////////
typedef int TTORATstpSequenceNoType;

/////////////////////////////////////////////////////////////////////////
/// TTORATstpSerialType是一個流水號型別
/////////////////////////////////////////////////////////////////////////
typedef char TTORATstpSerialType[31];

/////////////////////////////////////////////////////////////////////////
/// TTORATstpCommFluxType是一個通訊流量型別
/////////////////////////////////////////////////////////////////////////
typedef int TTORATstpCommFluxType;

/////////////////////////////////////////////////////////////////////////
/// TTORATstpRoleIDType是一個角色編號型別
/////////////////////////////////////////////////////////////////////////
typedef int TTORATstpRoleIDType;

/////////////////////////////////////////////////////////////////////////
/// TTORATstpRoleDescriptionType是一個角色描述型別
/////////////////////////////////////////////////////////////////////////
typedef char TTORATstpRoleDescriptionType[161];

/////////////////////////////////////////////////////////////////////////
/// TTORATstpFunctionsType是一個功能許可權集合型別
/////////////////////////////////////////////////////////////////////////
typedef char TTORATstpFunctionsType[129];

/////////////////////////////////////////////////////////////////////////
/// TTORATstpDeviceIDType是一個裝置標識型別
/////////////////////////////////////////////////////////////////////////
typedef char TTORATstpDeviceIDType[129];

/////////////////////////////////////////////////////////////////////////
/// TTORATstpDeviceSerialType是一個裝置序列型別
/////////////////////////////////////////////////////////////////////////
typedef char TTORATstpDeviceSerialType[129];

/////////////////////////////////////////////////////////////////////////
/// TTORATstpExchangeIDType是一個交易所程式碼型別
/////////////////////////////////////////////////////////////////////////
///內部使用)
#define TORA_TSTP_EXD_SSE_FO 'h'
///內部使用)
#define TORA_TSTP_EXD_SZSE_FO 'z'
///通用(內部使用)
#define TORA_TSTP_EXD_COMM '0'
///上海交易所
#define TORA_TSTP_EXD_SSE '1'
///深圳交易所
#define TORA_TSTP_EXD_SZSE '2'
///香港交易所
#define TORA_TSTP_EXD_HK '3'

typedef char TTORATstpExchangeIDType;

/////////////////////////////////////////////////////////////////////////
/// TTORATstpAuthModeType是一個認證方式型別
/////////////////////////////////////////////////////////////////////////
///密碼
#define TORA_TSTP_AM_Password '0'
///指紋
#define TORA_TSTP_AM_FingerPrint '1'

typedef char TTORATstpAuthModeType;

/////////////////////////////////////////////////////////////////////////
/// TTORATstpVolumeMultipleType是一個合約數量乘數型別
/////////////////////////////////////////////////////////////////////////
typedef int TTORATstpVolumeMultipleType;

/////////////////////////////////////////////////////////////////////////
/// TTORATstpIdCardNoType是一個證件編號型別
/////////////////////////////////////////////////////////////////////////
typedef char TTORATstpIdCardNoType[51];

/////////////////////////////////////////////////////////////////////////
/// TTORATstpUserIDType是一個交易使用者程式碼型別
/////////////////////////////////////////////////////////////////////////
typedef char TTORATstpUserIDType[16];

/////////////////////////////////////////////////////////////////////////
/// TTORATstpTradeIDType是一個成交編號型別
/////////////////////////////////////////////////////////////////////////
typedef char TTORATstpTradeIDType[21];

/////////////////////////////////////////////////////////////////////////
/// TTORATstpOrderSysIDType是一個系統報單編號型別
/////////////////////////////////////////////////////////////////////////
typedef char TTORATstpOrderSysIDType[21];

/////////////////////////////////////////////////////////////////////////
/// TTORATstpCondOrderIDType是一個條件報單編號型別
/////////////////////////////////////////////////////////////////////////
typedef int TTORATstpCondOrderIDType;

/////////////////////////////////////////////////////////////////////////
/// TTORATstpPasswordType是一個密碼型別
/////////////////////////////////////////////////////////////////////////
typedef char TTORATstpPasswordType[41];

/////////////////////////////////////////////////////////////////////////
/// TTORATstpFrontIDType是一個前置編號型別
/////////////////////////////////////////////////////////////////////////
typedef int TTORATstpFrontIDType;

/////////////////////////////////////////////////////////////////////////
/// TTORATstpSessionIDType是一個會話編號型別
/////////////////////////////////////////////////////////////////////////
typedef int TTORATstpSessionIDType;

/////////////////////////////////////////////////////////////////////////
/// TTORATstpProductInfoType是一個產品資訊型別
/////////////////////////////////////////////////////////////////////////
typedef char TTORATstpProductInfoType[11];

/////////////////////////////////////////////////////////////////////////
/// TTORATstpProtocolInfoType是一個協議資訊型別
/////////////////////////////////////////////////////////////////////////
typedef char TTORATstpProtocolInfoType[11];

/////////////////////////////////////////////////////////////////////////
/// TTORATstpErrorIDType是一個錯誤程式碼型別
/////////////////////////////////////////////////////////////////////////
typedef int TTORATstpErrorIDType;

/////////////////////////////////////////////////////////////////////////
/// TTORATstpErrorMsgType是一個錯誤資訊型別
/////////////////////////////////////////////////////////////////////////
typedef char TTORATstpErrorMsgType[81];

/////////////////////////////////////////////////////////////////////////
/// TTORATstpPositionTypeType是一個持倉型別型別
/////////////////////////////////////////////////////////////////////////
///淨持倉
#define TORA_TSTP_PT_Net '1'
///綜合持倉
#define TORA_TSTP_PT_Gross '2'

typedef char TTORATstpPositionTypeType;

/////////////////////////////////////////////////////////////////////////
/// TTORATstpParameterCharValType是一個引數文字值型別
/////////////////////////////////////////////////////////////////////////
typedef char TTORATstpParameterCharValType[101];

/////////////////////////////////////////////////////////////////////////
/// TTORATstpNameType是一個名稱型別
/////////////////////////////////////////////////////////////////////////
typedef char TTORATstpNameType[61];

/////////////////////////////////////////////////////////////////////////
/// TTORATstpListingMarketType是一個掛牌市場型別
/////////////////////////////////////////////////////////////////////////
typedef char TTORATstpListingMarketType[31];

/////////////////////////////////////////////////////////////////////////
/// TTORATstpProductIDType是一個證券品種程式碼型別
/////////////////////////////////////////////////////////////////////////
///通用(內部使用)
#define TORA_TSTP_PID_COMMON '0'
///上海股票
#define TORA_TSTP_PID_SHStock '1'
///上海配股配債
#define TORA_TSTP_PID_SHWarrant '2'
///上海基金
#define TORA_TSTP_PID_SHFund '3'
///上海債券
#define TORA_TSTP_PID_SHBond '4'
///上海標準券
#define TORA_TSTP_PID_SHStandard '5'
///上海質押式回購
#define TORA_TSTP_PID_SHRepurchase '6'
///深圳股票
#define TORA_TSTP_PID_SZStock '7'
///深圳配股配債
#define TORA_TSTP_PID_SZWarrant '8'
///深圳基金
#define TORA_TSTP_PID_SZFund '9'
///深圳債券
#define TORA_TSTP_PID_SZBond 'a'
///深圳標準券
#define TORA_TSTP_PID_SZStandard 'b'
///深圳質押式回購
#define TORA_TSTP_PID_SZRepurchase 'c'

typedef char TTORATstpProductIDType;

/////////////////////////////////////////////////////////////////////////
/// TTORATstpSecurityIDType是一個證券程式碼型別
/////////////////////////////////////////////////////////////////////////
typedef char TTORATstpSecurityIDType[31];

/////////////////////////////////////////////////////////////////////////
/// TTORATstpParValueType是一個面值型別
/////////////////////////////////////////////////////////////////////////
typedef double TTORATstpParValueType;

/////////////////////////////////////////////////////////////////////////
/// TTORATstpPriceTickType是一個最小變動價位型別
/////////////////////////////////////////////////////////////////////////
typedef double TTORATstpPriceTickType;

/////////////////////////////////////////////////////////////////////////
/// TTORATstpTradingUnitType是一個交易單位型別
/////////////////////////////////////////////////////////////////////////
typedef int TTORATstpTradingUnitType;

/////////////////////////////////////////////////////////////////////////
/// TTORATstpSecurityStatusType是一個證券狀態型別
/////////////////////////////////////////////////////////////////////////
typedef int TTORATstpSecurityStatusType;

/////////////////////////////////////////////////////////////////////////
/// TTORATstpAccountIDType是一個投資者資金帳號型別
/////////////////////////////////////////////////////////////////////////
typedef char TTORATstpAccountIDType[21];

/////////////////////////////////////////////////////////////////////////
/// TTORATstpInvestorIDType是一個投資者程式碼型別
/////////////////////////////////////////////////////////////////////////
typedef char TTORATstpInvestorIDType[13];

/////////////////////////////////////////////////////////////////////////
/// TTORATstpAddressType是一個通訊地址型別
/////////////////////////////////////////////////////////////////////////
typedef char TTORATstpAddressType[101];

/////////////////////////////////////////////////////////////////////////
/// TTORATstpDepartmentIDType是一個部門程式碼型別
/////////////////////////////////////////////////////////////////////////
typedef char TTORATstpDepartmentIDType[11];

/////////////////////////////////////////////////////////////////////////
/// TTORATstpTerminalInfoType是一個終端資訊型別
/////////////////////////////////////////////////////////////////////////
typedef char TTORATstpTerminalInfoType[256];

/////////////////////////////////////////////////////////////////////////
/// TTORATstpShareholderIDType是一個股東賬戶程式碼型別
/////////////////////////////////////////////////////////////////////////
typedef char TTORATstpShareholderIDType[11];

/////////////////////////////////////////////////////////////////////////
/// TTORATstpPbuIDType是一個交易單元程式碼型別
/////////////////////////////////////////////////////////////////////////
typedef char TTORATstpPbuIDType[11];

/////////////////////////////////////////////////////////////////////////
/// TTORATstpIPAddressType是一個IP地址型別
/////////////////////////////////////////////////////////////////////////
typedef char TTORATstpIPAddressType[16];

/////////////////////////////////////////////////////////////////////////
/// TTORATstpMacAddressType是一個Mac地址型別
/////////////////////////////////////////////////////////////////////////
typedef char TTORATstpMacAddressType[21];

/////////////////////////////////////////////////////////////////////////
/// TTORATstpLangType是一個語言型別
/////////////////////////////////////////////////////////////////////////
typedef char TTORATstpLangType[17];

/////////////////////////////////////////////////////////////////////////
/// TTORATstpInterestType是一個利息型別
/////////////////////////////////////////////////////////////////////////
typedef double TTORATstpInterestType;

/////////////////////////////////////////////////////////////////////////
/// TTORATstpOrderLocalIDType是一個本地報單編號型別
/////////////////////////////////////////////////////////////////////////
typedef char TTORATstpOrderLocalIDType[13];

/////////////////////////////////////////////////////////////////////////
/// TTORATstpPositionVolumeType是一個證券數量型別
/////////////////////////////////////////////////////////////////////////
typedef double TTORATstpPositionVolumeType;

/////////////////////////////////////////////////////////////////////////
/// TTORATstpBusinessUnitIDType是一個投資單元程式碼型別
/////////////////////////////////////////////////////////////////////////
typedef char TTORATstpBusinessUnitIDType[17];

/////////////////////////////////////////////////////////////////////////
/// TTORATstpBusinessUnitNameType是一個投資單元名稱型別
/////////////////////////////////////////////////////////////////////////
typedef char TTORATstpBusinessUnitNameType[61];

/////////////////////////////////////////////////////////////////////////
/// TTORATstpTimeStampType是一個時間戳型別
/////////////////////////////////////////////////////////////////////////
typedef int TTORATstpTimeStampType;

/////////////////////////////////////////////////////////////////////////
/// TTORATstpBigTimeStampType是一個長時間戳型別
/////////////////////////////////////////////////////////////////////////
typedef long long int TTORATstpBigTimeStampType;

/////////////////////////////////////////////////////////////////////////
/// TTORATstpSecurityNameType是一個證券名稱型別
/////////////////////////////////////////////////////////////////////////
typedef char TTORATstpSecurityNameType[41];

/////////////////////////////////////////////////////////////////////////
/// TTORATstpExternalSerialType是一個外部流水號型別
/////////////////////////////////////////////////////////////////////////
typedef char TTORATstpExternalSerialType[65];

/////////////////////////////////////////////////////////////////////////
/// TTORATstpOrderRefType是一個報單引用型別
/////////////////////////////////////////////////////////////////////////
typedef char TTORATstpOrderRefType[13];

/////////////////////////////////////////////////////////////////////////
/// TTORATstpRequestIDType是一個請求編號型別
/////////////////////////////////////////////////////////////////////////
typedef int TTORATstpRequestIDType;

/////////////////////////////////////////////////////////////////////////
/// TTORATstpIntSerialType是一個整數流水號型別
/////////////////////////////////////////////////////////////////////////
typedef int TTORATstpIntSerialType;

/////////////////////////////////////////////////////////////////////////
/// TTORATstpInvestorNameType是一個投資者名稱型別
/////////////////////////////////////////////////////////////////////////
typedef char TTORATstpInvestorNameType[81];

/////////////////////////////////////////////////////////////////////////
/// TTORATstpUserNameType是一個使用者名稱稱型別
/////////////////////////////////////////////////////////////////////////
typedef char TTORATstpUserNameType[81];

/////////////////////////////////////////////////////////////////////////
/// TTORATstpLoginLimitType是一個登入限制類型
/////////////////////////////////////////////////////////////////////////
typedef int TTORATstpLoginLimitType;

/////////////////////////////////////////////////////////////////////////
/// TTORATstpCurrencyIDType是一個幣種類型
/////////////////////////////////////////////////////////////////////////
typedef char TTORATstpCurrencyIDType[4];

/////////////////////////////////////////////////////////////////////////
/// TTORATstpBankIDType是一個銀行程式碼型別
/////////////////////////////////////////////////////////////////////////
///中國建設銀行
#define TORA_TSTP_BKID_CCB '1'
///中國農業銀行
#define TORA_TSTP_BKID_ABC '2'
///中國工商銀行
#define TORA_TSTP_BKID_ICBC '3'
///中國銀行
#define TORA_TSTP_BKID_BOC '4'
///中國招商銀行
#define TORA_TSTP_BKID_CMB '5'
///中國交通銀行
#define TORA_TSTP_BKID_BC '6'
///浦東發展銀行
#define TORA_TSTP_BKID_SPDB '7'
///興業銀行
#define TORA_TSTP_BKID_CIB '8'
///中國光大銀行
#define TORA_TSTP_BKID_CEB '9'
///廣東發展銀行
#define TORA_TSTP_BKID_GDB 'a'
///南京銀行
#define TORA_TSTP_BKID_NJCB 'b'
///上海銀行
#define TORA_TSTP_BKID_SHCB 'c'
///中信銀行
#define TORA_TSTP_BKID_CITICB 'd'
///華夏銀行
#define TORA_TSTP_BKID_HXB 'e'
///民生銀行
#define TORA_TSTP_BKID_CMBC 'f'
///平安銀行
#define TORA_TSTP_BKID_PACB 'g'
///寧波銀行
#define TORA_TSTP_BKID_NBCB 'h'

typedef char TTORATstpBankIDType;

/////////////////////////////////////////////////////////////////////////
/// TTORATstpBankAccountIDType是一個簽約銀行賬號型別
/////////////////////////////////////////////////////////////////////////
typedef char TTORATstpBankAccountIDType[31];

/////////////////////////////////////////////////////////////////////////
/// TTORATstpTransferReasonType是一個外圍系統倉位調撥原因型別
/////////////////////////////////////////////////////////////////////////
typedef char TTORATstpTransferReasonType[21];

/////////////////////////////////////////////////////////////////////////
/// TTORATstpCombOffsetFlagType是一個組合開平標誌型別
/////////////////////////////////////////////////////////////////////////
typedef char TTORATstpCombOffsetFlagType[5];

/////////////////////////////////////////////////////////////////////////
/// TTORATstpCombHedgeFlagType是一個組合投機套保標誌型別
/////////////////////////////////////////////////////////////////////////
typedef char TTORATstpCombHedgeFlagType[5];

/////////////////////////////////////////////////////////////////////////
/// TTORATstpExchangeInstIDType是一個交易所合約程式碼型別
/////////////////////////////////////////////////////////////////////////
typedef char TTORATstpExchangeInstIDType[31];

/////////////////////////////////////////////////////////////////////////
/// TTORATstpTelephoneType是一個聯絡電話型別
/////////////////////////////////////////////////////////////////////////
typedef char TTORATstpTelephoneType[41];

/////////////////////////////////////////////////////////////////////////
/// TTORATstpMobileType是一個手機型別
/////////////////////////////////////////////////////////////////////////
typedef char TTORATstpMobileType[41];

/////////////////////////////////////////////////////////////////////////
/// TTORATstpTraderIDType是一個交易員程式碼型別
/////////////////////////////////////////////////////////////////////////
typedef char TTORATstpTraderIDType[21];

/////////////////////////////////////////////////////////////////////////
/// TTORATstpLongVolumeType是一個LongVolume型別
/////////////////////////////////////////////////////////////////////////
typedef long long int TTORATstpLongVolumeType;

/////////////////////////////////////////////////////////////////////////
/// TTORATstpLongSequenceType是一個序號型別
/////////////////////////////////////////////////////////////////////////
typedef long long int TTORATstpLongSequenceType;

/////////////////////////////////////////////////////////////////////////
/// TTORATstpOrderUnitType是一個申報單位型別
/////////////////////////////////////////////////////////////////////////
///手
#define TORA_TSTP_OUT_Shou '0'
///股
#define TORA_TSTP_OUT_Gu '1'
///份
#define TORA_TSTP_OUT_Fen '2'
///張
#define TORA_TSTP_OUT_Zhang '3'

typedef char TTORATstpOrderUnitType;

/////////////////////////////////////////////////////////////////////////
/// TTORATstpIdCardTypeType是一個證件型別型別
/////////////////////////////////////////////////////////////////////////
///組織機構程式碼
#define TORA_TSTP_ICT_EID '0'
///中國公民身份證
#define TORA_TSTP_ICT_IDCard '1'
///軍官證
#define TORA_TSTP_ICT_OfficerIDCard '2'
///警官證
#define TORA_TSTP_ICT_PoliceIDCard '3'
///士兵證
#define TORA_TSTP_ICT_SoldierIDCard '4'
///戶口簿
#define TORA_TSTP_ICT_HouseholdRegister  '5'
///護照
#define TORA_TSTP_ICT_Passport '6'
///臺胞證
#define TORA_TSTP_ICT_TaiwanCompatriotIDCard  '7'
///回鄉證
#define TORA_TSTP_ICT_HomeComingCard '8'
///營業執照號
#define TORA_TSTP_ICT_LicenseNo '9'
///稅務登記號/當地納稅ID
#define TORA_TSTP_ICT_TaxNo 'A'
///港澳居民來往內地通行證
#define TORA_TSTP_ICT_HMMainlandTravelPermit 'B'
///臺灣居民來往大陸通行證
#define TORA_TSTP_ICT_TwMainlandTravelPermit 'C'
///駕照
#define TORA_TSTP_ICT_DrivingLicense 'D'
///當地社保ID
#define TORA_TSTP_ICT_SocialID 'F'
///當地身份證
#define TORA_TSTP_ICT_LocalID 'G'
///商業登記證
#define TORA_TSTP_ICT_BusinessRegistration 'H'
///港澳永久性居民身份證
#define TORA_TSTP_ICT_HKMCIDCard 'I'
///人行開戶許可證
#define TORA_TSTP_ICT_AccountsPermits 'J'
///其他證件
#define TORA_TSTP_ICT_OtherCard 'x'

typedef char TTORATstpIdCardTypeType;

/////////////////////////////////////////////////////////////////////////
/// TTORATstpAccountTypeType是一個資金賬戶型別型別
/////////////////////////////////////////////////////////////////////////
///普通
#define TORA_TSTP_FAT_Normal '1'
///信用
#define TORA_TSTP_FAT_Credit '2'
///衍生品
#define TORA_TSTP_FAT_Derivatives '3'

typedef char TTORATstpAccountTypeType;

/////////////////////////////////////////////////////////////////////////
/// TTORATstpDirectionType是一個報單類別型別
/////////////////////////////////////////////////////////////////////////
///買入
#define TORA_TSTP_D_Buy '0'
///賣出
#define TORA_TSTP_D_Sell '1'
///ETF申購
#define TORA_TSTP_D_ETFPur '2'
///ETF贖回
#define TORA_TSTP_D_ETFRed '3'
///新股申購
#define TORA_TSTP_D_IPO '4'
///正回購
#define TORA_TSTP_D_Repurchase '5'
///逆回購
#define TORA_TSTP_D_ReverseRepur '6'
///開放式基金申購
#define TORA_TSTP_D_OeFundPur '8'
///開放式基金贖回
#define TORA_TSTP_D_OeFundRed '9'
///擔保品劃入
#define TORA_TSTP_D_CollateralIn 'a'
///擔保品劃出
#define TORA_TSTP_D_CollateralOut 'b'
///質押入庫
#define TORA_TSTP_D_PledgeIn 'd'
///質押出庫
#define TORA_TSTP_D_PledgeOut 'e'
///配股配債
#define TORA_TSTP_D_Rationed 'f'
///開放式基金拆分
#define TORA_TSTP_D_Split 'g'
///開放式基金合併
#define TORA_TSTP_D_Merge 'h'
///融資買入
#define TORA_TSTP_D_MarginBuy 'i'
///融券賣出
#define TORA_TSTP_D_ShortSell 'j'
///賣券還款
#define TORA_TSTP_D_SellRepayment 'k'
///買券還券
#define TORA_TSTP_D_BuyRepayment 'l'
///還券劃轉
#define TORA_TSTP_D_SecurityRepay 'm'
///餘券劃轉
#define TORA_TSTP_D_RemainTransfer 'n'
///債轉股
#define TORA_TSTP_D_BondConvertStock 't'
///債券回售
#define TORA_TSTP_D_BondPutback 'u'

typedef char TTORATstpDirectionType;

/////////////////////////////////////////////////////////////////////////
/// TTORATstpBrokerageTypeType是一個佣金型別型別
/////////////////////////////////////////////////////////////////////////
///毛佣金
#define TORA_TSTP_BT_Gross '0'
///淨佣金
#define TORA_TSTP_BT_Net '1'

typedef char TTORATstpBrokerageTypeType;

/////////////////////////////////////////////////////////////////////////
/// TTORATstpUserTypeType是一個使用者型別型別
/////////////////////////////////////////////////////////////////////////
///經紀公司使用者
#define TORA_TSTP_UTYPE_BrokerUser '0'
///超級使用者
#define TORA_TSTP_UTYPE_SuperUser '1'
///投資者使用者
#define TORA_TSTP_UTYPE_Investor '2'

typedef char TTORATstpUserTypeType;

/////////////////////////////////////////////////////////////////////////
/// TTORATstpContingentConditionType是一個觸發條件型別
/////////////////////////////////////////////////////////////////////////
///成交觸發
#define TORA_TSTP_CC_TradeTouch '0'
///撤單觸發
#define TORA_TSTP_CC_CancelTouch '1'
///時間觸發
#define TORA_TSTP_CC_TimeTouch '2'
///交易時段觸發
#define TORA_TSTP_CC_SegmentTouch '3'
///最新價大於等於條件價
#define TORA_TSTP_CC_LastPriceGreaterThanStopPrice '4'
///最新價小於等於條件價
#define TORA_TSTP_CC_LastPriceLesserThanStopPrice '5'
///賣一價大於等於條件價
#define TORA_TSTP_CC_AskPriceGreaterEqualStopPrice '6'
///賣一價小於等於條件價
#define TORA_TSTP_CC_AskPriceLesserEqualStopPrice '7'
///買一價大於等於條件價
#define TORA_TSTP_CC_BidPriceGreaterEqualStopPrice '8'
///買一價小於等於條件價
#define TORA_TSTP_CC_BidPriceLesserEqualStopPrice '9'

typedef char TTORATstpContingentConditionType;

/////////////////////////////////////////////////////////////////////////
/// TTORATstpETFCurrenceReplaceStatusType是一個ETF現金替代標誌型別
/////////////////////////////////////////////////////////////////////////
///禁止現金替代
#define TORA_TSTP_ETFCTSTAT_Forbidden '0'
///可以現金替代
#define TORA_TSTP_ETFCTSTAT_Allow '1'
///必須現金替代
#define TORA_TSTP_ETFCTSTAT_Force '2'
///跨市退補現金替代
#define TORA_TSTP_ETFCTSTAT_CBAllow '3'
///跨市必須現金替代
#define TORA_TSTP_ETFCTSTAT_CBForce '4'

typedef char TTORATstpETFCurrenceReplaceStatusType;

/////////////////////////////////////////////////////////////////////////
/// TTORATstpOperateSourceType是一個操作來源型別
/////////////////////////////////////////////////////////////////////////
///實時上場
#define TORA_TSTP_OPRTSRC_DBCommand '0'
///API呼叫
#define TORA_TSTP_OPRTSRC_SyncAPI '1'

typedef char TTORATstpOperateSourceType;

/////////////////////////////////////////////////////////////////////////
/// TTORATstpOperwayType是一個委託方式型別
/////////////////////////////////////////////////////////////////////////
///電話委託
#define TORA_TSTP_OPERW_Telephone '0'
///櫃檯委託
#define TORA_TSTP_OPERW_OTC '1'
///移動客戶端委託
#define TORA_TSTP_OPERW_MobileClient '2'
///PC客戶端委託
#define TORA_TSTP_OPERW_PCClient '3'
///TY委託
#define TORA_TSTP_OPERW_TY '4'

typedef char TTORATstpOperwayType;

/////////////////////////////////////////////////////////////////////////
/// TTORATstpOperwaysType是一個委託方式合集型別
/////////////////////////////////////////////////////////////////////////
typedef char TTORATstpOperwaysType[41];

/////////////////////////////////////////////////////////////////////////
/// TTORATstpOrderPriceTypeType是一個報單價格條件型別
/////////////////////////////////////////////////////////////////////////
///任意價
#define TORA_TSTP_OPT_AnyPrice '1'
///限價
#define TORA_TSTP_OPT_LimitPrice '2'
///最優價
#define TORA_TSTP_OPT_BestPrice '3'
///最新價
#define TORA_TSTP_OPT_LastPrice '4'
///賣一價
#define TORA_TSTP_OPT_AskPrice1 '5'
///買一價
#define TORA_TSTP_OPT_BidPrice1 '6'
///相關價
#define TORA_TSTP_OPT_Relative '7'
///五檔價
#define TORA_TSTP_OPT_FiveLevelPrice 'G'
///本方最優
#define TORA_TSTP_OPT_HomeBestPrice 'a'

typedef char TTORATstpOrderPriceTypeType;

/////////////////////////////////////////////////////////////////////////
/// TTORATstpOrderVolumeTypeType是一個報單數量型別型別
/////////////////////////////////////////////////////////////////////////
///自定義數量
#define TORA_TSTP_OVT_CustomVol '1'
///相關數量
#define TORA_TSTP_OVT_RelativeVol '2'

typedef char TTORATstpOrderVolumeTypeType;

/////////////////////////////////////////////////////////////////////////
/// TTORATstpTimeConditionType是一個有效期型別型別
/////////////////////////////////////////////////////////////////////////
///立即完成，否則撤銷
#define TORA_TSTP_TC_IOC '1'
///本節有效
#define TORA_TSTP_TC_GFS '2'
///當日有效
#define TORA_TSTP_TC_GFD '3'
///指定日期前有效
#define TORA_TSTP_TC_GTD '4'
///撤銷前有效
#define TORA_TSTP_TC_GTC '5'
///集合競價有效
#define TORA_TSTP_TC_GFA '6'

typedef char TTORATstpTimeConditionType;

/////////////////////////////////////////////////////////////////////////
/// TTORATstpVolumeConditionType是一個成交量型別型別
/////////////////////////////////////////////////////////////////////////
///任何數量
#define TORA_TSTP_VC_AV '1'
///最小數量
#define TORA_TSTP_VC_MV '2'
///全部數量
#define TORA_TSTP_VC_CV '3'

typedef char TTORATstpVolumeConditionType;

/////////////////////////////////////////////////////////////////////////
/// TTORATstpForceCloseReasonType是一個強平原因型別
/////////////////////////////////////////////////////////////////////////
///非強平
#define TORA_TSTP_FCC_NotForceClose '0'
///資金不足
#define TORA_TSTP_FCC_LackDeposit '1'
///客戶超倉
#define TORA_TSTP_FCC_ClientOverPositionLimit '2'
///會員超倉
#define TORA_TSTP_FCC_MemberOverPositionLimit '3'
///持倉非整數倍
#define TORA_TSTP_FCC_NotMultiple '4'
///違規
#define TORA_TSTP_FCC_Violation '5'
///其它
#define TORA_TSTP_FCC_Other '6'

typedef char TTORATstpForceCloseReasonType;

/////////////////////////////////////////////////////////////////////////
/// TTORATstpFileOrderTypeType是一個檔案報單類別型別
/////////////////////////////////////////////////////////////////////////
///複核
#define TORA_TSTP_EOT_Review '0'
///撤單
#define TORA_TSTP_EOT_Cancel '1'
///限價單
#define TORA_TSTP_EOT_Limit '2'
///最優五檔即時成交剩餘撤銷
#define TORA_TSTP_EOT_FRC '3'
///最優五檔即時成交剩餘轉限價
#define TORA_TSTP_EOT_FRL '4'
///對手方最優
#define TORA_TSTP_EOT_BP '5'
///本方最優
#define TORA_TSTP_EOT_HP '6'
///立即成交剩餘撤銷
#define TORA_TSTP_EOT_FAK '7'
///全額成交或撤銷
#define TORA_TSTP_EOT_FOK '8'

typedef char TTORATstpFileOrderTypeType;

/////////////////////////////////////////////////////////////////////////
/// TTORATstpTransferDirectionType是一個轉移方向型別
/////////////////////////////////////////////////////////////////////////
///藍補
#define TORA_TSTP_TRNSD_In '0'
///紅衝
#define TORA_TSTP_TRNSD_Out '1'
///調入
#define TORA_TSTP_TRNSD_MoveIn '2'
///調出
#define TORA_TSTP_TRNSD_MoveOut '3'
///凍結
#define TORA_TSTP_TRNSD_Freeze '4'
///解凍
#define TORA_TSTP_TRNSD_UnFreeze '5'
///證券轉銀行
#define TORA_TSTP_TRNSD_StockToBank '6'
///銀行轉證券
#define TORA_TSTP_TRNSD_BankToStock '7'

typedef char TTORATstpTransferDirectionType;

/////////////////////////////////////////////////////////////////////////
/// TTORATstpCollateralDirectionType是一個擔保品劃入方向型別
/////////////////////////////////////////////////////////////////////////
///擔保品劃入
#define TORA_TSTP_CLTD_CollateralIn '6'
///擔保品劃出
#define TORA_TSTP_CLTD_CollateralOut '7'

typedef char TTORATstpCollateralDirectionType;

/////////////////////////////////////////////////////////////////////////
/// TTORATstpTransferStatusType是一個轉移狀態型別
/////////////////////////////////////////////////////////////////////////
///Transfer正在處理
#define TORA_TSTP_TRANST_TranferHandling '0'
///Transfer成功
#define TORA_TSTP_TRANST_TransferSuccess '1'
///Transfer失敗
#define TORA_TSTP_TRANST_TransferFail '2'
///Repeal正在處理
#define TORA_TSTP_TRANST_RepealHandling '3'
///Repeal成功
#define TORA_TSTP_TRANST_RepealSuccess '4'
///Repeal失敗
#define TORA_TSTP_TRANST_RepealFail '5'
///外部系統已接收
#define TORA_TSTP_TRANST_ExternalAccepted '6'

typedef char TTORATstpTransferStatusType;

/////////////////////////////////////////////////////////////////////////
/// TTORATstpTransferPositionTypeType是一個轉移持倉型別型別
/////////////////////////////////////////////////////////////////////////
///任意倉
#define TORA_TSTP_TPT_ALL '0'
///昨倉
#define TORA_TSTP_TPT_History '1'
///今買賣倉
#define TORA_TSTP_TPT_TodayBS '2'
///今申贖倉
#define TORA_TSTP_TPT_TodayPR '3'

typedef char TTORATstpTransferPositionTypeType;

/////////////////////////////////////////////////////////////////////////
/// TTORATstpSystemNameType是一個系統名稱型別
/////////////////////////////////////////////////////////////////////////
typedef char TTORATstpSystemNameType[41];

/////////////////////////////////////////////////////////////////////////
/// TTORATstpRelativeCondParamType是一個相關條件引數型別
/////////////////////////////////////////////////////////////////////////
typedef char TTORATstpRelativeCondParamType[31];

/////////////////////////////////////////////////////////////////////////
/// TTORATstpOrderStatusType是一個報單狀態型別
/////////////////////////////////////////////////////////////////////////
///全部成交
#define TORA_TSTP_OST_AllTraded '0'
///部分成交還在佇列中
#define TORA_TSTP_OST_PartTradedQueueing '1'
///部分成交不在佇列中
#define TORA_TSTP_OST_PartTradedNotQueueing '2'
///未成交還在佇列中
#define TORA_TSTP_OST_NoTradeQueueing '3'
///未成交不在佇列中
#define TORA_TSTP_OST_NoTradeNotQueueing '4'
///撤單
#define TORA_TSTP_OST_Canceled '5'
///未知
#define TORA_TSTP_OST_Unknown 'a'
///尚未觸發
#define TORA_TSTP_OST_NotTouched 'b'
///已觸發
#define TORA_TSTP_OST_Touched 'c'
///預埋
#define TORA_TSTP_OST_Cached 'd'

typedef char TTORATstpOrderStatusType;

/////////////////////////////////////////////////////////////////////////
/// TTORATstpCondOrderStatusType是一個條件單狀態型別
/////////////////////////////////////////////////////////////////////////
///初始
#define TORA_TSTP_COST_Initial '#'
///未觸發
#define TORA_TSTP_COST_NotTouched '0'
///已觸發
#define TORA_TSTP_COST_Touched '1'
///已結束
#define TORA_TSTP_COST_Finished '2'
///已撤銷
#define TORA_TSTP_COST_Cancel '3'
///觸發失敗
#define TORA_TSTP_COST_Failed '4'

typedef char TTORATstpCondOrderStatusType;

/////////////////////////////////////////////////////////////////////////
/// TTORATstpOrderSubmitStatusType是一個報單提交狀態型別
/////////////////////////////////////////////////////////////////////////
///未提交
#define TORA_TSTP_OSS_UnSubmit '#'
///已經提交
#define TORA_TSTP_OSS_InsertSubmitted '0'
///撤單已經提交
#define TORA_TSTP_OSS_CancelSubmitted '1'
///修改已經提交
#define TORA_TSTP_OSS_ModifySubmitted '2'
///已經接受
#define TORA_TSTP_OSS_Accepted '3'
///報單已經被拒絕
#define TORA_TSTP_OSS_InsertRejected '4'
///撤單已經被拒絕
#define TORA_TSTP_OSS_CancelRejected '5'
///改單已經被拒絕
#define TORA_TSTP_OSS_ModifyRejected '6'

typedef char TTORATstpOrderSubmitStatusType;

/////////////////////////////////////////////////////////////////////////
/// TTORATstpOrderTypeType是一個報單型別型別
/////////////////////////////////////////////////////////////////////////
///正常
#define TORA_TSTP_ORDT_Normal '0'
///報價衍生
#define TORA_TSTP_ORDT_DeriveFromQuote '1'
///組合衍生
#define TORA_TSTP_ORDT_DeriveFromCombination '2'
///組合報單
#define TORA_TSTP_ORDT_Combination '3'
///條件單
#define TORA_TSTP_ORDT_ConditionalOrder '4'
///互換單
#define TORA_TSTP_ORDT_Swap '5'

typedef char TTORATstpOrderTypeType;

/////////////////////////////////////////////////////////////////////////
/// TTORATstpOffsetFlagType是一個開平標誌型別
/////////////////////////////////////////////////////////////////////////
///開倉
#define TORA_TSTP_OF_Open '0'
///平倉
#define TORA_TSTP_OF_Close '1'
///強平
#define TORA_TSTP_OF_ForceClose '2'
///平今
#define TORA_TSTP_OF_CloseToday '3'
///平昨
#define TORA_TSTP_OF_CloseYesterday '4'
///強減
#define TORA_TSTP_OF_ForceOff '5'
///本地強平
#define TORA_TSTP_OF_LocalForceClose '6'

typedef char TTORATstpOffsetFlagType;

/////////////////////////////////////////////////////////////////////////
/// TTORATstpHedgeFlagType是一個投機套保標誌型別
/////////////////////////////////////////////////////////////////////////
///投機
#define TORA_TSTP_HF_Speculation '1'
///套利
#define TORA_TSTP_HF_Arbitrage '2'
///套保
#define TORA_TSTP_HF_Hedge '3'
///備兌
#define TORA_TSTP_HF_Covered '4'

typedef char TTORATstpHedgeFlagType;

/////////////////////////////////////////////////////////////////////////
/// TTORATstpActionFlagType是一個操作標誌型別
/////////////////////////////////////////////////////////////////////////
///刪除
#define TORA_TSTP_AF_Delete '0'
///修改
#define TORA_TSTP_AF_Modify '3'
///強制刪除
#define TORA_TSTP_AF_ForceDelete '4'

typedef char TTORATstpActionFlagType;

/////////////////////////////////////////////////////////////////////////
/// TTORATstpOrderActionStatusType是一個報單操作狀態型別
/////////////////////////////////////////////////////////////////////////
///已經提交
#define TORA_TSTP_OAS_Submitted 'a'
///已經接受
#define TORA_TSTP_OAS_Accepted 'b'
///已經被拒絕
#define TORA_TSTP_OAS_Rejected 'c'
///預埋未提交
#define TORA_TSTP_OAS_Cached 'e'

typedef char TTORATstpOrderActionStatusType;

/////////////////////////////////////////////////////////////////////////
/// TTORATstpClientIDTypeType是一個交易編碼型別型別
/////////////////////////////////////////////////////////////////////////
///未知
#define TORA_TSTP_CIDT_Unknown '0'
///投機
#define TORA_TSTP_CIDT_Speculation '1'
///套利
#define TORA_TSTP_CIDT_Arbitrage '2'
///套保
#define TORA_TSTP_CIDT_Hedge '3'
///普通
#define TORA_TSTP_CIDT_Normal 'a'
///信用
#define TORA_TSTP_CIDT_Credit 'b'
///衍生品
#define TORA_TSTP_CIDT_Derivatives 'c'

typedef char TTORATstpClientIDTypeType;

/////////////////////////////////////////////////////////////////////////
/// TTORATstpBizClassType是一個業務類別型別
/////////////////////////////////////////////////////////////////////////
///買入
#define TORA_TSTP_BC_Buy '0'
///賣出
#define TORA_TSTP_BC_Sell '1'
///ETF申購
#define TORA_TSTP_BC_ETFPur '2'
///ETF贖回
#define TORA_TSTP_BC_ETFRed '3'
///正回購
#define TORA_TSTP_BC_Repurchase '5'
///逆回購
#define TORA_TSTP_BC_ReverseRepur '6'
///配股配債
#define TORA_TSTP_BC_Rationed 'f'
///轉託管
#define TORA_TSTP_BC_CustodyTransfer 'q'
///買入開倉
#define TORA_TSTP_BC_BuyOpen 'A'
///買入平倉
#define TORA_TSTP_BC_BuyClose 'B'
///賣出開倉
#define TORA_TSTP_BC_SellOpen 'C'
///賣出平倉
#define TORA_TSTP_BC_SellClose 'D'
///備兌開倉
#define TORA_TSTP_BC_CoveredOpen 'E'
///備兌平倉
#define TORA_TSTP_BC_CoveredClose 'F'
///行權
#define TORA_TSTP_BC_ExecOrder 'G'
///自動行權
#define TORA_TSTP_BC_AutoExecOrder 'H'

typedef char TTORATstpBizClassType;

/////////////////////////////////////////////////////////////////////////
/// TTORATstpCreditPositionTypeType是一個頭寸型別型別
/////////////////////////////////////////////////////////////////////////
///普通
#define TORA_TSTP_CPT_Normal '0'
///專項
#define TORA_TSTP_CPT_Special '1'

typedef char TTORATstpCreditPositionTypeType;

/////////////////////////////////////////////////////////////////////////
/// TTORATstpFunctionIDType是一個功能程式碼型別
/////////////////////////////////////////////////////////////////////////
///空
#define TORA_TSTP_FID_NAN ' '
///會話管理：強制登出
#define TORA_TSTP_FID_SessionManager '0'
///使用者管理：強制使用者退出(禁用)、啟用、密碼操作
#define TORA_TSTP_FID_UserManager '1'
///報單插入
#define TORA_TSTP_FID_OrderInsert '2'
///報單操作
#define TORA_TSTP_FID_OrderAction '3'
///許可權調整
#define TORA_TSTP_FID_AdjustTradingRight '4'
///資金調撥
#define TORA_TSTP_FID_MoveFund '5'
///資金藍補
#define TORA_TSTP_FID_AddFund '6'
///資金紅衝
#define TORA_TSTP_FID_SubFund '7'
///強制凍結資金
#define TORA_TSTP_FID_ForceFreezeFund '8'
///強制解凍資金
#define TORA_TSTP_FID_ForceUnFreezeFund '9'
///倉位藍補
#define TORA_TSTP_FID_AddPosition 'a'
///倉位紅衝
#define TORA_TSTP_FID_SubPosition 'b'
///衝正資金
#define TORA_TSTP_FID_RepealFund 'c'
///衝正倉位
#define TORA_TSTP_FID_RepealPosition 'd'
///向外部系統劃撥擔保券
#define TORA_TSTP_FID_CollateralInJZ 'e'
///投資者費用調整
#define TORA_TSTP_FID_AdjustTradingFee 'f'
///調整特殊交易許可權
#define TORA_TSTP_FID_AdjustSpecPrivilege 'g'
///調整股東關聯關係
#define TORA_TSTP_FID_AdjustShareholderAssociation 'h'
///證券資訊調整
#define TORA_TSTP_FID_AdjustSecurity 'i'
///持倉調撥
#define TORA_TSTP_FID_MovePosition 'j'
///股東引數調整
#define TORA_TSTP_FID_AdjustShareholderParam 'k'
///條件報單插入
#define TORA_TSTP_FID_CondOrderInsert 'l'
///條件報單操作
#define TORA_TSTP_FID_CondOrderAction 'm'
///查詢條件單
#define TORA_TSTP_FID_QryCondOrder 'n'
///條件單引數維護
#define TORA_TSTP_FID_CondParamAdjust 'o'
///使用者角色管理
#define TORA_TSTP_FID_UserRoleManage 'p'
///費率模板管理
#define TORA_TSTP_FID_TradingFeeTemplateManage 'q'
///交易許可權模板管理
#define TORA_TSTP_FID_TradingRightTemplateManage 'r'
///股東賬戶證券程式碼系統許可權管理
#define TORA_TSTP_FID_SecurityPriorAuthManage 's'
///持倉交易屬性管理
#define TORA_TSTP_FID_PosiParamManage 't'
///報單編號字首調整
#define TORA_TSTP_FID_OrderLocalSeqPrefixAdjust 'u'
///席位管理
#define TORA_TSTP_FID_TraderManage 'v'
///新股申購引數額度管理
#define TORA_TSTP_FID_IPOManage 'w'
///內部元件執行配置
#define TORA_TSTP_FID_AppRunManage 'x'
///市場狀態管理
#define TORA_TSTP_FID_MarketStatusManage 'y'
///平臺狀態管理
#define TORA_TSTP_FID_PlatformStatusManage 'z'
///查詢資金
#define TORA_TSTP_FID_QryTradingAccount 'A'
///查詢持倉
#define TORA_TSTP_FID_QryPositon 'B'
///查詢股東賬戶
#define TORA_TSTP_FID_QryShareholderAccount 'C'
///查詢委託
#define TORA_TSTP_FID_QryOrder 'D'
///查詢成交
#define TORA_TSTP_FID_QryTrade 'E'
///查詢資金變動流水
#define TORA_TSTP_FID_QryFundSerial 'F'
///查詢持倉變動流水
#define TORA_TSTP_FID_QryPositionSerial 'G'
///Dump資金
#define TORA_TSTP_FID_DumpTradingAccount 'H'
///Dump持倉
#define TORA_TSTP_FID_DumpPositon 'I'
///Dump股東賬戶
#define TORA_TSTP_FID_DumpShareholderAccount 'J'
///Dump委託
#define TORA_TSTP_FID_DumpOrder 'K'
///Dump成交
#define TORA_TSTP_FID_DumpTrade 'L'
///Dump資金變動流水
#define TORA_TSTP_FID_DumpFundSerial 'M'
///Dump持倉變動流水
#define TORA_TSTP_FID_DumpPositionSerial 'N'
///回傳資料
#define TORA_TSTP_FID_UploadTradeData 'O'
///複核資金調整
#define TORA_TSTP_FID_ReviewFundAdjust 'P'
///複核倉位調整
#define TORA_TSTP_FID_ReviewPositionAdjust 'Q'
///記錄操作日誌
#define TORA_TSTP_FID_RecordOperateLog 'R'
///終端資訊管理
#define TORA_TSTP_FID_TerminalInfoManage 'S'
///查詢交易許可權
#define TORA_TSTP_FID_QryTradingRight 'T'
///指定交易登記&撤銷
#define TORA_TSTP_FID_DesignationRegistration 'U'
///深證轉託管&撤銷
#define TORA_TSTP_FID_CustodyTransfer 'V'
///強制刪除報單
#define TORA_TSTP_FID_ForceDelete 'W'
///風控管理
#define TORA_TSTP_FID_RiskMgr 'X'
///複核使用者登陸IP/MAC限制調整
#define TORA_TSTP_FID_ReviewUserIPLimitAdjust 'Y'
///使用者登入IP/MAC限制調整
#define TORA_TSTP_FID_AdjustUserIPLimit 'Z'
///調整系統引數
#define TORA_TSTP_FID_AdjustSystemParam '@'
///部門資訊管理
#define TORA_TSTP_FID_DepartmentInfoManage '#'
///新股配號中籤資訊管理
#define TORA_TSTP_FID_IPONumberMatchManage '$'
///客戶資訊管理
#define TORA_TSTP_FID_CustomerInfoManage '*'
///查詢使用者事件
#define TORA_TSTP_FID_QryTradeEvent '+'
///交易所回報序號維護
#define TORA_TSTP_FID_ExchRtnSeqManage '='
///銀證轉賬
#define TORA_TSTP_FID_TransferFund '-'

typedef char TTORATstpFunctionIDType;

/////////////////////////////////////////////////////////////////////////
/// TTORATstpSecurityTypeType是一個證券類別型別
/////////////////////////////////////////////////////////////////////////
///通用(內部使用)
#define TORA_TSTP_STP_COMMON '0'
///上海A股
#define TORA_TSTP_STP_SHAShares 'a'
///上海單市場股票ETF
#define TORA_TSTP_STP_SHSingleMarketStockETF 'b'
///上海單市場實物債券ETF
#define TORA_TSTP_STP_SHSingleMarketBondETF 'c'
///上海黃金ETF
#define TORA_TSTP_STP_SHGoldETF 'd'
///上海貨幣ETF
#define TORA_TSTP_STP_SHTradableMonetaryFund 'e'
///上海國債、地方債
#define TORA_TSTP_STP_SHBondNation 'f'
///上海企業債
#define TORA_TSTP_STP_SHBondCorporation 'g'
///上海公司債
#define TORA_TSTP_STP_SHBondCompany 'h'
///上海可轉債
#define TORA_TSTP_STP_SHBondConversion 'i'
///上海分離債
#define TORA_TSTP_STP_SHBondSeparation 'j'
///上海A股期權
#define TORA_TSTP_STP_SHASharesOption 'k'
///上海ETF期權
#define TORA_TSTP_STP_SHETFOption 'l'
///上海配股
#define TORA_TSTP_STP_SHAllotment 'm'
///上海配債
#define TORA_TSTP_STP_SHDistributeDebt 'n'
///上海標準券
#define TORA_TSTP_STP_SHStandard 'o'
///上海質押式回購
#define TORA_TSTP_STP_SHRepo 'p'
///上海封閉式基金
#define TORA_TSTP_STP_SHCEFund 'q'
///上海開放式基金
#define TORA_TSTP_STP_SHOEFund 'r'
///上海跨市場ETF
#define TORA_TSTP_STP_SHCrossMarketStockETF 's'
///上海跨境ETF
#define TORA_TSTP_STP_SHCrossBorderETF 't'
///上海分級母基金
#define TORA_TSTP_STP_SHMontherStructFund 'u'
///上海分級子基金
#define TORA_TSTP_STP_SHSubStructFund 'v'
///上海實時申贖貨幣基金
#define TORA_TSTP_STP_SHRealTimeMonetaryFund 'w'
///上海可交換債
#define TORA_TSTP_STP_SHExchangeableBond 'x'
///上海標準LOF基金
#define TORA_TSTP_STP_SHLOF 'A'
///深圳主機板A股
#define TORA_TSTP_STP_SZMainAShares 'B'
///深圳中小企業板
#define TORA_TSTP_STP_SZSME 'C'
///深圳國債、地方債
#define TORA_TSTP_STP_SZBondNation 'D'
///深圳企業債
#define TORA_TSTP_STP_SZBondCorporation 'E'
///深圳公司債
#define TORA_TSTP_STP_SZBondCompany 'F'
///深圳可轉債
#define TORA_TSTP_STP_SZBondConversion 'G'
///深圳分離債
#define TORA_TSTP_STP_SZBondSeparation 'H'
///深圳A股期權
#define TORA_TSTP_STP_SZASharesOption 'I'
///深圳ETF期權
#define TORA_TSTP_STP_SZETFOption 'J'
///深圳跨境ETF
#define TORA_TSTP_STP_SZCrossBorderETF 'K'
///深圳黃金ETF
#define TORA_TSTP_STP_SZGoldETF 'L'
///深圳現金債券ETF
#define TORA_TSTP_STP_SZCashBondETF 'M'
///深圳單市場股票ETF
#define TORA_TSTP_STP_SZSingleMarketStockETF 'N'
///深圳單市場實物債券ETF
#define TORA_TSTP_STP_SZSingleMarketBondETF 'O'
///深圳貨幣ETF
#define TORA_TSTP_STP_SZMonetaryFundETF 'P'
///深圳創業板
#define TORA_TSTP_STP_SZGEM 'Q'
///深圳配股
#define TORA_TSTP_STP_SZAllotment 'R'
///深圳配債
#define TORA_TSTP_STP_SZDistributeDebt 'S'
///深圳標準券
#define TORA_TSTP_STP_SZStandard 'T'
///深圳質押式回購
#define TORA_TSTP_STP_SZRepo 'U'
///深圳封閉式基金
#define TORA_TSTP_STP_SZCEFund 'V'
///深圳開放式基金
#define TORA_TSTP_STP_SZOEFund 'W'
///深圳跨境開放式基金
#define TORA_TSTP_STP_SZCrossBorderOEFund 'X'
///深圳跨市場市場股票ETF
#define TORA_TSTP_STP_SZCrossMarketStockETF 'Y'
///深圳標準LOF基金
#define TORA_TSTP_STP_SZLOF 'Z'
///深圳跨境LOF基金
#define TORA_TSTP_STP_SZCrossBorderLOF '1'
///深圳傳統分級母基金
#define TORA_TSTP_STP_SZMontherStructFund '2'
///深圳傳統分級子基金
#define TORA_TSTP_STP_SZSubStructFund '3'
///深圳跨境分級母基金
#define TORA_TSTP_STP_SZMontherCrossBorderStructFund '4'
///深圳跨境分級子基金
#define TORA_TSTP_STP_SZSubCrossBorderStructFund '5'
///深圳可交換債
#define TORA_TSTP_STP_SZExchangeableBond '6'
///深圳創業板可轉債
#define TORA_TSTP_STP_SZGEMConversionBond '7'

typedef char TTORATstpSecurityTypeType;

/////////////////////////////////////////////////////////////////////////
/// TTORATstpEndFlagType是一個結束標誌型別
/////////////////////////////////////////////////////////////////////////
///待續
#define TORA_TSTP_EF_ToBeContinued '1'
///批結束
#define TORA_TSTP_EF_BatchEnd '2'
///全部完成
#define TORA_TSTP_EF_Completed '3'
///無資料
#define TORA_TSTP_EF_NOP '4'

typedef char TTORATstpEndFlagType;

/////////////////////////////////////////////////////////////////////////
/// TTORATstpMarketIDType是一個市場程式碼型別
/////////////////////////////////////////////////////////////////////////
///通用(內部使用)
#define TORA_TSTP_MKD_COMMON '0'
///上海A股
#define TORA_TSTP_MKD_SHA '1'
///深圳A股
#define TORA_TSTP_MKD_SZA '2'
///上海B股
#define TORA_TSTP_MKD_SHB '3'
///深圳B股
#define TORA_TSTP_MKD_SZB '4'
///深圳三版A股
#define TORA_TSTP_MKD_SZThreeA '5'
///深圳三版B股
#define TORA_TSTP_MKD_SZThreeB '6'
///境外市場
#define TORA_TSTP_MKD_Foreign '7'

typedef char TTORATstpMarketIDType;

/////////////////////////////////////////////////////////////////////////
/// TTORATstpLogInAccountType是一個登入賬戶型別
/////////////////////////////////////////////////////////////////////////
typedef char TTORATstpLogInAccountType[21];

/////////////////////////////////////////////////////////////////////////
/// TTORATstpLogInAccountTypeType是一個登入賬戶型別型別
/////////////////////////////////////////////////////////////////////////
///使用者程式碼
#define TORA_TSTP_LACT_UserID '0'
///資金賬號
#define TORA_TSTP_LACT_AccountID '1'
///上海A股
#define TORA_TSTP_LACT_SHAStock '2'
///深圳A股
#define TORA_TSTP_LACT_SZAStock '3'
///上海B股
#define TORA_TSTP_LACT_SHBStock '4'
///深圳B股
#define TORA_TSTP_LACT_SZBStock '5'
///三板A
#define TORA_TSTP_LACT_ThreeNewBoardA '6'
///三板B
#define TORA_TSTP_LACT_ThreeNewBoardB '7'
///港股
#define TORA_TSTP_LACT_HKStock '8'

typedef char TTORATstpLogInAccountTypeType;

/////////////////////////////////////////////////////////////////////////
/// TTORATstpMarketStatusType是一個市場狀態型別
/////////////////////////////////////////////////////////////////////////
///未知
#define TORA_TSTP_MST_UnKnown '#'
///開盤前
#define TORA_TSTP_MST_BeforeTrading '0'
///連續交易
#define TORA_TSTP_MST_Continous '1'
///收盤
#define TORA_TSTP_MST_Closed '2'
///開盤集合競價
#define TORA_TSTP_MST_OpenCallAuction '3'

typedef char TTORATstpMarketStatusType;

/////////////////////////////////////////////////////////////////////////
/// TTORATstpBigsInfoType是一個長字串附加資訊型別
/////////////////////////////////////////////////////////////////////////
typedef char TTORATstpBigsInfoType[33];

/////////////////////////////////////////////////////////////////////////
/// TTORATstpShortsInfoType是一個短字串附加資訊型別
/////////////////////////////////////////////////////////////////////////
typedef char TTORATstpShortsInfoType[9];

/////////////////////////////////////////////////////////////////////////
/// TTORATstpIntInfoType是一個整形附加資訊型別
/////////////////////////////////////////////////////////////////////////
typedef int TTORATstpIntInfoType;

/////////////////////////////////////////////////////////////////////////
/// TTORATstpFloatInfoType是一個浮點型附加資訊型別
/////////////////////////////////////////////////////////////////////////
typedef double TTORATstpFloatInfoType;

/////////////////////////////////////////////////////////////////////////
/// TTORATstpApiGroupIDType是一個Api工作組號型別
/////////////////////////////////////////////////////////////////////////
typedef int TTORATstpApiGroupIDType;

/////////////////////////////////////////////////////////////////////////
/// TTORATstpApiRunModeType是一個Api執行模式型別
/////////////////////////////////////////////////////////////////////////
///單一
#define TORA_TSTP_ARM_Single '0'
///叢集
#define TORA_TSTP_ARM_Group '1'

typedef char TTORATstpApiRunModeType;

/////////////////////////////////////////////////////////////////////////
/// TTORATstpDesignationTypeType是一個指定交易操作型別型別
/////////////////////////////////////////////////////////////////////////
///指定交易登記
#define TORA_TSTP_DT_Register '0'
///指定交易撤銷登記
#define TORA_TSTP_DT_Cancel '1'

typedef char TTORATstpDesignationTypeType;

/////////////////////////////////////////////////////////////////////////
/// TTORATstpCustodyTransferTypeType是一個深證轉託管型別型別
/////////////////////////////////////////////////////////////////////////
///深證轉託管註冊
#define TORA_TSTP_CT_Register '0'
///深證轉託管撤單
#define TORA_TSTP_CT_Cancel '1'

typedef char TTORATstpCustodyTransferTypeType;

/////////////////////////////////////////////////////////////////////////
/// TTORATstpProperCtrlBusinessTypeType是一個適當性控制業務類別型別
/////////////////////////////////////////////////////////////////////////
///空值
#define TORA_TSTP_PCBT_None ' '
///其它
#define TORA_TSTP_PCBT_Other '0'
///上海退市整理
#define TORA_TSTP_PCBT_SHDelisting '1'
///風險警示
#define TORA_TSTP_PCBT_ST '2'
///創業板
#define TORA_TSTP_PCBT_GEM '3'
///分級基金
#define TORA_TSTP_PCBT_StructFund '4'
///債券
#define TORA_TSTP_PCBT_BondQualified '5'
///暫停上市債
#define TORA_TSTP_PCBT_SuspendBond '6'
///正回購
#define TORA_TSTP_PCBT_Repurchase '7'
///逆回購
#define TORA_TSTP_PCBT_ReverseRepur '8'
///深圳退市整理
#define TORA_TSTP_PCBT_SZDelisting '9'
///常規股票
#define TORA_TSTP_PCBT_Stock 'a'
///常規股票信用
#define TORA_TSTP_PCBT_CreditStock 'b'

typedef char TTORATstpProperCtrlBusinessTypeType;

/////////////////////////////////////////////////////////////////////////
/// TTORATstpProperCtrlPassFlagType是一個適當性控制通過標示型別
/////////////////////////////////////////////////////////////////////////
///空值
#define TORA_TSTP_PCPF_None ' '
///無條件通過
#define TORA_TSTP_PCPF_AnywayPass '0'
///匹配通過
#define TORA_TSTP_PCPF_MatchPass '1'
///有條件通過
#define TORA_TSTP_PCPF_SelectPass '2'
///專投豁免過
#define TORA_TSTP_PCPF_ProfInvestorPass '3'

typedef char TTORATstpProperCtrlPassFlagType;

/////////////////////////////////////////////////////////////////////////
/// TTORATstpCRiskLevelType是一個客戶風險等級型別
/////////////////////////////////////////////////////////////////////////
///最低級別風險
#define TORA_TSTP_RLV_Lowest '0'
///保守型
#define TORA_TSTP_RLV_Conservative '1'
///謹慎型
#define TORA_TSTP_RLV_Cautious '2'
///穩健型
#define TORA_TSTP_RLV_Steady '3'
///積極型
#define TORA_TSTP_RLV_Positive '4'
///激進型
#define TORA_TSTP_RLV_Aggressive '5'

typedef char TTORATstpCRiskLevelType;

/////////////////////////////////////////////////////////////////////////
/// TTORATstpProfInvestorTypeType是一個專業投資者類別型別
/////////////////////////////////////////////////////////////////////////
///非專業投資者
#define TORA_TSTP_PIT_NotProf '0'
///當然機構專業投資者
#define TORA_TSTP_PIT_OCInstiPro '1'
///法人或機構專業投資者
#define TORA_TSTP_PIT_InstiPro '2'
///自然人專業投資者
#define TORA_TSTP_PIT_PersonPro '3'
///認定法人或機構專業投資者
#define TORA_TSTP_PIT_ConfirmInstiPro '4'
///認定自然人專業投資者
#define TORA_TSTP_PIT_ConfirmPersonPro '5'

typedef char TTORATstpProfInvestorTypeType;

/////////////////////////////////////////////////////////////////////////
/// TTORATstpLOrderTypeType是一個訂單類別型別
/////////////////////////////////////////////////////////////////////////
///市價
#define TORA_TSTP_LOT_Market '1'
///限價
#define TORA_TSTP_LOT_Limit '2'
///本方最優
#define TORA_TSTP_LOT_HomeBest '3'

typedef char TTORATstpLOrderTypeType;

/////////////////////////////////////////////////////////////////////////
/// TTORATstpLSideType是一個委託方向型別
/////////////////////////////////////////////////////////////////////////
///買
#define TORA_TSTP_LSD_Buy '1'
///賣
#define TORA_TSTP_LSD_Sell '2'
///借入
#define TORA_TSTP_LSD_Borrow '3'
///借出
#define TORA_TSTP_LSD_Lend '4'

typedef char TTORATstpLSideType;

/////////////////////////////////////////////////////////////////////////
/// TTORATstpExecTypeType是一個成交類別型別
/////////////////////////////////////////////////////////////////////////
///成交
#define TORA_TSTP_ECT_Fill '1'
///撤銷
#define TORA_TSTP_ECT_Cancel '2'

typedef char TTORATstpExecTypeType;

/////////////////////////////////////////////////////////////////////////
/// TTORATstpCondCheckType是一個委託條件檢查型別
/////////////////////////////////////////////////////////////////////////
///不做任何檢查
#define TORA_TSTP_CCT_None '0'
///自成交檢查
#define TORA_TSTP_CCT_SelfDeal '1'

typedef char TTORATstpCondCheckType;

/////////////////////////////////////////////////////////////////////////
/// TTORATstpHDSerialType是一個硬碟序列號型別
/////////////////////////////////////////////////////////////////////////
typedef char TTORATstpHDSerialType[33];

/////////////////////////////////////////////////////////////////////////
/// TTORATstpMDSubModeType是一個行情訂閱模式型別
/////////////////////////////////////////////////////////////////////////
///TCP連線模式
#define TORA_TSTP_MST_TCP '0'
///UDP單播模式
#define TORA_TSTP_MST_UDP '1'
///UDP組播模式
#define TORA_TSTP_MST_MCAST '2'

typedef char TTORATstpMDSubModeType;

/////////////////////////////////////////////////////////////////////////
/// TTORATstpMDSecurityStatType是一個行情證券狀態型別
/////////////////////////////////////////////////////////////////////////
///開盤前
#define TORA_TSTP_MSST_PreOpen '0'
///集合競價
#define TORA_TSTP_MSST_CallAuction '1'
///連續交易
#define TORA_TSTP_MSST_Continous '2'
///休市
#define TORA_TSTP_MSST_Pause '3'
///停牌
#define TORA_TSTP_MSST_Suspend '4'
///長期停牌
#define TORA_TSTP_MSST_LongSuspend '5'
///波動性中斷
#define TORA_TSTP_MSST_UndulationInt '6'
///熔斷可恢復
#define TORA_TSTP_MSST_CircuitBreak '7'
///熔斷不可恢復
#define TORA_TSTP_MSST_CircuitBreakU '8'
///閉市
#define TORA_TSTP_MSST_Close '9'
///其它
#define TORA_TSTP_MSST_Other 'a'
///收盤集合競價
#define TORA_TSTP_MSST_CloseCallAuction 'b'

typedef char TTORATstpMDSecurityStatType;

/////////////////////////////////////////////////////////////////////////
/// TTORATstpCommitStatusType是一個檔案委託提交狀態型別
/////////////////////////////////////////////////////////////////////////
///初始
#define TORA_TSTP_FOCS_Init '0'
///已複核
#define TORA_TSTP_FOCS_Reviewed '1'
///處理失敗
#define TORA_TSTP_FOCS_Failed '2'

typedef char TTORATstpCommitStatusType;

/////////////////////////////////////////////////////////////////////////
/// TTORATstpParamTypeType是一個股東引數型別型別
/////////////////////////////////////////////////////////////////////////
///最大買量限制
#define TORA_TSTP_SPT_MaxBuyLimit '0'
///最大賣量限制
#define TORA_TSTP_SPT_MaxSellLimit '1'
///買入大額申報限制比例
#define TORA_TSTP_SPT_LargeBuyLimitRatio '2'
///賣出大額申報限制比例
#define TORA_TSTP_SPT_LargeSelLimitRatio '3'
///風險警示買入上限
#define TORA_TSTP_SPT_RiskWarnBoardLimitVol '4'
///連續申報時間間隔
#define TORA_TSTP_SPT_SeriesDecInterval '5'
///連續申報單位時間委託筆數
#define TORA_TSTP_SPT_SeriesLimitPerUnit '6'
///影響收盤價波動比例
#define TORA_TSTP_SPT_ClosePriceScopeRatio '7'
///炒新控制最大上市時間
#define TORA_TSTP_SPT_OpenDateLimit '8'
///漲跌停板虛假申報佔未成交比例
#define TORA_TSTP_SPT_LimitBoardShamRatio '9'
///撤單限制比例
#define TORA_TSTP_SPT_CancelOrderRatio 'a'

typedef char TTORATstpParamTypeType;

/////////////////////////////////////////////////////////////////////////
/// TTORATstpContentType是一個訊息正文型別
/////////////////////////////////////////////////////////////////////////
typedef char TTORATstpContentType[501];

/////////////////////////////////////////////////////////////////////////
/// TTORATstpStatusMsgType是一個狀態資訊型別
/////////////////////////////////////////////////////////////////////////
typedef char TTORATstpStatusMsgType[93];

/////////////////////////////////////////////////////////////////////////
/// TTORATstpIPONumberIDType是一個新股申購配股號型別
/////////////////////////////////////////////////////////////////////////
typedef char TTORATstpIPONumberIDType[31];

/////////////////////////////////////////////////////////////////////////
/// TTORATstpPageLocateType是一個頁定位符型別
/////////////////////////////////////////////////////////////////////////
typedef int TTORATstpPageLocateType;
#endif