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
 * ������: evm_porting_udisk_Init
 * ����˵��: ��ʼ���豸����ʵ�ֹ��غ�ж�ع���
 * �������:
 *     ��
 * �������:
 *      �ޡ�
 * ����ֵ: �μ�ret_code_eö��
 */
ret_code_e evm_porting_udisk_Init(void);

/*
 * ������: evm_porting_udisk_Finsh
 * ����˵��: ���շ�����ڴ�ռ�
 * �������:
 *     ��
 * �������:
 *      �ޡ�
 * ����ֵ: �μ�ret_code_eö��
 */
ret_code_e evm_porting_udisk_Finsh(void);

/*
 * ������: evm_porting_udisk_UninstallDev
 * ����˵��: ж����Ӵ洢�豸
 * ���������
 *      pDevName����Ӵ洢�豸·����
 * ���������
 *      ��
 * ����ֵ���μ�ret_code_eö��
 *
 */
ret_code_e evm_porting_udisk_UninstallDev(evm_s8 *pDevName);

/*
 * ������: evm_porting_udisk_DiskFormatDev
 * ����˵��: ��ʽ����Ӵ洢�豸
 * ���������
 *      pUdiskName����Ӵ洢�豸��
 *      fmt����ʽ����ʽ
 * ���������
 *      ��
 * ����ֵ���μ�ret_code_eö��
 *
 */
ret_code_e evm_porting_udisk_DiskFormatDev(evm_s8* pUdiskName, evm_s8 *pPartitionName,
        evm_porting_udiskFsType_e fmt);

/*
 * ������: evm_porting_udisk_GetUdiskCount
 * ����˵��: ��ȡ��Ӵ洢�豸����
 * �������:
 *      ��
 * �������:
 *      count: д����Ӵ洢�豸����
 * ����ֵ: �μ�ret_code_eö��
 */
ret_code_e evm_porting_udisk_GetUdiskCount(evm_u32 *count);

/*
 * ������: evm_porting_udisk_GetDevByDevName
 * ����˵��: ͨ���豸����ȡ�豸�ڵ�
 * �������:
 *      pDevName: �洢�豸��
 * �������:
 *      pDev����Ҫд����豸�ڵ�
 * ����ֵ: �μ�ret_code_eö��
 */
ret_code_e evm_porting_udisk_GetDevByDevName(evm_s8* pDevName, evm_porting_udisk_devInfo_t* pDev);

/*
 * ������: evm_porting_udisk_GetDevNames
 * ����˵��: ��ȡ�豸������
 * �������:
 *      count: ��Ҫд����豸������
 * �������:
 *      pDevBuffer����Ҫд����豸������
 *      availCount��ʵ��д��ĸ���
 * ����ֵ: �μ�ret_code_eö��
 */
ret_code_e evm_porting_udisk_GetDevNames(evm_s32 count, evm_porting_devName_t* pDevBuffer,
        evm_s32* availCount);

#endif /* EVM_PORTING_UDISK_H_ */
