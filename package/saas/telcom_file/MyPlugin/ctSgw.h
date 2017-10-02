#ifndef __CT_SGW_API_H__
#define __CT_SGW_API_H__


/**
 * IP��ַ�ַ�����󳤶�
 */
#define CT_IP_ADDR_STR_MAX_LEN    (16)

/**
 * IPv6��ַ�ַ�����󳤶�
 */
#define CT_IPV6_ADDR_STR_MAX_LEN    (64)

/**
 * USB�豸������󳤶�
 */
#define CT_USB_DEV_NAME_MAX_LEN    (128)

/**
 * USB�洢�豸mount·����󳤶�
 */
#define CT_USB_DEV_MOUNT_PATH_MAX_LEN    (256)

/**
 * ����SSID��󳤶�
 */
#define CT_WLAN_SSID_MAX_LEN    (32)

/**
 * ����������󳤶�
 */
#define CT_WLAN_PASSWORD_MAX_LEN    (32)


/**
 * �豸������󳤶�
 */
#define CT_LAN_DEV_NAME_MAX_LEN    (64)

/**
 * �豸Ʒ��������󳤶�
 */
#define CT_LAN_DEV_BRAND_NAME_MAX_LEN    (64)

/**
 * �豸����ϵͳ������󳤶�
 */
#define CT_LAN_DEV_OS_NAME_MAX_LEN    (64)

/**
 * �¼�����
 */
typedef enum
{
	CT_EVENT_USB_DEV_ACTION,
	CT_EVENT_WAN_IP_CHANGE,
	CT_EVENT_WLAN_DEV_ONLINE
} CtEventType;


/**
 * USB�豸��������
 */
typedef enum
{
    CT_USB_DEV_ACTION_INSERT,
    CT_USB_DEV_ACTION_PULL,
} CtUsbDevActionType;


/**
 * USB�豸����
 */
typedef enum
{
    CT_USB_DEV_SERIAL = 0x1,
    CT_USB_DEV_CDC_ACM = 0x2,
    CT_USB_DEV_HID = 0x4,
    CT_USB_DEV_STORAGE = 0x8,
} CtUsbDevType;


/**
 * LAN�豸��������
 */
typedef enum
{
    CT_LAN_DEV_CONN_UNKNOWN,
    CT_LAN_DEV_CONN_WIRED,
    CT_LAN_DEV_CONN_WLAN,
} CtLanDevConnType;


/**
 * LAN�豸����
 */
typedef enum
{
    CT_LAN_DEV_UNKNOWN,
    CT_LAN_DEV_PHONE,
    CT_LAN_DEV_PAD,
    CT_LAN_DEV_PC,
    CT_LAN_DEV_STB,
    CT_LAN_DEV_OTHER
} CtLanDevType;


/**
 * ���߰�ȫģʽ
 */
typedef enum
{
    CT_WL_AUTH_OPEN ,
    CT_WL_AUTH_SHARED,        
    CT_WL_AUTH_WPA_PSK,
    CT_WL_AUTH_WPA2_PSK,
    CT_WL_AUTH_WPA2_PSK_MIX    
} CtWlanAuthMode;


/**
 * ��żУ������
 */
typedef enum
{
    CT_PARITY_NONE,  /* û��У��λ*/
    CT_PARITY_EVEN,  /* żУ�� */
    CT_PARITY_ODD,  /* ��У�� */
    CT_PARITY_MARK,  /* У��λʼ��Ϊ1 */
    CT_PARITY_SPACE,  /* У��λʼ��Ϊ0 */
} CtParityType;



/**
 * USB�豸�¼�
 */
typedef struct
{
    CtUsbDevActionType actionType;  /* �������� */
    CtUsbDevType devType;  /* �豸���� */
    int devId;  /* �豸��ʶ */
    char devName[CT_USB_DEV_NAME_MAX_LEN];  /* USB�洢�豸���� */
    char mountPath[CT_USB_DEV_MOUNT_PATH_MAX_LEN];  /* USB�洢�豸mount·�� */
} CtUsbDevEvent;


/**
 * ����WAN����IP�ı��¼�
 */
