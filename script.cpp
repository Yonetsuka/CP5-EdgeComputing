#include <LiquidCrystal.h>

float distancia = 0;
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
  // put your setup code here, to run once:
  Serial.begin(9600);
  lcd.begin(16,2);
  lcd.setCursor(0,0);
  lcd.write("Funciona");
  delay(1000);
  lcd.clear();
}

void loop() {
  // put your main code here, to run repeatedly:
  chegarAoLocal();
  distancia = readUltrasonicDistance(9 , 8 );
  lcd.setCursor(0,0);
  lcd.print("Distancia = ");
  lcd.setCursor(0,1);
  lcd.print(distancia);
  delay(1000);
  lcd.clear();
}

void chegarAoLocal()
{
  if(distancia <= 1000)
  {
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Lembre-se de");
    lcd.setCursor(0,1);
    lcd.print("evitar sacolas");
    delay(500);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.write("plasticas");    
    delay(250);
  }  
}
