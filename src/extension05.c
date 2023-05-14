/***
 * Ex E5.0
 * 
 * Your task is to write code to implement a two-tone siren 
 * using the QUTy. You must use one of the Waveform Outputs 
 * of TCA0 to drive the buzzer. The buzzer should always
 * be driven with a 50% duty cycle signal.
 * 
 * Your siren must use the following two frequencies:
 *     f1 = 2AB0 Hz
 *     f2 = 4CD0 Hz
 * The siren should alternate between f1 and f2, with 
 * f1 active for T1 = 3E0 ms, and f2 active for T2 = 6F0 ms, 
 * where A-F are the 2nd through 7th digits of your student
 * number, e.g. nXABCDEFX.
 * 
 * EXAMPLE: If your student number were n12345678, then
 *   A = 2, B = 3, C = 4, D = 5, E = 6, F = 7
 *   f1 = 2230 Hz, f2 = 4450 Hz, T1 = 360 ms, T2 = 670 ms
 * 
 * Your programme must be interrupt driven. The code you 
 * write in this file (extension05.c) will be compiled 
 * alongside a main.c which we provide. main() will call 
 * the init() function you write below and then drop into 
 * an infinite loop. The init() function you write MUST 
 * return (to demonstrate your code is interrupt driven).
 * 
 * In addition to init(), you may write any code you wish
 * in this file, including ISRs.
 * 
 * We have provided a copy of the main.c code we will use
 * to test your code, so that you can build and test your
 * code locally. You should not write any code in main.c
 * as it will be replaced when you upload your programme.
 */ 

// my combo:  A = 1, B = 3, C = 1, D = 8, E = 5, F = 4
// f1 = 2AB0 = 2130, f2 = 4CD0 = 4180 
// t1 = 3E0 = 350, t2 = 6F0 = 640 
#include <stdio.h>
#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>
volatile uint8_t state = 0;
ISR(TCA0_OVF_vect) {
    if (state == 0) {
        TCA0.SINGLE.PERBUF = 9390;
        TCA0.SINGLE.CMP0BUF = 18779;
        _delay_ms(350);
        state = 1;
    } else {
        TCA0.SINGLE.PERBUF = 7485;
        TCA0.SINGLE.CMP0BUF = 9569;
        _delay_ms(640);
        state = 0;
    }
    TCA0.SINGLE.INTFLAGS = TCA_SINGLE_OVF_bm;
}
void init() {
    cli();
    PORTB.DIR |= PIN0_bm;
    TCA0.SINGLE.CTRLB = TCA_SINGLE_WGMODE_SINGLESLOPE_gc | TCA_SINGLE_CMP0EN_bm;
    TCA0.SINGLE.CMP0 = 782;
    TCA0.SINGLE.PER = 1564;
    TCA0.SINGLE.INTCTRL |= TCA_SINGLE_OVF_bm;
    TCA0.SINGLE.CTRLA = TCA_SINGLE_CLKSEL_DIV1_gc | TCA_SINGLE_ENABLE_bm;
    sei();
}

// Write your code for Ex E5.0 above this line.

