/*
******************* (C) COPYRIGHT 2015 Air Nano Team ***************************
 * 模块名称 : 主程序模块
 * 文件名   ：main.c
 * 描述     ：系统初始化         
 * 实验平台 ：HT_Hawk
 * 库版本   ：ST3.5.0
 * 作者     ：Air Nano Team 
 * 论坛     ：http://www.airnano.cn
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
	// boot_loader 相关配置
  Bootloader_Set();
	
	// 硬件初始化
	InitBoard();	

	// 传感器初始化
	Sensor_Init();
	
	// 加载参数
	paramLoad();
	
	/* 开定时中断 */
  EnTIMER;    

	while(1)
	{
    loop();
	}			
}