typedef struct
{
    char ipAddr[CT_IP_ADDR_STR_MAX_LEN];
    char subnetMask[CT_IP_ADDR_STR_MAX_LEN];
    char ipv6Addr[CT_IPV6_ADDR_STR_MAX_LEN];
    int prefixLen;
} CtWanIpChangeEvent;


/**
 * �����¹��豸�����¼�
 */
typedef struct
{
    unsigned char macAddr[6];
} CtWlanDevOnlineEvent;


/**
 * ϵͳIP��ַ����
 */
typedef struct
{
    char wanIpAddr[CT_IP_ADDR_STR_MAX_LEN];
    char wanSubnetMask[CT_IP_ADDR_STR_MAX_LEN];
    char ipv6WanAddr[CT_IPV6_ADDR_STR_MAX_LEN];
    int wanPrefixLen;
    char lanIpAddr[CT_IP_ADDR_STR_MAX_LEN];
    char lanSubnetMask[CT_IP_ADDR_STR_MAX_LEN];
    char ipv6LanAddr[CT_IPV6_ADDR_STR_MAX_LEN];
    int lanPrefixLen;
} CtSysIpAddrCfg;


/**
 * MAC��ַ
 */
typedef struct
{
    unsigned char macAddr[6];
} CtMacAddr;


/**
 * IP��ַ
 */
typedef struct
{
    char ipAddr[CT_IP_ADDR_STR_MAX_LEN];
} CtIpAddr;


/**
 * �豸��Ϣ
 */
typedef struct
{
    char devName[CT_LAN_DEV_NAME_MAX_LEN];  /** ������� */
    CtLanDevType devType;  /** �豸���� */
    unsigned char macAddr[6];  /** MAC��ַ */
    char ipAddr[CT_IP_ADDR_STR_MAX_LEN];  /** IP��ַ */
    CtLanDevConnType connType;  /** ������ʽ*/
    int port;  /** ���Ӷ˿ڣ�0��δ֪��1��lan1�����ӣ�2��lan2�����ӣ�3��lan3�����ӣ�4��lan4������ ��5��SSID-1��6��SSID-2��7��SSID-3��8��SSID-4��9��SSID-5��10��SSID-6��11��SSID-7��12��SSID-8*/
    char brandName[CT_LAN_DEV_BRAND_NAME_MAX_LEN];  /** Ʒ������ */
    char osName[CT_LAN_DEV_OS_NAME_MAX_LEN];  /** ����ϵͳ���� */
    unsigned int onlineTime;  /** ����ʱ������λΪ��*/
} CtLanDevInfo;


/**
 * ���߰�ȫ���ò���
 */
typedef struct
{
    int enable;
    CtWlanAuthMode authMode;
    char ssid[CT_WLAN_SSID_MAX_LEN];
    char password[CT_WLAN_PASSWORD_MAX_LEN];
} CtWlanSecurityCfg;


/**
 * �������ò���
 */
typedef struct
{
    int bandrate;  /* ��ʾ������ */
    CtParityType parity;  /* ��żУ������ */
    int dataBits;  /* ��ʾ����λ */
    int stopBits;  /* ��ʾֹͣλ */
    int hwFlowCtrl;  /* ��ʾ�Ƿ���Ӳ�����أ�0��ʾ�رգ�1��ʾ���� */
    int swFlowCtrl;  /* ��ʾ�Ƿ���������أ�0��ʾ�رգ�1��ʾ���� */
} CtUsbSerialCfg;


/*
DPI��������ṹ
*/
typedef struct CtSgwTupleInfo_{
	unsigned char direct;
	unsigned char proto;
	unsigned int sipv4;
	unsigned int dipv4;
	unsigned int sipv6[4];
	unsigned int dipv6[4];
	unsigned short sport;
	unsigned short dport;
	unsigned long in_iif;/* ���Ľ��ӿ�index*/
	unsigned long out_iif;/*���ĳ��ӿ�index*/
}CtSgwTupleInfo;

