/*
 * test.c
 *
 *  Created on: Feb 9, 2020
 *      Author: lymes
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "main.h"
#include "cmsis_os.h"
#include "arm_math.h"
#include "w25qxx.h"
#include "wm8731.h"
#include "audioproc.h"

#include "lcd.h"
#include "bmp.h"
#include "digits.h"

#define MAX(a,b) ((a) > (b) ? (a) : (b))

/* BSP_LCD_... */
#include "stm32_adafruit_lcd.h"

// create 16bits color from RGB888 or BGR888
//#define RGB888TORGB565(r, g, b) ((r & 0b11111000) << 8 | (g & 0b11111100) << 3 | b >> 3)
//#define RGB888TOBGR565(r, g, b) (r >> 3 | (g & 0b11111100) << 3 | (b & 0b11111000) << 8)

#define DW 15
#define DH 25
#define F_OFFS_X 35
#define F_OFFS_Y 5



extern LCD_DrvTypeDef *lcd_drv;
extern I2S_HandleTypeDef hi2s3;
extern DMA_HandleTypeDef hdma_memtomem_dma2_stream0;


void mainApp(void);


uint16_t row_bars[WATERFALL_WIDTH * BAR_HEIGHT];

uint16_t framebuffer1[WATERFALL_WIDTH * WATERFALL_HEIGHT];
uint16_t framebuffer2[WATERFALL_WIDTH * WATERFALL_HEIGHT];
uint16_t *currentFramebuffer = framebuffer1;

extern audio_data_t fftSamples[IQ_BUFSZ];
extern uint8_t   row_indices[IQ_BLOCK_SIZE];
extern uint16_t  row_colors[IQ_BLOCK_SIZE];


uint8_t  localRowIndices[IQ_BLOCK_SIZE];


static uint8_t renderingRequested = 0;
volatile TaskHandle_t fftTaskToNotify = NULL;






void DMA2_Stream0_TransferComplete(DMA_HandleTypeDef *DmaHandle)
{
	uint16_t *backBuffer = currentFramebuffer == framebuffer1 ? framebuffer2 : framebuffer1;
	currentFramebuffer = backBuffer;
}



void update()
{
	fftTaskToNotify = xTaskGetCurrentTaskHandle();
	uint32_t ulNotificationValue = ulTaskNotifyTake( pdTRUE, pdMS_TO_TICKS( 1 ) );
	if ( ulNotificationValue != 1 ) return;

	prepareFFTData((AudioSample_t*)fftSamples, IQ_BUFSZ);
	uint16_t *backBuffer = currentFramebuffer == framebuffer1 ? framebuffer2 : framebuffer1;

	//arm_copy_q15((q15_t *)row_colors, (q15_t *)backBuffer, WATERFALL_WIDTH);

//	for ( int i = 0; i < WATERFALL_WIDTH; i++ )
//	{
//		uint16_t color = 0;
//		for (int j = 0; j < 4; j++ )
//		{
//			color = MAX( color, row_colors[2 * i + j] );
//		}
//		backBuffer[i] = color;
//	}

//	// zoom
	for ( int i = 0; i < WATERFALL_WIDTH / 4; i++ )
	{
		backBuffer[i * 4 + 0] = row_colors[i];
		backBuffer[i * 4 + 1] = row_colors[i];
		backBuffer[i * 4 + 2] = row_colors[i];
	}

	HAL_DMA_Start_IT(&hdma_memtomem_dma2_stream0, (uint32_t)currentFramebuffer, (uint32_t)&backBuffer[WATERFALL_WIDTH], WATERFALL_WIDTH * (WATERFALL_HEIGHT - 1));

	arm_copy_q7((q7_t *)row_indices, (q7_t *)localRowIndices, IQ_BLOCK_SIZE);

//	for ( int i = 0; i < WATERFALL_WIDTH; i++ )
//	{
//		uint8_t len = (localRowIndices[i] >> 2);
//		for ( int j = 0; j < BAR_HEIGHT; j++ )
//		{
//			row_bars[ j * WATERFALL_WIDTH + i ] = (BAR_HEIGHT - len - j) < 0 ? LCD_COLOR_WHITE : 0x0;
//		}
//	}

	for ( int i = 0; i < WATERFALL_WIDTH / 4; i++ )
	{
		uint8_t len = (localRowIndices[i] >> 2);
		for ( int j = 0; j < BAR_HEIGHT; j++ )
		{
			row_bars[ j * WATERFALL_WIDTH + i * 4 + 0 ] = (BAR_HEIGHT - len - j) < 0 ? LCD_COLOR_WHITE : 0x0;
			row_bars[ j * WATERFALL_WIDTH + i * 4 + 1 ] = (BAR_HEIGHT - len - j) < 0 ? LCD_COLOR_WHITE : 0x0;
		}
	}


	while (currentFramebuffer != backBuffer) osDelay(1);
	renderingRequested = 1;
    osDelay(10);
}


void render()
{
    BSP_LCD_FillBuffer( F_OFFS_X + DW * 0, F_OFFS_Y, DW, DH, (uint8_t*) dig[10]);
    BSP_LCD_FillBuffer( F_OFFS_X + DW * 1, F_OFFS_Y, DW, DH, (uint8_t*) dig[1]);
    BSP_LCD_FillBuffer( F_OFFS_X + DW * 2, F_OFFS_Y, DW, DH, (uint8_t*) dig[2]);
    BSP_LCD_FillBuffer( F_OFFS_X + DW * 3, F_OFFS_Y, DW, DH, (uint8_t*) dig[3]);
    BSP_LCD_FillBuffer( F_OFFS_X + DW * 4, F_OFFS_Y, DW, DH, (uint8_t*) dig[4]);
    BSP_LCD_FillBuffer( F_OFFS_X + DW * 5, F_OFFS_Y, DW, DH, (uint8_t*) dig[5]);
    BSP_LCD_FillBuffer( F_OFFS_X + DW * 6, F_OFFS_Y, DW, DH, (uint8_t*) dig[6]);
    BSP_LCD_FillBuffer( F_OFFS_X + DW * 7, F_OFFS_Y, DW, DH, (uint8_t*) dig[0]);

    if ( renderingRequested )
    {
    	BSP_LCD_FillBuffer(4, 47, WATERFALL_WIDTH, BAR_HEIGHT, (uint8_t*) row_bars);
    	BSP_LCD_FillBuffer(4, 70, WATERFALL_WIDTH, WATERFALL_HEIGHT, (uint8_t*) currentFramebuffer);
    	renderingRequested = 0;
    }
}


void init()
{
	W25qxx_Init();

	renderingRequested = 0;

	BSP_LCD_Init();
	BSP_LCD_Clear(LCD_COLOR_BLACK);
    BSP_LCD_SetFont(&Font24);
    BSP_LCD_SetTextColor(LCD_COLOR_YELLOW);
    BSP_LCD_SetBackColor(LCD_COLOR_BLACK);
    BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
	BSP_LCD_DrawRect(3, 69, WATERFALL_WIDTH+2, WATERFALL_HEIGHT+2);

    wm8731_init();
}

