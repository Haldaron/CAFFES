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
#include "lmp.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define	BASE_SPI1	GPIOC
#define	BASE_SPI2	GPIOA
#define	PIN_SPI1	PIN4
#define	PIN_SPI2	PIN5
#define SIZE		2


/*******************************************************************************
 * Definitions
 ******************************************************************************/
/* Task priorities. */
#define master_task_PRIORITY (configMAX_PRIORITIES - 1)

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

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

    BOARD_BootClockRUN();
    BOARD_InitDebugConsole();

    PRINTF("EJEMPLO DE SPI PARA PROYECTO CAFFES.\r\n");
    PRINTF("Este ejemplo se utilizan dos dispositivos SPI de manera simultanea\r\n");
    PRINTF("cada uno con un GPIO diferente como CS.\r\n");
    PRINTF("   SOUT     --    SIN  \r\n");


    xTaskCreate(spi_task, "spi_task", configMINIMAL_STACK_SIZE, NULL, master_task_PRIORITY, NULL);

    vTaskStartScheduler();
    for (;;)
        ;
}

/*!
 * @brief Task responsible for master SPI communication.
 */



static void spi_task(void *pvParameters){
	spi_dev_t dev1;
	spi_dev_t dev2;
	spi_rtos_handle_t handle1;
	spi_rtos_handle_t handle2;
	uint8_t data_out[SIZE];
	uint8_t data_in[SIZE];

	dev1.spi_rtos_handle= &handle1;
	dev1.base=BASE_SPI1;
	dev1.pin=PIN_SPI1;

	dev2.spi_rtos_handle= &handle2;
	dev2.base=BASE_SPI2;
	dev2.pin=PIN_SPI2;

	if(spi_init(&dev1)!=0){
		PRINTF("Error de inicializacion dev1");
	}

	if(spi_init(&dev2)!=0){
		PRINTF("Error de inicializacion dev2");
	}

	for(int i=0;i<SIZE;i++){
		data_out[i]=i;
	}


	for(;;){
		if(spi_transfer(&dev1,data_out,data_in,SIZE)!=0){
			PRINTF("Error de transmision dev1");
		}
		PRINTF("DATO ENVIADO %X%X. DATO RECIBIDO %X%X \n\r", data_out[0],data_out[1], data_in[0],data_in[1]);
		vTaskDelay(2);

		if(spi_transfer(&dev2,data_out,data_in,SIZE)!=0){
			PRINTF("Error de transmision dev2");
		}
		PRINTF("DATO ENVIADO %X%X. DATO RECIBIDO %X%X \n\r", data_out[0],data_out[1], data_in[0],data_in[1]);
		vTaskDelay(2);
	}
}

