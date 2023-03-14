#include "ft5206.h"
#include "ctiic.h"

//向FT5206写入一次数据
//reg:起始寄存器地址
//buf:数据缓缓存区
//len:写数据长度
//返回值:0,成功;1,失败.
u8 FT5206_WR_Reg(u16 reg,u8 *buf,u8 len)
{
	u8 i;
	u8 ret=0;
	CT_IIC_Start();	 
	CT_IIC_Send_Byte(FT_CMD_WR);	//发送写命令 	 
	CT_IIC_Wait_Ack(); 	 										  		   
	CT_IIC_Send_Byte(reg&0XFF);   	//发送低8位地址
	CT_IIC_Wait_Ack();  
	for(i=0;i<len;i++)
	{	   
    CT_IIC_Send_Byte(buf[i]);  	//发数据
		ret=CT_IIC_Wait_Ack();
		if(ret)break;  
	}
  CT_IIC_Stop();					//产生一个停止条件	    
	return ret; 
}


//从FT5206读出一次数据
//reg:起始寄存器地址
//buf:数据缓缓存区
//len:读数据长度			  
void FT5206_RD_Reg(u16 reg,u8 *buf,u8 len)
{
	u8 i; 
 	CT_IIC_Start();	
 	CT_IIC_Send_Byte(FT_CMD_WR);   	//发送写命令 	 
	CT_IIC_Wait_Ack(); 	 										  		   
 	CT_IIC_Send_Byte(reg&0XFF);   	//发送低8位地址
	CT_IIC_Wait_Ack();  
 	CT_IIC_Start();  	 	   
	CT_IIC_Send_Byte(FT_CMD_RD);   	//发送读命令		   
	CT_IIC_Wait_Ack();	   
	for(i=0;i<len;i++)
	{	   
    	buf[i]=CT_IIC_Read_Byte(i==(len-1)?0:1); //发数据	  
	} 
  CT_IIC_Stop();//产生一个停止条件     
} 


//初始化FT5206触摸屏
//返回值:0,初始化成功;1,初始化失败 
u8 FT5206_Init(void)
{
	u8 temp[2]; 
	GPIO_InitTypeDef GPIO_Initure;

	__HAL_RCC_GPIOH_CLK_ENABLE();			//开启GPIOH时钟
	__HAL_RCC_GPIOI_CLK_ENABLE();			//开启GPIOI时钟
							
	//PH7(当有手按下时,一直输出低电平,否则一直输出高电平)
	GPIO_Initure.Pin=GPIO_PIN_7;            //PH7
	GPIO_Initure.Mode=GPIO_MODE_INPUT;      //输入
	GPIO_Initure.Pull=GPIO_PULLUP;          //上拉
	GPIO_Initure.Speed=GPIO_SPEED_HIGH;     //高速
	HAL_GPIO_Init(GPIOH,&GPIO_Initure);     //初始化
					
	//PI8
	GPIO_Initure.Pin=GPIO_PIN_8;            //PI8
	GPIO_Initure.Mode=GPIO_MODE_OUTPUT_PP;  //推挽输出
	HAL_GPIO_Init(GPIOI,&GPIO_Initure);     //初始化
			
	CT_IIC_Init();      	//初始化电容屏的I2C总线  
	FT_RST=1;
	delay_ms(120);			//至少延时100ms,多加20ms
	FT_RST=0;				//复位
	delay_ms(20);
	FT_RST=1;				//释放复位		    
	delay_ms(100);  //这里至少需要延时100ms,否则初始化会失败的 	
	temp[0]=0;
	FT5206_WR_Reg(FT_DEVIDE_MODE,temp,1);	//进入正常操作模式 
	FT5206_WR_Reg(FT_ID_G_MODE,temp,1);		//查询模式 
	temp[0]=22;								//触摸有效值，22，越小越灵敏	
	FT5206_WR_Reg(FT_ID_G_THGROUP,temp,1);	//设置触摸有效值
	temp[0]=12;								//激活周期，不能小于12，最大14
	FT5206_WR_Reg(FT_ID_G_PERIODACTIVE,temp,1); 
	//读取版本号，参考值：0x3003
	FT5206_RD_Reg(FT_ID_G_LIB_VERSION,&temp[0],2);  
	if((temp[0]==0X30&&temp[1]==0X03)||temp[1]==0X01||temp[1]==0X02)//版本:0X3003/0X0001/0X0002
	{
		return 0;
	} 
	return 1;
}


