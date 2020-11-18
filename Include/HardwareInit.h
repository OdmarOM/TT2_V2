#ifndef __HARDWARE_INIT_H
#define __HARDWARE_INIT_H

#ifdef __cplusplus
	extern "C" {
#endif
		
#include "stm32f10x.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"
//#include "Motor.h"

void GPIO_Initialize(void);
		
		
typedef struct Motor_port{
	
	GPIO_TypeDef* Puerto; //ex:GPIOA
	uint16_t Pin;  //ex:GPIO_Pin_3
}Motor_port;

typedef struct MotorData{
	int		Id;
	uint32_t 	 Timer;
	TIM_TypeDef* TIM;
	Motor_port Sig;
	Motor_port Dir;
	Motor_port Ena;
	Motor_port LimExt;
	Motor_port LimCont;
	Motor_port Rele;
	
}MotorData;

typedef enum {Clockwise=0,AntiClockwise}Motor_Rotation;
typedef enum{Right_Hip_Motor=0,Left_Ankle_Motor,Left_Knee_Motor,Right_Knee_Motor, Left_Hip_Motor,Right_Ankle_Motor}Joint_Motor_Id;
//se cambio right ankle por right hip, por falla de driver
//y posteriormente right hip por left ankle
const MotorData Config_motor[6]={
	{5,RCC_APB1Periph_TIM4,TIM4,{GPIOA,GPIO_Pin_0},{GPIOC,GPIO_Pin_13},{GPIOA,GPIO_Pin_13},{GPIOA,GPIO_Pin_15},{GPIOC,GPIO_Pin_7},{GPIOC,GPIO_Pin_11},},
	{0,RCC_APB1Periph_TIM2,TIM2,{GPIOB,GPIO_Pin_8},{GPIOB,GPIO_Pin_10},{GPIOA,GPIO_Pin_8} ,{GPIOA,GPIO_Pin_9} ,{GPIOA,GPIO_Pin_14} ,{GPIOC,GPIO_Pin_9} ,},
	{2,RCC_APB1Periph_TIM4,TIM4,{GPIOB,GPIO_Pin_7},{GPIOC,GPIO_Pin_3} ,{GPIOC,GPIO_Pin_2} ,{GPIOC,GPIO_Pin_15},{GPIOC,GPIO_Pin_14},{GPIOC,GPIO_Pin_10},},
	{3,RCC_APB1Periph_TIM4,TIM4,{GPIOB,GPIO_Pin_9},{GPIOA,GPIO_Pin_10},{GPIOB,GPIO_Pin_3} ,{GPIOB,GPIO_Pin_5} ,{GPIOB,GPIO_Pin_4} ,{GPIOC,GPIO_Pin_8} ,},
	{4,RCC_APB1Periph_TIM3,TIM3,{GPIOB,GPIO_Pin_0},{GPIOA,GPIO_Pin_4} ,{GPIOA,GPIO_Pin_1} ,{GPIOC,GPIO_Pin_0} ,{GPIOC,GPIO_Pin_1} ,{GPIOC,GPIO_Pin_12},},
	{1,RCC_APB1Periph_TIM3,TIM3,{GPIOA,GPIO_Pin_7},{GPIOB,GPIO_Pin_14},{GPIOB,GPIO_Pin_15},{GPIOB,GPIO_Pin_1} ,{GPIOB,GPIO_Pin_2} ,{GPIOC,GPIO_Pin_6}}
};

/* original without changes
const MotorData Config_motor[6]={
	{0,RCC_APB1Periph_TIM4,TIM4,{GPIOA,GPIO_Pin_0},{GPIOC,GPIO_Pin_13},{GPIOA,GPIO_Pin_13},{GPIOA,GPIO_Pin_15},{GPIOA,GPIO_Pin_14},{GPIOC,GPIO_Pin_11},},
	{5,RCC_APB1Periph_TIM2,TIM2,{GPIOB,GPIO_Pin_8},{GPIOB,GPIO_Pin_10},{GPIOA,GPIO_Pin_8} ,{GPIOA,GPIO_Pin_9} ,{GPIOC,GPIO_Pin_7} ,{GPIOC,GPIO_Pin_9} ,},
	{2,RCC_APB1Periph_TIM4,TIM4,{GPIOB,GPIO_Pin_7},{GPIOC,GPIO_Pin_3} ,{GPIOC,GPIO_Pin_2} ,{GPIOC,GPIO_Pin_15},{GPIOC,GPIO_Pin_14},{GPIOC,GPIO_Pin_10},},
	{3,RCC_APB1Periph_TIM4,TIM4,{GPIOB,GPIO_Pin_9},{GPIOA,GPIO_Pin_10},{GPIOB,GPIO_Pin_3} ,{GPIOB,GPIO_Pin_5} ,{GPIOB,GPIO_Pin_4} ,{GPIOC,GPIO_Pin_8} ,},
	{4,RCC_APB1Periph_TIM3,TIM3,{GPIOB,GPIO_Pin_0},{GPIOA,GPIO_Pin_4} ,{GPIOA,GPIO_Pin_1} ,{GPIOC,GPIO_Pin_0} ,{GPIOC,GPIO_Pin_1} ,{GPIOC,GPIO_Pin_12},},
	{1,RCC_APB1Periph_TIM3,TIM3,{GPIOA,GPIO_Pin_7},{GPIOB,GPIO_Pin_14},{GPIOB,GPIO_Pin_15},{GPIOB,GPIO_Pin_1} ,{GPIOB,GPIO_Pin_2} ,{GPIOC,GPIO_Pin_6}}
};
*/

#ifdef __cplusplus
	}
#endif
		
#endif
