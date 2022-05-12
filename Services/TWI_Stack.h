#ifndef TWI_STACK_H_
#define TWI_STACK_H_

#include "TWI.h"

#define STACK_SIZE 20
typedef enum{
	TWI_STACKFULL=0,
	TWI_STACKEMPTY,
	TWI_DONE
}TWIStackstatus_type;


TWIStackstatus_type TWI_Push(u8 data);
TWIStackstatus_type TWI_Pop(u8 *pdata);




#endif /* TWI_STACK_H_ */