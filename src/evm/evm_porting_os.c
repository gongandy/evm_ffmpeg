/*
 * evm_porting_os.c
 * Copyright(C) EnRich DTV Group Co.,Ltd.
 *
 * Description: 
 *
 * Authors: 沈辉<shenhui@evmtv.com>
 *			Endy	<caifk@evmtv.com>
 */

#include <malloc.h>
#include <pthread.h>
#include <semaphore.h>
#include <sys/time.h>
#include <sys/times.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include <fcntl.h>
#include <sys/msg.h>
#include <sys/ipc.h>
#include <errno.h>
#include <sys/reboot.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <arpa/inet.h>
#include <net/route.h>
#include <net/if.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <netinet/tcp.h>
#include <netinet/ip_icmp.h>
#include <linux/sockios.h>
#include <linux/netlink.h>
#include <linux/rtnetlink.h>
#include <linux/ioctl.h>
#include <sys/wait.h>  
#include <net/if.h>
#include <sys/socket.h>
#include <netdb.h>

#include "evm_typedef.h"
#include "evm_porting/internal/evm_porting_os.h"
/*
#include "evm_porting/evm_porting.h"
#include "nexus_config.h"
#include "nexus_types.h"
#include "nexus_platform.h"



//TODO: init eplat ?????????????????????????????????????????????
static evm_bool bFlag = EVM_FALSE;
static void  __evm_porting_os_brcmInit()
{
    if( bFlag == EVM_TRUE)
    {
        return ;
    }
    NEXUS_PlatformConfiguration platformConfig;    
    NEXUS_PlatformSettings tSettings;
    NEXUS_Platform_GetDefaultSettings(&tSettings);
    tSettings.openFrontend = false;
    tSettings.videoDecoderModuleSettings.deferInit = true;
    NEXUS_Platform_Init(&tSettings);    
    NEXUS_Platform_GetConfiguration(&platformConfig);
    bFlag = EVM_TRUE;
    return ;
}
*/

ret_code_e evm_porting_os_Init()
{
//    HI_SYS_Init();
//    HI_SYS_PreAV(NULL);
//    __evm_porting_os_brcmInit();
    evm_porting_OsTimeInit();
    evm_poriting_OsEventInit();
    evm_porting_OsTimerInit();
    return EVM_SUCCESS;
}

ret_code_e evm_porting_OsDeInit()
{
    return EVM_SUCCESS;
}

//////////////////////////////memory operation///////////////////////////////////////
//int g_m = 0, g_c= 0, g_f = 0, g_r = 0, g_ff = 0, obj_c = 0, obj_d = 0;
//#ifdef EVM_MEMORY_DEBUG
//
//#else
//#define m_printf(fmt, ...)    do{}while(0)
//static void evm_porting_memroy_debug(evm_s8 param)
//{
//    return ;
//    switch (param)
//    {
//        case 1:
//            g_m++;
//            if ((g_m % 10) == 0 && g_m)
//                m_printf(YELLOW"malloc num = %d"NONE"\n", g_m);
//            break;
//
//        case 2:
//            g_c++;
//            if ((g_c % 10) == 0 && g_c)
//                m_printf(YELLOW"calloc num = %d"NONE"\n", g_c);
//            break;
//
//        case 3:
//            g_r++;
//            if ((g_r % 10) == 0 && g_r)
//                m_printf(YELLOW"realloc num = %d"NONE"\n", g_r);
//            break;
//
//        case 4:
//            g_f++;
//            if ((g_f % 10) == 0 && g_f)
//                m_printf(YELLOW"free num = %d free diff = %d"NONE"\n", g_f, g_m+g_r+g_c - g_f);
//            break;
//
//        default:
//            break;
//    }
//}

#if 0

#define EVM_PORTING_MEM_POOL_SIZE (1024)
#define EVM_PORTING_MMZ_MEM_SIZE (1024 * 512 * 3)
static pthread_mutex_t *spstMemoryMutex = EVM_NULL;
typedef struct
{
    int size;
    void* ptr;
} evm_porting_memNode_t;
static int ss32MemNodeSize = 0;
static int ss32MemOperationTimes = 0;
static evm_porting_memNode_t starrMemPool[EVM_PORTING_MEM_POOL_SIZE];

static void __memLock()
{
    if (!spstMemoryMutex)
    {
        spstMemoryMutex = calloc(1, sizeof(pthread_mutex_t));
        pthread_mutex_init(spstMemoryMutex, NULL);
    }

    pthread_mutex_lock(spstMemoryMutex);
}

static void __memUnlock()
{
    pthread_mutex_unlock(spstMemoryMutex);
}

static void __dumpMemory()
{
    ss32MemOperationTimes++;
    int total = 0;

    if (0 == (ss32MemOperationTimes % 100))
    {
        int i;

        for (i = 0; i < ss32MemNodeSize; i++)
            total += starrMemPool[i].size;

        //printf("####################mem total = %d\n", total);
    }
}

static void __addMemNode(int size, void* ptr)
{
    if (NULL == ptr)
        return;

    if (ss32MemNodeSize < EVM_PORTING_MEM_POOL_SIZE)
    {
        starrMemPool[ss32MemNodeSize].size = size;
        starrMemPool[ss32MemNodeSize].ptr = ptr;
        ss32MemNodeSize++;
        //__dumpMemory();
    }
    else
    {
        //printf("#############error memfull\n");
    }
}

static void __removeMemNode(void* ptr)
{
    int i;

    if (NULL == ptr)
        return;

    for (i = 0; i < ss32MemNodeSize; i++)
    {
        if (starrMemPool[i].ptr == ptr)
            break;
    }

    if (i < ss32MemNodeSize)
    {
        memmove(&starrMemPool[i], &starrMemPool[i + 1], (ss32MemNodeSize - i - 1) * sizeof(evm_porting_memNode_t));
        ss32MemNodeSize--;
        (void)__dumpMemory;
        //__dumpMemory();
    }
    else
    {
        //printf("#############error ptr %s\n", (char*)ptr);
    }
}
#endif 

void* evm_porting_OsMalloc(evm_u32 size)
{
//    HI_MMZ_BUF_S stBuf;
//
//    memset(&stBuf, 0, sizeof(HI_MMZ_BUF_S));
//
//    stBuf.bufsize = size;
//
//    HI_MMZ_Malloc(&stBuf);
//
//    return stBuf.user_viraddr;
//    evm_porting_memroy_debug(1);
//
//    __memLock();
    void *ptr = malloc(size);
//    __addMemNode(size, ptr);
//    __memUnlock();

    return ptr;
}

void* evm_porting_OsCalloc(evm_u32 n, evm_u32 size)
{
//    void *p = evm_porting_OsMalloc(n * size);
//
//    if (p)
//        memset(p, 0, n * size);
//    return p;
//    evm_porting_memroy_debug(2);
//
//    __memLock();
    void *ptr = calloc(n, size);
//    __addMemNode(n*size, ptr);
//    __memUnlock();

    return ptr;
}

void* evm_porting_OsRealloc(void* addr, evm_u32 size)
{
//    evm_porting_memroy_debug(3);
//
//    __memLock();
//    __removeMemNode(addr);
    void *ptr = realloc(addr, size);
//    __addMemNode(size, ptr);
//    __memUnlock();

    return ptr;
}

void evm_porting_OsFree(void* addr)
{
//    HI_MMZ_BUF_S stBuf;
//
//    memset(&stBuf, 0, sizeof(HI_MMZ_BUF_S));
//    HI_MMZ_GetPhyaddr(addr, &stBuf.phyaddr, &stBuf.bufsize);
//
//    HI_MMZ_Free(&stBuf);
//    evm_porting_memroy_debug(4);
//
//    __memLock();
//    __removeMemNode(addr);
    free(addr);
//    __memUnlock();
}

#if 0
void* evm_porting_OsSkiaMalloc(evm_u32 size)
{
    if (size > 8 * 1024)
    {
        HI_MMZ_BUF_S stBuf;

        memset(&stBuf, 0, sizeof(HI_MMZ_BUF_S));

        stBuf.bufsize = size;

        __memLock();

        if (ss32MemNodeSize + (size + 1) / 4096 * 4096 < EVM_PORTING_MMZ_MEM_SIZE)
        {
            if (EVM_SUCCESS == HI_MMZ_Malloc(&stBuf))
            {
                __addMemNode((size + 1) / 4096 * 4096, stBuf.user_viraddr);
                __memUnlock();
                return stBuf.user_viraddr;
            }
        }

        __memUnlock();
    }

    return malloc(size);
}


void* evm_porting_OsSkiaRealloc(void* addr, evm_u32 size)
{
    return realloc(addr, size);
}

void evm_porting_OsSkiaFree(void* addr)
{
    HI_MMZ_BUF_S stBuf;

    memset(&stBuf, 0, sizeof(HI_MMZ_BUF_S));

    if (EVM_SUCCESS == HI_MMZ_GetPhyaddr(addr, &stBuf.phyaddr, &stBuf.bufsize))
    {
        __memLock();
        __removeMemNode(addr);
        HI_MMZ_Free(&stBuf);
        __memUnlock();
    }
    else
    {
        free(addr);
    }
}
#endif 

//#endif

void* evm_porting_OsMemCpy(void* pDestBuf, const void* pSrcBuf, evm_u32 wSize)
{
    return memcpy(pDestBuf, pSrcBuf, wSize);
}

void* evm_porting_OsMemSet(void* pDestBuf, evm_u8 c, evm_u32 wSize)
{
    return memset(pDestBuf, c, wSize);
}

evm_s32 evm_porting_OsMemCmp(const void* pDestBuf, const void* pSrcBuf, evm_u32 wSize)
{
    return memcmp(pDestBuf, pSrcBuf, wSize);
}

void* evm_porting_OsMemMove(void *dest, const void *src, evm_u32 n)
{
    return memmove(dest, src, n);
}

evm_s32 evm_porting_OsOpen(const char *pathname,evm_s32 flags)
{
    return open(pathname,flags);
}

evm_s32 evm_porting_OsClose(evm_s32 fd)
{
    return close(fd);
}

evm_s32 evm_porting_OsRead(evm_s32 fd,void *buf,evm_u32 count)
{
    return read(fd,buf,count);
}

evm_s32 evm_porting_OsWrite(evm_s32 fd,const void *buf,evm_u32 count)
{

    return write(fd,buf,count);
}

evm_u32 evm_porting_OsLseek(evm_s32 fildes,evm_u32 offset,evm_s32 whence)
{
    return lseek(fildes,offset,whence);
}

evm_s32 evm_porting_OsFsync(evm_s32 fd)
{
    return fsync(fd);
}



