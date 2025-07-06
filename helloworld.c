/******************************************************************************
* Copyright (C) 2023 Advanced Micro Devices, Inc. All Rights Reserved.
* SPDX-License-Identifier: MIT
******************************************************************************/
/*
 * helloworld.c: simple test application
 *
 * This application configures UART 16550 to baud rate 9600.
 * PS7 UART (Zynq) is not initialized by this application, since
 * bootrom/bsp configures it to baud rate 115200
 *
 * ------------------------------------------------
 * | UART TYPE   BAUD RATE                        |
 * ------------------------------------------------
 *   uartns550   9600
 *   uartlite    Configurable only in HW design
 *   ps7_uart    115200 (configured by bootrom/bsp)
 */

#include <stdio.h>
#include <xstatus.h>
#include "platform.h"
#include "xil_printf.h"

#include "xgpio_i.h"

#define LED_CHANEL0 0
#define LED_CHANEL1 1
#define LED_CHANEL2 2
#define LED_CHANEL3 3
#define LED_CHANEL4 4
#define LED_CHANEL5 5
#define LED_CHANEL6 6
#define LED_CHANEL7 7
#define LED_CHANEL8 8

#define LED_CHANEL 1
#define SWITCH_CHANEL 2
#define LEDS_MASK 0xFF      // 8 LEDs
#define SWITCHES_MASK 0xFF  // 8 Switches



int main()
{
    int Status;
    XGpio Gpio;

    init_platform();

    //print("Hello World\n\r");
    //print("Successfully ran Hello World application\r\n");
    print("Used design_1_wrapper.xsa file from abulnk@gmail.com\r\n");

    //Status = XGpio_Initialize(XGpio *InstancePtr, UINTPTR BaseAddress);
    Status = XGpio_Initialize(&Gpio, XPAR_XGPIO_0_BASEADDR);
    if (Status != XST_SUCCESS) {
        xil_printf("GPIO Initialization Failed\r\n");
        return XST_FAILURE;
    }

 
    XGpio_SetDataDirection(&Gpio, LED_CHANEL, ~LEDS_MASK);          // output
    XGpio_SetDataDirection(&Gpio, SWITCH_CHANEL, ~SWITCHES_MASK);   // input

    // Individually 
    XGpio_SetDataDirection(&Gpio, LED_CHANEL1, 1); 
    XGpio_DiscreteWrite(&Gpio, LED_CHANEL1, 1);
    u32 Led1 = XGpio_DiscreteRead(&Gpio, LED_CHANEL1);
    xil_printf("Led1 %x\r\n", Led1);

    XGpio_SetDataDirection(&Gpio, LED_CHANEL2, 1); 
    XGpio_DiscreteWrite(&Gpio, LED_CHANEL2, 1);
    u32 Led2 = XGpio_DiscreteRead(&Gpio, LED_CHANEL2);
    xil_printf("Led2 %x\r\n", Led2);

    XGpio_SetDataDirection(&Gpio, LED_CHANEL3, 1); 
    XGpio_DiscreteWrite(&Gpio, LED_CHANEL3, 1);
    XGpio_SetDataDirection(&Gpio, LED_CHANEL4, 1); 
    XGpio_DiscreteWrite(&Gpio, LED_CHANEL4, 1);


    while(1)
    {
        u32 switches = XGpio_DiscreteRead(&Gpio, SWITCH_CHANEL);
        XGpio_DiscreteWrite(&Gpio, LED_CHANEL, switches);
        xil_printf("Checked! %x\r\n", switches);
        sleep(1);
    }
    

    cleanup_platform();
    return 0;
}
