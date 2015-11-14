/*
 * evm_porting_avplayer.h
 * Copyright(C) EnRich DTV Group Co.,Ltd.
 *
 * Description: 
 *
 * Authors: ���<shenhui@evmtv.com>
 */

#ifndef EVM_PORTING_AVPLAYER_H_
#define EVM_PORTING_AVPLAYER_H_

#include "evm_typedef.h"

///////////////player///////////////
typedef enum
{
	EVM_PORTING_AV_ENBLE_AUDIO_CHANNEL_E = 0,		//ʹ����Ƶͨ��
	EVM_PORTING_AV_ENBLE_VIDEO_CHANNEL_E,			//ʹ����Ƶͨ��
	EVM_PORTING_AV_ENBLE_AV_CHANNEL_E,				//ʹ������Ƶͨ��

	EVM_PORTING_AV_ENBLE_AV_CHANNEL_END
}evm_porting_av_enableChannel_e;
typedef enum
{
	EVM_PORTING_AV_STREAM_INPUT_TYPE_RAM_TS_E = 0, 				//�ڴ濽����ʽts��
	EVM_PORTING_AV_STREAM_INPUT_TYPE_RAM_ES_E, 					//�ڴ濽����ʽes��
	EVM_PORTING_AV_STREAM_INPUT_TYPE_DEMUX_TS_E, 				//demux����ts��

	EVM_PORTING_AV_STREAM_INPUT_TYPE_COUNT_E
} evm_porting_av_streamInputType_e;

typedef enum
{
    EVM_PORTING_AV_STREAM_TYPE_RESERVED_E       = 0x00,     //     ITU-T | ISO/IEC Reserved
    EVM_PORTING_AV_STREAM_TYPE_MPEG1_VID_E      = 0x01,     //     ISO/IEC 11172-2 Video
    EVM_PORTING_AV_STREAM_TYPE_MPEG2_VID_E      = 0x02,     //     ITU-T Rec. H.262 | ISO/IEC 13818-2 Video or ISO/IEC 11172-2 constrained parameter video stream
    EVM_PORTING_AV_STREAM_TYPE_MPEG1_AUD_E      = 0x03,     //     ISO/IEC 11172-3 Audio
    EVM_PORTING_AV_STREAM_TYPE_MPEG2_AUD_E      = 0x04,     //     ISO/IEC 13818-3 Audio
    //0x05     ITU-T Rec. H.222.0 | ISO/IEC 13818-1 private_sections
    EVM_PORTING_AV_STREAM_TYPE_PRIVATRE_PES_E   = 0x6,      //0x06     ITU-T Rec. H.222.0 | ISO/IEC 13818-1 PES packets containing private data
    //0x07     ISO/IEC 13522 MHEG
    //0x08     ITU-T Rec. H.222.0 | ISO/IEC 13818-1 Annex A DSM-CC
    //0x09     ITU-T Rec. H.222.1
    //0x0A     ISO/IEC 13818-6 type A
    //0x0B     ISO/IEC 13818-6 type B
    //0x0C     ISO/IEC 13818-6 type C
    //0x0D     ISO/IEC 13818-6 type D
    //0x0E     ITU-T Rec. H.222.0 | ISO/IEC 13818-1 auxiliary
    EVM_PORTING_AV_STREAM_TYPE_ADST_AUD_E   = 0x0F,     //     ISO/IEC 13818-7 Audio with ADTS transport syntax
    EVM_PORTING_AV_STREAM_TYPE_MPEG4_VID_E      = 0x10,     //     ISO/IEC 14496-2 Visual
    EVM_PORTING_AV_STREAM_TYPE_AAC_AUD_E        = 0x11,     //     ISO/IEC 14496-3 Audio with the LATM transport syntax as defined in ISO/IEC 14496-3/Amd.1
    //0x12     ISO/IEC 14496-1 SL-packetized stream or FlexMux stream carried in PES packets
    //0x13     ISO/IEC 14496-1 SL-packetized stream or FlexMux stream carried in ISO/IEC 14496_sections
    //0x14     ISO/IEC 13818-6 Synchronized Download Protocol
    //0x15     Metadata carried in PES packets
    //0x16     Metadata carried in metadata_sections
    //0x17     Metadata carried in ISO/IEC 13818-6 Data Carousel
    //0x18     Metadata carried in ISO/IEC 13818-6 Object Carousel
    //0x19     Metadata carried in ISO/IEC 13818-6 Synchronized Download Protocol
    //0x1A     IPMP stream (defined in ISO/IEC 13818-11, MPEG-2 IPMP)
    EVM_PORTING_AV_STREAM_TYPE_H264_VID_E       = 0x1B,     //     AVC video stream as defined in ITU-T Rec. H.264 | ISO/IEC 14496-10 Video
    //0x1C     ISO/IEC 14496-3 Audio, without using any additional transport syntax, such as DST, ALS and SLS
    //0x1D     ISO/IEC 14496-17 Text
    //0x1E     Auxiliary video stream as defined in ISO/IEC 23002-3
    //0x1F-0x7E ITU-T Rec. H.222.0 | ISO/IEC 13818-1 Reserved
    //0x7F     IPMP stream
    EVM_PORTING_AV_STREAM_TYPE_AC3_AUD_E        = 0x81,
    EVM_PORTING_AV_STREAM_TYPE_DTS_AUD_E        = 0x82,
    EVM_PORTING_AV_STREAM_TYPE_PCM_AUD_E        = 0x100,
} evm_porting_av_streamType_e;

