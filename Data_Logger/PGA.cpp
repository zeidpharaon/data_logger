#include <SPI.h>
#include "PGA.h"

void PGA_init(){
  SPI.begin();
  pinMode(cs, OUTPUT);
  digitalWrite(cs, HIGH);
}

void PGA_setGain(uint8_t ch, uint8_t gain){
  digitalWrite(cs, LOW);
  SPI.beginTransaction(SPISettings(1000, MSBFIRST, SPI_MODE0));
  SPI.transfer(0b00101010); //write command
  SPI.transfer(gain | ch);
  SPI.endTransaction();
  digitalWrite(cs, HIGH);
}
