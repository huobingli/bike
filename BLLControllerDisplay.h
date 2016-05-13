#pragma once
#include"FrameDAL.h"
#include"BLLModelDisplay.h"
#include "EntityTimeSliceCountSet.h"
#include "EntityRelationSet.h"
#include"FrameBLLDisplay.h"
#include"StationInfo.h"
//�������Ҫ����

//Ҫ��
//�����������Ҫ��EntityRelationSet���EntityTimeSliceCountSet���е�ͬһ��ʱ��Ƭ�ڵ�����ݽ��л�ԭ
//��ԭ����Ҫ����ʾ�ڽ����ϵ��������ݸ�ʽ�����������飬����������Լ�������
//�����ʾ��������

//ע��
//��������ֻ���к������ã���Ҫ���㴦�����Ҫ�����ڴ�ģ��

class CBLLControllerDisplay
{
public:
	CBLLControllerDisplay(CFrameDAL *pFrameDAL)
	{
		m_pFrameDAL = pFrameDAL;
		m_pBLLModelDisplay = new CBLLModelDisplay();
	}
	~CBLLControllerDisplay()
	{

	}


	int GetTimeID(int TimeIDset[])
	{
		int ArraySize;
		CListWriteRelationSet *pWriteListRelationSetNew = new CListWriteRelationSet();
		CListWriteRelationNode *pWriteListRelationNode = NULL;
		m_pFrameDAL->initAlgorithmControl();
		m_pFrameDAL->initPreProcessControl();
		m_pFrameDAL->getRelatedData(pWriteListRelationSetNew);
		pWriteListRelationNode = pWriteListRelationSetNew->getListWriteRelationHeadNode();

		//��ȡһ��ͳ������
		CEntityTimeSliceCountSet *pSet = new CEntityTimeSliceCountSet();
		//�½�
		CEntityTimeSliceCountNode *pNode = new CEntityTimeSliceCountNode();
		CEntityTimeSliceCountNode *pt;
		m_pFrameDAL->getPreprocessedData(pSet);
		ArraySize = pSet->getNodeNum();
		pt = pSet->getHeadTimeSliceCountNode();
		for (int iCount = 0; iCount < ArraySize; iCount++)
		{
			TimeIDset[iCount] = pt->getTimeSliceCount()->getTimeID();
			pt=pt->getNextTimeSliceCountNode();
		}
		
		return ArraySize;
	}
	/**
    ˵������ʾ��������һ��ʱ��Ƭ�Ĺ�ϵ���ݺ�ͳ��������ʾ�ڽ�����
    ������վ�����
    ����ֵ��վ�������Ϣ����
    ����ʱ�䣺*/
	int *showData(int &StationNum,int TimeID)
	{
		/*���Զ�ȡ����*/
	
		int kCount = 0;
	
		CListWriteRelationSet *pWriteListRelationSetNew = new CListWriteRelationSet();

		CListWriteRelationNode *pWriteListRelationNode = NULL;
		m_pFrameDAL->initAlgorithmControl();
		m_pFrameDAL->initPreProcessControl();
		while (m_pFrameDAL->getRelatedData(pWriteListRelationSetNew)){
			pWriteListRelationNode = pWriteListRelationSetNew->getListWriteRelationHeadNode();

			//��ȡһ��ͳ������
			CEntityTimeSliceCountSet *pSet = new CEntityTimeSliceCountSet();
			//�½�
			CEntityTimeSliceCountNode *pNode = new CEntityTimeSliceCountNode();

			m_pFrameDAL->getPreprocessedData(pSet);
			/*while (pWriteListRelationNode != NULL)
			{*/
			m_pBLLModelDisplay->startDisplay(pWriteListRelationNode, pSet, pNode,TimeID);
			//}
			//��ȡվ����
			StationNum = pWriteListRelationNode->getEntityRelationSet()->getStationNum();
			int  *StationRelation = new int[StationNum*StationNum];
			//��ȡ��ϵ����
			for (int iCount = 0; iCount < StationNum; iCount++)
				for (int jCount = 0; jCount < StationNum; jCount++)
				{
				
				StationRelation[kCount] = pWriteListRelationNode->getEntityRelationSet()->getStationRelation(iCount, jCount);
				kCount++;
		        }
			return StationRelation;
			


			delete pWriteListRelationSetNew;
			delete StationRelation;
			pWriteListRelationSetNew = NULL;
			pWriteListRelationSetNew = new CListWriteRelationSet;
		}

		m_pFrameDAL->doPreprocessRehabilitation();
		m_pFrameDAL->doAlgorithmRehabilitation();
		

		
		
	}

