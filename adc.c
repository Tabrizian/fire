#include<avr/io.h>

#include "adc.h"
#include "constant.h"

void adcInit()
{
    ADCSRA = (1 << ADEN) | (0 << ADSC) | (0 << ADATE) |  (0 << ADIF)| (0 << ADIE)| (1 << ADPS2)  |(1 << ADPS1) | (1 << ADPS0) ;

    ADMUX  = (0 << REFS1) | (1 << REFS0) | (0 << ADLAR);
}

uint16_t adcRead(uint8_t channel)
{
    channel = channel & 0b00001111;
    ADMUX |= channel;


    ADCSRA |= (1 << ADSC);

   while(!(ADCSRA & (1 << ADIF)));


   ADCSRA |= (1 << ADIF);

   return ADC;
}

uint16_t adcSmooth(uint8_t channel)
{
    uint16_t result = 0;
    int i = 0;
    for(; i < SAMPLE_RATE; i++)
    {
        result += (adcRead(channel)/SAMPLE_RATE);
    }

    return result;
}
