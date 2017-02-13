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
#define SERVOMIN  150 // this is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX  600 // this is the 'maximum' pulse length count (out of 4096)

// our servo # counter
uint8_t servonum = 7;

void setup() {
  Serial.begin(9600);
  Serial.println("16 channel Servo test!");

  pwm.begin();
  
  pwm.setPWMFreq(60);  // Analog servos run at ~60 Hz updates

  //yield();
}



void loop() {
  // Drive each servo one at a time
  Serial.println(servonum);
//  for (uint16_t pulselen = SERVOMIN; pulselen < SERVOMAX; pulselen++) {
//    pwm.setPWM(servonum, 0, pulselen);
//    Serial.print("Servo min: ");Serial.println(pulselen);
//    delay(100);
//  }

  
//  for (uint16_t pulselen = SERVOMAX; pulselen > SERVOMIN; pulselen--) {
//    pwm.setPWM(servonum, 0, pulselen);
//    Serial.print("Servo max: ");Serial.println(pulselen);
//    delay(10);
//  }

//moveServo(7,0);
sweepServo(7,0, 180, 1);
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

