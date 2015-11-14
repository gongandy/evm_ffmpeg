/*
 * evm_ffmpeg.c
 *	Description:
 *
 *  Created on: Nov 7, 2015
 *      Author: 章云飞<zhangyf@evmtv.com>
 */

#include "evm_ffmpeg_pri.h"

#define EVM_FFMPEG_INPUT_MEMORY 	1024 *1024

static evm_ffmpeg_instance_t *pstFpInstance = EVM_NULL;


ret_code_e evm_ffmpeg_Init(evm_ffmpeg_initParam_t *initParam)
{
	ret_code_e eRet = EVM_FAILURE;

	if (EVM_NULL != pstFpInstance)
	{
		evm_ffmpeg_ErrorLog("[evm_ffmpeg_Init] pstFpInstance is already.\n");
		goto end_0;
	}


	/*初始化*/
	pstFpInstance = evm_ffmpeg_Calloc(1, sizeof(evm_ffmpeg_instance_t));
	if (EVM_NULL == pstFpInstance) {
		evm_ffmpeg_ErrorLog("[evm_ffmpeg_Init] allocate memory of Fp instance error\n");
		goto end_0;
	}

	eRet = evm_ffmpeg_CreateSem(&pstFpInstance->eventSem, 0);
	if (EVM_SUCCESS != eRet)
	{
		evm_ffmpeg_ErrorLog("");
		goto end_0;
	}

	eRet = evm_ffmpeg_CreateMutex(&pstFpInstance->mutex);
	if (EVM_SUCCESS != eRet)
	{
		evm_ffmpeg_ErrorLog("");
		goto end_0;
	}

	pstFpInstance->stInputFilePath.bpath = EVM_FALSE;
	pstFpInstance->stInputFilePath.pfilePath = EVM_NULL;
	pstFpInstance->pInputMemory = evm_ffmpeg_Calloc(1, EVM_FFMPEG_INPUT_MEMORY);
	if (EVM_NULL == pstFpInstance->pInputMemory)
	{
		evm_ffmpeg_ErrorLog("[evm_ffmpeg_Init] allocate memory of input memory error\n");
		goto end_1;
	}


	eRet = evm_ffmpeg_CreatConvertTask(pstFpInstance);
	if (EVM_SUCCESS != eRet)
	{
		evm_ffmpeg_ErrorLog("[evm_ffmpeg_Init] evm_ffmpeg_CreatConvertTask failed\n");
		goto end_2;
	}

end_2:
	evm_ffmpeg_Free(pstFpInstance->pInputMemory);

end_1:
	evm_ffmpeg_Free(pstFpInstance);

end_0:
	return	eRet;
}

ret_code_e evm_ffmpeg_StartConvert(evm_ffmpeg_inputParam_t *inParam)
{
	if (!pstFpInstance)
	{
		evm_ffmpeg_ErrorLog("[evm_ffmpeg_Convert] pstFpInstance is null.\n");

	}

	if (!inParam)
	{
		evm_ffmpeg_ErrorLog("[evm_ffmpeg_Convert] input param is null.\n");

	}

	//FIXME 输入是否需要设计链表
	switch(inParam->eType)
	{
		case EVM_FFMPEG_URLTYPE_FILE:
			evm_ffmpeg_SemPost(pstFpInstance->eventSem);
			pstFpInstance->stInputFilePath.pfilePath = inParam->pInputUrl;
			break;
		case EVM_FFMPEG_URLTYPE_RAM:

			break;
		case EVM_FFMPEG_URLTYPE_UDP:

			break;
		case EVM_FFMPEG_URLTYPE_HTTP:
			//FIXME 以流媒体HLS方式接收数据，设计适配器

			break;
		default:
			evm_ffmpeg_ErrorLog("");
			break;
	}


	return EVM_SUCCESS;
}

ret_code_e evm_ffmpeg_Play(evm_handle hFp)
{
	evm_s32 s32Ret = EVM_FAILURE;

	return s32Ret;
}

ret_code_e evm_ffmpeg_Stop(evm_handle hFp)
{
	evm_s32 s32Ret = EVM_FAILURE;

	return s32Ret;
}

ret_code_e evm_ffmpeg_GetInformationOfTS(evm_handle hFp)
{
	evm_s32 s32Ret = EVM_FAILURE;

	return s32Ret;
}

