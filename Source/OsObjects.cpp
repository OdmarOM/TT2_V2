#include "OsObjects.h"
#include "Robot.h"
#include "Linker.h"
#include <vector>
#include "Delay.h"

extern SerialUSART2 usart;
Linker Linker;


std::vector<TrajectoryInterface*> Global_Trajectories;

osMutexId mid_serial;
osMutexDef(Serial);


osThreadId Routine_Thread_Id;
osThreadId Phase_Id;

osThreadId robot_thread_id;
osThreadId Phase_Thread_Id;
osThreadId Right_Hip_Thread_Id;
osThreadId Right_Knee_Thread_Id;
osThreadId Right_Ankle_Thread_Id;
osThreadId Left_Hip_Thread_Id;
osThreadId Left_Knee_Thread_Id;
osThreadId Left_Ankle_Thread_Id;

osThreadDef(RobotThread, osPriorityNormal, 1, 0);
osThreadDef(Routine_Thread, osPriorityAboveNormal, 1, 0);
osThreadDef(Phase_Thread, osPriorityAboveNormal, 1, 0);
osThreadDef(Right_Hip_Thread, osPriorityNormal, 1, 0);
osThreadDef(Right_Knee_Thread, osPriorityNormal, 1, 0);
osThreadDef(Right_Ankle_Thread, osPriorityNormal, 1, 0);
osThreadDef(Left_Hip_Thread, osPriorityNormal, 1, 0);
osThreadDef(Left_Knee_Thread, osPriorityNormal, 1, 0);
osThreadDef(Left_Ankle_Thread, osPriorityNormal, 1, 0);


int InitThreads(void)
{
	mid_serial =   osMutexCreate(osMutex(Serial));
	robot_thread_id = osThreadCreate(osThread(RobotThread), NULL);
	Right_Hip_Thread_Id = osThreadCreate(osThread(Right_Hip_Thread), NULL);
	Right_Knee_Thread_Id = osThreadCreate(osThread(Right_Knee_Thread), NULL);
	Right_Ankle_Thread_Id = osThreadCreate(osThread(Right_Ankle_Thread), NULL);
	Left_Hip_Thread_Id = osThreadCreate(osThread(Left_Hip_Thread), NULL);
	Left_Knee_Thread_Id = osThreadCreate(osThread(Left_Knee_Thread), NULL);
	Left_Ankle_Thread_Id = osThreadCreate(osThread(Left_Ankle_Thread), NULL);
	Routine_Thread_Id = osThreadCreate(osThread(Routine_Thread), NULL);
	Phase_Thread_Id = osThreadCreate(osThread(Phase_Thread),NULL);
	

	if(!mid_serial)return(-1);
	if(!robot_thread_id)return(-1);
	if(!Right_Hip_Thread_Id) return(-1);
	if(!Right_Knee_Thread_Id) return(-1);
	if(!Right_Ankle_Thread_Id) return(-1);
	if(!Left_Hip_Thread_Id) return(-1);
	if(!Left_Knee_Thread_Id) return(-1);
	if(!Left_Ankle_Thread_Id) return(-1);
	if(!Routine_Thread_Id) return(-1);
	if(!Phase_Thread_Id) return(-1);
	//usart.printf("\nThreads Created");
	return(0);
}

