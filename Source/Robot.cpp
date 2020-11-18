#include "Robot.h"
#include "cmsis_os.h"

extern SerialUSART2 usart;
extern osMutexId mid_serial;

Robot::Robot()
{
	osStatus status = osMutexWait(mid_serial, osWaitForever);
	if(status == osOK)	usart.printf("\n\n	Robot created");	
	osMutexRelease(mid_serial);
	
	this->user = new UsartUser();
	this->routine=NULL;
}

void Robot::Set_Routine(RoutineInterface* Routine)
{
	
	this->routine=Routine;
}
	
void Robot::Delete_Routine()
{
		delete(this->routine);
		this->routine=NULL;
}

Robot::~Robot()
{
	usart.printf("\n\n	Robot deleted");	
}
