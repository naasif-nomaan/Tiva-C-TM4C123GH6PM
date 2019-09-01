

#include<stdio.h>
#include "tm4c123gh6pm.h"
#include "delay.h"


static uint16_t count=0;


uint32_t User_Button1_Read(GPIOA_Type *gpio){

	if((gpio->DATA & 0x10)==0){
	return 0;
	}else{
	return 1;
	}
}



int main(){



	
GPIOA_Type *gpiof;


gpiof=GPIOF;
SYSCTL->RCGCGPIO |= (1 << 5);	

gpiof->LOCK  &=~(0xFF); // clearing bits	
gpiof->LOCK  |=0x00; // getting permission for writing on CR 	

gpiof->CR  &=~(0xFF); // clearing bits		
gpiof->CR    |=0x1F; // getting permission for DEN and PUR registers

gpiof->AMSEL  &=~(0xFF); // clearing bits		
gpiof->AMSEL |=0x00; // disabling Analog functions.

gpiof->AFSEL  &=~(0xFF); // clearing bits		
gpiof->AFSEL |=0x00; // disabling ALTERNATE FUNCTIONS.	

gpiof->ODR  &=~(0xFF); // clearing bits	
gpiof->ODR   |=0x00;  // disabling Open Drain Mode for all pins.	

gpiof->PUR  &=~(0xFF); // clearing bits	
gpiof->PUR   |=0x11;	// enabling Pull-Up Resistor for Usr Button1 and Usr Button2

gpiof->DIR  &=~(0xFF); // clearing bits	
gpiof->DIR   |=0x0E; // Enabling User buttons as input and RGB pins as outputs.	

gpiof->DEN  &=~(0xFF); // clearing bits	
gpiof->DEN   |=0x7F; // Enabling digital function for all pins of PORTF
	
	




while(1){
	//gpiof->DATA &=~(0x0E); // clearing RGB or Default State
	
	if(User_Button1_Read(gpiof)==0){
   delay_ms(100);
		count++;
		
		if(count>3){
		count=0;
		gpiof->DATA &=~(0x0E); // clearing RGB or Default State
		}
		
		while(User_Button1_Read(gpiof)==0);
	}
	
	if(count==1){
	gpiof->DATA &=~(0x0E); // clearing RGB or Default State
	gpiof->DATA |= (1 << 1);
	}
	if(count==2){
	gpiof->DATA &=~(0x0E); // clearing RGB or Default State
	gpiof->DATA |= (1 << 3);
	}
	
	if(count==3){
	
  gpiof->DATA &=~(0x0E); // clearing RGB or Default State
	gpiof->DATA |= (1 << 1);
  delay_ms(100);   
		
	gpiof->DATA &=~(0x0E); // clearing RGB or Default State
	gpiof->DATA |= (1 << 3);
	delay_ms(100); 	
	}
	
	
}








return 0;
}











