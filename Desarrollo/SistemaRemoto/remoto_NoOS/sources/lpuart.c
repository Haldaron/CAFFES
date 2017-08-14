#include "lpuart.h"

void lpuart_callback(LPUART_Type *base, lpuart_handle_t *handle, status_t status, void *userData)
{
    lpuart_dev_t *dev = (lpuart_dev_t *)userData;

    if (kStatus_LPUART_TxIdle == status)
    {
        dev->txOnGoing = false;
    }

    if (kStatus_LPUART_RxIdle == status)
    {
        dev->rxOnGoing = false;
    }
}


/*!

 * @brief  Inicializa el dispositivo LPUART dev->configurando los pines necesarios de la tarjeta
 *
 * @param dev puntero a un lpuart_dev. Debe tener asignados *dev.base y *dev.pin
 * @return 0 si la inicializacion se realizo exitosamente. 1 de lo contrario.
 */
uint8_t lpuart_init(lpuart_dev_t *dev){
    /* Inicializacion de pines para LPUART0*/

	dev->lpuart_handle=malloc(sizeof(lpuart_handle_t));

	dev->txOnGoing=false;
	dev->rxOnGoing=false;

    /* Configuracion prioridad de interrupcion para LPUART0*/
    NVIC_SetPriority(LPUART0_IRQn, LPUART_NVIC_PRIO);

	return ERR_OK;
}


void lpuart_getConfig(lpuart_config_t *config){

	LPUART_GetDefaultConfig(config);
    config->baudRate_Bps = 9600U;
    config->parityMode = kLPUART_ParityDisabled;
    config->stopBitCount = kLPUART_OneStopBit;
    config->enableTx = true;
    config->enableRx = true;
}

/*!
 * @brief  Inicializa el dispositivo LPUART configurando los pines necesarios de la tarjeta
 *
 * @param dev puntero a un lpuart_dev. Debe tener asignados *dev.base y *dev.pin
 * @param data_in puntero a espacio de memoria donde se guardaran los datos recibidos
 * @param data_out puntero a arreglo de datos a transmitir
 * @param transfer_size tamaño en bytes de la transferencia a realizar
 * @return 0 si la transferencia se realizo exitosamente. 1 de lo contrario.
 */
uint8_t lpuart_transferSend(lpuart_dev_t *dev, uint8_t data_out[], uint8_t transfer_size){

    lpuart_transfer_t 		xfer = {0};
    status_t 				status;
	lpuart_config_t			config;
	uint8_t					i=0;

	/* Generacion de estructura de configuración por defecto*/
	dev->txOnGoing=true;

	lpuart_getConfig(&config);
	LPUART_Init( LPUART0, &config, CLOCK_GetFreq(kCLOCK_McgIrc48MClk));
	LPUART_EnableTx(LPUART_BASE,true);
	LPUART_EnableRx(LPUART_BASE,true);
//	LPUART_TransferCreateHandle(LPUART_BASE, dev->lpuart_handle, lpuart_callback, (void *)dev);



    /* Send and receive data through loopback  */
    xfer.data=data_out;
    xfer.dataSize = transfer_size;

    /*Inicio de proceso de transferencia*/
//    status = LPUART_TransferSendNonBlocking(LPUART_BASE, dev->lpuart_handle, &xfer);
    LPUART_WriteBlocking(LPUART_BASE,data_out,transfer_size);
    while(dev->txOnGoing!=false && i<=MAX_UART_TRANS_ITER){
    	i++;
    }

    LPUART_Deinit(LPUART_BASE);
    /*Verificacion de resultado de transferencia*/
    if (status != kStatus_Success)
    {
        return ERR_FAIL;
    }


	return ERR_OK;
}

