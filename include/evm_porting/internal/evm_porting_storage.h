/*
 * evm_porting_storage.h
 * Copyright(C) EnRich DTV Group Co.,Ltd.
 *
 * Description: 描述U盘、移动硬盘等外接存储设备的接口
 *
 * Authors: 沈辉<shenhui@evmtv.com>
 */

#ifndef EVM_PORTING_STORAGE_H_
#define EVM_PORTING_STORAGE_H_

#include "../../evm_typedef.h"

#define EVM_PORTING_STORAGE_PATH_LEN (256)
#define EVM_PORTING_STORAGE_NAME_LEN (EVM_PORTING_STORAGE_PATH_LEN/2)

//文件系统格式
typedef enum evm_porting_storageFsType_e
{
    EVM_PORTING_STORAGEFSTYPE_VFAT,
    EVM_PORTING_STORAGEFSTYPE_EXT2,
    EVM_PORTING_STORAGEFSTYPE_EXT3
} evm_porting_storageFsType_e;

//存储设备分区信息
typedef struct evm_porting_storagePartitionInfo_t
{
    evm_s8 name[EVM_PORTING_STORAGE_NAME_LEN];  	//分区，UTF8编码
    evm_s8 path[EVM_PORTING_STORAGE_PATH_LEN];  	//分区对应的路径，UTF8编码

    evm_s64 totalSize;  							//分区总容量
    evm_s64 usedSize;  								//分区已使用容量

    evm_porting_storageFsType_e fsType;  			//文件系统格式
} evm_porting_storagePartitionInfo_t;

//存储设备信息
typedef struct evm_porting_storageInfo_t
{
    evm_s8 name[EVM_PORTING_STORAGE_NAME_LEN];  	//设备名，UTF8编码
    evm_s8 path[EVM_PORTING_STORAGE_PATH_LEN];  	//设备对应的路径，UTF8编码

    evm_s64 totalSize;  							//设备总容量
    evm_s64 usedSize;  								//设备已使用容量

    evm_u32 partitionCount;  						//分区个数
} evm_porting_storageInfo_t;


/*
 * 函数名: evm_porting_GetStorageCount
 * 函数说明: 获取外接存储设备个数
 * 输入参数:
 *      无
 * 输出参数:
 *      count: 写入外接存储设备个数
 * 返回值: 参见ret_code_e枚举
 */
ret_code_e evm_porting_GetStorageCount(evm_u32 *count);

/*
 * 函数名: evm_porting_GetStorageInfo
 * 函数说明: 获取外接存储设备信息
 * 输入参数:
 *      count: 调用者分配的evm_porting_storageInfo_t数组个数
 * 输出参数:
 *      pInfo: 写入获取的存储设备信息
 *      avalidCount: 写入的evm_porting_storageInfo_t个数
 * 返回值: 参见ret_code_e枚举
 */
ret_code_e evm_porting_GetStorageInfo(evm_u32 count, evm_porting_storageInfo_t* pInfo, evm_u32 *avalidCount);

/*
 * 函数名: evm_porting_GetStoragePartitionInfo
 * 函数说明: 获取外接存储设备分区信息
 * 输入参数:
 *      pStorageName: 存储设备名
 *      count: 调用者分配的evm_porting_storagePartitionInfo_t数组个数
 * 输出参数:
 *      pInfo: 写入获取的分区信息
 *      avalidCount: 写入的evm_porting_storagePartitionInfo_t个数
 * 返回值: 参见ret_code_e枚举
 */
ret_code_e evm_porting_GetStoragePartitionInfo(evm_s8 *pStorageName, evm_u32 count, evm_porting_storagePartitionInfo_t* pInfo, evm_u32 *avalidCount);

/*
 * 函数名: evm_porting_UninstallStorage
 * 函数说明: 卸载外接存储设备
 * 输入参数:
 *      pStorageName: 存储设备名
 * 输出参数:
 *      无
 * 返回值: 参见ret_code_e枚举
 */
ret_code_e evm_porting_UninstallStorage(evm_s8 *pStorageName);

/*
 * 函数名: evm_porting_FormatStorage
 * 函数说明: 格式化外接存储设备
 * 输入参数:
 *      pStorageName: 存储设备名
 *      fmt: 格式化格式
 * 输出参数:
 *      无
 * 返回值: 参见ret_code_e枚举
 */
ret_code_e evm_porting_FormatStorage(evm_s8 *pStorageName, evm_porting_storageFsType_e fmt);

#endif /* EVM_PORTING_STORAGE_H_ */
