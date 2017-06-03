all:
	avr-gcc -Wno-cpp -c -mmcu=atmega8  usartTest.c -o usartTest.o
	avr-gcc -Wno-cpp -c -mmcu=atmega8  adc.c -o adc.o
	avr-gcc -Wno-cpp -c -mmcu=atmega8  usart.c -o usart.o
	avr-gcc -Wno-cpp -c -mmcu=atmega8  buzzer.c -o buzzer.o
	avr-gcc -mmcu=atmega8 usartTest.o adc.o usart.o buzzer.o -o temp.elf
	avr-objcopy -O ihex -j .text -j .data temp.elf temp.hex

clean:
	rm -rf *.o *.hex *.elf


