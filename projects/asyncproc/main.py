import argparse
import asyncio
import json
import io
from random import shuffle

import pandas as pd
import requests
import yfinance as yf


async def to_async(thunk):
    return await asyncio.get_event_loop().run_in_executor(None, thunk)


async def get_wiki(name: str) -> requests.Response:
    headers = {
        "User-Agent": "Mozilla/5.0",
    }
    return await to_async(
        lambda: requests.get(f"https://en.wikipedia.org/wiki/{name}", headers=headers)
    )


async def get_nasdaq_symbols() -> list[str]:
    nasdaq_wiki = await get_wiki("List_of_NASDAQ-100_companies")
    tables = pd.read_html(io.StringIO(nasdaq_wiki.text))
    for table in tables:
        if table.columns[0] == "Ticker":
            return table["Ticker"].to_list()
    return []


async def get_quote(symbol: str) -> tuple[str, float]:
    info = await to_async(lambda: yf.Ticker(symbol).info)
    return symbol, info["currentPrice"]


def try_shuffle(lst: list[str], value: bool):
    if value:
        shuffle(lst)
    return lst


def getParser():
    parser = argparse.ArgumentParser()
    parser.add_argument("-c", "--count", default=1, type=int)
    parser.add_argument("-r", "--random", action="store_true")
    return parser


def to_dict_list(quotes) -> list[dict[str, str | float]]:
    result = []
    for symbol, price in quotes:
        result.append(
            {
                "symbol": symbol,
                "price": price,
            }
        )
    return result


async def main():
    args = getParser().parse_args()
    symbols = await get_nasdaq_symbols()
    quotes = await asyncio.gather(
        *[
            get_quote(symbol)
            for symbol in try_shuffle(symbols, args.random)[: args.count]
        ],
        return_exceptions=True,
    )
    quotes = filter(lambda q: not isinstance(q, BaseException), quotes)
    print(json.dumps(to_dict_list(sorted(quotes))))


if __name__ == "__main__":
    asyncio.run(main())
