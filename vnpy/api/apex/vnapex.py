from pathlib import Path

from ctypes import (cdll, CFUNCTYPE,
                    c_bool, c_char_p, c_long, c_int,
                    c_void_p, create_string_buffer, byref)


DLL_PATH = Path(__file__).parent.joinpath("FixApi.dll")
APEX = cdll.LoadLibrary(str(DLL_PATH))

REPLY_FUNC = CFUNCTYPE(c_bool, c_long, c_long, c_int)
PUSH_FUNC = CFUNCTYPE(c_bool, c_long, c_long, c_long, c_char_p)
CONN_FUNC = CFUNCTYPE(c_bool, c_long, c_long, c_void_p)


class ApexApi:
    """
    Wrapper for APEX C API.
    """

    def __init__(self):
        """Constructor"""
        self.reply_call_func = REPLY_FUNC(self.on_reply)
        self.push_call_func = PUSH_FUNC(self.on_push)
        self.conn_call_func = CONN_FUNC(self.on_conn)

    def initialize(self):
        """初始化"""
        n = APEX.Fix_Initialize()
        return bool(n)

    def set_app_info(self, name: str, version: str):
        """設定應用資訊"""
        n = APEX.Fix_SetAppInfo(to_bytes(name), to_bytes(version))
        return bool(n)

    def uninitialize(self):
        """解除安裝庫"""
        n = APEX.Fix_Uninitialize()
        return bool(n)

    def set_default_info(self, user: str, wtfs: str, fbdm: str, dest: str):
        """設定預設資訊"""
        n = APEX.Fix_SetDefaultInfo(
            to_bytes(user),
            to_bytes(wtfs),
            to_bytes(fbdm),
            to_bytes(dest)
        )
        return bool(n)

    def connect(self, address: str, khh: str, pwd: str, timeout: int):
        """連線交易"""
        conn = APEX.Fix_Connect(
            to_bytes(address),
            to_bytes(khh),
            to_bytes(pwd),
            timeout
        )
        return conn

    def connect_ex(
        self, address: str, khh: str, pwd: str, file_cert: str,
        cert_pwd: str, file_ca: str, procotol: str, verify: bool,
        timeout: int
    ):
        """連線交易"""
        conn = APEX.Fix_ConnectEx(
            to_bytes(address),
            to_bytes(khh),
            to_bytes(pwd),
            to_bytes(file_cert),
            to_bytes(cert_pwd),
            to_bytes(file_ca),
            to_bytes(procotol),
            verify,
            timeout
        )
        return conn

    def close(self, conn: int):
        """斷開"""
        n = APEX.Fix_Close(conn)
        return bool(n)

    def allocate_session(self, conn: int):
        """分配會話"""
        sess = APEX.Fix_AllocateSession(conn)
        return sess

    def release_session(self, sess: int):
        """釋放會話"""
        n = APEX.Fix_ReleaseSession(sess)
        return bool(n)

    def set_timeout(self, sess: int, timeout: int):
        """設定會話超時時間"""
        n = APEX.Fix_SetTimeOut(sess, c_long(timeout))
        return bool(n)

    def set_wtfs(self, sess: int, wtfs: str):
        """設定委託方式"""
        n = APEX.Fix_SetWTFS(sess, to_bytes(wtfs))
        return bool(n)

    def set_fbdm(self, sess: int, fbdm: str):
        """設定來源營業部"""
        n = APEX.Fix_SetFBDM(sess, to_bytes(fbdm))
        return bool(n)

    def set_dest_fbdm(self, sess: int, fbdm: str):
        """設定目標營業部"""
        n = APEX.Fix_SetDestFBDM(sess, to_bytes(fbdm))
        return bool(n)

    def set_node(self, sess: int, node: str):
        """設定業務站點"""
        n = APEX.Fix_SetNode(sess, to_bytes(node))
        return bool(n)

    def set_gydm(self, sess: int, gydm: str):
        """設定櫃員號"""
        n = APEX.Fix_SetGYDM(sess, to_bytes(gydm))
        return bool(n)

    def create_head(self, sess: int, func: int):
        """設定會話功能號"""
        n = APEX.Fix_CreateHead(sess, func)
        return bool(n)

    def set_string(self, sess: int, val: str):
        """設定字串請求資料"""
        n = APEX.Fix_SetString(sess, val)
        return bool(n)

    def set_long(self, sess: int, val: int):
        """設定整形請求資料"""
        n = APEX.Fix_SetLong(sess, val)
        return bool(n)

    def set_double(self, sess: int, val: float):
        """設定浮點數請求資料"""
        n = APEX.Fix_SetDouble(sess, val)
        return bool(n)

    def run(self, sess: int):
        """執行"""
        n = APEX.Fix_Run(sess)
        return bool(n)

    def async_run(self, sess: int):
        """非同步執行"""
        n = APEX.Fix_AsyncRun(sess)
        return bool(n)

    def is_replyed(self, sess: int, msec: int):
        """是否收到應答"""
        n = APEX.Fix_IsReplyed(sess, msec)
        return bool(n)

    def cancel(self, sess: int):
        """取消應答等待"""
        n = APEX.Fix_Cancel(sess, sess)
        return bool(n)

    def get_code(self, sess: int):
        """獲取錯誤程式碼"""
        return APEX.Fix_GetCode(sess)

    def get_err_msg(self, sess: int):
        """獲取錯誤資訊"""
        size = 256
        out = create_string_buffer(b"", size)

        APEX.Fix_GetErrMsg(sess, out, size)
        return out.value

    def get_count(self, sess: int):
        """獲取行數"""
        return APEX.Fix_GetCount(sess)

    def get_item(self, sess: int, fid: int, row: int):
        """獲取字串內容"""
        size = 256
        out = create_string_buffer(b"", size)

        APEX.Fix_GetItem(sess, fid, out, size, row)
        return out.value

    def get_long(self, sess: int, fid: int, row: int):
        """獲取整形內容"""
        val = APEX.Fix_GetLong(sess, fid, row)
        return val

    def get_double(self, sess: int, fid: int, row: int):
        """獲取浮點型內容"""
        val = APEX.Fix_GetDouble(sess, fid, row)
        return val

    def get_have_item(self, sess: int, fid: int, row: int):
        """檢視指定應答資料"""
        n = APEX.Fix_HaveItem(sess, fid, row)
        return bool(n)

    def set_token(self, sess: int, token: str):
        """設定業務令牌"""
        n = APEX.Fix_SetToken(sess, token)
        return bool(n)

    def get_token(self, sess: int):
        """獲取業務令牌"""
        size = 256
        out = create_string_buffer(b"", size)

        APEX.Fix_GetToken(sess, out, size)
        return out.value

    def encode(self, data: str):
        """加密"""
        data = to_bytes(data)
        buf = create_string_buffer(data, 512)
        APEX.Fix_Encode(buf)
        return to_unicode(buf.value)

    def add_backup_svc_addr(self, address: str):
        """設定業務令牌"""
        address = to_bytes(address)
        n = APEX.Fix_AddBackupSvrAddr(address)
        return bool(n)

    def set_conn_event(self, conn: int):
        """設定連線狀態回撥函式"""
        n = APEX.Fix_SetConnEvent(conn, self.conn_call_func)
        return bool(n)

    def is_connect(self, conn: int):
        """檢查連線狀態"""
        n = APEX.Fix_IsConnect(conn)
        return bool(n)

    def subscribe_by_customer(self, conn: int, svc: int, khh: str, pwd: str):
        """訂閱資料"""
        func = APEX[108]
        n = func(conn, svc, self.push_call_func,
                 to_bytes(""), to_bytes(khh), to_bytes(pwd))

        return n

    def unsubscribe_by_handle(self, handle: int):
        """退訂推送"""
        n = APEX.Fix_UnSubscibeByHandle(handle)
        return bool(n)

    def get_column_count(self, sess: int, row: int):
        """獲取列數"""
        return APEX.Fix_GetColumnCount(sess, row)

    def get_val_with_id_by_index(self, sess: int, row: int, col: int):
        """根據行列獲取資料"""
        s = 256
        buf = create_string_buffer(b"", s)
        fid = c_long(0)
        size = c_int(s)

        APEX.Fix_GetValWithIdByIndex(
            sess, row, col, byref(fid), buf, byref(size))
        return fid.value, to_unicode(buf.value)

    def set_system_no(self, sess: int, val: str):
        """設定系統編號"""
        n = APEX.Fix_SetSystemNo(sess, to_bytes(val))
        return bool(n)

    def set_default_system_no(self, val: str):
        """設定預設系統編號"""
        n = APEX.Fix_SetDefaultSystemNo(to_bytes(val))
        return bool(n)

    def set_auto_reconnect(self, conn: int, reconnect: int):
        """設定自動連線"""
        n = APEX.Fix_SetAutoReconnect(conn, reconnect)
        return bool(n)

    def get_auto_reconnect(self, conn: int):
        """獲取自動連線狀態"""
        n = APEX.Fix_GetAutoReconnect(conn)
        return bool(n)

    def create_req(self, sess: int, func: int):
        """建立任務"""
        n = APEX.Fix_CreateReq(sess, func)
        return bool(n)

    def get_item_buf(self, sess, row):
        """獲取快取資料"""
        size = 1024
        outlen = c_int(size)
        buf = create_string_buffer(b"", size)

        APEX.Fix_GetItemBuf(sess, buf, byref(outlen), row)
        return buf

    def set_item(self, sess: int, fid: int, val: str):
        """設定請求內容"""
        n = APEX.Fix_SetString(sess, fid, to_bytes(val))
        return bool(n)

    def get_last_err_msg(self):
        """獲取錯誤資訊"""
        size = 256
        out = create_string_buffer(b"", size)

        APEX.Fix_GetLastErrMsg(out, size)
        return to_unicode(out.value)

    def reg_reply_call_func(self, sess: int = 0):
        """註冊回撥函式"""
        if not sess:
            n = APEX.Fix_RegReplyCallFunc(c_void_p(None), self.reply_call_func)
        else:
            n = APEX.Fix_RegReplyCallFunc(sess, self.reply_call_func)
        return bool(n)

    def on_reply(self, conn: int, sess: int, recv: int):
        """非同步回撥函式（需要繼承）"""
        return True

    def on_push(self, conn: int, sess: int, sub: int, data: str):
        """推送回調（需要繼承）"""
        return True

    def on_conn(self, conn: int, event, recv):
        """連接回調（需要繼承）"""
        return True


def to_bytes(data: str):
    """
    將unicode字串轉換為bytes
    """
    try:
        bytes_data = data.encode("GBK")
        return bytes_data
    except AttributeError:
        return data


def to_unicode(data: bytes):
    """
    將bytes字串轉換為unicode
    """
    return data.decode("GBK")
