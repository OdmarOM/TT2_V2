#include "main.h"

extern osMutexId mid_serial;
extern osThreadId robot_thread_id;
extern Linker Linker;


int main()
{
	int command;
	DelayInit();
	GPIO_Initialize();
	usart.printf("\n\n::System initialized::");
	osKernelInitialize();
	InitThreads();
	osKernelStart();
	UsartUser A;
	bool Drivers[6]={false,false,false,false,false,false};
	bool All_Drivers=false;
	
	for(int i=0;i<6;i++)
			{
			GPIO_ResetBits(Config_motor[i].Rele.Puerto,Config_motor[i].Rele.Pin);} 
		
	
		while(1){		
/*
	while(!GPIO_ReadInputDataBit(Config_motor[1].LimCont.Puerto,Config_motor[1].LimCont.Pin))
		{
				usart.printf("\n\n limit");
		}*/
	
		
	command=A.GetCommand();
			
	if(command==stop) 
		{
			Linker.Stop_Routine();
		}
	else if(command==AllDrivers) 
		{
			if(All_Drivers==false){
				for(int i=0;i<6;i++)
				{Drivers[i]=true;
				GPIO_SetBits(Config_motor[i].Rele.Puerto,Config_motor[i].Rele.Pin);} 
				All_Drivers=true;}
			else{
				for(int i=0;i<6;i++)
				{Drivers[i]=false;
				GPIO_ResetBits(Config_motor[i].Rele.Puerto,Config_motor[i].Rele.Pin);}
				All_Drivers=false;}
		}
	else if(command==Driver1) 
		{
			if(Drivers[0]==false)
			{Drivers[0]=true;
			GPIO_SetBits(Config_motor[0].Rele.Puerto,Config_motor[0].Rele.Pin);}
			else
			{Drivers[0]=false;
			GPIO_ResetBits(Config_motor[0].Rele.Puerto,Config_motor[0].Rele.Pin);}
		}
	else if(command==Driver2) 
		{
			if(Drivers[1]==false)
			{Drivers[1]=true;
			GPIO_SetBits(Config_motor[1].Rele.Puerto,Config_motor[1].Rele.Pin);}
			else
			{Drivers[1]=false;
			GPIO_ResetBits(Config_motor[1].Rele.Puerto,Config_motor[1].Rele.Pin);}
		}
	else if(command==Driver3) 
		{
			if(Drivers[2]==false)
			{Drivers[2]=true;
			GPIO_SetBits(Config_motor[2].Rele.Puerto,Config_motor[2].Rele.Pin);}
			else
			{Drivers[2]=false;
			GPIO_ResetBits(Config_motor[2].Rele.Puerto,Config_motor[2].Rele.Pin);}
		}
	else if(command==Driver4) 
		{
			if(Drivers[3]==false)
			{Drivers[3]=true;
			GPIO_SetBits(Config_motor[3].Rele.Puerto,Config_motor[3].Rele.Pin);}
			else
			{Drivers[3]=false;
			GPIO_ResetBits(Config_motor[3].Rele.Puerto,Config_motor[3].Rele.Pin);}
		}
	else if(command==Driver5) 
		{
			/*if(Drivers[4]==false)
			{Drivers[4]=true;
			GPIO_SetBits(Config_motor[4].Rele.Puerto,Config_motor[4].Rele.Pin);}
			else
			{Drivers[4]=false;
			GPIO_ResetBits(Config_motor[4].Rele.Puerto,Config_motor[4].Rele.Pin);}*/
			if(Linker.Proportion<1)
			Linker.Proportion+=0.1;
			else Linker.Proportion=1;
				
		}
	else if(command==Driver6) 
		{
			/*if(Drivers[5]==false)
			{Drivers[5]=true;
			GPIO_SetBits(Config_motor[5].Rele.Puerto,Config_motor[5].Rele.Pin);}
			else
			{Drivers[5]=false;
			GPIO_ResetBits(Config_motor[5].Rele.Puerto,Config_motor[5].Rele.Pin);}*/
			if(Linker.Proportion>0.2)
			Linker.Proportion-=0.1;
			else Linker.Proportion=.2;
		}
	else if(command==pause) 
		{
			
		//usart.printf("\n\n pausado");
			
			Linker.Pause_Routine();
		}
	else if(command==start) 
		{
			
		//usart.printf("\n\n iniciado");
			
			Linker.Start_Routine();
		}
	else if(command==gate) 
		{ 
			osSignalSet(robot_thread_id, 0x01);
			//usart.printf("\n\n m");
		}
		else 
			{	
			}	
	}
}	

