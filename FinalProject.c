#include "constant.h"

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "usart.h"
#include "adc.h"
#include "led.h"

int state=ACTIVE_NORMAL;
int main (void)
{
    int fire;
    int reported=0;
    serialInit(2400, 1, 1);
    adcInit();
    ledInit();
    while(1)
    {
    fire = adcSmooth(0);
        if(fire > FIRE_THRESHOLD)
        {
            switch(state)
            {
                case ACTIVE_NORMAL:
	            reported=0;
                    ledOn();
                    break;
                case ACTIVE_QUIET:
		    if(reported==0)
			    serialWriteString("Fire \r\n");
		    reported=1;
		    ledOff();
                    break;
                case DEACTIVE:
		    reported=0;
		    ledOff();
                    break;
            }
        } else {
            reported=0;
            ledOff();
        }
    }
}

