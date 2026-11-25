#include "Constantes.h"

void callback(char* topic, byte* payload, unsigned int length);
void reconnect();

const uint8_t SENSOR_TH = A5;
uint8_t temperature, humidity;

DHT dht(SENSOR_TH, DHT11);

EthernetClient ethClient;
PubSubClient mqttClient(ethClient);

void setup() {
  
  Serial.begin(115200);

  Ethernet.begin(MAC_ADDR, IP_ADDR, DNS_ADDR, GATEWAY);
  mqttClient.setServer(BROKER_NAME, BROKER_PORT);
  mqttClient.setCallback(callback);

  dht.begin();

  delay(1500);
}

void loop() {

  connect();

  mqttClient.subscribe("ddiot");
  mqttClient.subscribe("ddiot/mhg");

  temperature = humidity = 0;
  while(true){

    temperature = dht.readTemperature();
    humidity = dht.readHumidity();

    Serial.print("Temperatura ºC: ");
    Serial.println(temperature);
    Serial.print("Humedad: ");
    Serial.println(humidity);

    StaticJsonDocument<100> informeDHT;

    informeDHT["Temperatura"] = temperature;
    informeDHT["Humedad"] = humidity;

    char buff[100];
    serializeJson(informeDHT, buff);

    mqttClient.publish(INFORME_CLIMA, buff);

    Serial.println(measureJson(informeDHT));

    mqttClient.loop();

    

    delay(3000);

  }

}

void callback(char* topic, byte* payload, unsigned int length){
  
}

void connect() {
  bool connection_successful;

  // Loop until we're reconnected
  while (!mqttClient.connected()) {
    Serial.println("Attempting MQTT connection ...");

    // Attempt to connect
    connection_successful = mqttClient.connect(CLIENT_ID, "ddiot", "uibddiot2627");
    if (connection_successful) {
      Serial.println("connected");
    } else {
      Serial.print("failed, rc=");
      Serial.print(mqttClient.state());
      Serial.println(" try again in 2 seconds");
      delay(2000);
    }
  }
}
