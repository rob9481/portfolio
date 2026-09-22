import argparse
import asyncio
import io
from random import shuffle

import pandas as pd
import requests
import yfinance as yf


async def get_wiki(name: str) -> requests.Response:
    headers = {
        "User-Agent": "Mozilla/5.0",
    }
    return requests.get(f"https://en.wikipedia.org/wiki/{name}", headers=headers)


async def get_nasdaq_symbols() -> list[str]:
    nasdaq_wiki = await get_wiki("List_of_NASDAQ-100_companies")
    tables = pd.read_html(io.StringIO(nasdaq_wiki.text))
    for table in tables:
        if table.columns[0] == "Ticker":
            return table["Ticker"].to_list()
    return None


async def get_quote(symbol: str) -> float:
    ticker = yf.Ticker(symbol)
    return symbol, ticker.info["currentPrice"]


def try_shuffle(lst: list[str], value: bool):
    if value:
        shuffle(lst)
    return lst


def getParser():
    parser = argparse.ArgumentParser()
    parser.add_argument("-c", "--count", default=1, type=int)
    parser.add_argument("-r", "--random", action="store_true")
    return parser


async def main():
    args = getParser().parse_args()
    symbols = get_nasdaq_symbols()

    # not thread-safe, but we're using concurrency not threads.
    quotes = []

    async with asyncio.TaskGroup() as tg:
        for symbol in try_shuffle(await symbols, args.random)[: args.count]:
            t = tg.create_task(get_quote(symbol))
            t.add_done_callback(lambda t: quotes.append(t.result()))
    print(sorted(quotes))


if __name__ == "__main__":
    asyncio.run(main())