/*
DPI ����ص���������ṹ
*/
typedef  int  (*ctSgw_appCtxCreate)(void** p_app_ctx, unsigned char flag);
typedef  void (*ctSgw_appCtxDestroy)(void** p_app_ctx);
typedef  int (*ctSgw_appProcAppId)(unsigned char *layer2data, CtSgwTupleInfo *tupleinfo, void *p_app_ctx, unsigned int *layer7_id);

typedef struct ctSgw_dpiFuncs_
{
    ctSgw_appCtxCreate  ctSgw_appCtxCreateHook;
    ctSgw_appCtxDestroy ctSgw_appCtxDestroyHook;
	ctSgw_appProcAppId  ctSgw_appProcAppIdHook;
} ctSgw_dpiFuncs;

/**
 * ��ʼ��ģ��
 * @param sock(OUT) ���ص���Ϣ�����׽���
 * @return �����룬0��ʾ�ɹ���-1��ʾʧ��
 */
int ctSgw_init(int *sock);


/**
 * ����ģ��
 * @return �����룬0��ʾ�ɹ���-1��ʾʧ��
 */
int ctSgw_cleanup(void);


/**
 * �����¼�
 * @param eventType(OUT) ���ص��¼�����
 * @param eventInfo(OUT) ���ص��¼���Ϣ����̬�����ڴ棬��Ҫ�������ͷ�
 * @return �����룬0��ʾ�ɹ���-1��ʾʧ��
 */
int ctSgw_handleEvent(CtEventType *eventType, void **eventInfo);


/**
 * ��������SSID����״̬
 * @param ssidIndex(IN) SSID��ţ����ڵ�Ƶ������Ϊ1-4������˫Ƶ����Ϊ1-8����Ϊ0ʱ����ʾ����Wifiģ��
 * @param enable(IN) 0��ʾ�رգ�1��ʾ����
 * @return �����룬0��ʾ�ɹ���-1��ʾʧ��
 */
int ctSgw_wlanSetState(int ssidIndex, int enable);


/**
 * ��ȡWLAN��SSID-1���İ�ȫ����
 * @param securityCfg(OUT) ���ص����߰�ȫ����
 * @return �����룬0��ʾ�ɹ���-1��ʾʧ��
 */
int ctSgw_wlanGetSecurityCfg(CtWlanSecurityCfg *securityCfg);


/**
 * ��ȡLAN���豸��Ϣ
 * @param devInfoList(OUT) ���ص��豸��Ϣ�б���̬�����ڴ棬��Ҫ�������ͷ�
 * @param devNum(OUT) ���ص��豸��Ϣ����
 * @return �����룬0��ʾ�ɹ���-1��ʾʧ��
 */
int ctSgw_lanGetDevInfo(CtLanDevInfo **devInfoList, int *devNum);


/**
 * ����LAN���豸��Ϣ
 * @param devInfo(IN) �豸��Ϣ������
 *   devInfo->macAddr������ʶ��Ҫ���µ��豸������Ϊ�� *   devInfo->devNameΪ�ձ�ʾ����Ҫ����
 *   devInfo->devTypeΪCT_LAN_DEV_UNKNOWN��ʾ����Ҫ����
 *   devInfo->ipAddrΪ�ձ�ʾ����Ҫ����
 *   devInfo->connTypeΪCT_LAN_DEV_CONN_UNKNOWN��ʾ����Ҫ����
 *   devInfo->portΪ0��ʾ����Ҫ����
 *   devInfo->brandNameΪ�ձ�ʾ����Ҫ����
 *   devInfo->osNameΪ�ձ�ʾ����Ҫ����
 *   devInfo->onlineTimeӦ���ԣ�����Ҫ����
 * @return �����룬0��ʾ�ɹ���-1��ʾʧ��
 */
int ctSgw_lanUpdateDevInfo(const CtLanDevInfo *devInfo);


/**
 * ����LAN���豸����Ȩ��
 * @param macAddr(IN) �豸MAC��ַ
 * @param internetAccess(IN) �Ƿ��������Internet��0��ʾ������1��ʾ����
 * @param storageAccess(IN) �Ƿ�������ʴ洢�豸��0��ʾ������1��ʾ����
 * @return �����룬0��ʾ�ɹ���-1��ʾʧ��
 */
