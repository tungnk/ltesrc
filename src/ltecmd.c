
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <stddef.h>
#include <string.h>
#include <pthread.h>
#include "ltecmd.h"

BYTE gsmRestartCount;
WORD gsmCheckBillingCount;
PGSMMODEM gsmModem = NULL;

void printHelp() {
	printf( "Usage: ltecon [-hsm] \n"
		" -h help \n"
		" -m mode: 3g or 4g \n"
		"  connecting over serial  ttyUSB2 \n"		);

}

char* StrDup(const char* string)
{
	if (string == NULL) return NULL;
	char* pDest = malloc(strlen(string) + 1);
	memset(pDest, 0, strlen(string) + 1);
	memcpy(pDest, string, strlen(string));
	return pDest;
}

static void GsmSetRestart(BYTE nCount)
{
	gsmRestartCount = nCount;
}

BYTE GsmModemGetStatus()
{
	return gsmModem->status;
}

void GsmModemSetStatus(char status, char* command)
{
	gsmModem->status = status;
	char* newCommand = StrDup(command);
	if (gsmModem->waitingCommand != NULL )
	{
		free( gsmModem->waitingCommand);
		gsmModem->waitingCommand = NULL;
	}
	gsmModem->waitingCommand = newCommand;
}

void GsmModemSetCmdStatus(char* commandStatus)
{
	char* newCmdStatus = StrDup(commandStatus);
	if (gsmModem->commandStatus != NULL )
	{
		free( gsmModem->commandStatus);
		gsmModem->commandStatus = NULL;
	}
	gsmModem->commandStatus = newCmdStatus;
}

BYTE GsmModemExecuteCommand(char* command)
{
	WORD timeout;
	if ( gsmModem->status == GSM_MODEM_OFF )
		return COMMAND_ERROR;
	while( gsmModem->status != GSM_MODEM_ACTIVE )
	{
		sleep(1);
	}
	GsmModemSetCmdStatus(NULL);

	atSendCommand( command, gsmModem->serialPort);

	GsmModemSetStatus(GSM_MODEM_WAITING, command);

	timeout  = 0;

	char* eventMessage = malloc(50);

	memset ( eventMessage,0,50);
	while ( gsmModem->status == GSM_MODEM_WAITING )
	{
		usleep(100000);
		timeout++;
		if ( timeout == GSM_COMMAND_TIMEOUT )
		{
			GsmModemSetStatus( GSM_MODEM_ACTIVE, NULL );
			free ( eventMessage );
			return COMMAND_TIMEOUT;
		}
	}
	if (gsmModem->status == GSM_MODEM_CMD_ERROR )
	{
		printf( "command %s failed\n", gsmModem->waitingCommand );
		sprintf(eventMessage, "command.%s.error", gsmModem->waitingCommand);
		GsmModemSetStatus(GSM_MODEM_ACTIVE, NULL);
		free (eventMessage);
		return COMMAND_ERROR;
	}
	free ( eventMessage );
	return COMMAND_SUCCESS;
}

BOOL initModem()
{
	static pthread_t processThread;

	static pthread_t outputThread;

	static pthread_t handleThread;

	BYTE bCommandState = COMMAND_SUCCESS;

	char *command = malloc(255);

	/* open serial port */
	char *portName = malloc(strlen("/dev/ttyUSB2") + 1);

	memset( portName,0,strlen("/dev/ttyUSB2") + 1);

	printf("Open port %s\n",portName);

    /* open serial port for communication with modem */
	PSERIAL pSerialPort = SerialOpen(portName, B57600);

	if (pSerialPort == NULL )
	{
		printf( "Can not open serial port %s, try another port\n", portName );
		GsmSetRestart(5);
		return FALSE;
	}
	free(portName);
	return TRUE;
}

int main(int argc, char* argv[])
{
	/* Get option */
	int ch = 0;

	char serialPort[8] = "ttyUSB2";//malloc(sizeof("ttyUSB2"));
	char *conMode = NULL;

	static struct option long_options[] = {
			{ "serial", required_argument, 0, 's' },
	};

	int long_index;
	/* Process option */
	while (( ch = getopt_long(argc, argv,":hm:",
			long_options, &long_index )) != -1) {
		switch (ch) {
		case 'h' :
			printHelp();
			return EXIT_SUCCESS;
			break;
		case 'm' :
			conMode = StrDup(optarg);
			break;
		default:
			break;
		}
	}
	if ( conMode == NULL ) {
		printf( "invalid options, using -h for help\n" );
		return EXIT_FAILURE;

	}
	/* All option valid, start program */
	puts(" Program start ");
	/* Call function argument serialPort hier */
	//printf("serial port:%s\n",&serialPort);
	printf("connection mode:%s\n",optarg);
	return EXIT_SUCCESS;


}
