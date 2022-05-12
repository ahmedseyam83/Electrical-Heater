#ifndef TWI_H_
#define TWI_H_


#include "MemMap.h"
#include "StdTypes.h"
#include "Utils.h"
#include "Config.h"


#define W  0
#define R  1
#define TWI_MT_ARB_LOST		     0x38
#define TWI_MR_ARB_LOST			 0x38
#define TWI_START				 0x08
#define TWI_REP_START			 0x10
#define TWI_MT_SLA_ACK			 0x18
#define TWI_MT_DATA_ACK			 0x28
#define TWI_MR_DATA_NOT_ACK      0x58
#define TWI_MR_SLA_NOT_ACK       0x48
#define TWI_MT_SLA_NOT_ACK       0x20
#define TWI_MT_DATA_NOT_ACK      0x30
#define TWI_MR_DATA_ACK          0x50
#define TWI_MR_SLA_ACK           0x40
#define TW_ST_SLA_ACK            0xA8
#define TW_ST_ARB_LOST_SLA_ACK   0xB0
#define TW_ST_DATA_ACK           0xB8
#define TW_ST_DATA_NACK          0xC0
#define TW_ST_LAST_DATA          0xC8
#define TW_SR_SLA_ACK            0x60
#define TW_SR_ARB_LOST_SLA_ACK   0x68
#define TW_SR_GCALL_ACK          0x70
#define TW_SR_ARB_LOST_GCALL_ACK 0x78
#define TW_SR_DATA_ACK           0x80
#define	TW_SR_DATA_NACK          0x88
#define	TW_SR_GCALL_DATA_ACK     0x90
#define TW_SR_GCALL_DATA_NACK    0x98
#define TW_SR_STOP               0xA0
#define	TW_NO_INFO               0xF8
#define	TW_BUS_ERROR             0x00


typedef enum{
	PRESCALER_1=0,
	PRESCALER_4,
	PRESCALER_16,
	PRESCALER_64
}TWI_Prescaler;

typedef enum{
	READ=0,
	WRITE
	}RW_type;

typedef enum{
	DISABLE=0,
	ENABLE
	}GENERALCALL_Status;


void TWI_Init(TWI_Prescaler prescaler,GENERALCALL_Status General_call,u8 address);
u8 TWI_Start(void);
u8 TWI_Rep_Start(void);
void TWI_Stop(void);
u8 TWI_WriteData(u8 data);
u8 TWI_WriteAddress(u8 address,RW_type RW);
u8 TWI_ReadAck(void);
u8 TWI_ReadNoAck(void);
u8 TWI_GetStatus(void);
void TWI_SlaveInit(u8 address);
u8 TWI_SlaveListen(void);
u8 TWI_SlaveTransmit(u8 data);
u8 TWI_SlaveReceive(void);





#endif /* TWI_H_ */