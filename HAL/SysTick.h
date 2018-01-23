#pragma once
#include "Common.h"
/**
  ******************************************************************************
  * @file    SysTick.h
  * @author  ChrisKing
  * @version V1.0.0
  * @date    2017/07/07 13:40
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
struct __reserved_SSysTick
{
public:
	typedef enum
	{
		_STCLK,/*外部时钟*/
		_FCLK,/*内核时钟*/
	}SysTickClockSrc;
public:
		void	start();				
		void	stop();				
		void	enableInterrupt(BOOL bEnable);	
		void	setClockSrc(SysTickClockSrc src=_FCLK);	
		u32		isTickOut()	const;	/*注：该位在读取寄存器后会自动清零*/
		void	setReloadVal(u32 val);	/*最大24bit*/	
		u32		val()	const;	
		u32		deltaTick()	const;	/*计算经过了多少个Tick*/
		void	reset(); /*同时会清除CountFlag，写VAL会使VAL清零*/	
		void	setMaxTickUs(u32 us);/*设置LOAD为x us*/
private:
	__IO uint32_t CTRL;                         /*!< Offset: 0x00  SysTick Control and Status Register */
	__IO uint32_t LOAD;                         /*!< Offset: 0x04  SysTick Reload Value Register       */
	__IO uint32_t VAL;                          /*!< Offset: 0x08  SysTick Current Value Register      */
	__I  uint32_t CALIB;                        /*!< Offset: 0x0C  SysTick Calibration Register        */
};

#define systick		(*(__reserved_SSysTick*)SysTick)




inline void __reserved_SSysTick::start()
{
	CTRL|=1;
}

inline void __reserved_SSysTick::stop()
{
	CTRL&=~1;
}

inline void __reserved_SSysTick::enableInterrupt(BOOL bEnable)
{
	BRST_REG(CTRL,1,bEnable);
}

inline void __reserved_SSysTick::setClockSrc(SysTickClockSrc src/*=_FCLK*/)
{
	BRST_REG(CTRL,2,src);
}

inline u32 __reserved_SSysTick::isTickOut() const
{
	return (CTRL>>16)&0x1;
}

inline void __reserved_SSysTick::setReloadVal(u32 val)
{
	LOAD=val;
}

inline u32 __reserved_SSysTick::val() const
{
	return VAL;
}

inline u32 __reserved_SSysTick::deltaTick() const
{
	return LOAD-VAL;
}

inline void __reserved_SSysTick::reset()
{
	VAL=0;
}

inline void __reserved_SSysTick::setMaxTickUs(u32 us)
{
	LOAD=36*us;
}
