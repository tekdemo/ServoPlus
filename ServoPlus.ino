#include <Arduino.h>
#include <Servo.h>
#include "ServoPlus.h"

/* Testing sketch, which verifies all the various functionality
* Note, that for verification the line `#define DEBUG` in servoplus.h must be uncommented 
*/



ServoPlus servo;

void setup() {
  servo.attach(9);

  Serial.println("Testing Constraints");


  servo.write(90);
  delay(1000);

  servo.restrict(0, 0);
  servo.write(90);
  delay(1000);

  servo.restrict(180, 180);
  servo.write(90);
  delay(1000);


  servo.restrict(0, 180);
  servo.write(90);
  delay(1000);


  Serial.println("Testing Mirror functions");

  servo.restrict(0, 180);
  servo.write(90);
  delay(1000);

  Serial.println("Mirror not set");

  servo.write(0);
  delay(1000);
  
  Serial.println("Mirror set");
  servo.mirror();
  servo.write(0);
  delay(1000);
  servo.mirror();
  


  Serial.println("Testing Map functions");

  servo.write(90);
  delay(1000);

  Serial.println("Doubling range (target 180)");
  servo.map(0,180,0,360);
  servo.write(90);
  Serial.println(servo.read());
  delay(1000);
  
  
  Serial.println("Halving range (target 45)");
  servo.map(0,180,0,90);
  servo.write(90);
  Serial.println(servo.read());
  delay(1000);

  Serial.println("Shifting range -90 to 90 (target 45)");
  servo.map(0,180,-90,90);
  servo.write(-90);
  Serial.println(servo.read());
  delay(1000);
  servo.write(0);
  Serial.println(servo.read());
  delay(1000);
  servo.write(90);
  Serial.println(servo.read());
  delay(1000);



  Serial.println("Testing Offsets (control, expect 90)");
  servo.map(0,180,0,180);
  servo.offset(0);
  servo.write(90);
  delay(1000);

  Serial.println("Testing -90 offset (expect 0)");
  servo.offset(-90);
  servo.write(90);
  delay(1000);
  
  Serial.println("Testing Offsets +90 (expect 180)");
  servo.offset(90);
  servo.write(90);
  delay(1000);


  Serial.println("Testing reads");
  servo.map(0,180,0,180);
  servo.restrict(0,180);
  servo.offset(0);
  servo.write(200);
  Serial.print("write 200, expect 180 ");
  Serial.println(servo.read());
  servo.write(-10);
  Serial.print("write -10, expect 0 ");
  Serial.println(servo.read());

  delay(1000);


}

elapsedMillis timer;
void loop() {


  for (int i = 0; i < 180; i++) {
    //servo.write(i);
    delay(20);
  }

  if (timer > 2000) {

    servo.detach();
  }
}

