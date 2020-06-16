# By Traders, For Traders.

<p align="center">
  <img src ="https://vnpy.oss-cn-shanghai.aliyuncs.com/vnpy-logo.png"/>
</p>

<p align="center">
    <img src ="https://img.shields.io/badge/version-2.1.3-blueviolet.svg"/>
    <img src ="https://img.shields.io/badge/platform-windows|linux|macos-yellow.svg"/>
    <img src ="https://img.shields.io/badge/python-3.7-blue.svg" />
    <img src ="https://img.shields.io/github/workflow/status/vnpy/vnpy/Python%20application/master"/>
    <img src ="https://img.shields.io/github/license/vnpy/vnpy.svg?color=orange"/>
</p>

vn.py是一套基於Python的開源量化交易系統開發框架，於2015年1月正式釋出，在開源社群6年持續不斷的貢獻下一步步成長為全功能量化交易平臺，目前國內外金融機構使用者已經超過500家，包括：私募基金、證券自營和資管、期貨資管和子公司、高校研究機構、自營交易公司、交易所、Token Fund等。

全新的《vn.py全實戰進階》系列線上課程，已經在官方微信公眾號[**vnpy-community**]上線，覆蓋CTA策略（已完成）、期權波動率交易（更新中）等內容。購買請掃描下方二維碼關注後，點選選單欄的【進階課程】按鈕即可：

<p align="center">
  <img src ="https://vnpy.oss-cn-shanghai.aliyuncs.com/vnpy_qr.jpg"/>
</p>

在使用vn.py進行二次開發（策略、模組等）的過程中有任何疑問，請檢視[**vn.py專案文件**](https://www.vnpy.com/docs/cn/index.html)，如果無法解決請前往[**官方社群論壇**](https://www.vnpy.com/forum/)的【提問求助】板塊尋求幫助，也歡迎在【經驗分享】板塊分享你的使用心得！

針對vn.py的金融機構使用者，建立了一個專門的【vn.py機構使用者群】（QQ群號：676499931），主要分享機構應用方面相關的問題，如：銀行間市場接入、資管O32系統、分散式部署等內容。請注意本群只對金融機構使用者開放，加群時請註明：姓名-機構-部門。

## 功能特點

1. 全功能量化交易平臺（vnpy.trader），整合了多種交易介面，並針對具體策略演算法和功能開發提供了簡潔易用的API，用於快速構建交易員所需的量化交易應用。

2. 覆蓋國內外所有交易品種的交易介面（vnpy.gateway）：

    * 國內市場

        * CTP（ctp）：國內期貨、期權

        * CTP Mini（mini）：國內期貨、期權

        * CTP證券（sopt）：ETF期權

        * 飛馬（femas）：國內期貨

        * 恆生UFT（uft）：國內期貨、ETF期權

        * 寬睿（oes）：國內證券（A股）

        * 中泰XTP（xtp）：國內證券（A股）、ETF期權

        * 恆生期權（hsoption）：ETF期權

        * 華鑫奇點（tora）：國內證券（A股）

        * 飛鼠（sgit）：黃金TD、國內期貨

        * 金仕達黃金（ksgold）：黃金TD

        * 鑫管家（xgj）：期貨資管

        * 融航（rohon）：期貨資管

        * 中匯億達（comstar）：銀行間市場

    * 海外市場

        * 富途證券（futu）：港股、美股

        * 老虎證券（tiger）：全球證券、期貨、期權、外匯等

        * Interactive Brokers（ib）：全球證券、期貨、期權、外匯等

        * 易盛9.0外盤（tap）：全球期貨

        * 直達期貨（da）：全球期貨

        * OANDA（oanda）：外匯、CFD

        * Alpaca（alpaca）：美股（零佣金）

        * 佳兆業投資（kasia）：港股

        * 永豐金證券（Sinopac）：臺灣證券、臺灣期貨、臺灣期權

    * 數字貨幣

        * BitMEX（bitmex）：數字貨幣期貨、期權、永續合約

        * Bybit（bybit）：數字貨幣永續合約

        * 幣安（binance）：數字貨幣現貨

        * 幣安永續（binances)：數字貨幣永續合約

        * OKEX（okex）：數字貨幣現貨

        * OKEX永續（okexs）：數字貨幣永續合約

        * OKEX期貨（okexf）：數字貨幣期貨

        * OKEX期權（okexo）：數字貨幣期權

        * 火幣（huobi）：數字貨幣現貨

        * 火幣期貨（huobif）：數字貨幣期貨

        * 火幣永續（huobis）：數字貨幣永續

        * Gate.io永續（gateios）：數字貨幣永續合約

        * Deribit（deribit），數字貨幣期權、永續合約        

        * Bitfinex（bitfinex）：數字貨幣現貨

        * Coinbase（coinbase）：數字貨幣現貨

        * Bitstamp（bitstamp）：數字貨幣現貨

        * 1Token（onetoken）：數字貨幣券商（現貨、期貨）

    * 特殊應用

        * RPC服務（rpc）：跨程序通訊介面，用於分散式架構

