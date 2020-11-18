#include "HardwareInit.h"

void GPIO_Initialize(void){
	
RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR | RCC_APB1Periph_BKP , ENABLE);
 
  //PWR_BackupAccessCmd(ENABLE);
 
  RCC_LSEConfig(RCC_LSE_OFF); // Disable LSE - PC14 PC15 as GPIO   

	
	//GPIO_PinRemapConfig(GPIO_Remap_SWJ_Disable,DISABLE);
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOC |RCC_APB2Periph_AFIO, ENABLE); //habilitar el reloj de funciones alternativas

GPIO_InitTypeDef 	GPIO_Motor_DIR_Structure;
GPIO_InitTypeDef 	GPIO_Motor_ENA_Structure;
GPIO_InitTypeDef 	GPIO_Motor_LimExt_Structure;
GPIO_InitTypeDef 	GPIO_Motor_LimCont_Structure;
GPIO_InitTypeDef 	GPIO_Motor_SIG_Structure;
GPIO_InitTypeDef 	GPIO_Motor_Rele_Structure;
	
	for(int Motornum=0;Motornum<6;Motornum++){
	//RCC_APB1PeriphClockCmd(Config_motor[Motornum].Timer, ENABLE);
	 
		//Configura el puerto de la señal del motor
	GPIO_Motor_SIG_Structure.GPIO_Pin= Config_motor[Motornum].Sig.Pin; 			  													  
	GPIO_Motor_SIG_Structure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Motor_SIG_Structure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(Config_motor[Motornum].Sig.Puerto, &GPIO_Motor_SIG_Structure);
	
	 //Configura el puerto de la Direccion del motor	
	GPIO_Motor_DIR_Structure.GPIO_Pin= Config_motor[Motornum].Dir.Pin; 			  													  
	GPIO_Motor_DIR_Structure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Motor_DIR_Structure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(Config_motor[Motornum].Dir.Puerto, &GPIO_Motor_DIR_Structure);
		
	 //Configura el puerto del Enable del motor
	GPIO_Motor_ENA_Structure.GPIO_Pin= Config_motor[Motornum].Ena.Pin; 			  													  
	GPIO_Motor_ENA_Structure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Motor_ENA_Structure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(Config_motor[Motornum].Ena.Puerto, &GPIO_Motor_ENA_Structure);
	
	 //Configura el puerto del Limitswitch de Extensión del motor
	GPIO_Motor_LimExt_Structure.GPIO_Pin= Config_motor[Motornum].LimExt.Pin; 			  													  
	GPIO_Motor_LimExt_Structure.GPIO_Mode = GPIO_Mode_IPD;
	GPIO_Init(Config_motor[Motornum].LimExt.Puerto, &GPIO_Motor_LimExt_Structure);
	
	 //Configura el puerto del Limitswitch de Contracción del motor
	GPIO_Motor_LimCont_Structure.GPIO_Pin= Config_motor[Motornum].LimCont.Pin; 			  													  
	GPIO_Motor_LimCont_Structure.GPIO_Mode = GPIO_Mode_IPD;
	GPIO_Init(Config_motor[Motornum].LimCont.Puerto, &GPIO_Motor_LimCont_Structure);
	
	//Configura el puerto del Relé del motor
	GPIO_Motor_Rele_Structure.GPIO_Pin= Config_motor[Motornum].Rele.Pin; 			  													  
	GPIO_Motor_Rele_Structure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Motor_Rele_Structure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(Config_motor[Motornum].Rele.Puerto, &GPIO_Motor_Rele_Structure);
	}
}

