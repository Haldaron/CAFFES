#include "rtc.h"

/*!
 * @brief  Inicializa el dispositivo i2c dev  configurando los pines necesarios de la tarjeta
 *
 * @param dev puntero a un spi_dev. Debe tener asignados *dev.base y *dev.pin
 * @return 0 si la inicializacion se realizo exitosamente. 1 de lo contrario.
 */
uint8_t rtc_init(rtc_dev_t *dev, uint8_t address){

	dev->i2c_handle=pvPortMalloc(sizeof(i2c_dev_t));
	return i2c_init(dev->i2c_handle,address,BAUDRATE);
}

/*!
 * @brief  Inicializa el dispositivo i2c dev  configurando los pines necesarios de la tarjeta
 *
 * @param dev puntero a un spi_dev. Debe tener asignados *dev.base y *dev.pin
 * @return 0 si la inicializacion se realizo exitosamente. 1 de lo contrario.
 */
uint8_t rtc_halt(rtc_dev_t *dev){

	uint8_t	data=HALT;
	return i2c_write(dev->i2c_handle,SEG,&data,REG_SIZE);
}

uint8_t rtc_start(rtc_dev_t *dev){

	uint8_t	data=START;
	return i2c_write(dev->i2c_handle,SEG,&data,REG_SIZE);
}

uint8_t rtc_write(rtc_dev_t *dev, rtc_date_t *date){
	uint8_t 	data[DATE_SIZE];

	data[0]=binary_to_bsd(date->seg);
	data[1]=binary_to_bsd(date->min);
	data[2]=binary_to_bsd(date->hou);
	data[3]=binary_to_bsd(date->week);
	data[4]=binary_to_bsd(date->day);
	data[5]=binary_to_bsd(date->mon);
	data[6]=binary_to_bsd(date->yea);

	return i2c_write(dev->i2c_handle,SEG,data,DATE_SIZE);
}

uint8_t rtc_read(rtc_dev_t *dev, rtc_date_t *date){
	uint8_t 	data[DATE_SIZE];
    status_t 	status;

	status=i2c_read(dev->i2c_handle,SEG,data,DATE_SIZE);
	date->seg=data[0];
	date->min=data[1];
	date->hou=data[2];
	date->week=data[3];
	date->day=data[4];
	date->mon=data[5];
	date->yea=data[6];

	return status;
}

uint8_t binary_to_bsd(uint8_t binary){
	return 16*(binary/10)+binary%10;
}

uint8_t rtc_updateToCompilationTime(rtc_dev_t *dev){
	rtc_date_t date;
	char delim[2]=":";
	char time[20]=TIME;
	char strdate[20]=DATE;
	char *str;

	str=strtok(time,delim);
	date.hou=atoi(str);

	str=strtok(NULL,delim);
	date.min=atoi(str);

	str=strtok(NULL,delim);
	date.seg=atoi(str);


	delim[0]=' ';

	str=strtok(strdate,delim);
	date.mon=MONTH;

	str=strtok(NULL,delim);
	date.day=atoi(str);

	str=strtok(NULL,delim);
	date.yea=atoi(str)%100;

	PRINTF("%d/%d/%d  -  %d:%d:%d\n\r",date.day,date.mon,date.yea,date.hou,date.min,date.seg);

	rtc_write(dev,&date);

	return 0;
}