3. 開箱即用的各類量化策略交易應用（vnpy.app）：

    * cta_strategy：CTA策略引擎模組，在保持易用性的同時，允許使用者針對CTA類策略執行過程中委託的報撤行為進行細粒度控制（降低交易滑點、實現高頻策略）

    * cta_backtester：CTA策略回測模組，無需使用Jupyter Notebook，直接使用圖形介面直接進行策略回測分析、引數優化等相關工作

    * spread_trading：價差交易模組，支援自定義價差，實時計算價差行情和持倉，支援半自動價差演算法交易以及全自動價差策略交易兩種模式

    * option_master：期權交易模組，針對國內期權市場設計，支援多種期權定價模型、隱含波動率曲面計算、希臘值風險跟蹤等功能

    * portfolio_strategy：組合策略模組，面向同時交易多合約的量化策略（Alpha、期權套利等），提供歷史資料回測和實盤自動交易功能

    * algo_trading：演算法交易模組，提供多種常用的智慧交易演算法：TWAP、Sniper、Iceberg、BestLimit等等，支援常用演算法配置儲存

    * script_trader：指令碼策略模組，針對多標的組合類交易策略設計，同時也可以直接在命令列中實現REPL指令形式的交易，不支援回測功能

    * chart_wizard：K線圖表模組，基於RQData資料服務（期貨）或者交易介面（數字貨幣）獲取歷史資料，並結合Tick推送顯示實時行情變化

    * portfolio_manager：投資組合模組，面向各類基本面交易策略，以獨立的策略子賬戶為基礎，提供交易倉位的自動跟蹤以及盈虧實時統計功能

    * rpc_service：RPC服務模組，允許將某一VN Trader程序啟動為服務端，作為統一的行情和交易路由通道，允許多客戶端同時連線，實現多程序分散式系統

    * data_manager：歷史資料管理模組，通過樹形目錄檢視資料庫中已有的資料概況，選擇任意時間段資料檢視欄位細節，支援CSV檔案的資料匯入和匯出

    * data_recorder：行情記錄模組，基於圖形介面進行配置，根據需求實時錄製Tick或者K線行情到資料庫中，用於策略回測或者實盤初始化

    * excel_rtd：Excel RTD（Real Time Data）實時資料服務，基於pyxll模組實現在Excel中獲取各類資料（行情、合約、持倉等）的實時推送更新

    * risk_manager：風險管理模組，提供包括交易流控、下單數量、活動委託、撤單總數等規則的統計和限制，有效實現前端風控功能

4. Python交易API介面封裝（vnpy.api），提供上述交易介面的底層對接實現。

5. 簡潔易用的事件驅動引擎（vnpy.event），作為事件驅動型交易程式的核心。

6. 跨程序通訊標準組件（vnpy.rpc），用於實現分散式部署的複雜交易系統。

7. Python高效能K線圖表（vnpy.chart），支援大資料量圖表顯示以及實時資料更新功能。

