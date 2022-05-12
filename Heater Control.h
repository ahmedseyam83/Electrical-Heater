#ifndef HEATER CONTROL_H_
#define HEATER CONTROL_H_


#include "TWI_Services.h"
#include "Seven_Segment.h"
#include "Sensors.h"
#include "Power_Management.h"
#include "OS.h"
#include "EXInterrupt.h"
#include "Ex_EEPROM.h"
#include <stdio.h>

#define MAX_TEMP  75
#define MIN_TEMP  35


#define UP_BUTTON    PIND3
#define DOWN_BUTTON  PIND4
#define ONOFF_BUTTON PIND2
#define HEATING_LED  PIND5
#define STR_ADD  0x06

typedef enum{
	DOWN=0,
	UP
	}TEMPSET_status;

typedef enum{
	OFF=0,
	ON
	}HEATER_status;
	
void NUM_DISPLAY(void);
void Heater_ON(void);
void Heater_OFF(void);
void Temp_Setting(void);
void Temp_Sense(void);
void Heater_Init(void);
void Heater_State(void);
void Button_Check(void);


#endif /* HEATER CONTROL_H_ */