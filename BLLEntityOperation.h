#pragma once
#include"EntityTripData.h"

//������������¼ʵ����
class CBLLEntityOperation
{
public:
	
	//�������ƣ�CBLLEntityOperation
	//������ʱ��Ƭ���,��������
	//����ֵ����
	//������ͨ���������͹��������¼
	CBLLEntityOperation(int iTimeSliceID,bool bOpertedType);
	CBLLEntityOperation();
	~CBLLEntityOperation();

private:
	int	m_iTimeSliceID;			//ʱ��Ƭ���
	bool m_bOperatedType;		//��������
	int	 m_iOperatedStationID;	//����վ����
	int m_iRelatedStationID;	//����վ����
	int m_iCostTime;			//����ʱ��

public:
	
	//��������setTimeSliceID
	//������ʱ��Ƭ���
	//����ֵ����
	//����������ʱ��Ƭ���
	void setTimeSliceID(int iTimeSliceID);

	//��������setOperateType
	//��������������
	//����ֵ����
	//���������ò�������
	void setOperateType(bool bOperatedType);

	//��������setOperateStationID
	//����������վ����
	//����ֵ����
	//���������ò���վ����
	void setOperateStationID(int iOperatedStationID);

	//��������setRelateStationID
	//����������վ����
	//����ֵ����
	//���������ù���վ����
	void setRelatedStationID(int iRelatedStationID);

	//��������setCostTime
	//����������ʱ��
	//����ֵ����
	//���������û���ʱ��
	void setCostTime(int iCostTime);

	//�������ƣ�updatingRentOperation
	//�������軹��¼
	//����ֵ����
	//���������½������¼
	void updatingRentOperation(CEntityTripData* pTripData);

	//�������ƣ�updatingReturnOperation
	//�������軹��¼
	//����ֵ����
	//���������»�������¼
	void updatingReturnOperation(CEntityTripData* pTripData);

	//�������ƣ�getTimeSliceID
	//��������
	//����ֵ��ʱ��Ƭ���
	//��������ȡʱ��Ƭ���
	int getTimeSliceID();

	//�������ƣ�getOperateStationID
	//��������
	//����ֵ������վ����
	//��������ȡ����վ����
	int getOperatedStationID();

	//�������ƣ�getRelatedStationID
	//��������
	//����ֵ������վ����
	//��������ȡ����վ����
	int getRelatedStationID();

	//�������ƣ�getCostTime
	//��������
	//����ֵ������ʱ��
	//��������ȡ����ʱ��
	int getCostTime();

	//�������ƣ�getOperatedType
	//��������
	//����ֵ��bool�ͣ�true��ʾ�������false���ǻ�����
	//��������ȡ��������
	bool getOperatedType();


	//�������ƣ�updatingOperationByOperation
	//������������
	//����ֵ��bool
	//������ͨ�����������½軹�������������ֲ�����ʱ������
	bool updatingOperationByOperation(CBLLEntityOperation* pOperation);
};
