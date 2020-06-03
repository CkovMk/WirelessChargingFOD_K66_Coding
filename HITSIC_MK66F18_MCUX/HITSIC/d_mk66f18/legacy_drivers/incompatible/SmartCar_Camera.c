/******************************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2019,���������ܳ����¾��ֲ�
 * All rights reserved.
 *
 * @file       		����ͷ��غ�����������棩
 * @company	        ���������ܳ����¾��ֲ�
 * @author     		��ѧ�� qq512924543
 * @version    		v1.0
 * @Software 		IAR 7.7+
 * @Target core		K66
 * @date       		2019-9-27
 *
 * @note��
		����ͷ���Ź̶�����ò�Ҫ���׸��ģ�ʹ��ʱ����camera_init_MT9V032()
		�������г�ʼ����ÿ��ͼ��ɼ�������Ὣmt9v032_finish_flag��Ϊ1��ͼ��
		�ɼ����������image_Buffer_0�ڡ�ÿ�ζ�ȡ��ͼ��ǵý�mt9v032_finish_flag
		���㡣

		��������ҵ��ѧ���ܳ����¾��ֲ�ר�ã�����й¶
***************************************************************************************************************************/
#include "SmartCar_Camera.h"

volatile bool CameraON = false; //���Ʊ�־λ���ڲ������ã���¼��ǰ����ͷ����ͬ���
volatile bool CameraInitialized = false;//��¼�Ƿ񾭹���ʼ��
//volatile bool CameraDoingTransmission = false;//��¼��ǰ״̬��true��ζ�ŵ�ǰ���ڲɼ�һ��ͼ���У��ӷ������жϿ�ʼ��dma�������
volatile uint8_t if_EDMA_Init = 0;
volatile uint8_t if_DMAMUX_Init = 0;
volatile uint8_t mt9v032_finish_flag = 0;//һ��ͼ��ɼ���ɱ�־λ������ͬ�����µ�һ֡ͼ�����ʱ�ᱻ��1�����ֶ���0
uint8_t image_Buffer_0[ROW][COL];
edma_transfer_config_t transferToBuffer0Config;
#if defined(SMARTCAR_CAMERA_BUFFER)&&(SMARTCAR_CAMERA_BUFFER==2)
uint8_t image_Buffer_index = 0;//��־��ǰmt9v032_finish_flag = 1;ʱ���ĸ�������Ч
uint8_t image_Buffer_1[ROW][COL];
edma_transfer_config_t transferToBuffer1Config;
#endif

uint8_t image_size_half[ROW / 2][COL / 2];

//uint16_t version;
uint8_t   receive[3];
//uint8_t   receive_num = 0;
//uint8_t   uart_receive_flag = 1;
edma_handle_t Camera_Mission_EDMA_Handle;
edma_transfer_config_t transferConfig;
edma_config_t userConfig;

//��Ҫ���õ�����ͷ������
int16_t MT9V032_CFG[CONFIG_FINISH][2] =
{
  {AUTO_EXP,          0},   //�Զ��ع�����      ��Χ1-63 0Ϊ�ر� ����Զ��ع⿪��  EXP_TIME�������õ����ݽ����Ϊ����ع�ʱ�䣬Ҳ�����Զ��ع�ʱ�������
  //һ������ǲ���Ҫ����������ܣ���Ϊ�������ع���һ�㶼�ȽϾ��ȣ�����������߷ǳ������ȵ�������Գ������ø�ֵ������ͼ���ȶ���
  {EXP_TIME,          900}, //�ع�ʱ��          ����ͷ�յ�����Զ����������ع�ʱ�䣬������ù���������Ϊ�������������ع�ֵ
  {FPS,               50},  //ͼ��֡��          ����ͷ�յ�����Զ���������FPS���������������Ϊ������������FPS
  {SET_COL,           COL}, //ͼ��������        ��Χ1-752     K60�ɼ���������188
  {SET_ROW,           ROW}, //ͼ��������        ��Χ1-480
  {LR_OFFSET,         0},   //ͼ������ƫ����    ��ֵ ��ƫ��   ��ֵ ��ƫ��  ��Ϊ188 376 752ʱ�޷�����ƫ��    ����ͷ��ƫ�����ݺ���Զ��������ƫ�ƣ�������������ü�����������ƫ��
  {UD_OFFSET,         0},   //ͼ������ƫ����    ��ֵ ��ƫ��   ��ֵ ��ƫ��  ��Ϊ120 240 480ʱ�޷�����ƫ��    ����ͷ��ƫ�����ݺ���Զ��������ƫ�ƣ�������������ü�����������ƫ��
  {GAIN,              64},  //ͼ������          ��Χ16-64     ����������ع�ʱ��̶�������¸ı�ͼ�������̶�


  {INIT,              0}    //����ͷ��ʼ��ʼ��
};
//������ͷ�ڲ���ȡ������������
int16_t GET_CFG[CONFIG_FINISH - 1][2] =
{
  {AUTO_EXP,          0},   //�Զ��ع�����      
  {EXP_TIME,          0},   //�ع�ʱ��          
  {FPS,               0},   //ͼ��֡��          
  {SET_COL,           0},   //ͼ��������        
  {SET_ROW,           0},   //ͼ��������        
  {LR_OFFSET,         0},   //ͼ������ƫ����    
  {UD_OFFSET,         0},   //ͼ������ƫ����    
  {GAIN,              0},   //ͼ������          
};


