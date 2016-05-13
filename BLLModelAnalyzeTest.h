#pragma once
#include"EntityTimeSliceCountSet.h"
#include"ListRelationSet.h"
#include"ListWriteRelationSet.h"
#include"BufferPoolBLL.h"
#include"BLLModelEntityTimeSliceCountArray.h"
#include"BLLModelEntityMaxMinTestArray.h"
#include"BLLModelEntityRelationArray.h"
#include <string>
#include<sstream>
#include"iostream"

//数据库连接导入
#include <winsock2.h>
#include "mysql.h"
#pragma comment(lib, "libmysql.lib")
using namespace std;

class CBLLModelAnalyzeTest
{
public:
	CBLLModelAnalyzeTest(int iStationNum);
	~CBLLModelAnalyzeTest();

	//初始化数组
	void initArray();

	void setRelationSet(CListRelationNode *&pListRelationNode);

	//释放数组
	void releaseArray();

	//开始分析
	bool startAnalyze(CEntityTimeSliceCountSet *pEntityTimeSliceCountSet, CListWriteRelationSet *&pListWriteRelationSet);

	//拷贝时间片关系到模型内部数组
	bool copyEntityTimeSliceCountNode(CEntityTimeSliceCountNode *pEntityTimeSliceCountNode);

	//得到关系节点
	bool getRelation(CEntityTimeSliceCountNode *pEntityTimeSliceCountNode, CListRelationNode *&pListRelationNode, double &dMaxRelation, double &dMinRelation);

	//计算两个站点关联关系
	double calculateRelation(int iFirstStation, int iSecondStation);

	//获得iTImeSlice时间片节点中某组关系值
	double getStationRelationOfNode(int iTimeSlice, int iTargetStationID, int iRelationStationID);

	//获取重叠时间片
	void getOverLapTimes(CBLLModelEntityTimeSliceCountArray iFirstCount, CBLLModelEntityTimeSliceCountArray iSecondCount, int &iMinTime, int &iMaxTime);

	//判断生存周期
	bool judgeSurvivalTime(CListWriteRelationSet *&pListWriteRelationSet);

	//转化为写入链表
	bool turnToListWriteRelationSet(int iNodeNum, CListWriteRelationSet *&pListWriteRelationSet);

	//获取剩余模型内集合关系链表
	bool getRestRelationSet(CListWriteRelationSet *&pListWriteRelationSet);

	//字符串输出
	string changeToStringstream();

	//计算生存周期
	int getSurvivalNum(int iSurvivalTime);

	//获得模型内集合关系链表
	CListRelationSet *getListRelationSet();

	//矩阵归100化
	void NormalizeMatrix(CEntityRelationSet *&pEntityRelationSet, double dNormalizeParameter);

	void iteratorGetRelation(CListRelationNode *&pListRelationNode, double &dMaxRelation, double &dMinRelation);
	
	double calculateRelation(int iFirstStation, int iSecondStation, CListRelationNode *pListRelationNode);

	void initMaxMinArray();

	void releaseMaxMinArray();

	void initRelationArray();

	void releaseRelationArray();

	void initStationArray();

	void releaseStationArray();

	/*输出MaxMin数组*/
	string printMaxMinArray()
	{
		stringstream strstreamCount;
		char* cLeft = "(";
		char* cBlank = ",";
		char* cRight = ")";

		/*将各个属性放进字符串*/
		for (int iCount = 0; iCount < m_iTotalStationNum; iCount++)
		{
			strstreamCount << cLeft;
			strstreamCount << m_pMaxMinTestArray[iCount].getMaxStationRelation() << cBlank << m_pMaxMinTestArray[iCount].getMinStationRelation();
			strstreamCount << cRight << "\n";
		}

		/*将stringstream转换成string*/
		string strCount(strstreamCount.str());
		return strCount;
	}

	/*输出统计数据数组*/
	string printArray()
	{
		stringstream strstreamCount;
		char* cLeft = "(";
		char* cBlank = ",";
		char* cRight = ")";

		/*将各个属性放进字符串*/
		for (int iCount = 0; iCount < m_iTotalStationNum; iCount++)
		{
			for (int jCount = 0; jCount < m_iTotalStationNum; jCount++)
			{
				strstreamCount << cLeft;
				strstreamCount << m_pTimeSliceCountArray[iCount][jCount].getMaxTime() << cBlank << m_pTimeSliceCountArray[iCount][jCount].getMinTime()<<cBlank<<m_pTimeSliceCountArray[iCount][jCount].getOperateTimes();
				strstreamCount << cRight;
			}
			strstreamCount << "\n";
		}

		/*将stringstream转换成string*/
		string strCount(strstreamCount.str());
		return strCount;
	}


	/*输出Relation数组*/
	string printRelationArray()
	{
		stringstream strstreamCount;
		char* cLeft = "(";
		char* cBlank = ",";
		char* cRight = ")";

		/*将各个属性放进字符串*/
		for (int iCount = 0; iCount < 5000; iCount++)
		{
			strstreamCount << cLeft;
			strstreamCount << m_pModelEntityRelationArray[iCount].getTargetStation()
				<< cBlank << m_pModelEntityRelationArray[iCount].getRelationStation()
				<< cBlank << m_pModelEntityRelationArray[iCount].getStationRelation()
				<< cBlank << m_pModelEntityRelationArray[iCount].getflag();
			strstreamCount << cRight << "\n";
		}

		/*将stringstream转换成string*/
		string strCount(strstreamCount.str());
		return strCount;
	}
	string printClusterArray()
	{
		stringstream strstreamCount;
		char* cLeft = "(";
		char* cBlank = ",";
		char* cRight = ")";

		/*将各个属性放进字符串*/
		for (int iCount = 0; iCount < 200; iCount++)
		{
			strstreamCount << cLeft;
			strstreamCount << m_pModelEntityStationArray[iCount].getStationID()
				<< cBlank << m_pModelEntityStationArray[iCount].getFlag();
			strstreamCount << cRight << "\n";
		}

		/*将stringstream转换成string*/
		string strCount(strstreamCount.str());
		return strCount;
	}
	//将关系矩阵插入到mysql数据库中
	void insertMatrixIntoMysql(CListRelationNode *pListRelationNode);

	double getRelationOver60(CListRelationNode *pListRelationNode, double iOverNum);

	//void getRelationMatrix();
	void getCluster();
	
private:
	//总体生存周期
	int m_iTotalSurvivalNum;
	//模型内集合关系链表
	CListRelationSet* m_pHeadListRelationSet;
	//站点数
	int m_iTotalStationNum;
	//结构二维数组
	CBLLModelEntityTimeSliceCountArray** m_pTimeSliceCountArray;
	//测试结构数组，用来保存每次的迭代的最大最小值
	CBLLModelEntityMaxMinTestArray* m_pMaxMinTestArray;
	//记录关系值大于某一个临界值的数据数组
	CBLLModelEntityRelationArray* m_pModelEntityRelationArray;

	CBLLModelEntityStationArray*  m_pModelEntityStationArray;
};

struct matrixNode{
	int iRelationID;
	double iStationRelation;
	matrixNode *nextRelationStation;
};

struct matrixArray{
	int iStationID;
	matrixNode *firstmatrixNode;
};