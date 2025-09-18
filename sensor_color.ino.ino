// Pines conectados al ESP32
#define S0 27
#define S1 26
#define S2 33
#define S3 32
#define OUT_PIN 25

// ---- Límites de calibración medidos ----
int redMin = 2232;   int redMax = 13157;
int greenMin = 1941; int greenMax = 10638;
int blueMin = 2169;  int blueMax = 12195;

void setup() {
  Serial.begin(115200);

  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(OUT_PIN, INPUT);

  digitalWrite(S0, HIGH); // Escala de frecuencia 20%
  digitalWrite(S1, LOW);

  Serial.println("Sensor TCS3200 listo");
}

unsigned long readColorFrequency(int s2State, int s3State) {
  digitalWrite(S2, s2State);
  digitalWrite(S3, s3State);
  delay(50);

  unsigned long duration = pulseIn(OUT_PIN, LOW);
  if (duration == 0) return 0;
  return 1000000UL / duration;
}

float normalize(int value, int minVal, int maxVal) {
  if (value < minVal) value = minVal;
  if (value > maxVal) value = maxVal;
  return (float)(value - minVal) / (maxVal - minVal);
}

void loop() {
  // Leer frecuencias crudas
  unsigned long red = readColorFrequency(LOW, LOW);      // filtro rojo
  unsigned long blue = readColorFrequency(LOW, HIGH);    // filtro azul
  unsigned long green = readColorFrequency(HIGH, HIGH);  // filtro verde

  // Normalizar valores según calibración
  float rN = normalize(red, redMin, redMax);
  float gN = normalize(green, greenMin, greenMax);
  float bN = normalize(blue, blueMin, blueMax);

  // Determinar color dominante
  String color = "Mezcla";
  if (rN > gN && rN > bN) color = "Rojo";
  else if (gN > rN && gN > bN) color = "Verde";
  else if (bN > rN && bN > gN) color = "Azul";

  // Determinar claro u oscuro
  unsigned long total = red + green + blue;
  String brillo = (total > 15000) ? "Claro" : "Oscuro";

  // Mostrar resultados
  Serial.print("Crudos -> R:"); Serial.print(red);
  Serial.print(" G:"); Serial.print(green);
  Serial.print(" B:"); Serial.println(blue);

  Serial.print("Norm -> R:"); Serial.print(rN, 2);
  Serial.print(" G:"); Serial.print(gN, 2);
  Serial.print(" B:"); Serial.print(bN, 2);

  Serial.print(" | Color: "); Serial.print(color);
  Serial.print(" | Brillo: "); Serial.println(brillo);

  delay(500);
}




