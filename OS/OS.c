#include "OS.h"

static TASK_struct Taskstruct[TASK_MAX_NO];
static u8 task_number=0;

volatile static u8 _100usec=0;


void Timer(void)
{
	WDT_Set(WDT_TIME);
	TCNT0=INT_TIME;
	
	_100usec++;
	if(_100usec >= 50)
	{
		_100usec=0;
		OS_TaskTimer();
	}
}

void Schedular_Init(void)
{
	Timer0_Init(TIMER0_NORMAL_MODE,TIMER0_SCALER_8,OCO_DISCONNECTED);
	TCNT0=INT_TIME;
	Timer0_OV_SetCallBack(Timer);
}

void Schedular_Start(void)
{
	Timer0_OV_InterruptEnable();
}

void Schedular_Sleep(void)
{
	CPU_Sleep(IDLE_MODE);
}



TASK_feedback OS_TaskCreate(fncptr task,u8 periodicity,TASK_state default_state)
{
	TASK_feedback feedback = NOK_UNKNOWN;
	
	if(Taskstruct==NULLPTR)
	feedback = NOK_NULL_PTR;
	else if(periodicity>TASK_MAX_TIME || periodicity<TASK_MIN_TIME)
	feedback = NOK_TIME_LIMIT;
	else if(task_number>TASK_MAX_NO)
	feedback = NOK_CNT_LIMIT;
	else
	{
		Taskstruct[task_number].function=task;
		Taskstruct[task_number].state=default_state;
		Taskstruct[task_number].t_periodicity=periodicity;
		Taskstruct[task_number].time_cnt= 1;
		task_number++;
		feedback = OK;
	}
	return feedback;
}

TASK_feedback OS_TaskDelete(u8 Task_No)
{
	if (Taskstruct[Task_No].function==0)
	return NOK_NULL_PTR;
	
	else
	{
		Taskstruct[Task_No].function=0x00;
		Taskstruct[Task_No].state=0;
		Taskstruct[Task_No].t_periodicity=0;
		Taskstruct[Task_No].time_cnt= 0;
		
		if(Task_No==task_number)
			task_number--;
		else
		{
			for (u8 i=Task_No;i<task_number;i++)
			{
			Taskstruct[i].function=Taskstruct[i+1].function;
			Taskstruct[i].state=Taskstruct[i+1].state;
			Taskstruct[i].t_periodicity=Taskstruct[i+1].t_periodicity;
			Taskstruct[i].time_cnt= Taskstruct[i+1].time_cnt;
			}
			task_number--;
		}
		return OK;
	}
}


void OS_TaskExecution(void)
{
	
	for (u8 i=0;i<task_number;i++)
	{
		if(Taskstruct[i].state== READY)
		{
			Taskstruct[i].function();
			Taskstruct[i].state = BLOCKED;
		}
	}
}

void OS_TaskTimer(void)
{
	WDT_Stop();
	for (u8 i=0;i<task_number;i++)
	{
		if (Taskstruct[i].state!= SUSPENDED)
		{
			if (Taskstruct[i].time_cnt >= Taskstruct[i].t_periodicity)
			{
				Taskstruct[i].time_cnt=1;
				Taskstruct[i].state=READY;
			}
			else
			Taskstruct[i].time_cnt++;
		}
	}
}



void OS_create_semaphore(struct os_semaphore* sPtr)
{
	sPtr->x=NULLPTR;
}


void OS_lock_semaphore(struct os_semaphore* sPtr)
{
		sPtr->x=SEM_LOCK;
}
void OS_release_semaphore(struct os_semaphore* sPtr)
{
		sPtr->x=SEM_REL;
}
SEMAPHORE_state OS_check_Semaphore(struct os_semaphore* sPtr)
{
	
	if (sPtr->x==SEM_LOCK)
		return LOCKED;
	else if (sPtr->x==SEM_REL)
		return NLOCKED;
	
}