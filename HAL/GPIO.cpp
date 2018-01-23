#include "GPIO.h"
/**
  ******************************************************************************
  * @file    GPIO.cpp
  * @author  ChrisKing
  * @version V1.0.0
  * @date    2017/07/07 12:17
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

void __reserved_SGPIO::configPins(u8 *pins,GPIOMod mod,GPIOFreq freq/*=_50MHz*/)
{
	volatile uint32_t *pReg=&CRL;
	while(*pins != 0xff)
	{
		if(*pins>7)//CRH
		{
			pReg++;
			*pins-=8;
		}
		*pins<<=2;
		(*pReg) &= ~(((u32)0xf)<<*pins);
		(*pReg) |= ((u32)mod<<2|freq)<<*pins;
		pins++;
	}
}

