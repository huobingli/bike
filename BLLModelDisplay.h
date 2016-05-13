#pragma once
#include"EntityTimeSliceCountSet.h"
#include"ListWriteRelationSet.h"
class CBLLModelDisplay
{
public:
	CBLLModelDisplay();
	~CBLLModelDisplay();

	bool startDisplay(CListWriteRelationNode *pListWriteRelationNode, CEntityTimeSliceCountSet *pEntityTimeSliceCountSet, CEntityTimeSliceCountNode *&pEntityTimeSliceCountNode,int TimeID)
	{
		//获取时间片ID
		//int	iTimeID = pListWriteRelationNode->getEntityRelationSet()->getTimeID();
		pEntityTimeSliceCountNode = pEntityTimeSliceCountSet->getHeadTimeSliceCountNode();
		if(getRecordData(TimeID, pEntityTimeSliceCountNode))
			
		return true;
	}

	bool getRecordData(int iTimeID, CEntityTimeSliceCountNode *& pEntityTimeSliceCountNode)
	{
		while (iTimeID != pEntityTimeSliceCountNode->getTimeSliceCount()->getTimeID())
			pEntityTimeSliceCountNode = pEntityTimeSliceCountNode->getNextTimeSliceCountNode();
		
		return true;
	}
	
private:
	
};

