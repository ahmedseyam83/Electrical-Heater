#ifndef ADC_H_
#define ADC_H_

#include "StdTypes.h"
#include "MemMap.h"
#include "Utils.h"

typedef enum{
	VREF_AREF=0,
	VREF_VCC,
	VREF_V256
	}ADC_Vref_type;
	
typedef enum{
	ADC_SCALAR_2=1,
	ADC_SCALAR_4,
	ADC_SCALAR_8,
	ADC_SCALAR_16,
	ADC_SCALAR_32,
	ADC_SCALAR_64,
	ADC_SCALAR_128
	}ADC_scalar_type;
	
	typedef enum{
		CH_0=0,
		CH_1,
		CH_2,
		CH_3,
		CH_4,
		CH_5,
		CH_6,
		CH_7
	}ADC_CH_type;
	
	
	
	
void ADC_Init(ADC_Vref_type Vref,ADC_scalar_type scaler);
u16 ADC_Read(ADC_CH_type ch);


#endif /* ADC_H_ */