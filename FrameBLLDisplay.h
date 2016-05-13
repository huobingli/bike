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
	说明：显示关系数组
	参数：站点数，时间片ID
	返回值：关系数组
	更新时间：*/
	int* showData(int &StationNum,int TimeID)
	{
		CBLLControllerDisplay *pBLLControllerDisplay = new CBLLControllerDisplay(m_pFrameDAL);
		return pBLLControllerDisplay->showData(StationNum,TimeID);
		
	}
	/**
	说明：显示站点信息
	参数：站点信息数组，站点1，站点2，时间片ID
	返回值：bool
	更新时间：*/
	bool showInfo(StationInfo &m_StationInfo,int stationId1,int stationId2,int TimeID)
	{
		CBLLControllerDisplay *pBLLControllerDisplay = new CBLLControllerDisplay(m_pFrameDAL);
		pBLLControllerDisplay->showInfo(m_StationInfo,stationId1,stationId2,TimeID);
		return true;
	}
	/**
	说明：获取时间片
	参数：时间片数组
	返回值：数组长度
	更新时间：*/

	int GetTimeID(int TimeIDSet[])
	{
		int ArraySize;
		CBLLControllerDisplay *pBLLControllerDisplay = new CBLLControllerDisplay(m_pFrameDAL);
		ArraySize = pBLLControllerDisplay->GetTimeID(TimeIDSet);
		return ArraySize;
	}
	/**
	说明：求月份，日期
	参数：天数，月，日
	返回值：无
	更新时间：*/

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

