#include <Wire.h>
#include "DAC.h"

void DAC_init(){
  Wire.begin();
}

void DAC_update(uint8_t chan, boolean vRefInt, uint8_t gain, uint16_t data){
  Wire.begin();
  Wire.beginTransmission(DAC_ADDRESS);
  if(data >= 4096) data = 4095; //maximum 4096
  Wire.write((0b1011 << 3) | chan); //01011 single write command to do UDAC??
  Wire.write((vRefInt ? (1 << 7) : 0) | (gain != 1 ? (1 << 4) : 0) | (data >> 8)); //to do impliment power down
  Wire.write(data & 0xff);
  Wire.endTransmission();

  /*Serial.println(DAC_ADDRESS, BIN);
  Serial.println((0b1011 << 3) | chan, BIN); //01011 single write command to do UDAC??
  Serial.println((vRefInt ? (1 << 7) : 0) | (gain != 1 ? (1 << 4) : 0) | (data >> 8), BIN); //to do impliment power down
  Serial.println(data & 0xff, BIN);*/
}
