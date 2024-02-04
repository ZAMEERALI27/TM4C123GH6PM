#include "TM4C123.h"                    // Device header

void Timer_initialize(void);
void  TIMER1A_Handler();

/*
PF1 - RED LED
TIMER1A - 16bit
*/

int main()
{
	//Enabling clock
	SYSCTL->RCGCGPIO |= (1<<5);
	
	//Digitalizing the pins
	GPIOF->DEN |= (1<<1);
	
	//Direction of the pin as output
	GPIOF->DIR |= (1<<1);
	
	Timer_initialize();
	
	
	while(1)
	{
		
	}
}

void  TIMER1A_Handler()
{
	//if(TIMER1->MIS & 0x01)
	GPIOF -> DATA ^= (1<<1); //Toggling PF1
	TIMER1->ICR |= (1<<0); //clearing interrut flag
	
}

void Timer_initialize()
{
	//Enable Timer clock
	SYSCTL->RCGCTIMER |= (1<<1); //Enabling clock Timer1
	//Disabling Timer1A before configuring
	TIMER1 -> CTL &= (~(1<<0)); 
	//Selecting 16bit resolution
	TIMER1 -> CFG = 0x4;
	//Setting perodic and down counter mode
	TIMER1->TAMR = 0x02;	
	//set the interval load register value
	TIMER1->TAILR = 64000;
	//clear timeout flag
	TIMER1->ICR |= (1<<0);
	//Enabling Timer
	TIMER1 -> CTL |= (1<<0); 
	//Enabling interrupt
	TIMER1->IMR |= (1<<0);
	//enabling NVIC
  NVIC->ISER[0] |= (1<<21);	
}