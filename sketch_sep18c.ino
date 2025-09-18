#define S0 27
#define S1 26
#define S2 33
#define S3 32
#define OUT_PIN 25

void setup() {
  Serial.begin(115200);

  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(OUT_PIN, INPUT);

  digitalWrite(S0, HIGH);
  digitalWrite(S1, LOW);

  Serial.println("=== Calibracion TCS3200 ===");
  Serial.println("Coloca un objeto frente al sensor cuando lo indique.");
  delay(2000);
}

unsigned long readColorFrequency(int s2State, int s3State) {
  digitalWrite(S2, s2State);
  digitalWrite(S3, s3State);
  delay(200);

  unsigned long duration = pulseIn(OUT_PIN, LOW, 100000);
  if (duration == 0) return 0;
  return 1000000UL / duration;
}

void leerYMostrar() {
  unsigned long red = readColorFrequency(LOW, LOW);
  unsigned long blue = readColorFrequency(LOW, HIGH);
  unsigned long green = readColorFrequency(HIGH, HIGH);

  Serial.print("Rojo: "); Serial.print(red);
  Serial.print("  Verde: "); Serial.print(green);
  Serial.print("  Azul: "); Serial.println(blue);
}

void loop() {
  Serial.println(">>> Coloca PAPEL BLANCO y presiona ENTER en el monitor serie...");
  while (Serial.available() == 0); Serial.read();
  leerYMostrar();

  Serial.println(">>> Coloca PAPEL NEGRO y presiona ENTER...");
  while (Serial.available() == 0); Serial.read();
  leerYMostrar();

  Serial.println(">>> Coloca objeto ROJO y presiona ENTER...");
  while (Serial.available() == 0); Serial.read();
  leerYMostrar();

  Serial.println(">>> Coloca objeto VERDE y presiona ENTER...");
  while (Serial.available() == 0); Serial.read();
  leerYMostrar();

  Serial.println(">>> Coloca objeto AZUL y presiona ENTER...");
  while (Serial.available() == 0); Serial.read();
  leerYMostrar();

  Serial.println("=== Fin calibracion ===");
  while (true); // detener el loop
}

