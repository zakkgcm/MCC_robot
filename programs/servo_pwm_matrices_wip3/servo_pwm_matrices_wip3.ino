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

// old pwm min and max
//#define SERVOMIN  200 // this is the 'minimum' pulse length count (out of 4096)
//#define SERVOMAX  465 // this is the 'maximum' pulse length count (out of 4096)

#define SERVOMIN  150 // this is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX  600 // this is the 'maximum' pulse length count (out of 4096)

double servoPos[16] = {90, 90, 90, 90, 90, 90, 90, 90, 90, 90, 90, 90, 90, 90, 90, 90};
double servoMin[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
double servoMax[16] = {180, 180, 180, 180, 180, 180, 180, 180, 180, 180, 180, 180, 180, 180, 180, 180};
double homePos[16] = {90, 90, 90, 90, 90, 90, 90, 90, 90, 90, 90, 90, 90, 90, 90, 90};
double standPos[16] = {90, 90, 120, 60, 90, 90, 90, 90, 90, 90, 90, 90, 120, 60, 90, 90};
double sitPos[16] = {90, 90, 180, 0, 90, 90, 90, 90, 90, 90, 90, 90, 90, 30, 90, 90};
//double kickBack[16] = {90, 90, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
//double kickForward[16] = {90, 90, 180, 180, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
double kickBack[16] = {90, 0, 90, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 90, 0, 90};
double kickForward[16] = {90, 180, 90, 180, 0, 0, 0, 0, 0, 0, 0, 0, 180, 90, 180, 90};

double storage[16] = {90, 90, 180, 0, 0, 0, 0, 0, 0, 0, 0, 0, 180, 0, 90, 90};
double squat[16] = {90, 140, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 180, 180, 40, 90};

double servoStp[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};


void setup() {
  Serial.begin(9600);
  Serial.println("servo PWM calibrate");

  pwm.begin();

  pwm.setPWMFreq(60);  // Analog servos run at ~60 Hz updates


  //yield();

  //moveMatrix(squat, 5);  
  //moveMatrix(standPos, 1);
  //moveMatrix(kickForward, 4);
  
}

void loop() {
  moveMatrix(squat, 1);
  moveMatrix(homePos, 1);
  
  //moveMatrix(kickForward, 5);
  //moveMatrix(kickBack, 5);
}

float calcPdiff(double currPos, double finalPos) {
    float pdiff = finalPos - currPos; //pdiff = position difference
    int isNeg = currPos > finalPos;
    
    if(isNeg){
      pdiff = pdiff * -1;
      Serial.print("");//for some reason this prevents a compiler error - spill over ... 'POINTER REGS' 
    }

    return pdiff;
}

void moveMatrix(double *matrix, float haste) {
  boolean done = false;
  
  float stp = 0;
  float pdiff = 0;
  //Serial.println("Moving Servos.");

  // Find Max Pdiff
  float pdiffMax = 0;
  for (int i=0; i < 16; ++i) {
   float p = calcPdiff(servoPos[i], matrix[i]);
    
    if (p > pdiffMax){
      pdiffMax = p;
    }
  }
  //create array of step values for each servo
  for(int i=0; i < 16; ++i){
      pdiff = calcPdiff(servoPos[i], matrix[i]);
      servoStp[i] = pdiff / pdiffMax;   
      //Serial.println(servoStp[i]);
  }
 
  while (!done) {
    done = true;

    //Serial.print("Moving Servos: ");
    for (int i = 0; i < 16; ++i) { //XXX: only move 0 to 3
      //delay(250);
      
      pdiff = calcPdiff(servoPos[i], matrix[i]);
      //stp = pdiff / pdiffMax;

      //Serial.print("servoStp of: ");Serial.println(servoStp[i]);
  
      if (pdiff > servoStp[i]) {
        
        float nextStp = 0;
        
        if (servoPos[i] > matrix[i]) {
          nextStp = servoStp[i] * -1*haste;
        } else {
          nextStp = servoStp[i]*haste;
        }

        servoPos[i] += nextStp;
        moveServo(i, servoPos[i]);
        Serial.print("Moving Servo: ");Serial.print(i); Serial.print(" from pos: "); Serial.print(servoPos[i]-nextStp); 
        Serial.print(" to pos: "); Serial.print(servoPos[i]); Serial.print(" step of: ");Serial.print(nextStp);
        Serial.print(" pdiff of: ");Serial.print(pdiff);Serial.println();

        done = false;
      } else {
        moveServo(i, servoPos[i]);
        Serial.print("Servo: ");Serial.print(i); Serial.print(" Stall pos of: "); Serial.print(servoPos[i]); 
        Serial.println();
      }
    }
  }
}

void sweepServo(int n, double mind, double maxd, double inc) {
  int degree = 0;
  for (degree = mind; degree < maxd; degree = degree + inc) {
    moveServo(n, degree);
    delay(10);
  }
  for (degree = maxd; degree > mind; degree = degree - inc) {
    moveServo(n, degree);
    delay(10);
  }
}

void sweepMotors(int n) {
  int degree;
  int nMotors;

  for (nMotors = 0; nMotors <= n; nMotors++) {
    for (degree = 0; degree <= 180; degree++) {
      moveServo(nMotors, degree);
      moveServo(nMotors + 1, degree);
      moveServo(nMotors + 2, degree);
      delay(50);
    }

    for (degree = 180; degree > 0; degree--) {
      moveServo(nMotors, degree);
      moveServo(nMotors + 1, degree);
      moveServo(nMotors + 2, degree);
      delay(50);
    }
  }

}

int moveServo(int servoNumber, float degree)
{
  float pulseLength;
  pulseLength = map(degree , 0 , 180 , SERVOMIN , SERVOMAX);
  //Serial.print(" Moving Angle ") ; Serial.print(pulseLength); Serial.println();
  pwm.setPWM(servoNumber, 0, pulseLength);
  return pulseLength;
}
