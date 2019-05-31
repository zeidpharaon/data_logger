#include <SPI.h>
#include <SD.h>
#include "RTC.h"
#include "PGA.h"
#include "DAC.h"

const int chipSelect = 10;
const int analogInPin = A0;  // Analog input pin that the potentiometer is attached to
float analogValue;

unsigned long int timeLastMeas[] = {0, 0, 0, 0};
unsigned long int timeBetweenMeas[] = {30000, 60000, -1, -1};
int gains[] = {1, 8, 1, 1};
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  RTC_init();
  PGA_init();
  PGA_setGain(PGA_CHANNEL_1, PGA_GAIN_1);
  DAC_init();
  DAC_update(DAC_CHANNEL_A, true, 2, 1000);
  delay(100);
  DAC_update(DAC_CHANNEL_B, true, 2, 2000);
  
  Serial.print("Initializing SD card...");

  // see if the card is present and can be initialized:
  if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
    // don't do anything more:
    //while (1);
  }
  Serial.println("card initialized.");
  //analogReference(EXTERNAL);
}

void loop() {
  // put your main code here, to run repeatedly:
   Date d;
 for(int i = 0; i < 4; i++){
   if( (millis() - timeLastMeas[i]) > timeBetweenMeas[i]){
    
    getDate(&d);
    Serial.println(String(i+1));
    Serial.println(String(d.day) + '/' + String(d.month) + '/'  + String(d.year) + ' ' + String(d.hour) + ':' + String(d.minute) + ':' + String(d.second));
    PGA_setGain(PGA_channel(i+1), PGA_gain(gains[i]));
    analogValue = analogRead(analogInPin)*5.0 / 1024.0;
    float valCal = (analogValue+0.01342875)/1.0034175;
    Serial.println(analogValue);
    File dataFile = SD.open("datalog" + String(i+1) + ".txt", FILE_WRITE);
    // if the file is available, write to it:
    if (dataFile) {
      dataFile.println(String(d.day) + '/' + String(d.month) + '/'  + String(d.year) + ' ' + String(d.hour) + ':' + String(d.minute) + ':' + String(d.second));
      dataFile.println(analogValue);
      dataFile.close();
    }
    // if the file isn't open, pop up an error:
    else {
      Serial.println("error opening datalog.txt");
    }
    timeLastMeas[i] = millis();
  } 
 }
  getDate(&d);
  DAC_update(DAC_CHANNEL_A, true, 2, (1 + 50*d.minute));
  delay(1000);
  DAC_update(DAC_CHANNEL_B, true, 2, int(10*d.minute));
  //DAC_update(DAC_CHANNEL_B, true, 2, 600);
 
  //delay(1000);
}

int PGA_channel(int c){
  switch(c){
    case 1:
      return PGA_CHANNEL_1;
      break;
    case 2:
      return PGA_CHANNEL_2;
      break;
    case 3:
      return PGA_CHANNEL_3;
      break;
    case 4:
      return PGA_CHANNEL_4;
      break;
  }   
}

int PGA_gain(int c){
  switch(c){
    case 1:
      return PGA_GAIN_1;
      break;
    case 2:
      return PGA_GAIN_2;
      break;
    case 4:
      return PGA_GAIN_4;
      break;
    case 8:
      return PGA_GAIN_8;
      break;
    case 16:
      return PGA_GAIN_16;
      break;
    case 32:
      return PGA_GAIN_32;
      break;
    case 64:
      return PGA_GAIN_64;
      break;
    case 128:
      return PGA_GAIN_128;
      break;
  }   
}
