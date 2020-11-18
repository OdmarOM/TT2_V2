#ifndef _ROUTINE_H
#define _ROUTINE_H

#include "Phase.h"
#include <vector>


class RoutineInterface
{
	public:
		std::vector<Phase> Phases;			//Phase
		virtual void PerformRoutine();
		virtual void Pause();
		virtual void Stop();
		virtual void LoadRoutine()=0;
		virtual~RoutineInterface();
};

class CalibrationRoutine : public RoutineInterface
{
	public:
		CalibrationRoutine();
		virtual void LoadRoutine();
		virtual void Pause(void){};
		virtual ~CalibrationRoutine();
};

class GateRoutine : public RoutineInterface
{
	public:
		GateRoutine();
		virtual void LoadRoutine();
		
};


#endif //_ROUTINE_H
