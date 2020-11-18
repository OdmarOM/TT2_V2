#ifndef _ROBOT_H
#define _ROBOT_H

#include "User.h"
#include "Routine.h"

class Robot	 // En ingles 
{
	public:
		StatusDataType 			robot_status;
		RoutineInterface* 	routine;			
		UserInterface*			user;
		Robot();
		void Set_Routine(RoutineInterface*);
		void Delete_Routine();
		~Robot();
};


#endif
