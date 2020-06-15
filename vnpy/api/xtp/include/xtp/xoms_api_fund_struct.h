/////////////////////////////////////////////////////////////////////////
///@author 中泰證券股份有限公司
///@file xoms_api_fund_struct.h
///@brief 定義資金劃撥相關結構體型別
/////////////////////////////////////////////////////////////////////////
#ifndef XOMS_API_FUND_STRUCT_H_
#define XOMS_API_FUND_STRUCT_H_

#include "xtp_api_data_type.h"
#include "xoms_api_struct.h"
#include "xtp_api_struct_common.h"

#pragma pack(8)

/// 使用者資金賬戶的密碼字串長度
#define XTP_ACCOUNT_PASSWORD_LEN 64

/////////////////////////////////////////////////////////////////////////
///使用者資金請求
/////////////////////////////////////////////////////////////////////////
struct XTPFundTransferReq
{
    ///資金內轉編號，無需使用者填寫，類似於xtp_id
    uint64_t	serial_id;
	///資金賬戶程式碼
	char        fund_account[XTP_ACCOUNT_NAME_LEN];
	///資金賬戶密碼
	char	    password[XTP_ACCOUNT_PASSWORD_LEN];
	///金額
	double	    amount;
	///內轉型別
	XTP_FUND_TRANSFER_TYPE	transfer_type;

};

/////////////////////////////////////////////////////////////////////////
///使用者資金劃轉請求的響應-複用資金通知結構體
/////////////////////////////////////////////////////////////////////////
typedef struct XTPFundTransferNotice XTPFundTransferAck ;

#pragma pack()

#endif