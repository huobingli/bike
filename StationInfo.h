#pragma once
#include<sstream>
#include<iostream>
 class StationData{
 private:
	int stationId;           //վ��ID
	int maxtime;            //���ʱ��
	int mintime;            //��Сʱ��
	int OperatedTimes;      //��������
	int rent;              //�軹��� 1Ϊ�裬0Ϊ��
 public:
	StationData()
	{
		maxtime = -1;
		mintime = -1;
		maxtime = -1;
		OperatedTimes = -1;
		rent = -1;
		
	}
	void setId(int StationId)                       //����վ��ID
	{
		stationId = StationId;
	}

	void setMaxtime(int Maxtime)                 //�������ʱ��
	{
		maxtime = Maxtime;
	}

	void setMintime(int Mintime)               //������Сʱ��
	{
		mintime = Mintime;
	}

	void setOperatedTimes(int operatedTimes)           //���ò�������
	{
		OperatedTimes = operatedTimes;

	}
	void setRent(int Rent)                     //���ý軹���
	{
		rent = Rent;
	}
	int getId()                                //���վ��ID
	{
		return stationId;
	}
	 
	int getMaxtime()                       //������ʱ��
	{
		return maxtime;
	}

	int getMintime()                      //�����Сʱ��
	{
		return mintime;
	}

	int getOperatedTimes()                   //�����������
	{
		return OperatedTimes;

	}
	int getRent()                        //����軹���
	{
		return rent;
	}


};

class StationInfo{
public:
	 StationData *m_StationData1;     //վ����Ϣ����
	 StationData *m_StationData2;
	 int RecordNum1;       
	 int RecordNum2;   //��¼��
	 StationInfo()             //��ʼ��
	 {
		RecordNum1 = -1;
		RecordNum2 = -1;
		m_StationData1 = new StationData[20];
		m_StationData2 = new StationData[20];
		
	 }
	 void setRecordNum1(int recordNum1)
	 {
		 RecordNum1 = recordNum1;
	 }
	 void setRecordNum2(int recordNum2)
	 {
		 RecordNum2 = recordNum2;
	 }
	 void clearData()
	 {
		 delete[] m_StationData1;
		 delete[] m_StationData2;
		 m_StationData1 = new StationData[20];
		 m_StationData2 = new StationData[20];
		 RecordNum1 = -1;
		 RecordNum2 = -1;
	 }
	 ~StationInfo(){
		 delete [] m_StationData1;
		 m_StationData1 = NULL;
		 delete [] m_StationData2;
		 m_StationData2 = NULL;
	 }
};
 