void camera_uart_init()
{
	uart_init(CAMERA_UART, 9600U);
}

//void uart_getchar(UART_Type* base, uint8_t* ch)
//{
//	UART_ReadBlocking(base, ch, 1);
//}
//void uart_putchar(UART_Type* base, uint8_t ch)
//{
//	UART_WriteBlocking(base, &ch, 1);
//}
//void simple_delay(long t)
//{
//	while (t--);
//}


gpio_pin_config_t Input_port = {
	 .pinDirection = kGPIO_DigitalInput,
	 .outputLogic = 0U
};
port_pin_config_t Port_PULLDOWN_config = {
	   kPORT_PullDown,
	   kPORT_FastSlewRate,
	   kPORT_PassiveFilterDisable,
	   kPORT_OpenDrainDisable,
	   kPORT_LowDriveStrength,
	   kPORT_MuxAsGpio,
};
//uint32_t* debug;

/**********************************************************************************************************************
*  @brief      ����ͷ���ų�ʼ��
*  @return     void
*  @since      v1.0
*  Sample usage:          camera_port_initialize();
**********************************************************************************************************************/
void camera_port_initialize()
{
	/*���°˸����������߳�ʼ��*/
	PORT_SetPinMux(DATALINE_PORT, DATALINE_PORT_NUM + 0, kPORT_MuxAsGpio);
	PORT_SetPinMux(DATALINE_PORT, DATALINE_PORT_NUM + 1, kPORT_MuxAsGpio);
	PORT_SetPinMux(DATALINE_PORT, DATALINE_PORT_NUM + 2, kPORT_MuxAsGpio);
	PORT_SetPinMux(DATALINE_PORT, DATALINE_PORT_NUM + 3, kPORT_MuxAsGpio);
	PORT_SetPinMux(DATALINE_PORT, DATALINE_PORT_NUM + 4, kPORT_MuxAsGpio);
	PORT_SetPinMux(DATALINE_PORT, DATALINE_PORT_NUM + 5, kPORT_MuxAsGpio);
	PORT_SetPinMux(DATALINE_PORT, DATALINE_PORT_NUM + 6, kPORT_MuxAsGpio);
	PORT_SetPinMux(DATALINE_PORT, DATALINE_PORT_NUM + 7, kPORT_MuxAsGpio);
	PORT_SetPinConfig(DATALINE_PORT, DATALINE_PORT_NUM + 0, &Port_PULLDOWN_config);
	PORT_SetPinConfig(DATALINE_PORT, DATALINE_PORT_NUM + 1, &Port_PULLDOWN_config);
	PORT_SetPinConfig(DATALINE_PORT, DATALINE_PORT_NUM + 2, &Port_PULLDOWN_config);
	PORT_SetPinConfig(DATALINE_PORT, DATALINE_PORT_NUM + 3, &Port_PULLDOWN_config);
	PORT_SetPinConfig(DATALINE_PORT, DATALINE_PORT_NUM + 4, &Port_PULLDOWN_config);
	PORT_SetPinConfig(DATALINE_PORT, DATALINE_PORT_NUM + 5, &Port_PULLDOWN_config);
	PORT_SetPinConfig(DATALINE_PORT, DATALINE_PORT_NUM + 6, &Port_PULLDOWN_config);
	PORT_SetPinConfig(DATALINE_PORT, DATALINE_PORT_NUM + 7, &Port_PULLDOWN_config);
	GPIO_PinInit(DATALINE_GPIO, DATALINE_PORT_NUM + 0, &Input_port);
	GPIO_PinInit(DATALINE_GPIO, DATALINE_PORT_NUM + 1, &Input_port);
	GPIO_PinInit(DATALINE_GPIO, DATALINE_PORT_NUM + 2, &Input_port);
	GPIO_PinInit(DATALINE_GPIO, DATALINE_PORT_NUM + 3, &Input_port);
	GPIO_PinInit(DATALINE_GPIO, DATALINE_PORT_NUM + 4, &Input_port);
	GPIO_PinInit(DATALINE_GPIO, DATALINE_PORT_NUM + 5, &Input_port);
	GPIO_PinInit(DATALINE_GPIO, DATALINE_PORT_NUM + 6, &Input_port);
	GPIO_PinInit(DATALINE_GPIO, DATALINE_PORT_NUM + 7, &Input_port);
	/*���ϰ˸����������߳�ʼ��*/
	/*���³��ж��߳�ʼ��*/
	//DisableIRQ(VSY_IRQn);//�س��ж�
	PORT_SetPinConfig(VSY_PORT, VSY_PIN, &Port_PULLDOWN_config);//�������Ź���
	//PORT_SetPinInterruptConfig(VSY_PORT, VSY_PIN, kPORT_InterruptFallingEdge);//�����ж�
	GPIO_PinInit(VSY_GPIO, VSY_PIN, &Input_port);//���÷������루Ĭ�ϱ������룬����Ҫ��
	//NVIC_SetPriority(VSY_IRQn, VSY_Prio);//�ж����ȼ������ȼ�Ҫ��һ��
	//EnableIRQ(VSY_IRQn);//�����ж�
	/*���ϳ��ж��߳�ʼ��*/
	/*���������ж��߳�ʼ��*/
	DisableIRQ(PIX_DMA_CHANNEL_IRQn);
	PORT_SetPinConfig(PIX_PORT, PIX_PIN, &Port_PULLDOWN_config);//�������Ź���
	PORT_SetPinInterruptConfig(PIX_PORT, PIX_PIN, kPORT_DMARisingEdge);//�����жϣ�dma�ж�
	GPIO_PinInit(PIX_GPIO, PIX_PIN, &Input_port);//���÷������루Ĭ�ϱ������룬����Ҫ��
	NVIC_SetPriority(PIX_DMA_CHANNEL_IRQn, PIX_DMA_Prio);//�ж����ȼ������ȼ�Ҫ��һ��
	//EnableIRQ(PIX_DMA_CHANNEL_IRQn);
	/*���������ж��߳�ʼ��*/
}

