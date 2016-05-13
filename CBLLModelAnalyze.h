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
    ˵����model���캯������ʼ��model��һЩ��������
    ������վ�����
    ����ֵ��
    ����ʱ�䣺*/
	CBLLModelAnalyze(int iStationNum);


	~CBLLModelAnalyze();


	/**
    ˵������ʼ��model���ڲ����飬׼��ʹ��
    ������
    ����ֵ��
    ����ʱ�䣺*/
	void initArray();


	/**
    ˵�����ͷ�model���ڲ����飬������һ��ʹ��
    ������
    ����ֵ��
    ����ʱ�䣺*/
	void releaseArray();
	

	/**
    ˵����model����Ҫ����������ÿ�δ���һ��ͳ�Ƽ�������������������Ҫд��Ĺ�ϵ��������
    ������ͳ�Ƽ�������������ʽ���� �����ô��룩д�뼯������������ʽ��
    ����ֵ�������ô�����д�뼯������������ʽ��
    ����ʱ�䣺*/
	bool startAnalyze(CEntityTimeSliceCountSet *pEntityTimeSliceCountSet, CListWriteRelationSet *&pListWriteRelationSet);


	/**
    ˵��������ͳ�Ƽ��ϣ���ԭ��ͳ�Ƽ��Ϸ����ڴ�ģ�͵�������
    ������ʱ��Ƭͳ�Ƽ���
    ����ֵ��
    ����ʱ�䣺*/
	bool copyEntityTimeSliceCountNode(CEntityTimeSliceCountNode *pEntityTimeSliceCountNode);
	

	/**
    ˵������ʱ��Ƭͳ�Ƽ��Ͻ��м��㣬�ó���ǰʱ��Ƭ����Ĺ�ϵ����
    ������ʱ��Ƭͳ�Ƽ���
    ����ֵ��
    ����ʱ�䣺*/
	bool getRelation(CEntityTimeSliceCountNode *pEntityTimeSliceCountNode);
	

	/**
    ˵������������վ��֮������ƶȣ�����վ�㲻Ϊͬһ��վ�㣩
    ��������һ��վ�㣬�ڶ���վ��
    ����ֵ������վ�����ƶ�
    ����ʱ�䣺*/
	double calculateRelation(int iFirstStation, int iSecondStation);
	

	/**
    ˵������ȡ�������еĹ�ϵ�����ڲ���վ���ϵֵ
    ������ʱ��ƬID��Ŀ��վ�㣬����վ��
    ����ֵ��վ���ϵֵ
    ����ʱ�䣺*/
	double getStationRelationOfNode(int iTimeSlice, int iTargetStationID, int iRelationStationID);
	

	/**
    ˵�����õ��ص�ʱ��Ƭ
    ��������һ��վ�㣬�ڶ���վ�㣬��Сʱ���ţ����ʱ����
    ����ֵ�����ô�����Сʱ���ţ����ô������ʱ����
    ����ʱ�䣺*/
	void getOverLapTimes(CBLLModelEntityTimeSliceCountArray iFirstCount, CBLLModelEntityTimeSliceCountArray iSecondCount, int &iMinTime, int &iMaxTime);
	
	
	/**
    ˵������ģ���ڲ���ʱ��Ƭ��ϵ������������жϣ��������д�����������С��model�����������ڵģ������ϲ�BLL������
    ���������ô��뷵��BLL�������Ĺ�ϵ��������
    ����ֵ�����÷���
    ����ʱ�䣺*/
	bool judgeSurvivalTime(CListWriteRelationSet *&pListWriteRelationSet);
	

	/**
    ˵�������ڴ�ģ���е�������ʽת���ɿ��Դ���DAL���������ʽ������ListRelationSet ת����ListWriteRelationSet��
    �������ڴ�ģ���������ȡ������int���������ô��룩����DAL������������ʽ��
    ����ֵ�������ô���������DAL������������ʽ��
    ����ʱ�䣺*/
	bool turnToListWriteRelationSet(int iNodeNum, CListWriteRelationSet *&pListWriteRelationSet);
	

	bool  getRestRelationSet(CListWriteRelationSet *&pListWriteRelationSet)
	{
		turnToListWriteRelationSet(m_pHeadListRelationSet->getNodeNum(),pListWriteRelationSet);
		return true;
	}

	/**
    ˵�������������ַ�����ʽ
    ������
    ����ֵ�������ַ���
    ����ʱ�䣺*/
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
	 *��һ������
	 */
	void NormalizeMatrix(CEntityRelationSet *&pEntityRelationSet, double dNormalizeParameter);


	

private:
	//������������
	int m_iTotalSurvivalNum;
	//ģ���ڲ�ʱ��Ƭ��ϵ��������
	CListRelationSet *m_pHeadListRelationSet;
	//����ض���
	CBufferPoolBLL *m_pBufferPool;
	//��վ�����
	int m_iTotalStationNum;
	//�ṹ��ά����
	CBLLModelEntityTimeSliceCountArray **m_pTimeSliceCountArray;
};

