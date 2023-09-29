#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP085.h>
#include <GUVA-S12SD.h>




int ledPin = 9;
int indiceUV;

Adafruit_BMP085_Unified bmp; // Crie um objeto BMP085

GUVAS12SD uv; // Crie um objeto GUVA_S12SD

void setup() {
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
}

void loop() {
  

  delay(500);

  float mV = uv.read();
  float uv_index = uv.index(mV);

  if (uv_index <= 10) {
    indiceUV = 0;
  } else if (uv_index > 10 && uv_index <= 46) {
    indiceUV = 1;
  } else if (uv_index > 46 && uv_index <= 65) {
    indiceUV = 2;
  } else if (uv_index > 65 && uv_index <= 83) {
    indiceUV = 3;
  } else if (uv_index > 83 && uv_index <= 103) {
    indiceUV = 4;
  } else if (uv_index > 103 && uv_index <= 124) {
    indiceUV = 5;
  } else if (uv_index > 124 && uv_index <= 142) {
    indiceUV = 6;
  } else if (uv_index > 142 && uv_index <= 162) {
    indiceUV = 7;
  } else if (uv_index > 162 && uv_index <= 180) {
    indiceUV = 8;
  } else if (uv_index > 180 && uv_index <= 200) {
    indiceUV = 9;
  } else if (uv_index > 200 && uv_index <= 221) {
    indiceUV = 10;
  } else {
    indiceUV = 11;
  }

  delay(500);

  float temperature = bmp.readTemperature();
  float pressure = bmp.readPressure();
  float altitude = bmp.readAltitude();

  Serial.print("Temperatura: ");
  Serial.print(temperature);
  Serial.println(" ºC ");
  Serial.print("Pressão: ");
  Serial.print(pressure / 100.0); // Converte a pressão para hPa
  Serial.println(" hPa ");
  Serial.print("Índice UV: ");
  Serial.println(indiceUV);
  Serial.print("Altitude: ");
  Serial.println(altitude);

  delay(5000);
}
