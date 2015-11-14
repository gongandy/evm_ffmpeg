/*
 * evm_porting_avplayer.h
 * Copyright(C) EnRich DTV Group Co.,Ltd.
 *
 * Description: 
 *
 * Authors: 沈辉<shenhui@evmtv.com>
 */

#ifndef EVM_PORTING_AVPLAYER_H_
#define EVM_PORTING_AVPLAYER_H_

#include "evm_typedef.h"

///////////////player///////////////
typedef enum
{
	EVM_PORTING_AV_ENBLE_AUDIO_CHANNEL_E = 0,		//使能音频通道
	EVM_PORTING_AV_ENBLE_VIDEO_CHANNEL_E,			//使能视频通道
	EVM_PORTING_AV_ENBLE_AV_CHANNEL_E,				//使能音视频通道

	EVM_PORTING_AV_ENBLE_AV_CHANNEL_END
}evm_porting_av_enableChannel_e;
typedef enum
{
	EVM_PORTING_AV_STREAM_INPUT_TYPE_RAM_TS_E = 0, 				//内存拷贝方式ts流
	EVM_PORTING_AV_STREAM_INPUT_TYPE_RAM_ES_E, 					//内存拷贝方式es流
	EVM_PORTING_AV_STREAM_INPUT_TYPE_DEMUX_TS_E, 				//demux输入ts流

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
	EVM_PORTING_AV_SYNC_REF_NONE_E = 0, 		    //自由播放
	EVM_PORTING_AV_SYNC_REF_AUD_E, 					//以音频为准
	EVM_PORTING_AV_SYNC_REF_VID_E, 					//以视频为准
	EVM_PORTING_AV_SYNC_REF_PCR_E, 					//以PCR为准	
	EVM_PORTING_AV_SYNC_REF_QUICK_OUTPUT_E,         //快速输出,如mstart芯片半帧解码方式
	EVM_PORTING_AV_SYNC_REF_COUNT_E
} evm_porting_av_syncRef_e;

typedef enum
{
    EVM_PORTING_AV_AUD_SAMPLE_RATE_8K_E    = 8000,   /**<CNcomment: 8K采样频率 */
    EVM_PORTING_AV_AUD_SAMPLE_RATE_11K_E   = 11025,  /**<CNcomment: 11.025K采样频率 */
    EVM_PORTING_AV_AUD_SAMPLE_RATE_12K_E   = 12000,  /**<CNcomment: 12K采样频率 */
    EVM_PORTING_AV_AUD_SAMPLE_RATE_16K_E   = 16000,  /**<CNcomment: 16K采样频率 */
    EVM_PORTING_AV_AUD_SAMPLE_RATE_22K_E   = 22050,  /**<CNcomment: 22.050K采样频率 */
    EVM_PORTING_AV_AUD_SAMPLE_RATE_24K_E   = 24000,  /**<CNcomment: 24K采样频率 */
    EVM_PORTING_AV_AUD_SAMPLE_RATE_32K_E   = 32000,  /**<CNcomment: 32K采样频率 */
    EVM_PORTING_AV_AUD_SAMPLE_RATE_44K_E   = 44100,  /**<CNcomment: 44.1K采样频率 */
    EVM_PORTING_AV_AUD_SAMPLE_RATE_48K_E   = 48000,  /**<CNcomment: 48K采样频率 */
    EVM_PORTING_AV_AUD_SAMPLE_RATE_88K_E   = 88200,  /**<CNcomment: 88.2K采样频率 */
    EVM_PORTING_AV_AUD_SAMPLE_RATE_96K_E   = 96000,  /**<CNcomment: 96K采样频率 */
    EVM_PORTING_AV_AUD_SAMPLE_RATE_176K_E  = 176400,     /**<CNcomment: 176K采样频率 */
    EVM_PORTING_AV_AUD_SAMPLE_RATE_192K_E  = 192000,   /**<CNcomment: 192K采样频率 */

    EVM_PORTING_AV_AUD_SAMPLE_RATE_BUTT_E
} evm_porting_av_audSampleRate_e;

