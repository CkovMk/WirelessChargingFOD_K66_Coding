/******************************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2019,���������ܳ����¾��ֲ�
 * All rights reserved.
 * 
 * @file       		���뿪�ؼ��
 * @company	        ���������ܳ����¾��ֲ�
 * @author     		���Ļ� qq1280390945
 * @version    		v1.0
 * @Software 		IAR 7.7+
 * @Target core		K66
 * @date       		2019-9-27
 *
 * @note��
		Boma_Switch�ṹ�嶨�岦�밴����ӦGPIO�ں�����,BOMA_NUMΪ���밴��������
		���ò�ͬ���뿪��ʱ�ǵ��޸�
    ��������ҵ��ѧ���ܳ����¾��ֲ�ר�ã�����й¶
***************************************************************************************************************************/

#include "SmartCar_Boma.h"

#define  BOMA_NUM	4

Boma_Switch Boma[BOMA_NUM] =
{
  {
    .GPIO = GPIOA,
    .PORT = PORTA,
    .PIN  = 19
  },
  {
    .GPIO = GPIOA,
    .PORT = PORTA,
    .PIN  = 16
  },
  {
    .GPIO = GPIOA,
    .PORT = PORTA,
    .PIN  = 14
  },
  {
    .GPIO = GPIOA,
    .PORT = PORTA,
    .PIN  = 12
  }
};

gpio_pin_config_t Boma_config = {kGPIO_DigitalInput, 0};
port_pin_config_t Boma_port_config = {
     kPORT_PullUp,
     kPORT_FastSlewRate,
     kPORT_PassiveFilterDisable,
     kPORT_OpenDrainDisable,
     kPORT_LowDriveStrength,
     kPORT_MuxAsGpio,
     kPORT_UnlockRegister,
};

/**********************************************************************************************************************
*  @brief      ���뿪�س�ʼ��
*  @param      NULL
*  @return     NULL
*  @since      v1.0
*  Sample usage:    Boma_Init()
**********************************************************************************************************************/
void Boma_Init(void)
{
  uint8_t i;
  for( i = 0;i<BOMA_NUM;i++)
  {
  PORT_SetPinMux(Boma[i].PORT, Boma[i].PIN, kPORT_MuxAsGpio);
  GPIO_PinInit(Boma[i].GPIO, Boma[i].PIN, &Boma_config);
  PORT_SetPinConfig(Boma[i].PORT, Boma[i].PIN, &Boma_port_config);
  }
}

/**********************************************************************************************************************
*  @brief      ���뿪�ؼ�⺯��
*  @param      num        ���뿪��λ
*  @return     ����1�����ش򿪣�����0�����عر�
*  @since      v1.0
*  Sample usage:    Boma_Check(1)���1�Ų��뿪��
**********************************************************************************************************************/
uint8_t Boma_Check(uint8_t num)
{
  return !GPIO_PinRead(Boma[num-1].GPIO,Boma[num-1].PIN);
}
