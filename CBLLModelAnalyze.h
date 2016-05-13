#pragma once
#include"EntityTimeSliceCountSet.h"
#include"ListRelationSet.h"
#include"ListWriteRelationSet.h"
#include"BufferPoolBLL.h"
#include"BLLModelEntityTimeSliceCountArray.h"
//#include"FrameDAL.h"


class CBLLModelAnalyze
{
public:
	/**
    说明：model构造函数，初始化model中一些参数变量
    参数：站点个数
    返回值：
    更新时间：*/
	CBLLModelAnalyze(int iStationNum);


	~CBLLModelAnalyze();


	/**
    说明：初始化model中内部数组，准备使用
    参数：
    返回值：
    更新时间：*/
	void initArray();


	/**
    说明：释放model中内部数组，用于下一次使用
    参数：
    返回值：
    更新时间：*/
	void releaseArray();
	

	/**
    说明：model中主要分析方法，每次传入一个统计集合链表，经过处理返回需要写入的关系集合链表
    参数：统计集合链表（链表形式）， （引用传入）写入集合链表（链表形式）
    返回值：（引用传出）写入集合链表（链表形式）
    更新时间：*/
	bool startAnalyze(CEntityTimeSliceCountSet *pEntityTimeSliceCountSet, CListWriteRelationSet *&pListWriteRelationSet);


	/**
    说明：拷贝统计集合，将原先统计集合放入内存模型的数组中
    参数：时间片统计集合
    返回值：
    更新时间：*/
	bool copyEntityTimeSliceCountNode(CEntityTimeSliceCountNode *pEntityTimeSliceCountNode);
	

	/**
    说明：将时间片统计集合进行计算，得出当前时间片对象的关系集合
    参数：时间片统计集合
    返回值：
    更新时间：*/
	bool getRelation(CEntityTimeSliceCountNode *pEntityTimeSliceCountNode);
	

	/**
    说明：计算两个站点之间的相似度（两个站点不为同一个站点）
    参数：第一个站点，第二个站点
    返回值：两个站点相似度
    更新时间：*/
	double calculateRelation(int iFirstStation, int iSecondStation);
	

	/**
    说明：获取主链表中的关系集合内部的站点关系值
    参数：时间片ID，目标站点，关联站点
    返回值：站点关系值
    更新时间：*/
	double getStationRelationOfNode(int iTimeSlice, int iTargetStationID, int iRelationStationID);
	

	/**
    说明：得到重叠时间片
    参数：第一个站点，第二个站点，最小时间编号，最大时间编号
    返回值：引用传出最小时间编号，引用传出最大时间编号
    更新时间：*/
	void getOverLapTimes(CBLLModelEntityTimeSliceCountArray iFirstCount, CBLLModelEntityTimeSliceCountArray iSecondCount, int &iMinTime, int &iMaxTime);
	
	
	/**
    说明：将模型内部的时间片关系集合链表进行判断，若链表中存在生存周期小于model总体生存周期的，返回上层BLL控制类
    参数：引用传入返回BLL层控制类的关系数据链表
    返回值：引用返回
    更新时间：*/
	bool judgeSurvivalTime(CListWriteRelationSet *&pListWriteRelationSet);
	

	/**
    说明：将内存模型中的链表形式转换成可以传入DAL层的链表形式（即将ListRelationSet 转换成ListWriteRelationSet）
    参数：内存模型中链表读取个数（int），（引用传入）传入DAL层链表（链表形式）
    返回值：（引用传出）传入DAL层链表（链表形式）
    更新时间：*/
	bool turnToListWriteRelationSet(int iNodeNum, CListWriteRelationSet *&pListWriteRelationSet);
	

	bool  getRestRelationSet(CListWriteRelationSet *&pListWriteRelationSet)
	{
		turnToListWriteRelationSet(m_pHeadListRelationSet->getNodeNum(),pListWriteRelationSet);
		return true;
	}

	/**
    说明：获得数组的字符串形式
    参数：
    返回值：数组字符串
    更新时间：*/
	string changeToStringstream();


	int getSurvivalNum(int iSurvivalTime)
	{
		return (iSurvivalTime / 20 + 1);
	}
	CListRelationSet *getListRelationSet()
	{
		return m_pHeadListRelationSet;
	}

	/**
	 *归一化矩阵
	 */
	void NormalizeMatrix(CEntityRelationSet *&pEntityRelationSet, double dNormalizeParameter);


	

private:
	//总体生存周期
	int m_iTotalSurvivalNum;
	//模型内部时间片关系集合链表
	CListRelationSet *m_pHeadListRelationSet;
	//缓冲池对象
	CBufferPoolBLL *m_pBufferPool;
	//总站点个数
	int m_iTotalStationNum;
	//结构二维数组
	CBLLModelEntityTimeSliceCountArray **m_pTimeSliceCountArray;
};

