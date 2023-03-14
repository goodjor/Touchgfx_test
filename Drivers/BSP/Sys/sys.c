#include "sys.h"



//大致us延时函数
void delay_us(volatile u32 us)
{
	volatile u16 i,j;  
	while(us--)
	{
		for(i=0;i<11;i++)
			j++;
	}
}
//大致的ms延时函数
void delay_ms(u32 ms)
{
	delay_us(ms*1000);
}















