#ifndef EVM_PORTING_UPGRADE_H_
#define EVM_PORTING_UPGRADE_H_

#include "../../evm_typedef.h"

#define EVM_UPGRADE_MAX_SN (32) 						//序列号最大长度
#define EVM_SN_ACTUAL_LEN (26)  //wasu实际序列号长度
#define EVM_UPGRADE_MAC (12)
#define EVM_LOADER_FILE_NAME_LEN    (128)
#define EVM_LOADER_USER_NAME_LEN EVM_LOADER_FILE_NAME_LEN
#define EVM_UPGRADE_STRING_MAX_SIZE (128)

typedef enum _evm_porting_upgrade_ota_type_e
{
    EVM_PORTING_UPGRADE_TYPE_NONE_E,    //无升级
    EVM_PORTING_UPGRADE_TYPE_FORCE_E,   //强制升级
    EVM_PORTING_UPGRADE_TYPE_AUTO_E,    //自动升级。选 择否时，下次开机会升级
    EVM_PORTING_UPGRADE_TYPE_MANUAL_E,  //手动升级，一般指定页面才检测升级
} evm_porting_upgrade_ota_type_e;

typedef struct _evm_porting_upgrade_param_ota_t
{
    evm_porting_upgrade_ota_type_e eOtaType;		//升级类型
    //evm_s32 s32MayorNewSwVersion;					//升级后主软件 版本号
    //evm_s32 s32MinorNewSwVersion;					//升级后副软件版本号
    evm_u32 u32NewSwVer;
    evm_s32 s32Freq; 								//频点 KHZ为单位
    evm_s32 s32Symb; 								//符号率kbs
    evm_s32 s32Qam; 								//0-->16Qam;1->32Qam;2->64Qam;3->128Qam;4->256Qam
    evm_s32 s32ServiceID;
    evm_s32 s32CompnentTag;
    evm_u32 UpgrdModule;    						//升级模式

    evm_s32 s32DownloadPid;							//数据流下载pid
} evm_porting_upgrade_param_ota_t;

/**CNcomment:IP升级时使用IP地址类型定义*/
typedef enum _evm_loader_ip_type_e
{
    IP_TYPE_STATIC = 0,    /**< Use static IP *//**CNcomment:< 使用静态IP */
    IP_TYPE_DHCP,          /**< Use dynamic IP *//**CNcomment:< 使用动态IP */
    IP_TYPE_BUTT
} evm_loader_ip_type_e;

// +++ add by zhangsc +++
/**Definition of the IP address type used in IP upgrade*/
/*CNcomment:*升级时使用下载协议定义*/
typedef enum _evm_loader_ip_protocol_e
{
    PROTO_TFTP = 0,     /**<Use TFTP protocol*//**CNcomment:< TFTP协议下载 */
    PROTO_FTP,          /**<Use FTP protocol*//**CNcomment:< FTP协议下载 */
    PROTO_HTTP,         /**<Use HTTP protocol*//**CNcomment:< HTTP协议下载*/

    PROTO_BUTT
} evm_loader_ip_protocol_e;

