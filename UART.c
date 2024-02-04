#include "TM4C123.h"                    // Device header

/* SW1 = PF4
   SW2 = PF0
	 UART0 -> PA0 , PA1
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
	

	
//SYSTCTL Configuration
	SYSCTL->RCGCUART |= (1<<0);  //Enabling clock to UART0
	SYSCTL->RCGCGPIO |= (1<<0);  //Enabling clock to PORTA
	
//GPIO Configuration
  GPIOA->AFSEL |= (1<<0) | (1<<1) ;  //Enabling alternate function for PA0,PA1
	GPIOA->PCTL |= (1<<0) | (1<<4) ;
	GPIOA->DEN  |= (1<<0) | (1<<1) ;   //Digitalizing PA0,PA1

//UART Configuration
  UART0->CTL &= (~(1<<0)) & (~(1<<8)) & (~(1<<9));   //Disabling UART ,Tx ,Rx
  UART0->IBRD = 104;                        //set IBRD value
	UART0->FBRD = 11;                         //set FBRD value
	UART0->LCRH |= (1<<5) | (1<<6);           //setting 8 bit as word length
	UART0->CC = 0x5;                          //using PIOSC
	UART0->CTL |= (1<<0) | (1<<8) | (1<<9);   //Enabling UART ,Tx ,Rx
	
	while(1){
		//Pull up ==> released = PF4 = 1 , pressed = PF4 = 0
		Button_state1 = (GPIOF -> DATA & (1<<4))>>4;
    		
		if(Button_state1 == 0)
		{
			while((UART0->FR & (1<<5) != 0));            //To check FIFO is empty or not to load data
			UART0->DR = 'a';
			
		}
		Button_state2 = (GPIOF -> DATA & (1<<0))>>0;
		if(Button_state2==0){
			
			while((UART0->FR & (1<<5) != 0));
			UART0->DR = 'b';
		}
		
			
	}
	return 0;
}