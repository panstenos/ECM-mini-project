#include <xc.h>
#include "light_manager.h"
#include "timers.h"

void Light_init(){
    _LIGHT_OUTPUT = 0; // initialise street light -> H3
    TRISHbits.TRISH3 = 0; // set H3 to output
    _ERROR_OUTPUT = 0; // initialise error LED -> D7
    TRISDbits.TRISD7 = 0; // set D7 to output
    ANSELFbits.ANSELF2=0; //turn off analogue input on pin  
    TRISFbits.TRISF2 = 1; // set F2 to input
}
/*
int sunrise_records[62];
int sunset_records[62];
*/
unsigned int sunset_list[] = {0,16,17,18,20,20,21,21,20,19,18,16,16}; // sunset time of each month
unsigned int sunrise_list[] = {0,8,7,6,7,6,4,4,5,6,7,6,8}; // sunrise time of each month

char flag = 0;

void set_light(unsigned int curr_hour,unsigned int curr_day,unsigned int curr_month, unsigned int luminosity,unsigned int state){
    // if the hour is bt 1 and 5 am turn the lights off no matter what
    if(curr_hour >= 1 && curr_hour < 5){
        _LIGHT_OUTPUT = 0;            
        flag = 1; // (the no matter what bit)
    }
    if(state == 0){ // this will only run if the LDR is working
        //unsigned int record_index = (curr_month - 6)*31 + curr_day-1;
        if(luminosity < 10){ // if the LDR value is a night value (below 10)
            if(flag == 0){ // this will only run if its not bt 1 and 5 am
                _LIGHT_OUTPUT = 1; // turn on the street lights
            }
            /*
            if(sunset_records[record_index] == -1){
                sunset_records[record_index] = curr_hour;
            }
            */
        }else{
            if(flag == 0){ // this will only run if its not bt 1 and 5 am
                _LIGHT_OUTPUT = 0; // turn street lights off
            }
            /*
            if(sunrise_records[record_index] == -1){
                sunrise_records[record_index] = curr_hour;
            }
            */
        }
    }else{
        _ERROR_OUTPUT = 1; // in the case that the LDR is damaged
        if((curr_hour >= sunrise_list[curr_month+1] && curr_hour <= sunset_list[curr_month+1])){
        // if the hours of the clock is between sunrise and sunset
            if(flag == 0) // this will only run if its not bt 1 and 5 am
            {
                _LIGHT_OUTPUT = 0; // turn street lights off
            }
        }else{
            if(flag == 0) // this will only run if its not bt 1 and 5 am
            {
                _LIGHT_OUTPUT = 1; // turn street lights on
            }
        }
    }
    /*
    if(curr_hour == 0 && curr_day == 01 && curr_month == 06){ //reset all sunrise and sunset measurements for the adjustment
        for(unsigned int i = 0;i < 62;i++){
            sunrise_records[i] = -1;
            sunset_records[i] = -1;
        }
    }else if(curr_hour == 22 && curr_day == 31 && curr_month == 07){ //midnight approximation
        int midnight_approx = 0; 
        for(unsigned int i = 0; i < 61; i++){
            
            midnight_approx += sunrise_records[i+1] + sunset_records[i] - 24;
            if(sunrise_records[i+1] == -1 || sunset_records[i] == -1){ // if one measurement was kept bc of the ldr safety dont do time shift
                return;
            }
        }
        
        midnight_approx = midnight_approx/61;
        sunset_records[0] = -1;
        increment_hours(-midnight_approx); //apply time shift
    }
    */
    flag = 0; // reset the flag

}


void reset_ERROR_OUTPUT(void){ //function for resetting the error LED
    if (!PORTFbits.RF2){ // when button 'RF2' is pressed
        _ERROR_OUTPUT = 0; // set the state of the 'D7' LED (RD7) to 0
    }
    
}
