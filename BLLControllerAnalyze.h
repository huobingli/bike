#pragma once
#include"FrameDAL.h"
#include"EntityRelationSet.h"
#include"CBLLModelAnalyze.h"
#include"ListRelationSet.h"
#include"EntityTimeSliceCountSet.h"
#include"ListWriteRelationSet.h"
#include"BufferPoolBLL.h"
#include"BLLModelRecordCount.h"
#include"BLLModelAnalyzeTest.h"

#include <stdlib.h>    
class CBLLAnalyzeController
{
public:
	CBLLAnalyzeController(CFrameDAL *pFrameDAL)
	{
		//得到从BLL层传递过来的DAL层对象指针
		m_pFrameDAL = pFrameDAL;
		m_pModelBLL = new CBLLModelAnalyze(200);
		m_pModelBLLTest = new CBLLModelAnalyzeTest(610);
	}

	~CBLLAnalyzeController(void)
	{
		delete m_pModelBLL;
		m_pModelBLL = NULL;
		delete m_pModelBLLTest;
		m_pModelBLLTest = NULL;
	}


	/**
    说明：启动BLL控制类方法
    参数：每次读写对象个数
    返回值：
    更新时间：*/
	bool startAnalyze(int iReadStationNum)
	{
		
		//_CrtDumpMemoryLeaks();

		////第一个
		//CEntityTimeSliceCountNode *pEntityTimeSliceCountNode1 = new CEntityTimeSliceCountNode();
		//pEntityTimeSliceCountNode1->getTimeSliceCount()->set();
		//pEntityTimeSliceCountNode1->getTimeSliceCount()->setTimeID(3);
		//pEntityTimeSliceCountNode1->getTimeSliceCount()->setSurvivalTime(5);
		////第一个插入
		//pEntityTimeSliceCountSet->insertTimeSliceCount(pEntityTimeSliceCountNode1);

		//_CrtDumpMemoryLeaks();
		////pEntityTimeSliceCountSet->~CEntityTimeSliceCountSet();
		////_CrtDumpMemoryLeaks();
		////第二个
		//CEntityTimeSliceCountNode *pEntityTimeSliceCountNode2 = new CEntityTimeSliceCountNode();
		//pEntityTimeSliceCountNode2->getTimeSliceCount()->set1();
		//pEntityTimeSliceCountNode2->getTimeSliceCount()->setTimeID(2);
		//pEntityTimeSliceCountNode2->getTimeSliceCount()->setSurvivalTime(4);
		////第二个插入
		//pEntityTimeSliceCountSet->insertTimeSliceCount(pEntityTimeSliceCountNode2);

		////第三个
		//CEntityTimeSliceCountNode *pEntityTimeSliceCountNode3 = new CEntityTimeSliceCountNode();
		//pEntityTimeSliceCountNode3->getTimeSliceCount()->set2();
		//pEntityTimeSliceCountNode3->getTimeSliceCount()->setTimeID(1);
		//pEntityTimeSliceCountNode3->getTimeSliceCount()->setSurvivalTime(10);
		////第三个插入
		//pEntityTimeSliceCountSet->insertTimeSliceCount(pEntityTimeSliceCountNode3);
		//pEntityTimeSliceCountSet->setNodeNum(3);

		//m_pFrameDAL->initPreProcessControl();
		m_pFrameDAL->initAlgorithmControl();

		//m_pFrameDAL->getPreprocessedData(pEntityTimeSliceCountSet);
		
		//循环读取，处理，写入
		//for(int iCount = 0; iCount < 1; iCount++)
		bool bCheckSuccessed = true;
		while(bCheckSuccessed)
		{
			CEntityTimeSliceCountSet *pEntityTimeSliceCountSet = new CEntityTimeSliceCountSet();
			//创建传入DAL层的集合
			CListWriteRelationSet *pWriteListRelationSet = new CListWriteRelationSet();
			bCheckSuccessed = m_pFrameDAL->getPreprocessedData(pEntityTimeSliceCountSet);
			if(bCheckSuccessed == false)
				break;
			//每次分析开始时至少model链表中需要存在一个
			//进入分析
			//m_pModelBLL->startAnalyze(pEntityTimeSliceCountSet, pWriteListRelationSet);

			m_pModelBLLTest->startAnalyze(pEntityTimeSliceCountSet, pWriteListRelationSet);
			//check部分
			/*CListWriteRelationNode *temp = pWriteListRelationSet->getListWriteRelationHeadNode();
			while(temp)
			{
				m_objFrameDAL->writeStdFile(temp->getEntityRelationSet()->getString());
				temp = temp->getNextRelationNode();
			}*/

			//写入文件
			//如果有值返回
			if(pWriteListRelationSet->getNodeNum() != 0)
			{
				m_pFrameDAL->putRelatedData(pWriteListRelationSet);
				//清空写入链表，并将链表节点赋值为空
				delete pWriteListRelationSet;//->releaseNode();
				//pWriteListRelationSet->setNodeNum(0);
			}

			//删除读入链表
			delete pEntityTimeSliceCountSet;
			pEntityTimeSliceCountSet = NULL;
			//_CrtDumpMemoryLeaks();
		}
		//创建传入DAL层的集合
		if(m_pModelBLL->getListRelationSet()->getNodeNum() != 0)
		{
			CListWriteRelationSet *pWriteListRelationSet = new CListWriteRelationSet();
			m_pModelBLL->getRestRelationSet(pWriteListRelationSet);
			m_pFrameDAL->putRelatedData(pWriteListRelationSet);
			delete pWriteListRelationSet;
		}

		m_pFrameDAL->doAlgorithmRehabilitation();
		return true;
	}

	bool startPreAnalyze(int iRecordNum)
	{
		/*创建模型对象*/
		CBLLModelRecordCount* pModel = new CBLLModelRecordCount();
		/*打开文件*/
		m_pFrameDAL->initPreProcessControl();
		bool bCheck = true;
		/*循环读取借还记录并处理*/
		while(bCheck)
		{
			CEntityTripDataSet* pTripDataSet = new CEntityTripDataSet();
		
			bCheck = m_pFrameDAL->getUseRecord(pTripDataSet,50);
			/*创建时间片统计链表*/
			CEntityTimeSliceCountSet* pTimeSliceCountSet = new CEntityTimeSliceCountSet();
			pModel->insertingTripDataSet(pTimeSliceCountSet,pTripDataSet);
		
			/*检验数据*/
			//string strTimeSliceCountSet = pTimeSliceCountSet->changeToStringstream();
			//char* cstr =(char*)strTimeSliceCountSet.c_str();
			//m_pFrameDAL->writeStdFile(cstr);

			/*存入磁盘*/
			m_pFrameDAL->putPreprocessedData(pTimeSliceCountSet);

			delete pTripDataSet;
			pTripDataSet = NULL;
			/*销毁时间片统计链表*/
			delete pTimeSliceCountSet;
			pTimeSliceCountSet = NULL;
		}

		m_pFrameDAL->doPreprocessRehabilitation();
		/*销毁模型对象*/
		delete pModel;
		/*销毁DAL对象*/
		//delete m_pFrameDAL;
		return 0;		
	}
		
private:
	//DAL层对象
	CFrameDAL *m_pFrameDAL;

	//Model对象
	CBLLModelAnalyze *m_pModelBLL;

	CBLLModelAnalyzeTest *m_pModelBLLTest;
};
