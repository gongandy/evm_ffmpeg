/*
 * evm_porting_nim.h
 * Copyright(C) EnRich DTV Group Co.,Ltd.
 *
 * Description: 
 *
 * Authors: ���<shenhui@evmtv.com>
 */

#ifndef __EVM_PORTING_NIM_H__
#define __EVM_PORTING_NIM_H__

#include "../../evm_typedef.h"

typedef enum
{
    EVM_NIM_MODU_QAM16 = 1,
    EVM_NIM_MODU_QAM32,
    EVM_NIM_MODU_QAM64,
    EVM_NIM_MODU_QAM128,
    EVM_NIM_MODU_QAM256,
} evm_porting_nim_modulation_e;

typedef struct
{
	evm_u32 nimNum;
}evm_porting_nim_initOutParam_t;

typedef struct __evm_porting_nim_signalInfo_t
{
    evm_u32 nimId;                                       //tuner������Ĭ��0��1��2
    evm_u32 u32Snr; 						//�����
    evm_u32 u32Quality;  					//����
    evm_u32 u32Strength;					//�ź�ǿ��
    evm_u32 u32Level;						//��ƽ
    evm_u32 u32Ber[3];						//������
                                    		//pu32BER[0]:�����ʵ�������������
                                    		//pu32BER[1]:�����ʵ�����С�����ֳ���1000
                                    		//pu32BER[2]:������ָ������ȡ����ֵ
} evm_porting_nim_signalInfo_t;

typedef struct
{
    evm_u32 u32StartFreq;                   //������������ʼƵ�ʣ���λhz
    evm_u32 u32EndFreq;                     //���������Ľ���Ƶ�ʣ���λhz
    evm_s32 s32Level;                       //���������ĵ�ƽ����λΪ0.001dBm
} evm_porting_nim_fullbandSingalInfo_t;


typedef struct
{
    evm_u32 nimId;
    evm_bool lockstatus;                            // 1�ɹ���otherʧ��
    evm_u32 fre; 							//khz
    evm_u32 Symbol;                                 //��λ����kŶ
    evm_porting_nim_modulation_e Modulate;
} evm_porting_nim_tunnerInfo_t;

/*
 * ��ȡȫƵ���źŵĻص�����
 * status: ��ȡ�źųɹ����EVM_SUCCESS��ʾ�ɹ��������ʾʧ��
 * sampleCount: �źŵĲ�������
 * pstInfo: �źŵĲ�����Ϣ
 * private: ͸��evm_porting_nim_GetFullBandSignalInfo�����private
 * ����ֵ: ��
 */
typedef void evm_porting_nim_getFullbandSiganlInfo_cb(evm_s32 status, evm_u32 sampleCount, evm_porting_nim_fullbandSingalInfo_t *pstInfo, void* private);

/**
 * Function: evm_porting_nim_Init
 * Description: ��tunerģ��ĳ�ʼ����������tuner�豸��ʼ���ã������tuner����
 * Input:  
 *          none
 * Output: 
 *          pstInitOutParam:����tuner�������ϲ������0��1��2����tuner�豸��
 *                      tuner��dmxһһ��Ӧ��tuner 0 ��Ӧdmx 0 ��tuner 1 ��Ӧdmx 1 ...
 * Return: 0:SUCCESS , other is Fail
 */
ret_code_e evm_porting_nim_Init(evm_porting_nim_initOutParam_t *pstInitOutParam);

/**
 * Function: evm_porting_nim_DeInit
 * Description: ��tunerģ���ȥ��ʼ��
 * Input:  
 * 				NimId:tuner id�����ţ�Ϊ0xFFFFFFFFʱ��ȥ��ʼ������tuner
 *				
 * Output: none
 * Return: 0:SUCCESS , other is Fail
 */
ret_code_e evm_porting_nim_DeInit(evm_u32 NimDev);

/**
 * Function: evm_porting_nim_GetNum
 * Description: ��ȡtuner����
 * Input:
 * 			none
 *
 * Output:
 * 			u32NimNum ����tuner������
 * Return: 0:SUCCESS , other is Fail
 */
ret_code_e evm_porting_nim_GetNum(evm_u32 *u32NimNum);

/**
 * Function: evm_porting_nim_ChannelChange
 * Description: ����ָ����Ƶ�ʲ���
 * Input: 
 *          NimId:ָ��������tuner����
 *          Freq Ƶ�� (KHZ)259000
 *          Symbol:������ K 6875
 *          Modulate ���Ʒ�ʽ
 * Output: none
 * Return: 0:SUCCESS , other is Fail
 */
ret_code_e evm_porting_nim_ChannelChange(evm_u32 NimId, evm_u32 Freq, evm_u32 Symbol, evm_porting_nim_modulation_e Modulate);

