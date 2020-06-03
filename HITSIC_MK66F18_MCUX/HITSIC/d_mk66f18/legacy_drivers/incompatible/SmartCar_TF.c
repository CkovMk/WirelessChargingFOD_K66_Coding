/******************************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2019,���������ܳ����¾��ֲ�
 * All rights reserved.
 * 
 * @file       		tf_mini uart�ײ�
 * @company	        ���������ܳ����¾��ֲ�
 * @author     		���˴� �߼λ� 
 * @version    		v1.0
 * @Software 		IAR 7.7+
 * @Target core		K66
 * @date       		2019-9-30
 *
 * @note��
		�õײ�������tfmini��tfminiplus��ʹ��ʱ�����������Ÿ���tf.h�еĺ궨��
		
		��������ҵ��ѧ���ܳ����¾��ֲ�ר�ã�����й¶
***************************************************************************************************************************/

#include "SmartCar_TF.h"
  const uart_config_t UART_tf_config = {
  .baudRate_Bps = 115200,
  .parityMode = kUART_ParityDisabled,
  .stopBitCount = kUART_OneStopBit,
  .txFifoWatermark = 0,
  .rxFifoWatermark = 1,
  .idleType = kUART_IdleTypeStartBit,
  .enableTx = true,
  .enableRx = true
};

void my_getchar (UART_Type *base, uint8_t *ch)   //uart����һ���ַ�
{
    while(!(base->S1 & UART_S1_RDRF_MASK));     
    *ch =  base->D; 
    
}

int tf_distance;
int tf_strength;
uint8_t tf_arry[9];
/**********************************************************************************************************************
*  @brief      TOF���ڳ�ʼ��
*  @param      NULL
*  @return     NULL
*  @since      v1.0
*  Sample usage:    uart_tf_init()
**********************************************************************************************************************/
void uart_tf_init(void)                               //�жϳ�ʼ��                   
{
  UART_Init(UART_tf_PERIPHERAL, &UART_tf_config, UART_tf_CLOCK_SOURCE);
  UART_EnableInterrupts(UART_tf_PERIPHERAL, kUART_RxDataRegFullInterruptEnable | kUART_RxOverrunInterruptEnable);
  /* Interrupt vector UART1_RX_TX_IRQn priority settings in the NVIC */
  NVIC_SetPriority(UART_tf_SERIAL_RX_TX_IRQN, UART_tf_SERIAL_RX_TX_IRQ_PRIORITY);
  /* Enable interrupt UART1_RX_TX_IRQn request in the NVIC */
  EnableIRQ(UART_tf_SERIAL_RX_TX_IRQN);
}
/**********************************************************************************************************************
*  @brief      ��ȡTOF����
*  @param      NULL
*  @return     int   ����ֵ
*  @since      v1.0
*  Sample usage:    uart_tf_distance()
**********************************************************************************************************************/
int uart_tf_distance()
{
  return tf_distance;
}
/**********************************************************************************************************************
*  @brief      TOF�����жϷ�����
*  @param      NULL
*  @return     NULL
*  @since      v1.0
*  Sample usage:    NULL
**********************************************************************************************************************/
void UART_tf_SERIAL_RX_TX_IRQHANDLER()        //uart�Д���պ���
{
  static int TF_cnt=0;
  static int TF_check=0;
  static  uint8_t cache_buff[9];
 if(( kUART_RxDataRegFullFlag| kUART_RxOverrunFlag) & UART_GetStatusFlags(UART_tf_PERIPHERAL))
  {
    my_getchar(UART_tf_PERIPHERAL,&cache_buff[TF_cnt]);      //����һ���ַ������M
    if(TF_cnt==0 || TF_cnt==1)
    {
      if(cache_buff[TF_cnt]==0x59)     
           TF_cnt++;       
    }
    else
    {
      TF_cnt++;
    }
    if(TF_cnt>8)
    {
      for(int i = 0;i<8;i++)
      {
        TF_check += cache_buff[i];
      }
      if(cache_buff[8] == (TF_check&0xff))//У�
      {
        memcpy(tf_arry, cache_buff, sizeof(cache_buff));   //��������
        tf_strength = tf_arry[4]+(tf_arry[5]<<8);     //��ǿ�ȵĸ�8λ�͵�8λ�õ�ǿ��ֵ
        if(tf_strength>100 && tf_strength!=65535)     //�ź�ǿ����������ʱ�ſ���
          tf_distance = tf_arry[2]+(tf_arry[3]<<8);   //�ɾ���ĸ�8λ�͵�8λ�õ�����ֵ
        else tf_distance = 9999;
      }
      TF_cnt = 0;//�����Ƿ�У��ɹ��������¿�ʼ��ȡ����
      TF_check = 0;
    }
  }
  
}

