
#include "tm4c123gh6pm.h" 
#include "delay.h"

#define XTAL 80000000

static  __IO uint32_t PLL_Checker=0;
static __IO uint32_t sysTickCounter;



void SysTick_Handler(){
        SCB->ICSR |= 1<<25; // Clearing Pend Bit of Systick
     Decrement(); 

}




void PLL_Init_80MHz(){
  PLL_Checker=11;

	//1. Use RCC2
	SYSCTL->RCC2 |= (1 << 31);
	
	//2.Setting BYPASS2 to bypass
	SYSCTL->RCC2 |= (1 << 11);
		
	//3. RCC XTAL frequency setting and also enabling MAINOSC by 0th bit of RCC(The main oscillator is enabled)
	SYSCTL->RCC = (SYSCTL->RCC & (~0x000007C0)) + 0x00000540;
  // setting MAIN OSC in RCC2 OSCRC2
	SYSCTL->RCC2 &= ~(0x00000070);	
	
	//4. Activating PLL by PWRDN clearing
	SYSCTL->RCC2 &= ~(1<<13);
	 
	
	
	//5. select system divider DIV004
	SYSCTL->RCC2 |=(1 << 30);
	
	//(it was ignored in EDX) USESYSDIV Enable systemclock divider.
	//SYSCTL->RCC |= (1 << 22);
	

	

	
	//clearing SYSDIV2 value along with LSB
	
	SYSCTL->RCC2 = ( SYSCTL->RCC2 &= ~(0x1FC00000)) + (4 << 22);
	
	//6. // wait until RIS 6th bit is set
  while((SYSCTL->RIS & 0x00000040)==0){};
	//7. clearing the BYPASS
	 SYSCTL->RCC2 &= ~0x00000800; // clearing the bypass the PLL
	
	
	
}


void Decrement(void) {
	
		sysTickCounter--;
	
}
 

void delay_us(long n) {
	sysTickCounter = n;

	if(PLL_Checker==11){
	SysTick_Config(XTAL / 1000000);	
	}else{
	SysTick_Config(SystemCoreClock / 1000000);	
	}
	
	SysTick->CTRL |=(1 << 2);
  NVIC_SetPriority(SysTick_IRQn,Priority_6_systick);
	while (sysTickCounter != 0) {
	}
	SysTick->CTRL=0x00;
}

 
void delay_ms(long n) {
	sysTickCounter = n;

	if(PLL_Checker==11){
	SysTick_Config(XTAL / 1000);	
	}else{
	SysTick_Config(SystemCoreClock / 1000);	
	}
	
	SysTick->CTRL |=(1 << 2);
  NVIC_SetPriority(SysTick_IRQn,Priority_6_systick);
	while (sysTickCounter != 0) {
	}
	SysTick->CTRL=0x00;
}
 
