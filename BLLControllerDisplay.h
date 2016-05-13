#pragma once
#include"FrameDAL.h"
#include"BLLModelDisplay.h"
#include "EntityTimeSliceCountSet.h"
#include "EntityRelationSet.h"
#include"FrameBLLDisplay.h"
#include"StationInfo.h"
//这个类需要完善

//要点
//这个类里你需要把EntityRelationSet类和EntityTimeSliceCountSet类中的同一个时间片节点的数据进行还原
//还原成你要的显示在界面上的那种数据格式，可以是数组，链表（这个你自己决定）
//最后显示到界面上

//注意
//控制类中只进行函数调用，需要计算处理的需要创建内存模型

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

		//读取一次统计数据
		CEntityTimeSliceCountSet *pSet = new CEntityTimeSliceCountSet();
		//新建
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
    说明：显示函数，将一个时间片的关系数据和统计数据显示在界面上
    参数：站点个数
    返回值：站点关联信息数组
    更新时间：*/
	int *showData(int &StationNum,int TimeID)
	{
		/*测试读取功能*/
	
		int kCount = 0;
	
		CListWriteRelationSet *pWriteListRelationSetNew = new CListWriteRelationSet();

		CListWriteRelationNode *pWriteListRelationNode = NULL;
		m_pFrameDAL->initAlgorithmControl();
		m_pFrameDAL->initPreProcessControl();
		while (m_pFrameDAL->getRelatedData(pWriteListRelationSetNew)){
			pWriteListRelationNode = pWriteListRelationSetNew->getListWriteRelationHeadNode();

			//读取一次统计数据
			CEntityTimeSliceCountSet *pSet = new CEntityTimeSliceCountSet();
			//新建
			CEntityTimeSliceCountNode *pNode = new CEntityTimeSliceCountNode();

			m_pFrameDAL->getPreprocessedData(pSet);
			/*while (pWriteListRelationNode != NULL)
			{*/
			m_pBLLModelDisplay->startDisplay(pWriteListRelationNode, pSet, pNode,TimeID);
			//}
			//获取站点数
			StationNum = pWriteListRelationNode->getEntityRelationSet()->getStationNum();
			int  *StationRelation = new int[StationNum*StationNum];
			//获取关系数组
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
	说明：显示函数，将两个站点的的信息显示在界面上
	参数：站点信息数组，站点1，站点2
	返回值：无
	更新时间：*/
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

			//读取一次统计数据
			CEntityTimeSliceCountSet *pSet = new CEntityTimeSliceCountSet();
			//新建
			CEntityTimeSliceCountNode *pNode = new CEntityTimeSliceCountNode();

			m_pFrameDAL->getPreprocessedData(pSet);
		
			m_pBLLModelDisplay->startDisplay(pWriteListRelationNode, pSet, pNode,TimeID);
			
		//	for (int jCount = 0; jCount < pNode->getTimeSliceCount()->getArraySize(); jCount++)
		//	{
			m_pStationCount = pNode->getTimeSliceCount()->getStationCount();
			pt = m_pStationCount;
			ArraySize = pNode->getTimeSliceCount()->getArraySize();
			//找到对应站点
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
			//获取数组长度
			if (flag)
			{ 
				length1 = m_pStationCount->getRentArraySize();
				length2 = m_pStationCount->getReturnArraySize();
			//取出信息	
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
					//找到对应的站点
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
					//获取数组长度
					if (flag)
					{
						length1 = m_pStationCount->getRentArraySize();
						length2 = m_pStationCount->getReturnArraySize();
						//取出信息	
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