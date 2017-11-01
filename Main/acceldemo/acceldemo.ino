// Basic demo for accelerometer readings from Adafruit LIS3DH

#include <Wire.h>
#include <SPI.h>
#include "Adafruit_LIS3DH.h"
#include "Adafruit_Sensor.h"

Adafruit_LIS3DH lis = Adafruit_LIS3DH();

void setup(void) {
  
#ifndef ESP8266
  while (!Serial);     
#endif

  Serial.begin(9600);
  
  if (! lis.begin(0x18)) {   
    Serial.println("Couldnt start");
    while (1);
  }
  
  lis.setRange(LIS3DH_RANGE_2_G);   // 2, 4, 8 or 16 G!
}

void loop() {
      
  sensors_event_t event; 
  lis.getEvent(&event);
  
  /* Display the results (acceleration is measured in m/s^2) */
  Serial.print("|"); 
  Serial.print(event.acceleration.x);
  Serial.print("|"); 
  Serial.print(event.acceleration.y); 
  Serial.print("|"); 
  Serial.print(event.acceleration.z); 
  Serial.println("|");
  //Serial.println();
 
  delay(200); 
}
