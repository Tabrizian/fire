#ifndef USART_H
#define USART_H

void serialInit(int,int,int);
void serialWriteString(const char*);
void serialWriteInt(const int);
void serialWriteNewLine();
char serialRead();
#endif
