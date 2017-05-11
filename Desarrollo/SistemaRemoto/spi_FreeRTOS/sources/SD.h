/*
 * SD.h
 *
 *  Created on: Apr 19, 2017
 *      Author: luis
 */

#ifndef _SD_H_
#define _SD_H_

#include "spi.h"
#include "fsl_gpio.h"
#include "fsl_common.h"

/*deficines GLUE*/
typedef uint8_t BYTE;

/* Status of Disk Functions */
typedef uint8_t		DSTATUS;
typedef uint32_t	DWORD;
typedef uint32_t	UINT;

/* Results of Disk Functions */
typedef enum {
	RES_OK = 0,		/* 0: Successful */
	RES_ERROR,		/* 1: R/W Error */
	RES_WRPRT,		/* 2: Write Protected */
	RES_NOTRDY,		/* 3: Not Ready */
	RES_PARERR		/* 4: Invalid Parameter */
} DRESULT;

typedef struct co_dev{
	GPIO_Type *base;
	uint32_t pin;
}co_dev_t;

typedef struct SD_dev{
	spi_dev_t 	*spi_port;
	co_dev_t *co_pin;
}SD_dev_t;


/*!
 * crear los discos duros que tiene el sistema disponibles para almacenamiento
 *
 * */
#define SD0_PDRV 0 //Physical drive number
#define PDRV_NUMBER 1 //numero de elementos fisicos, se deben numerar sin espacios
static SD_dev_t SD_units[PDRV_NUMBER];//inicializa punteros para todos los discos duros tipo uSD

#define GO_IDLE_STATE           0U
#define SEND_OP_COND     	    1U
#define SEND_CSD                9U
#define STOP_TRANSMISSION       12U
#define SEND_STATUS             13U
#define SET_BLOCK_LEN           16U
#define READ_SINGLE_BLOCK       17U
#define READ_MULTIPLE_BLOCKS    18U
#define WRITE_SINGLE_BLOCK      24U
#define WRITE_MULTIPLE_BLOCKS   25U
#define ERASE_BLOCK_START_ADDR  32U
#define ERASE_BLOCK_END_ADDR    33U
#define ERASE_SELECTED_BLOCKS   38U
#define CRC_ON_OFF              59U
#define ON     1
#define OFF    0
#define CMD_SIZE 	6
#define CRC 		0x95

/*!
 * Drive  SD0
 * Disco Duro tipo SD card conectado al PORT C de la tarjeta
 */
#define PDVR_SD0 0 //primer disco duro
#define BASE_SPI1	GPIOC
#define	PIN_SPI1	PIN4

extern volatile unsigned long startBlock;
extern volatile unsigned long totalBlocks;
extern volatile unsigned char buffer[512];

DSTATUS disk_initialize (BYTE pdrv);
DSTATUS disk_status (BYTE pdrv);
DRESULT disk_read (BYTE pdrv, BYTE* buff, DWORD sector, UINT count);
DRESULT disk_write (BYTE pdrv, const BYTE* buff, DWORD sector, UINT count);
DRESULT disk_ioctl (BYTE pdrv, BYTE cmd, void* buff);

DSTATUS SD_sendCommand(uint8_t pdrv, uint8_t cmd, uint8_t *arg);
#endif /* SOURCES_SD_H_ */
