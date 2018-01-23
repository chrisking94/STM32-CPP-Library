#include "NVIC.h"
/**
  ******************************************************************************
  * @file    NVIC.cpp
  * @author  ChrisKing
  * @version V1.0.0
  * @date    2017/07/07 13:09
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

void __reserved_SNVIC::enable(IRQn_Type IRQn)
{
	ISER[((uint32_t)(IRQn) >> 5)] = (1 << ((uint32_t)(IRQn) & 0x1F));
}

void __reserved_SNVIC::disable(IRQn_Type IRQn)
{
	ICER[((uint32_t)(IRQn) >> 5)] = (1 << ((uint32_t)(IRQn) & 0x1F));
}

//!如果两个中断的响应优先级和响应优先级都是一样的话，则看哪个中断先发生就先执行。
//!高优先级的抢占优先级是可以打断正在进行的低抢占优先级中断的。而抢占优先级相同的
//!中断，高优先级的响应优先级不可以打断低响应优先级的中断。

void __reserved_SNVIC::configPriority(IRQn_Type IRQn,u8 PreemptionPriority,u8 SubPriority)
{
	u32 tmp,grp;

	grp=((SCB->AIRCR>>8)&0x7)-3;
	u8 IPRADDR = IRQn/4;//得到组（每组4个）地址x
	u8 IPROFFSET = IRQn%4;//得到组内偏移
	IPROFFSET=IPROFFSET*8+4;//得到偏移确切位置（8位一个Channel，但只使用高4bit）
	//!优先级设置共有4位，高位(共x位)为抢占优先级，低位（y位）为响应优先级，x y与SCB->AIRCR相关，参考前面说明
	tmp=((PreemptionPriority)<<grp)&0xf;//设置抢占优先级
	tmp|=SubPriority&(0x0f>>(4-grp));//设置响应优先级
	//!IP：中断优先级控制的寄存器组（Interrupt Priority Registers）
	IP[IPRADDR]|=tmp<<IPROFFSET;//设置响应优先级和抢断优先级 
}

