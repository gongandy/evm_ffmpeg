/*
 * evm_porting_nim.h
 * Copyright(C) EnRich DTV Group Co.,Ltd.
 *
 * Description: 
 *
 * Authors: 沈辉<shenhui@evmtv.com>
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
    evm_u32 nimId;                                       //tuner索引，默认0、1、2
    evm_u32 u32Snr; 						//信噪比
    evm_u32 u32Quality;  					//质量
    evm_u32 u32Strength;					//信号强度
    evm_u32 u32Level;						//电平
    evm_u32 u32Ber[3];						//误码率
                                    		//pu32BER[0]:误码率底数的整数部分
                                    		//pu32BER[1]:误码率底数的小数部分乘以1000
                                    		//pu32BER[2]:误码率指数部分取绝对值
} evm_porting_nim_signalInfo_t;

typedef struct
{
    evm_u32 u32StartFreq;                   //单个采样的起始频率，单位hz
    evm_u32 u32EndFreq;                     //单个采样的结束频率，单位hz
    evm_s32 s32Level;                       //单个采样的电平，单位为0.001dBm
} evm_porting_nim_fullbandSingalInfo_t;


typedef struct
{
    evm_u32 nimId;
    evm_bool lockstatus;                            // 1成功，other失败
    evm_u32 fre; 							//khz
    evm_u32 Symbol;                                 //单位不是k哦
    evm_porting_nim_modulation_e Modulate;
} evm_porting_nim_tunnerInfo_t;

/*
 * 获取全频段信号的回调函数
 * status: 获取信号成功与否，EVM_SUCCESS表示成功，否则表示失败
 * sampleCount: 信号的采样个数
 * pstInfo: 信号的采样信息
 * private: 透传evm_porting_nim_GetFullBandSignalInfo传入的private
 * 返回值: 无
 */
typedef void evm_porting_nim_getFullbandSiganlInfo_cb(evm_s32 status, evm_u32 sampleCount, evm_porting_nim_fullbandSingalInfo_t *pstInfo, void* private);

/**
 * Function: evm_porting_nim_Init
 * Description: 对tuner模块的初始化，将所有tuner设备初始化好，并输出tuner个数
 * Input:  
 *          none
 * Output: 
 *          pstInitOutParam:返回tuner个数。上层以序号0、1、2操作tuner设备。
 *                      tuner与dmx一一对应，tuner 0 对应dmx 0 ；tuner 1 对应dmx 1 ...
 * Return: 0:SUCCESS , other is Fail
 */
ret_code_e evm_porting_nim_Init(evm_porting_nim_initOutParam_t *pstInitOutParam);

/**
 * Function: evm_porting_nim_DeInit
 * Description: 对tuner模块的去初始化
 * Input:  
 * 				NimId:tuner id索引号，为0xFFFFFFFF时，去初始化所有tuner
 *				
 * Output: none
 * Return: 0:SUCCESS , other is Fail
 */
ret_code_e evm_porting_nim_DeInit(evm_u32 NimDev);

/**
 * Function: evm_porting_nim_GetNum
 * Description: 获取tuner个数
 * Input:
 * 			none
 *
 * Output:
 * 			u32NimNum 返回tuner个数。
 * Return: 0:SUCCESS , other is Fail
 */
ret_code_e evm_porting_nim_GetNum(evm_u32 *u32NimNum);

/**
 * Function: evm_porting_nim_ChannelChange
 * Description: 锁定指定的频率参数
 * Input: 
 *          NimId:指定操作的tuner索引
 *          Freq 频率 (KHZ)259000
 *          Symbol:符号率 K 6875
 *          Modulate 调制方式
 * Output: none
 * Return: 0:SUCCESS , other is Fail
 */
ret_code_e evm_porting_nim_ChannelChange(evm_u32 NimId, evm_u32 Freq, evm_u32 Symbol, evm_porting_nim_modulation_e Modulate);

/**
 * Function: evm_porting_nim_GetLockFlag
 * Description: 获取当前频率的锁定状态
 * Input:  
 *          NimId:指定操作的tuner索引
 *          LockFlag:锁定状态，1为锁定，0为非锁定
 *				
 * Output: none
 * Return: 0:SUCCESS , other is Fail
 */
ret_code_e evm_porting_nim_GetLockFlag(evm_u32 NimId, evm_u8 *LockFlag);

/**
 * Function: evm_porting_nim_GetSignalInfo
 * Description: 获取当前信号的情况
 * Input:  
 *          NimId:指定操作的tuner索引
 *          LockFlag:锁定状态，1为锁定，0为非锁定
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
 *          NimId:指定操作的tuner索引
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
 * Description: 异步获取指定频段的信号电平等信息，当请求的数据准备好后，底层调用传入的callback函数通知上层
 * Input:
 *          startFreq: 起始频率，单位hz
 *          endFreq: 结束频率，单位hz
 *          sampleCount: 采样个数，底层应该根据sampleCount平分startFreq至endFreq对应频率进行采样
 *          pcbCallback: 当请求的数据准备好后，底层调用通知上层
 *          private: 需要在pcbCallback透传的私有数据
 * Output:
 *      none
 * Return: 0:SUCCESS , other is Fail
 */
ret_code_e evm_porting_nim_GetFullbandSignalInfo(evm_u32 startFreq, evm_u32 endFreq, evm_u32 sampleCount, \
        evm_porting_nim_getFullbandSiganlInfo_cb pcbCallback, void* private);



//////////////////以下接口之针对需要使用窄带的情况下使用///////////////////////////
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

//从网卡读取需要发送的tcp/ip数据
evm_s32 evm_porting_nim_ReadTcpIpDataToNetDevice(evm_s8 s8arrEthName[16], evm_u8 *pu8Data, evm_u32 u32MaxLength, evm_u32 u32Timeout);

//向网卡写入接收到的tcp/ip数据
evm_s32 evm_porting_nim_WriteTcpIpDataToNetDevice(evm_s8 s8arrEthName[16], evm_u8 *pu8Data, evm_u32 u32Length, evm_u32 u32Timeout);

ret_code_e evm_porting_nim_OpenSerialPort(evm_porting_nim_serialPortCreateParam_t *pstParam);

ret_code_e evm_porting_nim_CloseSerialPort();

evm_s32 evm_porting_nim_WriteDataToSerialPort(evm_s32 uart_fd, evm_u8 *data, evm_s32 len, evm_s32 *ok_len, evm_s32 timeout);

evm_s32 evm_porting_nim_ReadDataFromSerialPort(evm_s32 uart_fd, evm_u8 *data, evm_s32 len, evm_s32 *ok_len, evm_s32 timeout);

#endif /* EVM_PORTING_NIM_H_ */
