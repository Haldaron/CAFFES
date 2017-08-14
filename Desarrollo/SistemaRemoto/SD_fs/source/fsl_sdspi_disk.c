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
 * DISCLAIMED. IN NO EVENT SL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <assert.h>
#include <stdio.h>
#include <string.h>
#include "fsl_sdspi.h"
#include "fsl_gpio.h"
#include "fsl_sdspi_disk.h"
#include "sdspi.h"

/*******************************************************************************
 * Definitons
 ******************************************************************************/

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/
/* Save current time in milliseconds */
volatile uint32_t g_milliseconds;

/* SDSPI driver state. */
sdspi_card_t g_card;
sdspi_host_t g_host;
/*******************************************************************************
 * Code - SD disk interface
 ******************************************************************************/

#if _USE_WRITE
DRESULT sdspi_disk_write(uint8_t physicalDrive, const uint8_t *buffer, uint32_t sector, uint8_t count)
{
    if (physicalDrive != SDSPIDISK)
    {
        return RES_PARERR;
    }

    if (kStatus_Success != SDSPI_WriteBlocks(&g_card, (uint8_t *)buffer, sector, count))
    {
        return RES_ERROR;
    }
    return RES_OK;
}
#endif

DRESULT sdspi_disk_read(uint8_t physicalDrive, uint8_t *buffer, uint32_t sector, uint8_t count)
{
    if (physicalDrive != SDSPIDISK)
    {
        return RES_PARERR;
    }

    if (kStatus_Success != SDSPI_ReadBlocks(&g_card, buffer, sector, count))
    {
        return RES_ERROR;
    }
    return RES_OK;
}

#if _USE_IOCTL
DRESULT sdspi_disk_ioctl(uint8_t physicalDrive, uint8_t command, void *buffer)
{
    DRESULT result = RES_OK;

    if (physicalDrive != SDSPIDISK)
    {
        return RES_PARERR;
    }

    switch (command)
    {
        case GET_SECTOR_COUNT:
            if (buffer)
            {
                *(uint32_t *)buffer = g_card.blockCount;
            }
            else
            {
                result = RES_PARERR;
            }
            break;
        case GET_SECTOR_SIZE:
            if (buffer)
            {
                *(uint32_t *)buffer = g_card.blockSize;
            }
            else
            {
                result = RES_PARERR;
            }
            break;
        case GET_BLOCK_SIZE:
            if (buffer)
            {
                *(uint32_t *)buffer = g_card.csd.eraseSectorSize;
            }
            else
            {
                result = RES_PARERR;
            }
            break;
        case CTRL_SYNC:
            result = RES_OK;
            break;
        default:
            result = RES_PARERR;
            break;
    }
    return result;
}
#endif

DSTATUS sdspi_disk_status(uint8_t physicalDrive)
{
    if (physicalDrive != SDSPIDISK)
    {
        return STA_NOINIT;
    }
    return 0;
}

DSTATUS sdspi_disk_initialize(uint8_t physicalDrive)
{
    if (physicalDrive == SDSPIDISK)
    {
        spi_init();
        sdspi_host_init();
        SDSPI_Init(&g_card);
        g_card.host = &g_host;
        return 0;
    }
    return STA_NOINIT;
}

/*******************************************************************************
 * Code - SPI interface
 ******************************************************************************/

void spi_init(void)
{
    sdspi_init(&sdspi_dev);
    g_card.blockCount=30316544;
    g_card.blockSize=512;
}

status_t spi_set_frequency(uint32_t frequency)
{
	sdspi_baudRate=frequency;
    return kStatus_Success;
}

status_t spi_exchange(uint8_t *in, uint8_t *out, uint32_t size)
{
	uint8_t status;

	for(int i;i<size;i++){
		PRINTF("data%d: %X\n\r",i,in[i]);
	}
	status=sdspi_transfer(&sdspi_dev,in,out,size);

    return status;
}

void SysTick_Handler(void)
{
    g_milliseconds++;
}

void timer_init(void)
{
    /* Set systick reload value to generate 1ms interrupt */
    SysTick_Config(CLOCK_GetFreq(kCLOCK_CoreSysClk) / 1000U);
}

uint32_t timer_get_current_milliseconds(void)
{
    return g_milliseconds;
}

void sdspi_host_init(void)
{
    /* Initializes timer to make host's callback function "timer_get_current_milliseconds" workable. */
    timer_init();

    /* Saves host state and callback. */
    g_host.busBaudRate = DSPI_BUS_BAUDRATE;
    g_host.setFrequency = spi_set_frequency;
    g_host.exchange = spi_exchange;
    g_host.getCurrentMilliseconds = timer_get_current_milliseconds;

    /* Saves card state. */
    g_card.host = &g_host;
}
