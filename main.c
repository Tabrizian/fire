#include "constant.h"

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "usart.h"
#include "adc.h"
#include "led.h"

int state = ACITVE_NORMAL;

ISR(USART_RX_vect)
{
    if(UDR == 0) {
        state = ACITVE_NORMAL;
    } else if(UDR == 1) {
        state = ACITVE_QUIET;
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
                case ACITVE_NORMAL:
                    buzzerOn();
                    break;
                case ACITVE_QUIET:
                    serialWriteString("Fire \r\n");
                    break;
                case DEACTIVE:
                    break;
            }
        }
    }
}