typedef enum
{
	EVM_PORTING_AV_SYNC_REF_NONE_E = 0, 		    //���ɲ���
	EVM_PORTING_AV_SYNC_REF_AUD_E, 					//����ƵΪ׼
	EVM_PORTING_AV_SYNC_REF_VID_E, 					//����ƵΪ׼
	EVM_PORTING_AV_SYNC_REF_PCR_E, 					//��PCRΪ׼	
	EVM_PORTING_AV_SYNC_REF_QUICK_OUTPUT_E,         //�������,��mstartоƬ��֡���뷽ʽ
	EVM_PORTING_AV_SYNC_REF_COUNT_E
} evm_porting_av_syncRef_e;

typedef enum
{
    EVM_PORTING_AV_AUD_SAMPLE_RATE_8K_E    = 8000,   /**<CNcomment: 8K����Ƶ�� */
    EVM_PORTING_AV_AUD_SAMPLE_RATE_11K_E   = 11025,  /**<CNcomment: 11.025K����Ƶ�� */
    EVM_PORTING_AV_AUD_SAMPLE_RATE_12K_E   = 12000,  /**<CNcomment: 12K����Ƶ�� */
    EVM_PORTING_AV_AUD_SAMPLE_RATE_16K_E   = 16000,  /**<CNcomment: 16K����Ƶ�� */
    EVM_PORTING_AV_AUD_SAMPLE_RATE_22K_E   = 22050,  /**<CNcomment: 22.050K����Ƶ�� */
    EVM_PORTING_AV_AUD_SAMPLE_RATE_24K_E   = 24000,  /**<CNcomment: 24K����Ƶ�� */
    EVM_PORTING_AV_AUD_SAMPLE_RATE_32K_E   = 32000,  /**<CNcomment: 32K����Ƶ�� */
    EVM_PORTING_AV_AUD_SAMPLE_RATE_44K_E   = 44100,  /**<CNcomment: 44.1K����Ƶ�� */
    EVM_PORTING_AV_AUD_SAMPLE_RATE_48K_E   = 48000,  /**<CNcomment: 48K����Ƶ�� */
    EVM_PORTING_AV_AUD_SAMPLE_RATE_88K_E   = 88200,  /**<CNcomment: 88.2K����Ƶ�� */
    EVM_PORTING_AV_AUD_SAMPLE_RATE_96K_E   = 96000,  /**<CNcomment: 96K����Ƶ�� */
    EVM_PORTING_AV_AUD_SAMPLE_RATE_176K_E  = 176400,     /**<CNcomment: 176K����Ƶ�� */
    EVM_PORTING_AV_AUD_SAMPLE_RATE_192K_E  = 192000,   /**<CNcomment: 192K����Ƶ�� */

    EVM_PORTING_AV_AUD_SAMPLE_RATE_BUTT_E
} evm_porting_av_audSampleRate_e;

typedef enum
{
    EVM_PORTING_AV_AUD_BIT_DEPTH_8_E  = 8,    /**< 8λ����λ��  */
    EVM_PORTING_AV_AUD_BIT_DEPTH_16_E = 16,   /**< 16λ����λ�� */
    EVM_PORTING_AV_AUD_BIT_DEPTH_18_E = 18,   /**< 18λ����λ�� */
    EVM_PORTING_AV_AUD_BIT_DEPTH_20_E = 20,   /**< 20λ����λ�� */
    EVM_PORTING_AV_AUD_BIT_DEPTH_24_E = 24,   /**< 24λ����λ�� */
    EVM_PORTING_AV_AUD_BIT_DEPTH_32_E = 32,   /**< 32λ����λ�� */

    EVM_PORTING_AV_AUD_BIT_DEPTH_BUTT
} evm_porting_av_audBitDepth_e;

