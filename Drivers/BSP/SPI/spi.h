#ifndef __SPI_H__
#define __SPI_H__
#include "sys.h"

#ifdef __cplusplus
extern "C" {
#endif

// SPI�����ٶ����� 
#define SPI_SPEED_2   		0
#define SPI_SPEED_4   		1
#define SPI_SPEED_8   		2
#define SPI_SPEED_16  		3
#define SPI_SPEED_32 		4
#define SPI_SPEED_64 		5
#define SPI_SPEED_128 		6
#define SPI_SPEED_256 		7
						  	    													  
void SPI5_Init(void);			 //��ʼ��SPI��
void SPI5_SetSpeed(u8 SpeedSet); //����SPI�ٶ�   
u8 SPI5_ReadWriteByte(u8 TxData);//SPI���߶�дһ���ֽ�

#ifdef __cplusplus
}
#endif
	
#endif

