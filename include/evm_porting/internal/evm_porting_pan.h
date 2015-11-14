/*
 * evm_porting_pan.h
 * Copyright(C) EnRich DTV Group Co.,Ltd.
 *
 * Description: 与面板遥控相关的操作接口
 *
 * Authors: 研发三部
 */

#ifndef evm_porting_pan_h
#define evm_porting_pan_h

#include "../../evm_typedef.h"

// c plus plus
#ifdef __cplusplus
extern "C" {
#endif


#define EVM_KEY_RESERVED     		0
#define EVM_KEY_ESC          		1
#define EVM_KEY_1            		2
#define EVM_KEY_2            		3
#define EVM_KEY_3            		4
#define EVM_KEY_4            		5
#define EVM_KEY_5            		6
#define EVM_KEY_6            		7
#define EVM_KEY_7            		8
#define EVM_KEY_8            		9
#define EVM_KEY_9            		10
#define EVM_KEY_0            		11
#define EVM_KEY_MINUS        		12
#define EVM_KEY_EQUAL        		13
#define EVM_KEY_BACKSPACE    		14
#define EVM_KEY_TAB          		15
#define EVM_KEY_Q            		16
#define EVM_KEY_W            		17
#define EVM_KEY_E            		18
#define EVM_KEY_R            		19
#define EVM_KEY_T            		20
#define EVM_KEY_Y            		21
#define EVM_KEY_U            		22
#define EVM_KEY_I            		23
#define EVM_KEY_O            		24
#define EVM_KEY_P            		25
#define EVM_KEY_LEFTBRACE    		26
#define EVM_KEY_RIGHTBRACE   		27
#define EVM_KEY_ENTER        		28
#define EVM_KEY_LEFTCTRL     		29
#define EVM_KEY_A            		30
#define EVM_KEY_S            		31
#define EVM_KEY_D            		32
#define EVM_KEY_F            		33
#define EVM_KEY_G            		34
#define EVM_KEY_H            		35
#define EVM_KEY_J            		36
#define EVM_KEY_K            		37
#define EVM_KEY_L            		38
#define EVM_KEY_SEMICOLON    		39
#define EVM_KEY_APOSTROPHE   		40
#define EVM_KEY_GRAVE        		41
#define EVM_KEY_LEFTSHIFT    		42
#define EVM_KEY_BACKSLASH    		43
#define EVM_KEY_Z            		44
#define EVM_KEY_X            		45
#define EVM_KEY_C            		46
#define EVM_KEY_V            		47
#define EVM_KEY_B            		48
#define EVM_KEY_N            		49
#define EVM_KEY_M            		50
#define EVM_KEY_COMMA        		51
#define EVM_KEY_DOT          		52
#define EVM_KEY_SLASH        		53
#define EVM_KEY_RIGHTSHIFT   		54
#define EVM_KEY_KPASTERISK   		55
#define EVM_KEY_LEFTALT      		56
#define EVM_KEY_SPACE        		57
#define EVM_KEY_CAPSLOCK     		58
#define EVM_KEY_F1           		59  	/***************************hongse anjian**************/
#define EVM_KEY_F2           		60 		/***************************lvse anjian**************/
#define EVM_KEY_F3           		61 		/***************************huangse anjian**************/
#define EVM_KEY_F4           		62 		/***************************lanse anjian**************/
#define EVM_KEY_F5           		63
#define EVM_KEY_F6           		64
#define EVM_KEY_F7           		65
#define EVM_KEY_F8           		66
#define EVM_KEY_F9           		67
#define EVM_KEY_F10          		68
#define EVM_KEY_NUMLOCK      		69
#define EVM_KEY_SCROLLLOCK   		70
#define EVM_KEY_KP7          		71
#define EVM_KEY_KP8          		72
#define EVM_KEY_KP9          		73
#define EVM_KEY_KPMINUS      		74
#define EVM_KEY_KP4          		75
#define EVM_KEY_KP5          		76
#define EVM_KEY_KP6          		77
#define EVM_KEY_KPPLUS       		78
#define EVM_KEY_KP1          		79
#define EVM_KEY_KP2          		80
#define EVM_KEY_KP3          		81
#define EVM_KEY_KP0          		82
#define EVM_KEY_KPDOT        		83

#define EVM_KEY_ZENKAKUHANKAKU    	85
#define EVM_KEY_102ND        		86
#define EVM_KEY_F11            		87
#define EVM_KEY_F12            		88
#define EVM_KEY_RO            		89
#define EVM_KEY_KATAKANA        	90
#define EVM_KEY_HIRAGANA        	91
#define EVM_KEY_HENKAN        		92
#define EVM_KEY_KATAKANAHIRAGANA    93
#define EVM_KEY_MUHENKAN        	94
#define EVM_KEY_KPJPCOMMA        	95
#define EVM_KEY_KPENTER        		96
#define EVM_KEY_RIGHTCTRL        	97
#define EVM_KEY_KPSLASH        		98
#define EVM_KEY_SYSRQ        		99
#define EVM_KEY_RIGHTALT        	100
#define EVM_KEY_LINEFEED        	101
#define EVM_KEY_HOME        		102
#define EVM_KEY_UP            		103
#define EVM_KEY_PAGEUP        		104
#define EVM_KEY_LEFT        		105
#define EVM_KEY_RIGHT        		106
#define EVM_KEY_END            		107
#define EVM_KEY_DOWN        		108
#define EVM_KEY_PAGEDOWN        	109
#define EVM_KEY_INSERT        		110
#define EVM_KEY_DELETE        		111
#define EVM_KEY_MACRO        		112
#define EVM_KEY_MUTE        		113
#define EVM_KEY_VOLUMEDOWN        	114
#define EVM_KEY_VOLUMEUP        	115
#define EVM_KEY_POWER        		116    	/* SC System Power Down */
#define EVM_KEY_KPEQUAL        		117
#define EVM_KEY_KPPLUSMINUS        	118
#define EVM_KEY_PAUSE        		119
#define EVM_KEY_SCALE        		120    	/* AL Compiz Scale (Expose) */

#define EVM_KEY_KPCOMMA        		121
#define EVM_KEY_HANGEUL        		122
#define EVM_KEY_HANGUEL        		EVM_KEY_HANGEUL
#define EVM_KEY_HANJA        		123
#define EVM_KEY_YEN            		124
#define EVM_KEY_LEFTMETA        	125
#define EVM_KEY_RIGHTMETA        	126
#define EVM_KEY_COMPOSE        		127

#define EVM_KEY_STOP        		128    	/* AC Stop */
#define EVM_KEY_AGAIN        		129
#define EVM_KEY_PROPS        		130    	/* AC Properties */
#define EVM_KEY_UNDO        		131    	/* AC Undo */
#define EVM_KEY_FRONT        		132
#define EVM_KEY_COPY        		133    	/* AC Copy */
#define EVM_KEY_OPEN        		134    	/* AC Open */
#define EVM_KEY_PASTE        		135    	/* AC Paste */
#define EVM_KEY_FIND        		136    	/* AC Search */
#define EVM_KEY_CUT            		137    	/* AC Cut */
#define EVM_KEY_HELP        		138    	/* AL Integrated Help Center */
#define EVM_KEY_MENU        		139    	/* Menu (show menu) */
#define EVM_KEY_CALC        		140    	/* AL Calculator */
#define EVM_KEY_SETUP        		141
#define EVM_KEY_SLEEP        		142    	/* SC System Sleep */
#define EVM_KEY_WAKEUP        		143    	/* System Wake Up */
#define EVM_KEY_FILE        		144    	/* AL Local Machine Browser */
#define EVM_KEY_SENDFILE        	145
#define EVM_KEY_DELETEFILE        	146
#define EVM_KEY_XFER        		147
#define EVM_KEY_PROG1        		148 	/***************************jiemu anjian**************/
#define EVM_KEY_PROG2        		149 	/***************************daoshi anjian***********/
#define EVM_KEY_WWW            		150    	/* AL Internet Browser */
#define EVM_KEY_MSDOS        		151
#define EVM_KEY_COFFEE        		152    	/* AL Terminal Lock/Screensaver */
#define EVM_KEY_SCREENLOCK        	EVM_KEY_COFFEE
#define EVM_KEY_DIRECTION        	153
#define EVM_KEY_CYCLEWINDOWS    	154
#define EVM_KEY_MAIL        		155
#define EVM_KEY_BOOKMARKS        	156    	/* AC Bookmarks */
#define EVM_KEY_COMPUTER        	157
#define EVM_KEY_BACK        		158    	/* AC Back */
#define EVM_KEY_FORWARD        		159    	/* AC Forward */
#define EVM_KEY_CLOSECD        		160
#define EVM_KEY_EJECTCD        		161
#define EVM_KEY_EJECTCLOSECD    	162
#define EVM_KEY_NEXTSONG        	163
#define EVM_KEY_PLAYPAUSE        	164   	/***************************huifu anjian**************/
#define EVM_KEY_PREVIOUSSONG    	165
#define EVM_KEY_STOPCD        		166
#define EVM_KEY_RECORD        		167
#define EVM_KEY_REWIND        		168
#define EVM_KEY_PHONE        		169    	/* Media Select Telephone */
#define EVM_KEY_ISO            		170
#define EVM_KEY_CONFIG        		171    	/* AL Consumer Control Configuration */
#define EVM_KEY_HOMEPAGE        	172    	/* AC Home */
#define EVM_KEY_REFRESH        		173    	/* AC Refresh */
#define EVM_KEY_EXIT        		174    	/* AC Exit */
#define EVM_KEY_MOVE        		175 	/***************************dingwei anjian**************/
#define EVM_KEY_EDIT        		176
#define EVM_KEY_SCROLLUP        	177
#define EVM_KEY_SCROLLDOWN        	178
#define EVM_KEY_KPLEFTPAREN        	179
#define EVM_KEY_KPRIGHTPAREN    	180
#define EVM_KEY_NEW            		181    	/* AC New */ /*************************xinxi anjian***************/
#define EVM_KEY_REDO        		182    	/* AC Redo/Repeat */

#define EVM_KEY_CHUP            	183  	//频道加
#define EVM_KEY_CHDOWN          	184  	//频道减
#define EVM_KEY_SCAN            	185  	//节目搜索
#define EVM_KEY_STOCK           	186  	//股票，证券
#define EVM_KEY_GAME            	187  	// 游戏
#define EVM_KEY_VOD             	188  	//点播
#define EVM_KEY_DATABROADCAST   	189  	//数据广播
#define EVM_KEY_RECALL          	190  	//回看
#define EVM_KEY_PG_LIST         	191  	//节目列表
#define EVM_KEY_NVOD            	192  	//准视频点播
#define EVM_KEY_F23             	193
#define EVM_KEY_F24             	194
#define EVM_KEY_ALL             	195  	//全部
#define EVM_KEY_EXPAND2        		196 	//扩展2
#define EVM_KEY_SHARP         		197 	//#键
#define EVM_KEY_BACKWARD        	198 	//快退

#define EVM_KEY_PLAYCD        		200
#define EVM_KEY_PAUSECD        		201
#define EVM_KEY_PROG3        		202
#define EVM_KEY_PROG4        		203
#define EVM_KEY_DASHBOARD        	204    	/* AL Dashboard */
#define EVM_KEY_SUSPEND        		205   	/***************************zanting anjian**************/
#define EVM_KEY_CLOSE        		206    	/* AC Close */
#define EVM_KEY_PLAY        		207
#define EVM_KEY_FASTFORWARD        	208
#define EVM_KEY_BASSBOOST        	209
#define EVM_KEY_PRINT        		210    	/* AC Print */  /***************************shurufa anjian**************/
#define EVM_KEY_HP            		211
#define EVM_KEY_CAMERA        		212
#define EVM_KEY_SOUND        		213
#define EVM_KEY_QUESTION        	214
#define EVM_KEY_EMAIL        		215    	/**********youjian anjian***********/
#define EVM_KEY_CHAT        		216
#define EVM_KEY_SEARCH        		217
#define EVM_KEY_CONNECT        		218
#define EVM_KEY_FINANCE        		219    	/* AL Checkbook/Finance */
#define EVM_KEY_SPORT        		220
#define EVM_KEY_SHOP        		221
#define EVM_KEY_ALTERASE        	222
#define EVM_KEY_CANCEL        		223    	/* AC Cancel */
#define EVM_KEY_BRIGHTNESSDOWN    	224
#define EVM_KEY_BRIGHTNESSUP    	225
#define EVM_KEY_MEDIA        		226    	/***************************xiai anjian**************/

#define EVM_KEY_SWITCHVIDEOMODE    	227    	/* Cycle between available video
                       outputs (Monitor/LCD/TV-out/etc) */  /***************************shengdao anjian**************/
#define EVM_KEY_KBDILLUMTOGGLE    	228
#define EVM_KEY_KBDILLUMDOWN    	229
#define EVM_KEY_KBDILLUMUP        	230

#define EVM_KEY_SEND        		231    	/* AC Send */  /*************************** *hao anjian**************/
#define EVM_KEY_REPLY        		232    	/* AC Reply */ /*************************** #hao anjian**************/
#define EVM_KEY_FORWARDMAIL        	233    	/* AC Forward Msg */
#define EVM_KEY_SAVE        		234    	/* AC Save */
#define EVM_KEY_DOCUMENTS        	235

#define EVM_KEY_BATTERY        		236

#define EVM_KEY_BLUETOOTH        	237
#define EVM_KEY_WLAN        		238
#define EVM_KEY_UWB            		239

#define EVM_KEY_UNKNOWN        		240

#define EVM_KEY_VIDEO_NEXT        	241    	/* drive next video source */
#define EVM_KEY_VIDEO_PREV        	242    	/* drive previous video source */
#define EVM_KEY_BRIGHTNESS_CYCLE    243    	/* brightness up, after max is min */
#define EVM_KEY_BRIGHTNESS_ZERO    	244    	/* brightness off, use ambient */
#define EVM_KEY_DISPLAY_OFF        	245 	/* display device to off state */

#define EVM_KEY_WIMAX        		246
#define EVM_KEY_RFKILL        		247 	/* Key that controls all radios */


#define EVM_KEY_HUHUXIANG     		248   	//户户响
#define EVM_KEY_JIAOHU        		249  	//交互
#define EVM_KEY_LABAGUAN      		250  	//喇叭关
#define EVM_KEY_LABAKAI       		251  	//喇叭开
#define EVM_KEY_DINGWEI       		252 	//定位
#define EVM_KEY_RESUME        		253 	//播放/暂停
#define EVM_KEY_EXPAND1      		254 	//扩展1

#define EVM_KEY_HOTKEY      		255 	//扩展2
 
#define EVM_KEY_EPG     			400
#define EVM_KEY_TV_RADIO 			401

#define EVM_KEY_TV					403
#define EVM_KEY_RADIO				404
#define EVM_KEY_CCTV				405
#define EVM_KEY_FAVORITE			406
#define EVM_KEY_PROVIENCE			407
#define EVN_KEY_GUIDE				408
#define EVM_KEY_ORDER				409
#define EVM_KEY_SUMMARY				410

#define EVM_KEY_SEARCH_PG           420

#define EVM_KEY_INVALUE 			0xFFFFFFFF


typedef enum
{
    EVM_PAN_KEY_DOWN,
    EVM_PAN_KEY_UP
}evm_pan_KeyStatu;
typedef evm_u32 evm_pan_Key;

typedef enum
{
    EVM_IR_KEY_AUTO,     				//用户码fd01 与e608都支持
    EVM_IR_KEY_CODE1,    				//只支持用户码fd01
    EVM_IR_KEY_CODE2 ,   				//只支持用户码e608
    EVM_IR_KEY_NOTSUPPORT 				//不支持的类型
}evm_pan_KeyCode;

typedef struct
{
    evm_pan_KeyStatu status;
    evm_pan_Key key;
}evm_pan_KeyEvent_t;

typedef enum
{
    EVM_PAN_MOUSE_PRESSED = 0,
    EVM_PAN_MOUSE_RELEASED = 1,
    EVM_PAN_MOUSE_MOVED = 2,
    EVM_PAN_MOUSE_WHEEL = 3
} evm_pan_mouseStatus_e;

typedef enum
{
    EVM_PAN_MOUSE_LEFT = 0,
    EVM_PAN_MOUSE_MIDDLE = 1,
    EVM_PAN_MOUSE_RIGHT = 2,
} evm_pan_mouseBUtton_e;

typedef struct
{
    evm_pan_mouseStatus_e status;
    evm_pan_mouseBUtton_e button;
    evm_s32 x, y;
}evm_pan_MouseEvent_t;

typedef enum
{
    EVM_PAN_JOYSTICK_PRESSED = 0,
    EVM_PAN_JOYSTICK_RELEASED,
    EVM_PAN_JOYSTICK_LEFT_MOVED,
    EVM_PAN_JOYSTICK_RIGHT_MOVED
} evm_pan_joystickStatus_e;

typedef enum
{
    EVM_JOYSTICK_BTN_RightArrow   =  0x0,
    EVM_JOYSTICK_BTN_LeftArrow    =  0x1,
    EVM_JOYSTICK_BTN_DownArrow    =  0x2,
    EVM_JOYSTICK_BTN_UpArrow      =  0x3,
    EVM_JOYSTICK_BTN_L1            =  0x4,
    EVM_JOYSTICK_BTN_R1            =  0x5,
    EVM_JOYSTICK_BTN_L2            =  0x6,
    EVM_JOYSTICK_BTN_R2            =  0x7,
    EVM_JOYSTICK_BTN_SELECT        =  0x8,
    EVM_JOYSTICK_BTN_START         =  0x9,
    EVM_JOYSTICK_BTN_LA            =  0xa,
    EVM_JOYSTICK_BTN_RA            =  0xb,
    EVM_JOYSTICK_BTN_MODE          =  0xc,
    EVM_JOYSTICK_BTN_TURBO         =  0xd,
    EVM_JOYSTICK_BTN_CLEAR         =  0xe,
    EVM_JOYSTICK_AXIS_POV0         =  0xf,
    EVM_JOYSTICK_AXIS_X            =  0x10,
    EVM_JOYSTICK_AXIS_Y            =  0x11,
    EVM_JOYSTICK_AXIS_Z            =  0x12,
    EVM_JOYSTICK_AXIS_Z_ROTATION  =  0x13,
    EVM_JOYSTICK_BTN_1             =  0x14,
    EVM_JOYSTICK_BTN_2             =  0x15,
    EVM_JOYSTICK_BTN_3             =  0x16,
    EVM_JOYSTICK_BTN_4             =  0x17,
} evm_pan_joystickButton_e;

typedef struct
{
    evm_pan_joystickStatus_e status;
    evm_pan_joystickButton_e button;
    evm_s32 x, y, z, Rz;
}evm_pan_JoystickEvent_t;



typedef enum
{
    EVM_PAN_IR,
    EVM_PAN_FRONT_PANEL,
    EVM_PAN_MOUSE,
    EVM_PAN_JOYSTICK,
    EVM_PAN_KEYBOARD,
    EVM_PAN_COUNT
}evm_pan_EventType_t;

typedef enum
{
    EVM_PAN_KEY_STATUS_DVB,
    EVM_PAN_KEY_STATUS_VOD,
    EVM_PAN_KEY_STATUS_CLOUD,
    EVM_PAN_KEY_STATUS__VPC,
    
    EVM_PAN_KEY_STATUS_END
}evm_key_status_e;

typedef struct
{
    evm_pan_EventType_t type;
    union
    {
        evm_pan_KeyEvent_t keyEvent;
        evm_pan_MouseEvent_t mouseEvent;
        evm_pan_JoystickEvent_t joystickEvent;
    };
}evm_pan_Event_t;

typedef struct{
   	evm_s32 keyType; // IRRTYPE_NEC;
	evm_s32 standbyKey; // BlcIrrPropertyValue_POWER;
	evm_s32 customCode ;
	evm_s32 reserve;    //预留
}evm_ir_param_t;


typedef void (*evm_pan_EventCallback) (evm_pan_Event_t *e);

typedef void (*input_dev_cb)(evm_pan_EventType_t type, evm_u32 param1, evm_u32 param2);

/*
 * Function: evm_porting_pan_Init
 * Description: 对面板摇控模块的初始化
 * Output: none
 * Return: 0:SUCCESS , other is Fail
 */
 ret_code_e evm_porting_pan_Init(void);
 
 /*
  * Function: evm_porting_pan_DeInit
  * Description: 对面板摇控模块的去初始化
  * Output: none
  * Return: 0:SUCCESS , other is Fail
  */
ret_code_e evm_porting_pan_DeInit(void);

#if 0
/*
 * Function: evm_porting_pan_GetKey
 * Description: 获取面板或摇控器的按键值
 * Input:
 *          KeyInfo: 存放键值的变量
            Timeout: 取值的超时时间
 * Output: none
 * Return: 0:SUCCESS , other is Fail
 */
ret_code_e evm_porting_pan_GetKey(evm_pan_KeyEvent_t *KeyInfo , evm_s32 Timeout);
#endif

ret_code_e evm_porting_pan_RegisterEvent(evm_pan_EventType_t type, const evm_pan_EventCallback cb);

/*
 * Function: evm_porting_pan_RegisterInputDevStatus
 * Description:  注册外界设备的状态通知函数，例如设备插入，拔出
 * Input:
 *          cb： 回调函数
 * Output: none
 * Return: 0:SUCCESS , other is Fail
 */
ret_code_e evm_porting_pan_RegisterInputDevStatusCB(const input_dev_cb cb);

/*
 * Function: evm_porting_pan_Display
 * Description: 设置面板显示内容
 * Input:
 *          Data: 需要显示的数据，以字符串形式
            Len:需要显示字符长度
 * Output: none
 * Return: 0:SUCCESS , other is Fail
 */
ret_code_e evm_porting_pan_Display(evm_u8 *Data , evm_u32 Len);


/*
 * Function: evm_porting_pan_Display
 * Description: 数码管显示当前时间
 * Input:
 *          Hour: 需要显示的小时数
            Minute: 需要显示的分钟数
 * Output: none
 * Return: 0:SUCCESS , other is Fail
 */
ret_code_e evm_porting_pan_TimeDisplay(evm_u32 Hour,evm_u32 Minute);





/*
* Function:      evm_porting_SetIRCode
* Description: 设置遥控器的用户码类型
* Input:
            CodeMode : 需要设置的遥控器的用户码
                               0 代表两种用户码都需支持；(fd01 与e608)
                               1 代表只支持fd01用户码；
                               2 代表只支持e608用户码。
 *Output:none
 *Return: 0:Success,other is fail
*/

ret_code_e evm_porting_pan_SetIRCode(evm_s32 CodeMode);

/*
*Function: evm_porting_GetPowerKey
*Description:  获取当前用户的待机键值
*Input:
        NA
*OutPut:
        KeyValue : 得到当前用户的待机键值
*Return:成功返回EVM_SUCCESS;失败返回EVM_FAILURE;
*/

ret_code_e evm_porting_pan_GetPowerKey(evm_u64 *KeyValue);

/*
*Function: evm_porting_PanEnable
*Description:  设置IR 遥控器按键使能
*Input:
        PanEnable: EVM_TRUE 为使能；
                          EVM_FALSE为去使能；
*OutPut:
        NA
*Return:NULL;
*/
void evm_porting_pan_Enable(bool PanEnable);


/*
*Function: evm_porting_Pan_SetLockLed
*Description:  设置前面板锁频灯工作状态
*Input:
        bLockFlag: EVM_TRUE  点亮；
                          EVM_FALSE  熄灭；
*OutPut:
        NA
*Return:成功返回EVM_SUCCESS,失败返回EVM_FAILURE;
*/

ret_code_e evm_porting_pan_SetLockLed(bool bLockFlag);

/*
*Function: evm_porting_pan_GetIrType
*Description:  获取底层的ir类型
*Input:
        irType: 返回ir类型
*OutPut:
        NA
*Return:成功返回EVM_SUCCESS,失败返回EVM_FAILURE;
*/

ret_code_e evm_porting_pan_GetIrType(evm_ir_param_t *irType);

/*
*Function: evm_porting_pan_SetKeyStatus
*Description:  通知底层目前key所在的状态，用于底层做一些特殊处理
*Input:
        keyStatus,当前状态
*OutPut:
        NA
*Return:成功返回EVM_SUCCESS,失败返回EVM_FAILURE;
*/

ret_code_e evm_porting_pan_SetKeyStatus(evm_key_status_e keyStatus);


/*
*Function: evm_porting_pan_Standby
*Description: 待机
*Input:
*OutPut:
        NA
*Return:成功返回EVM_SUCCESS,失败返回EVM_FAILURE;
*/
ret_code_e evm_porting_pan_Standby();
 // c plus plus
#ifdef __cplusplus
}
#endif


#endif

