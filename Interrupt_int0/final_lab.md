# Smart Intersection with Tramway Barrier  
**Timer Interrupt + UART Interrupt**

---

## Objective
Design a real-time embedded system using:
- **Timer interrupt** 
- **UART RX interrupt** → commands from PC

The system includes:
- Two **tricolor traffic lights**
- A **tramway barrier (motor)**
- **Manual override via UART**
- **Automatic and safety modes**

## Timing Base
- Timer interrupt every **100 ms**
- All durations are multiples of this tick

## System Modes

### 1. AUTO Mode (default after `START`)
Traffic lights operate automatically:

- When Light 1 is GREEN → Light 2 is RED
- Safe transitions via YELLOW

#### Example cycle:

L1: GREEN → YELLOW → RED → RED
L2: RED → RED → GREEN → YELLOW

#### Default durations:
- GREEN = 600 ms  
- YELLOW = 200 ms  
- RED = depends on the opposite side

### 2. MANUAL Override (via UART)

Commands allow forcing one light:

SET_GREEN1=1000
SET_RED1=600
SET_GREEN2=800

#### Behavior:
- `SET_GREEN1=1000`:
  - Light 1 → GREEN for 1000 ms  
  - Light 2 → RED  
- After timeout:
  - Return to AUTO mode  

### 3. STOP Mode (Flashing Yellow)

STOP


