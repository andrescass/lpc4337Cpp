/*
===============================================================================
 Name        : main.c
 Author      : $(author)
 Version     :
 Copyright   : $(copyright)
 Description : main definition
===============================================================================
*/

#if defined (__USE_LPCOPEN)
#if defined(NO_BOARD_LIB)
#include "LPC43xx.h"
#else
#include "board.h"
#endif
#endif

#include <cr_section_macros.h>
#include <NXP/crp.h>

__CRP const unsigned int CRP_WORD = CRP_NO_CRP;

// TODO: insert other include files here
#include "lpc43xx_gpio.h"
#include "lpc43xx_scu.h"
#include "lpc43xx_cgu.h"
#include "xplorer.h"

// TODO: insert other definitions and declarations here

#define DELAY_LEN_MAX 160
#define DELAY_LEN_MIN 10
#define DELAY_CHANGE 10

uint32_t flashval; // current length of led flash

volatile uint32_t msTicks; // counter for 1ms SysTicks

uint32_t maxflashval, minflashval, changeval;

// If set to none-zero, then speed of flash will stay constant
uint32_t constflash = 0;

// Controls whether flash period change is a decrease or increase
int32_t sign = +1;

// ****************
//  SysTick_Handler - just increment SysTick counter
extern "C" {
void SysTick_Handler(void) {
	msTicks++;
}
}

// ****************
// systick_delay - creates a delay of the appropriate number of Systicks (happens every 1 ms)
void systick_delay(uint32_t delayTicks) {
	uint32_t currentTicks;

	currentTicks = msTicks;	// read current tick counter
	// Now loop until required number of ticks passes.
	while ((msTicks - currentTicks) < delayTicks);
}

const uint32_t ledposition_port[] = { LED_D3_PORT, LED_D2_PORT };
const uint32_t ledposition_mask[] = { LED_D3_MASK, LED_D2_MASK };

int main(void) {

#if defined (__USE_LPCOPEN)
    // Read clock settings and update SystemCoreClock variable
//    SystemCoreClockUpdate();
#if !defined(NO_BOARD_LIB)
#if defined (__MULTICORE_MASTER) || defined (__MULTICORE_NONE)
    // Set up and initialize all required blocks and
    // functions related to the board hardware
    Board_Init();
#endif
    // Set the LED to the state of "On"
    Board_LED_Set(0, true);
#endif
#endif

    SystemInit();
    // TODO: insert code here

    scu_pinmux(2, 11, MD_PUP|MD_EZI,FUNC0);
	GPIO_SetDir(1, (1<<11), 1);
	GPIO_ClearValue(1, (1<<11));

	scu_pinmux(2, 12, MD_PUP|MD_EZI,FUNC0);
	GPIO_SetDir(1, (1<<12), 1);
	GPIO_ClearValue(1, (1<<12));

	// Set up initial flash period, max and min flash periods, and change value
	flashval = DELAY_LEN_MAX;
	maxflashval = DELAY_LEN_MAX;
	minflashval = DELAY_LEN_MIN;
	changeval = DELAY_CHANGE;

	// Setup SysTick Timer to interrupt at 1 msec intervals
	//CGU_EntityConnect(CGU_CLKSRC_PLL1, CGU_PERIPHERAL_M4CORE);
	int sysResult = SysTick_Config(CGU_GetPCLKFrequency(CGU_PERIPHERAL_M4CORE)/1000); //(1000000);

    while(1) {
    	/*GPIO_SetValue(1, (1<<11));
    	systick_delay(flashval);
    	GPIO_ClearValue(1, (1<<11));
    	systick_delay(flashval);*/
    	for (int loop = 0; loop < 2; loop++) {
			GPIO_SetValue(ledposition_port[loop], ledposition_mask[loop]);
			systick_delay(flashval);
			GPIO_ClearValue(ledposition_port[loop], ledposition_mask[loop]);
		}

		for (int loop = 1; loop >= 0; loop--) {
			GPIO_SetValue(ledposition_port[loop], ledposition_mask[loop]);
			systick_delay(flashval);
			GPIO_ClearValue(ledposition_port[loop], ledposition_mask[loop]);
		}

		// Check to see if changing flash period is required
		if (constflash == 0) {
			// Check to see if the flash period is at min or max point
			if (flashval <= minflashval) {	  // Reverse direction of change
				sign = +1;
				flashval = minflashval;
			} else if (flashval >= maxflashval) {
				sign = -1;
				flashval = maxflashval;
			}

			// Modify the flash period (either increase or decrease
			// depending on sign)
			flashval = flashval + (sign * changeval);
		}
    }
    return 0 ;
}
