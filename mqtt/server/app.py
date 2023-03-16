import time

import paho.mqtt.client as mqtt

id = 'fablabromagna'
server_name = id + '_server'

client_telemetry_topic = id + '/telemetry'
server_command_topic = id + '/commands'

broker_address = 'test.mosquitto.org'

def on_connect(client, userdata, flags, rc):
    print("Connected with result code "+str(rc))

    print(f"Subscribing for topic {client_telemetry_topic}")
    client.subscribe(client_telemetry_topic)

    print(f"MQTT >> [{server_command_topic}] off")
    client.publish(server_command_topic, "off")


def handle_telemetry(client, userdata, message):
    payload = message.payload.decode()
    print(f"MQTT << [{client_telemetry_topic}] {payload}")

    if payload == "off":
        command = "on"
    else:
        command = "off"

    print(f"MQTT >> [{server_command_topic}] {command}")
    client.publish(server_command_topic, command)
    time.sleep(3)

mqtt_client = mqtt.Client(server_name)
mqtt_client.enable_logger()
mqtt_client.on_connect = on_connect
mqtt_client.on_message = handle_telemetry

print(f"Connecting to the broker at {broker_address} with client name {server_name}...")
mqtt_client.connect(broker_address)

mqtt_client.loop_start()

while True:
    time.sleep(2)