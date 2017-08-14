#ifndef I2C_CAFFES_H
#define I2C_CAFFES_H

/* Freescale includes. */
#include "board.h"
#include "fsl_debug_console.h"
#include "fsl_i2c.h"
#include "fsl_i2c_freertos.h"
#include "fsl_device_registers.h"
#include "pin_mux.h"
#include <stdbool.h>
#include <stdlib.h>
#include "clock_config.h"
#include "stdbool.h"
#include "fsl_common.h"
#include "fsl_port.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define I2C_MASTER_BASE (I2C1_BASE)
#define I2C_MASTER_IRQN (I2C1_IRQn)

#define I2C_MASTER ((I2C_Type *)I2C_MASTER_BASE)
#define I2C_SLAVE ((I2C_Type *)I2C_SLAVE_BASE)

#define I2C_MASTER_CLK_SRC (I2C1_CLK_SRC)

#define PIN6_IDX                         6u   /*!< Pin number for pin 6 in a port */
#define PIN7_IDX                         7u   /*!< Pin number for pin 7 in a port */

#define MAX_I2C_TRANS_ITER				0xEF


typedef struct i2c_dev{
	uint8_t 				slaveAddress;      	/*!< 7-bit slave address. */
	uint32_t				baud_rate;
	bool					masterCompletion;
} i2c_dev_t;


/*******************************************************************************
 * Prototypes
 ******************************************************************************/
uint8_t i2c_init(i2c_dev_t *dev, uint8_t address, uint32_t baud_rate);
void 	i2c_initPins(void);
uint8_t i2c_write(i2c_dev_t *dev, uint8_t subaddress, uint8_t data_in[], uint8_t transfer_size);
uint8_t i2c_read(i2c_dev_t *dev, uint8_t subaddress, uint8_t data_out[], uint8_t transfer_size);

#endif
