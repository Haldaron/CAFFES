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

/*  Standard C Included Files */
#include <string.h>

/*  SDK Included Files */
#include "board.h"
#include "fsl_debug_console.h"
#include "fsl_i2c.h"

#if ((defined FSL_FEATURE_SOC_INTMUX_COUNT) && (FSL_FEATURE_SOC_INTMUX_COUNT))
#include "fsl_intmux.h"
#endif

#include "fsl_device_registers.h"
#include "pin_mux.h"
#include <stdbool.h>
#include "clock_config.h"
#include "stdbool.h"
#include "i2c.h"
#include "spi.h"
#include "lmp.h"
#include "rtc.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/


#define I2C_SLAVE_ADDR_7BIT (0x68U)
#define I2C_BAUDRATE (100000) /* 100K */
#define I2C_DATA_LENGTH (8)  /* MAX is 256 */
#define SUBADDRESS		(0)
#define KIN1_IS_USING_KINETIS_SDK	1

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/

uint8_t g_slave_buff[I2C_DATA_LENGTH];
uint8_t g_master_buff[I2C_DATA_LENGTH];

i2c_master_handle_t *g_m_handle;

/*******************************************************************************
 * Definitions
 ******************************************************************************/
/* Task priorities. */
/*******************************************************************************
 * Prototypes
 ******************************************************************************/
static void master_task(void);

/*******************************************************************************
 * Code
 ******************************************************************************/

int main(void)
{
    /* Init board hardware. */
    pinmux_init_all(true);
    BOARD_BootClockRUN();
    BOARD_InitDebugConsole();


    PRINTF("\r\n==FreeRTOS I2C example start.==\r\n");

    PRINTF("This example use two boards to connect with one as master and another as slave %s, %s.\r\n",DATE,TIME );

    master_task();

    for (;;)
        ;
}


/*!
 * @brief Data structure and callback function for slave I2C communication.
 */

typedef struct _callback_message_t
{
    status_t async_status;
    SemaphoreHandle_t sem;
} callback_message_t;



/*!
 * @brief Task responsible for slave I2C communication.
 */



static void master_task(void)
{
	rtc_dev_t 		rtc_dev;
	lmp_dev_t 		lmp_dev;
	rtc_date_t		date;
	uint32_t		adc;

	lmp_init(&lmp_dev, GPIOA,PIN5);
	rtc_init(&rtc_dev,ADDRESS);

	rtc_updateToCompilationTime(&rtc_dev);


	while(true){

		rtc_read(&rtc_dev,&date);

		lmp_getMeasure(&lmp_dev,&adc);

		PRINTF("Master received data: ");
		PRINTF("%2x:%2x:%2x  -  %2x/%2x/%2x  ", date.hou,date.min,date.seg,date.day,date.mon,date.yea);
		PRINTF("\r\n\r\n");
		for(int i=0;i<4800000;i++);
	}

	PRINTF("\r\nEnd of FreeRTOS I2C example.\r\n");
}

