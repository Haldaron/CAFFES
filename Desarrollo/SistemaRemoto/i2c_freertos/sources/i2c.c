#include "i2c.h"
/*!
 * @brief  Inicializa el dispositivo i2c dev  configurando los pines necesarios de la tarjeta
 *
 * @param dev puntero a un spi_dev. Debe tener asignados *dev.base y *dev.pin
 * @return 0 si la inicializacion se realizo exitosamente. 1 de lo contrario.
 */
uint8_t i2c_init(spi_dev_t *dev, uint32_t baud_rate){

	i2c_master_config_t masterConfig;
	uint32_t sourceClock;

	/* Inicializacion de pines para I2C1*/
	i2c_initPins();

	/* Alocando memoria en heap para dispositivo virtual*/
	dev->i2c_rtos_handle=pvPortMalloc(sizeof(i2c_rtos_handle_t));

	if (__CORTEX_M >= 0x03)
		NVIC_SetPriority(EXAMPLE_I2C_MASTER_IRQN, 6);
	else
		NVIC_SetPriority(EXAMPLE_I2C_MASTER_IRQN, 3);

	    /*
	     * masterConfig.baudRate_Bps = 100000U;
	     * masterConfig.enableHighDrive = false;
	     * masterConfig.enableStopHold = false;
	     * masterConfig.glitchFilterWidth = 0U;
	     * masterConfig.enableMaster = true;
	     */
	I2C_MasterGetDefaultConfig(&masterConfig);
	masterConfig.baudRate_Bps = baud_rate;
	sourceClock = CLOCK_GetFreq(I2C_MASTER_CLK_SRC);

	status = I2C_RTOS_Init(dev->i2c_rtos_handle, EXAMPLE_I2C_MASTER, &masterConfig, sourceClock);
	if (status != kStatus_Success)
	{
		PRINTF("I2C master: error during init, %d", status);
	}

	return ERR_OK;
}

void i2c_initPins(void){
	/* Configuración de pin CS como salida digital inicializada en 1*/
	  CLOCK_EnableClock(kCLOCK_PortD);                           /* Port D Clock Gate Control: Clock enabled */

	  PORT_SetPinMux(PORTD, PIN6_IDX, kPORT_MuxAlt4);            /* PORTD6 (pin 63) is configured as I2C1_SDA */
	  PORT_SetPinMux(PORTD, PIN7_IDX, kPORT_MuxAlt4);            /* PORTD7 (pin 64) is configured as I2C1_SCL */

}

uint8_t spi_write(spi_dev_t *dev, uint8_t address, uint8_t data_out[], uint8_t transfer_size){

	i2c_master_transfer_t 	masterXfer;
    status_t 				status;
	/* Generacion de estructura de configuración por defecto*/
    memset(&masterXfer, 0, sizeof(masterXfer));
	masterXfer.slaveAddress = I2C_MASTER_SLAVE_ADDR_7BIT;
	masterXfer.direction = kI2C_Write;
	masterXfer.subaddress = address;
	masterXfer.subaddressSize = 1;
	masterXfer.data = g_master_buff;
	masterXfer.dataSize = transfer_size;
	masterXfer.flags = kI2C_TransferDefaultFlag;

	status = I2C_RTOS_Transfer(dev->i2c_rtos_handle, &masterXfer);
	if (status != kStatus_Success)
	{
		PRINTF("I2C master: error during write transaction, %d", status);
	}
}

