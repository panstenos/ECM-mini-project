#ifndef _timers_H
#define _timers_H

#include <xc.h>

#define _XTAL_FREQ 64000000

void Timer0_init(unsigned short);
unsigned int get16bitTMR0val(void);
unsigned long get_time(void);
unsigned long set_time(unsigned long);
unsigned long increment_time(unsigned long);
unsigned int get_hour(void);

#endif
