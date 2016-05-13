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
说明：将传入的整型变量转成二进制类型
输入：待转整型变量，接收转换后的二进制类型数据的字符串变量(在内部分配内存)
返回值：是否转化成功
更新时间：2015/10/21*/
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
说明：将传入的二进制类型转成整型变量
输入：二进制类型数据的字符串变量(在内部分配内存)
返回值：转化成功的整型变量 
更新时间：2015/10/21*/
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
名称：getBinary
说明：获取本对象转成的二进制数据
返回值：二进制数据集合
更新时间：2015/10/21*/
unsigned char *CEntityCount::getBinary(){
    unsigned char *chBinary = (unsigned char *)malloc (16);
    bool isSuccessed = false;
    memset (chBinary, 0, 16);

    //将私有属性转化成二进制类型
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
名称：getBinaryLength
说明：获取本对象转成的二进制数据的长度
返回值：二进制数据长度
更新时间：2015/10/21*/
int CEntityCount::getBinaryLength(){
    if (m_iRelatedStationID == -1){
        return 0;
    }
    return 16;
}

/**
名称：update
说明：使用字节数据更新
参数：更新二进制数组
返回值：是否更新成功
更新时间：2015/10/9*/
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

	/*将各个属性转换成char型字符串*/
	itoa(m_iRelatedStationID,cRelatedStationID,10);
	itoa(m_iMaxCostTime,cMaxCostTime,10);
	itoa(m_iMinCostTime,cMinCostTime,10);
	itoa(m_iOperatedTimes,cOperatedTimes,10);

	/*拼接字符串*/
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
	/*将各个属性放进字符串*/
	strstreamCount<<cLeft;
	strstreamCount<<m_iRelatedStationID;
	strstreamCount<<cBlank;
	strstreamCount<<m_iMaxCostTime;
	strstreamCount<<cBlank;
	strstreamCount<<m_iMinCostTime;
	strstreamCount<<cBlank;
	strstreamCount<<m_iOperatedTimes;
	strstreamCount<<cRight;

	/*将stringstream转换成string*/
	string strCount(strstreamCount.str());


	return strCount;	
}

int CEntityCount::getRelatedStationID()
{
	return m_iRelatedStationID;
}