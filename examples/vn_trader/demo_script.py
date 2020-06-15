from time import sleep
from vnpy.app.script_trader import ScriptEngine


def run(engine: ScriptEngine):
    """
    指令碼策略的主函式說明：
    1. 唯一入參是指令碼引擎ScriptEngine物件，通用它來完成查詢和請求操作
    2. 該函式會通過一個獨立的執行緒來啟動執行，區別於其他策略模組的事件驅動
    3. while迴圈的維護，請通過engine.strategy_active狀態來判斷，實現可控退出

    指令碼策略的應用舉例：
    1. 自定義籃子委託執行執行演算法
    2. 股指期貨和一籃子股票之間的對衝策略
    3. 國內外商品、數字貨幣跨交易所的套利
    4. 自定義組合指數行情監控以及訊息通知
    5. 股票市場掃描選股類交易策略（龍一、龍二）
    6. 等等~~~
    """
    vt_symbols = ["IF1912.CFFEX", "rb2001.SHFE"]

    # 訂閱行情
    engine.subscribe(vt_symbols)

    # 獲取合約資訊
    for vt_symbol in vt_symbols:
        contract = engine.get_contract(vt_symbol)
        msg = f"合約資訊，{contract}"
        engine.write_log(msg)

    # 持續執行，使用strategy_active來判斷是否要退出程式
    while engine.strategy_active:
        # 輪詢獲取行情
        for vt_symbol in vt_symbols:
            tick = engine.get_tick(vt_symbol)
            msg = f"最新行情, {tick}"
            engine.write_log(msg)

        # 等待3秒進入下一輪
        sleep(3)
