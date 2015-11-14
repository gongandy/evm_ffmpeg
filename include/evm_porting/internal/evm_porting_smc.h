/*
 * evm_porting_smc.h
 * Copyright(C) EnRich DTV Group Co.,Ltd.
 *
 * Description: �����ܿ���صĲ����ӿ�
 *
 * Authors: �з�����
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
 * Description: �����ܿ�ģ��ĳ�ʼ��
 * Input: 
 *           SmcDev: ���ص����ܿ��豸��
 * Output: none
 * Return: 0:SUCCESS , other is Fail
 */
evm_s32 evm_porting_smc_Init(evm_u32 *SmcDev );

/*
 * Function: evm_porting_smc_DeInit
 * Description: �����ܿ�ģ���ȥ��ʼ��
 * Input: 
 *           SmcDev: ���ص����ܿ��豸��
 * Output: none
 * Return: 0:SUCCESS , other is Fail
 */
evm_s32 evm_porting_smc_DeInit(evm_u32 SmcDev );

/*
 * Function: evm_porting_smc_RegisterCb
 * Description: ע��һ���ص���֪ͨ���忨�¼�
 * Input: 
 *           SmcDev: ���ܿ��豸��
 * 		Callback:�ص�����ָ��
 * Output: none
 * Return: 0:SUCCESS , other is Fail
 */
evm_s32 evm_porting_smc_RegisterCb(evm_u32 SmcDev , evm_SmcCallback Callback);

/*
 * Function: evm_porting_smc_GetCardStatus
 * Description: ��ȡ��״̬
 * Input: 
 *           SmcDev: ���ܿ��豸��
 * 		Status:0Ϊδ�忨��1Ϊ�Ѳ忨
 * Output: none
 * Return: 0:SUCCESS , other is Fail
 */
evm_s32 evm_porting_smc_GetCardStatus(evm_u32 SmcDev , evm_smc_CardStatus_e *Status);

/*
 * Function: evm_porting_smc_SmcReset
 * Description: ��ȡ��״̬
 * Input: 
 *           SmcDev: ���ܿ��豸��
 * 		Atr:���ص�ATR
 *           AtrSize:ATR����
 *           Offset:
 * Output: none
 * Return: 0:SUCCESS , other is Fail
 */
evm_s32 evm_porting_smc_Reset(evm_u32 SmcDev , evm_u8 Atr[] , evm_u32 *AtrSize , evm_u32 *Offset);

/*
 * Function: evm_porting_smc_Transfer
 * Description: �뿨ͨѶ�ӿ�
 * Input: 
 *           SmcDev: ���ܿ��豸��
 * 		Command:�뿨ͨѶ��ָ��
 *           NumToWrite:�Կ�д�������
 *           Response:Ӧ������
 *           NumToRead:Ӧ�����ݳ���
 *           ActualSize:ʵ�ʶ�ȡ���ݵĴ�С
 * Output: none
 * Return: 0:SUCCESS , other is Fail
 */
evm_s32 evm_porting_smc_Transfer(evm_u32 SmcDev , evm_u8 *Command, evm_s16 NumToWrite, evm_u8 *Response, evm_s16 NumToRead, evm_s16 *ActualSize);

/*
 * Function: evm_porting_smc_SmcRawRead
 * Description: �ӿ��ж�ȡ����
 * Input: 
 *           SmcDev: ���ܿ��豸��
 * 		Buffer:������ָ��
 *           Size:��ȡ���ݳ���
 *           Actlen:��Ŷ�ȡ����������
 * Output: none
 * Return: 0:SUCCESS , other is Fail
 */
evm_s32 evm_porting_smc_SmcRead(evm_u32 SmcDev , evm_u8 *Buffer, evm_u16 Size, evm_u16 *Actlen);

/*
 * Function: evm_porting_smc_SmcRawWrite
 * Description: �ӿ���д������
 * Input: 
 *           SmcDev: ���ܿ��豸��
 * 		Buffer:���д������ݼ�ָ��
 *           Size:���ݳ���
 *           Actlen:Ӧ������
 * Output: none
 * Return: 0:SUCCESS , other is Fail
 */
 evm_s32 evm_porting_smc_SmcWrite(evm_u32 SmcDev , evm_u8 *Buffer, evm_s16 Size, evm_s16 *Actlen);

/*
 * Function: evm_porting_smc_SetTransTimeOut
 * Description: ���ÿ�����ʱ�ĳ�ʱʱ�䡣
 * Input: 
 *           SmcDev: ���ܿ��豸��
 * 		Type :��������
 *           TimeoutMs:��ʱʱ��
 * Output: none
 * Return: 0:SUCCESS , other is Fail
 */
 evm_s32 evm_porting_smc_SetTransTimeOut(evm_u32 SmcDev ,evm_smc_TransType_e Type , evm_u32 TimeoutMs);




#endif

