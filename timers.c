#include <xc.h>
#include "timers.h"

/************************************
 * Function to set up timer 0
************************************/

unsigned long time_counter = 0;
unsigned short test_mode = 0;

void Timer0_init(unsigned short init_test_mode)
{
    T0CON1bits.T0CS=0b010; // Fosc/4
    T0CON1bits.T0ASYNC=1; // see datasheet errata - needed to ensure correct operation when Fosc/4 used as clock source
    
    T0CON1bits.T0CKPS=8; // 1:16000000
    
    T0CON0bits.T016BIT=1;	//16bit mode	
	test_mode = init_test_mode;
    // it's a good idea to initialise the timer registers so we know we are at 0
    TMR0H = 0b1011;
    TMR0L = 0b11011100;
    T0CON0bits.T0EN=1;	//start the timer
}

/************************************
 * Function to return the full 16bit timer value
 * Note TMR0L and TMR0H must be read in the correct order, or TMR0H will not contain the correct value
************************************/
unsigned int get16bitTMR0val(void)
{
    unsigned int low_bits = TMR0L;
    unsigned int high_bits = TMR0H<<8;
    
    return(low_bits|high_bits);
	//add your code to get the full 16 bit timer value here
}

unsigned long get_time(){
    //Get the current time in seconds
    return time_counter;
}

unsigned long set_time(unsigned long time){
    time_counter = time;
    if(time_counter >= 86401){ //Reset time counter after 1 day
        time_counter = 0;
    }
    return time_counter;
}

unsigned long increment_time(unsigned long increment){
    
    if(test_mode == 0){
        time_counter += increment;
    }else{
        time_counter += increment*3600;
    }
    if(time_counter >= 86400){ //Reset time counter after 1 day
        time_counter = 0;
    }

    return time_counter;
}

unsigned int get_hour(){
    return time_counter/3600;
}
