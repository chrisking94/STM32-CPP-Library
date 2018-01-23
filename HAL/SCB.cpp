#include "SCB.h"
/**
  ******************************************************************************
  * @file    SCB.cpp
  * @author  ChrisKing
  * @version V1.0.0
  * @date    2017/07/07 13:30
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

void __reserved_SSCB::setNVICPriorityGroup(const NVICPriorityGroup group)
{
	u32 tmp,tmp1;

	tmp1=group;//取后三位
	tmp1<<=8;
	tmp=SCB->AIRCR;//读取先前的设置
	//!SCB->AIRCR：16位寄存器
	tmp&=0x0000F8FF;//清空先前分组
	//!SCB->AIRCR 的修改需要通过在高16 位写入0X05FA 这个密钥才能修改的
	tmp|=0x05FA0000;//写入钥匙
	tmp|=tmp1;
	SCB->AIRCR=tmp;
}

void __reserved_SSCB::setNVICVetorTable(NVICVectorTable tab,u32 offset/*=0*/)
{
	SCB->VTOR = tab | (offset & (uint32_t)0x1FFFFF80);
}
