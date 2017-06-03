#include <avr/io.h>

#include "usart.h"

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

}

void serial_read(char *str, int len)
{

}

int main (void)
{
	char ReceivedByte='N';
//	DDRD=0b00000010;
	for (;;) // Loop forever
	{
		//while ((UCSRA & (1 << RXC)) == 0) {}; // Do nothing until data have been received and is ready to be read from UDR
		//ReceivedByte = UDR; // Fetch the received byte value into the variable "ByteReceived"

		while ((UCSRA & (1 << UDRE)) == 0) {}; // Do nothing until UDR is ready for more data to be written to it
		UDR = ReceivedByte; // Echo back the received byte back to the computer


		PORTB=0b00000001;
		_delay_ms(1000);
		PORTB=0b00000000;
		_delay_ms(1000);
	}
}
