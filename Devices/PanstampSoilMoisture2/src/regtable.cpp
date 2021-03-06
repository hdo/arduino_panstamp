/**
 * regtable
 *
 * Copyright (c) 2011 Daniel Berenguer <dberenguer@usapiens.com>
 * 
 * This file is part of the panStamp project.
 * 
 * panStamp  is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * any later version.
 * 
 * panStamp is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with panStamp; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301 
 * USA
 * 
 * Author: Daniel Berenguer
 * Creation date: 03/31/2011
 */

#include <EEPROM.h>
#include "product.h"
#include "panstamp.h"
#include "regtable.h"
#include "board.h"
#include "Arduino.h"

/**
 * Declaration of common callback functions
 */
DECLARE_COMMON_CALLBACKS()

/**
 * Definition of common registers
 */
DEFINE_COMMON_REGISTERS()

// forware declaration
const void updtVoltSupply(byte rId);
const void updtSensor(byte rId);


/*
 * Definition of custom registers
 */
// Voltage supply
static unsigned long voltageSupply = 3300;
static byte dtVoltSupply[2];
REGISTER regVoltSupply(dtVoltSupply, sizeof(dtVoltSupply), &updtVoltSupply, NULL);
// Sensor value register (dual sensor)
static byte dtSensor[2];
REGISTER regSensor(dtSensor, sizeof(dtSensor), &updtSensor, NULL);

/**
 * Initialize table of registers
 */
DECLARE_REGISTERS_START()
  &regVoltSupply,
  &regSensor
DECLARE_REGISTERS_END()

/**
 * Definition of common getter/setter callback functions
 */
DEFINE_COMMON_CALLBACKS()

/**
 * Definition of custom getter/setter callback functions
 */
 
/**
 * updtVoltSupply
 *
 * Measure voltage supply and update register
 *
 * 'rId'  Register ID
 */
const void updtVoltSupply(byte rId)
{  
  unsigned long result;
  
  // Read 1.1V reference against AVcc
  ADMUX = _BV(REFS0) | _BV(MUX3) | _BV(MUX2) | _BV(MUX1);
  delay(2); // Wait for Vref to settle
  ADCSRA |= _BV(ADSC); // Convert
  while (bit_is_set(ADCSRA,ADSC));
  result = ADCL;
  result |= ADCH << 8;
  result = 1126400L / result; // Back-calculate AVcc in mV
  voltageSupply = result;     // Update global variable Vcc
  
  #ifdef VOLT_SUPPLY_A7
  
  // Read voltage supply from A7
  unsigned short ref = voltageSupply;
  result = analogRead(7);
  result *= ref;
  result /= 1024;
  #endif

  /**
   * register[eId]->member can be replaced by regVoltSupply in this case since
   * no other register is going to use "updtVoltSupply" as "updater" function
   */

  // Update register value
  regTable[rId]->value[0] = (result >> 8) & 0xFF;
  regTable[rId]->value[1] = result & 0xFF;
}


uint16_t readTimer1(void) {
	TCCR1A = 0; // normal operation
	TCCR1B = 0; // timer stopped
	TCNT1H = 0;
	TCNT1L = 0;
	// start timer
	TCCR1B = _BV(CS11) | _BV(CS12); // external clock on falling edge
	delay(100);
	// stop timer
	TCCR1B = 0;
	return TCNT1;
}

/**
 * updtSensor
 *
 * Measure sensor data and update register
 *
 * 'rId'  Register ID
 */
const void updtSensor(byte rId)
{
  // Power sensors
  digitalWrite(POWER_0_PIN, HIGH);
  delay(200);
  
  /*
   * low moisture -> high value
   * low moisture -> low value
   * so we need to invert the value
   * divide by 10 to decrease sensitivity
   */
  uint16_t value = (0xFFFF - readTimer1()) / 10;

  // Update register tempValue
  dtSensor[0] = (value >> 8) & 0xFF;
  dtSensor[1] = value & 0xFF;

  // Unpower sensors
  digitalWrite(POWER_0_PIN, LOW);
}


