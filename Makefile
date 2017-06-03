all:
	avr-gcc -c -mmcu=atmega8  usartTest.c -o usartTest.o
	avr-gcc -c -mmcu=atmega8  adc.c -o adc.o
	avr-gcc -c -mmcu=atmega8  usart.c -o usart.o
	avr-gcc -mmcu=atmega8 usartTest.o adc.o usart.o -o temp.elf
	avr-objcopy -O ihex -j .text -j .data temp.elf temp.hex


