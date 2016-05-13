#include"stdafx.h"

#include"BLLModelRecordCount.h"

CBLLModelRecordCount::CBLLModelRecordCount()
{
	m_pBufPool = new CBufPool();
	m_pTimeSliceMemorySet = new CBLLEntityTimeSliceMemorySet();
}

CBLLModelRecordCount::~CBLLModelRecordCount()
{
	delete m_pBufPool;
	m_pBufPool = NULL;
	delete m_pTimeSliceMemorySet;
}

bool CBLLModelRecordCount::insertingTripDataSet(CEntityTimeSliceCountSet* &pTimeSliceCountSet,CEntityTripDataSet* &pTripDataSet)
{
	//定义一个借还记录变量并获取第一条借还记录
	CEntityTripData* pTripData = pTripDataSet->getFirst();

	int iPresentTimeSliceID = -1; //当前时间片编号
	int iDealTimeSliceID = -1; //处理时间片编号
	int count = READNUM;
	while(count>0)
	{
		/*将借还记录按时间片划分为一个操作记录集集合*/
		CBLLEntityOperationSetSet* pOperationSetSet = new CBLLEntityOperationSetSet();
		divingOperation(pOperationSetSet,pTripData,60);


		//更新当前时间片编号
		iPresentTimeSliceID = updatingCurrentTimeSliceID(pOperationSetSet);

		
		/*对操作集集合进行操作*/
		/*借操作肯定存在，将借操作的时间片序号赋值给处理时间片编号
		  在操作集集合中，若借操作和还操作在同一时间片内，操作集集合的结构是第一个元素是借还操作集，第二个为空操作集
																						借还操作集中，有借操作和还操作
						  若借操作和还操作不在同一时间片内，操作集集合的结构是第一个元素是借操作集，第二个为还操作集
																						借操作集中，有借操作，没有还操作
																						还操作集中，没有借操作，有还操作
		*/
		/*定义借操作集（借还操作集）和还操作集（空操作集）*/		
		CBLLEntityOperationSet* pRentOperationSet = pOperationSetSet->getRentOperationSet();
		CBLLEntityOperationSet* pReturnOperationSet = pOperationSetSet->getReturnOperationSet();

		/*根据借操作设置操作时间片编号*/
		iDealTimeSliceID = pRentOperationSet->getTimeSliceID();
		
		/*判断借操作和还操作是否在同一时间片*/
		if(pOperationSetSet->isOneTimeSlice())
		{
			/*对借还操作集进行处理*/
			CBLLEntityOperationSet* pRentAndReturnOperationSet = pRentOperationSet;

			/*判断是否存在对应时间片*/
			int iRentAndReturnTimeSliceID = pRentAndReturnOperationSet->getTimeSliceID();
			if(!m_pTimeSliceMemorySet->locatingTimeSliceMemory(iRentAndReturnTimeSliceID))
			{
				/*从缓冲池申请对应时间片内存对象并插入链表*/
				CBLLEntityTimeSliceMemory* pApplyTimeSliceMemory = m_pBufPool->ApplyingTimeSliceMemory();
				pApplyTimeSliceMemory->setTimeSliceID(iRentAndReturnTimeSliceID);		
				CEntityTimeSliceMemoryNode* pTimeSliceMemoryNode = new CEntityTimeSliceMemoryNode(pApplyTimeSliceMemory);
				m_pTimeSliceMemorySet->insertingTimeSliceMemory(pTimeSliceMemoryNode);
			}
			/*取出对应时间内存对象并插入操作集集合*/
			CEntityTimeSliceMemoryNode* pRentAndReturnOperTimeSliceMemoryNode = m_pTimeSliceMemorySet->getNode(iRentAndReturnTimeSliceID);
			CBLLEntityTimeSliceMemory* pRentAndReturnOperTimeSliceMemory = pRentAndReturnOperTimeSliceMemoryNode->getTimeSliceMemory();
			pRentAndReturnOperTimeSliceMemory->insertingRentAndReturnOperationSet(pRentAndReturnOperationSet);
			m_pTimeSliceMemorySet->updatingTimeSliceMemoryNode(pRentAndReturnOperTimeSliceMemory);
		}
		else
		{
			/*对借操作集进行处理*/
			CBLLEntityOperationSet* pRent = pRentOperationSet;
			int iRentTimeSliceID = pRent->getTimeSliceID();
			/*判断是否存在对应时间片*/
			if(!m_pTimeSliceMemorySet->locatingTimeSliceMemory(iRentTimeSliceID))
			{
				/*从缓冲池申请对应时间片内存对象并插入链表*/
				CBLLEntityTimeSliceMemory* pApplyTimeSliceMemory = m_pBufPool->ApplyingTimeSliceMemory();
				pApplyTimeSliceMemory->setTimeSliceID(iRentTimeSliceID);
				CEntityTimeSliceMemoryNode* pTimeSliceMemoryNode = new CEntityTimeSliceMemoryNode(pApplyTimeSliceMemory);
				m_pTimeSliceMemorySet->insertingTimeSliceMemory(pTimeSliceMemoryNode);
			}
			/*取出对应时间片内存对象并插入借操作集*/
			CEntityTimeSliceMemoryNode* pRentOperTimeSliceMemoryNode = m_pTimeSliceMemorySet->getNode(iRentTimeSliceID);
			CBLLEntityTimeSliceMemory* pRentOperTimeSliceMemory = pRentOperTimeSliceMemoryNode->getTimeSliceMemory();
			pRentOperTimeSliceMemory->insertingRentOperationSet(pRent);
			m_pTimeSliceMemorySet->updatingTimeSliceMemoryNode(pRentOperTimeSliceMemory);

			/*对还操作集进行处理*/
			CBLLEntityOperationSet* pReturn = pReturnOperationSet;
			int iReturnTimeSliceID = pReturn->getTimeSliceID();
			/*判断是否存在对应时间片*/
			if(!m_pTimeSliceMemorySet->locatingTimeSliceMemory(iReturnTimeSliceID))
			{
				/*从缓冲池申请对应时间片内存对象并插入链表*/
				CBLLEntityTimeSliceMemory* pApplyTimeSliceMemory = m_pBufPool->ApplyingTimeSliceMemory();
				pApplyTimeSliceMemory->setTimeSliceID(iReturnTimeSliceID);
				CEntityTimeSliceMemoryNode* pTimeSliceMemoryNode = new CEntityTimeSliceMemoryNode(pApplyTimeSliceMemory);
				m_pTimeSliceMemorySet->insertingTimeSliceMemory(pTimeSliceMemoryNode);
			}
			/*取出对应时间片内存对象并插入借操作集*/
			CEntityTimeSliceMemoryNode* pReturnOperTimeSliceMemoryNode = m_pTimeSliceMemorySet->getNode(iReturnTimeSliceID);
			CBLLEntityTimeSliceMemory* pReturnOperTimeSliceMemory = pReturnOperTimeSliceMemoryNode->getTimeSliceMemory();
			pReturnOperTimeSliceMemory->insertingReturnOperationSet(pReturn);
			m_pTimeSliceMemorySet->updatingTimeSliceMemoryNode(pReturnOperTimeSliceMemory);
		}
		//释放操作集集合
		delete pOperationSetSet;
		pOperationSetSet = NULL;
		/*对不再进行操作的时间片内存对象进行永久化处理*/
		/*存储判断标志*/
		bool bCheck = true;
		/*循环读取头节点的时间片内存对象，如果该内存对象的时间片编号小于当前操作时间片编号就存储，
		若不满足，则将bCheck置为空，跳出while循环*/
		while(bCheck)
		{
			/*获取第一个元素，即时间片最小的元素*/
			CEntityTimeSliceMemoryNode* pWriteTimeSliceMemoryHeadNode =m_pTimeSliceMemorySet->getHeadNode();
			/*获取最小的时间片内存对象*/
			CBLLEntityTimeSliceMemory* pWriteTimeSliceMemory = pWriteTimeSliceMemoryHeadNode->getTimeSliceMemory();
			if(pWriteTimeSliceMemory->getTimeSliceID()<iPresentTimeSliceID)
			{
				CEntityTimeSliceCountNode* pWriteTimeSliceCountNode = new CEntityTimeSliceCountNode();
				pWriteTimeSliceCountNode->updatingTimeSliceCount(pWriteTimeSliceMemory);
				pTimeSliceCountSet->insertTimeSliceCount(pWriteTimeSliceCountNode);			
				/*更新头节点,即删除头节点*/
				m_pTimeSliceMemorySet->updatingHeadNode();
			}
			else
			{
				bCheck = false;
			}
		}

		pTripData = pTripDataSet->getNext();

		count--;
	}

	return true;
}


