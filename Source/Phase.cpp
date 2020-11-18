#include "Phase.h"
#include "Usart.h"
#include "cmsis_os.h"
#include "linker.h"

//extern SerialUSART2 usart;
extern osThreadId Phase_Id,Phase_Thread_Id;
extern Linker Linker;
extern std::vector<TrajectoryInterface*> Global_Trajectories;
extern SerialUSART2 usart;

//*************************************************************************
void Phase::PerformPhase()
{
	usart.printf("\n			Performing Phase");
	Phase_Id=osThreadGetId();
	if(Global_Trajectories.size() == 6)
	{	
		for(int i=0; i<6; i++) 
		{
			//delete(Global_Trajectories[6-i]);
			Global_Trajectories.pop_back();
		}
	}
	  
	for(int i=0; i<6; i++)
	{
		Global_Trajectories.push_back((this->trajectories[i]));
	}
	
	osSignalSet(Phase_Thread_Id, 0x01);//wake up phase thread
	
	osSignalWait(0x01, osWaitForever);
	
	this->FreeTrayectories();
	
}
void Phase::InsertTrayectory(TrajectoryInterface* new_trajectory)
{
	this->trajectories.push_back(new_trajectory);
}
void Phase::FreeTrayectories(void)
{
		for(int i=0; i<6; i++)
			this->trajectories.pop_back();

}