typedef enum
{
    EVM_PORTING_AV_PLAYER_ATTR_ID_STREAM_INPUT_TYPE_E = 0, 	    //�����ͣ���evm_avplayerStreamType_e
    EVM_PORTING_AV_PLAYER_ATTR_ID_ADEC_TYPE_E, 					//��Ƶ�����ʽ����evm_porting_av_streamType_e
    EVM_PORTING_AV_PLAYER_ATTR_ID_VDEC_TYPE_E, 					//��Ƶ�����ʽ����evm_porting_av_streamType_e
    EVM_PORTING_AV_PLAYER_ATTR_ID_AUD_PID_E, 					//��Ƶpid
    EVM_PORTING_AV_PLAYER_ATTR_ID_VID_PID_E, 					//��Ƶpid
    EVM_PORTING_AV_PLAYER_ATTR_ID_PCR_PID_E, 					//pcr pid
    EVM_PORTING_AV_PLAYER_ATTR_ID_SYNC_REF_E, 					//ͬ��ģʽ
    EVM_PORTING_AV_PLAYER_ATTR_ID_AUD_SAMPLE_RATE_E,             //��Ƶ�����ʣ���evm_porting_av_audSampleRate_e
    EVM_PORTING_AV_PLAYER_ATTR_ID_AUD_BIT_DEPTH_E,               //��Ƶ������ȣ���evm_porting_av_audBitDepth_e
    EVM_PORTING_AV_PLAYER_ATTR_ID_OUTPUTMODE_E,			//���ͨ��ѡ��Ϊ�������״̬�£�start��Ч��
                                                                                                            //��������Ϊ�����Ҫ��ײ����ض�Ӧ�Ĳ�����,
                                                                                                            //��evm_porting_av_playerOutputMode_e

	EVM_PORTING_AV_PLAYER_ATTR_ID_SYNC_COUNT_E
} evm_porting_av_playerAttrId_e;

typedef enum
{
    EVM_PORTING_AV_PLAYER_BUF_TYPE_TS_E = 0,    //ts��
    EVM_PORTING_AV_PLAYER_BUF_TYPE_AUD_ES_E,    //��Ƶes��
    EVM_PORTING_AV_PLAYER_BUF_TYPE_VID_ES_E,    //��Ƶes��

    EVM_PORTING_AV_PLAYER_BUF_TYPE_COUNT_E
} evm_porting_av_playerBufType_e;

typedef enum
{
    EVM_PORTING_AV_PLAYER_ONOFF_MODE_ALL_E = 0,  		//����Ƶȫ���򿪻��߹ر�
    EVM_PORTING_AV_PLAYER_ONOFF_MODE_VID_E,  			//ֻ�򿪻��߹ر���Ƶ
    EVM_PORTING_AV_PLAYER_ONOFF_MODE_AUD_E,  			//ֻ�򿪻��߹ر���Ƶ

    EVM_PORTING_AV_PLAYER_ONOFF_MODE_COUNT_E
} evm_porting_av_playerOnOffMode_e;

typedef enum
{
    EVM_PORTING_AV_PLAYER_OUTPUT_MODE_ALL_E = 0,  		//����Ƶͬʱ���
    EVM_PORTING_AV_PLAYER_OUTPUT_MODE_VID_E,  			//ֻ�����Ƶ
    EVM_PORTING_AV_PLAYER_OUTPUT_MODE_AUD_E,  			//ֻ�����Ƶ
    EVM_PORTING_AV_PLAYER_OUTPUT_MODE_NONE_E,			//����Ƶ�������

    EVM_PORTING_AV_PLAYER_OUTPUT_MODE_COUNT_E
} evm_porting_av_playerOutputMode_e;

typedef enum
{
    EVM_PORTING_AV_PLAYER_EVENT_TYPE_START_DECODE_E = 0,     //�������յ�����Ƶ���ݲ���ʼ����
    EVM_PORTING_AV_PLAYER_EVENT_TYPE_NO_STREAM_E,            //��ý������

    //�������ļ����ŵ��¼�֪ͨ���ͣ����ڷ��ļ����ŵĲ���Ҫ���������¼�����
    EVM_PROTING_AV_FILE_PLAYER_EVENT_STATE_E,                //param1:״̬�仯���״̬��param2:Ԥ��
    EVM_PROTING_AV_FILE_PLAYER_EVENT_BOF_E,                  //param1:Ԥ����param2:Ԥ��
    EVM_PROTING_AV_FILE_PLAYER_EVENT_EOF_E,                  //param1:Ԥ����param2:Ԥ��
    EVM_PROTING_AV_FILE_PLAYER_EVENT_PLAY_PROGRESS_E,        //param1:��ǰ���Ž���0-100��param2:��ǰ����ʱ��ms
    EVM_PROTING_AV_FILE_PLAYER_EVENT_DOWNLOAD_PROGRESS_E,    //param1:��ǰ���ؽ���0-100��param2:��ǰ����ʱ��ms
    EVM_PROTING_AV_FILE_PLAYER_EVENT_SEEK_FIN_E,             //param1:Ԥ����param2:Ԥ��
    EVM_PROTING_AV_FILE_PLAYER_EVENT_BUFFER_EMPTY_E,         //��ý�建�����ݣ�param1:Ԥ����param2:Ԥ��
    EVM_PROTING_AV_FILE_PLAYER_EVENT_BUFFER_ENOUGH_E,        //���������㹻���ţ�param1:Ԥ����param2:Ԥ��
    EVM_PROTING_AV_FILE_PLAYER_EVENT_ALL_BUFFERED_E,         //ȫ�����������param1:Ԥ����param2:Ԥ��
    EVM_PROTING_AV_FILE_PLAYER_EVENT_ERROR_E,                //param1:Ԥ����param2:Ԥ��

    EVM_PORTING_AV_PLAYER_EVENT_TYPE_COUNT_E
} evm_porting_av_playerEventType_e;


