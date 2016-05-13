#include"stdafx.h"
#include"BufPool.h"

CBufPool::CBufPool()
{
	m_pTimeSliceMemory = new CBLLEntityTimeSliceMemory[5];
}

CBufPool::~CBufPool()
{
	delete [] m_pTimeSliceMemory;
}

CBLLEntityTimeSliceMemory* CBufPool::ApplyingTimeSliceMemory()
{
	CBLLEntityTimeSliceMemory* pTimeSliceMemory = new CBLLEntityTimeSliceMemory();
	return pTimeSliceMemory;
}

bool CBufPool::DeletingTiemSliceMemory(CBLLEntityTimeSliceMemory* pTimeSliceMemory)
{
	delete pTimeSliceMemory;
	return true;
}
