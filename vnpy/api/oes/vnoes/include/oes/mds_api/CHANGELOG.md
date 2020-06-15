# MDS-API Change Log    {#changelog}

MDS_0.15.9 / 2019-05-31
==============================================

  * fix: 修復API無法支援取值大於1024的檔案描述符的問題 (因為select的限制, 當檔案描述符的取值大於1024時, 會導致堆疊溢位)
  * fix: 擴大深圳證券業務開關的最大數量（該修改會對之前版本API的延遲統計造成影響）, 以應對行情資料內容的更新
  * 調整行情資料型別(mdStreamType, eMdsMdStreamTypeT)的取值, 使其可以標識出快照行情的具體資料型別
     - 該修改會存在相容性問題, 客戶端程式可以通過編譯錯誤來識別需要調整的地方 (如果沒有編譯錯誤就不需要調整)
     - 行情資料型別的取值將盡量與訊息型別保持一致, 但以下型別比較特殊：
       - 深圳成交量統計指標
       - 上交所 Level1 行情快照-債券
       - 上交所 Level1 行情快照-基金
  * 重新命名 securityType => mdProductType, 以避免與交易端的證券型別混淆
    - securityType => mdProductType
    - eMdsSecurityTypeT => eMdsMdProductTypeT
  * 刪除已經廢棄的虛擬集合競價訊息的訊息定義和資料型別定義
  * 調整快照頭 MdsMktDataSnapshotHeadT 中的內部欄位定義, 將 __origTickSeq 欄位拆分為 __origTickSeq + __lastUpdateTime 兩個欄位 (內部使用的欄位, 協議保持相容)
  * 增加修改客戶端登入密碼介面
    - MdsApi_SendChangePasswordReq
  * 增加設定/獲取客戶端自定義的本地IP/MAC地址的介面
    - MdsApi_SetCustomizedIp
    - MdsApi_GetCustomizedIp
    - MdsApi_SetCustomizedMac
    - MdsApi_GetCustomizedMac
  * 增加設定/獲取客戶端自定義的裝置序列號的介面
    - MdsApi_SetCustomizedDriverId
    - MdsApi_GetCustomizedDriverId
  * 新增錯誤碼
    - 1029, 密碼未改變
    - 1034, 密碼強度不足
    - 1036, 未通過黑白名單檢查

MDS_0.15.8 / 2019-02-22
==============================================

  * fix: 修復API無法支援取值大於1024的檔案描述符的問題 (因為select的限制, 當檔案描述符的取值大於1024時, 會導致堆疊溢位)
  * 重新命名 securityType => mdProductType, 以避免與交易端的證券型別混淆
    - securityType => mdProductType
    - eMdsSecurityTypeT => eMdsMdProductTypeT
  * 刪除已經廢棄的虛擬集合競價訊息的訊息定義和資料型別定義
  * 調整快照頭 MdsMktDataSnapshotHeadT 中的內部欄位定義, 將 __origTickSeq 欄位拆分為 __origTickSeq + __lastUpdateTime 兩個欄位 (內部使用的欄位, 協議保持相容)
  * 增大登入時的網路超時時間, 避免因為系統繁忙等原因導致登入失敗
  * 調整錯誤描述
    - 1007, 非服務開放時間
    - 1022, 尚不支援或尚未開通此業務
    - 1035, 非法的產品型別

MDS_0.15.7.6 / 2018-11-28
==============================================

  * 新增批量查詢行情快照介面
    - MdsApi_QuerySnapshotList
  * 按照配置資訊結構體, 增加初始化客戶端環境介面
    - MdsApi_InitAllByCfgStruct

MDS_0.15.7.6 / 2018-11-03
==============================================

  * 增加查詢證券(股票/債券/基金)靜態資訊的介面
    - MdsApi_QueryStockStaticInfo
  * 新增錯誤碼定義
    - 1035, 非法的產品型別（MDSERR_ILLEGAL_PRODUCT_TYPE）

MDS_0.15.7.5 / 2018-08-31
==============================================

  * 修復 '返回錯誤號對應的錯誤資訊 (MdsApi_GetErrorMsg)' 介面, windows平臺獲取錯誤資訊不準確的問題

