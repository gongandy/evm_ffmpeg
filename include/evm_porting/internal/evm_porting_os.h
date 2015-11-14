/*
 * evm_porting_os.h
 * Copyright(C) EnRich DTV Group Co.,Ltd.
 *
 * Description: 
 *
 * Authors: 沈辉<shenhui@evmtv.com>
 *			Endy	<caifk@evmtv.com>
 */

#ifndef EVM_PORTING_OS_H_
#define EVM_PORTING_OS_H_

#include <stdio.h>
#include <stdarg.h>
//#include <termios.h>
#include <unistd.h>

typedef evm_s32 evm_threadID;
typedef evm_s32 evm_mutexID;
typedef evm_s32 evm_semID;
typedef evm_u32 evm_keyID;
typedef evm_s32 evm_onceID;

#define EVM_OS_O_RDONLY 0
#define EVM_OS_SEEK_SET 0
#define EVM_OS_O_WRONLY 1
#define SIZEOF_EVM_THREAD_ATTR_T	36
#define SIZEOF_EVM_SEM_T			16
#define __PIPE_BUF 512
#define FIFO_SERVER "/tmp/systemcall_fifo_server"
#define FIFO_CLIENT "/tmp/systemcall_fifo_client"


typedef union
{
	evm_s8 __size[SIZEOF_EVM_THREAD_ATTR_T];
	evm_s64 __align;
} evm_porting_threadAttr_t;

typedef union
{
	evm_s8 __size[SIZEOF_EVM_SEM_T];
	evm_s64 __align;
} evm_porting_sem_t;
#ifdef sched_param
#undef sched_param
#endif
struct _evm_sched_param_t
{
	evm_s32 sched_priority;
};

typedef enum _evm_porting_detachState_e
{
	EVM_PORTING_STATE_JOINABLE 	= 0,
	EVM_PORTING_STATE_DEATACHED = 1
} evm_porting_detachState_e;

typedef enum _evm_porting_schedPolicy_e
{
	EVM_PORTING_SCHED_POLICY_OTHER 	= 0,
	EVM_PORTING_SCHED_POLICY_FIFO  	= 1,
	EVM_PORTING_SCHED_POLICY_RR		= 2
} evm_porting_schedPolicy_e;

typedef enum evm_porting_threadPriority_e
{
    EVM_PORTING_THREADPRIORITY_MIN = 0,
    EVM_PORTING_THREADPRIORITY_NOR = 5,
    EVM_PORTING_THREADPRIORITY_MAX = 10
} evm_porting_threadPriority_e;

typedef enum evm_porting_threadStackSize_e
{
    EVM_PORTING_THREADSTACKSIZE_NOR = 32*1024,
    EVM_PORTING_THREADSTACKSIZE_LARGE = 128*1024
} evm_porting_threadStackSize_e;

typedef enum _evm_porting_eventType_e
{
    EVM_PORTING_EVENTTYPE_ANDSET=1,		//事件都满足时触发
    EVM_PORTING_EVENTTYPE_ORSET=2,		//事件中有一个满足时触发
    EVM_PORTING_EVENTTYPE_CLEARSET=4,	//事件触发之后清除标志位
    
} evm_porting_eventType_e;

typedef enum
{
	EVM_PORTING_EVENT_MOUSE_BUTTON_PRESSED		=		1
,	EVM_PORTING_EVENT_MOUSE_BUTTON_RELEASED		=		2
,	EVM_PORTING_EVENT_MOUSE_MOVED				=		3
,	EVM_PORTING_EVENT_KEY_PRESSED				=		4
,	EVM_PORTING_EVENT_KEY_RELEASED				=		5
} evm_porting_io_event_type_e;

typedef enum
{
	EVM_PORTING_MOUSE_BUTTON_LEFT 				= 		0
,	EVM_PORTING_MOUSE_BUTTON_MIDDLE 			= 		1
,	EVM_PORTING_MOUSE_BUTTON_RIGHT 				=		2
} evm_porting_io_mouse_button_e;

typedef struct _evm_porting_io_mouse_button_event_t
{
	evm_porting_io_event_type_e type;
	evm_porting_io_mouse_button_e button;
} evm_porting_io_mouse_button_event_t;

typedef struct _evm_porting_io_mouse_move_event_t
{
	evm_porting_io_event_type_e type;
	evm_s32 x, y;
} evm_porting_io_mouse_move_event_t;

