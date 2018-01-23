#include "BaseLib.h"
#include "CommuDev.h"
#include "stdarg.h"
#include "GPIOPin.h"
#include "RCC.h"
#include "AFIO.h"
#include "SysTick.h"
#include "NVIC.h"
#include "SCB.h"

#define obeep	PA14


void BaseLib_init(void)
{
	//++++++++++++++++++++RCC时钟配置
    //!用到Remap时必须先打开AFIO时钟
	rcc.enableClock(__reserved_SRCC::_AFIO);
	rcc.enableClock(__reserved_SRCC::_TIM1);
	rcc.enableClock(__reserved_SRCC::_TIM2);
	rcc.enableClock(__reserved_SRCC::_TIM3);
	rcc.enableClock(__reserved_SRCC::_TIM4);
	rcc.enableClock(__reserved_SRCC::_USART1);
	rcc.enableClock(__reserved_SRCC::_USART2);
	rcc.enableClock(__reserved_SRCC::_I2C1);
	rcc.enableClock(__reserved_SRCC::_SPI1);
	rcc.enableClock(__reserved_SRCC::_GPIOA);
	rcc.enableClock(__reserved_SRCC::_GPIOB);
	rcc.enableClock(__reserved_SRCC::_GPIOC);
	rcc.enableClock(__reserved_SRCC::_ADC1);
	rcc.enableClock(__reserved_SRCC::_SPI1);
	rcc.enableClock(__reserved_SRCC::_DMA1);
	
	rcc.resetPeriph(__reserved_SRCC::_SPI1);
	rcc.resetPeriph(__reserved_SRCC::_SPI2);
	
	afio.configJTAG(__reserved_SAFIO::_NSWJ);

	//NVIC
	scb.setNVICPriorityGroup(__reserved_SSCB::_4Preemption_4Sub);
	scb.setNVICVetorTable(__reserved_SSCB::_Flash);
	nvic.configPriority(TIM3_IRQn,1,1);
	nvic.enable(TIM3_IRQn);
	nvic.configPriority(DMA1_Channel3_IRQn,0,0);
	nvic.enable(DMA1_Channel3_IRQn);
	nvic.configPriority(TIM1_UP_IRQn,1,3);
	nvic.enable(TIM1_UP_IRQn);
	nvic.configPriority(TIM4_IRQn,2,3);
	nvic.enable(TIM4_IRQn);
	nvic.configPriority(EXTI15_10_IRQn,2,3);
	nvic.enable(EXTI15_10_IRQn);

	led1.pinMod(_OGOD);
	led2.pinMod(_OGOD);
	obeep.pinMod(_OGOD);
    led1=1;	
	led2=1;
}

void delays(u32 s)
{
	while (s--)
	{
		delayms(1000);
	}
}

void delayms(u32 ms)
{
	if(ms==0) return;
	SysTick->VAL =0;//清空计数器
	SysTick->CTRL |=  5;//开启计数器
	while (ms--)
	{
		SysTick->LOAD=36000;//时间加载，倒数至0时，将被重装载的值(24bit)，内部时钟36MHz，36000/36MHz=1ms
		while (!(SysTick->CTRL&(1<<16)))//等待倒数至0，CountFlag，数到0时该位为1
		{
			//HighPriorityInterrupt();//延时时间长(ms级)时先执行高优先级任务，在MasterControl中实现
		}

	}
	SysTick->CTRL &= ~1;       //关闭计数器
}

void delayus(u32 us)
{
	if(us==0) return;

	SysTick->LOAD=(u32)us*36;//时间加载，倒数至0时，将被重装载的值(24bit)
	SysTick->VAL =0;           //清空计数器
	SysTick->CTRL |=  5;          //(bit0，en)开始倒数，(bit2)内部36MHz时钟频率
	while (!(SysTick->CTRL&(1<<16)));//等待倒数至0，CountFlag，数到0时该位为1
	SysTick->CTRL &= ~1;       //关闭计数器
}

void waitWhile(bool condition)
{
	while(condition)
	{
		//HighPriorityInterrupt();//先执行高优先级任务
	}
}

void beep(u16 time ,u16 interval)
{
	interval+=200;
	for (;time>0;time--)
	{
		obeep=!obeep;
		delayus(interval);
	}
	obeep=1;
}

void startTiming(void)
{
	systick.setReloadVal(0x00FFFFFF);//时间加载，倒数至0时，将被重装载的值(24bit)
	systick.reset();
	systick.start();
}

u32 readTimingms(void)
{
	u32 ms;
	systick.stop();
	ms=(SysTick->LOAD-SysTick->VAL)/72000;
	return ms;
}

u32 div_u32(u32 n1,u32 n2)
{

}

u8 bcd2dec(u8 bcd)
{

}

u8 dec2bcd(u8 dec)
{

}

/*********************************
注：用来输出引脚电平时要写成以下方式
printf("%d",(u32)PA15);
若写成
printf("%d",PA15);
输出的是PA15的指针
*********************************/
u32 printf(const char *format,...)
{
	va_list args;
	u32 ret;

	va_start(args,format);
	ret=printf(format,args);
	va_end(args);
	return ret;//返回数目，待修改
}

u32 printf(const char *format,va_list &args)
{
#define put(x) CCommuDev::pDev->sendChar(x)//CCommuDev::pDev->sendChar(x)

	u8 i=0,j,k;
	char n;
	int num;
	char *s,buf[10];

	while(*format)
	{
		if(*format=='%')
		{
			format++;
			n=0;
			while(*format>='0'&&*format<='9')
			{
				n*=10;
				n+=*format++-0x30;
			}
			switch(*format)
			{
			case 'o'://offset
				while(n--) put(' ');
				break;
			case 'c':
				put((char)va_arg(args,int));
				break;
			case 's':
				s=va_arg(args,char*);
				while(*s) put(*s++);
				break;
			case 'd':
				num=((int)va_arg(args,int));
				k=0;
				if (num < 0)
				{
					num = ~num;
					num += 1;
					put('-');
					j++;
				}
				do
				{
					buf[k++] = num % 10 + 0x30;
				}
				while (num /= 10);
				//输出多个0填补digits
				j = k;
				while (j < n)
				{
					put('0');
					j++;
				}
				while (k)
				{
					put(buf[--k]);
				}
				break;
			case '%':
				put('%');
				break;
			}
		}
		else
		{
			put(*format);
		}
		format++;
	}
	put(*format);

	return 1;//返回数目，待修改
#undef put
}

u32 scanf(const char *format,...)
{

}