MDS_0.15.7.4 / 2018-08-31
==============================================

  * 增加設定當前執行緒登入使用者名稱/登入密碼的介面
    - MdsApi_SetThreadUsername
    - MdsApi_SetThreadPassword
  * 增加返回當前執行緒最近一次API呼叫失敗的錯誤號的介面
    - OesApi_GetLastError
    - OesApi_SetLastError
  * 新增錯誤號詳見 mds_errors.h
  * Merge MDS_0.15.5.16
    - fix: 修復當多個執行緒同時初始化API日誌時, 會導致日誌資訊重複輸出的問題
    - 增加 MdsApi_HasMoreCachedData 介面, 用於返回已經接收到但尚未被回撥函式處理的快取資料長度
    - 重構 SubscribeByString 介面
      - 支援訂閱所有產品的行情或不訂閱任何產品的行情
      - 支援通過 .SH 或 .SZ 字尾為證券程式碼指定其所屬的交易所
      - 新增 MdsHelper_SetTickTypeOnSubscribeByString 介面, 以設定SubscribeByString預設使用的資料模式 (TickType)
      - 增量訂閱時, 允許不指定 dataType (小於0) 而繼承之前訂閱的資料型別
    - 增加可訂閱的資料種類 (DataType), 以支援單獨訂閱指數行情和期權行情
      - MDS_SUB_DATA_TYPE_INDEX_SNAPSHOT, 與L1_SNAPSHOT的區別在於, INDEX_SNAPSHOT可以單獨訂閱指數行情
      - MDS_SUB_DATA_TYPE_OPTION_SNAPSHOT, 與L1_SNAPSHOT的區別在於, OPTION_SNAPSHOT可以單獨訂閱期權行情
    - 增加可以處理壓縮過的訊息的 WaitOnMsg 介面:
      - MdsApi_WaitOnMsgCompressible
      - MdsApi_WaitOnTcpChannelGroupCompressible
      - 與不帶 Compressible 字尾的介面相比, 帶 Compressible 字尾的介面會自動檢測和處理壓縮過的訊息, 但也會因此帶來微小的效能損失

MDS_0.15.5.16 / 2018-08-31
==============================================

  * fix: 修復當多個執行緒同時初始化API日誌時, 會導致日誌資訊重複輸出的問題
  * 增加 MdsApi_HasMoreCachedData 介面, 用於返回已經接收到但尚未被回撥函式處理的快取資料長度
  * 增加設定當前執行緒登入使用者名稱/登入密碼的介面
    - MdsApi_SetThreadUsername
    - MdsApi_SetThreadPassword
  * 增加返回最近一次API呼叫失敗的錯誤號的介面
    - MdsApi_GetLastError
  * 重構 SubscribeByString 介面
    - 支援訂閱所有產品的行情或不訂閱任何產品的行情
    - 支援通過 .SH 或 .SZ 字尾為證券程式碼指定其所屬的交易所
    - 新增 MdsHelper_SetTickTypeOnSubscribeByString 介面, 以設定SubscribeByString預設使用的資料模式 (TickType)
    - 增量訂閱時, 允許不指定 dataType (小於0) 而繼承之前訂閱的資料型別
  * 增加可訂閱的資料種類 (DataType), 以支援單獨訂閱指數行情和期權行情
    - MDS_SUB_DATA_TYPE_INDEX_SNAPSHOT, 與L1_SNAPSHOT的區別在於, INDEX_SNAPSHOT可以單獨訂閱指數行情
    - MDS_SUB_DATA_TYPE_OPTION_SNAPSHOT, 與L1_SNAPSHOT的區別在於, OPTION_SNAPSHOT可以單獨訂閱期權行情
  * 增加可以處理壓縮過的訊息的 WaitOnMsg 介面:
    - MdsApi_WaitOnMsgCompressible
    - MdsApi_WaitOnTcpChannelGroupCompressible
    - 與不帶 Compressible 字尾的介面相比, 帶 Compressible 字尾的介面會自動檢測和處理壓縮過的訊息, 但也會因此帶來微小的效能損失

MDS_0.15.5.11 / 2018-06-05
==============================================

  * fix: 擴大Level2增量更新訊息支援的最大價位變更數量和委託明細數量, 修復在巨幅波動場景下會因為支援的價位數量不足導致丟失價位資訊的BUG 
    - 如果使用的是舊版本的API, 那麼伺服器端將不再推送增量更新訊息 (只推送全量快照), 以此來保持相容
    - 如果需要使用增量更新訊息的話, 就需要更新到最新版本的API, 否則不需要更新API

