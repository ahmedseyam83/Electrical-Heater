#include "WDT.h"

void WDT_Set(TimeOut_type time)
{
	u8 wdt_value=0x08; //WDE Set & WDTOE Cleared 0x0b00001000
	wdt_value|=time;
	WDTCR|=(1<<WDTOE)|(1<<WDE);
	WDTCR=wdt_value;
}


void WDT_Stop(void)
{
	WDTCR=(1<<WDTOE)|(1<<WDE);
	WDTCR=0;
}