int ctSgw_lanSetDevAccessPermission(const CtMacAddr *macAddr, int internetAccess, int storageAccess);


/**
 * ��ȡLAN���豸Internet���ʺ�����
 * @param macAddrList(OUT) ���ص��豸�б���̬�����ڴ棬��Ҫ�������ͷ�
 * @param macAddrNum(OUT) ���ص��豸����
 * @return �����룬0��ʾ�ɹ���-1��ʾʧ��
 */
int ctSgw_lanGetDevInternetAccessBlacklist(CtMacAddr **macAddrList, int *macAddrNum);


/**
 * ��ȡLAN���豸�洢���ʺ�����
 * @param macAddrList(OUT) ���ص��豸�б���̬�����ڴ棬��Ҫ�������ͷ�
 * @param macAddrNum(OUT) ���ص��豸����
 * @return �����룬0��ʾ�ɹ���-1��ʾʧ��
 */
int ctSgw_lanGetDevStorageAccessBlacklist(CtMacAddr **macAddrList, int *macAddrNum);


/**
 * ��ȡLAN���豸�����д���
 * @param macAddr(IN) �豸MAC��ַ
 * @param usBandwidth(OUT) ���ص����д�����λkbps
 * @param dsBandwidth(OUT) ���ص����д�����λkbps
 * @return �����룬0��ʾ�ɹ���-1��ʾʧ��
 */
int ctSgw_lanGetDevBandwidth(const CtMacAddr *macAddr, int *usBandwidth, int *dsBandwidth);


/**
 * ����LAN���豸������������
 * @param macAddr(IN) �豸MAC��ַ
 * @param usBandwidth(IN) ���д�����λkbps��0��ʾ����
 * @param dsBandwidth(IN) ���д�����λkbps��0��ʾ����
 * @return �����룬0��ʾ�ɹ���-1��ʾʧ��
 */
int ctSgw_lanSetDevMaxBandwidth(const CtMacAddr *macAddr, int usBandwidth, int dsBandwidth);


/**
 * ��ȡLAN���豸������������
 * @param macAddr(IN) �豸MAC��ַ
 * @param usBandwidth(OUT) ���ص����д��� ��λkbps��0��ʾ����
 * @param dsBandwidth(OUT) ���ص����д�����λkbps��0��ʾ����
 * @return �����룬0��ʾ�ɹ���-1��ʾʧ��
 */
int ctSgw_lanGetDevMaxBandwidth(const CtMacAddr *macAddr, int *usBandwidth, int *dsBandwidth);


/**
 * ��ȡ����ӿ�����״̬
 * @param portStatus(OUT) ���صĶ˿�״̬λ���룬1��ʾ���ӣ�0��ʾΪ���ӣ�
                          λ0-5�ֱ��ʾLAN1��-LAN4��, WAN�ں�WiFiģ���״̬
 * @return �����룬0��ʾ�ɹ���-1��ʾʧ��
 */
int ctSgw_lanGetPortStatus(int *portStatus);


/**
 * ����LAN���豸����ͳ��״̬
 * @param enable(IN) ����/ֹͣ����ͳ�ƹ��ܣ�0��ʾ�رգ�1��ʾ����
 * @return �����룬0��ʾ�ɹ���-1��ʾʧ��
 */
int ctSgw_lanSetDevStatsStatus(int enable);


/**
 * ��ȡWAN��ӿ�ͳ��
 * @param usStats(OUT) ���ص�����ͳ�ƣ���λKbyte
 * @param dsStats(OUT) ���ص�����ͳ�ƣ���λKbyte
 * @return �����룬0��ʾ�ɹ���-1��ʾʧ��
 */
int ctSgw_wanGetIfStats(int *usStats, int *dsStats);


/**
 * ��ȡWAN��PPPoE�ʺ�
 * @param pppoeAccount(OUT) ���ص�PPPoE�˺�
 * @param accountLen(IN) �˺Ŵ洢����������
 * @return �����룬0��ʾ�ɹ���-1��ʾʧ��
 */
int ctSgw_wanGetPppoeAccount(char *pppoeAccount, int len);


