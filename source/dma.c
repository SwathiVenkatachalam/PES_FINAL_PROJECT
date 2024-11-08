/*
 * @file        dma.c
 * @brief       Function Implementation of audio output module
 *
 * Contains DMA initialization, Copy DMA to DAC BUffer, Start DMA Transfer and IRQ Handler functions
 *
 * @author      Swathi Venkatachalam
 * @tools       MCUXpresso IDE
 * @references   https://github.com/alexander-g-dean/ESF/blob/master/NXP/Code/Chapter_9/DMA_Examples/Source/main.c
 *               Assignment 7: https://github.com/ECEN5813/assignment-7-waveforms-SwathiVenkatachalam/blob/main/source/dma.c
 */

#include <musical_tones.h>
#include "dma.h"
#include "systick.h"
#include "MKL25Z4.h"

#include <stdint.h>
//audio output module utilizing DMA for efficient data transfer to DAC.
#define DMA_SOURCE_SIZE        (2)
#define DMA_DESTINATION_SIZE   (2)
#define PRIORITY               (2)
#define TPM0_OVERFLOW_TRIGG    (54) //Selecting TPM0 overflow as trigger for DMA
#define BCR_COUNT              (2)  //To increase number of bytes stored in DMA0 BCR register

int tone_transition_req = ZERO; //Set after 1 second is elapsed
uint16_t *Reload_DMA_Source; //Stores buffer's source address
uint32_t Reload_DMA_Byte_Count = ZERO; //Stores total number of samples in buffer

/*
 * @name   init_DMA0
 * @brief  Function initiates DMA0
 *
 * DMA0 Function Initialization
 *
 * @param  void
 * @return void
 */

void init_DMA0()
{
	// Gate clocks to DMA and DMAMUX
	SIM->SCGC7 |= SIM_SCGC7_DMA_MASK;
	SIM->SCGC6 |= SIM_SCGC6_DMAMUX_MASK;

	// Disable DMA channel to allow configuration
	DMAMUX0->CHCFG[ZERO] = ZERO;

	// Generate DMA interrupt when done
	// Configure DMA control register (DCR) to set up DMA transfer parameters
	DMA0->DMA[ZERO].DCR = DMA_DCR_EINT_MASK              | // Enable interrupt on transfer completion
			DMA_DCR_SINC_MASK                    | // Source address increments after each transfer
			DMA_DCR_SSIZE(DMA_SOURCE_SIZE)       | // Source data size (2 bytes)
			DMA_DCR_DSIZE(DMA_DESTINATION_SIZE)  | // Destination data size (2 bytes)
			DMA_DCR_ERQ_MASK                     | // Enable request for DMA
			DMA_DCR_CS_MASK; // Circular transfer mode enabled

	// Configure NVIC for DMA ISR
	NVIC_SetPriority(DMA0_IRQn, PRIORITY);
	NVIC_ClearPendingIRQ(DMA0_IRQn);
	NVIC_EnableIRQ(DMA0_IRQn); // Enable DMA0 interrupt in NVIC

	// Enable DMA MUX channel with TPM0 overflow as trigger
	DMAMUX0->CHCFG[ZERO] = DMAMUX_CHCFG_SOURCE(TPM0_OVERFLOW_TRIGG);
}


/*
 * @name   copy_dma_dacbuffer
 * @brief  Function copies from DMA Source to DAC Buffer
 *
 * Copying from DMA Source to DAC Buffer
 *
 * @param  buffer *waveform_buffer
 * @return void
 */

void copy_dma_dacbuffer(buffer *waveform_buffer)
{
	uint32_t sample_count = waveform_buffer->sample_count; // Get the number of samples from the buffer

	TPM0->SC &= ~TPM_SC_CMOD_MASK; //Stop TPM0 to prepare for DMA transfer
	// Store the start address of the DAC buffer in the DMA source pointer
	Reload_DMA_Source = &waveform_buffer->dac_buffer[ZERO]; //Store start address
	Reload_DMA_Byte_Count = sample_count; //Store total number of samples
	TPM0->SC |= TPM_SC_CMOD(ONE); //Start TPM0
}


/*
 * @name   start_dma_transfer
 * @brief  Function initiates DAC0
 *
 * Function for starting DMA0 to define source, destination address and byte counts
 * @param  void
 * @return void
 *
 */
void start_dma_transfer()
{
	// Set the DMA source address register with the buffer's source address
	DMA0->DMA[ZERO].SAR = DMA_SAR_SAR((uint32_t) Reload_DMA_Source);
	// Set the DMA destination address register with the DAC data register address
	DMA0->DMA[ZERO].DAR = DMA_DAR_DAR((uint32_t) (&(DAC0->DAT[ZERO])));

	// Set the byte count for the DMA transfer; multiplying by BCR_COUNT for total bytes to transfer
	DMA0->DMA[ZERO].DSR_BCR = DMA_DSR_BCR_BCR(Reload_DMA_Byte_Count * BCR_COUNT);

	// Clear the DMA done flag to reset the status before starting a new transfer
	DMA0->DMA[ZERO].DSR_BCR &= ~DMA_DSR_BCR_DONE_MASK;

	// Enable the DMA MUX channel to allow the transfer to start
	DMAMUX0->CHCFG[ZERO] |= DMAMUX_CHCFG_ENBL_MASK;
}


/*
 * @name   DMA0_IRQHandler
 * @brief  DMA0 interrupt handler and checks is 1 second has elapsed for waveform transition
 *
 * DMA0 interrupt handler called every time entire buffer is copied from source
 *
 * @param  void
 * @return void
 */
void DMA0_IRQHandler()
{
	// Clear the DMA done flag to acknowledge that the transfer is complete
	DMA0->DMA[ZERO].DSR_BCR |= DMA_DSR_BCR_DONE_MASK;
//
//	//Check if 1 second has elapsed
//	if(get_timer() >= ONE_SEC_ELAPSE)
//		tone_transition_req = ONE;
//	else
		start_dma_transfer(); // Start the next DMA transfer to continue sending data to the DAC
}
