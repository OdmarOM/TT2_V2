#include "User.h"

extern osMutexId mid_serial;
extern SerialUSART2 usart;

UsartUser::UsartUser()
{
	//osStatus status = osMutexWait(mid_serial, osWaitForever);
	//if(status == osOK)	usart.printf("\n	User created");	
	//osMutexRelease(mid_serial);
	//this->serial = SerialUSART2(9600);
}

int UsartUser::GetCommand()
{	
	char command;
	
	//osStatus status = osMutexWait(mid_serial, osWaitForever);
	//if(status == osOK)	
		command = usart.getChar();
	//osMutexRelease(mid_serial);
	
	for(int i=0; i<=sizeof(CommandMap); i++)
	{
		if(command == CommandMap[i].command)
			return CommandMap[i].command_index;
	}
	return -1;
}


void UsartUser::SendData(StatusDataType status)
{
	osMutexWait(mid_serial, osWaitForever);
	
	if (status.state==ok)
		serial.puts("\nEstado general: Correcto");
	else if(status.state==error)
		serial.puts("\nEstado general: Error");
	else{
		serial.puts("\nEstado general: Desconocido");
		}
	// 
	//serial.puts("\nPorcentaje del ciclo: ");
//		char buf[1];
//	sprintf(buf,"%d",status.Position);
//	serial.puts(buf);
	//serial.printf("\nPosicion actual: %d",status.Position);
		osMutexRelease(mid_serial);
}