typedef void (*evm_porting_av_playerEvent_cb)(evm_handle hPlayer, evm_porting_av_playerEventType_e eType, evm_s32 param1, evm_s32 param2);

///////////////audio output///////////////
typedef enum
{
    EVM_PORTING_AV_SND_TRACK_MODE_STEREO_E = 0, 	/**<������*/
    EVM_PORTING_AV_SND_TRACK_MODE_LEFT_E,			/**<������*/
    EVM_PORTING_AV_SND_TRACK_MODE_RIGHT_E,  		/**<������*/
    EVM_PORTING_AV_SND_TRACK_MODE_MONO_E ,          /**<�����*/

    EVM_PORTING_AV_SND_TRACK_MODE_COUNT_E
} evm_porting_av_sndTrackMode_e;

//spdif��hdmi�Ƚӿڵ���Ƶ�����ʽ
typedef enum
{
    EVM_PROTING_AV_SND_PASS_MODE_RAW_E,  			//ԭʼ����
    EVM_PROTING_AV_SND_PASS_MODE_PCM_E,  			//��������
    EVM_PROTING_AV_SND_PASS_MODE_OFF_E,  			//�ر�

    EVM_PROTING_AV_SND_PASS_MODE_COUNT_E
} evm_porting_av_sndPassMode_e;

typedef enum
{
    EVM_PORTING_AV_AO_ATTR_ID_MUTE_E = 0,               //��hPlayerΪ-1����ʾȫ�־�����������ʾָ������������
    EVM_PORTING_AV_AO_ATTR_ID_VOLUME_E,                 //��hPlayerΪ-1����ʾȫ��������������ʾָ������������
    EVM_PORTING_AV_AO_ATTR_ID_TRACK_MODE_E,         //��hPlayerΪ-1����ʾȫ������ģʽ����������ֵ
    EVM_PORTING_AV_AO_ATTR_ID_PASS_MODE_E,           //hPlayer����Ϊ-1����ʾָ����������͸��ģʽ���ο�evm_porting_av_sndPassMode_e

    //special
    EVM_PORTING_AV_AO_ATTR_ID_SPEAKER_MUTE_E,       //��hPlayerΪ-1����ʾȫ�ֻ�Ͳ������������ʾָ����������Ͳ����
    EVM_PORTING_AV_AO_ATTR_ID_SPEAKER_VOLUME_E,     //��hPlayerΪ-1����ʾȫ�ֻ�Ͳ������������ʾָ����������Ͳ����

    EVM_PORTING_AV_AO_ATTR_ID_COUNT_E   
} evm_porting_av_aoAttrId_e;


///////////////video output///////////////
typedef enum
{
    EVM_PORTING_AV_DISP_FMT_1920P_E = 0,
    EVM_PORTING_AV_DISP_FMT_1920I_E,
    EVM_PORTING_AV_DISP_FMT_1080P_E,
    EVM_PORTING_AV_DISP_FMT_1080I_E,
    EVM_PORTING_AV_DISP_FMT_720P_E,
    EVM_PORTING_AV_DISP_FMT_576P_E,
    EVM_PORTING_AV_DISP_FMT_576I_E,
    EVM_PORTING_AV_DISP_FMT_480P_E,
    EVM_PORTING_AV_DISP_FMT_PAL_E,
    EVM_PORTING_AV_DISP_FMT_NTSC_E,
    EVM_PORTING_AV_DISP_FMT_SECAM_E,
    EVM_PORTING_AV_DISP_FMT_AUTO_E,

    EVM_PORTING_AV_DISP_FMT_COUNT_E,
} evm_porting_av_dispFmt_e;

typedef enum
{
    EVM_PORTING_AV_DISP_ASPECT_4TO3_E = 0,
    EVM_PORTING_AV_DISP_ASPECT_SQUARE_E,
    EVM_PORTING_AV_DISP_ASPECT_16TO9_E,

    EVM_PORTING_AV_DISP_ASPECT_COUNT_E,
} evm_porting_av_dispAspect_e;

/**�����߱�ת����ʽö��*/
typedef enum
{
    EVM_PORTING_AV_DISP_ASPECT_CVRS_IGNORE_E = 0x0,  /**< ����*/
    EVM_PORTING_AV_DISP_ASPECT_CVRS_LETTER_BOX_E,    /**< �Ӻڱ�*/
    EVM_PORTING_AV_DISP_ASPECT_CVRS_PANAND_SCAN_E,   /**< �ü�*/
    EVM_PORTING_AV_DISP_ASPECT_CVRS_COMBINED_E,      /**< �ӺڱߺͲü����*/

    EVM_PORTING_AV_DISP_ASPECT_CVRS_COUNT_E
} evm_porting_av_dispAspectCvrs_e;

