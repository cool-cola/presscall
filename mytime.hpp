#ifndef _MYTIME_H_
#define _MYTIME_H_
#include <stdint.h>

//extern volatile uint32_t gnow;		//��ǰʱ��
//extern char gnowstr[30];	//��ǰʱ����ַ���

/*
 * ��ʼ��ʱ����ػ���
 */
//extern int init_time();
/*
 * ȡ��ǰʱ�䣨gnow���Զ����£�
 * return		��ǰʱ��
 */
//extern uint32_t nowtime();
/*
 * ȡ��ǰʱ����ַ�����ʾ
 * timestr		�洢������ָ��
 */
extern const char* nowtimestr(char* timestr);
/*
 * ȡĳ���ض�ʱ����ַ�����ʾ
 * timestr		�洢������ָ��
 */
extern const char* gettimestr(char* timestr, uint32_t tm);
/*
 * ȡ��ǰʱ���ʾ��tick��
 * return		tick��
 */
//extern uint64_t gettick();
/*
 * ת������Ϊtick��
 * sec			��ת��������
 * return		tick��
 */ 
//extern uint64_t maketick(double sec);
#endif

