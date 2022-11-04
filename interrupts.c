#include <xc.h>
#include "interrupts.h"

/************************************
 * Function to turn on interrupts and set if priority is used
 * Note you also need to enable peripheral interrupts in the INTCON register to use CM1IE.
************************************/
void Interrupts_init(void)
{
	// turn on global interrupts, peripheral interrupts and the interrupt source 
	// It's a good idea to turn on global interrupts last, once all other interrupt configuration is done.
    PIE2bits.C1IE = 1;
    INTCONbits.IPEN = 1;
    INTCONbits.GIEL=1;
    IPR2bits.C1IP=1;
    PIE0bits.TMR0IE=1; //Enabling the timer overflow interrupter
    INTCONbits.GIEH=1;
}

/************************************
 * High priority interrupt service routine
 * Make sure all enabled interrupts are checked and flags cleared
************************************/
void __interrupt(high_priority) HighISR()
{
	if(PIR2bits.C1IF){ 					//check the interrupt source
        LATHbits.LATH3 = !LATHbits.LATH3;
        PIR2bits.C1IF=0; 						//clear the interrupt flag!
	}
    if(PIR0bits.TMR0IF){ // Timer overflow flag
        LATHbits.LATH3 = !LATHbits.LATH3;
        PIR0bits.TMR0IF = 0;
        
        TMR0H = 0b1011;
        TMR0L = 0b11011100; //Changing the High and Low default value to better match 1s
    }
    
}

