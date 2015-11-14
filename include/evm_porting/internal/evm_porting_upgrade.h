#ifndef EVM_PORTING_UPGRADE_H_
#define EVM_PORTING_UPGRADE_H_

#include "../../evm_typedef.h"

#define EVM_UPGRADE_MAX_SN (32) 						//���к���󳤶�
#define EVM_SN_ACTUAL_LEN (26)  //wasuʵ�����кų���
#define EVM_UPGRADE_MAC (12)
#define EVM_LOADER_FILE_NAME_LEN    (128)
#define EVM_LOADER_USER_NAME_LEN EVM_LOADER_FILE_NAME_LEN
#define EVM_UPGRADE_STRING_MAX_SIZE (128)

typedef enum _evm_porting_upgrade_ota_type_e
{
    EVM_PORTING_UPGRADE_TYPE_NONE_E,    //������
    EVM_PORTING_UPGRADE_TYPE_FORCE_E,   //ǿ������
    EVM_PORTING_UPGRADE_TYPE_AUTO_E,    //�Զ�������ѡ ���ʱ���´ο���������
    EVM_PORTING_UPGRADE_TYPE_MANUAL_E,  //�ֶ�������һ��ָ��ҳ��ż������
} evm_porting_upgrade_ota_type_e;

typedef struct _evm_porting_upgrade_param_ota_t
{
    evm_porting_upgrade_ota_type_e eOtaType;		//��������
    //evm_s32 s32MayorNewSwVersion;					//����������� �汾��
    //evm_s32 s32MinorNewSwVersion;					//����������汾��
    evm_u32 u32NewSwVer;
    evm_s32 s32Freq; 								//Ƶ�� KHZΪ��λ
    evm_s32 s32Symb; 								//������kbs
    evm_s32 s32Qam; 								//0-->16Qam;1->32Qam;2->64Qam;3->128Qam;4->256Qam
    evm_s32 s32ServiceID;
    evm_s32 s32CompnentTag;
    evm_u32 UpgrdModule;    						//����ģʽ

    evm_s32 s32DownloadPid;							//����������pid
} evm_porting_upgrade_param_ota_t;

/**CNcomment:IP����ʱʹ��IP��ַ���Ͷ���*/
typedef enum _evm_loader_ip_type_e
{
    IP_TYPE_STATIC = 0,    /**< Use static IP *//**CNcomment:< ʹ�þ�̬IP */
    IP_TYPE_DHCP,          /**< Use dynamic IP *//**CNcomment:< ʹ�ö�̬IP */
    IP_TYPE_BUTT
} evm_loader_ip_type_e;

// +++ add by zhangsc +++
/**Definition of the IP address type used in IP upgrade*/
/*CNcomment:*����ʱʹ������Э�鶨��*/
typedef enum _evm_loader_ip_protocol_e
{
    PROTO_TFTP = 0,     /**<Use TFTP protocol*//**CNcomment:< TFTPЭ������ */
    PROTO_FTP,          /**<Use FTP protocol*//**CNcomment:< FTPЭ������ */
    PROTO_HTTP,         /**<Use HTTP protocol*//**CNcomment:< HTTPЭ������*/

    PROTO_BUTT
} evm_loader_ip_protocol_e;

typedef struct _evm_porting_upgrade_param_ip_t
{
    evm_loader_ip_protocol_e eProtocol;    /**< Protocol of data download 0:TFTP, 1:FTP, 2 HTTP>*//**CNcomment:< ��������Э�� 0:TFTP, 1:FTP, 2 HTTP >*/
    evm_loader_ip_type_e eIpType;            /**< Used by the IP loader. IP obtaining mode.*//**CNcomment:< ip  loaderʹ��, ip��ȡ����*/

    /*Configure the following parameters only when static IP addresses are used.*/
    evm_u32 ipOurIp;            /**< Used by the IP loader. Local IP address. *//**CNcomment:< ip  loaderʹ��, ����ip*/
    evm_u32 ipGateway;          /**< Used by the IP loader. Gateway*//**CNcomment:< ip  loaderʹ��, ����*/
    evm_u32 ipSubnetMask;       /**< Used by the IP loader. Subnet mask*//**CNcomment:< ip  loaderʹ��, ��������*/

    evm_u32 ipServer;           /**< Used by the IP loader. Server IP address. *//**CNcomment:< ip  loaderʹ��, ������ip*/
    evm_u16 ipServerPort;       /**< Used by the IP loader. Server port.*/ /**CNcomment:< ip  loaderʹ��, ������port*/

    evm_s8  fileName[EVM_LOADER_FILE_NAME_LEN]; /**<IP Used by the IP loader. Upgrade file name.*/ /**CNcomment:<IP ip  loaderʹ��, �����ļ���*/
    evm_u32 fileSize;           /*Used by the IP loader. Size of upgrade file.*//*CNcomment:*<IP ip  loaderʹ��, �����ļ���С */
    evm_s8  userName[EVM_LOADER_USER_NAME_LEN]; /**<Username, used by FTP.>*/
    evm_s8  password[EVM_LOADER_USER_NAME_LEN]; /**<Password, used by FTP .>*/

    evm_u32 u32NewSwVer;        /**current version of upgrade file*/
} evm_porting_upgrade_param_ip_t;

