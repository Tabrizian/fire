#include "constant.h"

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "usart.h"
#include "adc.h"
#include "led.h"

int state = ACTIVE_NORMAL;

ISR(USART_RXC_vect)
{
    if(UDR == 0) {
        state = ACTIVE_NORMAL;
    } else if(UDR == 1) {
        state = ACTIVE_QUIET;
    } else if(UDR == 2) {
        state = DEACTIVE;
    }

}

int main (void)
{
    int fire;
    serialInit(2400, 1, 1);
    adc_init();

    DDRB = 0b00000001;
    PORTB = 0b00000001;

    fire = adc_smooth(0);

    for (;;)
    {
        if(fire > FIRE)
        {
            switch(state)
            {
                case ACTIVE_NORMAL:
                    ledOn();
                    break;
                case ACTIVE_QUIET:
                    serialWriteString("Fire \r\n");
                    break;
                case DEACTIVE:
                    break;
            }
        } else {
            ledOff();
        }
    }
}

