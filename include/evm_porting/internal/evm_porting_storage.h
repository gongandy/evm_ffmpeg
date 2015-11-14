/*
 * evm_porting_storage.h
 * Copyright(C) EnRich DTV Group Co.,Ltd.
 *
 * Description: ����U�̡��ƶ�Ӳ�̵���Ӵ洢�豸�Ľӿ�
 *
 * Authors: ���<shenhui@evmtv.com>
 */

#ifndef EVM_PORTING_STORAGE_H_
#define EVM_PORTING_STORAGE_H_

#include "../../evm_typedef.h"

#define EVM_PORTING_STORAGE_PATH_LEN (256)
#define EVM_PORTING_STORAGE_NAME_LEN (EVM_PORTING_STORAGE_PATH_LEN/2)

//�ļ�ϵͳ��ʽ
typedef enum evm_porting_storageFsType_e
{
    EVM_PORTING_STORAGEFSTYPE_VFAT,
    EVM_PORTING_STORAGEFSTYPE_EXT2,
    EVM_PORTING_STORAGEFSTYPE_EXT3
} evm_porting_storageFsType_e;

//�洢�豸������Ϣ
typedef struct evm_porting_storagePartitionInfo_t
{
    evm_s8 name[EVM_PORTING_STORAGE_NAME_LEN];  	//������UTF8����
    evm_s8 path[EVM_PORTING_STORAGE_PATH_LEN];  	//������Ӧ��·����UTF8����

    evm_s64 totalSize;  							//����������
    evm_s64 usedSize;  								//������ʹ������

    evm_porting_storageFsType_e fsType;  			//�ļ�ϵͳ��ʽ
} evm_porting_storagePartitionInfo_t;

//�洢�豸��Ϣ
typedef struct evm_porting_storageInfo_t
{
    evm_s8 name[EVM_PORTING_STORAGE_NAME_LEN];  	//�豸����UTF8����
    evm_s8 path[EVM_PORTING_STORAGE_PATH_LEN];  	//�豸��Ӧ��·����UTF8����

    evm_s64 totalSize;  							//�豸������
    evm_s64 usedSize;  								//�豸��ʹ������

    evm_u32 partitionCount;  						//��������
} evm_porting_storageInfo_t;


/*
 * ������: evm_porting_GetStorageCount
 * ����˵��: ��ȡ��Ӵ洢�豸����
 * �������:
 *      ��
 * �������:
 *      count: д����Ӵ洢�豸����
 * ����ֵ: �μ�ret_code_eö��
 */
ret_code_e evm_porting_GetStorageCount(evm_u32 *count);

/*
 * ������: evm_porting_GetStorageInfo
 * ����˵��: ��ȡ��Ӵ洢�豸��Ϣ
 * �������:
 *      count: �����߷����evm_porting_storageInfo_t�������
 * �������:
 *      pInfo: д���ȡ�Ĵ洢�豸��Ϣ
 *      avalidCount: д���evm_porting_storageInfo_t����
 * ����ֵ: �μ�ret_code_eö��
 */
ret_code_e evm_porting_GetStorageInfo(evm_u32 count, evm_porting_storageInfo_t* pInfo, evm_u32 *avalidCount);

/*
 * ������: evm_porting_GetStoragePartitionInfo
 * ����˵��: ��ȡ��Ӵ洢�豸������Ϣ
 * �������:
 *      pStorageName: �洢�豸��
 *      count: �����߷����evm_porting_storagePartitionInfo_t�������
 * �������:
 *      pInfo: д���ȡ�ķ�����Ϣ
 *      avalidCount: д���evm_porting_storagePartitionInfo_t����
 * ����ֵ: �μ�ret_code_eö��
 */
ret_code_e evm_porting_GetStoragePartitionInfo(evm_s8 *pStorageName, evm_u32 count, evm_porting_storagePartitionInfo_t* pInfo, evm_u32 *avalidCount);

/*
 * ������: evm_porting_UninstallStorage
 * ����˵��: ж����Ӵ洢�豸
 * �������:
 *      pStorageName: �洢�豸��
 * �������:
 *      ��
 * ����ֵ: �μ�ret_code_eö��
 */
ret_code_e evm_porting_UninstallStorage(evm_s8 *pStorageName);

/*
 * ������: evm_porting_FormatStorage
 * ����˵��: ��ʽ����Ӵ洢�豸
 * �������:
 *      pStorageName: �洢�豸��
 *      fmt: ��ʽ����ʽ
 * �������:
 *      ��
 * ����ֵ: �μ�ret_code_eö��
 */
ret_code_e evm_porting_FormatStorage(evm_s8 *pStorageName, evm_porting_storageFsType_e fmt);

#endif /* EVM_PORTING_STORAGE_H_ */
