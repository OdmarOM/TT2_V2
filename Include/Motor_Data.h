#ifndef _Motor_Data_H
#define _Motor_Data_H

typedef struct Motor_port{
	
	GPIO_TypeDef* Puerto; //ex:GPIOA
	uint16_t Pin;  //ex:GPIO_Pin_3
}Motor_port;

typedef struct MotorData{
	uint8_t		Channel;
	uint32_t 	 Timer;
	TIM_TypeDef* TIM;
	Motor_port Sig;
	Motor_port Dir;
	Motor_port Ena;
	Motor_port LimExt;
	Motor_port LimCont;
	Motor_port Rele;
	
}MotorData;

const MotorData Config_motor[6]={
	{3,RCC_APB1Periph_TIM4,TIM4,{GPIOB,GPIO_Pin_8},{GPIOC,GPIO_Pin_13},{GPIOA,GPIO_Pin_13},{GPIOA,GPIO_Pin_14},{GPIOA,GPIO_Pin_15},{GPIOC,GPIO_Pin_12},},
	{1,RCC_APB1Periph_TIM2,TIM2,{GPIOA,GPIO_Pin_0},{GPIOB,GPIO_Pin_10},{GPIOA,GPIO_Pin_8} ,{GPIOA,GPIO_Pin_9} ,{GPIOC,GPIO_Pin_7} ,{GPIOC,GPIO_Pin_6} ,},
	{2,RCC_APB1Periph_TIM4,TIM4,{GPIOB,GPIO_Pin_7},{GPIOC,GPIO_Pin_3} ,{GPIOC,GPIO_Pin_2} ,{GPIOC,GPIO_Pin_15},{GPIOC,GPIO_Pin_14},{GPIOC,GPIO_Pin_10},},
	{4,RCC_APB1Periph_TIM4,TIM4,{GPIOB,GPIO_Pin_9},{GPIOA,GPIO_Pin_10},{GPIOB,GPIO_Pin_3} ,{GPIOB,GPIO_Pin_5} ,{GPIOB,GPIO_Pin_4} ,{GPIOC,GPIO_Pin_8} ,},
	{3,RCC_APB1Periph_TIM3,TIM3,{GPIOB,GPIO_Pin_0},{GPIOA,GPIO_Pin_4} ,{GPIOA,GPIO_Pin_1} ,{GPIOC,GPIO_Pin_0} ,{GPIOC,GPIO_Pin_1} ,{GPIOC,GPIO_Pin_11},},
	{2,RCC_APB1Periph_TIM3,TIM3,{GPIOA,GPIO_Pin_7},{GPIOB,GPIO_Pin_14},{GPIOB,GPIO_Pin_15},{GPIOB,GPIO_Pin_1} ,{GPIOB,GPIO_Pin_2} ,{GPIOC,GPIO_Pin_9}}
};

#endif

