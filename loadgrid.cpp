#include "Base.h"


//--------------------------------------------------------------------------
/*
��ʱ���᳤��iTimeAllSpanMs����
�������EachGridSpanMs����
����������MaxNumInAllSpan��
*/
CLoadGrid::CLoadGrid(int iTimeAllSpanMs, int iEachGridSpanMs, int iMaxNumInAllSpan/*=0*/)
{
    m_iTimeAllSpanMs = iTimeAllSpanMs;
    m_iEachGridSpanMs = iEachGridSpanMs;
    m_iMaxNumInAllSpan = iMaxNumInAllSpan;

    m_iNumInAllSpan = 0;
    m_iCurrGrid = 0;

    m_iAllGridCount = (int)(m_iTimeAllSpanMs / (float)m_iEachGridSpanMs + 0.9);
    m_iGridArray = new int[m_iAllGridCount];
    memset(m_iGridArray, 0, m_iAllGridCount * sizeof(int));

    gettimeofday(&m_tLastGridTime, NULL);
}

CLoadGrid::~CLoadGrid()
{
    delete []m_iGridArray;
}

/*
���ݵ�ǰʱ������ڲ�ʱ����
*/
void CLoadGrid::UpdateLoad(timeval *ptCurrTime)
{
    if (m_iTimeAllSpanMs <= 0 || m_iEachGridSpanMs <= 0)
    {
        return;
    }

    timeval tCurrTime;

    if (ptCurrTime)
    {
        memcpy(&tCurrTime, ptCurrTime, sizeof(timeval));
    }
    else
    {
        gettimeofday(&tCurrTime, NULL);
    }

    //���ŵ�ʱ��us
    int iTimeGoUs = (tCurrTime.tv_sec - m_tLastGridTime.tv_sec) * 1000000
                    + tCurrTime.tv_usec - m_tLastGridTime.tv_usec;

    //ʱ���쳣�����ŵ�ʱ�䳬����ʱ���������
    if ((iTimeGoUs < 0) || (iTimeGoUs >= m_iTimeAllSpanMs * 1000))
    {
        //ȫ������
        memset(m_iGridArray, 0, m_iAllGridCount * sizeof(int));
        m_iNumInAllSpan = 0;
        m_iCurrGrid = 0;
        //ȡ��������ʱ�䣬��ֹ���ǽ���˴�
        m_tLastGridTime = tCurrTime;
        return;
    }

    //����һ��ʱ��Ƭ
    int iEachGridSpanUs = m_iEachGridSpanMs * 1000;

    if (iTimeGoUs > iEachGridSpanUs)
    {
        //���ŵ�iGridGoNum��ʱ��Ƭ�Σ���βѭ��
        int iGridGoNum = iTimeGoUs / iEachGridSpanUs;

        for (int i = 0; i < iGridGoNum; i++)
        {
            m_iCurrGrid++;

            if (m_iCurrGrid == m_iAllGridCount)
            {
                m_iCurrGrid = 0;
            }

            m_iNumInAllSpan -= m_iGridArray[m_iCurrGrid];
            m_iGridArray[m_iCurrGrid] = 0;
        }

        //��������¼��ʱ��
        int iTimeGoGrid = iGridGoNum * iEachGridSpanUs;
        int iSec = (iTimeGoGrid / 1000000);
        int iuSec = (iTimeGoGrid % 1000000);

        m_tLastGridTime.tv_sec += iSec;
        m_tLastGridTime.tv_usec += iuSec;

        if (m_tLastGridTime.tv_usec > 1000000)
        {
            m_tLastGridTime.tv_usec -= 1000000;
            m_tLastGridTime.tv_sec++;
        }
    }
    //δ����һ��ʱ��Ƭ������Ҫ����
    else
    {
        ;
    }
}

int CLoadGrid::CheckLoad(timeval tCurrTime, bool bTest)
{
    if (m_iTimeAllSpanMs <= 0 || m_iEachGridSpanMs <= 0 || m_iMaxNumInAllSpan <= 0)
    {
        return LR_NORMAL;
    }

    //���ݵ�ǰʱ�����ʱ����
    UpdateLoad(&tCurrTime);

    if (m_iNumInAllSpan < m_iMaxNumInAllSpan)
    {
        if (!bTest)
        {
            //�ۼӱ���
            m_iNumInAllSpan++;
            m_iGridArray[m_iCurrGrid]++;
        }

        return LR_NORMAL;
    }

    //�����ٽ�
    return LR_FULL;
}

/*
��ȡ��ǰʱ�������ݣ���ȡ֮ǰҪ���ݵ�ǰʱ����£�����
�õ��������ʱ�̵����
*/
void CLoadGrid::FetchLoad(int &iTimeAllSpanMs, int &iReqNum)
{
    UpdateLoad();
    iTimeAllSpanMs = m_iTimeAllSpanMs;
    iReqNum = m_iNumInAllSpan;
}
//---------------------------------------------------------------
