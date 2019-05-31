#include <Wire.h>

#define DAC_ADDRESS 0b01100000 //a2 a1 a0 = 0
#define DAC_CHANNEL_A 0b00000000
#define DAC_CHANNEL_B 0b00000010
#define DAC_CHANNEL_C 0b00000100
#define DAC_CHANNEL_D 0b00000110

//calibration of dac on adapter
/*
//calibrated m and b of channel a
#define ma 0.9888
#define ba 1.6383
//calibrated m and b of channel b
#define mb 1.0004
#define bb 2.9172
//calibrated m and b of channel c
#define mc 1.0002
#define bc -7.9030
//calibrated m and b of channel d
#define md 0.9986
#define bd -1.6680
*/

//calibration of dac on final pcb

//calibrated m and b of channel a
#define ma 0.9894
#define ba 11.5918
//calibrated m and b of channel b
#define mb 1.0005
#define bb 15.2792
//calibrated m and b of channel c
#define mc 1.0040
#define bc 1.1152
//calibrated m and b of channel d
#define md 0.9986
#define bd 6.3522


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Wire.begin();

  /*Wire.beginTransmission(0b11000000);
  Wire.write(0b01011000);
  Wire.write(0b00001111);
  Wire.write(0b00000001);
  Wire.end();*/
  DAC_update(DAC_CHANNEL_D, true, 2, 0);
}

void loop() {
  // put your main code here, to run repeatedly:
  //internal vol ref gain 2 
  /*Wire.beginTransmission(DAC_address);
  Wire.write(0b01011000); //01011 single write command !!
  Wire.write(0b10011000);
  Wire.write(0b00000100);
  Wire.endTransmission();*/

  delay(10);
}

void DAC_update(uint8_t chan, boolean vRefInt, uint8_t gain, uint16_t data){
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

void serialEvent(){
  uint16_t rec = Serial.parseInt();
  int d = (rec - bd)/md; //calibration
  if(d < 0) d = 0;
  //int d = rec;
  if(rec != 0){
    Serial.println(rec);
    DAC_update(DAC_CHANNEL_D, true, 2, d);
  }
  
}
