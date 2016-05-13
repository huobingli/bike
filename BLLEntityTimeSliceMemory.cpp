#include"stdafx.h"
#include"BLLEntityTimeSliceMemory.h"

CBLLEntityTimeSliceMemory::CBLLEntityTimeSliceMemory()
{
	m_pStationCount = new CEntityStationCount[700];
	m_iTimeSliceID = -1;
	m_iSurvivalTime = 0;
	m_iArrayLength = 700;
	m_iArraySize = 0;
}

CBLLEntityTimeSliceMemory::CBLLEntityTimeSliceMemory(int iCurrentTimeSliceID)
{
	m_pStationCount = new CEntityStationCount[700];
	m_iTimeSliceID = iCurrentTimeSliceID;
	m_iSurvivalTime = 0;
	m_iArrayLength = 700;
	m_iArraySize = 0;
}

CBLLEntityTimeSliceMemory::~CBLLEntityTimeSliceMemory()
{
	delete [] m_pStationCount;
	m_pStationCount = NULL;
}

int CBLLEntityTimeSliceMemory::getTimeSliceID()
{
	return m_iTimeSliceID;
}

void CBLLEntityTimeSliceMemory::setTimeSliceID(int iTimeSliceID)
{
	m_iTimeSliceID = iTimeSliceID;
}

CEntityStationCount* CBLLEntityTimeSliceMemory::getStationCount()
{
	return m_pStationCount;
}

bool CBLLEntityTimeSliceMemory::checkingRentOperation(CBLLEntityOperation* pRentOperation)
{
	//���ݳ�ʼ����ʱ��Ž����ж�
	if(pRentOperation->getTimeSliceID()==-1)
		return false;
	else
		return true;
}

bool CBLLEntityTimeSliceMemory::checkingReturnOperation(CBLLEntityOperation* pReturntOperation)
{
	//���ݳ�ʼ����ʱ��Ž����ж�
	if(pReturntOperation->getTimeSliceID()==-1)
		return false;
	else
		return true;
}

int CBLLEntityTimeSliceMemory::getSurvivalTime()
{
	return m_iSurvivalTime;
}

bool CBLLEntityTimeSliceMemory::checkStationID(int iStationID)
{
	for(int i=0;i<m_iArraySize;i++)
	{
		if(m_pStationCount[i].getStationID()==iStationID)
		{
			return true;
		}
	}
	return false;
}

CEntityStationCount* CBLLEntityTimeSliceMemory::getStation(int iStationID)
{
	for(int i=0;i<m_iArraySize;i++)
	{
		if(m_pStationCount[i].getStationID()==iStationID)
		{
			return &m_pStationCount[i];
		}
	}
	return NULL;
}

bool CBLLEntityTimeSliceMemory::insertingRentAndReturnOperationSet(CBLLEntityOperationSet* pRentAndReturnOperationSet)
{
	int iOperationStationID;
	/*�������������*/
	CBLLEntityOperation* pRentOperaiton = pRentAndReturnOperationSet->getRentOperation();
	iOperationStationID = pRentOperaiton->getOperatedStationID();
	/*�ж��������Ƿ���ڱ��ΪiOperationStationID��վ��*/
	/*���ھ�ȡ����վ�㲢�������ͳ�Ƶ�վ��ͳ�ƶ�����*/
	if(checkStationID(iOperationStationID))
	{
		CEntityStationCount* pStationCount = getStation(iOperationStationID);
		pStationCount->setStationID(iOperationStationID);
		pStationCount->setRentCount(pRentOperaiton);
		int iSurvivalTime = pRentOperaiton->getCostTime();
		if(iSurvivalTime>m_iSurvivalTime)
		{
			m_iSurvivalTime = iSurvivalTime;
		}
	}
	else
	{
		m_pStationCount[m_iArraySize].setStationID(iOperationStationID);
		m_pStationCount[m_iArraySize].setRentCount(pRentOperaiton);
		int iSurvivalTime = pRentOperaiton->getCostTime();
		if(iSurvivalTime>m_iSurvivalTime)
		{
			m_iSurvivalTime = iSurvivalTime;
		}
		m_iArraySize++;
	}

	/*��������������*/
	CBLLEntityOperation* pReturnOperation = pRentAndReturnOperationSet->getReturnOperation();
	iOperationStationID = pReturnOperation->getOperatedStationID();
	/*�ж��������Ƿ���ڱ��ΪiOperationStationID��վ��*/
	/*���ھ�ȡ����վ�㲢�������ͳ�Ƶ�վ��ͳ�ƶ�����*/
	if(checkStationID(iOperationStationID))
	{
		CEntityStationCount* pStationCount = getStation(iOperationStationID);
		pStationCount->setStationID(iOperationStationID);
		pStationCount->setReturnCount(pReturnOperation);
		int iSurvivalTime = pReturnOperation->getCostTime();
		if(iSurvivalTime>m_iSurvivalTime)
		{
			m_iSurvivalTime = iSurvivalTime;
		}
	}
	else
	{
		m_pStationCount[m_iArraySize].setStationID(iOperationStationID);
		m_pStationCount[m_iArraySize].setReturnCount(pReturnOperation);
		int iSurvivalTime = pReturnOperation->getCostTime();
		if(iSurvivalTime>m_iSurvivalTime)
		{
			m_iSurvivalTime = iSurvivalTime;
		}
		m_iArraySize++;
	}

	return true;
}

