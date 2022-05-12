#ifndef POWER_MANAGEMENT_H_
#define POWER_MANAGEMENT_H_

#include "StdTypes.h"
#include "MemMap.h"
#include "Utils.h"


typedef enum{
	IDLE_MODE =0, //ALLOW SPI, USART, Analog Comparator, ADC, Two-wire SerialInterface, Timer/Counters, Watchdog, and the interrupt system to continue operating
	ADC_NR_MODE,  //allowing the ADC, the External Interrupts, the Two-wire Serial Interface address watch, Timer/Counter2 and the Watchdog to continue operating (if enabled)
	PWR_DOWN_MODE, //External Oscillator is stopped, while the External interrupts, the Two-wire Serial Interface address watch, and the Watchdog continue operating (if enabled).
	PWR_SAVE_MODE,
	RESERVED_MODE,
	STANDBY_MODE,
	EXT_STANDBY_MODE
	}SLEEP_MODES;


void CPU_Sleep(SLEEP_MODES mode);
void Set_SleepMode(SLEEP_MODES mode);
void CPU_SleepEnable(void);
void CPU_SleepDisable(void);






#endif /* POWER_MANAGEMENT_H_ */