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

EICRA = (EICRA & ~((1 << ISC00) | (1 << ISC01))) | (2 << ISC00);


int main(void)
{
    /* Replace with your appliation code */
	DDRB = DDRB | (1<<PINB5);  //0x20   PINB5 output
	PORTB = PORTB & ~(1<<PINB5);
	
	DDRD = DDRD & ~(1<<PIND2);  //0x00 PINC2 input
	PORTD = PORTD | (1<<PINC2);	//0x02 for setting input_pullup 
	    
	// setup our stdio stream
	stdout = &mystdout;
	    
	// fire up the usart
	usart_init ( MYUBRR );
    
    while (1) 
    {
		
		if((PIND & (1<<PIND2)) == 0x00){ // PIND&0x02==0 
										 // read PIND2 and check if it is LOW 
			_delay_ms(200);
			
			PORTB = PORTB ^ (1<<PINB5); //XOR to toggle the bit 5
										//if 1=>0, if 0=>1
			
		}
		
		printf("Delay started\n");
		_delay_ms(5000);
		printf("Delay finished\n");
		printf("..............\n");

    }
}

// ****************************************************************************
// usart Related functions
// *************************************************************************
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
    while ( !(UCSR0A & (1 << UDRE0)));
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

