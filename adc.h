#ifndef USART_H
#define USART_H

void adc_init();

uint16_t adc_read(uint8_t channel);

uint16_t adc_smooth(uint8_t channel);

#endif
