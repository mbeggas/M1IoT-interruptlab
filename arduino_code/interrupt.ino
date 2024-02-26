// Define LED and switch connections
const byte ledPin = 13;
const byte buttonPin = 2;
// Boolean to represent toggle state
volatile bool toggleState = false;

void checkSwitch() {
  // Check status of switch
  // Toggle LED if button pressed 
    // Change state of toggle
    toggleState = !toggleState;
    // Indicate state on LED
    digitalWrite(ledPin, toggleState);
}

void setup() {
  // Set LED pin as output
  pinMode(ledPin, OUTPUT);
  // Set switch pin as INPUT with pullup
  pinMode(buttonPin, INPUT_PULLUP);

  attachInterrupt(digitalPinToInterrupt(buttonPin),checkSwitch, FALLING);

  Serial.begin(9600);
}

void loop() {
	// Add a 5-second time delay
	// TO REPLACE OTHER WORK DONE BY THE MICROCONTROLLER
	Serial.println("Delay Started");
	delay(5000);
	Serial.println("Delay Finished");
	Serial.println(".............."); 
}
