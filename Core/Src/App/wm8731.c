/*
 * wm8731.c
 *
 *  Created on: Feb 23, 2020
 *      Author: lymes
 */

#include "wm8731.h"
#include "stm32f4xx_hal.h"
#include "cmsis_os.h"
#include "arm_math.h"
#include "string.h"
#include "main.h"
#include "audioproc.h"


audio_data_t RX_BUFFER[BUFF_LEN] = {};
audio_data_t TX_BUFFER[BUFF_LEN] = {};


extern I2C_HandleTypeDef hi2c1;
extern I2S_HandleTypeDef hi2s3;


static uint8_t DevAddr = 0b00110100;

static uint8_t resetAddr    =  0b00011110 ; // Reset
static uint8_t resetData[1] = {0b00000000};

static uint8_t pdccAddr    =  0b00001100 ; // Power Down Control
static uint8_t pdccData[1] = {0b00000000};

static uint8_t daifAddr    =  0b00001110 ; // Digital Audio Interface Format
//static uint8_t daifData[1] = {0b01000010}; // 48kHz 16bit I2S Master Mode
static uint8_t daifData[1] = {0b01001110}; // 96kHz 32bit I2S Master Mode


static uint8_t linVolAddr    =  0b00000000;
static uint8_t linVolData[1] = {LINVOL};

static uint8_t rinVolAddr    =  0b00000010;
static uint8_t rinVolData[1] = {RINVOL};

static uint8_t lhpVolAddr    =  0b00000100;
static uint8_t lhpVolData[1] = {LHPVOL};

static uint8_t rhpVolAddr    =  0b00000110 ;
static uint8_t rhpVolData[1] = {RHPVOL};

static uint8_t sampAddr      =  0b00010000 ; // Sampling control register
static uint8_t sampData[1]   =  {0b00011100} ; // 96K, Normal
//static uint8_t sampData[1]   =  {0b00000000} ; // 48K, Normal


static uint8_t aapcAddr    =  0b00001000 ; // Analog Audio Path Control
static uint8_t aapcData[1] = {0b00010100};

static uint8_t dapcAddr    =  0b00001010 ; // Digital Audio Path Control
static uint8_t dapcData[1] = {0b00000000};

static uint8_t aaccAddr    =  0b00010010 ; // Active Control
static uint8_t aaccData[1] = {0b00000001};



void HAL_I2SEx_TxRxCpltCallback(I2S_HandleTypeDef *hi2s)
{
	arm_copy_q15(&RX_BUFFER[IQ_BUFSZ], &TX_BUFFER[0], IQ_BUFSZ);
	audioProcessor(&RX_BUFFER[IQ_BUFSZ], IQ_BUFSZ);
}


void HAL_I2SEx_TxRxHalfCpltCallback(I2S_HandleTypeDef *hi2s)
{
	arm_copy_q15(&RX_BUFFER[0], &TX_BUFFER[IQ_BUFSZ], IQ_BUFSZ);
	audioProcessor(&RX_BUFFER[0], IQ_BUFSZ);
}


void wm8731_init(void)
{
	// reset
	HAL_I2C_Mem_Write(&hi2c1, DevAddr, resetAddr, 1, (uint8_t*)resetData, 1, 1000);

	// power reduction register
	// turn everything on
	HAL_I2C_Mem_Write(&hi2c1, DevAddr, pdccAddr, 1, (uint8_t*)pdccData, 1, 1000);

	// Digital Audio Interface Format
	// 48kHz 16bit I2S Master Mode
	HAL_I2C_Mem_Write(&hi2c1,DevAddr, daifAddr, 1, (uint8_t*)daifData, 1, 1000);

	// left in setup register
	linVolData[0] = 40;
	HAL_I2C_Mem_Write(&hi2c1,DevAddr, linVolAddr, 1, (uint8_t*)linVolData, 1, 1000);

	// right in setup register
	rinVolData[0] = 40;
	HAL_I2C_Mem_Write(&hi2c1,DevAddr, rinVolAddr, 1, (uint8_t*)rinVolData, 1, 1000);

	// left headphone setup register
	lhpVolData[0] = 120;
	HAL_I2C_Mem_Write(&hi2c1,DevAddr, lhpVolAddr, 1, (uint8_t*)lhpVolData, 1, 1000);

	// right headphone setup register
	rhpVolData[0] = 120;
	HAL_I2C_Mem_Write(&hi2c1,DevAddr, rhpVolAddr, 1, (uint8_t*)rhpVolData, 1, 1000);

	// digital audio path configuration
	//dapcData[0] = ADCHPD;
	HAL_I2C_Mem_Write(&hi2c1, DevAddr, dapcAddr, 1, (uint8_t*)dapcData, 1, 1000);

	// analog audio path configuration
	//aapcData[0] = (uint8_t)((SIDEATT << 6)|(SIDETONE << 5)|(DACSEL << 4)|(BYPASS << 3)|(INSEL << 2)|(MUTEMIC << 1)|(MICBOOST << 0));
	HAL_I2C_Mem_Write(&hi2c1, DevAddr, aapcAddr, 1, (uint8_t*)aapcData, 1, 1000);

	// sampling
	HAL_I2C_Mem_Write(&hi2c1, DevAddr, sampAddr, 1, (uint8_t*)sampData, 1, 1000);

	// LININ, CLKOUT power down
	pdccData[0] = 0x41;
	HAL_I2C_Mem_Write(&hi2c1, DevAddr, pdccAddr, 1, (uint8_t*)pdccData, 1, 1000);

	// codec enable
	HAL_I2C_Mem_Write(&hi2c1, DevAddr, aaccAddr, 1, (uint8_t*)aaccData, 1, 1000);

    osDelay(1);
	HAL_I2SEx_TransmitReceive_DMA(&hi2s3, (uint16_t*)TX_BUFFER, (uint16_t*)RX_BUFFER, BUFF_LEN);
}



