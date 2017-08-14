#include "spi.h"

static void masterCallback(SPI_Type *base, spi_master_handle_t *handle, status_t status, void *userData)
{
    masterFinished = true;
}

/*!

 * @brief  Inicializa el dispositivo SPI dev->configurando los pines necesarios de la tarjeta
 *
 * @param dev puntero a un spi_dev. Debe tener asignados *dev.base y *dev.pin
 * @return 0 si la inicializacion se realizo exitosamente. 1 de lo contrario.
 */
uint8_t spi_init(spi_dev_t *dev, GPIO_Type *base,uint32_t pin){
    /* Inicializacion de pines para SPI0*/

    uint32_t 				mascara;

	dev->spi_handle=malloc(sizeof(spi_master_handle_t));

	dev->pin=pin;
	dev->base=base;

	spi_initPins(dev);

    /* Configuracion prioridad de interrupcion para SPI0*/
    NVIC_SetPriority(SPI0_IRQn, SPI_NVIC_PRIO);

    mascara = spi_mask(dev->pin);
    GPIO_SetPinsOutput(dev->base, mascara );		//pinCS=1
	return ERR_OK;
}

void spi_initPins(spi_dev_t *dev){
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
	PORT_SetPinMux(spi_getPort(dev->base), dev->pin, kPORT_MuxAsGpio);		/* Puerto de la base y pin especificados se configura como GPIO*/
	PORT_SetPinMux(PORTC, PIN5, kPORT_MuxAlt2);				/* PORTC5 (pin 50) is configured as SPI0_SCK */
	PORT_SetPinMux(PORTC, PIN6, kPORT_MuxAlt2);				/* PORTC6 (pin 51) is configured as SPI0_MOSI */
	PORT_SetPinMux(PORTC, PIN7, kPORT_MuxAlt2);				/* PORTC7 (pin 52) is configured as SPI0_MISO */

	/*Habilitando clocks para GPIOs*/
	GPIO_PinInit(dev->base, dev->pin, &led_config);
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
	config->baudRate_Bps = 100000U;
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
uint8_t spi_transfer(spi_dev_t *dev, uint8_t data_out[], uint8_t data_in[], uint8_t transfer_size){

    spi_transfer_t 			masterXfer = {0};
    status_t 				status;
    uint32_t 				mascara;
    uint32_t 				sourceClock;
	spi_master_config_t 	config;

	/* Generacion de estructura de configuración por defecto*/
	masterFinished=false;

	spi_getConfig(&config);
    sourceClock = CLOCK_GetFreq(kCLOCK_BusClk);
	SPI_MasterInit( SPI_MASTER_BASE, &config, sourceClock);
	SPI_MasterTransferCreateHandle(SPI_MASTER_BASE, dev->spi_handle, masterCallback, NULL);



    /* Send and receive data through loopback  */
    masterXfer.txData = data_out;
    masterXfer.rxData = data_in;
    masterXfer.dataSize = transfer_size;

    /*Inicio de proceso de transferencia*/
    mascara = spi_mask(dev->pin); 					//obtencion de mascara para modificacion de CS

    GPIO_ClearPinsOutput(dev->base, mascara ); 		//pinCS=0
    status = SPI_MasterTransferNonBlocking(SPI_MASTER_BASE, dev->spi_handle, &masterXfer);
    while(masterFinished!=true){
    	;
    }
    GPIO_SetPinsOutput(dev->base, mascara );		//pinCS=1

    /*Verificacion de resultado de transferencia*/
    if (status != kStatus_Success)
    {
        return ERR_FAIL;
    }

	SPI_Deinit(SPI_MASTER_BASE);

	return ERR_OK;
}

uint32_t spi_mask(uint32_t pin){
	return 1u<<pin;
}

PORT_Type * spi_getPort(GPIO_Type *gpio){
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
