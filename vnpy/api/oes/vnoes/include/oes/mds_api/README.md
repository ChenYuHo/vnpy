# Swordfish-MDS API    {#mainpage}

箭魚行情資料服務系統API使用說明


---
### Quick Start

#### 1.1 示例程式碼

- 參見 mds_api/samples 目錄下的樣例檔案
	- 配置檔案樣例 <mds_client_sample.conf>
	- 行情接收與列印的程式碼樣例 <mds_client_sample.c>
	- 行情訂閱與接收的程式碼樣例 <mds_subscribe_sample.c>
	- 用於樣例程式碼編譯的 <Makefile.sample>

mds_subscribe_sample.c 摘錄如下：
~~~{.c}

/**
 * 通過證券程式碼列表, 重新訂閱行情資料 (根據程式碼字尾區分所屬市場, 如果沒有指定字尾, 則預設為上證股票)
 *
 * @param   pTcpChannel         會話資訊
 * @param   pCodeListString     證券程式碼列表字串 (以空格或逗號/分號/豎線分割的字串)
 * @return  TRUE 成功; FALSE 失敗
 */
static BOOL
MdsApiSample_ResubscribeByCodePostfix(MdsApiSessionInfoT *pTcpChannel,
        const char *pCodeListString) {
    return MdsApi_SubscribeByString(pTcpChannel,
            pCodeListString, (char *) NULL,
            MDS_EXCH_SSE, MDS_MD_PRODUCT_TYPE_STOCK, MDS_SUB_MODE_SET,
            MDS_SUB_DATA_TYPE_L1_SNAPSHOT
                    | MDS_SUB_DATA_TYPE_L2_SNAPSHOT
                    | MDS_SUB_DATA_TYPE_L2_BEST_ORDERS);
}


/**
 * 進行訊息處理的回撥函式
 *
 * @param   pSessionInfo    會話資訊
 * @param   pMsgHead        訊息頭
 * @param   pMsgBody        訊息體資料
 * @param   pCallbackParams 外部傳入的引數
 * @return  大於等於0，成功；小於0，失敗（錯誤號）
 */
static int32
MdsApiSample_HandleMsg(MdsApiSessionInfoT *pSessionInfo,
        SMsgHeadT *pMsgHead, void *pMsgBody, void *pCallbackParams) {
    MdsMktRspMsgBodyT   *pRspMsg = (MdsMktRspMsgBodyT *) pMsgBody;

    /*
     * 根據訊息型別對行情訊息進行處理
     */
    switch (pMsgHead->msgId) {
    case MDS_MSGTYPE_L2_MARKET_DATA_SNAPSHOT:
    case MDS_MSGTYPE_L2_BEST_ORDERS_SNAPSHOT:
        /* 處理Level2快照行情訊息 */
        printf("... 接收到Level2快照行情訊息 (exchId[%hhu], instrId[%d])\n",
                pRspMsg->mktDataSnapshot.head.exchId,
                pRspMsg->mktDataSnapshot.head.instrId);
        break;

    case MDS_MSGTYPE_L2_TRADE:
    case ...:
         ...
    }

    return 0;
}


