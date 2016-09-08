/***************************************************
  PCA9685 PWM/Servo Library
  SERVO Example Program
  
  Set PWM Frequency to 50Hz
  Set servo outputs to the following
  
  Channel	 Output
  0			  0 degrees (1ms)    - standard servo
  1			 90 degrees (1.5ms)  - standard servo
  2			180 degrees (2ms)    - standard servo
  3			  0 degrees (0.6ms)  - extended range servo type 1
  4			 90 degrees (1.5ms)  - extended range servo type 1
  5			180 degrees (2.4ms)  - extended range servo type 1
  6			  0 degrees (0.8ms)  - extended range servo type 2
  7			 90 degrees (1.5ms)  - extended range servo type 2
  8			180 degrees (2.2ms)  - extended range servo type 2
  
  Check on your particular servo for the pulse width values it requires
  
  Copyright (c) 2014 www.hobbytronics.co.uk  All right reserved.

****************************************************/

#include <Wire.h>
#include <HT_PCA9685.h>

HT_PCA9685 pwm = HT_PCA9685(0x40);

void setup() {

   pwm.begin();
   pwm.PWMFreq(50); // 50Hz Frequency - can go up to 400Hz max for servo's
    
   // Standard servo outputs (1ms to 2ms)
	pwm.servo(0,0,0);
	pwm.servo(1,0,90);
	pwm.servo(2,0,180);
	
   // Extended servo outputs type1 (0.6ms to 2.4ms)
	pwm.servo(3,1,0);
	pwm.servo(4,1,90);
	pwm.servo(5,1,180);	
	
   // Extended servo outputs type2 (0.8ms to 2.2ms)
	pwm.servo(6,2,0);
	pwm.servo(7,2,90);
	pwm.servo(8,2,180);		
}

void loop() {

}