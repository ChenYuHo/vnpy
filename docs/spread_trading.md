# 價差交易模組

價差交易與CTA有比較大的不同：

- CTA主要是針對單標的品種，盈利主要靠肥尾部分，特點是低勝率高盈虧比。

- 價差交易針對的是關聯程度高的品種，實現方式可以是期現套利、跨期套利、跨市套利、跨品種套利。從另一個角度來看，價差交易的標的物是價差，價差的統計特徵是均值迴歸，即圍繞某個數值上下波動。因此出現黑天鵝的概率要遠遠少於單標的品種，其盈利主要靠尖峰部分。

&nbsp;

根據品種相關程度不同，價差交易所適用的領域也有所不同：

- 相關程度100%，也就是說交易的是同一樣商品，區別僅僅是所處的市場不同。舉個例子：比特幣在火幣的價格是8500美元，在幣安是8495美元，這樣完全可以從幣安以8495美元買入，並且在火幣以8500美元賣出，賺取5美元的無風險利潤。因此類似這種無風險套利，拼的是低延時，屬於高頻交易領域。需要投入大量精力在託管機房、海底光纜、網絡卡設計等方面。

- 相關程度高的品種，如期貨的近期合約和遠期合約，可以做日內交易。簡單的可以設定固定閾值，如價差<買入閾值，買入價差（買入主動腿，並且賣出被動退完成對衝）；價差>賣出閾值，賣出價差（賣出主動腿，並且買入被動腿完成對衝）。若價差並不嚴格的遵守均值迴歸；或者在大週期上價差發生較大的偏離，但是在小週期上圍繞著均值上下波動；這兩類可以使用布林帶通道實現套利，如價差>布林帶通道上軌，賣出價差；價差<布林帶下軌，買入價差。

- 相關程度價高品種，如產業鏈相關的期貨品種，可以做基本面套利。基本面套利更要求投資者主動挖掘有用資訊，如參與實地調研，或者使用無人機加上圖形識別技術監控品種的實際庫存狀況；通過對基本面資訊的分析與處理，然後在單個方向去交易價差，即在高位賣出價差，在均值位平倉離場。由於價差基本面套利的持倉週期可以從幾周到幾個月，所以對執行的要求不高，更偏重於基本面資訊的挖掘和處理。

&nbsp;

## 模組構成

價差交易模組主要由6部分構成，如下圖：

- base：定義了價差交易模組中用到的一些基礎設定，如主動腿/被動腿合約資料結構，以及由主動腿和被動腿合成的價差資料結構。

- template：包含了價差演算法模板和價差交易策略模板。

- strategies: 官方提供的價差交易策略示例，如basic_spread_strategy實現了只要設定好固定的閾值（buy、sell、short、cover），即可實現自動化交易。

- algo: 定義了主動對價成交演算法：為了規避交易所設定掛撤單次數的上限，通用做法是犧牲點差來保證成交率。並且價差交易也要求在主動腿完成交易後，被動腿要立刻跟上完成對衝。

- engine：定義了父類價差引擎，並且繼承於父類的價差資料引擎、價差演算法引擎、價差策略引擎。

- ui：基於PyQt5的GUI圖形應用。

