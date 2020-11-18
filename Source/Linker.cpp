#include "Linker.h"
#include "user.h"
extern SerialUSART2 usart;
extern osMutexId mid_serial;

Linker::Linker()
{
	this->Sampling=.2;
	this->Dt_us=10000;
	
	for(int i=0;i<6;i++){
	this->ready[i]=0;
	}
	
	this->Proportion=0.4;
	
	this->Current_Command=0;
	this->Speed=2;
	this->Current_State=0;
	
	for(int i=0;i<6;i++){
	this->Current_Position[i]=0;
	}
	this->Pause=true;
	this->Performing=true;
}

void 	Linker::Set_Current_State(int Command)
{
	this->Current_State=Command;
}

int Linker::Get_Current_State()
{
	return(this->Current_State);
}

void 	Linker::Set_Current_Command(int Command)
{
		this->Current_Command=Command;
}

int 	Linker::Get_Current_Command()
{
		
	return(this->Current_Command);
}

float	Linker::Get_Speed()
{
	return(this->Speed);
}

void 	Linker::Set_Current_Position(float Position,int i)
{
		this->Current_Position[i]=Position;
}

float	Linker::Get_Current_Position(int i)
{
	return(this->Current_Position[i]);
}


void	Linker::Pause_Routine(void)
{
	if(this->Pause==false)
	{
	this->Pause=true;
	usart.printf("\n			Routine Paused");
	}
	//osStatus status = osMutexWait(mid_serial, osWaitForever);
	//if(status == osOK)	
	
	//osMutexRelease(mid_serial);
}

void	Linker::Start_Routine(void)
{
	if(this->Pause==true)
	{
	this->Pause=false;
	usart.printf("\n			Routine Started");
	}
	//osStatus status = osMutexWait(mid_serial, osWaitForever);
	//if(status == osOK)	
		
	//osMutexRelease(mid_serial);
}

void	Linker::Stop_Routine(void)
{
	this->Pause=true;
	this->Performing=false;
	
	//osStatus status = osMutexWait(mid_serial, osWaitForever);
	//if(status == osOK)	
		usart.printf("\n			Routine Stoped");
	//osMutexRelease(mid_serial);
}

bool Linker::Is_Paused(void)
{
	return(this->Pause);
}

bool Linker::Is_Performing(void)
{
	return(this->Performing);
}

void Linker::Increment_Speed()
{
	if(this->Speed>60)
	{
		this->Speed-=20;
	}
	else
	{
		this->Speed=60;
	}
}

void Linker::Decrement_Speed()
{
	if(this->Speed<200)
	{
		this->Speed+=20;
	}
	else
	{
		this->Speed=200;
	}
}
