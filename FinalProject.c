#include<avr/io.h>
#define F_CPU 1000000UL
#include<util/delay.h>
#include<avr/interrupt.h>
#define sampleRate 2000
void reset(){
	//enable buzzer & ready led
	DDRB=0b00000011;
	PORTB=0b00000001;
	//Analog 2 Digital Config
	ADMUX=(1<<REFS0);                         // For Aref=AVcc;
	ADCSRA=(1<<ADEN)|(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0); //Rrescalar div factor =128
	//enable global interupt
	//sei();
}
void ready()
{
	PORTB= PINB | 0b00000010;
}
void ringTheBuzzer(){
	int i;
	for ( i=0;i<400;i++){
		PORTB=PINB ^ 0b0000001;
		_delay_ms(50);
		}
		PORTB=PINB ^ 0b0000001;
}
void turnOnTheBuzzer(){
	PORTB=PINB & 0b11111110;
}
void turnOffTheBuzzer(){
	PORTB=PINB | 0b00000001;
}
uint16_t analogRead(uint8_t ch)
{
   ch=ch&0b00000111;
   ADMUX|=ch;

   ADCSRA|=(1<<ADSC);

   while(!(ADCSRA & (1<<ADIF)));

   ADCSRA|=(1<<ADIF);

   return(ADC);
}

float getData(int channel){
float result=0;
int i=0;
for(;i<sampleRate;i++){
	result+=analogRead(channel);
}
result=result/sampleRate;
return result;
}
int main(){
	reset();
	ready();
	while(1)
	{
//		if(getData(0)>650)
		turnOnTheBuzzer();
//		ringTheBuzzer();
//		else
//		turnOffTheBuzzer();
	//	_delay_ms(200);
//		turnOffTheBuzzer();
	}
}

