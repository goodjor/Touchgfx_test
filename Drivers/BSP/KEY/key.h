#ifndef __KEY_H__
#define __KEY_H__
#include "sys.h"

#ifdef __cplusplus
extern "C" {
#endif
	
#define KEY0        PHin(3) //KEY0����PH3
#define KEY1        PHin(2) //KEY1����PH2
#define KEY2        PCin(13)//KEY2����PC13
#define WK_UP       PAin(0) //WKUP����PA0

#define NONE_KEY_PRES	0
#define KEY0_PRES 		'0'	
#define KEY1_PRES			'1'
#define KEY2_PRES			'2'
#define WKUP_PRES   	'3'

void KEY_Init(void);
u8 KEY_Scan(u8 mode);

#ifdef __cplusplus
}
#endif	

#endif
