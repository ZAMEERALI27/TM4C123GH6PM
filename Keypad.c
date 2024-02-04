#include "TM4C123.h"                    // Device header

void delay(long d);
uint32_t number;
/*
R1 - PB3
R2 - PC4
R3 - PC5
R4 - PC6
C1 - PC7
C2 - PD6
C3 - PD7 (special pin)

R1,R2,R3,R4 - OUTPUT
C1,C2,C3 - INPUT
*/


void delay(long d)
{
	while(d--);
}

int main()
{
	//Enabling clock
	SYSCTL->RCGCGPIO = SYSCTL->RCGCGPIO | (1<<1) | (1<<2) | (1<<3);
	
	//Unlocking PD7
	GPIOD->LOCK = 0x4C4F434B;
	GPIOD->CR = GPIOD->CR |(1<<7);
	
	//Digitalizing the pins
	GPIOB -> DEN = GPIOB ->DEN | (1<<3);
	GPIOC->DEN = GPIOC->DEN | (1<<4) | (1<<5) | (1<<6) | (1<<7);
	GPIOD -> DEN = GPIOD -> DEN | (1<<6) | (1<<7);
	
	//Direction of the pins
	//Output
	GPIOB -> DIR = GPIOB ->DIR | (1<<3);
	GPIOC->DIR = GPIOC->DIR | (1<<4) | (1<<5) | (1<<6);
	//Input
	GPIOC->DIR = GPIOC->DIR & (~(1<<7));
	GPIOD -> DIR = GPIOD -> DIR & (~(1<<6)) & (~(1<<7));
	
	//Enabling Pull-up
	GPIOC->PUR = GPIOC->PUR | (1<<7);
	GPIOD -> PUR = GPIOD -> PUR | (1<<6) | (1<<7);

	while(1)
	{
		//************ROW 1**************
		GPIOB->DATA = GPIOB->DATA &(~(1<<3));
		GPIOC->DATA = GPIOC->DATA | (1<<4) | (1<<5) | (1<<6);
		if(((GPIOC->DATA & (1<<7))>>7) == 0)
		{
			number = 1;
			delay(50000);
		}
		if(((GPIOD->DATA & (1<<6))>>6) == 0)
		{
			number = 2;
			delay(50000);
		}
		if(((GPIOD->DATA & (1<<7))>>7) == 0)
		{
			number = 3;
			delay(50000); 
		}
		//************ROW 2**************
		GPIOC->DATA = GPIOC->DATA &(~(1<<4));
		GPIOB->DATA = GPIOB->DATA | (1<<3);
		GPIOC->DATA = GPIOC->DATA | (1<<5) | (1<<6);
		if(((GPIOC->DATA & (1<<7))>>7) == 0)
		{
			number = 4;
			delay(50000);
		}
		if(((GPIOD->DATA & (1<<6))>>6) == 0)
		{
			number = 5;
			delay(50000);
		}
		if(((GPIOD->DATA & (1<<7))>>7) == 0)
		{
			number = 6;
			delay(50000); 
		}
		//************ROW 3**************
		GPIOC->DATA = GPIOC->DATA &(~(1<<5));
		GPIOB->DATA = GPIOB->DATA | (1<<3);
		GPIOC->DATA = GPIOC->DATA | (1<<4) | (1<<6);
		if(((GPIOC->DATA & (1<<7))>>7) == 0)
		{
			number = 7;
			delay(50000);
		}
		if(((GPIOD->DATA & (1<<6))>>6) == 0)
		{
			number = 8;
			delay(50000);
		}
		if(((GPIOD->DATA & (1<<7))>>7) == 0)
		{
			number = 9;
			delay(50000); 
		}
		//************ROW 4**************
		GPIOC->DATA = GPIOC->DATA &(~(1<<6));
		GPIOB->DATA = GPIOB->DATA | (1<<3);
		GPIOC->DATA = GPIOC->DATA | (1<<4) | (1<<5);
		if(((GPIOC->DATA & (1<<7))>>7) == 0)
		{
			number = '*';
			delay(50000);
		}
		if(((GPIOD->DATA & (1<<6))>>6) == 0)
		{
			number = 0;
			delay(50000);
		}
		if(((GPIOD->DATA & (1<<7))>>7) == 0)
		{
			number = '#';
			delay(50000); 
		}
		
	}
	return 0;
}
