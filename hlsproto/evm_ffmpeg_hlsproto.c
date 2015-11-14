/*
 * evm_ffmpeg_hlsproto.c
 *	Description:
 *
 *  Created on: Nov 10, 2015
 *      Author: ÕÂÔÆ·É<zhangyf@evmtv.com>
 */
#include "evm_ffmpeg_hlsproto.h"




/*·ÖÎöm3u8ÎÄ¼þ*/
static ret_code_e evm_parse_playlist()
{
	ret_code_e s32Ret = EVM_FAILURE;
	evm_s8 line[128];



	if (strcmp(line, "#EXTM3U"))
	{
		s32Ret = EVM_FAILURE;
		goto fail;
	}




fail:
	return s32Ret;
}


static ret_code_e evm_hls_open(evm_s8 *uri)
{
	ret_code_e s32Ret = EVM_FAILURE;

	if ()
	{

	}


fail:
	return s32Ret;
}



evm_ffmpeg_urlProtocol_t stHLSProtocol = {
		.name = "hls",
		.url_open = evm_hls_open,
};