typedef struct _evm_porting_upgrade_param_ip_t
{
    evm_loader_ip_protocol_e eProtocol;    /**< Protocol of data download 0:TFTP, 1:FTP, 2 HTTP>*//**CNcomment:< 数据下载协议 0:TFTP, 1:FTP, 2 HTTP >*/
    evm_loader_ip_type_e eIpType;            /**< Used by the IP loader. IP obtaining mode.*//**CNcomment:< ip  loader使用, ip获取类型*/

    /*Configure the following parameters only when static IP addresses are used.*/
    evm_u32 ipOurIp;            /**< Used by the IP loader. Local IP address. *//**CNcomment:< ip  loader使用, 本机ip*/
    evm_u32 ipGateway;          /**< Used by the IP loader. Gateway*//**CNcomment:< ip  loader使用, 网关*/
    evm_u32 ipSubnetMask;       /**< Used by the IP loader. Subnet mask*//**CNcomment:< ip  loader使用, 子网掩码*/

    evm_u32 ipServer;           /**< Used by the IP loader. Server IP address. *//**CNcomment:< ip  loader使用, 服务器ip*/
    evm_u16 ipServerPort;       /**< Used by the IP loader. Server port.*/ /**CNcomment:< ip  loader使用, 服务器port*/

    evm_s8  fileName[EVM_LOADER_FILE_NAME_LEN]; /**<IP Used by the IP loader. Upgrade file name.*/ /**CNcomment:<IP ip  loader使用, 升级文件名*/
    evm_u32 fileSize;           /*Used by the IP loader. Size of upgrade file.*//*CNcomment:*<IP ip  loader使用, 升级文件大小 */
    evm_s8  userName[EVM_LOADER_USER_NAME_LEN]; /**<Username, used by FTP.>*/
    evm_s8  password[EVM_LOADER_USER_NAME_LEN]; /**<Password, used by FTP .>*/

    evm_u32 u32NewSwVer;        /**current version of upgrade file*/
} evm_porting_upgrade_param_ip_t;

typedef enum _evm_porting_upgrade_param_type_e
{
    EVM_LOADER_UPGRD_TYPE_NONE, //无升级
    EVM_LOADER_UPGRD_TYPE_OTA, //cable升级
    EVM_LOADER_UPGRD_TYPE_IP, //IP升级
    EVM_LOADER_UPGRD_TYPE_USB, //usb升级
    EVM_LOADER_UPGRD_TYPE_MAX
} evm_porting_upgrade_param_type_e;

typedef struct _evm_loader_upgrdTag_t
{
    evm_bool bNeedUpgrd; //EVM_TRUE：需要升级， EVM_FALSE：不需要升级
    evm_bool bManualFlag; //EVM_TRUE：需要手动升级， EVM_FALSE：不需要手动升级
    evm_bool bIsFlashDestory; //EVM_TRUE：分区损坏， EVM_FALSE：分区未损坏
    evm_u32 u32FailedCnt;   // 升级计数器
} evm_loader_upgrdTag_t;

typedef struct _evm_porting_upgrade_param_s
{
    evm_porting_upgrade_param_type_e eType; //升级方式
    union _param
    {
        evm_porting_upgrade_param_ota_t stOta; //cable
        evm_porting_upgrade_param_ip_t stIp;   // ip
    } param;
}evm_porting_upgrade_param_s;

typedef evm_porting_upgrade_param_s evm_loader_upgrdInfo_t;

// 记录Cable,IP 升级参数、计数器、标识位信息
typedef struct _evm_loader_loaderDb_t
{
    evm_loader_upgrdTag_t upgrdTag;    // 标志位
    evm_loader_upgrdInfo_t stUpgrdInfo;    //升级类型及参数
    evm_u32 u32CurVer; //当前软件版本号
    evm_u32 u32LoaderVer;   // 当前loader版本号
    evm_u32 u32Crc; //evm_loader_loaderDb_t数据结构crc
} evm_loader_loaderDb_t;

typedef struct _evm_porting_upgrade_stbinfo_s
{
    //evm_s32 s32MayorHwVersion; //主硬件版本号
    //evm_s32 s32MinorHwVersion;//副硬件版本号
    //evm_s32 s32MayorSwVersion;//主软件 版本号
    //evm_s32 s32MinorSwVersion;//副软件版本号
    //evm_s32 s32MayorNewSwVersion;//升级后主软件 版本号
    //evm_s32 s32MinorNewSwVersion;//升级后副软件版本号
    evm_u32 u32HwVer;
    evm_u32 u32SwVer;
    evm_u32 u32NewSwVer;
    
    evm_s32 s32Oui;			//厂商ID
    evm_s32 s32RegionCode;	//区域码
    evm_s32 s32StbType;		//机顶盒类型
    evm_s32 s32HwBatch;		//机顶盒硬件批次
    evm_u32 u32StbSn;		//机顶盒序列号
    evm_s8 s8StbID[EVM_UPGRADE_MAX_SN];	//机顶盒ID
} evm_porting_upgrade_stbinfo_s;

