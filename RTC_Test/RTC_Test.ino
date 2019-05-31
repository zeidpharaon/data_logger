struct Date{
  byte second;
  byte minute;
  byte hour;
  byte day;
  byte month;
  byte year;
};

#include <Wire.h>

int c = 0;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Wire.begin();
  Date now;
  now.year = 19;
  now.month = 5;
  now.day = 20;
  now.hour = 22;
  now.minute = 27;
  now.second = 0;
  //setDate(now);
}

void loop() {
  // put your main code here, to run repeatedly:
  Date d;
  
  //Serial.println("hmi");
  if(c%60 == 0){
    getDate(&d);
    Serial.println(String(d.day) + '/' + String(d.month) + '/'  + String(d.year) + ' ' + String(d.hour) + ':' + String(d.minute) + ':' + String(d.second));
  }
  delay(990);
  c++;
}

boolean getDate(struct Date* d){
  //Serial.println("in get date function");
  //struct Date ret;
  Wire.begin();
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
