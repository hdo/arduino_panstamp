/*
 * soilmoisture
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
 * Creation date: 04/29/2013
 *
 * Device:
 * Soil Moisture sensor
 *
 * Description:
 * This application measures soil moisture from any two sensor providing an
 * analog signal
 *
 * These devices are low-power enabled so they will enter low-power mode
 * just after reading the sensor values and transmitting them over the
 * SWAP network.
 *
 * Associated Device Definition File, defining registers, endpoints and
 * configuration parameters:
 * soilmoisture.xml
 */

#include "regtable.h"
#include "panstamp.h"
#include "board.h"

/**
 * Uncomment if you are reading Vcc from A7. All battery-boards do this
 */
#define VOLT_SUPPLY_A7
#define INITIAL_SLEEP_INTERVAl 8
#define INITIAL_SLEEP_COUNT 5
#define DEFAULT_SLEEP_INTERVAL 900 // about 15 minutes

uint8_t current_sleep_count = 0;
uint8_t is_initial_sleep_interval = 1;

void set_sleep_interval(uint16_t intval) {
	// multiple of 8 is optimal (see PANSTAMP::goToSleep)
	byte interval[2] = { (intval >> 8) & 0xFF, intval & 0xFF }; // high low

	// set initial TX Interval
	panstamp.setTxInterval(interval, 1);
}

/**
 * setup
 *
 * Arduino setup function
 */
void setup() {

	//eepromToFactoryDefaults();

	// Initialize power pins
	pinMode(POWER_0_PIN, OUTPUT);
	digitalWrite(POWER_0_PIN, LOW);

	// Init panStamp
	panstamp.init();

	set_sleep_interval(INITIAL_SLEEP_INTERVAl);

	// Transmit product code
	getRegister(REGI_PRODUCTCODE)->getData();

	// Enter SYNC state
	panstamp.enterSystemState(SYSTATE_SYNC);

	// Transmit periodic Tx interval
	getRegister(REGI_TXINTERVAL)->getData();
	// Transmit power voltage
	getRegister(REGI_VOLTSUPPLY)->getData();

	// wait 5 seconds to receive commands
	delay(5000);
	// Switch to Rx OFF state
	panstamp.enterSystemState(SYSTATE_RXOFF);
}

/**
 * loop
 *
 * Arduino main loop
 */
void loop() {
	// Transmit sensor data
	getRegister(REGI_SENSOR)->getData();
	// Transmit power voltage
	getRegister(REGI_VOLTSUPPLY)->getData();

	if (current_sleep_count < INITIAL_SLEEP_COUNT) {
		current_sleep_count++;
	}
	else {
		if (is_initial_sleep_interval) {
			is_initial_sleep_interval = 0;
			set_sleep_interval(DEFAULT_SLEEP_INTERVAL);
			// send new interval info
			getRegister(REGI_TXINTERVAL)->getData();
		}
	}

	// wait 1 second to receive commands
	delay(1000);
	// Sleep
	panstamp.goToSleep();
}

