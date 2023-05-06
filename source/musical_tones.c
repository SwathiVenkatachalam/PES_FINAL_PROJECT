/*
 * @file        musical_tones.c
 * @brief       Initialization of all musical waveforms functions
 *
 * Initialization musical waveform function and contains general macros and musical tunes
 *
 * @author      Swathi Venkatachalam
 * @tools       MCUXpresso IDE
 * @reference   Assignment 7
 *
 */
#include <stdio.h>
#include <math.h>
#include "musical_tones.h"
#include "led.h"

#define DURATION         (100) //to run tune
#define RESET            (-1)
#define ONE_SEC_ELAPSE   (16)

//Array of structures to store contents of each tone
buffer waveforms[BUFFER_ARRAY_SIZE];

/*
 * @name   init_all
 * @brief  Function initializes audio input and output modules
 *
 * Initializes DAC0, DMA0, TPM0, ADC0, TPM1, Systick
 *
 * @param  void
 * @return void
 */
void init_all()
{
    //Audio output module
    init_DAC0();
    init_DMA0();
    init_TPM0();

    //Audio input module
    init_ADC0();
    init_TPM1();

    init_systicktimer();
}

/*
 * @name   play_tune1
 * @brief  Function playes tune 1 notes: A4, D5, D6
 *
 * Plays A4, D5, D6 in loop
 *
 * @param  void
 * @return void
 */
void play_tune1()
{
	int waveform_no = ZERO; //To keep track of current tone

	//Pre-calculate the 3 buffers
	waveforms[WAVEFORM1].frequency = WAVEFORM1_FREQ;
	waveforms[WAVEFORM2].frequency = WAVEFORM2_FREQ;
	waveforms[WAVEFORM3].frequency = WAVEFORM3_FREQ;

	for(int i = WAVEFORM1; i < BUFFER_ARRAY_SIZE; i++)
	{
		tone_to_samples(&waveforms[i]);
	}

	copy_dma_dacbuffer(&waveforms[WAVEFORM1]); //Copy contents of tone 0
	TPM0->SC |= TPM_SC_CMOD(ONE); //Start TPM0
	start_dma_transfer(); //Start DMA0
	for(int k = ONE; k < DURATION; k++)
	{
		if(get_timer() >= ONE) //If 1 second has elapsed
		{
			waveform_no++; //Change to next tone
			copy_dma_dacbuffer(&waveforms[waveform_no]); //Copy next tone contents
			reset_timer(); //Reset timer
			start_dma_transfer(); //Start DMA again
		}
		if( waveform_no == WAVEFORM3) //If last waveform is reached, reset the waveform
		{
			 waveform_no = RESET;
		}
	}
	reset_timer();
}

/*
 * @name   play_tune2
 * @brief  Function playes tune 2 notes: D4, E5, F5
 *
 * Plays D4, E5, F5 in loop
 *
 * @param  void
 * @return void
 */
void play_tune2()
{
	int waveform_no = ZERO; //To keep track of current tone

	//Pre-calculate the 3 buffers
	waveforms[WAVEFORM1].frequency = WAVEFORM4_FREQ;
	waveforms[WAVEFORM2].frequency = WAVEFORM5_FREQ;
	waveforms[WAVEFORM3].frequency = WAVEFORM6_FREQ;

	for(int i = WAVEFORM1; i < BUFFER_ARRAY_SIZE; i++)
	{
		tone_to_samples(&waveforms[i]);
	}

	copy_dma_dacbuffer(&waveforms[WAVEFORM1]); //Copy contents of tone 0
	TPM0->SC |= TPM_SC_CMOD(ONE); //Start TPM0
	start_dma_transfer(); //Start DMA0
	for(int k = ONE; k < DURATION; k++)
	{
		if(get_timer() >= ONE) //If 1 second has elapsed
		{
			waveform_no++; //Change to next tone
			copy_dma_dacbuffer(&waveforms[waveform_no]); //Copy next tone contents
			reset_timer(); //Reset timer
			start_dma_transfer(); //Start DMA again
		}
		if( waveform_no == WAVEFORM3) //If last waveform is reached, reset the waveform
		{
			 waveform_no = RESET;
		}
	}
	reset_timer();
}

/*
 * @name   play_tune3
 * @brief  Function playes tune 3 notes: E6, F6, G6
 *
 * Plays A4, D5, D6 in loop
 *
 * @param  void
 * @return void
 */
