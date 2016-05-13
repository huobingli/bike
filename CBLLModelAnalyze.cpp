#include "StdAfx.h"
#include "CBLLModelAnalyze.h"
#include "FrameDAL.h"


CBLLModelAnalyze::CBLLModelAnalyze(int iStationNum)
{
	m_iTotalSurvivalNum = 0;
	m_iTotalStationNum = iStationNum;
	//�½�ͷ���
	m_pHeadListRelationSet = new CListRelationSet();
	m_pBufferPool = new CBufferPoolBLL();
	//����һ����ά����������
	m_pTimeSliceCountArray = NULL;

}

CBLLModelAnalyze::~CBLLModelAnalyze()
{
	delete m_pHeadListRelationSet;
	delete m_pBufferPool;
	m_pHeadListRelationSet = NULL;
	m_pBufferPool = NULL;
}

/**
˵������ʼ��model���ڲ�����
������
����ֵ��
����ʱ�䣺*/
void CBLLModelAnalyze::initArray()
{
	m_pTimeSliceCountArray = new CBLLModelEntityTimeSliceCountArray*[m_iTotalStationNum];
	for(int iCount = 0;iCount < m_iTotalStationNum; iCount++){
		m_pTimeSliceCountArray[iCount] = new CBLLModelEntityTimeSliceCountArray[m_iTotalStationNum];
	}
	
	//��ʼ����ά����
	for(int iCount = 0; iCount < m_iTotalStationNum; iCount++){
		for(int jCount = 0; jCount < m_iTotalStationNum; jCount++)
		{
			m_pTimeSliceCountArray[iCount][jCount].setMaxTime(0);
			m_pTimeSliceCountArray[iCount][jCount].setMinTime(0);
			m_pTimeSliceCountArray[iCount][jCount].setOperateTimes(0);
		}
	}
}
/**
˵�����ͷ�model���ڲ�����
������
����ֵ��
����ʱ�䣺*/
void CBLLModelAnalyze::releaseArray()
{
	for(int iCount = 0;iCount < m_iTotalStationNum; iCount++){
		delete [] m_pTimeSliceCountArray[iCount];
		m_pTimeSliceCountArray[iCount] = NULL;
	}
		delete []m_pTimeSliceCountArray;
}
	
string CBLLModelAnalyze::changeToStringstream()
{
	stringstream strstreamCount;
	char* cLeft = "(";
	char* cBlank = ",";
	char* cRight = ")";
	/*���������ԷŽ��ַ���*/
	strstreamCount<<cLeft;
	for(int iCount = 0; iCount < m_iTotalStationNum; iCount++)
	{
		strstreamCount<<cLeft;
		for(int jCount = 0; jCount < m_iTotalStationNum; jCount++)
		{
			strstreamCount<<m_pTimeSliceCountArray[iCount][jCount].changeToStringstream()<<cBlank;
		}
		strstreamCount<<cRight;
	}
	
	strstreamCount<<cRight;
	/*��stringstreamת����string*/
	string strCount(strstreamCount.str());

	return strCount;	
}

