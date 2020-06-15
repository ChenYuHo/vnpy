/////////////////////////////////////////////////////////////////////////
///@author 中泰證券股份有限公司
///@file xtp_api_struct_common.h
///@brief 定義業務公共資料結構
/////////////////////////////////////////////////////////////////////////

#ifndef _XTP_API_STRUCT_COMMON_H_
#define _XTP_API_STRUCT_COMMON_H_

#if defined(_MSC_VER) && _MSC_VER<1600
typedef signed char        int8_t;
typedef short              int16_t;
typedef int                int32_t;
typedef long long          int64_t;
typedef unsigned char      uint8_t;
typedef unsigned short     uint16_t;
typedef unsigned int       uint32_t;
typedef unsigned long long uint64_t;
#else
#include <stdint.h>
#endif

#include "xtp_api_data_type.h"

#pragma pack(8)

///錯誤資訊的字串長度
#define XTP_ERR_MSG_LEN  124
///響應資訊
typedef struct XTPRspInfoStruct
{
	///錯誤程式碼
	int32_t	error_id;
	///錯誤資訊
	char	error_msg[XTP_ERR_MSG_LEN];
} XTPRI;

#pragma pack()

#endif // !_XTP_API_STRUCT_COMMON_H_
