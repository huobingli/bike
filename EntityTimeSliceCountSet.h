#pragma once
#include"EntityTimeSliceCount.h"
#include"stdlib.h"
#include"string.h"

class CEntityTimeSliceCountNode
{
public:
	CEntityTimeSliceCountNode();
	~CEntityTimeSliceCountNode();
    /**
    说明：获取下一节点
    返回值：下一节点
    创建者：霍*/
    CEntityTimeSliceCountNode *getNextTimeSliceCountNode();
    
    /**
    说明：设置下一节点
    创建者：霍*/
    void setNextTimeSliceCountNode(CEntityTimeSliceCountNode *pNextTimeSliceCountNode);

    /**
    说明：获取时间片数量
    创建者：霍*/
    CEntityTimeSliceCount *getTimeSliceCount();

    /**
    说明：设置时间片数量
    创建者：霍*/
    void setTimeSliceCount(CEntityTimeSliceCount *pTimeSliceCount);

	bool updatingTimeSliceCount(CBLLEntityTimeSliceMemory* pTimeSliceMemory)
{
	m_pTimeSliceCount->setTimeSliceID(pTimeSliceMemory->getTimeSliceID());
	m_pTimeSliceCount->setSurvivalTime(pTimeSliceMemory->getSurvivalTime());
	m_pTimeSliceCount->setArrayLength(pTimeSliceMemory->getArrayLength());
	m_pTimeSliceCount->setArraySize(pTimeSliceMemory->getArraySize()); 
	m_pTimeSliceCount->setStationCount(pTimeSliceMemory->getStationCount());

	return true;
}
private:
	CEntityTimeSliceCount *m_pTimeSliceCount;
	CEntityTimeSliceCountNode *m_pNextTimeSliceCountNode;
};

class CEntityTimeSliceCountSet
{
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
	CEntityTimeSliceCountSet();
	~CEntityTimeSliceCountSet();

public:
	/**
	说明：将时间片统计对象节点插入时间统计链表
	参数：插入元素
	返回值：bool型 表示是否插入成功
	创建者：姚*/
	bool insertTimeSliceCount(CEntityTimeSliceCountNode* pTimeSliceCountNode);

	/**
	说明：获取链表元素个数
	返回值：链表元素个数
	创建者：霍
	*/
	int getNodeNum();

	/**
	说明：获取头节点
	返回值：头节点
	创建者：姚
	*/
	CEntityTimeSliceCountNode* getHeadTimeSliceCountNode();

	/**
	说明：获取二进制数据集合
	参数：无
	返回值：二进制数据集合
	创建者：蔡
	*/
	unsigned char* getBinary();

	/**
	说明：获取二进制数据长度
	参数：无
	返回值：二进制数据长度
	创建者：蔡
	*/
	int getBinaryLength();

	/**
	说明：更新二进制数组
	参数：二进制数组
	返回值：bool型，表示更新是否成功
	创建者：蔡
	*/
	bool update(const unsigned char* chBuffer);

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
	返回值：stringstream
	创建者：姚
	*/
	string changeToStringstream();


bool getLastTimeSliceCountNode(CEntityTimeSliceCountNode* pHeadNode);
private:
	 CEntityTimeSliceCountNode *m_pHeadTimeSliceCountNode;  //头节点  
	 int m_iNodeNum;										//链表元素个数
};

