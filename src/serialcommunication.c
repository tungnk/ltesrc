/*
 * serialcommunication.c
 *
 *  Created on: Feb 14, 2017
 *      Author: tungnk
 */

#include "serialcommunication.h"
#include "queue.h"
static WORD g_nPackageIndex;

/*
 * Function: SerialOpen ( unsigned int uiBaudrate )
 * Description:
 * - Open the serial port with the port name is given by typing
 * - Giving input and output queue for data read and write
 * Input:
 * - uiBaudrate: Baudrate of the port.
 * Return:
 * - pointer to serial management data struct.
 * */

PSERIAL SerialOpen(char* portname, unsigned int uiBaudrate)
{
	struct termios stSerialIo;
	PSERIAL pSerialPort = (PSERIAL)malloc(sizeof(SERIAL));
	pSerialPort->tty_fd = -1;
	/* Configure the port */
	memset(&stSerialIo, 0, sizeof(stSerialIo));
	stSerialIo.c_iflag = 0; // raw input
	stSerialIo.c_oflag = 0; // raw output
	stSerialIo.c_cflag = 0;
	stSerialIo.c_lflag = 0;
	stSerialIo.c_cc[VMIN] = 1;
	stSerialIo.c_cc[VTIME] = 0;

}

