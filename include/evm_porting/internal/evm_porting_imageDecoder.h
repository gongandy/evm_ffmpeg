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
    EVM_PORTING_COLOR_FMT_ARGB8888_PM_E,  //Ԥ��ģʽARGB8888
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
    /*����*/
    evm_u8 *pu8OrgData;  				//��Ҫ����ͼƬ��ԭʼ���ݵ�ַ
    evm_u32 u32OrgDataLength;  			//��Ҫ����ͼƬ��ԭʼ���ݳ���
    evm_u32 u32FrameIndex;  			//��Ҫ�����֡�����ţ����ڶ�֡��GIF��APNG�����壬����Ĭ����0
    evm_u32 u32Timeout;  				//���볬ʱʱ��, 0Ϊ����ģʽ
    evm_porting_color_fmt_e eColorFmt;  //��Ҫ��ѹ��������ɫģʽ
    evm_porting_picture_fmt_e ePicFmt;  //ͼƬ��ʽ

    /*���*/
    evm_u8 *pu8OutputData;  			//������ͼƬ���ݵ�ַ������ƽ̨��Ӧ���ֽ���洢��ɫ��Ϣ
    evm_u32 u32OutputLength;  			//������ͼƬ���ݳ���
    evm_u32 u32Width;  					//������ͼƬ���
    evm_u32 u32Height;  				//������ͼƬ�߶�
    evm_u32 u32Pitch;  					//������ͼƬһ����ռ�ֽ���
    evm_u32 u32Private;  				//˽������
    evm_u32 u32FrameCount;              //Numbers of pictures
    evm_u32 u32DelayTime;               //Duration between this frame and last frame (Units:10ms)
} evm_porting_HWImageDecoder_t;


/**
 * ����: evm_porting_imageDecoder_Init
 * ����: Initialyze image decoder.
 * �������:
 *      None
 * �������:
 *      None
 * ����: �μ�ret_code_e
 */

ret_code_e evm_porting_imageDecoder_Init(void);


/**
 * ����: evm_porting_DecodeImage
 * ����: ����ͼƬ����ѡ�ӿڡ����ƽ̨���ڸ�Ч�ʵ�ͼƬ����ӿڣ�Ӳ������ӿڣ���ʵ�ָú���������ֱ�ӷ��ؽ���ʧ��
 * �������:
 *      pstDecoderInfo: ��Ҫ�����ͼƬ��Ϣ
 * �������:
 *      ��
 * ����: �μ�ret_code_e
 */
ret_code_e evm_porting_DecodeImage(evm_porting_HWImageDecoder_t *pstDecoderInfo);

/**
 * ����: evm_porting_ReleaseImage
 * ����: �ͷŽ�����ͼƬ���ݣ���evm_porting_DecodeImageһ��ʵ�֡�
 * �������:
 *      pstDecoderInfo: ��Ҫ�ͷŵĽ����ͼƬ��Ϣ
 * �������:
 *      ��
 * ����: �μ�ret_code_e
 */
ret_code_e evm_porting_ReleaseImage(evm_porting_HWImageDecoder_t *pstDecoderInfo);


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* EVM_PORTING_IMAGEDECODER_H_ */