typedef struct _evm_porting_io_keyboard_event_t
{
	evm_porting_io_event_type_e type;
	evm_u32 keyScanCode;
} evm_porting_io_keyboard_event_t;

typedef union _evm_porting_event_u
{
	evm_porting_io_event_type_e	type;
	evm_porting_io_mouse_button_event_t mouseButton;
	evm_porting_io_mouse_move_event_t mouseMove;
	evm_porting_io_keyboard_event_t keyboard;
} evm_porting_event_u;

#define EVM_PORTING_WAITFOREVER (0xffffffff)
#define EVM_EVENT_NUM_MAX 256 			//最大支持Event个数

ret_code_e evm_porting_os_Init(void);

ret_code_e evm_porting_OsDeInit(void);

#ifdef EVM_MEMORY_DEBUG
extern int g_m;
extern int g_c;
extern int g_f;
extern int g_r;
extern int g_ff;

#define evm_porting_OsFree(x)     ( EVM_MEMORY_DEBUG(YELLOW"free [%s] %s %d count: %d  diff: %d\n"NONE, __EVM_FILE__, __FUNCTION__, __LINE__, ++g_f, g_c + g_m - (++g_ff)), free(x))
#define evm_porting_OsMalloc(x)     ( EVM_MEMORY_DEBUG(BLUE"malloc [%s] %s %d count: %d[%d]\n"NONE, __EVM_FILE__, __FUNCTION__, __LINE__, ++g_m, x), malloc(x))
#define evm_porting_OsRealloc(x, y)     ( EVM_MEMORY_DEBUG(BLUE"ralloc [%s] %s %d count: %d[%d]\n"NONE, __EVM_FILE__, __FUNCTION__, __LINE__, ++g_r, y), realloc(x, y))
#define evm_porting_OsCalloc(x, y)     ( EVM_MEMORY_DEBUG(PURPLE"calloc [%s] %s %d count: %d[%d] \n"NONE, __EVM_FILE__, __FUNCTION__, __LINE__, ++g_c, (x) * (y)), calloc(x, y))

#else
//////////////////////////////memory operation///////////////////////////////////////
/*
 * Function: evm_porting_OsMalloc
 * Description: allocate memory
 * Input:
 *        size: memory size in byte to allocate
 * Output: none
 * Return: pointer to memory allocated if success, EVM_NULL if failed
 */
void* evm_porting_OsMalloc(evm_u32 size);

/*
 * Function: evm_porting_OsCalloc
 * Description: allocate memory and initialize every byte with zero
 * Input:
 *        n: objects count
 *        size: every object size in byte
 * Output: none
 * Return: pointer to memory allocated if success, EVM_NULL if failed
 */
void* evm_porting_OsCalloc(evm_u32 n, evm_u32 size);

/*
 * Function: evm_porting_OsRealloc
 * Description: allocate memory with some origin content
 * Input:
 *        addr: origin content
 *        size: memory size in byte to allocate
 * Output: none
 * Return: pointer to memory allocated and deallocate memory in addr if success, EVM_NULL and stay addr unchanged if failed
 */
void* evm_porting_OsRealloc(void* addr, evm_u32 size);

/*
 * Function: evm_porting_OsFree
 * Description: deallocate memory
 * Input:
 *        addr: memory to deallocate
 * Output: none
 * Return: none
 */
void evm_porting_OsFree(void* addr);

#endif
/*
 * Function: evm_porting_OsMemCpy
 * Description:  memory copy
 * Input:
 *        addr: memory addr
 * Output: none
 * Return: none
 */
void* evm_porting_OsMemCpy(void* pDestBuf, const void* pSrcBuf, evm_u32 wSize );

/*
 * Function: evm_porting_OsMemSet
 * Description:  memory content set value
 * Input:
 *        addr: memory addr value,size
 * Output: none
 * Return: none
 */
void* evm_porting_OsMemSet(void* pDestBuf, evm_u8 c, evm_u32 wSize);

/*
 * Function: evm_porting_OsMemCmp
 * Description:  memory compare
 * Input:
 *        addr: memory addr and size
 * Output: none
 * Return: none
 */
evm_s32 evm_porting_OsMemCmp(const void* pDestBuf, const void* pSrcBuf, evm_u32 wSize);

