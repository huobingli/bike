
// station_3.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// Cstation_3App:
// �йش����ʵ�֣������ station_3.cpp
//

class Cstation_3App : public CWinApp
{
public:
	Cstation_3App();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern Cstation_3App theApp;