/**
˵����model����Ҫ����������ÿ�δ���һ��ͳ�Ƽ�������������������Ҫд��Ĺ�ϵ��������
������ͳ�Ƽ�������������ʽ���� �����ô��룩д�뼯������������ʽ��
����ֵ�������ô�����д�뼯������������ʽ��
����ʱ�䣺*/
bool CBLLModelAnalyze::startAnalyze(CEntityTimeSliceCountSet *pEntityTimeSliceCountSet, CListWriteRelationSet *&pListWriteRelationSet)
{
		
	//�жϴ���
	if(pEntityTimeSliceCountSet == NULL)
	{
		AfxMessageBox(_T("���벻��Ϊ��"));
		return false;
	}
	//���벻Ϊ��
	else
	{
		CEntityTimeSliceCountNode *tempTimeSliceCountNode;
		//��ȡ��һ���ڵ�
		tempTimeSliceCountNode = pEntityTimeSliceCountSet->getHeadTimeSliceCountNode();
			
		while(tempTimeSliceCountNode != NULL)
		{
			//��ʼ��model���ڴ�ṹ����
			initArray();
			//�����ݶ���model�е��ڴ�ṹ��
			copyEntityTimeSliceCountNode(tempTimeSliceCountNode);
			//���model��������Ϊ�գ������һ�����󣬶Խ���Ϊ0������Ϊ100
			if(m_pHeadListRelationSet->getNextRelationNode() == NULL)
			{			
				//��ýڵ����
				int iTimeSliceID = tempTimeSliceCountNode->getTimeSliceCount()->getTimeID();
				int iStationCount = tempTimeSliceCountNode->getTimeSliceCount()->getStationCount()->getRentArraySize();
				int iSurvivalNum = getSurvivalNum(tempTimeSliceCountNode->getTimeSliceCount()->getSurvivalTime());
	
				//������ϵ���ݽڵ�
				CListRelationNode *pListRelationNode = new CListRelationNode();
				//���ù�ϵ���ݲ���
				pListRelationNode->getEntityRelationSet()->setTimeID(iTimeSliceID);
				pListRelationNode->getEntityRelationSet()->setStationNum(m_iTotalStationNum);
				pListRelationNode->setSurvivalTime(iSurvivalNum);
				pListRelationNode->getEntityRelationSet()->initRelationSet();

				//���õ�һ���������
				for(int iCount = 0; iCount < m_iTotalStationNum; iCount++)
				{
					for(int jCount = 0; jCount < m_iTotalStationNum; jCount++)
					{
						if(iCount == jCount)
							pListRelationNode->getEntityRelationSet()->insertStationRelation(iCount, jCount, 100);
						else
							pListRelationNode->getEntityRelationSet()->insertStationRelation(iCount, jCount, 0);
					}
				}

				//����ڵ�
				m_pHeadListRelationSet->insertRelationNode(pListRelationNode);
					
				//�¸�׼������ڵ�
				tempTimeSliceCountNode = tempTimeSliceCountNode->getNextTimeSliceCountNode();

				CFrameDAL *pDAL = new CFrameDAL();
				string strTimeSliceCountSet = changeToStringstream();
				char* cstr =(char*)strTimeSliceCountSet.c_str();
				pDAL->writeStdFile(cstr);

				m_iTotalSurvivalNum++;
				releaseArray();
				continue;
			}
			//�������ڵ���������е�ͷ�ڵ����Ų�����
			//����һ���յĹ�ϵ����
			//else if(tempTimeSliceCountNode->getTimeSliceCount()->getTimeID() 
			//	- m_pHeadListRelationSet->getNextRelationNode()->getEntityRelationSet()->getTimeID() > 1)
			//{
			//	//������ݣ�����
			//	int iTimeSliceID = m_pHeadListRelationSet->getNextRelationNode()->getEntityRelationSet()->getTimeID() + 1;
			//	//�����µĹ�ϵ����
			//	CListRelationNode *pListRelationNode = new CListRelationNode();
			//	//���ù�ϵ���ݶ�λ�������
			//	pListRelationNode->getEntityRelationSet()->setTimeID(iTimeSliceID);
			//	pListRelationNode->getEntityRelationSet()->setStationNum(m_iTotalStationNum);
			//	//��ʼ����ϵ���ݶ�ά����
			//	pListRelationNode->getEntityRelationSet()->initRelationSet();

			//	//û�е�ʱ��Ƭ���ϣ�ֱ�ӽ���ʼ�������ݴ���������
			//	//getRelation(tempTimeSliceCountNode); 

			//	//���뵽��������
			//	m_pHeadListRelationSet->insertRelationNode(pListRelationNode);

			//		
			//m_iTotalSurvivalNum++;
			//	releaseArray();
			//	continue;
			//}
			else
			{
				//������
				getRelation(tempTimeSliceCountNode);      /***************/

				//������������
				int iFirstTime = tempTimeSliceCountNode->getTimeSliceCount()->getTimeID();
				int iSecondTime = m_pHeadListRelationSet->getNextRelationNode()->getNextRelationNode()->getEntityRelationSet()->getTimeID();
				//����������ڵ���
				m_iTotalSurvivalNum = m_iTotalSurvivalNum + iFirstTime - iSecondTime;

				//������
				/*CFrameDAL *pDAL = new CFrameDAL();
				string strTimeSliceCountSet = m_pHeadListRelationSet->changeToStringstream();
				char* cstr = (char*)strTimeSliceCountSet.c_str();
				pDAL->writeStdFile(cstr);*/


				//�¸�׼������ڵ�
				tempTimeSliceCountNode = tempTimeSliceCountNode->getNextTimeSliceCountNode();
				releaseArray();
				continue;
			}
			//����һ���ͽ������������ڽ�������
			//m_iTotalSurvivalTime++;

		}
		//_CrtDumpMemoryLeaks();
		//������
		CFrameDAL *pDAL = new CFrameDAL();
		string strTimeSliceCountSet = m_pHeadListRelationSet->changeToStringstream();
		char* cstr =(char*)strTimeSliceCountSet.c_str();
		pDAL->writeStdFile(cstr);

		judgeSurvivalTime(pListWriteRelationSet);
		//_CrtDumpMemoryLeaks();
		//�����ʱ����
		delete tempTimeSliceCountNode;
		tempTimeSliceCountNode = NULL;
		return true;
	}
}

