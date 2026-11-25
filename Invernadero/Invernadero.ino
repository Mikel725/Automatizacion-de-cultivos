#include "Timer.h"
#include "Constantes.h"

volatile bool timer_regado = false;

ISR(TIMER1_COMPA_vect) {
  timer_regado = true;
}

const uint8_t BUZZ = 5;

bool deposito_vacio;

uint8_t humedad_invernadero;

Timer tiempo_entre_regado;

EthernetClient ethClient;
PubSubClient mqttClient(ethClient);

void callback(char* topic, byte* payload, unsigned int length);
void connect(void);

void setup() {

  Serial.begin(115200);

  Ethernet.begin(MAC_ADDR, IP_ADDR, DNS_ADDR, GATEWAY);
  mqttClient.setServer(BROKER_NAME, BROKER_PORT);
  mqttClient.setCallback(callback);

  tiempo_entre_regado.init(256, 32500);

  tiempo_entre_regado.start();

  pinMode(BUZZ, OUTPUT);
}

void loop() {

  connect();

  mqttClient.subscribe(INFORME_CLIMA);
  mqttClient.subscribe(ALARMAS);

  while (true) {
    if (timer_regado == true) {
      timer_regado = false;
      regarPlantas();
    }
  }
}

void callback(char* topic, byte* payload, unsigned int length) {

  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.println("]");

  StaticJsonDocument<100> infCLima;

  if (strcmp(topic, INFORME_CLIMA) == 0) {
    DeserializationError error = deserializeJson(infCLima, payload, length);

    if (error) {
      Serial.print("Error al leer JSON: ");
      Serial.println(error.c_str());
      return;
    }

    uint8_t temperature = infCLima["Temperatura"];
    uint8_t humidity = infCLima["Humedad"];

    Serial.print("Temperatura");
    Serial.println(temperature);
    Serial.print("Humedad");
    Serial.println(humidity);
  }
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

void regarPlantas() {
  Serial.println("Regando");
  //mqttClient.publish(topic, "regado");
  delay(2000);
}