/**
 * Function: evm_porting_nim_GetLockFlag
 * Description: ��ȡ��ǰƵ�ʵ�����״̬
 * Input:  
 *          NimId:ָ��������tuner����
 *          LockFlag:����״̬��1Ϊ������0Ϊ������
 *				
 * Output: none
 * Return: 0:SUCCESS , other is Fail
 */
ret_code_e evm_porting_nim_GetLockFlag(evm_u32 NimId, evm_u8 *LockFlag);

/**
 * Function: evm_porting_nim_GetSignalInfo
 * Description: ��ȡ��ǰ�źŵ����
 * Input:  
 *          NimId:ָ��������tuner����
 *          LockFlag:����״̬��1Ϊ������0Ϊ������
 *				
 * Output:
 *      out_pstNimInfo
 * Return: 0:SUCCESS , other is Fail
 */
ret_code_e evm_porting_nim_GetSignalInfo(evm_u32 NimId, evm_porting_nim_signalInfo_t *out_pstSiganlInfo);


/**
 * Function: evm_porting_nim_GetTunInfo
 * Description: ??TUNER?????;
 * Input:  
 *          NimId:ָ��������tuner����
 *          info: ???????;
 *				
 * Output:     
 *      out_pstTunInfo
 *      
 * Return: 0:SUCCESS , other is Fail
 */
ret_code_e evm_porting_nim_GetTunnerInfo(evm_u32 NimId, evm_porting_nim_tunnerInfo_t *info);

/**
 * Function: evm_porting_nim_GetFullbandSignalInfo
 * Description: �첽��ȡָ��Ƶ�ε��źŵ�ƽ����Ϣ�������������׼���ú󣬵ײ���ô����callback����֪ͨ�ϲ�
 * Input:
 *          startFreq: ��ʼƵ�ʣ���λhz
 *          endFreq: ����Ƶ�ʣ���λhz
 *          sampleCount: �����������ײ�Ӧ�ø���sampleCountƽ��startFreq��endFreq��ӦƵ�ʽ��в���
 *          pcbCallback: �����������׼���ú󣬵ײ����֪ͨ�ϲ�
 *          private: ��Ҫ��pcbCallback͸����˽������
 * Output:
 *      none
 * Return: 0:SUCCESS , other is Fail
 */
ret_code_e evm_porting_nim_GetFullbandSignalInfo(evm_u32 startFreq, evm_u32 endFreq, evm_u32 sampleCount, \
        evm_porting_nim_getFullbandSiganlInfo_cb pcbCallback, void* private);



//////////////////���½ӿ�֮�����Ҫʹ��խ���������ʹ��///////////////////////////
typedef enum
{
    EVM_PORTING_NIM_NARROWBANDTYPE_LABCABLE_E = 0,
    EVM_PORTING_NIM_NARROWBANDTYPE_OVT_E,

    EVM_PORTING_NIM_NARROWBANDTYPE_COUNT_E
} evm_porting_nim_narrowBandType_e;

typedef struct
{
    //param in
    evm_u32 u32BitRate;
} evm_porting_nim_serialPortCreateParam_t;

ret_code_e evm_porting_nim_GetNarrowBandType(evm_porting_nim_narrowBandType_e *peType);

ret_code_e evm_porting_nim_CreateVirtualNetDevice(evm_u8 u8Mac[6], evm_s8 out_s8arrEthName[16]);

ret_code_e evm_porting_nim_DestroyVirtualNetDevice(evm_u8 u8Mac[6]);

//��������ȡ��Ҫ���͵�tcp/ip����
evm_s32 evm_porting_nim_ReadTcpIpDataToNetDevice(evm_s8 s8arrEthName[16], evm_u8 *pu8Data, evm_u32 u32MaxLength, evm_u32 u32Timeout);

//������д����յ���tcp/ip����
evm_s32 evm_porting_nim_WriteTcpIpDataToNetDevice(evm_s8 s8arrEthName[16], evm_u8 *pu8Data, evm_u32 u32Length, evm_u32 u32Timeout);

ret_code_e evm_porting_nim_OpenSerialPort(evm_porting_nim_serialPortCreateParam_t *pstParam);

ret_code_e evm_porting_nim_CloseSerialPort();

evm_s32 evm_porting_nim_WriteDataToSerialPort(evm_s32 uart_fd, evm_u8 *data, evm_s32 len, evm_s32 *ok_len, evm_s32 timeout);

evm_s32 evm_porting_nim_ReadDataFromSerialPort(evm_s32 uart_fd, evm_u8 *data, evm_s32 len, evm_s32 *ok_len, evm_s32 timeout);

#endif /* EVM_PORTING_NIM_H_ */
