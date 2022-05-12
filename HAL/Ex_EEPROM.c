#include "Ex_EEPROM.h"

void ExEEPROM_Write(u8 address,u8 data)
{
	TWI_Start();
	TWI_WriteAddress(EEPROM_ADDRESS,WRITE);
	TWI_WriteData(address);
	TWI_WriteData(data);
	TWI_Stop();
}

u8 ExEEPROM_Read(u8 address)
{
	u8 tempreture;
	TWI_Start();
	TWI_WriteAddress(EEPROM_ADDRESS,WRITE);
	TWI_WriteData(address);
	TWI_Rep_Start();
	TWI_WriteAddress(EEPROM_ADDRESS,READ);
	tempreture= TWI_ReadNoAck();
	TWI_Stop();
	return tempreture;
}
