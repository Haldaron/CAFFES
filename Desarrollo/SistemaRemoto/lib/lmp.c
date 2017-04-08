#include "lmp.h"

uint8_t lmp_init(lmp_dev_t* dev, GPIO_Type *base, uint32_t pin){

	dev->spi->base=base;
	dev->spi->pin =pin;

	if(spi_init(dev->spi)!=0){
		return ERR_FAIL;
	}
	return ERR_OK;
}

uint8_t lmp_write(lmp_dev_t* dev, uint8_t address, uint8_t* data, uint8_t size);

uint8_t lmp_read(lmp_dev_t* dev,uint8_t address,uint8_t* data, uint8_t size){
	uint8_t status;
	uint8_t	set_ura[URA_SETTING_SIZE];
	uint8_t	*set_read=pvPortMalloc(size*sizeof(uint8_t));

	set_ura[0]=WRITE_URA;
	set_ura[1]=address&URA_MASK;


	/*URA setting*/
	spi_transfer(dev->spi, set_ura, data, URA_SETTING_SIZE);


	/*Read register*/
	set_read[0]=READ_REG|(address&LRA_MASK)|BYTES_3;
	status=spi_transfer(dev->spi, set_read, data, size);

	vPortFree(set_read);

	return status;
}

uint8_t lmp_getMeasure(lmp_dev_t* dev, uint32_t* lectura);

uint8_t lmp_confMeasure(lmp_dev_t* dev,uint8_t first_ch, uint8_t last_ch);
