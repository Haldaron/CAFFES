#ifndef SPI_CAFFES_H
#define SPI_CAFFES_H
/* FreeRTOS kernel includes. */

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


/*!

 */
typedef enum _pin_number
{
    PIN1 = 1U, 			/*!< Pin 1 de la base asociada*/
	PIN2 = 2U, 			/*!< Pin 2 de la base asociada*/
	PIN3 = 3U, 			/*!< Pin 3 de la base asociada*/
	PIN4 = 4U, 			/*!< Pin 4 de la base asociada*/
	PIN5 = 5U, 			/*!< Pin 5 de la base asociada*/
	PIN6 = 6U, 			/*!< Pin 6 de la base asociada*/
	PIN7 = 7U, 			/*!< Pin 7 de la base asociada*/
	PIN8 = 8U, 			/*!< Pin 8 de la base asociada*/
	PIN9 = 9U, 			/*!< Pin 9 de la base asociada*/
	PIN10 = 10U, 		/*!< Pin 10 de la base asociada*/
	PIN11 = 11U, 		/*!< Pin 11 de la base asociada*/
	PIN12 = 12U, 		/*!< Pin 12 de la base asociada*/
	PIN13 = 13U, 		/*!< Pin 13 de la base asociada*/
	PIN14 = 14U, 		/*!< Pin 14 de la base asociada*/
	PIN15 = 15U, 		/*!< Pin 15 de la base asociada*/
	PIN16 = 16U, 		/*!< Pin 16 de la base asociada*/
	PIN17 = 17U, 		/*!< Pin 17 de la base asociada*/
	PIN18 = 18U, 		/*!< Pin 18 de la base asociada*/
	PIN19 = 19U, 		/*!< Pin 19 de la base asociada*/
	PIN20 = 20U, 		/*!< Pin 20 de la base asociada*/
	PIN21 = 21U, 		/*!< Pin 21 de la base asociada*/
	PIN22 = 22U, 		/*!< Pin 22 de la base asociada*/
	PIN23 = 23U, 		/*!< Pin 23 de la base asociada*/
	PIN24 = 24U, 		/*!< Pin 24 de la base asociada*/
	PIN25 = 25U, 		/*!< Pin 25 de la base asociada*/
} pin_number;

#define SD_RESET_SIZE				10
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
