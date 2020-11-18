
#include "delay.h"
 
// For store tick counts in us
static __IO uint32_t usTicks;
 
// SysTick_Handler function will be called every 1 us
/*extern "C" void SysTick_Handler()
{
    if (usTicks != 0)
    {
        usTicks--;
    }
}*/
 
void DelayInit()
{
    // Update SystemCoreClock value
    SystemCoreClockUpdate();
    // Configure the SysTick timer to overflow every 1 us
    SysTick_Config(SystemCoreClock / 1000);
}
 
void DelayUs(uint32_t us)
{
    // Reload us value
    usTicks = us;
    // Wait until usTick reach zero
    while (usTicks);
}
 
void DelayMs(uint32_t ms)
{
    // Wait until ms reach zero
    while (ms--)
    {
        // Delay 1ms
        DelayUs(1000);
    }
}

//#include "Delay.h"

//// For store tick counts in ms
//static __IO uint32_t msTicks;
//static uint32_t Clk_Cyc_Per_uS;

//void DelayInit()
//{
//// Update SystemCoreClock value
//SystemCoreClockUpdate();

//// Configure the SysTick timer to overflow every 1 ms
//SysTick_Config(SystemCoreClock /1000);

//// DWT_Init 
//Clk_Cyc_Per_uS = SystemCoreClock/5000000;

//if (!(CoreDebug->DEMCR & CoreDebug_DEMCR_TRCENA_Msk)) 
//{
//CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;
//DWT->CYCCNT = 0;
//DWT->CTRL |= DWT_CTRL_CYCCNTENA_Msk;
//}
//}


//// SysTick_Handler function will be called every 1 ms
///*void SysTick_Handler()
//{
//if (msTicks > 0) msTicks--;
//}

//*/
//void DelayMs(uint32_t ms)
//{
//// Reload ms value
////msTicks = ms;
//// Wait until usTick reach zero
//while (ms){
//DelayUs(250);
//	ms--;
//}
//}

//void DelayUs(uint32_t us)
//{
//int32_t tp = DWT->CYCCNT + us * Clk_Cyc_Per_uS;
//while (((int32_t)DWT->CYCCNT - tp) < 0);
//}

