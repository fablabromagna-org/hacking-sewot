#include <Arduino.h>
#include "EspMQTTClient.h"

#define ONBOARD_LED 15

EspMQTTClient client(
  "",                          // WiFi SSID
  "",                       // WiFi password
  "test.mosquitto.org",             // MQTT broker server ip
  "",                               // MQTT username
  "",                               // MQTT password
  "fablabromagna_client",           // Client unique identifier
  1883                              // MQTT Port
);

void setup() {
  pinMode(ONBOARD_LED, OUTPUT);
  Serial.begin(9600);
  client.enableDebuggingMessages();
}

void onConnectionEstablished() {
  client.subscribe("fablabromagna/commands", [] (const String &payload)  {
    if (payload == "on") {
      client.publish("fablabromagna/telemetry", "on");
      digitalWrite(ONBOARD_LED, HIGH);
    }
    if (payload == "off") {
      client.publish("fablabromagna/telemetry", "off");
      digitalWrite(ONBOARD_LED, LOW);
    }
  });
}

void loop() {
  client.loop();
}
