#include <Arduino.h>
#include "HX711.h"
#include "soc/rtc.h"


#define readInterval 5000 


// HX711 circuit wiring
const int LOADCELL_DOUT_PIN = 16;
const int LOADCELL_SCK_PIN = 4;

HX711 scale;

unsigned long 	prevMill = 0;

void setup() {
  Serial.begin(115200);
  setCpuFrequencyMhz(RTC_CPU_FREQ_80M);
  
  Serial.println("HX711 Demo");
  Serial.println("Initializing the scale");

  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);

  Serial.println("Before setting up the scale:");
  Serial.print("read: \t\t");
  Serial.println(scale.read());

  Serial.print("read average: \t\t");
  Serial.println(scale.read_average(20));

  Serial.print("get value: \t\t");
  Serial.println(scale.get_value(5));
  Serial.print("get units: \t\t");
  Serial.println(scale.get_units(5), 1); 
  scale.set_scale(-10758.0226667);  
  scale.tare();  
  
  Serial.println("After setting up the scale:");
  Serial.print("read: \t\t");
  Serial.println(scale.read());

  Serial.print("read average: \t\t");
  Serial.println(scale.read_average(20));

  Serial.print("get value: \t\t");
  Serial.println(scale.get_value(5));

  Serial.print("get units: \t\t");
  Serial.println(scale.get_units(5), 1);       
  Serial.println("Readings:");
}

void loop() 
{
	if(millis() - prevMill >= readInterval)
	{
		prevMill = millis();
		scale.power_up();
		Serial.print("one reading:\t");
		Serial.print(scale.get_units(), 1);
		Serial.print("\t| average:\t");
		Serial.println(scale.get_units(10), 5);
		scale.power_down();
	} 
}
