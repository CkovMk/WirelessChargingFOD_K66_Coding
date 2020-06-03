/******************************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2019,���������ܳ����¾��ֲ�
 * All rights reserved.
 * 
 * @file       		�������
 * @company	        ���������ܳ����¾��ֲ�
 * @author     		���Ļ� qq1280390945
 * @version    		v1.0
 * @Software 		IAR 7.7+
 * @Target core		K66
 * @date       		2019-9-27
 *
 * @note��
		KEY�ṹ�嶨�����������ӦGPIO�ںͶ�Ӧ���ţ�ʹ��ʱ���ա�Key.h����
		Key_e��˳�������г�,KEY_NUMΪ��������
		
		��������ҵ��ѧ���ܳ����¾��ֲ�ר�ã�����й¶
***************************************************************************************************************************/

#include "SmartCar_Key.h"
#include "fsl_gpio.h"

#define   KEY_NUM	5

KEY Key[KEY_NUM] =
{
  {
    .GPIO = GPIOE,
    .PORT = PORTE,
    .PIN  = 8
  },
  {
    .GPIO = GPIOE,
    .PORT = PORTE,
    .PIN  = 6
  },
  {
    .GPIO = GPIOE,
    .PORT = PORTE,
    .PIN  = 9
  },
  {
    .GPIO = GPIOE,
    .PORT = PORTE,
    .PIN  = 7
  },
  {
    .GPIO = GPIOE,
    .PORT = PORTE,
    .PIN  = 10
  },
};

gpio_pin_config_t Key_config = {kGPIO_DigitalInput, 0};
port_pin_config_t Key_port_config = {
     kPORT_PullUp,
     kPORT_FastSlewRate,
     kPORT_PassiveFilterDisable,
     kPORT_OpenDrainDisable,
     kPORT_LowDriveStrength,
     kPORT_MuxAsGpio,
     kPORT_UnlockRegister,
};
/**********************************************************************************************************************
*  @brief      ������⺯��
*  @param      key        ��Ҫ���İ���
*  @return     ����0�������£�����1����δ����
*  @since      v1.0
*  Sample usage:          Key_Init();
**********************************************************************************************************************/
void Key_Init(void)
{
  uint8_t i;
  for( i = 0;i<KEY_NUM;i++)
  {
  PORT_SetPinMux(Key[i].PORT, Key[i].PIN, kPORT_MuxAsGpio);
  GPIO_PinInit(Key[i].GPIO, Key[i].PIN, &Key_config);
  PORT_SetPinConfig(Key[i].PORT, Key[i].PIN, &Key_port_config);
  }
}
/**********************************************************************************************************************
*  @brief      ������⺯��
*  @param      key        ��Ҫ���İ���
*  @return     ����0�������£�����1����δ����
*  @since      v1.0
*  Sample usage:          Key_Check(KEY_ENTER);  
**********************************************************************************************************************/

KEY_STATUS Key_Check(KEY_e key)
{
    if((((Key[key].GPIO->PDIR) >> Key[key].PIN) & 0x01U)==KEY_P_DOWN )
    {
        DELAY_MS(50);
        if((((Key[key].GPIO->PDIR) >> Key[key].PIN) & 0x01U)==KEY_P_DOWN )
        return KEY_P_DOWN;
    }
    return KEY_P_UP;
}