/**********************************************************************************************************************
*  @brief      MT9V032����ͷ��ʼ��
*  @return     void
*  @since      v1.0
*  Sample usage:          camera_init_MT9V032();
**********************************************************************************************************************/
int camera_init_MT9V032(void)
{
	CameraON = false;
	CameraInitialized = false;
	/*���ò���    ������ο�ʹ���ֲ�*/
	camera_uart_init();	                 //��ʼ������ ��������ͷ    
	systick_delay_ms(50);        //�ȴ�����ͷ�ϵ��ʼ���ɹ�
	int16_t temp = 0;
	uint32_t delay_times = 0;
	uint8_t RXtemp = 0;
	uint8_t  send_buffer[4];
	for (int i = 0; i < CONFIG_FINISH; i++)//��ʼ��������ͷ�����³�ʼ��
	{
		send_buffer[0] = 0xA5;
		send_buffer[1] = MT9V032_CFG[i][0];
		temp = MT9V032_CFG[i][1];
		send_buffer[2] = temp >> 8;
		send_buffer[3] = (uint8_t)temp;
		UART_WriteBlocking(CAMERA_UART, send_buffer, 4);
		systick_delay_ms(1);
	}
	while (!(RXtemp == 0xA5 || RXtemp == 0xff))
	{
		while (!CAMERA_UART->RCFIFO)//fifoΪ��
		{
			delay_times++;
			systick_delay_ms(1);
			if (delay_times >= 1000)
			{
				PRINTF("time out! Did not receive a reply from camera\r\n!");
				return -1000;
			}
		}
		RXtemp = CAMERA_UART->D;
	}
	//����set_exposure_time�����������õ��ع����ݲ��洢��eeprom��
	//��ȡ���ñ��ڲ鿴�����Ƿ���ȷ
	camera_config_get();
	//��������Ƿ�һ��
	PRINTF("camera AUTO_EXP	= %d\n", (int)GET_CFG[AUTO_EXP - 1][1]);
	PRINTF("camera EXP_TIME	= %d\n", (int)GET_CFG[EXP_TIME - 1][1]);
	PRINTF("camera FPS		= %d\n", (int)GET_CFG[FPS - 1][1]);
	PRINTF("camera SET_COL	= %d\n", (int)GET_CFG[SET_COL - 1][1]);
	PRINTF("camera SET_ROW	= %d\n", (int)GET_CFG[SET_ROW - 1][1]);
	PRINTF("camera LR_OFFSET	= %d\n", (int)GET_CFG[LR_OFFSET - 1][1]);
	PRINTF("camera UD_OFFSET	= %d\n", (int)GET_CFG[UD_OFFSET - 1][1]);
	PRINTF("camera GAIN		= %d\n", (int)GET_CFG[GAIN - 1][1]);
	if ((MT9V032_CFG[SET_COL - 1][1] != GET_CFG[SET_COL - 1][1])
		|| (MT9V032_CFG[SET_ROW - 1][1] != GET_CFG[SET_ROW - 1][1]))
	{
		PRINTF("camera cfg error\r\n!");
		return -1001;
	}
	

	/*��ʼ������ͷ��������*/
	camera_port_initialize();


	/* Configure DMAMUX DMA����Դ·�� */
	if (if_DMAMUX_Init == 0)
	{
		if_DMAMUX_Init = 1;
		DMAMUX_Init(DMAMUX_SELECT);
	}
#if defined(FSL_FEATURE_DMAMUX_HAS_A_ON) && FSL_FEATURE_DMAMUX_HAS_A_ON//���Ӵ���
	DMAMUX_EnableAlwaysOn(DMAMUX_SELECT, DMA_CHANNEL_SELECT, true);//���Ӵ���
#else//���Ӵ���
	DMAMUX_SetSource(DMAMUX_SELECT, DMA_CHANNEL_SELECT, DMAPORTCode);
	//�ź�ѡ��
	//����һû��ѡ��������DMAͨ��������FSL_FEATURE_DMAMUX_MODULE_CHANNEL������32����
	//������DMA����Դ
#endif /* FSL_FEATURE_DMAMUX_HAS_A_ON *///���Ӵ���
	DMAMUX_EnableChannel(DMAMUX_SELECT, DMA_CHANNEL_SELECT);//����DMAͨ��0����DMAMUX_SetSource����

	EDMA_GetDefaultConfig(&userConfig);//��ȡĬ������
	if (if_EDMA_Init == 0)
	{
		if_EDMA_Init = 1;
		EDMA_Init(DMA_SELECT, &userConfig);//��ʼ��
	}
	EDMA_SetBandWidth(DMA_SELECT, DMA_CHANNEL_SELECT, kEDMA_BandwidthStall8Cycle);//��Ϣ
	//EDMA_SetChannelPreemptionConfig(DMA_SELECT,0u,&ecpc);//���ȼ��ܸ�
	EDMA_EnableAutoStopRequest(DMA_SELECT, DMA_CHANNEL_SELECT, true);
	EDMA_CreateHandle(&Camera_Mission_EDMA_Handle, DMA_SELECT, DMA_CHANNEL_SELECT);//�������ʹ���Ǹ�ͨ������Ϣ
	EDMA_SetCallback(&Camera_Mission_EDMA_Handle, camera_EDMA_Callback, NULL);//�ص���������
	EDMA_PrepareTransfer(&transferToBuffer0Config, (void*)(uint32_t)(DATALINE_LOCATION), 1,
		image_Buffer_0, 1, 1, COL * ROW, kEDMA_PeripheralToMemory);//д������0
#if defined(SMARTCAR_CAMERA_BUFFER)&&(SMARTCAR_CAMERA_BUFFER==2)
	EDMA_PrepareTransfer(&transferToBuffer1Config, (void*)(uint32_t)(DATALINE_LOCATION), 1,
		image_Buffer_1, 1, 1, COL * ROW, kEDMA_PeripheralToMemory);//д������1
	image_Buffer_index = 0;
#endif
	port_irq_init(VSY_PORT, VSY_PIN, kPORT_InterruptFallingEdge, 0, camera_VSYNC);
	EnableIRQ(PIX_DMA_CHANNEL_IRQn);//�������ж�/DMA����
	CameraON = true;
	CameraInitialized = true;
	EnableInterrupts;
	return 0;
}