int
main(int argc, char *argv[]) {
    /* 配置檔案 */
    static const char   THE_CONFIG_FILE_NAME[] = "mds_client_sample.conf";
    /* 嘗試等待行情訊息到達的超時時間 (毫秒) */
    static const int32  THE_TIMEOUT_MS = 1000;

    MdsApiClientEnvT    cliEnv = {NULLOBJ_MDSAPI_CLIENT_ENV};
    int32               ret = 0;

    /* 初始化客戶端環境 (配置檔案參見: mds_client_sample.conf) */
    if (! MdsApi_InitAllByConvention(&cliEnv, THE_CONFIG_FILE_NAME)) {
        return -1;
    }

    /* 根據證券程式碼列表重新訂閱行情 (根據程式碼字尾區分所屬市場) */
    if (! MdsApiSample_ResubscribeByCodePostfix(&cliEnv.tcpChannel,
            "600000.SH, 600001.SH, 000001.SZ, 0000002.SZ")) {
        goto ON_ERROR;
    }

    while (1) {
        /* 等待行情訊息到達, 並通過回撥函式對訊息進行處理 */
        ret = MdsApi_WaitOnMsg(&cliEnv.tcpChannel, THE_TIMEOUT_MS,
                MdsApiSample_HandleMsg, NULL);
        if (unlikely(ret < 0)) {
            if (likely(SPK_IS_NEG_ETIMEDOUT(ret))) {
                /* 執行超時檢查 (檢查會話是否已超時) */
                continue;
            }

            if (SPK_IS_NEG_EPIPE(ret)) {
                /* 連線已斷開 */
            }
            goto ON_ERROR;
        }
    }

    MdsApi_LogoutAll(&cliEnv, TRUE);
    return 0;

ON_ERROR:
    MdsApi_DestoryAll(&cliEnv);
    return -1;
}

~~~


#### 1.2 示例程式碼的編譯和執行

1. 進入樣例程式碼目錄
	- ``cd mds_libs-xxx/include/mds_api/samples/``

2. 編譯程式碼
	- ``make -f Makefile.sample``

3. 修改配置檔案，確認服務地址、使用者名稱等正確
	- ``vi mds_client_sample.conf``

4. 執行樣例程式
	- ``./mds_subscribe_sample``
	- ``./mds_client_sample``


---
### 版本升級指引及修改歷史

- 版本升級指引參見 <@ref update_guide>
- 版本修改歷史參見 <@ref changelog>


---
### 常見問題

- 價格和金額單位
	- MDS中的所有價格均為`int32`型別的整型數值，單位精確到元后四位, 即: 1元=10000
	- MDS中的所有金額均為`int64`型別的整型數值，單位精確到元后四位, 即: 1元=10000

- 份額單位
	- MDS中的所有委託數量、成交數量等份額單位均為`int32`或`int64`型別的整型數值，不帶小數位
	- **注意:** 上海債券的份額單位是 <b>'手'</b>，而不是 '張'，與其它不同

- MDS中的行情時間(updateTime)是交易所時間嗎？
	- 是的，該時間來源於交易所，是行情資料的生成時間或者上游傳送時間（如果採集不到行情生成時間的話）


---
### MDS錯誤碼錶

| 錯誤碼 | 錯誤說明                            |
| :---- | :--------------------------------- |
| 1001  | 報文格式錯誤                       |
| 1002  | 當前主機不是主節點                  |
| 1003  | 主存庫操作失敗                     |
| 1004  | 因狀態等基礎資料不匹配，無法更新資料   |
| 1005  | 協議版本不相容                     |
| 1006  | 資料不存在                         |
| 1007  | 非服務開放時間                     |
| 1008  | 非法的定位遊標                     |
| 1009  | 非法的客戶端登入使用者名稱稱             |
| 1010  | 非法的證券程式碼                     |
| 1011  | 非法的客戶程式碼                     |
| 1012  | 非法的客戶端型別                    |
| 1013  | 客戶端已被禁用                     |
| 1014  | 客戶端密碼不正確                    |
| 1015  | 客戶端重複登入                     |
| 1016  | 客戶端連線數量過多                  |
| 1017  | 客戶端未經授權操作他人賬戶           |
| 1018  | 資料超出修改範圍                    |
| 1019  | 非法的應用系統名稱                  |
| 1020  | 查詢條件不匹配                     |
| 1021  | 客戶端ip/mac地址格式錯誤            |
| 1022  | 尚不支援或尚未開通此業務             |
| 1029  | 密碼未改變                         |
| 1031  | 非法的加密型別                     |
| 1033  | 無可用節點                         |
| 1034  | 密碼強度不足                       |
| 1035  | 非法的產品型別                     |
| 1036  | 未通過黑白名單檢查                 |
| 1301  | 行情訂閱失敗                       |
