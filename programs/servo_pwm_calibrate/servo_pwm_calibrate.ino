/*************************************************** 
  This is an example for our Adafruit 16-channel PWM & Servo driver
  Servo test - this will drive 16 servos, one after the other

  Pick one up today in the adafruit shop!
  ------> http://www.adafruit.com/products/815

  These displays use I2C to communicate, 2 pins are required to  
  interface. For Arduino UNOs, thats SCL -> Analog 5, SDA -> Analog 4

  Adafruit invests time and resources providing this open source code, 
  please support Adafruit and open-source hardware by purchasing 
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.  
  BSD license, all text above must be included in any redistribution
 ****************************************************/

#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

// called this way, it uses the default address 0x40
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
// you can also call it with a different address you want
//Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x41);

// Depending on your servo make, the pulse width min and max may vary, you 
// want these to be as small/large as possible without hitting the hard stop
// for max range. You'll have to tweak them as necessary to match the servos you
// have!
#define SERVOMIN  200 // this is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX  465 // this is the 'maximum' pulse length count (out of 4096)

// our servo #
uint8_t servonum = 0;

void setup() {
  Serial.begin(9600);
  Serial.println("servo PWM calibrate");

  pwm.begin();
  
  pwm.setPWMFreq(50);  // Analog servos run at ~60 Hz updates
  
  
  yield();
}

void loop() {
   //sweepServo(12, 0, 120, .1);
   //sweepServo(1, 0, 120, 1);
   //sweepServo(2, 0, 120, 1);
   //sweepServo(3, 0, 120, .5);
   moveServo(3,60);
}

void homePos() {
  // Left Leg
  moveServo(0, 60);
  moveServo(1, 60);
  moveServo(2, 60);
  moveServo(3, 60);
  moveServo(4, 60);

  // Left Arm
  moveServo(5, 60);
  moveServo(6, 60);
  moveServo(7, 60);
  
  // Right Arm
  moveServo(8, 60);
  moveServo(9, 60);
  moveServo(10, 60);

  // Right Leg
  moveServo(11, 60);
  moveServo(12, 60);
  moveServo(13, 60);
  moveServo(14, 60);
  moveServo(15, 60);
}

void sweepServo(int n, float mind, float maxd, float inc) {
  float degree = 0;
  for (degree = mind; degree < maxd; degree = degree + inc) {
    moveServo(n, degree);
    delay(1);
  }
  for (degree = maxd; degree > mind; degree = degree - inc) {
    moveServo(n, degree);
    delay(1);
  }
}

void sweepMotors(int n) {
  int degree;
  int nMotors;
  
  for(nMotors = 0; nMotors <= n; nMotors++) {
       for(degree = 0; degree <= 120; degree++){
          moveServo(nMotors, degree);
          moveServo(nMotors+1, degree);
          moveServo(nMotors+2, degree);
          delay(50);
        }
    
       for(degree = 120; degree > 0; degree--){
          moveServo(nMotors, degree);
          moveServo(nMotors+1, degree);
          moveServo(nMotors+2, degree);
          delay(50);
        }
    }
   
}

int moveServo(int servoNumber, float degree)
{
  long pulseLength;
  pulseLength = map(degree , 0 ,120 , SERVOMIN ,SERVOMAX);
  Serial.print(" Moving Angle ") ; Serial.print(pulseLength); Serial.println(); 
  pwm.setPWM(servoNumber, 0, pulseLength);
  return pulseLength;
}