MDS_0.15.5.10 / 2018-05-24
==============================================

  * 行情訂閱條件和訂閱配置中增加 '逐筆資料的過期時間型別 tickExpireType' (相容之前版本)
  * 增加了一個僅內部使用的行情訂閱條件 '待訂閱的內部頻道號', 前端不需要關心和處理 (相容之前版本)

MDS_0.15.5.4 / 2018-02-22
==============================================

  * 調整介面 MdsApi_InitAll, 增加一個函式引數 (pUdpTickOrderAddrKey), 以支援分別訂閱逐筆成交和逐筆委託的行情組播
  * Merge MDS_0.15.5.2
    - fix: 解決在Windows下的相容性問題
    - 增加介面 MdsApi_GetLastRecvTime、MdsApi_GetLastSendTime, 用於獲取通道最近接受/傳送訊息的時間
    - 登入失敗時, 可以通過 errno/SPK_GET_ERRNO() 獲取到具體失敗原因

MDS_0.15.5.2 / 2018-01-29 (解決Windows相容性問題的API更新版本)
==============================================

  * fix: 解決在Windows下的相容性問題。包括:
    - fix: 在Windows下, API的Socket非阻塞模式有問題, 只能工作在阻塞模式下
    - fix: 在Windows下, 當沒有行情資料時, 行情訂閱的傳送處理會長時間夯住, 直到有心跳訊息觸發才返回
    - fix: 在Windows下, 當在除錯模式下執行時, 如果網路連線異常的話, 在退出時(關閉socket連線時)就會報異常
    - fix: 在Windows下, 不能自動獲取IP和MAC地址, 需要顯式的設定客戶端本地的IP和MAC
  * 增加介面 MdsApi_GetLastRecvTime、MdsApi_GetLastSendTime, 用於獲取通道最近接受/傳送訊息的時間
  * 登入失敗時, 可以通過 errno/SPK_GET_ERRNO() 獲取到具體失敗原因

MDS_0.15.5.1 / 2017-11-22
==============================================

  * fix: 修復 MdsApi_InitAllByConvention() 介面總是返回連線失敗的BUG
  * 增加數值型別的協議版本號 MDS_APPL_VER_VALUE, 以方便比對版本
  * 增加 MdsApi_IsValidTcpChannel、MdsApi_IsValidUdpChannel 等介面, 用於判斷通道是否已經連線且有效

MDS_0.15.5 / 2017-11-12
==============================================

  * 新增介面 '獲取API的發行版本號 (MdsApi_GetApiVersion)'
  * 預設開啟用於統計延時的打點資訊, 並將打點資訊的時間戳型別改為 timeval32 (STimeval32T) 型別
  * 伺服器端刪除了對JSON等通訊協議等支援, 改為只支援二進位制協議
  * 在行情組播中推送逐筆資料, 並劃分行情組播通道分別推送L1快照、L2快照和逐筆資料
  * 調整介面 MdsApi_InitAll, 以支援同時初始化多個組播通道
  * 增加通道組相關的 API 介面, 以支援同時接收多個連線通道的資料

MDS_0.15.3.3 / 2017/08/20
==============================================

 * 新增介面 '重置執行緒級別的日誌記錄器名稱 (MdsApi_ResetThreadLoggerName)', 以支援為當前執行緒設定獨立的日誌檔案

MDS_0.15.3 / 2017-08-14
==============================================

  * Merge MDS_0.12.9.12
    - fix: 針對Windows平臺, 因為GNULib的recv方法在多執行緒時有問題, 會出現不同的 Socket 互相干擾和序列執行的現象, 所以暫時切換回使用只能工作於阻塞模式的read/write方法
    - 已知問題:
      - 在Windows下, API的Socket非阻塞模式有問題, 暫時只能工作在阻塞模式下
  * Merge MDS_0.12.9.11
    - fix: 重構跨平臺處理, 完善API對Windows平臺的支援
      - fix: 修復在Windows下，Socket未能正確設定為非阻塞模式的BUG
      - fix: 修復在Windows下，因為errno不相容導致網路處理失敗的BUG
      - fix: 修復在Windows下，因為檔案路徑處理方式不相容，導致日誌初始化失敗的BUG
      - fix: 修復在Windows下，個別函式不相容導致編譯警告和執行錯誤的問題
      - fix: 修復因為中文字元編碼不一致導致在Windows下編譯失敗的問題
      - refactor: 在API標頭檔案中預設引用 spk_platforms.h 標頭檔案
      - refactor: 重構API樣例程式碼和樣例配置檔案

