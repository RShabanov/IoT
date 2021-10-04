#!bin/python3

import serial
import paho.mqtt.client as paho
import time
import json
import sys


MESSAGE_NUMBER = 10
BROKER = "broker.hivemq.com"

client = paho.Client("client-isu-shr_p")

print("Connecting to broker:", BROKER)
client.connect(BROKER)


msg_len = {
    b'0': 5,
    b'1': 5,
}

def connect():
    try:
        ser = serial.Serial('/dev/ttyACM0', timeout=1)
        return ser
    except Exception as e:
        print('Connection failed:', e)
        return None
    

def get_sensor(ser, sensor_byte):
    ser.write(sensor_byte)
    data = ser.read(msg_len[sensor_byte]).decode().strip()
    
    if data == '':
        print('No messages')
    
    return data


ser = connect()

if ser is not None:

    client.loop_start()
    print("Publishing...")

    for i in range(MESSAGE_NUMBER):
        sensor_data = json.dumps({
            'data': get_sensor(ser, b'0'),
            'time': time.strftime("%Y-%m-%d %H:%M:%S")
        })

        # print(f"Data (try {i}): {sensor_data}")

        client.publish("sensor/data-shr", sensor_data)
        time.sleep(1)
            
    client.disconnect()
    client.loop_stop()

    ser.close()