void* evm_porting_OsMemMove(void *dest, const void *src, evm_u32 n);

//////////////////////////////////////////Debug operation/////////////////////////////////////////////////////////////
/*
 * Function: evm_porting_OsPrintf
 * Description: print some information with specific format
 * Input:
 *        fmt: format
 * Output: none
 * Return: numbers of characters written
 */
evm_s32 evm_porting_OsPrintf(const evm_s8* fmt, ...);

/*
 * Function: evm_porting_OsVprintf
 * Description: print some information with specific format, use variable params
 * Input:
 *        fmt: format
 *        args: params
 * Output: none
 * Return: numbers of characters written
 */
evm_s32 evm_porting_OsVprintf(const evm_s8* fmt, va_list args);


//////////////////////////////////////////String operation/////////////////////////////////////////////////////////////
evm_s32 evm_porting_OsVsprintf(evm_s8 *str, const evm_s8 *format, va_list ap);
evm_s32 evm_porting_OsVsnprintf(evm_s8 *str, evm_u32 size, const evm_s8 *format, va_list ap);

evm_s32 evm_porting_OsSnprintf(evm_s8 *buffer, evm_u32 size, const evm_s8 *format , ...);

evm_s32 evm_porting_OsSprintf(evm_s8 *buffer, const evm_s8 *format , ...);

evm_s8* evm_porting_OsStrDup(const evm_s8* src);

evm_s8* evm_porting_OsStrnDup(const evm_s8* src, evm_u32 size);

evm_u32 evm_porting_OsStrLen(const evm_s8* str);

evm_s8* evm_porting_OsStrCpy(evm_s8* dest, const evm_s8* src);

evm_s8* evm_porting_OsStrnCpy(evm_s8* dest , const evm_s8* src, evm_u32 size);

evm_s8* evm_porting_OsStrStr(const evm_s8* haystack, const evm_s8* needle);

evm_s8* evm_porting_OsStrCaseStr(const evm_s8* haystack, const evm_s8* needle);

evm_s8* evm_porting_OsStrChr(const evm_s8 *src, evm_s32 ch);

evm_s8* evm_porting_OsStrrChr(const evm_s8 *src, evm_s32 ch);

evm_s32 evm_porting_OsSscanf(const evm_s8 *str, const evm_s8* fmt, ...);

evm_s8* evm_porting_OsStrCat(evm_s8 *dest, const evm_s8 *src);

evm_s8* evm_porting_OsStrnCat(evm_s8 *dest, const evm_s8 *src, evm_u32 n);

evm_s32 evm_porting_OsIsSpace(evm_s32 ch);

evm_s32 evm_porting_OsIsDigit(evm_s32 ch);

evm_s32 evm_porting_OsStrCmp(const evm_s8* s1, const evm_s8* s2);

evm_s32 evm_porting_OsStrnCmp(const evm_s8* s1, const evm_s8* s2, evm_u32 size);

evm_s32 evm_porting_OsStrCaseCmp(const evm_s8* s1, const evm_s8* s2);

evm_s32 evm_porting_OsStrnCaseCmp(const evm_s8* s1, const evm_s8* s2, evm_u32 size);

evm_s32 evm_porting_OsAtoi(const evm_s8* s1);

evm_s32 evm_porting_OsStrtol(const char *nptr, char **endptr, int base);

//////////////////////////////////////////Thread operation/////////////////////////////////////////////////////////////
/*
 * Function: evm_porting_OsCreateThreadPriv
 * Description: create a new thread
 * Input:
 *        name: name of new thread
 *        pfn: entrance function of new thread
 *        param: param  of pfn
 *        stackSize: stack size of new thread
 *        priority: priority of new thread
 * Output:
 *        pThreadID: ID of thread created
 * Return: see enum ret_code_e
 */
ret_code_e evm_porting_OsCreateThreadPriv(evm_threadID* pThreadID, const evm_s8* name, void* (*pfn)(void*)\
       , void* param, evm_s32 stackSize, evm_porting_threadPriority_e priority);

/*
 * Function: evm_porting_OsDestroyThread
 * Description: destory a thread
 * Input:
 *        pThreadID: ID of thread
 * Output: none
 * Return: see enum ret_code_e
 */
ret_code_e evm_porting_OsDestroyThread(evm_threadID threadID);