MDS_0.15.2 / 2017-07-12
==============================================

  * API 與 0.12.9.7 版本相同
    - 不再對外發布逐筆丟失訊息(MDS_MSGTYPE_L2_TICK_LOST), 該訊息已廢棄

MDS_0.15.1 / 2017-06-26
==============================================

  * fix: 修正效能測試版本的編譯錯誤
  * API 與 0.12.8 版本相同，無變化

MDS_0.12.9.12 / 2017-08-13
==============================================

  * fix: 針對Windows平臺, 因為GNULib的recv方法在多執行緒時有問題, 會出現不同的 Socket 互相干擾和序列執行的現象, 所以暫時切換回使用只能工作於阻塞模式的read/write方法
  * 已知問題:
    - 在Windows下, API的Socket非阻塞模式有問題, 暫時只能工作在阻塞模式下

MDS_0.12.9.11 / 2017-08-12
==============================================

  * 重構跨平臺處理, 完善API對Windows平臺的支援
    - fix: 修復在Windows下，Socket未能正確設定為非阻塞模式的BUG
    - fix: 修復在Windows下，因為errno不相容導致網路處理失敗的BUG
    - fix: 修復在Windows下，因為檔案路徑處理方式不相容，導致日誌初始化失敗的BUG
    - fix: 修復在Windows下，個別函式不相容導致編譯警告和執行錯誤的問題
    - fix: 修復因為中文字元編碼不一致導致在Windows下編譯失敗的問題
    - refactor: 重構跨平臺處理, 完善對Windows平臺的支援, 並在API標頭檔案中預設引用spk_platforms.h
    - refactor: 微調API樣例程式碼和樣例配置檔案

MDS_0.12.9.7 / 2017-07-12
==============================================

  * 不再對外發布逐筆丟失訊息(MDS_MSGTYPE_L2_TICK_LOST), 該訊息已廢棄

MDS_0.12.9_RC1 / 2017-06-05
==============================================

  * API 與 0.12.8 版本相同，無變化

MDS_0.12.8.1 / 2017-04-24 (API升級指引)
==============================================

### 訊息程式碼的變更
    1. 重新定義訊息型別的取值
    2. 將Level1證券行情全幅訊息拆分為'Level1市場行情快照'、'指數行情快照'、'期權行情快照'三個訊息:
        - MDS_MSGTYPE_MARKET_DATA_SNAPSHOT_FULL_REFRESH (Level1 市場行情快照)
        - MDS_MSGTYPE_INDEX_SNAPSHOT_FULL_REFRESH       (指數行情快照)
        - MDS_MSGTYPE_OPTION_SNAPSHOT_FULL_REFRESH      (期權行情快照)
    3. 新增Level2行情訊息:
        - MDS_MSGTYPE_L2_MARKET_DATA_SNAPSHOT           (Level2 市場行情快照)
        - MDS_MSGTYPE_L2_BEST_ORDERS_SNAPSHOT           (Level2 委託佇列快照 (買一/賣一前五十筆委託數量))
        - MDS_MSGTYPE_L2_TRADE                          (逐筆成交)
        - MDS_MSGTYPE_L2_ORDER                          (逐筆委託 (僅深圳))
        - MDS_MSGTYPE_L2_MARKET_OVERVIEW                (市場總覽訊息 (僅上海))
        - MDS_MSGTYPE_L2_VIRTUAL_AUCTION_PRICE          (虛擬集合競價訊息 (僅上海))
        - MDS_MSGTYPE_L2_MARKET_DATA_INCREMENTAL        (增量更新訊息, 僅在 TickType 為 AllIncrements 時存在 (僅上海))
        - MDS_MSGTYPE_L2_BEST_ORDERS_INCREMENTAL        (增量更新訊息, 僅在 TickType 為 AllIncrements 時存在 (僅上海))
    4. 新增通知訊息:
        - MDS_MSGTYPE_L2_TICK_LOST                      (逐筆資料丟失, 逐筆成交/逐筆委託發生了資料丟失, 並且無法重建, 將放棄這些丟失的逐筆資料)

