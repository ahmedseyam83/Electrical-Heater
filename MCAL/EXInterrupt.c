
#include "EXInterrupt.h"

static void (*Pf_EXINT0)(void)=NULLPTR;
static void (*Pf_EXINT1)(void)=NULLPTR;
static void (*Pf_EXINT2)(void)=NULLPTR;

void EXI_Enable(ExInterruptSource_type source)
{
	
	switch(source)
	{
		case EX_INT0:
		SET_BIT(GICR,INT0);
		break;
		case EX_INT1:
		SET_BIT(GICR,INT1);
		break;
		case EX_INT2:
		SET_BIT(GICR,INT2);
		break;
	}
	
	
	
}
void EXI_Disable(ExInterruptSource_type source)
{
	switch(source)
	{
		case EX_INT0:
		CLEAR_BIT(GICR,INT0);
		break;
		case EX_INT1:
		CLEAR_BIT(GICR,INT1);
		break;
		case EX_INT2:
		CLEAR_BIT(GICR,INT2);
		break;
	}
}
void EXI_TriggerEdge(ExInterruptSource_type source,TriggerEdge_type edge)
{
	
	
	switch(source)
	{
		case EX_INT0:
		switch(edge)
		{
			case LOW_LEVEL:
			CLEAR_BIT(MCUCR,ISC00);
			CLEAR_BIT(MCUCR,ISC01);
			break;
			case ANY_LOGIC_CHANGE:
			SET_BIT(MCUCR,ISC00);
			CLEAR_BIT(MCUCR,ISC01);
			break;
			case FALLING_EDGE:
			CLEAR_BIT(MCUCR,ISC00);
			SET_BIT(MCUCR,ISC01);
			break;
			case RISING_EDGE:
			SET_BIT(MCUCR,ISC00);
			SET_BIT(MCUCR,ISC01);
			break;
		}
		break;
		case EX_INT1:
		switch(edge)
		{
			case LOW_LEVEL:
			CLEAR_BIT(MCUCR,ISC10);
			CLEAR_BIT(MCUCR,ISC11);
			break;
			case ANY_LOGIC_CHANGE:
			SET_BIT(MCUCR,ISC10);
			CLEAR_BIT(MCUCR,ISC11);
			break;
			case FALLING_EDGE:
			CLEAR_BIT(MCUCR,ISC10);
			SET_BIT(MCUCR,ISC11);
			break;
			case RISING_EDGE:
			SET_BIT(MCUCR,ISC10);
			SET_BIT(MCUCR,ISC11);
			break;
		}
		break;
		case EX_INT2:
		switch(edge)
		{
			
			case FALLING_EDGE:
			CLEAR_BIT(MCUCSR,ISC2);
			break;
			case RISING_EDGE:
			SET_BIT(MCUCSR,ISC2);
			break;
			default:
			CLEAR_BIT(MCUCSR,ISC2);
			break;
		}
		
		break;
	}
	
	
}


void EX_SetCallBack(ExInterruptSource_type source,void(*localpf)(void))
{
	switch(source)
	{
		case EX_INT0:
		Pf_EXINT0=localpf;
		break;
		case EX_INT1:
		Pf_EXINT1=localpf;
		break;
		case EX_INT2:
		Pf_EXINT2=localpf;
	    break;
	}
	
}
ISR(INT0_vect)
{
	if (Pf_EXINT0!=NULLPTR)
	{
		Pf_EXINT0();
	}	
}

ISR(INT1_vect)
{
	if (Pf_EXINT1!=NULLPTR)
	{
		Pf_EXINT1();
	}	
}

ISR(INT2_vect)
{
	if (Pf_EXINT2!=NULLPTR)
	{
		Pf_EXINT2();
	}
}