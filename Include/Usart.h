#ifndef _USART_H
#define _USART_H

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

void USART2_init(int baudrate);
void USART2_sendChar(char ch);
char USART2_getChar(void);

class SerialStream{
	public:
		virtual char getChar(void) = 0;
		virtual void sendChar(char) = 0;
		void puts(const char * pString);
		int gets(char * pBuffer, int bufferSize);
		void printf(const char * format, ...) __attribute__ ((format (printf, 2, 3)));
};

class SerialUSART2: public SerialStream{
	public:
		SerialUSART2(){};
		SerialUSART2(int baudrate);
		virtual char getChar(void);
		virtual void sendChar(char c);
};

#endif //_USART_H



