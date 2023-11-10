#include <WiFi.h>
#include <ArduinoHttpClient.h>
#include <ArduinoJson.h>
#include <Adafruit_BMP085.h>
#include <SPI.h>

Adafruit_BMP085 bmp;

const char* ssid = "ivna";
const char* password = "ivnaok123";

const int SENSOR_PIN = 32;

const char* serverIP = "localhost";  // Endereço IP do seu servidor Flask
const int serverPort = 80;  // Porta usada pelo Flask

WiFiClient wifiClient;
HttpClient client = HttpClient(wifiClient, serverIP, serverPort);

// Cria um arquivo em JSOM para armazenar os dados do sensor 
StaticJsonDocument<256> sensorData;

void setup() {
  Serial.begin(9600);

  if (!bmp.begin(0x77)) {
    Serial.println("Não foi possivel estabelecer a conexão com o sensor BMO180");
    while (1) {}
  }
  while (!Serial);

  pinMode(SENSOR_PIN, INPUT);

  WiFi.begin(ssid, password, true);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Conectando ao WiFi...");
  }

  Serial.println("Conectado com o WiFi");

  analogReadResolution(12); // Define a resolução ADC para 12 bits 
}

void loop() {
  float sensorVoltage;
  float sensorValue;
  int uvindex;
  sensorValue = analogRead(SENSOR_PIN);
  sensorVoltage = sensorValue / 4095.0 * 3.3;

  if      (sensorVoltage < 0.05) uvindex = 0;
  else if (sensorVoltage > 0.05 && sensorVoltage <= 0.227) uvindex = 1;
  else if (sensorVoltage > 0.227 && sensorVoltage <= 0.318) uvindex = 2;
  else if (sensorVoltage > 0.318 && sensorVoltage <= 0.408) uvindex = 3;
  else if (sensorVoltage > 0.408 && sensorVoltage <= 0.503) uvindex = 4;
  else if (sensorVoltage > 0.503 && sensorVoltage <= 0.606) uvindex = 5;
  else if (sensorVoltage > 0.606 && sensorVoltage <= 0.696) uvindex = 6;
  else if (sensorVoltage > 0.696 && sensorVoltage <= 0.795) uvindex = 7;
  else if (sensorVoltage > 0.795 && sensorVoltage <= 0.881) uvindex = 8;
  else if (sensorVoltage > 0.881 && sensorVoltage <= 0.976) uvindex = 9;
  else if (sensorVoltage > 0.976 && sensorVoltage <= 1.079) uvindex = 10;
  else if (sensorVoltage > 1.079 && sensorVoltage <= 1.170) uvindex = 11;
  else uvindex = 0;

  // Leituras do sensor BMP180
  float temperature = bmp.readTemperature();
  float pressure = bmp.readPressure() / 100.0F;  // convertendo para hPa
  float altitude = bmp.readAltitude(1013.25);  // pressão ao nível do mar em hPa



  // Imprimindo informações do sensor
  //Serial.print("Leitura do sensor = ");
  //Serial.print(sensorValue);
  //Serial.println(" ADC unidades");
  //Serial.print("Voltagem do sensor = ");
  //Serial.print(sensorVoltage);
  //Serial.println("V");
  Serial.print("Raio UV = ");
  Serial.println(uvindex);



  // Imprimindo informações do sensor BMP180
  Serial.print("Temperatura = ");
  Serial.print(temperature);
  Serial.println(" ºC");
  Serial.print("Pressão = ");
  Serial.print(pressure);
  Serial.println(" hPa");
  Serial.print("Altitude = ");
  Serial.print(altitude);
  Serial.println(" m");

  // Lipa ao informações do aquivo json e insere as atuais
  sensorData.clear();
  sensorData["timestamp"] = millis();
  sensorData["sensorValue"] = sensorValue;
  sensorData["bmp180Data"]["temperature"] = temperature;
  sensorData["bmp180Data"]["pressure"] = pressure;
  sensorData["bmp180Data"]["altitude"] = altitude;

  // Cria uma string json a partir do documento em json
  String jsonPayload;
  serializeJson(sensorData, jsonPayload);

  // enviando informações para o servidor
  int responseCode = client.post("/sensor_data", "application/json", jsonPayload);

  if (responseCode > 0) {
    Serial.print("Código de retor no do servidor ");
    Serial.println(responseCode);
  } else {
    Serial.println("Erro ao estabelecer conexão com o servidor");
  }

  delay(1000);  
}
