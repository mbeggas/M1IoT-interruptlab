#ifndef F_CPU
#define F_CPU 16000000
#endif

#include <avr/io.h>
#include<util/delay.h>
#include <avr/interrupt.h>
#include <stdbool.h>
#include <stdio.h>
#define BAUD 9600
#define MYUBRR F_CPU/16UL/BAUD-1

void usart_init(uint16_t ubrr);
char usart_getchar( void );
void usart_putchar( char data );
void usart_pstr (char *s);
unsigned char usart_kbhit(void);
int usart_putchar_printf(char var, FILE *stream);

static FILE mystdout = FDEV_SETUP_STREAM(usart_putchar_printf, NULL, _FDEV_SETUP_WRITE);
int intFlag = 0;

// Handle interrupt at INT0
ISR (INT0_vect) {

	// Toggle LED
	PORTB = PORTB ^ (1<<PORTB5); //XOR to toggle the bit 5
								//if 1=>0, if 0=>1
	intFlag = 1;					
}

int main(void)
{
	DDRB = DDRB | (1<<PINB5);  //0x20   PINB5 output
	PORTB = PORTB & ~(1<<PINB5);
	
	DDRD = DDRD & ~(1<<DDD2);  //0x00 PIND2 input
	PORTD =  0x04;//PORTD | (1<<PORTD2);	//0x04 for setting input_pullup 
	printf("1st %d \n", PIND);
	    // Set External Interrupt Control Register A
	    // to 10: The low level of INT0 generates an interrupt request.
	   EICRA = (EICRA & ~(1 << ISC00))| (1 << ISC01);

		// Set External Interrupt Mask Register
		// to INT0 to activate interrupt INT0
		EIMSK |= (1 << INT0);
	    sei();
	// setup our stdio stream
	stdout = &mystdout;
	    
	// fire up the usart
	usart_init ( MYUBRR );
	
    
    while (1) 
    {
		if(intFlag==0)
			// Enable interrupts
			EIMSK |= (1 << INT0);
		else{
			// Disable interrupts
			EIMSK = EIMSK & ~(1 << INT0);

			// Debouncing by delaying for 1000ms
			_delay_ms(10000);

			// Reset flag to re-enable interrupts
			intFlag = 0;
		}
		

    }
}

// ********************************************************************************
// usart Related
// ********************************************************************************
void usart_init( uint16_t ubrr) {
    // Set baud rate
    UBRR0H = (uint8_t) (ubrr >> 8);
    UBRR0L = (uint8_t) ubrr;
    // Enable receiver and transmitter
    UCSR0B = (1 << RXEN0) | (1 << TXEN0);
    // Set frame format: 8data, 2stop bit
    UCSR0C = (1 << USBS0) | (3 << UCSZ00);
}
void usart_putchar(char data) {
    // Wait for empty transmit buffer
    while ( !(UCSR0A & (1 << UDRE0)))
    {}
    // Start transmission
    UDR0 = data;
}
char usart_getchar(void) {
    // Wait for incoming data
    while ( !(UCSR0A & (1 << RXC0)) );
    // Return the data
    return UDR0;
}
//unsigned char usart_kbhit(void) {
	////return nonzero if char waiting polled version
	//unsigned char b;
	//b=0;
	//if(UCSR0A & (1<<RXC0)) b=1;
	//return b;
//}
void usart_pstr(char *s) {
	// loop through entire string
	while (*s) {
		usart_putchar(*s);
		s++;
	}
}

// this function is called by printf as a stream handler
int usart_putchar_printf(char var, FILE *stream) {
	// translate \n to \r for br@y++ terminal
	if (var == '\n') usart_putchar('\r');
	usart_putchar(var);
	return 0;
}
