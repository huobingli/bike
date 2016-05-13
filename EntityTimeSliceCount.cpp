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
名称：getBinary
说明：获取本对象转成的二进制数据
返回值：二进制数据集合
更新时间：2015/10/21*/
unsigned char *CEntityTimeSliceCount::getBinary(){
    unsigned char *chBinary;
    bool isSuccessed = false;
    int iTotalLength = 21;
    int iDataLength = 20;

    //获取总数据量
    for (int i=0; i<m_iArraySize; i++){
        iTotalLength += m_pStationCount[i].getBinaryLength();
    }
    chBinary = (unsigned char *)malloc (iTotalLength);
    memset (chBinary, '0', iTotalLength);

    //将私有属性转化成二进制类型
    //头部添加总数据量
    isSuccessed = IntegerIntoBinary(iTotalLength, chBinary);
    //时间片序号转二进制
    isSuccessed = IntegerIntoBinary(m_iTimeSliceID, chBinary+4);
    //生存周期转二进制
    isSuccessed = IntegerIntoBinary(m_iSurvivalTime, chBinary+8);
    //时间片可放站点总量转二进制
    isSuccessed = IntegerIntoBinary(m_iArrayLength, chBinary+12);
    //实际站点数目转二进制
    isSuccessed = IntegerIntoBinary(m_iArraySize, chBinary+16);

    //站点统计对象集合转二进制
    for (int i=0; i<m_iArraySize; i++){
        memcpy (chBinary+iDataLength, m_pStationCount[i].getBinary(), m_pStationCount[i].getBinaryLength());
        iDataLength += m_pStationCount[i].getBinaryLength();
    }
    //末尾添加一个结束字符
    memset (chBinary+iTotalLength-1, '\0', 1);


    if (isSuccessed){
        return chBinary;
    }
    return NULL;
}

/**
名称：getBinaryLength
说明：获取本对象转成的二进制数据的长度
返回值：二进制数据长度
更新时间：2015/10/21*/
int CEntityTimeSliceCount::getBinaryLength()
{
    bool isSuccessed = false;

    if (m_iTimeSliceID != -1){
        //获取总数据量
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
名称：update
说明：使用字节数据更新
参数：更新二进制数组
返回值：是否更新成功
更新时间：2015/10/9*/
bool CEntityTimeSliceCount::update(const unsigned char *chBuffer){

    int iAllLength = 0;
    unsigned char *pTempInt = (unsigned char *)malloc (4);
    memset (pTempInt, 0, 4);

    //转总数据量
    memcpy (pTempInt, chBuffer, 4);
    iAllLength = BinaryIntoInteger(pTempInt);
    memset (pTempInt, 0, 4);

    //转时间片序号
    memcpy (pTempInt, chBuffer+4, 4);
    m_iTimeSliceID = BinaryIntoInteger(pTempInt);
    memset (pTempInt, 0, 4);

    //转生存周期
    memcpy (pTempInt, chBuffer+8, 4);
    m_iSurvivalTime = BinaryIntoInteger(pTempInt);
    memset (pTempInt, 0, 4);

    //转本时间片可放站点总量
    memcpy (pTempInt, chBuffer+12, 4);
    m_iArrayLength = BinaryIntoInteger(pTempInt);
    memset (pTempInt, 0, 4);

    //转实际站点数目
    memcpy (pTempInt, chBuffer+16, 4);
    m_iArraySize = BinaryIntoInteger(pTempInt);
    memset (pTempInt, 0, 4);
   
    /*转站点统计对象数组*/
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
说明：将传入的整型变量转成二进制类型
输入：待转整型变量，接收转换后的二进制类型数据的字符串变量(在内部分配内存)
返回值：是否转化成功
更新时间：2015/10/21*/
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
说明：将传入的二进制类型转成整型变量
输入：二进制类型数据的字符串变量(在内部分配内存)
返回值：转化成功的整型变量 
更新时间：2015/10/21*/
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

	/*将时间片编号转换成char型字符串*/
	itoa(m_iTimeSliceID,cTimeSliceID,10);
	/*将生存周期转换成char型字符串*/
	itoa(m_iSurvivalTime,cSurvivalTime,10);

	/*拼接字符串*/
	strcat(cTimeSliceCount,cLeft);
	strcat(cTimeSliceCount,cTimeSliceID);
	strcat(cTimeSliceCount,cBlank);
	strcat(cTimeSliceCount,cSurvivalTime);
	/*将站点统计拼接到时间片统计中*/
	/*如果站点统计为空，就返回()*/
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