//////////////////////////////////////////Debug operation/////////////////////////////////////////////////////////////
evm_s32 evm_porting_OsPrintf(const char* fmt, ...)
{
    evm_s32 s32Ret = -1;
#if 1
    va_list args;

    va_start(args, fmt);

    s32Ret = vprintf(fmt, args);

    va_end(args);
#endif
    return s32Ret;
}

evm_s32 evm_porting_OsSprintf(evm_s8 *buffer, const evm_s8 *format , ...)
{
    evm_s32 s32Ret;
    va_list args;

    va_start(args, format);

    s32Ret = vsprintf(buffer, format, args);

    va_end(args);

    return s32Ret;
}



//ret_code_e evm_porting_OsStandby(evm_bool bStandby)
//{
//
//    NEXUS_PlatformStandbySettings nexusStandbySettings;
//    NEXUS_Error rc;
//
//    extern ret_code_e evm_porting_pan_Standby();
//    evm_porting_pan_Standby();
//#if 1 //避免lowlater 模式待机死机
//    evm_porting_av_syncRef_e tSync = EVM_PORTING_AV_SYNC_REF_NONE_E;
//    evm_porting_av_PlayerGetAttr(0, EVM_PORTING_AV_PLAYER_ATTR_ID_SYNC_REF_E,(evm_u32)&tSync );
//
//    if(tSync == EVM_PORTING_AV_SYNC_REF_QUICK_OUTPUT_E)
//    {
//        evm_porting_av_PlayerStop(0, EVM_PORTING_AV_PLAYER_ONOFF_MODE_ALL_E, 0);
//        evm_porting_av_PlayerSetAttr(0, EVM_PORTING_AV_PLAYER_ATTR_ID_SYNC_REF_E, EVM_PORTING_AV_SYNC_REF_PCR_E);
//        evm_porting_av_PlayerStart(0, EVM_PORTING_AV_PLAYER_ONOFF_MODE_ALL_E, 0);
//
//    }
//
//    evm_porting_av_PlayerGetAttr(1, EVM_PORTING_AV_PLAYER_ATTR_ID_SYNC_REF_E,(evm_u32)&tSync );
//
//    if(tSync == EVM_PORTING_AV_SYNC_REF_QUICK_OUTPUT_E)
//    {
//        evm_porting_av_PlayerStop(1, EVM_PORTING_AV_PLAYER_ONOFF_MODE_ALL_E, 0);
//        evm_porting_av_PlayerSetAttr(1, EVM_PORTING_AV_PLAYER_ATTR_ID_SYNC_REF_E, EVM_PORTING_AV_SYNC_REF_PCR_E);
//        evm_porting_av_PlayerStart(1, EVM_PORTING_AV_PLAYER_ONOFF_MODE_ALL_E, 0);
//    }
//
//#endif /* if 0. 2015-1-28 12:27:55 evmqb */
//    NEXUS_Platform_GetStandbySettings(&nexusStandbySettings);
//    nexusStandbySettings.mode = NEXUS_PlatformStandbyMode_eDeepSleep;
//    nexusStandbySettings.wakeupSettings.ir = 1;
//    nexusStandbySettings.wakeupSettings.gpio = 1;
////    nexusStandbySettings.wakeupSettings.timeout = 0;
//    rc = NEXUS_Platform_SetStandbySettings(&nexusStandbySettings);
//    BDBG_ASSERT(!rc);
//
//#if 0
//    system("echo mem > /sys/power/state");
////system("echo standby > /sys/power/state");//
//    printf(" Wake up \n");
//
//#else
//    printf("S3 Cold Boot\n");
//    system("echo 1 > /sys/devices/platform/brcmstb/halt_mode");
//    system("halt");
//#endif /* if 0. 2014-12-31 10:16:11 evmqb */
//
//
//    return 0;
//
//}

evm_s32 evm_porting_OsReboot(evm_s32 s32DelayTime)
{
    sync();
    sleep(2);
    reboot(RB_AUTOBOOT);
    return EVM_SUCCESS;
}

evm_s32 evm_porting_OsSnprintf(evm_s8 *buffer, evm_u32 size, const evm_s8 *format , ...)
{
    int result;
    va_list args;
    va_start(args, format);
    result = vsnprintf(buffer, size, format, args);
    va_end(args);

    if (size > 0)
        buffer[size - 1] = '\0';

    return result;
}

evm_s32 evm_porting_OsVprintf(const char* fmt, va_list args)
{
    evm_s32 s32Ret = -1;
#if 1
    s32Ret = vprintf(fmt, args);
#endif
    return s32Ret;
}

evm_s32 evm_porting_OsVsprintf(evm_s8 *str, const evm_s8 *format, va_list ap)
{
    return vsprintf(str, format, ap);
}

evm_s32 evm_porting_OsVsnprintf(evm_s8 *str, evm_u32 size, const evm_s8 *format, va_list ap)
{
    evm_s32 nsize = 0;
    nsize = vsnprintf(str, sizeof(str) - 1, format, ap);
    return nsize;
}

evm_s8* evm_porting_OsStrDup(const evm_s8* src)
{
    return strdup(src);
}

evm_u64 evm_porting_OsStroull(const evm_s8 *nptr,evm_s8 **endptr,evm_s32 base)
{
    return strtoull(nptr,endptr,base);
}

evm_s8* evm_porting_OsStrnDup(const evm_s8* src, evm_u32 size)
{
    //return strndup(src, size);
    return strdup(src);
}

evm_u32 evm_porting_OsStrLen(const evm_s8* str)
{
    return strlen(str);
}

evm_s8* evm_porting_OsStrCpy(evm_s8* dest, const evm_s8* src)
{
    return strcpy(dest, src);
}

evm_s8* evm_porting_OsStrnCpy(evm_s8* dest, const evm_s8* src, evm_u32 size)
{
    return strncpy(dest, src, size);
}

evm_s8* evm_porting_OsStrStr(const evm_s8* haystack, const evm_s8* needle)
{
    return strstr(haystack, needle);
}

evm_s8* evm_porting_OsStrCaseStr(const evm_s8* haystack, const evm_s8* needle)
{	
	extern char* strcasestr(const char*, const char*);
    return strcasestr(haystack, needle);
}

evm_s8* evm_porting_OsStrChr(const evm_s8 *src, evm_s32 ch)
{
    return strchr(src, ch);
}

evm_s8* evm_porting_OsStrrChr(const evm_s8 *src, evm_s32 ch)
{
    return strrchr(src, ch);
}

evm_s32 evm_porting_OsSscanf(const evm_s8* str, const evm_s8 *fmt, ...)
{
    evm_s32 s32Ret = 0;
    va_list args;

    va_start(args, fmt);

    extern int vsscanf(const char *str, const char *format, va_list ap);
    s32Ret = vsscanf(str, fmt, args);

    va_end(args);

    return s32Ret;
}

evm_s8* evm_porting_OsStrCat(evm_s8 *dest, const evm_s8 *src)
{
    return strcat(dest, src);
}

evm_s8* evm_porting_OsStrnCat(evm_s8 *dest, const evm_s8 *src, evm_u32 n)
{
    return strncat(dest, src, n);
}

evm_s32 evm_porting_OsIsSpace(evm_s32 ch)
{
    return isspace(ch);
}

evm_s32 evm_porting_OsIsDigit(evm_s32 ch)
{
    return isdigit(ch);
}

evm_s32 evm_porting_OsStrCmp(const evm_s8* s1, const evm_s8* s2)
{
    return strcmp(s1, s2);
}

evm_s32 evm_porting_OsStrnCmp(const evm_s8* s1, const evm_s8* s2, evm_u32 size)
{
    return strncmp(s1, s2, size);
}

evm_s32 evm_porting_OsStrCaseCmp(const evm_s8* s1, const evm_s8* s2)
{
    return strcasecmp(s1, s2);
}

evm_s32 evm_porting_OsStrnCaseCmp(const evm_s8* s1, const evm_s8* s2, evm_u32 size)
{
    return strncasecmp(s1, s2, size);
}

evm_s32 evm_porting_OsAtoi(const evm_s8* s1)
{
	return atoi(s1);
}

evm_s32 evm_porting_OsStrtol(const char *nptr, char **endptr, int base)
{
	return strtol(nptr, endptr, base);
}
///////////////Thread operation////////////////////////////

ret_code_e evm_porting_OsCreateThreadPriv(evm_threadID* pThreadID, const char* name, void* (*pfn)(void*)\
        , void* param, evm_s32 stackSize, evm_porting_threadPriority_e priority)
{
    evm_s32 s32Ret = EVM_FAILURE;
    pthread_t *pstThread;
    pthread_attr_t attr;
    struct sched_param theadParam;

    theadParam.sched_priority = priority * 10 - 5 > 0 ? priority * 10 - 5 : 1;

    pthread_attr_init(&attr);

    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

    pthread_attr_setschedparam(&attr, &theadParam);

    pstThread = malloc(sizeof(pthread_t));
    if (!pstThread)
    {
        s32Ret = EVM_ERR_OUTOFMEMORY;
        goto end;
    }

    s32Ret = pthread_create(pstThread, &attr, pfn, (void*)param);
    if (0 == s32Ret)
    {
        *pThreadID = (evm_threadID)pstThread;
    }

    pthread_attr_destroy(&attr);

end:
    return s32Ret;
}

ret_code_e evm_porting_OsDestroyThread(evm_threadID threadID)
{
    evm_s32 s32Ret = EVM_FAILURE;
    pthread_t *pstThread;

    pstThread = (pthread_t *)threadID;
    if (!pstThread)
    {
        s32Ret = EVM_ERR_IDNOTEXIST;
        goto end;
    }
    

    s32Ret = pthread_cancel( *pstThread);
    free(pstThread);
    return EVM_SUCCESS;
//    return s32Ret;
end:
    return s32Ret;
}

ret_code_e evm_porting_OsThreadCreate(evm_threadID* pThreadID, evm_porting_threadAttr_t* attr, 
                                            void* (*pfn)(void*), void* param)
{
    return pthread_create((pthread_t *)pThreadID, (pthread_attr_t*)attr, pfn, param);
}

ret_code_e evm_porting_OsThreadCancel(evm_threadID pThreadID)
{
    return  pthread_cancel((pthread_t )pThreadID);
}

ret_code_e evm_porting_OsThreadJoin(evm_threadID pThreadID, void** retval)
{
    return pthread_join((pthread_t )pThreadID, retval);
}

evm_threadID evm_porting_OsThreadSelf()
{
    evm_threadID threadId;
    
    threadId = pthread_self();;
    return threadId;
}


ret_code_e evm_porting_OsDelay(evm_u32 ms)
{
    return usleep(ms*1000);
}



evm_u32 evm_porting_OsSClock()
{
    struct timeval tv = {0};

    gettimeofday(&tv, EVM_NULL);

    return (tv.tv_sec);
}

evm_s32 evm_porting_OsGetTimeZone()
{
    struct timezone tz = {0};
    struct timeval tv = {0};

    gettimeofday(&tv, &tz);

    return (tz.tz_minuteswest / 60);
}

