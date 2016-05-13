#pragma once
#include"BLLEntityOperationSet.h"

/*
操作集集合，是一个元素为操作集，数量为2的数组
当借还记录分成操作集时在同一时间片内
m_pOperationSet[0]就作为借还操作集
m_pOperationSet[1]就是一个空元素
当借还记录分成操作集时在两个时间内
m_pOperationSet[0]就作为借操作集
m_pOperationSet[1]就作为还操作集
*/
class CBLLEntityOperationSetSet
{
private:
	CBLLEntityOperationSet* m_pOperationSet;//操作集对象

public:
	CBLLEntityOperationSetSet();
	~CBLLEntityOperationSetSet();

public:
	//函数名称：getOperationSet
	//参数：操作集记号，共两个值0和1,0表示取借还操作集，1表示还操作集
	//返回值：操作集
	//描述：获取操作集
	CBLLEntityOperationSet* getOperationSet(int iOperationMark);

	//函数名称：insertingOperationSet
	//参数：记录标志(bool型，true表示生成一个，false则是两个)，操作记录集
	//返回值：bool,表示是否插入成功
	//描述：插入操作记录集
	bool insertingOperationSet(bool check,CBLLEntityOperationSet* pOperationSet);

	//函数名称：getRentOperationSet
	//参数：无
	//返回值：操作集
	//描述：获取借操作集
	CBLLEntityOperationSet* getRentOperationSet();

	//函数名称：getReturnOperationSet
	//参数：无
	//返回值：操作集
	//描述：获取还操作集
	CBLLEntityOperationSet* getReturnOperationSet();

	//函数名称：checkingRentOperation
	//参数：操作集
	//返回值：bool型，true表示有借操作，false则是没有
	//描述：判断是否有借操作
	bool checkingRentOperation(CBLLEntityOperationSet* pOperationSet);

	//函数名称:isOneTimeSlice
	//参数：无
	//返回值：bool型，true表示同一时间片，false表示不再同一时间片
	//描述：判断该操作集集合结构是（借还集合集，空操作集）或者（借操作集，还操作集）
	bool isOneTimeSlice();
};
