#include "I2C.h"

#define I2C_SCL PBout(6)
#define I2C_SDA PBout(7)

#define I2C_DutyCycle2 0xBFFF//duty cycle
#define I2C_DutyCycle16_9 0x4000
#define I2C_DutyCycle I2C_DutyCycle2
#define I2C_PCLK 8000000
#define I2C_Speed 40000

__reserved_SI2C	oI2C1(I2C1);

__reserved_SI2C::__reserved_SI2C(I2C_TypeDef *I2C)
{
	/* I2C 配置 */
	CR2 = 0x0700|(u16)(I2C_PCLK/1000000);//16进制最后两位为频率，2~36MHz，8MHz（I2C_CR2）
	OAR1 |= 0x00;//7bit地址（I2C_OAR1）
	OAR2  = 0;
	CCR = calcCRRValue(I2C_Speed);//（I2C_CCR）
	TRISE = calcTRISEValue(I2C_Speed);//（I2C_TRISE）
	CR1 = 0x0401;//bit15为1则使I2C处于复位状态（I2C_CR1）
	/* 成员初始化 */
	I2CDevAddr=0x00;
	Mod=_W;
	nReadLen=0;
	m_cStat=_Standby;
	nWriteLen=0;
}

__reserved_SI2C::~__reserved_SI2C(void)
{
}

void __reserved_SI2C::setClockFrequency(const u8 freq)
{
	RST_REG(CR2,0,0x3f,freq);
}

inline void __reserved_SI2C::set(const I2CCR1Conf conf)
{
	CR1|=conf;
}

inline void __reserved_SI2C::set(const I2CCR2Conf conf)
{
	CR2|=conf;
}

inline void __reserved_SI2C::reset(const I2CCR1Conf conf)
{
	CR1&=~conf;
}

inline void __reserved_SI2C::reset(const I2CCR2Conf conf)
{
	CR2&=~conf;
}

void __reserved_SI2C::enableDMA()
{
	CR2|=_En_DMARequest;
}

void __reserved_SI2C::disableDMA()
{
	CR2&=~_En_DMARequest;
}

inline void __reserved_SI2C::enableInterrupt(const I2CIntrConf conf)
{
	CR2|=conf;
}

inline void __reserved_SI2C::disableInterrupt(const I2CIntrConf conf)
{
	CR2&=~conf;
}

void __reserved_SI2C::setInterfaceAddress(const u8 conf)
{
	RST_REG(OAR1,1,0x7f,conf);
}

inline u16 __reserved_SI2C::isFlagOn(const I2CSR1Flag conf) const
{
	return SR1&conf;
}

inline u16 __reserved_SI2C::isFlagOn(const I2CSR2Flag conf) const
{
	return SR2&conf;
}

inline void __reserved_SI2C::clearFlag(const I2CSR2Flag conf)
{
	SR2&=~conf;
}

inline void __reserved_SI2C::clearFlag(const I2CSR1Flag conf)
{
	SR1&=~conf;
}

void __reserved_SI2C::writeData(u8 addr,u8 dat)
{
	Mod = _W;
	nWriteLen=2;
	Buffer[0]=addr;
	Buffer[1]=dat;
	transfer();
	wait();
}

u8 __reserved_SI2C::readData(u8 addr)
{
	Mod=_R;
	nReadLen=1;
	nWriteLen=1;
	Buffer[0]=addr;
	transfer();
	wait();
	return Buffer[0];
}