	/**
	˵������ʾ������������վ��ĵ���Ϣ��ʾ�ڽ�����
	������վ����Ϣ���飬վ��1��վ��2
	����ֵ����
	����ʱ�䣺*/
	void showInfo(StationInfo &m_StationInfo,int stationId1,int stationId2,int TimeID)
	{
		int flag = 0;
		int ArraySize;
		int length1 = 0;
		int length2 = 0;
	
		CEntityStationCount* m_pStationCount,*pt;
		CListWriteRelationSet *pWriteListRelationSetNew = new CListWriteRelationSet();

		CListWriteRelationNode *pWriteListRelationNode = NULL;
		m_pFrameDAL->initAlgorithmControl();
		m_pFrameDAL->initPreProcessControl();
		//while (m_pFrameDAL->getRelatedData(pWriteListRelationSetNew))
		//{
			m_pFrameDAL->getRelatedData(pWriteListRelationSetNew);
			pWriteListRelationNode = pWriteListRelationSetNew->getListWriteRelationHeadNode();

			//��ȡһ��ͳ������
			CEntityTimeSliceCountSet *pSet = new CEntityTimeSliceCountSet();
			//�½�
			CEntityTimeSliceCountNode *pNode = new CEntityTimeSliceCountNode();

			m_pFrameDAL->getPreprocessedData(pSet);
		
			m_pBLLModelDisplay->startDisplay(pWriteListRelationNode, pSet, pNode,TimeID);
			
		//	for (int jCount = 0; jCount < pNode->getTimeSliceCount()->getArraySize(); jCount++)
		//	{
			m_pStationCount = pNode->getTimeSliceCount()->getStationCount();
			pt = m_pStationCount;
			ArraySize = pNode->getTimeSliceCount()->getArraySize();
			//�ҵ���Ӧվ��
			while (ArraySize--)
			{
				if (stationId1 == m_pStationCount->getStationID())
				{
					flag = 1;
					break;
				}
					
				else
				{
					m_pStationCount++;
				}
			}
			//��ȡ���鳤��
			if (flag)
			{ 
				length1 = m_pStationCount->getRentArraySize();
				length2 = m_pStationCount->getReturnArraySize();
			//ȡ����Ϣ	
			for (int iCount = 0; iCount < length1; iCount++, m_StationInfo.m_StationData1++)
					{
				m_StationInfo.m_StationData1->setMaxtime(m_pStationCount->getRentCount()->getMaxCostTime());
				m_StationInfo.m_StationData1->setMintime(m_pStationCount->getRentCount()->getMinCostTime());
				m_StationInfo.m_StationData1->setOperatedTimes(m_pStationCount->getRentCount()->getOperatedTimes());
				m_StationInfo.m_StationData1->setId(m_pStationCount->getRentCount()->getRelatedStationID());
						m_StationInfo.m_StationData1->setRent(1);
						
					}
			for (int iCount = 0; iCount < length2; iCount++, m_StationInfo.m_StationData1++)
					{
				m_StationInfo.m_StationData1->setMaxtime(m_pStationCount->getReturnCount()->getMaxCostTime());
				m_StationInfo.m_StationData1->setMintime(m_pStationCount->getReturnCount()->getMinCostTime());
				m_StationInfo.m_StationData1->setOperatedTimes(m_pStationCount->getReturnCount()->getOperatedTimes());
				m_StationInfo.m_StationData1->setId(m_pStationCount->getReturnCount()->getRelatedStationID());
						m_StationInfo.m_StationData1->setRent(0);
						
					}


					m_StationInfo.setRecordNum1 (length1 + length2);


			}
					
					flag = 0;
					m_pStationCount = pt;
					ArraySize = pNode->getTimeSliceCount()->getArraySize();
					//�ҵ���Ӧ��վ��
					while (ArraySize--)
					{
						if (stationId2 == m_pStationCount->getStationID())
						{
							flag = 1;
							break;
						}

						else
						{
							m_pStationCount++;
						}
					}
					//��ȡ���鳤��
					if (flag)
					{
						length1 = m_pStationCount->getRentArraySize();
						length2 = m_pStationCount->getReturnArraySize();
						//ȡ����Ϣ	
						for (int iCount = 0; iCount < length1; iCount++, m_StationInfo.m_StationData2++)
						{
							m_StationInfo.m_StationData2->setMaxtime(m_pStationCount->getRentCount()->getMaxCostTime());
							m_StationInfo.m_StationData2->setMintime(m_pStationCount->getRentCount()->getMinCostTime());
							m_StationInfo.m_StationData2->setOperatedTimes(m_pStationCount->getRentCount()->getOperatedTimes());
							m_StationInfo.m_StationData2->setId(m_pStationCount->getRentCount()->getRelatedStationID());
							m_StationInfo.m_StationData2->setRent(1);

						}
						for (int iCount = 0; iCount < length2; iCount++, m_StationInfo.m_StationData2++)
						{
							m_StationInfo.m_StationData2->setMaxtime(m_pStationCount->getReturnCount()->getMaxCostTime());
							m_StationInfo.m_StationData2->setMintime(m_pStationCount->getReturnCount()->getMinCostTime());
							m_StationInfo.m_StationData2->setOperatedTimes(m_pStationCount->getReturnCount()->getOperatedTimes());
							m_StationInfo.m_StationData2->setId(m_pStationCount->getReturnCount()->getRelatedStationID());
							m_StationInfo.m_StationData2->setRent(0);

						}


						m_StationInfo.setRecordNum2(length1 + length2);


					}
		
		   

			delete pWriteListRelationSetNew;
		
			pWriteListRelationSetNew = NULL;
			pWriteListRelationSetNew = new CListWriteRelationSet;
		//}

		m_pFrameDAL->doPreprocessRehabilitation();
		m_pFrameDAL->doAlgorithmRehabilitation();
	}
	
	

private:
	CFrameDAL *m_pFrameDAL;

	CBLLModelDisplay *m_pBLLModelDisplay;
};