#include "TM4C123.h"                    // Device header

uint32_t ms;

void delay(uint16_t d){
	ms=0;
	while(d>ms);
}
int main()
{
	 SYSCTL ->RCGCGPIO  = 0x20; 
	 //GPIO_PORTF_DEN_R = 0x0E;
	 GPIOF -> DEN = 0x0E;
	 
	 //GPIO_PORTF_DIR_R = 0x0E;
	 GPIOF -> DIR = 0x0E;
	 //GPIOFDATA = 0x02U;   //Red - 0x02U ; Blue - 0x04U ; Green - 0x08U
	
	//cofiguring 4Mhz systick timer an enabling interrupt
	SysTick->CTRL = 0x03;
	//Load value for 1 sec
	//Load value for 1ms ==> 1ms/0.25 ==> 1000/0.25 = 4000
	SysTick->LOAD = 4000-1;
	
	
	while(1){
		 GPIOF->DATA = GPIOF->DATA ^ (1<<2);   //Toggles the LED
		 delay(1000);
	}
	return 0;
}

void SysTick_Handler(){
	 ms++;
}