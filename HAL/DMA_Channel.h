#pragma once
#include "Common.h"
/**
  ******************************************************************************
  * @file    CDMA_Channel.h
  * @author  ChrisKing
  * @version V1.0.0
  * @date    2017/07/07 12:50
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
struct __reserved_SDMA_Channel
{
public:
	typedef enum
	{
		_ChannelEn						=0x0001,
		_Intr_TransferCompleteEn		=0x0002,
		_Intr_HalfTransferEn			=0x0004,
		_Intr_TransferErrorEn			=0x0008,
		_DataTransferDirection			=0x0010,/*set从存储器读，else从外设读*/
		_Mode_Circular					=0x0020,/*set循环操作*/
		_Mode_PeripheralIncrement		=0x0040,/*set外设增量模式*/
		_Mode_MemoryIncrement			=0x0080,/*存储器增量模式*/
		_Mode_MemoryToMemory			=0x4000,/*存储器到存储器模式*/
	}DMAChxCCRConf;
	typedef	enum
	{
		_8bit,
		_16bit,
		_32bit,
	}BitSize;
	typedef enum
	{
		_low,
		_medium,
		_high,
		_highest
	}Priority;
public:
	__reserved_SDMA_Channel(void);
	~__reserved_SDMA_Channel(void);
	
		void	set(DMAChxCCRConf conf);
		void	reset(DMAChxCCRConf conf);
		void	setPeripheralBitSize(BitSize	size);/*设置外设数据元宽度*/
		void	setMemoryBitSize(BitSize	size);/*设置内存数据元宽度*/
		void	setPriority(Priority	priority);
		void	setNumberOfDataToTransfer(u16	num);/*只能在通道关闭时设置*/
		void	setPeripheralAddress(void *addr);/*外设DR地址*/
		void	setMemoryAddress(void *addr);/*内存地址*/
		void	enable();
		void	disable();
private:
	__IO uint32_t CCR;
	__IO uint32_t CNDTR;
	__IO uint32_t CPAR;
	__IO uint32_t CMAR;
	uint32_t	RESERVED0;
};

/*DMA1*/
#define	dma1_channel1	(*(__reserved_SDMA_Channel*)DMA1_Channel1)
#define	dma1_channel2	(*(__reserved_SDMA_Channel*)DMA1_Channel2)
#define	dma1_channel3	(*(__reserved_SDMA_Channel*)DMA1_Channel3)
#define	dma1_channel4	(*(__reserved_SDMA_Channel*)DMA1_Channel4)
#define	dma1_channel5	(*(__reserved_SDMA_Channel*)DMA1_Channel5)
#define	dma1_channel6	(*(__reserved_SDMA_Channel*)DMA1_Channel6)
#define	dma1_channel7	(*(__reserved_SDMA_Channel*)DMA1_Channel7)

#define dmaAdc1		dma1_channel1
#define dmaSpi1Tx	dma1_channel3

/*DMA2*/
#define	dma2_channel1	(*(__reserved_SDMA_Channel*)DMA2_Channel1)
#define	dma2_channel2	(*(__reserved_SDMA_Channel*)DMA2_Channel2)
#define	dma2_channel3	(*(__reserved_SDMA_Channel*)DMA2_Channel3)
#define	dma2_channel4	(*(__reserved_SDMA_Channel*)DMA2_Channel4)
#define	dma2_channel5	(*(__reserved_SDMA_Channel*)DMA2_Channel5)




inline void __reserved_SDMA_Channel::set(DMAChxCCRConf conf)
{
	CCR|=conf;
}

inline void __reserved_SDMA_Channel::reset(DMAChxCCRConf conf)
{
	CCR&=~conf;
}

inline void __reserved_SDMA_Channel::setPeripheralBitSize(BitSize size)
{
	RST_REG(CCR,8,0x3,size);
}

inline void __reserved_SDMA_Channel::setMemoryBitSize(BitSize size)
{
	RST_REG(CCR,10,0x3,size);
}

inline void __reserved_SDMA_Channel::setPriority(Priority priority)
{
	RST_REG(CCR,12,0x3,priority);
}

inline void __reserved_SDMA_Channel::setNumberOfDataToTransfer(u16 num)
{
	CNDTR=num;
}

inline void __reserved_SDMA_Channel::setPeripheralAddress(void *addr)
{
	CPAR=(u32)addr;
}

inline void __reserved_SDMA_Channel::setMemoryAddress(void *addr)
{
	CMAR=(u32)addr;
}

inline void __reserved_SDMA_Channel::enable()
{
	CCR|=_ChannelEn;
}

inline void __reserved_SDMA_Channel::disable()
{
	CCR&=~_ChannelEn;
}
