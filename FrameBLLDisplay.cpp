#include "stdafx.h"
#include "FrameBLLDisplay.h"


CFrameBLLDisplay::CFrameBLLDisplay()
{
	m_pFrameDAL = new CFrameDAL();
}


CFrameBLLDisplay::~CFrameBLLDisplay()
{
	delete m_pFrameDAL;
}
