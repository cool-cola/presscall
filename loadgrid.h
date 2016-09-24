#ifndef __LOADGRID_H__
#define __LOADGRID_H__

#include <stdio.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <errno.h>
#include <sys/time.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/file.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <vector>
#include <string>


using namespace std;

/*
    ���ؼ����,CLoadGrid(100000,50,99999) ��
    ��ʱ��������50msΪÿ��ǰ���Ŀ�ȣ���100s��
    �ܳ�ʱ�������ư���9999��
*/
class CLoadGrid
{
public:
    enum LoadRet
    {
        LR_ERROR = -1,
        LR_NORMAL = 0,
        LR_FULL = 1
    };
    CLoadGrid(int iTimeAllSpan, int iEachGridSpan, int iMaxNumInAllSpan = 0);
    ~CLoadGrid();

    //�û�ÿ�ε��ã�����Ƿ�ﵽˮλ����
    //return enum LoadRet{};
    int CheckLoad(timeval tCurrTime, bool bTest = false);

    //��ȡ��ǰˮλ��Ϣ
    void FetchLoad(int &iTimeAllSpanMs, int &iReqNum);

private:
    void UpdateLoad(timeval *ptCurrTime = NULL);

    int m_iTimeAllSpanMs;
    int m_iEachGridSpanMs;
    int m_iMaxNumInAllSpan;

    int m_iAllGridCount;            //��Ҫ���ܸ�����
    int *m_iGridArray;          //ʱ����
    timeval m_tLastGridTime;
    int m_iNumInAllSpan;

    //��ǰλ
    int m_iCurrGrid;
};
