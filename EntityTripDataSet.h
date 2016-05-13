#pragma once
#include"EntityTripData.h"

//���ڣ�2015.7.29
//���ߣ�Ҧ����
//�������軹��¼���ϣ���������CBLLCtrRelationOfTimeSliceStation������
//		������Ϣʵ����CEntityTripData
class CEntityTripDataSet
{
public:
	CEntityTripDataSet();	
	~CEntityTripDataSet();

private:
	CEntityTripData* m_CSexample;		//ָ��վ��¼�����ڴ��
	int m_iArrayLength;					//���ϴ�С
	int m_iArraySize;					//���ϳ���
	int m_iPos;							//��¼�����ڴ�洢ָ��
	int m_iEachNumStation;				//ÿ����������ĳ���
	int EachNumStation;

public:

    /**
    ˵������ȡ��ǰ�洢�ļ�¼��Ŀ
    ����ֵ��Ԫ�ظ���
    �����ߣ���*/
    int & gettingSize();

    /**
    ˵�����жϼ�¼�����Ƿ�Ϊ��
    �����ߣ���*/
    bool isEmpty() const;

    /**
    ˵�����ж������Ƿ�����
    �����ߣ���*/
    bool isEnd() const;

    /**
    ˵�������ؼ�¼����
    ����ֵ����¼���飨ʵ�ʵĴ洢��¼�ڴ��ַ�������ô���
    �����ߣ���*/
    CEntityTripData *& linkRecord();

    /**
    ˵��:��������
    �����ߣ���*/
    CEntityTripData *& biggerRecordSet();

	/**
	˵������ȡ��һ���軹��¼
	�����ߣ�Ҧ
	*/
	CEntityTripData* getFirst();

	/**
	˵������ȡ��һ���軹��¼
	�����ߣ�Ҧ
	*/
	CEntityTripData* getNext();

	/**
	˵�����ж��±��Ƿ������
	������:Ҧ
	*/
	bool isEnd();

};

