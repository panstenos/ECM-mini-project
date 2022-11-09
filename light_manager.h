
#ifndef LIGHT_MANAGER_H
#define	LIGHT_MANAGER_H

#include <xc.h>

#define _LIGHT_OUTPUT LATHbits.LATH3    

void Light_init(void);
void set_light(unsigned int,unsigned int);

#endif	/* LIGHT_MANAGER_H */

