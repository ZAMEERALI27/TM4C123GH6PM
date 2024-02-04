#include "TM4C123.h"             // Device header

/*
a - PA7
b - PA6
c - PA5
d - PB4
e - PE5
f - PE4
g - PB1
h - PB0
*/

void delay(long d)
{
	while(d--);
}

void Printdata(unsigned char data)
{
	//zeroth bit = a = PA7
  if ((data&0x01) == 0x01) {GPIOA -> DATA = GPIOA -> DATA | (1<<7); }
	else {GPIOA -> DATA = GPIOA -> DATA | (~(1<<7));}

  //firsth bit = b = PA6 
	if ((data&0x02) == 0x02) {GPIOA -> DATA = GPIOA -> DATA | (1<<6);}
	else {GPIOA -> DATA = GPIOA -> DATA | (~(1<<6));}

  //second bit = c = PA5
  if ((data&0x04) == 0x04) {GPIOA -> DATA = GPIOA -> DATA | (1<<5);}
  else{GPIOA -> DATA = GPIOA -> DATA | (~(1<<5));}

  //third bit = d = PB4
  if ((data&0x08) == 0x08) {GPIOB -> DATA = GPIOB -> DATA | (1<<4);}
  else {GPIOB -> DATA = GPIOB -> DATA | (~(1<<4));}

	//fourth bit = e = PE5
  if ((data&0x10) == 0x10) {GPIOE -> DATA = GPIOE -> DATA | (1<<5);}
  else {GPIOE -> DATA = GPIOE -> DATA | (~(1<<5));}

	//fifth bit = f = PE4 
  if ((data&0x20) == 0x20) {GPIOB -> DATA = GPIOE -> DATA | (1<<4);}
  else {GPIOE -> DATA = GPIOE -> DATA | (~(1<<4));}

	//sixth bit = g = PB1 
	if ((data&0x40) == 0x40) {GPIOB -> DATA = GPIOB -> DATA | (1<<1);}
  else {GPIOB -> DATA = GPIOB -> DATA | (~(1<<1));}
  
	//seventh bit = h = PB0
	if ((data&0x80) == 0x80) {GPIOB -> DATA = GPIOB -> DATA | (1<<0);}
	else {GPIOB -> DATA = GPIOB -> DATA | (~(1<<0));}
	}

int main()
{
	//enabling clock of Port A ,Port B ,Port E
	SYSCTL -> RCGCGPIO = SYSCTL -> RCGCGPIO | (1<<0)| (1<<1) | (1<<4); 
	
	//Digitalizing the pins
	GPIOA -> DEN = GPIOA ->DEN | (1<<5) | (1<<6) | (1<<7);
	GPIOB -> DEN = GPIOB ->DEN | (1<<0) | (1<<1) | (1<<4);
	GPIOE -> DEN = GPIOE ->DEN | (1<<4) | (1<<5);
	
	//Config the pins as output
	GPIOA -> DIR = GPIOA -> DIR | (1<<5) | (1<<6) | (1<<7);
	GPIOB -> DIR = GPIOB -> DIR | (1<<0) | (1<<1) | (1<<4);
	GPIOE -> DIR = GPIOE -> DIR | (1<<4) | (1<<5);
	
	
	
	
	while(1)
	{
		Printdata(0x82);
		delay(10000);
		
	}
	return 0;
}
