#include"stdafx.h"
#include"EntityStationCount.h"
#include<crtdbg.h>

CEntityStationCount::CEntityStationCount()
{

    m_pRentCount = new CEntityCount[700];
    m_pReturnCount = new CEntityCount[700];
    m_iStationID = -1;
    m_iRentArrayLength = 700;
    m_iReturnArrayLength = 700;
    m_iRentArraySize = 0;
    m_iReturnArraySize = 0;
}

CEntityStationCount::~CEntityStationCount()
{
	delete [] m_pRentCount;
	m_pRentCount = NULL;
	delete [] m_pReturnCount;
	m_pReturnCount = NULL;
}
CEntityCount* CEntityStationCount::getRent()
{
	return m_pRentCount;
}

CEntityCount* CEntityStationCount::getReturn()
{
	return m_pReturnCount;
}

int CEntityStationCount::getRentArraySize()
{
	return m_iRentArraySize;
}

int CEntityStationCount::getReturnArraySize()
{
	return m_iReturnArraySize;
}

void CEntityStationCount::setStationID(int iStationID)
{
	m_iStationID = iStationID;
}

void CEntityStationCount::setRentCount(CBLLEntityOperation* pRentOperation)
{
	int iRelatedStationID = pRentOperation->getRelatedStationID();
	if(checkRentRelatedStationID(iRelatedStationID))
	{
		CEntityCount* pRentCount = getRentCount(iRelatedStationID);
		pRentCount->setMaxCostTime(pRentOperation->getCostTime());
		pRentCount->setMinCostTime(pRentOperation->getCostTime());
		pRentCount->setOperatedTimes();
	}
	else
	{
		m_pRentCount[m_iRentArraySize].setRelatedStationID(iRelatedStationID);
		m_pRentCount[m_iRentArraySize].setMaxCostTime(pRentOperation->getCostTime());
		m_pRentCount[m_iRentArraySize].setMinCostTime(pRentOperation->getCostTime());
		m_pRentCount[m_iRentArraySize].setOperatedTimes();
		m_iRentArraySize++;
	}
}

void CEntityStationCount::setReturnCount(CBLLEntityOperation* pReturnOperation)
{
	int iRelatedStationID = pReturnOperation->getRelatedStationID();
	if(checkReturnRelatedStationID(iRelatedStationID))
	{
		CEntityCount* pReturnCount = getReturnCount(iRelatedStationID);
		pReturnCount->setMaxCostTime(pReturnOperation->getCostTime());
		pReturnCount->setMinCostTime(pReturnOperation->getCostTime());
		pReturnCount->setOperatedTimes();
	}
	else
	{
		m_pReturnCount[m_iReturnArraySize].setRelatedStationID(iRelatedStationID);
		m_pReturnCount[m_iReturnArraySize].setMaxCostTime(pReturnOperation->getCostTime());
		m_pReturnCount[m_iReturnArraySize].setMinCostTime(pReturnOperation->getCostTime());
		m_pReturnCount[m_iReturnArraySize].setOperatedTimes();
		m_iReturnArraySize++;
	}
}


