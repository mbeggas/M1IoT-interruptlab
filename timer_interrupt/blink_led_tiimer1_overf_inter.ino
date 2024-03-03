ISR(TIMER1_OVF_vect)
{
  
   digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));

}
 
void setup()
{
  Serial.begin(9600);
  TCCR1A = 0;           // Init Timer1A
  TCCR1B = 0;           // Init  Timer1B
  TCCR1B |= B00000100;  // Prescaler = 64
  TIMSK1 |= B00000001;  // Enable Timer Overflow Interrupt
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.println(TIMSK1);

}

void loop(){

}

