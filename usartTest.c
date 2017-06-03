#include "constant.h"

#include <avr/io.h>
#include <util/delay.h>

#include "usart.h"
#include "adc.h"

int main (void)
{
    serialInit(2400, 1, 1);
    adc_init();
    DDRB = 0b00000001;
	for (;;) // Loop forever
	{
        serialWriteInt(adc_read(0));
		PORTB=0b00000001;
		_delay_ms(1000);
		PORTB=0b00000000;
		_delay_ms(1000);
	}
}

