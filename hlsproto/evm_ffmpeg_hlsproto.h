/*
 * evm_ffmpeg_hlsproto.h
 *	Description:
 *
 *  Created on: Nov 10, 2015
 *      Author: ’¬‘∆∑…<zhangyf@evmtv.com>
 */

#ifndef EVM_FFMPEG_HLSPROTO_H_
#define EVM_FFMPEG_HLSPROTO_H_




/* ‰»Î–≠“È*/
typedef struct _evm_ffmpeg_urlProtocol_t_
{
	evm_s8 *name;
	ret_code_e (*url_open)(evm_s8 *uri);

}evm_ffmpeg_urlProtocol_t;

#endif /* EVM_FFMPEG_HLSPROTO_H_ */
