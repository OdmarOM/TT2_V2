#include "Trajectory.h"
#include "Usart.h"
#include "math.h"
#include "cmsis_os.h"

extern SerialUSART2 usart;
extern Linker Linker;
extern osThreadId Routine_Thread_Id;



void TrajectoryInterface :: SetStartPoint(int Start_Point){

	if (Start_Point>this->Min_Trajectory_Point || Start_Point <this->Max_Trajectory_Point)
		{
			this->StartPoint=Start_Point;
			//usart.puts("Start Point Ingresado");
		}
	else 
			{}
			//usart.puts("Start Point Invalido");
	
}


//*******************************************************************************************************
Home_Trajectory::Home_Trajectory() 
{
	usart.puts("\n					Home Trajectory Created");
	this->Min_Trajectory_Point=0;
	this->Max_Trajectory_Point=100;
	this->StartPoint=65;
	this->Trajectory_Resolution=5;
}


void Home_Trajectory::Perform_Trajectory(JointInterface* Joint)
{	
	
	//			|| !(GPIO_ReadInputData(this->Joint->Joint_Motor.Motor_Data.LimExt.Puerto) & this->Joint->Joint_Motor.Motor_Data.LimExt.Pin) )// Señal de los LimitSwitch
		//^^^ Codigo de control de los limit switch
	while(!GPIO_ReadInputDataBit(Joint->Joint_Motor.Motor_Data.LimCont.Puerto,Joint->Joint_Motor.Motor_Data.LimCont.Pin))
	{
		Joint->SetRelativePosition_C(-1);			
	}
	Joint->SetHome();

}

Home_Trajectory::~Home_Trajectory()
{
	
	usart.puts("\n					Home Trajectory Deleted");
}

//*******************************************************************************************************
Anatomic_Trajectory::Anatomic_Trajectory()
{
	usart.puts("\n					Anatomic Trajectory Created");
}

void Anatomic_Trajectory::Perform_Trajectory(JointInterface* Joint )
{	
	
	Joint->SetAbsolutePosition_C(Joint->Anatomic_Position);
}

Anatomic_Trajectory::~Anatomic_Trajectory()
{
	
	usart.puts("\n					Anatomic Trajectory Deleted");
}

//********************************************************************************************************
Null_Trajectory::Null_Trajectory()
{
	usart.puts("\n					Null Trajectory Created");
}

Null_Trajectory::~Null_Trajectory()
{
	usart.puts("\n					Null Trajectory Deleted");
}

void Null_Trajectory::Perform_Trajectory(JointInterface* Joint)
{
	usart.printf("\n				Performing null trajectory");
}

//******************************************************************************************************
Hip_Gate_Trajectory::Hip_Gate_Trajectory()
{
	usart.printf("\n					Hip Trajectory Created");	

	this->Min_Trajectory_Point=1;
	this->Max_Trajectory_Point=64; //65 points of difference
	this->StartPoint=1;	
}


void Hip_Gate_Trajectory::Perform_Trajectory(JointInterface* Joint)
{
	
//pow(x,3.)
	float y;
	float x=this->StartPoint;
	float mean=33,std=18.9;
	float z=(x-mean)/std;
	
	//y =-( 0.0033*pow(x,5) - 0.1278*pow(x,4) + 1.665*pow(x,3) - 8.2408*pow(x,2) + 13.711*x - 7.2308)+10;
	//y = -0.0022*pow(x,5) + 0.0876*pow(x,4) - 1.3242*pow(x,3) + 8.4255*pow(x,2) - 16.734*x + 8.5734;
	//y = 8*pow(10.,-9)*pow(x,6) - 3*pow(10.,-6)*pow(x,5) + 0.0004*pow(x,4) - 0.023*pow(x,3) + 0.6019*pow(x,2) - 4.5772*x - 7.1037;
	//y=-6.1632*pow(10.,-25)*pow(x,15)+7.8123*pow(10.,-22)*pow(x,14)-4.4507*pow(10.,-19)*pow(x,13)+1.5015*pow(10.,-16)*pow(x,12)-3.3320*pow(10.,-14)*pow(x,11)+5.1157*pow(10.,-12)*pow(x,10)-5.5676*pow(10.,-10)*pow(x,9)+4.3303*pow(10.,-8)*pow(x,8)-2.3967*pow(10.,-6)*pow(x,7)+9.2940*pow(10.,-5)*pow(x,6)-2.4564*pow(10.,-3)*pow(x,5)+4.2402*pow(10.,-2)*pow(x,4)-4.4661*pow(10.,-1)*pow(x,3)+2.5297*pow(x,2)-6.8272*x+24.843;
	
		y=-0.3188*pow(z,14)+0.3170*pow(z,13)+3.6456*pow(z,12)-2.4764*pow(z,11)-17.1076*pow(z,10)+5.7663*pow(z,9)+42.6433*pow(z,8)+1.4223*pow(z,7)-59.3629*pow(z,6)-26.2141*pow(z,5)+36.0392*pow(z,4)+39.8432*pow(z,3)+18.6035*pow(z,2)-18.0690*z-13.4381;
		y=y*Linker.Proportion;
	Joint->SetAbsolutePosition_C(y);
	
	while(!Linker.Is_Performing())
	{} //wait until starts perfomring
		
	while(Linker.Is_Performing())
	{
		while(!Linker.Is_Paused())
		{	
			if(Linker.ready[Joint->Joint_Motor.Motor_Data.Id]==1)
			{Linker.ready[Joint->Joint_Motor.Motor_Data.Id]=0;
			x+=Linker.Sampling;
			if(x>this->Max_Trajectory_Point)	x=this->Min_Trajectory_Point;
	
			z=(x-mean)/std;
				
			y=-0.3188*pow(z,14)+0.3170*pow(z,13)+3.6456*pow(z,12)-2.4764*pow(z,11)-17.1076*pow(z,10)+5.7663*pow(z,9)+42.6433*pow(z,8)+1.4223*pow(z,7)-59.3629*pow(z,6)-26.2141*pow(z,5)+36.0392*pow(z,4)+39.8432*pow(z,3)+18.6035*pow(z,2)-18.0690*z-13.4381;
			y=y*Linker.Proportion;
			Joint->SetAbsolutePosition_V(y);
			
			osSignalSet(Routine_Thread_Id,0x01);
			}
		}
	}
}
//****************************************************************************************************
Knee_Gate_Trajectory::Knee_Gate_Trajectory()
{
	usart.printf("\n					Knee Trajectory Created");	

	this->Min_Trajectory_Point=1;
	this->Max_Trajectory_Point=64; //65 points of difference
	this->StartPoint=1;		
}


