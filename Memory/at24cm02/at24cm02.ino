#include <Wire.h>

#define MEMORY 0xA0 // Memory Component Address


void writeEEPROM( byte data )
{
  
  Wire.beginTransmission( MEMORY );
  Wire.write( (int)(0x00 >> 8) );   // MSB
  Wire.write( (int)(0x00 & 0xFF) ); // LSB
  Wire.write( data );
  Wire.endTransmission();

  delay(5);
}

byte readEEPROM()
{
  byte rdata = 0xFF;

  Wire.beginTransmission( 0xA0 );
  Wire.write( (int)(0x00 >> 8) );   // MSB
  Wire.write( (int)(0x00 & 0xFF) ); // LSB
  Wire.endTransmission();

  Wire.requestFrom( MEMORY, 1 );

  if( Wire.available() ) rdata = Wire.read();

  return rdata;
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin( 9600 );
  Wire.begin();

  unsigned int a2 = 0;

  writeEEPROM( 0x50 );
  Serial.print( readEEPROM() );
}

void loop() {
  // put your main code here, to run repeatedly:

}
