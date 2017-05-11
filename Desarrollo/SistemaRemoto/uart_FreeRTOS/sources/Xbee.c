#include "Xbee.h"

/*
Calcula el checksum de frame Data de una estructura.
*/
unsigned char checkSum(unsigned char *mensaje, unsigned int n){
	unsigned char suma=0;//totalizador
	int i=0;//acumulador
	for(i=0;i<n;i++){
		suma+=mensaje[i];
	}
	return 0xFF-suma;
}

void Xbee_init(Xbee_dev_t *xbee_dev){

	lpuart_rtos_handle_t 	*handle=pvPortMalloc(sizeof(lpuart_rtos_handle_t));
	lpuart_handle_t 		*t_handle=pvPortMalloc(sizeof(lpuart_handle_t));
	lpuart_rtos_config_t 	*lpuart_config = pvPortMalloc(sizeof(lpuart_rtos_config_t));
	uint8_t 				*background_buffer=pvPortMalloc(100*sizeof(char));

	lpuart_config->baudrate = 9600;
	lpuart_config->parity = kLPUART_ParityDisabled;
	lpuart_config->stopbits = kLPUART_OneStopBit;
	lpuart_config->buffer = background_buffer;
	lpuart_config->buffer_size = sizeof(background_buffer);
    lpuart_config->srcclk = CLOCK_GetFreq(kCLOCK_McgIrc48MClk);
    lpuart_config->base = LPUART0;


	xbee_dev->handle=handle;
	xbee_dev->t_handle=t_handle;
	xbee_dev->lpuart_config=lpuart_config;

    NVIC_SetPriority(LPUART0_IRQn, 5);
}

void Xbee_setFrame(Xbee_frame* frame, char* msg){
	unsigned int msgLength=strlen(msg);
	unsigned char *frameData=pvPortMalloc(msgLength+5);
	//frame->RFData=pvPortMalloc(msgLength); //pone el cero el buffer


	frame->startDelimiter=START_DELIMITER;
	frame->lengthMSB=LENGTH_MSB;
	frame->lengthLSB=(unsigned char)(msgLength+5);
	frame->APIIdentifier=API_IDENTIFIER;
	frame->FrameID=FRAME_ID;
	frame->DestinationAddressMSB=DEST_ADDR_MSB;
	frame->DestinationAddressLSB=DEST_ADDR_LSB;
	frame->Options=OPTIONS;
	frame->RFData=msg;
	//copia el mensaje que se desea transmitir a RFData 
	//memcpy(frame->RFData,msg,msgLength); //copia el mensaje
	//Calcula el checkSum de Frame Data
	memcpy(frameData+API_IDENTIFIER_OFFSET,&frame->APIIdentifier,API_IDENTIFIER_SIZE);
	memcpy(frameData+FRAME_ID_OFFSET,&frame->FrameID,FRAME_ID_SIZE);
	memcpy(frameData+DEST_ADDR_MSB_OFFSET,&frame->DestinationAddressMSB,DEST_ADDR_MSB_SIZE);
	memcpy(frameData+DEST_ADDR_LSB_OFFSET,&frame->DestinationAddressLSB,DEST_ADDR_LSB_SIZE);
	memcpy(frameData+OPTIONS_OFFSET,&frame->Options,OPTIONS_SIZE);
	memcpy(frameData+RFDATA_OFFSET,frame->RFData,msgLength);
	frame->checkSum=checkSum(frameData,msgLength+5);

	vPortFree(frameData);
}

void Xbee_APISend(Xbee_dev_t *xbee_dev, Xbee_frame* frame){


    if (0 > LPUART_RTOS_Init(xbee_dev->handle, xbee_dev->t_handle, xbee_dev->lpuart_config)){
        vTaskSuspend(NULL);
    }

	LPUART_RTOS_Send(xbee_dev->handle,&frame->startDelimiter,1);
	LPUART_RTOS_Send(xbee_dev->handle,&frame->lengthMSB,1);
	LPUART_RTOS_Send(xbee_dev->handle,&frame->lengthLSB,1);
	LPUART_RTOS_Send(xbee_dev->handle,&frame->APIIdentifier,1);
	LPUART_RTOS_Send(xbee_dev->handle,&frame->FrameID,1);
	LPUART_RTOS_Send(xbee_dev->handle,&frame->DestinationAddressMSB,1);
	LPUART_RTOS_Send(xbee_dev->handle,&frame->DestinationAddressLSB,1);
	LPUART_RTOS_Send(xbee_dev->handle,&frame->Options,1);
	LPUART_RTOS_Send(xbee_dev->handle,frame->RFData,strlen(frame->RFData));
	LPUART_RTOS_Send(xbee_dev->handle,&frame->checkSum,1);


    if (0 > LPUART_RTOS_Deinit(xbee_dev->handle))
    {
        vTaskSuspend(NULL);
    }
}
void Xbee_printFrame(Xbee_frame* frame){
	int i=0;
	printf("Delimiter: %02x\n",frame->startDelimiter);
	printf("lengthMSB: %02x\n",frame->lengthMSB);
	printf("lengthLSB: %02x\n",frame->lengthLSB);
	printf("API Identifier: %02x\n",frame->APIIdentifier);
	printf("FrameID: %02x\n",frame->FrameID);
	printf("DestinationAddressMSB: %02x\n",frame->DestinationAddressMSB);
	printf("DestinationAddressLSB: %02x\n",frame->DestinationAddressLSB);
	printf("Options: %02x\n",frame->Options);
	for(i=0;i<=strlen(frame->RFData)-1;i++){		
		printf("RFDATA[%d]: %02x\n",i,frame->RFData[i]);
	}
	printf("checkSum: %02x\n",frame->checkSum);
}
