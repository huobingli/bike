#pragma once
#include<iostream>
#include"stdlib.h"
#include "string.h"
#include<sstream>
using namespace std;

class CBLLModelEntityTimeSliceCountArray
{
public:
	CBLLModelEntityTimeSliceCountArray(void)
	{
		m_iMaxTime = 0;
		m_iMinTime = 0;
		m_iOperateTimes = 0;
		m_iStartStation = 0;
		m_iFinishStation = 0;
	}
	~CBLLModelEntityTimeSliceCountArray(void)
	{

	}

	//get、set方法
	void setMaxTime(int iMaxTime)
	{
		m_iMaxTime = iMaxTime;
	}

	int getMaxTime()
	{
		return m_iMaxTime;
	}

	void setMinTime(int iMinTime)
	{
		m_iMinTime = iMinTime;
	}

	int getMinTime()
	{
		return m_iMinTime;
	}

	void setOperateTimes(int iOperateTimes)
	{
		m_iOperateTimes = iOperateTimes;
	}

	int getOperateTimes()
	{
		return m_iOperateTimes;
	}

	void setStartStation(int iStartStation)
	{
		m_iStartStation = iStartStation;
	}

	int getStartStation()
	{
		return m_iStartStation;
	}

	int getFinishStation()
	{
		return m_iStartStation;
	}

	void setFinishStation(int iFinishStation)
	{
		m_iFinishStation = iFinishStation;
	}

	string changeToStringstream()
	{
		stringstream strstreamCount;
		char* cLeft = "(";
		char* cBlank = ",";
		char* cRight = ")";
		strstreamCount<<m_iMaxTime;
		strstreamCount<<cBlank;
		strstreamCount<<m_iMinTime;
		strstreamCount<<cBlank;
		strstreamCount<<m_iOperateTimes;
		strstreamCount<<cRight;

		//将stringstream转换成string
		string strCount(strstreamCount.str());
		return strCount;	
	}
private:
	int m_iMaxTime;
	int m_iMinTime;
	int m_iOperateTimes;

	int m_iStartStation;
	int m_iFinishStation;
};

