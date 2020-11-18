#ifndef _MOTOR_H
#define _MOTOR_H


#include "Delay.h"
//#include "Utilities.h"
#include "HardwareInit.h"
#include "Linker.h"
#include <vector>


class Motor
{
	public:
		MotorData Motor_Data;
	
		Motor(){};
		Motor(int Motornum);
		void Move_Step(int);
		~Motor(){};
};


#endif
