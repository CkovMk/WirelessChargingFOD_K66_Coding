/******************************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2019,���������ܳ����¾��ֲ�
 * All rights reserved.
 * 
 * @file       		PIT��ʱ
 * @company	        ���������ܳ����¾��ֲ�
 * @author     		��ѧ�� qq512924543  ���Ļ�qq1280390945 Ф����1761690868
 * @version    		v1.1
 * @Software 		IAR 7.7+
 * @Target core		K66
 * @date       		2019-9-27
 * @date       		v1.1 2019-10-10 fix bug
 *
 * @note��
        �жϷ�������һ��Ҫ����PIT_ClearStatusFlags(PIT, kPIT_Chnl_2, kPIT_TimerFlag);����жϱ�־λ
    ��������ҵ��ѧ���ܳ����¾��ֲ�ר�ã�����й¶
***************************************************************************************************************************/

#include "SmartCar_Pit.h"

/**********************************************************************************************************************
*  @brief      pit��ʼ��
*  @return     void
*  @since      v1.1
*  Sample usage:          Pit_Init();
**********************************************************************************************************************/
void Pit_Init(void)
{
	pit_config_t pit_config;
	pit_config.enableRunInDebug = 1;
	PIT_Init(PIT, &pit_config);
}

/**********************************************************************************************************************
*  @brief      pit�жϳ�ʼ��
*  @param      channel            pitͨ��
*  @param      count              pit��ʱ��ʼ������λms
*  @return     void
*  @since      v1.1
*  Sample usage:          Pit_Interrupt_Init(kPIT_Chnl_0,500U);
**********************************************************************************************************************/
void Pit_Interrupt_Init(pit_chnl_t channel, uint32_t msec)
{
    uint32_t PIT_SOURCE_CLOCK = CLOCK_GetFreq(kCLOCK_BusClk);
    uint32_t my_count = MSEC_TO_COUNT(msec, PIT_SOURCE_CLOCK);
    PIT_SetTimerPeriod(PIT, channel, my_count);
	PIT_EnableInterrupts(PIT, channel, kPIT_TimerInterruptEnable);
    PIT_StartTimer(PIT,channel);
}

/**********************************************************************************************************************
*  @brief      pit���䶨ʱ
*  @param      channel            pitͨ��
*  @param      count              pit��ʱ��ʼ������λms
*  @return     void
*  @since      v1.1
*  Sample usage:          Pit_ChangeTime(kPIT_Chnl_0,500U)
**********************************************************************************************************************/
void Pit_ChangeTime(pit_chnl_t channel, uint32_t msec)
{
    PIT_StopTimer(PIT, channel);//��ռ�ʱ
    uint32_t PIT_SOURCE_CLOCK = CLOCK_GetFreq(kCLOCK_BusClk);
    uint32_t my_count = MSEC_TO_COUNT(msec, PIT_SOURCE_CLOCK);
    PIT_SetTimerPeriod(PIT, channel, my_count);
}

/**********************************************************************************************************************
*  @brief      pit��ʼ��ʱ
*  @param      channel      pitͨ��
*  @return     void
*  @since      v1.1
*  Sample usage:          Time_Start(kPIT_Chnl_0);
**********************************************************************************************************************/
void Time_Start(pit_chnl_t channel)
{
    PIT->CHANNEL[channel].LDVAL = ~0;//��������Ϊ���
    PIT_StopTimer(PIT, channel);//��ռ�ʱ
    PIT_StartTimer(PIT, channel);//��ʼ��ʱ
}


/**********************************************************************************************************************
*  @brief      pit��ü�ʱʱ��
*  @param      channel      pitͨ��
*  @return     uint32_t       ��ʱʱ�䣬��λms
*  @since      v1.1
*  Sample usage:         Get_Time(kPIT_Chnl_0);
**********************************************************************************************************************/
uint32_t Get_Time(pit_chnl_t channel)
{
    uint32_t PIT_SOURCE_CLOCK = CLOCK_GetFreq(kCLOCK_BusClk);
    uint32_t mytime =((uint32_t)(~0) - PIT_GetCurrentTimerCount(PIT,channel));
	uint32_t get_yime = COUNT_TO_MSEC(mytime, PIT_SOURCE_CLOCK);
    return get_yime;
}


/**********************************************************************************************************************
*  @brief      pit��ü�ʱʱ��
*  @param      channel      pitͨ��
*  @return     uint32_t       ��ʱʱ�䣬��λus
*  @since      v1.1
*  Sample usage:         Get_Time_us(kPIT_Chnl_0);
**********************************************************************************************************************/

uint32_t Get_Time_us(pit_chnl_t channel)
{
	uint32_t PIT_SOURCE_CLOCK = CLOCK_GetFreq(kCLOCK_BusClk);
	uint32_t mytime = ((uint32_t)(~0) - PIT_GetCurrentTimerCount(PIT, channel));
	uint32_t get_yime = COUNT_TO_USEC(mytime, PIT_SOURCE_CLOCK);
	return get_yime;
}
