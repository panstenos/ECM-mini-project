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
unsigned int sunset_list[] = {0,16,17,18,20,20,21,21,20,19,18,16,16}; // sunset time of each month
unsigned int sunrise_list[] = {0,8,7,6,7,5,5,5,5,6,7,6,8}; // sunrise time of each month

char flag = 0;

void set_light(unsigned int curr_hour,unsigned int curr_day,unsigned int curr_month, unsigned int LDR_val,unsigned int state){
    // if the hour is bt 1 and 5 am turn the lights off no matter what
    if(curr_hour >= 1 && curr_hour < 5){
        _LIGHT_OUTPUT = 0;            
        flag = 1; // (the no matter what bit)
    }
    if(state == 0){ // this will only run if the LDR is working
        //int record_index = (curr_month - 11)*31 + curr_day-1; //calibrate in December
        if(LDR_val < 10){ // if the LDR value is a night value (below 10)
            if(flag == 0){ // this will only run if its not bt 1 and 5 am
                _LIGHT_OUTPUT = 1; // turn on the street lights
            }  
        }else{
            if(flag == 0){ // this will only run if its not bt 1 and 5 am
                _LIGHT_OUTPUT = 0; // turn street lights off
            }
        }
    }else{
        _ERROR_OUTPUT = 1; // in the case that the LDR is damaged
        if((curr_hour >= sunrise_list[curr_month+1] && curr_hour < sunset_list[curr_month+1])){
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
    flag = 0; // reset the flag

}


void reset_ERROR_OUTPUT(void){ //function for resetting the error LED
    if (!PORTFbits.RF2){ // when button 'RF2' is pressed
        _ERROR_OUTPUT = 0; // set the state of the 'D7' LED (RD7) to 0
    }
    
}
