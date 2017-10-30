#include <Stepper.h>
#include <Servo.h> 

Servo servoMotor;
const int stepsPerRevolution = 500;
const int portaLDR = A5;
 
Stepper myStepper(stepsPerRevolution, 8,10,9,11); 

boolean waitForSecondEvent = true;

void setup(){
  
  Serial.begin(9600);
  myStepper.setSpeed(60);
  servoMotor.attach(7);
  servoMotor.write(0);
  
}

void loop(){
  
  if(waitForSecondEvent) secondEventTrigger();
  delay(50);
  
}

int verificaLuz(){

  Serial.println(analogRead(portaLDR));
  return analogRead(portaLDR);  
  
}

void secondEventTrigger(){
  
  if(verificaLuz() < 900) return;

  waitForSecondEvent = false;

  delay(500);

  myStepper.step(341); // ~60º sentido anti-horário (ABAIXA A PONTE).

  delay(1000);

  servoMotor.write(90);

  delay(10000);

  // Volta servo e stepper ao normal depois de 10 segundos.
  servoMotor.write(0);
  myStepper.step(-341);
  
}

