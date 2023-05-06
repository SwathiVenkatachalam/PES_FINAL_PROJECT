/*
 * @file        musical_tones.h
 * @brief       Initialization of all musical waveforms functions declaration
 *
 * Initialization musical waveform function declaration and contains general macros and musical tunes
 *
 * @author      Swathi Venkatachalam
 * @tools       MCUXpresso IDE
 */
#ifndef MUSICAL_TONES_H_
#define MUSICAL_TONES_H_

#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MKL25Z4.h"
#include "fsl_debug_console.h"
#include "systick.h"
#include "dac.h"
#include "adc.h"
#include "tone_to_sample.h"
#include "tpm.h"
#include "dma.h"
#include "test_sine.h"

#define ZERO              (0)
#define ONE               (1)
#define BUFFER_ARRAY_SIZE (3) //Number of tones

/*
 * @name   init_all
 * @brief  Function initializes audio input and output modules
 *
 * Initializes DAC0, DMA0, TPM0, ADC0, TPM1, Systick
 *
 * @param  void
 * @return void
 */
void init_all();

/*
 * @name   play_tune1
 * @brief  Function playes tune 1 notes: A4, D5, D6
 *
 * Plays A4, D5, D6 in loop
 *
 * @param  void
 * @return void
 */
void play_tune1();

/*
 * @name   play_tune2
 * @brief  Function playes tune 2 notes: D4, E5, F5
 *
 * Plays D4, E5, F5 in loop
 *
 * @param  void
 * @return void
 */
void play_tune2();

/*
 * @name   play_tune3
 * @brief  Function playes tune 3 notes: E6, F6, G6
 *
 * Plays A4, D5, D6 in loop
 *
 * @param  void
 * @return void
 */
void play_tune3();

/*
 * @name   play_tune4
 * @brief  Function playes tune 4 notes: D4, D5, D6
 *
 * Plays D4, D5, D6 in loop
 *
 * @param  void
 * @return void
 */
void play_tune4();

/*
 * @name   play_tunes
 * @brief  Function playes tunes based on accelerometer angle
 *
 * Function playes tunes based on accelerometer angle
 *
 * @param  int roll
 * @return void
 */
void play_tunes(int roll);


#endif /* MUSICAL_TONES_H_ */
