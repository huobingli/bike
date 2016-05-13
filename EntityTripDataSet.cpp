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
//Description of Function����ȡ��ǰ�洢��վ����Ŀ
//Input Parameter		 ����
int & CEntityTripDataSet::gettingSize(void)
{
	return m_iArraySize;
}
//---------------------------------------
//Description of Function���ж�վ�㼯���Ƿ�Ϊ��
//Input Parameter		 ��SS_ISEMPTY->վ�����鼯��
//Return Value			 ��true->վ�㼯��Ϊ�գ�false->վ�㼯�ϲ�Ϊ��
bool CEntityTripDataSet::isEmpty() const//����const���⽫���е�˽�г�Ա������ֵ�ı� ��
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
//Description of Function���ж������Ƿ��Ѿ�����
//Input Parameter		 ����
//Retrun Value			 ��true	->������������false->������δ��
bool CEntityTripDataSet::isEnd(void)
{
	/*�ж�վ�㼯������ģ��*/
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
//Description of Function:��������
CEntityTripData *& CEntityTripDataSet::biggerRecordSet()
{
	CEntityTripData *csStation = new CEntityTripData[ARRAY_LENGTH + m_iEachNumStation];
	CEntityTripData *csTemp = m_CSexample;
	memcpy(csStation, m_CSexample, sizeof(CEntityTripData)*gettingSize());// ����ԭ����
	m_CSexample = csStation;
	m_iArrayLength = ARRAY_LENGTH + m_iEachNumStation;

	delete[]csTemp;
	m_iEachNumStation += 50;
	return m_CSexample;
}
//--------------------------
//Description of Function:����վ������
//Input Parameter		 :��
//Return Value			 :վ�����飨ʵ�ʵĴ洢վ���ڴ��ַ�������ô���
CEntityTripData *& CEntityTripDataSet::linkRecord()
{
	return m_CSexample;
}

