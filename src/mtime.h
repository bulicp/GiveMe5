#ifndef MTIME_H
#define MTIME_H

#define CLINT_BASE                	0x02000000
#define CLINT_MTIME               	0x0200bff8
#define CLINT_MTIME_CMP         	0x02004000

//volatile unsigned int *pMTime 	= (unsigned int *)CLINT_MTIME;
//volatile unsigned int *pMTimeCmp = (unsigned int *)CLINT_MTIME_CMP;

#define MTIME_ADDRESS ((unsigned int *)CLINT_MTIME)
#define MTIMECMP_ADDRESS ((unsigned int *)CLINT_MTIME_CMP)


__attribute__ ((interrupt ("machine"))) void mtime__handler(void) ;

void mtime_delay(unsigned int miliseconds);

#endif
