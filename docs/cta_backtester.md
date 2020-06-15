# CTA回測模組
CTA回測模組是基於PyQt5和pyqtgraph的圖形化回測工具。啟動VN Trader後，在選單欄中點選“功能-> CTA回測”即可進入該圖形化回測介面，如下圖。CTA回測模組主要實現3個功能：歷史行情資料的下載、策略回測、引數優化、K線圖表買賣點展示。

![](https://vnpy-community.oss-cn-shanghai.aliyuncs.com/forum_experience/yazhang/cta_backtester/cta_backtester.png)

&nbsp;

## 載入啟動
進入圖形化回測介面“CTA回測”後，會立刻完成初始化工作：初始化回測引擎、初始化RQData客戶端。

```
    def init_engine(self):
        """"""
        self.write_log("初始化CTA回測引擎")

        self.backtesting_engine = BacktestingEngine()
        # Redirect log from backtesting engine outside.
        self.backtesting_engine.output = self.write_log

        self.write_log("策略檔案載入完成")

        self.init_rqdata()

    def init_rqdata(self):
        """
        Init RQData client.
        """
        result = rqdata_client.init()
        if result:
            self.write_log("RQData資料介面初始化成功")
```

&nbsp;


## 下載資料
在開始策略回測之前，必須保證資料庫內有充足的歷史資料。故vnpy提供了歷史資料一鍵下載的功能。

### RQData
RQData提供國內股票、ETF、期貨以及期權的歷史資料。
其下載資料功能主要是基於RQData的get_price()函式實現的。
```
get_price(
    order_book_ids, start_date='2013-01-04', end_date='2014-01-04',
    frequency='1d', fields=None, adjust_type='pre', skip_suspended =False,
    market='cn'
)
```


在使用前要保證RQData初始化完畢，然後填寫以下4個欄位資訊：
- 原生代碼：格式為合約品種+交易所，如IF88.CFFEX、rb88.SHFE；然後在底層通過RqdataClient的to_rq_symbol()函式轉換成符合RQData格式，對應RQData中get_price()函式的order_book_ids欄位。
- K線週期：可以填1m、1h、d、w，對應get_price()函式的frequency欄位。
- 開始日期：格式為yy/mm/dd，如2017/4/21，對應get_price()函式的start_date欄位。（點選視窗右側箭頭按鈕可改變日期大小）
- 結束日期：格式為yy/mm/dd，如2019/4/22，對應get_price()函式的end_date欄位。（點選視窗右側箭頭按鈕可改變日期大小）
  
填寫完欄位資訊後，點選下方“下載資料”按鈕啟動下載程式，下載成功如圖所示。


![](https://vnpy-community.oss-cn-shanghai.aliyuncs.com/forum_experience/yazhang/cta_backtester/data_loader.png)

&nbsp;

### IB

盈透證券提供外盤股票、期貨、期權的歷史資料。
下載前必須連線好IB介面，因為其下載資料功能主要是基於IbGateway類query_history()函式實現的。

```
    def query_history(self, req: HistoryRequest):
        """"""
        self.history_req = req

        self.reqid += 1

        ib_contract = Contract()
        ib_contract.conId = str(req.symbol)
        ib_contract.exchange = EXCHANGE_VT2IB[req.exchange]

        if req.end:
            end = req.end
            end_str = end.strftime("%Y%m%d %H:%M:%S")
        else:
            end = datetime.now()
            end_str = ""

        delta = end - req.start
        days = min(delta.days, 180)     # IB only provides 6-month data
        duration = f"{days} D"
        bar_size = INTERVAL_VT2IB[req.interval]

        if req.exchange == Exchange.IDEALPRO:
            bar_type = "MIDPOINT"
        else:
            bar_type = "TRADES"

        self.client.reqHistoricalData(
            self.reqid,
            ib_contract,
            end_str,
            duration,
            bar_size,
            bar_type,
            1,
            1,
            False,
            []
        )

        self.history_condition.acquire()    # Wait for async data return
        self.history_condition.wait()
        self.history_condition.release()

        history = self.history_buf
        self.history_buf = []       # Create new buffer list
        self.history_req = None

        return history
```
&nbsp;

### BITMEX

BITMEX交易所提供數字貨幣歷史資料。
由於模擬環境與實盤環境行情差異比較大，故需要用實盤賬號登入BIMEX介面來下載真實行情資料，其下載資料功能主要是基於BitmexGateway類query_history()函式實現的。

```
    def query_history(self, req: HistoryRequest):
        """"""
        if not self.check_rate_limit():
            return

        history = []
        count = 750
        start_time = req.start.isoformat()

        while True:
            # Create query params
            params = {
                "binSize": INTERVAL_VT2BITMEX[req.interval],
                "symbol": req.symbol,
                "count": count,
                "startTime": start_time
            }

            # Add end time if specified
            if req.end:
                params["endTime"] = req.end.isoformat()

            # Get response from server
            resp = self.request(
                "GET",
                "/trade/bucketed",
                params=params
            )

            # Break if request failed with other status code
            if resp.status_code // 100 != 2:
                msg = f"獲取歷史資料失敗，狀態碼：{resp.status_code}，資訊：{resp.text}"
                self.gateway.write_log(msg)
                break
            else:
                data = resp.json()
                if not data:
                    msg = f"獲取歷史資料為空，開始時間：{start_time}，數量：{count}"
                    break

                for d in data:
                    dt = datetime.strptime(
                        d["timestamp"], "%Y-%m-%dT%H:%M:%S.%fZ")
                    bar = BarData(
                        symbol=req.symbol,
                        exchange=req.exchange,
                        datetime=dt,
                        interval=req.interval,
                        volume=d["volume"],
                        open_price=d["open"],
                        high_price=d["high"],
                        low_price=d["low"],
                        close_price=d["close"],
                        gateway_name=self.gateway_name
                    )
                    history.append(bar)

                begin = data[0]["timestamp"]
                end = data[-1]["timestamp"]
                msg = f"獲取歷史資料成功，{req.symbol} - {req.interval.value}，{begin} - {end}"
                self.gateway.write_log(msg)

                # Break if total data count less than 750 (latest date collected)
                if len(data) < 750:
                    break

                # Update start time
                start_time = bar.datetime + TIMEDELTA_MAP[req.interval]

        return history
```

&nbsp;

## 策略回測
下載完歷史資料後，需要配置以下欄位：交易策略、手續費率、交易滑點、合約乘數、價格跳動、回測資金。
這些欄位主要對應BacktesterEngine類的run_backtesting函式。

若資料庫已存在歷史資料，無需重複下載，直接從本地資料庫中匯入資料進行回測。注意，vt_symbol的格式為品種程式碼.交易所的形式，如IF1908.CFFEX，匯入時會自動將其分割為品種和交易所兩部分

```
def run_backtesting(
    self, class_name: str, vt_symbol: str, interval: str, start: datetime, 
    end: datetime, rate: float, slippage: float, size: int, pricetick: float, 
    capital: int, setting: dict
)：
```


點選下方的“開始回測”按鈕可以開始回測：
首先會彈出如圖所示的引數配置視窗，用於調整策略引數。該設定對應的是run_backtesting()函式的setting字典。

![](https://vnpy-community.oss-cn-shanghai.aliyuncs.com/forum_experience/yazhang/cta_backtester/parameter_setting.png)



點選“確認”按鈕後開始執行回測，同時日誌介面會輸出相關資訊，如圖。

![](https://vnpy-community.oss-cn-shanghai.aliyuncs.com/forum_experience/yazhang/cta_backtester/backtesting_log.png)

回測完成後會顯示統計數字圖表。

&nbsp;

### 統計資料
用於顯示回測完成後的相關統計數值, 如結束資金、總收益率、夏普比率、收益回撤比。

![](https://vnpy-community.oss-cn-shanghai.aliyuncs.com/forum_experience/yazhang/cta_backtester/show_result.png)

&nbsp;

### 圖表分析
以下四個圖分別是代表賬號淨值、淨值回撤、每日盈虧、盈虧分佈。

![](https://vnpy-community.oss-cn-shanghai.aliyuncs.com/forum_experience/yazhang/cta_backtester/show_result_chat.png)


&nbsp;
### K線圖
K線圖是基於PyQtGraph開發的，整個模組由以下五大元件構成：

- BarManager：K線序列資料管理工具
- ChartItem：基礎圖形類，繼承實現後可以繪製K線、成交量、技術指標等
- DatetimeAxis：針對K線時間戳設計的定製座標軸
- ChartCursor：十字游標控制元件，用於顯示特定位置的資料細節
- ChartWidget：包含以上所有部分，提供單一函式入口的繪圖元件
  
在回測完畢後，點選“K線圖表”按鈕即可顯示歷史K線行情資料（預設1分鐘），並且標識有具體的買賣點位，如下圖。

![](https://vnpy-community.oss-cn-shanghai.aliyuncs.com/forum_experience/yazhang/cta_backtester/bar_chart.png)


&nbsp;

## 引數優化
vnpy提供2種引數優化的解決方案：窮舉演算法、遺傳演算法


&nbsp;

### 窮舉演算法

窮舉演算法原理：
- 輸入需要優化的引數名、優化區間、優化步進，以及優化目標。
```
    def add_parameter(
        self, name: str, start: float, end: float = None, step: float = None
    ):
        """"""
        if not end and not step:
            self.params[name] = [start]
            return

        if start >= end:
            print("引數優化起始點必須小於終止點")
            return

        if step <= 0:
            print("引數優化步進必須大於0")
            return

        value = start
        value_list = []

        while value <= end:
            value_list.append(value)
            value += step

        self.params[name] = value_list

    def set_target(self, target_name: str):
        """"""
        self.target_name = target_name
```

&nbsp;


- 形成全域性引數組合, 資料結構為[{key: value, key: value}, {key: value, key: value}]。
```
    def generate_setting(self):
        """"""
        keys = self.params.keys()
        values = self.params.values()
        products = list(product(*values))

        settings = []
        for p in products:
            setting = dict(zip(keys, p))
            settings.append(setting)

        return settings
```
&nbsp;


- 遍歷全域性中的每一個引數組合：遍歷的過程即執行一次策略回測，並且返回優化目標數值；然後根據目標數值排序，輸出優化結果。
```
    def run_optimization(self, optimization_setting: OptimizationSetting, output=True):
        """"""
        # Get optimization setting and target
        settings = optimization_setting.generate_setting()
        target_name = optimization_setting.target_name

        if not settings:
            self.output("優化引數組合為空，請檢查")
            return

        if not target_name:
            self.output("優化目標未設定，請檢查")
            return

        # Use multiprocessing pool for running backtesting with different setting
        pool = multiprocessing.Pool(multiprocessing.cpu_count())

        results = []
        for setting in settings:
            result = (pool.apply_async(optimize, (
                target_name,
                self.strategy_class,
                setting,
                self.vt_symbol,
                self.interval,
                self.start,
                self.rate,
                self.slippage,
                self.size,
                self.pricetick,
                self.capital,
                self.end,
                self.mode
            )))
            results.append(result)

        pool.close()
        pool.join()

        # Sort results and output
        result_values = [result.get() for result in results]
        result_values.sort(reverse=True, key=lambda result: result[1])

        if output:
            for value in result_values:
                msg = f"引數：{value[0]}, 目標：{value[1]}"
                self.output(msg)

        return result_values
```




注意：可以使用multiprocessing庫來建立多程序實現並行優化。例如：若使用者計算機是2核，優化時間為原來1/2；若計算機是10核，優化時間為原來1/10。

&nbsp;


窮舉演算法操作：

- 點選“引數優化”按鈕，會彈出“優化引數配置”視窗，用於設定優化目標（如最大化夏普比率、最大化收益回撤比）和設定需要優化的引數以及優化區間，如圖。
  
![](https://vnpy-community.oss-cn-shanghai.aliyuncs.com/forum_experience/yazhang/cta_backtester/optimize_setting.png)

- 設定好需要優化的引數後，點選“優化引數配置”視窗下方的“確認”按鈕開始進行呼叫CPU多核進行多程序並行優化，同時日誌會輸出相關資訊。
  
![](https://vnpy-community.oss-cn-shanghai.aliyuncs.com/forum_experience/yazhang/cta_backtester/optimize_log.png)

- 點選“優化結果”按鈕可以看出優化結果，如圖的引數組合是基於目標數值（夏普比率）由高到低的順序排列的。
  
![](https://vnpy-community.oss-cn-shanghai.aliyuncs.com/forum_experience/yazhang/cta_backtester/optimize_result.png)


&nbsp;

### 遺傳演算法

遺傳演算法原理：

- 輸入需要優化的引數名、優化區間、優化步進，以及優化目標；

- 形成全域性引數組合，該組合的資料結構是列表內鑲嵌元組，即\[[(key, value), (key, value)] , [(key, value), (key,value)]]，與窮舉演算法的全域性引數組合的資料結構不同。這樣做的目的是有利於引數間進行交叉互換和變異。
```
    def generate_setting_ga(self):
        """""" 
        settings_ga = []
        settings = self.generate_setting()     
        for d in settings:            
            param = [tuple(i) for i in d.items()]
            settings_ga.append(param)
        return settings_ga
```

&nbsp;


- 形成個體：呼叫random()函式隨機從全域性引數組合中獲取引數。
```
        def generate_parameter():
            """"""
            return random.choice(settings)
```

&nbsp;


- 定義個體變異規則: 即發生變異時，舊的個體完全被新的個體替代。
```
        def mutate_individual(individual, indpb):
            """"""
            size = len(individual)
            paramlist = generate_parameter()
            for i in range(size):
                if random.random() < indpb:
                    individual[i] = paramlist[i]
            return individual,
```

&nbsp;


- 定義評估函式：入參的是個體，即[(key, value), (key, value)]形式的引數組合，然後通過dict()轉化成setting字典，然後執行回測，輸出目標優化數值，如夏普比率、收益回撤比。(注意，修飾器@lru_cache作用是快取計算結果，避免遇到相同的輸入重複計算，大大降低執行遺傳演算法的時間)
```
@lru_cache(maxsize=1000000)
def _ga_optimize(parameter_values: tuple):
    """"""
    setting = dict(parameter_values)

    result = optimize(
        ga_target_name,
        ga_strategy_class,
        setting,
        ga_vt_symbol,
        ga_interval,
        ga_start,
        ga_rate,
        ga_slippage,
        ga_size,
        ga_pricetick,
        ga_capital,
        ga_end,
        ga_mode
    )
    return (result[1],)


def ga_optimize(parameter_values: list):
    """"""
    return _ga_optimize(tuple(parameter_values))
```

&nbsp;

- 執行遺傳演算法：呼叫deap庫的演算法引擎來執行遺傳演算法，其具體流程如下。
1）先定義優化方向，如夏普比率最大化；
2）然後隨機從全域性引數組合獲取個體，並形成族群；
3）對族群內所有個體進行評估（即執行回測），並且剔除表現不好個體；
4）剩下的個體會進行交叉或者變異，通過評估和篩選後形成新的族群；（到此為止是完整的一次種群迭代過程）；
5）多次迭代後，種群內差異性減少，整體適應性提高，最終輸出建議結果。該結果為帕累託解集，可以是1個或者多個引數組合。

注意：由於用到了@lru_cache, 迭代中後期的速度回提高非常多，因為很多重複的輸入都避免了再次的回測，直接在記憶體中查詢並且返回計算結果。
```
from deap import creator, base, tools, algorithms
creator.create("FitnessMax", base.Fitness, weights=(1.0,))
creator.create("Individual", list, fitness=creator.FitnessMax)
        ......
        # Set up genetic algorithem
        toolbox = base.Toolbox() 
        toolbox.register("individual", tools.initIterate, creator.Individual, generate_parameter)                          
        toolbox.register("population", tools.initRepeat, list, toolbox.individual)                                            
        toolbox.register("mate", tools.cxTwoPoint)                                               
        toolbox.register("mutate", mutate_individual, indpb=1)               
        toolbox.register("evaluate", ga_optimize)                                                
        toolbox.register("select", tools.selNSGA2)       

        total_size = len(settings)
        pop_size = population_size                      # number of individuals in each generation
        lambda_ = pop_size                              # number of children to produce at each generation
        mu = int(pop_size * 0.8)                        # number of individuals to select for the next generation

        cxpb = 0.95         # probability that an offspring is produced by crossover    
        mutpb = 1 - cxpb    # probability that an offspring is produced by mutation
        ngen = ngen_size    # number of generation
                
        pop = toolbox.population(pop_size)      
        hof = tools.ParetoFront()               # end result of pareto front

        stats = tools.Statistics(lambda ind: ind.fitness.values)
        np.set_printoptions(suppress=True)
        stats.register("mean", np.mean, axis=0)
        stats.register("std", np.std, axis=0)
        stats.register("min", np.min, axis=0)
        stats.register("max", np.max, axis=0)

        algorithms.eaMuPlusLambda(
            pop, 
            toolbox, 
            mu, 
            lambda_, 
            cxpb, 
            mutpb, 
            ngen, 
            stats,
            halloffame=hof
        )

        # Return result list
        results = []

        for parameter_values in hof:
            setting = dict(parameter_values)
            target_value = ga_optimize(parameter_values)[0]
            results.append((setting, target_value, {}))
        
        return results
```







