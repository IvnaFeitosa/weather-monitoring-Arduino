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

// Create a JSON document to store sensor data
StaticJsonDocument<256> sensorData;

void setup() {
  Serial.begin(9600);

  if (!bmp.begin(0x77)) {
    Serial.println("Could not find a valid BMP085/BMP180 sensor, check wiring!");
    while (1) {}
  }
  while (!Serial);

  pinMode(SENSOR_PIN, INPUT);

  WiFi.begin(ssid, password, true);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  Serial.println("Connected to WiFi");

  analogReadResolution(12); // Set the ADC resolution to 12 bits (0-4095)
}

void loop() {
  float sensorVoltage;
  float sensorValue;
  int uvindex;
  sensorValue = analogRead(SENSOR_PIN);
  sensorVoltage = sensorValue / 4095.0 * 3.3;

  // O código existente para calcular o índice UV continua aqui

  // Leituras do sensor BMP180
  float temperature = bmp.readTemperature();
  float pressure = bmp.readPressure() / 100.0F;  // Convert Pa to hPa
  float altitude = bmp.readAltitude(1013.25);  // Substitua pelo valor correto da pressão ao nível do mar

  // Print sensor data
  Serial.print("sensor reading = ");
  Serial.print(sensorValue);
  Serial.println(" ADC units");
  Serial.print("sensor voltage = ");
  Serial.print(sensorVoltage);
  Serial.println(" V");
  Serial.print("uvindex = ");
  Serial.println(uvindex);

  // Print dados do BMP180
  Serial.print("Temperature = ");
  Serial.print(temperature);
  Serial.println(" *C");
  Serial.print("Pressure = ");
  Serial.print(pressure);
  Serial.println(" hPa");
  Serial.print("Altitude = ");
  Serial.print(altitude);
  Serial.println(" meters");

  // Clear the JSON document and populate it with sensor data
  sensorData.clear();
  sensorData["timestamp"] = millis();
  sensorData["sensorValue"] = sensorValue;
  sensorData["bmp180Data"]["temperature"] = temperature;
  sensorData["bmp180Data"]["pressure"] = pressure;
  sensorData["bmp180Data"]["altitude"] = altitude;

  // Create a JSON string from the JSON document
  String jsonPayload;
  serializeJson(sensorData, jsonPayload);

  // Send data to the server
  int responseCode = client.post("/sensor_data", "application/json", jsonPayload);

  if (responseCode > 0) {
    Serial.print("Server response code: ");
    Serial.println(responseCode);
  } else {
    Serial.println("Error sending data to server.");
  }

  delay(1000);  // Adjust the delay as needed
}
