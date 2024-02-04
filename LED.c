#include "TM4C123.h"                    // Device header

#include "Time_delay.h"
/*void delay(int d){
	while(d--);
}*/

int main(void){
	 
	 SYSCTL ->RCGCGPIO  = 0x20; 
	 //GPIO_PORTF_DEN_R = 0x0E;
	 GPIOF -> DEN = 0x0E;
	 
	 //GPIO_PORTF_DIR_R = 0x0E;
	 GPIOF -> DIR = 0x0E;
	 //GPIOFDATA = 0x02U;   //Red - 0x02U ; Blue - 0x04U ; Green - 0x08U
	
	
	while(1){
		 //GPIOF -> DATA  = GPIOF -> DATA | (1<<1);
	   GPIOF -> DATA  = GPIOF -> DATA | (1<<1);
		 delay(10000000);
		 GPIOF -> DATA  = GPIOF -> DATA = 0x00;
		 delay(10000000);
     GPIOF -> DATA  = GPIOF -> DATA | (1<<3);
		 delay(10000000);  
		 GPIOF -> DATA  = GPIOF -> DATA = 0x00;
		 delay(10000000); 
	}

	
	return 0;
}