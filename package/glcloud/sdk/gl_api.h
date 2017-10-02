#ifndef __GL_API_H__
#define __GL_API_H__

typedef enum {
    /* ����͸�����ݵ�app�ˣ��μ�gl_data_t */
    GL_MSG_DATA_TO_APP,
#if 0
    /* ����͸�����ݵ�app�ˣ�ͨ�������������μ�gl_data_t */
    GL_MSG_DATA_TO_APP_LAN,
    /* ����͸�����ݵ��ƶˣ��μ�gl_data_t */
    GL_MSG_DATA_TO_CLOUD,
    /* �����ļ���app�ˣ��μ�gl_file_t */
    GL_MSG_FILE_TO_APP,
#endif
    /* ����ļ�������Ϣ�����͵��ֻ�APP���ο� gl_file_info_t */
    GL_SEND_FIN_FILE_INFO,
    /* �ļ��ϴ��Ľ��ȣ���λ�ǰٷֱȣ����͵��ֻ�APP���ο� gl_file_percent_t */
    GL_SEND_FILE_PERCENT,
    /* ���ƶ˷�������token����Ϣ, ����Ϊ�� */
    GL_SEND_REQUEST_TOKEN,
    /* ���������ѯ���°汾�̼���������� */
    GL_FOTA_GET_INFO,
    /* ��ʼ�������µĹ̼���������� */
    GL_FOTA_DOWNLOAD,
    /* ����豸���б��غ��ƶ˵����ݣ����豸�ָ���������ʱ���ô˽ӿڣ�������� */
    GL_CTRL_RESET_ALL,
    /* ��ʼ�ļ�������Ϣ�����͵��ֻ�APP���ο� gl_file_info_t */
    GL_SEND_START_FILE_INFO,
} gl_send_type_e;

typedef enum {
    /* �յ���app�˷��͹�����͸�����ݣ��μ�gl_data_t */
    GL_MSG_DATA_FROM_APP,
    /* �յ���app�˷��͹�����͸�����ݣ�ͨ�������������μ�gl_data_t */
    GL_MSG_DATA_FROM_APP_LAN,
#if 0
    /* �յ����ƶ˷��͹�����͸�����ݣ��μ�gl_data_t */
    GL_MSG_DATA_FROM_CLOUD,
    /* �յ���app�˵Ĺ����μ�gl_file_t */
    GL_MSG_FILE_FROM_APP,
#endif
    /* ���յ����ļ���Ϣ����APP���͵��豸 */
    GL_RECV_FILE_INFO,
    /* ���յ��������豸�ϴ��ļ��Ľ��ȣ�APP�������󣬲�Я���κβ��� */
    GL_RECV_FILE_PERCENT,
    /* ���յ��ϴ��ļ���tokenֵ */
    GL_RECV_UPLOAD_TOKEN,
    /* �̼�������Ϣ���μ�gl_fota_info_t */
    GL_FOTA_FW_INFO,
    /* �����صĹ̼��ļ����μ�gl_fota_data_t */
    GL_FOTA_FW_DATA,
    /* �����صĹ̼��ļ���У�������μ�gl_fota_result_t */
    GL_FOTA_RESULT,
    /* �յ�����Ϣ˵������豸���б��غ��ƶ˵����ݲ����ɹ����޲������� */
    GL_CTRL_RESET_ALL_ACK,
} gl_recv_type_e;

/* SDK��ʼ��������Ϣ */
typedef struct {
    char *imei;             /* imei��pin����Ψһ��ʶһ���豸�������ṩ */
    char *pin;
    char *product_id;       /* ��Ʒid�������ṩ */
    char *product_name;     /* ��Ʒ����,��󳤶�Ϊ20���ֽڣ���20���ַ� */
#if 0
    host = 0:          dt.gl.igexin.com
    host = 0x61463B7B; 123.59.70.97
    host = 0x62463B7B; 123.59.70.98
#endif
    int host;               /* ָ��Զ�̷�������Ĭ����0 */
    char *sw_ver;           /* �豸�ĵ�ǰ�̼��汾���粻ʹ�ø���FOTA���ܲ������� */
    int sdk_flash_addr;     /* SDK ����������ռ��flash����ʼ��ַ, Ϊ0���ʾ��ʹ�øù���*/
    int sdk_flash_size;     /* SDK ����������ռ��flash�Ĵ�С�� Ϊ0���ʾ��ʹ�øù���*/
} gl_cfg_t;

