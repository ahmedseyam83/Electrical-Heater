#include "Sensors.h"



u16 POT_VoltRead(void)
{
	u16 adc = ADC_Read(POT_CH);
	u16 volt=((u32)5000*adc)/1024;
	return volt;
}

u8 Temp_Read(void)
{
	u16 adc = ADC_Read(LM35_CH);
	u16 volt=((u32)5000*adc)/1024;
	u8 temp=volt/10;
	return temp;	
} 

f32 Thermistor_Read(void)
{
	u16 adc = ADC_Read(THERM_CH);
	f32 R = ((1023*10000/adc)-10000);
	f32 thermister= log(R);
	thermister = 1/(0.001129148+(0.000234125*thermister)+(0.0000000876741*thermister));
	thermister= thermister - 273.15;
	return thermister;
}

u16 Press_Read(void)
{
	u16 adc = ADC_Read(MPX4115_CH);
	u16 volt = ((u32)1085*adc-55) + (u32) 150000;
	u16 Press = volt/1000;
	return Press ;
}

u8 DHT_Read(u8 *Read)
{
	 u16 CS=0;
	 u8 rec=0;
	 u8 port=DHT11_CH/8;
	 u8 pin=DHT11_CH%8;
	 u8 dir=0;
	/* switch(dir)
	 {
		 case 0:
		 port=PORTA;
		 dir=DDRA;
	 }*/
	// Request
	    // Set Output
	DIO_InitPin(DHT11_CH,OUTPUT);
	    // Start Request
	DIO_WritePin(DHT11_CH,LOW);
	_delay_ms(20);
	DIO_WritePin(DHT11_CH,HIGH);
	
	// Response
	    // Set In Free
	DIO_InitPin(DHT11_CH,INFREE);
	    // Start Response
	while(DIO_ReadPin(DHT11_CH));
	while(!(DIO_ReadPin(DHT11_CH)));	
	while(DIO_ReadPin(DHT11_CH));
	
	// Read Data
	
	for (u8 i=0;i<5;i++)
	{
		for (u8 j=0;j<8;j++)
		{
			while(!DIO_ReadPin(DHT11_CH));
			_delay_us(30);
			
			if (DIO_ReadPin(DHT11_CH))
				rec |= (1<<j);
			else
				rec &= ~(1<<j);
				
			while(DIO_ReadPin(DHT11_CH));
			
		}
		Read[i]=rec;
	}
	
	CS= Read[0]+Read[1]+Read[2]+Read[3];
	
	if (CS==Read[4])
	return 1;
	else
	return 0;
	
	DIO_InitPin(DHT11_CH,PinsStatusArray[DHT11_CH]);
}