/**
˵��������ͳ�Ƽ��ϣ���ԭ��ͳ�Ƽ��Ϸ����ڴ�ģ��������
������ʱ��Ƭͳ�Ƽ���
����ֵ��
����ʱ�䣺*/
bool CBLLModelAnalyze::copyEntityTimeSliceCountNode(CEntityTimeSliceCountNode *pEntityTimeSliceCountNode)
{
	//д��վ����Ŀ
	int iArrayNum = pEntityTimeSliceCountNode->getTimeSliceCount()->getArraySize();
	int iRentArraySize = 0;//pEntityTimeSliceCountNode->getTimeSliceCount()->getStationCount()->getRentArraySize();
	int iReturnArraySize = 0;//pEntityTimeSliceCountNode->getTimeSliceCount()->getStationCount()->getReturnArraySize();

	int iTargetStationID = 0;
	int iRelationStationID = 0;

	CEntityStationCount *tempEntityStationCount = NULL;
	CEntityCount *tempEntityCount = NULL;

	//���ѭ����EntityTimeSliceCount�������Ч����
	for(int iCount = 0; iCount < iArrayNum; iCount++)
	{
		//��ȡͳ�Ƽ�����վ��ͳ�ƶ���ָ��
		tempEntityStationCount = pEntityTimeSliceCountNode->getTimeSliceCount()->getStationCount();
		iRentArraySize = tempEntityStationCount[iCount].getRentArraySize();
		iReturnArraySize = tempEntityStationCount[iCount].getReturnArraySize();

		iTargetStationID = tempEntityStationCount[iCount].getStationID();
		//�ڲ�ѭ����EntityStationCount�������Ч����
		//for(int jCount = 0; jCount < iRentArraySize; jCount++)
		//{
		//	//��ȡͳ�Ƽ�����վ��ͳ�ƶ����ڵĽ賵��������ָ��
		//	tempEntityCount = tempEntityStationCount[iCount].getRentCount();
		//	iRelationStationID = tempEntityCount[jCount].getRelatedStationID();
		//		
		//	m_pTimeSliceCountArray[iTargetStationID - 1][iRelationStationID - 1].setMaxTime(tempEntityCount[jCount].getMaxCostTime());
		//	m_pTimeSliceCountArray[iTargetStationID - 1][iRelationStationID - 1].setMinTime(tempEntityCount[jCount].getMinCostTime());
		//	m_pTimeSliceCountArray[iTargetStationID - 1][iRelationStationID - 1].setOperateTimes(tempEntityCount[jCount].getOperatedTimes());
		//}

		//��������
		for(int jCount = 0; jCount < iReturnArraySize; jCount++)
		{
			//��ȡͳ�Ƽ�����վ��ͳ�ƶ����ڵĻ�����������ָ��
			tempEntityCount = tempEntityStationCount[iCount].getReturnCount();
			iRelationStationID = tempEntityCount[jCount].getRelatedStationID();
			
			m_pTimeSliceCountArray[iTargetStationID - 1][iRelationStationID - 1].setMaxTime((tempEntityCount[jCount].getMaxCostTime()) / 30 + 1 + 14602);
			m_pTimeSliceCountArray[iTargetStationID - 1][iRelationStationID - 1].setMinTime((tempEntityCount[jCount].getMinCostTime()) / 30 + 1 + 14602);
			m_pTimeSliceCountArray[iTargetStationID - 1][iRelationStationID - 1].setOperateTimes(tempEntityCount[jCount].getOperatedTimes());
		}
	}
	/*delete tempEntityStationCount;
	delete tempEntityCount;*/
	return true;
}