typedef struct {
    char *data;             /* ͸��������*/
    int len;                /* ͸�����ݳ��ȣ�����С�ڵ���1024*/
    int msg_id;             /* ��Ϣid���ڽ������ݻص������ڷ���ԭ·��������ʹ�ø�msg_id */
                            /* ��������������ʱ���msg_id��Ϊ-1, ������ʧ�� */
                            
    int user_id;            /* ����/���ո���Ϣ���û������ڵ���0��ʾ�ض����û� */
                            /* -1�������а󶨸��豸���û���-2�����ƶ� */
} gl_data_t;


typedef enum
{
    GL_FILE_ENCRYPT_NONE,  /* �޼���*/
    GL_FILE_ENCRYPT_AES,   /* AES ���� */
    GL_FILE_ENCRYPT_END
}gl_file_encrypt_type_e;

typedef enum
{
    GL_FILE_CHECK_NONE,    /* ��У�� */
    GL_FILE_CHECK_MD5,     /* MD5У�鷽ʽ */
    GL_FILE_CHECK_CRC32,   /* CRC32У�鷽ʽ */
    GL_FILE_CHECK_CRC16,   /* CRC8У�鷽ʽ */
    GL_FILE_CHECK_END
}gl_file_check_type_e;

typedef struct
{
    char *file_name;       /* �ļ��� */
    char *file_url;        /* �ļ����ƶ˵�url */
    int  file_size;        /* �ļ���С����λ: Byte*/
    char encrypt_type;     /* �ļ��������ͣ���ο� gl_file_encrypt_type_e */
    char *encrypt_key;     /* ����key */
    char encrypt_key_len;  /* ����key�ĳ��� */
    char check_type;       /* У������, ��ο� gl_file_check_type_e*/
    char *check_key;       /* У��key */
    char check_key_len;    /* У��key�ĳ��� */
    char *file_key;        /* ����ļ��ϴ������ɵ�key */
    int  user_id;          /* ����/���ո���Ϣ���û������ڵ���0��ʾ�ض����û� */
                            /* -1�������а󶨸��豸���û� */
}gl_file_info_t;


typedef struct
{
    char *file_name;       /* �����ļ��� */
    char percent;          /* �ϴ��ļ��Ľ��ȣ��ٷֱ� */
    int  msg_id;           /* ���ڷ��͵��ض����û�������Ϣ����APP�ͻ��˷���ֻ�����ض���APP */        
}gl_file_percent_t;

typedef struct
{
    char *token;           /* �����ϴ��ļ���token,��'\0'���� */
}gl_file_token_t;


typedef struct {
    char *serv_version;     /* �ƶ����¹̼��汾 */
    char force_type;        /* �������ͣ�1��ǿ��������0�����û������� */
    int firmware_size;      /* �̼��Ĵ�С */
} gl_fota_info_t;

typedef struct
{
    int   offset;           /* ���ݵ�ƫ�Ƶ�ַ*/
    char *data_buf;         /* ����buf��ָ�������ļ������� */
    short len;              /* ���ݵĳ��� */
} gl_fota_data_t;

typedef struct
{
    int result;             /* 0��ʾ�����صĹ̼�У������-1��ʾ���س��� */
} gl_fota_result_t;

/*
 * �������û���ص����������յ�app��/�ƶ˵�͸������/�����ļ�����Ϣ�ᴥ���˻ص�
 * ������
 *      msg�� �����յ���Ϣ��ָ�룬����typeֵ����ǿ��ת��
 *      type�������յ���Ϣ������
 * ���أ���
 */
typedef void (*gl_cb_t)(void *msg, gl_recv_type_e type);

/* ������ */
#define GL_OK                   0 /* �ɹ� */
#define GL_ERR                  1 /* ͨ�ô��� */
#define GL_ESRVNOTCONN          2 /* ��δ���ӵ����������� */
#define GL_ENOTREGED            3 /* ��δ�ڸ���������ע��ɹ� */
#define GL_EPARAM               4 /* �������� */
#define GL_EIWAIT               5 /* igelink: �ȴ����� */
#define GL_EISTART              6 /* igelink: ��ʼ����wifi���� */
#define GL_EIGOT_SSID_PASSWD    7 /* igelink: �ѻ��wifi���� */
#define GL_EICONNECTING         8 /* igelink: ����Ŀ��wifi�� */
#define GL_EICONNECTED          9 /* igelink: �ɹ����ӵ�Ŀ��wifi */
#define GL_EIFAILED             10/* igelink: ��ʱʧ�� */

