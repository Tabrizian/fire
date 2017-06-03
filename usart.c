#include <avr/io.h>
#include <util/delay.h>

#include <string.h>

#include "usart.h"

#define F_CPU 1000000UL

// function to initialize UART

void serial_init(int baud_rate, int receive_enable, int transmit_enable)
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

}

void serial_write(const char *str)
{
    int i = 0;
    for(; i < strlen(str); i++)
    {
		while ((UCSRA & (1 << UDRE)) == 0);
        UDR = str[i];
    }
}

char serial_read()
{
    while ((UCSRA & (1 << RXC)) == 0);
    return UDR;
}

int main (void)
{
    serial_init(9600, 1, 1);
	for (;;) // Loop forever
	{
        serial_write("Salam");
		PORTB=0b00000001;
		_delay_ms(1000);
		PORTB=0b00000000;
		_delay_ms(1000);
	}
}
