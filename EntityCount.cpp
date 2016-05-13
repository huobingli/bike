#include"stdafx.h"
#include<stdlib.h>
#include<string>
#include"EntityCount.h"
using namespace std;

CEntityCount::CEntityCount(){
    m_iRelatedStationID = -1;
    m_iMaxCostTime = 0;
    m_iMinCostTime = 99999;
    m_iOperatedTimes = 0;
}

CEntityCount::~CEntityCount()
{}
int CEntityCount::getMaxCostTime(){
    return m_iMaxCostTime;
}

void CEntityCount::setRelatedStationID(int relatedStationID){
    m_iRelatedStationID = relatedStationID;
}

void CEntityCount::setOperatedTimes(){
    m_iOperatedTimes++;
}

void CEntityCount::setMaxCostTime(int costTime){
    if(costTime>m_iMaxCostTime){
        m_iMaxCostTime = costTime;
    }
}

void CEntityCount::setMinCostTime(int costTime){
    if(costTime<m_iMinCostTime){
        m_iMinCostTime = costTime;
    }
}

/**
˵��������������ͱ���ת�ɶ���������
���룺��ת���ͱ���������ת����Ķ������������ݵ��ַ�������(���ڲ������ڴ�)
����ֵ���Ƿ�ת���ɹ�
����ʱ�䣺2015/10/21*/
bool CEntityCount::IntegerIntoBinary(const int iNumIn, unsigned char *chBinaryOut){
    long int *iNum = new long int(iNumIn);

    memcpy (chBinaryOut, (char *)iNum, 1);
    memcpy (chBinaryOut+1, (char *)iNum+1, 1);
    memcpy (chBinaryOut+2, (char *)iNum+2, 1);
    memcpy (chBinaryOut+3, (char *)iNum+3, 1);

    delete iNum;
    iNum = NULL;
    if (chBinaryOut != 0){
        return true;
    }
    return false;
}

/**
˵����������Ķ���������ת�����ͱ���
���룺�������������ݵ��ַ�������(���ڲ������ڴ�)
����ֵ��ת���ɹ������ͱ��� 
����ʱ�䣺2015/10/21*/
int CEntityCount::BinaryIntoInteger(const unsigned char *chBinaryIn){
    long int iNum = -1;
    long int *iNumNew = new long int();

    memcpy ((unsigned char *)iNumNew, chBinaryIn, 4);
    iNum = *iNumNew;

    delete iNumNew;
    iNumNew = NULL;
    return iNum;
}



/**
���ƣ�getBinary
˵������ȡ������ת�ɵĶ���������
����ֵ�����������ݼ���
����ʱ�䣺2015/10/21*/
unsigned char *CEntityCount::getBinary(){
    unsigned char *chBinary = (unsigned char *)malloc (16);
    bool isSuccessed = false;
    memset (chBinary, 0, 16);

    //��˽������ת���ɶ���������
    isSuccessed = IntegerIntoBinary(m_iRelatedStationID, chBinary);
    isSuccessed = IntegerIntoBinary(m_iMaxCostTime, chBinary+4);
    isSuccessed = IntegerIntoBinary(m_iMinCostTime, chBinary+8);
    isSuccessed = IntegerIntoBinary(m_iOperatedTimes, chBinary+12);

    if (isSuccessed){
        return chBinary;
    }
    return NULL;
}

/**
���ƣ�getBinaryLength
˵������ȡ������ת�ɵĶ��������ݵĳ���
����ֵ�����������ݳ���
����ʱ�䣺2015/10/21*/
int CEntityCount::getBinaryLength(){
    if (m_iRelatedStationID == -1){
        return 0;
    }
    return 16;
}

/**
���ƣ�update
˵����ʹ���ֽ����ݸ���
���������¶���������
����ֵ���Ƿ���³ɹ�
����ʱ�䣺2015/10/9*/
bool CEntityCount::update(const unsigned char *chBuffer){

    unsigned char *pTemp = (unsigned char*)malloc(4);
    memset (pTemp, 0, 4);

    memcpy (pTemp, chBuffer, 4);
    m_iRelatedStationID =  BinaryIntoInteger(pTemp);
    memset (pTemp, 0, 4);

    memcpy (pTemp, chBuffer+4, 4);
    m_iMaxCostTime =  BinaryIntoInteger(pTemp);
    memset (pTemp, 0, 4);

    memcpy (pTemp, chBuffer+8, 4);
    m_iMinCostTime =  BinaryIntoInteger(pTemp);
    memset (pTemp, 0, 4);

    memcpy (pTemp, chBuffer+12, 4);
    m_iOperatedTimes =  BinaryIntoInteger(pTemp);
    memset (pTemp, 0, 4);


    free (pTemp);
    return true;
}

char* CEntityCount::changeToChar()
{
	char* cRelatedStationID = new char();
	char* cMaxCostTime =new char();
	char* cMinCostTime =new char();
	char* cOperatedTimes=new char();
	char* cCount = new char();
	char* cLeft = "(";
	char* cRight = ")";
	char* cBlank = " ";

	/*����������ת����char���ַ���*/
	itoa(m_iRelatedStationID,cRelatedStationID,10);
	itoa(m_iMaxCostTime,cMaxCostTime,10);
	itoa(m_iMinCostTime,cMinCostTime,10);
	itoa(m_iOperatedTimes,cOperatedTimes,10);

	/*ƴ���ַ���*/
	strcat(cCount,cLeft);
	strcat(cCount,cRelatedStationID);
	strcat(cCount,cBlank);
	strcat(cCount,cMaxCostTime);
	strcat(cCount,cBlank);
	strcat(cCount,cMinCostTime);
	strcat(cCount,cBlank);
	strcat(cCount,cOperatedTimes);
	strcat(cCount,cRight);

	return cCount;

}

string CEntityCount::changeToStrstream()
{

	stringstream strstreamCount;
	char* cLeft = "(";
	char* cBlank = " ";
	char* cRight = ")";
	/*���������ԷŽ��ַ���*/
	strstreamCount<<cLeft;
	strstreamCount<<m_iRelatedStationID;
	strstreamCount<<cBlank;
	strstreamCount<<m_iMaxCostTime;
	strstreamCount<<cBlank;
	strstreamCount<<m_iMinCostTime;
	strstreamCount<<cBlank;
	strstreamCount<<m_iOperatedTimes;
	strstreamCount<<cRight;

	/*��stringstreamת����string*/
	string strCount(strstreamCount.str());


	return strCount;	
}

int CEntityCount::getRelatedStationID()
{
	return m_iRelatedStationID;
}