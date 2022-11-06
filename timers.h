#ifndef _timers_H
#define _timers_H

#include <xc.h>

#define _XTAL_FREQ 64000000

void Timer0_init(unsigned short,unsigned int,unsigned int,unsigned int);
unsigned int get16bitTMR0val(void);
unsigned long get_time(void);
void set_time(unsigned long);
unsigned short test_mode;

float get_hour(void);
unsigned int get_day(void);
unsigned int get_month(void);

void increment_time(unsigned long);
void increment_day(unsigned int);
void increment_month(unsigned int);


#endif
