#include "TWI_Services.h"

void TWI_Send(u8 address,u8 data)
{
	u8 status;
	TWI_Start();
	TWI_WriteAddress(address,WRITE);
	TWI_WriteData(data);
	
}


void TWI_SendString(u8 address,u8 *str)
{
	u8 status;
	TWI_Start();
	TWI_WriteAddress(address,WRITE);
	for (u8 i=0;str[i];i++)
	{
		TWI_WriteData(str[i]);
	}
	
}

void TWI_Send_MM(u8 address,u8 data,START_Status status_start)
{
	if (status_start==FIRST_SLAVE)
	{
		TWI_Start();

	}
	else if (status_start==NEW_SLAVE)
	{
		TWI_Rep_Start();
	}
		
	TWI_WriteAddress(address,WRITE);
	
	TWI_WriteData(data);
	
}

void TWI_SendString_MM(u8 new_address,u8 *str,START_Status status_start)
{
	
	if (status_start==FIRST_SLAVE)
	{
		TWI_Start();

	}
	else if (status_start==NEW_SLAVE)
	{
		TWI_Rep_Start();
	}
	
	TWI_WriteAddress(new_address,WRITE);
	
	for (u8 i=0;str[i];i++)
	{
		TWI_WriteData(str[i]);
	}	
	
}


