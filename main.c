// CONFIG1L
#pragma config FEXTOSC = HS     // External Oscillator mode Selection bits (HS (crystal oscillator) above 8 MHz; PFM set to high power)
#pragma config RSTOSC = EXTOSC_4PLL// Power-up default value for COSC bits (EXTOSC with 4x PLL, with EXTOSC operating per FEXTOSC bits)

// CONFIG3L
#pragma config WDTE = OFF        // WDT operating mode (WDT enabled regardless of sleep)

#include <xc.h>
#include "LEDarray.h"
#include "interrupts.h"
#include "comparator.h"
#include "timers.h"
#include "ADC.h"

#define _XTAL_FREQ 64000000 //note intrinsic _delay function is 62.5ns at 64,000,000Hz  

#define _TEST_MODE 1
#define _CURRENT_DAY 06 //Current day on the installation
#define _CURRENT_MONTH 11 //Current month on the installation
#define _LEAP_YEAR 2 //In how many year will there be a leap year. If there was or will be a leap year this year, input 0

void main(void) {
	//call your initialisation functions to set up the hardware modules
    LATHbits.LATH3=0;   //set initial output statem different than the other diode for first task
    TRISHbits.TRISH3=0; //set TRIS value for pin (output)
    
    TRISDbits.TRISD7=0;
    LATDbits.LATD7=1;
    
    TRISAbits.TRISA3=1;
    
    LATHbits.LATH3 = 1;
    Comp1_init();
    Interrupts_init();
    Timer0_init(_TEST_MODE,_CURRENT_DAY,_CURRENT_MONTH,_LEAP_YEAR);
    LEDarray_init();
    ADC_init();

    unsigned int curr_day;
    unsigned int curr_month;

    while (1) {
        float curr_hour = get_hour();
        LEDarray_disp_bin((unsigned int) curr_hour);
        
        if(curr_hour >= 1 && curr_hour <= 5){
            LATHbits.LATH3 = 0;
        }else{
            LATHbits.LATH3 = 1;
        }
        
        curr_day = get_day();
        curr_month = get_month();
        curr_day += 1;
        curr_day -=1;
        
        curr_month += 1;
        curr_month -=1;
        increment_day(1);
        
    }
}