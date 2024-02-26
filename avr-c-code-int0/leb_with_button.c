#ifndef F_CPU
#define F_CPU 16000000
#endif

#include <avr/io.h>
#include<util/delay.h>

int main(void)
{
  DDRB = DDRB | (1<<PINB5);  //0x20   PINB5 output
  PORTB = PORTB & ~(1<<PINB5);
 
  DDRD = DDRD & ~(1<<PIND2);  //0x00 PINC2 input
  PORTD = PORTD | (1<<PINC2); //0x02 for setting input_pullup

    while (1){
		if((PIND & (1<<PIND2)) == 0x00){ // PIND&0x02==0
						 // read PIND2 and check if it is LOW
		  _delay_ms(200); 
		  PORTB = PORTB ^ (1<<PINB5); //XOR to toggle the bit 5
						//if 1=>0, if 0=>1		 
		}	
    }
}
