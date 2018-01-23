#pragma once
#include "Common.h"
/**
  ******************************************************************************
  * @file    RCC.h
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
struct __reserved_SRCC
{
public:
	typedef enum
	{
		//AHB
		_DMA1=       ((uint32_t)0x00000001),
		_DMA2=       ((uint32_t)0x00000002),
		_SRAM=       ((uint32_t)0x00000004),
		_FLITF=      ((uint32_t)0x00000010),
		_CRC  =		 ((uint32_t)0x00000040),

#ifndef STM32F10X_CL
		_FSMC=      ((uint32_t)0x00000100),
		_SDIO=      ((uint32_t)0x00000400),

#else
		_OTG_FS=    ((uint32_t)0x00001000),
		_ETH_MAC=   ((uint32_t)0x00004000),
		_ETH_MAC_Tx=((uint32_t)0x00008000),
		_ETH_MAC_Rx=((uint32_t)0x00010000),

#endif /* STM32F10X_CL */
	}AHBPeriph;
	typedef enum
	{
		//APB2
		_AFIO=      ((uint32_t)0x00000001),
		_GPIOA=     ((uint32_t)0x00000004),
		_GPIOB=     ((uint32_t)0x00000008),
		_GPIOC=     ((uint32_t)0x00000010),
		_GPIOD=     ((uint32_t)0x00000020),
		_GPIOE=     ((uint32_t)0x00000040),
		_GPIOF=     ((uint32_t)0x00000080),
		_GPIOG=     ((uint32_t)0x00000100),
		_ADC1=      ((uint32_t)0x00000200),
		_ADC2=      ((uint32_t)0x00000400),
		_TIM1=      ((uint32_t)0x00000800),
		_SPI1=      ((uint32_t)0x00001000),
		_TIM8=      ((uint32_t)0x00002000),
		_USART1=    ((uint32_t)0x00004000),
		_ADC3=      ((uint32_t)0x00008000),
		_TIM15=     ((uint32_t)0x00010000),
		_TIM16=     ((uint32_t)0x00020000),
		_TIM17=     ((uint32_t)0x00040000),
		_TIM9=      ((uint32_t)0x00080000),
		_TIM10=     ((uint32_t)0x00100000),
		_TIM11=     ((uint32_t)0x00200000),
	}APB2Periph;
	typedef enum
	{
		//APB1
		_TIM2=      ((uint32_t)0x00000001),
		_TIM3=      ((uint32_t)0x00000002),
		_TIM4=      ((uint32_t)0x00000004),
		_TIM5=      ((uint32_t)0x00000008),
		_TIM6=      ((uint32_t)0x00000010),
		_TIM7=      ((uint32_t)0x00000020),
		_TIM12=     ((uint32_t)0x00000040),
		_TIM13=     ((uint32_t)0x00000080),
		_TIM14=     ((uint32_t)0x00000100),
		_WWDG=      ((uint32_t)0x00000800),
		_SPI2=      ((uint32_t)0x00004000),
		_SPI3=      ((uint32_t)0x00008000),
		_USART2=    ((uint32_t)0x00020000),
		_USART3=    ((uint32_t)0x00040000),
		_UART4=     ((uint32_t)0x00080000),
		_UART5=     ((uint32_t)0x00100000),
		_I2C1=      ((uint32_t)0x00200000),
		_I2C2=      ((uint32_t)0x00400000),
		_USB=       ((uint32_t)0x00800000),
		_CAN1=      ((uint32_t)0x02000000),
		_CAN2=      ((uint32_t)0x04000000),
		_BKP=       ((uint32_t)0x08000000),
		_PWR=       ((uint32_t)0x10000000),
		_DAC=       ((uint32_t)0x20000000),
		_CEC=       ((uint32_t)0x40000000),
	}APB1Periph;
	typedef enum
	{
		_InternalHighSpeedClockEnable		=0x00000001,
		_InternalHighSpeedClockReadFlag		=0x00000002,
		_ExternalHighSpeedClockEnable		=0x00010000,
		_ExternalHighSpeedClockReadFlag		=0x00020000,
		_ExternalHighSpeedClockBypass		=0x00040000,
		_ClockSecurityEnable				=0x00080000,
		_PLLEnable							=0x01000000,
		_PLLClockReadyFlag					=0x02000000
	}CRConf;
	typedef enum
	{
		_SysClkHSI,/*High-Speed Internal Clock（高速内部时钟）*/
		_SysClkHSE,/*High-Speed External Clock（高速外部时钟）*/
		_SysClkPLL,/*The internal PLL can be used to multiply the HSI RC output or HSE crystal output clock frequency. */
	}SystemClock;
	typedef enum
	{
		_AHB1Prescaler		=0,/*不分频*/
		_AHB2Prescaler		=0x8,/*2分频*/
		_AHB4Prescaler			,/*4分频*/
		_AHB8Prescaler			,/*8分频*/
		_AHB16Prescaler		,/*16分频*/
		_AHB64Prescaler		,/*64分频*/
		_AHB128Prescaler		,/*128分频*/
		_AHB256Prescaler		,/*256分频*/
		_AHB512Prescaler		,/*512分频*/
	}AHBPrescaler;
	typedef enum
	{
		_APB1Prescaler	=0,/*不分频*/
		_APB2Prescaler	=0x4,/*2分频*/
		_APB4Prescaler		,/*2分频*/
		_APB8Prescaler		,/*2分频*/
		_APB16Prescaler	,/*2分频*/
	}APBPrescaler;
	typedef enum
	{
		_2Prescaler,
		_4Prescaler,
		_6Prescaler,
		_8Prescaler,
	}ADCPrescaler;
	typedef enum
	{
		_PLLClkHSI,
		_PLLClkHSE,
	}PLLClockSource;
	typedef	enum
	{
		_HSE1Prescaler,/*不分频*/
		_HSE2Prescaler,/*2分频*/
	}HSEDivider;
	typedef enum
	{
		_USB1_5Prescaler,/*1.5倍分频*/
		_USB1Prescaler,/*不分频*/
	}USBPrescaler;
