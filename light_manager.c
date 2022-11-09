#include <xc.h>
#include "light_manager.h"

void Light_init(){
    TRISHbits.TRISH3 = 0;
}

void set_light(unsigned int curr_hour, unsigned int luminosity){
    if(curr_hour >= 1 && curr_hour < 5){
        _LIGHT_OUTPUT = 0;
        return;
    }
    if(luminosity < 10){
        _LIGHT_OUTPUT = 1;
    }else{
        _LIGHT_OUTPUT = 0;
    }
    
}