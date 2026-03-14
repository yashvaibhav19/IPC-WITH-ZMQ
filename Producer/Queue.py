import zmq
import orjson

class TradePusher:
    def __init__(self, addr="tcp://127.0.0.1:5555", hwm=10000):
        self.context = zmq.Context()
        self.socket = self.context.socket(zmq.PUB)
        
        self.socket.set(zmq.SNDHWM, hwm)
        self.socket.bind(addr)
        print(f"ZMQ Pusher bound to {addr}")

    def pub(self, data_list):
        data_list = orjson.loads(data_list)["data"]
        for trade in data_list:
            payload = {
                "s": trade.get("s"), # Symbol
                "p": trade.get("p"), # Price
                "v": trade.get("v"), # Volume
                "t": trade.get("t")  # Timestamp (ms)
            }
            # print("DEBUG: ",orjson.dumps(payload)).decode('utf-8')
            self.socket.send_string(f"{orjson.dumps(payload).decode('utf-8')}")

    def close(self):
        self.socket.close()
        self.context.term()
