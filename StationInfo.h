#pragma once
#include<sstream>
#include<iostream>
 class StationData{
 private:
	int stationId;           //站点ID
	int maxtime;            //最大时间
	int mintime;            //最小时间
	int OperatedTimes;      //操作次数
	int rent;              //借还标记 1为借，0为还
 public:
	StationData()
	{
		maxtime = -1;
		mintime = -1;
		maxtime = -1;
		OperatedTimes = -1;
		rent = -1;
		
	}
	void setId(int StationId)                       //设置站点ID
	{
		stationId = StationId;
	}

	void setMaxtime(int Maxtime)                 //设置最大时间
	{
		maxtime = Maxtime;
	}

	void setMintime(int Mintime)               //设置最小时间
	{
		mintime = Mintime;
	}

	void setOperatedTimes(int operatedTimes)           //设置操作次数
	{
		OperatedTimes = operatedTimes;

	}
	void setRent(int Rent)                     //设置借还标记
	{
		rent = Rent;
	}
	int getId()                                //输出站点ID
	{
		return stationId;
	}
	 
	int getMaxtime()                       //输出最大时间
	{
		return maxtime;
	}

	int getMintime()                      //输出最小时间
	{
		return mintime;
	}

	int getOperatedTimes()                   //输出操作次数
	{
		return OperatedTimes;

	}
	int getRent()                        //输出借还标记
	{
		return rent;
	}


};

class StationInfo{
public:
	 StationData *m_StationData1;     //站点信息数组
	 StationData *m_StationData2;
	 int RecordNum1;       
	 int RecordNum2;   //记录数
	 StationInfo()             //初始化
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
 
