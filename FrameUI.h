#pragma once
#include"FrameBLL.h"
/**
 * ���ܣ�
 * ���룺
 * ������
 * ����������
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
	 * ���ܣ�������������,����ʱ������UI��
	 * ���룺Դ�ļ�����Ŀ���ļ�����ʱ��Ƭ����
	 * �������Ƿ����óɹ���bool��
	 * ����������
	 */
	bool setParameter(char *cpSourceFile, char *cpTargetFile, int iSliceLength)
	{
		m_pSourceFile = cpSourceFile;
		m_pTargetFile = cpTargetFile;
		m_iSliceLength = iSliceLength;

		return true;
	}

	/**
	 * ���ܣ�����UI�㷽�����ڲ�����BLL�㷽��
	 * ���룺
	 * �������Ƿ�ִ�гɹ���bool��
	 * ����������
	 */
	bool startAnalyze()
	{
		return m_pFrameBLL->startAnalyze(m_pSourceFile, m_pTargetFile, m_iSliceLength);
	}

	/**
	* ���ܣ�����UI�㷽�����ڲ�����BLL�㷽��
	* ���룺
	* �������Ƿ�ִ�гɹ���bool��
	* ����������
	*/
	bool startPreAnalyze()
	{
		return m_pFrameBLL->startPreAnalyze();
	}

private:
	//BLL�����
	CFrameBLL *m_pFrameBLL;

	//Դ�ļ��ļ���
	char *m_pSourceFile;
	//Ŀ���ļ��ļ���
	char *m_pTargetFile;
	//ʱ��Ƭ����
	int m_iSliceLength;
};

