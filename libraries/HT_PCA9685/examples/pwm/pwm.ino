/***************************************************
  PCA9685 PWM/Servo Library
  PWM Example Program
  
  Set PWM Frequency to 1kHz
  Set first 15 channel outputs to a step value 
  Set last channel (15) to sweep
  
  Copyright (c) 2014 www.hobbytronics.co.uk  All right reserved.

****************************************************/

#include <Wire.h>
#include <HT_PCA9685.h>

HT_PCA9685 pwm = HT_PCA9685(0x40);

void setup() {

   pwm.begin();
   pwm.PWMFreq(1000); // 1kHz
    
   // set each output to a step value so we have 16 steps
   for (unsigned char channel=0; channel < 16; channel++) {
      pwm.PWM(channel, (channel * (4096/16)));
   }	 
}

void loop() {

   // Sweep channel 15 slowly up then start back at 0
   for (unsigned int i=0; i<4096; i += 16) {
      pwm.PWM(15, i);
      delay(10);
   }
}