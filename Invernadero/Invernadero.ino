#include "Timer.h"

volatile bool timer_regado = false;

ISR(TIMER1_COMPA_vect){
  timer_regado = true;
}

const uint8_t BUZZ = 5;

bool deposito_vacio;

uint8_t humedad_invernadero;

Timer tiempo_entre_regado;

void setup() {

  Serial.begin(115200);

  tiempo_entre_regado.init(256, 32500);

  tiempo_entre_regado.start();
  
  pinMode(BUZZ, OUTPUT);

}

void loop() {

  while (true){
    if (timer_regado == true){ 
      timer_regado = false;
      regarPlantas();
    }
  }

}

void regarPlantas(){
  Serial.println("Regando");
  //mqttClient.publish(topic, "regado");
  delay(2000);
}