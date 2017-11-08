#include <Stepper.h>
#include <Servo.h> 
#include <Ultrasonic.h>

Servo servoMotor;
const int stepsPerRevolution = 500;
const int portaLDR2 = A4; // LDR DO TERCEIRO EVENTO
const int portaLDR = A5; // LDR DO SEGUNDO EVENTO
const int portaTransistor = 12;

Stepper myStepper(stepsPerRevolution, 8,10,9,11); // STEPPER DO ELEVADOR
Stepper myStepper2(stepsPerRevolution, 1,3,2,4); // STEPPER DA PONTE

Ultrasonic ultrasonic(6, 7); //6 -> trigger; 7 -> echo;

boolean waitForFirstEvent = true;
boolean waitForSecondEvent = true;

void setup(){
  
  Serial.begin(9600);
  myStepper.setSpeed(60);
  myStepper2.setSpeed(60);
  servoMotor.attach(7);
  servoMotor.write(0);
  pinMode(portaTransistor, OUTPUT);
  digitalWrite(portaTransistor, LOW);
  
}

void loop(){
  
  if(waitForFirstEvent) firstEventTrigger();
  else if(waitForSecondEvent) secondEventTrigger();
  else if(!waitForFirstEvent && !waitForSecondEvent) finish();
  delay(50);
  
}

int verificaLuz(){

  Serial.println(analogRead(portaLDR));
  return analogRead(portaLDR);  
  
}

int verificaSegundaLuz(){

  Serial.println(analogRead(portaLDR2));
  return analogRead(portaLDR2);  
  
}

void firstEventTrigger(){

  long distancia = 7;
  long distanciaUltrassom = ultrasonic.distanceRead();

  Serial.println(distanciaUltrassom);
  
  if(distanciaUltrassom < distancia && distanciaUltrassom != 0){
    
    waitForFirstEvent = false;

    delay(1000);

    //Supondo que 5 voltas são o suficiente pra puxar o barbante todo.
    
    for(int i = 0; i < 20; i++){
      if(i == 16) myStepper.setSpeed(30); //Reduz a velocidade quando estiver na última volta.
      myStepper.step(512); //90º sentido anti-horário
    }
    
  }
  
}

void secondEventTrigger(){
  
  if(verificaLuz() < 900) return;

  waitForSecondEvent = false;

  delay(500);

  myStepper2.step(341); // ~60º sentido anti-horário (ABAIXA A PONTE).

  delay(500);

  servoMotor.write(90);
  
}

void thirdEventTrigger(){

  if(verificaSegundaLuz() < 900) return;

  digitalWrite(portaTransistor, HIGH);
  
}

void finish(){

  delay(1000);

  // Volta stepper do elevador ao normal.
  myStepper.setSpeed(60);

  for(int i = 0; i < 20; i++){
    if(i == 16) myStepper.setSpeed(30); //Reduz a velocidade quando estiver na última volta.
    myStepper.step(-512); //90º sentido horário
  }

  // Volta servo e stepper da ponte ao normal.
  servoMotor.write(0);
  myStepper2.step(-341);

  // Desliga leds.
  digitalWrite(portaTransistor, LOW);
  
}

