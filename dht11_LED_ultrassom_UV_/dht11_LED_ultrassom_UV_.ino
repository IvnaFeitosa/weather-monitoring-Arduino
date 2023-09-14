#include <dht11.h>
//#include <HCSR04.h> //Inclui a biblioteca do ultrassônico
#include <GUVA-S12SD.h>
// Variável para o pino A6 que lê o DHT11
#define DHT11PIN 6
#include <Wire.h>
#include <Adafruit_BMP085.h>

Adafruit_BMP085 bmp;

GUVAS12SD uv(A0);
dht11 DHT11;
//UltraSonicDistanceSensor distanceSensor(5, 4);  // Initialize sensor that uses digital pins 13 and 12.

int ledPin = 9;//Atribui o valor 9 a variável inteira ledPin, que irá representar o pino digital 9
int indiceUV;
void  setup()
{
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);//Define ledPin (pino 9) como saída
 

  if (!bmp.begin()) {
    //Serial.println("Não foi possível encontrar o sensor BMP180. Verifique as conexões!");
    while (1);
  }

}

void loop()
{

  //Serial.println("");

  int chk = DHT11.read(DHT11PIN);

  if (chk != 0) {
   // Serial.println("Erro de Leitura !!!");
  }
  else {
   /* Serial.print("Humidade (%): ");
    Serial.println((float)DHT11.humidity, 2);

    Serial.print("Temperatura  (C): ");
    Serial.println((float)DHT11.temperature, 2);
    */
  }

  
  delay(500);
  /*
    // Every 500 miliseconds, do a measurement using the sensor and print the distance in centimeters.
    Serial.print("A distância é (cm): ");
    Serial.println(distanceSensor.measureDistanceCm());
 
 */
    float mV = uv.read();
    float uv_index = uv.index(mV);
    //Serial.print("A intensidade de radiação UV é (UV): ");
    
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
  //Serial.print(indiceUV);

    delay(500);


/*
    if(distanceSensor.measureDistanceCm() < 60){
      digitalWrite(ledPin, HIGH);//Coloca ledPin em nível alto (5V)
      }

    else{
      digitalWrite(ledPin, LOW);//Coloca ledPin em nível alto (5V)
    }
    delay(2000);
  */

  float temperature = bmp.readTemperature(); 
  float pressure = bmp.readPressure(); 

  float altitude = bmp.readAltitude(); 

  //float seaLevelPressure = 101325.0; 


  //Serial.print("Temperatura: ");
 // Serial.print(temperature);
 // Serial.println(" ºC ");
 // Serial.print("Pressão: ");
 // Serial.print(pressure / 100.0); // Converte a pressão para hPa
 // Serial.println(" hPa ");
 // Serial.print("Altitude: ");
 // Serial.println(altitude);
  //Serial.println(" m ");

  Serial.println  (temperature);
  Serial.println(pressure / 100.0); // Converte a pressão para hPa
  Serial.println(indiceUV);
  Serial.println(altitude);
  
  delay(5000);
  
}
