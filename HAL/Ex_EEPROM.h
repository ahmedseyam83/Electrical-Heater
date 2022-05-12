#ifndef EX_EEPROM_H_
#define EX_EEPROM_H_

#include "TWI_Services.h"
#include "TWI_Stack.h"

#define EEPROM_ADDRESS 0x54


void ExEEPROM_Write(u8 address,u8 data);
u8 ExEEPROM_Read(u8 address);




#endif /* EX_EEPROM_H_ */