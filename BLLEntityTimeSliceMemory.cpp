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
	//根据初始化的时间号进行判断
	if(pRentOperation->getTimeSliceID()==-1)
		return false;
	else
		return true;
}

bool CBLLEntityTimeSliceMemory::checkingReturnOperation(CBLLEntityOperation* pReturntOperation)
{
	//根据初始化的时间号进行判断
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
	/*创建借操作对象*/
	CBLLEntityOperation* pRentOperaiton = pRentAndReturnOperationSet->getRentOperation();
	iOperationStationID = pRentOperaiton->getOperatedStationID();
	/*判断数组中是否存在编号为iOperationStationID的站点*/
	/*存在就取出该站点并将借操作统计到站点统计对象中*/
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

	/*创建还操作对象*/
	CBLLEntityOperation* pReturnOperation = pRentAndReturnOperationSet->getReturnOperation();
	iOperationStationID = pReturnOperation->getOperatedStationID();
	/*判断数组中是否存在编号为iOperationStationID的站点*/
	/*存在就取出该站点并将借操作统计到站点统计对象中*/
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
	/*创建借操作对象*/
	CBLLEntityOperation* pRentOperaiton = pRentOperationSet->getRentOperation();
	iOperationStationID = pRentOperaiton->getOperatedStationID();
	/*判断数组中是否存在编号为iOperationStationID的站点*/
	/*存在就取出该站点并将借操作统计到站点统计对象中*/
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
	/*创建还操作对象*/
	CBLLEntityOperation* pReturnOperation = pReturnOperationSet->getReturnOperation();
	iOperationStationID = pReturnOperation->getOperatedStationID();
	/*判断数组中是否存在编号为iOperationStationID的站点*/
	/*存在就取出该站点并将借操作统计到站点统计对象中*/
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