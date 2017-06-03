#include <avr/io.h>
#include<stdlib.h>
#define F_CPU 1000000UL
#include <util/delay.h>

#include <string.h>

#include "usart.h"


// function to initialize UART

void serialInit(int baud_rate, int receive_enable, int transmit_enable)
{
    int baudrate_prescale = ((F_CPU) / (baud_rate * 16UL) - 1);

	UCSRA = (0 << RXC) | (0 << TXC) | (0 << UDRE) | (0 << FE) |
        (0 << DOR) | (0 << PE) | (0 << U2X) | (0 << MPCM);

	UCSRB = (0 << RXCIE) | (0 << TXCIE) | (0 << UDRIE) | (receive_enable << RXEN) |
        (transmit_enable << TXEN) | (0 << UCSZ2) | (0 << RXB8) | (0 << TXB8);

	UCSRC = (1 << URSEL) | (0 << UMSEL) | (0 << UPM1) | (0 << UPM0) |
        (0 << USBS) | (1 << UCSZ1) | (1 << UCSZ0) | (0 << UCPOL);
    UBRRH = (baudrate_prescale >> 8);
    UBRRL = baudrate_prescale;
	if(baud_rate==9600)
		UBRRL=6;


}

void serialWriteString(const char *str)
{
    int i = 0;
    for(; i < strlen(str); i++)
    {
		while ((UCSRA & (1 << UDRE)) == 0);
        UDR = str[i];
    }
}
void serialWriteInt(const int data)
{
   char  converted[10];
   itoa(data,converted,10);
   serialWriteString(converted);
}
char serialRead()
{
    while ((UCSRA & (1 << RXC)) == 0);
    return UDR;
}

int main (void)
{
    serialInit(2400, 1, 1);
	for (;;) // Loop forever
	{
        serialWriteInt(1025);
		PORTB=0b00000001;
		_delay_ms(1000);
		PORTB=0b00000000;
		_delay_ms(1000);
	}
}
