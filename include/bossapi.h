/*
* �ļ�: bossapi.h
* ����: ������bossapi V4����־�ӿ�
* ����: taozeng
* �汾: 1.0
* �޸���ʷ:
*       1.0 2012-07-24����
*/

#ifndef WEBDEV_BOSS_API_V4_20120723_H
#define WEBDEV_BOSS_API_V4_20120723_H

#ifdef _WIN32
#define boss_vafun	 __cdecl
#else
#define boss_vafun
#endif


#ifdef __cplusplus
extern "C" {
#endif

#define LOG_DEBUG 1
#define LOG_INFO 2 
#define LOG_WARN 3 
#define LOG_ERROR 4 
#define LOG_FATAL 5

/**********access log api****************************/
#define SEND_LOG_ACCESS(uin, module, oper, retcode, iflow, msginfo) do \
{ \
    sendAccessLog(uin, module, oper, retcode, iflow, msginfo, __FILE__, __LINE__, __FUNCTION__);\
} while (0);

/**********access log api****************************/
/**********error log api****************************/
// level: LOG_DEBUG, LOG_INFO, LOG_WARN, LOG_ERROR, LOG_FATAL
#define SEND_LOG_ERROR(module, uin, cmd, level, errcode, msg) do \
{ \
        sendError(module, uin, cmd, level, errcode, msg, __FILE__, __LINE__, __FUNCTION__);\
} while (0);

int sendError(const char* module, long long uin, const char* cmd, 
              short level, int errcode, const char* msg, 
              const char* srcfile,  int srcline, const char* func);
/**********error log api****************************/


int sendAccessLog(long long uin, const char* module, const char* oper, 
		int retcode, long long iflow, const char* msg, 
        const char* srcfile,  int srcline, const char* func);


/********************************************************************
** ������: loginit
** ����: 
**       ��ʼ�����Ͷ˿ڣ����̰߳�ȫ
** ����:
**      _udp_port,  �˿ںţ����Boss Agent�ļ����˿ں�һ�£�Ϊ6578
** ����ֵ:
**      0		    �ɹ�
**	   ���� 	    ʧ��
*********************************************************************/
int loginit(const unsigned short _udp_port);

/********************************************************************
** ������: logprintf
** ����: 
**       ��һ����־��BOSS�����̰߳�ȫ
** ����:
**      _boss_id,   ��־ID
**	   _format,     ��ʽ����־����
**      ...         ��������
** ����ֵ:
**      0		�ɹ�
**      -1    �����ڴ�ʧ��
**      -2    _boss_id�Ƿ�
**      -3    ����socket fdʧ��
**      -4    vsnprintf����ʧ�ܻ������ݳ��ȳ����Ϸ���Χ
**      -5    ����UDPʧ��
**	   ���� 	δ֪����
*********************************************************************/
int logprintf(const unsigned int _boss_id, const char* _format, ...);

/********************************************************************
** ������: sloginit
** ����: 
**       ��ʼ�����Ͷ˿�,�̰߳�ȫ
** ����:
**      _udp_port,  �˿ںţ����Boss Agent�ļ����˿ں�һ�£�Ϊ6578
** ����ֵ:
**      0		    �ɹ�
**	   ���� 	    ʧ��
*********************************************************************/
int sloginit(const unsigned short _udp_port);

/********************************************************************
** ������: slogprintf
** ����: 
**       ��һ����־��BOSS���̰߳�ȫ
** ����:
**      _boss_id,   ��־ID
**	   _format,     ��ʽ����־����
**      ...         ��������
** ����ֵ:
**      0		�ɹ�
**      -1    �����ڴ�ʧ��
**      -2    _boss_id�Ƿ�
**      -3    ����socket fdʧ��
**      -4    vsnprintf����ʧ�ܻ������ݳ��ȳ����Ϸ���Χ
**      -5    ����UDPʧ��
**	   ���� 	δ֪����
********************************************************************/
int slogprintf(const unsigned int _boss_id, const char* _format, ...);

/********************************************************************
** ������: convert_data
** ����: 
**       ת���ַ����ݣ�
        ����ַ������п��ܺ���NULL \r \n ���� б�� ���ŵ�
        �������ȵ��ñ�����ת���ٵ���(s)logprintf����
** ����:
**      _desc           �洢ת��������ݵĵ�ַ
**      _desc_capacity  �洢ת�������ݵ�����
**      _src            ��Ҫת������ݵ�ַ
**      _src_len        ��Ҫת������ݳ���
** ����ֵ:
**      0		    �ɹ�
**	   ���� 	    ʧ��
*********************************************************************/
int log_convert_data(char *_desc, const unsigned int _desc_capacity, 
		const char *_src, const unsigned int _src_len);

#ifdef __cplusplus
}
#endif
#endif

