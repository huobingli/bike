#pragma once
#include"BLLEntityTimeSliceMemory.h"



class CBufPool
{
private:
	CBLLEntityTimeSliceMemory* m_pTimeSliceMemory;	//ʱ��Ƭ�ڴ����

public:
	CBufPool();
	~CBufPool();

	//�������ƣ�ApplyingTimeSliceMemory
	//��������
	//����ֵ��ʱ��Ƭ�ڴ����
	//����������һ��ʱ��Ƭ�ڴ����
	CBLLEntityTimeSliceMemory* ApplyingTimeSliceMemory();
	
	//�������ƣ�DeletingTiemSliceMemory
	//������ʱ��Ƭ�ڴ����
	//����ֵ��bool
	//�������ͷ�һ��ʱ���ڴ����
	bool DeletingTiemSliceMemory(CBLLEntityTimeSliceMemory* pTimeSliceMemory);
	
};

