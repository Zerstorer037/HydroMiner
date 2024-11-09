#include <EEPROM.h>
#include "GravityTDS.h"

// Definir pines de sensores
#define TdsSensorPin A1  // Pin del TDS Meter
#define phSensorPin A0   // Pin del sensor de pH

GravityTDS gravityTds;  // Solo se define una vez

// Variables para el TDS y pH
float tdsValue = 0;              // Variable para almacenar el valor de TDS
float phValue = 0;               // Variable para almacenar el valor de pH
float tdsCalibrationOffset = -3200;  // Compensación/calibración para el TDS
float phCalibrationOffset = 0;   // Compensación/calibración para el pH

void setup() {
  Serial.begin(115200);

  // Inicialización del sensor TDS
  gravityTds.setPin(TdsSensorPin);
  gravityTds.setAref(5.0);       // Voltaje de referencia del ADC, por defecto 5.0V en Arduino UNO
  gravityTds.setAdcRange(1024);  // 1024 para 10bit ADC; 4096 para 12bit ADC
  gravityTds.begin();            // Inicializamos

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

// Función para evaluar la calidad del agua según el TDS
String evaluateWaterQuality(float tds) {
  if (tds < 50) {
    return "Unacceptable";
  } else if (tds < 200) {
    return "Good";
  } else if (tds < 400) {
    return "Acceptable";
  } else if (tds < 600) {
    return "Fairly Acceptable";
  } else if (tds < 900) {
    return "Less Acceptable";
  } else if (tds < 1200) {
    return "Least Acceptable";
  } else {
    return "Unacceptable";
  }
}

// Función para evaluar la calidad del agua según el pH
String evaluatePhQuality(float ph) {
  if (ph < 6.5) {
    return "Acidic";
  } else if (ph >= 6.5 && ph <= 8.5) {
    return "Neutral";
  } else {
    return "Alkaline";
  }
}

void loop() {
  // Leer y mostrar el valor promedio del TDS con la compensación aplicada
  tdsValue = readTdsAverage();
  Serial.print("TDS: ");
  Serial.print(tdsValue, 0);
  Serial.println(" ppm");

  // Evaluar la calidad del agua en función del valor de TDS
  String waterQuality = evaluateWaterQuality(tdsValue);
  Serial.print("Water Quality (TDS): ");
  Serial.println(waterQuality);

  // Leer y mostrar el valor promedio del pH con la compensación aplicada
  phValue = readPhAverage();
  Serial.print("pH: ");
  Serial.println(phValue, 1);

  // Evaluar la calidad del agua en función del valor de pH
  String phQuality = evaluatePhQuality(phValue);
  Serial.print("Water Quality (pH): ");
  Serial.println(phQuality);

  // Formatear y enviar los datos como JSON
  Serial.print("{\"TDS\": ");
  Serial.print(tdsValue, 2);
  Serial.print(", \"pH\": ");
  Serial.print(phValue, 2);
  Serial.println("}");

  delay(1000);  // Espera 1 segundo antes de la próxima lectura
}
