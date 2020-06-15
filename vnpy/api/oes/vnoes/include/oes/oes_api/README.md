# Swordfish-OES API    {#mainpage}

箭魚快速訂單系統API使用說明


---
### Quick Start

#### 1.1 示例程式碼

- 參見 oes_api/samples/c_sample 目錄下的樣例檔案
	- 配置檔案樣例 <oes_client_sample.conf>
	- 程式碼樣例 <oes_client_sample.c>
	- 用於樣例程式碼編譯的 <Makefile.sample>

oes_client_sample.c 摘錄如下：
~~~{.c}

/**
 * 傳送委託請求
 *
 * 提示:
 * - 可以通過 OesApi_GetClEnvId() 方法獲得到當前通道所使用的客戶端環境號(clEnvId), 如:
 *   <code>int8 clEnvId = OesApi_GetClEnvId(pOrdChannel);</code>
 *
 * @param   pOrdChannel     委託通道的會話資訊
 * @param   mktId           市場程式碼 (必填) @see eOesMarketIdT
 * @param   pSecurityId     股票程式碼 (必填)
 * @param   pInvAcctId      股東賬戶程式碼 (可不填)
 * @param   ordType         委託型別 (必填) @see eOesOrdTypeT, eOesOrdTypeShT, eOesOrdTypeSzT
 * @param   bsType          買賣型別 (必填) @see eOesBuySellTypeT
 * @param   ordQty          委託數量 (必填, 單位為股/張)
 * @param   ordPrice        委託價格 (必填, 單位精確到元后四位，即1元 = 10000)
 * @return  大於等於0，成功；小於0，失敗（錯誤號）
 */
static inline int32
_OesApiSample_SendOrderReq(OesApiSessionInfoT *pOrdChannel,
        uint8 mktId, const char *pSecurityId, const char *pInvAcctId,
        uint8 ordType, uint8 bsType, int32 ordQty, int32 ordPrice) {
    OesOrdReqT          ordReq = {NULLOBJ_OES_ORD_REQ};

    SLOG_ASSERT2(pOrdChannel
            && mktId > 0 && mktId < __OES_MKT_ID_MAX
            && pSecurityId && ordType < __OES_ORD_TYPE_FOK_MAX
            && bsType > 0 && bsType < __OES_BS_TYPE_MAX_TRADING
            && ordQty > 0 && ordPrice >= 0,
            "pOrdChannel[%p], mktId[%hhu], pSecurityId[%s], " \
            "ordType[%hhu], bsType[%hhu], ordQty[%d], ordPrice[%d]",
            pOrdChannel, mktId, pSecurityId ? pSecurityId : "NULL",
            ordType, bsType, ordQty, ordPrice);

    ordReq.clSeqNo = (int32) ++pOrdChannel->lastOutMsgSeq;
    ordReq.mktId = mktId;
    ordReq.ordType = ordType;
    ordReq.bsType = bsType;

    strncpy(ordReq.securityId, pSecurityId, sizeof(ordReq.securityId) - 1);
    if (pInvAcctId) {
        /* 股東賬戶可不填 */
        strncpy(ordReq.invAcctId, pInvAcctId, sizeof(ordReq.invAcctId) - 1);
    }

    ordReq.ordQty = ordQty;
    ordReq.ordPrice = ordPrice;

    return OesApi_SendOrderReq(pOrdChannel, &ordReq);
}


/**
 * 傳送撤單請求
 *
 * @param   pOrdChannel     委託通道的會話資訊
 * @param   mktId           被撤委託的市場程式碼 (必填) @see eOesMarketIdT
 * @param   pSecurityId     被撤委託的股票程式碼 (選填, 若不為空則校驗待撤訂單是否匹配)
 * @param   pInvAcctId      被撤委託的股東賬戶程式碼 (選填, 若不為空則校驗待撤訂單是否匹配)
 * @param   origClSeqNo     被撤委託的流水號 (若使用 origClOrdId, 則不必填充該欄位)
 * @param   origClEnvId     被撤委託的客戶端環境號 (小於等於0, 則使用當前會話的 clEnvId)
 * @param   origClOrdId     被撤委託的客戶訂單編號 (若使用 origClSeqNo, 則不必填充該欄位)
 * @return  大於等於0，成功；小於0，失敗（錯誤號）
 */
