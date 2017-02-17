/*
 * ltecmd.h
 *
 *  Created on: Feb 14, 2017
 *      Author: tungnk
 */

#ifndef LTECMD_H_
#define LTECMD_H_
#include "serialcommunication.h"

#define SIM_800_BOOT_TIME 	30

#define GSM_MODEM_ACTIVE		0x00
#define	GSM_MODEM_WAITING		0x01
#define GSM_MODEM_CMD_ERROR		0x02
#define GSM_MODEM_OFF			0x03

#define COMMAND_SUCCESS	0x00
#define COMMAND_ERROR	0x01
#define COMMAND_TIMEOUT	0x02
typedef unsigned char BOOL;
typedef unsigned char BYTE;
typedef unsigned char* PBYTE;
typedef unsigned short WORD;
typedef unsigned short* PWORD;


#ifndef TRUE
#  define TRUE (1==1)
#  define FALSE (!TRUE)
#endif


typedef struct tagGSMDEVICE {
	PSERIAL serialPort;
	BYTE 	status;
	BYTE 	powerMode;
	char* 	waitingCommand;
	char* 	commandStatus;
	char* 	carrier;
	char* 	apn;
	char* 	ipAddress;
	char* 	gateway;
	char* 	nameServer;
} GSMMODEM, *PGSMMODEM;

void GsmModemSetIpAddress(char* ipAddress);
void GsmModemSetGateway(char* gateway);
void GsmModemSetNameServer(char* nameServer);
BOOL GsmModemInit(char* SerialPort, int ttl);

#endif /* LTECMD_H_ */
