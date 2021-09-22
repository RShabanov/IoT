import time
import paho.mqtt.client as paho
import random
import json
import matplotlib.pyplot as plt
import matplotlib.dates as mdates
from datetime import datetime


broker="broker.hivemq.com"

RECEIVING = False
MSG_NUMBER = -1
RECEIVED_MSGS = 0

HUMIDITY_TOPIC = "house/humidity_shr"

dates = []
humidities = []

def on_message(client, userdata, message):
    global RECEIVING, MSG_NUMBER, RECEIVED_MSGS

    if RECEIVING and message.topic == HUMIDITY_TOPIC:
        data = json.loads(message.payload.decode("utf-8"))
        print("Received message:", data)
        print("Topic:", message.topic)
        print("QoS:", message.qos, end='\n\n')

        dates.append(datetime.strptime(data["time"], "%Y-%m-%d %H:%M:%S"))
        humidities.append(int(data["humidity"]))
        RECEIVED_MSGS += 1

    if message.topic == "house/msgs_shr" and not RECEIVING:
        RECEIVING = True
        MSG_NUMBER = int(message.payload)


def plot_humidity(dates, humidities):
    fig, ax = plt.subplots(constrained_layout=True)

    ax.xaxis.set_minor_locator(mdates.AutoDateLocator())
    ax.xaxis.set_minor_formatter(mdates.DateFormatter("%Y-%m-%d %H:%M:%S"))
    ax.xaxis.grid(True, which='minor')
    
    plt.setp(ax.xaxis.get_minorticklabels(), rotation='45deg')
    plt.setp(ax.xaxis.get_majorticklabels(), visible=True)

    base_date = min(dates)

    ax.plot(dates, humidities)
    ax.set_title(f"Humidity (base date: {base_date.year}-{base_date.month}-{base_date.day})")
    ax.set_ylabel("Humidity")
    ax.set_xlabel("Time")
    plt.show()
    

client = paho.Client("client-isu-101")
client.on_message = on_message

print("Connecting to broker", broker)
client.connect(broker)
client.loop_start()
print("Subscribing")

# time.sleep(60)
client.subscribe([("house/msgs_shr", 2), ("house/humidity_shr", 0)], )

while RECEIVED_MSGS != MSG_NUMBER:
    pass 

client.disconnect()
client.loop_stop()

plot_humidity(dates, humidities)