/**
˵������ʱ��Ƭͳ�Ƽ��Ͻ��м��㣬�ó���ǰʱ��Ƭ����Ĺ�ϵ����
������ʱ��Ƭͳ�Ƽ���
����ֵ��
����ʱ�䣺*/
bool CBLLModelAnalyze::getRelation(CEntityTimeSliceCountNode *pEntityTimeSliceCountNode)
{
	double iMaxRelation = 0;
	//�õ�ʱ��Ƭ����
	int iTimeSliceID = pEntityTimeSliceCountNode->getTimeSliceCount()->getTimeID();
	//�õ���ʱ��Ƭ�����а���վ������������վ�㲢����ȫ�����ڣ�
	//�õ������鳤��
	int iStationCount = pEntityTimeSliceCountNode->getTimeSliceCount()->getStationCount()->getReturnArraySize();
	//�õ���ʱ��Ƭ�����нڵ���������
	int iSurvivalNum = getSurvivalNum(pEntityTimeSliceCountNode->getTimeSliceCount()->getSurvivalTime());
	
	CListRelationNode *pListRelationNode = new CListRelationNode();
	//���ù�ϵ���ݶ�λ�������
	pListRelationNode->getEntityRelationSet()->setTimeID(iTimeSliceID);
	pListRelationNode->getEntityRelationSet()->setStationNum(m_iTotalStationNum);
	pListRelationNode->setSurvivalTime(iSurvivalNum);

	//��ʼ����ϵ���ݶ�ά����
	pListRelationNode->getEntityRelationSet()->initRelationSet();

	//�õ�����վ�����ƶȹ�ϵ
	double iStationRelation = 0;
	//��һ��վ��
	for(int iCount = 0;iCount < m_iTotalStationNum; iCount++)
	{
		//�ڶ���վ��
		for(int jCount = 0; jCount < m_iTotalStationNum; jCount++)
		{
			//��һ���ڵ�iCount �ڶ����ڵ�jCount
			if (iCount == jCount)
			{
				//pListRelationNode->getEntityRelationSet()->insertStationRelation(iCount, jCount, 1);
				continue;
			}
			//������վ�㲻Ϊͬһվ��
			else
			{
				//����iCount��jCount�����ڵ�֮������ƶ�
				iStationRelation = calculateRelation(iCount, jCount);
				if (iStationRelation > iMaxRelation)
				{
					iMaxRelation = iStationRelation;
				}
				pListRelationNode->getEntityRelationSet()->insertStationRelation(iCount, jCount, iStationRelation);
				iStationRelation = 0;
			}
		}
	}
	//CEntityRelationSet *pEntityRelationSet = pListRelationNode->getEntityRelationSet();
	//NormalizeMatrix(pEntityRelationSet, iMaxRelation);
	//������ɣ���������
	m_pHeadListRelationSet->insertRelationNode(pListRelationNode);
	return true;
}

