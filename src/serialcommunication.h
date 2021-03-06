/*
 * serialcommunication.h
 *
 *  Created on: Feb 14, 2017
 *      Author: tungnk
 */

#ifndef SERIALCOMMUNICATION_H_
#define SERIALCOMMUNICATION_H_
#include <termios.h>
#include "queue.h"
#include <fcntl.h>
#include "ltecmd.h"

#define MAX_SERIAL_PACKAGE_SIZE	512
#define SERIAL_QUEUE_SIZE		8

typedef struct stSerial {
	unsigned int uiBaudrate;
	int tty_fd;
	PQUEUECONTROL pInputQueue;
	PQUEUECONTROL pOutputQueue;
}SERIAL, *PSERIAL;

/* Exported Function */
PSERIAL SerialOpen (char* portName, unsigned int uiBaudrate);
void SerialClose(PSERIAL pSerialPort);
void SerialProcessIncomingData(PSERIAL pSerialPort);
void SerialOutputDataProcess(PSERIAL pSerialPort);
BYTE SerialOutput (PSERIAL pSerialPort, PBYTE pData, WORD nSize);
#endif /* SERIALCOMMUNICATION_H_ */
