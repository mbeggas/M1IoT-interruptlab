# Timer interrupt

Timer interrupts allow you to perform a task at very specifically timed intervals regardless of what else is going on in your code.

Timer interrupts allow you to momentarily pause the normal sequence of instructions taking place in the loop at precisely timed intervals, where you execute a separate set of instructions. Once these instructions are done the microcontroller picks up again where it was in the loop.

Atemga328p (Arduino UNO) has 3 hardware timers which are:

* Timer0: 8-Bit timer (can store a maximum counter value of 255)
* Timer1: 16-Bit timer (can store a maximum counter value of 65535)
* Timer2: 8-Bit timer (can store a maximum counter value of 255)

## Atemga328p (Arduino Uno) Timer Prescaler

## Atemga328p (Arduino Uno) Timer Interrupts

## Atemga328p (Arduino Uno) Timers Control Registers
We can initialize, configure, and control Timers & Timer Interrupts using the associated registers as stated in the datasheet of the microcontroller. The Timer-associated registers are as follows:

* TCCRxA: Timer/Counter Control Register A.
* TCCRxB: Timer/Counter Control Register B.
* TCNTx: Timer/Counter Registers.
* OCRxA: Output Compare A Register.
* OCRxB: Output Compare B Register.
* TMISKx: Timer Interrupts Mask Register, enable/disable timer interrupts.
* TIFRx: Timer interrupts Flag Bits Register, read/clear timer interrupt flag bits.

Where x can be 0, 1, or 2 for timers (Timer0, Timer1, and Timer2) respectively.