### 結構體的變更
    1. 刪除的結構體和欄位
        - 刪除獨立的 MdsMktDataSnapshotEntryMetaT 結構體,
          將欄位整合到 MdsMktDataSnapshotHeadT 中, 並刪除原 meta.priceUnit (價格單位) 欄位
        - 刪除 MdsStockSnapshotBodyT.MDStreamID, MdsIndexSnapshotBodyT.MDStreamID 欄位
    2. 重新命名的結構體和欄位
        - 重新命名 MdsMktDataSnapshotEntryT -> MdsL1SnapshotBodyT
        - 重新命名 MdsIndexDataSnapshotEntryT -> MdsIndexSnapshotBodyT
        - 重新命名 MdsStockDataSnapshotEntryT -> MdsStockSnapshotBodyT
        - 重新命名 MdsStockSnapshotBodyT.PreCloseIOPV -> NAV
        - 重新命名並拆分原五檔價位欄位 MdsStockSnapshotBodyT.PriceLevel[5] -> BidLevels[5] + OfferLevels[5]
            - 可以參考如下正則表示式進行替換:
            - ``PriceLevel\[(\w+)\].BuyPrice -> BidLevels[\1].Price``
            - ``PriceLevel\[(\w+)\].BuyVolume -> BidLevels[\1].OrderQty``
            - ``PriceLevel\[(\w+)\].SellPrice -> OfferLevels[\1].Price``
            - ``PriceLevel\[(\w+)\].SellVolume -> OfferLevels[\1].OrderQty``
        - 重新命名原快照行情中的成交總量欄位 TradeVolume -> TotalVolumeTraded
    3. 新增的結構體和欄位
        - 為'市場狀態'、'證券實時狀態'和'市場總覽訊息'訊息新增 __exchSendingTime 和 __mdsRecvTime 欄位，以方便比對實際的行情延時
        - 擴充套件'證券行情全幅訊息(MdsMktDataSnapshotT)'的定義, 新增Level2快照訊息體, 完整訊息體定義如下:
            - MdsL2StockSnapshotBodyT             l2Stock;                  (Level2 快照行情(股票、債券、基金))
            - MdsL2StockSnapshotIncrementalT      l2StockIncremental;       (Level2 快照行情的增量更新訊息)
            - MdsL2BestOrdersSnapshotBodyT        l2BestOrders;             (Level2 買一／賣一前五十筆委託明細)
            - MdsL2BestOrdersSnapshotIncrementalT l2BestOrdersIncremental;  (Level2 買一／賣一前五十筆委託明細的增量更新訊息)
            - MdsStockSnapshotBodyT               stock;                    (Level1 股票、債券、基金行情資料)
            - MdsStockSnapshotBodyT               option;                   (Level1/Level2 期權行情資料)
            - MdsIndexSnapshotBodyT               index;                    (Level1/Level2 指數行情資料)
            - MdsL2VirtualAuctionPriceT           l2VirtualAuctionPrice;    (Level2 虛擬集合競價 (僅上證))
            - MdsL2MarketOverviewT                l2MarketOverview;         (Level2 市場總覽 (僅上證))
        - 新增逐筆行情結構體定義:
            - MdsL2TradeT                               (逐筆成交)
            - MdsL2OrderT                               (逐筆委託)

