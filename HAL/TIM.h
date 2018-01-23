#pragma once
#include "Common.h"
#include "RCC.h"

#define TIM_STOP(tim) (BCLR_REG(tim->CR1,0))
#define TIM_START(tim) (BCLR_REG(tim->CR1,0))
#define TIM_CUIF(tim) (BCLR_REG(tim->SR,0))
struct __reserved_STIM
{
public:
	typedef enum
	{
		_=0,
		_En_Counter				=0x0001,/*使能计数器*/
		_DE_Update				=0x0002,/*禁止UEV*/
		_En_UpdateRequestSource	=0x0004,
		_Mode_OnePulse			=0x0008,/*单脉冲模式*/
		_Direction_CountDown	=0x0010,/*向下计数，否则向上*/
		_En_AutoReloadPreload	=0x0080,/*ARR寄存器被装入缓冲器*/
	}CR1Conf;
	typedef enum
	{
		/*边沿对齐模式。计数器依据方向位(DIR)向上或向下计数*/
		_EdgeMode,
		/*中央对齐模式1。计数器交替地向上和向下计数。配置为输出的通道(TIMx_CCMRx寄存器
		中CCxS=00)的输出比较中断标志位，只在计数器向下计数时被设置。*/
		_CenterMode1,
		/*中央对齐模式2。计数器交替地向上和向下计数。配置为输出的通道(TIMx_CCMRx寄存器
		中CCxS=00)的输出比较中断标志位，只在计数器向上计数时被设置。*/
		_CenterMode2,
		/*中央对齐模式3。计数器交替地向上和向下计数。配置为输出的通道(TIMx_CCMRx寄存器
		中CCxS=00)的输出比较中断标志位，在计数器向上和向下计数时均被设置。*/
	}CenterAlignedMode;
	typedef enum
	{
		_1div,
		_2div,
		_4div,
	}ClockDivisionConf;
	typedef enum
	{
		_Intr_Update				=0x0001,/*更新中断*/
		_Intr_CaptureCompare1		=0x0002,/*捕获比较1中断*/
		_Intr_CaptureCompare2		=0x0004,/*捕获比较2中断*/
		_Intr_CaptureCompare3		=0x0008,/*捕获比较3中断*/
		_Intr_CaptureCompare4		=0x0010,/*捕获比较4中断*/
		_Intr_COM					=0x0020,/*COM中断*/
		_Intr_Trigger				=0x0040,/*触发中断*/
		_Intr_Break					=0x0080,/*刹车中断*/
	}TimerInterrupt;
	typedef enum
	{
		_DMA_Update					=0x0100,/*更新DMA*/
		_DMA_CaptureCompare1		=0x0200,/*捕获比较1DMA*/
		_DMA_CaptureCompare2		=0x0400,/*捕获比较2DMA*/
		_DMA_CaptureCompare3		=0x0800,/*捕获比较3DMA*/
		_DMA_CaptureCompare4		=0x1000,/*捕获比较4DMA*/
		_DMA_COM					=0x2000,/*COM DMA*/
		_DMA_Trigger				=0x4000,/*触发DMA*/
	}TimerDMA;
	typedef enum
	{
		_Flag_UpdateInterrupt		=0x0001,/*更新中断标记*/
		_Flag_CaptureCompare1		=0x0002,/*捕获比较1标记*/
		_Flag_CaptureCompare2		=0x0004,/*捕获比较2标记*/
		_Flag_CaptureCompare3		=0x0008,/*捕获比较3标记*/
		_Flag_CaptureCompare4		=0x0010,/*捕获比较4标记*/
		_Flag_COM					=0x0020,/*COM标记*/
		_Flag_Trigger				=0x0040,/*触发标记*/
		_Flag_Break					=0x0080,/*刹车标记*/
		_Flag_CCOvercapture1		=0x0020,/*捕获/比较1 重复捕获标记*/
		_Flag_CCOvercapture2		=0x0040,/*捕获/比较2 重复捕获标记*/
		_Flag_CCOvercapture3		=0x0080,/*捕获/比较3 重复捕获标记*/
		_Flag_CCOvercapture4		=0x0100,/*捕获/比较4 重复捕获标记*/
	}TimerFlag;
	typedef enum
	{
		_Event_Update				=0x0001,/*更新事件*/
		_Event_CaptureCompare1		=0x0002,/*捕获比较1事件*/
		_Event_CaptureCompare2		=0x0004,/*捕获比较2事件*/
		_Event_CaptureCompare3		=0x0008,/*捕获比较3事件*/
		_Event_CaptureCompare4		=0x0010,/*捕获比较4事件*/
		_Event_COM					=0x0020,/*COM事件*/
		_Event_Trigger				=0x0040,/*触发事件*/
		_Event_Break				=0x0080,/*刹车事件*/
	}TimerEvent;
public:
	__reserved_STIM();
	~__reserved_STIM(void);
	/*这2位定义在定时器时钟(CK_INT)频率、死区时间和由死区发生器与数字滤波器(ETR,TIx)所用
	的采样时钟之间的分频比例。*/
	void setDTSClockDivision(ClockDivisionConf conf);
	void setCenterAlignedMode(CenterAlignedMode conf);
	void set(CR1Conf conf);
	void reset(CR1Conf conf);
	void enableInterrupt(TimerInterrupt conf);
	void disableInterrupt(TimerInterrupt conf);
	void enableDMARequest(TimerDMA conf);
	void disableDMARequest(TimerDMA conf);
	void clearFlag(TimerFlag conf);
	u32	 isFlagOn(TimerFlag conf) const;/*测试标志是否置位*/
	void generateEvent(TimerEvent conf);/*软件触发事件*/
	void enable();
	void disable();
	void setTimeMs(uint16_t ms);
	void setTimeUs(uint16_t us);
	void setTime56Ns(uint16_t hns);//以56纳秒为单位
	void clearUpateInterruptFlag(){SR &= ~1;}

