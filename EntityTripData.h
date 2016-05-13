#pragma once
#define ARRAY_LENGTH 100		//站点集合数组的初始最大长度
#define EACH_TIME_READ 50		//每次读取的数据量（按行计）
#define RECORD_SIZE 77			//每条记录大小
#include<string>
using namespace std;

//日期：2015.7.29
//作者：姚鑫涛
//描述:借还记录实体类
class CEntityTripData
{
private: 
	long int m_iStartStationTime;			//起始时间
	long int m_iStopStationTime;			//结束时间
	int m_iStartStationID;					//起始站点编号
	int m_iStopStationID;					//结束站点编号
	int m_iCostTime;						//花费时间

private:
	void setStartStationTime(string strStartStationTime);			//设置起始站点时间
	void setStopStationTime(string strStopStationTime);			//设置结束站点时间
	void setStartStationID(string strStartStationID);				//设置起始站点编号
	void setStopStationID(string strStopStationID);				//设置结束站点编号
	void setCostTime(string strCostTime);							//设置花费时间
	
    /**
    说明：将字符串按记录属性分割
    入口参数：包含有效的记录信息字符串
    返回值：是否更新成功
    创建者：蔡
    更新时间：2015/10/13*/
	bool translateRecordData(string csRecordData);


public:
	CEntityTripData();
	~CEntityTripData();


    /**
    说明：使用字节数据更新
    参数：包含记录信息的字符串
    返回值：是否更新成功
    创建者：蔡
    更新时间：2015/10/9*/
	bool update(string strRecord);




	long int getStartStationTime();		//获取起始时间
	long int getStopStationTime();		//获取结束时间
	int getStartStationID();			//获取起始站点ID
	int getStopStationID();				//获取结束站点ID
	int getCostTime();					//获取花费时间
	
};


