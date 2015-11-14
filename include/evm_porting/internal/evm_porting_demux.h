/*
 * evm_porting_demux.h
 * Copyright(C) EnRich DTV Group Co.,Ltd.
 *
 * Description: 
 *
 * Authors: 沈辉<shenhui@evmtv.com>
 */

#ifndef __EVM_PORTING_DEMUX_H__
#define __EVM_PORTING_DEMUX_H__

#include "../../evm_typedef.h"

#define EVM_DMX_INVALID_ID  0xffffffff
#define EVM_DMX_INVALID_PID 0x1fff
#define EVM_DMX_FILTER_MAX_DEPTH 16

typedef struct
{
	evm_u32 u32DmxNum;
}evm_porting_dmx_initOutParam_t;

typedef enum
{
	EVM_DMX_FILTER_STATUS_OK_E,  				//demux filter ok.
	EVM_DMX_FILTER_STATUS_FAILURE_E,  			//demux filter failure, maybe caused by imcomplete section.
	EVM_DMX_FILTER_STATUS_OVERFLOW_E,  			//demux filter buffer overflow, inform application.
	EVM_DMX_FILTER_STATUS_TIMEOUT_E,  			//demux filte timer out.
	EVM_DMX_FILTER_STATUS_CRCERROR_E,  			//demux filte crc error if filter enables crc checking.
} evm_dmx_filterStatus_e;

typedef enum
{
    EVM_DMX_CHANNEL_TYPE_SECTION_E = 0,
    EVM_DMX_CHANNEL_TYPE_TS_E
} evm_dmx_channelType_e;

typedef evm_s32 (*evm_porting_dmx_filter_cb)(evm_u32 u32DmxId, evm_u16 u16Pid, evm_u32 u32FilterId, evm_dmx_filterStatus_e eReason , evm_u8 *pu8Data, evm_u32 u32Size ,evm_u32 u32Private);

typedef evm_s32 (*evm_porting_dmx_channel_cb)(evm_u32 u32DmxId, evm_u16 u16Pid, evm_u32 u32ChannelId, evm_u8 *pu8Data, evm_u32 u32Size ,evm_u32 u32Private);

typedef struct _evm_dmx_channelAttr_t_
{
    evm_dmx_channelType_e eType;
    evm_porting_dmx_channel_cb pcbCallback;
    evm_bool bCRCMode;
    evm_u32 u32Private;
} evm_dmx_channelAttr_t;

typedef struct _evm_dmx_filterAttr_t_
{
    evm_u8 u8arrValue[EVM_DMX_FILTER_MAX_DEPTH];
    evm_u8 u8arrMask[EVM_DMX_FILTER_MAX_DEPTH];
    evm_u32 u32ValueLength;
    evm_u32 u32Timeout;
    evm_porting_dmx_filter_cb pcbCallback;
    evm_u32 u32Private;
} evm_dmx_filterAttr_t;

/*
 * Function: evm_porting_dmx_Init
 * Description: 对demux 模块的初始化,将所有dmx初始化好，输出dmx个数
 * Input: 
 * 				
 * Output: 
 *          pstInitOutParam，返回初始化后的dmx个数，后续上层以索引0、1、2使用dmx。
 *                              dmx与tuner一一对应，即dmx 1 对应tuner 1 ；dmx 0 对应tuner 0...
 *                              底层完成tuner与demux的绑定
 * Return: 0:SUCCESS , other is Fail
 */
ret_code_e evm_porting_dmx_Init(evm_porting_dmx_initOutParam_t *pstInitOutParam);

/*
 * Function: evm_porting_dmx_DeInit
 * Description: 对demux 模块的去初始化
 * Input:
 * 				
 * Output: none
 * Return: 0:SUCCESS , other is Fail
 */
ret_code_e evm_porting_dmx_DeInit(void);

/**
 * Function: evm_porting_dmx_GetNum
 * Description: 获取demux个数
 * Input:
 * 			none
 *
 * Output:
 * 			u32DmxNum 返回demux个数。
 * Return: 0:SUCCESS , other is Fail
 */
ret_code_e evm_porting_dmx_GetNum(evm_u32 *u32DmxNum);

/*
 * Function: evm_porting_dmx_AllocChannel
 * Description: 为pid 分配一个数据通道
 * Input: u32DmxId:指定创建channel的dmx
 *          pid 通道的PID
 * 		ChId:输出的通道 id
 * Output: none
 * Return: 0:SUCCESS , other is Fail
 */
ret_code_e evm_porting_dmx_AllocChannel(evm_u32 u32DmxId, evm_u16 u16Pid, evm_u32 *pu32ChId, evm_dmx_channelAttr_t *pstAttr);

/*
 * Function: evm_porting_dmx_AllocFilter
 * Description: 在channelid通道上申请一个过滤器
 * Input:               u32DmxId:指定创建filter的dmx
 *				ChannelId:所要申请过滤器的通道ID
 * 				FilterVal:过滤器参数(不包括section len字段)
 * 				FilterMask：匹配参数()
 *				FilterLen：过滤器参数长度
 *				Timeout：超时时间
 *				Callback：过滤器回调，返回数据，及状态
 *				Priv：私有数据
 *				FilterId:返回的过滤器ID
 * Output: none
 * Return: 0:SUCCESS , other is Fail
 */
ret_code_e evm_porting_dmx_AllocFilter(evm_u32 u32DmxId, evm_u32 u32ChannelId, evm_u32 *pu32FilterId, evm_dmx_filterAttr_t *pstAttr);

