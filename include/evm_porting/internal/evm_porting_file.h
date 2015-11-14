/*
 * evm_porting_file.h
 * Copyright(C) EnRich DTV Group Co.,Ltd.
 *
 * Description: 
 *
 * Authors: ���<shenhui@evmtv.com>
 *			Endy	<caifk@evmtv.com>
 */

#ifndef EVM_PORTING_FILE_H_
#define EVM_PORTING_FILE_H_

#include "../../evm_typedef.h"

#define EVM_EOF (-1)
#define EVM_PORTING_PATH_LEN (512)
#define EVM_PORTING_NAME_LEN (EVM_PORTING_PATH_LEN/2)
#define EVM_PORTING_URL_MAX		(4096)

typedef enum evm_porting_accessMode_e {
	EVM_PORTING_ACCESSMODE_FOK = 0,  			//existence
	EVM_PORTING_ACCESSMODE_XOK = 1,  			//excute permission
	EVM_PORTING_ACCESSMODE_WOK = 2, 			//write permission
	EVM_PORTING_ACCESSMODE_ROK = 4  			//read permission
} evm_porting_accessMode_e;

typedef enum evm_porting_fopenMode_e {
	EVM_PORTING_FOPENMODE_READ = 1,  			//ֻ����ʽ��
	EVM_PORTING_FOPENMODE_WRITE = 2,  			//ֻд��ʽ��
	EVM_PORTING_FOPENMODE_TRUNCATE = 4, 		//���ԭ������
	EVM_PORTING_FOPENMODE_CREATE = 8  			//����ļ������ھʹ���
} evm_porting_fopenMode_e;

typedef enum evm_porting_fseekOrigin_e {
	EVM_PORTING_SEEK_SET = 0,
	EVM_PORTING_SEEK_CUR = 1,
	EVM_PORTING_SEEK_END = 2
}evm_porting_fseekOrigin_e;

typedef enum evm_porting_dirNodeType_e {
	EVM_PORTING_DIRNODETYPE_FILE = 0x1,
	EVM_PORTING_DIRNODETYPE_DIRECTORY = 0x2
}evm_porting_dirNodeType_e;

typedef struct evm_porting_dirNode_t
{
	evm_porting_dirNodeType_e type;
	evm_s8 path[EVM_PORTING_PATH_LEN];  		//����name��utf8����
	evm_s8 name[EVM_PORTING_NAME_LEN];  		//utf8����
	evm_u32 size;  								//�ļ���С
} evm_porting_dirNode_t;


/*
 * ������: 		evm_porting_Access
 * ����˵��: 	ȷ���ļ����ļ��еķ���Ȩ�ޡ�
 * �������:
 *		path: 		������ļ�·����
 *		mode: 		�������
 * �������:
 *		�ޡ�
 * ����ֵ: 		����Ȩ�޷���0�����򷵻�-1
 */
ret_code_e evm_porting_Access(const evm_s8* path, evm_porting_accessMode_e mode);

//////////////////////////////////////////////////�ļ�����////////////////////////////////////////////////////
/*
 * ������: evm_porting_Fopen
 * ����˵��: ��ָ��·�����ļ������ļ���
 * �������:
 * 		path: Ҫ���ļ���·�����ļ������ַ�����
 * 		mode: ���ļ�������̬���򿪷�ʽ����
 * �������:
 * 		�ޡ�
 * ����ֵ: ���ر����ļ����ļ������ʧ�ܷ���0��
 */
evm_handle evm_porting_Fopen(const evm_s8* path, evm_s32 mode);

/*
 * ������: evm_porting_Fclose
 * ����˵��: �ر�evm_porting_Fopen�����򿪵��ļ���
 * �������:
 * 		hFile: �Ѵ��ļ����ļ������
 * �������:
 * 		�ޡ�
 * ����ֵ: �鿴ö���� ret_code_e ��
 */
ret_code_e evm_porting_Fclose(evm_handle hFile);

/*
 * ������: 		evm_porting_Feof
 * ����˵��: 	������ϵ��ļ�������
 * �������:
 * 					hFile: �Ѵ��ļ����ļ������
 * �������:
 * 					�ޡ�
 * ����ֵ: 		�����ļ����������ط���ֵ�����򷵻�0
 */
evm_s32 evm_porting_Feof(evm_handle hFile);

