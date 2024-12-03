// Definir el pin para el sensor pH
#define phSensorPin A1      // Pin donde está conectado el sensor pH

float phValue = 0;  // Variable para almacenar el valor de pH

void setup() {
  Serial.begin(115200);  // Iniciar la comunicación serial
}

void loop() {
  // Leer el valor del sensor de pH
  int sensorValue = analogRead(phSensorPin);
  
  // Convertir el valor analógico a un valor de pH en la escala de 0-14
  phValue = (1023 - sensorValue) / 73.07;

  // Imprimir el valor de pH en el monitor serie
  Serial.print("pH: ");
  Serial.println(phValue, 2);  // Mostrar el valor con 2 decimales
  
  delay(1000);  // Espera 1 segundo antes de la siguiente lectura
}