### 行情訂閱相關的變更
    1. 重新定義了行情訂閱訊息, 包括如下欄位和引數:
        - 訂閱模式 (subMode) @see eMdsSubscribedTickTypeT
            - 0: (Set) 重新訂閱，設定為訂閱列表中的股票
            - 1: (Append) 追加訂閱，增加訂閱列表中的股票
            - 2: (Delete) 刪除訂閱，刪除訂閱列表中的股票
        - 資料模式, 訂閱最新的行情快照還是所有時點的資料 (tickType) @see eMdsSubscribedTickTypeT
            - 0: (LatestSimplified) 只訂閱最新的行情快照資料, 並忽略和跳過已經過時的資料 (推薦使用該模式即可)
        - 指定市場和證券型別的訂閱標誌
            - 包括如下欄位:
                - sseStockFlag/sseIndexFlag/sseOptionFlag
                - szseStockFlag/szseIndexFlag/szseOptionFlag
            - 取值說明 @see eMdsMktSubscribeFlagT
                - 0: (Default) 根據訂閱列表訂閱產品行情
                - 1: (All) 訂閱該市場和證券型別下所有產品的行情
                - 2: (Disable) 禁用該市場下所有產品的行情
        - 在推送實時行情資料之前, 是否需要推送已訂閱產品的初始的行情快照 (isRequireInitialMktData)
            - 0: 不需要
            - 1: 需要, 即確保客戶端可以至少收到一幅已訂閱產品的快照行情 (如果有的話)
        - 訂閱的資料種類 (dataTypes) @see eMdsSubscribeDataTypeT
            - 0:      預設資料種類 (所有)
            - 0x0001: L1快照/指數/期權
            - 0x0002: L2快照
            - 0x0004: L2委託佇列
            - 0x0008: L2逐筆成交
            - 0x0010: L2逐筆委託（深圳）
            - 0x0020: L2虛擬集合競價（上海）
            - 0x0040: L2市場總覽（上海）
            - 0x0100: 市場狀態（上海）
            - 0x0200: 證券實時狀態（深圳）
            - 0xFFFF: 所有資料
            - 例如, 如果只需要訂閱 'L1快照' 和 'L2快照', 則可以將 dataTypes 設定為:
                - 0x01 | 0x02
        - 請求訂閱的行情資料的起始時間 (beginTime)
            - 小於 0: 從頭開始獲取
            - 等於 0: 從最新位置開始獲取實時行情
            - 等於 0: 從指定的起始時間開始獲取 (格式為: HHMMSS 或 HHMMSSsss)
        - 為了方便使用, 擴大每個訂閱請求中能同時指定的產品數量至: 4000
    2. 調整了行情訂閱的應答訊息
        - 將返回各市場的實際訂閱結果, 即實際已訂閱的產品數量
    3. 重新命名原行情訂閱介面
        - 重新命名 MdsApi_SubscribeMarketData -> MdsApi_SyncSubscribeOnLogon
          傳送證券行情訂閱訊息，並同步等待應答訊息的返回 (僅適用於連線建立後的初次訂閱)
        - 重新命名 MdsApi_ResubscribeMarketData -> MdsApi_SubscribeMarketData
          以非同步的方式傳送證券行情實時訂閱請求，以重新訂閱、追加訂閱或刪除訂閱行情資料
    4. 增加了幾個更便於使用的行情訂閱介面
        - MdsApi_SubscribeByString                      (直接根據字串形式的證券程式碼列表訂閱行情資訊)
        - MdsApi_SubscribeByString2                     (以字串指標陣列形式的證券程式碼列表訂閱行情資訊)
        - MdsApi_SubscribeByStringAndPrefixes           (直接根據字串形式的證券程式碼列表和證券程式碼字首列表訂閱行情資訊)
        - MdsApi_SubscribeByStringAndPrefixes2          (以字串指標陣列形式的證券程式碼列表以及證券程式碼字首列表訂閱行情資訊)
        - 這幾個字串形式的訂閱介面, 沒有產品數量限制, 可以一次行傳入所有待訂閱的產品程式碼列表
        - 為了簡化使用, 建議直接使用基於字串形式的訂閱介面即可, 但如果需要進行更細粒度的控制,
          則還需要通過 MdsApi_SubscribeMarketData 介面進行訂閱
        - 訂閱介面的使用示例, 可以參考樣例程式碼:
            - mds_subscribe_sample.c 樣例檔案中的函式 MdsApiSample_ResubscribeByCodeFile
    5. 增加了幾個輔助的(二進位制)訂閱請求資訊維護函式
        - MdsHelper_ClearSubscribeRequestEntries        (清空訂閱資訊中的產品列表)
        - MdsHelper_SetSubscribeRequestMode             (設定訂閱模式)
        - MdsHelper_SetSubscribeRequestTickType         (設定資料模式 (TickType))
        - MdsHelper_SetSubscribeRequestDataTypes        (設定訂閱的資料種類)
        - MdsHelper_SetSubscribeRequestSubFlag          (設定指定市場和證券型別的訂閱標誌)
        - MdsHelper_AddSubscribeRequestEntry            (新增待訂閱產品到訂閱資訊中)

