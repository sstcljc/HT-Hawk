/*
******************* (C) COPYRIGHT 2015 Air Nano Team ***************************
 * 模块名称 : 主程序模块
 * 文件名   ：main.c
 * 描述     ：系统初始化         
 * 实验平台 ：Air Nano四轴飞行器
 * 库版本   ：ST3.5.0
 * 作者     ：Air Nano Team 
 * 淘宝     ：http://byd2.taobao.com   
 *            http://hengtuo.taobao.com   
*********************************************************************************
*/

#include "board_config.h"

/*
*********************************************************************************************************
*	函 数 名: main
*	功能说明: c程序入口
*	形    参：无
*	返 回 值: 错误代码(无需处理)
*********************************************************************************************************
*/
int main(void)
{
	/* 为了是main函数看起来更简洁些，我们将硬件初始化的代码封装到这个函数 */
	InitBoard();	

	/* 初始化USB设备 */
  bsp_InitUsb();
	Sensor_Init();
	paramLoad();
	
	/* 开定时中断 */
  EnTIM3();     
	
	while(1)
	{
    loop();
	}			
}