/*
 * Function: evm_porting_dmx_FreeFilter
 * Description: 释放一个过滤器
 * Input:               u32DmxId:指定释放filter的dmx
 *				ChannelId  ： 通道ID
 *				FilterId：要释放的过滤器ID
 * Output: none
 * Return: 0:SUCCESS , Other is Fail
 */
ret_code_e evm_porting_dmx_FreeFilter(evm_u32 u32DmxId, evm_u32 u32ChannelId , evm_u32 u32FilterId);

/*
 * Function: evm_porting_dmx_FreeChannel
 * Description: 释放一个通道
 * Input:               u32DmxId:指定释放channel的dmx
 *				ChannelId  要释放的ID
 * Output: none
 * Return: 0:SUCCESS , other is Fail
 */
ret_code_e evm_porting_dmx_FreeChannel(evm_u32 u32DmxId, evm_u32 u32ChannelId);

/*
 * Function: evm_porting_dmx_AllocDescramble
 * Description: 申请一个解扰通道
 * Input:               u32DmxId:指定创建解扰器的dmx
 *				DescrambleId 返回的解扰器通道
 * Output: none
 * Return: 0:SUCCESS , other is Fail
 */
ret_code_e evm_porting_dmx_AllocDescramble(evm_u32 u32DmxId, evm_u32 *pu32DescrambleId);

/*
 * Function: evm_porting_dmx_AllocDescramble
 * Description: 绑定解扰器到指定通道
 * Input:               u32DmxId:指定绑定解扰器的channel对应的dmx
 *				DescrambleId 返回的解扰器通道
 * Output: none
 * Return: 0:SUCCESS , other is Fail
 */
ret_code_e evm_porting_dmx_DescrambleLinkChannel(evm_u32 u32DmxId, evm_u32 u32DescrambleId, evm_u32 u32ChannelId);

/*
 * Function: evm_porting_dmx_AllocDescramble
 * Description: 解绑定指定通道的解扰器
 * Input:               u32DmxId:指定解绑定解扰器的channel对应的dmx
 *				DescrambleId 返回的解扰器通道
 * Output: none
 * Return: 0:SUCCESS , other is Fail
 */
ret_code_e evm_porting_dmx_DescrambleUnbindChannel(evm_u32 u32DmxId, evm_u32 u32DescrambleId, evm_u32 u32ChannelId);

/*
 * Function: evm_porting_dmx_FreeDescramble
 * Description: 释放一个解扰器通道
 * Input:               u32DmxId:指定释放解扰器的dmx
 *				DescrambleId  要释放的解扰器ID
 * Output: none
 * Return: 0:SUCCESS , other is Fail
 */
ret_code_e evm_porting_dmx_FreeDescramble(evm_u32 u32DmxId, evm_u32 u32DescrambleId);

/*
 * Function: evm_porting_dmx_SetOddKey
 * Description: 设置指定dmx的奇秘钥
 * Input:               u32DmxId:指定设置秘钥的dmx
 *				DescrambleId  要释放的解扰器ID
 *                          pu8OddKey:秘钥值
 *                          u8Len:秘钥长度
 * Output: none
 * Return: 0:SUCCESS , other is Fail
 */
ret_code_e evm_porting_dmx_SetOddKey(evm_u32 u32DmxId, evm_u32 u32DescrambleId, const evm_u8 *pu8OddKey, evm_u8 u8Len);

/*
 * Function: evm_porting_dmx_SetEvenKey
 * Description: 设置指定dmx的偶秘钥
 * Input:               u32DmxId:指定设置秘钥的dmx
 *				DescrambleId  要释放的解扰器ID
 *                          pu8OddKey:秘钥值
 *                          u8Len:秘钥长度
 * Output: none
 * Return: 0:SUCCESS , other is Fail
 */
ret_code_e evm_porting_dmx_SetEvenKey(evm_u32 u32DmxId, evm_u32 u32DescrambleId, const evm_u8 *pu8EvenKey, evm_u8 u8Len);


/*
 * Function: evm_porting_dmx_GetChannelByPid
 * Description: 通过PID获取所申请的通道ID
 * Input:  u32DmxId:指定在哪个dmx上查找channel
 *		 u32Pid: 通道的PID
 * Output: u32ChannelId
 *             取到的通道ID
 * Return: 0:SUCCESS , other is Fail
 */
 ret_code_e evm_porting_dmx_GetChannelByPid(evm_u32 u32DmxId, evm_u32 u32Pid , evm_u32 * u32ChannelId);

/*
 * Function: evm_porting_dmx_GetVideoChannel
 * Description: 通过PID获取视频通道ID
 * Input:  u32DmxId: 在指定的dmx上获取视频通道
 *		 u32Pid:通道的PID
 * Output: u32ChannelId
 *             取到的通道ID
 * Return: 0:SUCCESS , other is Fail
 */
ret_code_e evm_porting_dmx_GetVideoChannel(evm_u32 u32DmxId, evm_u32 u32Pid , evm_u32 * u32ChannelId);


/*
 * Function: evm_porting_dmx_GetAudioChannel
 * Description: 通过PID获取音频通道ID
 * Input:  u32DmxId: 在指定的dmx上获取音频通道
 *		 u32Pid: 通道的PID
 * Output: u32ChannelId
 *             取到的通道ID
 * Return: 0:SUCCESS , other is Fail
 */
 ret_code_e evm_porting_dmx_GetAudioChannel(evm_u32 u32DmxId, evm_u32 u32Pid , evm_u32 * u32ChannelId);


#endif /* EVM_PORTING_DEMUX_H_ */
