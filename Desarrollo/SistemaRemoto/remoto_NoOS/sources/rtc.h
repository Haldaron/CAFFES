#ifndef RTC_CAFFES_H
#define RTC_CAFFES_H
/* FreeRTOS kernel includes. */

#include "i2c.h"
#include <string.h>
#include <stdlib.h>

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define ADDRESS		0x68 /*Direccion I2C de dispositivo*/

#define DATE 		__DATE__
#define TIME 		__TIME__
#define MONTH (\
  __DATE__ [2] == 'n' ? (__DATE__ [1] == 'a' ? 1 : 6) \
: __DATE__ [2] == 'b' ? 2 \
: __DATE__ [2] == 'r' ? (__DATE__ [0] == 'M' ? 3 : 4) \
: __DATE__ [2] == 'y' ? 5 \
: __DATE__ [2] == 'l' ? 7 \
: __DATE__ [2] == 'g' ? 8 \
: __DATE__ [2] == 'p' ? 9 \
: __DATE__ [2] == 't' ? 10 \
: __DATE__ [2] == 'v' ? 11 \
: 12)

/*Registros*/
#define SEG				0
#define MINU			1
#define HOU				2
#define WEEK			3
#define DAY				4
#define MON				5
#define YEA				6
#define CON				7
#define	REG_SIZE		1
#define	DATE_SIZE		7

/*SEG*/
#define HALT		0x80
#define START		0x00

/*HOURS*/
#define F_12HOUR	0x20
#define F_24HOUR	0x00
#define BAUDRATE	100000


typedef struct rtc_dev{
	i2c_dev_t 	*i2c_handle; 	/*!< estructura de configuracion. */
} rtc_dev_t;

typedef struct rtc_date{
	uint32_t	seg;	/*segundos*/
	uint32_t	min;	/*minutos*/
	uint32_t	hou;	/*hora*/
	uint32_t	week;	/*dia de semana*/
	uint32_t	day;	/*dia de mas*/
	uint32_t	mon;	/*mes*/
	uint32_t	yea;	/*año*/
} rtc_date_t;


/*******************************************************************************
 * Prototypes
 ******************************************************************************/
uint8_t rtc_init(rtc_dev_t *dev, uint8_t address);
uint8_t rtc_halt(rtc_dev_t *dev);
uint8_t rtc_start(rtc_dev_t *dev);
uint8_t rtc_write(rtc_dev_t *dev, rtc_date_t *date);
uint8_t rtc_read(rtc_dev_t *dev, rtc_date_t *data);
uint8_t binary_to_bsd(uint8_t binary);
uint8_t rtc_updateToCompilationTime(rtc_dev_t *dev);

#endif
