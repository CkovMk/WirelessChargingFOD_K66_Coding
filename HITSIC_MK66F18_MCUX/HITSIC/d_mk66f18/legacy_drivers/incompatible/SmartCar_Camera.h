#ifndef _SMARTCAR_MT9V032_H
#define _SMARTCAR_MT9V032_H

#define COL     188//ͼ����   ��Χ1-752     K60�ɼ���������188
#define ROW     120//ͼ��߶�	��Χ1-480
#include "stdafx.h"

//#include "smartcar_drivers/uart.h"
//#include "smartcar_drivers/IRQ_manager.h"
#include "include.h"
//#include "SmartCar_Systick.h"
//#include "SmartCar_OLED.h"
#define SMARTCAR_CAMERA_BUFFER (1U)//����Ϊ2��ʱ������˫���棬1���ǵ�����
#define DMAMUX_SELECT DMAMUX0
#define DMA_SELECT DMA0  
#define DMA_CHANNEL_SELECT 0 
/*���ж�����PTC6*/
#define VSY_PORT PORTC
#define VSY_GPIO GPIOC
#define VSY_PIN 6u
//#define VSY_IRQn  PORTC_IRQn
//#define VSY_Prio 1u //�ϸ����ȼ�
//#define camera_VSYNC PORTC_IRQHandler
/*�����ж�����PTC18*/
#define PIX_PORT PORTC
#define PIX_GPIO GPIOC
#define PIX_PIN 18u
#define PIX_DMA_CHANNEL_IRQn DMA0_DMA16_IRQn
#define DMAPORTCode kDmaRequestMux0PortC
#define PIX_DMA_Prio 2u //�Ը����ȼ�
#define DATALINE_PORT PORTC
#define DATALINE_GPIO GPIOC
#define DATALINE_GROUP GPIOC_BASE
#define DATALINE_PORT_NUM 8 //��һ�����źţ�     ����ptc0~ptc7Ϊ0 ��ptc8~ptc15Ϊ8 ����������
#define DATALINE_GROUP_PIN 1 //                 ����ptc0~ptc7Ϊ0 ��ptc8~ptc15Ϊ1 ����������
#define DATALINE_PDIR_OFFSET 0x10 //Port Data Input Register offset ��K66оƬ�ֲ�2191��ͨ�����ø�:Address: Base address + 10h offset
#define DATALINE_LOCATION GPIOC_BASE+DATALINE_PDIR_OFFSET+DATALINE_GROUP_PIN//���������������⼸�����������ŵ�PDIR��ַ��ǿ�ҽ����Լ���
#define CAMERA_UART UART3
///*����ͷ���ô����ж� UART_3 interrupt vector ID (number). */
//#define CAMERA_UART_RX_TX_IRQN UART3_RX_TX_IRQn
///*����ͷ���ô����ж����ȼ� UART_1 interrupt vector priority. */
//#define CAMERA_UART_RX_TX_IRQ_PRIORITY 3
///*�жϷ������ض���*/
//#define camera_config_handle UART3_RX_TX_IRQHandler
//#define CAMERA_UART_PORT PORTC
//#define CAMERA_UART_CLOCK_SRC UART3_CLK_SRC
//#define CAMERA_UART_RX_PIN 16u
//#define CAMERA_UART_TX_PIN 17u   

//����ͷ����ö��
typedef enum
{
	INIT = 0,               //����ͷ��ʼ������
	AUTO_EXP,               //�Զ��ع�����
	EXP_TIME,               //�ع�ʱ������
	FPS,                    //����ͷ֡������
	SET_COL,                //ͼ��������
	SET_ROW,                //ͼ��������
	LR_OFFSET,              //ͼ������ƫ������
	UD_OFFSET,              //ͼ������ƫ������
	GAIN,                   //ͼ��ƫ������
	CONFIG_FINISH,          //������λ����Ҫ����ռλ����

	SET_EXP_TIME = 0XF0,    //���������ع�ʱ������
	GET_STATUS,             //��ȡ����ͷ��������
	GET_VERSION,            //�̼��汾������

	SET_ADDR = 0XFE,        //�Ĵ�����ַ����
	SET_DATA                //�Ĵ�����������
}CMD;

#define BOARD_InitCamera camera_init_MT9V032
extern volatile bool CameraON; //���Ʊ�־λ���ڲ������ã���¼��ǰ����ͷ����ͬ���
extern volatile bool CameraInitialized;//��¼�Ƿ񾭹���ʼ��
extern volatile uint8_t if_EDMA_Init;
extern volatile uint8_t if_DMAMUX_Init;
extern volatile uint8_t mt9v032_finish_flag;  //һ��ͼ��ɼ���ɱ�־λ������ͬ�����µ�һ֡ͼ�����ʱ�ᱻ��1�����ֶ���0
extern uint8_t image_Buffer_0[ROW][COL];
#if defined(SMARTCAR_CAMERA_BUFFER)&&(SMARTCAR_CAMERA_BUFFER==2)
extern uint8_t image_Buffer_1[ROW][COL];
extern uint8_t image_Buffer_index;
#endif
int camera_init_MT9V032(void);
void camera_uart_init(void);
void camera_EDMA_Callback(edma_handle_t* handle, void* param, bool transferDone, uint32_t tcds);
void camera_config_get(void);
void camera_StopTransmittion();
void camera_StartTransmittion();
void camera_VSYNC(void);
void show_image_on_oled(uint8_t* image, uint16_t ro, uint16_t co);
uint8_t GetAvailableImageBufferIndex();


#endif
