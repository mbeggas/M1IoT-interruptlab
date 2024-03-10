/*
* usart.c
*
* Created : 15-08-2020 09:34:44 PM
* Author  : Arnab Kumar Das
* Website : www.ArnabKumarDas.com
*/

#define F_CPU 16000000UL // Defining the CPU Frequency

#include <avr/io.h>      // Contains all the I/O Register Macros
#include <util/delay.h>  // Generates a Blocking Delay
#include <avr/interrupt.h> // Contains all interrupt vectors

#define USART_BAUDRATE 9600 // Desired Baud Rate
#define BAUD_PRESCALER (((F_CPU / (USART_BAUDRATE * 16UL))) - 1)

#define ASYNCHRONOUS (0<<UMSEL00) // USART Mode Selection

#define DISABLED    (0<<UPM00)
#define EVEN_PARITY (2<<UPM00)
#define ODD_PARITY  (3<<UPM00)
#define PARITY_MODE  DISABLED // USART Parity Bit Selection

#define ONE_BIT (0<<USBS0)
#define TWO_BIT (1<<USBS0)
#define STOP_BIT ONE_BIT      // USART Stop Bit Selection

#define FIVE_BIT  (0<<UCSZ00)
#define SIX_BIT   (1<<UCSZ00)
#define SEVEN_BIT (2<<UCSZ00)
#define EIGHT_BIT (3<<UCSZ00)
#define DATA_BIT   EIGHT_BIT  // USART Data Bit Selection

#define RX_COMPLETE_INTERRUPT         (1<<RXCIE0)
#define DATA_REGISTER_EMPTY_INTERRUPT (1<<UDRIE0)

volatile uint8_t USART_TransmitBuffer; // Global Buffer

void USART_Init()
{
	// Set Baud Rate
	UBRR0H = BAUD_PRESCALER >> 8;
	UBRR0L = BAUD_PRESCALER;
	
	// Set Frame Format
	UCSR0C = ASYNCHRONOUS | PARITY_MODE | STOP_BIT | DATA_BIT;
	
	// Enable Receiver and Transmitter
	UCSR0B = (1<<RXEN0) | (1<<TXEN0);
	
	//Enable Global Interrupts
	sei();
}

void USART_TransmitInterrupt(uint8_t Buffer)
{
	USART_TransmitBuffer = Buffer;
	UCSR0B |= DATA_REGISTER_EMPTY_INTERRUPT; // Enables the Interrupt
}

int main()
{
	DDRB |= 1 << 5; // Configuring PB5 / D13 as Output
	uint8_t LocalData = 'a';
	USART_Init();
	USART_TransmitInterrupt(LocalData);
	
	while (1)
	{
		PORTB |= 1<<5; // Writing HIGH to glow LED
		_delay_ms(500);
		PORTB &= ~(1<<5); // Writing LOW
		_delay_ms(500);		
	}
	
	return 0;
}

ISR(USART_UDRE_vect)
{
	UDR0 = USART_TransmitBuffer;
	//UCSR0B &= ~DATA_REGISTER_EMPTY_INTERRUPT; // Disables the Interrupt, uncomment for one time transmission of data
}