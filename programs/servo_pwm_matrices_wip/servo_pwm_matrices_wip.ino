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

double servoPos[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
double servoMin[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
double servoMax[16] = {120, 120, 120, 120, 120, 120, 120, 120, 120, 120, 120, 120, 120};
double servoHome[16] = {60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60};
double standPos[16] = {60, 60, 90, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 30, 60, 60};


void setup() {
  Serial.begin(9600);
  Serial.println("servo PWM calibrate");

  pwm.begin();
  
  pwm.setPWMFreq(50);  // Analog servos run at ~60 Hz updates
  
  
  yield();
}

void loop() {
  moveMatrix(servoPos, standPos, 1);
}

void moveMatrix(double *curPos, double *matrix, double stp) {
  boolean done = false;
  while (!done) {
    done = true;
    
    done = moveAllServos(curPos, matrix, stp);
        
        delay(1000);
        
  }
}

// This might be simplified with a class that creates a new object
// for the set of movement functions.  We can't just loop through
// the servos b/c the servos would then move syncronously (one after the other).
// We want the servos to move async (at the same time). 
boolean moveAllServos(double *curPos, double *matrix, double stp) {
  int done = 0;
  
    if(curPos[0] < matrix[0]){
      curPos[0] += stp;
      moveServo(0, curPos[0]);
    } else {
      done++;
    }
    if(curPos[1] < matrix[1]){
      curPos[1] += stp;
      moveServo(1, curPos[1]);
    } else {
      done++;
    }
    if(curPos[2] < matrix[2]){
      curPos[2] += stp;
      moveServo(2, curPos[2]);
    } else {
      done++;
    }
    if(curPos[3] < matrix[3]){
      curPos[3] += stp;
      moveServo(3, curPos[3]);
    } else {
      done++;
    }
    if(curPos[4] < matrix[4]){
      curPos[4] += stp;
      moveServo(4, curPos[4]);
    } else {
      done++;
    }
    if(curPos[5] < matrix[5]){
      curPos[5] += stp;
      moveServo(5, curPos[5]);
    } else {
      done++;
    }
    if(curPos[6] < matrix[6]){
      curPos[6] += stp;
      moveServo(6, curPos[6]);
    } else {
      done++;
    }
    if(curPos[7] < matrix[7]){
      curPos[7] += stp;
      moveServo(7, curPos[7]);
    } else {
      done++;
    }
    if(curPos[8] < matrix[8]){
      curPos[8] += stp;
      moveServo(8, curPos[8]);
    } else {
      done++;
    }
    if(curPos[9] < matrix[9]){
      curPos[9] += stp;
      moveServo(9, curPos[9]);
    } else {
      done++;
    }
    if(curPos[10] < matrix[10]){
      curPos[10] += stp;
      moveServo(10, curPos[10]);
    } else {
      done++;
    }
    if(curPos[11] < matrix[11]){
      curPos[11] += stp;
      moveServo(11, curPos[11]);
    } else {
      done++;
    }
    if(curPos[12] < matrix[12]){
      curPos[12] += stp;
      moveServo(12, curPos[12]);
    } else {
      done++;
    }
    if(curPos[13] < matrix[13]){
      curPos[13] += stp;
      moveServo(13, curPos[13]);
    } else {
      done++;
    }
    if(curPos[14] < matrix[14]){
      curPos[14] += stp;
      moveServo(14, curPos[14]);
    } else {
      done++;
    }
    if(curPos[15] < matrix[15]){
      curPos[15] += stp;
      moveServo(15, curPos[15]);
    } else {
      done++;
    }

    if(done == 16) {
        Serial.print("Servos done moving.");Serial.println();
        return true;
      } else {
        Serial.print("# servos, done v. not done : ");Serial.print(done);Serial.print("/");Serial.print(16-done);Serial.println();
        return false;
     }

}

void sweepServo(int n, double mind, double maxd, double inc) {
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

int moveServo(int servoNumber, long degree)
{
  long pulseLength = 0;
  pulseLength = map(degree , 0 ,120 , SERVOMIN ,SERVOMAX);
  Serial.print(" Moving Angle ") ; Serial.print(pulseLength); Serial.println(); 
  pwm.setPWM(servoNumber, 0, pulseLength);
  return pulseLength;
}
