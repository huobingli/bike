#pragma once
#include<sstream>
using namespace std;

//ͳ�ƶ���
class CEntityCount
{
private:
	int m_iRelatedStationID;	//����վ��
	int m_iMaxCostTime;			//��󻨷�ʱ��
	int m_iMinCostTime;			//��С����ʱ��
	int m_iOperatedTimes;		//��������

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
	CEntityCount();
	~CEntityCount();

public:

	/**
	˵������ȡ���Է���
	�����ߣ�Ҧ
	*/
	int getMaxCostTime();

	int getMinCostTime()
	{
		return m_iMinCostTime;
	}

	int getOperatedTimes()
	{
		return m_iOperatedTimes;
	}
	/**
	˵�����������Է���
	�����ߣ�Ҧ
	*/
	void setRelatedStationID(int relatedStationID);
	void setMaxCostTime(int costTime);
	void setMinCostTime(int costTime);
	void setOperatedTimes();

public:
    /**
    ˵������ȡ������Ķ����Ƹ�ʽ����
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
	˵������˽������ת����char*
	��������
	����ֵ��char*����
	�����ߣ�Ҧ
	����ʱ�䣺2015/11/6
	*/
	char* changeToChar();

	/**
	˵������˽������ת����stringstream
	��������
	�����ߣ�Ҧ
	����ʱ�䣺2015/11/9
	*/
	string changeToStrstream();

	/**
	˵������ȡ����վ����
	��������
	������Ҫ
	����ʱ�䣺2015/11/9
	*/
	int getRelatedStationID();
};
