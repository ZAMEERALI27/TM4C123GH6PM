#include "TM4C123.h"                    // Device header

/*
SW1 - PF4
SW2 - PF0
GREEN LED - PF3
BLUE LED - PF2
*/

int main()
{
	//enable clock
	SYSCTL->RCGCGPIO = SYSCTL->RCGCGPIO |(1<<5);
	
	//We use special register 
	GPIOF->LOCK = 0x4C4F434B;
	GPIOF->CR = 0x01;
	GPIOF->LOCK = 0;
	
	//Digitalize the pins
	GPIOF->DEN = GPIOF->DEN |(1<<2) | (1<<3);
	GPIOF->DEN = GPIOF->DEN | (1<<0) | (1<<4);
	
	//Direction for the pins
	GPIOF->DIR = GPIOF->DIR |(1<<2) | (1<<3);
	GPIOF->DIR = GPIOF->DIR & (~(1<<0)) & (~(1<<4));
	
	
	//Enabling pull to SW1,SW2
	GPIOF->PUR = GPIOF->PUR | (1<<0) | (1<<4);
	
	//Enabling edge trigger interrupt to SW1,SW2
	GPIOF->IS = GPIOF->IS & (~(1<<0)) & (~(1<<4)); 
	
	//Disabling interrupt on both edges
	GPIOF->IBE = GPIOF->IBE & (~(1<<0)) & (~(1<<4));
	
	//Enabling falling edge detection
	GPIOF->IEV = GPIOF->IEV & (~(1<<0)) & (~(1<<4));
	
	//unmask the interrupts
	GPIOF->IM = GPIOF->IM | (1<<0) | (1<<4);
	
	//clearing interrupt flag
	GPIOF->ICR = GPIOF->ICR | (1<<0) | (1<<4); 
	
	//activate NVIC to use interrupte (refer note)
	NVIC ->ISER[0] = NVIC->ISER[0] | (1<<30);
	
	//setting priority to interrupt
	NVIC->IP[30] = 0x60;
	
	while(1)
	{
	}
	return 0;
}

void GPIOF_Handler()
{
	if((GPIOF->MIS & 0x10) == 0x10)     //if interrupt occur 4th bit MIS is set
	{
		GPIOF -> DATA = GPIOF -> DATA | (1<<3);  //Turn On Green LED
		GPIOF -> DATA = GPIOF -> DATA & (~(1<<2));  //Turn off Blue LED
		GPIOF->ICR = GPIOF->ICR |(1<<4);
	}
	else if((GPIOF->MIS & 0x01) == 0x01)
	{
		GPIOF -> DATA = GPIOF -> DATA | (1<<2);  //Turn On Blue LED
		GPIOF -> DATA = GPIOF -> DATA & (~(1<<3));  //Turn Off Green LED
		GPIOF->ICR = GPIOF->ICR | (1<<0);
	}
}
