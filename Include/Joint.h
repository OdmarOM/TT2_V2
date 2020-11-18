#ifndef _JOINT_H
#define _JOINT_H

#include "Motor.h"



class JointInterface
{
	public:
		int Anatomic_Position;
		float offset;
		Motor Joint_Motor;
		virtual void 	SetAbsolutePosition_C(float);
		virtual void 	SetRelativePosition_C(float);
		virtual void 	SetAbsolutePosition_V(float);
		virtual void 	SetRelativePosition_V(float);
		virtual int 	GetMotorPulses(float)=0;
		virtual void 	SetHome(void)=0;
		virtual ~JointInterface(){};

};

class Hip_Joint: public JointInterface
{
	public:
		Hip_Joint(Joint_Motor_Id);
		virtual void 	SetHome(void);
		virtual int GetMotorPulses(float);
		virtual ~Hip_Joint(){};

};

class Knee_Joint: public JointInterface
{
	public:
		Knee_Joint(Joint_Motor_Id);
		virtual void 	SetHome(void);
		virtual int GetMotorPulses(float);
		virtual ~Knee_Joint(){};

};

class Ankle_Joint: public JointInterface
{
	public:
		Ankle_Joint(Joint_Motor_Id);
		virtual void 	SetHome(void);
		virtual int GetMotorPulses(float);
		virtual ~Ankle_Joint(){};

};

#endif
