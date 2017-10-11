/*
 * LIS3DH.ino
 * COMMUNICATES WITH A LIS3DH ACCELEROMETER USING I2C
 * ENGINEER: ANGELINO LEFEVERS
 */
#include <Wire.h>
#include <SPI.h>

// LIS3DH I2C Address
#define LIS3DH_ADDRESS 0x18

// LIS3DH Pins
#define SCL 13
#define SDA 12
#define SDO 11
#define CS 10

// LIS3DH Registers
#define STATUS_REG_AUX  0x07
#define OUT_ADC1_L      0x08
#define OUT_ADC1_H      0x09
#define OUT_ADC2_L      0x0A
#define OUT_ADC2_H      0x0B
#define OUT_ADC3_L      0x0C
#define OUT_ADC3_H      0x0D
#define INT_COUNTER_REG 0x0E
#define WHO_AM_I        0x0F  // Device Identification
#define TEMP_CFG_REG    0x1F  // Temperature and ADC enable
#define CTRL_REG1       0x20  // Axis enable, Data Rate
#define CTRL_REG2       0x21  // High Pass Filter enable
#define CTRL_REG3       0x22  // Interrupts
#define CTRL_REG4       0x23  // Resolution, and Data Presentation
#define CTRL_REG5       0x24  // Memory reboot, FIFO
#define CTRL_REG6       0x25
#define REFERENCE       0x26  // Reference value
#define STATUS_REG2     0x27
#define OUT_X_L         0x28
#define OUT_X_H         0x29
#define OUT_Y_L         0x2A
#define OUT_Y_H         0x2B
#define OUT_Z_L         0x2C
#define OUT_Z_H         0x2D
#define FIFO_CTRL_REG   0x2E
#define FIFO_SRC_REG    0x30
#define INT1_SOURCE     0x31
#define INT1_THS        0x32
#define INT1_DURATION   0x33
#define CLICK_CFG       0x38
#define CLICK_SRC       0x39
#define CLICK_THS       0x3A
#define TIME_LIMIT      0x3B
#define TIME_LATENCY    0x3C
#define TIME_WINDOW     0x3D

// Range Divider Constants. Divide by these values to get force in g's at different ranges
#define DIV_16G   1365
#define DIV_8G    4096      
#define DIV_4G    8190
#define DIV_2G    16380

/* FUNCTION: writeRegister 
 * DESCRIPTION: writes <value> into register <reg>
 */
void writeRegister( uint8_t reg, uint8_t value ) {
  Wire.beginTransmission( (uint8_t) LIS3DH_ADDRESS );
  Wire.write( (uint8_t) reg );
  Wire.write( (uint8_t) value );
  Wire.endTransmission();
} // END FUNCTION writeRegister

/* FUNCTION: readRegister
 * DESCRIPTION: Returns value in register <reg>
 */
uint8_t readRegister( uint8_t reg ) {
  Wire.beginTransmission( (uint8_t) LIS3DH_ADDRESS );
  Wire.write( (uint8_t) reg );
  Wire.endTransmission();
  Wire.requestFrom( LIS3DH_ADDRESS, 1 );
  return Wire.read();
}

void setup() {
  // Setup Serial and I2C Communication Libraries
  Serial.begin(9600);
  Wire.begin();
  
  // Turns on ADC
  writeRegister( TEMP_CFG_REG, 0x80 );
  // Enables Accelerometer in only x direction (1h)
  // Data Rate: 0101(5h) -> 100Hz
  writeRegister( CTRL_REG1, 0x51 );
  // DRDY1 := Data Ready interrupt on INT1 
  writeRegister( CTRL_REG3, 0x10 );
  // High Resolution enabled
  // BDU enables : Block Data Update
  // BLE disable : Little Endian Data Format
  // FS (00h) : Full Scale Selection := +/- 2G
  writeRegister( CTRL_REG4, 0x88 );

  Serial.println( "BEGIN: " );
}

void loop() {
  
  Wire.beginTransmission( LIS3DH_ADDRESS );
  Wire.write( OUT_X_L | 0x80 );
  Wire.endTransmission();
  Wire.requestFrom( LIS3DH_ADDRESS, 6 );
  
  Serial.println( Wire.read() );
}

