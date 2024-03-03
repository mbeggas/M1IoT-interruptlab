#ifndef F_CPU
#define F_CPU 16000000
#endif

#include <avr/io.h>
#include<util/delay.h>
#include <avr/interrupt.h>
#include <stdbool.h>
#include <stdio.h>

// Handle interrupt TIMER1_OVF_vect
ISR (TIMER1_OVF_vect) {
	// Toggle LED
	PORTB = PORTB ^ (1<<PINB5); //XOR to toggle the bit 5
}

int main(void)
{
  DDRB = DDRB | (1<<PINB5);  //0x20   PINB5 output
	
  TCCR1A = 0;           // Init Timer1A
  TCCR1B = 0;           // Init  Timer1B
  TCCR1B |= 0b00000100;  // Prescaler = 64
  TIMSK1 |= 0b0000001;  // Enable Timer Overflow Interrupt

  sei();
	
  while (1);
}