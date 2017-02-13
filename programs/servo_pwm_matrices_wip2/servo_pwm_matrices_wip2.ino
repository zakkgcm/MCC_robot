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

//initialize servoPos to standing position.
float servoPos[16] = {60, 60, 90, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 30, 60, 60};

float servoMin[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
float servoMax[16] = {100, 120, 120, 120, 120, 120, 120, 120, 120, 120, 120, 120, 120};

float servoHome[16] = {60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60};
float standPos[16] = {60, 60, 90, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 30, 60, 60};
float sitPos[16] = {45, 45, 120, 0, 60, 60, 60, 60, 60, 60, 60, 60, 60, 30, 60, 60};


void setup() {
  Serial.begin(9600);
  Serial.println("servo PWM calibrate");

  pwm.begin();
  
  pwm.setPWMFreq(50);  // Analog servos run at ~60 Hz updates

  yield();
}

void loop() {
  moveMatrix(servoPos, servoMin, 1);
  //moveMatrix(curPos, standPos, 1);
}

void moveMatrix(float *curPos, float *matrix, int stp) {
  boolean done = false;
  while (!done) {
    done = true;
    
    for (int i=0; i < 4; ++i) { //XXX: only move 0 to 4
      if (curPos[i] < matrix[i]) {
        curPos[i] += stp;
        moveServo(i, curPos[i]);
        Serial.print("Moving Servo: "); Serial.print(i); Serial.print(" to pos: "); Serial.println(curPos[i]);
        delay(1000);
        
        done = false;
      }
    }
  }
}

void sweepServo(int n, float mind, float maxd, int inc) {
  int degree = 0;
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
  float pulseLength;
  pulseLength = map(degree , 0 ,120 , SERVOMIN ,SERVOMAX);
  //Serial.print(" Moving Angle ") ; Serial.print(pulseLength); Serial.println(); 
  pwm.setPWM(servoNumber, 0, pulseLength);
  return pulseLength;
}
