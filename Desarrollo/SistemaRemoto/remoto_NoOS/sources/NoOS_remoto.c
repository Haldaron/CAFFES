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
#include "board.h"
#include "fsl_gpio.h"


#include "fsl_common.h"
#include "fsl_port.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "spi.h"
#include "Xbee.h"
#include "lmp.h"
#include "i2c.h"
#include "rtc.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define	BASE_SPI1	GPIOC
#define	BASE_SPI2	GPIOA
#define	PIN_SPI1	PIN4
#define	PIN_SPI2	PIN5
#define SIZE		4

#define TASK_DELAY		1000U

#define RTD_CURR 		RTD_CUR_1000U

#define CH0_IC 			BURNOUT_DIS|VREF2|VINP0|VINN5
#define CH1_IC 			BURNOUT_DIS|VREF1|VINP1|VINN7
#define CH2_IC 			BURNOUT_DIS|VREF1|VINP2|VINN7
#define CH3_IC 			BURNOUT_DIS|VREF1|VINP3|VINN7
#define CH4_IC 			BURNOUT_DIS|VREF1|VINP4|VINN7

#define CH0_CONF		ODR_214_65|FGA_OFF_4|BUFF_ON


#define FIRST_CH			CH1_FIRST
#define LAST_CH				CH3_LAST


/*******************************************************************************
 * Definitions
 ******************************************************************************/
/* Task priorities. */

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

static void medicion_task(void);
static void confLmp(lmp_dev_t *dev);
void xbeeReset(void);

void HardFault_Handler(void){
	while(1);
	NVIC_SystemReset();
}
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

    xbeeReset();
    medicion_task();

    for (;;)
        ;
}

/*!
 * @brief Task responsible for master SPI communication.
 */



static void medicion_task(void){
    Xbee_dev_t 	*xbee_dev=malloc(sizeof(Xbee_dev_t));
    rtc_dev_t	*rtc_dev=malloc(sizeof(rtc_dev_t));
    rtc_date_t	*rtc_date=malloc(sizeof(rtc_date_t));
    char 		*str=malloc(40*sizeof(char));

	lmp_dev_t 	dev;
	uint32_t	adc;

	Xbee_init(xbee_dev);
	for(int i=0;i<4800000;i++);


	if(rtc_init(rtc_dev, ADDRESS)!=0){
//		Xbee_sendString(xbee_dev,"error rtc_init\n\r");
	}

	if(rtc_read(rtc_dev,rtc_date)){
//		Xbee_sendString(xbee_dev,"error rtc_read\n\r");
	}
//	rtc_updateToCompilationTime(rtc_dev);
	for(int i=0;i<4800000;i++);


	if(lmp_init(&dev, GPIOC, PIN4)!=0){
//		Xbee_sendString(xbee_dev,"error lmp_init\n\r");
	}


    confLmp(&dev);


	for(;;){

		sprintf(str,"h>remoto1>transmitir>var>Temperatura");
	    Xbee_sendString(xbee_dev,str);
		lmp_confMeasure(&dev, SCAN_MODE0, FIRST_CH, LAST_CH);
		lmp_getMeasure(&dev,&adc);
		sprintf(str,"d>%d>%2x:%2x:%2x-%2x/%2x/%2x",(int)adc , rtc_date->hou,rtc_date->min,rtc_date->seg,rtc_date->day,rtc_date->mon,rtc_date->yea);
		Xbee_sendString(xbee_dev,str);
		sprintf(str,"h>remoto1>stop>var>Temperatura");
		Xbee_sendString(xbee_dev,str);

		for(int i=0;i<4800000;i++);

		sprintf(str,"h>remoto1>transmitir>var>Humedad1");
		Xbee_sendString(xbee_dev,str);;
		lmp_confMeasure(&dev, SCAN_MODE0, CH2_FIRST, CH5_LAST);
		lmp_getMeasure(&dev,&adc);
		sprintf(str,"d>%d>%2x:%2x:%2x-%2x/%2x/%2x",(int)adc , rtc_date->hou,rtc_date->min,rtc_date->seg,rtc_date->day,rtc_date->mon,rtc_date->yea);
		Xbee_sendString(xbee_dev,str);
		sprintf(str,"h>remoto1>stop>var>Humedad1");
		Xbee_sendString(xbee_dev,str);


    	for(int i=0;i<4800000;i++);

		sprintf(str,"h>remoto1>transmitir>var>Humedad2");
		Xbee_sendString(xbee_dev,str);
		lmp_confMeasure(&dev, SCAN_MODE0, CH3_FIRST, CH5_LAST);
		lmp_getMeasure(&dev,&adc);
		sprintf(str,"d>%d>%2x:%2x:%2x-%2x/%2x/%2x",(int)adc , rtc_date->hou,rtc_date->min,rtc_date->seg,rtc_date->day,rtc_date->mon,rtc_date->yea);
		Xbee_sendString(xbee_dev,str);;
		sprintf(str,"h>remoto1>stop>var>Humedad2");
		Xbee_sendString(xbee_dev,str);

    	for(int i=0;i<4800000;i++);

    	sprintf(str,"h>remoto1>transmitir>var>Humedad3");
    	Xbee_sendString(xbee_dev,str);
		lmp_confMeasure(&dev, SCAN_MODE0, CH0_FIRST, CH5_LAST);
		lmp_getMeasure(&dev,&adc);
		sprintf(str,"d>%d>%2x:%2x:%2x-%2x/%2x/%2x",(int)adc , rtc_date->hou,rtc_date->min,rtc_date->seg,rtc_date->day,rtc_date->mon,rtc_date->yea);
		Xbee_sendString(xbee_dev,str);;
		sprintf(str,"h>remoto1>stop>var>Humedad3");
		Xbee_sendString(xbee_dev,str);

		for(int i=0;i<4800000;i++);
		NVIC_SystemReset();

	}

    /* Send data */

}

void xbeeReset(void){
    GPIO_ClearPinsOutput(GPIOD, PIN1 ); 		//pinCS=0
    for(int i=0;i<1000;i++){
    	;
    }
    GPIO_SetPinsOutput(GPIOD, PIN1 ); 		//pinCS=0
}

static void confLmp(lmp_dev_t *dev){

	if(lmp_write(dev,ADC_AUXCN,RTD_CURR)!=0){
		PRINTF("Error de transmision dev\n\r\n\r");
	}

	if(lmp_write(dev,CH0_INPUTCN,CH0_IC)!=0){
		PRINTF("Error de transmision dev\n\r\n\r");
	}
	if(lmp_write(dev,CH0_CONFIG,CH0_CONF)!=0){
			PRINTF("Error de transmision dev\n\r\n\r");
	}
	if(lmp_write(dev,CH1_INPUTCN,CH1_IC)!=0){
		PRINTF("Error de transmision dev\n\r\n\r");
	}
	if(lmp_write(dev,CH2_INPUTCN,CH2_IC)!=0){
		PRINTF("Error de transmision devd\n\r\n\r");
	}
	if(lmp_write(dev,CH3_INPUTCN,CH3_IC)!=0){
		PRINTF("Error de transmision dev\n\r\n\r");
	}
	if(lmp_write(dev,CH4_INPUTCN,CH4_IC)!=0){
		PRINTF("Error de transmision dev\n\r\n\r");
	}


//	if(lmp_write(dev,CH1_CONFIG,CH1_CONF)!=0){
//		PRINTF("Error de transmision dev: %d\n\r\n\r");
//	}


}
