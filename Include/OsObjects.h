#ifndef __OSOBJECTS_H
#define __OSOBJECTS_H

#include "cmsis_os.h"
#include "Usart.h"
 
int InitThreads(void);
void RobotThread(void const *argument);

void Right_Hip_Thread (void const *argument);
void Right_Knee_Thread (void const *argument);
void Right_Ankle_Thread (void const *argument);
void Left_Hip_Thread (void const *argument);
void Left_Knee_Thread (void const *argument);
void Left_Ankle_Thread (void const *argument);
void Phase_Thread(void const *argument);
void Routine_Thread (void const *argument);
//void User_Thread (void const *argument);



#endif
