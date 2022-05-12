#include "ADC.h"


static u8 ADC_Flag=0;

void ADC_Init(ADC_Vref_type Vref,ADC_scalar_type scaler)
{
	switch(Vref)
	{
		case VREF_AREF:
		CLEAR_BIT(ADMUX,REFS0);
		CLEAR_BIT(ADMUX,REFS1);
		break;
		case VREF_VCC:
		SET_BIT(ADMUX,REFS0);
		CLEAR_BIT(ADMUX,REFS1);
		break;
		case VREF_V256:
		SET_BIT(ADMUX,REFS0);
		SET_BIT(ADMUX,REFS1);
	    break;
	}
	//Scalar Selection
	scaler=scaler&0x07;
	ADCSRA=ADCSRA&0xF8;
	ADCSRA=ADCSRA|scaler;
	
	//Read Adjust Right 
	CLEAR_BIT(ADCSRA,ADLAR);
	
	//Enable
	SET_BIT(ADCSRA,ADEN);
	
}

u16 ADC_Read(ADC_CH_type ch)
{
	//select ch
	ADMUX=ADMUX&0xE0;
	ADMUX=ADMUX|ch;
	//start conversion
	SET_BIT(ADCSRA,ADSC);
	//POLLING
	while(READ_BIT(ADCSRA,ADSC)); //wait till conversion time finished
	
	return ADC;
}

void ADC_StartConversion(ADC_CH_type ch)
{
	if(ADC_Flag==0)
	{
	//select ch
	ADMUX=ADMUX&0xE0;
	ADMUX=ADMUX|ch;
	//start conversion
	SET_BIT(ADCSRA,ADSC);
	}
}

u16 ADC_GetRead(void)
{
	while(READ_BIT(ADCSRA,ADSC)); 
	
	return ADC;
}

u8 ADC_GetReadNoBlock(u16* Pdata)
{
	if (READ_BIT(ADCSRA,ADSC)==0)
	{
		*Pdata=ADC;
		ADC_Flag=1;
		return 1;
	}
	else
	return 0;
}