void RobotThread(void const *argument)
{	
	//Robot exo:
	//	
	/*osStatus status = osMutexWait(mid_serial, osWaitForever);
	if(status == osOK)	usart.printf("\n		Robot started");
	osMutexRelease(mid_serial);*/
	//JointInterface* Joint=new Knee_Joint(Right_Knee_Motor);
	//Home_Trajectory home;
	while(1)
	{
		//osSignalWait(0x01,osWaitForever);
		//GPIO_SetBits(Config_motor[4].Rele.Puerto,Config_motor[4].Rele.Pin);	

		osSignalWait(0x01,osWaitForever);
		
		Global_Trajectories.push_back(new Home_Trajectory());
		Global_Trajectories.push_back(new Home_Trajectory());
		Global_Trajectories.push_back(new Home_Trajectory());
		Global_Trajectories.push_back(new Home_Trajectory());
		Global_Trajectories.push_back(new Home_Trajectory());
		Global_Trajectories.push_back(new Home_Trajectory());
		
		osSignalSet(Phase_Thread_Id,0x01);
		
		osSignalWait(0x01,osWaitForever);
		
		for(int i=0;i<6;i++){
		Global_Trajectories.pop_back();
		}
		
		Global_Trajectories.push_back(new Anatomic_Trajectory());
		Global_Trajectories.push_back(new Anatomic_Trajectory());
		Global_Trajectories.push_back(new Anatomic_Trajectory());
		Global_Trajectories.push_back(new Anatomic_Trajectory());
		Global_Trajectories.push_back(new Anatomic_Trajectory());
		Global_Trajectories.push_back(new Anatomic_Trajectory());
		
		osSignalSet(Phase_Thread_Id,0x01);
		osSignalWait(0x01,osWaitForever);
		
		for(int i=0;i<6;i++){
		Global_Trajectories.pop_back();
		}
		
		Global_Trajectories.push_back(new Ankle_Gate_Trajectory());
		Global_Trajectories.push_back(new Ankle_Gate_Trajectory());
		Global_Trajectories.push_back(new Knee_Gate_Trajectory());
		Global_Trajectories.push_back(new Knee_Gate_Trajectory());
		Global_Trajectories.push_back(new Hip_Gate_Trajectory());
		Global_Trajectories.push_back(new Hip_Gate_Trajectory());
		
		usart.printf("\n Running...");
		osSignalSet(Phase_Thread_Id,0x01);
		osSignalSet(Routine_Thread_Id,0x01);
		
		osSignalWait(0x01,osWaitForever);
		
				
		for(int i=0;i<6;i++){
		Global_Trajectories.pop_back();
		}
		
		Global_Trajectories.push_back(new Anatomic_Trajectory());
		Global_Trajectories.push_back(new Anatomic_Trajectory());
		Global_Trajectories.push_back(new Anatomic_Trajectory());
		Global_Trajectories.push_back(new Anatomic_Trajectory());
		Global_Trajectories.push_back(new Anatomic_Trajectory());
		Global_Trajectories.push_back(new Anatomic_Trajectory());
		
		
		osSignalSet(Phase_Thread_Id,0x01);
		
		/*osSignalWait(0x01,osWaitForever);	
		//home.Perform_Trajectory(Joint);
		Joint->SetRelativePositionA(-1);*/
		
				
			/*	Linker.Set_Current_Command(exo.user->GetCommand());
		
		if(Linker.Get_Current_Command()==not_a_command)
		{
			status = osMutexWait(mid_serial, osWaitForever);
				if(status == osOK)		usart.printf("\r*****Not a Valid Comand");
			osMutexRelease(mid_serial);
		}
		else if(Linker.Get_Current_Command()==pause && !Linker.Is_Paused() )			Linker.Pause_Routine();
		else if(Linker.Get_Current_Command()==start &&  Linker.Is_Paused() )			Linker.Start_Routine();
		else if(Linker.Get_Current_Command()==stop && Linker.Routine!=NULL)
		{
				if(Linker.Get_Current_Routine_Command()!= calibration){ //<---------unstopable routines
					
				Linker.Set_Current_Routine_Command(Linker.Get_Current_Command());
				Linker.Routine->Stop();
				Linker.Routine=NULL;}
		}
		else if(Linker.Get_Current_Command()!=Linker.Current_Routine_Command && Linker.Routine==NULL)
		{
			Linker.Set_Current_Routine_Command(Linker.Get_Current_Command());
			
			switch(Linker.Get_Current_Command())
		{
			case calibration:
				status = osMutexWait(mid_serial, osWaitForever);
				if(status == osOK)	usart.printf("\n		Calibration Routine selected");
					osMutexRelease(mid_serial);
					
					exo.Set_Routine(new CalibrationRoutine());
					Linker.Pause_Routine();
					Linker.Routine=exo.routine;
					osSignalSet(Routine_Thread_Id,0x01);
			break;
			case gate:
				status = osMutexWait(mid_serial, osWaitForever);
				if(status == osOK)	usart.printf("\n	Gate Routine selected");
				osMutexRelease(mid_serial);
					
					exo.Set_Routine(new GateRoutine());
					Linker.Pause_Routine();
					Linker.Routine=exo.routine;
					osSignalSet(Routine_Thread_Id,0x01);
			break;
			default:	
			break;	
			}
			
		}
		else
		{}
		*/
	}
}



