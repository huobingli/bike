#include"stdafx.h"
#include"BLLEntityOperation.h"

CBLLEntityOperation::CBLLEntityOperation(int iTimeSliceID,bool bOpertedType)
{
	m_iTimeSliceID = iTimeSliceID;
	m_bOperatedType = bOpertedType;
	m_iOperatedStationID = -1;
	m_iRelatedStationID = -1;
	m_iCostTime = 0;
}

CBLLEntityOperation::CBLLEntityOperation()
{	
	m_iTimeSliceID = -1;
}

CBLLEntityOperation::~CBLLEntityOperation()
{
}

void CBLLEntityOperation::setTimeSliceID(int iTimeSliceID)
{
	m_iTimeSliceID = iTimeSliceID;
}

void CBLLEntityOperation::setOperateType(bool bOperatedType)
{
	m_bOperatedType = bOperatedType;
}

void CBLLEntityOperation::setOperateStationID(int iOperatedStationID)
{
	m_iOperatedStationID = iOperatedStationID;
}

void CBLLEntityOperation::setRelatedStationID(int iRelatedStationID)
{
	m_iRelatedStationID = iRelatedStationID;
}

void CBLLEntityOperation::setCostTime(int iCostTime)
{
	m_iCostTime = iCostTime;
}

void CBLLEntityOperation::updatingRentOperation(CEntityTripData* pTripData)
{
	setOperateStationID(pTripData->getStartStationID());
	setRelatedStationID(pTripData->getStopStationID());
	setCostTime(pTripData->getCostTime());
}

void CBLLEntityOperation::updatingReturnOperation(CEntityTripData* pTripData)
{
	setOperateStationID(pTripData->getStopStationID());
	setRelatedStationID(pTripData->getStartStationID());
	setCostTime(pTripData->getCostTime());
}

bool CBLLEntityOperation::updatingOperationByOperation(CBLLEntityOperation* pOperation)
{
	m_iTimeSliceID = pOperation->getTimeSliceID();
	m_bOperatedType = pOperation->getOperatedType();
	m_iOperatedStationID = pOperation->getOperatedStationID();
	m_iRelatedStationID = pOperation->getRelatedStationID();
	m_iCostTime = pOperation->getCostTime();

	return true;
}
int CBLLEntityOperation::getTimeSliceID()
{
	return m_iTimeSliceID;
}

int CBLLEntityOperation::getOperatedStationID()
{
	return m_iOperatedStationID;
}

int CBLLEntityOperation::getRelatedStationID()
{
	return m_iRelatedStationID;
}

int CBLLEntityOperation::getCostTime()
{
	return m_iCostTime;
}

bool CBLLEntityOperation::getOperatedType()
{
	return m_bOperatedType;
}