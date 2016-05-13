#define READNUM 50
#include"EntityTripDataSet.h"
#include"BufPool.h"
#include"BLLEntityOperationSetSet.h"
#include"EntityTimeSliceCountSet.h"
#include"BLLEntityTimeSliceMemorySet.h"


//�ڴ�ģ��
class CBLLModelRecordCount
{
public:
	CBLLModelRecordCount();
	~CBLLModelRecordCount();

private:
	CBufPool* m_pBufPool;									   //�����ָ��
	CBLLEntityTimeSliceMemorySet* m_pTimeSliceMemorySet;	   //ʱ��Ƭ�ڴ��������ָ��

public:
	//�������ƣ�insertingTripData
	//������ʱ��ͳ��Ƭ����,�軹��¼����
	//����ֵ��bool�ͣ���ʾ�����Ƿ�ɹ�
	//���������軹��¼���ϲ����ڴ�ṹ��ת����ʱ��ͳ��Ƭ
	bool insertingTripDataSet(CEntityTimeSliceCountSet* &pTimeSliceCountSet,CEntityTripDataSet* &pTripDataSet);

private:

	//�������ƣ�divingOperation
	//�������軹��¼����ʱ����
	//����ֵ��������¼������
	//���������軹��¼��ʱ��Ƭ����Ϊһ��������¼������
	bool divingOperation(CBLLEntityOperationSetSet* pOperationSetSet,CEntityTripData* pTripData,int iTimeCell);

	//�������ƣ�computingTimeSliceID
	//������ʱ���¼��ʱ����
	//����ֵ��ʱ��Ƭ���
	//����������ʱ��Ƭ���
	int computingTimeSliceID(long int iTime,int iTimeCell);

	//�������ƣ�updatingCurrentTimeSliceID
	//����������������
	//����ֵ����ǰʱ��Ƭ���
	//����:���µ�ǰʱ��Ƭ���
	int updatingCurrentTimeSliceID(CBLLEntityOperationSetSet* pOperationSetSet);


	//�������ƣ�judgingTimeSlice
	//��������ǰʱ��Ƭ��� �����������ʱ����
	//����ֵ��bool�ͣ���ʾ�Ƿ���Ҫ�洢
	//������ͨ����ǰʱ��Ƭ��źͽ������ʱ�����ж��Ƿ���Ҫ�洢
	bool judgingTimeSlice(int iPresentTimeSliceID,int iRentOperationSetTimeSlice);

	//�������ƣ�changeDayInYear
	//�������£���
	//����ֵ��������һ���еĵ�һ��
	//������δ�������꣬���¼�28��
	int changeDayInYear(int iMonth,int iDay);

};