/**********************************************************************************************************************
*  @brief      MT9V032����ͷ��ʼ��
*  @return     void
*  @since      v1.0
*  Sample usage:          camera_init_MT9V032();
**********************************************************************************************************************/
extern void dis_bmp(uint16_t high, uint16_t width, uint8_t* p, uint8_t value);

void camera_VSYNC(void)
{
	port_irq_deinit(VSY_PORT, VSY_PIN);//�رճ��жϣ����ڲɼ����֮����
#if defined(SMARTCAR_CAMERA_BUFFER)&&(SMARTCAR_CAMERA_BUFFER==2)
	if (image_Buffer_index == 0)//�������0��Ч���ύ����1
	{
		EDMA_SubmitTransfer(&Camera_Mission_EDMA_Handle, &transferToBuffer1Config);
	}
	else
	{
		EDMA_SubmitTransfer(&Camera_Mission_EDMA_Handle, &transferToBuffer0Config);
	}
#else
	EDMA_SubmitTransfer(&Camera_Mission_EDMA_Handle, &transferToBuffer0Config);
#endif
	EDMA_StartTransfer(&Camera_Mission_EDMA_Handle);//����
}

void camera_StartTransmittion()
{
	CameraON = true;
	port_irq_init(VSY_PORT, VSY_PIN, kPORT_InterruptFallingEdge, 0, camera_VSYNC);
}



