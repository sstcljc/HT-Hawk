/******************** (C) COPYRIGHT 2014 Air Nano Team ***************************
 * 文件名  ：INIT.c
 * 描述    ：系统初始化         
 * 实验平台：Air Nano四轴飞行器
 * 库版本  ：ST3.5.0
 * 作者    ：Air Nano Team 
 * 淘宝    ：http://byd2.taobao.com   
             http://hengtuo.taobao.com  
**********************************************************************************/
#include "include.h"
#include "MultiRotor_app.h"

fp32 Battery_Voltage;
Flag_t flag;



/*====================================================================================================*/
/*====================================================================================================*
**函数 : Sensor_Init
**功能 : 传感器初始化
**输入 : None
**輸出 : None
**备注 : None
**====================================================================================================*/
/*====================================================================================================*/
void InitBoard(void)
{
	 delay_init(72);
	 Nvic_Init();
   LED_GPIO_Config();
   i2cInit(I2CDEV_2);
	 TIM3_Config();
	 PWM_OUT_Config();
	 PWM_IN_Config();
	 ADC1_Init();	
	 OLED_Init();
	 NRF24L01_Init();
 	 LED_SHOW();
 	 FLASH_Unlock();
 	 EE_Init();
}
/*====================================================================================================*/
/*====================================================================================================*
**函数 : Sensor_Init
**功能 : 传感器初始化
**输入 : None
**輸出 : None
**备注 : None
**====================================================================================================*/
/*====================================================================================================*/
void Sensor_Init(void)
{
	flag.MpuExist = InitMPU6050();
	flag.MagExist = Init_HMC5883L();
  flag.NrfExist = NRF24L01_Check();
  NRF24L01_Mode(1);
	
	
	
	OLED_P6x8Str(0,1,"ROLL:");
	OLED_P6x8Str(0,2,"PITCH:"); 
	OLED_P6x8Str(0,3,"YAW:");
	OLED_P6x8Str(0,5,"YAW:");
	OLED_P6x8Str(0,6,"THR:");
	OLED_P6x8Str(56,5,"ROLL:");
	OLED_P6x8Str(56,6,"PITCH:"); 
}

/*====================================================================================================*/
/*====================================================================================================*
**函数 : Screen_Update
**功能 : 屏幕数据更新
**输入 : None
**輸出 : None
**备注 : None
**====================================================================================================*/
/*====================================================================================================*/
void Screen_Update(void)
{
	Dis_Float(1,40,AngE.Roll,1);
	Dis_Float(2,40,AngE.Pitch,1);
	Dis_Float(3,40,AngE.Yaw,1);
  OLED_4num(4,5,RC_Data.YAW);
	OLED_4num(4,6,RC_Data.THROTTLE);
	OLED_4num(57,5,RC_Data.ROLL);
	OLED_4num(58,6,RC_Data.PITCH);
}



void loop(void)
{
	// 250HZ
	if(flag.Loop_250Hz){
		flag.Loop_250Hz=0;
		UsbCmdPro();
    FailSafeLEDAlarm();
	}
	
	// 100HZ
	if(flag.Loop_100Hz){
		flag.Loop_100Hz=0;
    mavlink();
		Screen_Update();
	}
		if(flag.Loop_10Hz){
		flag.Loop_10Hz=0;
    EE_SAVE_Attitude_PID();
	}
}

/*====================================================================================================*/
/*====================================================================================================*
**函数 : Time_slice
**功能 : 时间片
**输入 : None
**輸出 : None
**备注 : None
**====================================================================================================*/
/*====================================================================================================*/
void Time_slice(void)
{
  static u16 tick[3]={0,0,0};
	
	tick[0]++;tick[1]++;tick[2]++;
	
	if(tick[0]>=2){
		 tick[0] = 0;
		 flag.Loop_250Hz = 1;
	}
  if(tick[1]>=5){
		tick[1] = 0;
		flag.Loop_100Hz = 1;
	}	
  if(tick[2] >= 50)	{
		tick[2] = 0;
		flag.Loop_10Hz = 1;
	}
}