evm_s32 evm_porting_OsSetTimeZone(evm_s32 time)
{
    struct timezone tz = {0};
    struct timeval tv = {0};

    gettimeofday(&tv, &tz);

    if (tv.tv_sec > (evm_porting_OsGetTimeZone() - time) * 3600)
        tv.tv_sec = tv.tv_sec + ((time - evm_porting_OsGetTimeZone()) * 60 * 60);
    tz.tz_minuteswest = time * 60;

    settimeofday(&tv, &tz);

    return EVM_SUCCESS;
}

static evm_s32 ss32TickPerSecond = 100;

ret_code_e evm_porting_OsTimeInit()
{
    //获取每秒的tick次数
    ss32TickPerSecond = sysconf(_SC_CLK_TCK);

    return EVM_SUCCESS;
}

evm_s32 evm_porting_OsTickTime()
{
#if 0
    clock_t ticks;
    struct tms stTms;
    static evm_s32 tickTimes = 0;

    ticks = times(&stTms);

//    printf("* %lu **u = %lu **s = %lu **c = %lu **c = %lu **** \n", ticks, stTms.tms_utime, stTms.tms_stime, stTms.tms_cstime, stTms.tms_cutime);

    if ((clock_t)-1 == ticks)
    {
        printf("get times failed, error = %d\n", errno);
    }
    else
    {
        if (ss32TickPerSecond == 100)
        {
            tickTimes = (evm_s32)(((evm_s64)ticks) * 10);
        }
        else
        {
            tickTimes = (evm_s32)(((evm_s64)ticks) * 1000 / ss32TickPerSecond);
        }
    }
    return tickTimes;
#else
    evm_u32 ms = 0;
    struct timeval struTime = {0};

    gettimeofday(&struTime, NULL);
    ms = struTime.tv_sec * 1000 + struTime.tv_usec / 1000;

    return ms;
#endif    
}
//////////////////////////////////////////Mutex operation/////////////////////////////////////////////////////////////
ret_code_e evm_porting_OsCreateMutex(evm_mutexID* pMutexID)
{
    evm_s32 s32Ret = EVM_FAILURE;
    pthread_mutex_t *pstMutex = EVM_NULL;

    pstMutex = malloc(sizeof(pthread_mutex_t));
    if (!pstMutex)
    {
        s32Ret = EVM_ERR_OUTOFMEMORY;
        goto end;
    }

    s32Ret = pthread_mutex_init(pstMutex, EVM_NULL);
    if (0 == s32Ret)
    {
        *pMutexID = (evm_mutexID)pstMutex;
    }

end:
    return s32Ret;
}

ret_code_e evm_porting_OsDestroyMutex(evm_mutexID mutexID)
{
    evm_s32 s32Ret = EVM_FAILURE;
    pthread_mutex_t *pstMutex = EVM_NULL;

    pstMutex = (pthread_mutex_t *)mutexID;
    if (!pstMutex)
    {
        s32Ret = EVM_ERR_IDNOTEXIST;
        goto end;
    }

    s32Ret = pthread_mutex_destroy(pstMutex);
    free(pstMutex);

end:
    return s32Ret;
}

#if 0
extern  evm_mutexID dmxMutex ;
static evm_u32 countDmx = 0;
#endif /* if 0. 2014-12-2 13:08:53 evmqb */

ret_code_e evm_porting_OsMutexLock(evm_mutexID mutexID)
{
    evm_s32 s32Ret = EVM_FAILURE;
    pthread_mutex_t *pstMutex = EVM_NULL;
    
    pstMutex = (pthread_mutex_t *)mutexID;
    if (!pstMutex)
    {
        s32Ret = EVM_ERR_IDNOTEXIST;
        goto end;
    }

    s32Ret = pthread_mutex_lock(pstMutex);
#if 0
    if(dmxMutex == mutexID)
    {
        countDmx++;
        printf("dmxMutex to lock end \n ");
    }
#endif /* if 0. 2014-12-2 13:08:40 evmqb */

    end:
    return s32Ret;
}

ret_code_e evm_porting_OsMutexUnlock(evm_mutexID mutexID)
{
    evm_s32 s32Ret = EVM_FAILURE;
    pthread_mutex_t *pstMutex = EVM_NULL;

    pstMutex = (pthread_mutex_t *)mutexID;
    if (!pstMutex)
    {
        s32Ret = EVM_ERR_IDNOTEXIST;
        goto end;
    }

    s32Ret = pthread_mutex_unlock(pstMutex);

#if 0
    if(dmxMutex == mutexID)
    {
        countDmx--;
        printf("dmxMutex to unlock end countDmx:%d mutexID:%d  \n ",countDmx,mutexID);
    }

#endif /* if 0. 2014-12-2 13:09:14 evmqb */
end:
    return s32Ret;
}


ret_code_e evm_porting_OsMutexTryLock(evm_mutexID mutexID)
{
    evm_s32 s32Ret = EVM_FAILURE;
    pthread_mutex_t *pstMutex = EVM_NULL;

    pstMutex = (pthread_mutex_t *)mutexID;
    if (!pstMutex)
    {
        s32Ret = EVM_ERR_IDNOTEXIST;
        goto end;
    }

    ;
    while((s32Ret = pthread_mutex_trylock(pstMutex) )!= EVM_SUCCESS)
    {
        printf(" pthread_mutex_trylock:%d \n",s32Ret);
        usleep(10*1000);
        if(s32Ret == 22)
        {
            break;
        }
    }
end:
    return s32Ret;
}



//////////////////////////////////////////Semaphore operation/////////////////////////////////////////////////////////////
ret_code_e evm_porting_OsCreateSem(evm_semID* pSemID, evm_u32 count)
{
    evm_s32 s32Ret = EVM_FAILURE;
    sem_t *pstSem = EVM_NULL;

    pstSem = malloc(sizeof(sem_t));
    if (!pstSem)
    {
        s32Ret = EVM_ERR_OUTOFMEMORY;
        goto end;
    }

    s32Ret = sem_init(pstSem, 0, count);
    if (0 == s32Ret)
    {
        *pSemID = (evm_semID)pstSem;
    }

end:
    return s32Ret;
}

ret_code_e evm_porting_OsDestroySem(evm_semID semID)
{
    evm_s32 s32Ret = EVM_FAILURE;
    sem_t *pstSem = EVM_NULL;

    pstSem = (sem_t *)semID;
    if (!pstSem)
    {
        s32Ret = EVM_ERR_IDNOTEXIST;
        goto end;
    }

    s32Ret = sem_destroy(pstSem);
    free(pstSem);

end:
    return s32Ret;
}

ret_code_e evm_porting_OsSemWait(evm_semID semID, evm_u32 ms)
{
    evm_s32 s32Ret = EVM_FAILURE;
    evm_u32 waitTime = 0;
    sem_t *pstSem = EVM_NULL;

    pstSem = (sem_t *)semID;
    if (!pstSem)
    {
        s32Ret = EVM_ERR_IDNOTEXIST;
        goto end;
    }

    if (0 == sem_trywait(pstSem))
    {
        s32Ret = EVM_SUCCESS;
        goto end;
    }

    while (waitTime < ms)
    {
        if (0 == sem_trywait(pstSem))
        {
            s32Ret = EVM_SUCCESS;
            break;
        }

        waitTime += 10;
        usleep(10*1000);
    }

    if (EVM_SUCCESS != s32Ret)
    {
        
        s32Ret = EVM_ERR_TIMEOUT;
    }

end:
    return s32Ret;
}

ret_code_e evm_porting_OsSemPost(evm_semID semID)
{
    evm_s32 s32Ret = EVM_FAILURE;
    sem_t *pstSem = EVM_NULL;

    pstSem = (sem_t *)semID;
    if (!pstSem)
    {
        s32Ret = EVM_ERR_IDNOTEXIST;
        goto end;
    }

    s32Ret = sem_post(pstSem);

end:
    return s32Ret;
}

ret_code_e evm_porting_OsSemGetCount(evm_semID semID,evm_s32 *count)
{
    evm_s32 s32Ret = EVM_FAILURE;
    sem_t *pstSem = EVM_NULL;

    pstSem = (sem_t *)semID;
    if (!pstSem)
    {
        s32Ret = EVM_ERR_IDNOTEXIST;
        goto end;
    }

    s32Ret = sem_getvalue(pstSem,count);

end:
    return s32Ret;
}



ret_code_e evm_porting_OsMsgCreat(evm_u32 *MsgId, evm_u32 MsgNum, evm_u32 MsgSize)
{
    int msgid;

    if( MsgNum >16384 )
    {
        printf( "### waring message max len is 16384 !\n");
    }

    msgid = msgget( IPC_PRIVATE, IPC_EXCL|IPC_CREAT|0660 ); //0666
    if( 0 > msgid )
    {
        printf( "### msgget failed ! msgid=%d errno=%d\n", msgid,errno );
        if( errno==ENOSPC)  //这时是无法恢复的了
        {
            perror("we are going to reboot now, because of msgget");
            //system("reboot");
        }
        return EVM_FAILURE;
    }

    *MsgId = msgid+1;
    /*linux 0 is valid*/
    return EVM_SUCCESS;
}

#define EVM_PORTING_MSG_TYPE (1)
typedef struct _evm_porting_msgbuf_t_
{
    long mtype;
    char mtext[1];
} evm_porting_msgbuf_t;

ret_code_e evm_porting_OsMsgSend(evm_u32 MsgId , void *Msg , evm_u32 MsgSize ,evm_u32 Timeout)
{
    int msgid;
    evm_porting_msgbuf_t *pstMsg = NULL;

    if( MsgId <= 0 ){
        printf( "### handle error !\n" );
        return EVM_FAILURE;
    }

    if( EVM_NULL == Msg )
    {
        printf( "### msg is NULL !\n" );
        return EVM_FAILURE;
    }

    pstMsg = malloc(sizeof(evm_porting_msgbuf_t) + MsgSize - 1);
    if (!pstMsg)
    {
        printf( "out of memory\n" );
        return EVM_FAILURE;
    }
    pstMsg->mtype = EVM_PORTING_MSG_TYPE;
    memcpy(pstMsg->mtext, Msg, MsgSize);

    msgid = MsgId-1;
    if( EVM_SUCCESS != msgsnd(msgid, pstMsg, MsgSize, IPC_NOWAIT) )
    {
        printf( "###msgsnd failed ! errno =%d \n",errno);
        free(pstMsg);
        return EVM_FAILURE;
    }
    free(pstMsg);
    return EVM_SUCCESS;
}

