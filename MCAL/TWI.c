#include "TWI.h"

void TWI_Init(TWI_Prescaler prescaler,GENERALCALL_Status General_call,u8 address)
{
	TWBR= 72;
	
	switch (General_call)
	{
		case DISABLE:
		TWAR |= (address<<1)|0;
		break;
		case ENABLE:
		TWAR |= (address<<1)|1;
		break;
	}
	TWCR = (1<<TWEA) | (1<<TWEN);  //TWEA :TWI Enable Acknowledgment bit , TWEN: TW Communication enable 0x44;
	TWSR &= prescaler;
	
}

/****************************** MASTER ***************************/

u8 TWI_Start(void)
{
	u8 status;
	//Start Condition
	TWCR= (1<<TWINT) | (1<<TWEN) | (1<<TWSTA);
	
	//Wait the flag
	while(!READ_BIT(TWCR,TWINT));
	
	//Check flag
	status = TWI_GetStatus();
	if (status != TWI_START)
	return 0;
	
}

u8 TWI_Rep_Start(void)
{
	u8 status;
	//Start Condition
	TWCR= (1<<TWINT) | (1<<TWEN) | (1<<TWSTA);
	
	//Wait the flag
	while(!READ_BIT(TWCR,TWINT));
	
	//Check flag
	status = TWI_GetStatus();
	if (status != TWI_REP_START)
	return 0;
}


void TWI_Stop(void)
{
	TWCR= (1<<TWINT) | (1<<TWEN) | (1<<TWSTO);
}


u8 TWI_WriteData(u8 data)
{
	u8 status;
	TWDR=data;
	TWCR= (1<<TWINT) | (1<<TWEN);
	while(!READ_BIT(TWCR,TWINT));
	
	status= TWI_GetStatus();
	if(status == TWI_MT_DATA_ACK )
	return 1;
	if(status == TWI_MT_DATA_NOT_ACK)
	return 2;
	else 
	return 3;
}

u8 TWI_WriteAddress(u8 address,RW_type RW)
{
	u8 status;
	switch (RW)
	{
		case WRITE:
		TWDR = ((address<<1)|W);
		break;
		case READ:
		TWDR = ((address<<1)|R);
		break;
	}
	
	TWCR= (1<<TWINT) | (1<<TWEN);
	while(!READ_BIT(TWCR,TWINT));
	
	status= TWI_GetStatus();
	switch (RW)
	{
		case WRITE:
	    if (status == TWI_MT_SLA_ACK)
	    return 1;
		else if(status == TWI_MT_SLA_NOT_ACK)
		return 2;
		else
		return 3;
		break;
		case READ:
		if (status == TWI_MR_SLA_ACK)
		return 1;
		else if (status == TWI_MR_SLA_NOT_ACK)
		return 2;
		else 
		return 3;
		break;
	}
}
u8 TWI_ReadAck(void)
{
	TWCR= (1<<TWINT) | (1<<TWEN) | (1<<TWEA);
	while(!READ_BIT(TWCR,TWINT));
	return TWDR;
}
u8 TWI_ReadNoAck(void)
{
	TWCR= (1<<TWINT) | (1<<TWEN);
	while(!READ_BIT(TWCR,TWINT));
	return TWDR;
}
u8 TWI_GetStatus(void)
{
	u8 status;
	status= TWSR & 0xF8;
	return status;
}

/****************************** SLAVE ***************************/
void TWI_SlaveInit(u8 address)
{
	TWBR=72;
	TWAR= address;
	TWCR = (1<<TWEN) | (1<<TWEN) | (1<<TWEA);
}

u8 TWI_SlaveListen(void)
{
	u8 status=0;
	while (1)
	{
	while(!READ_BIT(TWCR,TWINT));
	status=TWI_GetStatus();
	if(status ==TW_SR_SLA_ACK  || status ==TW_SR_ARB_LOST_SLA_ACK)
	return 0;
	else if(status == TW_ST_SLA_ACK  || status ==TW_ST_ARB_LOST_SLA_ACK)
	return 1;
	else if(status == TW_SR_GCALL_ACK  || status ==TW_SR_ARB_LOST_GCALL_ACK)
	return 2;
	}
}

u8 TWI_SlaveTransmit(u8 data)
{
	
	u8 status;
	TWDR=data;
	TWCR= (1<<TWINT) | (1<<TWEN);
	while(!READ_BIT(TWCR,TWINT));
	
	status= TWI_GetStatus();
	if(status==TW_SR_STOP)		
	{
		TWCR|=(1<<TWINT);			/* Clear interrupt flag & return -1 */
		return -1;
	}
	if(status==TW_ST_DATA_ACK)		
	return 0;		             	/* If yes then return 0 */
	if(status==TW_ST_DATA_NACK)		
	{
		TWCR|=(1<<TWINT);       	/* Clear interrupt flag & return -2 */
		return -2;
	}
	if(status==TW_ST_LAST_DATA)		
	return -3;			          /* If yes then return -3 */
	else			
	return -4;
}

u8 TWI_SlaveReceive(void)
{
	u8 status;
	TWCR=(1<<TWEN)|(1<<TWEA)|(1<<TWINT);
	while(!READ_BIT(TWCR,TWINT));
	
	status=TWI_GetStatus();
	if(status==TW_SR_DATA_ACK||status==TW_SR_GCALL_DATA_ACK)
	return TWDR;
	else if(status == TW_SR_DATA_ACK || status == TW_SR_DATA_NACK )
	return TWDR;
	else if(status == TW_SR_GCALL_DATA_ACK || status == TW_SR_GCALL_DATA_NACK)
	return TWDR;
	else if (status==TW_SR_STOP)
	{
		TWCR|=(1<<TWINT);			/* Clear interrupt flag & return -1 */
		return -1;
	}
}