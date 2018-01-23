#pragma once
#include "Common.h"
#include "stdarg.h"

#define led2	PC13
#define led1	PA15

void BaseLib_init(void);
void delays(u32 s);
void delayms(u32 ms);
void delayus(u32 us);
void waitWhile(bool condition);
void beep(u16 time ,u16 interval);
void startTiming(void);
u32 readTimingms(void);
u32 div_u32(u32 n1,u32 n2);
u8	bcd2dec(u8 bcd);
u8	dec2bcd(u8 dec);
u32 printf(const char *format,va_list &args);
u32 printf(const char *format,...);
u32 scanf(const char *format,...);
