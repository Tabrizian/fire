all:
	avr-gcc -Wno-cpp -c -mmcu=atmega328p  FinalProject.c -o FinalProject.o 
	avr-gcc -Wno-cpp -c -mmcu=atmega328p  adc.c -o adc.o
	avr-gcc -Wno-cpp -c -mmcu=atmega328p usart.c -o usart.o
	avr-gcc -Wno-cpp -c -mmcu=atmega328p  led.c -o led.o
	avr-gcc -mmcu=atmega328p FinalProject.o led.o usart.o adc.o   -o temp.elf
	avr-objcopy -O ihex -j .text -j .data temp.elf temp.hex
	

clean:
	rm -rf *.o *.hex *.elf