/*
 * Function: evm_porting_OsThreadCreate
 * Description: create a new thread with pthread rules
 * Input:
 *        	pfn: entrance function of new thread
 *       	param: param  of pfn
 * Output:
 *        	pThreadID: ID of thread created
 * Return: see enum ret_code_e
 */
ret_code_e evm_porting_OsThreadCreate(evm_threadID* pThreadID, evm_porting_threadAttr_t* attr, void* (*pfn)(void*)\
       , void* param);


/*
 * Function: evm_porting_OsThreadJoin
 * Description: 		以阻塞的方式等待指定的线程结束。
 * Input:
 *        	pThreadID: 	线程ID标识符
 * Output:
 *        	retval: 		用户自定义指针，用于存储被等待线程返回值。
 * Return: see enum ret_code_e
 */
ret_code_e evm_porting_OsThreadJoin(evm_threadID pThreadID, void** retval);

/*
 * Function: evm_porting_OsThreadSelf
 * Description: 		获取当前线程ID
 * Input:
 *        	无
 * Output:
 *        	retval: 		当前线程ID
 * Return: see enum ret_code_e
 */
evm_threadID evm_porting_OsThreadSelf(void);


/*
 * Function: evm_porting_OsThreadCancel
 * Description: 		发送终止信号给线程
 * Input:
 *        	pThreadID: 	线程ID标识符
 * Output:
 *        	无
 * Return: see enum ret_code_e
 */
ret_code_e evm_porting_OsThreadCancel(evm_threadID pThreadID);


/*
 * Function: evm_porting_OsThreadKeyCreate
 * Description: 		创建键值
 * Input:
 *        	key: 		键值ID
 *		*:			线程结束时回调函数
 * Output:
 *        	无
 * Return: see enum ret_code_e
 */
ret_code_e evm_porting_OsThreadKeyCreate(evm_keyID * key, void (*) (void *));

/*
 * Function: 			evm_porting_OsThreadKeyDelete
 * Description: 		删除键值
 * Input:
 *        	key: 		键值ID
 * Output:
 *        	无
 * Return: see enum ret_code_e
 */
ret_code_e evm_porting_OsThreadKeyDelete(evm_keyID key);


/*
 * Function: 			evm_porting_OsSetSpecific
 * Description: 		为指定键值设置线程绑定数据
 * Input:
 *        	key: 		绑定的键值
 *		pointer:		数据地址
 * Output:
 *        	无
 * Return: see enum ret_code_e
 */
 
ret_code_e evm_porting_OsThreadSetSpecific(evm_keyID key, void* pointer);

/*
 * Function: 			evm_porting_OsGetSpecific
 * Description: 		获取指定键值的线程绑定数据
 * Input:
 *   		key: 		绑定的键值
 * Output:
 *        	无
 * Return: 			绑定的数据
 */
void* evm_porting_OsThreadGetSpecific(evm_keyID key);

/*
 * Function: 			evm_porting_OsThreadAttrInit
 * Description: 		初始化线程属性
 * Input:
 *        	attr: 		属性结构
 * Output:
 *        	无
 * Return: 			see enum ret_code_e
 */
ret_code_e evm_porting_OsThreadAttrInit(evm_porting_threadAttr_t* attr);


/*
 * Function: 			evm_porting_OsThreadAttrDestroy
 * Description: 		销毁线程属性
 * Input:
 *        	attr: 		属性结构
 * Output:
 *        	无
 * Return: 			see enum ret_code_e
 */
ret_code_e evm_porting_OsThreadAttrDestroy(evm_porting_threadAttr_t* attr);


/*
 * Function: 			evm_porting_OsThreadSetSchedParam
 * Description: 		设置线程优先级
 * Input:
 *        	attr: 		属性结构
 *		param:		优先级结构
 * Output:
 *        	无
 * Return: 			see enum ret_code_e
 */
ret_code_e evm_porting_OsThreadSetSchedParam(evm_porting_threadAttr_t* attr, struct _evm_sched_param_t* param);

/*
 * Function: 			evm_porting_OsThreadSetDetachState
 * Description: 		设置线程detach状态属性
 * Input:
 *        	attr: 		属性结构
 *		state:		状态枚举值
 * Output:
 *        	无
 * Return: 			see enum ret_code_e
 */
ret_code_e evm_porting_OsThreadSetDetachState(evm_porting_threadAttr_t* attr, evm_porting_detachState_e state);

