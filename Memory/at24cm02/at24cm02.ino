#include <Wire.h>

#define MEMORY 0xA0 // Memory Component Address


void writeEEPROM()
{
  
  Wire.beginTransmission( MEMORY | 0x00 );  // Device Address
  Wire.write( 0x00 ); // First Word Address
  Wire.write( 0x01 ); // Second Word Address
  Wire.write( 0x01 ); // Data Word
  Wire.endTransmission();
}

byte readEEPROM()
{
  byte data = 0xFF;
  
  // Random Read
  // Starts by using a 'Dummy Write'
  Wire.beginTransmission( MEMORY | 0x00 );  // Device Address
  Wire.write( 0x00 ); // First Word Address
  Wire.write( 0x01 ); // Second Word Address
  // Wire.endTransmission();
  // Then reads data
  Wire.beginTransmission( MEMORY | 0x01 );
  Wire.requestFrom( MEMORY, 2 );

  data = Wire.read();

  Wire.endTransmission();

  return data;
}

void get100Addresses( void ) {
  int i = 0;
  
  // 'Dummy Write'
  Wire.beginTransmission( MEMORY | 0x00 );  // Device Address
  Wire.write( 0x00 ); // First Word Address
  Wire.write( 0x01 ); // Second Word Address

  Wire.beginTransmission( MEMORY | 0x01 );

  for( i = 0; i < 100; i++ ) {
    Wire.requestFrom( MEMORY, 2 );

    Serial.print( i );
    Serial.print( ": " );
    Serial.println( Wire.read() );
  }
  Wire.endTransmission();
}

void setup() {
  // put your setup code here, to run once:
  
  Serial.begin( 9600 );
  Wire.begin();

  // Wire.setClock( 10000 );
  writeEEPROM();
  Serial.println( readEEPROM() );
  get100Addresses();
}

void loop() {
  // put your main code here, to run repeatedly:

}