ret_code_e evm_porting_OsMsgReceive(evm_u32 MsgId , void *MsgBuf ,evm_u32 *MsgSize , evm_u32 Timeout)
{
    int ret;
    int msgid;
    struct timeval tv1;
    struct timeval tv2;
    struct timezone tz;
    evm_porting_msgbuf_t *pstMsg = NULL;
    int s32MsgSize;

    if( MsgId <= 0 )
    {
        printf("handle error\n");
        return EVM_FAILURE;
    }

    if (!MsgBuf || !MsgSize)
    {
        printf("param error\n");
        return EVM_FAILURE;
    }

    pstMsg = malloc(sizeof(evm_porting_msgbuf_t) + *MsgSize - 1);
    if (!pstMsg)
    {
        printf( "out of memory\n" );
        return EVM_FAILURE;
    }
    s32MsgSize = sizeof(evm_porting_msgbuf_t) + *MsgSize - 1;

    msgid = MsgId-1;
    gettimeofday(&tv1, &tz);
    
    tv1.tv_sec += Timeout/1000;
    tv1.tv_usec +=0;
    do
    {
        gettimeofday(&tv2, &tz);
        ret = msgrcv(msgid, pstMsg, s32MsgSize, EVM_PORTING_MSG_TYPE, IPC_NOWAIT);
        if (EVM_FAILURE  == ret)
        {
            if( ENOMSG != errno)
            {
                printf("msgrcv failed ! errno=%d\n", errno );
                free(pstMsg);
                return EVM_FAILURE;   
            }
        }
        else
        {
            memcpy(MsgBuf, pstMsg->mtext, *MsgSize);
            free(pstMsg);
            return EVM_SUCCESS;
        }
        if( (tv2.tv_sec>tv1.tv_sec) )
        {
            break;
        }
        else if( (tv2.tv_sec==tv1.tv_sec) && (tv2.tv_usec>=tv1.tv_usec) )
        {
            break;
        }
        usleep(1000);
    } while(1);

    free(pstMsg);
    return EVM_ERR_TIMEOUT;
}


ret_code_e evm_porting_OsMsgDestroy(evm_u32 MsgId)
{
    evm_s32 s32Ret = EVM_FAILURE;
    evm_s32 s32MsgId = MsgId-1;
    
    s32Ret= msgctl(s32MsgId, IPC_RMID, NULL);
    if(s32Ret != EVM_SUCCESS)
    {
        return EVM_FAILURE;
    }
    else
    {
        return EVM_SUCCESS;
    }
}

//////////////////////////////////////////Timer operation/////////////////////////////////////////////////////////////
#define EVM_PORTING_OS_TIMER_MAX_CNT (256)
#define EVM_PORTING_OS_TIMER_MAX_DELAY_TIME (100)

typedef struct _evm_porting_timerObject_t_
{
    evm_u32 u32Dealy;
    evm_u32 u32Interval;
    evm_bool bRepeat;
    evm_porting_os_timer_cb pcbCallback;
    void *pPrivate;

    evm_s32 s32NextInvokeTime;
    evm_bool bInUse;
} evm_porting_timerObject_t;

typedef struct _evm_porting_timerPool_t_
{
    evm_mutexID mutex;
    evm_threadID thread;

    evm_porting_timerObject_t stTimers[EVM_PORTING_OS_TIMER_MAX_CNT];
} evm_porting_timerPool_t;

static evm_porting_timerPool_t *spstTimerPool = EVM_NULL;

static void* __evm_porting_OsTimerTask(void* param)
{
    evm_u32 u32DelayTime;
    evm_s32 i, s32CurrentTime, s32MinInvokeTime = 0;

    while (1)
    {
        evm_porting_OsMutexLock(spstTimerPool->mutex);

        //计算时间最近的
        s32MinInvokeTime = 0x7fffffff;
        for (i = 0; i < EVM_PORTING_OS_TIMER_MAX_CNT; i++)
        {
            if (spstTimerPool->stTimers[i].bInUse)
                s32MinInvokeTime = EVM_MIN(s32MinInvokeTime, spstTimerPool->stTimers[i].s32NextInvokeTime);
        }

        s32CurrentTime = evm_porting_OsTickTime();
        if (s32CurrentTime < s32MinInvokeTime)
        {
            u32DelayTime = s32MinInvokeTime - s32CurrentTime;
            //防止某个timer间隔太长，可能卡住后面加入的间隔短的timer
            if (u32DelayTime > EVM_PORTING_OS_TIMER_MAX_DELAY_TIME)
                u32DelayTime = EVM_PORTING_OS_TIMER_MAX_DELAY_TIME;
        }
        else
        {
            //有timer触发
            for (i = 0; i < EVM_PORTING_OS_TIMER_MAX_CNT; i++)
            {
                if (spstTimerPool->stTimers[i].bInUse && (s32CurrentTime >= spstTimerPool->stTimers[i].s32NextInvokeTime))
                {
                    evm_porting_os_timer_cb pcbCallback = spstTimerPool->stTimers[i].pcbCallback;
                    void *pPrivate = spstTimerPool->stTimers[i].pPrivate;

                    if (spstTimerPool->stTimers[i].bRepeat)
                    {
                        spstTimerPool->stTimers[i].s32NextInvokeTime += spstTimerPool->stTimers[i].u32Interval;
                    }
                    else
                    {
                        spstTimerPool->stTimers[i].s32NextInvokeTime = 0x7fffffff;
                    }

                    evm_porting_OsMutexUnlock(spstTimerPool->mutex);

                    pcbCallback(pPrivate);

                    evm_porting_OsMutexLock(spstTimerPool->mutex);
                }
            }
        }
        evm_porting_OsMutexUnlock(spstTimerPool->mutex);

        //等待
        if (0 != u32DelayTime)
            evm_porting_OsDelay(u32DelayTime);
    }

    return EVM_NULL;
}

ret_code_e evm_porting_OsTimerInit()
{
    evm_s32 s32Ret = EVM_FAILURE;

    if (spstTimerPool)
    {
        EVM_INFO_PRINT("timer has been inited already\n");
        s32Ret = EVM_SUCCESS;
        goto end;
    }

    spstTimerPool = evm_porting_OsCalloc(1, sizeof(evm_porting_timerPool_t));
    if (!spstTimerPool)
    {
        EVM_ERROR_PRINT("allocate memory for spstTimerPool failed\n");
        s32Ret = EVM_ERR_OUTOFMEMORY;
        goto end;
    }

    s32Ret = evm_porting_OsCreateMutex(&spstTimerPool->mutex);
    if (EVM_SUCCESS != s32Ret)
    {
        EVM_ERROR_PRINT("create mutex failed\n");
        goto end;
    }

    s32Ret = evm_porting_OsCreateThreadPriv(&spstTimerPool->thread, "timer task", __evm_porting_OsTimerTask, \
            EVM_NULL, EVM_PORTING_THREADSTACKSIZE_NOR, EVM_PORTING_THREADPRIORITY_MAX);
    if (EVM_SUCCESS != s32Ret)
    {
        EVM_ERROR_PRINT("create thread failed\n");
        goto end;
    }

end:
    return s32Ret;
}
 
ret_code_e evm_porting_OsTimerCreate(evm_u32 *TimerId, evm_porting_os_timer_cb pcbCallback, void *Param, evm_u32 u32Delay, evm_u32 u32Interval, evm_bool bRepeat)
{
    evm_s32 s32Ret = EVM_FAILURE, i;

    if (!spstTimerPool)
    {
        printf("timer has not been inited already\n");
        goto end;
    }

    if (!TimerId)
    {
        printf("param error\n");
        goto end;
    }

    evm_porting_OsMutexLock(spstTimerPool->mutex);

    for (i = 0; i < EVM_PORTING_OS_TIMER_MAX_CNT; i++)
    {
        if (!spstTimerPool->stTimers[i].bInUse)
        {
            break;
        }
    }

    if (i < EVM_PORTING_OS_TIMER_MAX_CNT)
    {
        spstTimerPool->stTimers[i].bRepeat = bRepeat;
        spstTimerPool->stTimers[i].pPrivate = Param;
        spstTimerPool->stTimers[i].pcbCallback = pcbCallback;
        spstTimerPool->stTimers[i].u32Dealy = u32Delay;

        //防止数据溢出，我们只允许这么大的timer
        if (u32Interval > 0x40000000)
            u32Interval = 0x40000000;
        spstTimerPool->stTimers[i].u32Interval = u32Interval;

        if (u32Delay > 0x40000000)
            u32Delay = 0x40000000;
        spstTimerPool->stTimers[i].s32NextInvokeTime = evm_porting_OsTickTime() + u32Delay;

        spstTimerPool->stTimers[i].bInUse = EVM_TRUE;

        *TimerId = i;

        s32Ret= EVM_SUCCESS;
    }
    else
    {
        printf("timer resource is not enough\n");

        s32Ret = EVM_FAILURE;
    }

    evm_porting_OsMutexUnlock(spstTimerPool->mutex);

end:
    return s32Ret;
}

ret_code_e evm_porting_OsTimerReset(evm_u32 TimerId, evm_u32 u32Interval)
{
    evm_s32 s32Ret = EVM_FAILURE;

    if (!spstTimerPool)
    {
        EVM_INFO_PRINT("timer has not been inited already\n");
        goto end;
    }

    if (TimerId < 0 || TimerId >= EVM_PORTING_OS_TIMER_MAX_CNT)
    {
        EVM_INFO_PRINT("timer id error\n");
        goto end;
    }

    evm_porting_OsMutexLock(spstTimerPool->mutex);

    if (u32Interval > 0x40000000)
        u32Interval = 0x40000000;

    spstTimerPool->stTimers[TimerId].s32NextInvokeTime = evm_porting_OsTickTime() + u32Interval;
    spstTimerPool->stTimers[TimerId].u32Interval = u32Interval;

    s32Ret = EVM_SUCCESS;

    evm_porting_OsMutexUnlock(spstTimerPool->mutex);

end:
    return s32Ret;
}

ret_code_e evm_porting_OsTimerDestroy(evm_u32  TimerId)
{
    evm_s32 s32Ret = EVM_FAILURE;

    if (!spstTimerPool)
    {
        EVM_INFO_PRINT("timer has not been inited already\n");
        goto end;
    }

    if (TimerId >= EVM_PORTING_OS_TIMER_MAX_CNT)
    {
        EVM_INFO_PRINT("timer id error\n");
        goto end;
    }

    evm_porting_OsMutexLock(spstTimerPool->mutex);

    spstTimerPool->stTimers[TimerId].bInUse = EVM_FALSE;

    s32Ret = EVM_SUCCESS;

    evm_porting_OsMutexUnlock(spstTimerPool->mutex);

end:
    return s32Ret;
}

//////////////////////////////////////////Event operation/////////////////////////////////////////////////////////////
typedef struct _evm_porting_waittask_s
{
    evm_semID semID;
    evm_porting_eventType_e u32Opt;      /* operation, and, or, clr */
    evm_u32 u32Request;  /* requested events */
    struct _evm_porting_waittask_s * pstruPrev;
    struct _evm_porting_waittask_s * pstruNext;
}evm_porting_waittask_s;

