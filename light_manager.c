#include <xc.h>
#include "light_manager.h"
#include "timers.h"

void Light_init(){
    TRISHbits.TRISH3 = 0;
    TRISDbits.TRISD7 = 0;
}

int sunrise_records[62];
int sunset_records[62];

unsigned int sunset_list[] = {16,17,18,20,20,21,21,20,19,18,16,16};
unsigned int sunrise_list[] = {8,7,6,7,6,4,4,5,6,7,6,8};

char flag = 0;

void set_light(unsigned int curr_hour,unsigned int curr_day,unsigned int curr_month, unsigned int luminosity,unsigned int state){
    if(curr_hour >= 1 && curr_hour < 5){
        _LIGHT_OUTPUT = 0;            
        flag = 1;
    }
    if(state == 0){
        unsigned int record_index = (curr_month - 6)*31 + curr_day-1;

        if(luminosity < 10){
            if(flag == 0){
                _LIGHT_OUTPUT = 1;
            }
            if(sunset_records[record_index] == -1){
                sunset_records[record_index] = curr_hour;
            }

        }else{
            if(flag == 0){
                _LIGHT_OUTPUT = 0;
            }
            
            if(sunrise_records[record_index] == -1){
                sunrise_records[record_index] = curr_hour;
            }
        }
    }else{
        _ERROR_OUTPUT = 1;
        if((curr_hour >= sunrise_list[curr_month] && curr_hour <= sunset_list[curr_month])){
            if(flag == 0){
            _LIGHT_OUTPUT = 0;
            }
        }else{
            if(flag == 0){
                _LIGHT_OUTPUT = 1;
            }
        }
    }
    
    
    if(curr_hour == 0 && curr_day == 01 && curr_month == 06){
        for(unsigned int i = 0;i < 62;i++){
            sunrise_records[i] = -1;
            sunset_records[i] = -1;
        }
    }else if(curr_hour == 1 && curr_day == 31 && curr_month == 07){
        int midnight_approx = 0;
        for(unsigned int i = 0; i < 61; i++){
            
            midnight_approx += sunrise_records[i+1] - sunset_records[i]; 
            if(sunrise_records[i+1] == -1 || sunset_records[i] == -1){
                return;
            }
        }
        
        midnight_approx = midnight_approx/61;
        sunset_records[0] = -1;
        increment_hours(midnight_approx);
    }
    
    flag = 0;

}