/*
 * ������: evm_porting_Fread
 * ����˵��: ���ļ����е�ָ��λ�ÿ�ʼ��ȡ���ݡ�
 * �������:
 * 		hFile: �Ѵ��ļ����ļ������
 * 		size: Ҫ��ȡ���ݵ��ֽ�����
 * 		offset: �ӵ�ǰ�ļ����Ķ�дλ������offset��λ������
 * �������:
 * 		buffer: ָ������Ŷ�ȡ���ݵĿռ� ��
 * ����ֵ: ʵ�ʶ�ȡ�������ֽ�����
 */
evm_s32 evm_porting_Fread(evm_handle hFile, void* buffer, evm_u32 size, evm_s32 offset);

/*
 * ������: evm_porting_Fwrite
 * ����˵��: ���ļ����е�ָ��λ�ÿ�ʼд�����ݡ�
 * �������:
 *      hFile: �Ѵ��ļ����ļ������
 *      buffer: ָ����д������ݵĿռ䡣
 *      size: Ҫд�����ݵ��ֽ�����
 *      offset: �ӵ�ǰ�ļ����Ķ�дλ������offset��λ������
 * �������:
 *      ��
 * ����ֵ: ʵ�ʶ�ȡ�������ֽ�����
 */
evm_s32 evm_porting_Fwrite(evm_handle hFile, void* buffer, evm_u32 size, evm_s32 offset);

/*
 * ������: evm_porting_Fseek
 * ����˵��: �ƶ��ļ����Ķ�дλ�á�
 * �������:
 * 		hFile: �Ѵ��ļ����ļ������
 * 		offset: �ӵ�ǰ�ļ����Ķ�дλ������offset��λ������
 * 		origin: �����ļ����п�ʼ�ƶ�ǰ�Ķ�дλ�õġ�
 * �������:
 * 		�ޡ�
 * ����ֵ: ���óɹ�����0�����д��󷵻�-1��
 */
evm_s32 evm_porting_Fseek(evm_handle hFile, evm_s32 offset, evm_porting_fseekOrigin_e origin);

/*
 * ������: evm_porting_Ftell
 * ����˵��: ȡ�õ�ǰ�ļ����Ķ�дλ�á�
 * �������:
 * 		hFile: �Ѵ��ļ����ļ������
 * �������:
 * 		�ޡ�
 * ����ֵ: ���óɹ�����Ŀǰ�Ķ�дλ�ã����д��󷵻�-1��
 */
evm_s32 evm_porting_Ftell(evm_handle hFile);

/*
 * ������: evm_porting_CopyFile
 * ����˵��: �����ļ�
 * �������:
 *      src: Դ�ļ�·��
 *      dst: Ŀ���ļ�·��
 * �������:
 *      ��
 * ����ֵ: �μ�ret_code_eö��
 */
ret_code_e evm_porting_CopyFile(evm_s8* src, evm_s8* dst);

/*
 * ������: evm_porting_MoveFile
 * ����˵��: �ƶ��ļ�
 * �������:
 *      src: Դ�ļ�·��
 *      dst: Ŀ���ļ�·��
 * �������:
 *      ��
 * ����ֵ: �μ�ret_code_eö��
 */
ret_code_e evm_porting_MoveFile(evm_s8* src, evm_s8* dst);

/*
 * ������: evm_porting_DeleteFile
 * ����˵��: ɾ���ļ�
 * �������:
 *      src: Դ�ļ�·��
 * �������:
 *      ��
 * ����ֵ: �μ�ret_code_eö��
 */
ret_code_e evm_porting_DeleteFile(evm_s8* src);

///////////////////////////////////////////////Ŀ¼����///////////////////////////////////////////////////////////
/*
 * ������: evm_porting_CopyDir
 * ����˵��: ����Ŀ¼
 * �������:
 *      src: ԴĿ¼·��
 *      dst: Ŀ��Ŀ¼·��
 * �������:
 *      ��
 * ����ֵ: �μ�ret_code_eö��
 */
ret_code_e evm_porting_CopyDir(evm_s8* src, evm_s8* dst);

/*
 * ������: evm_porting_MoveDir
 * ����˵��: �ƶ�Ŀ¼
 * �������:
 *      src: ԴĿ¼·��
 *      dst: Ŀ��Ŀ¼·��
 * �������:
 *      ��
 * ����ֵ: �μ�ret_code_eö��
 */
ret_code_e evm_porting_MoveDir(evm_s8* src, evm_s8* dst);

