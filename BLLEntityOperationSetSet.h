#pragma once
#include"BLLEntityOperationSet.h"

/*
���������ϣ���һ��Ԫ��Ϊ������������Ϊ2������
���軹��¼�ֳɲ�����ʱ��ͬһʱ��Ƭ��
m_pOperationSet[0]����Ϊ�軹������
m_pOperationSet[1]����һ����Ԫ��
���軹��¼�ֳɲ�����ʱ������ʱ����
m_pOperationSet[0]����Ϊ�������
m_pOperationSet[1]����Ϊ��������
*/
class CBLLEntityOperationSetSet
{
private:
	CBLLEntityOperationSet* m_pOperationSet;//����������

public:
	CBLLEntityOperationSetSet();
	~CBLLEntityOperationSetSet();

public:
	//�������ƣ�getOperationSet
	//�������������Ǻţ�������ֵ0��1,0��ʾȡ�軹��������1��ʾ��������
	//����ֵ��������
	//��������ȡ������
	CBLLEntityOperationSet* getOperationSet(int iOperationMark);

	//�������ƣ�insertingOperationSet
	//��������¼��־(bool�ͣ�true��ʾ����һ����false��������)��������¼��
	//����ֵ��bool,��ʾ�Ƿ����ɹ�
	//���������������¼��
	bool insertingOperationSet(bool check,CBLLEntityOperationSet* pOperationSet);

	//�������ƣ�getRentOperationSet
	//��������
	//����ֵ��������
	//��������ȡ�������
	CBLLEntityOperationSet* getRentOperationSet();

	//�������ƣ�getReturnOperationSet
	//��������
	//����ֵ��������
	//��������ȡ��������
	CBLLEntityOperationSet* getReturnOperationSet();

	//�������ƣ�checkingRentOperation
	//������������
	//����ֵ��bool�ͣ�true��ʾ�н������false����û��
	//�������ж��Ƿ��н����
	bool checkingRentOperation(CBLLEntityOperationSet* pOperationSet);

	//��������:isOneTimeSlice
	//��������
	//����ֵ��bool�ͣ�true��ʾͬһʱ��Ƭ��false��ʾ����ͬһʱ��Ƭ
	//�������жϸò��������Ͻṹ�ǣ��軹���ϼ����ղ����������ߣ��������������������
	bool isOneTimeSlice();
};
