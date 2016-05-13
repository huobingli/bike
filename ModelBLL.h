#pragma once
#include"EntityTimeSliceCountSet.h"
#include"ListRelationSet.h"
#include"ListWriteRelationSet.h"
#include"BufferPoolBLL.h"
#include"BLLModelEntityTimeSliceCountArray.h"
class CBLLModelAnalyze
{
public:
	/**
	 * ���ܣ�
	 * ���룺
	 * ������
	 * ����������
	 */
	CBLLModelAnalyze(int iStationNum)
	{
		m_iTotalSurvivalTime = 3000;
		m_iTotalStationNum = iStationNum;
		//�½�ͷ���
		m_pHeadListRelationSet = new CListRelationSet();
		_CrtDumpMemoryLeaks();
		m_pBufferPool = new CBufferPoolBLL();
		_CrtDumpMemoryLeaks();
		//����һ����ά����������
		m_pTimeSliceCountArray = NULL;
		//��ʼ������
		initArray();
		_CrtDumpMemoryLeaks();
		/*releaseArray();
		_CrtDumpMemoryLeaks();*/
	}

	~CBLLModelAnalyze()
	{
		delete m_pHeadListRelationSet;
		delete m_pBufferPool;
		//delete m_pTimeSliceCountArray;
		//_CrtDumpMemoryLeaks();
		releaseArray();
		//_CrtDumpMemoryLeaks();
	}

	void initArray()
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

	void releaseArray()
	{
		for(int iCount = 0;iCount < m_iTotalStationNum; iCount++){
			delete [] m_pTimeSliceCountArray[iCount];
		}

		delete [] m_pTimeSliceCountArray;
	}
	/**
	 * ���ܣ�model����Ҫ����������ÿ�δ���һ��ͳ�Ƽ�������������������Ҫд��Ĺ�ϵ��������
	 * ���룺ͳ�Ƽ�������������ʽ���� �����ô��룩д�뼯������������ʽ��
	 * �����������ô�����д�뼯������������ʽ��
	 * ����������
	 */
	bool startAnalyze(CEntityTimeSliceCountSet *pEntityTimeSliceCountSet, CListWriteRelationSet *&pListWriteRelationSet)
	{
		CEntityTimeSliceCountNode *tempTimeSliceCountNode;
		//�жϴ���
		if(pEntityTimeSliceCountSet == NULL)
		{
			AfxMessageBox(_T("���벻��Ϊ��"));
			return false;
		}
		//���벻Ϊ��
		else
		{
			//��ȡ��һ���ڵ�
			tempTimeSliceCountNode = pEntityTimeSliceCountSet->getHeadTimeSliceCountNode();
			
			//���Դ��룬��������667ʱ��Ƭ
			//tempTimeSliceCountNode = tempTimeSliceCountNode->getNextTimeSliceCountNode()->
			//	getNextTimeSliceCountNode()->getNextTimeSliceCountNode();
			//if(tempTimeSliceCountNode->getTimeSliceCount()->getTimeID() == 667)
			//{
			//	initArray();
			//	copyEntityTimeSliceCountNode(tempTimeSliceCountNode);
			//	getRelation(tempTimeSliceCountNode);
			//}

			while(tempTimeSliceCountNode != NULL)
			{
				//��ʼ��model���ڴ�ṹ����
				initArray();
				//�����ݶ���model�е��ڴ�ṹ��
				copyEntityTimeSliceCountNode(tempTimeSliceCountNode);

				//���model��������Ϊ�գ������һ�����󣬶Խ���Ϊ0������Ϊ100
				if(m_pHeadListRelationSet->getNextRelationNode() == NULL)
				{
					//�����ϲ�����������
					//getRelation(tempTimeSliceCountNode);      /***************/
			
					//�õ�ʱ��Ƭ����
					int iTimeSliceID = tempTimeSliceCountNode->getTimeSliceCount()->getTimeID();
					int iStationCount = tempTimeSliceCountNode->getTimeSliceCount()->getStationCount()->getRentArraySize();
					int iSurvivalTime = tempTimeSliceCountNode->getTimeSliceCount()->getSurvivalTime();
	
					CListRelationNode *pListRelationNode = new CListRelationNode();
					//���ù�ϵ���ݶ�λ�������
					pListRelationNode->getEntityRelationSet()->setTimeID(iTimeSliceID);
					pListRelationNode->getEntityRelationSet()->setStationNum(m_iTotalStationNum);
					pListRelationNode->setSurvivalTime(iSurvivalTime);
					pListRelationNode->getEntityRelationSet()->initRelationSet();
					for(int iCount = 0; iCount < m_iTotalStationNum; iCount++)
					{
						for(int jCount = 0; jCount < m_iTotalStationNum; jCount++)
						{
							if(iCount == jCount)
								pListRelationNode->getEntityRelationSet()->insertStationRelation(iCount, jCount, 0);
							else
								pListRelationNode->getEntityRelationSet()->insertStationRelation(iCount, jCount, 100);
						}
					}
					m_pHeadListRelationSet->insertRelationNode(pListRelationNode);

					//�¸�׼������ڵ�
					tempTimeSliceCountNode = tempTimeSliceCountNode->getNextTimeSliceCountNode();

					m_iTotalSurvivalTime++;
					continue;
				}
				//�������ڵ���������е�ͷ�ڵ����Ų�����
				//����һ���յĹ�ϵ����
				else if(tempTimeSliceCountNode->getTimeSliceCount()->getTimeID() 
					- m_pHeadListRelationSet->getNextRelationNode()->getEntityRelationSet()->getTimeID() > 1)
				{
					//������ݣ�����
					int iTimeSliceID = m_pHeadListRelationSet->getNextRelationNode()->getEntityRelationSet()->getTimeID() + 1;
					//�����µĹ�ϵ����
					CListRelationNode *pListRelationNode = new CListRelationNode();
					//���ù�ϵ���ݶ�λ�������
					pListRelationNode->getEntityRelationSet()->setTimeID(iTimeSliceID);
					pListRelationNode->getEntityRelationSet()->setStationNum(m_iTotalStationNum);
					//��ʼ����ϵ���ݶ�ά����
					pListRelationNode->getEntityRelationSet()->initRelationSet();

					//û�е�ʱ��Ƭ���ϣ�ֱ�ӽ���ʼ�������ݴ���������
					//getRelation(tempTimeSliceCountNode); 

					//���뵽��������
					m_pHeadListRelationSet->insertRelationNode(pListRelationNode);

					
					m_iTotalSurvivalTime++;
					continue;
				}
				else
				{
					//������
					getRelation(tempTimeSliceCountNode);      /***************/
			
					//�¸�׼������ڵ�
					tempTimeSliceCountNode = tempTimeSliceCountNode->getNextTimeSliceCountNode();

					
					m_iTotalSurvivalTime++;
					continue;
				}
				//����һ���ͽ������������ڽ�������
				//m_iTotalSurvivalTime++;

			}
		
			judgeSurvivalTime(pListWriteRelationSet);
			
			//�ͷ�
			delete tempTimeSliceCountNode;
			return true;
		}
	}


