#include <Servo.h>
#include "ServoPlus.h"

//Testing sketch

ServoPlus servo;

void setup(){
  servo.attach(9);
  
  servo.write(90);
  //servo.restrict(30,90);
  servo.mirror();
  
  servo.map(0,180,45,135);
  
}


void loop(){
  
  for (int i=0; i<180; i++){
    servo.write(i); 
    delay(20);
  }
  
}
  
