#pragma once
#include "Common.h"
/**
  ******************************************************************************
  * @file    SCB.h
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
struct __reserved_SSCB
{
public:
	typedef enum
	{
		_16Preemption_0Sub=3,/*0个抢占优先级，16个子优先级*/
		_8Preemption_2Sub,/*2个抢占优先级，8个子优先级*/
		_4Preemption_4Sub,/*3个抢占优先级，4个子优先级*/
		_2Preemption_8Sub,/*4个抢占优先级，2个子优先级*/
		_0Preemption_16Sub,/*16个抢占优先级，0个子优先级*/
	}NVICPriorityGroup;
	typedef enum
	{
		_RAM	=	((uint32_t)0x20000000),
		_Flash	=	((uint32_t)0x08000000)
	}NVICVectorTable;
public:
	__reserved_SSCB(void);
	~__reserved_SSCB(void);

	void setNVICPriorityGroup(const NVICPriorityGroup group);/*group 0~4*/
	void setNVICVetorTable(NVICVectorTable tab,u32 offset=0);
private:
	__I  uint32_t CPUID;                        /*!< Offset: 0x00  CPU ID Base Register                                  */
	__IO uint32_t ICSR;                         /*!< Offset: 0x04  Interrupt Control State Register                      */
	__IO uint32_t VTOR;                         /*!< Offset: 0x08  Vector Table Offset Register                          */
	__IO uint32_t AIRCR;                        /*!< Offset: 0x0C  Application Interrupt / Reset Control Register        */
	__IO uint32_t SCR;                          /*!< Offset: 0x10  System Control Register                               */
	__IO uint32_t CCR;                          /*!< Offset: 0x14  Configuration Control Register                        */
	__IO uint8_t  SHP[12];                      /*!< Offset: 0x18  System Handlers Priority Registers (4-7, 8-11, 12-15) */
	__IO uint32_t SHCSR;                        /*!< Offset: 0x24  System Handler Control and State Register             */
	__IO uint32_t CFSR;                         /*!< Offset: 0x28  Configurable Fault Status Register                    */
	__IO uint32_t HFSR;                         /*!< Offset: 0x2C  Hard Fault Status Register                            */
	__IO uint32_t DFSR;                         /*!< Offset: 0x30  Debug Fault Status Register                           */
	__IO uint32_t MMFAR;                        /*!< Offset: 0x34  Mem Manage Address Register                           */
	__IO uint32_t BFAR;                         /*!< Offset: 0x38  Bus Fault Address Register                            */
	__IO uint32_t AFSR;                         /*!< Offset: 0x3C  Auxiliary Fault Status Register                       */
	__I  uint32_t PFR[2];                       /*!< Offset: 0x40  Processor Feature Register                            */
	__I  uint32_t DFR;                          /*!< Offset: 0x48  Debug Feature Register                                */
	__I  uint32_t ADR;                          /*!< Offset: 0x4C  Auxiliary Feature Register                            */
	__I  uint32_t MMFR[4];                      /*!< Offset: 0x50  Memory Model Feature Register                         */
	__I  uint32_t ISAR[5];                      /*!< Offset: 0x60  ISA Feature Register                                  */
};

#define scb	(*(__reserved_SSCB*)SCB)
