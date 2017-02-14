/*
 * ltecmd.h
 *
 *  Created on: Feb 14, 2017
 *      Author: tungnk
 */

#ifndef LTECMD_H_
#define LTECMD_H_
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

#endif /* LTECMD_H_ */
