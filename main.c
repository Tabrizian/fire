#include "constant.h"

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "usart.h"
#include "adc.h"
#include "led.h"

int state = ACTIVE_NORMAL;

int main (void)
{
    int fire;
    int reported = 0;

    serial_init(2400, 1, 1);

    adc_init();
    led_init();

    while(1)
    {
        fire = adc_smooth(0);
        if(fire > FIRE_THRESHOLD)
        {
            switch(state)
            {
                case ACTIVE_NORMAL:
                    reported = 0;
                    led_on();
                    break;

                case ACTIVE_QUIET:
                    if(reported == 0)
                        serial_write_string("Fire \r\n");
                    reported = 1;
                    led_off();
                    break;

                case DEACTIVE:
                    reported = 0;
                    led_off();
                    break;
            }
        } else {
            reported = 0;
            led_off();
        }
    }
}

