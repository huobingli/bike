#pragma once
#include"EntityTripData.h"

//日期：2015.7.29
//作者：姚鑫涛
//描述：借还记录集合，被控制类CBLLCtrRelationOfTimeSliceStation，调用
//		旅行信息实体类CEntityTripData
class CEntityTripDataSet
{
public:
	CEntityTripDataSet();	
	~CEntityTripDataSet();

private:
	CEntityTripData* m_CSexample;		//指向站记录集合内存块
	int m_iArrayLength;					//集合大小
	int m_iArraySize;					//集合长度
	int m_iPos;							//记录集合内存存储指针
	int m_iEachNumStation;				//每次扩充数组的长度
	int EachNumStation;

public:

    /**
    说明：获取当前存储的记录数目
    返回值：元素个数
    创建者：蔡*/
    int & gettingSize();

    /**
    说明：判断记录集合是否为空
    创建者：蔡*/
    bool isEmpty() const;

    /**
    说明：判断数组是否已满
    创建者：蔡*/
    bool isEnd() const;

    /**
    说明：返回记录数组
    返回值：记录数组（实际的存储记录内存地址），引用传参
    创建者：蔡*/
    CEntityTripData *& linkRecord();

    /**
    说明:扩充数组
    创建者：蔡*/
    CEntityTripData *& biggerRecordSet();

	/**
	说明：获取第一条借还记录
	创建者：姚
	*/
	CEntityTripData* getFirst();

	/**
	说明：获取下一条借还记录
	创建者：姚
	*/
	CEntityTripData* getNext();

	/**
	说明：判断下标是否到了最后
	创建者:姚
	*/
	bool isEnd();

};

