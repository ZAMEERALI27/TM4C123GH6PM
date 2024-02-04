#include "TM4C123.h"   // Device header
#

void delay(long d){
	while(d--);
}

int main()
{
	SYSCTL ->RCGCGPIO = 0x00000001;
	GPIOA ->DEN =       0x00000004;  //digitalizing PA2
	GPIOA -> DIR =      0x00000004;  //PA2 as output
	
	
	while(1)
	{
		GPIOA ->DATA = GPIOA ->DATA | (1<<2);
		delay(1000000);
		GPIOA ->DATA = GPIOA ->DATA | (~(1<<2));
		delay(1000000);
		
		
	}
	return 0;
}
