#pragma once
#include<sstream>
using namespace std;

//统计对象
class CEntityCount
{
private:
	int m_iRelatedStationID;	//关联站点
	int m_iMaxCostTime;			//最大花费时间
	int m_iMinCostTime;			//最小花费时间
	int m_iOperatedTimes;		//操作次数

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
	CEntityCount();
	~CEntityCount();

public:

	/**
	说明：获取属性方法
	创建者：姚
	*/
	int getMaxCostTime();

	int getMinCostTime()
	{
		return m_iMinCostTime;
	}

	int getOperatedTimes()
	{
		return m_iOperatedTimes;
	}
	/**
	说明：设置属性方法
	创建者：姚
	*/
	void setRelatedStationID(int relatedStationID);
	void setMaxCostTime(int costTime);
	void setMinCostTime(int costTime);
	void setOperatedTimes();

public:
    /**
    说明：获取本对象的二进制格式数据
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
	说明：将私有属性转换成char*
	参数：无
	返回值：char*数组
	创建者：姚
	更新时间：2015/11/6
	*/
	char* changeToChar();

	/**
	说明：将私有属性转换成stringstream
	参数：无
	创建者：姚
	更新时间：2015/11/9
	*/
	string changeToStrstream();

	/**
	说明：获取关联站点编号
	参数：无
	创建：要
	更新时间：2015/11/9
	*/
	int getRelatedStationID();
};
