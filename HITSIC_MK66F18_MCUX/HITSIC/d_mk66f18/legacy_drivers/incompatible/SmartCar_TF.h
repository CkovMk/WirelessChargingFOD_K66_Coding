#ifndef _SMARTCAR_TF_H
#define _SMARTCAR_TF_H
#include "fsl_clock.h"
#include "fsl_uart.h"
//�Ñ��޸�
#define UART_tf_PERIPHERAL UART0
#define UART_tf_CLOCK_SOURCE CLOCK_GetFreq(UART0_CLK_SRC)
#define UART_tf_SERIAL_RX_TX_IRQN UART0_RX_TX_IRQn    
#define UART_tf_SERIAL_RX_TX_IRQ_PRIORITY 0           //�����ж����ȼ�
#define UART_tf_SERIAL_RX_TX_IRQHANDLER UART0_RX_TX_IRQHandler     //�жϷ�������

void uart_tf_init(void);
int uart_tf_distance(void);


#endif

