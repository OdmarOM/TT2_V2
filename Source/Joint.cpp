#include "Joint.h"
#include "usart.h"
#include <math.h>

extern SerialUSART2 usart;
extern Linker Linker;

void JointInterface::SetRelativePosition_C(float Angle)
{	
	int Number_of_Pulses=this->GetMotorPulses(Angle);
	
	for(int i=0;i<=Number_of_Pulses;i++)
	{
	if(Angle<0) 
		this->Joint_Motor.Move_Step(Clockwise);
	else
		this->Joint_Motor.Move_Step(AntiClockwise);
		for(int i=0; i<800;i++){} 
	}
	Linker.Set_Current_Position(Linker.Current_Position[this->Joint_Motor.Motor_Data.Id]+Angle,this->Joint_Motor.Motor_Data.Id);
	//usart.printf("%i",Number_of_Pulses);
}

void JointInterface::SetAbsolutePosition_C(float Angle)
{	
	int Relative_Angle=Angle-Linker.Get_Current_Position(this->Joint_Motor.Motor_Data.Id);
	this->SetRelativePosition_C(Relative_Angle);
}
//*********************************************************

void JointInterface::SetRelativePosition_V(float Angle)
{	
		int Number_of_Pulses=this->GetMotorPulses(Angle);

	//float time_span_of_pulse=35; //in microseconds;
	
	/*int delayus=((Linker.Dt_us-Number_of_Pulses*time_span_of_pulse)/Number_of_Pulses)+1; 
	//we muliply by 100 to get houndreds of nanoseconds beacouse thats what each iteration of the for last
			
	if(delayus<0)
			{
				Linker.Pause_Routine();
				while(delayus<0)
				{	Linker.Dt_us+=50;
					delayus=((Linker.Dt_us-Number_of_Pulses*time_span_of_pulse)/Number_of_Pulses)*100; 
				}
				Linker.Start_Routine();
			}
			else
			{
			}*/
			
	float in_min=0; //the inputs represent the values from the graph
								float in_max=5*(Linker.Proportion);
								float out_min=40;// the outputs are the values we are mapping to and corresponds to the
								float out_max=0;// time of the delay, less delay faster speed.
							
								int delayus=(Angle - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;	
			
	for(int i=0;i<=Number_of_Pulses;i++)
	{
	if(Angle<0) 
		this->Joint_Motor.Move_Step(Clockwise);
	else
		this->Joint_Motor.Move_Step(AntiClockwise);
		for(int i=0; i<delayus;i++){} 
	}
	Linker.Set_Current_Position(Linker.Current_Position[this->Joint_Motor.Motor_Data.Id]+Angle,this->Joint_Motor.Motor_Data.Id);
	
}

void JointInterface::SetAbsolutePosition_V(float Angle)
{	
	float Relative_Angle=Angle-Linker.Get_Current_Position(this->Joint_Motor.Motor_Data.Id);
	this->SetRelativePosition_V(Relative_Angle);
}


//intervalo total / dt = speed
//**************************************************
//*************************************************************************


Hip_Joint::Hip_Joint(Joint_Motor_Id Motor_Id)
{
	//	usart.puts("\n					Hip Created");
	
		this->Joint_Motor= Motor(Motor_Id);
		this->Anatomic_Position=0;
}

int Hip_Joint::GetMotorPulses(float Angle)
{ 
	float I_A,F_A;
	int Motor_Pulses;
	float Initial_Angle=Linker.Get_Current_Position(this->Joint_Motor.Motor_Data.Id);

	I_A = -0.0002*pow(Initial_Angle,3) + 0.0072*pow(Initial_Angle,2) + 2.4268*Initial_Angle + 61.751;
	F_A = -0.0002*pow(Initial_Angle+Angle,3) + 0.0072*pow(Initial_Angle+Angle,2) + 2.4268*(Initial_Angle+Angle)+ 61.751;
	Motor_Pulses=((F_A-I_A)/5)*1250;

	return(abs(Motor_Pulses));
}

void Hip_Joint::SetHome()
{

Linker.Set_Current_Position(-26,this->Joint_Motor.Motor_Data.Id);
}
//**************************************************
Knee_Joint::Knee_Joint(Joint_Motor_Id Motor_Id)
{
		//	usart.puts("\n					Knee Created");
	this->Joint_Motor=Motor(Motor_Id);
	this->Anatomic_Position=0;
	
}

int Knee_Joint::GetMotorPulses(float Angle)
{ 
	float I_A,F_A;
	int Motor_Pulses;
	float Initial_Angle=Linker.Get_Current_Position(this->Joint_Motor.Motor_Data.Id);

		I_A = 0.0002*pow(Initial_Angle,3) - 0.0141*pow(Initial_Angle,2) + 1.6777*Initial_Angle - 0.0831;
		F_A =  0.0002*pow(Initial_Angle+Angle,3) - 0.0141*pow(Initial_Angle+Angle,2) + 1.6777*(Initial_Angle+Angle) - 0.0831;
		Motor_Pulses=((F_A-I_A)/5)*1250;

	return(abs(Motor_Pulses));
}

void Knee_Joint::SetHome()
{

Linker.Set_Current_Position(0,this->Joint_Motor.Motor_Data.Id);
}

//**************************************************
Ankle_Joint::Ankle_Joint(Joint_Motor_Id Motor_Id)
{
	//			usart.puts("\n					Ankle Created");
	this->Joint_Motor=Motor(Motor_Id);
	this->Anatomic_Position=0;
}

int Ankle_Joint::GetMotorPulses(float Angle)
{ 
	float I_A,F_A;
	int Motor_Pulses;
	float Initial_Angle=Linker.Get_Current_Position(this->Joint_Motor.Motor_Data.Id);
	
		I_A = -1.1205*Initial_Angle + 138.33;
		F_A =	-1.1205*(Initial_Angle+Angle) + 138.33;
		Motor_Pulses=((F_A-I_A)/5)*1250;

	return(abs(Motor_Pulses));
}


void Ankle_Joint::SetHome()
{

Linker.Set_Current_Position(-37,this->Joint_Motor.Motor_Data.Id);
}
//section to calculate the delay based on the velocity graph of the trajectory
								
								/*float in_min=0; //the inputs represent the values from the graph
								float in_max=7.5;
								float out_min=20;// the outputs are the values we are mapping to and corresponds to the
								float out_max=0;	// time of the delay, less delay faster speed.
							
								int delay=(Speed - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;*/


