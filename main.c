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
/*
#define _TEST_MODE 1
#define _CURRENT_MINUTE 59 // from 0 to 59
#define _CURRENT_HOUR 23 // from 0 to 23
#define _DAY_OF_THE_WEEK 1 // 1 for monday, 7 for sunday
#define _CURRENT_DAY 06 //Current day on the installation (from 1 to 30/31 depending on the month)
#define _CURRENT_MONTH 11 //Current month on the installation (from 1 to 12)
#define _CURRENT_YEAR 2022 //Current year
*/

void main(void) {
	//call your initialisation functions to set up the hardware modules
    //LEDarray_init();
    Timer0_init();
    Interrupts_init();
    LCD_Init();
    //char *lst[8] = {"Mon","30","01","2002","23","12","43","232"};
    int *Sec;
    int *Min;
    int *Hou;
    int *Day;
    int *Week_day;
    int *Mon;
    int *Yea;
    char day_of_the_week[7] = {'Mon','Tue','Wed','Thu','Fri','Sat','Sun'};
    
    char *Sec2;
    char *Min2;
    char *Hou2;
    char *Day2;
    char *Week_day2;
    char *Mon2;
    char *Yea2;
    while (1) {
        //LCD_clear();
        get(*Sec,*Min,*Hou,*Day,*Week_day,*Mon,*Yea);
        ADC2String(*Sec2, Sec, 2);
        ADC2String(*Min2, Min, 2);
        ADC2String(*Hou2, Hou, 2);
        ADC2String(*Day2, Sec, 2);
        ADC2String(*Mon2, Mon, 2);
        ADC2String(*Yea2, Yea, 4);
        char *day_name = day_of_the_week[*Week_day];
        char *lst[8] = {day_name,Day,Mon,Yea,Hou,Min,Sec,"123"};
        LCD_sendstring(lst);
        __delay_ms(200);
    }
}