bool CBLLModelRecordCount::divingOperation(CBLLEntityOperationSetSet* pOperationSetSet,CEntityTripData* pTripData,int iTimeCell)
{

	//计算时间片编号
	int iRentTimeSliceID = computingTimeSliceID(pTripData->getStartStationTime(),iTimeCell);
	int iReturnTimeSliceID = computingTimeSliceID(pTripData->getStopStationTime(),iTimeCell);

	//划分借操作1
	CBLLEntityOperation* pRentOperation = new CBLLEntityOperation(iRentTimeSliceID,true);
	pRentOperation->updatingRentOperation(pTripData);
	
	//划分还操作1
	CBLLEntityOperation* pReturnOperation = new CBLLEntityOperation(iReturnTimeSliceID,false);
	pReturnOperation->updatingReturnOperation(pTripData);

	//如果借操作和还操作的在同一时间片
	if(iRentTimeSliceID == iReturnTimeSliceID)
	{
		//创建操作集，
		CBLLEntityOperationSet* pOperationSet = new CBLLEntityOperationSet(iRentTimeSliceID,pRentOperation,pReturnOperation);
		pOperationSetSet->insertingOperationSet(true,pOperationSet);
		delete pRentOperation;
		pRentOperation = NULL;
		delete pReturnOperation;
		pReturnOperation = NULL;
		return true;
	}
	//如果借操作和还操作不在同一时间片
	else
	{
		//创建借操作集
		CBLLEntityOperationSet* pRentOperationSet = new CBLLEntityOperationSet(iRentTimeSliceID,pRentOperation,true);
		pOperationSetSet->insertingOperationSet(true,pRentOperationSet);
		delete pRentOperation;
		pRentOperation = NULL;
		//创建还操作集
		CBLLEntityOperationSet* pReturnOperationSet = new CBLLEntityOperationSet(iReturnTimeSliceID,pReturnOperation,false);
		pOperationSetSet->insertingOperationSet(false,pReturnOperationSet);
		delete pReturnOperation;
		pReturnOperation = NULL;
		return true;
	}
}

