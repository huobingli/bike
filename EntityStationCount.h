#pragma once
#include"EntityCount.h"
#include"BLLEntityOperation.h"
#include "stdlib.h"
#include "string.h"

//վ��ͳ�ƶ���
class CEntityStationCount
{
private:
	int m_iStationID;					//վ����
	CEntityCount* m_pRentCount;			//�賵ͳ�ƶ�������
	CEntityCount* m_pReturnCount;		//����ͳ�ƶ�������
	int m_iRentArrayLength;				//�賵ͳ�ƶ������鳤��
	int m_iReturnArrayLength;			//����ͳ�ƶ������鳤��
    int m_iRentArraySize;               //�賵ͳ�ƶ��������С
    int m_iReturnArraySize;             //����ͳ�ƶ��������С

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
	CEntityStationCount();
	~CEntityStationCount();

private:
	//�������ƣ�initArray
	//���������鳤��
	//����ֵ����
	//��������ʼ��ͳ�ƶ�������
	void initArray(int iArrayLength);

public:
	CEntityCount* getRent();
	CEntityCount* getReturn();
	void setRentArrayLength(int iRentArrayLength)
	{
		m_iRentArrayLength = iRentArrayLength;
	}
	void setReturnArrayLength(int iReturnArrayLength)
	{
		m_iReturnArrayLength = iReturnArrayLength;
	}

	void setRentArraySize(int iRentArraySize)
	{
		m_iRentArraySize = iRentArraySize;
	}

	void setReturnArraySize(int iReturnArraySize)
	{
		m_iReturnArraySize = iReturnArraySize;
	}

	int getRentArrayLength()
	{
		return m_iRentArrayLength;
	}
	int getReturnArrayLength()
	{
		return m_iReturnArrayLength;
	}

	/**
	˵������ý賵ͳ�ƶ�������ʵ�ʴ�С
	����ֵ���賵ͳ�ƶ�������ʵ�ʴ�С
	�����ߣ�Ҧ*/
	int getRentArraySize();

	/**
	˵������û���ͳ�ƶ�������ʵ�ʴ�С
	����ֵ������ͳ�ƶ�������ʵ�ʴ�С
	�����ߣ�Ҧ*/
	int getReturnArraySize();

	/**
	˵��������վ����
	������վ����
	����ֵ����
	�����ߣ�Ҧ*/
	void setStationID(int iStationID);


	/**
	˵��������������µ��賵ͳ�Ƽ�¼��
	�����������
	����ֵ����
	�����ߣ�Ҧ*/
	void setRentCount(CBLLEntityOperation* pRentOperation);

	/**
	˵���������������µ�����ͳ�Ƽ�¼��
	������������
	����ֵ����
	�����ߣ�Ҧ*/
	void setReturnCount(CBLLEntityOperation* pReturnOperation);
	

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
	˵������˽������ת����char
	��������
	����ֵ��char
	�����ߣ�Ҧ
	����ʱ�䣺2015/11/6
	*/
	char* changeToChar();

	/**
	˵������ȡվ����
	��������
	����ֵ��int
	�����ߣ�Ҧ
	����ʱ�䣺2015/11/8
	*/
	int getStationID();

	/**
	˵������˽������ת����stringstream
	��������
	����ֵ��stringstream
	�����ߣ�Ҧ
	����ʱ�䣺2015/11/9
	*/
	string changeToStrstream();

	/**
	˵��������ڽ�ͳ�����Ƿ������ͬ�Ĺ���վ��
	����������վ����
	�����ߣ�Ҧ
	����ʱ�䣺2015/11/9
	*/
	bool checkRentRelatedStationID(int iRelatedStationID);

	/**
	˵��������ڻ�ͳ�����Ƿ������ͬ�Ĺ���վ��
	����������վ����
	�����ߣ�Ҧ
	����ʱ�䣺2015/11/9
	*/
	bool checkReturnRelatedStationID(int iRelatedStationID);
	/**
	˵������ȡָ�����������վ��
	����������վ����
	�����ߣ�Ҧ
	����ʱ�䣺2015/11/9
	*/
	CEntityCount* getRentCount(int iRelatedStationID);

	CEntityCount* getRentCount()
	{
		return m_pRentCount;
	}

	/**
	˵������ȡָ������������վ��
	����������վ����
	�����ߣ�Ҧ
	����ʱ�䣺2015/11/9
	*/
	CEntityCount* getReturnCount(int iRelatedStationID);

	CEntityCount* getReturnCount()
	{
		return m_pReturnCount;
	}

};


