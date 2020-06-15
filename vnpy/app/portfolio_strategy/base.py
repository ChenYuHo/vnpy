"""
Defines constants and objects used in PortfolioStrategy App.
"""

from enum import Enum


APP_NAME = "PortfolioStrategy"


class EngineType(Enum):
    LIVE = "實盤"
    BACKTESTING = "回測"


EVENT_PORTFOLIO_LOG = "ePortfolioLog"
EVENT_PORTFOLIO_STRATEGY = "ePortfolioStrategy"
