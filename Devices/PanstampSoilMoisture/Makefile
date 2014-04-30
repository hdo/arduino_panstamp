include ../../Makefile.common

# Sources

CPP_SRC += \
regtable.cpp \
soilmoisture.cpp \
main.cpp

# Project name
PROJ_NAME=panstampsoilmoisture
OUTPATH=build


vpath %.c src
vpath %.cpp src
vpath %.a ../../lib

# Includes
CFLAGS += -Isrc
CFLAGS += -I../../lib/arduinocore/src
CFLAGS += -I../../lib/arduinoeeprom/src
CFLAGS += -I../../lib/timerone/src
CFLAGS += -I../../lib/panstamp/src

CXXFLAGS += -Isrc
CXXFLAGS += -I../../lib/arduinocore/src
CXXFLAGS += -I../../lib/arduinoeeprom/src
CXXFLAGS += -I../../lib/timerone/src
CXXFLAGS += -I../../lib/panstamp/src

# Library paths
LIBPATHS = -L../../lib/arduinocore -L../../lib/arduinoeeprom -L../../lib/timerone -L../../lib/panstamp

# Libraries to link

# NOTE: the order is very important !!! 
LIBS  = -lpanstamp -ltimerone -larduinoeeprom -larduinocore 

OBJS = $(CPP_SRC:.cpp=.o)

###################################################

.PHONY: lib proj

flash: all 
	$(AVRDUDE) $(AVRDUDE_FLAGS) $(AVRDUDE_WRITE_FLASH)

all: lib proj 
	$(SIZE) $(OUTPATH)/$(PROJ_NAME).elf

lib:
	$(MAKE) -C ../../lib 

proj: prepare $(OUTPATH)/$(PROJ_NAME).elf
	

$(OUTPATH)/$(PROJ_NAME).elf: $(CPP_SRC)
	mkdir -p $(OUTPATH)	
	#bash ./scripts/setbuildid.script
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LIBPATHS) $(LIBS)
	$(OBJCOPY) -j .text  -j .data -O ihex $(OUTPATH)/$(PROJ_NAME).elf $(OUTPATH)/$(PROJ_NAME).hex
	
cleanall: clean
	$(MAKE) clean -C ../../lib # Remove this line if you don't want to clean the libs as well

prepare:
	rm -f $(OUTPATH)/$(PROJ_NAME).elf
	rm -f $(OUTPATH)/$(PROJ_NAME).hex
	rm -f $(OUTPATH)/$(PROJ_NAME).bin
	
clean:
	rm -f *.o
	rm -f $(OUTPATH)/$(PROJ_NAME).elf
	rm -f $(OUTPATH)/$(PROJ_NAME).hex
	rm -f $(OUTPATH)/$(PROJ_NAME).bin
