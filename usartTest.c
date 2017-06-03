#include<avr/io.h>
#define FOSC 1000000UL
#define BAUD_PRESCALE ((F_CPU)/(BAUD*16UL)-1)            // set baud rate value for UBRR
#define F_CPU 1000000UL
#include<avr/interrupt.h>
#include<util/delay.h>
#define BAUD 2400                                   // define baud
  
// function to initialize UART

int main (void)
{
	char ReceivedByte='N';
//	DDRD=0b00000010;
	UCSRA=0b00000000;
	UCSRB =0b00001000;
	UCSRC =0b10000110;
	UBRRH =0b00000000; 
	UBRRL =0b00011001;
	DDRB=0b00000001;
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
