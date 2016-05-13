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

//���ݿ����ӵ���
#include <winsock2.h>
#include "mysql.h"
#pragma comment(lib, "libmysql.lib")
using namespace std;

class CBLLModelAnalyzeTest
{
public:
	CBLLModelAnalyzeTest(int iStationNum);
	~CBLLModelAnalyzeTest();

	//��ʼ������
	void initArray();

	void setRelationSet(CListRelationNode *&pListRelationNode);

	//�ͷ�����
	void releaseArray();

	//��ʼ����
	bool startAnalyze(CEntityTimeSliceCountSet *pEntityTimeSliceCountSet, CListWriteRelationSet *&pListWriteRelationSet);

	//����ʱ��Ƭ��ϵ��ģ���ڲ�����
	bool copyEntityTimeSliceCountNode(CEntityTimeSliceCountNode *pEntityTimeSliceCountNode);

	//�õ���ϵ�ڵ�
	bool getRelation(CEntityTimeSliceCountNode *pEntityTimeSliceCountNode, CListRelationNode *&pListRelationNode, double &dMaxRelation, double &dMinRelation);

	//��������վ�������ϵ
	double calculateRelation(int iFirstStation, int iSecondStation);

	//���iTImeSliceʱ��Ƭ�ڵ���ĳ���ϵֵ
	double getStationRelationOfNode(int iTimeSlice, int iTargetStationID, int iRelationStationID);

	//��ȡ�ص�ʱ��Ƭ
	void getOverLapTimes(CBLLModelEntityTimeSliceCountArray iFirstCount, CBLLModelEntityTimeSliceCountArray iSecondCount, int &iMinTime, int &iMaxTime);

	//�ж���������
	bool judgeSurvivalTime(CListWriteRelationSet *&pListWriteRelationSet);

	//ת��Ϊд������
	bool turnToListWriteRelationSet(int iNodeNum, CListWriteRelationSet *&pListWriteRelationSet);

	//��ȡʣ��ģ���ڼ��Ϲ�ϵ����
	bool getRestRelationSet(CListWriteRelationSet *&pListWriteRelationSet);

	//�ַ������
	string changeToStringstream();

	//������������
	int getSurvivalNum(int iSurvivalTime);

	//���ģ���ڼ��Ϲ�ϵ����
	CListRelationSet *getListRelationSet();

	//�����100��
	void NormalizeMatrix(CEntityRelationSet *&pEntityRelationSet, double dNormalizeParameter);

	void iteratorGetRelation(CListRelationNode *&pListRelationNode, double &dMaxRelation, double &dMinRelation);
	
	double calculateRelation(int iFirstStation, int iSecondStation, CListRelationNode *pListRelationNode);

	void initMaxMinArray();

	void releaseMaxMinArray();

	void initRelationArray();

	void releaseRelationArray();

	void initStationArray();

	void releaseStationArray();

	/*���MaxMin����*/
	string printMaxMinArray()
	{
		stringstream strstreamCount;
		char* cLeft = "(";
		char* cBlank = ",";
		char* cRight = ")";

		/*���������ԷŽ��ַ���*/
		for (int iCount = 0; iCount < m_iTotalStationNum; iCount++)
		{
			strstreamCount << cLeft;
			strstreamCount << m_pMaxMinTestArray[iCount].getMaxStationRelation() << cBlank << m_pMaxMinTestArray[iCount].getMinStationRelation();
			strstreamCount << cRight << "\n";
		}

		/*��stringstreamת����string*/
		string strCount(strstreamCount.str());
		return strCount;
	}

	/*���ͳ����������*/
	string printArray()
	{
		stringstream strstreamCount;
		char* cLeft = "(";
		char* cBlank = ",";
		char* cRight = ")";

		/*���������ԷŽ��ַ���*/
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

		/*��stringstreamת����string*/
		string strCount(strstreamCount.str());
		return strCount;
	}


	/*���Relation����*/
	string printRelationArray()
	{
		stringstream strstreamCount;
		char* cLeft = "(";
		char* cBlank = ",";
		char* cRight = ")";

		/*���������ԷŽ��ַ���*/
		for (int iCount = 0; iCount < 5000; iCount++)
		{
			strstreamCount << cLeft;
			strstreamCount << m_pModelEntityRelationArray[iCount].getTargetStation()
				<< cBlank << m_pModelEntityRelationArray[iCount].getRelationStation()
				<< cBlank << m_pModelEntityRelationArray[iCount].getStationRelation()
				<< cBlank << m_pModelEntityRelationArray[iCount].getflag();
			strstreamCount << cRight << "\n";
		}

		/*��stringstreamת����string*/
		string strCount(strstreamCount.str());
		return strCount;
	}
	string printClusterArray()
	{
		stringstream strstreamCount;
		char* cLeft = "(";
		char* cBlank = ",";
		char* cRight = ")";

		/*���������ԷŽ��ַ���*/
		for (int iCount = 0; iCount < 200; iCount++)
		{
			strstreamCount << cLeft;
			strstreamCount << m_pModelEntityStationArray[iCount].getStationID()
				<< cBlank << m_pModelEntityStationArray[iCount].getFlag();
			strstreamCount << cRight << "\n";
		}

		/*��stringstreamת����string*/
		string strCount(strstreamCount.str());
		return strCount;
	}
	//����ϵ������뵽mysql���ݿ���
	void insertMatrixIntoMysql(CListRelationNode *pListRelationNode);

	double getRelationOver60(CListRelationNode *pListRelationNode, double iOverNum);

	//void getRelationMatrix();
	void getCluster();
	
private:
	//������������
	int m_iTotalSurvivalNum;
	//ģ���ڼ��Ϲ�ϵ����
	CListRelationSet* m_pHeadListRelationSet;
	//վ����
	int m_iTotalStationNum;
	//�ṹ��ά����
	CBLLModelEntityTimeSliceCountArray** m_pTimeSliceCountArray;
	//���Խṹ���飬��������ÿ�εĵ����������Сֵ
	CBLLModelEntityMaxMinTestArray* m_pMaxMinTestArray;
	//��¼��ϵֵ����ĳһ���ٽ�ֵ����������
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