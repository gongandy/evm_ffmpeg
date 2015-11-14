/*
 * evm_porting_udisk.h
 * Copyright(C) EnRich DTV Group Co.,Ltd.
 *
 * Description:
 *
 * Author: chengzp
 */

#ifndef EVM_PORTING_UDISK_H_
#define EVM_PORTING_UDISK_H_

#include "../../evm_typedef.h"
#define EVM_PORTING_DEV_PATH_LEN 128
#define EVM_PORTING_DEV_NAME_LEN 64

////////////////////////////////////// type define ////////////////////////////////
/* USB Device State*/

typedef enum evm_porting_udiskFsType_e
{
    EVM_PORTING_UDISKFSTYPE_NULL = 0,
    EVM_PORTING_UDISKFSTYPE_VFAT,
    EVM_PORTING_UDISKFSTYPE_EXT2,
    EVM_PORTING_UDISKFSTYPE_EXT3
} evm_porting_udiskFsType_e;

typedef enum evm_porting_udisk_usbState_e
{
    UDISK_USB_STATE_PLUGOUT = 0,
    UDISK_USB_STATE_PLUGIN
} evm_porting_udisk_usbState_e;

typedef struct evm_porting_devName_t
{
    evm_s8 devName[EVM_PORTING_DEV_NAME_LEN];
}evm_porting_devName_t;


typedef struct evm_porting_partitionInfo_t
{
    evm_s32 partitionID;
    evm_porting_udiskFsType_e fsType;
    evm_s8 partitionName[EVM_PORTING_DEV_NAME_LEN];
    evm_s8 mntName[EVM_PORTING_DEV_NAME_LEN];
    evm_bool partitionIsMount;
}evm_porting_partitionInfo_t;

typedef struct evm_porting_udisk_devInfo_t
{
    evm_s32 devID;
    evm_s8 devName[EVM_PORTING_DEV_PATH_LEN];
    evm_s8 mntName[EVM_PORTING_DEV_PATH_LEN];
    evm_porting_udisk_usbState_e usbState;
    evm_porting_partitionInfo_t* partitions;
    evm_u32 partitionCnt;
    evm_bool usbIsMount;
    struct evm_porting_udisk_devInfo_t* next;
}evm_porting_udisk_devInfo_t;

///////////////////////////////////// udisk function /////////////////////////////////

/*
 * 函数名: evm_porting_udisk_Init
 * 函数说明: 初始化设备，并实现挂载和卸载功能
 * 输入参数:
 *     无
 * 输出参数:
 *      无。
 * 返回值: 参见ret_code_e枚举
 */
ret_code_e evm_porting_udisk_Init(void);

/*
 * 函数名: evm_porting_udisk_Finsh
 * 函数说明: 回收分配的内存空间
 * 输入参数:
 *     无
 * 输出参数:
 *      无。
 * 返回值: 参见ret_code_e枚举
 */
ret_code_e evm_porting_udisk_Finsh(void);

/*
 * 函数名: evm_porting_udisk_UninstallDev
 * 函数说明: 卸载外接存储设备
 * 输入参数：
 *      pDevName：外接存储设备路径名
 * 输出参数：
 *      无
 * 返回值：参见ret_code_e枚举
 *
 */
ret_code_e evm_porting_udisk_UninstallDev(evm_s8 *pDevName);

/*
 * 函数名: evm_porting_udisk_DiskFormatDev
 * 函数说明: 格式化外接存储设备
 * 输入参数：
 *      pUdiskName：外接存储设备名
 *      fmt：格式化格式
 * 输出参数：
 *      无
 * 返回值：参见ret_code_e枚举
 *
 */
ret_code_e evm_porting_udisk_DiskFormatDev(evm_s8* pUdiskName, evm_s8 *pPartitionName,
        evm_porting_udiskFsType_e fmt);

/*
 * 函数名: evm_porting_udisk_GetUdiskCount
 * 函数说明: 获取外接存储设备个数
 * 输入参数:
 *      无
 * 输出参数:
 *      count: 写入外接存储设备个数
 * 返回值: 参见ret_code_e枚举
 */
ret_code_e evm_porting_udisk_GetUdiskCount(evm_u32 *count);

/*
 * 函数名: evm_porting_udisk_GetDevByDevName
 * 函数说明: 通过设备名获取设备节点
 * 输入参数:
 *      pDevName: 存储设备名
 * 输出参数:
 *      pDev：需要写入的设备节点
 * 返回值: 参见ret_code_e枚举
 */
ret_code_e evm_porting_udisk_GetDevByDevName(evm_s8* pDevName, evm_porting_udisk_devInfo_t* pDev);

/*
 * 函数名: evm_porting_udisk_GetDevNames
 * 函数说明: 获取设备名数组
 * 输入参数:
 *      count: 需要写入的设备名个数
 * 输出参数:
 *      pDevBuffer：需要写入的设备名数组
 *      availCount：实际写入的个数
 * 返回值: 参见ret_code_e枚举
 */
ret_code_e evm_porting_udisk_GetDevNames(evm_s32 count, evm_porting_devName_t* pDevBuffer,
        evm_s32* availCount);

#endif /* EVM_PORTING_UDISK_H_ */
