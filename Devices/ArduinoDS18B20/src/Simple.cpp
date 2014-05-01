#include <OneWire.h>
#include <DallasTemperature.h>

// Data wire is plugged into port 2 on the Arduino
#define ONE_WIRE_BUS 2

// Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);

// Pass our oneWire reference to Dallas Temperature. 
DallasTemperature sensors(&oneWire);

void setup(void)
{
  // start serial port
  Serial.begin(38400);
  delay(2000);
  Serial.println("Dallas Temperature IC Control Library Demo");

  // Start up the library
  sensors.begin();
}

void loop(void)
{ 
  // call sensors.requestTemperatures() to issue a global temperature 
  // request to all devices on the bus
  Serial.print("Requesting temperatures...");
  sensors.requestTemperatures(); // Send the command to get temperatures
  Serial.println("DONE");
  
  Serial.print("Temperature for the device 1 (index 0) is: ");
  float temp=sensors.getTempCByIndex(0);
  uint8_t vz = 0;
  if (temp < 0.0) {
	  vz = 1;
  }
  uint8_t z1 = (int) (floor(temp));
  uint8_t z2 = (int) ((temp - floor(temp)) * 100);
  Serial.println(sensors.getTempCByIndex(0));
  Serial.print("VZ: ");
  Serial.println(vz);
  Serial.print("Z1: ");
  Serial.println(z1);
  Serial.print("Z2: ");
  Serial.println(z2);
  delay(1000);
}
