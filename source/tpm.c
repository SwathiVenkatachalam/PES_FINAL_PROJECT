/*
 * @file        tpm.c
 * @brief       Function Implementation of timer module
 *
 * Contains timer module functions
 *
 * @author      Swathi Venkatachalam
 * @tools       MCUXpresso IDE
 * @references   https://github.com/alexander-g-dean/ESF/blob/master/NXP/Code/Chapter_7/Analog%20Waveform%20Generation/src/timers.c
 *               Assignment 7
 */

#include <musical_tones.h>
#include "MKL25Z4.h"
#include "tpm.h"


#define PERIOD              (CLOCK/OUTPUT_SAMPLE_RATE) - ONE
#define PRESCALAR           (ZERO)
#define INPUT_PERIOD        (CLOCK/INPUT_SAMPLE_RATE) - ONE

/*
 * @name   init_TPM0
 * @brief  Function initiates TPM0
 *
 * TPM0 Function Initialization
 *
 * @param  void
 * @return void
 */

void init_TPM0()
{
	// Turn on clock to TPM
	SIM->SCGC6 |= SIM_SCGC6_TPM0_MASK;

	// Set clock source for tpm
	SIM->SOPT2 |= (SIM_SOPT2_TPMSRC(ONE) | SIM_SOPT2_PLLFLLSEL_MASK);

	//Disable TPM for configuration
	TPM0->SC = ZERO;

	// Load the Counter and Mod
	TPM0->MOD = TPM_MOD_MOD(PERIOD); //Generate delay at DAC output sample rate 48KHz
	TPM0->CNT = ZERO;

	//Set TPM0 to enable DMA transfer, count up and divide clock by no prescaler
	TPM0->SC = TPM_SC_DMA_MASK | TPM_SC_PS(PRESCALAR);
}

/*
 * @name   init_TPM1
 * @brief  Function initiates TPM1
 *
 * TPM1 Function Initialization
 *
 * @param  void
 * @return void
 */
void init_TPM1()
{
	// Turn on clock to TPM
	SIM->SCGC6 |= SIM_SCGC6_TPM1_MASK;

	// Set clock source for tpm
	SIM->SOPT2 |= (SIM_SOPT2_TPMSRC(ONE) | SIM_SOPT2_PLLFLLSEL_MASK);

	//Disable TPM for configuration
	TPM1->SC = ZERO;

	// Load the counter and mod, given prescaler of 32
	TPM1->MOD = TPM_MOD_MOD(INPUT_PERIOD); //Generate delay at ADC input sample rate 96KHz
	TPM1->CNT = ZERO;
}
