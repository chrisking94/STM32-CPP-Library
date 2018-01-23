#include "Usart.h"

void __reserved_SUsart::setBaudRate(u32 baudRate)
{
	if(this==(void*)USART1)
	{
		BRR = calcBRRDiv(baudRate,Pclk2_72MHz);//（USART_BRR）
	}
	else
	{
		BRR = calcBRRDiv(baudRate,Pclk1_36MHz);//（USART_BRR）
	}

	GTPR = USART_PSC/2;//（USART_GTPR）
	CR1 = 0x0000202C;//（USART_CR1)0x000020EC
	CR2 = 0;				 //（USART_CR2)
	CR3 = 0;				 //（USART_CR3)
}

void __reserved_SUsart::sendChar(char ch)
{
	while (!(SR & 1<<7));//!等待上次传输结束
	DR = (u16)ch;
}

char __reserved_SUsart::recvChar()
{

}

u32 __reserved_SUsart::calcBRRDiv(u32 BaudRate,u32 Pclk)
{
	u32 div_mant;
	u32 div_frac;
	double frac;
	div_mant=Pclk/(USART_PSC*BaudRate);
	frac=(double)Pclk/(USART_PSC*BaudRate);
	frac-=div_mant;
	frac*=USART_PSC;
	div_frac=(u32)frac;
	div_frac+=(frac-div_frac)>=0.5?1:0;//四舍五入

	if (div_frac==USART_PSC)//满USART_PSC进位
	{
		div_frac=0;
		div_mant++;
	}
	div_mant<<=4;
	div_mant|=div_frac;
	return div_mant;
}