void __reserved_SI2C::EV_IRQHandler()
{
	static u32 x;//!指针
    static u16 mod=_W;
	
    if (this->SR1 & 1<<0)//!已发送启始条件
    {
        this-> DR = this->I2CDevAddr | mod ;//!主模式：写从机地址
    }
    else if (this->SR1 & 1<<1)//!主模式：已发送从机地址☆
    {
        x=0;

        this->SR2;//!读SR2以清除SR1 bit1↑

        this->ack();//!启用ack

        if (mod==_W)//!模式为读的时候不进行这一步,即地址发送后直接进行读取
        {
            if (this->nWriteLen>0)
            {
                this-> DR = this->Buffer[x++];//!发送第一个字节
            }
        }
        else
        {
            if (this->nReadLen==1)
            {
                this->nack();//!关闭ack
				this->stop();//!当前为读模式，在接收完将要到来的唯一一个字节后产生停止位
            }
        }
    }
    else if (this-> SR1 & 1<<6)//!接收到新数据且还未被读取
    {
        if (this->nReadLen==1)
        {
			mod=_W;//!字节读取完毕，切换状态
        }
        else
        {
            if (x==this->nReadLen-2)
            {
                //!在倒数第二个字节收到后清除应答位，以保证最后一个字节后没有应答位（NAck）
				//!并在将要到来的最后一个字节后产生停止位
                this->nack();
				this->stop();
				nWriteLen=0;
				mod=_W;
            }
        }

        this->Buffer[x++] = this-> DR;//!将收入寄存器的值写入缓存数组
		
		if(x==this->nReadLen)
		{
			this->m_cStat = _Standby;
		}
    }
    else if (this-> SR1 & 1<<7)//!新数据将被发送且数据寄存器未写入新数据
    {
        if (x<this->nWriteLen)
        {
			if (this->Mod == _W)
			{
				/*if (!(pI2C-> SR1 & 1<<7))//!收到NAck
				{
					
				}*/
				if (x==this->nWriteLen-1)//!准备在最后一个字节写出后，停止总线
				{
					//I2C_nack();
					this->stop();
					nReadLen=0;
					nWriteLen=0;
				}
			}
            //!连续向总线写数据
            this-> DR = this->Buffer[x++];
        }
        else
        {
			if (this->Mod == _R)
			{
				//!读模式的写命令操作已经完成
				//!开始Read模式的读操作
				mod=_R;
				this->start();
			}
			else //!I2CT.imod == I2CWrite，在Stop信号产生后，可能不会执行到这里。可能出现阻塞
			{
				((__reserved_SI2C*)this)->m_cStat = _Standby;
			}
        }
    }
    else
    {
        //printStr(" SR1="   ,USART2);
       //printNum(pI2C->SR1   ,USART2);
        //printStr(" "   ,USART2);
    }
}

/******************
	错误中断
******************/
void __reserved_SI2C::ER_IRQHandler()
{
	m_cStat=_Error;
	if (SR1 & 1<<10)         //应答失败
	{
		SR1 &=~(1<<10);      //清除中断
	}
	if (SR1 & 1<<14)         //超时
	{
		SR1 &=~(1<<14);      //清除中断
	}
	if (SR1 & 1<<11)         //过载/欠载
	{
		SR1 &=~(1<<11);      //清除中断
	}
	if (SR1 & 1<<9)          //仲裁丢失
	{
		SR1 &=~(1<<9);       //清除中断
	}
	if (SR1 & 1<<8)          //总线出错
	{
		SR1 &=~(1<<8);       //清除中断
	}
}

/* Calc Maximum Rise Time for fast mode */
u16 __reserved_SI2C::calcTRISEValue(u32 ClockSpeed)
{
	u16 value;
	value=(u16)(I2C_PCLK / 1000000);
	if (ClockSpeed > 100000)
	{
		value = value*300/1000;
	}
	value++;
	return value;
}

/******************
	中断入口
******************/
void I2C1_EV_IRQHandler(void)
{
    oI2C1.EV_IRQHandler();
}

void I2C1_ER_IRQHandler(void)       //m_I2C Error Interrupt
{
	oI2C1.ER_IRQHandler();
}

u16 __reserved_SI2C::calcCRRValue(u32 ClockSpeed)
{
	u16 result=0x04;
	if (ClockSpeed <= 100000)
	{
		/* 计算标准模式下速度 */
		result = I2C_PCLK / (ClockSpeed << 1);
		/* 检测是否小于0x4（允许的最小值）*/
		if (result < 0x04)
		{
			result = 0x04;
		}
		/* Maximum Rise Time for standard mode */
	}
	else /*(ClockSpeed <= 400000)*/
	{
		/* 计算快速模式下速度 */
		if (I2C_DutyCycle == I2C_DutyCycle2)
		{
			/* Fast mode speed calculate: Tlow/Thigh = 2 */
			result = (uint16_t)(I2C_PCLK / (ClockSpeed * 3));
		}
		else
		{
			/* Fast mode speed calculate: Tlow/Thigh = 16/9 */
			result = (uint16_t)(I2C_PCLK / (ClockSpeed * 25));
			/* Set DUTY bit */
			result |= I2C_DutyCycle16_9;
		}

		/* 检测result中CCR是否为零*/
		if ((result & 0x0FFF) == 0)
		{
			/* 设置最小允许值 */
			result |= (uint16_t)0x0001;
		}
		/* 置位F/S */
		result |=0x8000;
	}
	return result;
}
