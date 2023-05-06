/*
 * @file        dac.c
 * @brief       Function Implementation of audio output module
 *
 * Contains DAC initialization function
 *
 * @author      Swathi Venkatachalam
 * @tools       MCUXpresso IDE
 * @references   https://github.com/alexander-g-dean/ESF/blob/master/NXP/Code/Chapter_9/DMA_Examples/Source/main.c
 *               Assignment 7
 */

#include <musical_tones.h>
#include "dac.h"
#include "MKL25Z4.h"

// On Port E PIN 30; PTE30
#define DAC_POS (30) // J10-11 Pin out on FRDM KL25Z
#define SEVEN   (7) // PORT_PCR_MUX

/*
 * @name   init_DAC0
 * @brief  Function initiates DAC0
 *
 * DAC0 Function Initialization
 *
 * @param  void
 * @return void
 */

void init_DAC0()
{
	// System Integration Module: System Clock Gating Control Register 6 - Init DAC output
	// Field 31: DAC0 Clock Gate Control - clock Enable
	SIM->SCGC6 |=  SIM_SCGC6_DAC0_MASK;

    // System Integration Module: System Clock Gating Control Register 5
	// Field 13: Port E Clock Gate Control - clock enable
	SIM->SCGC5 |= SIM_SCGC5_PORTE_MASK;

	// Pull devices are enabled by writing to PORTx_PCRn[PE] field
	PORTE->PCR[DAC_POS] &= ~(PORT_PCR_MUX(SEVEN));	// Select analog

	// Disable buffer mode
	DAC0->C1 = ZERO; //DAC Control Register 1
	DAC0->C2 = ZERO; //DAC Control Register 2

	// Enable DAC, select VDDA as reference voltage
	DAC0->C0 = DAC_C0_DACEN_MASK | DAC_C0_DACRFS_MASK;
}
