#include "TM4C123.h"                    // Device header

/*
PF2 - 	Greeen LED (PWM 1 - Channel 6)
PA2 & PA3 - Direction of motor
*/
void delay(long d)
{
	while(d--);
}

void Turn_OtherDirection(void);
void Turn_oneDirection(void);

uint16_t i;

void Turn_oneDirection(void)
{
     SYSCTL->RCGCGPIO |= 0x01;   /* enable clock to PORTA */
	   GPIOA->DIR |= (1<<3)|(1<<2);            /* pin digital */
     GPIOA->DEN |= (1<<3)|(1<<2);            /* pin digital */
     GPIOA->DATA |=(1<<2);
		 GPIOA->DATA &=~(1<<3);
}

//Spin motor in other direction by giving IN1 and IN2 signals to L298N

void Turn_OtherDirection(void)
{
     SYSCTL->RCGCGPIO |= 0x01;   /* enable clock to PORTA */
	   GPIOA->DIR |= (1<<3)|(1<<2);            /* pin digital */
     GPIOA->DEN |= (1<<3)|(1<<2);            /* pin digital */
     GPIOA->DATA |=(1<<3);
		 GPIOA->DATA &=~(1<<2);
}

int main()
{
	 /* Clock setting for PWM and GPIO PORT */
      SYSCTL->RCGCPWM |= (1<<1);  /*Enable clock to PWM1 module */
      SYSCTL->RCGCGPIO |= (1<<5); /* Enable system clock to PORTF */
      //f =16000Hz
	    SYSCTL->RCC |= (1<<20);    /* Enable System Clock Divisor function  */
	    SYSCTL->RCC |= 0x000E0000; /* Use pre-divider valur of 64 and after that feed clock to PWM1 module*/
	
	
   /* setting of PF2 pin for M1PWM6 channel output pin */
      GPIOF->AFSEL |= (1<<2);    /* PF2 sets a alternate function */
      GPIOF->PCTL = 0x00000500;  /* make PF2 PWM output pin */
      GPIOF->DEN |= (1<<2);      /*set PF2 as a digital pin */
	
   /* PWM1 channel 6 setting */
      PWM1->_3_CTL &= (~(1<<0));   /* Disable Generator 3 counter */
      PWM1->_3_CTL &= (~(1<<1));   /* select down count mode of counter 3*/
      PWM1->_3_LOAD = 1600;        /* set load value for 10KHz (16MHz/16000) */
      PWM1->_3_CMPA = 800;         /* set duty cyle to 50% by loading of 16000 to PWM1CMPA */
      PWM1->_3_GENA |= (1<<2) | (1<<3) | (1<<7); /*Set PWM output when counter reloaded and clear when match*/
	    PWM1->_3_CTL |= (1<<0);     /* Enable Generator 3 counter */
      PWM1->ENABLE |= (1<<6);      /* Enable PWML channel 6 output */

      Turn_oneDirection();
	
	while(1)
	{
		for (i=0; i<16000; i++){
      PWM1->_3_CMPA = i;
      delay (1000);
		}
    
		delay (1000000) ;
    
		for (i=16000; i>0; i--){
      PWM1->_3_CMPA = i;
      delay (1000);
	  }
 }
}
