#ifndef SENSORS_H_
#define SENSORS_H_



#include "ADC.h"
#include "DIO_Interface.h"
#include <util/delay.h>

#define   POT_CH       CH_0
#define   LM35_CH      CH_1
#define   MPX4115_CH   CH_2
#define   DHT11_CH     CH_3
#define   THERM_CH     CH_4

 
u16 POT_VoltRead(void);
u8 Temp_Read(void);
u16 Press_Read(void);
u8 DHT_Read(u8 *Read);
f32 Thermistor_Read(void);



#endif /* SENSORS_H_ */