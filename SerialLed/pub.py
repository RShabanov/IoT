import time
import paho.mqtt.client as paho
import random
from random import randint
import json


MSG_NUMBER = 10

broker="broker.hivemq.com"

client = paho.Client("client-isu-202")

print("Connecting to broker", broker)
client.connect(broker)
client.loop_start()
print("Publishing...")


while True:
    for i in range(1, 13 * 3):
        value = f"{[randint(0, 255) for rgb in range(i)]}"
        # print(value)
        client.publish("light/lights-shr", value)
        time.sleep(0.2)

client.disconnect()
client.loop_stop()