![](https://vnpy-community.oss-cn-shanghai.aliyuncs.com/forum_experience/yazhang/spread_trading/seis_elementos.png)


&nbsp;

## 基本操作

### 打開價差交易介面

開啟VN Trader，先連線上交易介面，如BITMEX；然後在選單欄中點選【功能】->【價差交易】進入價差交易介面。

![](https://vnpy-community.oss-cn-shanghai.aliyuncs.com/forum_experience/yazhang/spread_trading/inicio.png)

&nbsp;

總體來說，價差交易介面可分成2部分：

- 交易部分：在建立好價差合約後，可以呼叫價差策略實現自動交易，也可以手動交易來調整倉位。
- 監控部分：可以檢視實時價差合約行情資訊，價差策略和價差演算法執行情況，日誌元件也會輸出相關資訊。

&nbsp;

### 建立價差合約

1） 尋找可組成價差的合約：

- 回到VN Trader，在選單欄中點選【幫助】-> 【查詢合約】按鈕，彈出合約查詢介面;
- 在介面中找到我們用於價差交易的合約;
- 在BITMEX的示例中，我們主要通過比特幣期貨的跨期套利來展示，即交易XBTUSD（比特幣期貨永續合約）和XBTZ19（比特幣期貨19年12月到期合約）。

![](https://vnpy-community.oss-cn-shanghai.aliyuncs.com/forum_experience/yazhang/spread_trading/future_contracto.png)

&nbsp;

2） 構建價差合約

- 點選【價差建立】按鈕，會彈出建立價差介面；
- 在介面中，【價差名稱】指的是使用者定義的價差合約名稱；
- 【主動腿程式碼】是在下面的【腿】選項中，通過【原生代碼】來找到的主動腿。一般來說，價差交易原則上是主動腿完成交易後，立刻用被動腿進行對衝，故主動腿一般選擇較為不活躍的合約，價格乘數和交易乘數均為正；被動腿一般選擇較為活躍的合約，價格乘數和交易乘數均為負；
- 【腿】包含構建價差合約的主動腿與被動腿，它們由【原生代碼】，【價格乘數】，【交易乘數】組成；
- 在BITMEX的比特幣期貨跨期套利示例中，其價格乘數和交易乘數均為1：1，即價差= XBTZ19 - XBTUSD；買入1手價差等於買入1手XBTZ19，同時賣出1手XBTUSD完成對衝。
- 設定好價差合約的引數後，點選下方的【建立價差】按鈕。


注意：在多條腿並且期貨合約規模不等時，構建價差會相對困難一些，如構建虛擬鋼廠套利所用到的價差合約：

- 螺紋鋼生產技藝是16噸鐵礦石加上5噸焦炭練成10噸螺紋鋼。
- 基於價格乘數的價差spread = 1* RB - 1.6\*I  - 0.5\*O。
- 但是由於螺紋是10噸/手，鐵礦石和焦炭都是100噸/手，所以他們交易乘數是1：10：10；
- 故基於最大公約數規則，其實際交易手數關係是每買入100手螺紋鋼（1000噸），需要賣出16手鐵礦石（1600噸）和5手焦炭（500噸）完成對衝。

![](https://vnpy-community.oss-cn-shanghai.aliyuncs.com/forum_experience/yazhang/spread_trading/contruction_spread_contracto.png)

&nbsp;

3）監控價差合約

- 建立好xbt價差後，【日誌】元件會輸出相關資訊；
- 【價差】元件也實時價差合約的行情資訊，價差合約由base.py的SpreadData類來負責；
- 在xbt價差的示例中，【買價】= 1\*XBTZ19買一價 - 1\*XBTUSD賣一價
- 【買量】= min（XBTZ19買一量，XBTUSD賣一量），取最小值用於保證各合約能均能成交；
- 【賣價】= 1\*XBTZ19賣一價 - 1\*XBTUSD買一價；
- 【賣量】= min（XBTZ19賣一量，XBTUSD買一量）；

![](https://vnpy-community.oss-cn-shanghai.aliyuncs.com/forum_experience/yazhang/spread_trading/resultado_contruction_spread_contracto.png)

&nbsp;

### 手動交易

假設當前xbt價差合約，買價為330和賣價為340；並且在大週期上，價差圍繞0上下波動。

價差交易的盈利在於高拋低吸，即在低位，如-500買入xbt價差合約，在高位，如+500賣出xbt價差合約，平倉獲利離場。由於不能立刻成交，所以其預設執行演算法SpreadTaker（主動對價成交演算法）會每隔一段時間進行委託操作：一般是以超價的限價單的形式發出委託。

下面通過2個例子，分別是發出委託立即成交和發出委託等待成交來具體介紹手動交易的操作情況：

1）發出委託立即成交

- 目標價差合約價格的350；
- 我們以超價5美金的形式，及355的價位發出買入限價單；
- 由於限價單（355）價位高於當前賣價（340），所以委託立刻成交。

![](https://vnpy-community.oss-cn-shanghai.aliyuncs.com/forum_experience/yazhang/spread_trading/buy_en_mano.png)

&nbsp;

2）成交委託監控

- 【日誌】元件顯示發出買入xbt價差合約的順序是：發出XBTZ19多頭委託 -> XBTZ19委託成交 -> 發出XBTUSD空頭委託 -> XBTUSD委託成交。價差交易必須遵循的邏輯是主動腿成交後，才去用被動腿來對衝頭寸，並且對衝必須儘可能及時。這也為什麼一般被動腿選擇較為活躍合約的原因。

- 【價差】元件顯示買入1手xbt價差合約成交後，【淨倉】從0變成1；實際上，VN Trader【持倉】元件顯示，XBTZ19合約多頭持倉1手，XBTUSD合約空頭持倉1手。

- 【演算法】元件顯示本次委託SpreadTaker演算法執行情況：成交數量1手，委託狀態是完全成交。

![](https://vnpy-community.oss-cn-shanghai.aliyuncs.com/forum_experience/yazhang/spread_trading/resultado_buy_en_mano.png)

&nbsp;

3）發出委託等待成交

- 以-500的價位發出限價買入指令，由於當前買價賣價分別位於330和340，所以委託狀態是“未成交”。僅當賣價低於-500時，才出發該限價單，已超價5美金，即-495去主動成交。
- 【日誌】元件顯示本次演算法即SpreadTaker_000004已經啟動，但由於價格沒有觸發到目標價位，演算法在迴圈讀秒中處於等待狀態；
- 【演算法】元件顯示其委託狀態為"未成交"，要結束演算法只需滑鼠雙擊【SpreadTaker_000004】單元格即可。

![](https://vnpy-community.oss-cn-shanghai.aliyuncs.com/forum_experience/yazhang/spread_trading/buy_en_mano_no_trade.png)

&nbsp;

4）撤銷委託

滑鼠雙擊完【SpreadTaker_000004】單元格後，在【日誌】元件可以看到演算法已經停止，【演算法】元件顯示委託狀態由“未成交”變成”已撤單“。

![](https://vnpy-community.oss-cn-shanghai.aliyuncs.com/forum_experience/yazhang/spread_trading/buy_en_mano_cancel.png)

&nbsp;

### 自動交易

目前，vnpy官方只提供一個價差策略BasicSpreadStrategy，策略邏輯相對簡單，即設定4個目標價位：

- 在價差合約的價格低位買入開倉（BUY），然後在接近均值時候賣出平倉（SELL）；
- 在合約價格高位賣出開倉（SHORT），然後在價格走低接近均值買入平倉（COVER）。

![](https://vnpy-community.oss-cn-shanghai.aliyuncs.com/forum_experience/yazhang/spread_trading/dibujo_spread.png)

&nbsp;

BasicSpreadStrategy策略繼承於SpreadStrategyTemplate，其策略邏輯主要在on_spread_data()函式上。執行邏輯是先檢測倉位：

- 若無倉位，分別發出買入開倉和賣出開倉委託，然後檢測若存在平倉委託，呼叫stop_algo()函式撤銷；
- 若持有多頭倉位，先發出賣出平倉委託，然後檢測若存在買入開倉委託，撤單處理；
- 若持有空頭倉位，先發出買入平倉委託，然後檢測若存在賣出開倉委託，撤單處理。

```
    def on_spread_data(self):
        """
        Callback when spread price is updated.
        """
        self.spread_pos = self.get_spread_pos()

        # No position
        if not self.spread_pos:
            # Start open algos
            if not self.buy_algoid:
                self.buy_algoid = self.start_long_algo(
                    self.buy_price, self.max_pos, self.payup, self.interval
                )

            if not self.short_algoid:
                self.short_algoid = self.start_short_algo(
                    self.short_price, self.max_pos, self.payup, self.interval
                )

            # Stop close algos
            if self.sell_algoid:
                self.stop_algo(self.sell_algoid)

            if self.cover_algoid:
                self.stop_algo(self.cover_algoid)

        # Long position
        elif self.spread_pos > 0:
            # Start sell close algo
            if not self.sell_algoid:
                self.sell_algoid = self.start_short_algo(
                    self.sell_price, self.spread_pos, self.payup, self.interval
                )

            # Stop buy open algo
            if self.buy_algoid:
                self.stop_algo(self.buy_algoid)

        # Short position
        elif self.spread_pos < 0:
            # Start cover close algo
            if not self.cover_algoid:
                self.cover_algoid = self.start_long_algo(
                    self.cover_price, abs(
                        self.spread_pos), self.payup, self.interval
                )

            # Stop short open algo
            if self.short_algoid:
                self.stop_algo(self.short_algoid)

        self.put_event()
```

由此可見，BasicSpreadStrategy策略邏輯是基於預先設定好的閾值來發出委託，只能處理相對簡單的均值迴歸情況，若價差均值並不是圍繞某個固定數值波動，或者它能夠持續走出趨勢，就需要更加複雜的策略，如價差的布林帶策略等等。這些更加個性化的策略，使用者可以基於SpreadStrategyTemplate策略模板自己實現。

現在展示價差交易模組，如何基於現有策略去建立策略例項來實現自動交易。由於其用法與CTA策略模組一樣，故使用者遷移成交較低。

1）新增策略例項

- 先選擇使用的策略：BasicSpreadStrategy；
- 點選【新增策略】按鈕，在彈出的介面中寫入相關引數；
- 【strategy_name】為使用者自定義的策略例項名稱，這裡是xbt_arb；
- 【spread_name】為用於交易的價差合約，這裡是xbt；
- 【buy_price】為買入開倉閾值，這裡是-500，即當價格跌破-500時，執行委託；
- 【sell_price】為賣出平倉閾值，這裡是-200，即當價格回升到-200時，執行委託；
- 【short_price】為賣出開倉閾值，這裡是500，即當價格上漲到500時，執行委託；
- 【cover_price】為買入平倉閾值，這裡是200，即當價格下跌到200時，執行委託；
- 【max_pos】為主動腿委託數量；
- 【payup】為超價的數值;
- 【interval】為時間間隔，即每隔一段時間，會發出委託；
- 最後，點選【新增】按鈕完成策略例項的建立。

![](https://vnpy-community.oss-cn-shanghai.aliyuncs.com/forum_experience/yazhang/spread_trading/add_strategy.png)

&nbsp;

2）啟動策略

- 建立好策略例項後，在【策略】元件會顯示該策略；
- 依次點選【初始化】和【啟動】按鈕後，在【日誌】元件中可以看到相關資訊的輸出；
- 【演算法】元件顯示，xbt_arb策略呼叫SpreadTaker演算法，分別在-500和500的位子上掛上買入和賣出委託；
- 由於實際價格沒有達到這2個閾值，故委託一直掛著，其委託狀態為"未成交"。

![](https://vnpy-community.oss-cn-shanghai.aliyuncs.com/forum_experience/yazhang/spread_trading/start_strategy.png)

&nbsp;

最後，若要停止策略，點選【停止】按鈕即可；【編輯】按鈕用於修改策略引數；【移除】按鈕用於移除該策略。
