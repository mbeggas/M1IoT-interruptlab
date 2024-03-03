ISR(TIMER1_OVF_vect)
{
  
   digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));

}
 
void setup()
{
  TCCR1A = 0;           // Init Timer1A
  TCCR1B = 0;           // Init  Timer1B
  TCCR1B |= B00000100;  // Prescaler = 256
  TIMSK1 |= B00000001;  // Enable Timer Overflow Interrupt
  pinMode(LED_BUILTIN, OUTPUT);

}

void loop(){

}