int CBLLModelRecordCount::computingTimeSliceID(long int iTime,int iTimeCell)
{
	int iTimeSliceID,iMonth,iDay,iHour,iMinute;
	iMonth = (int)(iTime%100000000)/1000000;
	iDay = (int)(iTime%1000000)/10000;
	iHour = (int)(iTime%10000)/100;
	iMinute = (int)iTime%100;

	/*计算该天是一年中的第几天*/
	int iDayInYear = changeDayInYear(iMonth,iDay);
	/*时间片编号从0开始*/
	iTimeSliceID = (iDayInYear-1)*144 + (iHour)*6 + iMinute/10;
	return iTimeSliceID;

}

int CBLLModelRecordCount::updatingCurrentTimeSliceID(CBLLEntityOperationSetSet* pOperationSetSet)
{
	int iTimeSliceID;
	CBLLEntityOperationSet* pOperationSet = new CBLLEntityOperationSet();
	
	pOperationSet = pOperationSetSet->getRentOperationSet();
	iTimeSliceID = pOperationSet->getTimeSliceID();
	return iTimeSliceID;
}

int CBLLModelRecordCount::changeDayInYear(int iMonth,int iDay)
{
	int iDayInYear = 0;
	int months[12] = {31,28,31,30,31,30,31,31,30,31,30,31};
	for(int i=0;i<iMonth;i++)
	{
		iDayInYear = iDayInYear+months[i];
	}
	iDayInYear = iDayInYear + iDay;

	return iDayInYear;
}
