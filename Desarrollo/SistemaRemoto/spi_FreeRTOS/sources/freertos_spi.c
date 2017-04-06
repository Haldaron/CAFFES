/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of Freescale Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */


/* FreeRTOS kernel includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "timers.h"

/* Freescale includes. */
#include "fsl_device_registers.h"
#include "fsl_debug_console.h"
#include "fsl_spi.h"
#include "fsl_spi_freertos.h"
#include "board.h"
#include "fsl_gpio.h"


#include "fsl_common.h"
#include "fsl_port.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "spi.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define EXAMPLE_SPI_MASTER_BASE (SPI0_BASE)
#define PIN18_IDX                         18u   /*!< Pin number for pin 7 in a port */
#ifndef EXAMPLE_SPI_MASTER_BASE
#error Undefined SPI base address!
#endif // ifndef EXAMPLE_SPI_MASTER_BASE

#define EXAMPLE_SPI_MASTER_BASEADDR ((SPI_Type *)EXAMPLE_SPI_MASTER_BASE)

#ifndef SPI_MASTER_CLK_SRC

#if (EXAMPLE_SPI_MASTER_BASE == SPI0_BASE)
#define SPI_MASTER_CLK_SRC (SPI0_CLK_SRC)
#elif(EXAMPLE_SPI_MASTER_BASE == SPI1_BASE)
#define SPI_MASTER_CLK_SRC (SPI1_CLK_SRC)
#elif(EXAMPLE_SPI_MASTER_BASE == SPI2_BASE)
#define SPI_MASTER_CLK_SRC (SPI2_CLK_SRC)
#elif(EXAMPLE_SPI_MASTER_BASE == SPI3_BASE)
#define SPI_MASTER_CLK_SRC (SPI3_CLK_SRC)
#elif(EXAMPLE_SPI_MASTER_BASE == SPI4_BASE)
#define SPI_MASTER_CLK_SRC (SPI4_CLK_SRC)
#else
#error Undefined SPI_MASTER_CLK_SRC!
#endif

#endif // ifndef SPI_MASTER_CLK_SRC

#if (__CORTEX_M >= 0x03)
#define SPI_NVIC_PRIO 6
#else
#define SPI_NVIC_PRIO 2
#endif

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/
#define BUFFER_SIZE (32)
#define BOARD_LED_GPIO BOARD_LED_RED_GPIO
#define BOARD_LED_GPIO_PIN BOARD_LED_RED_GPIO_PIN
static uint8_t srcBuff[BUFFER_SIZE];
static uint8_t destBuff[BUFFER_SIZE];

spi_rtos_handle_t master_rtos_handle;
/*******************************************************************************
 * Definitions
 ******************************************************************************/
/* Task priorities. */
#define master_task_PRIORITY (configMAX_PRIORITIES - 1)

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

static void master_task(void *pvParameters);
static void gpio_tast(void *pvParameters);
static void spi_task(void *pvParameters);
/*******************************************************************************
 * Code
 ******************************************************************************/
/*!
 * @brief Application entry point.
 */
int main(void)
{
    /* Init board hardware. */
    pinmux_init_all(true);
    gpio_pin_config_t led_config = {
        kGPIO_DigitalOutput, 0,
    };

    GPIO_PinInit(GPIOB, PIN18_IDX, &led_config);


    BOARD_BootClockRUN();
    BOARD_InitDebugConsole();

    PRINTF("SPI FreeRTOS example start.\r\n");
    PRINTF("This example use one SPI instance in master mode\r\n");
    PRINTF("to transfer data through loopback.\r\n");
    PRINTF("Please be sure to externally connect together SOUT and SIN signals.\r\n");
    PRINTF("   SOUT     --    SIN  \r\n");



    GPIO_TogglePinsOutput(BOARD_LED_RED_GPIO, 1u << BOARD_LED_RED_GPIO_PIN);


    xTaskCreate(spi_task, "spi_task", configMINIMAL_STACK_SIZE, NULL, master_task_PRIORITY, NULL);
    xTaskCreate(gpio_tast, "gpio", configMINIMAL_STACK_SIZE, NULL, configMAX_PRIORITIES, NULL);


    vTaskStartScheduler();
    for (;;)
        ;
}

/*!
 * @brief Task responsible for master SPI communication.
 */

static void gpio_tast(void *pvParameters)
{
	 while (1)
	 {
		 GPIO_TogglePinsOutput(GPIOB, 1u << PIN18_IDX);
	     vTaskDelay(500);
	 }
}

