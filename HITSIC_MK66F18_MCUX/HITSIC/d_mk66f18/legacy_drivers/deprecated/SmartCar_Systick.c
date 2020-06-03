/******************************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2019,���������ܳ����¾��ֲ�
 * All rights reserved.
 * 
 * @file       		ʱ�亯��
 * @company	        ���������ܳ����¾��ֲ�
 * @author     		��ѧ�� qq512924543     ���Ļ�qq1280390945
 * @version    		v1.0
 * @Software 		IAR 7.7+
 * @Target core		K66
 * @date       		2019-9-27
 *
 * @note��
				
    ��������ҵ��ѧ���ܳ����¾��ֲ�ר�ã�����й¶
***************************************************************************************************************************/

#include "SmartCar_Systick.h"

/**********************************************************************************************************************
*  @brief      systick��ʱ����
*  @param      time            ��Ҫ��ʱ��ʱ��
*  @return     void
*  @since      v1.0
*  Sample usage:               systick_delay(1000);   *��ʱ1000���ں�ʱ������
**********************************************************************************************************************/
void systick_delay(uint32_t time)
{
    if(time == 0)   return;

    SysTick->CTRL = 0x00;//�ȹ��� systick ,���־λ
    SysTick->LOAD = time;//������ʱʱ��..
    SysTick->VAL = 0x00;//��ռ�����
    SysTick->CTRL = ( 0 | SysTick_CTRL_ENABLE_Msk         //ʹ�� systick
                  //| SysTick_CTRL_TICKINT_Msk        //ʹ���ж� (ע���˱�ʾ�ر��ж�)
                    | SysTick_CTRL_CLKSOURCE_Msk      //ʱ��Դѡ�� (core clk) K60ֻ��ѡ��(core clk)
                );
     while( !(SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk));//�ȴ�ʱ�䵽
}

/**********************************************************************************************************************
*  @brief      ���뼶systick��ʱ����
*  @param      ms              ��ʱ���ٺ���
*  @return     void
*  @since      v1.0
*  Sample usage:               systick_delay_ms(1000);   *��ʱ1000����
**********************************************************************************************************************/
void systick_delay_ms(uint32_t ms)
{
    //get_clk();//��ȡ�ں�ʱ�ӱ��ں�������
    uint32_t core_clk_mhz = CLOCK_GetCoreSysClkFreq();
    while(ms--) systick_delay(core_clk_mhz/1000);
}

/**********************************************************************************************************************
*  @brief      systick��ʱ��
*  @param      time            ��ʱʱ��(0-0x00ffffff)
*  @return     void
*  @since      v1.0
*  Sample usage:               systick_timing(1000);   *��ʱ1000���ں�ʱ������
**********************************************************************************************************************/
void systick_timing(uint32_t time)
{
    time &= 0x00ffffff;     	//����ǿ�Ʊ任Ϊ24λ 
    SysTick->LOAD = time;       //������ʱʱ��
    SysTick->VAL = 0x00;       	//��ռ�����
    SysTick->CTRL = ( 0 
					| SysTick_CTRL_ENABLE_Msk       //ʹ�� systick
                    | SysTick_CTRL_TICKINT_Msk      //ʹ���ж�
                    | SysTick_CTRL_CLKSOURCE_Msk    //ʱ��Դѡ�� (core clk) K60ֻ��ѡ��(core clk)
                );
}

/**********************************************************************************************************************
*  @brief      ��õ�ǰSystem tick timer��ֵ
*  @return     ���ص�ǰSystem tick timer��ֵ
*  @since      v1.0
*  Sample usage:               uint32_t tim = systick_getval();   
**********************************************************************************************************************/
uint32_t systick_getval(void)
{
    return SysTick->VAL;
}