typedef enum
{
    EVM_PORTING_AV_DISP_OUTPUT_MODE_CVBS_E    = 1,
    EVM_PORTING_AV_DISP_OUTPUT_MODE_YPBPR_E   = 2,
    EVM_PORTING_AV_DISP_OUTPUT_MODE_SVIDEO_E  = 4,
    EVM_PORTING_AV_DISP_OUTPUT_MODE_HDMI_E    = 8,
} evm_porting_av_dispOutputMode_e;

typedef enum
{
    EVM_PORTING_AV_VO_ATTR_ID_FMT_E = 0,                //��hPlayerΪ-1����ʾȫ����ʽ��������ʾָ����������ʽ���ο�evm_porting_av_dispFmt_e
    EVM_PORTING_AV_VO_ATTR_ID_ASPECT_E,                 //hPlayer����Ϊ-1����ʾָ���������ĳ���ȡ��ο�evm_porting_av_dispAspect_e
    EVM_PORTING_AV_VO_ATTR_ID_ASPECT_CVRS_E,        //hPlayer����Ϊ-1����ʾָ���������ı߿�ģʽ���ο�evm_porting_av_dispAspectCvrs_e
    EVM_PORTING_AV_VO_ATTR_ID_OUTPUT_RECT_E,        //hPlayer����Ϊ-1����ʾָ�����������������λ�úʹ�С
    EVM_PORTING_AV_VO_ATTR_ID_OUTPUT_MODE_E,        //hPlayer����Ϊ-1����ʾָ�������������ģʽ���ο�evm_porting_av_dispOutputMode_e
    EVM_PORTING_AV_VO_ATTR_ID_SATURATION_E,         //��hPlayerΪ-1����ʾȫ�ֱ��Ͷȣ�������ʾָ�����������Ͷ�
    EVM_PORTING_AV_VO_ATTR_ID_CONTRAST_E,               //��hPlayerΪ-1����ʾȫ�ֶԱȶȣ�������ʾָ���������Աȶ�
    EVM_PORTING_AV_VO_ATTR_ID_BRIGHTNESS_E,             //��hPlayerΪ-1����ʾȫ�����ȣ�������ʾָ������������
    EVM_PORTING_AV_VO_ATTR_ID_ZINDEX_E,                     //hPlayer����Ϊ-1����ʾָ���������Ĳ�ι�ϵ��index���ʾ���ϲ��������ͨ������index������ͬ

    EVM_PORTING_AV_VO_ATTR_ID_COUNT_E
} evm_porting_av_voAttrId_e;

typedef enum
{
    EVM_PORTING_IFRAME_LOGO,                            //Ĭ�Ͽ�������
    EVM_PORTING_IFRAME_ADV,                            //Ĭ�Ͽ���adv
    EVM_PORTING_IFRAME_AUDIO_BK                         //��Ƶ�㲥����
}evm_porting_IframeDataType_e;

typedef enum
{
    EVM_PORTING_LOGO_IFRAME,                            //IFrame
    EVM_PORTING_LOGO_JPEG                               //JPEG
}evm_porting_LogoDataType_e;

///////////////global///////////////
typedef struct
{
    evm_porting_av_streamInputType_e eStreamInputType;

    evm_porting_av_dispAspect_e eAspect;
    evm_porting_av_dispAspectCvrs_e eAspectCvrs;
    evm_porting_av_dispFmt_e eDispFmt;
    evm_porting_av_dispOutputMode_e eDispOutputMode;

    evm_porting_av_sndTrackMode_e eSndTrackMode;
    evm_porting_av_sndPassMode_e eSndPassMode;
} evm_porting_av_initParam_t;

typedef struct
{
    evm_u32 u32PlayerNum;
}evm_porting_av_initOutParam_t;

typedef struct
{
    evm_bool bTrueDeInit;
} evm_porting_av_deInitParam_t;

///////////////av�����ʼ������///////////////
/*
 * ����: evm_porting_av_Init
 * ����: ��ʼ������Ƶ���ģ�飬��������Ƶ������������ȣ�
 *              �����ʼ�����player������������ʹ��0��1��2��������player��
 *              �ײ���Ҫ��player��dmx��tunerһһ��Ӧ��player 0 ��dmx 0 ��tuner 0 ����
 * �������:
 *      pstInitParam: ��ʼ������
 * �������:
 *      pstInitOutParam:��������Ĳ�������������Ϣ
 * ����ֵ:
 *      �μ�ret_code_eö�ٶ���
 */
ret_code_e evm_porting_av_Init(evm_porting_av_initParam_t *pstInitParam, evm_porting_av_initOutParam_t *pstInitOutParam);

