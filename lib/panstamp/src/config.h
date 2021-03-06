/**
 * Copyright (c) 2011 panStamp <contact@panstamp.com>
 * 
 * This file is part of the panStamp project.
 * 
 * panStamp  is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * any later version.
 * 
 * panStamp is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public License
 * along with panStamp; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301 
 * USA
 * 
 * Author: Daniel Berenguer
 * Creation date: 10/03/2012
 */

#ifndef _CONFIG_H
#define _CONFIG_H


/**
 * SPI pins
 */
#define SPI_SS   10     // PB2 = SPI_SS
#define SPI_MOSI 11     // PB3 = MOSI
#define SPI_MISO 12     // PB4 = MISO
#define SPI_SCK  13     // PB5 = SCK
//#define GDO0	 2        // PD2 = INT0
#define GDO0	 8        // PB0 = ICP // ARDUINO style!


#define PORT_SPI_MISO  PINB
#define BIT_SPI_MISO  4

#define PORT_SPI_SS  PORTB
#define BIT_SPI_SS   2

//#define PORT_GDO0  PIND
//#define BIT_GDO0  2

// configuration for custom board
#define PORT_GDO0  PINB
#define BIT_GDO0  0


/**
 * Repeater options
 */
// Amount of transactions to be saved for evaluation before repeating a packet
// Maximum depth = 255
#define REPEATER_TABLE_DEPTH  20
// Expiration time (in ms) for any transaction
#define REPEATER_EXPIRATION_TIME  2000

#endif

