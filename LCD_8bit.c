#include "TM4C123.h" // Device header

void delay(long d);
void Printdata(unsigned char data);
void lcd_data(unsigned char data);
void lcd_cmd(unsigned char cmd);
void lcd_string(char *str,unsigned char len);
void lcd_init(void);


/*
RS - PD0
RW - PD1
EN - PD2

D0 - PA7
D1 - PA6
D2 - PA5
D3 - PB4
D4 - PE5
D5 - PE4
D6 - PB1
D7 - PB0
*/




int main()
{
	//enable clock for PORT A,B,D,E
	SYSCTL->RCGCGPIO = SYSCTL->RCGCGPIO | (1<<0) | (1<<1) | (1<<3) | (1<<4);
	
	//Digitalizing the pins
	GPIOA -> DEN = GPIOA ->DEN | (1<<5) | (1<<6) | (1<<7);
	GPIOB -> DEN = GPIOB ->DEN | (1<<0) | (1<<1) | (1<<4);
	GPIOD -> DEN = GPIOD -> DEN | (1<<0) | (1<<1) | (1<<2);
	GPIOE -> DEN = GPIOE ->DEN | (1<<4) | (1<<5);

	
	//direction of the pins
	GPIOA -> DIR = GPIOA -> DIR | (1<<5) | (1<<6) | (1<<7);
	GPIOB -> DIR = GPIOB -> DIR | (1<<0) | (1<<1) | (1<<4);
	GPIOD -> DIR = GPIOD -> DIR | (1<<0) | (1<<1) | (1<<2);
	GPIOE -> DIR = GPIOE -> DIR | (1<<4) | (1<<5);
	delay(10000);
	lcd_init();
	lcd_cmd(0x80);  //cursor to first row first column
	//lcd_data('a');
	lcd_string("ZAMEER",6);
	lcd_cmd(0xC0);  //cursor to second row first column
	lcd_string("ALI",3);

	return 0;
}

void lcd_data(unsigned char data)
{
	Printdata(data);           //Passing 8bit data to datalines
	GPIOD->DATA &= (~(1<<1));  //Turn Off Rw of writing operation
	GPIOD->DATA |= (1<<0);     //Turn On Rs for writing to data register of LCD
	GPIOD->DATA |= (1<<2);     //Turn On En for enabling clock of LCD
  delay(1000);        
  GPIOD->DATA &= (~(1<<2));  //Turn Off En of LCD  
	
}

void lcd_cmd(unsigned char cmd)
{
	Printdata(cmd);           //Passing 8bit data to datalines
	GPIOD->DATA &= (~(1<<1));  //Turn Off Rw of writing operation
	GPIOD->DATA &= (~(1<<0));     //Turn Off Rs for writing to instruction register of LCD
	GPIOD->DATA |= (1<<2);     //Turn On En for enabling clock of LCD
  delay(1000);        
  GPIOD->DATA &= (~(1<<2));  //Turn Off En of LCD 
}

void lcd_string(char *str,unsigned char len)
{
	char i;
	for(i=0;i<len;i++){
		lcd_data(str[i]);
	}
}

void delay(long d)
{
	while(d--);
}

void lcd_init(void)
{
	lcd_cmd(0x38);  //utilizing 8bit mode for 16x2
	lcd_cmd(0x06);  //auto incrementing the cursor 
	lcd_cmd(0x0C);  //cursor off and display on
	lcd_cmd(0x01);  //clear screen
}
void Printdata(unsigned char data)
{
	//zeroth bit = D0 = PA7
  if ((data&0x01) == 0x01) {GPIOA -> DATA = GPIOA -> DATA | (1<<7); }
	else {GPIOA -> DATA = GPIOA -> DATA | (~(1<<7));}

  //firsth bit = D1 = PA6 
	if ((data&0x02) == 0x02) {GPIOA -> DATA = GPIOA -> DATA | (1<<6);}
	else {GPIOA -> DATA = GPIOA -> DATA | (~(1<<6));}

  //second bit = D2 = PA5
  if ((data&0x04) == 0x04) {GPIOA -> DATA = GPIOA -> DATA | (1<<5);}
  else{GPIOA -> DATA = GPIOA -> DATA | (~(1<<5));}

  //third bit = D3 = PB4
  if ((data&0x08) == 0x08) {GPIOB -> DATA = GPIOB -> DATA | (1<<4);}
  else {GPIOB -> DATA = GPIOB -> DATA | (~(1<<4));}

	//fourth bit = D4 = PE5
  if ((data&0x10) == 0x10) {GPIOE -> DATA = GPIOE -> DATA | (1<<5);}
  else {GPIOE -> DATA = GPIOE -> DATA | (~(1<<5));}

	//fifth bit = D5 = PE4 
  if ((data&0x20) == 0x20) {GPIOB -> DATA = GPIOE -> DATA | (1<<4);}
  else {GPIOE -> DATA = GPIOE -> DATA | (~(1<<4));}

	//sixth bit = D6 = PB1 
	if ((data&0x40) == 0x40) {GPIOB -> DATA = GPIOB -> DATA | (1<<1);}
  else {GPIOB -> DATA = GPIOB -> DATA | (~(1<<1));}
  
	//seventh bit = D7 = PB0
	if ((data&0x80) == 0x80) {GPIOB -> DATA = GPIOB -> DATA | (1<<0);}
	else {GPIOB -> DATA = GPIOB -> DATA | (~(1<<0));}
	}
