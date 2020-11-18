#ifndef _LINKER_H
#define _LINKER_H

class Linker
{
	public:
		int 		Current_State;
		int 		Current_Command;
		float 	Speed;
		float 	Current_Position[6];
		bool 		Pause;
		bool 		Performing;
		int 		Dt_us;
		float 	Sampling;
		int 		ready[6];
		float 	Proportion;

		Linker();
		void		Set_Current_State(int);
		int			Get_Current_State();
		void 		Set_Current_Command(int);
		int 		Get_Current_Command();
		float		Get_Speed();
		void 		Set_Current_Position(float,int);
		float		Get_Current_Position(int);
		void		Pause_Routine(void);
		void		Start_Routine(void);
		void		Stop_Routine(void);		
		void		Increment_Speed(void);
		void		Decrement_Speed(void);
		bool		Is_Paused(void);
		bool		Is_Performing(void);
		
};






#endif
