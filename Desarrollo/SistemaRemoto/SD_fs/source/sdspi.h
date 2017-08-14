#ifndef SDSPI_CAFFES_H
#define SDSPI_CAFFES_H
/* FreeRTOS kernel includes. */

/* Freescale includes. */
#include "fsl_device_registers.h"
#include "fsl_debug_console.h"
#include "fsl_spi.h"
#include "spi.h"
#include "board.h"
#include "fsl_gpio.h"
#include "fsl_common.h"
#include "fsl_port.h"
#include "pin_mux.h"
#include "clock_config.h"
#include <stdlib.h>


#include "stdint.h"

#ifndef ERR_OK
	#define ERR_OK		0U
#endif

#ifndef ERR_FAIL
	#define ERR_FAIL	1U
#endif

#define SDSPI_MASTER_BASE	SPI0
#define MAX_SPI_TRANS_ITER			0xEF



#if (__CORTEX_M >= 0x03)
#define SPI_NVIC_PRIO 6
#else
#define SPI_NVIC_PRIO 2
#endif



#define SD_RESET_SIZE				20
#define SD_BASE						GPIOA
#define SD_PIN						PIN5

typedef struct sdspi_dev{
	spi_master_handle_t 	*spi_handle; /*!< estructura de configuracion. */
	bool					masterFinished;
} sdspi_dev_t;


sdspi_dev_t	sdspi_dev;
uint32_t	sdspi_baudRate;

/*!
 * @brief  Inicializa el dispositivo SPI configurando los pines necesarios de la tarjeta
 *
 * @param dev puntero a un spi_dev. Debe tener asignados *dev.base y *dev.pin
 * @return 0 si la inicializacion se realizo exitosamente. 1 de lo contrario.
 */


/*!
 * @brief  Inicializa el dispositivo SPI configurando los pines necesarios de la tarjeta
 *
 * @param dev puntero a un spi_dev. Debe tener asignados *dev.base y *dev.pin
 * @return 0 si la inicializacion se realizo exitosamente. 1 de lo contrario.
 */
uint8_t sdspi_init(sdspi_dev_t *dev);

/*!
 * @brief  Inicializa el dispositivo SPI configurando los pines necesarios de la tarjeta
 *
 * @param dev puntero a un spi_dev. Debe tener asignados *dev.base y *dev.pin
 * @param data_in puntero a espacio de memoria donde se guardaran los datos recibidos
 * @param data_out puntero a arreglo de datos a transmitir
 * @param transfer_size tamaño en bytes de la transferencia a realizar
 * @return 0 si la transferencia se realizo exitosamente. 1 de lo contrario.
 */
uint8_t sdspi_transfer(sdspi_dev_t *dev, uint8_t data_out[], uint8_t data_in[], uint8_t transfer_size);

void sdspi_reset(sdspi_dev_t *dev);
void sdspi_initPins(sdspi_dev_t *dev);
void sdspi_getConfig(spi_master_config_t *config);
uint32_t sdspi_mask(uint32_t pin);
PORT_Type * sdspi_getPort(GPIO_Type *gpio);

#endif
