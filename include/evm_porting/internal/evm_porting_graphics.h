/*
 *  evm_porting_graphics.h
 *  Copyright(C) EnRich DTV Group Co.,Ltd.
 *
 *  Description:
 *
 *  Created on: Jan 14, 2015
 *  Author: 沈辉<shenhui@evmtv.com>
 */

#ifndef EVM_PORTING_GRAPHICS_H_
#define EVM_PORTING_GRAPHICS_H_

#ifdef __cplusplus__
extern "C" {
#endif

#include "evm_typedef.h"

typedef enum
{
    EVM_PORTING_GRAPHICS_COLOR_OPERATION_COPY_E = 0,
    EVM_PORTING_GRAPHICS_COLOR_OPERATION_BLEND_E,

    EVM_PORTING_GRAPHICS_COLOR_OPERATION_BUTT_E,
} evm_porting_graphics_colorOperation_e;

//目前以argb8888为准
typedef struct
{
    evm_u32 u32Width;
    evm_u32 u32Height;
} evm_porting_graphics_surfaceAllocateInfo_t;

typedef struct
{
    evm_u32 u32Width;
    evm_u32 u32Height;
    evm_u32 u32Pitch; //bytes per line
    evm_u32 u32BitsPerPixel;
    void* pAddress;
} evm_porting_graphics_surfaceInfo_t;

typedef struct
{
    evm_u32 u32ArgbColor;
    evm_rect_t stFillRect;
    evm_porting_graphics_colorOperation_e eColorOperation;
} evm_porting_graphics_fillInfo_t;

typedef struct
{
    evm_rect_t stSrcRect;
    evm_rect_t stDstRect;
    evm_porting_graphics_colorOperation_e eColorOperation;
} evm_porting_graphics_BlitInfo_t;

typedef ret_code_e (*evm_porting_graphics_getOsdSurface_cb)(evm_handle *hSurface);
typedef ret_code_e (*evm_porting_graphics_allocateSurface_cb)(evm_handle *hSurface, evm_porting_graphics_surfaceAllocateInfo_t *pstAllocateInfo);
typedef ret_code_e (*evm_porting_graphics_freeSurface_cb)(evm_handle hSurface);
typedef ret_code_e (*evm_porting_graphics_getSurfaceInfo_cb)(evm_handle hSurface, evm_porting_graphics_surfaceInfo_t *pstSurfaceInfo);
typedef ret_code_e (*evm_porting_graphics_requestHwOperation_cb)(evm_handle hSurface);
typedef ret_code_e (*evm_porting_graphics_requestSwOperation_cb)(evm_handle hSurface);
typedef ret_code_e (*evm_porting_graphics_fillSurface_cb)(evm_handle hSurface, evm_porting_graphics_fillInfo_t *pstFillInfo);
typedef ret_code_e (*evm_porting_graphics_blitSurface_cb)(evm_handle hSrcSurface, evm_handle hDstSurface, evm_porting_graphics_BlitInfo_t *pstBlitInfo);

typedef struct
{
    struct
    {
        evm_bool bSupportHwOpeartion;
        evm_bool bSupportPreMult;

        evm_porting_graphics_getOsdSurface_cb pcbGetOsdSurface;
        evm_porting_graphics_allocateSurface_cb pcbAllocateSurface;
        evm_porting_graphics_freeSurface_cb pcbFreeSurface;
        evm_porting_graphics_getSurfaceInfo_cb pcbGetSurfaceInfo;

        evm_porting_graphics_requestSwOperation_cb pcbRequestSwOperation;
        evm_porting_graphics_requestHwOperation_cb pcbRequestHwOperation;
            
        evm_porting_graphics_fillSurface_cb pcbFillSurface;
        evm_porting_graphics_blitSurface_cb pcbBlitSurface;
    } stOut;
} evm_porting_graphics_initParam_t;

typedef struct
{
    evm_s32 reserved;
} evm_porting_graphics_deinitParam_t;

ret_code_e evm_porting_graphics_Init(evm_porting_graphics_initParam_t *pstInitParam);

ret_code_e evm_porting_graphics_DeInit(evm_porting_graphics_deinitParam_t *pstDeinitParam);

#ifdef __cplusplus__
}
#endif

#endif /* EVM_PORTING_GRAPHICS_H_ */
