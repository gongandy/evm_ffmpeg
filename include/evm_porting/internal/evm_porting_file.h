/*
 * evm_porting_file.h
 * Copyright(C) EnRich DTV Group Co.,Ltd.
 *
 * Description: 
 *
 * Authors: 沈辉<shenhui@evmtv.com>
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
	EVM_PORTING_FOPENMODE_READ = 1,  			//只读方式打开
	EVM_PORTING_FOPENMODE_WRITE = 2,  			//只写方式打开
	EVM_PORTING_FOPENMODE_TRUNCATE = 4, 		//清除原来内容
	EVM_PORTING_FOPENMODE_CREATE = 8  			//如果文件不存在就创建
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
	evm_s8 path[EVM_PORTING_PATH_LEN];  		//包含name，utf8编码
	evm_s8 name[EVM_PORTING_NAME_LEN];  		//utf8编码
	evm_u32 size;  								//文件大小
} evm_porting_dirNode_t;


/*
 * 函数名: 		evm_porting_Access
 * 函数说明: 	确定文件或文件夹的访问权限。
 * 输入参数:
 *		path: 		需检测的文件路径。
 *		mode: 		检测类型
 * 输出参数:
 *		无。
 * 返回值: 		具有权限返回0，否则返回-1
 */
ret_code_e evm_porting_Access(const evm_s8* path, evm_porting_accessMode_e mode);

//////////////////////////////////////////////////文件操作////////////////////////////////////////////////////
/*
 * 函数名: evm_porting_Fopen
 * 函数说明: 打开指定路径及文件名的文件。
 * 输入参数:
 * 		path: 要打开文件的路径及文件名的字符串。
 * 		mode: 打开文件的流形态（打开方式）。
 * 输出参数:
 * 		无。
 * 返回值: 返回被打开文件的文件句柄，失败返回0。
 */
evm_handle evm_porting_Fopen(const evm_s8* path, evm_s32 mode);

/*
 * 函数名: evm_porting_Fclose
 * 函数说明: 关闭evm_porting_Fopen（）打开的文件。
 * 输入参数:
 * 		hFile: 已打开文件的文件句柄。
 * 输出参数:
 * 		无。
 * 返回值: 查看枚举型 ret_code_e 。
 */
ret_code_e evm_porting_Fclose(evm_handle hFile);

/*
 * 函数名: 		evm_porting_Feof
 * 函数说明: 	检测流上的文件结束符
 * 输入参数:
 * 					hFile: 已打开文件的文件句柄。
 * 输出参数:
 * 					无。
 * 返回值: 		遇到文件结束符返回非零值，否则返回0
 */
evm_s32 evm_porting_Feof(evm_handle hFile);

/*
 * 函数名: evm_porting_Fread
 * 函数说明: 从文件流中的指定位置开始读取数据。
 * 输入参数:
 * 		hFile: 已打开文件的文件句柄。
 * 		size: 要读取数据的字节数。
 * 		offset: 从当前文件流的读写位置增加offset个位移量。
 * 输出参数:
 * 		buffer: 指向欲存放读取数据的空间 。
 * 返回值: 实际读取出来的字节数。
 */
evm_s32 evm_porting_Fread(evm_handle hFile, void* buffer, evm_u32 size, evm_s32 offset);

/*
 * 函数名: evm_porting_Fwrite
 * 函数说明: 从文件流中的指定位置开始写入数据。
 * 输入参数:
 *      hFile: 已打开文件的文件句柄。
 *      buffer: 指向欲写入的数据的空间。
 *      size: 要写入数据的字节数。
 *      offset: 从当前文件流的读写位置增加offset个位移量。
 * 输入参数:
 *      无
 * 返回值: 实际读取出来的字节数。
 */
evm_s32 evm_porting_Fwrite(evm_handle hFile, void* buffer, evm_u32 size, evm_s32 offset);

/*
 * 函数名: evm_porting_Fseek
 * 函数说明: 移动文件流的读写位置。
 * 输入参数:
 * 		hFile: 已打开文件的文件句柄。
 * 		offset: 从当前文件流的读写位置增加offset个位移量。
 * 		origin: 设置文件流中开始移动前的读写位置的。
 * 输出参数:
 * 		无。
 * 返回值: 调用成功返回0，若有错误返回-1。
 */
evm_s32 evm_porting_Fseek(evm_handle hFile, evm_s32 offset, evm_porting_fseekOrigin_e origin);

/*
 * 函数名: evm_porting_Ftell
 * 函数说明: 取得当前文件流的读写位置。
 * 输入参数:
 * 		hFile: 已打开文件的文件句柄。
 * 输出参数:
 * 		无。
 * 返回值: 调用成功返回目前的读写位置，若有错误返回-1。
 */
evm_s32 evm_porting_Ftell(evm_handle hFile);

/*
 * 函数名: evm_porting_CopyFile
 * 函数说明: 复制文件
 * 输入参数:
 *      src: 源文件路径
 *      dst: 目的文件路径
 * 输出参数:
 *      无
 * 返回值: 参见ret_code_e枚举
 */
ret_code_e evm_porting_CopyFile(evm_s8* src, evm_s8* dst);

