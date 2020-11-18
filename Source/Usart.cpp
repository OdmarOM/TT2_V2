#include "Usart.h"
#include "stm32f10x.h"                  // Device header
#include "stdio.h"
#include "string.h"

SerialUSART2::SerialUSART2(int baudrate){
	USART2_init(baudrate);
}

void SerialUSART2::sendChar(char ch){
	USART2_sendChar(ch);
}

char SerialUSART2::getChar(void){
	return USART2_getChar();
}


void SerialStream::puts(const char * pString){
	char newChar; 
	int i;
	for(i = 0 ; i < 81; i++){
		newChar = pString[i];
		if( newChar != '\0' ){
			this->sendChar(newChar);
		}else{
			break;
		}
	}
}

int SerialStream::gets(char * pBuffer, int bufferSize){
	char newChar; 
	int i ;
	for(i = 0 ; i < (bufferSize - 1); i++){
		newChar = this->getChar();
		if( (newChar != '\r') ){
			pBuffer[i]=newChar;
		}else{
			pBuffer[i]='\0';
			return i;
		}
	}
	pBuffer[bufferSize-1]='\0';
	return bufferSize-1;
}

#define OUT_BUFFER_SIZE 80

void SerialStream::printf(const char * format ,...){
	char * tempBuffer;
	va_list args;
	va_start(args, format);
	#if defined ( __GNUC__ )
	vasprintf(&tempBuffer,format, args);
	#else	
	tempBuffer=(char *)malloc(OUT_BUFFER_SIZE);//alocate memory manualy
	vsnprintf(tempBuffer,OUT_BUFFER_SIZE,format,args);
	#endif
	va_end(args);
	this->puts(tempBuffer);
	free(tempBuffer);
}

//////////////////////////////////////////////////////////

void USART2_init(int baudrate){
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	
	/*Enable peripheral clock for GPIOA*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); 
	/*Enable peripheral clock for UART2*/
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);

	/*GPIOA Configuration PA2 as TX / PA3 as RX*/
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_2|GPIO_Pin_3; 			  													   /* NOTE: Configure USART2 Rx (PA.3) as input floating */
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	USART_StructInit(&USART_InitStructure);
	USART_InitStructure.USART_BaudRate=baudrate;
	USART_InitStructure.USART_WordLength=USART_WordLength_8b;
	USART_InitStructure.USART_StopBits=USART_StopBits_1;
	USART_InitStructure.USART_Parity=USART_Parity_No;

	USART_InitStructure.USART_HardwareFlowControl=USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode=USART_Mode_Tx|USART_Mode_Rx;
	USART_Init(USART2,&USART_InitStructure);
	
	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);
	USART_Cmd(USART2,ENABLE);
	
	/*NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn; // Interrupt configuration
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);*/
}


void USART2_sendChar(char ch){
	while(!USART_GetFlagStatus(USART2,USART_FLAG_TXE));
	
	USART_SendData(USART2,ch);
}

char USART2_getChar(void){
	if(USART_GetFlagStatus(USART2,USART_FLAG_ORE)) USART_ClearFlag(USART2,USART_FLAG_ORE); 
	
	while(!USART_GetFlagStatus(USART2,USART_FLAG_RXNE));
	return USART_ReceiveData(USART2);
}

void USART1_sendChar(char ch){
	while(!USART_GetFlagStatus(USART1,USART_FLAG_TXE));
	
	USART_SendData(USART1,ch);
}

char USART1_getChar(void){
	if(USART_GetFlagStatus(USART1,USART_FLAG_ORE)) USART_ClearFlag(USART1,USART_FLAG_ORE); 
	
	while(!USART_GetFlagStatus(USART1,USART_FLAG_RXNE));
	return USART_ReceiveData(USART1);
}
