include ../../Makefile.common

# Includes
CFLAGS += -Isrc 
CFLAGS += -I../arduinocore/src

CXXFLAGS += -Isrc
CXXFLAGS += -I../arduinocore/src

# Sources
C_SRC = 

CPP_SRC = src/EEPROM.cpp

OBJS := $(C_SRC:.c=.o) $(CPP_SRC:.cpp=.o)
LIBNAME = libarduinoeeprom.a

all: $(LIBNAME)
	$(SIZE) $(LIBNAME)

%.o : %.c
	$(CC) $(CFLAGS) -c -o $@ $^

%.o : %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $^

$(LIBNAME): $(OBJS)
	$(AR) -r $@ $(OBJS)

clean:
	rm -f $(OBJS) $(LIBNAME)
	