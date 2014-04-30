#include <avr/interrupt.h>
#include <avr/io.h>
#include "myinterrupt.h"
#include "Arduino.h"

//#define myGetGDO0state()  bitRead(PORT_GDO0, BIT_GDO0)
#define myGetGDO0state()  bitRead(PINB, 0)

static volatile myVoidFuncPtr myIntFunc;

void myAttachInterrupt(void (*userFunc)(void)) {
	myIntFunc = userFunc;
	PCICR |= _BV(PCIE0);
	PCMSK0 |= _BV(PCINT0);
}

void myDetachInterrupt(void) {
	PCMSK0 &= ~_BV(PCINT0);
}


ISR(PCINT0_vect) {
	// catch falling edge
	if(!myGetGDO0state()) {
		myIntFunc();
	}
}
