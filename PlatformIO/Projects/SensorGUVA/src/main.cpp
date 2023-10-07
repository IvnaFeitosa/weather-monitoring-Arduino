#include <Arduino.h>
const int SENSOR_PIN = 32;


void setup() {
  Serial.begin(9600);
  delay(1000);
}

void loop() {
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
