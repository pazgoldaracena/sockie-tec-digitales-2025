/*El rango de velocidad va de 0 a 255, el valor predeterminado es 100.
Usa setSpeed(velocidad) para cambiarla.

A veces, a velocidades más bajas, los motores parecen no funcionar.
Es normal, puede depender del motor y la fuente de alimentación.

Notas:

Este programa es para manejar un motor de CC, no olvidar conectar el ground (-) de la fuente
con el ESP32.

// para motor de CC (los amarillos)
// o motores rescatados de impresoras

A velocidades menores a 200 el motor no tiene fuerza,
gira pero solo serviría para mostrar movimiento.
*/

// Incluir la biblioteca
#include <L298N.h>

// Definición de pines
const unsigned int IN1 = 32;
const unsigned int IN2 = 25;
const unsigned int EN = 33;

// Crear una instancia del motor
L298N motor(EN, IN1, IN2);

void setup()
{
  // Usado para mostrar información
  Serial.begin(115200);

  // Establecer la velocidad inicial
  motor.setSpeed(70);
}

void loop()
{
  // Indicar al motor que avance (depende del cableado)
  motor.forward();

  // Método alternativo:
  // motor.run(L298N::FORWARD);

  // Imprimir el estado del motor en el monitor serial
  printSomeInfo();

  delay(3000);

  // Detener el motor
  motor.stop();

  // Método alternativo:
  // motor.run(L298N::STOP);

  printSomeInfo();

  // Cambiar la velocidad
  motor.setSpeed(255);

  delay(3000);

  // Indicar al motor que retroceda (depende del cableado)
  motor.backward();

  // Método alternativo:
  // motor.run(L298N::BACKWARD);

  printSomeInfo();

  motor.setSpeed(200);

  delay(3000);

  // Detener el motor
  motor.stop();

  printSomeInfo();

  delay(3000);
}

/*
Imprimir algunas informaciones en el Monitor Serial
*/
void printSomeInfo()
{
  Serial.print("El motor está en movimiento = ");
  Serial.print(motor.isMoving());
  Serial.print(" a una velocidad de = ");
  Serial.println(motor.getSpeed());
}
