/*
 * queue.h
 *
 *  Created on: Feb 14, 2017
 *      Author: tungnk
 */

#ifndef QUEUE_H_
#define QUEUE_H_
#include "ltecmd.h"
typedef struct tagQueueControl {
	BYTE nQueueSize;
	WORD nBufferSize;
	BYTE nState;
	BYTE nCurrentPointer;
	BYTE nFreePointer;
	PBYTE pContent;
	PBYTE pContentLenght;
} QUEUECONTROL, *PQUEUECONTROL;





#endif /* QUEUE_H_ */
