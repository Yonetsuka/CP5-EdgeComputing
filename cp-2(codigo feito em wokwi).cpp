//importando bibliotecas necessárias
#include "DHTesp.h"
#include <WiFi.h>
#include <PubSubClient.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C LCD = LiquidCrystal_I2C(0x27, 16, 2);

//declarando variáveis para o programa
String luz;
float temperatura;
float humidade;

//declarando id mqtt
#define ID_MQTT  "fiware_101"

//Tópicos
#define TOPICO_PUBLISH   "/TEF/lamp101/attrs/l"
#define TOPICO_PUBLISH_2    "/TEF/lamp101/attrs/t"
#define TOPICO_PUBLISH_3    "/TEF/lamp101/attrs/h"

// WIFI
const char* SSID = "Wokwi-GUEST"; // SSID / nome da rede WI-FI que deseja se conectar
const char* PASSWORD = ""; // Senha da rede WI-FI que deseja se conectar

// MQTT
const char* BROKER_MQTT = "46.17.108.113"; //URL do broker MQTT que se deseja utilizar
int BROKER_PORT = 1883; // Porta do Broker MQTT

//Variáveis e objetos globais
WiFiClient espClient; // Cria o objeto espClient
PubSubClient MQTT(espClient); // Instancia o Cliente MQTT passando o objeto espClient
char EstadoSaida = '0';  //variável que armazena o estado atual da saída
int D4 = 2;

//Pinagem
#define LDR_PIN 2
const int DHT_PIN = 15;
#define BUZZ_PIN 25
#define GLED_PIN 5
#define YLED_PIN 4
#define RLED_PIN 23

DHTesp dhtSensor;

void mqtt_callback(char* topic, byte* payload, unsigned int length);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  initWiFi();
  pinMode(GLED_PIN, OUTPUT);
  pinMode(YLED_PIN, OUTPUT);
  pinMode(RLED_PIN, OUTPUT);
  digitalWrite(GLED_PIN, HIGH);
  digitalWrite(YLED_PIN, HIGH);
  digitalWrite(RLED_PIN, HIGH);
  //Display lcd
  LCD.init();
  LCD.backlight();
  LCD.setCursor(0, 0);
  //Sensor DHT
  dhtSensor.setup(DHT_PIN, DHTesp::DHT22);
  pinMode(LDR_PIN, INPUT);
  initMQTT();
}
void initWiFi() 
{
    delay(10);
    Serial.println("------Conexao WI-FI------");
    Serial.print("Conectando-se na rede: ");
    Serial.println(SSID);
    Serial.println("Aguarde");
     
    reconectWiFi();
}

void reconectWiFi() 
{
    //se já está conectado a rede WI-FI, nada é feito. 
    //Caso contrário, são efetuadas tentativas de conexão
    if (WiFi.status() == WL_CONNECTED)
        return;
         
    WiFi.begin(SSID, PASSWORD, 6); // Conecta na rede WI-FI
     
    while (WiFi.status() != WL_CONNECTED) 
    {
        delay(100);
        Serial.print(".");
    }
   
    Serial.println();
    Serial.print("Conectado com sucesso na rede ");
    Serial.print(SSID);
    Serial.println("IP obtido: ");
    Serial.println(WiFi.localIP());
}


void reconnectMQTT() 
{
    while (!MQTT.connected()) 
    {
        Serial.print("* Tentando se conectar ao Broker MQTT: ");
        Serial.println(BROKER_MQTT);
        if (MQTT.connect(ID_MQTT)) 
        {
            Serial.println("Conectado com sucesso ao broker MQTT!");
            //MQTT.subscribe(TOPICO_SUBSCRIBE); 
        } 
        else
        {
            Serial.println("Falha ao reconectar no broker.");
            Serial.println("Havera nova tentatica de conexao em 2s");
            delay(2000);
        }
    }
}

void initMQTT() 
{
    MQTT.setServer(BROKER_MQTT, BROKER_PORT);   //informa qual broker e porta deve ser conectado
    MQTT.setCallback(mqtt_callback);            //atribui função de callback (função chamada quando qualquer informação de um dos tópicos subescritos chega)
}

