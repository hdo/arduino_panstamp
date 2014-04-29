include ../Makefile.common

# Build all libraries

all:
	$(MAKE) -C arduinocore
	$(MAKE) -C arduinoeeprom
	$(MAKE) -C timerone
	$(MAKE) -C panstamp

clean:
	$(MAKE) clean -C arduinocore
	$(MAKE) clean -C arduinoeeprom
	$(MAKE) clean -C timerone
	$(MAKE) clean -C panstamp
	