/*
 * ������: evm_porting_CreateDir
 * ����˵��: ����Ŀ¼
 * �������:
 *      path: Ŀ¼·��
 * �������:
 *      ��
 * ����ֵ: �μ�ret_code_eö��
 */
ret_code_e evm_porting_CreateDir(evm_s8* path);

/*
 * ������: evm_porting_DirExist
 * ����˵��: �ж�Ŀ¼�Ƿ����
 * �������:
 *      path: Ŀ¼·��
 * �������:
 *      pbExist: д��Ŀ¼�Ƿ����
 * ����ֵ: �μ�ret_code_eö��
 */
ret_code_e evm_porting_DirExist(evm_s8* path, evm_bool *pbExist);

/*
 * ������: evm_porting_DeleteDir
 * ����˵��: ɾ��Ŀ¼
 * �������:
 *      src: ԴĿ¼·��
 * �������:
 *      ��
 * ����ֵ: �μ�ret_code_eö��
 */
ret_code_e evm_porting_DeleteDir(evm_s8* src);

/*
 * ������: evm_porting_DirGetNodeNum
 * ����˵��: ��ȡpathĿ¼��ָ�����͵Ľڵ����
 * �������:
 * 		path: Ŀ¼·��
 * 		nodeType: �ڵ����ͣ�ʹ��evm_porting_dirNodeType_eö�����ͣ���EVM_PORTING_DIRNODETYPE_FILE��ʾֻ�г��ļ���
 * 			EVM_PORTING_DIRNODETYPE_FILE|EVM_PORTING_DIRNODETYPE_DIRECTORY��ʾ�г��ļ���Ŀ¼
 * �������:
 * 		pNum: ���ػ�ȡ����ָ�����͵Ľڵ����
 * ����ֵ: �����ȡ�ɹ�����EVM_SUCCESS�����򷵻�EVM_FAILURE
 */
ret_code_e evm_porting_DirGetNodeNum(evm_s8 *path, evm_s32 nodeType, evm_u32 *pNum);

/*
 * ������: evm_porting_DirListNode
 * ����˵��: ��ȡpathĿ¼��ָ�����͵Ľڵ�����
 * �������:
 * 		path: Ŀ¼·��
 * 		nodeType: �ڵ����ͣ�ʹ��evm_porting_dirNodeType_eö�����ͣ���EVM_PORTING_DIRNODETYPE_FILE��ʾֻ�г��ļ���
 * 			EVM_PORTING_DIRNODETYPE_FILE|EVM_PORTING_DIRNODETYPE_DIRECTORY��ʾ�г��ļ���Ŀ¼
 * 		listNum: ��Ҫ��ȡ�Ľڵ����
 * �������:
 * 		list: ���ػ�ȡ����ָ�����͵Ľڵ�����ԣ�evm_porting_dirNode_t���͵����飬�ڴ��ɵ��ñ������߷��䣬����Ԫ�ظ���ΪlistNum
 * 		pAvalidNum: ����ʵ�ʻ�ȡ�Ľڵ����
 * ����ֵ: �����ȡ�ɹ�����EVM_SUCCESS�����򷵻�EVM_FAILURE
 */
ret_code_e evm_porting_DirListNode(evm_s8 *path, evm_s32 nodeType, evm_u32 listNum, evm_porting_dirNode_t* list, evm_u32 *pAvalidNum);


/*
 * ������: evm_porting_PlatGetUdiskPath
 * ����˵��: 	��ȡ�ļ�·��ӳ��
 * �������:
 * 		path: 		ӳ��ǰ·��
 * �������:
 *		��
 * ����ֵ: 		ӳ�����ļ�·��������ӳ�䣬ֱ�ӷ����������
 */
 
evm_s8* evm_porting_PlatGetUdiskPath(evm_s8 const*path);

/*
 * ������: evm_porting_PlatHandleUIProtocol
 * ����˵��: 	��ȡ�ļ�·��ӳ��
 * �������:
 * 		fileName: 	ӳ��ǰ·��
 * �������:
 *		buf:			ӳ���·��
 *		len:			·���ַ������ȣ����ɴ���EVM_PORTING_URL_MAX
 * ����ֵ: 		see enum ret_code_e
 */
ret_code_e evm_porting_PlatHandleUIProtocol(evm_s8 const* fileName, evm_u8* buf, evm_s32* len);

#endif /* EVM_PORTING_FILE_H_ */
