#pragma once
#include"BLLEntityOperation.h"


//������¼��
class CBLLEntityOperationSet
{
private:
	int m_iTimeSliceID;								//ʱ��Ƭ���
	CBLLEntityOperation* m_pRentOperation;			//�������¼
	CBLLEntityOperation* m_pReturnOperation;	    //��������¼

public:
	//�������ƣ�CBLLEntityOperationSet
	//������ʱ��Ƭ��ţ��������������
	//����ֵ����
	//�������ڽ�����ͻ�������ͬһʱ��Ƭ�����ȥ���������
	CBLLEntityOperationSet(int iTimeSliceID,CBLLEntityOperation* pRentOperation,CBLLEntityOperation* pReturnOperation);
	
	//�������ƣ�CBLLEntityOperationSet
	//������ʱ��Ƭ��ţ�������¼��������־��trueΪ�������falseΪ��������
	//����ֵ����
	//�������ڽ�����ͻ���������ͬһʱ��Ƭ����·ֱ���ݲ�����־ȥ������Ӧʱ��Ƭ�Ĳ�����¼
	CBLLEntityOperationSet(int iTimeSliceID,CBLLEntityOperation* pOperaiotn,bool bCheck);
	CBLLEntityOperationSet();
	~CBLLEntityOperationSet();

public:
	void setTimeSliceID(int iTimeSliceID)
	{
		m_iTimeSliceID = iTimeSliceID;
	}
	//�������ƣ�getTimeSliceID
	//��������
	//����ֵ��ʱ��Ƭ���
	//��������ȡʱ��Ƭ���
	int getTimeSliceID();

	//�������ƣ�getRentOperation
	//��������
	//����ֵ���������¼
	//��������ȡ�������¼
	CBLLEntityOperation* getRentOperation();

	//�������ƣ�getReturnOperation
	//��������
	//����ֵ����������¼
	//��������ȡ��������¼	
	CBLLEntityOperation* getReturnOperation();

	//�������ƣ�checkingRentOperation
	//������������¼
	//����ֵ��bool�ͣ�true��ʾ�У�false����
	//�������ж��Ƿ������
	bool checkingRentOperation(CBLLEntityOperationSet* pOperationSet);


};