	/**

	 * ���ܣ�����ͳ�Ƽ��ϣ���ԭ��ͳ�Ƽ��Ϸ����ڴ�ģ��
	 * ���룺ͳ�Ƽ���
	 * ������
	 * ����������
	 */
	bool copyEntityTimeSliceCountNode(CEntityTimeSliceCountNode *pEntityTimeSliceCountNode)
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
			//iReturnArraySize = tempEntityStationCount[iCount].getReturnArraySize();

			iTargetStationID = tempEntityStationCount[iCount].getStationID();
			//�ڲ�ѭ����EntityStationCount�������Ч����
			for(int jCount = 0; jCount < iRentArraySize; jCount++)
			{
				//��ȡͳ�Ƽ�����վ��ͳ�ƶ����ڵĽ賵��������ָ��
				tempEntityCount = tempEntityStationCount[iCount].getRentCount();
				iRelationStationID = tempEntityCount[jCount].getRelatedStationID();
				
				m_pTimeSliceCountArray[iTargetStationID - 1][iRelationStationID - 1].setMaxTime(tempEntityCount[jCount].getMaxCostTime());
				m_pTimeSliceCountArray[iTargetStationID - 1][iRelationStationID - 1].setMinTime(tempEntityCount[jCount].getMinCostTime());
				m_pTimeSliceCountArray[iTargetStationID - 1][iRelationStationID - 1].setOperateTimes(tempEntityCount[jCount].getOperatedTimes());
			}

