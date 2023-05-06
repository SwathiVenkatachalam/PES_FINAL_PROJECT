/*
 * @file        dma.h
 * @brief       Function declaration of audio output module
 *
 * Contains DMA initialization, Copy DMA to DAC BUffer, Start DMA Transfer and IRQ Handler function declarations
 *
 * @author      Swathi Venkatachalam
 * @tools       MCUXpresso IDE
 * @references   https://github.com/alexander-g-dean/ESF/blob/master/NXP/Code/Chapter_9/DMA_Examples/Source/main.c
 *
 */
#ifndef DMA_H_
#define DMA_H_

#include "tone_to_sample.h"

/*
 * @name   init_DMA0
 * @brief  Function initiates DMA0
 *
 * DMA0 Function Initialization
 *
 * @param  void
 * @return void
 */

void init_DMA0();

/*
 * @name   copy_dma_dacbuffer
 * @brief  Function copies from DMA Source to DAC Buffer
 *
 * Copying from DMA Source to DAC Buffer
 *
 * @param  buffer *waveform_buffer
 * @return void
 */

void copy_dma_dacbuffer(buffer *out_buff);

/*
 * @name   start_dma_transfer
 * @brief  Function initiates DAC0
 *
 * Function for starting DMA0 to define source, destination address and byte counts
 * @param  void
 * @return void
 *
 */
void start_dma_transfer();

/*
 * @name   DMA0_IRQHandler
 * @brief  DMA0 interrupt handler and checks is 1 second has elapsed for waveform transition
 *
 * DMA0 interrupt handler called every time entire buffer is copied from source
 *
 * @param  void
 * @return void
 */

void DMA0_IRQHandler();

#endif /* DMA_H_ */
