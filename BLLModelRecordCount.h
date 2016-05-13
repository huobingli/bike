#define READNUM 50
#include"EntityTripDataSet.h"
#include"BufPool.h"
#include"BLLEntityOperationSetSet.h"
#include"EntityTimeSliceCountSet.h"
#include"BLLEntityTimeSliceMemorySet.h"


//内存模型
class CBLLModelRecordCount
{
public:
	CBLLModelRecordCount();
	~CBLLModelRecordCount();

private:
	CBufPool* m_pBufPool;									   //缓冲池指针
	CBLLEntityTimeSliceMemorySet* m_pTimeSliceMemorySet;	   //时间片内存对象链表指针

public:
	//函数名称：insertingTripData
	//参数：时间统计片集合,借还记录集合
	//返回值：bool型，表示插入是否成功
	//描述：将借还记录集合插入内存结构并转换成时间统计片
	bool insertingTripDataSet(CEntityTimeSliceCountSet* &pTimeSliceCountSet,CEntityTripDataSet* &pTripDataSet);

private:

	//函数名称：divingOperation
	//参数：借还记录对象，时间间隔
	//返回值：操作记录集集合
	//描述：将借还记录按时间片划分为一个操作记录集集合
	bool divingOperation(CBLLEntityOperationSetSet* pOperationSetSet,CEntityTripData* pTripData,int iTimeCell);

	//函数名称：computingTimeSliceID
	//参数：时间记录，时间间隔
	//返回值：时间片编号
	//描述：计算时间片编号
	int computingTimeSliceID(long int iTime,int iTimeCell);

	//函数名称：updatingCurrentTimeSliceID
	//参数：操作集集合
	//返回值：当前时间片编号
	//描述:更新当前时间片编号
	int updatingCurrentTimeSliceID(CBLLEntityOperationSetSet* pOperationSetSet);


	//函数名称：judgingTimeSlice
	//参数：当前时间片编号 借操作操作集时间编号
	//返回值：bool型，表示是否需要存储
	//描述：通过当前时间片编号和借操作集时间编号判断是否需要存储
	bool judgingTimeSlice(int iPresentTimeSliceID,int iRentOperationSetTimeSlice);

	//函数名称：changeDayInYear
	//参数：月，日
	//返回值：该天是一年中的第一天
	//描述：未考虑闰年，二月计28天
	int changeDayInYear(int iMonth,int iDay);

};
