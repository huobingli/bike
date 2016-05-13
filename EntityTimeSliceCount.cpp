#include"stdafx.h"
#include"stdlib.h"
#include"EntityTimeSliceCount.h"


CEntityTimeSliceCount::CEntityTimeSliceCount()
{
	m_iTimeSliceID = -1;
	m_pStationCount = new CEntityStationCount[700];
	m_iArrayLength = 700;
    m_iArraySize = 0;
    m_iSurvivalTime = 0;
}

CEntityTimeSliceCount::~CEntityTimeSliceCount()
{
 	delete [] m_pStationCount;
	m_pStationCount = NULL;
}

void CEntityTimeSliceCount::setStationCount(CEntityStationCount* pStationCount)
{
	for(int i=0;i<m_iArraySize;i++)
	{
		m_pStationCount[i].setStationID(pStationCount[i].getStationID());
		m_pStationCount[i].setRentArrayLength(pStationCount[i].getRentArrayLength());
		m_pStationCount[i].setReturnArrayLength(pStationCount[i].getReturnArrayLength());
		m_pStationCount[i].setRentArraySize(pStationCount[i].getRentArraySize());
		m_pStationCount[i].setReturnArraySize(pStationCount[i].getReturnArraySize());
		int iTempRentArraySize = m_pStationCount[i].getRentArraySize();
		int iTempReturnArraySize = m_pStationCount[i].getReturnArraySize();
		for(int j=0;j<iTempRentArraySize;j++)
		{
			memcpy(&(m_pStationCount[i].getRent()[j]),&(pStationCount[i].getRent()[j]),sizeof(CEntityStationCount));
		}
		for(int k=0;k<iTempReturnArraySize;k++)
		{
			memcpy(&(m_pStationCount[i].getReturn()[k]),&(pStationCount[i].getReturn()[k]),sizeof(CEntityStationCount));
		}

	}
}

int CEntityTimeSliceCount::getSurvivalTime()
{
	return m_iSurvivalTime;
}

void CEntityTimeSliceCount::setSurvivalTime(int iSurvivalTime)
{
	m_iSurvivalTime = iSurvivalTime;
}