			//��������
			//for(int jCount = 0; jCount < iReturnArraySize; jCount++)
			//{
			//	//��ȡͳ�Ƽ�����վ��ͳ�ƶ����ڵĻ�����������ָ��
			//	tempEntityCount = tempEntityStationCount[iCount].getReturnCount();
			//	iRelationStationID = tempEntityCount[jCount].getRelatedStationID();
			//	
			//	m_pTimeSliceCountArray[iTargetStationID - 1][iRelationStationID - 1].setMaxTime(tempEntityCount[jCount].getMaxCostTime());
			//	m_pTimeSliceCountArray[iTargetStationID - 1][iRelationStationID - 1].setMinTime(tempEntityCount[jCount].getMinCostTime());
			//	m_pTimeSliceCountArray[iTargetStationID - 1][iRelationStationID - 1].setOperateTimes(tempEntityCount[jCount].getOperatedTimes());
			//}
		}

		/*delete tempEntityStationCount;
		delete tempEntityCount;*/
		return true;
	}

	/**
	 * ���ܣ���ʱ��Ƭͳ�Ƽ��Ͻ��м��㣬�ó���ǰʱ��Ƭ����Ĺ�ϵ����
	 * ���룺ʱ��Ƭͳ�Ƽ��ϣ�������ʽ��,д��DAL���ϵͳ�Ƽ��ϣ�������ʽ��
	 * ���������ô���
	 * ����������
	 */
	bool getRelation(CEntityTimeSliceCountNode *pEntityTimeSliceCountNode)
	{
		//�õ�ʱ��Ƭ����
		int iTimeSliceID = pEntityTimeSliceCountNode->getTimeSliceCount()->getTimeID();
		//�õ���ʱ��Ƭ�����а���վ������������վ�㲢����ȫ�����ڣ�
		//�õ������鳤��
		int iStationCount = pEntityTimeSliceCountNode->getTimeSliceCount()->getStationCount()->getRentArraySize();
		//�õ���ʱ��Ƭ�����нڵ���������
		int iSurvivalTime = pEntityTimeSliceCountNode->getTimeSliceCount()->getSurvivalTime();
	
		CListRelationNode *pListRelationNode = new CListRelationNode();
		//���ù�ϵ���ݶ�λ�������
		pListRelationNode->getEntityRelationSet()->setTimeID(iTimeSliceID);
		pListRelationNode->getEntityRelationSet()->setStationNum(m_iTotalStationNum);
		pListRelationNode->setSurvivalTime(iSurvivalTime);

		//��ʼ����ϵ���ݶ�ά����
		pListRelationNode->getEntityRelationSet()->initRelationSet();

		//����������
		/*****************************�������Ӧ��û��ô��***********************************/
		//for(int iCount = 0; iCount < iStationCount; iCount++)
		//{
		//	//pEntityTimeSliceCountNode->getTimeSliceCount()->getStationCount()->getStationID();
		//	pListRelationNode->getEntityRelationSet()->insertStationRelation(iCount,);
		//	
		//}
		int iStationRelation = 0;
		//��һ��վ��
		for(int iCount = 0;iCount < m_iTotalStationNum; iCount++)
		 {
			 //�ڶ���վ��
			 for(int jCount = 0; jCount < m_iTotalStationNum; jCount++)
			 {
				 //��һ���ڵ�iCount �ڶ����ڵ�jCount
				 if(iCount == jCount)
					//pListRelationNode->getEntityRelationSet()->insertStationRelation(iCount, jCount, 1);
					continue;
				 //������վ�㲻Ϊͬһվ��
				 else
				 {
					 /*if((iCount == 24 || iCount == 37 || iCount == 44 || iCount == 51 || iCount == 90)
						 && (jCount == 24 || jCount == 37 || jCount == 44 || jCount == 51 || jCount == 99))*/
					 //����iCount��jCount�����ڵ�֮������ƶ�
					 iStationRelation = calculateRelation(iCount, jCount);
					 pListRelationNode->getEntityRelationSet()->insertStationRelation(iCount, jCount, iStationRelation);
					 iStationRelation = 0;
				 }
				 //if(m_pTimesliceCountArray[iCount][jCount].getOperateTimes() == 0)
				 //calculateRelation(iCount, jCount);

				 //pListRelationNode->getEntityRelationSet()->insertStationRelation();
			 }
		 }

		//������ɣ���������
		m_pHeadListRelationSet->insertRelationNode(pListRelationNode);
		return true;
	}

	/**
	 * ���ܣ���������վ��֮������ƶȣ�����վ�㲻Ϊͬһ��վ�㣩
	 * ���룺��һ��վ�㣬�ڶ���վ��
	 * ����������վ�����ƶ�
	 * ����������
	 */
	int calculateRelation(int iFirstStation, int iSecondStation)
	{
		double iStationRelation = 0;
		int iMaxTime = 0;
		int iMinTime = 0;
		//iEveryCoupleRelationSum���ڱ���һ������վ��Ĺ�ϵվ��֮��Ĺ�ϵ��
		double iEveryCoupleRelationSum = 0;
		//iPlusCount���ڱ����ۼӴ���������󷵻�����վ��֮���ϵֵ��ʱ����Ϊ����
		int iPlusCount = 0;

		//��һ��վ��ʱ��Ƭ�Ĳ�ֵ
		int iFirstStationTimeD_value = 0;
		//����վ��֮���ʱ��Ƭ�ص���ֵ
		int iStationOverLapTimeD_value = 0;
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
					iEveryCoupleRelationSum = 0;
				}
			}

			dRateOfStationCount = 0;
		}
		if(iPlusCount == 0)
			return 0;
		else
			return (int)(iStationRelation / iPlusCount);
	}
	
	/**
	 * ���ܣ���ȡ�������еĹ�ϵ�����ڲ���վ���ϵֵ
	 * ���룺ʱ��ƬID��Ŀ��վ�㣬����վ��
	 * ������վ���ϵֵ
	 * ����������
	 */
	int getStationRelationOfNode(int iTimeSlice, int iTargetStationID, int iRelationStationID)
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
				if(tempListRelationNode->getEntityRelationSet()->getTimeID() == iTimeSlice)
					return tempListRelationNode->getEntityRelationSet()->getStationRelation(	iTargetStationID, iRelationStationID);	
				else
					tempListRelationNode = tempListRelationNode->getNextRelationNode();
			}
			return 0;
		}
	}


	/**
	 * ���ܣ��õ��ص�ʱ��Ƭ
	 * ���룺��һ��վ�㣬�ڶ���վ�㣬��Сʱ���ţ����ʱ����
	 * ���������ô�����Сʱ���ţ����ô������ʱ����
	 * ����������
	 */
	void getOverLapTimes(CBLLModelEntityTimeSliceCountArray iFirstCount, CBLLModelEntityTimeSliceCountArray iSecondCount, int &iMinTime, int &iMaxTime)
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
	 * ���ܣ���ģ���ڲ���ʱ��Ƭ��ϵ������������жϣ��������д�����������С��model�����������ڵģ������ϲ�BLL������
	 * ���룺
	 * ������
	 * ����������
	 */
	bool judgeSurvivalTime(CListWriteRelationSet *&pListWriteRelationSet)
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
				if(pHeadListRelationNode->getSurvivalTime() > m_iTotalSurvivalTime)
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
		}

		//�ж�д��������ɣ����������ʽת��
		turnToListWriteRelationSet(iStationCount, pListWriteRelationSet);

		//�ͷ��ڴ�
		delete pHeadListRelationNode;
		return true;
	}

	/**
	 * ���ܣ����ڴ�ģ���е�������ʽת���ɿ��Դ���DAL���������ʽ������ListRelationSet ת����ListWriteRelationSet��
	 * ���룺�ڴ�ģ���������ȡ������int���������ô��룩����DAL������������ʽ��
	 * �����������ô���������DAL������������ʽ��
	 * ����������
	 */
	bool turnToListWriteRelationSet(int iNodeNum, CListWriteRelationSet *&pListWriteRelationSet)
	{
	
		//m_objBufferPool->mallocWriteRelationNode();
		//������Ҫ�����         
		/*******************************�����*************************************/
		
		//CListWriteRelationNode *pListWriteRelationNode = new CListWriteRelationNode();
		
		CListRelationNode *pListRelationNode = m_pHeadListRelationSet->getNextRelationNode();
		for(int iCount = 0; iCount < iNodeNum; iCount++)
		{
			//CListWriteRelationNode *pListWriteRelationNode = m_objBufferPool->getWriteRelationNode();
			m_pBufferPool->mallocWriteRelationNode();
			CListWriteRelationNode *pListWriteRelationNode = m_pBufferPool->getWriteRelationNode();
			//���ù�ϵ����,�����й�ϵ���ϳ�ʼ��
			pListWriteRelationNode->getEntityRelationSet()->setStationNum(m_iTotalStationNum);
			pListWriteRelationNode->getEntityRelationSet()->initRelationSet();
			//����ʱ��ƬID
			pListWriteRelationNode->getEntityRelationSet()->setTimeID(pListRelationNode->getEntityRelationSet()->getTimeID());
			//���ù�ϵ����
			pListWriteRelationNode->setEntityRelationSet(pListRelationNode->getEntityRelationSet());
			

			//���뵽����DAL������
			pListWriteRelationSet->insertRelationSet(pListWriteRelationNode);
			//�Ƶ���һ���ڴ��ϵ����
			pListRelationNode = pListRelationNode->getNextRelationNode();
		}
		//��ȥд��DAL��Ľڵ���������±���ڵ���
		m_pHeadListRelationSet->setNodeNum(m_pHeadListRelationSet->getNodeNum() - iNodeNum);

		CListRelationNode *pTempRelationNode = m_pHeadListRelationSet->getNextRelationNode();
		while(iNodeNum > 0)
		{
			pTempRelationNode = pTempRelationNode->getNextRelationNode();
			iNodeNum--;
		}
		m_pHeadListRelationSet->setFirstListRelationNode(pTempRelationNode);
		return true;
	}

private:
	//������������
	int m_iTotalSurvivalTime;
	//ģ���ڲ�ʱ��Ƭ��ϵ��������
	CListRelationSet *m_pHeadListRelationSet;
	//����ض���
	CBufferPoolBLL *m_pBufferPool;
	//��վ�����
	int m_iTotalStationNum;
	////�ṹ���ά����
	//structSet **m_pStructSet;
	CBLLModelEntityTimeSliceCountArray **m_pTimeSliceCountArray;
};

