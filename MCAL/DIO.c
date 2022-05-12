#include "Utils.h"
#include "StdTypes.h"
#include "MemMap.h"
#include "DIO_Interface.h"


extern void DIO_InitPin(DIO_Pin_type pin,DIO_PinStatus_type status )
{
	DIO_Port_type port = pin/8;
	u8 pin_num = pin%8;
	switch (status)
	{
		case OUTPUT :
		
		switch (port) 
		{
		case PA:
		    SET_BIT(DDRA,pin_num);
			break;
		case PB :
		    SET_BIT(DDRB,pin_num);
		    break;	
		case PC :
			SET_BIT(DDRC,pin_num);
			break;			
		case PD :
			SET_BIT(DDRD,pin_num);
			break;	
		}
		break;
		
		
		case INFREE :
		
		switch(port)
		{
			
		
		case PA :
			CLEAR_BIT(DDRA,pin_num);
			CLEAR_BIT(PORTA,pin_num);
			break;
		case PB :
			CLEAR_BIT(DDRB,pin_num);
			CLEAR_BIT(PORTB,pin_num);
			break;
		case PC :
			CLEAR_BIT(DDRC,pin_num);
			CLEAR_BIT(PORTC,pin_num);
			break;
		case PD :
			CLEAR_BIT(DDRC,pin_num);
			CLEAR_BIT(PORTD,pin_num);
			break;
		}
		break;
		
		case INLLUP :
		
		switch (port) 
		{
			
		
		case PA :
			CLEAR_BIT(DDRA,pin_num);
			SET_BIT(PORTA,pin_num);
			break;
		case PB :
			CLEAR_BIT(DDRB,pin_num);
			SET_BIT(PORTB,pin_num);
			break;
		case PC :
			CLEAR_BIT(DDRC,pin_num);
			SET_BIT(PORTC,pin_num);
			break;
		case PD :
			CLEAR_BIT(DDRC,pin_num);
			SET_BIT(PORTD,pin_num);
			break;
		}
	break;
    }
}


extern void DIO_WritePin(DIO_Pin_type pin,DIO_Voltage_type volt)
{
	DIO_Port_type port = pin/8;
	u8 pin_number = pin%8;
	if (volt == HIGH)
	{
		switch(port)
		{
			case PA :
			SET_BIT(PORTA,pin_number);
			break;
			case PB :
			SET_BIT(PORTB,pin_number);
			break;
			case PC :
			SET_BIT(PORTC,pin_number);
			break;
			case PD :
			SET_BIT(PORTD,pin_number);
			break;
		}
	}
	if (volt == LOW)
	{
		switch(port)
		{
			case PA :
			CLEAR_BIT(PORTA,pin_number);
			break;
			case PB :
			CLEAR_BIT(PORTB,pin_number);
			break;
			case PC :
			CLEAR_BIT(PORTC,pin_number);
			break;
			case PD :
			CLEAR_BIT(PORTD,pin_number);
			break;
			
		}
	}
	
}


extern DIO_Voltage_type DIO_ReadPin(DIO_Pin_type pin)
{
	DIO_Port_type port = pin/8;
	u8 pin_number = pin%8;
	DIO_Voltage_type volt ;
	
	switch(port)
	{
		case PA :
		volt = READ_BIT(PINA,pin_number);
		break;
		case PB :
		volt = READ_BIT(PINB,pin_number);
		break;
		case PC :
		volt = READ_BIT(PINC,pin_number);
		break;
		case PD :
		volt = READ_BIT(PIND,pin_number);
		break;
	}
	return volt ;
}


extern void DIO_TogglePin(DIO_Pin_type pin)
{
	DIO_Port_type port = pin/8;
	u8 pin_number = pin%8;
	
	switch (port)
	{
		case PA :
		TOGGLE_BIT(PORTA,pin_number);
		break;
		case PB :
		TOGGLE_BIT(PORTB,pin_number);
		break;
		case PC :
		TOGGLE_BIT(PORTC,pin_number);
		break;
		case PD :
		TOGGLE_BIT(PORTD,pin_number);
		break;
	}
}


extern void DIO_WritePort(DIO_Port_type port ,u8 value)
{
	
	switch(port)
	{
		case PA : 
		PORTA = value;
		break;
		case PB :
		PORTB = value;
		break;
		case PC :
		PORTC = value;
		break;
		case PD :
		PORTD = value;
		break;
	}
}


extern u8 DIO_ReadPort(DIO_Port_type port)
{
	u8 value ;
	switch(port)
	{
		case PA :
		value = PORTA ;
		break;
		case PB :
		value = PORTB ;
		break;
		case PC :
		value = PORTC ;
		break;
		case PD :
		value = PORTD ;
		break;
	}
	return value;
}

extern void DIO_Init(void)
{
	DIO_Pin_type i;
	for (i=PINA0;i<TOTAL_PINS;i++)
	{
		DIO_InitPin(i,PinsStatusArray[i]);
	}
	
}