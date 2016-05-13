#pragma once
#define ARRAY_LENGTH 100		//վ�㼯������ĳ�ʼ��󳤶�
#define EACH_TIME_READ 50		//ÿ�ζ�ȡ�������������мƣ�
#define RECORD_SIZE 77			//ÿ����¼��С
#include<string>
using namespace std;

//���ڣ�2015.7.29
//���ߣ�Ҧ����
//����:�軹��¼ʵ����
class CEntityTripData
{
private: 
	long int m_iStartStationTime;			//��ʼʱ��
	long int m_iStopStationTime;			//����ʱ��
	int m_iStartStationID;					//��ʼվ����
	int m_iStopStationID;					//����վ����
	int m_iCostTime;						//����ʱ��

private:
	void setStartStationTime(string strStartStationTime);			//������ʼվ��ʱ��
	void setStopStationTime(string strStopStationTime);			//���ý���վ��ʱ��
	void setStartStationID(string strStartStationID);				//������ʼվ����
	void setStopStationID(string strStopStationID);				//���ý���վ����
	void setCostTime(string strCostTime);							//���û���ʱ��
	
    /**
    ˵�������ַ�������¼���Էָ�
    ��ڲ�����������Ч�ļ�¼��Ϣ�ַ���
    ����ֵ���Ƿ���³ɹ�
    �����ߣ���
    ����ʱ�䣺2015/10/13*/
	bool translateRecordData(string csRecordData);


public:
	CEntityTripData();
	~CEntityTripData();


    /**
    ˵����ʹ���ֽ����ݸ���
    ������������¼��Ϣ���ַ���
    ����ֵ���Ƿ���³ɹ�
    �����ߣ���
    ����ʱ�䣺2015/10/9*/
	bool update(string strRecord);




	long int getStartStationTime();		//��ȡ��ʼʱ��
	long int getStopStationTime();		//��ȡ����ʱ��
	int getStartStationID();			//��ȡ��ʼվ��ID
	int getStopStationID();				//��ȡ����վ��ID
	int getCostTime();					//��ȡ����ʱ��
	
};


