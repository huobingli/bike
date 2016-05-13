#pragma once
#include"BLLEntityOperationSetSet.h"
#include"EntityStationCount.h"

//时间片内存对象
class CBLLEntityTimeSliceMemory
{
private:
	int m_iTimeSliceID;						//时间片序号
	int m_iSurvivalTime;					//生存周期
	CEntityStationCount* m_pStationCount;	//站点统计对象数组指针
	int m_iArrayLength;						//站点统计对象数组长度
	int m_iArraySize;						//站点统计对象数组实际大小（对象个数）

public:
	CBLLEntityTimeSliceMemory();
	CBLLEntityTimeSliceMemory(int iCurrentTimeSliceID);
	~CBLLEntityTimeSliceMemory();

private:
	//函数名称：checkingRentOperation
	//参数：无
	//返回值：bool型 true表示有借操作，false则没有
	//描述：检查是否借操作
	bool checkingRentOperation(CBLLEntityOperation* pRentOperation);

	//函数名称：checkingReturnOperation
	//参数：无
	//返回值：bool型 true表示有还操作，false则没有
	//描述：检查是否还操作
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
	//函数名称：getTimeSliceID
	//参数：无
	//返回值：时间片编号
	//描述：获取时间片编号
	int getTimeSliceID();

	//函数名称：getStationCount
	//参数：无
	//返回值：站点统计数组指针
	//描述：获取站点统计数组指针
	CEntityStationCount* getStationCount();

	//函数名称：setTimeSliceID
	//参数：时间片编号
	//返回值：无
	//描述：设置时间片编号
	void setTimeSliceID(int iTimeSliceID);

	//函数名称：getSurvivalTime
	//参数：无
	//返回值：生存周期
	//描述：获取生存周期
	int getSurvivalTime();

	//函数名称：checkStationID
	//参数：站点编号
	//返回值：bool
	//描述：在插入时判断是否已经存在相同的站点
	bool checkStationID(int iStationID);

	//函数名称：getStation
	//参数：站点编号
	//返回值：站点统计对象
	//描述：如果存在相同的站点，就在数组中取出该站点
	CEntityStationCount* getStation(int iStationID);

	//函数名称：insertingRentAndReturnOperationSet
	//参数：借还操作集
	//返回值：bool型
	//描述：将借还操作集插入的时间片内存对象中
	bool insertingRentAndReturnOperationSet(CBLLEntityOperationSet* pRentAndReturnOperationSet);

	//函数名称：insertingRentOperationSet
	//参数：借操作集
	//返回值：bool型
	//描述：将借操作集插入到时间片内存对象中
	bool insertingRentOperationSet(CBLLEntityOperationSet* pRentOperationSet);

	//函数名称：insertingReturnOperationSet
	//参数：还操作集
	//返回值:bool型
	//描述：将还操作集插入到时间片内存对象中
	bool insertingReturnOperationSet(CBLLEntityOperationSet* pReturnOperationSet);
};
