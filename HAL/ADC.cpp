#include "ADC.h"

inline u16 __reserved_SADC::isFlagOn(const ADC_SRFlag conf) const
{
	return SR&conf;
}

inline void __reserved_SADC::clearFlag(const ADC_SRFlag conf)
{
	SR&=~conf;
}

inline void __reserved_SADC::enableInterrupt(const ADC_IntrConf conf)
{
	CR1|=conf;
}

inline void __reserved_SADC::disableInterrupt(const ADC_IntrConf conf)
{
	CR1&=~conf;
}

void __reserved_SADC::selectExternalTriggerForInjectedChannels(const ADC1_2InjectTrig conf)
{
	RST_REG(CR2,12,0x7,conf);
}

inline void __reserved_SADC::enableDMA()
{
	CR2|=(1<<8);
}

inline void __reserved_SADC::disableDMA()
{
	CR2&=~(1<<8);
}

void __reserved_SADC::calibrate()
{
	BSETB_REG(CR2,3);//reset calibration
	while(BGET_REG(CR2,3));//wait for the end of reset
	BSETB_REG(CR2,2);//calibrate
}

void __reserved_SADC::setDiscontinuousModeChannelCount(const u16 count)
{
	RST_REG(CR1,13,0x7,count);
}

void __reserved_SADC::setDualMode(u16 mode)
{
	RST_REG(CR1,16,0xf,mode);
}

void __reserved_SADC::selectAnalogWatchDogChannel(u16 chx)
{
	RST_REG(CR1,0,0x1f,chx);
}
