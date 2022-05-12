#ifndef TWI_SERVICES_H_
#define TWI_SERVICES_H_

#include "TWI.h"

	
typedef enum{
	NEW_SLAVE=0,
	FIRST_SLAVE
	}START_Status;

void TWI_Send(u8 address,u8 data);
void TWI_SendString(u8 address,u8 *str);
void TWI_Send_MM(u8 address,u8 data,START_Status status_start);  //if there are Multi Masters to Master the bus you can choose Start status: New slave or same slave   
void TWI_SendString_MM(u8 new_address,u8 *str,START_Status status_start);




#endif /* TWI_SERVICES_H_ */