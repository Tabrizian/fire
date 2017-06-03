all:
	avr-gcc -Wno-cpp -c -mmcu=atmega328p  main.c -o main.o
	avr-gcc -Wno-cpp -c -mmcu=atmega328p  adc.c -o adc.o
	avr-gcc -Wno-cpp -c -mmcu=atmega328p  usart.c -o usart.o
	avr-gcc -Wno-cpp -c -mmcu=atmega328p  led.c -o led.o
	avr-gcc -mmcu=atmega328p main.o adc.o usart.o led.o -o temp.elf
	avr-objcopy -O ihex -j .text -j .data temp.elf temp.hex

install:
	avrdude -c usbasp -p atmega328p -U flash:w:temp.hex

clean:
	rm -rf *.o *.hex *.elf


