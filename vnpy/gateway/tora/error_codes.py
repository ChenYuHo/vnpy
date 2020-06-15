error_codes = {
    0: "沒有錯誤",
    -1: "TCP連線沒建立",
    -2: "互動通道無效",
    -3: "使用者未登入",
    -4: "非本前置會話不能訂閱私有流",
    -5: "重複的私有流訂閱請求",
    -6: "開啟私有流檔案失敗",
    -7: "內部通訊錯誤",
    -8: "建立會話通道失敗",
    -9: "超出流控限制",
}


def get_error_msg(error_code: int):
    try:
        return error_codes[error_code]
    except KeyError:
        return "未知錯誤"
