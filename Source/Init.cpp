#include "Init.h"
#include "cmsis_os.h"
#include "usart.h"
#include "stm32f10x.h"
#include "Motor_Data.h"

void GPIO_iniciar(void){
RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOC |RCC_APB2Periph_AFIO, ENABLE); //habilitar el reloj de funciones alternativas
	
	GPIO_InitTypeDef 	GPIO_Motor_DIR_Structure;
	GPIO_InitTypeDef 	GPIO_Motor_ENA_Structure;
	GPIO_InitTypeDef 	GPIO_Motor_LimExt_Structure;
	GPIO_InitTypeDef 	GPIO_Motor_LimCont_Structure;
	GPIO_InitTypeDef 	GPIO_Motor_SIG_Structure;
	
	for(int Motornum=1;Motornum<6;Motornum++){
	RCC_APB1PeriphClockCmd(Config_motor[Motornum-1].Timer, ENABLE);
	 //Configura el puerto de la señal del motor
	GPIO_Motor_SIG_Structure.GPIO_Pin= Config_motor[Motornum-1].Sig.Pin; 			  													  
	GPIO_Motor_SIG_Structure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Motor_SIG_Structure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(Config_motor[Motornum-1].Sig.Puerto, &GPIO_Motor_SIG_Structure);
	
	 //Configura el puerto de la Direccion del motor	
	GPIO_Motor_DIR_Structure.GPIO_Pin= Config_motor[Motornum-1].Dir.Pin; 			  													  
	GPIO_Motor_DIR_Structure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Motor_DIR_Structure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(Config_motor[Motornum-1].Dir.Puerto, &GPIO_Motor_DIR_Structure);
		
	 //Configura el puerto del Enable del motor
	GPIO_Motor_ENA_Structure.GPIO_Pin= Config_motor[Motornum-1].Ena.Pin; 			  													  
	GPIO_Motor_ENA_Structure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Motor_ENA_Structure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(Config_motor[Motornum-1].Ena.Puerto, &GPIO_Motor_ENA_Structure);
	
	 //Configura el puerto del Limitswitch de Extensión del motor
	GPIO_Motor_LimExt_Structure.GPIO_Pin= Config_motor[Motornum-1].LimExt.Pin; 			  													  
	GPIO_Motor_LimExt_Structure.GPIO_Mode = GPIO_Mode_IPD;
	GPIO_Init(Config_motor[Motornum-1].LimExt.Puerto, &GPIO_Motor_LimExt_Structure);
	
	 //Configura el puerto del Limitswitch de Contracción del motor
	GPIO_Motor_LimCont_Structure.GPIO_Pin= Config_motor[Motornum-1].LimCont.Pin; 			  													  
	GPIO_Motor_LimCont_Structure.GPIO_Mode = GPIO_Mode_IPD;
	GPIO_Init(Config_motor[Motornum-1].Ena.Puerto, &GPIO_Motor_LimCont_Structure);
	}
	//Configuracion inicial del PWM del motor

}

