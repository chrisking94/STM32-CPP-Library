#pragma once

class CCommuDev
{
public:
	CCommuDev(void);
	~CCommuDev(void);
	
	virtual void sendChar(char ch){}//写字符
	virtual char recvChar(){}//接收字符

	virtual void printf(const char *format,...);
	static  void selectDevice(CCommuDev &pDev_){pDev=&pDev_;}//选择一个输入输出设备
public:
	static CCommuDev *pDev;//默认serial1
};

