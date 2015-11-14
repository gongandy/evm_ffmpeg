/*
 * evm_porting_demux.h
 * Copyright(C) EnRich DTV Group Co.,Ltd.
 *
 * Description: 
 *
 * Authors: ���<shenhui@evmtv.com>
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
 * Description: ��demux ģ��ĳ�ʼ��,������dmx��ʼ���ã����dmx����
 * Input: 
 * 				
 * Output: 
 *          pstInitOutParam�����س�ʼ�����dmx�����������ϲ�������0��1��2ʹ��dmx��
 *                              dmx��tunerһһ��Ӧ����dmx 1 ��Ӧtuner 1 ��dmx 0 ��Ӧtuner 0...
 *                              �ײ����tuner��demux�İ�
 * Return: 0:SUCCESS , other is Fail
 */
ret_code_e evm_porting_dmx_Init(evm_porting_dmx_initOutParam_t *pstInitOutParam);

/*
 * Function: evm_porting_dmx_DeInit
 * Description: ��demux ģ���ȥ��ʼ��
 * Input:
 * 				
 * Output: none
 * Return: 0:SUCCESS , other is Fail
 */
ret_code_e evm_porting_dmx_DeInit(void);

/**
 * Function: evm_porting_dmx_GetNum
 * Description: ��ȡdemux����
 * Input:
 * 			none
 *
 * Output:
 * 			u32DmxNum ����demux������
 * Return: 0:SUCCESS , other is Fail
 */
ret_code_e evm_porting_dmx_GetNum(evm_u32 *u32DmxNum);

/*
 * Function: evm_porting_dmx_AllocChannel
 * Description: Ϊpid ����һ������ͨ��
 * Input: u32DmxId:ָ������channel��dmx
 *          pid ͨ����PID
 * 		ChId:�����ͨ�� id
 * Output: none
 * Return: 0:SUCCESS , other is Fail
 */
ret_code_e evm_porting_dmx_AllocChannel(evm_u32 u32DmxId, evm_u16 u16Pid, evm_u32 *pu32ChId, evm_dmx_channelAttr_t *pstAttr);

/*
 * Function: evm_porting_dmx_AllocFilter
 * Description: ��channelidͨ��������һ��������
 * Input:               u32DmxId:ָ������filter��dmx
 *				ChannelId:��Ҫ�����������ͨ��ID
 * 				FilterVal:����������(������section len�ֶ�)
 * 				FilterMask��ƥ�����()
 *				FilterLen����������������
 *				Timeout����ʱʱ��
 *				Callback���������ص����������ݣ���״̬
 *				Priv��˽������
 *				FilterId:���صĹ�����ID
 * Output: none
 * Return: 0:SUCCESS , other is Fail
 */
ret_code_e evm_porting_dmx_AllocFilter(evm_u32 u32DmxId, evm_u32 u32ChannelId, evm_u32 *pu32FilterId, evm_dmx_filterAttr_t *pstAttr);

/*
 * Function: evm_porting_dmx_FreeFilter
 * Description: �ͷ�һ��������
 * Input:               u32DmxId:ָ���ͷ�filter��dmx
 *				ChannelId  �� ͨ��ID
 *				FilterId��Ҫ�ͷŵĹ�����ID
 * Output: none
 * Return: 0:SUCCESS , Other is Fail
 */
ret_code_e evm_porting_dmx_FreeFilter(evm_u32 u32DmxId, evm_u32 u32ChannelId , evm_u32 u32FilterId);

/*
 * Function: evm_porting_dmx_FreeChannel
 * Description: �ͷ�һ��ͨ��
 * Input:               u32DmxId:ָ���ͷ�channel��dmx
 *				ChannelId  Ҫ�ͷŵ�ID
 * Output: none
 * Return: 0:SUCCESS , other is Fail
 */
ret_code_e evm_porting_dmx_FreeChannel(evm_u32 u32DmxId, evm_u32 u32ChannelId);

/*
 * Function: evm_porting_dmx_AllocDescramble
 * Description: ����һ������ͨ��
 * Input:               u32DmxId:ָ��������������dmx
 *				DescrambleId ���صĽ�����ͨ��
 * Output: none
 * Return: 0:SUCCESS , other is Fail
 */
ret_code_e evm_porting_dmx_AllocDescramble(evm_u32 u32DmxId, evm_u32 *pu32DescrambleId);

