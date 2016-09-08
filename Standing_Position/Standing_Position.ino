#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
#define SERVOMIN 340
#define SERVOMAX 340

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("16 channel Servo test!");

  pwm.begin();
  
  pwm.setPWMFreq(60);  // Analog servos run at ~60 Hz updates
pwm.setPWM(0, 0, 340);
pwm.setPWM(1, 0, 340);
pwm.setPWM(2, 0, 340);
pwm.setPWM(3, 0, 340);
pwm.setPWM(4, 0, 340);
pwm.setPWM(5, 0, 340);
pwm.setPWM(6, 0, 340);
pwm.setPWM(7, 0, 340);
pwm.setPWM(8, 0, 340);
pwm.setPWM(9, 0, 340);
pwm.setPWM(10, 0, 340);
pwm.setPWM(11, 0, 340);
pwm.setPWM(12, 0, 340);
pwm.setPWM(13, 0, 340);
pwm.setPWM(14, 0, 340);
pwm.setPWM(15, 0, 340);
  yield();
}

void loop() {
  // put your main code here, to run repeatedly:

}