public:
	void enableClock(AHBPeriph	periph);
	void enableClock(APB2Periph periph);
	void enableClock(APB1Periph periph);
	void disableClock(AHBPeriph	periph);
	void disableClock(APB2Periph periph);
	void disableClock(APB1Periph periph);
	void resetPeriph(APB2Periph periph);
	void resetPeriph(APB1Periph periph);
	void set(CRConf	conf);
	void reset(CRConf conf);
	void switchSystemClock(SystemClock conf);/*切换系统时钟*/
	void setAHBPrescaler(AHBPrescaler conf);/*设置AHB时钟分频*/
	void setAPB1Prescaler(APBPrescaler conf);/*设置APB1时钟分频*/
	void setAPB2Prescaler(APBPrescaler conf);/*设置APB2时钟分频*/
	void setADCPrescaler(ADCPrescaler conf);/*设置ADC时钟分频*/
	void setPLLEntryClockSource(PLLClockSource	conf);/*设置PLL时钟源*/
	void setHSEDividerForPLLEntry(HSEDivider	conf);/*设置HSE作为PLL输入时的分频系数*/
	void setPLLMultiplicationFactor(u16 conf);/*[1~16]，设置PLL倍频系数*/
	void setUSBPrescaler(USBPrescaler conf);/*设置USB时钟分频*/
private:
	__IO uint32_t CR;
	__IO uint32_t CFGR;
	__IO uint32_t CIR;
	__IO uint32_t APB2RSTR;
	__IO uint32_t APB1RSTR;
	__IO uint32_t AHBENR;
	__IO uint32_t APB2ENR;
	__IO uint32_t APB1ENR;
	__IO uint32_t BDCR;
	__IO uint32_t CSR;

#ifdef STM32F10X_CL  
	__IO uint32_t AHBRSTR;
	__IO uint32_t CFGR2;
#endif /* STM32F10X_CL */ 

#if defined (STM32F10X_LD_VL) || defined (STM32F10X_MD_VL) || defined (STM32F10X_HD_VL)   
	uint32_t RESERVED0;
	__IO uint32_t CFGR2;
#endif /* STM32F10X_LD_VL || STM32F10X_MD_VL || STM32F10X_HD_VL */
};

#define rcc		(*(__reserved_SRCC*)RCC)


inline void __reserved_SRCC::enableClock(AHBPeriph periph)
{
	AHBENR|=periph;
}

inline void __reserved_SRCC::enableClock(APB2Periph periph)
{
	APB2ENR|=periph;
}

inline void __reserved_SRCC::enableClock(APB1Periph periph)
{
	APB1ENR|=periph;
}

inline void __reserved_SRCC::disableClock(AHBPeriph periph)
{
	AHBENR&=~periph;
}

inline void __reserved_SRCC::disableClock(APB2Periph periph)
{
	APB2ENR&=~periph;
}

inline void __reserved_SRCC::disableClock(APB1Periph periph)
{
	APB1ENR&=~periph;
}

inline void __reserved_SRCC::set(CRConf conf)
{
	CR|=conf;
}

inline void __reserved_SRCC::reset(CRConf conf)
{
	CR&=~conf;
}

inline void __reserved_SRCC::switchSystemClock(SystemClock conf)
{
	RST_REG(CFGR,0,0x3,conf);
}

inline void __reserved_SRCC::setAHBPrescaler(AHBPrescaler conf)
{
	RST_REG(CFGR,4,0xf,conf);
}

inline void __reserved_SRCC::setAPB1Prescaler(APBPrescaler conf)
{
	RST_REG(CFGR,8,0x7,conf);
}

inline void __reserved_SRCC::setAPB2Prescaler(APBPrescaler conf)
{
	RST_REG(CFGR,11,0x7,conf);
}

inline void __reserved_SRCC::setADCPrescaler(ADCPrescaler conf)
{
	RST_REG(CFGR,14,0x3,conf);
}

inline void __reserved_SRCC::setPLLEntryClockSource(PLLClockSource conf)
{
	RST_REG(CFGR,16,0x1,conf);
}

inline void __reserved_SRCC::setHSEDividerForPLLEntry(HSEDivider conf)
{
	RST_REG(CFGR,17,0x1,conf);
}

inline void __reserved_SRCC::setPLLMultiplicationFactor(u16 conf)
{
	RST_REG(CFGR,18,0xf,conf);
}

inline void __reserved_SRCC::setUSBPrescaler(USBPrescaler conf)
{
	RST_REG(CFGR,22,0x1,conf);
}
