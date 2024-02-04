#include "TM4C123.h"                    // Device header

/* SW1 = PF4
   SW2 = PF0
	 LED = PF3
*/
uint8_t Button_state1,Button_state2;

void delay(long d){
	while(d--);
}

int main(){
	
	SYSCTL -> RCGCGPIO = SYSCTL -> RCGCGPIO | (1<<5);
	
	//Here we're using PF0 which is a special purpose pin
	GPIOF ->LOCK = 0x4C4F434B;
	GPIOF->CR = GPIOF->CR |(1<<0);
	
	GPIOF -> DIR = GPIOF -> DIR | (1<<3);    //LED as output
	GPIOF -> DIR = GPIOF -> DIR & (~(1<<4)) & (~(1<<0)); //SW1 & SW2 as input
	
	GPIOF -> PUR = GPIOF -> PUR | (1<<4) | (1<<0);    //Enabling pull up resistor
	
	GPIOF -> DEN = GPIOF -> DEN | (1<<3) | (1<<4) | (1<<0); //Digitalizing the led and SW1 and SW2
	
	while(1){
		//Pull up ==> released = PF4 = 1 , pressed = PF4 = 0
		Button_state1 = (GPIOF -> DATA & (1<<4))>>4;
    		
		if(Button_state1 == 0)
		{
			GPIOF -> DATA = GPIOF -> DATA | (1<<3);  //LED ON
		}
		Button_state2 = (GPIOF -> DATA & (1<<0))>>0;
		if(Button_state2==0){
			GPIOF -> DATA = GPIOF -> DATA & (~(1<<3)); //LED OFF
		}
		/*else
			GPIOF -> DATA = GPIOF -> DATA & (~(1<<3)); //LED OFF */
			
	}
	return 0;
}