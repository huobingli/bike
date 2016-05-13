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
	//����һ���軹��¼��������ȡ��һ���軹��¼
	CEntityTripData* pTripData = pTripDataSet->getFirst();

	int iPresentTimeSliceID = -1; //��ǰʱ��Ƭ���
	int iDealTimeSliceID = -1; //����ʱ��Ƭ���
	int count = READNUM;
	while(count>0)
	{
		/*���軹��¼��ʱ��Ƭ����Ϊһ��������¼������*/
		CBLLEntityOperationSetSet* pOperationSetSet = new CBLLEntityOperationSetSet();
		divingOperation(pOperationSetSet,pTripData,60);


		//���µ�ǰʱ��Ƭ���
		iPresentTimeSliceID = updatingCurrentTimeSliceID(pOperationSetSet);

		
		/*�Բ��������Ͻ��в���*/
		/*������϶����ڣ����������ʱ��Ƭ��Ÿ�ֵ������ʱ��Ƭ���
		  �ڲ����������У���������ͻ�������ͬһʱ��Ƭ�ڣ����������ϵĽṹ�ǵ�һ��Ԫ���ǽ軹���������ڶ���Ϊ�ղ�����
																						�軹�������У��н�����ͻ�����
						  ��������ͻ���������ͬһʱ��Ƭ�ڣ����������ϵĽṹ�ǵ�һ��Ԫ���ǽ���������ڶ���Ϊ��������
																						��������У��н������û�л�����
																						���������У�û�н�������л�����
		*/
		/*�������������軹���������ͻ����������ղ�������*/		
		CBLLEntityOperationSet* pRentOperationSet = pOperationSetSet->getRentOperationSet();
		CBLLEntityOperationSet* pReturnOperationSet = pOperationSetSet->getReturnOperationSet();

		/*���ݽ�������ò���ʱ��Ƭ���*/
		iDealTimeSliceID = pRentOperationSet->getTimeSliceID();
		
		/*�жϽ�����ͻ������Ƿ���ͬһʱ��Ƭ*/
		if(pOperationSetSet->isOneTimeSlice())
		{
			/*�Խ軹���������д���*/
			CBLLEntityOperationSet* pRentAndReturnOperationSet = pRentOperationSet;

			/*�ж��Ƿ���ڶ�Ӧʱ��Ƭ*/
			int iRentAndReturnTimeSliceID = pRentAndReturnOperationSet->getTimeSliceID();
			if(!m_pTimeSliceMemorySet->locatingTimeSliceMemory(iRentAndReturnTimeSliceID))
			{
				/*�ӻ���������Ӧʱ��Ƭ�ڴ���󲢲�������*/
				CBLLEntityTimeSliceMemory* pApplyTimeSliceMemory = m_pBufPool->ApplyingTimeSliceMemory();
				pApplyTimeSliceMemory->setTimeSliceID(iRentAndReturnTimeSliceID);		
				CEntityTimeSliceMemoryNode* pTimeSliceMemoryNode = new CEntityTimeSliceMemoryNode(pApplyTimeSliceMemory);
				m_pTimeSliceMemorySet->insertingTimeSliceMemory(pTimeSliceMemoryNode);
			}
			/*ȡ����Ӧʱ���ڴ���󲢲������������*/
			CEntityTimeSliceMemoryNode* pRentAndReturnOperTimeSliceMemoryNode = m_pTimeSliceMemorySet->getNode(iRentAndReturnTimeSliceID);
			CBLLEntityTimeSliceMemory* pRentAndReturnOperTimeSliceMemory = pRentAndReturnOperTimeSliceMemoryNode->getTimeSliceMemory();
			pRentAndReturnOperTimeSliceMemory->insertingRentAndReturnOperationSet(pRentAndReturnOperationSet);
			m_pTimeSliceMemorySet->updatingTimeSliceMemoryNode(pRentAndReturnOperTimeSliceMemory);
		}
		else
		{
			/*�Խ���������д���*/
			CBLLEntityOperationSet* pRent = pRentOperationSet;
			int iRentTimeSliceID = pRent->getTimeSliceID();
			/*�ж��Ƿ���ڶ�Ӧʱ��Ƭ*/
			if(!m_pTimeSliceMemorySet->locatingTimeSliceMemory(iRentTimeSliceID))
			{
				/*�ӻ���������Ӧʱ��Ƭ�ڴ���󲢲�������*/
				CBLLEntityTimeSliceMemory* pApplyTimeSliceMemory = m_pBufPool->ApplyingTimeSliceMemory();
				pApplyTimeSliceMemory->setTimeSliceID(iRentTimeSliceID);
				CEntityTimeSliceMemoryNode* pTimeSliceMemoryNode = new CEntityTimeSliceMemoryNode(pApplyTimeSliceMemory);
				m_pTimeSliceMemorySet->insertingTimeSliceMemory(pTimeSliceMemoryNode);
			}
			/*ȡ����Ӧʱ��Ƭ�ڴ���󲢲���������*/
			CEntityTimeSliceMemoryNode* pRentOperTimeSliceMemoryNode = m_pTimeSliceMemorySet->getNode(iRentTimeSliceID);
			CBLLEntityTimeSliceMemory* pRentOperTimeSliceMemory = pRentOperTimeSliceMemoryNode->getTimeSliceMemory();
			pRentOperTimeSliceMemory->insertingRentOperationSet(pRent);
			m_pTimeSliceMemorySet->updatingTimeSliceMemoryNode(pRentOperTimeSliceMemory);

			/*�Ի����������д���*/
			CBLLEntityOperationSet* pReturn = pReturnOperationSet;
			int iReturnTimeSliceID = pReturn->getTimeSliceID();
			/*�ж��Ƿ���ڶ�Ӧʱ��Ƭ*/
			if(!m_pTimeSliceMemorySet->locatingTimeSliceMemory(iReturnTimeSliceID))
			{
				/*�ӻ���������Ӧʱ��Ƭ�ڴ���󲢲�������*/
				CBLLEntityTimeSliceMemory* pApplyTimeSliceMemory = m_pBufPool->ApplyingTimeSliceMemory();
				pApplyTimeSliceMemory->setTimeSliceID(iReturnTimeSliceID);
				CEntityTimeSliceMemoryNode* pTimeSliceMemoryNode = new CEntityTimeSliceMemoryNode(pApplyTimeSliceMemory);
				m_pTimeSliceMemorySet->insertingTimeSliceMemory(pTimeSliceMemoryNode);
			}
			/*ȡ����Ӧʱ��Ƭ�ڴ���󲢲���������*/
			CEntityTimeSliceMemoryNode* pReturnOperTimeSliceMemoryNode = m_pTimeSliceMemorySet->getNode(iReturnTimeSliceID);
			CBLLEntityTimeSliceMemory* pReturnOperTimeSliceMemory = pReturnOperTimeSliceMemoryNode->getTimeSliceMemory();
			pReturnOperTimeSliceMemory->insertingReturnOperationSet(pReturn);
			m_pTimeSliceMemorySet->updatingTimeSliceMemoryNode(pReturnOperTimeSliceMemory);
		}
		//�ͷŲ���������
		delete pOperationSetSet;
		pOperationSetSet = NULL;
		/*�Բ��ٽ��в�����ʱ��Ƭ�ڴ����������û�����*/
		/*�洢�жϱ�־*/
		bool bCheck = true;
		/*ѭ����ȡͷ�ڵ��ʱ��Ƭ�ڴ����������ڴ�����ʱ��Ƭ���С�ڵ�ǰ����ʱ��Ƭ��žʹ洢��
		�������㣬��bCheck��Ϊ�գ�����whileѭ��*/
		while(bCheck)
		{
			/*��ȡ��һ��Ԫ�أ���ʱ��Ƭ��С��Ԫ��*/
			CEntityTimeSliceMemoryNode* pWriteTimeSliceMemoryHeadNode =m_pTimeSliceMemorySet->getHeadNode();
			/*��ȡ��С��ʱ��Ƭ�ڴ����*/
			CBLLEntityTimeSliceMemory* pWriteTimeSliceMemory = pWriteTimeSliceMemoryHeadNode->getTimeSliceMemory();
			if(pWriteTimeSliceMemory->getTimeSliceID()<iPresentTimeSliceID)
			{
				CEntityTimeSliceCountNode* pWriteTimeSliceCountNode = new CEntityTimeSliceCountNode();
				pWriteTimeSliceCountNode->updatingTimeSliceCount(pWriteTimeSliceMemory);
				pTimeSliceCountSet->insertTimeSliceCount(pWriteTimeSliceCountNode);			
				/*����ͷ�ڵ�,��ɾ��ͷ�ڵ�*/
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

	//����ʱ��Ƭ���
	int iRentTimeSliceID = computingTimeSliceID(pTripData->getStartStationTime(),iTimeCell);
	int iReturnTimeSliceID = computingTimeSliceID(pTripData->getStopStationTime(),iTimeCell);

	//���ֽ����1
	CBLLEntityOperation* pRentOperation = new CBLLEntityOperation(iRentTimeSliceID,true);
	pRentOperation->updatingRentOperation(pTripData);
	
	//���ֻ�����1
	CBLLEntityOperation* pReturnOperation = new CBLLEntityOperation(iReturnTimeSliceID,false);
	pReturnOperation->updatingReturnOperation(pTripData);

	//���������ͻ���������ͬһʱ��Ƭ
	if(iRentTimeSliceID == iReturnTimeSliceID)
	{
		//������������
		CBLLEntityOperationSet* pOperationSet = new CBLLEntityOperationSet(iRentTimeSliceID,pRentOperation,pReturnOperation);
		pOperationSetSet->insertingOperationSet(true,pOperationSet);
		delete pRentOperation;
		pRentOperation = NULL;
		delete pReturnOperation;
		pReturnOperation = NULL;
		return true;
	}
	//���������ͻ���������ͬһʱ��Ƭ
	else
	{
		//�����������
		CBLLEntityOperationSet* pRentOperationSet = new CBLLEntityOperationSet(iRentTimeSliceID,pRentOperation,true);
		pOperationSetSet->insertingOperationSet(true,pRentOperationSet);
		delete pRentOperation;
		pRentOperation = NULL;
		//������������
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

	/*���������һ���еĵڼ���*/
	int iDayInYear = changeDayInYear(iMonth,iDay);
	/*ʱ��Ƭ��Ŵ�0��ʼ*/
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
