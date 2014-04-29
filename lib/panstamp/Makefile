include ../../Makefile.common

# Includes
CFLAGS += -Isrc 
CFLAGS += -I../arduinocore/src
CFLAGS += -I../arduinoeeprom/src

CXXFLAGS += -Isrc 
CXXFLAGS += -I../arduinocore/src
CXXFLAGS += -I../arduinoeeprom/src

# Sources
C_SRC = 

CPP_SRC = src/calibration.cpp \
src/cc1101.cpp \
src/panstamp.cpp \
src/register.cpp \
src/repeater.cpp \
src/spi.cpp \
src/swcommand.cpp \
src/swpacket.cpp \
src/swquery.cpp \
src/swstatus.cpp  

OBJS := $(C_SRC:.c=.o) $(CPP_SRC:.cpp=.o)
LIBNAME = libpanstamp.a

# Library paths
#LIBPATHS = -L../arduino -L../eeprom 

# Libraries to link
#IBS  = -larduino -leeprom 


all: $(LIBNAME)
	$(SIZE) $(LIBNAME)

%.o : %.c
	$(CC) $(CFLAGS) -c -o $@ $^

%.o : %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $^ $(LIBPATHS) $(LIBS)
	
$(LIBNAME): $(OBJS)
	$(AR) -r $@ $(OBJS)

clean:
	rm -f $(OBJS) $(LIBNAME)
	