typedef struct _evm_porting_upgrade_dramInfo_t
{
    evm_u32 uDramSize;
    evm_u32 uDramFrequency;
} evm_porting_upgrade_dramInfo_t;


typedef struct _evm_porting_upgrade_osInfo_t
{
    evm_s8 osName[EVM_UPGRADE_STRING_MAX_SIZE];
    evm_s8 osProvider[EVM_UPGRADE_STRING_MAX_SIZE];
    evm_s8 osVersion[EVM_UPGRADE_STRING_MAX_SIZE];
} evm_porting_upgrade_osInfo_t;

typedef struct _evm_porting_upgrade_driverInfo_t
{
    evm_s8  driverName[EVM_UPGRADE_STRING_MAX_SIZE];
    evm_s8  driverProvider[EVM_UPGRADE_STRING_MAX_SIZE];
    evm_u32 uDriverSize;
    evm_s8  driverVersion[EVM_UPGRADE_STRING_MAX_SIZE];
}  evm_porting_upgrade_driverInfo_t;

typedef struct _evm_porting_upgrade_flashInfo_t
{
    evm_u32 uFlahSize;
}  evm_porting_upgrade_flashInfo_t;


typedef struct _evm_porting_upgrade_stbconfig_s
{
    evm_bool bHasLanCable; //是否有窄带猫模块
    evm_porting_upgrade_flashInfo_t tFlashInfo;
    evm_porting_upgrade_driverInfo_t tDriverInfo;
    evm_porting_upgrade_osInfo_t tOsInfo;
    evm_porting_upgrade_dramInfo_t tDramInfo;    
}evm_porting_upgrade_stbconfig_s;



/*
 * 函数: evm_porting_UpgrdInit
 * 描述: 创建一个读写loaderDB的互斥锁
 * 输入参数:
 * 输出参数:
 * 返回值:
 * 		成功返回:EVM_SUCCESS,失败返回:EVM_FAILURE;
 */


ret_code_e evm_porting_UpgrdInit(void);


/*
 * 函数: evm_upgrade_getStbinfo
 * 描述: 获取机顶盒升级相关信息
 * 输入参数:
 * 输出参数:
    evm_upgrade_stbinfo_s *pStbinfo ;
 * 返回值:
 * 		参见ret_code_e枚举定义
 */
ret_code_e evm_porting_upgrade_GetStbinfo(evm_porting_upgrade_stbinfo_s *pstStbInfo);

/*
 * 函数: evm_upgrade_porting_SaveParam
 * 描述: 保存pUpgradeParam 升级信息
 * 输入参数:
    evm_porting_upgrade_param_s *pUpgradeParam 升级参数信息
 * 输出参数:
 * 返回值:
 * 		参见ret_code_e枚举定义
 */
ret_code_e evm_porting_upgrade_SaveParam(evm_porting_upgrade_param_s *pUpgradeParam);
/*
 * 函数: evm_upgrade_start
 * 描述:退出应用，开始升级
 * 输入参数:
 * 输出参数:
 * 返回值:
 * 		参见ret_code_e枚举定义
 */
ret_code_e evm_porting_upgrade_ReStart(void);


/*
 * 函数: evm_GetChipId
 * 描述:退出应用，开始升级
 * 输入参数:
            chipid:获取id；
 * 输出参数:
            chipid；
 * 返回值:
 * 
 * 		成功返回:0，非0 失败；
 */

ret_code_e evm_GetChipId(evm_u32 *ChipId);


/*
 * 函数: evm_porting_upgrade_StbConfig
 * 描述:机顶盒的配置信息
 * 输入参数:
 * 输出参数:
 * 返回值:
 * 		参见ret_code_e枚举定义
 */
ret_code_e evm_porting_upgrade_StbConfig( evm_porting_upgrade_stbconfig_s  *pstUpgradeConfig);
ret_code_e evm_porting_upgrade_UpdateSerialNo(evm_s8* sn, evm_s32 len);
#endif

