/*
 * evm_porting_imageDecoder.h
 *
 * Description:
 *
 * Author: shenhui@evmtv.com Oct 28, 2012
 *
 */

#ifndef EVM_PORTING_IMAGEDECODER_H_
#define EVM_PORTING_IMAGEDECODER_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include "evm_typedef.h"

typedef enum
{
    EVM_PORTING_COLOR_FMT_ARGB8888_E = 0,
    EVM_PORTING_COLOR_FMT_ARGB8888_PM_E,  //预乘模式ARGB8888
    EVM_PORTING_COLOR_FMT_ARGB4444_E,
    EVM_PORTING_COLOR_FMT_ARGB1555_E,
    EVM_PORTING_COLOR_FMT_RGB565_E
} evm_porting_color_fmt_e;

typedef enum
{
    EVM_PORTING_PICTURE_FMT_GIF_E = 0,
    EVM_PORTING_PICTURE_FMT_JPG_E,
    EVM_PORTING_PICTURE_FMT_PNG_E,
    EVM_PORTING_PICTURE_FMT_BMP_E
} evm_porting_picture_fmt_e;

typedef struct _evm_porting_HWImageDecoder_t_
{
    /*输入*/
    evm_u8 *pu8OrgData;  				//需要解码图片的原始数据地址
    evm_u32 u32OrgDataLength;  			//需要解码图片的原始数据长度
    evm_u32 u32FrameIndex;  			//需要解码的帧索引号，对于多帧的GIF或APNG有意义，其他默认是0
    evm_u32 u32Timeout;  				//解码超时时间, 0为阻塞模式
    evm_porting_color_fmt_e eColorFmt;  //需要解压出来的颜色模式
    evm_porting_picture_fmt_e ePicFmt;  //图片格式

    /*输出*/
    evm_u8 *pu8OutputData;  			//解码后的图片数据地址，按照平台对应的字节序存储颜色信息
    evm_u32 u32OutputLength;  			//解码后的图片数据长度
    evm_u32 u32Width;  					//解码后的图片宽度
    evm_u32 u32Height;  				//解码后的图片高度
    evm_u32 u32Pitch;  					//解码后的图片一行所占字节数
    evm_u32 u32Private;  				//私有数据
    evm_u32 u32FrameCount;              //Numbers of pictures
    evm_u32 u32DelayTime;               //Duration between this frame and last frame (Units:10ms)
} evm_porting_HWImageDecoder_t;


/**
 * 函数: evm_porting_imageDecoder_Init
 * 描述: Initialyze image decoder.
 * 输入参数:
 *      None
 * 输出参数:
 *      None
 * 返回: 参见ret_code_e
 */

ret_code_e evm_porting_imageDecoder_Init(void);


/**
 * 函数: evm_porting_DecodeImage
 * 描述: 解码图片。可选接口。如果平台存在高效率的图片解码接口（硬件解码接口），实现该函数；否则直接返回解码失败
 * 输入参数:
 *      pstDecoderInfo: 需要解码的图片信息
 * 输出参数:
 *      无
 * 返回: 参见ret_code_e
 */
ret_code_e evm_porting_DecodeImage(evm_porting_HWImageDecoder_t *pstDecoderInfo);

/**
 * 函数: evm_porting_ReleaseImage
 * 描述: 释放解码后的图片数据，和evm_porting_DecodeImage一起实现。
 * 输入参数:
 *      pstDecoderInfo: 需要释放的解码后图片信息
 * 输出参数:
 *      无
 * 返回: 参见ret_code_e
 */
ret_code_e evm_porting_ReleaseImage(evm_porting_HWImageDecoder_t *pstDecoderInfo);


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* EVM_PORTING_IMAGEDECODER_H_ */
