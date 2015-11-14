/*
 * evm_porting_osd.h
 * Copyright(C) EnRich DTV Group Co.,Ltd.
 *
 * Description: 
 *
 * Authors: 研发三部
 */

#ifndef __EVM_PORTING_OSD_H__
#define __EVM_PORTING_OSD_H__

#include "evm_typedef.h"

typedef enum
{
    EVM_PORTING_OSD_ATTR_ID_INFO_E = 0,
    EVM_PORTING_OSD_ATTR_ID_ALPHA_E,
    EVM_PORTING_OSD_ATTR_ID_CLEAR_E,
    EVM_PORTING_OSD_ATTR_ID_ENABEL_UPDATE_E,
} evm_porting_osd_attrId_e;

typedef struct
{
    void *pBuffer;
    evm_u32 width;
    evm_u32 height;
} evm_porting_osd_surfaceInfo_t;

typedef struct
{

} evm_porting_osd_initParam_t;

typedef struct
{

} evm_porting_osd_deInitParam_t;

ret_code_e evm_porting_osd_Init(evm_porting_osd_initParam_t *pstInitParam);

ret_code_e evm_porting_osd_DeInit(evm_porting_osd_deInitParam_t *pstDeInitParam);

ret_code_e evm_porting_osd_GetHandle(evm_handle *pHandle, evm_s32 param);

ret_code_e evm_porting_osd_Update(evm_handle hOsd, evm_rect_t *pstSrcRect, evm_rect_t *pstDstRect, evm_s32 param);

//设置osd 透明度(0<=s32Alpha<=100)
ret_code_e evm_porting_OsdSetAlpha(evm_s32 s32Alpha);

ret_code_e evm_porting_osd_GetAttr(evm_handle hOsd, evm_porting_osd_attrId_e eAttrId, evm_s32 param);

ret_code_e evm_porting_osd_SetAttr(evm_handle hOsd, evm_porting_osd_attrId_e eAttrId, evm_s32 param);


ret_code_e evm_porting_osd_change_size(evm_s32 width, evm_s32 height);
#endif


