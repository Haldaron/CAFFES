#ifndef LMP_CAFFES_H
#define LMP_CAFFES_H

#include "spi.h"
#include "stdlib.h"

/*--------------------------------------------------------------------------*/
/*
 *                DIRECCION REGISTROS INTERNOS DEL LMP90100
 */


#define RESETCN 			0x00
#define SPI_HANDSHAKECN		0x01
#define SPI_RESET 			0x02
#define SPI_STREAMCN  		0x03

#define PWRCN  				0x08
#define DATA_ONLY_1  		0x09
#define DATA_ONLY_2  		0x0A
#define ADC_RESTART  		0x0B

#define GPIO_DIRCN 			0x0E
#define GPIO_DAT 			0x0F
#define BGCALCN 			0x10
#define SPI_DRDYBCN 		0x11
#define ADC_AUXCN 			0x12
#define SPI_CRC_CN 			0x13
#define SENDIAG_THLD  		0x14

#define SCALCN 				0x17
#define ADC_DONE 			0x18
#define SENDIAG_FLAGS 		0x19
#define ADC_DOUT 			0x1A
#define SPI_CRC_DAT 		0x1D

/* Registros para configuracion de canales de medicion*/
#define CH_STS 				0x1E
#define CH_SCAN 			0x1F
#define CH0_INPUTCN 		0x20
#define CH0_CONFIG			0x21
#define CH1_INPUTCN 		0x22
#define CH1_CONFIG 			0x23
#define CH2_INPUTCN 		0x24
#define CH2_CONFIG 			0x25
#define CH3_INPUTCN 		0x26
#define CH3_CONFIG 			0x27
#define CH4_INPUTCN 		0x28
#define CH4_CONFIG 			0x29
#define CH5_INPUTCN 		0x2A
#define CH5_CONFIG 			0x2B
#define CH6_INPUTCN			0x2C
#define CH6_CONFIG			0x2D

#define CH0_SCAL_OFFSET		0x30
#define CH0_SCAL_GAIN		0x33
#define CH0_SCAL_SCALING	0x36

/*--------------------------------------------------------------------------*/
/*
 *                MASCARAS PARA DIRECCION
 */

#define URA_MASK	0b01110000
#define LRA_MASK	0b00001111

/*--------------------------------------------------------------------------*/
/*
 *                CONFIGURACION REGISTROS INTERNOS DEL LMP90100
 */


/*
RESETCN
 */
#define RESET_CMD		0xC3


/*
SPI_HANDSHAKECN
 */



/*
SPI_RESET
 */



/*
SPI_STREAMCN
 */



/*
PWRCN
 */


/*
BGCALCN
 */

#define BGCALMODE0	0U		/* BGCAL apagado*/
#define BGCALMODE1	1U		/* OffSetCorrection-GainEstimation*/
#define BGCALMODE2	2U		/* OffSetCorrection-GainCorrection*/
#define BGCALMODE3	3U		/* OffSetEstimation-GainEstimation*/


/*
SPI_DRDYBCN
 */
#define SPI_DRDYB_D6_AS_GPIO	0x00U	/* Usar el pin D6 como GPIO*/
#define SPI_DRDYB_D6_AS_DRDY	0x80U	/* Usar el pin D6 como Data Ready*/
#define CRC_RST_ENABLE			0x00U	/* Habilitar reset del CRC*/
#define CRC_RST_DISABLE			0x20U	/* Deshabilitar reset del CRC*/
#define FGA_BGCAL_CORRECTION	0x00U	/* BGCAL con correccion*/
#define FGA_BGCAL_ESTIMATION	0x08U	/* BGCAL con estimacion*/

/*
ADC_AUXCN
 */
#define RTD_CUR_1000U		0x0AU	/* Fuentes de corriente generan 1000uA*/
#define RTD_CUR_900U		0x09U	/* Fuentes de corriente generan 900uA*/
#define RTD_CUR_800U		0x08U	/* Fuentes de corriente generan 800uA*/
#define RTD_CUR_700U		0x07U	/* Fuentes de corriente generan 700uA*/
#define RTD_CUR_600U		0x06U	/* Fuentes de corriente generan 600uA*/
#define RTD_CUR_500U		0x05U	/* Fuentes de corriente generan 500uA*/
#define RTD_CUR_400U		0x04U	/* Fuentes de corriente generan 400uA*/
#define RTD_CUR_300U		0x03U	/* Fuentes de corriente generan 300uA*/
#define RTD_CUR_200U		0x02U	/* Fuentes de corriente generan 200uA*/
#define RTD_CUR_100U		0x01U	/* Fuentes de corriente generan 100uA*/
#define RTD_CUR_0U			0x00U	/* Fuentes de corriente generan 0uA*/


