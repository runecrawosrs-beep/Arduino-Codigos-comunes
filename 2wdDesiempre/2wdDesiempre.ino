#include <SoftwareSerial.h>

// RX = 2, TX = 3
SoftwareSerial BT(2, 3);

const uint8_t M1A = 5;
const uint8_t M1B = 6;
const uint8_t M2A = 9;
const uint8_t M2B = 10;

void setMotors(uint8_t m1a, uint8_t m1b, uint8_t m2a, uint8_t m2b) {
  digitalWrite(M1A, m1a);
  digitalWrite(M1B, m1b);
  digitalWrite(M2A, m2a);
  digitalWrite(M2B, m2b);
}

void setup() {
  // Monitor Serie para depuración
  Serial.begin(115200); 
  
  // Baudrate estándar para módulos HC-05/HC-06. Ajusta si el tuyo es distinto.
  BT.begin(9600);       

  pinMode(M1A, OUTPUT); pinMode(M1B, OUTPUT);
  pinMode(M2A, OUTPUT); pinMode(M2B, OUTPUT);

  setMotors(LOW, LOW, LOW, LOW);
  Serial.println("Arduino Uno listo. Esperando comandos BT...");
}

void loop() {
  if (BT.available()) {
    char cmd = BT.read();
    
    // Aquí ves en el monitor qué está recibiendo exactamente
    Serial.print("Comando recibido: ");
    Serial.println(cmd);

    switch(cmd) {
      case 'F': setMotors(HIGH, LOW, HIGH, LOW); break; // Adelante
      case 'B': setMotors(LOW, HIGH, LOW, HIGH); break; // Atrás
      case 'L': setMotors(LOW, HIGH, HIGH, LOW); break; // Pivote Izquierda
      case 'R': setMotors(HIGH, LOW, LOW, HIGH); break; // Pivote Derecha
      
      // Diagonales clásicas de apps RC
      case 'G': setMotors(LOW, LOW, HIGH, LOW); break;  // Adelante-Izq
      case 'I': setMotors(HIGH, LOW, LOW, LOW); break;  // Adelante-Der
      case 'H': setMotors(LOW, LOW, LOW, HIGH); break;  // Atrás-Izq
      case 'J': setMotors(LOW, HIGH, LOW, LOW); break;  // Atrás-Der
      
      case 'S': setMotors(LOW, LOW, LOW, LOW); break;   // Parar
      
      case '\n': 
      case '\r': 
        break; // Ignorar retornos de carro invisibles
        
      default:
        Serial.println("-> Comando ignorado/desconocido.");
        break;
    }
  }
}
