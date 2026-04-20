# Lab: Interrupt-Based Button System with UART Status + Timer LED Control

## Objective
Build a reactive embedded system using:
- External interrupt (push button)
- Timer interrupt (LED control/blinking)
- UART communication (PC ↔ Arduino)

---

## Hardware
- Arduino (ATmega328P or similar)
- 1 push button (external interrupt pin)
- 1 LED
- USB serial connection (PC terminal)

---

## System Behavior

### 1. Button (External Interrupt)
On button press:
- LED turns OFF immediately
- Arduino sends to PC: BUTTON_PRESSED


---

### 2. LED Control (Timer Interrupt)
- LED state is controlled using a timer interrupt (e.g., 100 ms tick)
- Timer can:
- maintain LED state
- optionally support blinking (extension)

---

### 3. UART Communication

#### PC → Arduino commands
- `STATUS`
- `LED=ON`
- `LED=OFF`

#### Arduino → PC responses
- `BUTTON_PRESSED`
- `LED=ON`
- `LED=OFF`
- `STATUS: ON/OFF`

---

## System Logic

### Button event flow
1. External interrupt triggers
2. LED forced OFF
3. Message sent to PC: `BUTTON_PRESSED`

---

### Status request flow
1. PC sends `STATUS`
2. Arduino responds with current LED state

---

## Interrupt Roles

### External Interrupt
- Detect button press immediately
- Set flag + send UART message

### Timer Interrupt
- Manage LED timing / blinking (optional)
- Ensure non-blocking behavior

### UART RX Interrupt
- Receive and buffer commands
- Signal main loop when command is complete

---

## Constraints
- No polling for button
- No delays inside interrupts
- All communication handled asynchronously

---

## Learning Outcomes
- External interrupt handling
- Timer-based scheduling
- UART command/response protocol
- Event-driven embedded design

---

## Extensions (Optional)
- LED blinking after button press
- Debounce using timer
- Auto status reporting every 1s
- Add second LED for UART activity