### 行情處理相關的變更
    1. 更新行情訂閱配置, 設定需要訂閱的資料種類
    2. 更新行情處理方法, 處理以下這些新增的行情訊息 (如果已經訂閱了的話):
        - MDS_MSGTYPE_MARKET_DATA_SNAPSHOT_FULL_REFRESH (Level1 市場行情快照)
        - MDS_MSGTYPE_INDEX_SNAPSHOT_FULL_REFRESH       (指數行情快照)
        - MDS_MSGTYPE_OPTION_SNAPSHOT_FULL_REFRESH      (期權行情快照)
        - MDS_MSGTYPE_L2_MARKET_DATA_SNAPSHOT           (Level2 市場行情快照)
        - MDS_MSGTYPE_L2_BEST_ORDERS_SNAPSHOT           (Level2 委託佇列快照 (買一/賣一前五十筆委託數量))
        - MDS_MSGTYPE_L2_TRADE                          (逐筆成交)
        - MDS_MSGTYPE_L2_ORDER                          (逐筆委託 (僅深圳))
        - MDS_MSGTYPE_L2_MARKET_OVERVIEW                (市場總覽訊息 (僅上海))
        - MDS_MSGTYPE_L2_VIRTUAL_AUCTION_PRICE          (虛擬集合競價訊息 (僅上海))
        - MDS_MSGTYPE_L2_MARKET_DATA_INCREMENTAL        (增量更新訊息, 僅在 TickType 為 AllIncrements 時存在 (僅上海))
        - MDS_MSGTYPE_L2_BEST_ORDERS_INCREMENTAL        (增量更新訊息, 僅在 TickType 為 AllIncrements 時存在 (僅上海))
    3. 可以參考樣例程式碼:
        - mds_subscribe_sample.c 樣例檔案中的函式 MdsApiSample_HandleMsg
        - 或者, mds_client_sample.c 樣例檔案中的函式 _MdsApiSample_HandleMsg

MDS_0.12.8.2 / 2017-05-16 (ChangeLog)
==============================================

  * 新增 '逐筆資料丟失訊息(MdsL2TickLostT)', 以通知下游系統逐筆資料(逐筆成交/逐筆委託)發生了資料丟失, 並且無法重建, 將放棄這些丟失的逐筆資料

MDS_0.12.8.1 / 2017-04-24 (ChangeLog)
==============================================

### 領域模型相關的變更
    - 刪除獨立的 MdsMktDataSnapshotEntryMetaT 結構體,
      將欄位整合到 MdsMktDataSnapshotHeadT 中, 並刪除原 meta.priceUnit (價格單位) 欄位
    - 重新命名 MdsMktDataSnapshotEntryT -> MdsL1SnapshotBodyT
    - 重新命名 MdsIndexDataSnapshotEntryT -> MdsIndexSnapshotBodyT
    - 重新命名 MdsStockDataSnapshotEntryT -> MdsStockSnapshotBodyT
    - 重新命名 MdsStockSnapshotBodyT.PreCloseIOPV -> NAV
    - 重定義 MdsStockSnapshotBodyT.PriceLevel[5] -> BidLevels[5] + OfferLevels[5]
        - ``PriceLevel\[(\w+)\].BuyPrice -> BidLevels[\1].Price``
        - ``PriceLevel\[(\w+)\].BuyVolume -> BidLevels[\1].OrderQty``
        - ``PriceLevel\[(\w+)\].SellPrice -> OfferLevels[\1].Price``
        - ``PriceLevel\[(\w+)\].SellVolume -> OfferLevels[\1].OrderQty``
    - 重新命名 MdsStockSnapshotBodyT.TradeVolume -> TotalVolumeTraded
    - 重新命名 MdsIndexSnapshotBodyT.TradeVolume -> TotalVolumeTraded
    - 刪除 MdsStockSnapshotBodyT.MDStreamID, MdsIndexSnapshotBodyT.MDStreamID 欄位
    - 為'市場狀態'和'證券實時狀態'訊息新增 __exchSendingTime, __mdsRecvTime 欄位，
      以方便比對實際的行情延時

