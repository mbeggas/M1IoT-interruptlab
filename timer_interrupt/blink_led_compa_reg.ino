ISR(TIMER1_COMPA_vect)
{
   OCR1A += 31250; // Advance The COMPA Register
   digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));..
}
 
void setup()
{
  TCCR1A = 0;           // Init Timer1
  TCCR1B = 0;           // Init Timer1
  TCCR1B |= B00000100;  // Prescalar = 256
  OCR1A = 31250;        // Timer CompareA Register
  TIMSK1 |= B00000010;  // Enable Timer COMPA Interrupt

  pinMode(LED_BUILTIN, OUTPUT);
}
void loop(){}