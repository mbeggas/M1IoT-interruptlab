#include <avr/io.h>
#include <avr/interrupt.h>

// TIMER1 Compare Match A Interrupt
ISR(TIMER1_COMPA_vect)
{
    OCR1A += 31250;                 // Schedule next interrupt
    PORTB ^= (1 << PORTB5);         // Toggle LED (PB5)
}

int main(void)
{
    // Set PB5 (Arduino pin 13) as output
    DDRB |= (1 << DDB5);

    // Initialize Timer1
    TCCR1A = 0;
    TCCR1B = 0;

    // Prescaler = 256
    TCCR1B |= (1 << CS12); //B00000100;

    // Initial compare value
    OCR1A = 31250;

    // Enable Timer1 Compare Match A interrupt
    TIMSK1 |= (1 << OCIE1A);

    // Enable global interrupts
    sei();

    while (1)
    {
        // Main loop does nothing
    }
}
