#pragma once
#include"EntityTimeSliceCount.h"
#include"stdlib.h"
#include"string.h"

class CEntityTimeSliceCountNode
{
public:
	CEntityTimeSliceCountNode();
	~CEntityTimeSliceCountNode();
    /**
    ˵������ȡ��һ�ڵ�
    ����ֵ����һ�ڵ�
    �����ߣ���*/
    CEntityTimeSliceCountNode *getNextTimeSliceCountNode();
    
    /**
    ˵����������һ�ڵ�
    �����ߣ���*/
    void setNextTimeSliceCountNode(CEntityTimeSliceCountNode *pNextTimeSliceCountNode);

    /**
    ˵������ȡʱ��Ƭ����
    �����ߣ���*/
    CEntityTimeSliceCount *getTimeSliceCount();

    /**
    ˵��������ʱ��Ƭ����
    �����ߣ���*/
    void setTimeSliceCount(CEntityTimeSliceCount *pTimeSliceCount);

	bool updatingTimeSliceCount(CBLLEntityTimeSliceMemory* pTimeSliceMemory)
{
	m_pTimeSliceCount->setTimeSliceID(pTimeSliceMemory->getTimeSliceID());
	m_pTimeSliceCount->setSurvivalTime(pTimeSliceMemory->getSurvivalTime());
	m_pTimeSliceCount->setArrayLength(pTimeSliceMemory->getArrayLength());
	m_pTimeSliceCount->setArraySize(pTimeSliceMemory->getArraySize()); 
	m_pTimeSliceCount->setStationCount(pTimeSliceMemory->getStationCount());

	return true;
}
private:
	CEntityTimeSliceCount *m_pTimeSliceCount;
	CEntityTimeSliceCountNode *m_pNextTimeSliceCountNode;
};

class CEntityTimeSliceCountSet
{
    /**
    ˵��������������ͱ���ת�ɶ���������
    ���룺��ת���ͱ���������ת����Ķ������������ݵ��ַ�������
    ����ֵ���Ƿ�ת���ɹ�
    ����ʱ�䣺2015/10/21*/
    bool IntegerIntoBinary(const int iNumIn, unsigned char *chBinaryOut);

    /**
    ˵����������Ķ���������ת�����ͱ���
    ���룺�������������ݵ��ַ�������(���ڲ������ڴ�)
    ����ֵ��ת���ɹ������ͱ��� 
    ����ʱ�䣺2015/10/21*/
    int BinaryIntoInteger(const unsigned char *chBinaryIn);


public:
	CEntityTimeSliceCountSet();
	~CEntityTimeSliceCountSet();

public:
	/**
	˵������ʱ��Ƭͳ�ƶ���ڵ����ʱ��ͳ������
	����������Ԫ��
	����ֵ��bool�� ��ʾ�Ƿ����ɹ�
	�����ߣ�Ҧ*/
	bool insertTimeSliceCount(CEntityTimeSliceCountNode* pTimeSliceCountNode);

	/**
	˵������ȡ����Ԫ�ظ���
	����ֵ������Ԫ�ظ���
	�����ߣ���
	*/
	int getNodeNum();

	/**
	˵������ȡͷ�ڵ�
	����ֵ��ͷ�ڵ�
	�����ߣ�Ҧ
	*/
	CEntityTimeSliceCountNode* getHeadTimeSliceCountNode();

	/**
	˵������ȡ���������ݼ���
	��������
	����ֵ�����������ݼ���
	�����ߣ���
	*/
	unsigned char* getBinary();

	/**
	˵������ȡ���������ݳ���
	��������
	����ֵ�����������ݳ���
	�����ߣ���
	*/
	int getBinaryLength();

	/**
	˵�������¶���������
	����������������
	����ֵ��bool�ͣ���ʾ�����Ƿ�ɹ�
	�����ߣ���
	*/
	bool update(const unsigned char* chBuffer);

	/**
	˵������˽������ת����char
	��������
	����ֵ��char
	�����ߣ�Ҧ
	*/
	char* changeToChar();

	/**
	˵������˽������ת����stringstream
	��������
	����ֵ��stringstream
	�����ߣ�Ҧ
	*/
	string changeToStringstream();


bool getLastTimeSliceCountNode(CEntityTimeSliceCountNode* pHeadNode);
private:
	 CEntityTimeSliceCountNode *m_pHeadTimeSliceCountNode;  //ͷ�ڵ�  
	 int m_iNodeNum;										//����Ԫ�ظ���
};

