#include "Heater Control.h"



u8 Set_temp,Set_flag;
u8 temp;
HEATER_status state;



/****************Temperature Setting****************/
void Button_Check(void)
{
	if ( (!DIO_ReadPin(UP_BUTTON)) || (!DIO_ReadPin(DOWN_BUTTON)) )
	{
		Temp_Setting();
		while((!DIO_ReadPin(UP_BUTTON)) || (!DIO_ReadPin(DOWN_BUTTON)));
	}	
}

void NUM_DISPLAY(void)
{
	u16 static c=0;
	u8 static flag=0;
	if(state == ON && Set_flag ==1)
	{
		SEGMENT_DISPLAY(Set_temp);
		if(c == 1000)
		{
			Set_flag=0;
			flag=1;
			c=0;
		}
		else
		c++;
	}
	
	else if(state == ON && Set_flag ==0)
	{
		if (flag==0)
		{
			SEGMENT_DISPLAY(Set_temp);
			if(c == 1000)
			{
				flag=1;
				c=0;
			}
			else
			c++;
		}
		else
			SEGMENT_DISPLAY(temp);	
	}

	else if (state == OFF)
	{
		flag=0;
		Segment_OFF();
	}
}

void Temp_Setting(void)
{
	u8 static tempreture=60;
	if (Set_flag ==0)
	{
		tempreture =60;
		Set_flag=1;
	}
    else if (Set_flag== 1)
	{
		if((!DIO_ReadPin(UP_BUTTON)) && tempreture <= MAX_TEMP)
		{
			tempreture += 5;
		}
		else if((!DIO_ReadPin(DOWN_BUTTON)) && tempreture >= MIN_TEMP)
		{
			tempreture -= 5;
		}
	}
	Set_temp=tempreture;
	ExEEPROM_Write(STR_ADD,Set_temp);
}


/****************Heater Setting****************/
// Heater ON/OFF

void Heater_State(void)
{

	while (!DIO_ReadPin(ONOFF_BUTTON));
	if (state == OFF)
	{
		Heater_ON();	
	}
	else if(state == ON)
	{
		Heater_OFF();
	}
}

void Heater_ON(void)
{
	state=ON;
	Set_temp = ExEEPROM_Read(STR_ADD);
}


void Heater_OFF(void)
{
	WDT_Stop(); // Runtime Error
	state=OFF;
	Set_flag=0;
	Segment_OFF();
	CPU_Sleep(PWR_DOWN_MODE);
}
/**********************************************/
// Heat/Cool Elements

void Temp_Sense(void)
{
	
	u16 static c=0;
	u16 static avg=0;
	u16 Sensor=Temp_Read();
	
	if (Sensor <15)
		Sensor=Sensor;
	else if (Sensor >= 15 && Sensor < 32)
		Sensor -= 1;
	else if(Sensor >= 32 && Sensor < 50)
		Sensor -= 2;
	else if(Sensor >= 50 && Sensor < 68)
		Sensor -= 3;
	else if(Sensor >= 68 && Sensor < 86)
		Sensor -= 4;
	else if(Sensor >= 86 && Sensor < 95)
		Sensor -= 5;
	else
		{
			DIO_WritePin(PIND7,HIGH);
			if (c==1000)
			{
				CPU_Sleep(PWR_DOWN_MODE);
				c=0;
			}
			else
			c++;
		}
	avg +=Sensor;
	
	if (c==10)
	{ 
		avg /= 10;
		
		if(avg >=10 && avg < 20)
		  avg -= 1;
		else if(avg >=20 && avg < 30)
		  avg -= 2;
		else if(avg >=30 && avg < 40)
		  avg -= 3;
		else if(avg >=40 && avg < 50)
		  avg -= 4;
		else if(avg >=50 && avg < 60)
		  avg -= 5;
		else if(avg >=60 && avg < 70)
		  avg -= 6;
		else if(avg >=70 && avg < 80)
		  avg -= 7;
		else if(avg >=80 && avg < 90)
		  avg -= 8;
		else if(avg >=90 && avg < 100)
		  avg -= 9;
	  
	  if (avg < (Set_temp-5))
	  {
		DIO_WritePin(PIND5,HIGH);
		DIO_WritePin(PIND6,LOW);
	  }
	  else if (avg >(Set_temp+5))
	  {
		DIO_WritePin(PIND5,LOW);
		DIO_WritePin(PIND6,HIGH);
	  }
	  else
	  {
		 DIO_WritePin(PIND5,LOW);
		 DIO_WritePin(PIND6,LOW);
	  }
	  c=0;
	  avg=0;
	}
	else
		c++;
		
	temp=Sensor;
	
}