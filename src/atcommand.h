/*
 * atcommand.h
 *
 *  Created on: Feb 16, 2017
 *      Author: tungnk
 */

#ifndef ATCOMMAND_H_
#define ATCOMMAND_H_


#include "serialcommunication.h"

typedef void(*ATHANDLEFN)(void* param, char* message);

void atProcessInputByte(BYTE nData, PWORD index, PBYTE pReceiveBuffer, PSERIAL pSerialPort);
void atHandleMessage (PBYTE pData, WORD nSize);
void atHandleCgcontrdpEvent(char* message);
void atSendCommand(char* command, PSERIAL serialPort);
void atRegisterIncommingProc(void (*function)(void* pParam, char* message), void* param);


#endif /* ATCOMMAND_H_ */
