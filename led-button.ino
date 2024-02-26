// Define LED and switch connections
const byte ledPin = 13;
const byte buttonPin = 2;

// Boolean to represent toggle state
volatile bool toggleState = false;

void setup() {
  // Set LED pin as output
  pinMode(ledPin, OUTPUT);
  // Set switch pin as INPUT with pullup
  pinMode(buttonPin, INPUT_PULLUP);
}

void loop() {
 if (digitalRead(buttonPin) == LOW) {
    // Switch was pressed
    // Slight delay to debounce
    delay(200);
    // Change state of toggle
    toggleState = !toggleState;
    // Indicate state on LED
    digitalWrite(ledPin,toggleState);
  }
}