	//PWN
	void enablePWM(uint8_t chx);//使能chx[1~4]通道PWN输出
	void setCCR(const u8 chx,uint16_t val);
	void setLowVoltageValid(const u8 chx);
	void setHighVoltageValid(const u8 chx);
private:
	__IO uint16_t CR1;
	uint16_t  RESERVED0;
	__IO uint16_t CR2;
	uint16_t  RESERVED1;
	__IO uint16_t SMCR;
	uint16_t  RESERVED2;
	__IO uint16_t DIER;
	uint16_t  RESERVED3;
	__IO uint16_t SR;
	uint16_t  RESERVED4;
	__IO uint16_t EGR;
	uint16_t  RESERVED5;
	__IO uint16_t CCMR1;
	uint16_t  RESERVED6;
	__IO uint16_t CCMR2;
	uint16_t  RESERVED7;
	__IO uint16_t CCER;
	uint16_t  RESERVED8;
	__IO uint16_t CNT;
	uint16_t  RESERVED9;
	__IO uint16_t PSC;
	uint16_t  RESERVED10;
	__IO uint16_t ARR;
	uint16_t  RESERVED11;
	__IO uint16_t RCR;
	uint16_t  RESERVED12;
	__IO uint16_t CCR1;
	uint16_t  RESERVED13;
	__IO uint16_t CCR2;
	uint16_t  RESERVED14;
	__IO uint16_t CCR3;
	uint16_t  RESERVED15;
	__IO uint16_t CCR4;
	uint16_t  RESERVED16;
	__IO uint16_t BDTR;
	uint16_t  RESERVED17;
	__IO uint16_t DCR;
	uint16_t  RESERVED18;
	__IO uint16_t DMAR;
	uint16_t  RESERVED19;
};

//Timer对象宏定义
#define tim1	(*(__reserved_STimer*)TIM1)
#define tim2	(*(__reserved_STimer*)TIM2)
#define tim3	(*(__reserved_STimer*)TIM3)
#define tim4	(*(__reserved_STimer*)TIM4)
#define tim5	(*(__reserved_STimer*)TIM5)
#define tim6	(*(__reserved_STimer*)TIM6)
#define tim7	(*(__reserved_STimer*)TIM7)
#define tim8	(*(__reserved_STimer*)TIM8)
#define tim9	(*(__reserved_STimer*)TIM9)
#define tim10	(*(__reserved_STimer*)TIM10)
#define tim11	(*(__reserved_STimer*)TIM11)
#define tim12	(*(__reserved_STimer*)TIM12)
#define tim13	(*(__reserved_STimer*)TIM13)
#define tim14	(*(__reserved_STimer*)TIM14)
#define tim15	(*(__reserved_STimer*)TIM15)
#define tim16	(*(__reserved_STimer*)TIM16)
#define tim17	(*(__reserved_STimer*)TIM17)




inline void __reserved_STIM::setDTSClockDivision(ClockDivisionConf conf)
{
	RST_REG(CR1,8,0x3,conf);
}

inline void __reserved_STIM::setCenterAlignedMode(CenterAlignedMode conf)
{
	RST_REG(CR1,5,0x3,conf);
}

inline void __reserved_STIM::set(CR1Conf conf)
{
	CR1|=conf;
}

inline void __reserved_STIM::reset(CR1Conf conf)
{
	CR1&=~conf;
}

inline void __reserved_STIM::enableInterrupt(TimerInterrupt conf)
{
	DIER|=conf;
}

inline void __reserved_STIM::disableInterrupt(TimerInterrupt conf)
{
	DIER&=~conf;
}

inline void __reserved_STIM::enableDMARequest(TimerDMA conf)
{
	DIER|=conf;
}

inline void __reserved_STIM::disableDMARequest(TimerDMA conf)
{
	DIER&=~conf;
}

inline void __reserved_STIM::clearFlag(TimerFlag conf)
{
	SR&=~conf;
}

inline u32 __reserved_STIM::isFlagOn(TimerFlag conf) const
{
	return SR&conf;
}

inline void __reserved_STIM::generateEvent(TimerEvent conf)
{
	EGR|=conf;
}

inline void __reserved_STIM::enable()
{
	CR1|=_En_Counter;
}
