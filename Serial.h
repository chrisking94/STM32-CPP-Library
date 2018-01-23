#pragma once
#include "commudev.h"
#include "Usart.h"

class CSerial :
	public CCommuDev
{
public:
	CSerial(__reserved_SUsart &usart,u32 baudRate);
	~CSerial(void);

	 void sendChar(char ch){pUsart->sendChar(ch);}
	 char recvChar(){pUsart->recvChar();}
private:
	__reserved_SUsart	*pUsart;
};

extern CSerial serial1;
