/*
 * SD.c
 *
 *  Created on: Apr 19, 2017
 *      Author: luis
 */

#include "SD.h"

/*!
 * @brief: Inicializa un dispositivo SD card.
 * @return: SD_STATUS- ERROR_OK indica que el dipositivo quedo bien inicializado
 * */


DSTATUS disk_initialize (uint8_t pdrv){
	DSTATUS error=0;
	SD_units[pdrv].spi_port->base=BASE_SPI1;
	SD_units[pdrv].spi_port->pin=PIN_SPI1;
	if(spi_init(SD_units[pdrv].spi_port)!=0){
		error=1;//muestra un error si no se puede inicializar el puerto SPI
	}
	SD_units[pdrv].co_pin=NULL; // por el momento no se le va asignar un pin de CO al dispositivo

	return error;
}


DSTATUS SD_sendCommand(uint8_t pdrv, uint8_t cmd, uint8_t *arg){
	uint8_t buffer_in[CMD_SIZE];
	uint8_t buffer_out[CMD_SIZE];
	/*se conforma el comando que se va a enviar*/
	buffer_in[0]=(cmd&0x3F)|0x40; // _0_1_cmd[5]_cmd[4]_cmd[3]_cmd[2]_cmd[1]_cmd[0]_
	buffer_in[1]=*(arg);
	buffer_in[2]=*(arg+1);
	buffer_in[3]=*(arg+2);
	buffer_in[4]=*(arg+3);
	buffer_in[5]=CRC;
	/*writes in the spi port*/
	return spi_transfer(SD_units[pdrv].spi_port, buffer_out, buffer_in,CMD_SIZE);
}

