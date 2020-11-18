#ifndef _PHASE_H
#define _PHASE_H

#include "Trajectory.h"


class Phase
{
	private:
		std::vector<TrajectoryInterface*> trajectories;
	public:
		void PerformPhase();
		void InsertTrayectory(TrajectoryInterface* trayectory);
		void FreeTrayectories(void);
};


#endif

