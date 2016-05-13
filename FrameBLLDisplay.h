#pragma once
#include"FrameDAL.h"
#include"BLLControllerDisplay.h"
#include"StationInfo.h"

class CFrameBLLDisplay
{
public:
	CFrameBLLDisplay();
	
	~CFrameBLLDisplay();

	/**
	˵������ʾ��ϵ����
	������վ������ʱ��ƬID
	����ֵ����ϵ����
	����ʱ�䣺*/
	int* showData(int &StationNum,int TimeID)
	{
		CBLLControllerDisplay *pBLLControllerDisplay = new CBLLControllerDisplay(m_pFrameDAL);
		return pBLLControllerDisplay->showData(StationNum,TimeID);
		
	}
	/**
	˵������ʾվ����Ϣ
	������վ����Ϣ���飬վ��1��վ��2��ʱ��ƬID
	����ֵ��bool
	����ʱ�䣺*/
	bool showInfo(StationInfo &m_StationInfo,int stationId1,int stationId2,int TimeID)
	{
		CBLLControllerDisplay *pBLLControllerDisplay = new CBLLControllerDisplay(m_pFrameDAL);
		pBLLControllerDisplay->showInfo(m_StationInfo,stationId1,stationId2,TimeID);
		return true;
	}
	/**
	˵������ȡʱ��Ƭ
	������ʱ��Ƭ����
	����ֵ�����鳤��
	����ʱ�䣺*/

	int GetTimeID(int TimeIDSet[])
	{
		int ArraySize;
		CBLLControllerDisplay *pBLLControllerDisplay = new CBLLControllerDisplay(m_pFrameDAL);
		ArraySize = pBLLControllerDisplay->GetTimeID(TimeIDSet);
		return ArraySize;
	}
	/**
	˵�������·ݣ�����
	�������������£���
	����ֵ����
	����ʱ�䣺*/

	void getDate(int day_Num, int &month, int &day)

	{
		int iCount = 0;
		int date[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
		while (iCount<12)
		{
			if (day_Num < date[iCount])
			{
				month = iCount + 1;
				day = day_Num+1;
				break;
			}
			else
			{
				day_Num = day_Num - date[iCount];
				iCount++;
			}
		}

		}
	void getToday(int days_Today, int &hour, int &minute)
	{
		/*****************
		hour = days_Today / 2;
		days_Today = days_Today % 2;
		if (days_Today == 1)
			minute = 30;
		else
			minute = 60;
		**************/
		hour = days_Today / 3;
		minute = days_Today % 3;
		
	}
		
private:
	CFrameDAL *m_pFrameDAL;
};

