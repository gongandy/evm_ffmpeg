/*
 * evm_porting_smc.h
 * Copyright(C) EnRich DTV Group Co.,Ltd.
 *
 * Description: 与智能卡相关的操作接口
 *
 * Authors: 研发三部
 */

#ifndef __EVM_PORTING_SMC_H__
#define __EVM_PORTING_SMC_H__

#include "../../evm_typedef.h"


typedef enum _evm_smc_CardStatus_e
{
    EVM_MODULE_SMC_STATUS_OUT,
    EVM_MODULE_SMC_STATUS_IN,
    EVM_MODULE_SMC_STATUS_UNKNOW
}evm_smc_CardStatus_e;

typedef enum
{
    EVM_SMC_TRANS_READ,
    EVM_SMC_TRANS_WRITE
}evm_smc_TransType_e;

typedef void (*evm_SmcCallback)(evm_u32 Param);

/*
 * Function: evm_porting_smc_Init
 * Description: 对智能卡模块的初始化
 * Input: 
 *           SmcDev: 返回的智能卡设备号
 * Output: none
 * Return: 0:SUCCESS , other is Fail
 */
evm_s32 evm_porting_smc_Init(evm_u32 *SmcDev );

/*
 * Function: evm_porting_smc_DeInit
 * Description: 对智能卡模块的去初始化
 * Input: 
 *           SmcDev: 返回的智能卡设备号
 * Output: none
 * Return: 0:SUCCESS , other is Fail
 */
evm_s32 evm_porting_smc_DeInit(evm_u32 SmcDev );

/*
 * Function: evm_porting_smc_RegisterCb
 * Description: 注册一个回调，通知拨插卡事件
 * Input: 
 *           SmcDev: 智能卡设备号
 * 		Callback:回调函数指针
 * Output: none
 * Return: 0:SUCCESS , other is Fail
 */
evm_s32 evm_porting_smc_RegisterCb(evm_u32 SmcDev , evm_SmcCallback Callback);

/*
 * Function: evm_porting_smc_GetCardStatus
 * Description: 获取卡状态
 * Input: 
 *           SmcDev: 智能卡设备号
 * 		Status:0为未插卡，1为已插卡
 * Output: none
 * Return: 0:SUCCESS , other is Fail
 */
evm_s32 evm_porting_smc_GetCardStatus(evm_u32 SmcDev , evm_smc_CardStatus_e *Status);

/*
 * Function: evm_porting_smc_SmcReset
 * Description: 获取卡状态
 * Input: 
 *           SmcDev: 智能卡设备号
 * 		Atr:返回的ATR
 *           AtrSize:ATR长度
 *           Offset:
 * Output: none
 * Return: 0:SUCCESS , other is Fail
 */
evm_s32 evm_porting_smc_Reset(evm_u32 SmcDev , evm_u8 Atr[] , evm_u32 *AtrSize , evm_u32 *Offset);

/*
 * Function: evm_porting_smc_Transfer
 * Description: 与卡通讯接口
 * Input: 
 *           SmcDev: 智能卡设备号
 * 		Command:与卡通讯的指令
 *           NumToWrite:对卡写入的数量
 *           Response:应答数据
 *           NumToRead:应答数据长度
 *           ActualSize:实际读取数据的大小
 * Output: none
 * Return: 0:SUCCESS , other is Fail
 */
evm_s32 evm_porting_smc_Transfer(evm_u32 SmcDev , evm_u8 *Command, evm_s16 NumToWrite, evm_u8 *Response, evm_s16 NumToRead, evm_s16 *ActualSize);

/*
 * Function: evm_porting_smc_SmcRawRead
 * Description: 从卡中读取数据
 * Input: 
 *           SmcDev: 智能卡设备号
 * 		Buffer:读数据指令
 *           Size:读取数据长度
 *           Actlen:存放读取出来的数据
 * Output: none
 * Return: 0:SUCCESS , other is Fail
 */
evm_s32 evm_porting_smc_SmcRead(evm_u32 SmcDev , evm_u8 *Buffer, evm_u16 Size, evm_u16 *Actlen);

/*
 * Function: evm_porting_smc_SmcRawWrite
 * Description: 从卡中写入数据
 * Input: 
 *           SmcDev: 智能卡设备号
 * 		Buffer:存放写入的数据及指令
 *           Size:数据长度
 *           Actlen:应答数据
 * Output: none
 * Return: 0:SUCCESS , other is Fail
 */
 evm_s32 evm_porting_smc_SmcWrite(evm_u32 SmcDev , evm_u8 *Buffer, evm_s16 Size, evm_s16 *Actlen);

/*
 * Function: evm_porting_smc_SetTransTimeOut
 * Description: 设置卡传输时的超时时间。
 * Input: 
 *           SmcDev: 智能卡设备号
 * 		Type :传输类型
 *           TimeoutMs:超时时间
 * Output: none
 * Return: 0:SUCCESS , other is Fail
 */
 evm_s32 evm_porting_smc_SetTransTimeOut(evm_u32 SmcDev ,evm_smc_TransType_e Type , evm_u32 TimeoutMs);




#endif

