#include <Arduino.h>

// Pines de control del TCS3200
#define S0 27
#define S1 26
#define S2 33
#define S3 32
#define OUT 25

void setup() {
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(OUT, INPUT);

  // Escala 20%
  digitalWrite(S0, HIGH);
  digitalWrite(S1, LOW);

  Serial.begin(115200);
}

// --- Lee un canal de color ---
unsigned int readColor(bool s2, bool s3) {
  digitalWrite(S2, s2);
  digitalWrite(S3, s3);
  delay(2);
  return pulseIn(OUT, LOW);
}

// --- Clasificación siempre ROJO o AZUL ---
String detectarColor() {
  unsigned int rojo = readColor(LOW, LOW);
  unsigned int verde = readColor(HIGH, HIGH);
  unsigned int azul = readColor(LOW, HIGH);

  Serial.print("R: "); Serial.print(rojo);
  Serial.print(" G: "); Serial.print(verde);
  Serial.print(" B: "); Serial.print(azul);

  float total = rojo + verde + azul;
  float pR = rojo / total;
  float pB = azul / total;

  Serial.print(" -> %R: "); Serial.print(pR, 2);
  Serial.print(" %B: "); Serial.println(pB, 2);

  // Elegir al que más se parezca
  if (pR >= pB) {
    Serial.println("Resultado: AZUL");
    return "ROJO / ROSA";
  } else {
    Serial.println("Resultado: ROJO");
    return "AZUL / CELESTE";
  }
}

void loop() {
  detectarColor();
  delay(1000);
}