/**
 * ��ȡCPUռ����
 * @param status(OUT) ���ص�CPUռ���ʰٷֱ�
 * @return �����룬0��ʾ�ɹ���-1��ʾʧ��
 */
int ctSgw_sysGetCpuUsage(int *percent);


/**
 * ��ȡ�ڴ�ռ����
 * @param status(OUT) ���ص��ڴ�ռ���ʰٷֱ�
 * @return �����룬0��ʾ�ɹ���-1��ʾʧ��
 */
int ctSgw_sysGetMemUsage(int *percent);


/**
 * ��ȡLAN/WAN��IP��ַ
 * @param ipAddrCfg(OUT) ���ص�IP��ַ����
 * @return �����룬0��ʾ�ɹ���-1��ʾʧ��
 */
int ctSgw_sysGetIpAddr(CtSysIpAddrCfg *ipAddrCfg);


/**
 * ��ȡLOID
 * @param loid(OUT) ���ص�loid
 * @param loidLen(IN) loid����������
 * @return �����룬0��ʾ�ɹ���-1��ʾʧ��
 */
int ctSgw_sysGetLoid(char *loid, int len);


/*
* ��ȡ����MAC��ַ
* @param MAC(OUT) ���ص�6�ֽ�MAC  
* @return �����룬0��ʾ�ɹ���-1��ʾʧ��
*/
int ctSgw_sysGetMac(unsigned char mac[6]);


/**
 * ����ҳ��
 * @param enable(IN)���͹����Ƿ�����0 ��ʾ�رգ�1��ʾ����
 * @param width(IN) ������
 * @param height(IN) ����߶�
 * @param place(IN) ���嵯��ҳ��λ�ã�����ԭ��Ϊ��Ļ����λ�ã���λΪ����
 * @param url(IN) ����URL
 * @param time(IN) ��������ʱ�䣬�������յ����ӿ�ʱ����TIME ʱ���ڣ������⵽�û����������ؽ�URL ���͵��û�����������û����⵽�����ؽ������β�������λΪ��
 * @return �����룬0��ʾ�ɹ���-1��ʾʧ��
 */
int ctSgw_sysPushWeb(int enable, int width, int height, int place, const char *url, int time);


/**
 * ע�����Ȥ��USB�豸����
 * @param devType(IN) ����Ȥ��USB�豸����
 * @return �����룬0��ʾ�ɹ���-1��ʾʧ��
 */
int ctSgw_usbRegister(CtUsbDevType devType);


/**
 * ��ע�����и���Ȥ���豸����
 * @return �����룬0��ʾ�ɹ���-1��ʾʧ��
 */
int ctSgw_usbUnregister(void);


/**
 * ����USB�豸
 * @param devId(IN) USB�豸��ʶ
 * @return �����룬0��ʾ�ɹ���-1��ʾʧ��
 */
int ctSgw_usbLock(int devId);


 /**
 * ����USB�豸
 * @param devId(IN) USB�豸��ʶ
 * @return �����룬0��ʾ�ɹ���-1��ʾʧ��
 */
int ctSgw_usbUnlock(int devId);


/**
 * ��USB�豸
 * @param devId(IN) USB�豸��ʶ
 * @param handle(OUT) ���ص�USB�豸�������
 * @return �����룬0��ʾ�ɹ���-1��ʾʧ��
 */
int ctSgw_usbOpen(int devId, int *handle);


/**
 * ���USB�豸���Ƿ������ݿ��Զ�ȡ
* @param handle(IN) USB�豸�������
* @return �Ƿ�������ݿɶ���0��ʾû�����ݿɶ��� 1��ʾ�������ݿɶ�
 */
int ctSgw_usbDataAvailable(int handle);


/**
 * ��USB�豸�ж�����
 * @param handle(IN) USB�豸�������
 * @param buf(OUT) ���صĶ�ȡ����
 * @param count(IN/OUT) ��Ҫ��ȡ�����ݳ���/ʵ�ʶ�ȡ�����ݳ���
* @param timeout (IN) �ȴ����ݿ��õĳ�ʱʱ�䣬��λΪ���룬0��ʾ���ȴ���-1��ʾһֱ�ȴ�
 * @return �����룬0��ʾ�ɹ���-1��ʾʧ�ܣ�-2��ʾ��ʱ
 */
