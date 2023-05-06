/*
 * @file        adc.h
 * @brief       Function Declaration of audio input module
 *
 * Contains ADC initialization, storing 1024 samples from dac onto buffer and waveform analysis function declarations
 *
 * @author      Swathi Venkatachalam
 * @tools       MCUXpresso IDE
 *              Assignment 7
 */
#ifndef ADC_H_
#define ADC_H_

#include <stdint.h>

/*
 * @name   init_ADC0
 * @brief  Function initiates ADC0
 *
 * ADC0 Function Initialization
 *
 * @param  void
 * @return void
 */
void init_ADC0();

/*
 * @name   adc_buffer
 * @brief  Function initiates ADC0
 *
 * Storing the 1024 samples from DAC to ADC Buffer input
 *
 * @param  uint16_t *adc_buffer (Pointer to ADC buffer to store 1024 samples from DAC)
 * @return void
 */
void adc_buffer(uint16_t *adc_buffer);

/*
 * @name   adc_analysis
 * @brief  Function for ADC analysis
 *
 * Checks if the DAC generated waveforms are correct, since it's given as a input to ADC
 *
 * @param  uint16_t *adc_buffer (Pointer to ADC buffer to store 1024 samples from DAC)
 * @return void
 */
void adc_analysis(uint16_t *adc_buffer);

/*
 * @name   calibrate_ADC
 * @brief  Function calibrates ADC0
 *
 * 1. Initialize or clear a 16-bit variable in RAM.
 * 2. Add the plus-side calibration results CLP0, CLP1, CLP2, CLP3, CLP4, and CLPS to the variable.
 * 3. Divide the variable by two.
 * 4. Set the MSB of the variable.
 * 5. The previous two steps can be achieved by setting the carry bit, rotating to the right through the carry bit on the high byte and again on the low byte.
 * 6. Store the value in the plus-side gain calibration register PG.
 * 7. Repeat the procedure for the minus-side gain calibration value.
 *
 * @param  void
 * @return void
 */
void calibrate_ADC();

#endif /* ADC_H_ */
