#ifndef _timers_H
#define _timers_H

#include <xc.h>

#define _XTAL_FREQ 64000000

void Timer0_init(void);
void get(int *Sec, int *Min, int *Hou, int *Day, int *Week_day, int *Mon, int *Yea);
unsigned int get16bitTMR0val(void);
void increment_seconds(void);
unsigned int check_for_hour_shift(void);
#endif
