import time
import paho.mqtt.client as paho
import random
import json


MSG_NUMBER = 10

broker="broker.hivemq.com"

client = paho.Client("client-isu-202")

print("Connecting to broker", broker)
client.connect(broker)
client.loop_start()
print("Publishing...")


while True:
    
    humidity = json.dumps({
        'humidity': random.randint(1, 100),
        'time': time.strftime("%Y-%m-%d %H:%M:%S")
    })
    print("Humidity:", humidity)

    client.publish("house/humidity_shr", humidity)
    client.publish("house/msgs_shr", MSG_NUMBER)
    time.sleep(random.randint(1, 5))

client.disconnect()
client.loop_stop()