/**
˵������������վ��֮������ƶȣ�����վ�㲻Ϊͬһ��վ�㣩
��������һ��վ�㣬�ڶ���վ��
����ֵ������վ�����ƶ�
����ʱ�䣺*/
double CBLLModelAnalyze::calculateRelation(int iFirstStation, int iSecondStation)
{
	double iStationRelation = 0;
	int iMaxTime = 0;
	int iMinTime = 0;
	//iEveryCoupleRelationSum���ڱ���һ������վ��Ĺ�ϵվ��֮��Ĺ�ϵ��
	double iEveryCoupleRelationSum = 0;
	//iPlusCount���ڱ����ۼӴ���������󷵻�����վ��֮���ϵֵ��ʱ����Ϊ����
	double iPlusCount = 0;

	//��һ��վ��ʱ��Ƭ�Ĳ�ֵ
	double iFirstStationTimeD_value = 0;
	//����վ��֮���ʱ��Ƭ�ص���ֵ
	double iStationOverLapTimeD_value = 0;
	//��һ��վ���ڵ�����ռ�ڸ�վ�㻻���ı���;
	double dRateOfStationCount = 0;

	//
	for(int iCount = 0; iCount < m_iTotalStationNum; iCount++)
	{
		//�����һ��վ��Ĺ�ϵվ��Ĳ�����Ϊ0����ʾ�ù�ϵվ�㲻��Ҫ����
		if(m_pTimeSliceCountArray[iFirstStation][iCount].getOperateTimes() == 0)
		{
			continue;
		}
		//��ϵվ����Ҫ���ǣ��õ���һ��վ���ϵվ���һЩ���ݣ�C�͵�һ��վ��������ֵ
		else
		{
			//��ȡ��һ��ʱ��Ƭ�����С����Ĳ�ֵ
			iFirstStationTimeD_value = m_pTimeSliceCountArray[iFirstStation][iCount].getMaxTime()
				- m_pTimeSliceCountArray[iFirstStation][iCount].getMinTime() + 1;
			
			//��ȡC��ֵ
			for(int kCount = 0; kCount < m_iTotalStationNum; kCount++)
			{
				dRateOfStationCount = dRateOfStationCount + m_pTimeSliceCountArray[iFirstStation][kCount].getOperateTimes();
			}
			//�õ�C
			dRateOfStationCount = m_pTimeSliceCountArray[iFirstStation][iCount].getOperateTimes() / dRateOfStationCount;

		}

		//�õ��Ƚ�վ�������
		for(int jCount = 0; jCount < m_iTotalStationNum; jCount++)
		{
			//���Ƚ�վ��Ĳ�����Ϊ0������Ƚ�
			if(m_pTimeSliceCountArray[iSecondStation][jCount].getOperateTimes() == 0)
				continue;

			//����ͻ�ȡ�������ص�ʱ��Ƭ
			else
			{
				//��ȡ��һ��վ���ϵվ��͵ڶ���վ���ϵվ���ص�ʱ��Ƭ
				getOverLapTimes(m_pTimeSliceCountArray[iFirstStation][iCount], 
				m_pTimeSliceCountArray[iSecondStation][jCount], iMaxTime, iMinTime);

				if(iMaxTime != iMinTime)
				{
					//��������վ��֮���ص�ʱ��Ƭ��ֵ
					iStationOverLapTimeD_value = iMinTime - iMaxTime + 1;
					
					//iEveryCoupleRelationSum���ڱ���һ������վ��Ĺ�ϵվ��֮��Ĺ�ϵ��
					//iPlusCount���ڱ����ۼӴ���������󷵻�����վ��֮���ϵֵ��ʱ����Ϊ����
					//���㵱ǰ�ص�ʱ��Ƭ�е��ص�ʱ��վ���ϵ��
					for(int lCount = iMaxTime; lCount <= iMinTime; lCount++)
					{
						iEveryCoupleRelationSum = iEveryCoupleRelationSum + 
							getStationRelationOfNode(lCount, iFirstStation, iSecondStation) *
							iStationOverLapTimeD_value / iFirstStationTimeD_value * dRateOfStationCount;
						iPlusCount++;
					}
				}
				iStationRelation = iStationRelation + iEveryCoupleRelationSum;

				//��ÿ�ε����ӵ���������
				iEveryCoupleRelationSum = 0;
			}
		}

		//Cֵ����
		dRateOfStationCount = 0;
	}
	if(iPlusCount == 0)
		return 0;
	else
		return (iStationRelation / iPlusCount);
}
	
/**
˵������ȡ�������еĹ�ϵ�����ڲ���վ���ϵֵ
������ʱ��ƬID��Ŀ��վ�㣬����վ��
����ֵ��վ���ϵֵ
����ʱ�䣺*/
double CBLLModelAnalyze::getStationRelationOfNode(int iTimeSlice, int iTargetStationID, int iRelationStationID)
{
	//��ȡʱ��Ƭվ��ϵ����ʱ������������û������ʱ�����������������
	if(m_pHeadListRelationSet->getNextRelationNode() == NULL || 
		m_pHeadListRelationSet->getNextRelationNode()->getEntityRelationSet()->getTimeID() < iTimeSlice)
		return 0;
	//��ȡ����
	else
	{
		CListRelationNode *tempListRelationNode = m_pHeadListRelationSet->getNextRelationNode();
		while(tempListRelationNode != NULL)
		{
			//ѭ��ƥ����ϵ�ʱ��Ƭ
			if(tempListRelationNode->getEntityRelationSet()->getTimeID() == iTimeSlice)
				return tempListRelationNode->getEntityRelationSet()->getStationRelation(iTargetStationID, iRelationStationID);	
			else
				tempListRelationNode = tempListRelationNode->getNextRelationNode();
		}
		return 0;
	}
}

