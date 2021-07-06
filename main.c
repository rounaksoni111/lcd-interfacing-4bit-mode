//LCD_4_bit_mode

#include<avr/io.h>
#include<util/delay.h>

#define rs PB2
#define en PB3

void lcd_init();
void command(char);
void display(char);

int main(void)
{
	unsigned char data0[]="LCD Interfacing";
	unsigned char data1[]="By 5Voltz";


	DDRB=0xFF;
	lcd_init();

	while (1)
	{
		int i=0;
		command(0x01);
		while(data0[i]!='\0')
		{
			display(data0[i]);
			_delay_ms(100);
			i++;
		}
		command(0xC0);
		i=0;
		while(data1[i]!='\0')
		{
			display(data1[i]);
			_delay_ms(100);
			i++;
		}
	}
}

void lcd_init() // function for initialize
{
	command(0x02); // to initialize LCD in 4-bit mode.	
	command(0x28); //to initialize LCD in 2 lines, 5X7 dots and 4bit mode.
	command(0x01); //clear current screen
	command(0x0E); //display on cursor on (0C--> display on cursor off)
	command(0x80); //Position for character
}

void command(char cmd_value)
{
	char cmd_value1;

	cmd_value1 = cmd_value & 0xF0; //mask lower nibble
	
	PORTB=cmd_value1;
	PORTB&=~(1<<rs); //RS 0 for command
	PORTB|=(1<<en);  //High to low for Enable
	_delay_ms(1);
	PORTB&=~(1<<en);

	cmd_value1 = ((cmd_value<<4) & 0xF0); //shift 4-bit and mask

	PORTB=cmd_value1;
	PORTB&=~(1<<rs);
	PORTB|=(1<<en);
	_delay_ms(1);
	PORTB&=~(1<<en);
}

void display(char data_value)
{
	char data_value1;

	data_value1=data_value&0xF0;
	PORTB=data_value1;
	PORTB|=(1<<rs)|(1<<en);
	_delay_ms(1);
	PORTB&=~(1<<en)|(1<<rs);
	
	
	data_value1=((data_value<<4)&0xF0);
	PORTB=data_value1;
	PORTB|=(1<<rs)|(1<<en);
	_delay_ms(1);
	PORTB&=~(1<<en)|(1<<rs);
}
