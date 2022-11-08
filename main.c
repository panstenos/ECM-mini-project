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
#include "LCD.h"

#define _XTAL_FREQ 64000000 //note intrinsic _delay function is 62.5ns at 64,000,000Hz  

#define _TEST_MODE 1
#define _CURRENT_MINUTE 57 // from 0 to 59
#define _CURRENT_HOUR 17 // from 0 to 23
#define _DAY_OF_THE_WEEK 1 // 1 for monday, 7 for sunday
#define _CURRENT_DAY 06 //Current day on the installation (from 1 to 30/31 depending on the month)
#define _CURRENT_MONTH 11 //Current month on the installation (from 1 to 12)
#define _CURRENT_YEAR 2022 //Current year

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
    Timer0_init(_TEST_MODE,_CURRENT_MINUTE,_CURRENT_HOUR,_CURRENT_DAY,_DAY_OF_THE_WEEK,_CURRENT_MONTH,_CURRENT_YEAR);
    LEDarray_init();
    ADC_init();
    LCD_Init();

    unsigned int curr_day;
    unsigned int curr_month;

    while (1) {
        unsigned int curr_hour = get_hours();
        LEDarray_disp_bin(curr_hour);
        
        if(curr_hour >= 1 && curr_hour <= 5){
            LATHbits.LATH3 = 0;
        }else{
            LATHbits.LATH3 = 1;
        }
        
        
        display_informations(ADC_getval());
        
        
        __delay_ms(100);
        LCD_clear();
    }
}