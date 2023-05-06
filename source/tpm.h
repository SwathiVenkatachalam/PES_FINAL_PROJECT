/*
 * @file        tpm.h
 * @brief       Function prototypes of timer module
 *
 * Contains timer module functions
 *
 * @author      Swathi Venkatachalam
 * @tools       MCUXpresso IDE
 * @references   https://github.com/alexander-g-dean/ESF/blob/master/NXP/Code/Chapter_7/Analog%20Waveform%20Generation/src/timers.c
 *               Assignment 7
 */

#ifndef TPM_H_
#define TPM_H_

#define CLOCK                   (48000000) //Clock frequency
#define INPUT_SAMPLE_RATE       (96000)//ADC Input Sampling Rate: 96KHz
#define OUTPUT_SAMPLE_RATE      (48000) //DAC Output Sampling Rate: 48KHz; TPM Overflow

/*
 * @name   init_TPM0
 * @brief  Function initiates TPM0
 *
 * TPM0 Function Initialization
 *
 * @param  void
 * @return void
 */

void init_TPM0();

/*
 * @name   init_TPM1
 * @brief  Function initiates TPM1
 *
 * TPM1 Function Initialization
 *
 * @param  void
 * @return void
 */

void init_TPM1();

#endif /* TPM_H_ */
