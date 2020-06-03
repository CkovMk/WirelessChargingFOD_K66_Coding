#ifndef _SMARTCAR_KEY_H
#define _SMARTCAR_KEY_H

#include "fsl_common.h"
#include "SmartCar_Systick.h"




//-------------------------------------------------------------------------------------------------------------------
//  @brief      �������壬�ɸ�����Ҫ����˳��
//-------------------------------------------------------------------------------------------------------------------
typedef enum
{
    KEY_ENTER,//0 	���ļ�
    KEY_UP,   //1	�ϼ�

    KEY_DOWN, //2 	�¼�
    KEY_LEFT, //3	���

    KEY_RIGHT,//4	�Ҽ�

    KEY_MAX,  //5   ��ʼ����
}KEY_e;

typedef enum
{
    KEY_P_DOWN,
    KEY_P_UP,
}KEY_STATUS;

typedef struct _Key
{
  GPIO_Type* GPIO;
  PORT_Type* PORT;
  uint8_t    PIN;
} KEY;


void Key_Init();
KEY_STATUS Key_Check(KEY_e key);

#endif // __KEY_H