/**
˵�����õ��ص�ʱ��Ƭ
��������һ��վ�㣬�ڶ���վ�㣬��Сʱ���ţ����ʱ����
����ֵ�����ô�����Сʱ���ţ����ô������ʱ����
����ʱ�䣺*/
void CBLLModelAnalyze::getOverLapTimes(CBLLModelEntityTimeSliceCountArray iFirstCount, CBLLModelEntityTimeSliceCountArray iSecondCount, int &iMinTime, int &iMaxTime)
{
	//�������վ���û��ֵ,����ж�Ҫ��Ҫ�ٴ��޸�
	if(iFirstCount.getMaxTime() == 0 && iSecondCount.getMaxTime() == 0)
	{
		iMinTime = 0;
		iMaxTime = 0;
	}
	//����һ��վ�����Сʱ����ڵڶ���վ������ʱ�䣬���ߵ�һ�����ʱ��С�ڵ�һ��վ����Сʱ��
	else if (iFirstCount.getMaxTime() < iSecondCount.getMinTime() || iFirstCount.getMinTime() > iSecondCount.getMaxTime())
	{
		iMinTime = 0;
		iMaxTime = 0;
	}
	//��Ч����
	else 
	{
		//����һ��վ�����С�ȵڶ���վ����С��
		if(iFirstCount.getMaxTime() > iSecondCount.getMaxTime())
			iMaxTime = iSecondCount.getMaxTime();
		else
			iMaxTime = iFirstCount.getMaxTime();
		//����һ��վ������ȵڶ���վ�����С
		if(iFirstCount.getMinTime() < iSecondCount.getMinTime())
			iMinTime = iSecondCount.getMinTime();
		else
			iMinTime = iFirstCount.getMinTime();
	}
}
	
/**
˵������ģ���ڲ���ʱ��Ƭ��ϵ������������жϣ��������д�����������С��model�����������ڵģ������ϲ�BLL������
���������ô��뷵��BLL�������Ĺ�ϵ��������
����ֵ�����÷���
����ʱ�䣺*/
bool CBLLModelAnalyze::judgeSurvivalTime(CListWriteRelationSet *&pListWriteRelationSet)
{
	//��¼��ȡ�ڵ����
	int iStationCount = 0;
	//�½�һ����ϵ����ָ�룬������ֵΪ��
	CListRelationNode *pHeadListRelationNode = NULL;
	//��������������
	if(m_pHeadListRelationSet->getNodeNum() >= 0)
	{
		//����һ���ڵ㸳ֵ���½��Ĺ�ϵ����ָ��
		pHeadListRelationNode = m_pHeadListRelationSet->getNextRelationNode();

		//ͨ�����ѭ���õ��������
		//1����������������while��ͨ��if�����������������ڶ��ȵ�ǰ��������С��������������д��
		//2����������whileͨ��if����
		while(pHeadListRelationNode != NULL)
		{
			//���ڵ��е��������ڴ��ڵ�ǰ��������
			if(pHeadListRelationNode->getSurvivalTime() > m_iTotalSurvivalNum)
			{
				//����ѭ��
				//pHeadListRelationNode = pHeadListRelationNode->getNextRelationNode();
				break;
			} else {
				//��ָ��������λ,������ȡ�ڵ����ۼ�
				pHeadListRelationNode = pHeadListRelationNode->getNextRelationNode();
				iStationCount++;
			}
		}
	} else {
		AfxMessageBox(_T("�������нڵ��������Ϊ��ֵ"));
		return false;
	}
	//_CrtDumpMemoryLeaks();
	//_CrtDumpMemoryLeaks();
	//�ж�д��������ɣ����������ʽת��
	if(iStationCount == 0)
		return true;
	else
	{
		turnToListWriteRelationSet(iStationCount, pListWriteRelationSet);
		return true;
	}
	//_CrtDumpMemoryLeaks();
	//�ͷ��ڴ�
	//delete pHeadListRelationNode;
	
}

