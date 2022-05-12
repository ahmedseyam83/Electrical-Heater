#ifndef SEVEN_SEGMENT_H_
#define SEVEN_SEGMENT_H_



#include "StdTypes.h"
#include "DIO_Interface.h"

/****************************Configuration of 7Segmant *******************************/

/************ Set Enables Pins  ***********/
#define  SEG_EN1 PINA6
#define  SEG_EN2 PINA7

/************ Set Segmants Port By Number ***********/   //(0 (PORTA) , 1 (PORTB) , 2 (PORTC) , 3 (PORTD) ) 
#define SEG_PORT1  1
#define SEG_PORT2  0

/************* Segmant Type Configuration **********/
#define  DIF_PORT   0
#define  SAME_PORT  1
#define  DEC_PORT   2 //Using a decode like BCD_7seg decoder

/************ Set 7Segmant Type *********/
#define  SEG_TYPE  SAME_PORT

/**************************************************************************************/


extern void SEGMENT_DISPLAY(u8 x);
extern void Segment_OFF(void);
extern void Segment_ON(void);
extern const u8 segment_read[10];
#endif /* SEVEN_SEGMENT_H_ */