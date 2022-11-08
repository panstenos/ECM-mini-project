#include <xc.h>
#include "timers.h"

/************************************
 * Function to set up timer 0
************************************/

unsigned int day_of_the_week = 1;
unsigned int *seconds = 1;
unsigned int *hours = 1;
unsigned int *minutes = 1;
unsigned int *day = 1;
unsigned int *month = 1;
unsigned int *year = 2020;

unsigned char day_names[] = {"MON","TUE","WED","THU","FRI","SAT","SUN"};


unsigned short test_mode = 0;

void Timer0_init(unsigned short init_test_mode,unsigned long current_minute,unsigned long current_hour, unsigned int current_day,unsigned int current_day_of_the_week,unsigned int current_month, unsigned int current_year)
{
    test_mode = init_test_mode; //Set the test_mode value
    minutes = current_minute;
    hours = current_hour;
    day = current_day;
    day_of_the_week = current_day_of_the_week;
    month = current_month;
    year = current_year;

    T0CON1bits.T0CS=0b010; // Fosc/4
    T0CON1bits.T0ASYNC=1; // see datasheet errata - needed to ensure correct operation when Fosc/4 used as clock source
    
    T0CON0bits.T016BIT=1;	//16bit mode	
    // it's a good idea to initialise the timer registers so we know we are at 0
    if(test_mode == 0){
        
        T0CON1bits.T0CKPS=8; // 1:16000000 Set the overflow every second

        TMR0H = 0b1011;
        TMR0L = 0b11011011;
    }else{
        T0CON1bits.T0CKPS=0; // Trigger the overflow every 1/15s (precisely 1/14.7456 s)

        TMR0H = 0;
        TMR0L = 0;
    }
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
}

unsigned int get_seconds(){
    //Get the current time in seconds
    return seconds;
}

unsigned int get_minutes(){
    return minutes;
}

unsigned int get_hours(){
    return hours;
}

unsigned int get_day(){
    return day;
}
unsigned int get_month(){
    return month;
}

unsigned int * get_time(){
    unsigned int  r[7] = {seconds, minutes, hours, day, day_of_the_week,month,year};
    return r;
}

void increment_seconds(unsigned int increment){ //increment time in seconds
    if(test_mode == 1){
            increment *= 15;
        }
    while(increment > 0){
        seconds += 1;
        if(seconds == 60){ //Reset time counter after 1 day
            seconds = 0;
            increment_minutes(1);
        }
    increment -= 1;
    }
}

void increment_minutes(unsigned int increment){
    while(increment > 0){
        minutes += 1;
        if(minutes == 60){
            minutes = 0;
            increment_hours(1);
        }
        increment -= 1;
    }
}

void increment_hours(unsigned int increment){
    while(increment > 0){
        hours += 1;
        if(hours == 24){
            hours = 0;
            increment_day(1);
        }
        increment -= 1;
    }
}

void increment_day(unsigned int increment){ //Increment the current day
    while(increment > 0){
    
        unsigned int day_in_month[] = {31,28,31,30,31,30,31,31,30,31,30,31};
        unsigned int curr_day_in_month = day_in_month[month - 1];
        if(month == 2 && (year - 2020)%4 == 0){
            curr_day_in_month = 29;
        }

        day += 1;
        day_of_the_week += 1;
        
        if(day_of_the_week == 8){
            day_of_the_week = 1;
        }
        
        if(day > curr_day_in_month){
            increment_month(1);
            day = 1;
        }
               
        increment -= 1;
    } 
}

int check_for_hour_shift(){
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


void increment_month(unsigned int increment){ //Increment the current month
    while(increment > 0){
    
        month += 1;
        if(month > 12){
            month = 1;
            year += 1;
        }
        increment -= 1;
    
    }
}


