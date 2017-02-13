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

// our servo # counter
uint8_t servonum = 0;

void setup() {
  Serial.begin(9600);
  Serial.println("16 channel Servo test!");

  pwm.begin();
  
  pwm.setPWMFreq(60);  // Analog servos run at ~60 Hz updates

  yield();
}

// you can use this function if you'd like to set the pulse length in seconds
// e.g. setServoPulse(0, 0.001) is a ~1 millisecond pulse width. its not precise!
void setServoPulse(uint8_t n, double pulse) {
  double pulselength;
  
  pulselength = 1000000;   // 1,000,000 us per second
  pulselength /= 60;   // 60 Hz
  Serial.print(pulselength); Serial.println(" us per period"); 
  pulselength /= 4096;  // 12 bits of resolution
  Serial.print(pulselength); Serial.println(" us per bit"); 
  pulse *= 1000;
  pulse /= pulselength;
  Serial.println(pulse);
  pwm.setPWM(n, 0, pulse);
}

void loop() 
{
//  long movingAngle;
//   movingAngle = 90; //left leg max
//   movingAngle = map(movingAngle , 0 ,180 , 150 ,600);
//  Serial.print(" Moving Angle ") ; Serial.print(movingAngle);Serial.println(); 
//  moveServo(1,movingAngle);
  //moveServo(1,90);
  moveNeutralPos();
}

// 90 degrees is physical reference standing
int moveNeutralPos()
{
moveServo(0, 60);
moveServo(1, 60);
moveServo(2, 60);

moveServo(3, 60);
moveServo(4, 60);

moveServo(5, 60);
moveServo(6, 60);

moveServo(7, 60);
moveServo(8, 60);

moveServo(9, 60);
moveServo(10, 60);

moveServo(11, 60);
moveServo(12, 60); // only leg offset

moveServo(13, 60);
moveServo(14, 60);
moveServo(15, 60);
}
int moveStandingPos()
{
moveServo(0, 60);
moveServo(1, 90);
moveServo(2, 0);

moveServo(3, 90);
moveServo(4, 90);

moveServo(5, 90);
moveServo(6, 90);

moveServo(7, 90);
moveServo(8, 90);

moveServo(9, 90);
moveServo(10, 90);

moveServo(11, 90);
moveServo(12, 80);

moveServo(13, 120);
moveServo(14, 90);
moveServo(15, 90);
}

int moveServo(int servoNumber, long degree)
{
  long pulseLength;
  pulseLength = map(degree , 0 ,120 , 0 ,255);
  Serial.print(" Moving Angle ") ; Serial.print(pulseLength); Serial.println(); 
  pwm.setPWM(servoNumber, 0, pulseLength);
  return pulseLength;
}

//int moveServo( int servoNumber, int Position)
//{
//pwm.setPWM(servoNumber, 0, Position);
//}
