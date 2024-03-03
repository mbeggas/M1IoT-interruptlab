ISR(TIMER1_COMPA_vect)
{
  OCR1A += 16384; // Advance The COMPA Register
   digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
   Serial.println("sssss");
}

ISR(TIMER1_OVF_vect)
{ 
   digitalWrite(12, !digitalRead(12));
  Serial.println("BBBBBBBBBBBBBBB");
}

void setup()
{
  Serial.begin(9600);
  TCCR1A = 0;           // Init Timer1
  TCCR1B = 0;           // Init Timer1
  TCCR1B |= B00000101;  // Prescalar = 256
  OCR1A = 16384;        // Timer CompareA Register
  TIMSK1 |= B00000011;  // Enable Timer COMPA and OVT1 Interrupts

  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(12, OUTPUT);
}
void loop(){}