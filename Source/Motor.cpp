#include "Motor.h"
#include "usart.h"
#include "cmsis_os.h"
#include "stm32f10x.h"

#include "Utilities.h"
#include "HardwareInit.h"
#include "Delay.h"
#include "Linker.h"

extern SerialUSART2 usart;
//**************************************************
Motor::Motor(int Motornum)
{
			Motor_Data=Config_motor[Motornum];
	//usart.printf("\n						Motor %i Created",this->Motor_Data.Id);
}


void Motor::Move_Step(int Type)
{
	if(Type==AntiClockwise)	{GPIO_ResetBits(Motor_Data.Dir.Puerto,Motor_Data.Dir.Pin);}
	else								{GPIO_SetBits(Motor_Data.Dir.Puerto,Motor_Data.Dir.Pin);}
	
		for(int i=0; i<4;i++){
		GPIO_SetBits(Motor_Data.Sig.Puerto,Motor_Data.Sig.Pin);
		for(int i=0; i<40;i++){}  
		GPIO_ResetBits(Motor_Data.Sig.Puerto,Motor_Data.Sig.Pin);
		for(int i=0; i<40;i++){}
		}
		//each for last 4100 ns fot a total of 8200 + 250ns of each sentence gives a total of
		// 8750 ns , this value represents a value of aproximate 114 KHz or 8.7 uS
}

//**************************************************




