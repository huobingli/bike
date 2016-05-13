#pragma once
#include"FrameBLL.h"
/**
 * 功能：
 * 传入：
 * 传出：
 * 调用条件：
 */
class CFrameUI
{
public:
	CFrameUI(void)
	{
		AfxMessageBox(_T("UI"));
		m_pFrameBLL = new CFrameBLL();
		
	}

	~CFrameUI(void)
	{
		delete m_pFrameBLL;
		
	}

	/**
	 * 功能：设置启动参数,并临时保存在UI中
	 * 传入：源文件名，目标文件名，时间片长度
	 * 传出：是否设置成功（bool）
	 * 调用条件：
	 */
	bool setParameter(char *cpSourceFile, char *cpTargetFile, int iSliceLength)
	{
		m_pSourceFile = cpSourceFile;
		m_pTargetFile = cpTargetFile;
		m_iSliceLength = iSliceLength;

		return true;
	}

	/**
	 * 功能：启动UI层方法，内部启动BLL层方法
	 * 传入：
	 * 传出：是否执行成功（bool）
	 * 调用条件：
	 */
	bool startAnalyze()
	{
		return m_pFrameBLL->startAnalyze(m_pSourceFile, m_pTargetFile, m_iSliceLength);
	}

	/**
	* 功能：启动UI层方法，内部启动BLL层方法
	* 传入：
	* 传出：是否执行成功（bool）
	* 调用条件：
	*/
	bool startPreAnalyze()
	{
		return m_pFrameBLL->startPreAnalyze();
	}

private:
	//BLL层对象
	CFrameBLL *m_pFrameBLL;

	//源文件文件名
	char *m_pSourceFile;
	//目标文件文件名
	char *m_pTargetFile;
	//时间片长度
	int m_iSliceLength;
};

