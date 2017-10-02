#include <unistd.h>
#include <sys/stat.h>
#include "curl/curl.h"
#include "rs.h"
#include "resumable_io.h"
#include "gl_api.h"
#include "gl_file_cloud.h"

#ifndef blockBits
#define blockBits 22
#endif
#define qiniu_block_size  (1<< blockBits)


typedef struct {
    char *file;
    char uploading;
    char encrypt;
    char *token;
    char *hash;
    char *key;
    char *url;
    int   file_size;
    int   finish_size;
} gl_file_upload_param_t;

typedef struct {
    char *file;
    char downloading;
    char *url;
    char *md5;
    FILE *file_stream;
    size_t finish_size;
} gl_file_download_param_t;


static char file_inited = 0;
static gl_file_upload_param_t up_param;
static gl_file_download_param_t down_param;
static Qiniu_Client client;

static size_t curl_fwrite_cb(void *buffer, size_t size, size_t nmemb, void *stream)
{
  if(!down_param.file_stream) {
    down_param.file_stream = fopen(down_param.file, "wb");//���ļ�����д��
    if(!down_param.file_stream)
      return -1;
  }
  down_param.finish_size += size*nmemb;
  printf("my_fwrite(), size:%d, down_load_size:%d\n", size*nmemb, down_param.finish_size);
  
  return fwrite(buffer, size, nmemb, down_param.file_stream);
}

static void *gl_download_file(void *arg)
{
    CURL *curl;
    CURLcode res;

    printf("gl_download_file() ...\n");
    
    curl = curl_easy_init();  //��ʼ��һ��curlָ��
    if(curl) { //curl������ڵ������ִ�еĲ���

        //����Զ�˵�ַ
        curl_easy_setopt(curl, CURLOPT_URL,down_param.url);
  
        //ִ��д���ļ�������
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, curl_fwrite_cb);//�������ݱ�д�룬�ص����������ã�
        //curl_easy_setopt(curl, CURLOPT_WRITEDATA, &ftpfile); //���ýṹ���ָ�봫�ݸ��ص�����

        //����ʱ��㱨���е���Ϣ�������STDERR��ָ����CURLOPT_STDERR��
        curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
        curl_easy_setopt(curl, CURLOPT_USERPWD, "SUREN:SUREN");

        //д���ļ�
        res = curl_easy_perform(curl);
 
        //�ͷ�curl����
        curl_easy_cleanup(curl);

        if(res != CURLE_OK)
        {
            printf("gl_download_file() download error.\n");
        }
     }

    if(down_param.file_stream)
    {
        //�ر��ļ���
        fclose(down_param.file_stream);
    }

  
    //�ͷ�ȫ��curl����
    curl_global_cleanup();

    if (down_param.url)
        free(down_param.url);
    if (down_param.md5)
        free(down_param.md5);
    if (down_param.file)
        free(down_param.file);

    memset(&down_param, 0, sizeof(down_param));

    return 0;
 }


static int gl_file_get_file_size(const char *file)
{
	unsigned long filesize = -1;      
    struct stat statbuff;  
    if(stat(file, &statbuff) < 0){  
        return filesize;  
    }else{  
        filesize = statbuff.st_size;  
    }
    return filesize; 
}

static char* gl_file_get_file_name(char *full_path)
{
    char *file_name = NULL;
    
    file_name = strrchr(full_path, '/');
    if (0 == file_name)
    {
        return full_path;
    }

    return (char*)(file_name+1);
}


void qiniu_debug(Qiniu_Client* client, Qiniu_Error err)
{
    printf("error code: %d, message: %s\n", err.code, err.message);
    printf("respose header:\n%s", Qiniu_Buffer_CStr(&client->respHeader));
    printf("respose body:\n%s", Qiniu_Buffer_CStr(&client->b));
}

static int qiniu_upload_progress_cb(void* self, int blkIdx, int blkSize, Qiniu_Rio_BlkputRet* ret) 
{
    
    up_param.finish_size = blkIdx*(qiniu_block_size)+ret->offset;
    
    return QINIU_RIO_NOTIFY_OK; 
}

static int qiniu_upload_err_cb(void* self, int blkIdx, int blkSize, Qiniu_Error err)
{
    printf("qiniu_upload_err_cb(), code:%d, msg:%s\n", err.code, err.message);
    return QINIU_RIO_NOTIFY_OK;
}


