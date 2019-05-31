#include <Wire.h>
#include "RTC.h"

void RTC_init(){
  Wire.begin();
}

boolean getDate(struct Date* d){
  //Serial.println("in get date function");
  //struct Date ret;
  //Wire.begin();
  Wire.beginTransmission(0x68);
  Wire.write(0x00); //address of second register;
  Wire.endTransmission();
  //Serial.println(Wire.requestFrom(0x68, 7));
  if(Wire.requestFrom(0x68, 7) != 7) return false;
  d->second = bcdToDec(Wire.read());
  d->minute = bcdToDec(Wire.read());
  d->hour = bcdToDec(Wire.read());
  //now.hours = bcdToDec(Wire.read() & 0b10111111);
  bcdToDec(Wire.read());
  d->day = bcdToDec(Wire.read());
  d->month = bcdToDec(Wire.read());
  d->year = bcdToDec(Wire.read());
  //Serial.println("leaving get date function");
  return true;
}



void setDate(struct Date d){
  Wire.beginTransmission(0x68);
  Wire.write(0x00); //address of second register;
  Wire.write(decToBcd(d.second));
  Wire.write(decToBcd(d.minute));
  Wire.write(decToBcd(d.hour));
  Wire.write(decToBcd(0));
  Wire.write(decToBcd(d.day));
  Wire.write(decToBcd(d.month));
  Wire.write(decToBcd(d.year));
  Wire.endTransmission();
}

uint8_t decToBcd(uint8_t dec){
  uint8_t bcd;
  bcd = ((dec / 10) << 4) | (dec % 10);
  return bcd;
}

uint8_t bcdToDec(uint8_t bcd){
  uint8_t dec;
  dec = 10*(bcd >> 4) + (bcd & 0x0F);
  return dec;
}
