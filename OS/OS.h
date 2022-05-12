#ifndef SCHEDULAR_H_
#define SCHEDULAR_H_

#include "StdTypes.h"
#include "Timers.h"
#include "Power_Management.h"
#include "WDT.h"

#define SEM_LOCK  2
#define SEM_REL   1



#define TASK_MAX_NO     10
#define TASK_MAX_TIME	20  //hyper period
#define TASK_MIN_TIME	4

#define INT_TIME 156

#define WDT_TIME timeout_65ms

typedef void (*fncptr) (void);

struct os_semaphore{
	u8 x;
} ;

struct os_semaphore semaphore;

typedef enum{
	LOCKED=0,
	NLOCKED
}SEMAPHORE_state;




typedef enum{
	BLOCKED=0,
	READY,
	SUSPENDED
}TASK_state;


typedef struct{
	fncptr		function;
	u8			t_periodicity;
	u8			time_cnt;
	TASK_state  state;
}TASK_struct;

typedef enum{
	OK=0,
	NOK_NULL_PTR,
	NOK_TIME_LIMIT,
	NOK_CNT_LIMIT,
	NOK_UNKNOWN
}TASK_feedback;

void Schedular_Init(void);
void Schedular_SetCallBack(void (*Local_pf)(void));
void Schedular_Start(void);
void Schedular_Sleep(void);
TASK_feedback OS_TaskCreate(fncptr task,u8 default_time_burst,TASK_state default_state);
TASK_feedback OS_TaskDelete(u8 Task_No);
void OS_TaskTimer(void);
void OS_TaskExecution(void);

void OS_create_semaphore(struct os_semaphore* sPtr);
void OS_lock_semaphore(struct os_semaphore* sPtr);
void OS_release_semaphore(struct os_semaphore* sPtr);
SEMAPHORE_state OS_check_Semaphore(struct os_semaphore* sPtr);


#endif /* SCHEDULAR_H_ */