include ../../Makefile.common

# Includes
CFLAGS += -Isrc 
CFLAGS += -I../arduinocore/src

CXXFLAGS += -Isrc
CXXFLAGS += -I../arduinocore/src
CXXFLAGS += -I../onewire/src


# Sources
C_SRC = 

CPP_SRC = src/DallasTemperature.cpp

OBJS := $(C_SRC:.c=.o) $(CPP_SRC:.cpp=.o)
LIBNAME = libdallastemperature.a

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
	