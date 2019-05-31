#ifndef RTC_H_   /* Include guard */
#define RTC_H_


struct Date{
  byte second;
  byte minute;
  byte hour;
  byte day;
  byte month;
  byte year;
};

void RTC_init();
boolean getDate(struct Date* d);
void setDate(struct Date d);
uint8_t decToBcd(uint8_t dec);
uint8_t bcdToDec(uint8_t bcd);

#endif 
