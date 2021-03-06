#include "sdspi.h"
/*!
 * @brief  Inicializa el dispositivo SPI dev->configurando los pines necesarios de la tarjeta
 *
 * @param dev puntero a un spi_dev. Debe tener asignados *dev.base y *dev.pin
 * @return 0 si la inicializacion se realizo exitosamente. 1 de lo contrario.
 */
uint8_t sdspi_init(sdspi_dev_t *dev){
    /* Inicializacion de pines para SPI0*/
	dev->spi_rtos_handle=pvPortMalloc(sizeof(spi_rtos_handle_t));
	dev->base=GPIOA;
	dev->pin=PIN5;
	sdspi_initPins(dev);
    /* Configuracion prioridad de interrupcion para SPI0*/
    NVIC_SetPriority(SPI0_IRQn, SPI_NVIC_PRIO);

    sdspi_reset(dev);

	return ERR_OK;
}

void sdspi_initPins(sdspi_dev_t *dev){
	/* Configuración de pin CS como salida digital inicializada en 1*/
    gpio_pin_config_t led_config = {
        kGPIO_DigitalOutput, 1,
    };

	/*Habilitando clocks para GPIOs*/
	CLOCK_EnableClock(kCLOCK_PortA);                          /* Port A Clock Gate Control: Clock enabled */
	CLOCK_EnableClock(kCLOCK_PortB);                          /* Port B Clock Gate Control: Clock enabled */
	CLOCK_EnableClock(kCLOCK_PortC);                          /* Port C Clock Gate Control: Clock enabled */
	CLOCK_EnableClock(kCLOCK_PortD);                          /* Port D Clock Gate Control: Clock enabled */
	CLOCK_EnableClock(kCLOCK_PortE);                          /* Port E Clock Gate Control: Clock enabled */
	PORT_SetPinMux(sdspi_getPort(dev->base), dev->pin, kPORT_MuxAsGpio);		/* Puerto de la base y pin especificados se configura como GPIO*/
	PORT_SetPinMux(PORTC, PIN5, kPORT_MuxAlt2);				/* PORTC5 (pin 50) is configured as SPI0_SCK */
	PORT_SetPinMux(PORTC, PIN6, kPORT_MuxAlt2);				/* PORTC6 (pin 51) is configured as SPI0_MOSI */
	PORT_SetPinMux(PORTC, PIN7, kPORT_MuxAlt2);				/* PORTC7 (pin 52) is configured as SPI0_MISO */

	/*Habilitando clocks para GPIOs*/
	GPIO_PinInit(dev->base, dev->pin, &led_config);
}

uint8_t sdspi_reset(sdspi_dev_t *dev){

    spi_transfer_t 	masterXfer = {0};
    status_t 				status;
    uint8_t					data_out[SD_RESET_SIZE];
    uint8_t					data_in[SD_RESET_SIZE];
    uint32_t 				mascara;
    uint32_t 				sourceClock;
	spi_master_config_t 	config;

	/* Generacion de estructura de configuración por defecto*/
    sdspi_getConfig(&config);


    sourceClock = CLOCK_GetFreq(kCLOCK_BusClk);
	status = SPI_RTOS_Init(dev->spi_rtos_handle, SPI0, &config, sourceClock);
	if (status != kStatus_Success)
	{
		return status;
	}

	memset(data_out,0xFF,SD_RESET_SIZE);
    /* Send and receive data through loopback  */
    masterXfer.txData = data_out;
    masterXfer.rxData = data_in;
    masterXfer.dataSize = SD_RESET_SIZE;

    /*Inicio de proceso de transferencia*/
    mascara = sdspi_mask(dev->pin); 					//obtencion de mascara para modificacion de CS

    GPIO_SetPinsOutput(dev->base, mascara ); 		//pinCS=0
    status = SPI_RTOS_Transfer(dev->spi_rtos_handle, &masterXfer);

	status = SPI_RTOS_Deinit(dev->spi_rtos_handle);

	if (status != kStatus_Success)
	{
		return status;
	}

	return ERR_OK;
}


void sdspi_getConfig(spi_master_config_t *config){
	config->enableMaster=true;
	config->enableStopInWaitMode = true;
	config->polarity = kSPI_ClockPolarityActiveHigh;
	config->phase = kSPI_ClockPhaseFirstEdge;
	config->direction = kSPI_MsbFirst;
	config->dataMode = kSPI_8BitMode;
	config->txWatermark = kSPI_TxFifoOneHalfEmpty;
	config->rxWatermark = kSPI_RxFifoOneHalfFull;
	config->pinMode = kSPI_PinModeNormal;
	config->outputMode = kSPI_SlaveSelectAsGpio;
	config->baudRate_Bps = sdspi_baudRate;
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
uint8_t sdspi_transfer(sdspi_dev_t *dev, uint8_t data_out[], uint8_t data_in[], uint8_t transfer_size){

    spi_transfer_t 	masterXfer = {0};
    status_t 				status;
    uint32_t 				mascara;
    uint32_t 				sourceClock;
	spi_master_config_t 	config;

	/* Generacion de estructura de configuración por defecto*/
    sdspi_getConfig(&config);

    sourceClock = CLOCK_GetFreq(kCLOCK_BusClk);
	status = SPI_RTOS_Init(dev->spi_rtos_handle, SPI0, &config, sourceClock);
	if (status != kStatus_Success)
	{
		return status;
	}

    /* Send and receive data through loopback  */
    masterXfer.txData = data_out;
    masterXfer.rxData = data_in;
    masterXfer.dataSize = transfer_size;

    /*Inicio de proceso de transferencia*/
    mascara = sdspi_mask(dev->pin); 					//obtencion de mascara para modificacion de CS

    GPIO_ClearPinsOutput(dev->base, mascara ); 		//pinCS=0
    status = SPI_RTOS_Transfer(dev->spi_rtos_handle, &masterXfer);
    GPIO_SetPinsOutput(dev->base, mascara );		//pinCS=1

	status = SPI_RTOS_Deinit(dev->spi_rtos_handle);
	if (status != kStatus_Success)
	{
		return status;
	}

    /*Verificacion de resultado de transferencia*/
    if (status != kStatus_Success)
    {
        return ERR_FAIL;
    }

	return ERR_OK;
}

uint32_t sdspi_mask(uint32_t pin){
	return 1u<<pin;
}

PORT_Type * sdspi_getPort(GPIO_Type *gpio){
	switch((uint32_t)gpio){
		case (uint32_t)GPIOA:
			return PORTA;
		case (uint32_t)GPIOB:
			return PORTB;
		case (uint32_t)GPIOC:
			return PORTC;
		case (uint32_t)GPIOD:
			return PORTD;
	}
	return PORTC;
}
