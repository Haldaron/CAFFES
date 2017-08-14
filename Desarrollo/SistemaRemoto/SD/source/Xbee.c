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

	lpuart_dev_t 			*dev=malloc(sizeof(lpuart_dev_t));

	lpuart_init(dev);

	xbee_dev->lpuart_dev=dev;

    NVIC_SetPriority(LPUART0_IRQn, 5);
}

void Xbee_setFrame(Xbee_frame* frame, char* msg){
	unsigned int msgLength=strlen(msg);
	unsigned char *frameData=malloc(msgLength+5);
	//frame->RFData=malloc(msgLength); //pone el cero el buffer


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

	free(frameData);
}

void Xbee_APISend(Xbee_dev_t *xbee_dev, Xbee_frame* frame){

	lpuart_transferSend(xbee_dev->lpuart_dev,&frame->startDelimiter,1);
	lpuart_transferSend(xbee_dev->lpuart_dev,&frame->lengthMSB,1);
	lpuart_transferSend(xbee_dev->lpuart_dev,&frame->lengthLSB,1);
	lpuart_transferSend(xbee_dev->lpuart_dev,&frame->APIIdentifier,1);
	lpuart_transferSend(xbee_dev->lpuart_dev,&frame->FrameID,1);
	lpuart_transferSend(xbee_dev->lpuart_dev,&frame->DestinationAddressMSB,1);
	lpuart_transferSend(xbee_dev->lpuart_dev,&frame->DestinationAddressLSB,1);
	lpuart_transferSend(xbee_dev->lpuart_dev,&frame->Options,1);
	lpuart_transferSend(xbee_dev->lpuart_dev,frame->RFData,strlen(frame->RFData));
	lpuart_transferSend(xbee_dev->lpuart_dev,&frame->checkSum,1);
}

void Xbee_sendString(Xbee_dev_t *dev, char *str){
	Xbee_frame 	*frame=malloc(sizeof(Xbee_frame));

	Xbee_setFrame(frame, str);
	Xbee_APISend(dev, frame);

	free(frame);
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
