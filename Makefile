compiler=avr-gcc
hexConverter=avr-objcopy
driverProgram=avrdude
all:
	$(compiler) -Wno-cpp -c -mmcu=atmega328p  FinalProject.c -o FinalProject.o
	$(compiler) -Wno-cpp -c -mmcu=atmega328p  adc.c -o adc.o
	$(compiler) -Wno-cpp -c -mmcu=atmega328p usart.c -o usart.o
	$(compiler) -Wno-cpp -c -mmcu=atmega328p  led.c -o led.o
	$(compiler) -mmcu=atmega328p FinalProject.o led.o usart.o adc.o   -o temp.elf
	$(hexConverter) -O ihex -j .text -j .data temp.elf temp.hex

install:
	$(driverProgram) -p atmega328p -c usbasp -U flash:w:temp.hex

clean:
	rm -rf *.o *.hex *.elf


