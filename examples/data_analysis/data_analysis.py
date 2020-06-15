from datetime import datetime
import warnings

import numpy as np
import pandas as pd
from pandas import DataFrame
import matplotlib.pyplot as plt
from statsmodels.stats.diagnostic import acorr_ljungbox
from statsmodels.tsa.stattools import adfuller as ADF
from statsmodels.graphics.tsaplots import plot_acf, plot_pacf
import talib

from vnpy.trader.constant import Exchange, Interval
from vnpy.trader.database import database_manager
warnings.filterwarnings("ignore")


class DataAnalysis:

    def __init__(self):
        """"""
        self.symbol = ""
        self.exchange = None
        self.interval = None
        self.start = None
        self.end = None
        self.rate = 0.0

        self.window_volatility = 20
        self.window_index = 20

        self.orignal = pd.DataFrame()

        self.index_1to1 = []
        self.index_2to2 = []
        self.index_3to1 = []
        self.index_2to1 = []
        self.index_4to1 = []
        self.intervals = []

        self.results = {}

    def load_history(
        self,
        symbol: str,
        exchange: Exchange,
        interval: Interval,
        start: datetime,
        end: datetime,
        rate: float = 0.0,
        index_1to1: list = None,
        index_2to2: list = None,
        index_3to1: list = None,
        index_2to1: list = None,
        index_4to1: list = None,
        window_index: int = 20,
        window_volatility: int = 20,

    ):
        """"""
        output("開始載入歷史資料")

        self.window_volatility = window_volatility
        self.window_index = window_index
        self.rate = rate
        self.index_1to1 = index_1to1
        self.index_2to2 = index_2to2
        self.index_3to1 = index_3to1
        self.index_2to1 = index_2to1
        self.index_4to1 = index_4to1

        # Load history data from database
        bars = database_manager.load_bar_data(
            symbol=symbol,
            exchange=exchange,
            interval=interval,
            start=start,
            end=end,

        )

        output(f"歷史資料載入完成，資料量：{len(bars)}")

        # Generate history data in DataFrame
        t = []
        o = []
        h = []
        l = []  # noqa
        c = []
        v = []

        for bar in bars:
            time = bar.datetime
            open_price = bar.open_price
            high_price = bar.high_price
            low_price = bar.low_price
            close_price = bar.close_price
            volume = bar.volume

            t.append(time)
            o.append(open_price)
            h.append(high_price)
            l.append(low_price)
            c.append(close_price)
            v.append(volume)

        self.orignal["open"] = o
        self.orignal["high"] = h
        self.orignal["low"] = l
        self.orignal["close"] = c
        self.orignal["volume"] = v
        self.orignal.index = t

    def base_analysis(self, df: DataFrame = None):
        """"""
        if df is None:
            df = self.orignal

        if df is None:
            output("資料為空，請輸入資料")

        close_price = df["close"]

        output("第一步:畫出行情圖，檢查資料斷點")

        close_price.plot(figsize=(20, 8), title="close_price")
        plt.show()

        random_test(close_price)
        stability_test(close_price)
        autocorrelation_test(close_price)

        self.relative_volatility_analysis(df)
        self.growth_analysis(df)

        self.calculate_index(df)

        return df

    def relative_volatility_analysis(self, df: DataFrame = None):
        """
        相對波動率
        """
        output("第五步：相對波動率分析")
        df["volatility"] = talib.ATR(
            np.array(df["high"]),
            np.array(df["low"]),
            np.array(df["close"]),
            self.window_volatility
        )

        df["fixed_cost"] = df["close"] * self.rate
        df["relative_vol"] = df["volatility"] - df["fixed_cost"]

        df["relative_vol"].plot(figsize=(20, 6), title="relative volatility")
        plt.show()

        df["relative_vol"].hist(bins=200, figsize=(20, 6), grid=False)
        plt.show()

        statitstic_info(df["relative_vol"])

    def growth_analysis(self, df: DataFrame = None):
        """
        百分比K線變化率
        """
        output("第六步：變化率分析")
        df["pre_close"] = df["close"].shift(1).fillna(0)
        df["g%"] = 100 * (df["close"] - df["pre_close"]) / df["close"]

        df["g%"].plot(figsize=(20, 6), title="growth", ylim=(-5, 5))
        plt.show()

        df["g%"].hist(bins=200, figsize=(20, 6), grid=False)
        plt.show()

        statitstic_info(df["g%"])

    def calculate_index(self, df: DataFrame = None):
        """"""
        output("第七步：計算相關技術指標，返回DataFrame\n")

        if self.index_1to1:
            for i in self.index_1to1:
                func = getattr(talib, i)
                df[i] = func(
                    np.array(df["close"]),
                    self.window_index
                )

        if self.index_3to1:
            for i in self.index_3to1:
                func = getattr(talib, i)
                df[i] = func(
                    np.array(df["high"]),
                    np.array(df["low"]),
                    np.array(df["close"]),
                    self.window_index
                )

        if self.index_2to2:
            for i in self.index_2to2:
                func = getattr(talib, i)
                result_down, result_up = func(
                    np.array(df["high"]),
                    np.array(df["low"]),
                    self.window_index
                )
                up = i + "_UP"
                down = i + "_DOWN"
                df[up] = result_up
                df[down] = result_down

        if self.index_2to1:
            for i in self.index_2to1:
                func = getattr(talib, i)
                df[i] = func(
                    np.array(df["high"]),
                    np.array(df["low"]),
                    self.window_index
                )

        if self.index_4to1:
            for i in self.index_4to1:
                func = getattr(talib, i)
                df[i] = func(
                    np.array(df["open"]),
                    np.array(df["high"]),
                    np.array(df["low"]),
                    np.array(df["close"]),
                )

        return df

    def multi_time_frame_analysis(self, intervals: list = None, df: DataFrame = None):
        """"""
        if not intervals:
            output("請輸入K線合成週期")
            return

        if df is None:
            df = self.orignal

        if df is None:
            output("請先載入資料")
            return

        for interval in intervals:
            output("------------------------------------------------")
            output(f"合成{interval}週期K先並開始資料分析")

            data = pd.DataFrame()
            data["open"] = df["open"].resample(interval, how="first")
            data["high"] = df["high"].resample(interval, how="max")
            data["low"] = df["low"].resample(interval, how="min")
            data["close"] = df["close"].resample(interval, how="last")
            data["volume"] = df["volume"].resample(interval, how="sum")

            result = self.base_analysis(data)
            self.results[interval] = result

    def show_chart(self, data, boll_wide):
        """"""
        data["boll_up"] = data["SMA"] + data["STDDEV"] * boll_wide
        data["boll_down"] = data["SMA"] - data["STDDEV"] * boll_wide

        up_signal = []
        down_signal = []
        len_data = len(data["close"])
        for i in range(1, len_data):
            if data.iloc[i]["close"] > data.iloc[i]["boll_up"]and data.iloc[i - 1]["close"] < data.iloc[i - 1]["boll_up"]:
                up_signal.append(i)

            elif data.iloc[i]["close"] < data.iloc[i]["boll_down"] and data.iloc[i - 1]["close"] > data.iloc[i - 1]["boll_down"]:
                down_signal.append(i)

        plt.figure(figsize=(20, 8))
        close = data["close"]
        plt.plot(close, lw=1)
        plt.plot(close, '^', markersize=5, color='r',
                 label='UP signal', markevery=up_signal)
        plt.plot(close, 'v', markersize=5, color='g',
                 label='DOWN signal', markevery=down_signal)
        plt.plot(data["boll_up"], lw=0.5, color="r")
        plt.plot(data["boll_down"], lw=0.5, color="g")
        plt.legend()
        plt.show()

        data["ATR"].plot(figsize=(20, 3), title="ATR")
        plt.show()