/*
 * Function: 			evm_porting_OsThreadSetSchedPolicy
 * Description: 		设置线程调度策略
 * Input:
 *        	attr: 		属性结构
 *		policy:		优先级枚举值
 * Output:
 *        	无
 * Return: 			see enum ret_code_e
 */
ret_code_e evm_porting_OsThreadSetSchedPolicy(evm_porting_threadAttr_t* attr, evm_porting_schedPolicy_e policy);


evm_threadID evm_porting_OsThreadSelf(void);


/*
 * Function: 			evm_porting_OsGetEvent
 * Description: 		获取IO事件
 * Input:
 *        	event: 		事件结构
 * Output:
 *        	无
 * Return: 			see enum ret_code_e
 */
ret_code_e evm_porting_OsGetEvent(evm_porting_event_u *event);

/*
 * Function: 			evm_porting_OsOSDChangesSize
 * Description: 		切换OSD的输出分辨率
 * Input:
 *        	width: 		输出宽度
 *		height:		输出高度
 * Output:
 *        	无
 * Return: 			N/A
 */
void evm_porting_OsOSDChangesSize(evm_s32 width, evm_s32 height);

/*
 * Function: evm_porting_OsDealy
 * Description: delay current thread
 * Input:
 *        ms: time in millisecond to delay
 * Output: none
 * Return: see enum ret_code_e
 */
ret_code_e evm_porting_OsDelay(evm_u32 ms);

/*
 * Function: evm_porting_OsUSecDealy
 * Description: delay current thread
 * Input:
 *        ms: time in microsecond to delay
 * Output: none
 * Return: see enum ret_code_e
 */
ret_code_e evm_porting_OsUSecDelay(evm_u32 us);

/*
 * Function: evm_porting_OsTickTime
 * Description: get tick time after boot up
 * Input: none
 * Output: none
 * Return: time in millisecond
 */
evm_s32 evm_porting_OsTickTime(void);


ret_code_e evm_porting_OsTimeInit(void);

/*
 * Function: evm_porting_OsSetSClock
 * Description: set current GMT time , seconds
 * Input: updateTime
 * Output: none
 * Return: if success
 */
ret_code_e evm_porting_OsSetSClock(evm_u32 updateTime);


/*
 * Function: evm_porting_OsSetTimeZone
 * Description: set current time zone
 * Input: timeZone fixme: how many minutes ?
 * Output:
 * Return: if success
 */
ret_code_e evm_porting_OsSetTimeZone(evm_s32 timeZone);

/*
 * Function: evm_porting_OsGetTimeZone
 * Description: get current time zone
 * Input: none
 * Output: none
 * Return: difference with GMT  (minutes)
 */
evm_s32 evm_porting_OsGetTimeZone(void);



//////////////////////////////////////////Mutex operation/////////////////////////////////////////////////////////////
/*
 * Function: evm_porting_OsCreateMutex
 * Description: create a mutex
 * Input: none
 * Output:
 *        pMutexID: ID of mutex created
 * Return: see enum ret_code_e
 */
ret_code_e evm_porting_OsCreateMutex(evm_mutexID* pMutexID);

/*
 * Function: evm_porting_OsDestroyMutex
 * Description: destroy a mutex
 * Input:
 *        mutexID: ID of mutex to destroy
 * Output: none
 * Return: see enum ret_code_e
 */
ret_code_e evm_porting_OsDestroyMutex(evm_mutexID mutexID);

/*
 * Function: evm_porting_OsMutexLock
 * Description: lock a mutex
 * Input:
 *        mutexID: ID of mutex to lock
 * Output: none
 * Return: see enum ret_code_e
 */
ret_code_e evm_porting_OsMutexLock(evm_mutexID mutexID);

/*
 * Function: evm_porting_OsMutexTryLock
 * Description: try lock a mutex
 * Input:
 *        mutexID: ID of mutex to lock
 * Output: none
 * Return: 
 */

ret_code_e evm_porting_OsMutexTryLock(evm_mutexID mutexID);

/*
 * Function: evm_porting_OsMutexUnlock
 * Description: unlock a mutex
 * Input:
 *        mutexID: ID of mutex to unlock
 * Output: none
 * Return: see enum ret_code_e
 */
