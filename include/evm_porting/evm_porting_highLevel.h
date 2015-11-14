/*
 * evm_porting_highLevel.h
 * Copyright(C) EnRich DTV Group Co.,Ltd.
 *
 * Description: ���ļ���������ĳЩ��������£����ǻ���û�����ʵ�ֵĸ߲�ӿڣ����粥�ŵ�
 *
 * Authors: ���<shenhui@evmtv.com>
 */

#ifndef EVM_PORTING_HIGHLEVEL_H_
#define EVM_PORTING_HIGHLEVEL_H_


typedef enum
{
    EVM_PORTING_HIGHLEVEL_PLAYAV_ATTR_FREQ_SERVICE_E = 0,  	//Ƶ���Լ�serviceid
    EVM_PORTING_HIGHLEVEL_PLAYAV_ATTR_FREQ_PMTPID_E,  		//Ƶ���Լ�pmtPid
    EVM_PORTING_HIGHLEVEL_PLAYAV_ATTR_TS_SERVICE_E,  		//tsid�Լ�service id
    EVM_PORTING_HIGHLEVEL_PLAYAV_ATTR_SERVICE_E  			//����serviceid
} evm_porting_highLevel_playAv_attr_e;

typedef enum
{
    EVM_PORTING_HIGHLEVEL_MOD_QAM16_E = 0,
    EVM_PORTING_HIGHLEVEL_MOD_QAM32_E,
    EVM_PORTING_HIGHLEVEL_MOD_QAM64_E,
    EVM_PORTING_HIGHLEVEL_MOD_QAM128_E,
    EVM_PORTING_HIGHLEVEL_MOD_QAM256_E,

    EVM_PORTING_HIGHLEVEL_MOD_DEFAULT_E  					//Ĭ�ϵ��Է�ʽ
} evm_porting_highLevel_mod_e;

typedef struct _evm_porting_highLevl_playAV_attr_t_
{
    evm_porting_highLevel_playAv_attr_e mode;

    struct
    {
        evm_u32 freq;  										//KHZ
        evm_s32 symbol;  									//K��-1ΪĬ�ϵķ�����
        evm_porting_highLevel_mod_e qam;
    } freq;

    evm_u32 networkId;
    evm_u32 tsId;
    evm_u32 pmtPid;
    evm_u32 serviceId;
} evm_porting_highLevl_playAV_attr_t;

/*
 * Function: evm_porting_highLevel_StopAV
 * Description: ��������Ƶ��Ŀ
 * Input:
 *      attr: ���Ž�Ŀ��Ӧ����Ϣ
 * Output:
 * Return: see enum ret_code_e
 */
ret_code_e evm_porting_highLevel_PlayAV(evm_porting_highLevl_playAV_attr_t* attr);

/*
 * Function: evm_porting_highLevel_StopAV
 * Description: ֹͣ����Ƶ���ţ�����Ƶ������λ����������ֹͣ��ǰ��ֱ����VOD���ŵȡ�
 * Input:
 *      none
 * Output:
 * Return: see enum ret_code_e
 */
ret_code_e evm_porting_highLevel_StopAV();

/*
	Fuction		:	evm_porting_highLevel_Tune
	Description	:	notify stb to tune frequency
	Parameters	:	evm_u8* str, tune string like "dvb://1.C.4B3"
					int timeout, timeout of this operating.
	Return		:	ret_code_e
*/
ret_code_e evm_porting_highLevel_Tune(evm_u8* str, int timeout);
/*
	Fuction		:	evm_porting_highLevel_SetDVBPosition
	Description	:	notify stb DVB playing rect.
	Parameters	:	evm_rect_t* rect, rectangle structure of video window.
	Return		:	ret_code_e
*/
ret_code_e evm_porting_highLevel_SetDVBPosition(evm_rect_t* rect);
/*
	Fuction		:	evm_porting_highLevel_PlayOrStopAV
	Description	:	notify stb to play or stop av
	Parameters	:	evm_bool isPlay, true to play and false to stop
	Return		:	ret_code_e
*/
ret_code_e evm_porting_highLevel_PlayOrStopAV(evm_bool isPlay);

#endif /* EVM_PORTING_HIGHLEVEL_H_ */
