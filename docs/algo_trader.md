# 演算法交易
演算法交易可以用於把巨型單子拆分成一個個小單，能夠有效降低交易成本，衝擊成本等（冰山演算法、狙擊手演算法)；也可以在設定的閾值內進行高拋低吸操作(網格演算法、套利演算法）。

&nbsp;

## 模組構成

演算法交易模組主要由4部分構成，如下圖：

- engine：定義了演算法引擎，其中包括：引擎初始化、儲存/移除/載入演算法配置、啟動演算法、停止演算法、訂閱行情、掛撤單等。
- template：定義了交易演算法模板，具體的演算法示例，如冰山演算法，都需要繼承於該模板。
- algos：具體的交易演算法示例。使用者基於演算法模板和官方提供是演算法示例，可以自己搭建新的演算法。
- ui：基於PyQt5的GUI圖形應用。

![](https://vnpy-community.oss-cn-shanghai.aliyuncs.com/forum_experience/yazhang/algo_trader/algo_trader_document.png)

&nbsp;

## 基本操作

在VN Trader的選單欄中點選“功能”—>“演算法交易”即可開啟如圖演算法交易模組視窗，如下圖。

演算法交易模組有2部分構成：
- 委託交易，用於啟動演算法交易；
- 資料監控，用於監控演算法交易執行情況，並且能夠手動停止演算法。

![](https://vnpy-community.oss-cn-shanghai.aliyuncs.com/forum_experience/yazhang/algo_trader/algo_trader_all_section.png)

&nbsp;

### 委託交易

下面以時間加權平均演算法為例，具體介紹如下圖委託交易功能選項。
- 演算法：目前提供了5種交易演算法：時間加權平均演算法、冰山演算法、狙擊手演算法、條件委託、最優限價；
- 原生代碼：vt_symbol格式，如AAPL.SMART, 用於演算法交易組建訂閱行情和委託交易；
- 方向：做多或者做空；
- 價格：委託下單的價格；
- 數量：委託的總數量，需要拆分成小單進行交易；
- 執行時間：執行改演算法交易的總時間，以秒為單位；
- 每輪間隔：每隔一段時間（秒）進行委託下單操作；
- 啟動演算法：設定好演算法配置後，用於立刻執行演算法交易。

所以，該演算法執行的任務如下：通過時間加權平均演算法，買入10000股AAPL（美股），執行價格為180美金，執行時間為600秒，間隔為6秒；即每隔6秒鐘，當買一價少於等於180時，以180的價格買入100股AAPL，買入操作分割成100次。

![](https://vnpy-community.oss-cn-shanghai.aliyuncs.com/forum_experience/yazhang/algo_trader/trading_section.png)

交易配置可以儲存在json檔案，這樣每次開啟演算法交易模組就不用重複輸入配置。其操作是在“演算法名稱”選項輸入該演算法設定命名，然後點選下方"儲存設定”按鈕。儲存的json檔案在C:\Users\Administrator\\.vntrader資料夾的algo_trading_setting.json中，如圖。

![](https://vnpy-community.oss-cn-shanghai.aliyuncs.com/forum_experience/yazhang/algo_trader/setting.png)

委託交易介面最下方的“全部停止”按鈕用於一鍵停止所有執行中的演算法交易。

&nbsp;

### 資料監控

資料監控由4個部分構成。

- 活動元件：顯示正在執行的演算法交易，包括：演算法名稱、引數、狀態。最右邊的“停止”按鈕用於手動停止執行中的演算法。

![](https://vnpy-community.oss-cn-shanghai.aliyuncs.com/forum_experience/yazhang/algo_trader/action.png)

&nbsp;

- 歷史委託元件：顯示已完成的演算法交易，同樣包括：演算法名稱、引數、狀態。

![](https://vnpy-community.oss-cn-shanghai.aliyuncs.com/forum_experience/yazhang/algo_trader/final.png)

&nbsp;

- 日誌元件：顯示啟動、停止、完成演算法的相關日誌資訊。在開啟演算法交易模組後，會進行初始化，故日誌上會首先顯示“演算法交易引擎啟動”和“演算法配置載入成功”。

![](https://vnpy-community.oss-cn-shanghai.aliyuncs.com/forum_experience/yazhang/algo_trader/log_section.png)

&nbsp;

- 配置元件：用於載入algo_trading_setting.json的配置資訊，並且以圖形化介面顯示出來。
使用者可以點選“使用”按鈕立刻讀取配置資訊，並顯示在委託交易介面上，點選“啟動演算法”即可開始進行交易；
使用者也可以點選“移除”按鈕來移除該演算法配置，同步更新到json檔案內。

![](https://vnpy-community.oss-cn-shanghai.aliyuncs.com/forum_experience/yazhang/algo_trader/setting_section.png)

&nbsp;

## 演算法示例


### 直接委託演算法

直接發出新的委託（限價單、停止單、市價單）

```
    def on_tick(self, tick: TickData):
        """"""
        if not self.vt_orderid:
            if self.direction == Direction.LONG:
                self.vt_orderid = self.buy(
                    self.vt_symbol,
                    self.price,
                    self.volume,
                    self.order_type,
                    self.offset
                )
                
            else:
                self.vt_orderid = self.sell(
                    self.vt_symbol,
                    self.price,
                    self.volume,
                    self.order_type,
                    self.offset
                )
        self.put_variables_event()
```

&nbsp;

### 時間加權平均演算法

- 將委託數量平均分佈在某個時間區域內；
- 每隔一段時間用指定的價格掛出買單（或者賣單）。
- 買入情況：買一價低於目標價格時，發出委託，委託數量在剩餘委託量與委託分割量中取最小值。
- 賣出情況：賣一價高於目標價格時，發出委託，委託數量在剩餘委託量與委託分割量中取最小值。

```
    def on_timer(self):
        """"""
        self.timer_count += 1
        self.total_count += 1
        self.put_variables_event()

        if self.total_count >= self.time:
            self.write_log("執行時間已結束，停止演算法")
            self.stop()
            return

        if self.timer_count < self.interval:
            return
        self.timer_count = 0

        tick = self.get_tick(self.vt_symbol)
        if not tick:
            return

        self.cancel_all()

        left_volume = self.volume - self.traded
        order_volume = min(self.order_volume, left_volume)

        if self.direction == Direction.LONG:
            if tick.ask_price_1 <= self.price:
                self.buy(self.vt_symbol, self.price,
                         order_volume, offset=self.offset)
        else:
            if tick.bid_price_1 >= self.price:
                self.sell(self.vt_symbol, self.price,
                          order_volume, offset=self.offset)
```

&nbsp;

### 冰山演算法

- 在某個價位掛單，但是隻掛一部分，直到全部成交。
- 買入情況：先檢查撤單：最新Tick賣一價低於目標價格，執行撤單；若無活動委託，發出委託：委託數量在剩餘委託量與掛出委託量中取最小值。
- 賣出情況：先檢查撤單：最新Tick買一價高於目標價格，執行撤單；若無活動委託，發出委託：委託數量在剩餘委託量與掛出委託量中取最小值。

```
    def on_timer(self):
        """"""
        self.timer_count += 1

        if self.timer_count < self.interval:
            self.put_variables_event()
            return

        self.timer_count = 0

        contract = self.get_contract(self.vt_symbol)
        if not contract:
            return

        # If order already finished, just send new order
        if not self.vt_orderid:
            order_volume = self.volume - self.traded
            order_volume = min(order_volume, self.display_volume)

            if self.direction == Direction.LONG:
                self.vt_orderid = self.buy(
                    self.vt_symbol,
                    self.price,
                    order_volume,
                    offset=self.offset
                )
            else:
                self.vt_orderid = self.sell(
                    self.vt_symbol,
                    self.price,
                    order_volume,
                    offset=self.offset
                )
        # Otherwise check for cancel
        else:
            if self.direction == Direction.LONG:
                if self.last_tick.ask_price_1 <= self.price:
                    self.cancel_order(self.vt_orderid)
                    self.vt_orderid = ""
                    self.write_log(u"最新Tick賣一價，低於買入委託價格，之前委託可能丟失，強制撤單")
            else:
                if self.last_tick.bid_price_1 >= self.price:
                    self.cancel_order(self.vt_orderid)
                    self.vt_orderid = ""
                    self.write_log(u"最新Tick買一價，高於賣出委託價格，之前委託可能丟失，強制撤單")

        self.put_variables_event()
```

&nbsp;

### 狙擊手演算法

- 監控最新tick推送的行情，發現好的價格立刻報價成交。
- 買入情況：最新Tick賣一價低於目標價格時，發出委託，委託數量在剩餘委託量與賣一量中取最小值。
- 賣出情況：最新Tick買一價高於目標價格時，發出委託，委託數量在剩餘委託量與買一量中取最小值。

```
    def on_tick(self, tick: TickData):
        """"""
        if self.vt_orderid:
            self.cancel_all()
            return

        if self.direction == Direction.LONG:
            if tick.ask_price_1 <= self.price:
                order_volume = self.volume - self.traded
                order_volume = min(order_volume, tick.ask_volume_1)

                self.vt_orderid = self.buy(
                    self.vt_symbol,
                    self.price,
                    order_volume,
                    offset=self.offset
                )
        else:
            if tick.bid_price_1 >= self.price:
                order_volume = self.volume - self.traded
                order_volume = min(order_volume, tick.bid_volume_1)

                self.vt_orderid = self.sell(
                    self.vt_symbol,
                    self.price,
                    order_volume,
                    offset=self.offset
                )

        self.put_variables_event()
```

&nbsp;

### 條件委託演算法

- 監控最新tick推送的行情，發現行情突破立刻報價成交。
- 買入情況：Tick最新價高於目標價格時，發出委託，委託價為目標價格加上超價。
- 賣出情況：Tick最新價低於目標價格時，發出委託，委託價為目標價格減去超價。

```
    def on_tick(self, tick: TickData):
        """"""
        if self.vt_orderid:
            return

        if self.direction == Direction.LONG:
            if tick.last_price >= self.stop_price:
                price = self.stop_price + self.price_add

                if tick.limit_up:
                    price = min(price, tick.limit_up)

                self.vt_orderid = self.buy(
                    self.vt_symbol,
                    price,
                    self.volume,
                    offset=self.offset
                )
                self.write_log(f"停止單已觸發，程式碼：{self.vt_symbol}，方向：{self.direction}, 價格：{self.stop_price}，數量：{self.volume}，開平：{self.offset}")                   

        else:
            if tick.last_price <= self.stop_price:
                price = self.stop_price - self.price_add
                
                if tick.limit_down:
                    price = max(price, tick.limit_down)

                self.vt_orderid = self.buy(
                    self.vt_symbol,
                    price,
                    self.volume,
                    offset=self.offset
                )
                self.write_log(f"停止單已觸發，程式碼：{self.vt_symbol}，方向：{self.direction}, 價格：{self.stop_price}，數量：{self.volume}，開平：{self.offset}") 

        self.put_variables_event()
```

&nbsp;

### 最優限價演算法

- 監控最新tick推送的行情，發現好的價格立刻報價成交。
- 買入情況：先檢查撤單：最新Tick買一價不等於目標價格時，執行撤單；若無活動委託，發出委託：委託價格為最新Tick買一價，委託數量為剩餘委託量。
- 賣出情況：先檢查撤單：最新Tick買一價不等於目標價格時，執行撤單；若無活動委託，發出委託：委託價格為最新Tick賣一價，委託數量為剩餘委託量。

```
    def on_tick(self, tick: TickData):
        """"""
        self.last_tick = tick

        if self.direction == Direction.LONG:
            if not self.vt_orderid:
                self.buy_best_limit()
            elif self.order_price != self.last_tick.bid_price_1:
                self.cancel_all()
        else:
            if not self.vt_orderid:
                self.sell_best_limit()
            elif self.order_price != self.last_tick.ask_price_1:
                self.cancel_all()

        self.put_variables_event()

    def buy_best_limit(self):
        """"""
        order_volume = self.volume - self.traded
        self.order_price = self.last_tick.bid_price_1
        self.vt_orderid = self.buy(
            self.vt_symbol,
            self.order_price,
            order_volume,
            offset=self.offset
        )        

    def sell_best_limit(self):
        """"""
        order_volume = self.volume - self.traded
        self.order_price = self.last_tick.ask_price_1
        self.vt_orderid = self.sell(
            self.vt_symbol,
            self.order_price,
            order_volume,
            offset=self.offset
        ) 
```

&nbsp;

### 網格演算法

- 每隔一段時間檢查委託情況，若有委託則先清空。
- 基於使用者設定的價格步進（即網格）計算目標距離，目標距離=（目標價格- 當前價格）/價格步進，故當前價格低於目標價格，目標距離為正，方向為買入；當前價格高於目標價格，目標距離為負，方向為賣出。（高拋低吸概念）
- 計算目標倉位，目標倉位= 取整後的目標距離 * 委託數量步進。注意賣賣方向取整的方式是不同的：買入方向要向下取整math.floor()，如目標距離為1.6，取1；賣出方向要向上取整，如目標距離為-1.6，取-1。
- 計算具體委託倉位：若目標買入倉位大於當前倉位，執行買入操作；若目標賣出倉位低於當前倉位，執行賣出操作。
- 為了能夠快速成交，買入情況是基於ask price計算，賣出情況是基於bid price計算。


```
    def on_timer(self):
        """"""
        if not self.last_tick:
            return

        self.timer_count += 1
        if self.timer_count < self.interval:
            self.put_variables_event()
            return        
        self.timer_count = 0
        
        if self.vt_orderid:
            self.cancel_all()        

        # Calculate target volume to buy
        target_buy_distance = (self.price - self.last_tick.ask_price_1) / self.step_price
        target_buy_position = math.floor(target_buy_distance) * self.step_volume
        target_buy_volume = target_buy_position - self.last_pos

        # Buy when price dropping
        if target_buy_volume > 0:
            self.vt_orderid = self.buy(
                self.vt_symbol,
                self.last_tick.ask_price_1,
                min(target_buy_volume, self.last_tick.ask_volume_1)
            )
        
        # Calculate target volume to sell
        target_sell_distance = (self.price - self.last_tick.bid_price_1) / self.step_price
        target_sell_position = math.ceil(target_sell_distance) * self.step_volume
        target_sell_volume = self.last_pos - target_sell_position

        # Sell when price rising
        if target_sell_volume > 0:
            self.vt_orderid = self.sell(
                self.vt_symbol,
                self.last_tick.bid_price_1,
                min(target_sell_volume, self.last_tick.bid_volume_1)
            )
```

&nbsp;

### 套利演算法

- 每隔一段時間檢查委託情況，若有委託則先清空；若主動腿還持有淨持倉，通過被動腿成交來對衝。
- 計算價差spread_bid_price 和 spread_ask_price, 以及對應的委託數量
- 賣出情況：主動腿價格相對被動腿上漲，其價差spread_bid_price大於spread_up時，觸發買入訊號
- 買入情況：主動腿價格相對被動腿下跌，其價差spread_ask_price小於 - spread_down(spread_down預設設定為正數)時，觸發賣出訊號
- 在買賣訊號判斷加入最大持倉的限制，其作用是避免持倉過多導致保證金不足或者直接被交易所懲罰性強平；而且隨著價差持續波動，主動腿持倉可以從0 -> 10 -> 0 -> -10 -> 0,從而實現平倉獲利離場。


```
    def on_timer(self):
        """"""
        self.timer_count += 1
        if self.timer_count < self.interval:
            self.put_variables_event()
            return
        self.timer_count = 0

        if self.active_vt_orderid or self.passive_vt_orderid:
            self.cancel_all()
            return
        
        if self.net_pos:
            self.hedge()
            return
      
        active_tick = self.get_tick(self.active_vt_symbol)
        passive_tick = self.get_tick(self.passive_vt_symbol)
        if not active_tick or not passive_tick:
            return

        # Calculate spread
        spread_bid_price = active_tick.bid_price_1 - passive_tick.ask_price_1
        spread_ask_price = active_tick.ask_price_1 - passive_tick.bid_price_1

        spread_bid_volume = min(active_tick.bid_volume_1, passive_tick.ask_volume_1)
        spread_ask_volume = min(active_tick.ask_volume_1, passive_tick.bid_volume_1)

        # Sell condition      
        if spread_bid_price > self.spread_up:
            if self.acum_pos <= -self.max_pos:
                return
            else:
                self.active_vt_orderid = self.sell(
                    self.active_vt_symbol,
                    active_tick.bid_price_1,
                    spread_bid_volume               
                )

        # Buy condition
        elif spread_ask_price < -self.spread_down:
            if self.acum_pos >= self.max_pos:
                return
            else:
                self.active_vt_orderid = self.buy(
                    self.active_vt_symbol,
                    active_tick.ask_price_1,
                    spread_ask_volume
                )
        self.put_variables_event()
    
    def hedge(self):
        """"""
        tick = self.get_tick(self.passive_vt_symbol)
        volume = abs(self.net_pos)

        if self.net_pos > 0:
            self.passive_vt_orderid = self.sell(
                self.passive_vt_symbol,
                tick.bid_price_5,
                volume
            )
        elif self.net_pos < 0:
            self.passive_vt_orderid = self.buy(
                self.passive_vt_symbol,
                tick.ask_price_5,
                volume
            )

    def on_trade(self, trade: TradeData):
        """"""
        # Update net position volume
        if trade.direction == Direction.LONG:
            self.net_pos += trade.volume
        else:
            self.net_pos -= trade.volume

        # Update active symbol position           
        if trade.vt_symbol == self.active_vt_symbol:
            if trade.direction == Direction.LONG:
                self.acum_pos += trade.volume
            else:
                self.acum_pos -= trade.volume

        # Hedge if active symbol traded     
        if trade.vt_symbol == self.active_vt_symbol:
            self.hedge()
        
        self.put_variables_event()

```