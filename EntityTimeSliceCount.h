#pragma once
#include"BLLEntityTimeSliceMemory.h"
#include"EntityStationCount.h"
#include"stdlib.h"
#include"string.h"

//ʱ��Ƭͳ��ʵ����
class CEntityTimeSliceCount
{
private:
	int m_iTimeSliceID;                           //ʱ��Ƭ���
    int m_iSurvivalTime;						  //��������
	CEntityStationCount* m_pStationCount;       //վ��ͳ�ƶ���ָ�� 
	int m_iArrayLength;                           //վ��ͳ�ƶ������鳤��
    int m_iArraySize;                             //վ��ͳ�ƶ�������ʵ�ʴ�С�����������

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
	CEntityTimeSliceCount();
	~CEntityTimeSliceCount();

	void setStationCount(CEntityStationCount* pStationCount);

    /**
    ˵������ȡ��������
    �����ߣ���*/
    int getSurvivalTime();

    /**
    ˵����������������
    ��������������
    �����ߣ���*/
    void setSurvivalTime(int iSurvivalTime);

	void setTimeSliceID(int iTimeSliceID)
	{
		m_iTimeSliceID = iTimeSliceID;
	}
	int getTimeID()
	{
		return m_iTimeSliceID;
	}
	void setArrayLength(int iArrayLength)
	{
		m_iArrayLength = iArrayLength;
	}
	void setArraySize(int iArraySize)
	{
		m_iArraySize = iArraySize;
	}
	int getArraySize()
	{
		return m_iArraySize;
	}
	
	CEntityStationCount* getStationCount()
	{
		return m_pStationCount;
	}
public:
    /**
    ˵������ȡ������ת�ɵĶ���������
    ����ֵ�����������ݼ���
    �����ߣ���
    ����ʱ�䣺2015/10/21*/
    unsigned char* getBinary();

    /**
    ˵������ȡ������ת�ɵĶ��������ݵĳ���
    ����ֵ�����������ݳ���
    �����ߣ���
    ����ʱ�䣺2015/10/21*/
    int getBinaryLength();

    /**
    ˵����ʹ���ֽ����ݸ���
    ���������¶���������
    ����ֵ���Ƿ���³ɹ�
    �����ߣ���
    ����ʱ�䣺2015/10/9*/
    bool update(const unsigned char* chBuffer);

	/**
	˵������ʱ��Ƭ�ڴ������µ�ʱ��ͳ�ƶ�����
	������ʱ��Ƭ�ڴ����
	����ֵ��bool�ͣ���ʾ�����Ƿ�ɹ�
	�����ߣ�Ҧ*/
	CEntityTimeSliceCount* updatingTimeSliceCount(CBLLEntityTimeSliceMemory* pTimeSliceMemory);

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
	����ֵ����
	�����ߣ�Ҧ
	*/
	string changeToStringstream();

};

