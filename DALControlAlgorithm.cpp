#include"stdafx.h"
#include "DALControlAlgorithm.h"

CControlAlgorithm::CControlAlgorithm(const CDALFile *objTargetFileIn, const CDALFile *objRelationFileIn){
    m_objTargetFile = (CDALFile *)objTargetFileIn;
    m_objRelationFile = (CDALFile *)objRelationFileIn;
}

/**
说明：将传入的整型变量转成二进制类型
参数：待转整型变量，接收转换后的二进制类型数据的字符串变量(在内部分配内存)
返回值：是否转化成功
更新时间：2015/10/21*/
bool CControlAlgorithm::IntegerIntoBinary(const int iNumIn, unsigned char *chBinaryOut){
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
参数：二进制类型数据的字符串变量(在内部分配内存)
返回值：转化成功的整型变量 
更新时间：2015/10/21*/
int CControlAlgorithm::BinaryIntoInteger(const unsigned char *chBinaryIn){
    int iNum = 0;
    long int *iNumNew = new long int();

    memcpy ((unsigned char *)iNumNew, chBinaryIn, 4);
    iNum = *iNumNew;

    delete iNumNew;
    iNumNew = NULL;
    return iNum;
}

/**
说明：获取所有数据量-
参数：二进制集合
返回值：数据量
更新时间：2015/10/23*/
int CControlAlgorithm::getTotalNum(const unsigned char *chBufferIn){

    //获取总数据量;
    int *iLength = new int();
    int iNum = 0;

    memcpy ((unsigned char *)iLength, chBufferIn, 4);
    iNum = *iLength + CONTRL_STATUS_FILELD + 1;

    delete iLength;
    iLength = NULL;
    return iNum;
}

/**
说明：获取所需可分组数
参数：记录数
返回值：可分组数
更新时间：2015/10/8*/
int CControlAlgorithm::getGroupNum(const unsigned char *chBufferIn){

    //获取所有数据量
    int iTotalNum = getTotalNum(chBufferIn);

    //获取可分组数
    int iTotalBlockNum;
    if (iTotalNum % 500 != 0){
        return iTotalBlockNum = (iTotalNum)/(BLOCK_SIZE - BLOCK_SIZE_STATUS_FIELD) + 1;
    }else{
        return iTotalBlockNum = (iTotalNum)/(BLOCK_SIZE - BLOCK_SIZE_STATUS_FIELD);
    }
}

CControlAlgorithm::~CControlAlgorithm(){
}

/**
说明：读取时间片关联数据对象
参数：时间片关联二进制对象和开始位置
返回值：是否成功
更新时间：2015/10/5*/
bool CControlAlgorithm::readTimeSliceStatisticalBinaryObject(unsigned char *&chBufferOut, int iPosStartIn){

    bool isSuccessed = false;
    unsigned char *chBuf = NULL;
    int iRealNum = 0;

    isSuccessed = m_objTargetFile->readFromFile(chBuf, iPosStartIn);
    if (isSuccessed){
        iRealNum = this->getTotalNum(chBuf);
        chBufferOut = (unsigned char *)malloc (iRealNum);
        memset (chBufferOut, 0, iRealNum);
        memcpy (chBufferOut, chBuf+12, iRealNum);
        return true;
    }
    return false;
}

/**
说明：写入待定数据对象
参数：待定数据二进制对象和开始位置
返回值：是否成功
更新时间：2015/10/5*/
bool CControlAlgorithm::writeTimeSliceRelatedBinaryObject(const unsigned char *chBufferIn, int iPosStartIn){
    bool isSuccessed = false;

    //获取有效数据量
    int iTotalLength = this->getTotalNum(chBufferIn);
    //获取可分组数
    int iGroupNum = this->getGroupNum(chBufferIn);
    unsigned char *chData = (unsigned char *)malloc (iTotalLength);
    unsigned char *chTemp = (unsigned char *)malloc (sizeof (int));
    memset (chData, 0, iTotalLength);
    memset (chTemp, 0, sizeof (int));

    //添加总有效数据量
    isSuccessed = IntegerIntoBinary(iTotalLength, chTemp);
    if (!isSuccessed){
        return false;
    }
    memcpy (chData, chTemp, 4);

    //添加块数
    isSuccessed = IntegerIntoBinary(iGroupNum, chTemp);
    if (!isSuccessed){
        return false;
    }
    memcpy (chData+4, chTemp, 4);  
    memcpy (chData+12, chBufferIn, iTotalLength-13);
    memset (chData+iTotalLength-1, '\0', 1);        //添加换行符校验符

    this->m_objRelationFile->writeToFile(chData,iPosStartIn);

    free (chData);
    chData = NULL;
    free (chTemp);
    chTemp = NULL;
    return true;
}

/**
说明：读取时间片关联数据对象
入口参数：时间片关联二进制对象和开始位置
返回值：是否成功
更新时间：2015/10/8*/
bool CControlAlgorithm::readTimeSliceRelatedBinaryObject(unsigned char *&chBufferOut, int iPosStartIn){
    
    bool isSuccessed = false;
    unsigned char *chBuf = NULL;
    int iRealNum = 0;

    isSuccessed = m_objRelationFile->readFromFile(chBuf, iPosStartIn);
    if (isSuccessed){
        iRealNum = this->getTotalNum(chBuf);
        chBufferOut = (unsigned char *)malloc (iRealNum);
        memset (chBufferOut, 0, iRealNum);
        memcpy (chBufferOut, chBuf+12, iRealNum);
        return true;
    }
    return false;
}