/**
˵�������ڴ�ģ���е�������ʽת���ɿ��Դ���DAL���������ʽ������ListRelationSet ת����ListWriteRelationSet��
�������ڴ�ģ���������ȡ������int���������ô��룩����DAL������������ʽ��
����ֵ�������ô���������DAL������������ʽ��
����ʱ�䣺*/
bool CBLLModelAnalyze::turnToListWriteRelationSet(int iNodeNum, CListWriteRelationSet *&pListWriteRelationSet)
{
	//�������
	//_CrtDumpMemoryLeaks();
	CListRelationNode *pListRelationNode = m_pHeadListRelationSet->getNextRelationNode();
	for(int iCount = 0; iCount < iNodeNum; iCount++)
	{
		//CListWriteRelationNode *pListWriteRelationNode = m_objBufferPool->getWriteRelationNode();
		//m_pBufferPool->mallocWriteRelationNode();
		CListWriteRelationNode *pListWriteRelationNode = new CListWriteRelationNode();//m_pBufferPool->getWriteRelationNode();

		//���ù�ϵ����,�����й�ϵ���ϳ�ʼ��
		pListWriteRelationNode->getEntityRelationSet()->setTimeID(pListRelationNode->getEntityRelationSet()->getTimeID());
		pListWriteRelationNode->getEntityRelationSet()->setStationNum(m_iTotalStationNum);
		pListWriteRelationNode->getEntityRelationSet()->initRelationSet();
		//_CrtDumpMemoryLeaks();
		//����ʱ��ƬID
			
		//���ù�ϵ����
		pListWriteRelationNode->setEntityRelationSet(pListRelationNode->getEntityRelationSet());
			
		//_CrtDumpMemoryLeaks();
		//���뵽����DAL������
		pListWriteRelationSet->insertRelationSet(pListWriteRelationNode);
		//�Ƶ���һ���ڴ��ϵ����
		pListRelationNode = pListRelationNode->getNextRelationNode();
			
	}
	//������
	//_CrtDumpMemoryLeaks();
	//��ȥд��DAL��Ľڵ���������±���ڵ���
	m_pHeadListRelationSet->setNodeNum(m_pHeadListRelationSet->getNodeNum() - iNodeNum);

	//_CrtDumpMemoryLeaks();
	//�������
	pListRelationNode = m_pHeadListRelationSet->getNextRelationNode();

	CListRelationNode *pListRelationLinkNode = NULL;
	//������ϵ������
	if(iNodeNum == 1)
	{
		pListRelationLinkNode = pListRelationNode->getNextRelationNode();
		pListRelationNode->setNextRelationNode(NULL);
		delete pListRelationNode;
	}
	else
	{
		int iNodeCount = iNodeNum;
		CListRelationSet *pListRelationDeleteSet = new CListRelationSet();
		pListRelationDeleteSet->setFirstListRelationNode(pListRelationNode);
		/*CListRelationNode *pListRelationLinkNode = pTempRelationNode->getNextRelationNode();*/
		while(iNodeCount > 1)
		{
				
			pListRelationNode = pListRelationNode->getNextRelationNode();
			iNodeCount--;
		}
		pListRelationLinkNode = pListRelationNode->getNextRelationNode();
		pListRelationNode->setNextRelationNode(NULL);

		//_CrtDumpMemoryLeaks();
		pListRelationDeleteSet->releaseNode();
			
	}
	//����ͷ�
	//_CrtDumpMemoryLeaks();

	//�����������ϵĵ�һ�����ݽڵ�
	//�����������ݸ�����Ϊ0�������¸��ڵ�
	//��������ΪNULL
	if(m_pHeadListRelationSet->getNodeNum() != 0)
	{
		m_pHeadListRelationSet->setFirstListRelationNode(pListRelationLinkNode);
	}
	else
	{
		m_pHeadListRelationSet->setFirstListRelationNode(NULL);
	}
	return true;
}



/*************************************************test****test****test****test**********************************************/
/**
 * ���ܣ������100�������ڵ������㣬�Ǿ����ȶ�
 * ���룺Դ���󣬹�100������
 * ��������100������
 */
void CBLLModelAnalyze::NormalizeMatrix(CEntityRelationSet *&pEntityRelationSet, double dNormalizeParameter){
	double iGetRelation = 0;
	double iWriteRelation = 0;
	dNormalizeParameter = dNormalizeParameter / 100;
	
	for (int iCount = 0; iCount < m_iTotalStationNum; iCount++)
	{
		for (int jCount = 0; jCount < m_iTotalStationNum; jCount++)
		{
			if (iCount == jCount)
				continue;
			else
			{
				iGetRelation = pEntityRelationSet->getStationRelation(iCount, jCount);
				iWriteRelation = iGetRelation / dNormalizeParameter;
				pEntityRelationSet->insertStationRelation(iCount, jCount, iWriteRelation);
			}
		}
	}

}