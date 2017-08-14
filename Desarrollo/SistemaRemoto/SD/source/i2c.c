#include "i2c.h"

static void i2c_master_callback(I2C_Type *base, i2c_master_handle_t *handle, status_t status, void *userData)
{
    /* Signal transfer success when received success status. */
    i2c_dev_t *dev=userData;

	if (status == kStatus_Success)
    {
        dev->masterCompletion = true;
    }
}

/*!
 * @brief  Inicializa el dispositivo i2c dev  configurando los pines necesarios de la tarjeta
 *
 * @param dev puntero a un spi_dev. Debe tener asignados *dev.base y *dev.pin
 * @return 0 si la inicializacion se realizo exitosamente. 1 de lo contrario.
 */
uint8_t i2c_init(i2c_dev_t *dev, uint8_t address, uint32_t baud_rate){


	/* Inicializacion de pines para I2C1*/
	i2c_initPins();

	/* Alocando memoria en heap para dispositivo virtual*/
	dev->slaveAddress=address;
	dev->baud_rate=baud_rate;

	if (__CORTEX_M >= 0x03)
		NVIC_SetPriority(I2C_MASTER_IRQN, 6);
	else
		NVIC_SetPriority(I2C_MASTER_IRQN, 3);

	    /*
	     * masterConfig.baudRate_Bps = 100000U;
	     * masterConfig.enableHighDrive = false;
	     * masterConfig.enableStopHold = false;
	     * masterConfig.glitchFilterWidth = 0U;
	     * masterConfig.enableMaster = true;
	     */



    return kStatus_Success;
}

void i2c_initPins(void){
	/* Configuración de pin CS como salida digital inicializada en 1*/
	  CLOCK_EnableClock(kCLOCK_PortD);                           /* Port D Clock Gate Control: Clock enabled */

	  PORT_SetPinMux(PORTD, PIN6_IDX, kPORT_MuxAlt4);            /* PORTD6 (pin 63) is configured as I2C1_SDA */
	  PORT_SetPinMux(PORTD, PIN7_IDX, kPORT_MuxAlt4);            /* PORTD7 (pin 64) is configured as I2C1_SCL */
}

uint8_t i2c_write(i2c_dev_t *dev, uint8_t subaddress, uint8_t data_in[], uint8_t transfer_size){

	i2c_master_transfer_t 	masterXfer;
	i2c_master_handle_t		master_handle;
	uint32_t 				sourceClock;
	i2c_master_config_t		masterConfig;
    status_t 				status;
    uint8_t					i=0;

	I2C_MasterGetDefaultConfig(&masterConfig);
	masterConfig.baudRate_Bps = dev->baud_rate;
	sourceClock = CLOCK_GetFreq(I2C_MASTER_CLK_SRC);

	I2C_MasterInit(I2C_MASTER, &masterConfig, sourceClock);
    I2C_MasterTransferCreateHandle(I2C_MASTER, &master_handle, i2c_master_callback, dev);


	/* Generacion de estructura de configuración por defecto*/
    memset(&masterXfer, 0, sizeof(masterXfer));
	masterXfer.slaveAddress = dev->slaveAddress;
	masterXfer.direction = kI2C_Write;
	masterXfer.subaddress = subaddress;
	masterXfer.subaddressSize = 1;
	masterXfer.data = data_in;
	masterXfer.dataSize = transfer_size;
	masterXfer.flags = kI2C_TransferDefaultFlag;

	dev->masterCompletion=false;

    status=I2C_MasterTransferNonBlocking(I2C_MASTER, &master_handle, &masterXfer);

    PRINTF("Write I2C: post transfer\n\r");
    /*  Wait for transfer completed. */
    while(dev->masterCompletion!=true && i<=MAX_I2C_TRANS_ITER){
    	i++;
    }

	I2C_MasterDeinit(I2C_MASTER);

	return status;
}

uint8_t i2c_read(i2c_dev_t *dev, uint8_t subaddress, uint8_t data_out[], uint8_t transfer_size){

	i2c_master_transfer_t 	masterXfer;
	i2c_master_handle_t		master_handle;
	uint32_t 				sourceClock;
	i2c_master_config_t		masterConfig;
	status_t 				status;
	uint8_t					i=0;

	I2C_MasterGetDefaultConfig(&masterConfig);
	masterConfig.baudRate_Bps = dev->baud_rate;
	sourceClock = CLOCK_GetFreq(I2C_MASTER_CLK_SRC);

	I2C_MasterInit(I2C_MASTER, &masterConfig, sourceClock);
	I2C_MasterTransferCreateHandle(I2C_MASTER, &master_handle, i2c_master_callback, dev);

	/* Generacion de estructura de configuración por defecto*/
    memset(&masterXfer, 0, sizeof(i2c_master_transfer_t));
	masterXfer.slaveAddress = dev->slaveAddress;
	masterXfer.direction = kI2C_Read;
	masterXfer.subaddress = subaddress;
	masterXfer.subaddressSize = 1;
	masterXfer.data = data_out;
	masterXfer.dataSize = transfer_size;
	masterXfer.flags = kI2C_TransferDefaultFlag;
	PRINTF("Read I2C: pre transfer\n");
	dev->masterCompletion=false;

    status=I2C_MasterTransferNonBlocking(I2C_MASTER, &master_handle, &masterXfer);
    PRINTF("Read I2C: post transfer\n\r");
    /*  Wait for transfer completed. */
    while(dev->masterCompletion!=true && i<=MAX_I2C_TRANS_ITER){
    	i++;
    }

	if (status != kStatus_Success)
	{
		PRINTF("I2C master: error during read transaction, %X\n\r", status);
	}

	I2C_MasterDeinit(I2C_MASTER);

	return status;
}

