#include"stdafx.h"
#include "DALBlock.h"

CDALBlock::CDALBlock()
:
m_pchBinaryArrary(0),
m_iBinaryLength(0){
    init();
}

CDALBlock::CDALBlock(CDALBlock *&p){
    p->getValidData(m_pchBinaryArrary, m_iBinaryLength);
}

/**
名称：构造*/
CDALBlock::~CDALBlock(){
    m_iBinaryLength = 0;
    free (m_pchBinaryArrary);
    m_pchBinaryArrary = NULL;
}

bool CDALBlock::init(){
    m_pchBinaryArrary = new unsigned char [BLOCK_SIZE_DATA];//规定一个块大小为500字节
    memset (m_pchBinaryArrary, 0, BLOCK_SIZE_DATA);
    return 0;
}

/**
说明：获取有效数据
参数:二进制数据地址,有效数据量
返回值：是否截取成功
更新时间：2015/10/8*/
bool CDALBlock::getValidData(unsigned char*& pchBinary, int &iLength){
    pchBinary = m_pchBinaryArrary;
    iLength = m_iBinaryLength;

    if (pchBinary != NULL){
        return true;
    }
    return false;
}

/**
说明：获取有效数据长度
返回值：有效数据长度
更新时间：2015/10/9*/
int CDALBlock::getVailDataLength(){
    return m_iBinaryLength; 
}

/**
说明：将数据放入有效数据字段
返回值：是否放置成功
更新时间：2015/10/8*/
bool CDALBlock::putValidData(unsigned char* pchBinary,  int iLength){

    if (pchBinary != NULL || iLength != 0){
        memcpy (m_pchBinaryArrary, pchBinary, iLength);
        m_iBinaryLength = iLength; 
        return true;
    }
    return false;
}

/**
参数：要放入的数据，要放入的数据量
说明：将数据放入有效数据字段
返回值：是否放置成功
更新时间：2015/10/25*/
bool CDALBlock::putBlockData(unsigned char* pchBinary,  int iLength){
    int *iRealNum = NULL;
    
    if (pchBinary != NULL || iLength != 0){
        iRealNum = new int();
        memcpy ((unsigned char *)iRealNum, pchBinary, 4);
        m_iBinaryLength = *iRealNum;
        memcpy (m_pchBinaryArrary, pchBinary + 12, m_iBinaryLength);
        delete iRealNum;
        iRealNum = NULL;
        return true;
    }
    return false;
}

/**
说明：将block中数据重置
返回值：是否重置成功
更新时间：2015/10/8*/
bool CDALBlock::resetBlock(){
    m_iBinaryLength = 0;
    memset (m_pchBinaryArrary, 0, BLOCK_SIZE_DATA);
    return true;
}


/**
说明：获取所有数据
入口参数:二进制数据地址,有效数据量
返回值：是否截取成功
更新时间：2015/10/23*/
bool CDALBlock::getBlockData(unsigned char*& pchBinary, int &iLength){
    bool isSuccessed = false;
    unsigned char *chBuf = (unsigned char *)malloc (BLOCK_SIZE);
    unsigned char *chInt = (unsigned char *)malloc (4);
    memset (chBuf, 0, BLOCK_SIZE);
    memset (chInt, 0, 4);
    isSuccessed = IntegerIntoBinary(m_iBinaryLength, chInt);
    if (!isSuccessed){
        return false;
    }
    memcpy (chBuf, chInt, 4);
    memcpy (chBuf+12, m_pchBinaryArrary, m_iBinaryLength);
    pchBinary = chBuf;
    iLength = m_iBinaryLength +12;

    free (chInt);
    chInt = NULL;
    return true;
}


/**
说明：将传入的整型变量转成二进制类型
参数：待转整型变量，接收转换后的二进制类型数据的字符串变量(在内部分配内存)
返回值：是否转化成功
更新时间：2015/10/21*/
bool CDALBlock::IntegerIntoBinary(const int iNumIn, unsigned char *chBinaryOut){
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
int CDALBlock::BinaryIntoInteger(const unsigned char *chBinaryIn){
    int iNum = 0;
    long int *iNumNew = new long int();

    memcpy ((unsigned char *)iNumNew, chBinaryIn, 4);
    iNum = *iNumNew;

    delete iNumNew;
    iNumNew = NULL;
    return iNum;
}