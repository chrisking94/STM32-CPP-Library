#include "RTC.h"
/**
  ******************************************************************************
  * @file    RTC.cpp
  * @author  ChrisKing
  * @version V1.0.0
  * @date    2017/07/07 13:26
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

void __reserved_CRTC::setPrescalerReloadValue(u32 val)
{
	PRLL=(u16)val;
	PRLH=(u16)(val>>16);
}

u32 __reserved_CRTC::getClockDivider(u32 val)
{
	return (((u32)DIVH)<<16)|DIVL;
}

void __reserved_CRTC::setCounter(u32 val)
{
	CNTL=(u16)val;
	CNTH=(u16)(val>>16);
}

u32 __reserved_CRTC::getCounter(u32 val)
{
	return (((u32)CNTH)<<16)|CNTL;
}

void __reserved_CRTC::setAlarm(u32 val)
{
	ALRL=(u16)val;
	ALRH=(u16)(val>>16);
}
