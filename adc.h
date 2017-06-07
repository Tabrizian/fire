#ifndef USART_H
#define USART_H

void adcInit();

uint16_t adcRead(uint8_t channel);

uint16_t adcSmooth(uint8_t channel);

#endif
