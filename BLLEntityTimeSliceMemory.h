#pragma once
#include"BLLEntityOperationSetSet.h"
#include"EntityStationCount.h"

//ʱ��Ƭ�ڴ����
class CBLLEntityTimeSliceMemory
{
private:
	int m_iTimeSliceID;						//ʱ��Ƭ���
	int m_iSurvivalTime;					//��������
	CEntityStationCount* m_pStationCount;	//վ��ͳ�ƶ�������ָ��
	int m_iArrayLength;						//վ��ͳ�ƶ������鳤��
	int m_iArraySize;						//վ��ͳ�ƶ�������ʵ�ʴ�С�����������

public:
	CBLLEntityTimeSliceMemory();
	CBLLEntityTimeSliceMemory(int iCurrentTimeSliceID);
	~CBLLEntityTimeSliceMemory();

private:
	//�������ƣ�checkingRentOperation
	//��������
	//����ֵ��bool�� true��ʾ�н������false��û��
	//����������Ƿ�����
	bool checkingRentOperation(CBLLEntityOperation* pRentOperation);

	//�������ƣ�checkingReturnOperation
	//��������
	//����ֵ��bool�� true��ʾ�л�������false��û��
	//����������Ƿ񻹲���
	bool checkingReturnOperation(CBLLEntityOperation* pReturnOperation);

public:
	void setArrayLength(int iArrayLength)
	{
		m_iArrayLength = iArrayLength;
	}

	void setArraySize(int iArraySize)
	{
		m_iArraySize = iArraySize;
	}

	void setSurvivalTime(int iSurivalTime)
	{
		m_iSurvivalTime = iSurivalTime;
	}
	int getArrayLength()
	{
		return m_iArrayLength;
	}
	int getArraySize()
	{
		return m_iArraySize;
	}
	//�������ƣ�getTimeSliceID
	//��������
	//����ֵ��ʱ��Ƭ���
	//��������ȡʱ��Ƭ���
	int getTimeSliceID();

	//�������ƣ�getStationCount
	//��������
	//����ֵ��վ��ͳ������ָ��
	//��������ȡվ��ͳ������ָ��
	CEntityStationCount* getStationCount();

	//�������ƣ�setTimeSliceID
	//������ʱ��Ƭ���
	//����ֵ����
	//����������ʱ��Ƭ���
	void setTimeSliceID(int iTimeSliceID);

	//�������ƣ�getSurvivalTime
	//��������
	//����ֵ����������
	//��������ȡ��������
	int getSurvivalTime();

	//�������ƣ�checkStationID
	//������վ����
	//����ֵ��bool
	//�������ڲ���ʱ�ж��Ƿ��Ѿ�������ͬ��վ��
	bool checkStationID(int iStationID);

	//�������ƣ�getStation
	//������վ����
	//����ֵ��վ��ͳ�ƶ���
	//���������������ͬ��վ�㣬����������ȡ����վ��
	CEntityStationCount* getStation(int iStationID);

	//�������ƣ�insertingRentAndReturnOperationSet
	//�������軹������
	//����ֵ��bool��
	//���������軹�����������ʱ��Ƭ�ڴ������
	bool insertingRentAndReturnOperationSet(CBLLEntityOperationSet* pRentAndReturnOperationSet);

	//�������ƣ�insertingRentOperationSet
	//�������������
	//����ֵ��bool��
	//������������������뵽ʱ��Ƭ�ڴ������
	bool insertingRentOperationSet(CBLLEntityOperationSet* pRentOperationSet);

	//�������ƣ�insertingReturnOperationSet
	//��������������
	//����ֵ:bool��
	//�������������������뵽ʱ��Ƭ�ڴ������
	bool insertingReturnOperationSet(CBLLEntityOperationSet* pReturnOperationSet);
};