typedef enum _evm_porting_upgrade_param_type_e
{
    EVM_LOADER_UPGRD_TYPE_NONE, //������
    EVM_LOADER_UPGRD_TYPE_OTA, //cable����
    EVM_LOADER_UPGRD_TYPE_IP, //IP����
    EVM_LOADER_UPGRD_TYPE_USB, //usb����
    EVM_LOADER_UPGRD_TYPE_MAX
} evm_porting_upgrade_param_type_e;

typedef struct _evm_loader_upgrdTag_t
{
    evm_bool bNeedUpgrd; //EVM_TRUE����Ҫ������ EVM_FALSE������Ҫ����
    evm_bool bManualFlag; //EVM_TRUE����Ҫ�ֶ������� EVM_FALSE������Ҫ�ֶ�����
    evm_bool bIsFlashDestory; //EVM_TRUE�������𻵣� EVM_FALSE������δ��
    evm_u32 u32FailedCnt;   // ����������
} evm_loader_upgrdTag_t;

typedef struct _evm_porting_upgrade_param_s
{
    evm_porting_upgrade_param_type_e eType; //������ʽ
    union _param
    {
        evm_porting_upgrade_param_ota_t stOta; //cable
        evm_porting_upgrade_param_ip_t stIp;   // ip
    } param;
}evm_porting_upgrade_param_s;

typedef evm_porting_upgrade_param_s evm_loader_upgrdInfo_t;

// ��¼Cable,IP ��������������������ʶλ��Ϣ
typedef struct _evm_loader_loaderDb_t
{
    evm_loader_upgrdTag_t upgrdTag;    // ��־λ
    evm_loader_upgrdInfo_t stUpgrdInfo;    //�������ͼ�����
    evm_u32 u32CurVer; //��ǰ����汾��
    evm_u32 u32LoaderVer;   // ��ǰloader�汾��
    evm_u32 u32Crc; //evm_loader_loaderDb_t���ݽṹcrc
} evm_loader_loaderDb_t;

typedef struct _evm_porting_upgrade_stbinfo_s
{
    //evm_s32 s32MayorHwVersion; //��Ӳ���汾��
    //evm_s32 s32MinorHwVersion;//��Ӳ���汾��
    //evm_s32 s32MayorSwVersion;//����� �汾��
    //evm_s32 s32MinorSwVersion;//������汾��
    //evm_s32 s32MayorNewSwVersion;//����������� �汾��
    //evm_s32 s32MinorNewSwVersion;//����������汾��
    evm_u32 u32HwVer;
    evm_u32 u32SwVer;
    evm_u32 u32NewSwVer;
    
    evm_s32 s32Oui;			//����ID
    evm_s32 s32RegionCode;	//������
    evm_s32 s32StbType;		//����������
    evm_s32 s32HwBatch;		//������Ӳ������
    evm_u32 u32StbSn;		//���������к�
    evm_s8 s8StbID[EVM_UPGRADE_MAX_SN];	//������ID
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
    evm_bool bHasLanCable; //�Ƿ���խ��èģ��
    evm_porting_upgrade_flashInfo_t tFlashInfo;
    evm_porting_upgrade_driverInfo_t tDriverInfo;
    evm_porting_upgrade_osInfo_t tOsInfo;
    evm_porting_upgrade_dramInfo_t tDramInfo;    
}evm_porting_upgrade_stbconfig_s;



/*
 * ����: evm_porting_UpgrdInit
 * ����: ����һ����дloaderDB�Ļ�����
 * �������:
 * �������:
 * ����ֵ:
 * 		�ɹ�����:EVM_SUCCESS,ʧ�ܷ���:EVM_FAILURE;
 */


ret_code_e evm_porting_UpgrdInit(void);


/*
 * ����: evm_upgrade_getStbinfo
 * ����: ��ȡ���������������Ϣ
 * �������:
 * �������:
    evm_upgrade_stbinfo_s *pStbinfo ;
 * ����ֵ:
 * 		�μ�ret_code_eö�ٶ���
 */
ret_code_e evm_porting_upgrade_GetStbinfo(evm_porting_upgrade_stbinfo_s *pstStbInfo);

/*
 * ����: evm_upgrade_porting_SaveParam
 * ����: ����pUpgradeParam ������Ϣ
 * �������:
    evm_porting_upgrade_param_s *pUpgradeParam ����������Ϣ
 * �������:
 * ����ֵ:
 * 		�μ�ret_code_eö�ٶ���
 */
ret_code_e evm_porting_upgrade_SaveParam(evm_porting_upgrade_param_s *pUpgradeParam);
/*
 * ����: evm_upgrade_start
 * ����:�˳�Ӧ�ã���ʼ����
 * �������:
 * �������:
 * ����ֵ:
 * 		�μ�ret_code_eö�ٶ���
 */
ret_code_e evm_porting_upgrade_ReStart(void);


/*
 * ����: evm_GetChipId
 * ����:�˳�Ӧ�ã���ʼ����
 * �������:
            chipid:��ȡid��
 * �������:
            chipid��
 * ����ֵ:
 * 
 * 		�ɹ�����:0����0 ʧ�ܣ�
 */

ret_code_e evm_GetChipId(evm_u32 *ChipId);


/*
 * ����: evm_porting_upgrade_StbConfig
 * ����:�����е�������Ϣ
 * �������:
 * �������:
 * ����ֵ:
 * 		�μ�ret_code_eö�ٶ���
 */
ret_code_e evm_porting_upgrade_StbConfig( evm_porting_upgrade_stbconfig_s  *pstUpgradeConfig);
ret_code_e evm_porting_upgrade_UpdateSerialNo(evm_s8* sn, evm_s32 len);
#endif