/*
 * 函数名: evm_porting_MoveFile
 * 函数说明: 移动文件
 * 输入参数:
 *      src: 源文件路径
 *      dst: 目的文件路径
 * 输出参数:
 *      无
 * 返回值: 参见ret_code_e枚举
 */
ret_code_e evm_porting_MoveFile(evm_s8* src, evm_s8* dst);

/*
 * 函数名: evm_porting_DeleteFile
 * 函数说明: 删除文件
 * 输入参数:
 *      src: 源文件路径
 * 输出参数:
 *      无
 * 返回值: 参见ret_code_e枚举
 */
ret_code_e evm_porting_DeleteFile(evm_s8* src);

///////////////////////////////////////////////目录操作///////////////////////////////////////////////////////////
/*
 * 函数名: evm_porting_CopyDir
 * 函数说明: 复制目录
 * 输入参数:
 *      src: 源目录路径
 *      dst: 目的目录路径
 * 输出参数:
 *      无
 * 返回值: 参见ret_code_e枚举
 */
ret_code_e evm_porting_CopyDir(evm_s8* src, evm_s8* dst);

/*
 * 函数名: evm_porting_MoveDir
 * 函数说明: 移动目录
 * 输入参数:
 *      src: 源目录路径
 *      dst: 目的目录路径
 * 输出参数:
 *      无
 * 返回值: 参见ret_code_e枚举
 */
ret_code_e evm_porting_MoveDir(evm_s8* src, evm_s8* dst);

/*
 * 函数名: evm_porting_CreateDir
 * 函数说明: 创建目录
 * 输入参数:
 *      path: 目录路径
 * 输出参数:
 *      无
 * 返回值: 参见ret_code_e枚举
 */
ret_code_e evm_porting_CreateDir(evm_s8* path);

/*
 * 函数名: evm_porting_DirExist
 * 函数说明: 判断目录是否存在
 * 输入参数:
 *      path: 目录路径
 * 输出参数:
 *      pbExist: 写入目录是否存在
 * 返回值: 参见ret_code_e枚举
 */
ret_code_e evm_porting_DirExist(evm_s8* path, evm_bool *pbExist);

/*
 * 函数名: evm_porting_DeleteDir
 * 函数说明: 删除目录
 * 输入参数:
 *      src: 源目录路径
 * 输出参数:
 *      无
 * 返回值: 参见ret_code_e枚举
 */
ret_code_e evm_porting_DeleteDir(evm_s8* src);

/*
 * 函数名: evm_porting_DirGetNodeNum
 * 函数说明: 获取path目录下指定类型的节点个数
 * 输入参数:
 * 		path: 目录路径
 * 		nodeType: 节点类型，使用evm_porting_dirNodeType_e枚举类型，如EVM_PORTING_DIRNODETYPE_FILE表示只列出文件，
 * 			EVM_PORTING_DIRNODETYPE_FILE|EVM_PORTING_DIRNODETYPE_DIRECTORY表示列出文件和目录
 * 输出参数:
 * 		pNum: 返回获取到的指定类型的节点个数
 * 返回值: 如果获取成功返回EVM_SUCCESS，否则返回EVM_FAILURE
 */
ret_code_e evm_porting_DirGetNodeNum(evm_s8 *path, evm_s32 nodeType, evm_u32 *pNum);

/*
 * 函数名: evm_porting_DirListNode
 * 函数说明: 获取path目录下指定类型的节点属性
 * 输入参数:
 * 		path: 目录路径
 * 		nodeType: 节点类型，使用evm_porting_dirNodeType_e枚举类型，如EVM_PORTING_DIRNODETYPE_FILE表示只列出文件，
 * 			EVM_PORTING_DIRNODETYPE_FILE|EVM_PORTING_DIRNODETYPE_DIRECTORY表示列出文件和目录
 * 		listNum: 需要获取的节点个数
 * 输出参数:
 * 		list: 返回获取到的指定类型的节点的属性，evm_porting_dirNode_t类型的数组，内存由调用本函数者分配，数组元素个数为listNum
 * 		pAvalidNum: 返回实际获取的节点个数
 * 返回值: 如果获取成功返回EVM_SUCCESS，否则返回EVM_FAILURE
 */
ret_code_e evm_porting_DirListNode(evm_s8 *path, evm_s32 nodeType, evm_u32 listNum, evm_porting_dirNode_t* list, evm_u32 *pAvalidNum);


/*
 * 函数名: evm_porting_PlatGetUdiskPath
 * 函数说明: 	获取文件路径映射
 * 输入参数:
 * 		path: 		映射前路径
 * 输出参数:
 *		无
 * 返回值: 		映射后的文件路径，如无映射，直接返回输入参数
 */
 
evm_s8* evm_porting_PlatGetUdiskPath(evm_s8 const*path);

/*
 * 函数名: evm_porting_PlatHandleUIProtocol
 * 函数说明: 	获取文件路径映射
 * 输入参数:
 * 		fileName: 	映射前路径
 * 输出参数:
 *		buf:			映射后路径
 *		len:			路径字符串长度，不可大于EVM_PORTING_URL_MAX
 * 返回值: 		see enum ret_code_e
 */
ret_code_e evm_porting_PlatHandleUIProtocol(evm_s8 const* fileName, evm_u8* buf, evm_s32* len);

#endif /* EVM_PORTING_FILE_H_ */
