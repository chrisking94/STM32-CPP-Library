#pragma once
#include "Common.h"
class __reserved_SI2C
{
#define DevCount 2//使用的I2C模块的个数
#define BUFFER_SIZE 8//缓冲区大小
public:
	typedef enum
	{
		_En_I2C				=0x0001,/*启用I2C*/
		_Mode_SMBus			=0x0002,/*SMBus模式,否则I2C模式*/
		_Mode_SMBBusMaster	=0x0008,/*SMBus主机模式，否则SMBus从机*/
		_En_ARP				=0x0010,/*使能ARP*/
		_En_PEC				=0x0020,/*开启PEC*/
		_En_GneralCall		=0x0040,/*允许广播呼叫，以应答相应地址00h*/
		_Da_ClockStretching	=0x0080,/*禁止时钟延长（从模式）*/
		_Gen_Start			=0x0100,/*主模式：重复产生起始条件，从模式：总线空闲时产生起始条件*/
		_Gen_Stop			=0x0200,/*主模式：在当前字节传输或当前起始条件发出后产生停止位，从模式：在当前字节传输或释放SCL或SDA线*/
		_En_Acknowledge		=0x0400,/*启用应答*/
		/*1：ACK位控制在移位寄存器里接收的下一个字节的(N)ACK。PEC位表明在移位寄存器里接收的下一个字节是PEC。
		  0：ACK位控制当前移位寄存器内正在接收的字节的(N)ACK。PEC位表明当前移位寄存器内的字节是PEC*/
		_AckPECPostion		=0x0800,
		_PacketErrorChecking=0x1000,/*PEC传输*/
		_SMBusAlert			=0x2000,
		_SoftwareRest		=0x8000,/*I2C模块复位*/
	}I2CCR1Conf;
	typedef enum
	{
		/*
		在下列条件下，将产生该中断：
		– BERR = 1；
		– ARLO = 1；
		– AF = 1；
		– OVR = 1；
		– PECERR = 1；
		– TIMEOUT = 1；
		– SMBAlert = 1。
		*/
		_Intr_Error		=0x0010,
		/*
		在下列条件下，将产生该中断：
		– SB = 1 (主模式)；
		– ADDR = 1 (主/从模式)；
		– ADD10= 1 (主模式)；
		– STOPF = 1 (从模式)；
		– BTF = 1，但是没有TxE或RxNE事件；
		– 如果ITBUFEN = 1，TxE事件为1；
		– 如果ITBUFEN = 1，RxNE事件为1。
		*/
		_Intr_Event		=0x0020,
		_Intr_Buffer	=0x0040,/*1：当TxE=1或RxNE=1时，产生事件中断(不管DMAEN是何种状态)。*/
	}I2CIntrConf;
	typedef enum
	{
		_En_DMARequest	=0x0080,/*1：当TxE=1或RxNE =1时，允许DMA请求。*/
		_DMALastTransfer=0x0100,/*1：下一次DMA的EOT是最后的传输。注：该位在主接收模式使用， 使得在最后一次接收数据时可以产生一个NACK。*/
	}I2CCR2Conf;
	typedef enum
	{
		_Flag_StartBit				=0x0001,/*起始条件已发送*/
		_Flag_AddressSentOrMatched	=0x0002,/*地址已发送或匹配*/
		_Flag_ByteTransferFinished	=0x0004,/*字节发送结束*/
		_Flag_10BitHeaderSent		=0x0008,/*主机已将第10位地址的一个字节发送出去*/
		_Flag_StopDetected			=0x0010,/*检测到停止位*/
		_Flag_RxRegNotEmpty			=0x0040,/*接收寄存器非空*/
		_Flag_TxRegNotEmpty			=0x0080,/*发送寄存器非空*/
		_Flag_BusError				=0x0100,/*起始或停止条件出错*/
		_Flag_ArbitrationLost		=0x0200,/*仲裁丢失*/
		_Flag_AcknowledgeFailure	=0x0400,/*应答失败*/
		_Flag_OverrunOrUnderrun		=0x0800,/*过载或欠载*/
		/*0: 无PEC错误：接收到PEC后接收器返回ACK(如果ACK=1)；
		  1: 有PEC错误：接收到PEC后接收器返回NACK(不管ACK是什么值)。
		– 该位由软件写’0’清除，或在PE=0时由硬件清除。*/
		_Flag_PECErrorInReception	=0x1000,
		/*0：无超时错误；
		  1：SCL处 于低已达 到25ms(超时)；或者主 机 低电平累 积 时钟扩展 时 间超过
		10ms(Tlow:mext)；或从设备低电平累积时钟扩展时间超过25ms(Tlow:sext)。
		– 当在从模式下设置该位：从设备复位通讯，硬件释放总线。
		– 当在主模式下设置该位：硬件发出停止条件。*/
		_Flag_TimeoutOrTlowError	=0x4000,
		_Flag_SMBusAlert			=0x8000,
	}I2CSR1Flag;
	typedef enum
	{
		_Flag_Master					=0x0001,/*主模式*/
		_Flag_BusBusy					=0x0002,/*总线上正在进行数据通讯*/
		_Flag_Transmitter				=0x0004,/*作为数据发送器，接受的地址字节R/W位决定该位*/
		_Flag_GeneralCall				=0x0010,/*收到广播呼叫的地址*/
		/*0：未收到SMBus设备的默认地址；
		  1：当ENARP=1时，收到SMBus设备的默认地址。*/
		_Flag_SMBusDeviceDefaultAdress	=0x0020,
		/*0：未收到SMBus主机的地址；
		  1：当SMBTYPE=1且ENARP=1时，收到SMBus主机地址。*/
		_Flag_SMBusHostHeader			=0x0040,
		/*0：接收到的地址与OAR1内的内容相匹配；
		  1：接收到的地址与OAR2内的内容相匹配。*/
		_Flag_DualFlag					=0x0080,
	}I2CSR2Flag;
public:
	__reserved_SI2C(I2C_TypeDef *I2C);
	~__reserved_SI2C(void);
	void setClockFrequency(const u8 freq);/*I2C模块时钟频率，范围2~36MHz*/
	void set(const I2CCR1Conf conf);
	void reset(const I2CCR1Conf conf);
	void enableDMA();
	void disableDMA();
	void set(const I2CCR2Conf conf);
	void reset(const I2CCR2Conf conf);
	void enableInterrupt(const I2CIntrConf conf);
	void disableInterrupt(const I2CIntrConf conf);
	void setInterfaceAddress(const u8 conf);/*设置器件地址，高7位有效*/
	u16	 isFlagOn(const I2CSR1Flag	conf) const;
	u16	 isFlagOn(const I2CSR2Flag	conf) const;
	void clearFlag(const I2CSR2Flag conf);
	void clearFlag(const I2CSR1Flag conf);

