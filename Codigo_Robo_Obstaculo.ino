// Adiciona a biblitoeca Servo
#include <Servo.h>

//Definindo os pinos do sensor
#define trigPin 4
#define echoPin 3

// motor um
#define in1  9
#define in2  8

// motor dois
#define in3  7
#define in4  6

// Crie um objeto Servo para controlar o Servo.
Servo servoSensor;

//função para procurar obtasculos
int Procurar (void) {
  
// variavael para quartar a duração do retorno do som
float duracao = 0.0;
  
// variavael para quartar a distancia
float CM = 0.0;
  
digitalWrite(trigPin, LOW);
delayMicroseconds(2);
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);

//Captura a duração em tempo do retorno do som.
duracao = pulseIn(echoPin, HIGH);

//Calcula a distância em centimetros
CM = (duracao / 58.8);
Serial.print("Distancia em CM: ");
  
//Imprimi no monitor serial a distancia
Serial.println(CM);               
return CM;
}

//variavel de Distâncias de ambos os lados
int DistanciaDireita, DistanciaEsquerda;

//variavel para guardar a distancia
float Distancia = 0.00;

//Velocidades dos motores
int velocidadeMotorUm = 80;
int velocidadeMotorDois = 95;

void setup() {

Serial.begin(9600);
  
//Define o servo na porta 7
servoSensor.attach(7); 
  
pinMode(in1, OUTPUT);
pinMode(in2, OUTPUT);
pinMode(in3, OUTPUT);
pinMode(in4, OUTPUT);
  
pinMode(trigPin, OUTPUT);
pinMode(echoPin, INPUT); 
}

void loop() {
  
//Gira o Servo com o sensor a 90 graus
servoSensor.write (90);
delay (1000);

//Medindo a Distancia em CM.
Distancia = Procurar ();
  
//Se há obstáculo encontrado a menos de 40cm.  
if (Distancia < 40) {

//Mover o robo para desviar do obstaculo
direcao ();
}
//Se o obstáculo for encontrado entre a mais de 40cm 
else if (Distancia >= 40){
  
//Robô se move para a direção da Frente.  
Frente ();
}  
}

// Função para pegar as distancias de cada direção
void direcao () {        
Parar ();   
ParaTras ();
Parar ();   
  
//Gira o Servo com o sensor a 180 graus
servoSensor.write (180);
delay (1000);
 
//Defina a Distancia da Esquerda 
DistanciaEsquerda = Procurar ();                  
delay (500);
  
//Gira o Servo com o sensor a 0 graus
servoSensor.write (0);
delay (500);
  
//Defina a Distancia da Direita
DistanciaDireita = Procurar ();
delay (500);

//Gira o Servo com o sensor a 90 graus
servoSensor.write (90);                           
delay (500);
  
//Encontre a distância mais longa.
CompareDistance ();                               
}
//Função para calcular qual a distancia é melhor para o robô ir
void CompareDistance () {

//Se a direita for a melhor opção ele irá para a direita
if (DistanciaDireita > DistanciaEsquerda) {
Vireadireita (); 
}

//Se a esquerda for a melhor opção ele irá para a esquerda 
else if (DistanciaEsquerda > DistanciaDireita) {
VireaEsquerda ();
}

//Se a esquerda e a direita tiverem obstaculos ele vira para trás
else {
Retorne ();
}
}

//Função para fazer o carro parar
void Parar()
{
Serial.println("Robo: Parar");
digitalWrite(in1, LOW); 
digitalWrite(in2, LOW);
digitalWrite(in3, LOW);
digitalWrite(in4, LOW);
delay(200);
}

//Função para fazer o robô andar para frente
void Frente()
{
    Serial.println("Robo: Frente");
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
    analogWrite(velocidadeMotorUm, velocidadeMotorDois);
}

//Função que faz o robô andar para trás
void ParaTras()
{
    Serial.println("Robo: Ré");
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);
    analogWrite(velocidadeMotorUm, velocidadeMotorDois);
}

//Função que faz o robô virar à direita
void Vireadireita()
{
    Serial.println("Robo: Direita");
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
    analogWrite(velocidadeMotorUm, velocidadeMotorDois);
}

//Função que faz o robô virar à esquerda
void VireaEsquerda()
{
    Serial.println("Robo: Esquerda");
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
    analogWrite(velocidadeMotorUm, velocidadeMotorDois);
}

//Função para o robô virar para o outro lado
void Retorne()
{
    Serial.println("Robo: Girar");
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
    analogWrite(velocidadeMotorUm, velocidadeMotorDois);
}