static inline int32
_OesApiSample_SendOrderCancelReq(OesApiSessionInfoT *pOrdChannel,
        uint8 mktId, const char *pSecurityId, const char *pInvAcctId,
        int32 origClSeqNo, int8 origClEnvId, int64 origClOrdId) {
    OesOrdCancelReqT    cancelReq = {NULLOBJ_OES_ORD_CANCEL_REQ};

    SLOG_ASSERT2(pOrdChannel && mktId > 0 && mktId < __OES_MKT_ID_MAX,
            "pOrdChannel[%p], mktId[%hhu]", pOrdChannel, mktId);

    cancelReq.clSeqNo = (int32) ++pOrdChannel->lastOutMsgSeq;
    cancelReq.mktId = mktId;

    if (pSecurityId) {
        /* 撤單時被撤委託的股票程式碼可不填 */
        strncpy(cancelReq.securityId, pSecurityId, sizeof(cancelReq.securityId) - 1);
    }

    if (pInvAcctId) {
        /* 撤單時被撤委託的股東賬戶可不填 */
        strncpy(cancelReq.invAcctId, pInvAcctId, sizeof(cancelReq.invAcctId) - 1);
    }

    cancelReq.origClSeqNo = origClSeqNo;
    cancelReq.origClEnvId = origClEnvId;
    cancelReq.origClOrdId = origClOrdId;

    return OesApi_SendOrderCancelReq(pOrdChannel, &cancelReq);
}


/**
 * 對執行報告訊息進行處理的回撥函式
 *
 * @param   pRptChannel     回報通道的會話資訊
 * @param   pMsgHead        訊息頭
 * @param   pMsgBody        訊息體資料
 * @param   pCallbackParams 外部傳入的引數
 * @return  大於等於0，成功；小於0，失敗（錯誤號）
 */
static inline int32
_OesApiSample_HandleReportMsg(OesApiSessionInfoT *pRptChannel,
        SMsgHeadT *pMsgHead, void *pMsgBody, void *pCallbackParams) {
    OesRspMsgBodyT      *pRspMsg = (OesRspMsgBodyT *) pMsgBody;
    OesRptMsgT          *pRptMsg = &pRspMsg->rptMsg;

    assert(pRptChannel && pMsgHead && pRspMsg);

    switch (pMsgHead->msgId) {
    case OESMSG_RPT_ORDER_INSERT:               /* OES委託已生成 (已通過風控檢查) */
        printf(">>> Recv OrdInsertRsp: {clSeqNo: %d, clOrdId: %lld}\n",
                pRptMsg->rptBody.ordInsertRsp.clSeqNo,
                pRptMsg->rptBody.ordInsertRsp.clOrdId);
        break;

    case OESMSG_RPT_BUSINESS_REJECT:            /* OES業務拒絕 (未通過風控檢查等) */
        printf(">>> Recv OrdRejectRsp: {clSeqNo: %d, ordRejReason: %d}\n",
                pRptMsg->rptBody.ordRejectRsp.clSeqNo,
                pRptMsg->rptHead.ordRejReason);
        break;

    case OESMSG_RPT_ORDER_REPORT:               /* 交易所委託回報 (包括交易所委託拒絕、委託確認和撤單完成通知) */
        printf(">>> Recv OrdCnfm: {clSeqNo: %d, clOrdId: %lld}\n",
                pRptMsg->rptBody.ordCnfm.clSeqNo,
                pRptMsg->rptBody.ordCnfm.clOrdId);
        break;

    case OESMSG_RPT_REPORT_SYNCHRONIZATION:     /* 回報同步響應 */
    case ...:
         ...
    }

    return 0;
}


/**
 * 回報採集處理 (可以做為執行緒的主函式執行)
 *
 * @param   pRptChannel     回報通道的會話資訊
 * @return  TRUE 處理成功; FALSE 處理失敗
 */
void*
OesApiSample_ReportThreadMain(OesApiClientEnvT *pClientEnv) {
    static const int32  THE_TIMEOUT_MS = 1000;

    OesApiSessionInfoT  *pRptChannel = &pClientEnv->rptChannel;
    int32               ret = 0;

    while (1) {
        /* 等待回報訊息到達, 並通過回撥函式對訊息進行處理 */
        ret = OesApi_WaitReportMsg(pRptChannel, THE_TIMEOUT_MS,
                _OesApiSample_HandleReportMsg, NULL);
        if (unlikely(ret < 0)) {
            if (likely(SPK_IS_NEG_ETIMEDOUT(ret))) {
                /* 執行超時檢查 (檢查會話是否已超時) */
                if (likely(_OesApiSample_OnTimeout(pClientEnv) == 0)) {
                    continue;
                }

                /* 會話已超時 */
                goto ON_ERROR;
            }

            if (SPK_IS_NEG_EPIPE(ret)) {
                /* 連線已斷開 */
            }
            goto ON_ERROR;
        }
    }

    return (void *) TRUE;

ON_ERROR:
    return (void *) FALSE;
}

~~~


#### 1.2 示例程式碼的編譯和執行