typedef struct _evm_porting_eventObject_s
{
    evm_u32  u32EventId;
    evm_u32 u32Flag;
    evm_mutexID mutexID;
    evm_bool bDestory;
    evm_porting_waittask_s struHead;
}evm_porting_eventObject_s;

static evm_porting_eventObject_s   gEventFlag[EVM_EVENT_NUM_MAX];
static evm_mutexID  gEventMutex;

#define EVENT_INVALID_HANDLE 0xffffffff 

#define CHECK_EVENT_FAIL_AND_RETURN(bFlag,mutexId)  \
    if(bFlag == EVM_TRUE)   \
    {   \
        evm_porting_OsMutexUnlock(mutexId );    \
        return EVM_ERR_SRCNOTEXIST; \
        }    


ret_code_e evm_poriting_OsEventInit()
{
    evm_u32  i;
    ret_code_e eRet =EVM_FAILURE;
    
    for ( i = 0; i < EVM_EVENT_NUM_MAX; i++ )
    {
        gEventFlag[i].u32EventId =EVENT_INVALID_HANDLE ;
    }

    eRet=evm_porting_OsCreateMutex(&gEventMutex);
    if(eRet!=EVM_SUCCESS)
    {
        EVM_ERROR_PRINT("evm_porting_OsCreateMutex  gEventMutex error \n");
        return EVM_FAILURE;
    }
    return EVM_SUCCESS;
}
ret_code_e evm_porting_OsEventCreate(evm_u32 *EventId)
{
    evm_u32 i;
    ret_code_e eRet =EVM_FAILURE;
    
    if(EventId ==EVM_NULL)
    {
        EVM_ERROR_PRINT("invalid param  EventId null \n");
        return EVM_FAILURE;
    }
    evm_porting_OsMutexLock( gEventMutex );
    for ( i = 0; i < EVM_EVENT_NUM_MAX; i++ )
    {
        /* found an unused element */
        if ( EVENT_INVALID_HANDLE == gEventFlag[i].u32EventId )
        {
            gEventFlag[i].u32EventId = i;
            gEventFlag[i].u32Flag = 0;
            gEventFlag[i].bDestory = EVM_FALSE;
            gEventFlag[i].struHead.pstruNext = &gEventFlag[i].struHead;
            gEventFlag[i].struHead.pstruPrev = &gEventFlag[i].struHead;
            eRet=evm_porting_OsCreateMutex( &gEventFlag[i].mutexID);
            if(eRet!=EVM_SUCCESS)
            {
                EVM_ERROR_PRINT("create mutex error \n");
                evm_porting_OsMutexUnlock( gEventMutex);
                return EVM_FAILURE;
            }
            *EventId = i;
            evm_porting_OsMutexUnlock(gEventMutex );
            return EVM_SUCCESS;
        }
    }
    evm_porting_OsMutexUnlock( gEventMutex );
    EVM_ERROR_PRINT("not left event to create \n");
    return EVM_FAILURE;
}


static void  OSFlagAddToTail( evm_porting_eventObject_s *psEventObj, evm_porting_waittask_s *pstruNode )
{
    if ( ( EVM_NULL == psEventObj) || ( EVM_NULL == pstruNode) )
    {
        EVM_ERROR_PRINT("OSFlagAddToTail invalid arguments\n");
        return;
    }
    pstruNode->pstruPrev = psEventObj->struHead.pstruPrev;
    pstruNode->pstruNext = &psEventObj->struHead;
    pstruNode->pstruPrev->pstruNext = pstruNode;
    pstruNode->pstruNext->pstruPrev = pstruNode;
    return ;
}

static void  OSFlagDelNode( evm_porting_eventObject_s *psEventObj, evm_porting_waittask_s *pstruNode )
{
    evm_porting_waittask_s *pstruCurrTask;
    
    if ( ( EVM_NULL == psEventObj) || ( EVM_NULL == pstruNode) )
    {
        EVM_ERROR_PRINT("OSFlagAddToTail invalid arguments\n");
        return;
    }

    pstruCurrTask = psEventObj->struHead.pstruNext;

    while ( ( pstruCurrTask != pstruNode ) && ( pstruCurrTask != &psEventObj->struHead ) )
    {
        pstruCurrTask = pstruCurrTask->pstruNext;
    }

    if ( &psEventObj->struHead == pstruCurrTask )
    {
        EVM_ERROR_PRINT("OSFlagDelNode failed, not found specified node\n");
        return;
    }
    
    if(pstruCurrTask && pstruCurrTask->pstruNext)
    {
        pstruCurrTask->pstruNext->pstruPrev = pstruCurrTask->pstruPrev;
    }
    
    if(pstruCurrTask && pstruCurrTask->pstruPrev)
    {
        pstruCurrTask->pstruPrev->pstruNext = pstruCurrTask->pstruNext;
    }

    return;
}

ret_code_e evm_porting_OsEventWait(evm_u32 EventId , evm_u32 Pattern , evm_porting_eventType_e eEventType,evm_u32 *Value,evm_u32 Timeout)
{
    evm_u32 i;
    ret_code_e eRet = 0;
    evm_u32 compare;
    evm_porting_waittask_s *pstruCurrTask;

    for ( i = 0; i < EVM_EVENT_NUM_MAX; i++ )
    {
        /* found corresponding element */
        if ( EventId == gEventFlag[i].u32EventId )
        {
            eRet = evm_porting_OsMutexTryLock( gEventFlag[i].mutexID);
            if(eRet == 22)//锁已经销毁
            {
                eRet = EVM_ERR_IDNOTEXIST;
                break;
            }
            CHECK_EVENT_FAIL_AND_RETURN(gEventFlag[i].bDestory, gEventFlag[i].mutexID);
            /* Isolate common event flags.  */
            compare =  gEventFlag[i].u32Flag & Pattern;

            /* Determine if all of the events must be present.  */
            if (eEventType & EVM_PORTING_EVENTTYPE_ANDSET)
            {
                /* Yes, all events must be present.  See if the compare value is
                   the same as the requested value.  */
                compare =  (compare == Pattern);
            }

            /* Determine if the requested combination of event flags are present.  */
            if (compare)
            {

                /* Yes, necessary event flags are present.  */

                /* Copy the current event flags into the appropriate destination.  */
                *Value =  gEventFlag[i].u32Flag;

                /* Determine if consumption is required.  If so, consume the event
                   flags present in the group.  */
                if (eEventType & EVM_PORTING_EVENTTYPE_CLEARSET)
                {
                    gEventFlag[i].u32Flag = gEventFlag[i].u32Flag & ( ~Pattern );
                }      

                
                evm_porting_OsMutexUnlock( gEventFlag[i].mutexID);
                
                return eRet;

            }
            else
            {

                /* Determine if the task requested suspension.  */
                if (Timeout)
                {
                    /* Suspension is selected.  */

                    /* allocate an element */
                    pstruCurrTask = ( evm_porting_waittask_s * )malloc( sizeof( evm_porting_waittask_s ) );
                    if ( EVM_NULL == pstruCurrTask )
                    {
                        EVM_ERROR_PRINT("out of memory\n");
                        return -1;
                    }

                    pstruCurrTask->u32Opt = eEventType;
                    pstruCurrTask->u32Request = Pattern;
                    evm_porting_OsCreateSem( &pstruCurrTask->semID,0);                   

                    OSFlagAddToTail( &gEventFlag[i], pstruCurrTask );
                    /* Isolate common event flags.  */
                    compare =  gEventFlag[i].u32Flag & Pattern;

                    /* Determine if all of the events must be present.  */
                    if (eEventType & EVM_PORTING_EVENTTYPE_ANDSET)
                    {
                        /* Yes, all events must be present.  See if the compare value is
                           the same as the requested value.  */
                        compare =  (compare == Pattern);
                    }

                    /* Determine if the requested combination of event flags are present.  */
                    if ( compare)
                    {
                        
                    }
                    else    
                    {
                        
                        evm_porting_OsMutexUnlock( gEventFlag[i].mutexID);
                        
                        if ( EVM_PORTING_WAITFOREVER == Timeout )
                        {
                            evm_porting_OsSemWait( pstruCurrTask->semID,EVM_PORTING_WAITFOREVER);
                        }
                        else
                        {
                            while ( Timeout > 0 )
                            {
                                eRet = evm_porting_OsSemWait( pstruCurrTask->semID,0);
                                if ( 0 == eRet )
                                {
                                    break;
                                }
                                evm_porting_OsDelay(1);
                                Timeout--;
                            }

                        }
                        
                       evm_porting_OsMutexLock( gEventFlag[i].mutexID);
                        
                    }

                    OSFlagDelNode( &gEventFlag[i], pstruCurrTask );

                    /* free the delteted node */
                    evm_porting_OsDestroySem( pstruCurrTask->semID);
                    free( pstruCurrTask );


                    /* Copy the current event flags into the appropriate destination.  */
                    *Value =  gEventFlag[i].u32Flag;
                    /* Determine if consumption is required.  If so, consume the event
                       flags present in the group.  */
                    if (eEventType & EVM_PORTING_EVENTTYPE_CLEARSET)
                    {
                        gEventFlag[i].u32Flag = gEventFlag[i].u32Flag & ( ~Pattern );
                    }      
                }
                else
                {

                    /* No suspension requested.  Simply return an error status
                       and zero the retrieved events variable.  */
                    eRet = -1;
                    *Value = 0;
                }
                
                evm_porting_OsMutexUnlock( gEventFlag[i].mutexID );
                
                return eRet;
            }
            
            evm_porting_OsMutexUnlock( gEventFlag[i].mutexID);
            
        }
    }

    return EVM_FAILURE;
}

ret_code_e evm_porting_OsEventSet(evm_u32 EventId , evm_u32 Mask)
{
    evm_u32 i;
    evm_porting_waittask_s *pstruCurrTask;
    evm_u32 compare;
    ret_code_e eRet = EVM_SUCCESS ;

    for ( i = 0; i < EVM_EVENT_NUM_MAX; i++ )
    {
        /* found corresponding element */
        if ( EventId == gEventFlag[i].u32EventId )
        {
            /* set the flag */

            eRet = evm_porting_OsMutexTryLock( gEventFlag[i].mutexID);
            if(eRet == 22)//锁已经销毁
            {
                eRet = EVM_ERR_IDNOTEXIST;
                break;
            }
            CHECK_EVENT_FAIL_AND_RETURN(gEventFlag[i].bDestory, gEventFlag[i].mutexID);
            gEventFlag[i].u32Flag = gEventFlag[i].u32Flag | Mask;
            pstruCurrTask = gEventFlag[i].struHead.pstruNext;
            while ( pstruCurrTask !=  &gEventFlag[i].struHead )
            {

                /* First, find the event flags in common.  */
                compare = gEventFlag[i].u32Flag & pstruCurrTask->u32Request;

                /* Second, determine if all the event flags must match.  */
                if ( pstruCurrTask->u32Opt & EVM_PORTING_EVENTTYPE_ANDSET )
                {
                    /* Yes, an AND condition is present.  All requested events
                       must be present.  */
                    compare = ( compare == pstruCurrTask->u32Request );
                }

                /* If compare is non-zero, the suspended task's event request is
                   satisfied.  */
                if (compare)
                {
                    /* Resume the suspended task.  */
                    evm_porting_OsSemPost( pstruCurrTask->semID);
                }  

                pstruCurrTask = pstruCurrTask->pstruNext;

            }
            evm_porting_OsMutexUnlock( gEventFlag[i].mutexID);
            return EVM_SUCCESS;          
        }
    }
    return EVM_FAILURE;
}

