/*
 * queue.c
 *
 *  Created on: Feb 16, 2017
 *      Author: tungnk
 */
#include "queue.h"
#include "stdio.h"
#include "stdlib.h"
#include "ltecmd.h"

PQUEUECONTROL QueueCreate(BYTE nQueueSize, WORD nBufferSize)
{
	PBYTE pQueueContent;
	PBYTE pBufferLength;
	BYTE nIndex;
	PQUEUECONTROL pQueue;
	if (nQueueSize <= 1) return NULL;
	pQueueContent = (PBYTE)malloc(nQueueSize * nBufferSize);
	if (pQueueContent == NULL) return NULL;
	pBufferLength = (PBYTE)malloc(nQueueSize);
	for (nIndex = 0; nIndex < nQueueSize; nIndex++)
		pBufferLength[nIndex] = 0;
	if (pBufferLength == NULL)
	{
		free(pQueueContent);
		return NULL;
	}
	pQueue = (PQUEUECONTROL)malloc(sizeof(QUEUECONTROL));
	if (pQueue == NULL)
	{
		free(pQueueContent);
		free(pBufferLength);
		return NULL;
	}
	pQueue->nBufferSize = nBufferSize;
	pQueue->nQueueSize = nQueueSize;
	pQueue->nCurrentPointer = nQueueSize - 1;
	pQueue->nFreePointer = 0;
	pQueue->nState = QUEUE_ACTIVE;
	pQueue->pContent = pQueueContent;
	pQueue->pContentLength = pBufferLength;
	return pQueue;
}

void QueueFreeMem(PQUEUECONTROL pQueue)
{
	if (pQueue == NULL) return;
	free((void *)(pQueue->pContent));
	free((void *)(pQueue->pContentLength));
	free((void *)pQueue);
}

BYTE QueuePush(void* pSource, WORD nSize, PQUEUECONTROL pQueue)
{
	BYTE nIndex;
	PBYTE pDataContent;
	if (pQueue == NULL) return 1;
	if (pQueue->nFreePointer == pQueue->nCurrentPointer)
	{
		printf("queue is full\n");
		return 1;
	}
	if (nSize > pQueue->nBufferSize)
	{
		printf("input data is too large");
		return 1;
	}
	pQueue->pContentLength[pQueue->nFreePointer] = nSize;
	pDataContent = pQueue->pContent + (pQueue->nFreePointer * pQueue->nBufferSize);
	for (nIndex = 0; nIndex < nSize; nIndex++)
		*(pDataContent + nIndex) = *((PBYTE)(pSource + nIndex));
	pQueue->nFreePointer++;
	if (pQueue->nFreePointer == pQueue->nQueueSize)
		pQueue->nFreePointer = 0;
	return 0;
}

QUEUECONTENT QueueGetContent(PQUEUECONTROL pQueue)
{
	QUEUECONTENT stContent;
	stContent.nSize = 0;
	stContent.pData = NULL;
	if (pQueue == NULL) return stContent;
	BYTE nPosition = pQueue->nCurrentPointer + 1;
	if (nPosition == pQueue->nQueueSize) nPosition = 0;
	if (nPosition != pQueue->nFreePointer)
	{
		stContent.nSize = (pQueue->pContentLength)[nPosition];
		stContent.pData = (PBYTE)(pQueue->pContent + (pQueue->nBufferSize * nPosition));
	}
	return stContent;
}

void QueueFinishProcBuffer(PQUEUECONTROL pQueue)
{
	pQueue->nCurrentPointer++;
	if (pQueue->nCurrentPointer == pQueue->nQueueSize)
		pQueue->nCurrentPointer = 0;
}

void QueueSetState(PQUEUECONTROL pQueue, BYTE nState)
{
	if (pQueue != NULL)
	{
		pQueue->nState = nState;
	}
}

BYTE QueueGetState(PQUEUECONTROL pQueue)
{
	return pQueue->nState;
}
