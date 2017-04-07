#include "lmp.h"

uint8_t lmp_init(lmp_dev_t* dev, GPIO_Type *base, uint32_t pin){

	spi_dev_t *spi_dev=pvPortMalloc(sizeof(spi_dev_t));
	spi_dev->base=base;
	spi_dev->pin =pin;

}

uint8_t lmp_write(lmp_dev_t* dev, uint8_t address, uint8_t* data, uint8_t size);

uint8_t lmp_read(lmp_dev_t* dev,uint8_t address,uint8_t* data, uint8_t size);

uint8_t lmp_getMeasure(lmp_dev_t* dev, uint32_t* lectura);

uint8_t lmp_confMeasure(lmp_dev_t* dev,uint8_t first_ch, uint8_t last_ch);
