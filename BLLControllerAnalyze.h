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
		//�õ���BLL�㴫�ݹ�����DAL�����ָ��
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
    ˵��������BLL�����෽��
    ������ÿ�ζ�д�������
    ����ֵ��
    ����ʱ�䣺*/
	bool startAnalyze(int iReadStationNum)
	{
		
		//_CrtDumpMemoryLeaks();

		////��һ��
		//CEntityTimeSliceCountNode *pEntityTimeSliceCountNode1 = new CEntityTimeSliceCountNode();
		//pEntityTimeSliceCountNode1->getTimeSliceCount()->set();
		//pEntityTimeSliceCountNode1->getTimeSliceCount()->setTimeID(3);
		//pEntityTimeSliceCountNode1->getTimeSliceCount()->setSurvivalTime(5);
		////��һ������
		//pEntityTimeSliceCountSet->insertTimeSliceCount(pEntityTimeSliceCountNode1);

		//_CrtDumpMemoryLeaks();
		////pEntityTimeSliceCountSet->~CEntityTimeSliceCountSet();
		////_CrtDumpMemoryLeaks();
		////�ڶ���
		//CEntityTimeSliceCountNode *pEntityTimeSliceCountNode2 = new CEntityTimeSliceCountNode();
		//pEntityTimeSliceCountNode2->getTimeSliceCount()->set1();
		//pEntityTimeSliceCountNode2->getTimeSliceCount()->setTimeID(2);
		//pEntityTimeSliceCountNode2->getTimeSliceCount()->setSurvivalTime(4);
		////�ڶ�������
		//pEntityTimeSliceCountSet->insertTimeSliceCount(pEntityTimeSliceCountNode2);

		////������
		//CEntityTimeSliceCountNode *pEntityTimeSliceCountNode3 = new CEntityTimeSliceCountNode();
		//pEntityTimeSliceCountNode3->getTimeSliceCount()->set2();
		//pEntityTimeSliceCountNode3->getTimeSliceCount()->setTimeID(1);
		//pEntityTimeSliceCountNode3->getTimeSliceCount()->setSurvivalTime(10);
		////����������
		//pEntityTimeSliceCountSet->insertTimeSliceCount(pEntityTimeSliceCountNode3);
		//pEntityTimeSliceCountSet->setNodeNum(3);

		//m_pFrameDAL->initPreProcessControl();
		m_pFrameDAL->initAlgorithmControl();

		//m_pFrameDAL->getPreprocessedData(pEntityTimeSliceCountSet);
		
		//ѭ����ȡ������д��
		//for(int iCount = 0; iCount < 1; iCount++)
		bool bCheckSuccessed = true;
		while(bCheckSuccessed)
		{
			CEntityTimeSliceCountSet *pEntityTimeSliceCountSet = new CEntityTimeSliceCountSet();
			//��������DAL��ļ���
			CListWriteRelationSet *pWriteListRelationSet = new CListWriteRelationSet();
			bCheckSuccessed = m_pFrameDAL->getPreprocessedData(pEntityTimeSliceCountSet);
			if(bCheckSuccessed == false)
				break;
			//ÿ�η�����ʼʱ����model��������Ҫ����һ��
			//�������
			//m_pModelBLL->startAnalyze(pEntityTimeSliceCountSet, pWriteListRelationSet);

			m_pModelBLLTest->startAnalyze(pEntityTimeSliceCountSet, pWriteListRelationSet);
			//check����
			/*CListWriteRelationNode *temp = pWriteListRelationSet->getListWriteRelationHeadNode();
			while(temp)
			{
				m_objFrameDAL->writeStdFile(temp->getEntityRelationSet()->getString());
				temp = temp->getNextRelationNode();
			}*/

			//д���ļ�
			//�����ֵ����
			if(pWriteListRelationSet->getNodeNum() != 0)
			{
				m_pFrameDAL->putRelatedData(pWriteListRelationSet);
				//���д��������������ڵ㸳ֵΪ��
				delete pWriteListRelationSet;//->releaseNode();
				//pWriteListRelationSet->setNodeNum(0);
			}

			//ɾ����������
			delete pEntityTimeSliceCountSet;
			pEntityTimeSliceCountSet = NULL;
			//_CrtDumpMemoryLeaks();
		}
		//��������DAL��ļ���
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
		/*����ģ�Ͷ���*/
		CBLLModelRecordCount* pModel = new CBLLModelRecordCount();
		/*���ļ�*/
		m_pFrameDAL->initPreProcessControl();
		bool bCheck = true;
		/*ѭ����ȡ�軹��¼������*/
		while(bCheck)
		{
			CEntityTripDataSet* pTripDataSet = new CEntityTripDataSet();
		
			bCheck = m_pFrameDAL->getUseRecord(pTripDataSet,50);
			/*����ʱ��Ƭͳ������*/
			CEntityTimeSliceCountSet* pTimeSliceCountSet = new CEntityTimeSliceCountSet();
			pModel->insertingTripDataSet(pTimeSliceCountSet,pTripDataSet);
		
			/*��������*/
			//string strTimeSliceCountSet = pTimeSliceCountSet->changeToStringstream();
			//char* cstr =(char*)strTimeSliceCountSet.c_str();
			//m_pFrameDAL->writeStdFile(cstr);

			/*�������*/
			m_pFrameDAL->putPreprocessedData(pTimeSliceCountSet);

			delete pTripDataSet;
			pTripDataSet = NULL;
			/*����ʱ��Ƭͳ������*/
			delete pTimeSliceCountSet;
			pTimeSliceCountSet = NULL;
		}

		m_pFrameDAL->doPreprocessRehabilitation();
		/*����ģ�Ͷ���*/
		delete pModel;
		/*����DAL����*/
		//delete m_pFrameDAL;
		return 0;		
	}
		
private:
	//DAL�����
	CFrameDAL *m_pFrameDAL;

	//Model����
	CBLLModelAnalyze *m_pModelBLL;

	CBLLModelAnalyzeTest *m_pModelBLLTest;
};
