#ifndef _TRAJECTORY_H
#define _TRAJECTORY_H

#include "Joint.h"

class TrajectoryInterface
{
	public:
		//JointInterface* Joint;
		
		int StartPoint,Min_Trajectory_Point,Max_Trajectory_Point,Trajectory_Resolution;
		virtual void 		Perform_Trajectory(JointInterface*)=0;
		virtual void 		SetStartPoint(int StartPoint);
		virtual float		GetTrajectoryAngle(float)=0;
		virtual int 		GetTrajectorySpeed(float)=0;
		virtual ~TrajectoryInterface(){};

};

class Home_Trajectory: public TrajectoryInterface
{	
public:	
		Home_Trajectory();
			virtual void 		Perform_Trajectory(JointInterface*);
			virtual float		GetTrajectoryAngle(float){return 0;};
			virtual int 		GetTrajectorySpeed(float){return 0;};
			virtual ~Home_Trajectory();
	

};

class Anatomic_Trajectory: public TrajectoryInterface
{	
public:	
		Anatomic_Trajectory();
			virtual void		Perform_Trajectory(JointInterface*);
			virtual float		GetTrajectoryAngle(float){return 0;};
			virtual int 		GetTrajectorySpeed(float){return 0;};
			virtual ~Anatomic_Trajectory();
	

};

class Null_Trajectory : public TrajectoryInterface
{
	public:	
		Null_Trajectory();
			virtual void 		Perform_Trajectory(JointInterface*);
			virtual float		GetTrajectoryAngle(float){return 0;};
			virtual int 		GetTrajectorySpeed(float){return 0;};
			virtual ~Null_Trajectory();

};

class Hip_Gate_Trajectory : public TrajectoryInterface
{
	public:	
		Hip_Gate_Trajectory();
			virtual void		Perform_Trajectory(JointInterface*);
			virtual float		GetTrajectoryAngle(float){return 0;};
			virtual int 		GetTrajectorySpeed(float){return 0;};
			virtual ~Hip_Gate_Trajectory(){};

};

class Knee_Gate_Trajectory : public TrajectoryInterface
{
	public:	
		Knee_Gate_Trajectory();
			virtual void		Perform_Trajectory(JointInterface*);
			virtual float		GetTrajectoryAngle(float){return 0;};
			virtual int 		GetTrajectorySpeed(float){return 0;};
			virtual ~Knee_Gate_Trajectory(){};

};

class Ankle_Gate_Trajectory : public TrajectoryInterface
{
	public:	
		Ankle_Gate_Trajectory();
			virtual void		Perform_Trajectory(JointInterface*);
			virtual float		GetTrajectoryAngle(float){return 0;};
			virtual int 		GetTrajectorySpeed(float){return 0;};
			virtual ~Ankle_Gate_Trajectory(){};

};

#endif