### 通訊協議相關的變更
    - 重新定義訊息型別的取值
    - 將證券行情全幅訊息拆分為'Level1市場行情快照'、'指數行情快照'、'期權行情快照'三個訊息:
        - MDS_MSGTYPE_MARKET_DATA_SNAPSHOT_FULL_REFRESH
        - MDS_MSGTYPE_INDEX_SNAPSHOT_FULL_REFRESH
        - MDS_MSGTYPE_OPTION_SNAPSHOT_FULL_REFRESH
    - 調整訂閱型別（TickType）的列舉型別定義和取值
        - 重定義 MDS_TICK_TYPE_LATEST_ONLY -> MDS_TICK_TYPE_LATEST_SIMPLIFIED
            - 只訂閱最新的行情快照資料, 並忽略和跳過已經過時的資料 (推送的資料量最小, 不會重複傳送最新快照)
        - 重定義 MDS_TICK_TYPE_ALL_TICK -> MDS_TICK_TYPE_ALL_INCREMENTS
            - 訂閱所有時點的行情快照資料 (需要注意的是，在該模式下將會額外發送Level2行情快照的增量更新訊息)
        - 新增 MDS_TICK_TYPE_LATEST_TIMELY
            - 只訂閱最新的行情快照資料, 並立即傳送最新資料 (會更及時的獲取到交易活躍的最新行情, 但會重複傳送最新快照)
    - 為了方便使用, 擴大每個訂閱請求中能同時指定的產品數量至: 4000
    - 重新定義行情訂閱訊息
        - 訂閱模式 @see eMdsSubscribeModeT
        - 市場和證券型別訂閱標誌 @see eMdsMktSubscribeFlagT
        - 資料模式 @see eMdsSubscribedTickTypeT
        - 資料種類 @see eMdsSubscribeDataTypeT
        - 開始時間 (-1: 從頭開始獲取, 0: 從最新位置開始獲取實時行情, >0: 從指定的起始時間開始獲取)
        - 是否需要初始的行情資料

### API介面相關的變更
    - 重新命名 MdsApi_SubscribeMarketData -> MdsApi_SyncSubscribeOnLogon
    - 重新命名 MdsApi_ResubscribeMarketData -> MdsApi_SubscribeMarketData
    - 新增輔助的行情訂閱介面
        - MdsApi_SubscribeByString
        - MdsApi_SubscribeByStringAndPrefixes
        - MdsHelper_SetSubscribeRequestMode
        - MdsHelper_SetSubscribeRequestTickType
        - MdsHelper_SetSubscribeRequestDataTypes

MDS_0.12.6.3 / 2017-03-24
================================

  * 增加mds_api.h中的標頭檔案引用，API使用者不再需要顯式引用sutil庫的標頭檔案

MDS_0.12.3 / 2017-02-21
================================

  * 精簡API依賴的標頭檔案，並最小化API釋出包中的標頭檔案數量
  * 重新命名 protocol_parser/errors/mds_protocol_errors.h -> errors/mds_errors.h
  * 重構 MdsApi_GetErrorMsg 方法，支援統一返回業務錯誤或系統錯誤資訊
  * fix: 修復API解析訂閱配置時，交易所程式碼賦值錯誤的BUG
  * 新增輔助實現實時行情訂閱功能的介面和樣例程式碼
     - MdsApi_ResubscribeMarketData
     - MdsHelper_ClearSubscribeRequestEntries
     - MdsHelper_AddSubscribeRequestEntry
     - 樣例程式碼: mds_subscribe_sample.c

MDS_0.12.1 / 2016-12-21
================================

  * 查詢介面重新命名
     - MdsApi_QryMktDataSnapshot -> MdsApi_QueryMktDataSnapshot
     - MdsApi_QrySecurityStatus -> MdsApi_QuerySecurityStatus
     - MdsApi_QryTrdSessionStatus -> MdsApi_QueryTrdSessionStatus
  * 刪除 MdsApi_IsBusinessError 介面，查詢介面不再返回小於 -1000 的錯誤
  * 查詢介面返回值變更:
     - 無資料返回 NEG(ENOENT)
     - 查詢被伺服器拒絕返回 NEG(EINVAL)，具體錯誤資訊通過日誌列印

MDS_0.12 / 2016-12-06
==============================

  * 重構錯誤號定義，使錯誤號從1000開始
  * 增加 MdsApi_GetErrorMsg 和 MdsApi_GetErrorMsg2 方法
  * 在登入報文中增加協議版本號資訊, 並在登入時校驗協議版本號的相容性
