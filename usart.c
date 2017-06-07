#include <avr/io.h>
#include <stdlib.h>
#include <string.h>
#include <avr/interrupt.h>
#include "usart.h"
#include "constant.h"
int busySerial=0;
ISR(USART_RX_vect)
{
    uint8_t temp=UDR0;
    if(temp == ACTIVE_NORMAL+ASCII_NUMBER_BASE) {
    state = ACTIVE_NORMAL;
    serialWriteString("Normal mode activated! \r\n");
    } else if(temp == ACTIVE_QUIET+ASCII_NUMBER_BASE) {
    state = ACTIVE_QUIET;
    serialWriteString("Quiet  mode activated! \r\n");
    } else if(temp == DEACTIVE+ASCII_NUMBER_BASE) {
    state = DEACTIVE;
    serialWriteString("Deactivated! \r\n");
    }

}


// function to initialize UART

void serialInit(int baud_rate, int receiveEnable, int transmitEnable)
{
    int baudrate_prescale = ((F_CPU) / (baud_rate * 16UL) - 1);

	UCSR0A = (0 << RXC0) | (0 << TXC0) | (0 << UDRE0) | (0 << FE0) |
        (0 << DOR0) | (0 << UPE0) | (0 << U2X0) | (0 << MPCM0);

	UCSR0B = (1 << RXCIE0) | (0 << TXCIE0) | (0 << UDRIE0) | (receiveEnable << RXEN0) |
        (transmitEnable << TXEN0) | (0 << UCSZ02) | (0 << RXB80) | (0 << TXB80);

	UCSR0C = (0 << UMSEL00) | (0 << UMSEL01) | (1 << UPM01) | (0 << UPM00) |
        (0 << USBS0) | (1 << UCSZ01) | (1 << UCSZ00) | (0 << UCPOL0);

    UBRR0H = (baudrate_prescale >> 8);
    UBRR0L = baudrate_prescale;
	if(baud_rate==9600)
		UBRR0L=6;
    	if(receiveEnable)
	sei();
	if(transmitEnable){
	serialWriteString("Normal mode Activated!!");
	serialWriteNewLine();}

}

void serialWriteString(const char *str)
{
    while(busySerial);
    busySerial=1;
    int i = 0;
    for(; i < strlen(str); i++)
    {
		while ((UCSR0A & (1 << UDRE0)) == 0);
        UDR0 = str[i];
    }
   busySerial=0;
}

void serialWriteInt(const int data)
{
   char  converted[10];
   itoa(data, converted, 10);
   serialWriteString(converted);
}

char serialRead()
{
    while ((UCSR0A & (1 << RXC0)) == 0);
    return UDR0;
}

void serialWriteNewLine(){
   serialWriteString("\n\r");
}