void Knee_Gate_Trajectory::Perform_Trajectory(JointInterface* Joint)
{
	
		float y;
	float x=this->StartPoint;
	float mean=33,std=18.9;
	float z=(x-mean)/std;
	
			y=-1.1546*pow(z,14)-1.0963*pow(z,13)+12.7896*pow(z,12)+12.3534*pow(z,11)-54.4391*pow(z,10)-56.5627*pow(z,9)+110.0934*pow(z,8)+134.4479*pow(z,7)-96.2309*pow(z,6)-168.9311*pow(z,5)-10.2798*pow(z,4)+83.5419*pow(z,3)+67.8062*pow(z,2)+18.2441*z+6.0145;
			y=(y+Joint->offset)*Linker.Proportion;
		Joint->SetAbsolutePosition_C(y);
	
	while(!Linker.Is_Performing())
	{} //wait until starts perfomring
		
	while(Linker.Is_Performing())
	{
		while(!Linker.Is_Paused())
		{
			
			if(Linker.ready[Joint->Joint_Motor.Motor_Data.Id]==1)
			{	Linker.ready[Joint->Joint_Motor.Motor_Data.Id]=0;
					x+=Linker.Sampling;
					if(x>this->Max_Trajectory_Point)	x=this->Min_Trajectory_Point;
					
					z=(x-mean)/std;
					
					y=-1.1546*pow(z,14)-1.0963*pow(z,13)+12.7896*pow(z,12)+12.3534*pow(z,11)-54.4391*pow(z,10)-56.5627*pow(z,9)+110.0934*pow(z,8)+134.4479*pow(z,7)-96.2309*pow(z,6)-168.9311*pow(z,5)-10.2798*pow(z,4)+83.5419*pow(z,3)+67.8062*pow(z,2)+18.2441*z+6.0145;
					y=(y+Joint->offset)*Linker.Proportion;
					Joint->SetAbsolutePosition_V(y);
				osSignalSet(Routine_Thread_Id,0x01);
			}
		}
	}
	
}
//****************************************************************************************************
Ankle_Gate_Trajectory::Ankle_Gate_Trajectory()
{
	usart.printf("\n					Ankle Trajectory Created");	

	this->Min_Trajectory_Point=1;
	this->Max_Trajectory_Point=64; //65 points of difference
	this->StartPoint=1;	
}


void Ankle_Gate_Trajectory::Perform_Trajectory(JointInterface* Joint)
{
		float y;
	float x=this->StartPoint;
	float mean=33,std=18.9;
	float z=(x-mean)/std;
	
		y=90-(-3.1174*pow(z,14)-0.5496*pow(z,13)+33.7126*pow(z,12)+7.0378*pow(z,11)-143.5784*pow(z,10)-38.2535*pow(z,9)+301.4557*pow(z,8)+107.9351*pow(z,7)-312.4248*pow(z,6)-154.1425*pow(z,5)+123.4064*pow(z,4)+86.8645*pow(z,3)+14.3427*pow(z,2)+0.8635*z+87.6623);
		y=y*Linker.Proportion;
		Joint->SetAbsolutePosition_C(y);
		
	while(!Linker.Is_Performing())
	{} //wait until starts perfomring
		
	while(Linker.Is_Performing())
	{
			while(!Linker.Is_Paused())
			{
			if(Linker.ready[Joint->Joint_Motor.Motor_Data.Id]==1)
			{	Linker.ready[Joint->Joint_Motor.Motor_Data.Id]=0;
				x+=Linker.Sampling;
				if(x>this->Max_Trajectory_Point)	x=this->Min_Trajectory_Point;
				
					z=(x-mean)/std;
				
					y=90-(-3.1174*pow(z,14)-0.5496*pow(z,13)+33.7126*pow(z,12)+7.0378*pow(z,11)-143.5784*pow(z,10)-38.2535*pow(z,9)+301.4557*pow(z,8)+107.9351*pow(z,7)-312.4248*pow(z,6)-154.1425*pow(z,5)+123.4064*pow(z,4)+86.8645*pow(z,3)+14.3427*pow(z,2)+0.8635*z+87.6623);
					y=y*Linker.Proportion;
				Joint->SetAbsolutePosition_V(y);
				osSignalSet(Routine_Thread_Id,0x01);
			}
		}		
	}
	
}
//****************************************************************************************************


