#include <OneWire.h>
#include <DallasTemperature.h>

// Definir el pin para el sensor de temperatura
#define tempSensorPin A0

// Inicializar el objeto OneWire
OneWire oneWire(tempSensorPin);

// Inicializar el objeto de sensor DS18B20
DallasTemperature sensors(&oneWire);

float temperature = 0;  // Variable para almacenar el valor de temperatura

void setup() {
  Serial.begin(115200);  // Iniciar la comunicación serial

  // Inicializar el sensor DS18B20
  sensors.begin();
}

void loop() {
  sensors.requestTemperatures();  // Solicitar la temperatura
  
  // Obtener la temperatura del sensor en grados Celsius
  temperature = sensors.getTempCByIndex(0);

  // Imprimir la temperatura en el monitor serie
  Serial.print("Temperatura: ");
  Serial.print(temperature);
  Serial.println(" °C");
  
  delay(1000);  // Espera 1 segundo antes de la siguiente lectura
}