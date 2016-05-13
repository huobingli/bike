#include"stdafx.h"
#include"BLLEntityOperationSet.h"

CBLLEntityOperationSet::CBLLEntityOperationSet()
{
	m_iTimeSliceID = -1;
	m_pRentOperation = new CBLLEntityOperation(m_iTimeSliceID,true);   
	m_pReturnOperation = new CBLLEntityOperation(m_iTimeSliceID,false);
}

CBLLEntityOperationSet::CBLLEntityOperationSet(int iTimeSliceID,CBLLEntityOperation* pRentOperation,CBLLEntityOperation* pReturnOperation)
{
	m_iTimeSliceID = iTimeSliceID;
	m_pRentOperation = pRentOperation;
	m_pReturnOperation = pReturnOperation;
}

CBLLEntityOperationSet::CBLLEntityOperationSet(int iTimeSliceID,CBLLEntityOperation* pOperaiotn,bool bCheck)
{
	m_iTimeSliceID = iTimeSliceID;
	if(bCheck)
	{
		m_pRentOperation = pOperaiotn;
		m_pReturnOperation = new CBLLEntityOperation(-1,false);
	}
	else
	{
		m_pRentOperation = new CBLLEntityOperation(-1,true);
		m_pReturnOperation = pOperaiotn;
	}
}

CBLLEntityOperationSet::~CBLLEntityOperationSet()
{
	delete m_pRentOperation;
	m_pRentOperation = NULL;
	delete m_pReturnOperation;
	m_pReturnOperation = NULL;
}

int CBLLEntityOperationSet ::getTimeSliceID()
{
	return m_iTimeSliceID;
}


CBLLEntityOperation* CBLLEntityOperationSet::getRentOperation()
{
	return m_pRentOperation;
}

CBLLEntityOperation* CBLLEntityOperationSet::getReturnOperation()
{
	return m_pReturnOperation;
}

bool CBLLEntityOperationSet::checkingRentOperation(CBLLEntityOperationSet* pOperationSet)
{
	CBLLEntityOperation* pOperation = new CBLLEntityOperation();
	pOperation = pOperationSet->getRentOperation();
	if(pOperation->getTimeSliceID()==-1)
	{
		//delete pOperation;
		return false;
	}
	else
	{
		//delete pOperation;
		return true;
	}
}

