#include <GravityTDS.h>

// Definir el pin para el sensor TDS
#define TdsSensorPin A2       // Pin donde está conectado el sensor TDS

// Inicializar objeto para el sensor TDS
GravityTDS gravityTds;

float tdsValue = 0;  // Variable para almacenar el valor de TDS

void setup() {
  Serial.begin(115200);  // Iniciar la comunicación serial

  // Configuración del sensor TDS
  gravityTds.setPin(TdsSensorPin);
  gravityTds.setAref(5.0);       // Voltaje de referencia del ADC
  gravityTds.setAdcRange(1024);  // Rango del ADC (10 bit)
  gravityTds.begin();            // Inicializar el sensor TDS
}

void loop() {
  gravityTds.update();   // Obtener la última lectura del TDS
  tdsValue = gravityTds.getTdsValue();  // Almacenar el valor de TDS
  
  // Imprimir el valor de TDS en el monitor serie
  Serial.print("TDS: ");
  Serial.print(tdsValue);
  Serial.println(" ppm");
  
  delay(1000);  // Espera 1 segundo antes de la siguiente lectura
}