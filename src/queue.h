/*
 * queue.h
 *
 *  Created on: Feb 14, 2017
 *      Author: tungnk
 */

#ifndef QUEUE_H_
#define QUEUE_H_
#include "ltecmd.h"

#define MAX_QUEUE_SIZE 128
#define QUEUE_ACTIVE	0
#define QUEUE_WAIT		1
typedef struct tagQueueControl {
	BYTE nQueueSize;
	WORD nBufferSize;
	BYTE nState;
	BYTE nCurrentPointer;
	BYTE nFreePointer;
	PBYTE pContent;
	PBYTE pContentLength;
} QUEUECONTROL, *PQUEUECONTROL;


typedef struct tagQueueContent {
	WORD nSize;
	PBYTE pData;
} QUEUECONTENT, *PQUEUECONTENT;


PQUEUECONTROL QueueCreate(BYTE nQueueSize, WORD nBufferSize);
void QueueFreeMem(PQUEUECONTROL pQueue);
BYTE QueuePush(void* pSource, WORD nSize, PQUEUECONTROL pQueue);
QUEUECONTENT QueueGetContent(PQUEUECONTROL pQueue);
void QueueFinishProcBuffer(PQUEUECONTROL pQueue);
void QueueSetState(PQUEUECONTROL pQueue, BYTE nState);
BYTE QueueGetState(PQUEUECONTROL pQueue);

#endif /* QUEUE_H_ */