1. 進入樣例程式碼目錄
	- ``cd oes_libs-xxx/include/oes_api/samples/c_sample``

2. 編譯程式碼
	- ``make -f Makefile.sample``

3. 修改配置檔案，確認服務地址、使用者名稱等正確
	- ``vi oes_client_sample.conf``

4. 執行樣例程式
	- ``./oes_client_sample``


---
### 版本升級指引及修改歷史

- 版本升級指引參見 <@ref update_guide>
- 版本修改歷史參見 <@ref changelog>


---
### 常見問題

- 價格和金額單位
  - OES中的所有價格均為`int32`型別的整型數值，單位精確到元后四位，即: 1元=10000
  - OES中的所有金額均為`int64`型別的整型數值，單位精確到元后四位，即: 1元=10000

- 份額單位
  - OES中的所有委託數量、成交數量等份額單位均為`int32`或`int64`型別的整型數值，不帶小數位
  - OES中債券交易的份額單位是 <b>'張'</b>，股票交易份額單位是 <b>'股'</b>

- 報價單位不在合法區間？
	- OES中的所有價格均為`int32`型別的整型數值，單位精確到元后四位，即: 1元=10000

- 怎麼分辨出查詢返回的最後一條記錄？
  <br>OesApi_QueryOrder是同步函式，它返回了代表查詢到的所有委託資訊回撥完成，在Action_OnQryOrdItem
  回撥函式中沒有想過最後一條的標識，返回值>=0代表查詢到的記錄數量。

- 如何檢視OrdRejectRsp的拒絕原因？
  <br>用OesApi_GetErrorMsg(rptHead.ordRejReason)去獲取相關錯誤資訊，訊息頭中的status、detailStatus
  主要返回通訊層的錯誤。

- clEnvId 作用？
	- clEnvId 是客戶端環境號，用於區分不同客戶端例項上報的委託。即可以為每個客戶端例項分配不同的 clEnvId，這樣這些客戶端例項就可以各自維護自己的 clSeqNo 而不會相互干擾
	- 不同客戶端例項可以使用同一 clEnvId 登入服務端。此時這些使用了同一 clEnvId 的客戶端例項共享同一個 clSeqNo 序列
	- clEnvId 客戶端的取值範圍是 __[0~99]__ ([100~127] 為保留區間，客戶端應避免使用)
	- 可以通過 OesApi_GetClEnvId() 介面獲得本客戶端例項繫結的 clEnvId
	- 服務端維護的委託資訊中，會記錄傳送此委託的源客戶端例項所繫結的 clEnvId。委託回報訊息(OesOrdCnfmT.clEnvId) 和 委託查詢應答(OesOrdItemT.clEnvId) 會攜帶此資訊
	- 配置檔案相關設定請參考 oes_client_sample.conf 中 [oes_client].clEnvId 引數的設定


---
### OES錯誤碼錶