bool CBLLEntityTimeSliceMemory::insertingRentOperationSet(CBLLEntityOperationSet* pRentOperationSet)
{
	int iOperationStationID;
	/*�������������*/
	CBLLEntityOperation* pRentOperaiton = pRentOperationSet->getRentOperation();
	iOperationStationID = pRentOperaiton->getOperatedStationID();
	/*�ж��������Ƿ���ڱ��ΪiOperationStationID��վ��*/
	/*���ھ�ȡ����վ�㲢�������ͳ�Ƶ�վ��ͳ�ƶ�����*/
	if(checkStationID(iOperationStationID))
	{
		CEntityStationCount* pStationCount = getStation(iOperationStationID);
		pStationCount->setStationID(iOperationStationID);
		pStationCount->setRentCount(pRentOperaiton);
		int iSurvivalTime = pRentOperaiton->getCostTime();
		if(iSurvivalTime>m_iSurvivalTime)
		{
			m_iSurvivalTime = iSurvivalTime;
		}
	}
	else
	{
		m_pStationCount[m_iArraySize].setStationID(iOperationStationID);
		m_pStationCount[m_iArraySize].setRentCount(pRentOperaiton);
		int iSurvivalTime = pRentOperaiton->getCostTime();
		if(iSurvivalTime>m_iSurvivalTime)
		{
			m_iSurvivalTime = iSurvivalTime;
		}
		m_iArraySize++;
	}	
	return true;
}

bool CBLLEntityTimeSliceMemory::insertingReturnOperationSet(CBLLEntityOperationSet* pReturnOperationSet)
{
	int iOperationStationID;
	/*��������������*/
	CBLLEntityOperation* pReturnOperation = pReturnOperationSet->getReturnOperation();
	iOperationStationID = pReturnOperation->getOperatedStationID();
	/*�ж��������Ƿ���ڱ��ΪiOperationStationID��վ��*/
	/*���ھ�ȡ����վ�㲢�������ͳ�Ƶ�վ��ͳ�ƶ�����*/
	if(checkStationID(iOperationStationID))
	{
		CEntityStationCount* pStationCount = getStation(iOperationStationID);
		pStationCount->setStationID(iOperationStationID);
		pStationCount->setReturnCount(pReturnOperation);
		int iSurvivalTime = pReturnOperation->getCostTime();
		if(iSurvivalTime>m_iSurvivalTime)
		{
			m_iSurvivalTime = iSurvivalTime;
		}
	}
	else
	{
		m_pStationCount[m_iArraySize].setStationID(iOperationStationID);
		m_pStationCount[m_iArraySize].setReturnCount(pReturnOperation);
		int iSurvivalTime = pReturnOperation->getCostTime();
		if(iSurvivalTime>m_iSurvivalTime)
		{
			m_iSurvivalTime = iSurvivalTime;
		}
		m_iArraySize++;
	}

	return true;	
}