inline void camera_StopTransmittion()
{
	CameraON = false;
	port_irq_deinit(VSY_PORT, VSY_PIN);//�رճ��жϣ����ڲɼ����֮����
}

void show_image_on_oled(uint8_t* image, uint16_t ro, uint16_t co)
{
	image_size_half_forOLED((uint8_t*)image, (uint8_t*)image_size_half, ro, co);
	dis_bmp(ro / 2, co / 2, (uint8_t*)image_size_half, 100);//����ʾ����ɺ���������һ���ж�
}
uint8_t GetAvailableImageBufferIndex()
{
#if defined(SMARTCAR_CAMERA_BUFFER)&&(SMARTCAR_CAMERA_BUFFER==2)
	return image_Buffer_index;
#else
	return 0;
#endif
}
///*ǿ���������±�־λCameraDoingTransmission����������Ҫ�ȴ��ɼ���������Ŀ*/
//int UpdateStatusNOW()
//{
//	int t = EDMA_GetRemainingMajorLoopCount(DMA_SELECT, DMA_CHANNEL_SELECT);
//	//��ȡʣ���DMAѭ����
//	if (t != 0)
//	{
//		CameraDoingTransmission = true;
//	}
//	else
//	{//�ľ���һ��ͼ���DMA�����Ѿ����
//		CameraDoingTransmission = false;
//	}
//	return t;
//}

/**********************************************************************************************************************
*  @brief      MT9V032����ͷDMA����ж�   User callback function for EDMA transfer.
*  @param      NULL
*  @return     void
*  @since      v1.0
*  Sample usage:				��isr.c�����ȴ�����Ӧ���жϺ�����Ȼ����øú���(֮�����������жϱ�־λ)
************************************************************************************************************************/
void camera_EDMA_Callback(edma_handle_t* handle, void* param, bool transferDone, uint32_t tcds)
{
	if (transferDone)
	{
		EDMA_ClearChannelStatusFlags(DMA_SELECT, DMA_CHANNEL_SELECT, kEDMA_InterruptFlag);
		mt9v032_finish_flag = 1;
#if defined(SMARTCAR_CAMERA_BUFFER)&&(SMARTCAR_CAMERA_BUFFER==2)
		image_Buffer_index = image_Buffer_index ^ 0x01;//�������
#else
#endif
		if (CameraON)
		{
			port_irq_init(VSY_PORT, VSY_PIN, kPORT_InterruptFallingEdge, 0, camera_VSYNC);
		}
	}
}



/////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////���¸�����ʼ�������ÿ�///////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////
//void camera_config_handle()
//{
//	/* If new data arrived. */
//	if ((kUART_RxDataRegFullFlag | kUART_RxOverrunFlag) & UART_GetStatusFlags(CAMERA_UART))
//	{
//		mt9v032_cof_uart_interrupt();
//	}
//
//}
/***********************************************************************************************************************
*  @brief      MT9V032����ͷ�����жϺ���
*  @param      NULL
*  @return     void
*  @since      v1.0
*  Sample usage:
//*  @note       �ú�����ISR�ļ� ����3�жϳ��򱻵���
//************************************************************************************************************************/
//void mt9v032_cof_uart_interrupt(void)
//{
//	uart_getchar(CAMERA_UART, &receive[receive_num]);;
//	receive_num++;
//
//	if (1 == receive_num && 0XA5 != receive[0])  receive_num = 0;
//	if (3 == receive_num)
//	{
//		receive_num = 0;
//		uart_receive_flag = 1;
//	}
//
//}

