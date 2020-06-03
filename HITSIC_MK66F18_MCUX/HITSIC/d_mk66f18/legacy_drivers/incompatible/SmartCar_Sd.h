#pragma once
/*
�������Ҫ��ͼ������ñ�ģ��
*/

#ifndef _SMARTCAR_SD_H
#define _SMARTCAR_SD_H
#include "stdint.h"
#include "fsl_common.h"
#include "fsl_sd.h"
#include "fsl_sysmpu.h"

// #define _SD_DISABLE


#ifndef _SD_DISABLE_

#define ROW 120
#define COL 188


/*! @brief Data block count accessed in card */
#define DATA_BLOCK_COUNT (COL * ROW / 512 + 1)
/*! @brief Start data block number accessed in card */
#define DATA_BLOCK_START (10000U)
/*! @brief Data buffer size. */
#define DATA_BUFFER_SIZE DATA_BLOCK_COUNT * 512
/* ��д���������Сbuffer size (in byte) for read/write operations */
#define BUFFER_SIZE (100U)
/*!
 *   @brief ��ȡSD����Ϣ
 */
static void CardInformationLog(sd_card_t *card);
static status_t sdcardWaitCardInsert(void);
//static FATFS g_fileSystem; /* File system object */
//static FIL g_fileObject;   /* File object */
///*! @brief Data written to the card ��֪�������*/
//SDK_ALIGN(uint8_t g_dataWrite[SDK_SIZEALIGN(DATA_BUFFER_SIZE, SDMMC_DATA_BUFFER_ALIGN_CACHE)],
//	MAX(SDMMC_DATA_BUFFER_ALIGN_CACHE, SDMMCHOST_DMA_BUFFER_ADDR_ALIGN));
///*! @brief Data read from the card */
//SDK_ALIGN(uint8_t g_dataRead[SDK_SIZEALIGN(DATA_BUFFER_SIZE, SDMMC_DATA_BUFFER_ALIGN_CACHE)],
//	MAX(SDMMC_DATA_BUFFER_ALIGN_CACHE, SDMMCHOST_DMA_BUFFER_ADDR_ALIGN));
//SDK_ALIGN(uint8_t g_bufferWrite[SDK_SIZEALIGN(BUFFER_SIZE, SDMMC_DATA_BUFFER_ALIGN_CACHE)],
//	MAX(SDMMC_DATA_BUFFER_ALIGN_CACHE, SDMMCHOST_DMA_BUFFER_ADDR_ALIGN));
//SDK_ALIGN(uint8_t g_bufferRead[SDK_SIZEALIGN(BUFFER_SIZE, SDMMC_DATA_BUFFER_ALIGN_CACHE)],
//	MAX(SDMMC_DATA_BUFFER_ALIGN_CACHE, SDMMCHOST_DMA_BUFFER_ADDR_ALIGN));

/*!
 *   @brief ������ PORTE_IRQHandler ���ⲿ�жϺ���, ps:  PORTE_IRQHandler  ��  startup_MK66F18.s�б�����
 *   #define key_interrupt PORTE_IRQHandler
 *   �����жϺ�������
 */
 /*! @brief SDMMC host detect card configuration host�ṹ��*/
static const sdmmchost_detect_card_t s_sdCardDetect = {
#ifndef BOARD_SD_DETECT_TYPE
	.cdType = kSDMMCHOST_DetectCardByGpioCD,
#else
	.cdType = BOARD_SD_DETECT_TYPE,
#endif
	.cdTimeOut_ms = (~0u),
};
/*! @brief SDMMC card power control configuration ��Դ���ƽṹ��*/
#if defined DEMO_SDCARD_POWER_CTRL_FUNCTION_EXIST
static const sdmmchost_pwr_card_t s_sdCardPwrCtrl = {
	.powerOn = BOARD_PowerOnSDCARD,.powerOnDelay_ms = 500U,.powerOff = BOARD_PowerOffSDCARD,.powerOffDelay_ms = 0U,
};
#endif

static uint8_t sd_inserted_flag = 0;
static volatile uint8_t sd_save_flag = 0;
static volatile int num = 0;//sd����ͼͼ��
static sd_card_t smartcar_sd;//sd���ṹ��
static uint8_t smart_buff[DATA_BUFFER_SIZE];//׼�����͵�����
static int GlobalControl = 0;
static int GlobalWatcher = 0;
static uint32_t label_sd = 0;

#endif // !_SD_DISABLE_
void sd_init(void);
void sd_initPins(void);
void sd_image_save(uint8_t(_IMG)[COL]);
void sd_image_save_start();
uint32_t creat_random_num(void);
#endif // !_SD_H_