typedef enum
{
    EVM_PORTING_AV_AUD_BIT_DEPTH_8_E  = 8,    /**< 8位采样位宽  */
    EVM_PORTING_AV_AUD_BIT_DEPTH_16_E = 16,   /**< 16位采样位宽 */
    EVM_PORTING_AV_AUD_BIT_DEPTH_18_E = 18,   /**< 18位采样位宽 */
    EVM_PORTING_AV_AUD_BIT_DEPTH_20_E = 20,   /**< 20位采样位宽 */
    EVM_PORTING_AV_AUD_BIT_DEPTH_24_E = 24,   /**< 24位采样位宽 */
    EVM_PORTING_AV_AUD_BIT_DEPTH_32_E = 32,   /**< 32位采样位宽 */

    EVM_PORTING_AV_AUD_BIT_DEPTH_BUTT
} evm_porting_av_audBitDepth_e;

typedef enum
{
    EVM_PORTING_AV_PLAYER_ATTR_ID_STREAM_INPUT_TYPE_E = 0, 	    //流类型，见evm_avplayerStreamType_e
    EVM_PORTING_AV_PLAYER_ATTR_ID_ADEC_TYPE_E, 					//音频解码格式，见evm_porting_av_streamType_e
    EVM_PORTING_AV_PLAYER_ATTR_ID_VDEC_TYPE_E, 					//视频解码格式，见evm_porting_av_streamType_e
    EVM_PORTING_AV_PLAYER_ATTR_ID_AUD_PID_E, 					//音频pid
    EVM_PORTING_AV_PLAYER_ATTR_ID_VID_PID_E, 					//视频pid
    EVM_PORTING_AV_PLAYER_ATTR_ID_PCR_PID_E, 					//pcr pid
    EVM_PORTING_AV_PLAYER_ATTR_ID_SYNC_REF_E, 					//同步模式
    EVM_PORTING_AV_PLAYER_ATTR_ID_AUD_SAMPLE_RATE_E,             //音频采样率，见evm_porting_av_audSampleRate_e
    EVM_PORTING_AV_PLAYER_ATTR_ID_AUD_BIT_DEPTH_E,               //音频采样深度，见evm_porting_av_audBitDepth_e
    EVM_PORTING_AV_PLAYER_ATTR_ID_OUTPUTMODE_E,			//输出通道选择，为不输出的状态下，start无效，
                                                                                                            //并且设置为不输出要求底层隐藏对应的播放器,
                                                                                                            //见evm_porting_av_playerOutputMode_e

	EVM_PORTING_AV_PLAYER_ATTR_ID_SYNC_COUNT_E
} evm_porting_av_playerAttrId_e;

typedef enum
{
    EVM_PORTING_AV_PLAYER_BUF_TYPE_TS_E = 0,    //ts流
    EVM_PORTING_AV_PLAYER_BUF_TYPE_AUD_ES_E,    //音频es流
    EVM_PORTING_AV_PLAYER_BUF_TYPE_VID_ES_E,    //视频es流

    EVM_PORTING_AV_PLAYER_BUF_TYPE_COUNT_E
} evm_porting_av_playerBufType_e;

typedef enum
{
    EVM_PORTING_AV_PLAYER_ONOFF_MODE_ALL_E = 0,  		//音视频全部打开或者关闭
    EVM_PORTING_AV_PLAYER_ONOFF_MODE_VID_E,  			//只打开或者关闭视频
    EVM_PORTING_AV_PLAYER_ONOFF_MODE_AUD_E,  			//只打开或者关闭音频

    EVM_PORTING_AV_PLAYER_ONOFF_MODE_COUNT_E
} evm_porting_av_playerOnOffMode_e;

typedef enum
{
    EVM_PORTING_AV_PLAYER_OUTPUT_MODE_ALL_E = 0,  		//音视频同时输出
    EVM_PORTING_AV_PLAYER_OUTPUT_MODE_VID_E,  			//只输出视频
    EVM_PORTING_AV_PLAYER_OUTPUT_MODE_AUD_E,  			//只输出音频
    EVM_PORTING_AV_PLAYER_OUTPUT_MODE_NONE_E,			//音视频都不输出

    EVM_PORTING_AV_PLAYER_OUTPUT_MODE_COUNT_E
} evm_porting_av_playerOutputMode_e;

