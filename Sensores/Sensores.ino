#include <Ethernet2.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include <DHT.h>
#include <DHT_U.h>

byte mac[] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x02 };

// Dirección ip y gateway
IPAddress ip();
IPAddress gw();

// DNS information
IPAddress dns(8, 8, 8, 8);

// Broker information
const char broker_name[] = "tom.uib.es";
const unsigned int broker_port = 1883;
const char client_id[] = "secondsAway"; 

void callback(char* topic, byte* payload, unsigned int length);
void reconnect();

const uint8_t SENSOR_TH = 40;
uint8_t temperatue, humidity;

DHT dht(SENSOR_TH, DHT11);

EthernetClient ethClient;
PubSubClient mqttClient(ethClient);

void setup() {
  
  Serial.begin(115200);

  Ethernet.begin(mac, ip, dns, gw);
  mqttClient.setServer(broker_name, broker_port);
  mqttClient.setCallback(callback);

  dht.begin();

  delay(1500);
}

void loop() {

  connect();

  mqttClient.suscribe();
  mqttClient.suscribe();

  temperatue = humidity = 0;
  while(true){

    mqttClient.loop();

    temperature = dht.readTemperature();
    humidity = dht.readHumidity();

    Serial.print("Temperatura ºC: ");
    Serial.println(temperatue);
    Serial.print("Humedad: ");
    Serial.println(humidity));

    delay(5000);
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
    connection_successful = mqttClient.connect(client_id, "ddiot", "uibddiot2627");
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
