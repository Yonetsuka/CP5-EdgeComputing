/* 
  Sketch generated by the Arduino IoT Cloud Thing "Sensor_de_distancia"
  https://create.arduino.cc/cloud/things/2d73e61e-abde-4bf7-af9b-d7ed3d1ef523 

  Arduino IoT Cloud Variables description

  The following variables are automatically generated and updated when changes are made to the Thing

  String local;
  float distancia;
  bool iniciar;

  Variables which are marked as READ/WRITE in the Cloud Thing will also have functions
  which are called when their values are changed from the Dashboard.
  These functions are generated with the Thing and added at the end of this sketch.
*/

#include "thingProperties.h"
#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 10, 5, 4, 3, 2);//Declara o lcd e suas entradas
long readUltrasonicDistance(int triggerPin, int echoPin)// Define as leituras do sensor como long, variável que pode armazenar até 32 bits de dado 
{
  pinMode(triggerPin, OUTPUT);  // Define o pino"triggerPin" como saída
  digitalWrite(triggerPin, LOW);// Define que o pino está sem tensão neste momento
  delayMicroseconds(10);    // Aguarda por 10 microsegundos (0,01 s)
  digitalWrite(triggerPin, HIGH);// Define que o pino está com tensão neste moemtno
  delayMicroseconds(10);    // Aguarda por 10 microsegundos (0,01 s)
  digitalWrite(triggerPin, LOW);// Define que o pino está sem tensão neste momento
  pinMode(echoPin, INPUT);    // Define o pino "echoPin" como de entrada
  return pulseIn(echoPin, HIGH);
  // Realiza a leitura do pino echoPin e retorna o tempo de viagem da onda sonora em microssegundos
}

void setup() {
  // Initialize serial and wait for port to open:
  Serial.begin(9600);
  // This delay gives the chance to wait for a Serial Monitor without blocking if none is found
  delay(1500); 

  // Defined in thingProperties.h
  initProperties();

  // Connect to Arduino IoT Cloud
  ArduinoCloud.begin(ArduinoIoTPreferredConnection);
  
  /*
     The following function allows you to obtain more information
     related to the state of network and IoT Cloud connection and errors
     the higher number the more granular information you’ll get.
     The default is 0 (only errors).
     Maximum is 4
 */
  setDebugMessageLevel(2);
  ArduinoCloud.printDebugInfo();
}

void loop() {
  ArduinoCloud.update();
  // Your code here 
  
  
}
/*
  Since Iniciar is READ_WRITE variable, onIniciarChange() is
  executed every time a new value is received from IoT Cloud.
*/
void onIniciarChange()  {
  // Add your code here to act upon Iniciar change
  if(iniciar == True)
  {
    while(iniciar == True)
    {
      distancia = readUltrasonicDistance(int triggerPin, int echoPin);
    }
  }
  else
  {
    distancia == 0;
  }
}

/*
  Since Local is READ_WRITE variable, onLocalChange() is
  executed every time a new value is received from IoT Cloud.
*/
void onLocalChange()  {
  // Add your code here to act upon Local change
  if local
}

/*
  Since Distancia is READ_WRITE variable, onDistanciaChange() is
  executed every time a new value is received from IoT Cloud.
*/
void onDistanciaChange()  {
  // Add your code here to act upon Distancia change
  if (Distancia <= 30 && Distancia != 0)
  {
    lcd.clear();
    lcd.write("Aproveitando que");
    lcd.setCursor(0,1);
    lcd.write("você está aqui");
    delay(1500);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.write("Lembre-se de");
    lcd.setCursor(0,1);
    lcd.write("evitar sacolas");
    delay(750);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.write("de plastico")
  }
}