/**
���ƣ�getBinary
˵������ȡ������ת�ɵĶ���������
����ֵ�����������ݼ���
����ʱ�䣺2015/10/21*/
unsigned char *CEntityTimeSliceCount::getBinary(){
    unsigned char *chBinary;
    bool isSuccessed = false;
    int iTotalLength = 21;
    int iDataLength = 20;

    //��ȡ��������
    for (int i=0; i<m_iArraySize; i++){
        iTotalLength += m_pStationCount[i].getBinaryLength();
    }
    chBinary = (unsigned char *)malloc (iTotalLength);
    memset (chBinary, '0', iTotalLength);

    //��˽������ת���ɶ���������
    //ͷ�������������
    isSuccessed = IntegerIntoBinary(iTotalLength, chBinary);
    //ʱ��Ƭ���ת������
    isSuccessed = IntegerIntoBinary(m_iTimeSliceID, chBinary+4);
    //��������ת������
    isSuccessed = IntegerIntoBinary(m_iSurvivalTime, chBinary+8);
    //ʱ��Ƭ�ɷ�վ������ת������
    isSuccessed = IntegerIntoBinary(m_iArrayLength, chBinary+12);
    //ʵ��վ����Ŀת������
    isSuccessed = IntegerIntoBinary(m_iArraySize, chBinary+16);

    //վ��ͳ�ƶ��󼯺�ת������
    for (int i=0; i<m_iArraySize; i++){
        memcpy (chBinary+iDataLength, m_pStationCount[i].getBinary(), m_pStationCount[i].getBinaryLength());
        iDataLength += m_pStationCount[i].getBinaryLength();
    }
    //ĩβ���һ�������ַ�
    memset (chBinary+iTotalLength-1, '\0', 1);


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
int CEntityTimeSliceCount::getBinaryLength()
{
    bool isSuccessed = false;

    if (m_iTimeSliceID != -1){
        //��ȡ��������
        int iTotalLength = 20;
        for (int i=0; i<m_iArraySize; i++){
            iTotalLength += m_pStationCount[i].getBinaryLength();
        }
        iTotalLength += 1;
        return iTotalLength;
    }
    return 21;
}

/**
���ƣ�update
˵����ʹ���ֽ����ݸ���
���������¶���������
����ֵ���Ƿ���³ɹ�
����ʱ�䣺2015/10/9*/
bool CEntityTimeSliceCount::update(const unsigned char *chBuffer){

    int iAllLength = 0;
    unsigned char *pTempInt = (unsigned char *)malloc (4);
    memset (pTempInt, 0, 4);

    //ת��������
    memcpy (pTempInt, chBuffer, 4);
    iAllLength = BinaryIntoInteger(pTempInt);
    memset (pTempInt, 0, 4);

    //תʱ��Ƭ���
    memcpy (pTempInt, chBuffer+4, 4);
    m_iTimeSliceID = BinaryIntoInteger(pTempInt);
    memset (pTempInt, 0, 4);

    //ת��������
    memcpy (pTempInt, chBuffer+8, 4);
    m_iSurvivalTime = BinaryIntoInteger(pTempInt);
    memset (pTempInt, 0, 4);

    //ת��ʱ��Ƭ�ɷ�վ������
    memcpy (pTempInt, chBuffer+12, 4);
    m_iArrayLength = BinaryIntoInteger(pTempInt);
    memset (pTempInt, 0, 4);

    //תʵ��վ����Ŀ
    memcpy (pTempInt, chBuffer+16, 4);
    m_iArraySize = BinaryIntoInteger(pTempInt);
    memset (pTempInt, 0, 4);
   
    /*תվ��ͳ�ƶ�������*/
    int iSectionLength = 0;
    int iTempLength = 20;
    unsigned char *chSectionLength = (unsigned char *)malloc (4);
    unsigned char *pTempBuf;

    if (m_iArraySize != 0){
        for (int i=0; i<m_iArraySize; i++){
            memset (chSectionLength, 0, 4);
            memcpy (chSectionLength, chBuffer+iTempLength, 4);
            iSectionLength = this->BinaryIntoInteger(chSectionLength);
            //iTempLength += 4;
            pTempBuf = (unsigned char *)malloc (iSectionLength);
            memset (pTempBuf, 0, iSectionLength);
            memcpy (pTempBuf, chBuffer+iTempLength, iSectionLength);
            m_pStationCount[i].update(pTempBuf);
            iTempLength += iSectionLength;
            free (pTempBuf);
            pTempBuf = NULL;
        }
    }

    free (chSectionLength);
    free (pTempInt);
    pTempInt = NULL;
    return true;
}

/**
˵��������������ͱ���ת�ɶ���������
���룺��ת���ͱ���������ת����Ķ������������ݵ��ַ�������(���ڲ������ڴ�)
����ֵ���Ƿ�ת���ɹ�
����ʱ�䣺2015/10/21*/
bool CEntityTimeSliceCount::IntegerIntoBinary(const int iNumIn, unsigned char *chBinaryOut){
    long int *iNum = new long int(iNumIn);

    memcpy (chBinaryOut, (unsigned char *)iNum, 1);
    memcpy (chBinaryOut+1, (unsigned char *)iNum+1, 1);
    memcpy (chBinaryOut+2, (unsigned char *)iNum+2, 1);
    memcpy (chBinaryOut+3, (unsigned char *)iNum+3, 1);

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
int CEntityTimeSliceCount::BinaryIntoInteger(const unsigned char *chBinaryIn){
    int iNum = 0;
    long int *iNumNew = new long int();

    memcpy ((unsigned char *)iNumNew, chBinaryIn, 4);
    iNum = *iNumNew;

    delete iNumNew;
    iNumNew = NULL;
    return iNum;
}

char* CEntityTimeSliceCount::changeToChar()
{
	char* cTimeSliceID = new char();
	char* cSurvivalTime = new char();
	char* cTimeSliceCount = new char();
	char* cLeft = "(";
	char* cRight = ")";
	char* cBlank = " ";

	/*��ʱ��Ƭ���ת����char���ַ���*/
	itoa(m_iTimeSliceID,cTimeSliceID,10);
	/*����������ת����char���ַ���*/
	itoa(m_iSurvivalTime,cSurvivalTime,10);

	/*ƴ���ַ���*/
	strcat(cTimeSliceCount,cLeft);
	strcat(cTimeSliceCount,cTimeSliceID);
	strcat(cTimeSliceCount,cBlank);
	strcat(cTimeSliceCount,cSurvivalTime);
	/*��վ��ͳ��ƴ�ӵ�ʱ��Ƭͳ����*/
	/*���վ��ͳ��Ϊ�գ��ͷ���()*/
	if(m_iArraySize==0)
	{
		strcat(cTimeSliceCount,cLeft);
		strcat(cTimeSliceCount,cRight);
	}
	else
	{
		for(int i=0;i<m_iArraySize;i++)
		{
			strcat(cTimeSliceCount,m_pStationCount[i].changeToChar());
		}
	}
	strcat(cTimeSliceCount,cRight);

	return cTimeSliceCount;

}

string CEntityTimeSliceCount::changeToStringstream()
{
	stringstream strstreamTimeSliceCount;
	char* cLeft = "(";
	char* cRight = ")";
	char* cBlank = " ";	
	char* cWrap = "\n";

	strstreamTimeSliceCount<<cLeft;
	strstreamTimeSliceCount<<m_iTimeSliceID;
	strstreamTimeSliceCount<<cBlank;
	strstreamTimeSliceCount<<m_iSurvivalTime;
	if(m_iArraySize==0)
	{
		strstreamTimeSliceCount<<cLeft;
		strstreamTimeSliceCount<<cRight;
	}
	else
	{
		for(int i=0;i<m_iArraySize;i++)
		{
			strstreamTimeSliceCount<<m_pStationCount[i].changeToStrstream();
		}
	}
	strstreamTimeSliceCount<<cRight;
	strstreamTimeSliceCount<<cWrap;
	string strTimeSliceCount(strstreamTimeSliceCount.str());

	return strTimeSliceCount;
}

