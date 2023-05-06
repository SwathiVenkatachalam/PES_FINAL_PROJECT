/*
 * @file        tone_to_sample.c
 * @brief       Function Stores sine and triangle wave in 1024 size buffer
 *
 *  Function Stores sine and triangle wave in 1024 size buffer
 *
 * @author      Swathi Venkatachalam
 * @tools       MCUXpresso IDE
 * @references  https://github.com/alexander-g-dean/ESF/blob/master/NXP/Code/Chapter_6/Analog%20Demo/src/main.c
 *              Assignment 7
 */

#include <musical_tones.h>
#include "tone_to_sample.h"
#include "fp_trig.h"
#include "tpm.h"
#include <stdio.h>
#include "fsl_debug_console.h"

#define DAC_MAX      (4095)
#define DAC_MIN      (ZERO)
#define ONE_FOURTH   (0.25)
#define THREE_FOURTH (0.75)

/*
 * @name   tone_to_samples
 * @brief  Function initiates DMA0
 *
 * Converting waveform to samples and storing it in 1024 buffer to send it to DAC
 *
 * @param  buffer *waveform_buffer, int sine_wave (Checks if it's a size wave or triangle wave)
 * @return void
 */
void tone_to_samples(buffer *waveform_buffer) //waveform_buffer: buffer to be filled //tells if its sine waveform or triangular waveform
{
	int i = ZERO;
	int frequency = waveform_buffer->frequency;
	int samples_per_period =  ZERO;
	uint32_t samples_count = ZERO;

	//samples per period calculated
	waveform_buffer->samples_per_period = OUTPUT_SAMPLE_RATE / frequency; //Samples per period
	samples_per_period = waveform_buffer->samples_per_period;

	//total number of samples calculated
	waveform_buffer->sample_count = (samples_per_period) * (BUFFER_SIZE / samples_per_period); //sample count = cycles * samples per period
	samples_count = waveform_buffer->sample_count;
	while(i < samples_count)
	{
		//Stores the output of sine function in buffer as a sample
		waveform_buffer->dac_buffer[i] = fp_sin(i * TWO_PI / samples_per_period) + TRIG_SCALE_FACTOR;
		i++;
	}
}
