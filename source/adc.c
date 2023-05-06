/*
 * @file        adc.c
 * @brief       Function Implementation of audio input module
 *
 * Contains ADC initialization, storing 1024 samples from dac onto buffer and waveform analysis functions
 *
 * @author      Swathi Venkatachalam
 * @tools       MCUXpresso IDE
 * @references  https://github.com/alexander-g-dean/ESF/blob/master/NXP/Code/Chapter_6/Analog%20-%20IR%20Proximity%20Sensor/Source/main.c
 *              https://github.com/ECEN5813/assignment-7-waveforms-SwathiVenkatachalam/blob/main/source/adc.c
 *              Assignment 7
 */

#include <stdio.h>
#include <fsl_debug_console.h>
#include <musical_tones.h>

#include "adc.h"

#include "MKL25Z4.h"
#include "tpm.h"
#include "autocorrelate.h"

#define SINGLE_ENDED_16BIT_CONV (3)
#define ADC_INPUT_CHANNEL       (23)
#define TPM1_OVFLW_TRIGG        (9)
#define BUFFER_SIZE             (1024)

/*
 * @name   init_ADC0
 * @brief  Function initiates ADC0
 *
 * ADC0 Function Initialization
 *
 * @param  void
 * @return void
 */

void init_ADC0()
{
	SIM->SCGC6 |= SIM_SCGC6_ADC0_MASK;

	ADC0->CFG1 = ADC_CFG1_ADLPC(ZERO)                      |
			     ADC_CFG1_ADIV(ZERO)                       |
				 ADC_CFG1_ADLSMP(ZERO)                     |
		         ADC_CFG1_MODE(SINGLE_ENDED_16BIT_CONV)    |
		         ADC_CFG1_ADICLK(ZERO); // 16 bit conversion mode

	//Disabled Compare function, DMA disabled, default reference voltage
	ADC0->SC2 = ADC_SC2_ADTRG(ONE)    |
			    ADC_SC2_ACFE(ZERO)  |
				ADC_SC2_DMAEN(ZERO) |
				ADC_SC2_REFSEL(ZERO);

	//ADC0 interrupt disabled, Single ended conversion 10111 When DIFF=0, AD23 is selected as input for ADC0
	ADC0->SC1[0] = ADC_SC1_AIEN(ZERO) |
			       ADC_SC1_DIFF(ZERO) |
				   ADC_SC1_ADCH(ADC_INPUT_CHANNEL);

	//calibrate ADC
	calibrate_ADC();

	//Select hardware trigger of ADC; Set trigger to TPM1 overflow
	SIM->SOPT7 = SIM_SOPT7_ADC0ALTTRGEN(ONE)              |
			     SIM_SOPT7_ADC0TRGSEL(TPM1_OVFLW_TRIGG) |
				 SIM_SOPT7_ADC0PRETRGSEL(ZERO);
}

/*
 * @name   adc_buffer
 * @brief  Function initiates ADC0
 *
 * Storing the 1024 samples from DAC to ADC Buffer input
 *
 * @param  uint16_t *adc_buffer (Pointer to ADC buffer to store 1024 samples from DAC)
 * @return void
 */

void adc_buffer(uint16_t *adc_buffer)
{
	//Start TPM1
	TPM1->SC |= TPM_SC_CMOD(ONE);

	for(int i = ZERO; i < BUFFER_SIZE; i++) //For 1024 samples
	{
		// wait for ADC to Complete
		while (!(ADC0->SC1[ZERO] & ADC_SC1_COCO_MASK))
	    {
			;
	    }
		// Store Analog to Digital result in buffer
		adc_buffer[i] = ADC0->R[ZERO];
	}
	//Stop TPM1
	TPM1->SC &= ~TPM_SC_CMOD_MASK;
}

/*
 * @name   adc_analysis
 * @brief  Function for ADC analysis
 *
 * Checks if the DAC generated waveforms are correct, since it's given as a input to ADC
 *
 * @param  uint16_t *adc_buffer (Pointer to ADC buffer to store 1024 samples from DAC)
 * @return void
 */

void adc_analysis(uint16_t *adc_buffer)
{
	int total = ZERO;
	int avg = ZERO;
	int frequency = ZERO;
	int min = adc_buffer[ZERO];
	int max = adc_buffer[ZERO];
	int period;

	for(int i = ZERO; i < BUFFER_SIZE; i++)
	{
		if(min > adc_buffer[i])
			min = adc_buffer[i];
		if(max < adc_buffer[i])
			max = adc_buffer[i];
		total += adc_buffer[i];
	}

	avg = total / BUFFER_SIZE;
	//obtain period from autocorrelate function
	period = autocorrelate_detect_period(adc_buffer, BUFFER_SIZE, kAC_16bps_unsigned);
	frequency = INPUT_SAMPLE_RATE / period;

	//print analysis of input audio signal on terminal
	printf("min=%d max=%d avg=%d period=%d samples frequency=%d Hz\r\n\n", min, max, avg, period, frequency);
}
