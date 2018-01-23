#pragma once
#include "Common.h"

#define Pclk1_36MHz ((u32)36000000) //其他USART
#define Pclk2_72MHz ((u32)72000000) //USART1
#define USART_PSC 16				 //Prescaler Value 时钟预分频

struct __reserved_SUsart
{
public:
	__reserved_SUsart();
	~__reserved_SUsart(void);

	void setBaudRate(u32 baudRate);
	void sendChar(char ch);
	char recvChar();
private:
	static u32 calcBRRDiv(u32 BaudRate,u32 Pclk);
public:
	__IO uint16_t SR;
	uint16_t  RESERVED0;
	__IO uint16_t DR;
	uint16_t  RESERVED1;
	__IO uint16_t BRR;
	uint16_t  RESERVED2;
	__IO uint16_t CR1;
	uint16_t  RESERVED3;
	__IO uint16_t CR2;
	uint16_t  RESERVED4;
	__IO uint16_t CR3;
	uint16_t  RESERVED5;
	__IO uint16_t GTPR;
	uint16_t  RESERVED6;
};

#define usart1	(*(__reserved_SUsart*)USART1)
#define usart2	(*(__reserved_SUsart*)USART2)
#define usart3	(*(__reserved_SUsart*)USART3)
#define usart4	(*(__reserved_SUsart*)USART4)
#define usart5	(*(__reserved_SUsart*)USART5)
