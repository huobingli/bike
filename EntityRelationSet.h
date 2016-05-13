#pragma once
#include <string>
#include<sstream>
#include"iostream"
using namespace std;

class CEntityRelationSet{
	//������վ�����
    int m_iStationNum;   
	//ʱ��ƬID
    int m_iTimeID;  
	//��ϵ��ά����
    double **m_RelationSet;     
	//byte **m_RelationSet;
    /**
    ˵��������������ͱ���ת�ɶ���������
    ���룺��ת���ͱ���������ת����Ķ������������ݵ��ַ�������
    ����ֵ���Ƿ�ת���ɹ�
    �����ߣ���
    ����ʱ�䣺2015/10/21*/
    bool IntegerIntoBinary(const int iNumIn, unsigned char *chBinaryOut);

    /**
    ˵����������Ķ���������ת�����ͱ���
    ���룺�������������ݵ��ַ�������(���ڲ������ڴ�)
    ����ֵ��ת���ɹ������ͱ��� 
    �����ߣ���
    ����ʱ�䣺2015/10/21*/
    int BinaryIntoInteger(const unsigned char *chBinaryIn);
public:
	
    /**
    ˵���������ϵ���ݼ���ʵ�壬���첢��ʼ����ά��������Ź�ϵ����
    ������վ�����
    �����ߣ���*/
    CEntityRelationSet(int iStationNum, int iTimeID);

    CEntityRelationSet();

    ~CEntityRelationSet(void);

    /**
    ˵��������վ�����
    ������վ�����
    �����ߣ���*/
    void setStationNum(int iStationNum);

    /**
    ˵�����õ�վ�����
    ����ֵ��վ�����
    �����ߣ���*/
    int getStationNum();

	//CEntityRelation *getRelationSet()
	//{
	//	return m_RelationSet;
	//}
    /**
    ˵������ʼ����ϵ��ά���飬�Խ���Ϊ1������������
    �����ߣ���*/
	void initRelationSet();

    /**
    ˵�����������ݹ�ϵ����
    ��������ʼվ���ϵ��Ŀ��վ���ϵ��վ�����ֵ
    ����ֵ���Ƿ����ɹ�
    �����ߣ���*/
    void insertRelationSet(int iTargetStationID, int iRelationStationID, double iStationRelation);

    /**
    ˵�����������ݹ�ϵ����
    ��������ʼվ���ϵ��Ŀ��վ���ϵ��վ�����ֵ
    ����ֵ���Ƿ����ɹ�
    �����ߣ���*/
	void insertStationRelation(int iTargetStationID, int iRelationStationID, double iStationRelation);

    /**
    ˵����ĳ��ʱ��Ƭ�еõ�����վ���ϵ
    ������Ŀ��վ�㣬����վ��
    ����ֵ��վ���ϵ
    �����ߣ���*/
    double getStationRelation(int iSourceStationID, int iTargetStationID);

    /**
    ˵�����õ�վ�����
    ����ֵ��վ�����
    �����ߣ���*/
    int getEntityNum();

    /**
    ˵�����õ�����ʱ��ƬID
    ����ֵ��ʱ��ƬID
    �����ߣ���*/
    int getTimeID();

    /**
    ˵�������ü���ʱ��ƬID
    ���룺ʱ��ƬID
    �����ߣ���*/
    void setTimeID(int iTimeID);

    /**
    ���ƣ�getBinary
    ˵������ȡ������ת�ɵĶ���������
    ����ֵ�����������ݼ���
    �����ߣ���
    ����ʱ�䣺2015/10/9*/
    unsigned char *getBinary();

    /**
    ���ƣ�getBinaryLength
    ˵������ȡ������ת�ɵĶ��������ݵĳ���
    ����ֵ�����������ݳ���
    �����ߣ���
    ����ʱ�䣺2015/10/9*/
    int getBinaryLength();

    /**
    ���ƣ�update
    ˵�������¶���������
    ����������������Ϣ�Ķ���������
    ����ֵ��bool�ͣ���ʾ�����Ƿ�ɹ�
    �����ߣ���
    ����ʱ��:2015/10/25*/
    bool update(const unsigned char* chBuffer);

	char *getString()
	{
		char cString [20000];
		itoa(m_iTimeID,cString, 10);
		strcat(cString, "   ");
		
		char cStringStationNum[10];
		itoa(m_iStationNum, cStringStationNum, 10);
		strcat(cStringStationNum, "   ");

		strcat(cString,cStringStationNum);
		
		for(int iCount = 0; iCount < m_iStationNum; iCount++)
		{
			for (int jCount = 0; jCount < m_iStationNum; jCount++)
			{
				char *a = (char *)malloc (5);
				memset(a, 0, 5);
				itoa(m_RelationSet[iCount][jCount], a, 10);
				strcat(cString, a);
			}
		}
		return cString;
	}

	string changeToStringstream()
	{
		stringstream strstreamCount;
		char* cLeft = "(";
		char* cBlank = ",";
		char* cRight = ")";
		/*���������ԷŽ��ַ���*/
		strstreamCount<<cLeft;
		for(int iCount = 0; iCount < m_iStationNum; iCount++)
		{
			strstreamCount<<cLeft;
			for(int jCount = 0; jCount < m_iStationNum; jCount++)
			{
				strstreamCount<<m_RelationSet[iCount][jCount]<<cBlank;
			}
			strstreamCount<<cRight<<"\n";
		}
		
		strstreamCount<<cRight;

		/*��stringstreamת����string*/
		string strCount(strstreamCount.str());


		return strCount;
	}
};
