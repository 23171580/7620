
#ifndef __GL_FILE_CLOUD_H__
#define __GL_FILE_CLOUD_H__

/*
 * ��ʼ���ļ��ϴ�������ݣ�ϵͳ����ʱ���ã�������һ��
 *
 * ��������
 *
 * ����ֵ��
 * 0���ɹ���
 * -1��ʧ��
 */
int gl_file_cloud_init(void);

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
int gl_file_cloud_upload(const char *file, char encrypt);

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
int gl_file_cloud_upload_buffer(const char *file, char encrypt, const char *buf, int size);

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
int gl_file_cloud_get_upload_percent(char *file_name);

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
int gl_file_cloud_set_token(char *token);

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
int gl_file_cloud_download(const char *dirname, const char *basename, const char *url, const char *md5, char *aes_key);

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
int gl_file_cloud_download_buffer(const char *buf, int size, const char *url, const char *md5, const char *aes_key);

#endif


