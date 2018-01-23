#pragma once
#include "GPIO.h"
#include "stdint-gcc.h"
/**
  ******************************************************************************
  * @file    GPIOPin.h
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
typedef enum
{
	_PA0,_PA1,_PA2,_PA3,_PA4,_PA5,_PA6,_PA7,_PA8,_PA9,_PA10,_PA11,_PA12,_PA13,_PA14,_PA15,
	_PB0,_PB1,_PB2,_PB3,_PB4,_PB5,_PB6,_PB7,_PB8,_PB9,_PB10,_PB11,_PB12,_PB13,_PB14,_PB15,
	_PC0,_PC1,_PC2,_PC3,_PC4,_PC5,_PC6,_PC7,_PC8,_PC9,_PC10,_PC11,_PC12,_PC13,_PC14,_PC15,
	_PD0,_PD1,_PD2,_PD3,_PD4,_PD5,_PD6,_PD7,_PD8,_PD9,_PD10,_PD11,_PD12,_PD13,_PD14,_PD15,
	_PE0,_PE1,_PE2,_PE3,_PE4,_PE5,_PE6,_PE7,_PE8,_PE9,_PE10,_PE11,_PE12,_PE13,_PE14,_PE15,
	_PF0,_PF1,_PF2,_PF3,_PF4,_PF5,_PF6,_PF7,_PF8,_PF9,_PF10,_PF11,_PF12,_PF13,_PF14,_PF15,
	_PG0,_PG1,_PG2,_PG3,_PG4,_PG5,_PG6,_PG7,_PG8,_PG9,_PG10,_PG11,_PG12,_PG13,_PG14,_PG15,
}GPIOPin;

struct __reserved_SGPIOPin
{
public:
	void pinMod(GPIOMod mod,GPIOFreq freq=_50MHz);/*use like this: PA0.pinMode(_OGPP); */
	operator uint32_t() const;/*use like this: int a=PA0; */
	uint32_t operator=(const uint32_t voltage);/*use like this: PA0=1; */
	GPIOPin pinNum() const;/*calculate pin number*/
private:
	volatile uint32_t	IBand;//输入位带
	volatile uint32_t	__Offset[31];//I起始地址偏移128个字节到O
	volatile uint32_t	OBand;//输出位带
};

#define __GPIO_IDR(pin)		(GPIOA_BASE+(pin>>4)*0x0400+8)//pin:0,1,..,16,...对应PA0,PA1,...PB0,...，计算IDR地址
#define __PA0IBAND(pin)		(((__GPIO_IDR(pin)) & 0xF0000000)+0x2000000+(((__GPIO_IDR(pin)) &0xFFFFF)<<5)+((pin%16)<<2))
//All
#define P(pin)				(*(__reserved_SGPIOPin*)__PA0IBAND(((uint32_t)pin)))
//PA
#define PA(pin)				P(pin)
#define PA0					PA(0)
#define PA1					PA(1)
#define PA2					PA(2)
#define PA3					PA(3)
#define PA4					PA(4)
#define PA5					PA(5)
#define PA6					PA(6)
#define PA7					PA(7)
#define PA8					PA(8)
#define PA9					PA(9)
#define PA10				PA(10)
#define PA11				PA(11)
#define PA12				PA(12)
#define PA13				PA(13)
#define PA14				PA(14)
#define PA15				PA(15)
//PB
#define PB(pin)				P(pin+0x10)
#define PB0					PB(0)
#define PB1					PB(1)
#define PB2					PB(2)
#define PB3					PB(3)
#define PB4					PB(4)
#define PB5					PB(5)
#define PB6					PB(6)
#define PB7					PB(7)
#define PB8					PB(8)
#define PB9					PB(9)
#define PB10				PB(10)
#define PB11				PB(11)
#define PB12				PB(12)
#define PB13				PB(13)
#define PB14				PB(14)
#define PB15				PB(15)
//PC
#define PC(pin)				P(pin+0x20)
#define PC0					PC(0)
#define PC1					PC(1)
#define PC2					PC(2)
#define PC3					PC(3)
#define PC4					PC(4)
#define PC5					PC(5)
#define PC6					PC(6)
#define PC7					PC(7)
#define PC8					PC(8)
#define PC9					PC(9)
#define PC10				PC(10)
#define PC11				PC(11)
#define PC12				PC(12)
#define PC13				PC(13)
#define PC14				PC(14)
#define PC15				PC(15)
//PD
#define PD(pin)				P(pin+0x30)
#define PD0					PD(0)
#define PD1					PD(1)
#define PD2					PD(2)
#define PD3					PD(3)
#define PD4					PD(4)
#define PD5					PD(5)
#define PD6					PD(6)
#define PD7					PD(7)
#define PD8					PD(8)
#define PD9					PD(9)
#define PD10				PD(10)
#define PD11				PD(11)
#define PD12				PD(12)
#define PD13				PD(13)
#define PD14				PD(14)
#define PD15				PD(15)
//PE
#define PE(pin)				P(pin+0x40)
#define PE0					PE(0)
#define PE1					PE(1)
#define PE2					PE(2)
#define PE3					PE(3)
#define PE4					PE(4)
#define PE5					PE(5)
#define PE6					PE(6)
#define PE7					PE(7)
#define PE8					PE(8)
#define PE9					PE(9)
#define PE10				PE(10)
#define PE11				PE(11)
#define PE12				PE(12)
#define PE13				PE(13)
#define PE14				PE(14)
#define PE15				PE(15)
//PF
#define PF(pin)				P(pin+0x50)
#define PF0					PF(0)
#define PF1					PF(1)
#define PF2					PF(2)
#define PF3					PF(3)
#define PF4					PF(4)
#define PF5					PF(5)
#define PF6					PF(6)
#define PF7					PF(7)
#define PF8					PF(8)
#define PF9					PF(9)
#define PF10				PF(10)
#define PF11				PF(11)
#define PF12				PF(12)
#define PF13				PF(13)
#define PF14				PF(14)
#define PF15				PF(15)
//PG
#define PG(pin)				P(pin+0x60)
#define PG0					PG(0)
#define PG1					PG(1)
#define PG2					PG(2)
#define PG3					PG(3)
#define PG4					PG(4)
#define PG5					PG(5)
#define PG6					PG(6)
#define PG7					PG(7)
#define PG8					PG(8)
#define PG9					PG(9)
#define PG10				PG(10)
#define PG11				PG(11)
#define PG12				PG(12)
#define PG13				PG(13)
#define PG14				PG(14)
#define PG15				PG(15)




inline __reserved_SGPIOPin::operator uint32_t() const
{
	return IBand;
}

inline uint32_t __reserved_SGPIOPin::operator=(const uint32_t voltage)
{
	return OBand=voltage;
}
