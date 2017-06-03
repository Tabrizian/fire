#ifndef USART_H
#define USART_H

void serial_init(int baud_rate);

void serial_write(const char *str);

void serial_read(char *str, int len);
#endif
