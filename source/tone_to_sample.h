/*
 * @file        tone_to_sample.h
 * @brief       Function Stores sine and triangle wave in 1024 size buffer
 *
 *  Function prototype that Stores sine and triangle wave in 1024 size buffer
 *
 * @author      Swathi Venkatachalam
 * @tools       MCUXpresso IDE
 * @references  https://github.com/alexander-g-dean/ESF/blob/master/NXP/Code/Chapter_6/Analog%20Demo/src/main.c
 *              Musical tone Frequency: https://www.szynalski.com/tone-generator/
 *              Assignment 7
 *
 */

#ifndef TONE_TO_SAMPLE_H_
#define TONE_TO_SAMPLE_H_

#include <stdint.h>

#define BUFFER_SIZE (1024) //Number of tones

//3 tones
#define WAVEFORM1 (0)
#define WAVEFORM2 (1)
#define WAVEFORM3 (2)

//Frequencies of 3 tones
//tune 1
#define WAVEFORM1_FREQ (440) //A4
#define WAVEFORM2_FREQ (587) //D5
#define WAVEFORM3_FREQ (1175) //D6

//tune 2
#define WAVEFORM4_FREQ (294) //D4
#define WAVEFORM5_FREQ (659) //E5
#define WAVEFORM6_FREQ (698) //F5

//tune 3
#define WAVEFORM7_FREQ (1319) //E6
#define WAVEFORM8_FREQ (1397) //F6
#define WAVEFORM9_FREQ (1568) //G6

//tune 4
#define WAVEFORM10_FREQ (294) //D4
#define WAVEFORM11_FREQ (587) //D5
#define WAVEFORM12_FREQ (1175) //D6
//buffer struct to store frequency, samples per period, samples count and dac buffer for each waveform generated
typedef struct buffer
{
	int frequency;
	int samples_per_period;
	uint32_t sample_count;
	uint16_t dac_buffer[BUFFER_SIZE];
} buffer;

/*
 * @name   tone_to_samples
 * @brief  Function initiates DMA0
 *
 * Converting waveform to samples and storing it in 1024 buffer to send it to DAC
 *
 * @param  buffer *waveform_buffer, int sine_wave (Checks if it's a size wave or triangle wave)
 * @return void
 */

void tone_to_samples(buffer *buf);

#endif /* TONE_TO_SAMPLE_H_ */