ret_code_e evm_porting_OsMutexUnlock(evm_mutexID mutexID);


//////////////////////////////////////////Semaphore operation/////////////////////////////////////////////////////////////
/*
 * Function: evm_porting_OsCreateSem
 * Description: create a new semaphore
 * Input:
 *        count: semaphore count when init
 * Output:
 *        pSemID: ID of semaphore created
 * Return: see enum ret_code_e
 */
ret_code_e evm_porting_OsCreateSem(evm_semID* pSemID, evm_u32 count);

/*
 * Function: evm_porting_OsDestroySem
 * Description: destroy a semaphore
 * Input:
 *        semID: ID of semaphore to destroy
 * Output: none
 * Return: see enum ret_code_e
 */
ret_code_e evm_porting_OsDestroySem(evm_semID semID);

/*
 * Function: evm_porting_OsSemWait
 * Description: wait on a semaphore
 * Input:
 *        semID: ID of semaphore to wait on
 *        ms: time out, always wait while this value equals -1.
 * Output: none
 * Return: see enum ret_code_e
 */
ret_code_e evm_porting_OsSemWait(evm_semID semID, evm_u32 ms);

/*
 * Function: evm_porting_OsSemPost
 * Description: notify on a semaphore
 * Input:
 *        semID: ID of semaphore to notify on
 * Output: none
 * Return: see enum ret_code_e
 */
ret_code_e evm_porting_OsSemPost(evm_semID semID);

ret_code_e evm_porting_OsSemGetCount(evm_semID semID,evm_s32 *count);

//////////////////////////////////////////Message queue operation/////////////////////////////////////////////////////////////
ret_code_e evm_porting_OsMsgCreat(evm_u32 *MsgId , evm_u32 MsgNum , evm_u32 MsgSize);


ret_code_e evm_porting_OsMsgSend(evm_u32 MsgId , void *Msg , evm_u32 MsgSize ,evm_u32 Timeout);


ret_code_e evm_porting_OsMsgReceive(evm_u32 MsgId , void *MsgBuf ,evm_u32 *MsgSize , evm_u32 Timeout);


ret_code_e evm_porting_OsMsgDestroy(evm_u32 MsgId);

//////////////////////////////////////////Timer operation/////////////////////////////////////////////////////////////


typedef void (*evm_porting_os_timer_cb)(void *);

/*
 * init timer info
 */
ret_code_e evm_porting_OsTimerInit(void);
/*
 * Function: evm_porting_OsTimerCreat
 * Description: create a timer
 * Input:
 *        pcbCallback: callback function if time expired
 *        Param: param of timer_fun if called
 *        u32Dealy: first time timer_fun is called after timer created (in ms)
 *        u32Timeout: interval of timer_fun is called (in ms), only sensitive when bRepeat is true
 *        bRepeat: if timer is cyclical or not
 * Output:
 *        TimerId: id of timer if created successfully
 * Return: see enum ret_code_e
 */
ret_code_e evm_porting_OsTimerCreate(evm_u32 *TimerId, evm_porting_os_timer_cb pcbCallback, void *Param, evm_u32 u32Delay, evm_u32 u32Interval, evm_bool bRepeat);

/*
 * Function: evm_porting_OsTimerReset
 * Description: reset a timer to change it's interval. If it's not cyclical, the timer will been restart.
 * Input:
 *        TimerId: id of timer to reset
 *        u32Interval: interval of timer_fun is called (in ms)
 * Output: none
 * Return: see enum ret_code_e
 */
ret_code_e evm_porting_OsTimerReset(evm_u32  TimerId, evm_u32 u32Interval);

ret_code_e evm_porting_OsTimerDestroy(evm_u32  TimerId);

//////////////////////////////////////////Event operation/////////////////////////////////////////////////////////////
ret_code_e evm_poriting_OsEventInit(void);

ret_code_e evm_porting_OsEventCreate(evm_u32 *EventId);

ret_code_e evm_porting_OsEventWait(evm_u32 EventId , evm_u32 Pattern , evm_porting_eventType_e eEventType,evm_u32 *Value,evm_u32 Timeout);

ret_code_e evm_porting_OsEventSet(evm_u32 EventId , evm_u32 Mask);

ret_code_e evm_porting_OsEventClear(evm_u32 EventId, evm_u32 Mask);

ret_code_e evm_porting_OsEventDestroy(evm_u32 EventId);