void Routine_Thread (void const *argument){

	while(1){
		osSignalWait(0x01,osWaitForever);
		while(1)
		{
			Linker.ready[0]=1;
			Linker.ready[2]=1;
			Linker.ready[4]=1;
			
			Linker.ready[1]=1;
			Linker.ready[3]=1;
			Linker.ready[5]=1;
			
		for(int i=0;i<4;i++)
		{
		osSignalWait(0x01,osWaitForever);
		}
	}
		/*
		if(Linker.Get_Current_Routine_Command()==calibration)cycles=1;
		else cycles=5;
			
		for(int i=0;i<cycles;i++){ 
		
			Linker.Routine->LoadRoutine();
			Linker.Routine->PerformRoutine();
		}
			Linker.Routine->Stop();
			Linker.Set_Current_Routine_Command(0);
			Linker.Routine=NULL;*/
			
	}
}

void Phase_Thread (void const* argument)
{
while(1)
	{
		osSignalWait(0x01,osWaitForever);
			//usart.printf("\n		 Thread Phase");
		
		osSignalSet(Right_Hip_Thread_Id,0x01);
		osSignalSet(Right_Knee_Thread_Id,0x01);		
		//osSignalSet(Right_Ankle_Thread_Id,0x01);
		osSignalSet(Left_Hip_Thread_Id,0x01);
		osSignalSet(Left_Knee_Thread_Id,0x01);
		//osSignalSet(Left_Ankle_Thread_Id,0x01);
		
		
		for(int i=0;i<4;i++)
		{
		osSignalWait(0x01,osWaitForever);
		}
		usart.printf("\n	done0");
		//osSignalSet(Phase_Id,0x01);
		osSignalSet(robot_thread_id, 0x01);
	}	
}

void Right_Hip_Thread (void const *argument){
	JointInterface* Joint=new Hip_Joint(Right_Hip_Motor);
	while(1){
		osSignalWait(0x01,osWaitForever);
			Global_Trajectories[Joint->Joint_Motor.Motor_Data.Id]->SetStartPoint(33);
			Global_Trajectories[Joint->Joint_Motor.Motor_Data.Id]->Perform_Trajectory(Joint);
		osSignalSet(Phase_Thread_Id,0x01);
	}
}

void Right_Knee_Thread (void const *argument){
	JointInterface* Joint=new Knee_Joint(Right_Knee_Motor);
	Joint->offset=4.5;
	while(1){
		osSignalWait(0x01,osWaitForever);
		
		Global_Trajectories[Joint->Joint_Motor.Motor_Data.Id]->SetStartPoint(33);
		Global_Trajectories[Joint->Joint_Motor.Motor_Data.Id]->Perform_Trajectory(Joint);
		osSignalSet(Phase_Thread_Id,0x01);
	}
}

void Right_Ankle_Thread (void const *argument){
	JointInterface* Joint=new Ankle_Joint(Right_Ankle_Motor);
	while(1){
		osSignalWait(0x01,osWaitForever);
		
			Global_Trajectories[Joint->Joint_Motor.Motor_Data.Id]->Perform_Trajectory(Joint);
		osSignalSet(Phase_Thread_Id,0x01);
	}
}


void Left_Hip_Thread (void const *argument){
	JointInterface* Joint=new Hip_Joint(Left_Hip_Motor);
	while(1){
		osSignalWait(0x01,osWaitForever);
		
		Global_Trajectories[Joint->Joint_Motor.Motor_Data.Id]->Perform_Trajectory(Joint);

		osSignalSet(Phase_Thread_Id,0x01);

	}
}

void Left_Knee_Thread (void const *argument){
	JointInterface* Joint=new Knee_Joint(Left_Knee_Motor);
	Joint->offset=-2;
	while(1){
		osSignalWait(0x01,osWaitForever);
		
			Global_Trajectories[Joint->Joint_Motor.Motor_Data.Id]->Perform_Trajectory(Joint);
		osSignalSet(Phase_Thread_Id,0x01);
	}
}

void Left_Ankle_Thread (void const *argument){
	JointInterface* Joint=new Ankle_Joint(Left_Ankle_Motor);
	while(1){
		osSignalWait(0x01,osWaitForever);
		
		Global_Trajectories[Joint->Joint_Motor.Motor_Data.Id]->Perform_Trajectory(Joint);
		osSignalSet(Phase_Thread_Id,0x01);
	}
}

