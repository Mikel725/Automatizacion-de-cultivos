// config.h
#ifndef Constantes_h
#define Constantes_h

#include <Arduino.h>
#include <Ethernet2.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include <DHT.h>
#include <DHT_U.h>

// Red
const byte MAC_ADDR[] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x02 };
const IPAddress IP_ADDR(192, 168, 132, 162);
const IPAddress GATEWAY(192, 168, 132, 7);
const IPAddress DNS_ADDR(8, 8, 8, 8);

// Broker MQTT
const char BROKER_NAME[] = "tom.uib.es";
const unsigned int BROKER_PORT = 1883;
const char CLIENT_ID[] = "secondsAway";
const char MQTT_USER[] = "ddiot";
const char MQTT_PASS[] = "uibddiot2627";

// Topics

const char INFORME_CLIMA[] = "ddiot/AutCul/Ambiente/TempHum";
const char ESTADO_INVERNADERO[] = "ddiot/AutCul";
const char ALARMAS[] = "ddiot/AutCul/invernadero/alarmas";

#endif