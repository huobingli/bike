#pragma once
#include"FrameDAL.h"
#include"BLLControllerAnalyze.h"

class CFrameBLL
{
public:
	CFrameBLL(void)
	{
		//����DAL����
		m_pFrameDAL = new CFrameDAL();
	}

	~CFrameBLL(void)
	{
		//�ͷ�DAL����
		delete m_pFrameDAL;
		m_pFrameDAL = NULL;
	}

	/**
	 * ���ܣ�����BLL�㷽����������Controller�з���
	 * ���룺
	 * ������
	 * ����������
	 */
	bool startAnalyze(char *cpSourceFile,  char *cpTargetFile, int iSliceLength)
	{
		//����BLL��������󣬲�����DAL�����
		CBLLAnalyzeController *pControllerBLL  = new CBLLAnalyzeController(m_pFrameDAL);

		pControllerBLL->startAnalyze(1);
		AfxMessageBox(_T("�������"));
		delete pControllerBLL;
		return true;
	}

	bool startPreAnalyze()
	{
		CBLLAnalyzeController *pControllerBLL  = new CBLLAnalyzeController(m_pFrameDAL);
		pControllerBLL->startPreAnalyze(50);
		return true;
	}


	//������Ҫ���
	//���Ǹ�����Ǹ��ӿڣ�����Ǹ���ť�����������Ϻ���Ǿ�����Ŀ�����CBLLControllerDisplay
	//���Խ����������д��д��ʱ����Կ���CBLLControllerAnalyze�ࣨ����������BLL�����ࣩ
	//bool startGetData()
	//{
	//	CBLLControllerDisplay *pControllerBLL = new CBLLControllerDisplay(m_pFrameDAL);
	//	//pControllerBLL->

	//	delete pControllerBLL;
	//	return true;
	//}
private:
	//DAL�����
	CFrameDAL *m_pFrameDAL;

};

