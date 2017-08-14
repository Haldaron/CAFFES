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



/* Freescale includes. */
#include "fsl_device_registers.h"
#include "fsl_debug_console.h"
#include "fsl_spi.h"
#include "fsl_spi_freertos.h"
#include "board.h"
#include "fsl_gpio.h"
#include "ff.h"
#include "spi.h"
#include <stdlib.h>


#include "fsl_common.h"
#include "fsl_port.h"
#include "pin_mux.h"
#include "clock_config.h"

#define OS_FREERTOS

#ifdef OS_FREERTOS
	#include "spi.h"

	/* FreeRTOS kernel includes. */
	#include "FreeRTOS.h"
	#include "task.h"
	#include "queue.h"
	#include "timers.h"
	/*******************************************************************************
	 * Definitions
	 ******************************************************************************/
	/* Task priorities. */
	#define master_task_PRIORITY (configMAX_PRIORITIES - 1)
#else
	#include "spi_nf.h"
#endif
/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define	BASE_SPI1	GPIOC
#define	BASE_SPI2	GPIOA
#define	PIN_SPI1	PIN4
#define	PIN_SPI2	PIN5
#define SIZE		4




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
    PRINTF("   SOUT     --    SIN  \r\n");


    xTaskCreate(spi_task, "med_task", configMINIMAL_STACK_SIZE, NULL, master_task_PRIORITY, NULL);
    vTaskStartScheduler();

    for (;;)
        ;
}

/*!
 * @brief Task responsible for master SPI communication.
 */



static void spi_task(void *pvParameters){

	FATFS 		*fs=pvPortMalloc(sizeof(FATFS));
	FRESULT 	fr;
	spi_dev_t 	*spi_dev=pvPortMalloc(sizeof(spi_dev_t));

    PRINTF("begin.\r\n");

	char file_name1[12]="Test.csv";

	spi_initialize(spi_dev,GPIOC,PIN4);


//	sdspi_init(&sdspi_dev);
//
//
//	data_out[0]=0x40;
//	data_out[1]=0x00;
//	data_out[2]=0x00;
//	data_out[3]=0x00;
//	data_out[4]=0x00;
//	data_out[5]=0x95;
//	for(;;){
//		PRINTF("Reset Command\n\r");
//		sdspi_init(&sdspi_dev);
//		data_out[0]=0x40;
//		sdspi_transfer(&sdspi_dev,data_out,data_in,6);
//		data_out[0]=0xFF;
//		for(int i=0;i<9;i++){
//			sdspi_transfer(&sdspi_dev,data_out,data_in,1);
//			PRINTF("Response: %X\n\r",data_in[0]);
//			for(int j=0;j<480000;j++);
//		}
//	}

	fr= f_mount(fs,file_name1,1);
	if(fr)
	{

					PRINTF("\nError mounting file system\r\n");

					for(;;){}

	}
	//
	//	fr = f_open(&fil, file_name1, FA_WRITE | FA_OPEN_ALWAYS);//create csv file
	//
	//	if(fr)
	//
	//	{
	//
	//					PRINTF("\nError opening text file\r\n");
	//
	//					for(;;){}
	//
	//	}
	//
	//	fr = f_write(&fil, "Test1 ,Test2 ,Test3 ,Test4 \r\n", 29, &bw); //write data to the excel file
	//
	//	if(fr)
	//
	//	{
	//
	//					PRINTF("\nError write text file\r\n");
	//
	//					for(;;){}
	//
	//	}
	//
	//	 fr = f_close(&fil);
	//
	//	if(fr)
	//
	//	{
	//
	//					PRINTF("\nError close text file\r\n");
	//
	//					for(;;){}
	//
	//	}
	//
	//	fr= f_mount(&fs,file_name2,0);
	//
	//	if(fr)
	//
	//	{
	//
	//					PRINTF("\nError mounting file system\r\n");
	//
	//					for(;;){}
	//
	//	}
	//
	//	fr = f_open(&fil, file_name2, FA_WRITE | FA_OPEN_ALWAYS);//create txt file
	//
	//	if(fr)
	//
	//	{
	//
	//					PRINTF("\nError opening text file\r\n");
	//
	//					for(;;){}
	//
	//	}
	//
	//	fr = f_write(&fil, "Test1 ,Test2 ,Test3 ,Test4 \r\n", 29, &bw); //write data to the txt file
	//
	//	if(fr)
	//
	//	{
	//
	//					PRINTF("\nError write text file\r\n");
	//
	//					for(;;){}
	//
	//	}
	//
	//	fr = f_close(&fil);
	//
	//	if(fr)
	//
	//	{
	//
	//					PRINTF("\nError close text file\r\n");
	//
	//					for(;;){}
	//
	//	}
	//
	//while(1)
	//
	//	{
	//
	//			 for(i=0;i<10;i++) for(j=0;j<65535;j++);
	//
	//			PRINTF("\ntest_sd\n");//
	//
	//	}

}

