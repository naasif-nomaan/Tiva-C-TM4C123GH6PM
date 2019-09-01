
#ifndef DELAY_H
#define DELAY_H

#define Priority_6_systick  0x06

void Decrement();
void delay_us(long n);
void delay_ms(long n);
void PLL_Init_80MHz();
#endif
