// CONFIG1L
#pragma config FEXTOSC = HS     // External Oscillator mode Selection bits (HS (crystal oscillator) above 8 MHz; PFM set to high power)
#pragma config RSTOSC = EXTOSC_4PLL// Power-up default value for COSC bits (EXTOSC with 4x PLL, with EXTOSC operating per FEXTOSC bits)

// CONFIG3L
#pragma config WDTE = OFF        // WDT operating mode (WDT enabled regardless of sleep)

#include <xc.h>
#include "LEDarray.h"
#include "interrupts.h"
#include "timers.h"
#include "ADC.h"
#include "LCD.h"

#define _XTAL_FREQ 64000000 //note intrinsic _delay function is 62.5ns at 64,000,000Hz  

int seconds = 0;

void main(void) {
	//call your initialisation functions to set up the hardware modules
    //LEDarray_init();  
    Timer0_init();
    Interrupts_init();
    LCD_Init();
    ADC_init();
    
    char Sec[2];
    char Min[2];
    char Hou[2];
    char Day[2];
    char Mon[2];
    char Yea[4];
    char ADC[3];
    char day_of_the_week[] = {"MON","TUE","WED","THU","FRI","SAT","SUN"};
    while (1) {
        LCD_clear();
        
        ADC2String(Sec, get_seconds(), 2);
        ADC2String(Min, get_minutes(), 2);
        ADC2String(Hou, get_hours(), 2);
        ADC2String(Day, get_day(), 2);
        ADC2String(Mon, get_month()+1, 2);
        ADC2String(Yea, get_year(), 4);   
        ADC2String(ADC, ADC_getval(), 3);
        
        char *lst[8] = {get_week_day(),Day,Mon,Yea,Hou,Min,Sec,ADC};
        LCD_sendstring(lst);
        __delay_ms(100);
    }
}
