#include "Heater Control.h"
#include <stdio.h>






int main(void)
{
	sei();
	DIO_Init();
	ADC_Init(VREF_VCC,ADC_SCALAR_64);
	TWI_Init(PRESCALER_1,DISABLE,0x02);
	
	EXI_TriggerEdge(EX_INT0,LOW_LEVEL);
	EX_SetCallBack(EX_INT0,Heater_State);
	EXI_Enable(EX_INT0);

	Schedular_Init();
	Heater_OFF();
	
	OS_TaskCreate(Temp_Sense,20,BLOCKED);
	OS_TaskCreate(Button_Check,4,BLOCKED);
	OS_TaskCreate(NUM_DISPLAY,4,BLOCKED);
	OS_TaskCreate(Schedular_Sleep,4,BLOCKED);-
	
	Schedular_Start();
   
    while (1) 
    {
		OS_TaskExecution();
    }
}



