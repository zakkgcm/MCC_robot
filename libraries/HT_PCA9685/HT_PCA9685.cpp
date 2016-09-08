/***************************************************
  PCA9685 PWM/Servo Library

  Copyright (c) 2014 www.hobbytronics.co.uk  All right reserved.

  Arduino Library for the Hobbytronics PCA9685 PWM/Servo board
  V1.0 Nov 2014
  
  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
****************************************************/

#include <Wire.h>
#include <HT_PCA9685.h>

HT_PCA9685::HT_PCA9685(uint8_t i2c_address) {
  _i2caddr = i2c_address;
}

void HT_PCA9685::begin(void) {
	Wire.begin();
	write_byte(PCA9685_MODE1_REG, 0x00);
}

void HT_PCA9685::PWMFreq(float frequency) {

	// Set PWM Frequency by setting the Prescale value (min 3, max 255)
	// Equates to max frequency approx 1.5kHz - varies depending on internal osc
	//            min frequency 24 Hz
	// Setting the PWM Frequency also turns the device on

	// Set limits so we don't get out of range results
	if(frequency < 16) frequency = 16;
	if(frequency > 1500) frequency = 1500;

	// Retain frequency setting and calculate 1ms duration for use in servo calculations
	_pwm_frequency = frequency;
	_duration_1ms = ((4096*_pwm_frequency)/1000);  // This is 1ms duration
  
	// Frequencies up to 1KHz use external 16MHz input
	// Frequencies above 1KHz use internal 25MHz osc which is not accurate - power off reset required
	float prescale;
	if(frequency <=1000) prescale = 16000000;
	else prescale = 25000000;

	prescale /= 4096;
	prescale /= frequency;
	prescale -= 1;
 
	uint8_t prescale_8 = floor(prescale + 0.5);

	write_byte(PCA9685_MODE1_REG, 0x10); 				// set sleep register
	if(frequency <=1000) write_byte(PCA9685_MODE1_REG, 0x50); 	// set to external clock - can only go back to internal via power off reset	
	write_byte(PCA9685_PRESCALE_REG, prescale_8); 	// set the prescaler
	write_byte(PCA9685_MODE1_REG, 0x00); 				// Turn off sleep
	delay(1);													// Wait 500 uS
	write_byte(PCA9685_MODE1_REG, 0xA1); 				// Set Auto-Increment on, enable restart

}

void HT_PCA9685::PWM(uint8_t port, uint16_t duration) {
	// Set PWM Duration
	// Duration is from 0 to 4095 (OFF to fully ON)

	if(duration>4095) duration=4095;		// Ensure within bounds
	Wire.beginTransmission(_i2caddr);
	#if ARDUINO >= 100  	
	Wire.write(LED0_REG+(4*port));
	Wire.write(0);
	Wire.write(0);	
	Wire.write(duration);					// Send Low Byte
	Wire.write(duration>>8);				// Send High Byte
	#else
	Wire.send(LED0_REG+(4*port));
	Wire.send(0);
	Wire.send(0);		
	Wire.send(duration);
	Wire.send(duration>>8);	
	#endif
	Wire.endTransmission();
}

void HT_PCA9685::servo(uint8_t port, uint8_t servo_type, uint16_t degrees) {
	// Set Servo values
	// Degrees is from 0 to 180
	// servo_type: 0 = standard 1ms to 2ms
	//             1 = extended 0.6ms to 2.4ms
	//             2 = extended 0.8ms to 2.2ms	
   uint16_t duration;
	
   if(degrees>180) degrees=180;		// Ensure within bounds
	
   switch (servo_type) {
      case 0:              // Standard Servo 1ms to 2ms
         duration = _duration_1ms + ((_duration_1ms*degrees)/180);
         break;
       
      case 1:              // Extended Servo 0.6ms to 2.4ms, i.e. 1.8ms from 0 to 180
         //duration = (_duration_1ms*0.6) + ((_duration_1ms*1.8*degrees)/180); simplified to..
         duration = (_duration_1ms*0.6) + ((_duration_1ms*degrees)/100);       
         break;
       
      case 2:              // Extended Servo 0.8ms to 2.2ms, i.e. 1.4ms from 0 to 180
         //duration = (_duration_1ms*0.8) + ((_duration_1ms*1.4*degrees)/180); simplified to..
         duration = (_duration_1ms*0.8) + ((_duration_1ms*degrees)/128);       
         break;
   }
	 
	Wire.beginTransmission(_i2caddr);
	#if ARDUINO >= 100  	
	Wire.write(LED0_REG+(4*port));
	Wire.write(0);
	Wire.write(0);	
	Wire.write(duration);					// Send Low Byte
	Wire.write(duration>>8);				// Send High Byte
	#else
	Wire.send(LED0_REG+(4*port));
	Wire.send(0);
	Wire.send(0);		
	Wire.send(duration);
	Wire.send(duration>>8);	
	#endif
	Wire.endTransmission();
}

uint8_t HT_PCA9685::read_byte(uint8_t regaddr) {
	Wire.beginTransmission(_i2caddr);
	#if ARDUINO >= 100  
	Wire.write(regaddr);
	#else
   Wire.send(regaddr); 
	#endif		
	Wire.endTransmission();
	Wire.requestFrom((uint8_t)_i2caddr, (uint8_t)1);	// Request 1 byte
	return Wire.read();
}

void HT_PCA9685::write_byte(uint8_t regaddr, uint8_t data) {
	Wire.beginTransmission(_i2caddr);
	#if ARDUINO >= 100   
	Wire.write(regaddr);
	Wire.write(data);
	#else
   Wire.send(regaddr); 
	Wire.send(data);	
	#endif		
	Wire.endTransmission();
}