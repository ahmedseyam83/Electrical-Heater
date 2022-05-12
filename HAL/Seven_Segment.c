#define F_CPU 8000000UL
#include "Seven_Segment.h"
#include "DIO_Interface.h"
#include <util/delay.h>



#if (SEG_TYPE==DIF_PORT)
	extern void SEGMENT_DISPLAY(u8 x)
	{
		DIO_WritePort(SEG_PORT1 ,segment_read[x/10]);
		DIO_WritePort(SEG_PORT2 ,segment_read[x%10]);
	}


#elif (SEG_TYPE==SAME_PORT)
	extern void SEGMENT_DISPLAY(u8 x)
	{
		DIO_WritePin(SEG_EN2,HIGH);
		DIO_WritePin(SEG_EN1,LOW);
		DIO_WritePort(SEG_PORT1,segment_read[x/10]);
		_delay_ms(1);
		DIO_WritePin(SEG_EN1,HIGH);
		DIO_WritePin(SEG_EN2,LOW);
		DIO_WritePort(SEG_PORT1,segment_read[x%10]);
		_delay_ms(1);
	}
 
	
   
     
#elif (SEG_TYPE==DEC_PORT)
	extern void SEGMENT_DISPLAY(u8 x)
   {
	  DIO_WritePort(SEG_PORT1,x); 
   }
   
   
#endif
 
   extern void Segment_OFF(void)
   {
	   DIO_WritePin(SEG_EN2,HIGH);
	   DIO_WritePin(SEG_EN1,LOW);
	   DIO_WritePort(SEG_PORT1,0x00);
	   _delay_ms(1);
	   DIO_WritePin(SEG_EN1,HIGH);
	   DIO_WritePin(SEG_EN2,LOW);
	   DIO_WritePort(SEG_PORT1,0x00);
	   _delay_ms(1);
   }

   extern void Segment_ON(void)
   {
	   DIO_WritePin(SEG_EN2,HIGH);
	   DIO_WritePin(SEG_EN1,LOW);
	   DIO_WritePort(SEG_PORT1,segment_read[0]);
	   _delay_ms(1);
	   DIO_WritePin(SEG_EN1,HIGH);
	   DIO_WritePin(SEG_EN2,LOW);
	   DIO_WritePort(SEG_PORT1,segment_read[0]);
	   _delay_ms(1);
   }



extern const u8 segment_read[10] = {0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f}; //Common Cathode .... For common Anode but ( ~ ) before Segment_read call