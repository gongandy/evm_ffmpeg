/*
 * evm_ffmpeg_debug.h
 *	Description:
 *
 *  Created on: Nov 9, 2015
 *      Author: ÕÂÔÆ·É<zhangyf@evmtv.com>
 */

#ifndef EVM_FFMPEG_DEBUG_H_
#define EVM_FFMPEG_DEBUG_H_

#include "include/evm_porting/internal/evm_porting_os.h"

#define evm_ffmpeg_CreateThread 	evm_porting_OsThreadCreate
#define evm_ffmpeg_ErrorLog 		EVM_ERROR_PRINT
#define evm_ffmpeg_Calloc			evm_porting_OsCalloc
#define evm_ffmpeg_Free				evm_porting_OsFree
#define evm_ffmpeg_SemWait			evm_porting_OsSemWait
#define evm_ffmpeg_SemPost 			evm_porting_OsSemPost
#define evm_ffmpeg_CreateSem		evm_porting_OsCreateSem
#define evm_ffmpeg_CreateMutex		evm_porting_OsCreateMutex
#define evm_ffmpeg_MutexLock		evm_porting_OsMutexLock
#endif /* EVM_FFMPEG_DEBUG_H_ */
