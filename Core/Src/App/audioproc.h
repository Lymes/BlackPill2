/*
 * audioproc.h
 *
 *  Created on: Mar 8, 2020
 *      Author: lymes
 */

#ifndef _AUDIOPROC_H_
#define _AUDIOPROC_H_

#include <stdlib.h>
#include <stdint.h>


#define BUFF_LEN 1024

#define	IQ_BUFSZ 	  (BUFF_LEN / 2) /* Half of total buffer, since in each interrupte we get half of the total buffer filled */
#define IQ_BLOCK_SIZE (IQ_BUFSZ / 2) /* number of samples is half of size since we have 2 values (l/r or i/q) per sample */

#define WATERFALL_WIDTH 128 //(IQ_BLOCK_SIZE / 4)
#define BAR_HEIGHT 20
#define WATERFALL_HEIGHT 53


typedef struct {
    __packed int16_t l;
    __packed int16_t r;
} AudioSample_t;

typedef int16_t audio_data_t;


void audioProcessor(audio_data_t *src, uint16_t sz);
void prepareFFTData(AudioSample_t * const src, const uint16_t blockSize);


#endif /* _AUDIOPROC_H_ */