int ctSgw_usbRead(int handle, void *buf, size_t *count, int timeout);


/**
 * ��USB�豸��д����
 * @param handle(IN) USB�豸�������
 * @param buf(IN) д������
 * @param count(IN/OUT) ��Ҫд������ݳ���/ʵ��д������ݳ���
 * @return �����룬0��ʾ�ɹ���-1��ʾʧ��
 */
int ctSgw_usbWrite(int handle, const void *buf, size_t *count);


/**
 * ����USB��������
 * @param handle(IN) USB�豸�������
 * @param serialCfg(IN) ���ò���
 * @return �����룬0��ʾ�ɹ���-1��ʾʧ��
 */
int ctSgw_usbSetSerial(int handle, const CtUsbSerialCfg *serialCfg);


/**
 * �ر�USB�豸
 * @param handle(IN) USB�豸�������
 * @return �����룬0��ʾ�ɹ���-1��ʾʧ��
 */
int ctSgw_usbClose(int handle);


/**
 * �ϱ��¼���ƽ̨
 * @param event(IN) ��Ҫ�ϱ����¼���Ϣ����JSON��ʽ��ʾ
 * @return �����룬0��ʾ�ɹ���-1��ʾʧ��
 */
int ctSgw_eventInform(const char *event);


/*
����˵�����ú���������ÿһ���Ự����ʱ����DPI��ص���������Ϣ�������Ựʱ���øýӿڣ�
����˵����p_dpi_ctx(IN)��ָ������ڻỰ�ṹ����ָ��ĵ�ַ��
                 flag(IN)�� ���ã�Ŀǰ������Ϊ0��
����ֵ��0    ��ȷ
              < 0 ����
*/
int ctSgw_dpiCtxCreate(void** p_dpi_ctx, unsigned char flag);
/*


����˵�����ú���������ÿһ���Ự����ʱ�ͷ�DPI��ص���������Ϣ�����ٻỰʱ���øýӿڣ�
����˵����p_dpi_ctx(IN)��ָ������ڻỰ�ṹ����ָ��ĵ�ַ��
����ֵ����
*/
void ctSgw_dpiCtxDestroy(void** p_dpi_ctx);
 

/*
����˵�����ú��������ڻỰ���±��ĵ���ʱ�����øýӿڣ�ִ��DPI�����̣�
����˵����layer2data,(IN) �µ��ﱨ�ĵ�Layer2���ϵ�payload
                 tupleinfo(IN), ���Ķ�Ӧ�Ự��������Ԫ����Ϣ�ͷ����Լ�����ӿ���Ϣ���μ��ṹ��CtSgwTupleInfo����
                 dpi_ctx(IN)�������ڱ�������Ӧ�Ự�ṹ����ָ�룻
                 layer7_id(OUT), ������ֵΪMAXNET_DPI_FINʱ����ֵ��ʾDPIƥ��Ľ��
����ֵ�� 0�� ��ʾDPIδ��ɣ���Ӧ�Ự���±��ĵ���ʱ����Ҫ�������ñ��ӿ�
               1�� ��ʾDPI��ɣ���Ӧ�Ự��������������ñ��ӿ�    
*/
int ctSgw_dpiProcAppId(unsigned char *layer2data, CtSgwTupleInfo *tupleinfo, void *dpi_ctx, unsigned int *layer7_id);
 


/*
����˵�����ú���������DPI�����е��ã��ڱ��Ĵ�����������ע����صĴ�����
����˵����funcs,(IN) ע�ᴦ�����Ľṹ��
����ֵ��   0�� �ɹ�
          -1�� ʧ��               
*/
int ctSgw_appRegisterFunc(ctSgw_dpiFuncs  *funcs);


/*
����˵�����ú���������DPI�����е��ã��ڱ��Ĵ�����������ע����صĴ�����
����˵������ 
����ֵ��   None
*/
void ctSgw_appUnRegisterFunc(void);
#endif

