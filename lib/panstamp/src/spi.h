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
 * Creation date: 03/03/2011
 */

#ifndef _SPI_H
#define _SPI_H

#include "Arduino.h"


/**
 * Macros
 */
// Wait until SPI operation is terminated
#define wait_Spi()  while(!(SPSR & _BV(SPIF)))

/**
 * Class: SPI
 * 
 * Description:
 * Basic SPI class
 */
class SPI
{
  public:
    /**
     * init
     * 
     * SPI initialization
     */
    void init();

    /**
     * send
     * 
     * Send byte via SPI
     * 
     * 'value'	Value to be sent
     * 
     * Return:
     * 	Response received from SPI slave
     */
    byte send(byte value);
};
#endif