/*
 * ����: evm_porting_av_DeInit
 * ����: ȥ��ʼ������Ƶ���ģ��
 * �������:
 *      u32PlayerHandle:���������������Ϊ����ֵ0��1��2
 *      pstDeInitParam: ȥ��ʼ������
 * �������:
 *      ��
 * ����ֵ:
 *      �μ�ret_code_eö�ٶ���
 */
ret_code_e evm_porting_av_DeInit(evm_porting_av_deInitParam_t *pstDeInitParam);

/*
 * ����: evm_porting_av_GetPlayerNum
 * ����: ��ȡ����������
 * �������:
 *      none
 * �������:
 *      u32PlayerNum: �������������
 * ����ֵ:
 *      �μ�ret_code_eö�ٶ���
 */
ret_code_e evm_porting_av_GetPlayerNum(evm_u32 *u32PlayerNum);

/*
 * ����: evm_porting_av_GetPlayerChannel
 * ����: ��ȡ�������������
 * �������:
 *      hPlayer: ��������������Ϊ����ֵ0��1��2
 * �������:
 *      phAudioChannel: ��Ż�ȡ������Ƶͨ�����
 *      phVideoChannel: ��Ż�ȡ������Ƶͨ�����
 * ����ֵ:
 *      �μ�ret_code_eö�ٶ���
 */
ret_code_e evm_porting_av_GetPlayerChannel(evm_handle hPlayer, evm_handle *phAudioChannel, evm_handle *phVideoChannel);

/*
 * ����: evm_porting_av_PlayerGetAttr
 * ����: ��ȡ���������ԣ����Ϊ����ֵ0��1��2
 * �������:
 *      hPlayer: ���������
 *      attrId: ���Զ�Ӧ��ö��
 * �������:
 *      param: ��ȡ������ֵ
 * ����ֵ:
 *      �μ�ret_code_eö�ٶ���
 */
ret_code_e evm_porting_av_PlayerGetAttr(evm_handle hPlayer, evm_porting_av_playerAttrId_e attrId, evm_s32 param);

/*
 * ����: evm_porting_av_PlayerSetAttr
 * ����: ���ò��������ԣ�Ҫ��������Ч�����Ϊ����ֵ0��1��2
 * �������:
 *      hPlayer: ���������
 *      attrId: ���Զ�Ӧ��ö��
 *      param: ���õ�����ֵ
 * �������:
 *      ��
 * ����ֵ:
 *      �μ�ret_code_eö�ٶ���
 */
ret_code_e evm_porting_av_PlayerSetAttr(evm_handle hPlayer, evm_porting_av_playerAttrId_e attrId, evm_s32 param);

///////////////���������š�ֹͣ����ͣ���ָ�����///////////////
/*
 * ����: evm_porting_av_PlayerStart
 * ����: ��ʼ���ţ���������Ƶ���״̬����setAttr����Ϊ׼
 * �������:
 *      hPlayer: ��������������Ϊ����ֵ0��1��2
 *      eMode: ��ģʽ
 *      param: ������������δʹ��
 * �������:
 *      ��
 * ����ֵ:
 *      �μ�ret_code_eö�ٶ���
 */
ret_code_e evm_porting_av_PlayerStart(evm_handle hPlayer, evm_porting_av_playerOnOffMode_e eMode, evm_s32 param);

/*
 * ����: evm_porting_av_PlayerStop
 * ����: ֹͣ���ţ���ֹ������������ͷŵ�ǰռ�õ�handle��
 * �������:
 *      hPlayer: ��������������Ϊ����ֵ0��1��2
 *      eMode: ��ģʽ
 *      param: 0��ʾ��Ƶ�㾲�壬������ʾ����Ƶ�����
 * �������:
 *      ��
 * ����ֵ:
 *      �μ�ret_code_eö�ٶ���
 */
ret_code_e evm_porting_av_PlayerStop(evm_handle hPlayer, evm_porting_av_playerOnOffMode_e eMode, evm_s32 param);

/*
 * ����: evm_porting_av_PlayerPause
 * ����: ��ͣ����
 * �������:
 *      hPlayer: ��������������Ϊ����ֵ0��1��2
 *      param: 0��ʾ��Ƶ�㾲�壬������ʾ����Ƶ�����
 * �������:
 *      ��
 * ����ֵ:
 *      �μ�ret_code_eö�ٶ���
 */
ret_code_e evm_porting_av_PlayerPause(evm_handle hPlayer, evm_s32 param);

/*
 * ����: evm_porting_av_PlayerResume
 * ����: �ָ�����
 * �������:
 *      hPlayer: ��������������Ϊ����ֵ0��1��2
 *      param: ������������δʹ��
 * �������:
 *      ��
 * ����ֵ:
 *      �μ�ret_code_eö�ٶ���
 */
ret_code_e evm_porting_av_PlayerResume(evm_handle hPlayer, evm_s32 param);

/*
 * ����: evm_porting_av_PlayerReset
 * ����: ��λAV����
 * �������:
 *      hPlayer: ��������������Ϊ����ֵ0��1��2
 *      param: ������������δʹ��
 * �������:
 *      ��
 * ����ֵ:
 *      �μ�ret_code_eö�ٶ���
 */
