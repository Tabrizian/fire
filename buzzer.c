#include "constant.h"

#include <avr/io.h>
#include <util/delay.h>

#include "buzzer.h"

void buzzerInit()
{
	DDRB = DDRB | (1 << DDB0);
}

void buzzerRing()
{
    int i = 0;
    for(;i < 400; i++)
    {
        PORTB = PINB ^ 0b0000001;
        _delay_ms(50);
    }

    PORTB = PINB ^ 0b0000001;
}

void buzzerOn()
{
	PORTB = PINB & 0b11111110;
}

void buzzerOff()
{
	PORTB = PINB | 0b00000001;
}
