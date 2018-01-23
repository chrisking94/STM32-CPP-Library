#pragma once
#include "Common.h"
/**
  ******************************************************************************
  * @file    GPIO.h
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
typedef enum
{
	_OGPP,/*Output General Push-Pull*/
	_OGOD,/*Output General Open-Drain*/
	_OMPP,/*Output Multiplex Push-Pull*/
	_OMOD,/*Output Multiplex Open-Drain*/
	_IA,/*Input Analog*/
	_IF,/*Input Float*/
	_IPDU,/*Input Pull Down or UP*/
}GPIOMod;

typedef enum
{
	_10MHz=1,
	_2MHz,
	_50MHz
}GPIOFreq;//最大输出速度

struct __reserved_SGPIO
{
public:
	operator	uint16_t() const;/*Use GPIO like this:u16 a=pa;*/
	uint16_t	operator=(uint16_t val);/*Use GPIO like this pa=0x00ff;*/
	void		configPins(u8 *pins,GPIOMod mod,GPIOFreq freq=_50MHz);/*配置一个数组的引脚[0~15]，且该数组必须以0xff结尾*/
private:
	__IO uint32_t CRL;
	__IO uint32_t CRH;
	__IO uint32_t IDR;
	__IO uint32_t ODR;
	__IO uint32_t BSRR;
	__IO uint32_t BRR;
	__IO uint32_t LCKR;
};

#define pa	(*(__reserved_SGPIO*)GPIOA)/*Object GPIOA*/
#define pb	(*(__reserved_SGPIO*)GPIOB)/*Object GPIOB*/
#define pc	(*(__reserved_SGPIO*)GPIOC)/*Object GPIOC*/
#define pd	(*(__reserved_SGPIO*)GPIOD)/*Object GPIOD*/
#define pe	(*(__reserved_SGPIO*)GPIOE)/*Object GPIOE*/
#define pf	(*(__reserved_SGPIO*)GPIOF)/*Object GPIOF*/
#define pg	(*(__reserved_SGPIO*)GPIOG)/*Object GPIOG*/




inline __reserved_SGPIO::operator uint16_t() const
{
	return IDR;
}

inline uint16_t __reserved_SGPIO::operator=(uint16_t val)
{
	return ODR=val;
}