/**
���ƣ�getBinary
˵������ȡ������ת�ɵĶ���������
����ֵ�����������ݼ���
����ʱ�䣺2015/10/21*/
unsigned char *CEntityStationCount::getBinary(){
    unsigned char *chBinary = (unsigned char *)malloc (25+16*(m_iRentArraySize + m_iReturnArraySize));
    memset (chBinary, '0', 25+16*(m_iRentArraySize + m_iReturnArraySize));
    bool isSuccessed = false;
    int iLength = 0;

    //��˽������ת���ɶ���������
    //վ����ת������
    isSuccessed = IntegerIntoBinary(m_iStationID, chBinary+4);
    //������󼯺��ܳ���ת������
    isSuccessed = IntegerIntoBinary(m_iRentArrayLength, chBinary+8);
    //�黹���󼯺��ܳ���ת������
    isSuccessed = IntegerIntoBinary(m_iReturnArrayLength, chBinary+12);
    //������󼯺�ʵ�ʴ�Сת������
    isSuccessed = IntegerIntoBinary(m_iRentArraySize, chBinary+16);
    //������󼯺�ת������
    for (int i=0; i<m_iRentArraySize; i++){
        memcpy (chBinary+20+i*16, m_pRentCount[i].getBinary(), 16);
    }
    //�黹���󼯺�ʵ�ʴ�Сת������
    isSuccessed = IntegerIntoBinary(m_iReturnArraySize, chBinary+20+m_iRentArraySize*16);
    //�黹���󼯺�ת������
    for (int i=0; i<m_iReturnArraySize; i++){
        memcpy (chBinary+24+m_iRentArraySize*16+i*16, m_pReturnCount[i].getBinary(), 16);
    }
    //ĩβ���һ�������ַ�
    memset (chBinary+24+16*(m_iRentArraySize + m_iReturnArraySize), '\0', 1);
    //ͷ�������������
    iLength = 25+16*(m_iRentArraySize + m_iReturnArraySize);
    isSuccessed = IntegerIntoBinary(iLength, chBinary);

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
int CEntityStationCount::getBinaryLength(){
    if (m_iStationID == -1){
        return 25;
    }

    return (24+16*(m_iRentArraySize + m_iReturnArraySize) + 1);
}

/**
���ƣ�update
˵����ʹ���ֽ����ݸ���
���������¶���������
����ֵ���Ƿ���³ɹ�
����ʱ�䣺2015/10/9*/
bool CEntityStationCount::update(const unsigned char *chBuffer){

    int iAllLength = 0;
    unsigned char *pTempInt = (unsigned char *)malloc (4);
    memset (pTempInt, 0, 4);

    //ת��������
    memcpy (pTempInt, chBuffer, 4);
    iAllLength = BinaryIntoInteger(pTempInt);
    memset (pTempInt, 0, 4);

    //תվ����
    memcpy (pTempInt, chBuffer+4, 4);
    m_iStationID = BinaryIntoInteger(pTempInt);
    memset (pTempInt, 0, 4);

    //ת������������ܳ���
    memcpy (pTempInt, chBuffer+8, 4);
    m_iRentArrayLength = BinaryIntoInteger(pTempInt);
    memset (pTempInt, 0, 4); 

    //ת�黹���������ܳ���
    memcpy (pTempInt, chBuffer+12, 4);
    m_iReturnArrayLength = BinaryIntoInteger(pTempInt);
    memset (pTempInt, 0, 4); 

    /*תʵ�ʽ����*/
    memcpy (pTempInt, chBuffer+16, 4);
    m_iRentArraySize = BinaryIntoInteger(pTempInt);
    memset (pTempInt, 0, 4);

    /*ת�������*/
	if (m_iRentArraySize != 0){
        unsigned char *pTempBuf = (unsigned char *)malloc (16);
		memset(pTempBuf, 0, 16);
        int iSectionLength = 0;
        memset (pTempBuf, 0, 16);
        for (int i=0; i<m_iRentArraySize; i++){
            memcpy (pTempBuf, chBuffer+20+iSectionLength, 16);
            m_pRentCount[i].update(pTempBuf);
            iSectionLength += 16;
            memset (pTempBuf, 0, 16);
        }
        free (pTempBuf);
        pTempBuf = NULL;
    }


    /*תʵ�ʹ黹��*/
    memcpy (pTempInt, chBuffer+20+16*m_iRentArraySize, 4);
    m_iReturnArraySize = BinaryIntoInteger(pTempInt);
    memset (pTempInt, 0, 4);

    /*ת�黹����*/
	if (m_iReturnArraySize != 0){
        unsigned char *pTempBuf = (unsigned char *)malloc (16);
        int iSectionLength = 0;
        memset (pTempBuf, 0, 16);
        for (int i=0; i<m_iReturnArraySize; i++){
            memcpy (pTempBuf, chBuffer+20+iSectionLength, 16);
            m_pReturnCount[i].update(pTempBuf);
            iSectionLength += 16;
            memset (pTempBuf, 0, 16);
        }
        free (pTempBuf);
        pTempBuf = NULL;
    }


    free (pTempInt);
    pTempInt = NULL;
    return true;
}

/**
˵��������������ͱ���ת�ɶ���������
���룺��ת���ͱ���������ת����Ķ������������ݵ��ַ�������(���ڲ������ڴ�)
����ֵ���Ƿ�ת���ɹ�
����ʱ�䣺2015/10/21*/
bool CEntityStationCount::IntegerIntoBinary(const int iNumIn, unsigned char *chBinaryOut){
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
int CEntityStationCount::BinaryIntoInteger(const unsigned char *chBinaryIn){
    int iNum = 0;
    long int *iNumNew = new long int();

    memcpy ((unsigned char *)iNumNew, chBinaryIn, 4);
    iNum = *iNumNew;

    delete iNumNew;
    iNumNew = NULL;
    return iNum;
}

char* CEntityStationCount::changeToChar()
{
	char* cStationID = new char();
	char* cStationCount = new char();
	char* cLeft = "(";
	char* cRight = ")";
	char* cRent = "Rent:";
	char* cReturn = "Return:";
	
	/*��վ����ת����char���ַ���*/
	itoa(m_iStationID,cStationID,10);

	/*ƴ���ַ���*/
	strcat(cStationCount,cLeft);
	strcat(cStationCount,cStationID);
	/*����ͳ�Ƶ��ַ���ƴ�ӵ�վ��ͳ����*/
	/*������¼Ϊ�գ��ͷ���()*/
	strcat(cStationCount,cRent);
	if(m_iRentArraySize==0)
	{
		strcat(cStationCount,cLeft);
		strcat(cStationCount,cRight);
	}
	else
	{
		for(int i=0;i<m_iRentArraySize;i++)
		{
			strcat(cStationCount,m_pRentCount[i].changeToChar());
		}
	}
	/*����ͳ�Ƶ��ַ���ƴ�ӵ�վ��ͳ����*/
	/*�������¼Ϊ�գ��ͷ���()*/
	strcat(cStationCount,cReturn);
	if(m_iReturnArraySize==0)
	{
		strcat(cStationCount,cLeft);
		strcat(cStationCount,cRight);		
	}
	else
	{
		for(int i=0;i<m_iReturnArraySize;i++)
		{
			strcat(cStationCount,m_pReturnCount[i].changeToChar());
		}
	}
	strcat(cStationCount,cRight);

	return cStationCount;
}

int CEntityStationCount::getStationID()
{
	return m_iStationID;
}

string CEntityStationCount::changeToStrstream()
{
	stringstream strstreamStationCount;
	char* cLeft = "(";
	char* cRight = ")";
	char* cRent = "Rent:";
	char* cReturn = "Return:";

	strstreamStationCount<<cLeft;
	strstreamStationCount<<m_iStationID;
	/*����ͳ�Ʒ����ַ���*/
	strstreamStationCount<<cRent;
	if(m_iRentArraySize==0)
	{
		strstreamStationCount<<cLeft;
		strstreamStationCount<<cRight;
	}
	else
	{
		for(int i=0;i<m_iRentArraySize;i++)
		{
			strstreamStationCount<<m_pRentCount[i].changeToStrstream();
		}
	}

	/*����ͳ�Ʒ����ַ���*/
	strstreamStationCount<<cReturn;
	if(m_iReturnArraySize==0)
	{
		strstreamStationCount<<cLeft;
		strstreamStationCount<<cRight;		
	}
	else
	{
		for(int i=0;i<m_iReturnArraySize;i++)
		{
			strstreamStationCount<<m_pReturnCount[i].changeToStrstream();
		}
	}
	strstreamStationCount<<cRight;

	string strStationCount(strstreamStationCount.str());

	return strStationCount;

}

bool CEntityStationCount::checkRentRelatedStationID(int iRelatedStationID)
{
	for(int i=0;i<m_iRentArraySize;i++)
	{
		if(m_pRentCount[i].getRelatedStationID()==iRelatedStationID)
		{
			return true;
		}
	}
	return false;
}

bool CEntityStationCount::checkReturnRelatedStationID(int iRelatedStationID)
{
	for(int i=0;i<m_iReturnArraySize;i++)
	{
		if(m_pReturnCount[i].getRelatedStationID()==iRelatedStationID)
		{
			return true;
		}
	}
	return false;
}

CEntityCount* CEntityStationCount::getRentCount(int iRelatedStationID)
{
	for(int i=0;i<m_iRentArraySize;i++)
	{
		if(m_pRentCount[i].getRelatedStationID()==iRelatedStationID)
		{
			return &m_pRentCount[i];
		}
	}
	return NULL;	
}

CEntityCount* CEntityStationCount::getReturnCount(int iRelatedStationID)
{
	for(int i=0;i<m_iReturnArraySize;i++)
	{
		if(m_pReturnCount[i].getRelatedStationID()==iRelatedStationID)
		{
			return &m_pReturnCount[i];
		}
	}
	return NULL;	
}