static int qiniu_upload_file(void)
{
    Qiniu_Error err;
    Qiniu_Io_PutRet ret;
    Qiniu_Rio_PutExtra extra;
    gl_file_info_t file_info;
    Qiniu_Zero(extra);

    extra.notify = qiniu_upload_progress_cb;
    extra.notifyErr = qiniu_upload_err_cb;

    memset(&file_info, 0x00, sizeof(file_info));
    file_info.check_key = 0;
    file_info.check_key_len = 0;
    file_info.check_type = GL_FILE_CHECK_MD5;
    file_info.encrypt_key = 0;
    file_info.encrypt_key_len = 0;
    file_info.encrypt_type = GL_FILE_ENCRYPT_AES;
    file_info.file_name = gl_file_get_file_name(up_param.file);
    file_info.file_size = up_param.file_size;
    file_info.file_url = 0;
    file_info.user_id = 0; /* -1,���͸����а��豸��APP, ���ڵ���0�����͸��ض����û�*/
    gl_send((void *)&file_info, GL_SEND_START_FILE_INFO);
    

    err = Qiniu_Rio_PutFile(&client, &ret, up_param.token, NULL, up_param.file, &extra);

    if (err.code != 200) {
        qiniu_debug(&client, err);
        return -1;
    }
    
    printf("qiniu_upload_file(), ret.key:%s, ret.hash:%s\n", ret.key, ret.hash);
    up_param.key = strdup(ret.key);

    memset(&file_info, 0x00, sizeof(file_info));
    file_info.check_key = "123456789abcdef";
    file_info.check_key_len = 16;
    file_info.check_type = GL_FILE_CHECK_MD5;
    file_info.encrypt_key = "123456789abcdef";
    file_info.encrypt_key_len = 16;
    file_info.encrypt_type = GL_FILE_ENCRYPT_AES;
    file_info.file_name = gl_file_get_file_name(up_param.file);
    file_info.file_size = up_param.file_size;
    file_info.file_url = 0; /* �ɸ����ƶ�����url */
    file_info.file_key = up_param.key;
    file_info.user_id = 0; /* -1,���͸����а��豸��APP, ���ڵ���0�����͸��ض����û�*/
    gl_send((void *)&file_info, GL_SEND_FIN_FILE_INFO);

    return 0;
}



static void *gl_qiniu_upload_file(void *arg)
{
    while (up_param.token == 0)
    {
        // if need, add counter to exit.
        printf("gl_qiniu_upload_file(), waiting token\n");
        sleep(1);
    };
    
    while (qiniu_upload_file() != 0) {
        sleep(2);
    }

    if (up_param.file)
        free(up_param.file);
    if (up_param.token)
        free(up_param.token);
    if (up_param.hash)
        free(up_param.hash);
    if (up_param.key)
        free(up_param.key);
    if (up_param.url)
        free(up_param.url);

    memset(&up_param, 0, sizeof(up_param));
    
    return NULL;
}


/*
 * ��ʼ���ļ��ϴ�������ݣ�ϵͳ����ʱ���ã�������һ��
 *
 * ��������
 *
 * ����ֵ��
 * 0���ɹ���
 * -1��ʧ��
 */
int gl_file_cloud_init(void)
{
    if (file_inited)
        return 0;

    Qiniu_Global_Init(-1);
    Qiniu_Client_InitNoAuth(&client, 1024);

    memset(&up_param, 0, sizeof(up_param));
    memset(&down_param, 0, sizeof(down_param));

    file_inited = 1;

    return 0;
}


/*
 * �ϴ�ָ���ļ����õ��û�����ֱ���ļ��ϴ���ɲ�����Ϣ���͵�app��
 *
 * ������
 * @file: ���ϴ��ļ�������·����
 * @encrypt: �Ƿ��ļ����ܺ��ϴ������ܺķ�cpu��Դ�����������������á�
 *
 * ����ֵ��
 * 0���ɹ���
 * 1: ����tokenʧ��
 * -1�����ļ������ϴ���
 */
int gl_file_cloud_upload(const char *file, char encrypt)
{
    pthread_t thread;
 
    if (up_param.uploading)
        return -1;
    up_param.uploading = 1;

    up_param.file_size = gl_file_get_file_size(file);
    up_param.file = strdup(file);
    up_param.token = 0;

    if (GL_OK != gl_send(0, GL_SEND_REQUEST_TOKEN))
    {
        printf("gl_file_cloud_upload() send get tokent failure\n");
        if (up_param.file != 0)
        {
            free(up_param.file);
        }
        memset(&up_param, 0, sizeof(up_param));
        return 1;
    }

    pthread_create(&thread, NULL, gl_qiniu_upload_file, NULL);

    return 0;
}

