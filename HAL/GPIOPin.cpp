#include "GPIOPin.h"
#include "Common.h"
/**
  ******************************************************************************
  * @file    GPIOPin.cpp
  * @author  ChrisKing
  * @version V1.0.0
  * @date    2017/07/07 12:16
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
void __reserved_SGPIOPin::pinMod(GPIOMod mod,GPIOFreq freq/*=_50MHz*/)
{
	volatile uint32_t *pReg;

	GPIOPin pin=pinNum();
	if(mod>=_IA) freq=(GPIOFreq)0;//输入模式低二位(freq)为00
	//配置引脚
	pReg=(volatile uint32_t *)GPIOA_BASE;
	pReg+=(pin/16)*0x0100;//计算A、B、C、...组的BASE地址，整数除法一般情况不能和整数乘法交换，除法会取整
	pin=(GPIOPin)(pin%16);
	if(pin>7)//CRH
	{
		pReg++;
		pin=(GPIOPin)(pin-8);
	}
	pin=(GPIOPin)(pin<<2);
	(*pReg) &= ~(((u32)0xf)<<pin);
	(*pReg) |= ((u32)mod<<2|freq)<<pin;
}

GPIOPin __reserved_SGPIOPin::pinNum() const
{
	u32 ib=(u32)&IBand-(u32)&PA0,i;

	for(i=0;ib>((u32)&PB0-(u32)&PA0);i+=1,ib-=(u32)((u32)&PB0-(u32)&PA0));
	
	return (GPIOPin)((i<<4)+(ib>>2));
}
