#include <WiFi.h>

const char* ssid ="ivna";
const char* password ="ivnaok123";


const int SENSOR_PIN = 32;
//#define SENSOR_PIN 32


void setup() {
  Serial.begin(9600);
  while (!Serial);
 
  pinMode(SENSOR_PIN, INPUT);
 
  WiFi.begin(ssid, password, true);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
    Serial.println(WiFi.status());
    delay(1000);
  }

  Serial.println("Connected to WiFi");

  analogReadResolution(12); // Set the ADC resolution to 12 bits (0-4095)

}


void loop(){
  


  float sensorVoltage; 
  float sensorValue;
  int uvindex;
  sensorValue = analogRead(SENSOR_PIN);
  sensorVoltage = sensorValue/4095*3.3;

  if      (sensorVoltage < 0.05) uvindex=0;
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
  

  Serial.print("sensor reading = ");
  Serial.print(sensorValue);
  Serial.println("");
  Serial.print("sensor voltage = ");
  Serial.print(sensorVoltage);
  Serial.println(" V");
  Serial.print("uvindex= ");
  Serial.print(uvindex);
  Serial.println();
  delay(1000);

}