/******************************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2019,���������ܳ����¾��ֲ�
 * All rights reserved.
 * 
 * @file       		���ֵ�λ��5206
 * @company	        ���������ܳ����¾��ֲ�
 * @author     		Ǯ����2248285537  �����786240762	���Ļ� qq1280390945
 * @version    		v1.0
 * @Software 		IAR 7.7+
 * @Target core		K66
 * @date       		2019-9-27
 *
 * @note��
    ��������ҵ��ѧ���ܳ����¾��ֲ�ר�ã�����й¶
***************************************************************************************************************************/

#include "SmartCar_AD5206.h"

#define CS_LOW() GPIO_PortClear(CS_GPIO,1U<<CS_PIN)
#define CS_HIGH() GPIO_PortSet(CS_GPIO,1U<<CS_PIN)
#define DIN_LOW() GPIO_PortClear(DIN_GPIO,1U<<DIN_PIN)
#define DIN_HIGH() GPIO_PortSet(DIN_GPIO,1U<<DIN_PIN)
#define CLK_LOW() GPIO_PortClear(CLK_GPIO,1U<<CLK_PIN)
#define CLK_HIGH() GPIO_PortSet(CLK_GPIO,1U<<CLK_PIN)

gpio_pin_config_t AD5206_GPIO_out_config = {
    .pinDirection = kGPIO_DigitalOutput,
    .outputLogic = 1U
};

void Delay()
{
    int i,j;
    for(i=0;i<10;i++)
      for(j=0;j<50;j++);

}

/**********************************************************************************************************************
*  @brief      ���뿪�س�ʼ��
*  @param      address	�����ַ
*  @param      dat		�趨ֵ
*  @return     NULL
*  @since      v1.0
*  Sample usage:    WriteAD5206(R0,100);
**********************************************************************************************************************/
void AD5206_init()
{
      PORT_SetPinMux(CS_PORT, CS_PIN, kPORT_MuxAsGpio);
	  PORT_SetPinMux(DIN_PORT, DIN_PIN, kPORT_MuxAsGpio);
	  PORT_SetPinMux(CLK_PORT, CLK_PIN, kPORT_MuxAsGpio);
      GPIO_PinInit(CS_GPIO, CS_PIN, &AD5206_GPIO_out_config);
      GPIO_PinInit(DIN_GPIO, DIN_PIN, &AD5206_GPIO_out_config);
      GPIO_PinInit(CLK_GPIO, CLK_PIN, &AD5206_GPIO_out_config);
}

/**********************************************************************************************************************
*  @brief      AD5206�趨����ֵ
*  @param      address	�����ַ
*  @param      dat		�趨ֵ
*  @return     NULL
*  @since      v1.0
*  Sample usage:    WriteAD5206(R0,100);
**********************************************************************************************************************/
void WriteAD5206(unsigned char address,unsigned char dat)
{
    uint8_t i;
    
    CS_LOW();    //����Ƭѡ�ߣ�ѡ������
    //���͵�ַ
    for (i=0;i<3;i++)        //��λѭ��3��              
    {   
       CLK_LOW();       //����ʱ������
       if(address&0x80)
        DIN_HIGH();
       else
        DIN_LOW();
       address<<=1;             //����һλ
       Delay();
       CLK_HIGH();      //ʱ�������أ����͵�ַ
       Delay();
    }
    //��������
    for (i=0;i<8;i++)        //��λѭ��8��              
    {   
       CLK_LOW();       //����ʱ������
       if(dat&0x80)
         DIN_HIGH();
       else
         DIN_LOW();
       dat<<=1;             //����һλ
       Delay();
       CLK_HIGH();      //ʱ�������أ����͵�ַ
        Delay();
    }
   CS_HIGH();     //���ͽ�������������������   
}




 