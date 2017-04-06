#include "Xbee.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>  /* UNIX standard function definitions */
#include <fcntl.h>   /* File control definitions */
#include <errno.h>   /* Error number definitions */
#include <termios.h> /* POSIX terminal control definitions */

int open_port(void){
  int fd; /* File descriptor for the port */		
  fd = open("/dev/ttyUSB1", O_RDWR | O_NOCTTY | O_NDELAY);
  if (fd == -1)
  {
   /*
    * Could not open the port.
    */

    perror("open_port: Unable to open /dev/ttyf1 - ");
  }
  else
    fcntl(fd, F_SETFL, 0);

  return (fd);
}


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

void Xbee_setFrame(Xbee_frame* frame, char* msg){
	unsigned int msgLength=strlen(msg);
	unsigned char *frameData=malloc(msgLength+5);
	frame->startDelimiter=START_DELIMITER;
	frame->lengthMSB=LENGTH_MSB;
	frame->lengthLSB=(unsigned char)(msgLength+5);
	frame->APIIdentifier=API_IDENTIFIER;
	frame->FrameID=FRAME_ID;
	frame->DestinationAddressMSB=DEST_ADDR_MSB;
	frame->DestinationAddressLSB=DEST_ADDR_LSB;
	frame->Options=OPTIONS;
	//copia el mensaje que se desea transmitir a RFData 
	frame->RFData=malloc(msgLength); //pone el cero el buffer
	memcpy(frame->RFData,msg,msgLength); //copia el mensaje
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

void Xbee_APISend(Xbee_frame* frame){
	int identifier=open_port();
	write(identifier,&frame->startDelimiter,1);
	write(identifier,&frame->lengthMSB,1);
	write(identifier,&frame->lengthLSB,1);
	write(identifier,&frame->APIIdentifier,1);
	write(identifier,&frame->FrameID,1);
	write(identifier,&frame->DestinationAddressMSB,1);
	write(identifier,&frame->DestinationAddressLSB,1);
	write(identifier,&frame->Options,1);
	write(identifier,frame->RFData,strlen(frame->RFData));
	write(identifier,&frame->checkSum,1);	
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
