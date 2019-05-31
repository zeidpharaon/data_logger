#ifndef DAC_H_   /* Include guard */
#define DAC_H_


#define DAC_ADDRESS 0b01100000 //a2 a1 a0 = 0
#define DAC_CHANNEL_A 0b00000000
#define DAC_CHANNEL_B 0b00000010
#define DAC_CHANNEL_C 0b00000100
#define DAC_CHANNEL_D 0b00000110

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

void DAC_update(uint8_t chan, boolean vRefInt, uint8_t gain, uint16_t data);
void DAC_init();

#endif 
