#include "Power_Management.h"

void Set_SleepMode(SLEEP_MODES mode)
{
	switch(mode)
	{
		case IDLE_MODE:
		CLEAR_BIT(MCUCR,SM0);
		CLEAR_BIT(MCUCR,SM1);
		CLEAR_BIT(MCUCR,SM2);
		break;
		case ADC_NR_MODE:
		SET_BIT(MCUCR,SM0);
		CLEAR_BIT(MCUCR,SM1);
		CLEAR_BIT(MCUCR,SM2);
		break;
		case PWR_DOWN_MODE:
		CLEAR_BIT(MCUCR,SM0);
		SET_BIT(MCUCR,SM1);
		CLEAR_BIT(MCUCR,SM2);
		break;
		case PWR_SAVE_MODE:
		SET_BIT(MCUCR,SM0);
		SET_BIT(MCUCR,SM1);
		CLEAR_BIT(MCUCR,SM2);
		break;
		case RESERVED_MODE:
		CLEAR_BIT(MCUCR,SM0);
		CLEAR_BIT(MCUCR,SM1);
		SET_BIT(MCUCR,SM2);
		break;
		case STANDBY_MODE:
		CLEAR_BIT(MCUCR,SM0);
		SET_BIT(MCUCR,SM1);
		SET_BIT(MCUCR,SM2);
		break;
		case EXT_STANDBY_MODE:
		SET_BIT(MCUCR,SM0);
		SET_BIT(MCUCR,SM1);
		SET_BIT(MCUCR,SM2);
		break;
	}
}

void CPU_SleepEnable(void)
{
	SET_BIT(MCUCR,SE);
}

void CPU_SleepDisable(void)
{
	CLEAR_BIT(MCUCR,SE);
}

void Sleep_CPU(void)
{
	do 
	{
		sleep();
	} while (0);
}

void CPU_Sleep(SLEEP_MODES mode)
{
	Set_SleepMode(mode);
	cli();
	CPU_SleepEnable();
	sei();
	Sleep_CPU();
	CPU_SleepDisable();
}

