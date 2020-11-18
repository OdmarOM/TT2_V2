#include "Routine.h"
#include "Usart.h"

extern SerialUSART2 usart;
extern Linker Linker;

void RoutineInterface::PerformRoutine(void)
{
	usart.printf("\n			Performing Routine");
	usart.printf("\n");
	for(int i=0; i<this->Phases.size(); i++)
	{
		//usart.printf("%d",i);
		this->Phases[i].PerformPhase(); //this also eliminates the trajectories at the end 
	}
	
	for(int i=0; i<=this->Phases.size(); i++)
	{
		this->Phases.pop_back();
	}
}

void RoutineInterface::Pause()
{

}

void RoutineInterface::Stop()
{
	Linker.Pause_Routine();
	usart.printf("\n\n		stoping...");
	for(int i=0; i<this->Phases.size(); i++)
	{
		this->Phases[i].FreeTrayectories(); 
	}	

	for(int i=0; i<this->Phases.size(); i++)
	{
		this->Phases.pop_back();
	}
	Phase Stop;
		for(int i=0; i<6; i++)
		{
		Stop.InsertTrayectory(new Anatomic_Trajectory());
		}
		
	this->Phases.push_back(Stop);
		this->Phases[1].PerformPhase();
		this->Phases.pop_back();
	usart.printf("\n\n		stoped");
	delete(this);
}

RoutineInterface::~RoutineInterface()
{
	usart.printf("\n\n		Routine Deleted");

}

//**************************************************
CalibrationRoutine::CalibrationRoutine()
{
	usart.printf("\n		CalibrationRoutine created");
}

void CalibrationRoutine::LoadRoutine()
{
	Phase phase1;
	Phase phase2;
	
	for(int i=0; i<6; i++)
	{
			phase1.InsertTrayectory(new Home_Trajectory);
			phase2.InsertTrayectory(new Anatomic_Trajectory);
	}
	this->Phases.push_back(phase1);
	this->Phases.push_back(phase2);
		
usart.printf("\n\n		CalibrationRoutine Loaded");

}

CalibrationRoutine::~CalibrationRoutine()
{
		usart.printf("\n		Calibration routine deleting...");
}

//**************************************************

GateRoutine::GateRoutine()
{

}


void GateRoutine::LoadRoutine(void)
{
usart.printf("\n\n		GateRoutine Loaded");
}



