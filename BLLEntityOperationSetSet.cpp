#include"stdafx.h"
#include<cstring>
#include"BLLEntityOperationSetSet.h"

CBLLEntityOperationSetSet::CBLLEntityOperationSetSet()
{
	m_pOperationSet = new CBLLEntityOperationSet[2];
}

CBLLEntityOperationSetSet::~CBLLEntityOperationSetSet()
{
	delete [] m_pOperationSet;
}

CBLLEntityOperationSet* CBLLEntityOperationSetSet::getOperationSet(int iOperationMark)
{
	return &m_pOperationSet[iOperationMark];
}

bool CBLLEntityOperationSetSet::insertingOperationSet(bool check,CBLLEntityOperationSet* pOperationSet)
{
	if(check)
	{
		m_pOperationSet[0].setTimeSliceID (pOperationSet->getTimeSliceID());
		memcpy(m_pOperationSet[0].getRentOperation(),pOperationSet->getRentOperation(),sizeof(CBLLEntityOperation));
		memcpy(m_pOperationSet[0].getReturnOperation(),pOperationSet->getReturnOperation(),sizeof(CBLLEntityOperation));
		return true;
	}
	else
	{
		m_pOperationSet[1].setTimeSliceID(pOperationSet->getTimeSliceID());
		memcpy(m_pOperationSet[1].getRentOperation(),pOperationSet->getRentOperation(),sizeof(CBLLEntityOperation));
		memcpy(m_pOperationSet[1].getReturnOperation(),pOperationSet->getReturnOperation(),sizeof(CBLLEntityOperation));
		return true;
	}
	
}

CBLLEntityOperationSet* CBLLEntityOperationSetSet::getRentOperationSet()
{
	return &m_pOperationSet[0];
}

CBLLEntityOperationSet* CBLLEntityOperationSetSet::getReturnOperationSet()
{
	return &m_pOperationSet[1];
}

bool CBLLEntityOperationSetSet::checkingRentOperation(CBLLEntityOperationSet* pOperationSet)
{
	bool bCheck = false;

	bCheck = pOperationSet->checkingRentOperation(pOperationSet);

	return bCheck;
}

bool CBLLEntityOperationSetSet::isOneTimeSlice()
{
	return (m_pOperationSet[1].getTimeSliceID() == -1);
}