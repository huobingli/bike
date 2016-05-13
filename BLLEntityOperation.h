#pragma once
#include"EntityTripData.h"

//描述：操作记录实体类
class CBLLEntityOperation
{
public:
	
	//函数名称：CBLLEntityOperation
	//参数：时间片编号,操作类型
	//返回值：无
	//描述：通过操作类型构造操作记录
	CBLLEntityOperation(int iTimeSliceID,bool bOpertedType);
	CBLLEntityOperation();
	~CBLLEntityOperation();

private:
	int	m_iTimeSliceID;			//时间片序号
	bool m_bOperatedType;		//操作类型
	int	 m_iOperatedStationID;	//操作站点编号
	int m_iRelatedStationID;	//关联站点编号
	int m_iCostTime;			//花费时间

public:
	
	//函数名：setTimeSliceID
	//参数：时间片序号
	//返回值：无
	//描述：设置时间片序号
	void setTimeSliceID(int iTimeSliceID);

	//函数名：setOperateType
	//参数：操作类型
	//返回值：无
	//描述：设置操作类型
	void setOperateType(bool bOperatedType);

	//函数名：setOperateStationID
	//参数：操作站点编号
	//返回值：无
	//描述：设置操作站点编号
	void setOperateStationID(int iOperatedStationID);

	//函数名：setRelateStationID
	//参数：关联站点编号
	//返回值：无
	//描述：设置关联站点编号
	void setRelatedStationID(int iRelatedStationID);

	//函数名：setCostTime
	//参数：花费时间
	//返回值：无
	//描述：设置花费时间
	void setCostTime(int iCostTime);

	//函数名称：updatingRentOperation
	//参数：借还记录
	//返回值：无
	//描述：更新借操作记录
	void updatingRentOperation(CEntityTripData* pTripData);

	//函数名称：updatingReturnOperation
	//参数：借还记录
	//返回值：无
	//描述：更新还操作记录
	void updatingReturnOperation(CEntityTripData* pTripData);

	//函数名称：getTimeSliceID
	//参数：无
	//返回值：时间片编号
	//描述：获取时间片编号
	int getTimeSliceID();

	//函数名称：getOperateStationID
	//参数：无
	//返回值：操作站点编号
	//描述：获取操作站点编号
	int getOperatedStationID();

	//函数名称：getRelatedStationID
	//参数：无
	//返回值：关联站点编号
	//描述：获取关联站点编号
	int getRelatedStationID();

	//函数名称：getCostTime
	//参数：无
	//返回值：花费时间
	//描述：获取花费时间
	int getCostTime();

	//函数名称：getOperatedType
	//参数：无
	//返回值：bool型，true表示借操作，false则是还操作
	//描述：获取操作类型
	bool getOperatedType();


	//函数名称：updatingOperationByOperation
	//参数：操作集
	//返回值：bool
	//描述：通过操作集更新借还操作集，在区分操作集时被调用
	bool updatingOperationByOperation(CBLLEntityOperation* pOperation);
};
