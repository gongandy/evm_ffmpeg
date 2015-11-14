/*
 * evm_typedef.h
 * Copyright(C) EnRich DTV Group Co.,Ltd.
 *
 * Description: 
 *
 * Authors: 沈辉<shenhui@evmtv.com>
 *			Endy	<caifk@evmtv.com>
 */

#ifndef EVM_TYPEDEF_H_
#define EVM_TYPEDEF_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <unistd.h>

//#include "evm_config.h"


typedef char evm_s8;
typedef unsigned char evm_u8;
typedef short evm_s16;
typedef unsigned short evm_u16;
typedef int evm_s32;
typedef unsigned int evm_u32;
typedef long long evm_s64;
typedef unsigned long long evm_u64;
typedef float evm_f32;
typedef double evm_f64;
typedef int evm_bool;

typedef evm_u32 evm_handle;

#ifndef NULL
#define EVM_NULL (0)
#else
#define EVM_NULL NULL
#endif /* NULL */

#ifndef __LINE__
#define __LINE__ (-1)
#endif /* __LINE__*/

#define EVM_TRUE (0==0)
#define EVM_FALSE (!EVM_TRUE)

#define EVM_MIN(x, y) ((x>y)?y:x)
#define EVM_MAX(x, y) ((x>y)?x:y)

#define EVM_INVALID_ID (0xffffffff)

#define INLINE inline
#define REGISTER register

typedef enum ret_code_e {
	EVM_SUCCESS = 0,
	EVM_FAILURE = -1,

	EVM_ERR_OUTOFMEMORY = -2, /* 内存泄漏 */
	EVM_ERR_INVALIDPOINTER = -3, /* 无效指针 */
	EVM_ERR_INVALIDID = -4,

	EVM_ERR_TIMEOUT = -5, /* 超时 */

	EVM_ERR_IOERROR = -6,

	EVM_ERR_NOTINITED = -7, /* 未初始化 */
	EVM_ERR_HASINITED = -8, /* 已初始化过 */
	EVM_ERR_CANNTREENTRANT = -9, /* 不可重入 */

	EVM_ERR_IDNOTEXIST = -10,  /* 无效的ID */

	EVM_ERR_SRCNOTEXIST = -11,  /* 源不存在 */
	EVM_ERR_NOENOUGHSPACE = -12,  /* 没有足够空间 */
}ret_code_e;

typedef struct evm_rect_t
{
	evm_s32 x;
	evm_s32 y;
	evm_s32 w;
	evm_s32 h;
} evm_rect_t;

#ifndef __LINE__
#define __EVM_LINE__ (-1)
#else
#define __EVM_LINE__ __LINE__
#endif

#ifndef __FILE__
#define __EVM_FILE__ ("null")
#else
#define __EVM_FILE__ __FILE__
#endif

//__FUNCTION__不是宏，我们只能默认所有的编译器都支持__FUNCTION__
#define __EVM_FUNCTION__ __FUNCTION__

#define EVM_MAKE_COMPLIER_HAPPY(x) (void)x

//错误打印，所有模块统一使用本宏定义。由于__LINE__会返回路径，作为错误打印太多，所以使用__FUNCTION__
#define RED          "\033[0;32;31m"
#define NONE         "\033[m"
#define BLUE         "\033[0;32;34m"
#define YELLOW       "\033[01;33m"
#define GREEN        "\033[0;32;32m"
#define WHITE        "\e[0;37m"
#define PURPLE       "\e[0;35m"

typedef enum
{
    EVM_PRINT_LEVEL_NONE_E = -1,
    EVM_PRINT_LEVEL_ERROR_E,
    EVM_PRINT_LEVEL_WARN_E,
    EVM_PRINT_LEVEL_DEBUG_E,
    EVM_PRINT_LEVEL_INFO_E,
    EVM_PRINT_LEVEL_DATA_DUMP_PARAM_E,  //仅仅打印简单的函数参数等信息
    EVM_PRINT_LEVEL_DATA_DUMP_ALL_E,    //打印全部的数据，包括section、文件读写等具体数据
} evm_printLevel_e;

#if EVM_DEBUG

#define EVM_ERROR_PRINT(fmt, ...)  evm_porting_OsPrintf(RED "[ERROR][%s][%s][%d] [time:%u] "fmt NONE, __EVM_FILE__, __EVM_FUNCTION__, __EVM_LINE__,evm_porting_OsTickTime(), ##__VA_ARGS__)

#define EVM_INFO_PRINT(fmt, ...)  //evm_porting_OsPrintf(NONE "[INFO][%s][%s][%d]"fmt, __EVM_FILE__, __EVM_FUNCTION__, __EVM_LINE__, ##__VA_ARGS__)

#define EVM_DEBUG_PRINT(fmt, ...) evm_porting_OsPrintf(NONE "[DEBUG][%s][%s][%d]"fmt, __EVM_FILE__, __EVM_FUNCTION__, __EVM_LINE__, ##__VA_ARGS__)

#define EVM_WARN_PRINT(fmt, ...) //evm_porting_OsPrintf(NONE "[DEBUG][%s][%s][%d]"fmt, __EVM_FILE__, __EVM_FUNCTION__, __EVM_LINE__, ##__VA_ARGS__)

#else

#define EVM_ERROR_PRINT(fmt, ...)  evm_porting_OsPrintf(RED "[ERROR][%s][%s][%d]"fmt NONE, __EVM_FILE__, __EVM_FUNCTION__, __EVM_LINE__, ##__VA_ARGS__)

#define EVM_INFO_PRINT(fmt, ...)  

#define EVM_DEBUG_PRINT(fmt, ...) 

#define EVM_WARN_PRINT(fmt, ...) 

#endif /* if 0. 2013-8-27 14:38:43 evm */


//void printBeforeConsumeTime(evm_s8 *moduleName);
//void printModuleConsumeTime(evm_s8 *moduleName);

#endif /* EVM_TYPEDEF_H_ */
