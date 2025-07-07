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


#define SWITCH_CHANNEL1 1
#define LED_CHANNEL2 2


int main()
{
    int Status;
    XGpio Gpio;

    init_platform();

    print("Used design_1_wrapper.xsa file from abulnk@gmail.com\r\n");

    Status = XGpio_Initialize(&Gpio, XPAR_XGPIO_0_BASEADDR);
    if (Status != XST_SUCCESS) {
        xil_printf("GPIO Initialization Failed\r\n");
        return XST_FAILURE;
    }

    // GPIO Switch control
    XGpio_SetDataDirection(&Gpio, SWITCH_CHANNEL1, 1); // input
    u32 Switch1 = XGpio_DiscreteRead(&Gpio, SWITCH_CHANNEL1);
    xil_printf("Switch1 0x%x\r\n", Switch1);

    // GPIO LED show
    XGpio_SetDataDirection(&Gpio, LED_CHANNEL2, 0); // output
    //XGpio_DiscreteWrite(&Gpio, LED_CHANNEL2, 0xFFFFFFFF); ALL LEDs Lit
    XGpio_DiscreteWrite(&Gpio, LED_CHANNEL2, 0xF); // LED0, LED1, LED2, LED3 lit
    u32 Led2 = XGpio_DiscreteRead(&Gpio, LED_CHANNEL2);
    xil_printf("Led2 0x%x\r\n", Led2);


    while(1)
    {
        u32 switches = XGpio_DiscreteRead(&Gpio, SWITCH_CHANNEL1);
        XGpio_DiscreteWrite(&Gpio, LED_CHANNEL2, switches);
        xil_printf("Checked! %x\r\n", switches);
        sleep(1);
    }
    

    cleanup_platform();
    return 0;
}
