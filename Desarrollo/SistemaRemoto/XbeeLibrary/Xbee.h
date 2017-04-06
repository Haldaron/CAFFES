#ifndef _XBEE_H_
#define _XBEE_H_

#define RFDATA_BUFFER_SIZE 100

#define START_DELIMITER 0X7E
#define LENGTH_MSB 0x00
#define API_IDENTIFIER 0x01
#define FRAME_ID 0x00
#define DEST_ADDR_MSB 0xFF
#define DEST_ADDR_LSB 0xFF
#define OPTIONS 0x00


#define API_IDENTIFIER_OFFSET 0U
#define API_IDENTIFIER_SIZE 1U
#define FRAME_ID_OFFSET 1U
#define FRAME_ID_SIZE 1U
#define DEST_ADDR_MSB_OFFSET 2U
#define DEST_ADDR_MSB_SIZE 1U
#define DEST_ADDR_LSB_OFFSET 3U
#define DEST_ADDR_LSB_SIZE 1U
#define OPTIONS_OFFSET 4U
#define OPTIONS_SIZE 1U
#define RFDATA_OFFSET 5U


typedef struct XbeeFrame{
	unsigned char startDelimiter;
	unsigned char lengthMSB;
	unsigned char lengthLSB;
	unsigned char APIIdentifier;
	unsigned char FrameID;
	unsigned char DestinationAddressMSB;
	unsigned char DestinationAddressLSB;
	unsigned char Options;
	char *RFData;
	unsigned char checkSum;
}Xbee_frame;

unsigned char checkSum(unsigned char *mensaje, unsigned int n);

void Xbee_setFrame(Xbee_frame* frame, char* msg);

void Xbee_APISend(Xbee_frame* frame);

void Xbee_printFrame(Xbee_frame* frame);
#endif