/*
 * ��������ȡSDK�汾
 * ��������
 * ���أ���ǰSDK�汾
 */
char *gl_version(void);

/*
 * ��������ʼ��SDK
 * ������
 *      cfg���μ�gl_cfg_t
 *      cb���μ�gl_cb_t
 * ���أ��μ�������
 */
int gl_init(gl_cfg_t *cfg, gl_cb_t cb);

/*
 * ��������ȡ����SDK�ĵ�ǰ״̬
 * ��������
 * ���أ��μ�������
 */
int gl_state(void);

/*
 * �����������û�����
 * ������
 *      msg�������͵�����
 *      type���μ�gl_send_type_e
 * ���أ��μ�������
 */
int gl_send(void *msg, gl_send_type_e type);


/*
 * ����������igelink���ܣ������ظ����ô˽ӿ�
 *       igelink�ɹ����Զ�ֹͣ
 * ������
 *      aes_key��AES��Կ��16bytes��NULL��ʾ��ʹ��AES����
 *               ���Ȳ���16bytes�Զ���0������16�ض�
 *      chan_dura���ŵ��л��������λ���룩
 *                 0����ʹ��Ĭ�ϼ��100����
 *      timeout����ʱʱ�䣨��λ�룩��������ʱ�����δ�ɹ�����ֹͣigelink
 *               0�������ó�ʱ����igelink��һֱ����ֱ���ɹ�
 * ���أ��μ�������
 */
int gl_igelink_start(const char *aes_key, int chan_dura, int timeout);

/*
 * ��������ȡigelink�ĵ�ǰ״̬
 * ��������
 * ���أ��μ�������
 */
int gl_igelink_state(void);

/*
 * �����������Ⲩ�����������ܣ������ظ����ô˽ӿ�
 *       ���óɹ����Զ�ֹͣ
 * ������
 *      aes_key��AES��Կ��16bytes��NULL��ʾ��ʹ��AES����
 *               ���Ȳ���16bytes�Զ���0������16�ض�
 *      timeout����ʱʱ�䣨��λ�룩��������ʱ�����δ�ɹ�����ֹͣigelink
 *               0�������ó�ʱ����igelink��һֱ����ֱ���ɹ�
 * ���أ��μ�������
 */
int gl_igelink_light_wave_start(const char *aes_key, int timeout);

/*
 * ��������ȡ�Ⲩ���õĵ�ǰ״̬
 * ��������
 * ���أ��μ�������
 */
int gl_igelink_light_wave_state(void);

typedef enum {
    GL_DC_CHRC_VALUE_SET        = 0, /* ��������ֵ */
    GL_DC_CHRC_VALUE_GET        = 1, /* ��ȡ����ֵ*/
} chrc_valu_op_type_t;

typedef void (*gl_dev_ctrl_valu_func)(chrc_valu_op_type_t op, void *value);

typedef struct 
{
    unsigned int chrc_id;             /* ���Ե�id */
    gl_dev_ctrl_valu_func valu_func;  /* ���úͶ�ȡ�������ݵĻص����� */
    void * const chrc_data;           /* ���ԵĲ��� */
} user_dev_chrc_t;

/*
 * ��������ʼ���豸����
 * ������
 *      chrcs���豸���Բ�������
 *      count�����Եĸ���
 * ���أ��μ�������
 */
int gl_dev_ctrl_init(user_dev_chrc_t *chrcs, int count);

/*
 * �����������������ݵ�ֵ
 * ������
 *      char_id���豸����id
 *      value���豸��������ֵ
 * ���أ��μ�������
 */
int gl_dev_ctrl_set_value(unsigned int char_id, void *value);

/*
 * �������ύ�豸�������ݵ�APP
 * ������
 *      ��
 * ���أ��μ�������
 */
int gl_dev_ctrl_commit_all(void);

#endif /* __GL_API_H__ */

