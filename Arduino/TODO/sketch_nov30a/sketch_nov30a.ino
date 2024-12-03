#include <EEPROM.h>
#include "GravityTDS.h"
#include <OneWire.h>
#include <DallasTemperature.h>

// Definir pines de sensores
#define TdsSensorPin A2       // Pin del TDS Meter
#define phSensorPin A1      // Pin del sensor de pH
#define tempSensorPin A0       // Pin del sensor DS18B20

// Inicializar objetos de sensores
GravityTDS gravityTds;        // Objeto para el TDS
OneWire oneWireObjeto(tempSensorPin);  // Objeto para OneWire en el pin 2
DallasTemperature sensorDS18B20(&oneWireObjeto); // Objeto para DS18B20

// Variables para TDS, pH y Temperatura
float tdsValue = 0;           // Valor del TDS
float phValue = 0;            // Valor del pH
float temperature = 0;        // Valor de temperatura
int tdsQuality = 0;           // Clasificación numérica de TDS
int phQuality = 0;            // Clasificación numérica de pH
int tempQuality = 0;          // Clasificación numérica de temperatura
float tdsCalibrationOffset = 400;  // Compensación/calibración para el TDS
float phCalibrationOffset = 0;       // Compensación/calibración para el pH

void setup() {
  Serial.begin(115200);

  // Inicialización del sensor TDS
  gravityTds.setPin(TdsSensorPin);
  gravityTds.setAref(5.0);       // Voltaje de referencia del ADC, por defecto 5.0V en Arduino UNO
  gravityTds.setAdcRange(1024);  // 1024 para 10bit ADC; 4096 para 12bit ADC
  gravityTds.begin();            // Inicializar TDS

  // Inicialización del sensor de temperatura DS18B20
  sensorDS18B20.begin();

  // Configurar el pin del sensor de pH
  pinMode(phSensorPin, INPUT);
}

// Función para tomar múltiples muestras y obtener el promedio del TDS
float readTdsAverage(int samples = 10) {
  float sum = 0;
  for (int i = 0; i < samples; i++) {
    gravityTds.update();
    sum += gravityTds.getTdsValue();
    delay(10);  // Pequeño retraso para estabilizar las lecturas
  }
  return (sum / samples) + tdsCalibrationOffset;
}

// Función para tomar múltiples muestras y obtener el promedio del pH
float readPhAverage(int samples = 10) {
  float sum = 0;
  for (int i = 0; i < samples; i++) {
    sum += (1023 - analogRead(phSensorPin)) / 73.07;  // Conversión a escala de pH
    delay(10);                                        // Pequeño retraso para estabilizar las lecturas
  }
  return (sum / samples) + phCalibrationOffset;
}

// Función para leer la temperatura del DS18B20
float readTemperature() {
  sensorDS18B20.requestTemperatures(); // Solicitar la temperatura
  return sensorDS18B20.getTempCByIndex(0); // Obtener la temperatura en grados Celsius
}

// **Clasificación numérica del TDS**
int classifyTds(float tds) {
  if (tds < 50) return 1; // Unacceptable
  if (tds < 200) return 2; // Good
  if (tds < 400) return 3; // Acceptable
  if (tds < 600) return 4; // Fairly Acceptable
  if (tds < 900) return 5; // Less Acceptable
  if (tds < 1200) return 6; // Least Acceptable
  return 1; // Unacceptable
}

// **Clasificación numérica del pH**
int classifyPh(float ph) {
  if (ph < 6.5) return 1; // Acidic
  if (ph >= 6.5 && ph <= 8.5) return 2; // Neutral
  return 3; // Alkaline
}

// **Clasificación numérica de temperatura**
int classifyTemperature(float temp) {
  if (temp < 0) return 1; // Freezing
  if (temp < 10) return 2; // Cold
  if (temp < 25) return 3; // Moderate
  if (temp < 35) return 4; // Warm
  return 5; // Hot
}

void loop() {
  // Leer y clasificar el TDS
  tdsValue = readTdsAverage();
  tdsQuality = classifyTds(tdsValue);

  // Leer y clasificar el pH
  phValue = readPhAverage();
  phQuality = classifyPh(phValue);

  // Leer y clasificar la temperatura
  temperature = readTemperature();
  tempQuality = classifyTemperature(temperature);

  // Imprimir los resultados en el Monitor Serial
  Serial.print("TDS: ");
  Serial.print(tdsValue, 0);
  Serial.print(" ppm, Quality: ");
  Serial.println(tdsQuality);

  Serial.print("pH: ");
  Serial.print(phValue, 1);
  Serial.print(", Quality: ");
  Serial.println(phQuality);

  Serial.print("Temperatura: ");
  Serial.print(temperature, 2);
  Serial.print(" °C, Quality: ");
  Serial.println(tempQuality);

  // Formatear y enviar los datos como JSON
  Serial.print("{\"TDS\": ");
  Serial.print(tdsValue, 2);
  Serial.print(", \"TDS_Quality\": ");
  Serial.print(tdsQuality);
  Serial.print(", \"pH\": ");
  Serial.print(phValue, 2);
  Serial.print(", \"pH_Quality\": ");
  Serial.print(phQuality);
  Serial.print(", \"Temperatura\": ");
  Serial.print(temperature, 2);
  Serial.print(", \"Temp_Quality\": ");
  Serial.print(tempQuality);
  Serial.println("}");

  delay(1000);  // Espera 1 segundo antes de la próxima lectura
}