	void transfer(){start();}//启动传输
	void wait(void)	const{while(m_cStat==_Transffering);}
	void writeData(u8 addr,u8 dat);
	u8 readData(u8 addr);
	 void EV_IRQHandler();//供中断函数调用
	 void ER_IRQHandler();
protected:
	u16 calcCRRValue(u32 ClockSpeed);
	u16 calcTRISEValue(u32 ClockSpeed);
	 void start()			{m_cStat=_Transffering;m_I2C->CR1 |=   1<<8;}//!产生起始条件
	 void stop()		const{m_I2C->CR1 |=   1<<9;}
	 void end()		const{m_I2C->CR1 &=   ~1;}//PE置0
	 void ack()		const{m_I2C->CR1 |= 1<<10;}//允许ACK
	 void nack()		const{m_I2C->CR1 &= ~(1<<10);}//无ACK
public:
	u8			I2CDevAddr;//I2C总线上的设备地址
	u8			Buffer[BUFFER_SIZE];//传输缓冲
	u8			nWriteLen;//写出数据个数
	enum{_W,_R}	Mod;//写 或 读
	u8			nReadLen;//读取数据个数
private:
	__IO uint16_t CR1;
	uint16_t  RESERVED0;
	__IO uint16_t CR2;
	uint16_t  RESERVED1;
	__IO uint16_t OAR1;
	uint16_t  RESERVED2;
	__IO uint16_t OAR2;
	uint16_t  RESERVED3;
	__IO uint16_t DR;
	uint16_t  RESERVED4;
	__IO uint16_t SR1;
	uint16_t  RESERVED5;
	__IO uint16_t SR2;
	uint16_t  RESERVED6;
	__IO uint16_t CCR;
	uint16_t  RESERVED7;
	__IO uint16_t TRISE;
	uint16_t  RESERVED8;
	I2C_TypeDef *m_I2C;
	enum		
	{
		_Standby,
		_Transffering,
		_Error
	}			m_cStat;
private://静态成员
	static I2C_TypeDef *s_CurI2C;//当前正在使用的I2C
};

extern __reserved_SI2C oI2C1;