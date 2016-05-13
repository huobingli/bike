#pragma once
#include"BLLEntityTimeSliceMemory.h"



class CBufPool
{
private:
	CBLLEntityTimeSliceMemory* m_pTimeSliceMemory;	//时间片内存对象

public:
	CBufPool();
	~CBufPool();

	//函数名称：ApplyingTimeSliceMemory
	//参数：无
	//返回值：时间片内存对象
	//描述：申请一个时间片内存对象
	CBLLEntityTimeSliceMemory* ApplyingTimeSliceMemory();
	
	//函数名称：DeletingTiemSliceMemory
	//参数：时间片内存对象
	//返回值：bool
	//描述：释放一个时间内存对象
	bool DeletingTiemSliceMemory(CBLLEntityTimeSliceMemory* pTimeSliceMemory);
	
};

