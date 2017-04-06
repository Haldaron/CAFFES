#include "spi.h"
/*!
 * @brief  Inicializa el dispositivo SPI dev->configurando los pines necesarios de la tarjeta
 *
 * @param dev puntero a un spi_dev. Debe tener asignados *dev.base y *dev.pin
 * @return 0 si la inicializacion se realizo exitosamente. 1 de lo contrario.
 */
uint8_t spi_init(spi_dev *dev){

	spi_master_config_t config;
	uint32_t 			sourceClock;
	status_t			status;

	/* Generacion de estructura de configuración por defecto*/
    spi_getConfig(&config);

    /* Inicializacion de pines para SPI0*/
    spi_initPins(dev);

    /* Configuracion prioridad de interrupcion para SPI0*/
    NVIC_SetPriority(SPI0_IRQn, SPI_NVIC_PRIO);


    sourceClock = CLOCK_GetFreq(kCLOCK_BusClk);
	status = SPI_RTOS_Init(dev->spi_rtos_handle, SPI0, &config, sourceClock);


	if (status != kStatus_Success)
	{
		return status;
	}


	return ERR_OK;
}

void spi_initPins(spi_dev *dev){
	  CLOCK_EnableClock(kCLOCK_PortA);                          /* Port A Clock Gate Control: Clock enabled */
	  CLOCK_EnableClock(kCLOCK_PortB);                          /* Port B Clock Gate Control: Clock enabled */
	  CLOCK_EnableClock(kCLOCK_PortC);                          /* Port C Clock Gate Control: Clock enabled */
	  CLOCK_EnableClock(kCLOCK_PortD);                          /* Port D Clock Gate Control: Clock enabled */
	  CLOCK_EnableClock(kCLOCK_PortE);                          /* Port E Clock Gate Control: Clock enabled */
	  PORT_SetPinMux(dev->base, dev->pin, kPORT_MuxAsGpio);		/* Puerto de la base y pin especificados se configura como GPIO*/
	  PORT_SetPinMux(PORTC, PIN5, kPORT_MuxAlt2);				/* PORTC5 (pin 50) is configured as SPI0_SCK */
	  PORT_SetPinMux(PORTC, PIN6, kPORT_MuxAlt2);				/* PORTC6 (pin 51) is configured as SPI0_MOSI */
	  PORT_SetPinMux(PORTC, PIN7, kPORT_MuxAlt2);				/* PORTC7 (pin 52) is configured as SPI0_MISO */
}

void spi_getConfig(spi_master_config_t *config){
	config->enableMaster=true;
	config->enableStopInWaitMode = false;
	config->polarity = kSPI_ClockPolarityActiveLow;
	config->phase = kSPI_ClockPhaseSecondEdge;
	config->direction = kSPI_MsbFirst;
	config->dataMode = kSPI_8BitMode;
	config->txWatermark = kSPI_TxFifoOneHalfEmpty;
	config->rxWatermark = kSPI_RxFifoOneHalfFull;
	config->pinMode = kSPI_PinModeNormal;
	config->outputMode = kSPI_SlaveSelectAsGpio;
	config->baudRate_Bps = 500000U;
}

/*!
 * @brief  Inicializa el dispositivo SPI configurando los pines necesarios de la tarjeta
 *
 * @param dev puntero a un spi_dev. Debe tener asignados *dev.base y *dev.pin
 * @param data_in puntero a espacio de memoria donde se guardaran los datos recibidos
 * @param data_out puntero a arreglo de datos a transmitir
 * @param transfer_size tamaño en bytes de la transferencia a realizar
 * @return 0 si la transferencia se realizo exitosamente. 1 de lo contrario.
 */
uint8_t spi_transfer(spi_dev *dev, uint8_t data_out[], uint8_t data_in[], uint8_t transfer_size){

    spi_transfer_t masterXfer = {0};
    status_t status;

    /* Send and receive data through loopback  */
    masterXfer.txData = data_out;
    masterXfer.rxData = data_in;
    masterXfer.dataSize = transfer_size;

    status = SPI_RTOS_Transfer(dev->spi_rtos_handle, &masterXfer);

    if (status != kStatus_Success)
    {

        PRINTF("SPI transfer completed with error. \r\n");
        return ERR_FAIL;
    }

	return ERR_OK;
}
