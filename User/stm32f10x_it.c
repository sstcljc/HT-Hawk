/*
*********************************************************************************************************
*	                                  
*	模块名称 : 中断模块
*	文件名称 : stm32f10x_it.c
*	版    本 : V2.0
*	说    明 : 本文件存放所有的中断服务函数。为了便于他人了解程序用到的中断，我们不建议将中断函数移到其他
*			的文件。
*				
*********************************************************************************************************
*/
#include "stm32f10x_it.h"
#include "board_config.h"

void TIM3_IRQHandler(void)		    //2ms中断一次
{	
	if(TIM3->SR & TIM_IT_Update)	{    
    TIM3->SR = ~TIM_FLAG_Update;//清除中断标志	
		
		Time_slice();
		RDAU();
 		AHRS_Geteuler();
		Calculate_Target();
 		CONTROL(Target);	
	}
}
/*
*********************************************************************************************************
*	Cortex-M3 内核异常中断服务程序
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*	函 数 名: NMI_Handler
*	功能说明: 不可屏蔽中断服务程序。
*	形    参：无
*	返 回 值: 无
*********************************************************************************************************
*/  
void NMI_Handler(void)
{
}

/*
*********************************************************************************************************
*	函 数 名: HardFault_Handler
*	功能说明: 硬件失效中断服务程序。
*	形    参：无
*	返 回 值: 无
*********************************************************************************************************
*/ 
void HardFault_Handler(void)
{
  /* 当硬件失效异常发生时进入死循环 */
  while (1)
  {
  }
}

/*
*********************************************************************************************************
*	函 数 名: MemManage_Handler
*	功能说明: 内存管理异常中断服务程序。
*	形    参：无
*	返 回 值: 无
*********************************************************************************************************
*/   
void MemManage_Handler(void)
{
  /* 当内存管理异常发生时进入死循环 */
  while (1)
  {
  }
}

/*
*********************************************************************************************************
*	函 数 名: BusFault_Handler
*	功能说明: 总线访问异常中断服务程序。
*	形    参：无
*	返 回 值: 无
*********************************************************************************************************
*/    
void BusFault_Handler(void)
{
  /* 当总线异常时进入死循环 */
  while (1)
  {
  }
}

/*
*********************************************************************************************************
*	函 数 名: UsageFault_Handler
*	功能说明: 未定义的指令或非法状态中断服务程序。
*	形    参：无
*	返 回 值: 无
*********************************************************************************************************
*/   
void UsageFault_Handler(void)
{
  /* 当用法异常时进入死循环 */
  while (1)
  {
  }
}

/*
*********************************************************************************************************
*	函 数 名: SVC_Handler
*	功能说明: 通过SWI指令的系统服务调用中断服务程序。
*	形    参：无
*	返 回 值: 无
*********************************************************************************************************
*/   
void SVC_Handler(void)
{
}

/*
*********************************************************************************************************
*	函 数 名: DebugMon_Handler
*	功能说明: 调试监视器中断服务程序。
*	形    参：无
*	返 回 值: 无
*********************************************************************************************************
*/   
void DebugMon_Handler(void)
{
}

/*
*********************************************************************************************************
*	函 数 名: PendSV_Handler
*	功能说明: 可挂起的系统服务调用中断服务程序。
*	形    参：无
*	返 回 值: 无
*********************************************************************************************************
*/     
void PendSV_Handler(void)
{
}

/*
*********************************************************************************************************
*	函 数 名: SysTick_Handler
*	功能说明: 系统嘀嗒定时器中断服务程序。
*	形    参：无
*	返 回 值: 无
*********************************************************************************************************
*/     
// extern void SysTick_ISR(void);	/* 声明调用外部的函数 */
// void SysTick_Handler(void)
// {
// 	SysTick_ISR();	/* 这个函数在bsp_timer.c中 */
// }

/*
*********************************************************************************************************
*	STM32F10x内部外设中断服务程序
*	用户在此添加用到外设中断服务函数。有效的中断服务函数名请参考启动文件(startup_stm32f10x_xx.s)
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*	函 数 名: USB_LP_CAN1_RX0_IRQHandler
*	功能说明: 低优先级USB中断服务程序。
*	形    参：无
*	返 回 值: 无
*********************************************************************************************************
*/ 
extern void usb_Istr(void);
void USB_LP_CAN1_RX0_IRQHandler(void)
{
	usb_Istr();
}


