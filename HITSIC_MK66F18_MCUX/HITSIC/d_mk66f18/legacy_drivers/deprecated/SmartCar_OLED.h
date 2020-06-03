/*********************************************************************************************************************
Smartcar OLED��ʾ�ײ�
�����ˣ���ѧ��
��ϵ��ʽ��18846446962
qq��512924543
��ע����������ҵ��ѧ���ܳ����¾��ֲ�ר�ã�����й¶����л��ɿƼ�
      OLED�����ж��ַ�ʽ����Ҫ�Լ�������ͬѧ�����в�ѯоƬ�ֲ�
					OLED���߶��壺
					------------------------------------ 
					OLEDҺ��      ��Ƭ��                        
    					PTD0          A15
    					PTD1          A16            
    					RES         A14    
    					DC          B16
					------------------------------------ 
 ********************************************************************************************************************/

#ifndef _SMARTCAR_OELD_H
#define _SMARTCAR_OELD_H

#include "fsl_debug_console.h"
#include "board.h"
#include "fsl_ftm.h"
#include "clock_config.h"
#include "pin_mux.h"
#include <stdio.h>
//OLED���ź궨��
#define BOARD_OLED_SCL_GPIO GPIOD
#define BOARD_OLED_SCL_PORT PORTD
#define BOARD_OLED_SCL_GPIO_PIN 12U
#define BOARD_OLED_SDA_GPIO GPIOD   
#define BOARD_OLED_SDA_PORT PORTD
#define BOARD_OLED_SDA_GPIO_PIN 14U 
#define BOARD_OLED_RST_GPIO GPIOD   
#define BOARD_OLED_RST_PORT PORTD
#define BOARD_OLED_RST_GPIO_PIN 13U 
#define BOARD_OLED_DC_GPIO GPIOD
#define BOARD_OLED_DC_PORT PORTD
#define BOARD_OLED_DC_GPIO_PIN 15U 

void OLED_Init(void);
void OLED_Fill(uint8_t dat);
void OLED_WrDat(uint8_t data);
void OLED_Wr6Dat(uint8_t data);
void OLED_PutPixel(uint8_t x,uint8_t y);
void OLED_ClrPixel(uint8_t x,uint8_t y);
void OLED_Set_Pos(uint8_t x, uint8_t y);
void OLED_P6x8Str(uint8_t x,uint8_t y,uint8_t ch[]);
void OLED_P8x16Str(uint8_t x,uint8_t y,uint8_t ch[]);
void OLED_HEXACSII(uint16_t hex,uint8_t* Print);
void OLED_Print_Num(uint8_t x, uint8_t y, int16_t num);
void dis_bmp(uint16_t high, uint16_t width, uint8_t *p,uint8_t value);
void OLED_Logo(void);
void OLED_P6x8Rst(uint8_t x,uint8_t y,uint8_t ch[]);
void Str_Clr(uint32_t x,uint32_t y,uint32_t num);
void image_size_half_forOLED(uint8_t *src,uint8_t *dst,const int row,const int col);
#endif
