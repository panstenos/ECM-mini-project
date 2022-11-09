
#ifndef LIGHT_MANAGER_H
#define	LIGHT_MANAGER_H

#include <xc.h>

#define _LIGHT_OUTPUT LATHbits.LATH3    
#define _ERROR_OUTPUT LATDbits.LATD7

void Light_init(void);
void set_light(unsigned int,unsigned int,unsigned int,unsigned int,unsigned int);

#endif	/* LIGHT_MANAGER_H */

