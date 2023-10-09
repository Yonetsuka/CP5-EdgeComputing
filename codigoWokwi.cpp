#include "DHTesp.h"

#define LDR_PIN 2
const int DHT_PIN = 15;

const float GAMMA = 0.7;
const float RL10 = 50;


DHTesp dhtSensor;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  dhtSensor.setup(DHT_PIN, DHTesp::DHT22);
  pinMode(LDR_PIN, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  //luminosidade
  int lightState = digitalRead(LDR_PIN);
  if (lightState == HIGH)
    Serial.println("Está escuro");
  else
    Serial.println("Está claro");
  //temperatura e humidade
  TempAndHumidity  data = dhtSensor.getTempAndHumidity();
  Serial.println("Temp: " + String(data.temperature, 2) + "°C");
  Serial.println("Humidity: " + String(data.humidity, 1) + "%");
  Serial.println("---");
  delay(2000);
}
