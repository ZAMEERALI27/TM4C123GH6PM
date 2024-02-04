#include "TM4C123.h"                    // Device header

/*
Module-1

PA6- SCL
PA7- SDA
*/

uint8_t led;

void delay(long d){
	while(d--);
}

void SetSlave_Address(uint8_t slaveAddress)
{
	I2C1->MSA |= (slaveAddress << 1);
}

void setRW(uint8_t mode)
{
	if(mode == 0){
		//Write = 0
		I2C1->MSA &= (~(1<<0));
	}
	else{
		//Read = 1
		I2C1->MSA |= (1<<0);
	}
}

void writeByte(uint8_t dataByte, uint8_t conditions)
{
	//Place data (byte) to be transmitted in the data register by writing the I2CMDR register
	I2C1->MDR = dataByte;
	//Initiate a single byte transmit of the data from Master to Slave by writing the I2CMCS register
	I2C1->MCS = conditions;
	
	//Wait until the transmission completes by polling the I2CMCS register's BUSBSY bit until it has been cleared.
	
  /*Read only MCS register*/
	while((I2C1->MCS & (1<<0)) != 0);  
	
	/*check if there are any error*/
	if((I2C1->MCS & (1<<1)) != 0){
	
		if((I2C1->MCS & (1<<4)) == 1){
			
	}
		else
		{
			I2C1->MCS = (1<<2);
			while((I2C1->MCS & (1<<0)) != 0);
		}
	
	}
	
}

int main(){
  
	/*Clock configuration*/
	
	//Enable the I2C clock using the RCGCI2C register
	SYSCTL->RCGCI2C |= (1<<1);
	//Enable the clock to the appropriate GPIO module via the RCGCGPIO register
	SYSCTL->RCGCGPIO |= (1<<0);
	
	/*GPIO Configuration*/
	
	//In the GPIO module, enable the appropriate pins for their alternate function
	GPIOA->AFSEL |= (1<<6) | (1<<7);
	//Digitalizing the pins
	GPIOA->DEN |= (1<<6) | (1<<7);
	//Enable the I2CSDA pin for open-drain operation
	GPIOA->ODR |= (1<<7);
	//Configure the PMCn fields in the GPIOPCTL register
	GPIOA->PCTL |= (3<<24) | (3<<28);
	
	/*I2C Configuration*/
	
	//Initialize the I2C Master by writing the I2CMCR register
	I2C1->MCR = 0x00000010;
	
	/*
	TPR = (System Clock/(2*(SCL_LP + SCL_HP)*SCL_CLK))-1;
  TPR = (16MHz/(2*(6+4)*100000))-1;
  TPR = 7
	*/
	I2C1->MTPR |= (7<<0);
	
	SetSlave_Address(0x20);
	setRW(0);
	
	writeByte(0x00, (1<<0) | (1<<1));   //send IODIR adress, conditions = RUN and START
	writeByte(0x00, (1<<0) | (1<<2));   //send IODIR adress, conditions = RUN and STOP
	
	while(1)
	{
		writeByte(0x09,(1<<0) | (1<<1));   //send GPIO adress, conditions = RUN and START
		
		writeByte(led++,(1<<0) | (1<<2));  //send data adress, conditions = RUN and STOP
		
		delay(1000000);
	}
	return 0;
}