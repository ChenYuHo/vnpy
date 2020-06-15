# 行情記錄
行情記錄模組用於實時行情的收錄：
- 連線上介面後並且啟動行情記錄模組；
- 通過本地合約(vt_symbol)新增記錄任務；
- 後臺會自動呼叫行情API介面的suscribe()函式自動訂閱行情；
- 行情資訊通過database_manager模組的save_bar_data()函式/save_tick_data()函式載入到資料庫中。
  
注意：目前vnpy支援的資料庫為SQLite/ MySQL/ PostgreSQL/ MongoDB。其在VnTrader的選單欄選擇“配置”進入“全域性配置”介面來選擇資料庫(預設為SQLite), 或者在使用者目錄下的.vntrader/vt_setting.json裡面直接配置。若使用者使用MongoDB，則行情記錄資料直接載入到MongoDB中。

&nbsp;



## 載入啟動
進入VN Trader後，首先登陸介面，如連線CTP；然後在選單欄中點選“功能”->"行情記錄“後，會彈出行情記錄視窗，如圖。
![](https://vnpy-community.oss-cn-shanghai.aliyuncs.com/forum_experience/yazhang/data_recoder/datarecoder.png)

此時行情記錄模組的啟動狀態為True，會啟動while迴圈，可以新增任務實現實時行情記錄。
```
    def start(self):
        """"""
        self.active = True
        self.thread.start()

    def run(self):
        """"""
        while self.active:
            try:
                task = self.queue.get(timeout=1)
                task_type, data = task

                if task_type == "tick":
                    database_manager.save_tick_data([data])
                elif task_type == "bar":
                    database_manager.save_bar_data([data])

            except Empty:
                continue
```

&nbsp;

## 開始收錄

- 在“原生代碼”選擇輸入需要訂閱的行情，如rb1905.SHFE；
- 然後點選後邊“K線記錄”或者“Tick記錄”中的“新增”選項，會把記錄特定品種任務新增到data_recorder_setting.json上，並且顯示到“K線記錄列表”或者“Tick記錄列表”中，如圖。
- 通過queue.put()與queue.get()非同步完成收錄行情資訊任務。

![](https://vnpy-community.oss-cn-shanghai.aliyuncs.com/forum_experience/yazhang/data_recoder/start.png)

&nbsp;

下面介紹行情收錄的具體原理：若無合約記錄的歷史，使用者需要先新增行情記錄任務，如連線CTP介面後記錄rb1905.SHFE的tick資料，然後呼叫add_tick_recording()函式執行下面工作：
1) 先建立tick_recordings字典；
2) 呼叫介面的suscribe()函式訂閱行情；
3) 儲存該tick_recordings字典到json檔案上；
4) 推送行情記錄事件。

```
    def add_tick_recording(self, vt_symbol: str):
        """"""
        if vt_symbol in self.tick_recordings:
            self.write_log(f"已在Tick記錄列表中：{vt_symbol}")
            return

        contract = self.main_engine.get_contract(vt_symbol)
        if not contract:
            self.write_log(f"找不到合約：{vt_symbol}")
            return

        self.tick_recordings[vt_symbol] = {}
            "symbol": contract.symbol,
            "exchange": contract.exchange.value,
            "gateway_name": contract.gateway_name
        }

        self.subscribe(contract)
        self.save_setting()
        self.put_event()

        self.write_log(f"新增Tick記錄成功：{vt_symbol}")
```

下面對add_tick_recording()函式裡面呼叫的子函式進行擴充套件：

### 訂閱行情

呼叫main_engine的suscribe()函式來訂閱行情，需要填入的資訊為symbol、exchange、gateway_name
```
    def subscribe(self, contract: ContractData):
        """"""
        req = SubscribeRequest(
            symbol=contract.symbol,
            exchange=contract.exchange
        )
        self.main_engine.subscribe(req, contract.gateway_name)
```

&nbsp;

### 將訂閱資訊儲存到json檔案

- 主要把tick_recordings或者bar_recordings通過save_json()函式儲存到C:\Users\Administrator\\.vntrader資料夾內的data_recorder_setting.json上。
- 該json檔案用於存放行情記錄的任務，當每次啟動行情模組後，會呼叫load_setting()函式來得到tick_recordings和bar_recordings字典，進而開始記錄的任務。
```
setting_filename = "data_recorder_setting.json"
    def save_setting(self):
        """"""
        setting = {
            "tick": self.tick_recordings,
            "bar": self.bar_recordings
        }
        save_json(self.setting_filename, setting)

    def load_setting(self):
        """"""
        setting = load_json(self.setting_filename)
        self.tick_recordings = setting.get("tick", {})
        self.bar_recordings = setting.get("bar", {})        
```