/*
 * Function: evm_porting_dmx_AllocDescramble
 * Description: �󶨽�������ָ��ͨ��
 * Input:               u32DmxId:ָ���󶨽�������channel��Ӧ��dmx
 *				DescrambleId ���صĽ�����ͨ��
 * Output: none
 * Return: 0:SUCCESS , other is Fail
 */
ret_code_e evm_porting_dmx_DescrambleLinkChannel(evm_u32 u32DmxId, evm_u32 u32DescrambleId, evm_u32 u32ChannelId);

/*
 * Function: evm_porting_dmx_AllocDescramble
 * Description: ���ָ��ͨ���Ľ�����
 * Input:               u32DmxId:ָ����󶨽�������channel��Ӧ��dmx
 *				DescrambleId ���صĽ�����ͨ��
 * Output: none
 * Return: 0:SUCCESS , other is Fail
 */
ret_code_e evm_porting_dmx_DescrambleUnbindChannel(evm_u32 u32DmxId, evm_u32 u32DescrambleId, evm_u32 u32ChannelId);

/*
 * Function: evm_porting_dmx_FreeDescramble
 * Description: �ͷ�һ��������ͨ��
 * Input:               u32DmxId:ָ���ͷŽ�������dmx
 *				DescrambleId  Ҫ�ͷŵĽ�����ID
 * Output: none
 * Return: 0:SUCCESS , other is Fail
 */
ret_code_e evm_porting_dmx_FreeDescramble(evm_u32 u32DmxId, evm_u32 u32DescrambleId);

/*
 * Function: evm_porting_dmx_SetOddKey
 * Description: ����ָ��dmx������Կ
 * Input:               u32DmxId:ָ��������Կ��dmx
 *				DescrambleId  Ҫ�ͷŵĽ�����ID
 *                          pu8OddKey:��Կֵ
 *                          u8Len:��Կ����
 * Output: none
 * Return: 0:SUCCESS , other is Fail
 */
ret_code_e evm_porting_dmx_SetOddKey(evm_u32 u32DmxId, evm_u32 u32DescrambleId, const evm_u8 *pu8OddKey, evm_u8 u8Len);

/*
 * Function: evm_porting_dmx_SetEvenKey
 * Description: ����ָ��dmx��ż��Կ
 * Input:               u32DmxId:ָ��������Կ��dmx
 *				DescrambleId  Ҫ�ͷŵĽ�����ID
 *                          pu8OddKey:��Կֵ
 *                          u8Len:��Կ����
 * Output: none
 * Return: 0:SUCCESS , other is Fail
 */
ret_code_e evm_porting_dmx_SetEvenKey(evm_u32 u32DmxId, evm_u32 u32DescrambleId, const evm_u8 *pu8EvenKey, evm_u8 u8Len);


/*
 * Function: evm_porting_dmx_GetChannelByPid
 * Description: ͨ��PID��ȡ�������ͨ��ID
 * Input:  u32DmxId:ָ�����ĸ�dmx�ϲ���channel
 *		 u32Pid: ͨ����PID
 * Output: u32ChannelId
 *             ȡ����ͨ��ID
 * Return: 0:SUCCESS , other is Fail
 */
 ret_code_e evm_porting_dmx_GetChannelByPid(evm_u32 u32DmxId, evm_u32 u32Pid , evm_u32 * u32ChannelId);

/*
 * Function: evm_porting_dmx_GetVideoChannel
 * Description: ͨ��PID��ȡ��Ƶͨ��ID
 * Input:  u32DmxId: ��ָ����dmx�ϻ�ȡ��Ƶͨ��
 *		 u32Pid:ͨ����PID
 * Output: u32ChannelId
 *             ȡ����ͨ��ID
 * Return: 0:SUCCESS , other is Fail
 */
ret_code_e evm_porting_dmx_GetVideoChannel(evm_u32 u32DmxId, evm_u32 u32Pid , evm_u32 * u32ChannelId);


/*
 * Function: evm_porting_dmx_GetAudioChannel
 * Description: ͨ��PID��ȡ��Ƶͨ��ID
 * Input:  u32DmxId: ��ָ����dmx�ϻ�ȡ��Ƶͨ��
 *		 u32Pid: ͨ����PID
 * Output: u32ChannelId
 *             ȡ����ͨ��ID
 * Return: 0:SUCCESS , other is Fail
 */
 ret_code_e evm_porting_dmx_GetAudioChannel(evm_u32 u32DmxId, evm_u32 u32Pid , evm_u32 * u32ChannelId);


#endif /* EVM_PORTING_DEMUX_H_ */
