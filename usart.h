#ifndef USART_H
#define USART_H

void serial_init(int, int, int);
void serial_write_string(const char*);
void serial_write_int(const int);
void serial_write_newline();
char serial_read();

#endif
