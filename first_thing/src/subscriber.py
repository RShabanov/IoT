import paho.mqtt.client as paho
import json
import matplotlib.pyplot as plt
import matplotlib.dates as mdates
from datetime import datetime
import time


broker="broker.hivemq.com"

SENSOR_TOPIC = "sensor/data-shr"

dates = []
data = []

def on_message(client, userdata, message):
    if message.topic == SENSOR_TOPIC:
        data = json.loads(message.payload.decode("utf-8"))
        print("Received message:", data)
        print("Topic:", message.topic)
        print("QoS:", message.qos, end='\n\n')

        dates.append(datetime.strptime(data["time"], "%Y-%m-%d %H:%M:%S"))
        data.append(int(data["data"]))

client = paho.Client("client-isu-shr_s")
client.on_message = on_message

print("Connecting to", broker)
client.connect(broker)
client.loop_start()
print("Subscribing")


client.subscribe((SENSOR_TOPIC, 2))
time.sleep(60)


print("Disconnecting...")
client.disconnect()
client.loop_stop()