def random_test(close_price):
    """"""
    acorr_result = acorr_ljungbox(close_price, lags=1)
    p_value = acorr_result[1]
    if p_value < 0.05:
        output("第二步：隨機性檢驗：非純隨機性")
    else:
        output("第二步：隨機性檢驗：純隨機性")
    output(f"白噪聲檢驗結果:{acorr_result}\n")


def stability_test(close_price):
    """"""
    statitstic = ADF(close_price)
    t_s = statitstic[1]
    t_c = statitstic[4]["10%"]

    if t_s > t_c:
        output("第三步：平穩性檢驗：存在單位根，時間序列不平穩")
    else:
        output("第三步：平穩性檢驗：不存在單位根，時間序列平穩")

    output(f"ADF檢驗結果：{statitstic}\n")


def autocorrelation_test(close_price):
    """"""
    output("第四步：畫出自相關性圖，觀察自相關特性")

    plot_acf(close_price, lags=60)
    plt.show()

    plot_pacf(close_price, lags=60).show()
    plt.show()


def statitstic_info(df):
    """"""
    mean = round(df.mean(), 4)
    median = round(df.median(), 4)
    output(f"樣本平均數：{mean}, 中位數: {median}")

    skew = round(df.skew(), 4)
    kurt = round(df.kurt(), 4)

    if skew == 0:
        skew_attribute = "對稱分佈"
    elif skew > 0:
        skew_attribute = "分佈偏左"
    else:
        skew_attribute = "分佈偏右"

    if kurt == 0:
        kurt_attribute = "正態分佈"
    elif kurt > 0:
        kurt_attribute = "分佈陡峭"
    else:
        kurt_attribute = "分佈平緩"

    output(f"偏度為：{skew}，屬於{skew_attribute}；峰度為：{kurt}，屬於{kurt_attribute}\n")


def output(msg):
    """
    Output message of backtesting engine.
    """
    print(f"{datetime.now()}\t{msg}")
