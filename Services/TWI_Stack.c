#include "TWI_Stack.h"

static u8 TWI_stack[STACK_SIZE] = {0};
static u8 sp=0;

TWIStackstatus_type TWI_Push(u8 data)
{
	if (sp==STACK_SIZE)
	{
		return TWI_STACKFULL;
	}
	TWI_stack[sp]=data;
	sp++;
	return TWI_DONE;
}

TWIStackstatus_type TWI_Pop(u8 *pdata)
{
	if(sp==0)
	{
		return TWI_STACKEMPTY;
	}
	sp--;
	*pdata=TWI_stack[sp];
	return TWI_DONE;
}