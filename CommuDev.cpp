#include "CommuDev.h"
#include "Serial.h"
#include "BaseLib.h"

CCommuDev::CCommuDev(void)
{

}

CCommuDev::~CCommuDev(void)
{
}

void CCommuDev::printf(const char *format,...)
{
	va_list args;

	selectDevice(*this);
	va_start(args,format);
	::printf(format,args);
	va_end(args);
}

CCommuDev * CCommuDev::pDev=&serial1;
