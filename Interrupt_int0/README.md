# M1IoT-interruptlab
Intrrupt Lab for M1 IoT and Cyber security

## Why we have to use interruption?
Check and test arduino sketch in arduino IDE that toggle a led when pusshing a button 
[see the code](arduino_code_int0/led-button.ino)

```c
#ifndef F_CPU
#define F_CPU 16000000
#endif

#include <avr/io.h>
#include<util/delay.h>

int main(void)
{
  DDRB = DDRB | (1<<PINB5);  //0x20   PINB5 output
  PORTB = PORTB & ~(1<<PINB5);
 
  DDRD = DDRD & ~(1<<PIND2);  //0x00 PINC2 input
  PORTD = PORTD | (1<<PINC2); //0x02 for setting input_pullup

    while (1){
		if((PIND & (1<<PIND2)) == 0x00){ // PIND&0x02==0
						 // read PIND2 and check if it is LOW
		  _delay_ms(200); 
		  PORTB = PORTB ^ (1<<PINB5); //XOR to toggle the bit 5
						//if 1=>0, if 0=>1		 
		}	
    }
}
```

Arduino c equivalent code

```c
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
```

Now we will add a delay to the above code and adding other work to the microcontroller in the main loop, saying serial sending and delay. Now see what happen when pushing the button
[see the code](arduino_code/leb-buittonèwithdelay.ino)

```c
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

  Serial.begin(9600);
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

    // Add a 5-second time delay
    // TO REPLACE OTHER WORK DONE BY THE MICROCONTROLLER
    Serial.println("Delay Started");
    delay(5000);
    Serial.println("Delay Finished");
    Serial.println("..............");
  } 
}
```
The microcontroller not respond to the pushbutton signal when it is occupied by the other work


For C code use microship  studio [Sownload from here](https://www.microchip.com/en-us/tools-resources/develop/microchip-studio)

Now, let's try the same code above with minor changes (adding interruption)

```c
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
```
## What is an interruption?
An interrupt is a mechanism that allows a microcontroller like the ATmega328P (used in Arduino Uno) to pause its current task, handle an urgent event, and then resume execution. This improves efficiency by eliminating the need for constant polling.


## Circuit example
The used circuit for int0 codes for both arduino skechzq or avr C
![The used circuit for int0 codes for both arduino skechzq or avr C  ](https://i0.wp.com/dronebotworkshop.com/wp-content/uploads/2022/05/interrupt-test-hookup.jpg?w=768&ssl=1)

The used circuit for pin change interrupt is
![pin change i nterrupt circuit](https://i0.wp.com/dronebotworkshop.com/wp-content/uploads/2022/05/pin-change-test-hookup.jpg?w=768&ssl=1)

# Atemga328p (Arduino Uno) Extenal interrupt description

The ATMega328 microcontroller has two external interrupts: INT0 and INT1. These external interrupts allow the microcontroller to respond to external events or signals asynchronously.

### External Interrupt INT0
1. Associated with PD2 (pin 2) on the ATmega328P.
2. Triggered by any logical change (rising edge, falling edge, or level change) on the INT0 pin, depending on the configuration in the EICRA register.
3. Can be used to trigger an interrupt service routine (ISR) that responds to events such as button presses, sensor readings, or other external signals.
### External Interrupt INT1
1. Associated with PD3 (pin 3) on the ATmega328P.
2. Triggered by any logical change (rising edge, falling edge, or level change) on the INT1 pin, depending on the configuration in the EICRA register.
3. Can be used as a second external interrupt to trigger another ISR for handling additional external events or signals.

To configure INT0 or INT yhous should

STEP 01:
Configure interruption mode in ECRA (External Interrupt Control Register)
![EICRA registe](../assets/2_EICRA.jpg)

The bits ISC00 and ISC01 (bits 0 and 1) are used to configure the mode of INT0.

The bits ISC10 and ISC11 (bits 2 and 3) are used to configure the mode of INT1

The interrupts can be configured in 4 modes

![EICRA registe mode](../assets/EICRA-int-mode.png)



STEP 02:
Enable the interrupt in 
INT0 and INT1 are individually enabled by setting bits INT1 and INT0 in EIMSK (External Interrupt Mask Register).

![EIMSK registe enable](../assets/EIMSK.jpg)

The bit 0 corresponds to INT0 and the bit 1 corresponds to INT1

The interrput code is wrriten in 
```c
ISR(INT0_vect){
   // interrupt INTO code here
}
```
