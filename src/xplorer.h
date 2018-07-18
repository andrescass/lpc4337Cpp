//*****************************************************************************
//   +--+
//   | ++----+
//   +-++    |
//     |     |
//   +-+--+  |
//   | +--+--+
//   +----+    Copyright (c) 2013 Code Red Technologies Ltd.
//
// xplorer.h - Defines for accessing LEDs and switch on NGX Xplorer board
//
// Software License Agreement
//
// The software is owned by Code Red Technologies and/or its suppliers, and is
// protected under applicable copyright laws.  All rights are reserved.  Any
// use in violation of the foregoing restrictions may subject the user to criminal
// sanctions under applicable laws, as well as to civil liability for the breach
// of the terms and conditions of this license.
//
// THIS SOFTWARE IS PROVIDED "AS IS".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED
// OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
// MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
// USE OF THIS SOFTWARE FOR COMMERCIAL DEVELOPMENT AND/OR EDUCATION IS SUBJECT
// TO A CURRENT END USER LICENSE AGREEMENT (COMMERCIAL OR EDUCATIONAL) WITH
// CODE RED TECHNOLOGIES LTD.
//*****************************************************************************

#ifndef __XPLORER_H
#define __XPLORER_H

// P2.12 : GPIO1_12: Xplorer BOARD (LED D2)
#define LED_D2_SCU_PORT		2
#define LED_D2_SCU_PIN		12
#define LED_D2_BIT			12 //LEDUSB
#define LED_D2_PORT			1
#define LED_D2_MASK	(1<<LED_D2_BIT)

// P2.11 : GPIO1_11: Xplorer BOARD (LED D3)
#define LED_D3_SCU_PORT		2
#define LED_D3_SCU_PIN		11
#define LED_D3_BIT			11 //LEDUSB
#define LED_D3_PORT			1
#define LED_D3_MASK	(1<<LED_D3_BIT)

// P2.7 : GPIO 0.7 : Button SW2
#define SW2_SCU_PORT	2
#define SW2_SCU_PIN		7
#define SW2_GPIO_PORT	0
#define SW2_GPIO_MASK	(1<<7)

#endif // __XPLORER_H
