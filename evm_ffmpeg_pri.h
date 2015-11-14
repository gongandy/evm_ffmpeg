/*
 * evm_ffmpeg_pri.h
 *	Description:
 *
 *  Created on: Nov 7, 2015
 *      Author: 章云飞<zhangyf@evmtv.com>
 */

#ifndef EVM_FFMPEG_PRI_H_
#define EVM_FFMPEG_PRI_H_

#include "include/evm_typedef.h"

typedef struct _evm_ffmpeg_initParam_
{

}evm_ffmpeg_initParam_t;




typedef enum _evm_ffmpeg_urlType_e_
{
	EVM_FFMPEG_URLTYPE_FILE = 0,
	EVM_FFMPEG_URLTYPE_RAM,
	EVM_FFMPEG_URLTYPE_UDP,
	EVM_FFMPEG_URLTYPE_HTTP,
}evm_ffmpeg_urlType_e;

typedef struct _evm_ffmpeg_inputParam_t_
{
	evm_ffmpeg_urlType_e eType;
	evm_s8 *pInputUrl;
}evm_ffmpeg_inputParam_t;




typedef struct _evm_ffmpeg_filePath_t_
{
	evm_bool bpath;
	evm_s8 *pfilePath;
}evm_ffmpeg_filePath_t;

/*设计ffmpeg-convert线程*/
typedef struct _evm_ffmpeg_instance_t_
{
	evm_mutexID mutex;
	evm_semID eventSem;

	evm_u32 (*evm_read_packet)(void *opaque, evm_u8 *buf, evm_u32 buf_size);
	evm_u32 (*evm_write_packet)(void *opaque, evm_u8 *buf, evm_u32 buf_size);

	evm_ffmpeg_filePath_t stInputFilePath;
	evm_s8 *pInputMemory;
	evm_s8 *pOutputMemory;
}evm_ffmpeg_instance_t;




#endif /* EVM_FFMPEG_PRI_H_ */
