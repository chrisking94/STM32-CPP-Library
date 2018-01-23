#pragma once
#include "Common.h"

class __reserved_SADC
{
public:
	typedef enum
	{
		_Flag_AnalogWatchDog					=0x0001,
		_Flag_EndOfConversion					=0x0002,
		_Flag_InjectedChannelEndOfConversion	=0x0004,
		_Flag_InjectedChannelStart				=0x0008,
		_Flag_RegularChannelStart				=0x0010,
	}ADC_SRFlag;
	typedef enum
	{
		_Intr_EndOfConversion		=0x0020,
		_Intr_AnalogWatchDog		=0x0040,
		_Intr_InjectedChannels		=0x0080,
	}ADC_IntrConf;
	typedef enum
	{
		_Mode_Scan							=0x00000010,
		_WatchDogOnSingleChannelInScanMode	=0x00000020,/*1:on single channel 0:the dog on all channel*/
		_En_AutomaticInjectedGroupConversion=0x00000040,
		_Mode_DiscontinuousOnRegularChannels=0x00000080,
		_Mode_DiscontinuousOnInjectedChannels=0x00000100,
		_En_AnalogWatchdogOnInjectedChannels=0x00400000,
		_En_AnalogWatchdogOnRegularChannels	=0x00800000,
	}ADC_CR1Conf;
	typedef enum
	{
		_On_ADConverter				=0x0001,
		_Mode_ContinuousConversion	=0x0002,
		_DataAlignLeft				=0x0080,
	};
	typedef enum
	{
		_TrigI_T1TRGO,
		_TrigI_T1CC4,
		_TrigI_T2TRGO,
		_TrigI_T2CC1,
		_TrigI_T3CC4,
		_TrigI_T4TRGO,
		_TrigI_EXTI15OrTIM8CC4,
		_TrigI_JSWSTART,
	}ADC1_2InjectTrig;
public:
	u16		isFlagOn(const ADC_SRFlag conf) const;
	void	clearFlag(const ADC_SRFlag conf);
	void	enableInterrupt(const ADC_IntrConf conf);
	void	disableInterrupt(const ADC_IntrConf conf);
	void	selectExternalTriggerForInjectedChannels(const ADC1_2InjectTrig conf);
	void	enableDMA();
	void	disableDMA();
	void	calibrate();/*start calibration,cleared by hardware after calibration*/
	void	setDiscontinuousModeChannelCount(const u16 count);
	void	setDualMode(u16 mode);
	void	selectAnalogWatchDogChannel(u16 chx);/*chx[0~17]*/
private:
	__IO uint32_t SR;
	__IO uint32_t CR1;
	__IO uint32_t CR2;
	__IO uint32_t SMPR1;
	__IO uint32_t SMPR2;
	__IO uint32_t JOFR1;
	__IO uint32_t JOFR2;
	__IO uint32_t JOFR3;
	__IO uint32_t JOFR4;
	__IO uint32_t HTR;
	__IO uint32_t LTR;
	__IO uint32_t SQR1;
	__IO uint32_t SQR2;
	__IO uint32_t SQR3;
	__IO uint32_t JSQR;
	__IO uint32_t JDR1;
	__IO uint32_t JDR2;
	__IO uint32_t JDR3;
	__IO uint32_t JDR4;
	__IO uint32_t DR;
};

#define adc1	(*(__reserved_SADC*)ADC1)
#define adc2	(*(__reserved_SADC*)ADC2)
#define adc3	(*(__reserved_SADC*)ADC3)

