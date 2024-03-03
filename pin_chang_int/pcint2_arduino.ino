// LED and switch
const byte ledPin = 13;
const byte buttonPin = 7;
 
// Boolean to represent toggle state
volatile bool togglestate = false;
 
void setup() {
 
  // Set LED as output
  pinMode(ledPin, OUTPUT);
 
  // Set switch as input with pullup
  pinMode(buttonPin, INPUT_PULLUP);
 
 
  // Enable PCIE2 Bit3 = 1 (Port D)
  PCICR |= B00000100;
  // Select PCINT23 Bit7 = 1 (Pin D7)
  PCMSK2 |= B10000000;
 
}
 
void loop() {
  // No code in Loop
}
 
ISR (PCINT2_vect)
{
  // Interrupt for Port D
  // Invert toggle state
  togglestate = !togglestate;
  // Indicate state on LED
  digitalWrite(ledPin, togglestate);
 
 
}
