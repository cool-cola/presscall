#ifndef _PRESSCALL_H_
#define _PRESSCALL_H_
/*
 * Copyright (c) 2005 by zhongchaoyu
 * Copyright 2005, 2005 by zhongchaoyu.  All rights reserved.
 */

#define CFGFILE "./conf.cfg"

//���н��Ԫ��
struct  TUsrResult
{
	//�ܺ���
	long iAllReqNum;
	long iOkResponseNum;
	long iNoResponseNum;
	long iBadResponseNum;

    unsigned long long ullRspTimeUs;
    unsigned long long ullAllRspTimeUs;
    unsigned long long ullMaxRspTimeUs;

    long m_iTimeL1Num;
	long m_iTimeL2Num;
	long m_iTimeL3Num;
};

struct  TResult
{
	long iAllReqNum;
	long iOkResponseNum;
	long iNoResponseNum;
	long iBadResponseNum;
    
	unsigned long long ullRspTimeUs;
	unsigned long long ullMaxRspTimeUs;

	long m_iTimeL1Num;
	long m_iTimeL2Num;
	long m_iTimeL3Num;
};

#endif

