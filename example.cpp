#include "BaseLib.h"
#include "GPIO.h"
#include "GPIOPin.h"

#define led	PC13
int main()
{
	BaseLib_init();//RCC,AFIO,SCB,NVIC,
	led.pinMod(_OGPP);
	
	for(;;)
	{
		led=!led;
	}
}
