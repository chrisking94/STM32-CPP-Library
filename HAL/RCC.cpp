#include "RCC.h"
/**
  ******************************************************************************
  * @file    RCC.cpp
  * @author  ChrisKing
  * @version V1.0.0
  * @date    2017/07/07 13:23
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

void __reserved_SRCC::resetPeriph(APB2Periph periph)
{
	APB2ENR|=periph;
	APB2ENR&=~periph;
}

void __reserved_SRCC::resetPeriph(APB1Periph periph)
{
	APB1ENR|=periph;
	APB1ENR&=~periph;
}