void play_tune3()
{
	int waveform_no = ZERO; //To keep track of current tone

	//Pre-calculate the 3 buffers
	waveforms[WAVEFORM1].frequency = WAVEFORM7_FREQ;
	waveforms[WAVEFORM2].frequency = WAVEFORM8_FREQ;
	waveforms[WAVEFORM3].frequency = WAVEFORM9_FREQ;

	for(int i = WAVEFORM1; i < BUFFER_ARRAY_SIZE; i++)
	{
		tone_to_samples(&waveforms[i]);
	}

	copy_dma_dacbuffer(&waveforms[WAVEFORM1]); //Copy contents of tone 0
	TPM0->SC |= TPM_SC_CMOD(ONE); //Start TPM0
	start_dma_transfer(); //Start DMA0
	for(int k = ONE; k < DURATION; k++)
	{
		if(get_timer() >= ONE) //If 1 second has elapsed
		{
			waveform_no++; //Change to next tone
			copy_dma_dacbuffer(&waveforms[waveform_no]); //Copy next tone contents
			reset_timer(); //Reset timer
			start_dma_transfer(); //Start DMA again
		}
		if( waveform_no == WAVEFORM3) //If last waveform is reached, reset the waveform
		{
			 waveform_no = RESET;
		}
	}
	reset_timer();

}

/*
 * @name   play_tune4
 * @brief  Function playes tune 4 notes: D4, D5, D6
 *
 * Plays D4, D5, D6 in loop
 *
 * @param  void
 * @return void
 */
void play_tune4()
{
	int waveform_no = ZERO; //To keep track of current tone

	//Pre-calculate the 3 buffers
	waveforms[WAVEFORM1].frequency = WAVEFORM10_FREQ;
	waveforms[WAVEFORM2].frequency = WAVEFORM11_FREQ;
	waveforms[WAVEFORM3].frequency = WAVEFORM12_FREQ;

	for(int i = WAVEFORM1; i < BUFFER_ARRAY_SIZE; i++)
	{
		tone_to_samples(&waveforms[i]);
	}

	copy_dma_dacbuffer(&waveforms[WAVEFORM1]); //Copy contents of tone 0
	TPM0->SC |= TPM_SC_CMOD(ONE); //Start TPM0
	start_dma_transfer(); //Start DMA0
	for(int k = ONE; k < DURATION; k++)
	{
		if(get_timer() >= ONE) //If 1 second has elapsed
		{
			waveform_no++; //Change to next tone
			copy_dma_dacbuffer(&waveforms[waveform_no]); //Copy next tone contents
			reset_timer(); //Reset timer
			start_dma_transfer(); //Start DMA again
		}
		if( waveform_no == WAVEFORM3) //If last waveform is reached, reset the waveform
		{
			 waveform_no = RESET;
		}
	}
}

/*
 * @name   play_tunes
 * @brief  Function playes tunes based on accelerometer angle
 *
 * Function playes tunes based on accelerometer angle
 *
 * @param  int roll
 * @return void
 */
void play_tunes(int roll)
{
	if (roll < 0)
	{
		roll = -roll;
	}
	printf("\r\nThe roll angle in degrees is: %d\n\r", roll);
	if (fabs(roll) >= 0 && fabs(roll) <= 5)
	{
		Control_RGB_LEDs(0, 1, 0);
		//stops music player
	}
	else if (fabs(roll) > 5 && fabs(roll) <= 45)
	{
		Control_RGB_LEDs(1, 1, 1);
		printf("\r\nPlaying tune1\r");
		play_tune1();
	}
	else if (fabs(roll) > 45 && fabs(roll) <= 90)
	{
		Control_RGB_LEDs(1, 1, 0);
		printf("\r\nPlaying tune2\n\r");
		play_tune2();
	}
	else if (fabs(roll) > 90 && fabs(roll) <= 135)
	{
		Control_RGB_LEDs(1, 0, 1);
		printf("\r\nPlaying tune3\n\r");
		play_tune3();
	}
	else if (fabs(roll) > 135 && fabs(roll) <= 800)
	{
		Control_RGB_LEDs(0, 1, 1);
		printf("\r\nPlaying tune4\n\r");
		play_tune4();
	 }
}
