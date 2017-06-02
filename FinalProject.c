#include<avr/io.h>
#define F_CPU 1000000UL
#include<util/delay.h>
int reset(){
	//enable buzzer works
	DDRB=0b00000001;
	PORTB=0b00000001;
}
void ringTheBuzzer(){
	int i;
	for ( i=0;i<40;i++){
		PORTB=PINB ^ 0b0000001;
		_delay_ms(50);
		}
}
int main(){
	reset();
	ringTheBuzzer();	
	while(1)
	{
	}
}
