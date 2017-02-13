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

float pos = 41;
float increment = 1;
float pos2 = 41;
float increment2 = 1;

unsigned long time;
unsigned long lastUpdate = 0;
unsigned long updateInterval = 15;

unsigned long lastUpdate2 = 0;
unsigned long updateInterval2 = 25;


void setup() {
  Serial.begin(9600);
  Serial.println("servo PWM calibrate");

  pwm.begin();

  pwm.setPWMFreq(60);  // Analog servos run at ~60 Hz updates
  
  //yield();
  
}

void loop() {
  
  
  if((millis() - lastUpdate) > updateInterval)  // time to update
    {
      lastUpdate = millis();
      
      pos += increment;
      moveServo(0, pos);
      
      Serial.println(pos);
      if ((pos >= 100) || (pos <= 40)) // end of sweep
      {
        // reverse direction
        increment = -increment;
      }
    }

  if((millis() - lastUpdate2) > updateInterval2)  // time to update
    {
      lastUpdate2 = millis();
      
      pos2 += increment2;
      moveServo(15, pos2);
      
      Serial.println(pos2);
      if ((pos2 >= 100) || (pos <= 40)) // end of sweep
      {
        // reverse direction
        increment2 = -increment2;
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
