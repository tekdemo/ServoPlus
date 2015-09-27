#include <Servo.h>
#include <ServoPlus.h>

ServoPlus left;
ServoPlus right;

void setup(){

	//Our demo system doesn't allow a full range of a servo, so restrict it.
	//This is based on standard "servo" ranges.
	left.restrict(90,180);
	
	
	//Our off-side servo has the same range of motion, but it's reversed. We have functions for that.  
	left.mirror();
	//Let's take advantage of the mirroring to take advantage of the newly specified mirror
	right.restrictMapped(90,180);

	//Aw, shoot. We also got our servo splines set up a bit wrong. 
	//Let's adjust one of them so they have the same alignment
	left.offset(-2);
	
	//OK, physical bits seem to be in order, let's simplify how we do think about things. 
	//Our system has a 1/2 gear reduction, so let's factor that in so our end angle matches the 
	//servo's write angle.
	left.map(0,180,0,90);
	right.map(0,180,0,90);
	
	//At long last, we can start putting our servos to work
	left.attach(9);
	left.attach(10);
	
}



void loop(){

	//And, now we can just do a simple write to the servos, and all the work is done. 
	//Our servo will refuse to go into places it shouldn't.
	for(int i=0; i++;i==180){
		left.write(i);
		right.write(i);
		delay(15);
	}

	for(int  i=180; i--;i==0){
		left.write(i);
		right.write(i);
		delay(15);
	}
}
