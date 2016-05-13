#pragma once
#include"BLLEntityTimeSliceMemory.h"
#include"EntityStationCount.h"
#include"stdlib.h"
#include"string.h"

//时间片统计实体类
class CEntityTimeSliceCount
{
private:
	int m_iTimeSliceID;                           //时间片序号
    int m_iSurvivalTime;						  //生存周期
	CEntityStationCount* m_pStationCount;       //站点统计对象指针 
	int m_iArrayLength;                           //站点统计对象数组长度
    int m_iArraySize;                             //站点统计对象数组实际大小（对象个数）

    /**
    说明：将传入的整型变量转成二进制类型
    输入：待转整型变量，接收转换后的二进制类型数据的字符串变量
    返回值：是否转化成功
    更新时间：2015/10/21*/
    bool IntegerIntoBinary(const int iNumIn, unsigned char *chBinaryOut);

    /**
    说明：将传入的二进制类型转成整型变量
    输入：二进制类型数据的字符串变量(在内部分配内存)
    返回值：转化成功的整型变量 
    更新时间：2015/10/21*/
    int BinaryIntoInteger(const unsigned char *chBinaryIn);

public:
	CEntityTimeSliceCount();
	~CEntityTimeSliceCount();

	void setStationCount(CEntityStationCount* pStationCount);

    /**
    说明：获取生存周期
    创建者：霍*/
    int getSurvivalTime();

    /**
    说明：设置生存周期
    参数：生存周期
    创建者：霍*/
    void setSurvivalTime(int iSurvivalTime);

	void setTimeSliceID(int iTimeSliceID)
	{
		m_iTimeSliceID = iTimeSliceID;
	}
	int getTimeID()
	{
		return m_iTimeSliceID;
	}
	void setArrayLength(int iArrayLength)
	{
		m_iArrayLength = iArrayLength;
	}
	void setArraySize(int iArraySize)
	{
		m_iArraySize = iArraySize;
	}
	int getArraySize()
	{
		return m_iArraySize;
	}
	
	CEntityStationCount* getStationCount()
	{
		return m_pStationCount;
	}
public:
    /**
    说明：获取本对象转成的二进制数据
    返回值：二进制数据集合
    创建者：蔡
    更新时间：2015/10/21*/
    unsigned char* getBinary();

    /**
    说明：获取本对象转成的二进制数据的长度
    返回值：二进制数据长度
    创建者：蔡
    更新时间：2015/10/21*/
    int getBinaryLength();

    /**
    说明：使用字节数据更新
    参数：更新二进制数组
    返回值：是否更新成功
    创建者：蔡
    更新时间：2015/10/9*/
    bool update(const unsigned char* chBuffer);

	/**
	说明：将时间片内存对象更新到时间统计对象中
	参数：时间片内存对象
	返回值：bool型，表示更新是否成功
	创建者：姚*/
	CEntityTimeSliceCount* updatingTimeSliceCount(CBLLEntityTimeSliceMemory* pTimeSliceMemory);

	/**
	说明：将私有属性转换成char
	参数：无
	返回值：char
	创建者：姚
	*/
	char* changeToChar();

	/**
	说明：将私有属性转换成stringstream
	参数：无
	返回值：无
	创建者：姚
	*/
	string changeToStringstream();

};