8. [社群論壇](http://www.vnpy.com)和[知乎專欄](http://zhuanlan.zhihu.com/vn-py)，內容包括vn.py專案的開發教程和Python在量化交易領域的應用研究等內容。

9. 官方交流群262656087（QQ），管理嚴格（定期清除長期潛水的成員），入群費將捐贈給vn.py社群基金。

## 環境準備

* 推薦使用vn.py團隊為量化交易專門打造的Python發行版[VNStudio-2.1.3](https://download.vnpy.com/vnstudio-2.1.3.exe)，內建了最新版的vn.py框架以及VN Station量化管理平臺，無需手動安裝
* 支援的系統版本：Windows 7以上/Windows Server 2008以上/Ubuntu 18.04 LTS
* 支援的Python版本：Python 3.7 64位（**注意必須是Python 3.7 64位版本**）

## 安裝步驟

在[這裡](https://github.com/vnpy/vnpy/releases)下載最新版本，解壓後執行以下命令安裝：

**Windows**

    install.bat

**Ubuntu**

    bash install.sh

## 使用指南

1. 在[SimNow](http://www.simnow.com.cn/)註冊CTP模擬賬號，並在[該頁面](http://www.simnow.com.cn/product.action)獲取經紀商程式碼以及交易行情伺服器地址。

2. 在[vn.py社群論壇](https://www.vnpy.com/forum/)註冊獲得VN Station賬號密碼（論壇賬號密碼即是）

3. 啟動VN Station（安裝VN Studio後會在桌面自動建立快捷方式），輸入上一步的賬號密碼登入

4. 點選底部的**VN Trader Lite**按鈕，開始你的交易！！！

注意：

* 在VN Trader的執行過程中請勿關閉VN Station（會自動退出）
* 如需要靈活配置量化交易應用元件，請使用**VN Trader Pro**

## 指令碼執行

除了基於VN Station的圖形化啟動方式外，也可以在任意目錄下建立run.py，寫入以下示例程式碼：

```Python
from vnpy.event import EventEngine
from vnpy.trader.engine import MainEngine
from vnpy.trader.ui import MainWindow, create_qapp
from vnpy.gateway.ctp import CtpGateway
from vnpy.app.cta_strategy import CtaStrategyApp
from vnpy.app.cta_backtester import CtaBacktesterApp

def main():
    """Start VN Trader"""
    qapp = create_qapp()

    event_engine = EventEngine()
    main_engine = MainEngine(event_engine)
    
    main_engine.add_gateway(CtpGateway)
    main_engine.add_app(CtaStrategyApp)
    main_engine.add_app(CtaBacktesterApp)

    main_window = MainWindow(main_engine, event_engine)
    main_window.showMaximized()

    qapp.exec()

if __name__ == "__main__":
    main()
```

在該目錄下開啟CMD（按住Shift->點選滑鼠右鍵->在此處開啟命令視窗/PowerShell）後執行下列命令啟動VN Trader：

    python run.py

## 貢獻程式碼

vn.py使用Github託管其原始碼，如果希望貢獻程式碼請使用github的PR（Pull Request）的流程:

1. [建立 Issue](https://github.com/vnpy/vnpy/issues/new) - 對於較大的改動（如新功能，大型重構等）最好先開issue討論一下，較小的improvement（如文件改進，bugfix等）直接發PR即可

2. Fork [vn.py](https://github.com/vnpy/vnpy) - 點選右上角**Fork**按鈕

3. Clone你自己的fork: ```git clone https://github.com/$userid/vnpy.git```
	* 如果你的fork已經過時，需要手動sync：[同步方法](https://help.github.com/articles/syncing-a-fork/)

4. 從**dev**建立你自己的feature branch: ```git checkout -b $my_feature_branch dev```

5. 在$my_feature_branch上修改並將修改push到你的fork上

6. 建立從你的fork的$my_feature_branch分支到主專案的**dev**分支的[Pull Request] -  [在此](https://github.com/vnpy/vnpy/compare?expand=1)點選**compare across forks**，選擇需要的fork和branch建立PR

7. 等待review, 需要繼續改進，或者被Merge!

在提交程式碼的時候，請遵守以下規則，以提高程式碼質量：

  * 使用[autopep8](https://github.com/hhatto/autopep8)格式化你的程式碼。執行```autopep8 --in-place --recursive . ```即可。
  * 使用[flake8](https://pypi.org/project/flake8/)檢查你的程式碼，確保沒有error和warning。在專案根目錄下執行```flake8```即可。



## 專案捐贈

過去6年中收到過許多社群使用者的捐贈，在此深表感謝！所有的捐贈資金都投入到了vn.py社群基金中，用於支援vn.py專案的運作。

先強調一下：**vn.py是開源專案，可以永久免費使用，並沒有強制捐贈的要求！！！**

捐贈方式：支付寶3216630132@qq.com（*曉優）

長期維護捐贈清單，請在留言中註明是專案捐贈以及捐贈人的名字。

## 其他內容

* [獲取幫助](https://github.com/vnpy/vnpy/blob/dev/.github/SUPPORT.md)
* [社群行為準側](https://github.com/vnpy/vnpy/blob/dev/.github/CODE_OF_CONDUCT.md)
* [Issue模板](https://github.com/vnpy/vnpy/blob/dev/.github/ISSUE_TEMPLATE.md)
* [PR模板](https://github.com/vnpy/vnpy/blob/dev/.github/PULL_REQUEST_TEMPLATE.md)

## 版權說明

MIT
