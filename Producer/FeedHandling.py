#!/usr/bin/env python3
from dotenv import load_dotenv
import websocket
import os
import orjson
import zmq
from Queue import TradePusher

load_dotenv("environments.env")

pusher = TradePusher(os.getenv("zmq-addr"),int(os.getenv("zmq-hwm")))

def on_message(ws, message):
    # print(message)
    pusher.pub(message)

def on_error(ws, error):
    print(error)

def on_close(ws):
    print("### closed ###")

def on_open(ws):
    ws.send('{"type":"subscribe","symbol":"BINANCE:BTCUSDT"}')
    # ws.send('{"type":"subscribe","symbol":"IC MARKETS:1"}')

if __name__ == "__main__":
    websocket.enableTrace(True)
    FINNHUB_API_KEY = os.getenv("FINNHUB_API_KEY")
    ws = websocket.WebSocketApp(f"wss://ws.finnhub.io?token={FINNHUB_API_KEY}",
                              on_message = on_message,
                              on_error = on_error,
                              on_close = on_close)
    ws.on_open = on_open
    ws.run_forever()