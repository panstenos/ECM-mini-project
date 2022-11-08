#include <xc.h>
#include "timers.h"

/************************************
 * Function to set up timer 0
************************************/

int seconds = 0; 
int minutes = 0;
int hours = 0;
int day = 1;
int week_day = 2;
int month = 0;
int year = 2020;
int month_days[12] = {31,28,31,30,31,31,30,31,30,31,30,31};
void Timer0_init(void)
{
    T0CON1bits.T0CS=0b010; // Fosc/4
    T0CON1bits.T0ASYNC=1; // see datasheet errata - needed to ensure correct operation when Fosc/4 used as clock source
    T0CON1bits.T0CKPS=0b1000; // 1:256 -> required: 1:244.14
    T0CON0bits.T016BIT=1;	//8bit mode	
    
    // initialise the time registers to 3035 for the LED to toggle every one second
    TMR0H=0b00001011;            
    TMR0L=0b11011011;
    T0CON0bits.T0EN=1;	//start the timer
}

/************************************
 * Function to return the full 16bit timer value
 * Note TMR0L and TMR0H must be read in the correct order, or TMR0H will not contain the correct value
************************************/
unsigned int get16bitTMR0val(void)
{
	return TMR0L | (TMR0H << 8); //use bitwise operator to combine the H and L bits
}

void increment_seconds(void){ //increment time in seconds
    
    seconds ++ ; // increment by the second
    if (seconds == 60){ // if you reach 60 sec
        seconds = 0; // reset seconds to 0
        minutes ++ ; // increse minutes by 1 
    }
    if (minutes == 60){ 
        minutes = 0; //reset minutes to 0
        hours ++ ; // increase hours by 1
    }
    if (hours == 24){
        hours = 0; //reset hours to 0
        day ++ ; // increase day count by 1
        week_day ++; // increase day of week by 1
    }
    if (week_day == 7){ // if the day is Sunday
        week_day = 0; //reset count to Monday
    }
    if (month == 1 && year%4 == 0){ // check for leap year
        if (week_day == 30) // check if its after the 29th of February
        {
            week_day = 1; // reset the days
            month += 1; // add a month
        }
    }else{
        if (day == month_days[month]+1) //else just check for the days
        {
            day = 1;
            month += 1;
        }
    }
    if (month == 12) // when the month reaches 12
    {
        month = 0;
        year += 1;   
    }
    
}

void get(int *Sec, int *Min, int *Hou, int *Day, int *Week_day, int *Mon, int *Yea)
{
    *Sec = seconds;
    *Min = minutes;
    *Hou = hours;
    *Day = day;
    *Week_day = week_day;
    *Mon = month;
    *Yea = year;
}

/*
unsigned int check_for_hour_shift(void){
    if(day_of_the_week != 7){
        return 0;
    }
    if(month == 3 && day + 7 <= 31){
        return 1;
    }
    if(month == 10 && day + 7 <= 31){
        return -1;
    }
}
*/
