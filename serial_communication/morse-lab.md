# 🔬 Lab Task: Morse Code Display Using USART Receiver Interrupt

## 🧑‍🏫 Objective:
Modify the **USART Receiver ISR** [interrup_recption.c](./interrup_recption.c) so that when a character is received via serial (e.g., from a terminal), its **Morse code is displayed using two LEDs**:
- **Dot LED**: Lights up for `.` (dot)
- **Dash LED**: Lights up for `-` (dash)

The supported characters for this lab are: **A, B, C, D, E**

---

## Instructions:

1. **Connect two LEDs**:
   - **PB5 (13)** → Dot LED  
   - **PB4  (12)** → Dash LED

2. Inside the `USART_RX_vect` ISR:
   - Receive the character from `UDR0`.
   - Ad the logic to find the Morse code for:
     - A → `.-`
     - B → `-...`
     - C → `-.-.`
     - D → `-..`
     - E → `.`
   - Blink the **Dot LED** for `.` and the **Dash LED** for `-`.
   - Set a **500 ms delay** between every LED ON/OFF and between symbols.

3. **If any other character is received**:
   - Blink **both LEDs simultaneously** (PB4 and PB5 ON at the same time for 1000 ms).


---

## ⏱️ Timing Rules:
- LED ON: 1000 ms  
- LED OFF (between symbols): 500 ms

---

## 💡 Example:

If `'C'` is received:
- Dash LED ON → 1000 ms  
- OFF → 500 ms  
- Dot LED ON → 1000 ms  
- OFF → 500 ms  
- Dash LED ON → 1000 ms  
- OFF → 500 ms  
- Dot LED ON → 1000 ms  
- OFF → 500 ms

