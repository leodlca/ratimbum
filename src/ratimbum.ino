#include <Ultrasonic.h>
#include <Stepper.h> 

const int stepsPerRevolution = 500; 
 
Ultrasonic ultrasonic(6, 7); //6 -> trigger; 7 -> echo;
Stepper myStepper(stepsPerRevolution, 8,10,9,11); 

boolean waitForFirstEvent = true;

void setup() {
  Serial.begin(9600);
  myStepper.setSpeed(60);
}
 
void loop() {
  if(waitForFirstEvent) firstEventTrigger();
}

void firstEventTrigger(){

  long distancia = 7.5;
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

    delay(10000);

    myStepper.setSpeed(60);

    for(int i = 0; i < 20; i++){
      if(i == 16) myStepper.setSpeed(30); //Reduz a velocidade quando estiver na última volta.
      myStepper.step(-512); //90º sentido horário
    }
    
  }
  
}

