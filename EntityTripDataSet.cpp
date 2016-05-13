#include"stdafx.h"
#include "EntityTripDataSet.h"
#include <stdlib.h>
#include <string.h>

CEntityTripDataSet::CEntityTripDataSet(void)
{
	m_CSexample = new CEntityTripData[ARRAY_LENGTH];
	m_iArrayLength = ARRAY_LENGTH;
	m_iArraySize = 0;
	m_iPos = 0;
	m_iEachNumStation = 50;
}

CEntityTripDataSet::~CEntityTripDataSet(void)
{
	delete[]m_CSexample;
	m_CSexample = NULL;
}
//---------------------------------------
//Description of Function：获取当前存储的站点数目
//Input Parameter		 ：无
int & CEntityTripDataSet::gettingSize(void)
{
	return m_iArraySize;
}
//---------------------------------------
//Description of Function：判断站点集合是否为空
//Input Parameter		 ：SS_ISEMPTY->站点数组集合
//Return Value			 ：true->站点集合为空，false->站点集合不为空
bool CEntityTripDataSet::isEmpty() const//加上const避免将类中的私有成员变量的值改变 。
{
	if (m_iPos == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

CEntityTripData* CEntityTripDataSet::getFirst()
{
	return &m_CSexample[0];
}

CEntityTripData* CEntityTripDataSet::getNext()
{
	if (m_iPos == m_iArraySize)
	{
		return &m_CSexample[m_iArraySize];
	}
	else
	{
		m_iPos++;
		return &m_CSexample[m_iPos];
	}
}
//----------------------------------------------
//Description of Function：判断数组是否已经存满
//Input Parameter		 ：无
//Retrun Value			 ：true	->该数组已满，false->该数组未满
bool CEntityTripDataSet::isEnd(void)
{
	/*判断站点集合已满模块*/
	if (m_iArraySize == m_iArrayLength)
	{
		return true;
	}
	else
	{
		return false;
	}
}
//--------------------------------
//Description of Function:扩充数组
CEntityTripData *& CEntityTripDataSet::biggerRecordSet()
{
	CEntityTripData *csStation = new CEntityTripData[ARRAY_LENGTH + m_iEachNumStation];
	CEntityTripData *csTemp = m_CSexample;
	memcpy(csStation, m_CSexample, sizeof(CEntityTripData)*gettingSize());// 拷贝原数据
	m_CSexample = csStation;
	m_iArrayLength = ARRAY_LENGTH + m_iEachNumStation;

	delete[]csTemp;
	m_iEachNumStation += 50;
	return m_CSexample;
}
//--------------------------
//Description of Function:返回站点数组
//Input Parameter		 :无
//Return Value			 :站点数组（实际的存储站点内存地址），引用传参
CEntityTripData *& CEntityTripDataSet::linkRecord()
{
	return m_CSexample;
}

