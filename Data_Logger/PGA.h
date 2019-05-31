#ifndef PGA_H_   /* Include guard */
#define PGA_H_

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
#define PGA_CHANNEL_CAL1 0b00001100
#define PGA_CHANNEL_CAL2 0b00001101
#define PGA_CHANNEL_CAL3 0b00001110
#define PGA_CHANNEL_CAL4 0b00001111

void PGA_init();
void PGA_setGain(uint8_t ch, uint8_t gain);

#endif 
