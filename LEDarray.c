#include <xc.h>
#include "LEDarray.h"

/************************************
/ LEDarray_init
/ Function used to initialise pins to drive the LEDarray
************************************/
void LEDarray_init(void)
{
    
    	//set up TRIS registers for pins connected to LED array
	//set initial output LAT values (they may have random values when powered on)
    
    TRISGbits.TRISG0 = 0;
    TRISGbits.TRISG1 = 0;
    TRISAbits.TRISA2 = 0;
    TRISFbits.TRISF6 = 0;
    TRISAbits.TRISA4 = 0;
    TRISAbits.TRISA5 = 0;
    TRISFbits.TRISF0 = 0;
    TRISBbits.TRISB0 = 0;
    TRISBbits.TRISB1 = 0;
    
    PORTGbits.RG0 = 1;
    PORTGbits.RG1 = 1;
    PORTAbits.RA2 = 1;
    PORTFbits.RF6 = 1;
    PORTAbits.RA4 = 1;
    PORTAbits.RA5 = 1;
    PORTFbits.RF0 = 1;
    PORTBbits.RB0 = 1;
    PORTBbits.RB1 = 1;
    
    LATGbits.LATG0 = 0;
    LATGbits.LATG1 = 0;
    LATAbits.LATA2 = 0;
    LATFbits.LATF6 = 0;
    LATAbits.LATA4 = 0;
    LATAbits.LATA5 = 0;
    LATFbits.LATF0 = 0;
    LATBbits.LATB0 = 0;
    LATBbits.LATB1 = 0;
}

/************************************
/ LEDarray_disp_bin
/ Function used to display a number on the LED array in binary
************************************/
void LEDarray_disp_bin(unsigned int number)
{
	//some code to turn on/off the pins connected to the LED array
	//if statements and bit masks can be used to determine if a particular pin should be on/off
	//see Readme.md for examples
    if(number & 0b000000001){LATGbits.LATG0 = 1;}else{LATGbits.LATG0 = 0;}
    if(number & 0b000000010){LATGbits.LATG1 = 1;}else{LATGbits.LATG1 = 0;}
    if(number & 0b000000100){LATAbits.LATA2 = 1;}else{LATAbits.LATA2 = 0;}
    if(number & 0b000001000){LATFbits.LATF6 = 1;}else{LATFbits.LATF6 = 0;}
    if(number & 0b000010000){LATAbits.LATA4 = 1;}else{LATAbits.LATA4 = 0;}
    if(number & 0b000100000){LATAbits.LATA5 = 1;}else{LATAbits.LATA5 = 0;}
    if(number & 0b001000000){LATFbits.LATF0 = 1;}else{LATFbits.LATF0 = 0;}
    if(number & 0b010000000){LATBbits.LATB0 = 1;}else{LATBbits.LATB0 = 0;}
    if(number & 0b100000000){LATBbits.LATB1 = 1;}else{LATBbits.LATB1 = 0;}
    
   
}

/************************************
/ Function LEDarray_disp_dec
/ Used to display a number on the LEDs
/ where each LED is a value of 10
************************************/
void LEDarray_disp_dec(unsigned int number)
{
	unsigned int disp_val;
	
	//some code to manipulate the variable number into the correct
	//format and store in disp_val for display on the LED array
   
    disp_val = 0;
    
    unsigned int num_tens = (number - number %10)/10; // Get the value of the digit of the tens
    for(unsigned int i = 0; i < num_tens; i++){ 
        disp_val += 1 << i;
    }   
    
	LEDarray_disp_bin(disp_val); 	//display value on LED array
}


/************************************
/ LEDarray_disp_PPM
/ Function used to display a level on the LED array with peak hold
/ cur_val is the current level from the most recent sample, and max is the peak value for the last second
/ these input values need to calculated else where in your code
************************************/
void LEDarray_disp_PPM(unsigned int cur_val, unsigned int max)
{
	unsigned int disp_val = 0;
	
	// some code to format the variable cur_val and max, store in disp_val for display on the LED array
	// hint: one method is to manipulate the variables separately and then combine them using the bitwise OR operator
    unsigned int cur_tens = (cur_val - cur_val %10)/10; // Get the value of the digit of the tens
    for(unsigned int i = 0; i < cur_tens; i++){ 
        disp_val += 1 << i;
    }
    
    unsigned int max_tens = (max - max%10)/10;
    
    
    disp_val = disp_val | (1 << max_tens-1); //We add the max value to the disp_val
    
	LEDarray_disp_bin(disp_val);	//display value on LED array
}

