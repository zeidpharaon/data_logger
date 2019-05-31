//vref to gnd
// enable to 5v

#define cs 9

#define PGA_GAIN_1    0b00000000
#define PGA_GAIN_2    0b00010000
#define PGA_GAIN_4    0b00100000
#define PGA_GAIN_8    0b00110000
#define PGA_GAIN_16   0b01000000
#define PGA_GAIN_32   0b01010000
#define PGA_GAIN_64   0b01100000
#define PGA_GAIN_128  0b01110000

#define PGA_CHANNEL_0 0b00000000
#define PGA_CHANNEL_1 0b00000001
#define PGA_CHANNEL_2 0b00000010
#define PGA_CHANNEL_3 0b00000011
#define PGA_CHANNEL_4 0b00000100
#define PGA_CHANNEL_5 0b00000101
#define PGA_CHANNEL_6 0b00000110
#define PGA_CHANNEL_7 0b00000111
#define PGA_CHANNEL_8 0b00001000
#define PGA_CHANNEL_9 0b00001001
#define PGA_CAL2 0b00001101 //0.9Vcal
#define PGA_CAL3 0b00001110 //0.1Vcal

#define G 1.0034175
#define O -0.01342875

#include <SPI.h>

void setup() {
  // put your setup code here, to run once:
  SPI.begin();
  Serial.begin(9600);
  pinMode(cs, OUTPUT);
  digitalWrite(cs, HIGH);

  PGA_setGain(PGA_CHANNEL_4, PGA_GAIN_1);
}

void loop() {
  // put your main code here, to run repeatedly:
  float a = analogRead(A0)*5.00 / 1024.0;
  float v = (a - O)/G;
  Serial.println(v,5);
  delay(1000);
}

void PGA_setGain(uint8_t ch, uint8_t gain){
  digitalWrite(cs, LOW);
  SPI.beginTransaction(SPISettings(1000, MSBFIRST, SPI_MODE0));
  SPI.transfer(0b00101010); //write command
  SPI.transfer(gain | ch);
  SPI.endTransaction();
  digitalWrite(cs, HIGH);
}

void serialEvent(){
  uint8_t rec = Serial.parseInt();
  if(rec != 0){
    Serial.println(rec);
    digitalWrite(cs, LOW);
    SPI.beginTransaction(SPISettings(1000, MSBFIRST, SPI_MODE0));
    SPI.transfer(0b00101010); //write command
    SPI.transfer(rec);
    SPI.endTransaction();
    digitalWrite(cs, HIGH);
  }
  /*Serial.println(rec);
  digitalWrite(cs, LOW);
  SPI.beginTransaction(SPISettings(1000, MSBFIRST, SPI_MODE0));
  SPI.transfer(0b00101010); //write command
  SPI.transfer(rec);
  SPI.endTransaction();
  digitalWrite(cs, HIGH);*/
}
