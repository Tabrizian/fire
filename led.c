#include "constant.h"

#include <avr/io.h>
#include <util/delay.h>

#include "led.h"

void ledInit()
{
	DDRB = DDRB | (1 << DDB0);
}

void ledOn()
{
	PORTB = PINB | 0b00000001;
}

void ledOff()
{
	PORTB = PINB & 0b11111110;
}