ret_code_e evm_porting_OsEventDestroy(evm_u32 EventId)
{
    evm_u32 i;
    evm_porting_waittask_s *pstruCurrTask;    

    for ( i = 0; i < EVM_EVENT_NUM_MAX; i++ )
    {
        /* found corresponding element */
        if ( EventId == gEventFlag[i].u32EventId)
        {
        
            evm_porting_OsMutexLock( gEventFlag[i].mutexID);
            
            gEventFlag[i].bDestory = EVM_TRUE;
            pstruCurrTask = gEventFlag[i].struHead.pstruNext;
            /* Walk the chain task(s) currently suspended on the event_group.  */
            while ( pstruCurrTask != & gEventFlag[i].struHead )
            {
                /* Resume the suspended task.  */
                evm_porting_OsSemPost( pstruCurrTask->semID );
                pstruCurrTask = pstruCurrTask->pstruNext;

            }
            evm_porting_OsMutexUnlock( gEventFlag[i].mutexID);
            /* check if the list is empty */
            while( gEventFlag[i].struHead.pstruNext != &gEventFlag[i].struHead )
            {
                evm_porting_OsDelay( 100);
            }
            evm_porting_OsMutexLock( gEventFlag[i].mutexID);
            gEventFlag[i].u32Flag = 0;
            gEventFlag[i].u32EventId = EVENT_INVALID_HANDLE;
            evm_porting_OsMutexUnlock( gEventFlag[i].mutexID);
            evm_porting_OsDestroyMutex( gEventFlag[i].mutexID);
            return EVM_SUCCESS;
        }
    }
    EVM_ERROR_PRINT(" error  \n");
    return EVM_FAILURE;
}

ret_code_e evm_porting_OsEventClear(evm_u32 EventId, evm_u32 Mask )
{
    evm_u32 i;

    for ( i = 0; i < EVM_EVENT_NUM_MAX; i++ )
    {
        /* found corresponding element */
        if ( EventId == gEventFlag[i].u32EventId)
        {
            /* set the flag */
            evm_porting_OsMutexLock( gEventFlag[i].mutexID);            
            gEventFlag[i].u32Flag = gEventFlag[i].u32Flag & ( ~Mask);
            evm_porting_OsMutexUnlock( gEventFlag[i].mutexID );
            return EVM_SUCCESS;
        }
    }

    return EVM_FAILURE;
}

ret_code_e evm_porting_OsGetCwd(evm_s8 *Buff, evm_s32 MaxLen)
{
    evm_s32 s32Ret = EVM_FAILURE;

    if(EVM_NULL == getcwd(Buff, MaxLen))
    {
        s32Ret = EVM_ERR_SRCNOTEXIST;
        goto end;
    }

    s32Ret = EVM_SUCCESS;
end:
    return s32Ret;
}

ret_code_e evm_porting_OsTimerCreat(evm_u32 *TimerId, evm_porting_os_timer_cb pcbCallback, void *Param, evm_u32 u32Delay, evm_u32 u32Interval, evm_bool bRepeat)
{
    return evm_porting_OsTimerCreate(TimerId, pcbCallback, Param, u32Delay, u32Interval, bRepeat);
}

////////////////////////////network///////////////////////////////////////////
evm_s32 evm_porting_OsGetMac(evm_s8 *ps8Eth, evm_s8 *out_ps8Mac, evm_s8 s8Dot)
{
    evm_s32 s32Ret = EVM_FAILURE;
    evm_handle hSocket = -1;
    struct ifreq stIfReq;

    if (!ps8Eth || !out_ps8Mac)
    {
        printf("param is NULL\n");
        goto end;
    }

    hSocket = socket(AF_INET,SOCK_STREAM,0);
    if (hSocket < 0)
    {
        printf("get socket failed\n");
        goto end;
    }

    bzero((char *)&stIfReq, sizeof(stIfReq));
    strcpy(stIfReq.ifr_name, ps8Eth);

    s32Ret = ioctl(hSocket, SIOCGIFHWADDR, &stIfReq);
    if (EVM_SUCCESS != s32Ret)
    {
        printf("ioctl failed\n");
        goto end;
    }

    if (s8Dot)
    {
        sprintf(out_ps8Mac, "%02X%c%02X%c%02X%c%02X%c%02X%c%02X", 0xFF & stIfReq.ifr_ifru.ifru_hwaddr.sa_data[0], s8Dot, \
                0xFF & stIfReq.ifr_ifru.ifru_hwaddr.sa_data[1], s8Dot, 0xFF & stIfReq.ifr_ifru.ifru_hwaddr.sa_data[2], s8Dot, 0xFF & stIfReq.ifr_ifru.ifru_hwaddr.sa_data[3], s8Dot, \
                0xFF & stIfReq.ifr_ifru.ifru_hwaddr.sa_data[4], s8Dot, 0xFF & stIfReq.ifr_ifru.ifru_hwaddr.sa_data[5]);
    }
    else
    {
        sprintf(out_ps8Mac, "%02X%02X%02X%02X%02X%02X", 0xFF & stIfReq.ifr_ifru.ifru_hwaddr.sa_data[0], \
                0xFF & stIfReq.ifr_ifru.ifru_hwaddr.sa_data[1],  0xFF & stIfReq.ifr_ifru.ifru_hwaddr.sa_data[2],  0xFF & stIfReq.ifr_ifru.ifru_hwaddr.sa_data[3], \
                0xFF & stIfReq.ifr_ifru.ifru_hwaddr.sa_data[4],  0xFF & stIfReq.ifr_ifru.ifru_hwaddr.sa_data[5]);
    }


    s32Ret = EVM_SUCCESS;

end:
    if (hSocket >= 0)
        close(hSocket);

    return s32Ret;
}

#define RESOLV_FILE     "/etc/resolv.conf"
#define INET_NTOA(buffer, ip) sprintf(buffer, "%03d.%03d.%03d.%03d", ip & 0xff, (ip >> 8) & 0xff, (ip >> 16) & 0xff, (ip >> 24) & 0xff)
#define SET_SA_FAMILY(addr, family) \
    memset ((char *) &(addr), '\0', sizeof(addr));\
    addr.sa_family = (family);

#define SIN_ADDR(x) (((struct sockaddr_in *) (&(x)))->sin_addr.s_addr)

#define DEL_LEADING_ZERO(dst, src) do \
    { \
        int a, b, c, d; \
        a = b = c = d = 0; \
        sscanf(src, "%03d.%03d.%03d.%03d", &a, &b, &c, &d); \
        sprintf(dst, "%d.%d.%d.%d", a, b, c, d); \
    } \
    while (0);

ret_code_e evm_porting_OsSetDns(evm_s8 *ps8Domain, evm_s8 **pps8NameServer, evm_u32 u32Num)
{
    FILE *fp = EVM_NULL;
    evm_s32 i;
    char s8arrIp[32];

    if (EVM_NULL == pps8NameServer)
    {
        printf("----pps8NameServer is null ...\n");
        return EVM_FAILURE;
    }

    fp = fopen(RESOLV_FILE, "w");
    if (NULL == fp)
    {
        printf("----fopen resolv.conf error..\n");
        return EVM_FAILURE;
    }

    if (NULL != ps8Domain)
    {
        fwrite("search ", 1, strlen("search "), fp);
        fwrite(ps8Domain, 1, strlen(ps8Domain), fp);
        fwrite("\n", 1, 1, fp);
    }

    for (i = 0; i < u32Num; i++)
    {
        DEL_LEADING_ZERO(s8arrIp, pps8NameServer[i]);
        fwrite("nameserver ", 1, strlen("nameserver "), fp);
        fwrite(s8arrIp, 1, strlen(s8arrIp), fp);
        fwrite("\n", 1, 1, fp);
    }

    fflush(fp);
    fclose(fp);

    return EVM_SUCCESS;
}

ret_code_e evm_porting_OsGetDns(evm_s8 **out_pps8NameServer, evm_u32 *out_pu32Num)
{
    FILE *fp = NULL;
    char buf[128] = {0}; // 128 is enough for linux
    char tmpBuff[16] = {0};
    char *pbuf = buf;
    char *ptr = NULL, *ptr2 = NULL;

    fp = fopen(RESOLV_FILE, "r");

    if (fp == NULL)
    {
        printf("can't open RESOLV_FILE \n");
        return -1;
    }

    int i = 0;
    while (fgets(buf, sizeof(buf), fp) && i < *out_pu32Num)
    {
        if ((ptr=strstr(pbuf, "nameserver")) != NULL)
        {
            ptr += strlen("nameserver");

            while (*ptr < '0' || *ptr > '9') ptr++;
                ptr2 = ptr;

            while (((*ptr2 >= '0' && *ptr2 <= '9') || (*ptr2==0x2e)) && ((ptr2-ptr) < 16))
                ptr2++;

            if (out_pps8NameServer[i])
            {
                struct sockaddr_in addr;
                memset(tmpBuff, 0, sizeof(tmpBuff));

                memset(out_pps8NameServer[i], 0, sizeof("255.255.255.255"));
                memcpy(out_pps8NameServer[i], ptr, ptr2-ptr);

                bzero(&addr, sizeof(struct sockaddr_in));
                addr.sin_family = AF_INET;

                DEL_LEADING_ZERO(tmpBuff, out_pps8NameServer[i]);

                inet_aton(tmpBuff, &addr.sin_addr);

                INET_NTOA(out_pps8NameServer[i], addr.sin_addr.s_addr);
            }
            i++;
        }
        memset(buf, 0, sizeof(buf));

    }

    *out_pu32Num = i;

    fclose(fp);

    if (0 != i)
    {
        return EVM_SUCCESS;
    }
    else
    {
        return EVM_FAILURE;
    }
}

#define UDP_BUFFER_SIZE 8192
struct route_info
{
    struct in_addr dstAddr;
    struct in_addr srcAddr;
    struct in_addr gateWay;
    char ifName[IFNAMSIZ];
};

