#include <Stepper.h>
#include <Servo.h> 
#include <Ultrasonic.h>

Servo servoMotor;

const int stepsPerRevolution = 500;
const int portaLDR2 = A5; // LDR DO TERCEIRO EVENTO
const int portaLDR = A4; // LDR DO SEGUNDO EVENTO
const int portaTransistor = 13;

Stepper myStepper(stepsPerRevolution, 8,10,9,11); // STEPPER DO ELEVADOR
Stepper myStepper2(stepsPerRevolution, 4,6,5,7); // STEPPER DA PONTE

Ultrasonic ultrasonic(2, 3); //2 -> trigger; 3 -> echo;

boolean waitForFirstEvent = true;
boolean waitForSecondEvent = true;
boolean waitForThirdEvent = true;
boolean waitForFinish = true;

void setup(){
  
  Serial.begin(9600);
  myStepper.setSpeed(60);
  myStepper2.setSpeed(60);
  servoMotor.attach(12);
  servoMotor.write(0);
  pinMode(portaTransistor, OUTPUT);
  digitalWrite(portaTransistor, LOW);
  
}

void loop(){

  // Todos os eventos ocorrem de forma síncrona, um após o outro, um bloqueando o outro para que não hajam erros.
  
  if(waitForFirstEvent) firstEventTrigger();
  else if(waitForSecondEvent) secondEventTrigger();
  else if(waitForThirdEvent) thirdEventTrigger();
  else if(!waitForFirstEvent && !waitForSecondEvent && !waitForThirdEvent && waitForFinish) finish();
  delay(50);
  
}

int verificaLuz(){

  return analogRead(portaLDR);  
  
}

int verificaSegundaLuz(){

  return analogRead(portaLDR2);  
  
}

void firstEventTrigger(){

  // Quando a bolinha se aproxima do sensor, liga o elevador.

  long distancia = 8;
  long distanciaUltrassom = ultrasonic.distanceRead();

  Serial.println(distanciaUltrassom);
  
  if(distanciaUltrassom < distancia && distanciaUltrassom != 0){
    
    waitForFirstEvent = false;

    delay(1000);

    // Supondo que 5 voltas são o suficiente pra puxar o barbante todo.
    
    for(int i = 0; i < 20; i++){
      if(i == 16) myStepper.setSpeed(30); // Reduz a velocidade quando estiver na última volta.
      myStepper.step(512); // 90º sentido anti-horário
    }
    
  }
  
}

void secondEventTrigger(){

  // Verifica o 1º LDR, abaixa ponte pelo 2º Step Motor, e libera bolinha pelo servo.
  
  if(verificaLuz() < 300) return;

  waitForSecondEvent = false;

  delay(500);

  myStepper2.step(341); // ~60º sentido anti-horário (ABAIXA A PONTE).

  delay(500);

  servoMotor.write(85);
  
}

void thirdEventTrigger(){

  // Verifica 2º LDR e liga LED através do transistor que controla o rele.

  if(verificaSegundaLuz() < 300) return;

  waitForThirdEvent = false;

  digitalWrite(portaTransistor, HIGH);
  
}

void finish(){

  waitForFinish = false;

  delay(1000);

  // Volta stepper do elevador ao normal.
  myStepper.setSpeed(60);

  for(int i = 0; i < 20; i++){
    if(i == 16) myStepper.setSpeed(30); // Reduz a velocidade quando estiver na última volta.
    myStepper.step(-512); // 90º sentido horário
  }
    delay(1000);

  // Volta servo e stepper da ponte ao normal.
  servoMotor.write(0);
  myStepper2.step(-341);

  // Desliga leds.
  digitalWrite(portaTransistor, LOW);

  // Reinicia todas as flags para repetir o circuito.
  waitForFinish = true;
  waitForFirstEvent = true;
  waitForSecondEvent = true;
  waitForThirdEvent = true;
  
}
