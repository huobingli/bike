#pragma once
#include"BLLEntityOperation.h"


//操作记录集
class CBLLEntityOperationSet
{
private:
	int m_iTimeSliceID;								//时间片序号
	CBLLEntityOperation* m_pRentOperation;			//借操作记录
	CBLLEntityOperation* m_pReturnOperation;	    //还操作记录

public:
	//函数名称：CBLLEntityOperationSet
	//参数：时间片编号，借操作，还操作
	//返回值：无
	//描述：在借操作和还操作在同一时间片情况下去构造操作集
	CBLLEntityOperationSet(int iTimeSliceID,CBLLEntityOperation* pRentOperation,CBLLEntityOperation* pReturnOperation);
	
	//函数名称：CBLLEntityOperationSet
	//参数：时间片编号，操作记录，操作标志（true为借操作，false为还操作）
	//返回值：无
	//描述：在借操作和还操作不在同一时间片情况下分别根据操作标志去创建对应时间片的操作记录
	CBLLEntityOperationSet(int iTimeSliceID,CBLLEntityOperation* pOperaiotn,bool bCheck);
	CBLLEntityOperationSet();
	~CBLLEntityOperationSet();

public:
	void setTimeSliceID(int iTimeSliceID)
	{
		m_iTimeSliceID = iTimeSliceID;
	}
	//函数名称：getTimeSliceID
	//参数：无
	//返回值：时间片编号
	//描述：获取时间片编号
	int getTimeSliceID();

	//函数名称：getRentOperation
	//参数：无
	//返回值：借操作记录
	//描述：获取借操作记录
	CBLLEntityOperation* getRentOperation();

	//函数名称：getReturnOperation
	//参数：无
	//返回值：还操作记录
	//描述：获取还操作记录	
	CBLLEntityOperation* getReturnOperation();

	//函数名称：checkingRentOperation
	//参数：操作记录
	//返回值：bool型，true表示有，false则无
	//描述：判断是否存借操作
	bool checkingRentOperation(CBLLEntityOperationSet* pOperationSet);


};