ret_code_e evm_porting_OsGetCwd(evm_s8 *Buff, evm_s32 MaxLen);

/*
	function : 	evm_porting_OsReboot
	description:	reboot stb
	param:		delay,	reboot after [delay] seconds
	return value:	error ret codes for exception, otherwise EVM_SUCCESS
*/

ret_code_e evm_porting_OsReboot(evm_s32 delay);

ret_code_e evm_porting_getNetLinkstatus(evm_s8 *interface_name, evm_s32 *pStatus);
ret_code_e evm_porting_OsGetNetLinkstatus(evm_s8 *interface_name, evm_s32 *pStatus);

/*
Function:        evm_porting_AVPlayerPowerOff
Description:     实现真待机处理接口
Input:         NA
Output:        NA
Return:        成功返回EVM_SUCCESS，否则返回EVM_FAILURE。
Others:        NA
*/

ret_code_e evm_porting_OsTruePowerOff(void);



/*
Function:        evm_porting_AVPlayerPowerOff
Description:     实现假待机处理接口
Input:         NA
Output:        NA
Return:        成功返回EVM_SUCCESS，否则返回EVM_FAILURE。
Others:        NA
*/

ret_code_e evm_porting_OsFlasePowerOff(void);




evm_s32 evm_porting_OsStandby(evm_bool bStandby);

ret_code_e evm_porting_OsGetMac(evm_s8 *ps8Eth, evm_s8 *out_ps8Mac, evm_s8 s8Dot);


evm_s32 evm_porting_OsSetMac(evm_s8 *ps8Eth, evm_s8 *in_ps8Mac, evm_s8 s8Dot);

ret_code_e evm_porting_OsSetDns(evm_s8 *ps8Domain, evm_s8 **pps8NameServer, evm_u32 u32Num);

ret_code_e evm_porting_OsGetDns(evm_s8 **out_pps8NameServer, evm_u32 *out_pu32Num);

ret_code_e evm_porting_OsGetGateway(evm_s8 *ps8Eth, evm_s8 **out_pps8Getway, evm_u32 *pu32Num);

ret_code_e evm_porting_OsSetGateway(evm_s8 *ps8Eth, evm_s8 **pps8Getaway, evm_u32 u32Num);

ret_code_e evm_porting_OsSetIp(evm_s8 *ps8Eth, evm_s8 *ps8Ip);

ret_code_e evm_porting_OsGetIp(evm_s8 *ps8Eth, evm_s8 *ps8Ip);

ret_code_e evm_porting_OsSetNetMask(evm_s8 *ps8Eth, evm_s8 *ps8Mask);

ret_code_e evm_porting_OsGetNetMask(evm_s8 *ps8Eth, evm_s8 *ps8Mask);

ret_code_e evm_porting_OsGetNetLinkstatus(evm_s8 *interface_name, evm_s32 *pStatus);

ret_code_e evm_porting_getIpAddrByName(const void *src, evm_s8* dst, evm_u32 size);

ret_code_e evm_porting_OsDhcp(evm_s8 *ps8Eth, evm_s8 *ps8Cmd, evm_s32 s32Timeout);

ret_code_e evm_porting_OsExitDhcp(void);

evm_s32 evm_porting_OsOpen(const char *pathname,evm_s32 flags);

evm_s32 evm_porting_OsClose(evm_s32 fd);

evm_s32 evm_porting_OsRead(evm_s32 fd,void *buf,evm_u32 count);

evm_s32 evm_porting_OsWrite(evm_s32 fd,const void *buf,evm_u32 count);

evm_u32 evm_porting_OsLseek(evm_s32 fildes,evm_u32 offset,evm_s32 whence);

evm_s32 evm_porting_OsFsync(evm_s32 fd);

evm_u64 evm_porting_OsStroull(const evm_s8 *nptr,evm_s8 **endptr,evm_s32 base);
ret_code_e evm_porting_OsGetCpuId(evm_u32 *CpuId);
ret_code_e evm_porting_OsLancableDhcp(evm_s8 *ps8Eth, evm_u8 *mac,evm_s32 s32Timeout);


ret_code_e evm_porting_OsSystemCall(evm_s8 *cmd);


ret_code_e evm_porting_OsNetPing(evm_s8 *ip);

#endif /* EVM_PORTING_OS_H_ */
