/*
 * evm_porting_socket.h
 * Copyright(C) EnRich DTV Group Co.,Ltd.
 *
 * Description: 
 *
 * Authors: ���<shenhui@evmtv.com>
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
 * ������: evm_porting_ServerSocketOpen
 * ����˵��: ����һ���µ�socket������ϵͳע��һ���µ�ͨ�Ŷ˿ڣ���Ϊ����ˡ�
 * �������:
 *      port: �˿ںš�
 *      type: ����Э�����͡�
 *      bBlock�� �Ƿ�Ϊ������
 * �������:
 *      phSocket: ��������ɹ���socket��ͨ�Ŷ˿ڣ��ľ����д�� phSocket���ڴ档
 * ����ֵ: �鿴ö���� ret_code_e ��
 */
ret_code_e evm_porting_ServerSocketOpen(evm_handle* phSocket, evm_u16 port, evm_porting_socketType_e type, evm_bool bBlock);
/*
 * ������: evm_porting_ServerSocketClose
 * ����˵��: �ر�һ��socket������ϵͳע��һ��ͨ�Ŷ˿ڡ�
 * �������:
 *      handle: Ҫ�رյ�socket��ͨ�Ŷ˿ڣ����ļ������
 * �������:
 *      �ޡ�
 * ����ֵ: �鿴ö���� ret_code_e ��
 */
ret_code_e evm_porting_ServerSocketClose(evm_handle handle);
/*
 * ������: evm_porting_ClientSocketOpen
 * ����˵��: ����һ���µ�socket������ϵͳע��һ���µ�ͨ�Ŷ˿ڣ���Ϊ�ͻ��ˡ�
 * �������:
 * 		host: ��������socketͨ�ŵ�����������
 * 		port: �˿ںš�
 *      type: ����Э�����͡�
 *      bBlock�� �Ƿ�Ϊ������
 * �������:
 * 		phSocket: ��������ɹ���socket��ͨ�Ŷ˿ڣ��ľ����д�� phSocket���ڴ档
 * ����ֵ: �鿴ö���� ret_code_e ��
 */
ret_code_e evm_porting_ClientSocketOpen(evm_handle* phSocket, evm_s8 const* host, evm_u16 port, evm_porting_socketType_e type, evm_bool bBblock);
/*
 * ������: evm_porting_ClientSocketClose
 * ����˵��: �ر�һ��socket������ϵͳע��һ��ͨ�Ŷ˿ڡ�
 * �������:
 * 		handle: Ҫ�رյ�socket��ͨ�Ŷ˿ڣ����ļ������
 * �������:
 * 		�ޡ�
 * ����ֵ: �鿴ö���� ret_code_e ��
 */
ret_code_e evm_porting_ClientSocketClose(evm_handle handle);
/*
 * ������: evm_porting_SocketRecv
 * ����˵��: ��һ��socket��ͨ�Ŷ˿ڣ��н������ݡ�
 * �������:
 * 		handle: Ҫ�������ݵ�socket��ͨ�Ŷ˿ڣ����ļ������
 * 		size: �������ݵĴ�С��
 * �������:
 * 		data: �Ѵ�socket��ͨ�Ŷ˿ڣ����ܵ�������д��data���ڴ��С�
 * ����ֵ: ����ʵ�ʽ��յ����ݵĳ��ȣ����ɹ�����-1��
 */
evm_s32 evm_porting_SocketRecv(evm_handle handle, evm_s8* data, evm_s32 size);
/*
 * ������: evm_porting_SocketSend
 * ����˵��: �����õ�socket��ͨ�Ŷ˿ڣ���д��size��С�����ݡ�
 * �������:
 * 		data: Ҫд�����ݵ�socket��ͨ�Ŷ˿ڣ������ݵ��ڴ��ַ��
 * 		size: д�����ݵĴ�С��
 * �������:
 * 		handle: ����д��socket��ͨ�Ŷ˿ڣ����ļ������
 * ����ֵ: ����ʵ��д������ݵĳ��ȣ����ɹ�����-1��
 */
evm_s32 evm_porting_SocketSend(evm_handle handle, evm_s8* data, evm_s32 size);

#endif /* EVM_PORTING_SOCKET_H_ */
