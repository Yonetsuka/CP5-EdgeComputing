#include <WiFi.h>
#include <PubSubClient.h>
#include "DHT.h"

#define ID_MQTT  "fiware_112"

//declarando variáveis para o programa
String luz;
float temperatura;
float humidade;

//definir pino
#define DHTPIN 4

//defnir dht
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);


//definição de tópicos
#define TOPICO_SUBSCRIBE    "/TEF/lamp112/cmd"        //tópico MQTT de escuta
#define TOPICO_PUBLISH      "/TEF/lamp112/attrs"      //tópico MQTT de envio de informações para Broker
#define TOPICO_PUBLISH_2    "/TEF/lamp112/attrs/l"    //tópico MQTT de envio de informações para Broker
#define TOPICO_PUBLISH_3    "/TEF/lamp112/attrs/h"    //tópico MQTT de envio de informações para Broker
#define TOPICO_PUBLISH_4    "/TEF/lamp112/attrs/t"    //tópico MQTT de envio de informações para Broker

// WIFI
const char* SSID = "FIAP-IBM"; // SSID / nome da rede WI-FI que deseja se conectar
const char* PASSWORD = "Challenge@23!"; // Senha da rede WI-FI que deseja se 

// MQTT
const char* BROKER_MQTT = "46.17.108.113"; //URL do broker MQTT que se deseja utilizar
int BROKER_PORT = 1883; // Porta do Broker MQTT

//Variáveis e objetos globais
WiFiClient espClient; // Cria o objeto espClient
PubSubClient MQTT(espClient); // Instancia o Cliente MQTT passando o objeto espClient
char EstadoSaida = '0';  //variável que armazena o estado atual da saída
int D4 = 2;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  initWiFi();
  initMQTT();
  dht.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
      //garante funcionamento das conexões WiFi e ao broker MQTT
    VerificaConexoesWiFIEMQTT();
 
    //envia o status de todos os outputs para o Broker no protocolo esperado
  verTemHum();
  verLum();
  MQTT.loop();
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
    if (msg.equals("lamp112@on|"))
    {
        digitalWrite(D4, HIGH);
        EstadoSaida = '1';
    }
 
    //verifica se deve colocar nivel alto de tensão na saída D0:
    if (msg.equals("lamp112@off|"))
    {
        digitalWrite(D4, LOW);
        EstadoSaida = '0';
    }
}

void reconectWiFi() 
{
    //se já está conectado a rede WI-FI, nada é feito. 
    //Caso contrário, são efetuadas tentativas de conexão
    if (WiFi.status() == WL_CONNECTED)
        return;
         
    WiFi.begin(SSID, PASSWORD); // Conecta na rede WI-FI
     
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
            MQTT.subscribe(TOPICO_SUBSCRIBE); 
        } 
        else
        {
            Serial.println("Falha ao reconectar no broker.");
            Serial.println("Havera nova tentatica de conexao em 2s");
            delay(2000);
        }
    }
}

void VerificaConexoesWiFIEMQTT(void)
{
    if (!MQTT.connected()) 
        reconnectMQTT(); //se não há conexão com o Broker, a conexão é refeita
     
     reconectWiFi(); //se não há conexão com o WiFI, a conexão é refeita
}

void verTemHum()
{
  char msgBuffer[4];
  char msgBuffer2[4];
  // Wait a few seconds between measurements.
  delay(2000);

  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();

  // Check if any reads failed and exit early (to try again).
  /*if (isnan(h) || isnan(t)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }*/
   Serial.print(F("Humidity: "));
  Serial.print(h);
  Serial.print(F("%  Temperature: "));
  Serial.print(t);
  Serial.println(F("°C "));
  dtostrf(h, 4, 2, msgBuffer);
  MQTT.publish(TOPICO_PUBLISH_3,msgBuffer);
  dtostrf(t, 4, 2, msgBuffer2); 
  MQTT.publish(TOPICO_PUBLISH_4,msgBuffer2);
}

void verLum()
{
  char msgBuffer3[4];
  const int potPin = 34;
  int sensorValue = analogRead(potPin);
  float voltage = sensorValue * (3.3 / 4096.0);
  float luminosity = map(sensorValue, 2000, 4095, 0, 100);
  float luminosidade = luminosity * -1;
  Serial.print(luminosidade);
  Serial.println("%");
  dtostrf(luminosidade, 4, 2, msgBuffer3);
  MQTT.publish(TOPICO_PUBLISH_2,msgBuffer3);  
}
