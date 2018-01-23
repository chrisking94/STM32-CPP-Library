#include "Serial.h"
#include "stdarg.h"
#include "BaseLib.h"

CSerial serial1(usart1,9600);

CSerial::CSerial(__reserved_SUsart &usart,u32 baudRate):pUsart(&usart)
{
	pUsart->setBaudRate(baudRate);
}


CSerial::~CSerial(void)
{
}
