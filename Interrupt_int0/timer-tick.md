# 🧪 Lab : Timer Tick Event

---

## Objective

Modify the given  code to:

1. Configure timer interrupt that fires every 100 ms.
2. Create a variable `ss` that cycles from 1 to 10 repeatedly.
3. Blink a LED on **pin 13** every 100 ms (each timer tick).
4. Create a variable `elapsed_seconds` that increments every 1 second (when `ss == 10`).
5. Print the value of `elapsed_seconds` to the serial monitor every second.

---

## Starting Point Code

```cpp
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
  TCCR1B |= B00000101;  // Prescaler = 256
  OCR1A = 16384;        // Timer CompareA Register
  TIMSK1 |= B00000011;  // Enable Timer COMPA and OVF Interrupts

  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(12, OUTPUT);
}

int main() {
  setup();
  while (1);
}