| 錯誤碼 | 錯誤說明                            |
| :---- | :--------------------------------- |
| 1001  | 報文格式錯誤                         |
| 1002  | 當前主機不是主節點                    |
| 1003  | 主存庫操作失敗                       |
| 1004  | 因狀態等基礎資料不匹配，無法更新資料     |
| 1005  | 協議版本不相容                       |
| 1006  | 資料不存在                           |
| 1007  | 非服務開放時間                       |
| 1008  | 非法的定位遊標                       |
| 1009  | 非法的客戶端登入使用者名稱稱               |
| 1010  | 非法的證券程式碼                       |
| 1011  | 非法的客戶程式碼                       |
| 1012  | 非法的客戶端型別                      |
| 1013  | 客戶端已被禁用                       |
| 1014  | 客戶端密碼不正確                      |
| 1015  | 客戶端重複登入                       |
| 1016  | 客戶端連線數量過多                    |
| 1017  | 客戶端未經授權操作他人賬戶             |
| 1018  | 資料超出修改範圍                      |
| 1019  | 非法的應用系統名稱                    |
| 1020  | 請求條件有衝突                       |
| 1021  | 非法的客戶端IP/MAC地址格式            |
| 1022  | 尚不支援或尚未開通此業務               |
| 1023  | 非法的客戶端環境號                    |
| 1024  | 交易所拒絕                           |
| 1025  | 主櫃拒絕                            |
| 1026  | 流量超出限制範圍                      |
| 1027  | 禁止使用API登入                      |
| 1028  | 非法的私募基金產品程式碼                 |
| 1029  | 密碼未改變                           |
| 1030  | 非法的來源分類                       |
| 1031  | 非法的加密型別                       |
| 1032  | 非法的客戶端裝置序列號                 |
| 1033  | 無可用節點                           |
| 1034  | 密碼強度不足                         |
| 1035  | 非法的產品型別                       |
| 1036  | 未通過黑白名單檢查 |
| 1101  | 登入櫃檯失敗                         |
| 1102  | 上報至櫃檯失敗                       |
| 1103  | 從櫃檯獲取狀態失敗                    |
| 1201  | 非法的證券賬戶程式碼                    |
| 1202  | 非法的資金賬戶程式碼                    |
| 1203  | 非法的出入金方向                      |
| 1204  | 非法的市場程式碼                       |
| 1205  | 非法的證券類別                       |
| 1206  | 非法的買賣型別                       |
| 1207  | 非法的幣種                           |
| 1208  | 非法的委託型別                       |
| 1209  | 無效的賬戶狀態                       |
| 1210  | 未找到委託資訊                       |
| 1211  | 未找到持倉資訊                       |
| 1212  | 未找到出入金流水                      |
| 1213  | 流水號重複                           |
| 1214  | 當前時段不能報價                      |
| 1215  | 沒有操作許可權                         |
| 1216  | 可用/可取資金餘額不足                 |
| 1217  | 可用持倉不足                         |
| 1218  | 委託數量不在合法區間內                 |
| 1219  | 非數量單位的整數倍                    |
| 1220  | 非法的PBU程式碼                        |
| 1221  | 價格不在合法區間內                    |
| 1222  | 非價格單位的整數倍                    |
| 1223  | 無漲停價市價委託失敗                  |
| 1224  | 當前時段不支援市價委託                 |
| 1225  | 無效的訂單狀態                       |
| 1226  | 撤單資訊與原始委託不符                 |
| 1227  | 重複撤單                            |
| 1228  | 未通過限倉檢查                       |
| 1229  | 未通過限購檢查                       |
| 1230  | 超過了ETF最大現金替代比例              |
| 1231  | 非行權日                            |
| 1232  | 證券停牌                            |
| 1233  | 合約限制開倉                         |
| 1234  | 當日累計申購或贖回數量超過限額          |
| 1235  | 當日累計淨申購或淨贖回數量超過限額       |
| 1236  | 找不到前收盤價                       |
| 1237  | 超過報撤比限制                       |
| 1238  | 委託請求過於頻繁                      |
| 1239  | 非法的出入金轉賬金額                  |
| 1240  | 重複的認購委託                       |
| 1241  | 認購委託份數超過認購額度               |
| 1242  | 出入金筆數超過限制                    |
| 1243  | 禁止同時做多筆出入金                  |
| 1244  | 非法的新股配號、中籤記錄型別            |
| 1245  | 限制股東賬戶進行買交易                 |
| 1246  | 限制股東賬戶進行賣交易                 |
| 1247  | 限制股東賬戶進行逆回購交易             |
| 1248  | 限制股東賬戶進行新股認購交易            |
| 1249  | 股東賬戶沒有市價委託交易的許可權          |
| 1250  | 股東賬戶沒有交易創業板證券的許可權        |
| 1251  | 股東賬戶沒有交易分級基金的許可權          |
| 1252  | 股東賬戶沒有債券合格投資者的許可權        |
| 1253  | 客戶風險評級低於交易證券需求的風險等級   |
| 1254  | 股東賬戶沒有交易風險警示證券的許可權       |
| 1255  | 股東賬戶沒有交易退市整理證券的許可權       |
| 1256  | 股東賬戶沒有交易單市場ETF的許可權         |
| 1257  | 股東賬戶沒有交易跨市場ETF的許可權         |
| 1258  | 股東賬戶沒有交易貨幣基金ETF的許可權       |
| 1259  | 股東賬戶沒有交易跨境ETF的許可權          |
| 1260  | 僅允許合格投資者投資該證券             |
| 1261  | 僅允許合格機構投資者投資該證券          |
| 1262  | 出入金執行異常，待人工干預             |
| 1263  | 交易日不在證券的發行期內               |
| 1264  | 該ETF禁止申購                        |
| 1265  | 該ETF禁止贖回                        |
| 1266  | 限制股東賬戶進行撤指定                 |
| 1267  | 限制股東賬戶進行轉託管                 |
| 1268  | 機構客戶/主櫃業務不支援銀行轉帳         |
| 1269  | 禁止私募基金產品交易此證券             |
| 1270  | 禁止客戶交易此證券                    |
| 1271  | 股東賬戶沒有交易存託憑證的許可權          |
| 1272  | 股東賬戶沒有交易創新企業股票的許可權       |
| 1273  | 非法的出入金轉賬型別                  |
| 1274  | 股東賬戶沒有交易滬倫通存託憑證的許可權     |
| 1275  | 股東賬戶沒有交易科創板的許可權     |