/*
 * �ϴ�ָ��buffer���õ��û�����ֱ��buffer�ϴ���ɲ�����Ϣ���͵�app��
 *
 * ������
 * @file: �����Ŀ���ļ��������ڱ�ʶ���ϴ���buffer��
 * @buf: ���ϴ�bufferָ�롣
 * @size: buffer��С��
 * @encrypt: �Ƿ�buffer���ܺ��ϴ������ܺķ�cpu��Դ�����������������á�
 *
 * ����ֵ��
 * 0���ɹ���
 * -1������
 */
int gl_file_cloud_upload_buffer(const char *file, char encrypt, const char *buf, int size)
{
    if (!buf || size <= 0)
        return -1;

    return 0;
}

/*
 * ��ȡ��ǰ�ļ��ϴ��Ľ��ȡ�
 *
 * ������
 * @file_name, �ļ���
 *
 * ����ֵ��
 * 0-100���ļ��ϴ����ȡ�
 * -1��û���ļ����ϴ���
 */
int gl_file_cloud_get_upload_percent(char *file_name)
{
    if (!up_param.uploading || up_param.file_size == 0)
    {
        return -1;
    }

    if (strncmp(file_name, gl_file_get_file_name(up_param.file), strlen(file_name)))
    {
        printf("the file name error, %s\n", file_name);
        return -1;
    }

    return (up_param.finish_size*100)/up_param.file_size;
}

/*
 * �����ϴ���tokenֵ
 *
 * ������
 * @token��tokenֵ
 *
 * ����ֵ��
 * 0 �����óɹ�
 * -1������ʧ�ܣ�tokenΪ��
 */
int gl_file_cloud_set_token(char *token)
{
    if (0 == token)
    {
        printf("gl_file_cloud_set_token(), token is null\n");
        return -1;
    }

    up_param.token = strdup(token);

    return 0;
}

/*
 * �����ļ���ָ��·�����õ��û�����ֱ���ļ�������ɡ�
 *
 * ������
 * @dirname: �ļ��ı���·������ΪĿ¼·����
 * @basename: �ļ�����
 * @url: ���ص�ַ��
 * @md5: �ļ���md5ֵ��
 * @aes_key: �ļ��Ľ�����Կ�����ϴ�ʱδ���ܣ�����ʱ���ա�
 *
 * ����ֵ��
 * 0���ɹ���
 * -1������
 */
int gl_file_cloud_download(const char *dirname, const char *basename, const char *url, const char *md5, char *aes_key)
{
    pthread_t thread;
    int full_path_len;

    if (down_param.downloading || !dirname || !basename || !url)
    {
        printf("gl_file_cloud_download() param is null\n");
        printf("down_param.downloading:%d\n", down_param.downloading);
        printf("dirname:%s\n", dirname);
        printf("basename:%s\n", basename);
        printf("url:%s\n", url);
        return -1;
    }
        
    down_param.downloading = 1;

    down_param.url = strdup(url);
    if (md5 != 0)
    {
        down_param.md5 = strdup(md5);
    }
    full_path_len = strlen(dirname) + strlen(basename) + 3;
    down_param.file = malloc(full_path_len);
    memset(down_param.file, 0, full_path_len);
    snprintf(down_param.file, full_path_len-1, "%s/%s", dirname, basename);
    printf("gl_file_cloud_download(), file:%s\n", down_param.file);
    pthread_create(&thread, NULL, gl_download_file, NULL);
    
    return 0;
}

/*
 * �����ļ���ָ��buffer���õ��û�����ֱ���ļ�������ɡ�
 *
 * ������
 * @buf: �ļ������ص�Ŀ��bufferָ�롣
 * @size: buffer�Ĵ�С��
 * @url: ���ص�ַ��
 * @md5: �ļ���md5ֵ��
 * @aes_key: �ļ��Ľ�����Կ�����ϴ�ʱδ���ܣ�����ʱ���ա�
 *
 * ����ֵ��
 * 0���ɹ���
 * -1������
 */
int gl_file_cloud_download_buffer(const char *buf, int size, const char *url, const char *md5, const char *aes_key)
{
    if (!buf || size <= 0 || !url || !md5)
        return -1;

    return 0;
}





