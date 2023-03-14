#ifndef __LED_H__
#define __LED_H__
#include "sys.h"

#ifdef __cplusplus
extern "C" {
#endif

#define LED0 PBout(1)   //LED0
#define LED1 PBout(0)   //LED1

void LED_Init(void);
	
#ifdef __cplusplus
}
#endif
	
#endif