ret_code_e evm_porting_av_PlayerReset(evm_handle hPlayer, evm_s32 param);

/*
 * ����: evm_porting_av_playerTPlay
 * ����: ���ٲ���
 * �������:
 *      hPlayer: ��������������Ϊ����ֵ0��1��2
 *      param: ������������δʹ��
 * �������:
 *      ��
 * ����ֵ:
 *      �μ�ret_code_eö�ٶ���
 */
ret_code_e evm_porting_av_playerTPlay(evm_handle hPlayer, evm_s32 param);

/*
 * ����: evm_porting_av_PlayerAddEventListener
 * ����: ��Ӳ������¼���������
 * �������:
 *      hPlayer: ��������������Ϊ����ֵ0��1��2
 *      pcbCallback: ��������
 *      param: ������������δʹ��
 * �������:
 *      ��
 * ����ֵ:
 *      �μ�ret_code_eö�ٶ���
 */
ret_code_e evm_porting_av_PlayerAddEventListener(evm_handle hPlayer, evm_porting_av_playerEvent_cb pcbCallback, evm_s32 param);

/*
 * ����: evm_porting_av_PlayerRemoveEventListener
 * ����: �Ƴ��������¼���������
 * �������:
 *      hPlayer: ��������������Ϊ����ֵ0��1��2
 *      pcbCallback: ��������
 *      param: ������������δʹ��
 * �������:
 *      ��
 * ����ֵ:
 *      �μ�ret_code_eö�ٶ���
 */
ret_code_e evm_porting_av_PlayerRemoveEventListener(evm_handle hPlayer, evm_porting_av_playerEvent_cb pcbCallback, evm_s32 param);

///////////////�������ڴ淽ʽע�������Ų���///////////////
/*
 * ����: evm_porting_av_PlayerGetBuf
 * ����: ����ע�����Ļ�����
 * �������:
 *      hPlayer: ��������������Ϊ����ֵ0��1��2
 *      bufType: ������
 *      requestSize: ����Ļ�������С
 *      param: ��������
 * �������:
 *      ��
 * ����ֵ:
 *      �μ�ret_code_eö�ٶ���
 */
ret_code_e evm_porting_av_PlayerGetBuf(evm_handle hPlayer, evm_porting_av_playerBufType_e bufType, evm_u32 requestSize, void** ppBufAddr, evm_s32 param);

/*
 * ����: evm_porting_av_PlayerPutBuf
 * ����: �ڵ���evm_porting_av_PlayerGetBuf�ɹ����ϲ���ppBufAddr��Ӧ�ĵ�ַ���������ݣ���ͨ��������֪ͨ�ײ㱾��ע�������
 * �������:
 *      hPlayer: ��������������Ϊ����ֵ0��1��2
 *      bufType: ������
 *      validSize: ע�������ֽ���
 *      param: ����������������es���ĳ�����param�Ǳ����������ݵ�pts
 * �������:
 *      ��
 * ����ֵ:
 *      �μ�ret_code_eö�ٶ���
 */
ret_code_e evm_porting_av_PlayerPutBuf(evm_handle hPlayer, evm_porting_av_playerBufType_e bufType, evm_u32 validSize, evm_s32 param);

/*
 * ����: evm_porting_av_PlayerGetBufUsedSize
 * ����: ��ȡ�����������Ѿ�ע�뵫��δ���ĵ����ݴ�С
 * �������:
 *      hPlayer: ��������������Ϊ����ֵ0��1��2
 *      bufType: ������
 *      requestSize: ����Ļ�������С
 *      param: ��������
 * �������:
 *      usedSize: �����������Ѿ�ע�뵱��δ���ĵ����ݴ�С
 * ����ֵ:
 *      �μ�ret_code_eö�ٶ���
 */
ret_code_e evm_porting_av_PlayerGetBufUsedSize(evm_handle hPlayer, evm_porting_av_playerBufType_e bufType, evm_u32 *usedSize, evm_s32 param);

/*
 * ����: evm_porting_av_PlayerClearBuf
 * ����: ������������ڵ�����
 * �������:
 *      hPlayer: ��������������Ϊ����ֵ0��1��2
 *      bufType: ������
 *      param: ��������
 * �������:
 *      usedSize: �����������Ѿ�ע�뵱��δ���ĵ����ݴ�С
 * ����ֵ:
 *      �μ�ret_code_eö�ٶ���
 */
ret_code_e evm_porting_av_PlayerClearBuf(evm_handle hPlayer, evm_porting_av_playerBufType_e bufType, evm_s32 param);

/*
 * ����: evm_porting_av_PlayerIsBufEmpty
 * ����: �ж�ע�������Ƶ�����Ƿ��Ѿ����ĸɾ������Ž�����
 * �������:
 *      hPlayer: ��������������Ϊ����ֵ0��1��2
 *      param: ��������
 * �������:
 *      pbEmpty: ����Ƶ�����Ƿ�Ϊ��
 * ����ֵ:
 *      �μ�ret_code_eö�ٶ���
 */
