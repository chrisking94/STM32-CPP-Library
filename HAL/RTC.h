#pragma once
#include "Common.h"
/**
  ******************************************************************************
  * @file    RTC.h
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
struct __reserved_CRTC
{
public:
	typedef enum
	{
		_SecondInterruptEnable		=0x0001
		,_AlarmInterruptEnable		=0x0002
		,_OverflowInterruptEnable	=0x0004
	}CRHConf;
	typedef enum
	{
		_SecondFlag					=0x0001,
		_AlarmFlag					=0x0002,
		_OverflowFlag				=0x0004,
		_RegistersSynchronizedFlag	=0x0008,
		_ConfigurationFlag			=0x0010,
		_RTCOperationOFF			=0x0020,
	}CRLConf;
public:
		void	set(CRHConf	conf);
		void	set(CRLConf	conf);
		void	setPrescalerReloadValue(u32	val);/*20 bit*/
		u32		getClockDivider(u32	val);/*获得预分频计数器的当前值*/
		void	setCounter(u32	val);/*32bit计数寄存器*/
		u32		getCounter(u32 val);/*32bit计数寄存器*/
		void	setAlarm(u32 val);/*32bit*/
private:
	__IO uint16_t CRH;
	uint16_t  RESERVED0;
	__IO uint16_t CRL;
	uint16_t  RESERVED1;
	__IO uint16_t PRLH;
	uint16_t  RESERVED2;
	__IO uint16_t PRLL;
	uint16_t  RESERVED3;
	__IO uint16_t DIVH;
	uint16_t  RESERVED4;
	__IO uint16_t DIVL;
	uint16_t  RESERVED5;
	__IO uint16_t CNTH;
	uint16_t  RESERVED6;
	__IO uint16_t CNTL;
	uint16_t  RESERVED7;
	__IO uint16_t ALRH;
	uint16_t  RESERVED8;
	__IO uint16_t ALRL;
	uint16_t  RESERVED9;
};

#define	rtc	(*(_reserved_CRTC*)RTC)




inline void __reserved_CRTC::set(CRHConf conf)
{
	CRH|=conf;
}

inline void __reserved_CRTC::set(CRLConf conf)
{
	CRL|=conf;
}
