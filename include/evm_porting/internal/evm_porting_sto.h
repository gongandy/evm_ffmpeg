/*
 * evm_porting_sto.h
 * Copyright(C) EnRich DTV Group Co.,Ltd.
 *
 * Description: 与FLASH存储相关接口
 *
 * Authors: 研发三部
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
 * Description: 对flash的初始化
 * Input: 
 *           StoDev: 返回FLASH设备句柄
 * 		
 * Output: none
 * Return: 0:SUCCESS , other is Fail
 */
ret_code_e evm_porting_sto_FlashInit(evm_u32 *StoDev);

/*
 * Function: evm_porting_sto_ReadFlash
 * Description: 从FLASH中读取数据
 * Input: 
 *           StoDev: FLASH设备号
 * 		Addr:FLASH地址
 *           DataBuf:读取数据存放地址
 *           Size: 读取长度
 * Output: none
 * Return: 0:SUCCESS , other is Fail
 */
ret_code_e evm_porting_sto_ReadFlash(evm_u32 StoDev, evm_u32 Addr , evm_u8 *DataBuf , evm_u32 Size);


/*
 * Function: evm_porting_sto_WriteFlash
 * Description: 把数据写入FLASH中
 * Input: 
 *           StoDev: FLASH设备号
 * 		Addr:FLASH地址
 *           DataBuf:数据存放地址
 *           Size: 数据长度
 * Output: none
 * Return: 0:SUCCESS , other is Fail
 */
ret_code_e evm_porting_sto_WriteFlash(evm_u32 StoDev, evm_u32 Addr , evm_u8 *DataBuf , evm_u32 Size);


/*
 * Function: evm_porting_sto_GetFlashPartitionInfo
 * Description: 获取各个分区模块的Flash地址、大小等信息
 * Input: 
 *           partition：分区枚举
 * 		
 *           
 * Output: 
 *           info:分区信息结构体
 * Return: 0:SUCCESS , other is Fail
 */

ret_code_e evm_porting_sto_GetFlashPartitionInfo(EVM_FLASH_PARTITION_E partition, EVM_FlashPartitionInfo_T *info);

#endif

