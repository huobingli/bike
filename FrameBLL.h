#pragma once
#include"FrameDAL.h"
#include"BLLControllerAnalyze.h"

class CFrameBLL
{
public:
	CFrameBLL(void)
	{
		//创建DAL对象
		m_pFrameDAL = new CFrameDAL();
	}

	~CFrameBLL(void)
	{
		//释放DAL对象
		delete m_pFrameDAL;
		m_pFrameDAL = NULL;
	}

	/**
	 * 功能：启动BLL层方法，并启动Controller中方法
	 * 传入：
	 * 传出：
	 * 调用条件：
	 */
	bool startAnalyze(char *cpSourceFile,  char *cpTargetFile, int iSliceLength)
	{
		//创建BLL控制类对象，并传入DAL层对象
		CBLLAnalyzeController *pControllerBLL  = new CBLLAnalyzeController(m_pFrameDAL);

		pControllerBLL->startAnalyze(1);
		AfxMessageBox(_T("分析完成"));
		delete pControllerBLL;
		return true;
	}

	bool startPreAnalyze()
	{
		CBLLAnalyzeController *pControllerBLL  = new CBLLAnalyzeController(m_pFrameDAL);
		pControllerBLL->startPreAnalyze(50);
		return true;
	}


	//这里需要完成
	//这是给你的那个接口，点击那个按钮到这个函数，虾米那就是你的控制类CBLLControllerDisplay
	//可以进入这个类来写，写的时候可以看看CBLLControllerAnalyze类（这两个都是BLL控制类）
	//bool startGetData()
	//{
	//	CBLLControllerDisplay *pControllerBLL = new CBLLControllerDisplay(m_pFrameDAL);
	//	//pControllerBLL->

	//	delete pControllerBLL;
	//	return true;
	//}
private:
	//DAL层对象
	CFrameDAL *m_pFrameDAL;

};