ret_code_e evm_porting_av_PlayerIsBufEmpty(evm_handle hPlayer, evm_bool *pbEmpty, evm_s32 param);

///////////////�������������///////////////
/*
 * ����: evm_porting_av_PlayerShowIframe
 * ����: ��ʾI֡
 * �������:
 *      hPlayer: ��������������Ϊ����ֵ0��1��2
 *      size: I֡���ݴ�С
 *      data:I֡����
 * �������:
 *      ��
 * ����ֵ:
 *      �μ�ret_code_eö�ٶ���
 */
ret_code_e evm_porting_av_PlayerShowIFrame(evm_handle hPlayer, evm_s32 size, evm_s8 *data);

/*
 * ����: evm_porting_av_PlayerClearScreen
 * ����: ����Ƶ����ɺ�������������I֡�������Ƶ��ȳ���
 * �������:
 *      hPlayer: ��������������Ϊ����ֵ-1(�����в�����Ϊ����)��0��1��2
 *      param: 0�����I֡��1�������Ƶ���һ֡
 * �������:
 *      ��
 * ����ֵ:
 *      �μ�ret_code_eö�ٶ���
 */
ret_code_e evm_porting_av_PlayerClearScreen(evm_handle hPlayer, evm_s32 param);


///////////////��Ƶ�����ز���///////////////
/*
 * ����: evm_porting_av_AoGetAttr
 * ����: ��ȡ��Ƶ����������
 * �������:
 *      hPlayer: ��������������Ϊ����ֵ-1��0��1��2
 *      attrId: ���Զ�Ӧ��ö��
 * �������:
 *      param: ��ȡ������ֵ
 * ����ֵ:
 *      �μ�ret_code_eö�ٶ���
 */
ret_code_e evm_porting_av_AoGetAttr(evm_handle hPlayer, evm_porting_av_aoAttrId_e attrId, evm_s32 param);


/*
 * ����: evm_porting_av_AoSetAttr
 * ����: ������Ƶ����������
 * �������:
 *      hPlayer: ��������������Ϊ����ֵ-1��0��1��2
 *      attrId: ���Զ�Ӧ��ö��
 *      param: ���õ�����ֵ
 * �������:
 *      ��
 * ����ֵ:
 *      �μ�ret_code_eö�ٶ���
 */
ret_code_e evm_porting_av_AoSetAttr(evm_handle hPlayer, evm_porting_av_aoAttrId_e attrId, evm_s32 param);

///////////////��Ƶ�����ز�������///////////////
/*
 * ����: evm_porting_av_VoGetAttr
 * ����: ��ȡ��Ƶ����������
 * �������:
 *      hPlayer: ��������������Ϊ����ֵ-1��0��1��2
 *      attrId: ���Զ�Ӧ��ö��
 * �������:
 *      param: ��ȡ������ֵ
 * ����ֵ:
 *      �μ�ret_code_eö�ٶ���
 */
ret_code_e evm_porting_av_VoGetAttr(evm_handle hPlayer, evm_porting_av_voAttrId_e attrId, evm_s32 param);

/*
 * ����: evm_porting_av_VoSetAttr
 * ����: ������Ƶ����������
 * �������:
 *      hPlayer: ��������������Ϊ����ֵ-1��0��1��2
 *      attrId: ���Զ�Ӧ��ö��
 *      param: ���õ�����ֵ
 * �������:
 *      ��
 * ����ֵ:
 *      �μ�ret_code_eö�ٶ���
 */
ret_code_e evm_porting_av_VoSetAttr(evm_handle hPlayer, evm_porting_av_voAttrId_e attrId, evm_s32 param);

/*
 * ����: evm_porting_av_PlayerSetScene
 * ����: ���ò��ŵĳ���
 * �������:
 *      hPlayer: ��������������Ϊ����ֵ-1��0��1��2
 *      param: ���õ�����ֵ
 *          ��ͬ������0-��dvb�� 1-��cloud�� 2-��vod�� 3-��vpc
 * �������:
 *      ��
 * ����ֵ:
 *      �μ�ret_code_eö�ٶ���
 */
ret_code_e evm_porting_av_PlayerSetScene(evm_handle hPlayer,evm_s32 param);

/*
 * ����: evm_porting_av_SetSomething
 * ����: ���ò��������������ԣ����ض���Ŀ����
 * �������:
 *      hPlayer: ��������������Ϊ����ֵ-1��0��1��2
 *      param1: ����1
 *      param2: ����2
 * �������:
 *      ��
 * ����ֵ:
 *      �μ�ret_code_eö�ٶ���
 */
ret_code_e evm_porting_av_SetSomething(evm_handle hPlayer, evm_s32 param1, evm_s32 param2);

#endif /* EVM_PORTING_AVPLAYER_H_ */