typedef enum
{
    EVM_PORTING_AV_PLAYER_EVENT_TYPE_START_DECODE_E = 0,     //播放器收到音视频数据并开始解码
    EVM_PORTING_AV_PLAYER_EVENT_TYPE_NO_STREAM_E,            //无媒体数据

    //以下是文件播放的事件通知类型，对于非文件播放的不需要关心以下事件类型
    EVM_PROTING_AV_FILE_PLAYER_EVENT_STATE_E,                //param1:状态变化后的状态，param2:预留
    EVM_PROTING_AV_FILE_PLAYER_EVENT_BOF_E,                  //param1:预留，param2:预留
    EVM_PROTING_AV_FILE_PLAYER_EVENT_EOF_E,                  //param1:预留，param2:预留
    EVM_PROTING_AV_FILE_PLAYER_EVENT_PLAY_PROGRESS_E,        //param1:当前播放进度0-100，param2:当前播放时间ms
    EVM_PROTING_AV_FILE_PLAYER_EVENT_DOWNLOAD_PROGRESS_E,    //param1:当前下载进度0-100，param2:当前下载时间ms
    EVM_PROTING_AV_FILE_PLAYER_EVENT_SEEK_FIN_E,             //param1:预留，param2:预留
    EVM_PROTING_AV_FILE_PLAYER_EVENT_BUFFER_EMPTY_E,         //无媒体缓冲数据，param1:预留，param2:预留
    EVM_PROTING_AV_FILE_PLAYER_EVENT_BUFFER_ENOUGH_E,        //缓冲数据足够播放，param1:预留，param2:预留
    EVM_PROTING_AV_FILE_PLAYER_EVENT_ALL_BUFFERED_E,         //全部缓冲结束，param1:预留，param2:预留
    EVM_PROTING_AV_FILE_PLAYER_EVENT_ERROR_E,                //param1:预留，param2:预留

    EVM_PORTING_AV_PLAYER_EVENT_TYPE_COUNT_E
} evm_porting_av_playerEventType_e;


typedef void (*evm_porting_av_playerEvent_cb)(evm_handle hPlayer, evm_porting_av_playerEventType_e eType, evm_s32 param1, evm_s32 param2);

///////////////audio output///////////////
typedef enum
{
    EVM_PORTING_AV_SND_TRACK_MODE_STEREO_E = 0, 	/**<立体声*/
    EVM_PORTING_AV_SND_TRACK_MODE_LEFT_E,			/**<左声道*/
    EVM_PORTING_AV_SND_TRACK_MODE_RIGHT_E,  		/**<右声道*/
    EVM_PORTING_AV_SND_TRACK_MODE_MONO_E ,          /**<混合声*/

    EVM_PORTING_AV_SND_TRACK_MODE_COUNT_E
} evm_porting_av_sndTrackMode_e;

//spdif、hdmi等接口的音频输出方式
typedef enum
{
    EVM_PROTING_AV_SND_PASS_MODE_RAW_E,  			//原始数据
    EVM_PROTING_AV_SND_PASS_MODE_PCM_E,  			//解码数据
    EVM_PROTING_AV_SND_PASS_MODE_OFF_E,  			//关闭

    EVM_PROTING_AV_SND_PASS_MODE_COUNT_E
} evm_porting_av_sndPassMode_e;

