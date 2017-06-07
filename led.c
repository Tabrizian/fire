#include "constant.h"

#include <avr/io.h>
#include <util/delay.h>

#include "led.h"

void led_init()
{
	DDRB = DDRB | (1 << DDB0);
}

void led_on()
{
	PORTB = PINB | 0b00000001;
}

void led_off()
{
	PORTB = PINB & 0b11111110;
}
