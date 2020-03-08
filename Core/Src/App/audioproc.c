/*
 * audioproc.c
 *
 *  Created on: Mar 8, 2020
 *      Author: lymes
 */

#include "audioproc.h"
#include "arm_math.h"
#include "cmsis_os.h"
#include "wfcolors.h"


//arm_cfft_radix4_instance_f32 S;	/* ARM CFFT module */
extern const arm_cfft_instance_f32 arm_cfft_sR_f32_len512;
extern const arm_cfft_instance_f32 arm_cfft_sR_f32_len256;
extern const arm_cfft_instance_f32 arm_cfft_sR_f32_len128;


extern TaskHandle_t fftTaskToNotify;

audio_data_t fftSamples[IQ_BUFSZ] = {};

float32_t     i_buffer[IQ_BUFSZ];
float32_t     q_buffer[IQ_BUFSZ];
float32_t     fft_buffer[IQ_BLOCK_SIZE];

uint8_t   row_indices[IQ_BLOCK_SIZE];
uint16_t  row_colors[IQ_BLOCK_SIZE];


void audioProcessor(audio_data_t *src, uint16_t sz)
{
	if ( fftTaskToNotify )
	{
		arm_copy_q15(src, fftSamples, sz);
		BaseType_t xHigherPriorityTaskWoken = pdFALSE;
		/* Notify the task that the FFT samples are complete. */
		vTaskNotifyGiveFromISR( fftTaskToNotify, &xHigherPriorityTaskWoken );
		fftTaskToNotify = NULL;
	}
}


void prepareFFTData(AudioSample_t * const src, const uint16_t blockSize)
{
	uint32_t maxIndex;	/* Index in Output array where max value is */
	float32_t maxValue;

	for ( int i = 0; i < IQ_BLOCK_SIZE; i++ )
	{
		i_buffer[2 * i + 0] = (float32_t)src[i].l; // real part
		i_buffer[2 * i + 1] = 0; // imaginary part
		//q_buffer[2 * i + 0] = src[i].r;
		//q_buffer[2 * i + 1] = 0;
	}

    /* Process the data through the CFFT/CIFFT module */
	//arm_cfft_radix4_f32(&S, i_buffer);

	arm_cfft_f32(&arm_cfft_sR_f32_len256, i_buffer, 0, 1);	// Do FFT

	/* Process the data through the Complex Magniture Module for calculating the magnitude at each bin */
	arm_cmplx_mag_f32(i_buffer, fft_buffer, IQ_BLOCK_SIZE);

	/* Calculates maxValue and returns corresponding value */
	arm_max_f32(fft_buffer, IQ_BLOCK_SIZE / 2, &maxValue, &maxIndex);

	for ( int i = 0; i < IQ_BLOCK_SIZE; i++ )
	{
		float32_t val = (fft_buffer[i] / 150000.0);
		val = (val > 1.0) ? 1.0 : val;  // clip if needed
		uint8_t j = val * (NUMBER_WATERFALL_COLOURS - 1);
		row_indices[i] = j;//(fft_buffer[i] / maxValue) * (NUMBER_WATERFALL_COLOURS - 1);
		row_colors[i] = waterfall_rainbow[j];//waterfall_blue[j];
	}
}