/*
ADC_DONE
 */
#define DT_NOT_AVAIL		0xFF		/* No hay dato disponible. Cualquier otro valor indica lo contrario*/


/*
BGCALCN
 */



/*
CH_SCAN
 */
#define	SCAN_MODE0		0x00
#define	SCAN_MODE1		0x40
#define	SCAN_MODE2		0x80
#define	SCAN_MODE3		0xC0

#define CH0_FIRST		0x00
#define CH1_FIRST		0x01
#define CH2_FIRST		0x02
#define CH3_FIRST		0x03
#define CH4_FIRST		0x04
#define CH5_FIRST		0x05
#define CH6_FIRST		0x06

#define CH0_LAST		0x08
#define CH1_LAST		0x10
#define CH2_LAST		0x18
#define CH3_LAST		0x20
#define CH4_LAST		0x28
#define CH5_LAST		0x30
#define CH6_LAST		0x38




/*
CHx_INPUTCN
 */

#define BURNOUT_EN		0x80
#define BURNOUT_DIS		0x00

#define VREF1			0x00
#define VREF2			0x40

#define VINP0			0x00
#define VINP1			0x08
#define VINP2			0x10
#define VINP3			0x18
#define VINP4			0x20
#define VINP5			0x28
#define VINP6			0x30
#define VINP7			0x38

#define VINN0			0x00
#define VINN1			0x01
#define VINN2			0x02
#define VINN3			0x03
#define VINN4			0x04
#define VINN5			0x05
#define VINN6			0x06
#define VINN7			0x07


/*
CHx_CONFIG:
 */
#define ODR_1_6775 		0x00U
#define ODR_3_355 		0x10U
#define ODR_6_71 		0x20U
#define ODR_13_42 		0x30U
#define ODR_26_83125	0x40U
#define ODR_53_6625		0x50U
#define ODR_107_325		0x60U
#define ODR_214_65 		0x70U

#define FGA_OFF_1		0x00U
#define FGA_OFF_2		0x02U
#define FGA_OFF_4		0x04U
#define FGA_OFF_8		0x06U
#define FGA_ON_16		0x08U
#define FGA_ON_32		0x0AU
#define FGA_ON_64		0x0CU
#define FGA_ON_128		0x0EU

#define BUFF_OFF		0
#define BUFF_ON			1


/*--------------------------------------------------------------------------*/
/*
 *                ESTADOS DE LA COMUNICIÓN CON EL LMP90100
 *
 * Estas definiciones contienen los valuees posibles de st_lmp.
 */
#define LMP_OK		0x00U
#define LMP_ESPERA 	0x01U
#define LMP_ERROR	0x02U

/*Transaction 1-URA Setup*/
#define URA_SETTING_SIZE	0x02
#define	WRITE_SIZE			0x02
#define ADC_READ_SIZE		0x04
#define DATA_RDY_SIZE		0x02
#define WRITE_URA 			0x10
#define READ_URA  			0x90

/*Transaction 2-Data Access*/
#define WRITE_REG 		0X00
#define READ_REG  		0X80

 /**Size Transaction 2*/
#define BYTES_1 0x00 /*1 Byte*/
#define BYTES_2 0x20 /*2 Bytes*/
#define BYTES_3 0x40 /*3 Bytes*/
#define BYTES_X 0x80 /**Streaming 3+ Bytes hasta que se desactive CS*/



typedef struct{
	spi_dev_t* 	spi;    		/*No es necesario que el usuario instancie este campo.*/
	GPIO_Type 	*base;			/*!< Base del pin a utilizar como CS. Ej: GPIOA, GPIOB, GPIOC... */
	uint32_t 	pin;			/*!< pin_number a utilizar como CS. Ej: PIN1,PIN2... */
}lmp_dev_t;

uint8_t lmp_init(lmp_dev_t* dev, GPIO_Type *base, uint32_t pin);

uint8_t lmp_write(lmp_dev_t* dev, uint8_t address, uint8_t data);

uint8_t lmp_read(lmp_dev_t* dev,uint8_t address,uint8_t* data, uint8_t size);

uint8_t lmp_getMeasure(lmp_dev_t* dev, uint32_t* lectura);

uint8_t lmp_confMeasure(lmp_dev_t* dev, uint8_t mode, uint8_t first_ch, uint8_t last_ch);

uint8_t lmp_getSizeMask(uint8_t size);

uint8_t lmp_dataReady(lmp_dev_t *dev);

uint8_t lmp_getURA(uint8_t address);

#endif /* LMP_H_ */
