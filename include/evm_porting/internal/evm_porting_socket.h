/*
 * evm_porting_socket.h
 * Copyright(C) EnRich DTV Group Co.,Ltd.
 *
 * Description: 
 *
 * Authors: 沈辉<shenhui@evmtv.com>
 */

#ifndef EVM_PORTING_SOCKET_H_
#define EVM_PORTING_SOCKET_H_

#include "../../evm_typedef.h"

typedef enum evm_porting_socketType_e {
	EVM_PORTING_SOCKTYPE_TCP = 0,
	EVM_PORTING_SOCKTYPE_UDP ,
	EVM_PORTING_SOCKTYPE_COUNT
} evm_porting_socketType_e;

/*
 * 函数名: evm_porting_ServerSocketOpen
 * 函数说明: 建立一个新的socket，即向系统注册一个新的通信端口，作为服务端。
 * 输入参数:
 *      port: 端口号。
 *      type: 网络协议类型。
 *      bBlock： 是否为阻塞。
 * 输出参数:
 *      phSocket: 如果建立成功，socket（通信端口）的句柄被写入 phSocket的内存。
 * 返回值: 查看枚举型 ret_code_e 。
 */
ret_code_e evm_porting_ServerSocketOpen(evm_handle* phSocket, evm_u16 port, evm_porting_socketType_e type, evm_bool bBlock);
/*
 * 函数名: evm_porting_ServerSocketClose
 * 函数说明: 关闭一个socket，即向系统注销一个通信端口。
 * 输入参数:
 *      handle: 要关闭的socket（通信端口）的文件句柄。
 * 输出参数:
 *      无。
 * 返回值: 查看枚举型 ret_code_e 。
 */
ret_code_e evm_porting_ServerSocketClose(evm_handle handle);
/*
 * 函数名: evm_porting_ClientSocketOpen
 * 函数说明: 建立一个新的socket，即向系统注册一个新的通信端口，作为客户端。
 * 输入参数:
 * 		host: 用来建立socket通信的主机域名。
 * 		port: 端口号。
 *      type: 网络协议类型。
 *      bBlock： 是否为阻塞。
 * 输出参数:
 * 		phSocket: 如果建立成功，socket（通信端口）的句柄被写入 phSocket的内存。
 * 返回值: 查看枚举型 ret_code_e 。
 */
ret_code_e evm_porting_ClientSocketOpen(evm_handle* phSocket, evm_s8 const* host, evm_u16 port, evm_porting_socketType_e type, evm_bool bBblock);
/*
 * 函数名: evm_porting_ClientSocketClose
 * 函数说明: 关闭一个socket，即向系统注销一个通信端口。
 * 输入参数:
 * 		handle: 要关闭的socket（通信端口）的文件句柄。
 * 输出参数:
 * 		无。
 * 返回值: 查看枚举型 ret_code_e 。
 */
ret_code_e evm_porting_ClientSocketClose(evm_handle handle);
/*
 * 函数名: evm_porting_SocketRecv
 * 函数说明: 从一个socket（通信端口）中接收数据。
 * 输入参数:
 * 		handle: 要接收数据的socket（通信端口）的文件句柄。
 * 		size: 接收数据的大小。
 * 输出参数:
 * 		data: 把从socket（通信端口）接受到的数据写入data的内存中。
 * 返回值: 返回实际接收的数据的长度，不成功返回-1。
 */
evm_s32 evm_porting_SocketRecv(evm_handle handle, evm_s8* data, evm_s32 size);
/*
 * 函数名: evm_porting_SocketSend
 * 函数说明: 向建立好的socket（通信端口）中写入size大小的数据。
 * 输入参数:
 * 		data: 要写入数据的socket（通信端口）的数据的内存地址。
 * 		size: 写入数据的大小。
 * 输出参数:
 * 		handle: 数据写入socket（通信端口）的文件句柄。
 * 返回值: 返回实际写入的数据的长度，不成功返回-1。
 */
evm_s32 evm_porting_SocketSend(evm_handle handle, evm_s8* data, evm_s32 size);

#endif /* EVM_PORTING_SOCKET_H_ */