typedef enum
{
    EVM_PORTING_AV_AO_ATTR_ID_MUTE_E = 0,               //当hPlayer为-1，表示全局静音，其他表示指定播放器静音
    EVM_PORTING_AV_AO_ATTR_ID_VOLUME_E,                 //当hPlayer为-1，表示全局音量，其他表示指定播放器音量
    EVM_PORTING_AV_AO_ATTR_ID_TRACK_MODE_E,         //当hPlayer为-1，表示全局声道模式，暂无其他值
    EVM_PORTING_AV_AO_ATTR_ID_PASS_MODE_E,           //hPlayer不能为-1，表示指定播放器的透传模式，参考evm_porting_av_sndPassMode_e

    //special
    EVM_PORTING_AV_AO_ATTR_ID_SPEAKER_MUTE_E,       //当hPlayer为-1，表示全局话筒静音，其他表示指定播放器话筒静音
    EVM_PORTING_AV_AO_ATTR_ID_SPEAKER_VOLUME_E,     //当hPlayer为-1，表示全局话筒音量，其他表示指定播放器话筒音量

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

/**定义宽高比转换方式枚举*/
typedef enum
{
    EVM_PORTING_AV_DISP_ASPECT_CVRS_IGNORE_E = 0x0,  /**< 忽略*/
    EVM_PORTING_AV_DISP_ASPECT_CVRS_LETTER_BOX_E,    /**< 加黑边*/
    EVM_PORTING_AV_DISP_ASPECT_CVRS_PANAND_SCAN_E,   /**< 裁减*/
    EVM_PORTING_AV_DISP_ASPECT_CVRS_COMBINED_E,      /**< 加黑边和裁减混合*/

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
    EVM_PORTING_AV_VO_ATTR_ID_FMT_E = 0,                //当hPlayer为-1，表示全局制式，其他表示指定播放器制式。参考evm_porting_av_dispFmt_e
    EVM_PORTING_AV_VO_ATTR_ID_ASPECT_E,                 //hPlayer不能为-1，表示指定播放器的长宽比。参考evm_porting_av_dispAspect_e
    EVM_PORTING_AV_VO_ATTR_ID_ASPECT_CVRS_E,        //hPlayer不能为-1，表示指定播放器的边框模式。参考evm_porting_av_dispAspectCvrs_e
    EVM_PORTING_AV_VO_ATTR_ID_OUTPUT_RECT_E,        //hPlayer不能为-1，表示指定播放器的输出窗口位置和大小
    EVM_PORTING_AV_VO_ATTR_ID_OUTPUT_MODE_E,        //hPlayer不能为-1，表示指定播放器的输出模式。参考evm_porting_av_dispOutputMode_e
    EVM_PORTING_AV_VO_ATTR_ID_SATURATION_E,         //当hPlayer为-1，表示全局饱和度，其他表示指定播放器饱和度
    EVM_PORTING_AV_VO_ATTR_ID_CONTRAST_E,               //当hPlayer为-1，表示全局对比度，其他表示指定播放器对比度
    EVM_PORTING_AV_VO_ATTR_ID_BRIGHTNESS_E,             //当hPlayer为-1，表示全局亮度，其他表示指定播放器亮度
    EVM_PORTING_AV_VO_ATTR_ID_ZINDEX_E,                     //hPlayer不能为-1，表示指定播放器的层次关系，index大表示在上层输出，不通播放器index可以相同

    EVM_PORTING_AV_VO_ATTR_ID_COUNT_E
} evm_porting_av_voAttrId_e;

typedef enum
{
    EVM_PORTING_IFRAME_LOGO,                            //默认开机背景
    EVM_PORTING_IFRAME_ADV,                            //默认开机adv
    EVM_PORTING_IFRAME_AUDIO_BK                         //音频广播背景
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

///////////////av整体初始化操作///////////////
/*
 * 函数: evm_porting_av_Init
 * 描述: 初始化音视频相关模块，包括音视频输出、播放器等，
 *              输出初始化后的player个数。后续会使用0、1、2索引操作player。
 *              底层需要将player、dmx、tuner一一对应。player 0 与dmx 0 与tuner 0 关联
 * 输入参数:
 *      pstInitParam: 初始化参数
 * 输出参数:
 *      pstInitOutParam:输出创建的播放器个数等信息
 * 返回值:
 *      参见ret_code_e枚举定义
 */
ret_code_e evm_porting_av_Init(evm_porting_av_initParam_t *pstInitParam, evm_porting_av_initOutParam_t *pstInitOutParam);

/*
 * 函数: evm_porting_av_DeInit
 * 描述: 去初始化音视频相关模块
 * 输入参数:
 *      u32PlayerHandle:播放器索引，句柄为索引值0、1、2
 *      pstDeInitParam: 去初始化参数
 * 输出参数:
 *      无
 * 返回值:
 *      参见ret_code_e枚举定义
 */
ret_code_e evm_porting_av_DeInit(evm_porting_av_deInitParam_t *pstDeInitParam);

/*
 * 函数: evm_porting_av_GetPlayerNum
 * 描述: 获取播放器个数
 * 输入参数:
 *      none
 * 输出参数:
 *      u32PlayerNum: 输出播放器个数
 * 返回值:
 *      参见ret_code_e枚举定义
 */
ret_code_e evm_porting_av_GetPlayerNum(evm_u32 *u32PlayerNum);

/*
 * 函数: evm_porting_av_GetPlayerChannel
 * 描述: 获取播放器相关属性
 * 输入参数:
 *      hPlayer: 播放器句柄，句柄为索引值0、1、2
 * 输出参数:
 *      phAudioChannel: 存放获取到的音频通道句柄
 *      phVideoChannel: 存放获取到的视频通道句柄
 * 返回值:
 *      参见ret_code_e枚举定义
 */
ret_code_e evm_porting_av_GetPlayerChannel(evm_handle hPlayer, evm_handle *phAudioChannel, evm_handle *phVideoChannel);

/*
 * 函数: evm_porting_av_PlayerGetAttr
 * 描述: 获取播放器属性，句柄为索引值0、1、2
 * 输入参数:
 *      hPlayer: 播放器句柄
 *      attrId: 属性对应的枚举
 * 输出参数:
 *      param: 获取的属性值
 * 返回值:
 *      参见ret_code_e枚举定义
 */
ret_code_e evm_porting_av_PlayerGetAttr(evm_handle hPlayer, evm_porting_av_playerAttrId_e attrId, evm_s32 param);

/*
 * 函数: evm_porting_av_PlayerSetAttr
 * 描述: 设置播放器属性，要求立即生效，句柄为索引值0、1、2
 * 输入参数:
 *      hPlayer: 播放器句柄
 *      attrId: 属性对应的枚举
 *      param: 设置的属性值
 * 输出参数:
 *      无
 * 返回值:
 *      参见ret_code_e枚举定义
 */
ret_code_e evm_porting_av_PlayerSetAttr(evm_handle hPlayer, evm_porting_av_playerAttrId_e attrId, evm_s32 param);

///////////////播放器播放、停止、暂停、恢复操作///////////////
/*
 * 函数: evm_porting_av_PlayerStart
 * 描述: 开始播放，但是音视频输出状态依据setAttr设置为准
 * 输入参数:
 *      hPlayer: 播放器句柄，句柄为索引值0、1、2
 *      eMode: 打开模式
 *      param: 保留参数，暂未使用
 * 输出参数:
 *      无
 * 返回值:
 *      参见ret_code_e枚举定义
 */
ret_code_e evm_porting_av_PlayerStart(evm_handle hPlayer, evm_porting_av_playerOnOffMode_e eMode, evm_s32 param);

/*
 * 函数: evm_porting_av_PlayerStop
 * 描述: 停止播放，禁止播放器输出，释放当前占用的handle。
 * 输入参数:
 *      hPlayer: 播放器句柄，句柄为索引值0、1、2
 *      eMode: 打开模式
 *      param: 0表示视频层静桢，其他表示以视频层黑屏
 * 输出参数:
 *      无
 * 返回值:
 *      参见ret_code_e枚举定义
 */
ret_code_e evm_porting_av_PlayerStop(evm_handle hPlayer, evm_porting_av_playerOnOffMode_e eMode, evm_s32 param);

/*
 * 函数: evm_porting_av_PlayerPause
 * 描述: 暂停播放
 * 输入参数:
 *      hPlayer: 播放器句柄，句柄为索引值0、1、2
 *      param: 0表示视频层静桢，其他表示以视频层黑屏
 * 输出参数:
 *      无
 * 返回值:
 *      参见ret_code_e枚举定义
 */
ret_code_e evm_porting_av_PlayerPause(evm_handle hPlayer, evm_s32 param);

/*
 * 函数: evm_porting_av_PlayerResume
 * 描述: 恢复播放
 * 输入参数:
 *      hPlayer: 播放器句柄，句柄为索引值0、1、2
 *      param: 保留参数，暂未使用
 * 输出参数:
 *      无
 * 返回值:
 *      参见ret_code_e枚举定义
 */
ret_code_e evm_porting_av_PlayerResume(evm_handle hPlayer, evm_s32 param);

/*
 * 函数: evm_porting_av_PlayerReset
 * 描述: 复位AV播放
 * 输入参数:
 *      hPlayer: 播放器句柄，句柄为索引值0、1、2
 *      param: 保留参数，暂未使用
 * 输出参数:
 *      无
 * 返回值:
 *      参见ret_code_e枚举定义
 */
ret_code_e evm_porting_av_PlayerReset(evm_handle hPlayer, evm_s32 param);

/*
 * 函数: evm_porting_av_playerTPlay
 * 描述: 倍速播放
 * 输入参数:
 *      hPlayer: 播放器句柄，句柄为索引值0、1、2
 *      param: 保留参数，暂未使用
 * 输出参数:
 *      无
 * 返回值:
 *      参见ret_code_e枚举定义
 */
ret_code_e evm_porting_av_playerTPlay(evm_handle hPlayer, evm_s32 param);

/*
 * 函数: evm_porting_av_PlayerAddEventListener
 * 描述: 添加播放器事件监听函数
 * 输入参数:
 *      hPlayer: 播放器句柄，句柄为索引值0、1、2
 *      pcbCallback: 监听函数
 *      param: 保留参数，暂未使用
 * 输出参数:
 *      无
 * 返回值:
 *      参见ret_code_e枚举定义
 */
ret_code_e evm_porting_av_PlayerAddEventListener(evm_handle hPlayer, evm_porting_av_playerEvent_cb pcbCallback, evm_s32 param);

/*
 * 函数: evm_porting_av_PlayerRemoveEventListener
 * 描述: 移除播放器事件监听函数
 * 输入参数:
 *      hPlayer: 播放器句柄，句柄为索引值0、1、2
 *      pcbCallback: 监听函数
 *      param: 保留参数，暂未使用
 * 输出参数:
 *      无
 * 返回值:
 *      参见ret_code_e枚举定义
 */
ret_code_e evm_porting_av_PlayerRemoveEventListener(evm_handle hPlayer, evm_porting_av_playerEvent_cb pcbCallback, evm_s32 param);

///////////////播放器内存方式注入流播放操作///////////////
/*
 * 函数: evm_porting_av_PlayerGetBuf
 * 描述: 申请注入流的缓冲区
 * 输入参数:
 *      hPlayer: 播放器句柄，句柄为索引值0、1、2
 *      bufType: 流类型
 *      requestSize: 请求的缓冲区大小
 *      param: 保留参数
 * 输出参数:
 *      无
 * 返回值:
 *      参见ret_code_e枚举定义
 */
ret_code_e evm_porting_av_PlayerGetBuf(evm_handle hPlayer, evm_porting_av_playerBufType_e bufType, evm_u32 requestSize, void** ppBufAddr, evm_s32 param);

/*
 * 函数: evm_porting_av_PlayerPutBuf
 * 描述: 在调用evm_porting_av_PlayerGetBuf成功后，上层向ppBufAddr对应的地址拷贝流数据，并通过本函数通知底层本次注入结束。
 * 输入参数:
 *      hPlayer: 播放器句柄，句柄为索引值0、1、2
 *      bufType: 流类型
 *      validSize: 注入流的字节数
 *      param: 保留参数，对于退es流的场景，param是本次推入数据的pts
 * 输出参数:
 *      无
 * 返回值:
 *      参见ret_code_e枚举定义
 */
ret_code_e evm_porting_av_PlayerPutBuf(evm_handle hPlayer, evm_porting_av_playerBufType_e bufType, evm_u32 validSize, evm_s32 param);

/*
 * 函数: evm_porting_av_PlayerGetBufUsedSize
 * 描述: 获取流缓冲区内已经注入但尚未消耗的数据大小
 * 输入参数:
 *      hPlayer: 播放器句柄，句柄为索引值0、1、2
 *      bufType: 流类型
 *      requestSize: 请求的缓冲区大小
 *      param: 保留参数
 * 输出参数:
 *      usedSize: 流缓冲区内已经注入当尚未消耗的数据大小
 * 返回值:
 *      参见ret_code_e枚举定义
 */
ret_code_e evm_porting_av_PlayerGetBufUsedSize(evm_handle hPlayer, evm_porting_av_playerBufType_e bufType, evm_u32 *usedSize, evm_s32 param);

/*
 * 函数: evm_porting_av_PlayerClearBuf
 * 描述: 清除流缓冲区内的数据
 * 输入参数:
 *      hPlayer: 播放器句柄，句柄为索引值0、1、2
 *      bufType: 流类型
 *      param: 保留参数
 * 输出参数:
 *      usedSize: 流缓冲区内已经注入当尚未消耗的数据大小
 * 返回值:
 *      参见ret_code_e枚举定义
 */
ret_code_e evm_porting_av_PlayerClearBuf(evm_handle hPlayer, evm_porting_av_playerBufType_e bufType, evm_s32 param);

/*
 * 函数: evm_porting_av_PlayerIsBufEmpty
 * 描述: 判断注入的音视频数据是否已经消耗干净（播放结束）
 * 输入参数:
 *      hPlayer: 播放器句柄，句柄为索引值0、1、2
 *      param: 保留参数
 * 输出参数:
 *      pbEmpty: 音视频数据是否为空
 * 返回值:
 *      参见ret_code_e枚举定义
 */
ret_code_e evm_porting_av_PlayerIsBufEmpty(evm_handle hPlayer, evm_bool *pbEmpty, evm_s32 param);

///////////////播放器杂项操作///////////////
/*
 * 函数: evm_porting_av_PlayerShowIframe
 * 描述: 显示I帧
 * 输入参数:
 *      hPlayer: 播放器句柄，句柄为索引值0、1、2
 *      size: I帧数据大小
 *      data:I帧数据
 * 输出参数:
 *      无
 * 返回值:
 *      参见ret_code_e枚举定义
 */
ret_code_e evm_porting_av_PlayerShowIFrame(evm_handle hPlayer, evm_s32 size, evm_s8 *data);

/*
 * 函数: evm_porting_av_PlayerClearScreen
 * 描述: 将视频层清成黑屏，用于隐藏I帧、清除视频桢等场景
 * 输入参数:
 *      hPlayer: 播放器句柄，句柄为索引值-1(清所有播放器为黑屏)、0、1、2
 *      param: 0，清除I帧；1，清除视频最后一帧
 * 输出参数:
 *      无
 * 返回值:
 *      参见ret_code_e枚举定义
 */
ret_code_e evm_porting_av_PlayerClearScreen(evm_handle hPlayer, evm_s32 param);


///////////////音频输出相关操作///////////////
/*
 * 函数: evm_porting_av_AoGetAttr
 * 描述: 获取音频输出相关属性
 * 输入参数:
 *      hPlayer: 播放器句柄，句柄为索引值-1、0、1、2
 *      attrId: 属性对应的枚举
 * 输出参数:
 *      param: 获取的属性值
 * 返回值:
 *      参见ret_code_e枚举定义
 */
ret_code_e evm_porting_av_AoGetAttr(evm_handle hPlayer, evm_porting_av_aoAttrId_e attrId, evm_s32 param);


/*
 * 函数: evm_porting_av_AoSetAttr
 * 描述: 设置音频输出相关属性
 * 输入参数:
 *      hPlayer: 播放器句柄，句柄为索引值-1、0、1、2
 *      attrId: 属性对应的枚举
 *      param: 设置的属性值
 * 输出参数:
 *      无
 * 返回值:
 *      参见ret_code_e枚举定义
 */
ret_code_e evm_porting_av_AoSetAttr(evm_handle hPlayer, evm_porting_av_aoAttrId_e attrId, evm_s32 param);

///////////////视频输出相关操作操作///////////////
/*
 * 函数: evm_porting_av_VoGetAttr
 * 描述: 获取视频输出相关属性
 * 输入参数:
 *      hPlayer: 播放器句柄，句柄为索引值-1、0、1、2
 *      attrId: 属性对应的枚举
 * 输出参数:
 *      param: 获取的属性值
 * 返回值:
 *      参见ret_code_e枚举定义
 */
ret_code_e evm_porting_av_VoGetAttr(evm_handle hPlayer, evm_porting_av_voAttrId_e attrId, evm_s32 param);

/*
 * 函数: evm_porting_av_VoSetAttr
 * 描述: 设置视频输出相关属性
 * 输入参数:
 *      hPlayer: 播放器句柄，句柄为索引值-1、0、1、2
 *      attrId: 属性对应的枚举
 *      param: 设置的属性值
 * 输出参数:
 *      无
 * 返回值:
 *      参见ret_code_e枚举定义
 */
ret_code_e evm_porting_av_VoSetAttr(evm_handle hPlayer, evm_porting_av_voAttrId_e attrId, evm_s32 param);

/*
 * 函数: evm_porting_av_PlayerSetScene
 * 描述: 设置播放的场景
 * 输入参数:
 *      hPlayer: 播放器句柄，句柄为索引值-1、0、1、2
 *      param: 设置的属性值
 *          不同场景：0-》dvb； 1-》cloud； 2-》vod； 3-》vpc
 * 输出参数:
 *      无
 * 返回值:
 *      参见ret_code_e枚举定义
 */
ret_code_e evm_porting_av_PlayerSetScene(evm_handle hPlayer,evm_s32 param);

/*
 * 函数: evm_porting_av_SetSomething
 * 描述: 设置播放器的特殊属性，由特定项目决定
 * 输入参数:
 *      hPlayer: 播放器句柄，句柄为索引值-1、0、1、2
 *      param1: 参数1
 *      param2: 参数2
 * 输出参数:
 *      无
 * 返回值:
 *      参见ret_code_e枚举定义
 */
ret_code_e evm_porting_av_SetSomething(evm_handle hPlayer, evm_s32 param1, evm_s32 param2);

#endif /* EVM_PORTING_AVPLAYER_H_ */