static ret_code_e __parseRoutes(struct nlmsghdr *nlHdr, struct route_info *rtInfo, struct in_addr *pstRoute, evm_s8 *ifName)
{
    struct rtmsg *rtMsg;
    struct rtattr *rtAttr;
    evm_s32 rtLen = 0;

    rtMsg = (struct rtmsg *)NLMSG_DATA(nlHdr);

    /* If the route is not for AF_INET or does not belong to main routing table
    then return. */
    if ((rtMsg->rtm_family != AF_INET) || (rtMsg->rtm_table != RT_TABLE_MAIN))
        return EVM_FAILURE;

    /* get the rtattr field */
    rtAttr = (struct rtattr *)RTM_RTA(rtMsg);
    rtLen = RTM_PAYLOAD(nlHdr);

    for (; RTA_OK(rtAttr,rtLen); rtAttr = RTA_NEXT(rtAttr,rtLen))
    {
        switch (rtAttr->rta_type)
        {
        case RTA_OIF:
            if_indextoname(*(unsigned *)RTA_DATA(rtAttr), rtInfo->ifName);
            break;
        case RTA_GATEWAY:
            rtInfo->gateWay.s_addr = *(u_int *)RTA_DATA(rtAttr);
            break;
        case RTA_PREFSRC:
            rtInfo->srcAddr.s_addr = *(u_int *)RTA_DATA(rtAttr);
            break;
        case RTA_DST:
            rtInfo->dstAddr.s_addr = *(u_int *)RTA_DATA(rtAttr);
            break;
        }
    }

    if (strstr((evm_s8 *)inet_ntoa(rtInfo->dstAddr), "0.0.0.0"))
    {
        if(strcmp(rtInfo->ifName, ifName) == 0)
        {
            memcpy(pstRoute, &rtInfo->gateWay, sizeof(struct in_addr));

            return EVM_SUCCESS;
        }
    }

    return EVM_FAILURE;
}

static evm_s32 __readNlSock(evm_s32 sockFd, evm_s8 *bufPtr, evm_s32 seqNum, evm_s32 pId)
{
    struct nlmsghdr *nlHdr;
    int readLen = 0, msgLen = 0;

    do
    {
        /* Recieve response from the kernel */
        if ((readLen = recv(sockFd, bufPtr, UDP_BUFFER_SIZE - msgLen, 0)) < 0)
        {
            perror("SOCK READ: ");
            return EVM_FAILURE;
        }

        nlHdr = (struct nlmsghdr *)bufPtr;

        /* Check if the header is valid */
        if ((NLMSG_OK(nlHdr, readLen) == 0) || (nlHdr->nlmsg_type == NLMSG_ERROR))
        {
            perror("Error in recieved packet");
            return EVM_FAILURE;
        }

        /* Check if the its the last message */
        if (nlHdr->nlmsg_type == NLMSG_DONE)
        {
            break;
        }
        else
        {
            /* Else move the pointer to buffer appropriately */
            bufPtr += readLen;
            msgLen += readLen;
        }

        /* Check if its a multi part message */
        if((nlHdr->nlmsg_flags & NLM_F_MULTI) == 0)
        {
            /* return if its not */
            break;
        }
    } while ((nlHdr->nlmsg_seq != seqNum) || (nlHdr->nlmsg_pid != pId));

    return msgLen;
}

ret_code_e evm_porting_OsGetGateway(evm_s8 *ps8Eth, evm_s8 **out_pps8Getway, evm_u32 *pu32Num)
{
    struct nlmsghdr *nlMsg;
    struct rtmsg *rtMsg;
    struct route_info rtInfo;
    char msgBuf[UDP_BUFFER_SIZE];
    struct in_addr gw;
    int gw_cnt = 0;
    int sock = 0;
    int len = 0;
    int msgSeq = 0;

    /* Create Socket */
    if ((sock = socket(PF_NETLINK, SOCK_DGRAM, NETLINK_ROUTE)) < 0)
    {
        printf("[%s] socket error\n", __func__);
        return EVM_FAILURE;
    }
    /* Initialize the buffer */
    memset(msgBuf, 0, UDP_BUFFER_SIZE);

    /* point the header and the msg structure pointers into the buffer */
    nlMsg = (struct nlmsghdr *)msgBuf;
    rtMsg = (struct rtmsg *)NLMSG_DATA(nlMsg);

    /* Fill in the nlmsg header*/
    nlMsg->nlmsg_len  = NLMSG_LENGTH(sizeof(struct rtmsg)); // Length of message.
    nlMsg->nlmsg_type = RTM_GETROUTE; // Get the routes from kernel routing table .

    nlMsg->nlmsg_flags = NLM_F_DUMP | NLM_F_REQUEST; // The message is a request for dump.
    nlMsg->nlmsg_seq   = msgSeq++; // Sequence of the message packet.
    nlMsg->nlmsg_pid   = getpid(); // PID of process sending the request.

    /* Send the request */
    if (send(sock, nlMsg, nlMsg->nlmsg_len, 0) < 0)
    {
        printf("Write To Socket Failed...\n");
        close(sock);
        return EVM_FAILURE;
    }

    /* Read the response */
    if ((len = __readNlSock(sock, msgBuf, msgSeq, getpid())) < 0)
    {
        printf("Read From Socket Failed...\n");
        close(sock);
        return EVM_FAILURE;
    }

    // ADDED BY BOB
    /* THIS IS THE NETTSTAT -RL code I commented out the printing here and in parse routes */
    for(; NLMSG_OK(nlMsg, len); nlMsg = NLMSG_NEXT(nlMsg,len))
    {
        memset(&rtInfo, 0, sizeof(struct route_info));
        if (EVM_SUCCESS == __parseRoutes(nlMsg, &rtInfo, &gw, ps8Eth))
        {
            if (NULL != out_pps8Getway)
            {
                INET_NTOA(out_pps8Getway[gw_cnt], gw.s_addr);
                gw_cnt++;
                if(gw_cnt >= *pu32Num)
                {
                    break;
                }
            }
            else
                gw_cnt++;
        }
    }
    close(sock);

    *pu32Num = gw_cnt;

    return EVM_SUCCESS;
}

ret_code_e evm_porting_OsSetGateway(evm_s8 *ps8Eth, evm_s8 **pps8Getaway, evm_u32 u32Num)
{
    evm_s32 s32Ret = EVM_FAILURE, i;
    evm_u32 u32CurNum = 0, u32AllocateNum = 0;
    evm_s8 **pps8CurGateway = EVM_NULL;
    int sock = 0;
    struct rtentry rt;
    char s8arrIp[32];

    s32Ret = evm_porting_OsGetGateway(ps8Eth, EVM_NULL, &u32CurNum);
    if (EVM_SUCCESS != s32Ret)
    {
        printf("get gata way failed\n");
        goto end;
    }

    /* Get an internet socket for doing socket ioctls. */
    sock = socket(AF_INET, SOCK_DGRAM, 0);

    memset(&rt, 0, sizeof (rt));

    /*set Destination addr*/
    SET_SA_FAMILY (rt.rt_dst, AF_INET);
    SIN_ADDR(rt.rt_gateway) = inet_addr("0.0.0.0");

    /*set gw addr*/
    SET_SA_FAMILY (rt.rt_gateway, AF_INET);

    rt.rt_dev = ps8Eth;
    rt.rt_flags = RTF_GATEWAY;

    if (u32CurNum > 0)
    {
        pps8CurGateway = calloc(u32CurNum, sizeof(evm_s8*));
        if (!pps8CurGateway)
        {
            printf("allocate memory failed\n");
            goto end;
        }

        u32AllocateNum = u32CurNum;

        for (i = 0; i < u32CurNum; i++)
        {
            pps8CurGateway[i] = calloc(32, sizeof(evm_s8));
            if (!pps8CurGateway[i])
            {
                printf("allocate memory failed\n");
                goto end;
            }
        }

        s32Ret = evm_porting_OsGetGateway(ps8Eth, pps8CurGateway, &u32CurNum);
        if (EVM_SUCCESS != s32Ret)
        {
            printf("get gata way failed\n");
            goto end;
        }

        for (i = 0; i < u32CurNum; i++)
        {
            DEL_LEADING_ZERO(s8arrIp, pps8CurGateway[i]);
            SIN_ADDR(rt.rt_gateway) = inet_addr(s8arrIp);
            s32Ret = ioctl(sock, SIOCDELRT, &rt);
            if (s32Ret < 0)
            {
                printf("ioctl failed error = %d\n", errno);
                goto end;
            }
        }
    }

    for (i = 0 ; i < u32Num; i++)
    {
        DEL_LEADING_ZERO(s8arrIp, pps8Getaway[i]);
        SIN_ADDR(rt.rt_gateway) = inet_addr(s8arrIp);
        if (ioctl(sock, SIOCADDRT, &rt) < 0)
        {
            printf("ioctl2 failed error = %d\n", errno);
            goto end;
        }
    }

    s32Ret = EVM_SUCCESS;

end:
    if (sock)
    {
        close(sock);
    }

    if (pps8CurGateway)
    {
        for (i = 0; i < u32AllocateNum; i++)
        {
            if (pps8CurGateway[i])
                free(pps8CurGateway[i]);
        }
        free(pps8CurGateway);
    }
    return s32Ret;
}

ret_code_e evm_porting_OsSetIp(evm_s8 *ps8Eth, evm_s8 *ps8Ip)
{
    int s;
    struct ifreq ifr;
    struct sockaddr_in addr;
    char s8arrIp[32];

    if (NULL == ps8Eth || NULL == ps8Ip)
    {
        return EVM_FAILURE;
    }

    if ((s = socket(AF_INET,SOCK_STREAM,0)) < 0)
    {
        return EVM_FAILURE;
    }

    DEL_LEADING_ZERO(s8arrIp, ps8Ip);

    strcpy(ifr.ifr_name, ps8Eth);
    bzero(&addr, sizeof(struct sockaddr_in));
    addr.sin_family = AF_INET;
    inet_aton(s8arrIp, &addr.sin_addr);

    memcpy((char*)&ifr.ifr_ifru.ifru_addr,(char*)&addr,sizeof(struct sockaddr_in));

    if (ioctl(s, SIOCSIFADDR, &ifr) < 0)
    {
        close(s);
        return EVM_FAILURE;
    }

    close(s);

    return EVM_SUCCESS;
}

