#include "lmp.h"

uint8_t lmp_init(lmp_dev_t* dev, GPIO_Type *base, uint32_t pin){

	spi_dev_t	*spi_dev=malloc(sizeof(spi_dev_t));
	dev->spi=spi_dev;

	if(spi_init(dev->spi,base,pin)!=0){
		return ERR_FAIL;
	}
	return ERR_OK;
}

uint8_t lmp_write(lmp_dev_t* dev, uint8_t address, uint8_t data){
	uint8_t status;
	uint8_t	set_ura[URA_SETTING_SIZE];
	uint8_t rec_data[WRITE_SIZE];
	uint8_t	*set_write=malloc(WRITE_SIZE*sizeof(uint8_t));

	set_ura[0]=WRITE_URA;
	set_ura[1]=lmp_getURA(address);


	/*URA setting*/
	spi_transfer(dev->spi, set_ura, rec_data, URA_SETTING_SIZE);

	/*Read register*/
	set_write[0]=WRITE_REG|lmp_getSizeMask(WRITE_SIZE)|(address&LRA_MASK);
	set_write[1]=data;

	status=spi_transfer(dev->spi, set_write, rec_data, WRITE_SIZE);

	free(set_write);

	return status;
}

uint8_t lmp_read(lmp_dev_t* dev,uint8_t address,uint8_t* data, uint8_t size){
	uint8_t status;
	uint8_t	set_ura[URA_SETTING_SIZE];
	uint8_t	*set_read=malloc(size*sizeof(uint8_t));

	set_ura[0]=WRITE_URA;
	set_ura[1]=lmp_getURA(address);


	/*URA setting*/
	spi_transfer(dev->spi, set_ura, data, URA_SETTING_SIZE);

	/*Read register*/
	set_read[0]=READ_REG|lmp_getSizeMask(size)|(address&LRA_MASK);
	status=spi_transfer(dev->spi, set_read, data, size);

	free(set_read);

	return status;
}

uint8_t lmp_getMeasure(lmp_dev_t* dev, uint32_t* lectura){
	uint8_t status;
	uint8_t data_in[ADC_READ_SIZE];

	status=lmp_read(dev,ADC_DOUT,data_in,ADC_READ_SIZE);

	*lectura=(data_in[3]+data_in[2]*256+data_in[1]*65536);

	return status;
}

uint8_t lmp_confMeasure(lmp_dev_t* dev, uint8_t mode, uint8_t first_ch, uint8_t last_ch){
	uint8_t status;
	uint8_t conf;

	conf= mode|first_ch|last_ch;
	status=lmp_write(dev,CH_SCAN,conf);

	return status;

}

uint8_t lmp_getSizeMask(uint8_t size){
	if(size-1==1){
		return BYTES_1;
	}else if(size-1==2){
		return BYTES_2;
	}else if(size-1==3){
		return BYTES_3;
	}
	return BYTES_X;
}

uint8_t lmp_dataReady(lmp_dev_t *dev){
	uint8_t data[DATA_RDY_SIZE];

	lmp_read(dev,ADC_DONE,data, DATA_RDY_SIZE);
	if(data[1]==DT_NOT_AVAIL){
		return 0;
	}

	return 1;
}

uint8_t lmp_getURA(uint8_t address){

	return address>>4;
}

