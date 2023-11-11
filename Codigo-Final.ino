#include <Servo.h>

#define trigPin 13
#define echoPin 4
#define IN1 9
#define IN2 8
#define IN3 5
#define IN4 6
#define SERVO_PIN 7

int velocidade = 30;

Servo servoSensor;

void setup() {
  Serial.begin(9600);
  servoSensor.attach(SERVO_PIN);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop() {
  servoSensor.write(90);
  delay(1000);
  float distancia = Procurar();

  if (distancia < 30) {
    direcao();
  } else {
    Frente();
  }
}

float Procurar() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  float duracao = pulseIn(echoPin, HIGH);
  float cm = duracao / 90.8;

  Serial.print("Distancia em CM: ");
  Serial.println(cm);

  return cm;
}

void Parar() {
  Serial.println("Robo: Parar ");
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  delay(100);
}

void Frente() {
  Serial.println("Robo: Frente ");
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void ParaTras() {
  Serial.println("Robo: Ré ");
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  delay(300);
  analogWrite(IN1, velocidade);
  analogWrite(IN2, 0);
  analogWrite(IN3, velocidade);
  analogWrite(IN4, 0);
}

void Vireadireita() {
  Serial.println("Robo: Direita");
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  delay(500);
  analogWrite(IN1, velocidade);
  analogWrite(IN2, 0);
  analogWrite(IN3, velocidade);
  analogWrite(IN4, 0);
}

void VireaEsquerda() {
  Serial.println("Robo: Esquerda");
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  delay(500);
  analogWrite(IN1, velocidade);
  analogWrite(IN2, 0);
  analogWrite(IN3, velocidade);
  analogWrite(IN4, 0);
}

void Retorne() {
  Serial.println("Robo: Girar");
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  delay(500);
  analogWrite(IN1, velocidade);
  analogWrite(IN2, 0);
  analogWrite(IN3, velocidade);
  analogWrite(IN4, 0);
}

void direcao() {
  Parar();
  ParaTras();
  Parar();
  servoSensor.write(180);
  delay(1000);
  float distEsquerda = Procurar();
  delay(500);
  servoSensor.write(0);
  delay(500);
  float distDireita = Procurar();
  delay(500);
  servoSensor.write(90);
  delay(500);
  CompareDistance(distEsquerda, distDireita);
}

void CompareDistance(float distEsquerda, float distDireita) {
  if (distDireita > distEsquerda) {
    Vireadireita();
  } else if (distEsquerda > distDireita) {
    VireaEsquerda();
  } else {
    Retorne();
  }
}