static void spi_task(void *pvParameters){
	spi_dev dev;
	spi_rtos_handle_t handle;
	uint8_t data_out=0xAA;
	uint8_t data_in=0;
	uint8_t size=1;

	dev.spi_rtos_handle= &handle;
	dev.base=GPIOB;
	dev.pin=PIN2;

	spi_init(&dev);

	for(;;){
		data_out+=0;
		spi_transfer(&dev,&data_out,&data_in,size);
		PRINTF("DATO ENVIADO %d. DATO RECIBIDO %d \n\r", data_out, data_in);
		vTaskDelay(10);
	}
}

static void master_task(void *pvParameters)
{
    spi_master_config_t masterConfig;
    spi_transfer_t masterXfer = {0};
    uint32_t sourceClock;
    status_t status;

#if (EXAMPLE_SPI_MASTER_BASE == SPI0_BASE)
    NVIC_SetPriority(SPI0_IRQn, SPI_NVIC_PRIO);
#elif(EXAMPLE_SPI_MASTER_BASE == SPI1_BASE)
    NVIC_SetPriority(SPI1_IRQn, SPI_NVIC_PRIO);
#elif(EXAMPLE_SPI_MASTER_BASE == SPI2_BASE)
    NVIC_SetPriority(SPI2_IRQn, SPI_NVIC_PRIO);
#elif(EXAMPLE_SPI_MASTER_BASE == SPI3_BASE)
    NVIC_SetPriority(SPI3_IRQn, SPI_NVIC_PRIO);
#elif(EXAMPLE_SPI_MASTER_BASE == SPI4_BASE)
    NVIC_SetPriority(SPI4_IRQn, SPI_NVIC_PRIO);
#endif

    /*
     * masterConfig.enableStopInWaitMode = false;
     * masterConfig.polarity = kSPI_ClockPolarityActiveHigh;
     * masterConfig.phase = kSPI_ClockPhaseFirstEdge;
     * masterConfig.direction = kSPI_MsbFirst;
     * masterConfig.dataMode = kSPI_8BitMode;
     * masterConfig.txWatermark = kSPI_TxFifoOneHalfEmpty;
     * masterConfig.rxWatermark = kSPI_RxFifoOneHalfFull;
     * masterConfig.pinMode = kSPI_PinModeNormal;
     * masterConfig.outputMode = kSPI_SlaveSelectAutomaticOutput;
     * masterConfig.baudRate_Bps = 500000U;
     */

    SPI_MasterGetDefaultConfig(&masterConfig);
    masterConfig.baudRate_Bps = 500000;
    masterConfig.outputMode = kSPI_SlaveSelectAsGpio;
    masterConfig.polarity=kSPI_ClockPolarityActiveLow;
    masterConfig.phase = kSPI_ClockPhaseSecondEdge;
    masterConfig.dataMode = kSPI_16BitMode;

    sourceClock = CLOCK_GetFreq(kCLOCK_BusClk);
    status = SPI_RTOS_Init(&master_rtos_handle, EXAMPLE_SPI_MASTER_BASEADDR, &masterConfig, sourceClock);

    if (status != kStatus_Success)
    {
        PRINTF("DSPI master: error during initialization. \r\n");
        vTaskSuspend(NULL);
    }

    /* Init Buffer */
    uint8_t i = 0;
    for (i = 0; i < BUFFER_SIZE; i++)
    {
        srcBuff[i] = i;
    }

    	srcBuff[0]=0x10;
    	srcBuff[1]=0x00;
    	srcBuff[2]=0x89;
    	srcBuff[3]=0x00;


    /* Send and receive data through loopback  */
    masterXfer.txData = srcBuff;
    masterXfer.rxData = destBuff;
    masterXfer.dataSize = BUFFER_SIZE;

    status = SPI_RTOS_Transfer(&master_rtos_handle, &masterXfer);

    if (status == kStatus_Success)
    {
        PRINTF("SPI transfer completed successfully. \r\n");
    }
    else
    {
        PRINTF("SPI transfer completed with error. \r\n");
    }

    /* Verify received data */
    uint32_t err = 0;
    for (i = 0; i < BUFFER_SIZE; i++)
    {
        if (srcBuff[i] != destBuff[i])
        {
            err++;
            PRINTF("Mismatch at offset %d. %X != %X \n\r", i, destBuff[i], srcBuff[i]);
        }
    }
    if (err == 0)
    {
        PRINTF("Data verified ok.\n\r");
    }
    for (;;)
        ;
}
