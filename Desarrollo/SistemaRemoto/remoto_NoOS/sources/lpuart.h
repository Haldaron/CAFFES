#ifndef LPUART_CAFFES_H
#define LPUART_CAFFES_H
/* FreeRTOS kernel includes. */

/* Freescale includes. */
#include "fsl_device_registers.h"
#include "fsl_debug_console.h"
#include "fsl_lpuart.h"
#include "board.h"
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

#define LPUART_BASE	LPUART0
#define MAX_UART_TRANS_ITER		0xEF

#if (__CORTEX_M >= 0x03)
#define LPUART_NVIC_PRIO 6
#else
#define LPUART_NVIC_PRIO 1
#endif



/*!
 * @brief  Inicializa el dispositivo LPUART configurando los pines necesarios de la tarjeta
 *
 * @param dev puntero a un LPUART_dev. Debe tener asignados *dev.base y *dev.pin
 * @return 0 si la inicializacion se realizo exitosamente. 1 de lo contrario.
 */

typedef struct lpuart_dev{
	lpuart_handle_t	*lpuart_handle;
	uint32_t		txOnGoing;
	uint32_t		rxOnGoing;
}lpuart_dev_t;



/*!
 * @brief  Inicializa el dispositivo LPUART configurando los pines necesarios de la tarjeta
 *
 * @param dev puntero a un LPUART_dev. Debe tener asignados *dev.base y *dev.pin
 * @return 0 si la inicializacion se realizo exitosamente. 1 de lo contrario.
 */
uint8_t lpuart_init(lpuart_dev_t *dev);

/*!
 * @brief  Inicializa el dispositivo LPUART configurando los pines necesarios de la tarjeta
 *
 * @param dev puntero a un lpuart_dev. Debe tener asignados *dev.base y *dev.pin
 * @param data_in puntero a espacio de memoria donde se guardaran los datos recibidos
 * @param data_out puntero a arreglo de datos a transmitir
 * @param transfer_size tamaño en bytes de la transferencia a realizar
 * @return 0 si la transferencia se realizo exitosamente. 1 de lo contrario.
 */
uint8_t lpuart_transferSend(lpuart_dev_t *dev, uint8_t data_out[], uint8_t transfer_size);

void lpuart_getConfig(lpuart_config_t *config);

#endif

