#include <WiFi.h>
#include <ArduinoHttpClient.h>
#include <ArduinoJson.h>

const char* ssid = "ivna";
const char* password = "ivnaok123";

const int SENSOR_PIN = 32;

const char* serverIP = "localhost";
const int serverPort = 80;  // Change to the port you're using on your computer

WiFiClient wifiClient;
HttpClient client = HttpClient(wifiClient, serverIP, serverPort);

// Create a JSON document to store sensor data
StaticJsonDocument<256> sensorData;

void setup() {
  Serial.begin(9600);
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
  sensorVoltage = sensorValue / 4095 * 3.3;

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

  // Print sensor data
  Serial.print("sensor reading = ");
  Serial.print(sensorValue);
  Serial.println(" ADC units");
  Serial.print("sensor voltage = ");
  Serial.print(sensorVoltage);
  Serial.println(" V");
  Serial.print("uvindex = ");
  Serial.println(uvindex);

  // Clear the JSON document and populate it with sensor data
  sensorData.clear();
  sensorData["timestamp"] = millis();
  sensorData["sensorValue"] = sensorValue;
  
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