&nbsp;

### 推送行情記錄事件

- 建立行情記錄列表tick_symbols和bar_symbols，並且快取在data字典裡；
- 建立evnte物件，其型別是EVENT_RECORDER_UPDATE, 內容是data字典；
- 呼叫event_engine的put()函式推送event事件。

```
    def put_event(self):
        """"""
        tick_symbols = list(self.tick_recordings.keys())
        tick_symbols.sort()

        bar_symbols = list(self.bar_recordings.keys())
        bar_symbols.sort()

        data = {
            "tick": tick_symbols,
            "bar": bar_symbols
        }

        event = Event(
            EVENT_RECORDER_UPDATE,
            data
        )
        self.event_engine.put(event)
```

&nbsp;

### 註冊行情記錄事件

register_event()函式分別註冊2種事件：EVENT_CONTRACT、EVENT_TICK
- EVENT_CONTRACT事件，呼叫的是process_contract_event()函式: 從tick_recordings和bar_recordings字典獲取需要訂閱的合約品種；然後使用subscribe()函式進行訂閱行情。
- EVENT_TICK事件，呼叫的是process_tick_event()函式：從tick_recordings和bar_recordings字典獲取需要訂閱的合約品種；然後使用record_tick()和record_bar()函式，把行情記錄任務推送到queue佇列中等待執行。

```
    def register_event(self):
        """"""
        self.event_engine.register(EVENT_TICK, self.process_tick_event)
        self.event_engine.register(EVENT_CONTRACT, self.process_contract_event)

    def process_tick_event(self, event: Event):
        """"""
        tick = event.data

        if tick.vt_symbol in self.tick_recordings:
            self.record_tick(tick)

        if tick.vt_symbol in self.bar_recordings:
            bg = self.get_bar_generator(tick.vt_symbol)
            bg.update_tick(tick)

    def process_contract_event(self, event: Event):
        """"""
        contract = event.data
        vt_symbol = contract.vt_symbol

        if (vt_symbol in self.tick_recordings or vt_symbol in self.bar_recordings):
            self.subscribe(contract)

    def record_tick(self, tick: TickData):
        """"""
        task = ("tick", copy(tick))
        self.queue.put(task)

    def record_bar(self, bar: BarData):
        """"""
        task = ("bar", copy(bar))
        self.queue.put(task)

    def get_bar_generator(self, vt_symbol: str):
        """"""
        bg = self.bar_generators.get(vt_symbol, None)

        if not bg:
            bg = BarGenerator(self.record_bar)
            self.bar_generators[vt_symbol] = bg

        return bg
```

&nbsp;

### 執行記錄行情任務

在while迴圈中，從queue佇列讀取任務，呼叫save_tick_data()或者save_bar_data()函式來記錄資料，並且載入到資料庫中。
```
    def run(self):
        """"""
        while self.active:
            try:
                task = self.queue.get(timeout=1)
                task_type, data = task

                if task_type == "tick":
                    database_manager.save_tick_data([data])
                elif task_type == "bar":
                    database_manager.save_bar_data([data])

            except Empty:
                continue
```

&nbsp;




## 移除記錄

移除記錄操作：輸入需要移除合約品種的原生代碼，如rb1905.SHFE。該原生代碼必須在“Tick記錄列表” 或者“K線記錄列表”中。若要移除Tick記錄，只需在”Tick記錄“那一欄上點選”移除“按鈕即可。

下面展示程式碼運作原理：

- 從tick_recordings字典移除vt_symbol
- 呼叫save_setting()函式儲存json配置檔案
- 推送最新的tick_recordings字典來繼續記錄行情，原來移除合約品種不再記錄。
```
    def remove_tick_recording(self, vt_symbol: str):
        """"""
        if vt_symbol not in self.tick_recordings:
            self.write_log(f"不在Tick記錄列表中：{vt_symbol}")
            return

        self.tick_recordings.pop(vt_symbol)
        self.save_setting()
        self.put_event()

        self.write_log(f"移除Tick記錄成功：{vt_symbol}")
```

&nbsp;

## 停止記錄

停止記錄操作：只需手動關閉行情記錄模組視窗就停止記錄行情。

- 記錄行情狀態改為False, 停止while迴圈；
- 呼叫join()函式關掉執行緒。

```
    def close(self):
        """"""
        self.active = False

        if self.thread.isAlive():
            self.thread.join()
```