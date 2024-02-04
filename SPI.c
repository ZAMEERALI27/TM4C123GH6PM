#include "TM4C123.h"                    // Device header

/*
Module-2

PB4- Clock
PB5- Chip select
PB6- Rx
PB7- Tx
*/

uint8_t led = 0x00;

void delay(long d){
	while(d--);
}

void SPIwrite(uint8_t data)
{
	SSI2->DR = data;
	//Checking status register is empty or not; SR=1 (empty)
	while((SSI2->SR & (1<<0) == 0));
}

int main(){
	/*Clock configuration*/
	
	//Enable the SSI module using the RCGCSSI register
	SYSCTL->RCGCSSI |= (1<<2);
	//Enable the clock to the appropriate GPIO module via the RCGCGPIO register
	SYSCTL->RCGCGPIO |= (1<<1);
	
	/*GPIO Configuration*/
	
	//Set the GPIO AFSEL bits for the appropriate pins
	GPIOB->AFSEL |= (1<<4) | (1<<6) | (1<<7);
	GPIOB->AFSEL &= (~(1<<5));
	//Configure the PMCn fields in the GPIOPCTL register to assign the SSI signals to the appropriate pins
	GPIOB->PCTL |= (2<<16) | (2<<20) | (2<<24) | (2<<28);
	//Program the GPIODEN register to enable the pin's digital function
	GPIOB->DEN |= (1<<4) | (1<<5) | (1<<6) | (1<<7);
	
	/*SSI Configuration*/
	
	//Disabling SSICR1 before configuring
	SSI2->CR1 &= (~(1<<1));
	//master operation of our MC
	SSI2->CR1 =  0x00000000;
	//Configure the SSI clock source by writing to the SSICC register.
	SSI2->CC = 0x0;
	
	/*
	Configure the clock prescale divisor by writing the SSICPSR register
	here,we're using system clock of 16Mhz so, 16Mhz/10 = 1.6	Mhz each clock
	*/
	SSI2->CPSR = 10;
	//Write the SSICR0 register
	SSI2->CR0 |= (0x07<<0);
	//Enable the SSI
	SSI2->CR1 |= (1<<1);
	
	GPIOB -> DATA |= (1<<5);
	GPIOB -> DATA &= (~(1<<5));
	
	SPIwrite(0x40); //slave address
	SPIwrite(0x00); //IODIR address
	SPIwrite(0x00); //set pins as outputs
	
	GPIOB -> DATA |= (1<<5);
	
	while(1)
	{
		GPIOB -> DATA &= (~(1<<5));  //start of transmission (SPI connected)
		
		SPIwrite(0x40);
		SPIwrite(0x09);
		SPIwrite(led++); 
		
		delay(15);
		GPIOB -> DATA |= (1<<5);    //end of transmission
		delay(10000000);
	}
	
	
	return 0;
}
