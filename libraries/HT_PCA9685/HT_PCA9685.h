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

#ifndef _HT_PCA9685_H
#define _HT_PCA9685_H

#if ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#define PCA9685_MODE1_REG 		0x00
#define PCA9685_PRESCALE_REG 	0xFE
#define LED0_REG 					0x06


class HT_PCA9685 {
	public:
		HT_PCA9685(uint8_t i2c_address = 0x40);	// Default address
		void begin(void);
		void PWMFreq(float freq);
		void PWM(uint8_t port, uint16_t duration);
		void servo(uint8_t port, uint8_t servo_type, uint16_t degrees);

	private:
		uint8_t _i2caddr;
		float _pwm_frequency;		
		float _duration_1ms;
		uint8_t read_byte(uint8_t regaddr);
		void write_byte(uint8_t regaddr, uint8_t data);
};

#endif