/*
 * evm_porting_sto.h
 * Copyright(C) EnRich DTV Group Co.,Ltd.
 *
 * Description: ��FLASH�洢��ؽӿ�
 *
 * Authors: �з�����
 */

#ifndef __EVM_PORTING_STO_H__
#define __EVM_PORTING_STO_H__

#include "../../evm_typedef.h"

typedef enum 
{
    EVM_SPI_FLASH_PARTITION_MBOOT       = 0,
    EVM_SPI_FLASH_PARTITION_STBID,
    EVM_SPI_FLASH_PARTITION_LOADER,
    EVM_SPI_FLASH_PARTITION_LOADERBK,
    EVM_SPI_FLASH_PARTITION_LOADERDB,
    EVM_SPI_FLASH_PARTITION_KL,
    EVM_SPI_FLASH_PARTITION_RFS,
    EVM_SPI_FLASH_PARTITION_APP,
    EVM_SPI_FLASH_PARTITION_USERDATA,
    EVM_SPI_FLASH_PARTITION_NUM
}EVM_FLASH_PARTITION_E;


typedef struct {
    evm_bool partitonSupport; 				// If this type of partition support.
    evm_u32 startAddr;  					// Start address of sepecify partition;
    evm_u32 partitionSize; 					// Specify partition size;
    evm_u32 StoDevice;
}EVM_FlashPartitionInfo_T;

/*
 * Function: evm_porting_sto_FlashInit
 * Description: ��flash�ĳ�ʼ��
 * Input: 
 *           StoDev: ����FLASH�豸���
 * 		
 * Output: none
 * Return: 0:SUCCESS , other is Fail
 */
ret_code_e evm_porting_sto_FlashInit(evm_u32 *StoDev);

/*
 * Function: evm_porting_sto_ReadFlash
 * Description: ��FLASH�ж�ȡ����
 * Input: 
 *           StoDev: FLASH�豸��
 * 		Addr:FLASH��ַ
 *           DataBuf:��ȡ���ݴ�ŵ�ַ
 *           Size: ��ȡ����
 * Output: none
 * Return: 0:SUCCESS , other is Fail
 */
ret_code_e evm_porting_sto_ReadFlash(evm_u32 StoDev, evm_u32 Addr , evm_u8 *DataBuf , evm_u32 Size);


/*
 * Function: evm_porting_sto_WriteFlash
 * Description: ������д��FLASH��
 * Input: 
 *           StoDev: FLASH�豸��
 * 		Addr:FLASH��ַ
 *           DataBuf:���ݴ�ŵ�ַ
 *           Size: ���ݳ���
 * Output: none
 * Return: 0:SUCCESS , other is Fail
 */
ret_code_e evm_porting_sto_WriteFlash(evm_u32 StoDev, evm_u32 Addr , evm_u8 *DataBuf , evm_u32 Size);


/*
 * Function: evm_porting_sto_GetFlashPartitionInfo
 * Description: ��ȡ��������ģ���Flash��ַ����С����Ϣ
 * Input: 
 *           partition������ö��
 * 		
 *           
 * Output: 
 *           info:������Ϣ�ṹ��
 * Return: 0:SUCCESS , other is Fail
 */

ret_code_e evm_porting_sto_GetFlashPartitionInfo(EVM_FLASH_PARTITION_E partition, EVM_FlashPartitionInfo_T *info);

#endif

