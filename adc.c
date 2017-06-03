#include<avr/io.h>

#include "adc.h"
#include "constant.h"

void adc_init()
{
    ADCSRA = (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0) |
        (0 << ADSC) | (0 << ADFR) | (0 << ADIF) | (0 << ADIE);

    ADMUX  = (0 << REFS1) | (1 << REFS0) | (0 << ADLAR);
}

uint16_t adc_read(uint8_t channel)
{
    channel = channel & 0b00001111;
    ADMUX |= channel;


    ADCSR |= (1 << ADSC);

   while(!(ADCSRA & (1 << ADIF)));


   ADCSRA |= (1 << ADIF);

   return ADC;
}

uint16_t adc_smooth(uint8_t channel)
{
    uint16_t result = 0;
    int i = 0;
    for(; i < SAMPLE_RATE; i++)
    {
        result += adc_read(channel);
    }

    result = result / SAMPLE_RATE;
    return result;
}
