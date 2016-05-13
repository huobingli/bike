#pragma once
#include"EntityCount.h"
#include"BLLEntityOperation.h"
#include "stdlib.h"
#include "string.h"

//站点统计对象
class CEntityStationCount
{
private:
	int m_iStationID;					//站点编号
	CEntityCount* m_pRentCount;			//借车统计对象数组
	CEntityCount* m_pReturnCount;		//还车统计对象数组
	int m_iRentArrayLength;				//借车统计对象数组长度
	int m_iReturnArrayLength;			//还车统计对象数组长度
    int m_iRentArraySize;               //借车统计对象数组大小
    int m_iReturnArraySize;             //还车统计对象数组大小

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
	CEntityStationCount();
	~CEntityStationCount();

private:
	//函数名称：initArray
	//参数：数组长度
	//返回值：无
	//描述：初始化统计对象数组
	void initArray(int iArrayLength);

public:
	CEntityCount* getRent();
	CEntityCount* getReturn();
	void setRentArrayLength(int iRentArrayLength)
	{
		m_iRentArrayLength = iRentArrayLength;
	}
	void setReturnArrayLength(int iReturnArrayLength)
	{
		m_iReturnArrayLength = iReturnArrayLength;
	}

	void setRentArraySize(int iRentArraySize)
	{
		m_iRentArraySize = iRentArraySize;
	}

	void setReturnArraySize(int iReturnArraySize)
	{
		m_iReturnArraySize = iReturnArraySize;
	}

	int getRentArrayLength()
	{
		return m_iRentArrayLength;
	}
	int getReturnArrayLength()
	{
		return m_iReturnArrayLength;
	}

	/**
	说明：获得借车统计对象数组实际大小
	返回值：借车统计对象数组实际大小
	创建者：姚*/
	int getRentArraySize();

	/**
	说明：获得还车统计对象数组实际大小
	返回值：还车统计对象数组实际大小
	创建者：姚*/
	int getReturnArraySize();

	/**
	说明：设置站点编号
	参数：站点编号
	返回值：无
	创建者：姚*/
	void setStationID(int iStationID);


	/**
	说明：将借操作更新到借车统计记录里
	参数：借操作
	返回值：无
	创建者：姚*/
	void setRentCount(CBLLEntityOperation* pRentOperation);

	/**
	说明：将还操作更新到还车统计记录里
	参数：还操作
	返回值：无
	创建者：姚*/
	void setReturnCount(CBLLEntityOperation* pReturnOperation);
	

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
	说明：将私有属性转换成char
	参数：无
	返回值：char
	创建者：姚
	更新时间：2015/11/6
	*/
	char* changeToChar();

	/**
	说明：获取站点编号
	参数：无
	返回值：int
	创建者：姚
	更新时间：2015/11/8
	*/
	int getStationID();

	/**
	说明：将私有属性转换成stringstream
	参数：无
	返回值：stringstream
	创建者：姚
	更新时间：2015/11/9
	*/
	string changeToStrstream();

	/**
	说明：检查在借统计中是否存在相同的关联站点
	参数：关联站点编号
	创建者：姚
	更新时间：2015/11/9
	*/
	bool checkRentRelatedStationID(int iRelatedStationID);

	/**
	说明：检查在还统计中是否存在相同的关联站点
	参数：关联站点编号
	创建者：姚
	更新时间：2015/11/9
	*/
	bool checkReturnRelatedStationID(int iRelatedStationID);
	/**
	说明：获取指定借操作关联站点
	参数：关联站点编号
	创建者：姚
	更新时间：2015/11/9
	*/
	CEntityCount* getRentCount(int iRelatedStationID);

	CEntityCount* getRentCount()
	{
		return m_pRentCount;
	}

	/**
	说明：获取指定还操作关联站点
	参数：关联站点编号
	创建者：姚
	更新时间：2015/11/9
	*/
	CEntityCount* getReturnCount(int iRelatedStationID);

	CEntityCount* getReturnCount()
	{
		return m_pReturnCount;
	}

};


