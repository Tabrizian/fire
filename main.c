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
    int fire = adc_smooth(0);
    serialWriteString("\r\n");
    serialWriteString("\r\n");
    serialWriteString("\r\n");
    serialWriteInt(fire);
    serialWriteString("\r\n");
    serialWriteString("\r\n");
    serialWriteString("\r\n");
    if(UDR == '0') {
    serialWriteString("\r\n");
    serialWriteString("\r\n");
    serialWriteString("\r\n");
    serialWriteString("Normal mode activated! \r\n");
    serialWriteString("\r\n");
    serialWriteString("\r\n");
    serialWriteString("\r\n");
        state = ACTIVE_NORMAL;
	
    } else if(UDR == '1') {
    serialWriteString("\r\n");
    serialWriteString("\r\n");
    serialWriteString("\r\n");
	serialWriteString("Normal quiet mode activated! \r\n");
    serialWriteString("\r\n");
    serialWriteString("\r\n");
    serialWriteString("\r\n");
        state = ACTIVE_QUIET;
    } else if(UDR == '2') {
    serialWriteString("\r\n");
    serialWriteString("\r\n");
    serialWriteString("\r\n");
	serialWriteString("Deactivated! \r\n");
    serialWriteString("\r\n");
    serialWriteString("\r\n");
    serialWriteString("\r\n");
        state = DEACTIVE;
    }

}

int main (void)
{
    int fire;
    serialInit(2400, 1, 1);
    adc_init();

   sei();

    DDRB = 0b00000001;
    PORTB = 0b00000001;


    for (;;)
    {
    fire = adc_read(0);
    serialWriteString("\r\n");
    serialWriteString("\r\n");
    serialWriteString("\r\n");
	    serialWriteInt(fire);
    serialWriteString("\r\n");
    serialWriteString("\r\n");
    serialWriteString("\r\n");
        if(fire > FIRE)
        {
            switch(state)
            {
                case ACTIVE_NORMAL:
                    ledOn();
                    break;
                case ACTIVE_QUIET:
    serialWriteString("\r\n");
    serialWriteString("\r\n");
    serialWriteString("\r\n");
                    serialWriteString("Fire \r\n");
    serialWriteString("\r\n");
    serialWriteString("\r\n");
    serialWriteString("\r\n");
                    break;
                case DEACTIVE:
                    break;
            }
        } else {
            ledOff();
        }
    }
}

