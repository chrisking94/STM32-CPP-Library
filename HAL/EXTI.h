#pragma once
#include "Common.h"
#include "GPIOPin.h"
/**
  ******************************************************************************
  * @file    EXTI.h
  * @author  ChrisKing
  * @version V1.0.0
  * @date    2017/07/07 12:54
  * @contact 1050243371@qq.com
  * @brief   TestMCU:STM32F103C8T6 IDE:VS2010 OS:Windows7
  * @history
  *  <author> 
  *  <date>   
  *  <version>
  *  <brief>  
  ******************************************************************************     
  *
  * You can modify this file and redistribute it.Yet you shoud keep the original
  * authors' information and copyright declaration unmodified.If you are willing
  * to redistribute this file after your modification,it's very nice for you to
  * add your information to the history list.
  *
  * 				Copyright (c) XinxinWang.XiHua University,China.
  ******************************************************************************
  */

struct __reserved_SEXTI//总共只有16个外部中断模块，所以多组GPIO的设置为中断时，引脚号不能相同
{
public:
	typedef enum 
	{
		_Rising=1,//上升沿触发
		_Falling,//下降沿触发
		_RisiFall//上升和下降沿触发
	}EXTITrigMode;
public:
		void	enableInterrupt(u8	linex);/*linex[0~19]*/
		void	disableInterrupt(u8	linex);/*linex[0~19]*/
		void	enableEventRequest(u8	linex);/*linex[0~19]*/
		void	disableEventRequest(u8	linex);/*linex[0~19]*/
		void	enableRisingTrig(u8	linex);/*linex[0~19]，允许上升沿触发*/
		void	disableRisingTrig(u8	linex);/*linex[0~19]，禁止上升沿触发*/
		void	enableFallingTrig(u8	linex);/*linex[0~19]，允许下降沿触发*/
		void	disableFallingTrig(u8	linex);/*linex[0~19]，禁止下降沿触发*/
		void	trigInterrupt(u8	linex);/*linex[0~19]，通过该函数可以触发中断*/
		void	clearPendingBit(u8	linex);/*linex[0~19]，清除挂起位，中断函数中需要调用*/
		u32		isPended(u8	linex);/*linex[0~19]，是否挂起*/
private:
	__IO uint32_t IMR;
	__IO uint32_t EMR;
	__IO uint32_t RTSR;
	__IO uint32_t FTSR;
	__IO uint32_t SWIER;
	__IO uint32_t PR;
};

#define exti	(*(__reserved_SEXTI*)EXTI)




inline void __reserved_SEXTI::enableInterrupt(u8 linex)
{
	BSETB_REG(IMR,linex);
}

inline void __reserved_SEXTI::disableInterrupt(u8 linex)
{
	BCLR_REG(IMR,linex);
}

inline void __reserved_SEXTI::enableEventRequest(u8 linex)
{
	BSETB_REG(EMR,linex);
}

inline void __reserved_SEXTI::disableEventRequest(u8 linex)
{
	BCLR_REG(EMR,linex);
}

inline void __reserved_SEXTI::enableRisingTrig(u8 linex)
{
	BSETB_REG(RTSR,linex);
}

inline void __reserved_SEXTI::disableRisingTrig(u8 linex)
{
	BCLR_REG(RTSR,linex);
}

inline void __reserved_SEXTI::enableFallingTrig(u8 linex)
{
	BSETB_REG(FTSR,linex);
}

inline void __reserved_SEXTI::disableFallingTrig(u8 linex)
{
	BCLR_REG(FTSR,linex);
}

inline void __reserved_SEXTI::trigInterrupt(u8 linex)
{
	BSETB_REG(SWIER,linex);
}

inline void __reserved_SEXTI::clearPendingBit(u8 linex)
{
	BSETB_REG(PR,linex);
}

inline u32 __reserved_SEXTI::isPended(u8 linex)
{
	return BGET_REG(PR,linex);
}
