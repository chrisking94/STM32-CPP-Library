#pragma once
#include "Common.h"
/**
******************************************************************************
* @file    SPI.h
* @author  ChrisKing
* @version V1.0.0
* @date    2017/07/07 13:32
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
struct __reserved_SSPI
{
public:
	typedef enum
	{
		_SamplingFrom2ndClock	=0x0001,/*从第2个时钟边缘开始采样，否则第1个*/
		_HighSckWhileIdle		=0x0002,/*空闲时Sck高电平，否则低电平*/
		_MasterMode				=0x0004,/*主机模式，否则从机模式*/
		_EnableSPI				=0x0040,/*开启SPI*/
		_LSBFirst				=0x0080,/*先发送LSB，否则先MSB*/
		_InternalSlaveSelect	=0x0100,/*内部从设备选择，SSM=1时该位决定NSS脚电平*/
		_SoftwareSlaveManagement=0x0200,/*启用软件从设备管理*/
		_ReceiveOnly			=0x0400,/*仅接收*/
		_16BitDataFrame			=0x0800,/*16位数据帧，否则8位。只能在SPEnable=0时才能写该位，否则出错*/
		_TransmitCRCNext		=0x1000,/*下一个数据为CRC校验，在DR中写入最后一个值后写入该位发送CRC校验*/
		_CRCEnable				=0x2000,/*启动CRC校验，条件：SPE=0时*/
		_EnableOutput			=0x4000,/*使能输出（只发模式），否则禁止输出（只收模式），配合SingleLine使用*/
		_SingleLine				=0x8000,/*单线双向，否则双线双向。单线：主机MOSI，从机MISO*/
	}SPICR1Setting;
	typedef	enum
	{
		_EnRxDMA				=0x0001,/*启动接收DMA,RXNE=1时发出DMA请求*/
		_EnTxDMA				=0x0002,/*启用发送DMA，TXE=1时发出DMA请求*/
		_EnSSOutput				=0x0004,/*开启主模式下SS输出*/
		_EnErrorInterrupt		=0x0020,/*错误中断（CRCERR，OVR，MODF产生时）*/
		_EnRxBuffNotEmptyIntr	=0x0040,/*接收缓冲区非空中断*/
		_EnTxBuffEmptyIntr		=0x0080,/*发送缓冲区空使能*/
	}SPICR2Setting;
public:
	char	sendChar(char ch);/*write a char，主机模式，半双工*/
	u16		sendWord(u16 wd);
	u16		isBusy() const;
	void	enableDMA(BOOL bEnable);
	void	set(SPICR1Setting	st);	
	void	reset(SPICR1Setting st); 
	void	set(SPICR2Setting	st);	
	void	reset(SPICR2Setting st); 
	void	enable();
	void	disable();
	void	setMasterMode(BOOL bMaster);/*1.设置为主机,0.设置为从机*/
	void	setBaudrateDiv(u16 div);/*波特率分频，BDR=fpclk/div*/
private:
	__IO uint16_t CR1;
	uint16_t  RESERVED0;
	__IO uint16_t CR2;
	uint16_t  RESERVED1;
	__IO uint16_t SR;
	uint16_t  RESERVED2;
	__IO uint16_t DR;
	uint16_t  RESERVED3;
	__IO uint16_t CRCPR;
	uint16_t  RESERVED4;
	__IO uint16_t RXCRCR;
	uint16_t  RESERVED5;
	__IO uint16_t TXCRCR;
	uint16_t  RESERVED6;
	__IO uint16_t I2SCFGR;
	uint16_t  RESERVED7;
	__IO uint16_t I2SPR;
	uint16_t  RESERVED8; 
};

#define spi1	(*(__reserved_SSPI*)SPI1)
#define spi2	(*(__reserved_SSPI*)SPI2)
#define spi3	(*(__reserved_SSPI*)SPI3)