void mqtt_callback(char* topic, byte* payload, unsigned int length) 
{
    String msg;
     
    //obtem a string do payload recebido
    for(int i = 0; i < length; i++) 
    {
       char c = (char)payload[i];
       msg += c;
    }
    
    Serial.print("- Mensagem recebida: ");
    Serial.println(msg);
    
    //toma ação dependendo da string recebida:
    //verifica se deve colocar nivel alto de tensão na saída D0:
    //IMPORTANTE: o Led já contido na placa é acionado com lógica invertida (ou seja,
    //enviar HIGH para o output faz o Led apagar / enviar LOW faz o Led acender)
    if (msg.equals("lamp101@on|"))
    {
        digitalWrite(D4, HIGH);
        EstadoSaida = '1';
    }
 
    //verifica se deve colocar nivel alto de tensão na saída D0:
    if (msg.equals("lamp101@off|"))
    {
        digitalWrite(D4, LOW);
        EstadoSaida = '0';
    }
}

void loop() {
  // put your main code here, to run repeatedly:
  //decleração de chars
  char msgBuffer2[4];
  char msgBuffer3[4];
  //luminosidade
  int lightState = digitalRead(LDR_PIN);
  if (lightState == HIGH)
  {
    Serial.println("Está escuro");
    MQTT.publish(TOPICO_PUBLISH, "ESCURO");
    luz = "Escuro";
  }
  else
  {
    Serial.println("Está claro");
    MQTT.publish(TOPICO_PUBLISH, "CLARO");
    luz = "Claro";
  }
  //temperatura e humidade
  TempAndHumidity  data = dhtSensor.getTempAndHumidity();
  temperatura = data.temperature;
  humidade = data.humidity;
  Serial.println("Temp: " + String(temperatura, 2) + "°C");
  Serial.println("Humidity: " + String(humidade, 1) + "%");
  Serial.println("---");
  //mostrando informações no display LCD
  LCD.clear();
  LCD.setCursor(0,0);
  LCD.print("Temperatura:");
  LCD.setCursor(0,1);
  LCD.print(temperatura);
  delay(2500);
  LCD.clear();
  LCD.setCursor(0,0);
  LCD.print("Humidade:");
  LCD.setCursor(0,1);
  LCD.print(humidade);
  delay(2500);
  LCD.clear();
  LCD.setCursor(0,0);
  LCD.print("Luminosidade:");
  LCD.setCursor(0,1);
  LCD.print(luz);
  //verificando se nenhuma das variáveis está com um valor maior ou menor do que deve
  //1) luz
  if(luz == "Claro")
  {
    LCD.clear();
    LCD.setCursor(0,0);
    LCD.print("Ambiente");
    LCD.setCursor(0,1);
    LCD.print("claro");
    tone(BUZZ_PIN, 250);
    delay(3000);
  }
  //2) temperatura
  if(temperatura >= 15)
  {
    LCD.clear();
    LCD.setCursor(0,0);
    LCD.print("Ambiente muito");
    LCD.setCursor(0,1);
    LCD.print("quente");
    tone(BUZZ_PIN, 300);
    delay(3000);
  }
  //3) umidade
  if(humidade >= 70)
  {
    LCD.clear();
    LCD.setCursor(0,0);
    LCD.print("Ambiente muito");
    LCD.setCursor(0,1);
    LCD.print("umido");
    tone(BUZZ_PIN, 350);
    delay(3000);
  }
  //passando informações para o broker mqtt
  dtostrf(temperatura,4,2,msgBuffer2);
  dtostrf(humidade,4,2,msgBuffer3);
  MQTT.publish(TOPICO_PUBLISH_2,msgBuffer2);
  MQTT.publish(TOPICO_PUBLISH_3,msgBuffer3);
  delay(2000);
  noTone(BUZZ_PIN);
  //keep alive mqtt
  MQTT.loop();
}