ret_code_e evm_porting_OsGetIp(evm_s8 *ps8Eth, evm_s8 *ps8Ip)
{
    int s;
    struct ifreq ifr;
    struct sockaddr_in * ptr;

    if (NULL == ps8Eth || NULL == ps8Ip)
    {
        return EVM_FAILURE;
    }

    if ((s = socket(AF_INET,SOCK_STREAM,0)) < 0)
    {
        return EVM_FAILURE;
    }

    bzero((char *)&ifr, sizeof(ifr));
    strcpy(ifr.ifr_name, ps8Eth);

    if(ioctl(s,SIOCGIFADDR,&ifr) < 0)
    {
        close(s);
        return EVM_FAILURE;
    }

    ptr = (struct sockaddr_in *)&ifr.ifr_ifru.ifru_addr;

    INET_NTOA(ps8Ip, ptr->sin_addr.s_addr);

    close(s);
    return EVM_SUCCESS;
}

ret_code_e evm_porting_OsSetNetMask(evm_s8 *ps8Eth, evm_s8 *ps8Mask)
{
    int s = 0;
    struct ifreq ifr;
    struct sockaddr_in netmask_addr;
    char s8arrIp[32];

    if (NULL == ps8Eth || NULL == ps8Mask)
    {
        return EVM_FAILURE;
    }

    if ((s = socket(AF_INET,SOCK_STREAM,0)) < 0)
    {
        return EVM_FAILURE;
    }

    DEL_LEADING_ZERO(s8arrIp, ps8Mask);

    bzero((char *)&ifr, sizeof(ifr));
    strcpy(ifr.ifr_name, ps8Eth);

    bzero(&netmask_addr,sizeof(struct sockaddr_in));
    netmask_addr.sin_family = AF_INET;
    inet_aton(s8arrIp, &netmask_addr.sin_addr);

    memcpy((evm_s8*)&ifr.ifr_ifru.ifru_netmask, (evm_s8*)&netmask_addr, sizeof(struct sockaddr_in));

    if(ioctl(s, SIOCSIFNETMASK, &ifr) < 0)
    {
        close(s);
        return EVM_FAILURE;
    }

    close(s);

    return EVM_SUCCESS;
}


ret_code_e evm_porting_OsGetNetMask(evm_s8 *ps8Eth, evm_s8 *ps8Mask)
{
    int s = 0;
    struct ifreq ifr;
    struct sockaddr_in *ptr;

    if (NULL == ps8Eth || NULL == ps8Mask)
    {
        return EVM_FAILURE;
    }

    if ((s = socket(AF_INET,SOCK_STREAM,0)) < 0)
    {
        return EVM_FAILURE;
    }

    bzero((char *)&ifr, sizeof(ifr));
    strcpy(ifr.ifr_name, ps8Eth);

    if (ioctl(s, SIOCGIFNETMASK, &ifr) < 0)
    {
        close(s);
        return EVM_FAILURE;
    }

    ptr = (struct sockaddr_in *)&ifr.ifr_ifru.ifru_netmask;

    INET_NTOA(ps8Mask, ptr->sin_addr.s_addr);

    close(s);

    return EVM_SUCCESS;
}

ret_code_e evm_porting_OsGetNetLinkstatus(evm_s8 *interface_name, evm_s32 *pStatus)
{
    if(NULL == interface_name || NULL == pStatus)
    {
        return EVM_FAILURE;
    }

    int sfd = -1;
    struct ifreq ifr;
    bzero((evm_s8 *)&ifr, sizeof(ifr));

    sfd = socket (AF_INET,SOCK_STREAM, 0);
    if (sfd < 0)
    {
        return EVM_FAILURE;
    }

    strcpy(ifr.ifr_name, interface_name);
    if (ioctl (sfd, SIOCGIFFLAGS, &ifr) < 0)
    {
        close(sfd);
        return EVM_FAILURE;
    }

    if (((ifr.ifr_flags) & IFF_UP) && ((ifr.ifr_flags) & IFF_RUNNING))
    {
        *pStatus = 1;
    }
    else
    {
        *pStatus = 0;
    }

    close(sfd);

    return EVM_SUCCESS;
}

ret_code_e evm_porting_getIpAddrByName(const void *src, char* dst, unsigned int size)
{
    struct addrinfo *result;
    struct addrinfo *res;
    int error;
    const char *addrString;

    if (src == EVM_NULL || dst == EVM_NULL || size == 0)
    {
        return EVM_FAILURE;
    }

    error = getaddrinfo(src, EVM_NULL, EVM_NULL, &result);
    if (error != 0)
    {
        printf("error in getaddrinfo: %s\n", gai_strerror(error));
        return EVM_FAILURE;
    }
    for (res = result; res != EVM_NULL; res = res->ai_next)
    {
        char buf[INET6_ADDRSTRLEN];
        addrString = inet_ntop (res->ai_family,
                                 res->ai_family == AF_INET
                                 ? (void *) &((struct sockaddr_in *) res->ai_addr)->sin_addr
                                 : (void *) &((struct sockaddr_in6 *) res->ai_addr)->sin6_addr,
                                 buf, sizeof(buf));
        if (addrString != NULL)
        {
            unsigned int copySize = size < INET6_ADDRSTRLEN? size: INET6_ADDRSTRLEN;
            strncpy(dst, addrString, copySize);
            dst[copySize] = '\0';
            break;
        }
    }

    freeaddrinfo(result);

    return EVM_SUCCESS;
}

#if 1
static evm_s32 __evm_Os_system(const evm_s8 *command)
{
    evm_s32 fd_server = 0;
    evm_s32 fd_client = 0;
    evm_s32 value = 0;
    if((fd_server = evm_porting_OsOpen(FIFO_SERVER, O_RDWR)) < 0)
    {
        perror("open:");
        return EVM_FAILURE;
    }
    if((fd_client = evm_porting_OsOpen(FIFO_CLIENT, O_RDWR)) < 0)
    {
        perror("open:");
        evm_porting_OsClose(fd_server);
        return EVM_FAILURE;
    }
    if(evm_porting_OsWrite(fd_server, command, evm_porting_OsStrLen(command) + 1) < 0)
    {
        perror("write:");
        goto FD_CLOSE;
    }
    if(evm_porting_OsRead(fd_client, &value, __PIPE_BUF) < 0)
    {
        perror("read:");
        goto FD_CLOSE;
    }
    return value; /*返回系统调用的返回值*/
FD_CLOSE:    
    evm_porting_OsClose(fd_server);
    evm_porting_OsClose(fd_client);
    return EVM_FAILURE;
}
#endif

ret_code_e evm_porting_OsDhcp(evm_s8 *ps8Eth, evm_s8 *ps8Cmd, evm_s32 s32Timeout)
{
    evm_s32 s32Ret = EVM_FAILURE;
    evm_s8 s8arrIpaddr[64];
    evm_s8 s8Cmd[128];

    if (!ps8Eth || !ps8Cmd)
        return s32Ret;
        
    sprintf(s8Cmd, "killall -9 udhcpc");

 // printf("[%s][%d] s8Cmd : %s\n",__FUNCTION__,__LINE__,s8Cmd);
    
    system(s8Cmd);

    if (ps8Cmd && strlen(ps8Cmd) > 8)
        sprintf(s8Cmd, "./udhcpc -i %s -I HZCNCAMSV1 -O HZCNCSTBV1 -f &", ps8Eth);
    else
        sprintf(s8Cmd, "./udhcpc -i %s &", ps8Eth);


 // printf("[%s][%d] s8Cmd : %s\n",__FUNCTION__,__LINE__,s8Cmd);
    
#if 1
   system(s8Cmd);
#else
    system("udhcpc &");
#endif 

    if (s32Timeout > 0)
    {
        while (1)
        {
            usleep(500 * 1000);
            s32Ret = evm_porting_OsGetIp(ps8Eth, s8arrIpaddr);
            if (EVM_SUCCESS == s32Ret)
            {
                s32Ret = EVM_SUCCESS;
                break;
            }
            else
            {
                s32Timeout -= 500;
                if (s32Timeout < 0)
                {
                    sprintf(s8Cmd, "killall -9 udhcpc");
                    system(s8Cmd);

                    break;
                }
            }
        }
    }
    else
    {
        s32Ret = EVM_SUCCESS;
    }

    evm_porting_OsPrintf("[%s][%d] s8arrIpaddr : %s\n",__FUNCTION__,__LINE__,s8arrIpaddr);

    return s32Ret;
}


ret_code_e evm_porting_OsLancableDhcp(evm_s8 *ps8Eth, evm_u8 *mac,evm_s32 s32Timeout)
{
    evm_s8 ps8Ip[12] = {0};
    evm_s8 strip[64];   
    evm_s8 s8Cmd[128];
   
    evm_s32 s32Ret = EVM_FAILURE;

    sprintf(s8Cmd,"ifconfig %s down",ps8Eth);

    __evm_Os_system(s8Cmd);
    
    sprintf(s8Cmd,"ifconfig %s hw ether %02x%02x%02x%02x%02x%02x",ps8Eth,mac[0],mac[1],mac[2],mac[3],mac[4],mac[5]);
        
    __evm_Os_system(s8Cmd);
        
    sprintf(s8Cmd,"ifconfig %s up",ps8Eth);

    __evm_Os_system(s8Cmd);
        
    sprintf(s8Cmd,"udhcpc -V TJSTB -i %s &",ps8Eth);
    
    __evm_Os_system(s8Cmd);
    
    if (s32Timeout > 0)
    {
        while (1)
        {
            usleep(500 * 1000);
            s32Ret = evm_porting_OsGetIp(ps8Eth, ps8Ip);
            if (EVM_SUCCESS == s32Ret)
            {
                if (ps8Ip == strstr(ps8Ip, "192.168.100."))  //192.168.100.***的IP地址认为是不合法的
                {
                    s32Ret = EVM_FAILURE;
                    s32Timeout -= 500;

                    if (s32Timeout < 0)
                        break;
                }
                else
                {
                    s32Ret = EVM_SUCCESS;                  
                    break;
                }
            }
            else
            {
                s32Timeout -= 500;
                if (s32Timeout < 0)
                    break;
            }
        }
    }
    else
    {
        s32Ret = EVM_SUCCESS;
    }

    if(EVM_SUCCESS == s32Ret)
    {
        sprintf(strip,"ifconfig %s %s netmask 255.255.255.0",ps8Eth,ps8Ip); 
        evm_porting_OsPrintf("[%s][%d] strip : %s - %s\n",__FUNCTION__,__LINE__,&strip[0],strip);        
        __evm_Os_system(strip); 

    }

    return s32Ret;

}
    

ret_code_e evm_porting_OsExitDhcp()
{
    evm_s8 s8Cmd[128];

    sprintf(s8Cmd, "killall -9 udhcpc");
    system(s8Cmd);

    return EVM_SUCCESS;
}

ret_code_e evm_porting_OsTruePowerOff(void)
{
 //   evm_porting_os_Init();
 //  evm_porting_OsStandby(EVM_TRUE);
    printf(" not implement \n");
    return EVM_SUCCESS;
}

ret_code_e evm_porting_OsSystemCall(evm_s8 *cmd)
{
    system(cmd);

    return 0;
}