/***********************************************************************************************************************
*  @brief      ��ȡ����ͷ�ڲ�������Ϣ
*  @param      NULL
*  @return     void
*  @since      v1.0
*  Sample usage:				���øú���ǰ���ȳ�ʼ��uart2
************************************************************************************************************************/
void camera_config_get(void)
{
	int16_t temp, i;
	uint8_t  send_buffer[4];
	uint8_t tempppp = 0;
	uint8_t txlen;
	uint8_t rxlen;
	while (CAMERA_UART->RCFIFO)//fifoΪ��
	{
		tempppp = CAMERA_UART->D;
	}
	for (i = 0; i < CONFIG_FINISH - 1; i++)
	{
		send_buffer[0] = 0xA5;
		send_buffer[1] = GET_STATUS;
		temp = GET_CFG[i][0];
		send_buffer[2] = temp >> 8;
		send_buffer[3] = (uint8_t)temp;
		txlen = 4;
		rxlen = 3;
		while (txlen || rxlen)
		{
			if ((CAMERA_UART->RCFIFO) && rxlen != 0)
			{
				receive[3 - rxlen] = CAMERA_UART->D;
				if (receive[0] == 0xa5) {
					rxlen--;
				}
			}
			if ((CAMERA_UART->S1 & UART_S1_TDRE_MASK) && txlen != 0)
			{
				CAMERA_UART->D = send_buffer[4 - txlen];
				txlen--;
			}
		}
		//UART_WriteBlocking(CAMERA_UART, send_buffer, 4);
		//UART_ReadBlocking(CAMERA_UART, receive, 3);
		GET_CFG[i][1] = receive[1] << 8 | receive[2];
		//PRINTF("b0=%#x b1=%#x b2=%#x\n", receive[0], receive[1], receive[2]);
		//PRINTF("%d\n", (int)GET_CFG[i][1]);
	}
}

/***********************************************************************************************************************
*  @brief      ��ȡ����ͷ�̼��汾
*  @param      NULL
*  @return     void
*  @since      v1.0
*  Sample usage:				���øú���ǰ���ȳ�ʼ��uart2
************************************************************************************************************************/
//uint16_t get_version(void)
//{
//	uint16_t temp;
//	uint8_t  send_buffer[4];
//	send_buffer[0] = 0xA5;
//	send_buffer[1] = GET_STATUS;
//	temp = GET_VERSION;
//	send_buffer[2] = temp >> 8;
//	send_buffer[3] = (uint8_t)temp;
//
//	UART_WriteBlocking(CAMERA_UART, send_buffer, 4);
//
//	uart_receive_flag = 1;  //����¥�����
//
//	//�ȴ����ܻش�����
//	while (!uart_receive_flag);
//	uart_receive_flag = 0;
//
//	return ((uint16_t)(receive[1] << 8) | receive[2]);
//}

/***********************************************************************************************************************
*  @brief      ������������ͷ�ع�ʱ��
*  @param      light   �����ع�ʱ��Խ��ͼ��Խ��������ͷ�յ������ݷֱ��ʼ�FPS��������ع�ʱ��������õ����ݹ�����ô����ͷ��������������ֵ
*  @return     uint16_t  ��ǰ�ع�ֵ������ȷ���Ƿ���ȷд��
*  @since      v1.0
*  Sample usage:
************************************************************************************************************************/
//uint16_t set_exposure_time(uint16_t light)
//{
//	uint16_t temp;
//	uint8_t  send_buffer[4];
//
//	send_buffer[0] = 0xA5;
//	send_buffer[1] = SET_EXP_TIME;
//	temp = light;
//	send_buffer[2] = temp >> 8;
//	send_buffer[3] = (uint8_t)temp;
//
//	UART_WriteBlocking(CAMERA_UART, send_buffer, 4);
//
//
//	//�ȴ����ܻش�����
//	while (!uart_receive_flag);
//	uart_receive_flag = 0;
//
//	temp = receive[1] << 8 | receive[2];
//	return temp;
//
//}

