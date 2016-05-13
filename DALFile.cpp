#include"stdafx.h"
#include "DALFile.h"

CDALFile::CDALFile(const char *chFileName, const char *chFlag)
    :
m_pBlock(0),
m_chFileName(0),
m_chFlag(0),
m_pFP(0){
    init((char *)chFileName);
}

CDALFile::~CDALFile(){

    if (m_pBlock != NULL && m_chFileName != NULL && m_chFlag != NULL){
        delete m_pBlock;
        delete m_chFileName;
        delete m_chFlag;
        m_chFlag = NULL;
        m_chFileName = NULL;
        m_pBlock = NULL;
    }
}

bool CDALFile::init(char *chFileName){
    m_chFileName = chFileName;
    m_chFlag = "rb+";
    return true;
}

/**
说明：更新当前操作指针位置
返回值：是否移动成功
更新时间：2015/10/11*/
bool CDALFile::moveSeek(int iPosIn){
    return true;
}

/**
说明：读取
参数：存放地址
返回值：本次读取量
更新时间：2015/10/11*/
int CDALFile::read(CDALBlock *&pBlockOut){
    int iRealNum = 0;
    bool isSuccessed = false;
    unsigned char *pBuf = (unsigned char *)malloc (BLOCK_SIZE);
    memset (pBuf, 0, BLOCK_SIZE);

    iRealNum = fread (pBuf, 1, BLOCK_SIZE, m_pFP);
    if (iRealNum == 0){
        free (pBuf);
        pBuf = NULL;
        return -1;
    }

    isSuccessed = pBlockOut->putBlockData(pBuf, iRealNum);
    if (!isSuccessed){
        free (pBuf);
        pBuf = NULL;
        return -1;
    }

    free (pBuf);
    pBuf = NULL;
    return iRealNum;
}

/**
说明：写入
参数：存放地址
返回值：本次写入量
更新时间：2015/10/11*/
int CDALFile::write(const CDALBlock *pBlockIn){
    int iRealNum = 0;
    bool isSuccessed = false;
    unsigned char *pBuf = NULL;
    CDALBlock *pTemp = (CDALBlock *)pBlockIn;
    unsigned char *pTempBuf = (unsigned char *)malloc (BLOCK_SIZE);
    memset (pTempBuf, 0, BLOCK_SIZE);

    isSuccessed = pTemp->getBlockData(pBuf, iRealNum);
    if (!isSuccessed){
        return -1;
    }

    memcpy (pTempBuf, pBuf, iRealNum);
    iRealNum = fwrite (pTempBuf, 1, BLOCK_SIZE, m_pFP);

    free (pBuf);
    pBuf = NULL;
    free (pTempBuf);
    pTempBuf = NULL;
    return iRealNum;
}

/**
说明：打开文件
返回值：是否打开成功
更新时间：2015/10/8*/
bool CDALFile::openFile(){
    m_pFP = fopen (m_chFileName, m_chFlag);

    if (m_pFP != 0){
        return true;
    }
    
    return false;
}

/**
说明：关闭文件
返回值：是否关闭成功
更新时间：2015/10/8*/
bool CDALFile::closeFile(){
    if (fclose (m_pFP) == 0){
        return true;
    }
    return false;
}

/**
说明：获取所有数据量-
参数：二进制集合
返回值：数据量
更新时间：2015/10/23*/
int CDALFile::getTotalNum(const unsigned char *chBufferIn){

    //获取总数据量;
    int *iLength = new int();
    int iNum = 0;

    memcpy ((unsigned char *)iLength, chBufferIn, 4);
    iNum = *iLength;

    delete iLength;
    iLength = NULL;
    return iNum;
}

/**
说明：获取所需可分组数
参数：记录数
返回值：可分组数
更新时间：2015/10/8*/
int CDALFile::getGroupNum(const unsigned char *chBufferIn){
    
    //获取分组数;
    int *iGroupNum = new int();
    int iNum = 0;

    memcpy ((unsigned char *)iGroupNum, chBufferIn+4, 4);
    iNum = *iGroupNum;

    delete iGroupNum;
    iGroupNum = NULL;

    return iNum;
}

/**
参数:单块，写入位置
返回值：是否写入成功
更新时间：2015/10/8*/
bool CDALFile::writeToFile(const unsigned char *pBinaryIn, int iBlockPos){
    if (iBlockPos != DEFAULT_POS){
        moveSeek(iBlockPos);
    }

    int iTotalNum = this->getTotalNum(pBinaryIn);  //总数据量
    int iGroupNum = this->getGroupNum(pBinaryIn);  //总分组数
    int iPos = 0;                                  //当前切分位置
    int iBlockDataLength = 0;                      //单块有效数据量
    int iBlockLength = 0;                          //单块整体数据量
    CDALBlock *objBlock = new CDALBlock();
    unsigned char *chBlockData;                              //单块有效数据
    chBlockData= (unsigned char *)malloc (BLOCK_SIZE_DATA);  
    unsigned char *chBlock = NULL;                           //单块整体数据
    memset (chBlockData, 0, BLOCK_SIZE_DATA);

    //分组，加块头，写入
    while (iGroupNum > 0){
       
        iBlockDataLength = (iTotalNum-iPos)/BLOCK_SIZE_DATA>=1? BLOCK_SIZE_DATA: iTotalNum-iPos;//真实的本块有效数据量
        if (iBlockDataLength == BLOCK_SIZE_DATA){
            memcpy (chBlockData, pBinaryIn+iPos, BLOCK_SIZE_DATA);
        }else{
            memcpy (chBlockData, pBinaryIn+iPos, iBlockDataLength);
        }
        objBlock->putValidData(chBlockData,iBlockDataLength);
        this->write(objBlock);
        objBlock->resetBlock();
        memset (chBlockData, 0, BLOCK_SIZE_DATA);
        iPos += BLOCK_SIZE_DATA;
        iGroupNum -- ;
    }
    
    delete objBlock;
    objBlock = NULL;
    free (chBlockData);
    chBlockData = NULL;
	return true;
}

/**
参数:单块，读取位置
返回值：是否读取成功
更新时间：2015/10/8*/
bool CDALFile::readFromFile(unsigned char *&pBinaryOut, int iBlockPos){
    if (iBlockPos != DEFAULT_POS){
        moveSeek(iBlockPos);
    }

    //fseek (m_pFP,0 ,SEEK_SET);

    bool isSuccessed = false;
    int iTotalNum = 0;  //总数据量
    int iGroupNum = 0;  //总分组数
    int iPos = 0;       //当前切分位置
    int iBlockDataLength = 0;                      //单块有效数据量
    unsigned char *chBlockData = NULL;             //单块有效数据
    chBlockData= (unsigned char *)malloc (BLOCK_SIZE_DATA);  
    memset (chBlockData, 0, BLOCK_SIZE_DATA);

    //获取首块数据
    CDALBlock *objBlock = new CDALBlock();
    if (this->read(objBlock) == -1){
        free (chBlockData);
        chBlockData = NULL;
        return false;
    }
    isSuccessed = objBlock->getValidData(chBlockData, iBlockDataLength);
    iTotalNum = this->getTotalNum(chBlockData);  //获取总数据量
    iGroupNum = this->getGroupNum(chBlockData);  //获取总分组数
    iGroupNum --;
    pBinaryOut = (unsigned char *)malloc (iTotalNum);  
    memset (pBinaryOut, 0, iTotalNum);

    //组装块数据
    memcpy (pBinaryOut, chBlockData, iBlockDataLength);
    iPos += iBlockDataLength;
    while (iGroupNum != 0){
        this->read(objBlock);
        isSuccessed = objBlock->getValidData(chBlockData, iBlockDataLength);
        memcpy (pBinaryOut +iPos, chBlockData, iBlockDataLength);
        //memset (pBinaryOut, 0, iTotalNum);
        iPos += iBlockDataLength;
        iGroupNum --;
    }
    memset (pBinaryOut +iTotalNum-1, '\0', 1);

    delete objBlock;
    objBlock = NULL;
    if (isSuccessed){
        return true;
    }
	return false;
}


/**
说明：将传入的整型变量转成二进制类型
参数：待转整型变量，接收转换后的二进制类型数据的字符串变量(在内部分配内存)
返回值：是否转化成功
更新时间：2015/10/21*/
bool CDALFile::IntegerIntoBinary(const int iNumIn, unsigned char *chBinaryOut){
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
int CDALFile::BinaryIntoInteger(const unsigned char *chBinaryIn){
    int iNum = 0;
    long int *iNumNew = new long int();

    memcpy ((unsigned char *)iNumNew, chBinaryIn, 4);
    iNum = *iNumNew;

    delete iNumNew;
    iNumNew = NULL;
    return iNum;
}

//bool CDALFile::readTest (unsigned char *&pBinaryOut){
//
//    //du qu
//    int i = -1;
//    pBinaryOut = (unsigned char *)malloc (5000);
//    memset (pBinaryOut, 0, 5000);
//    fseek (m_pFP, 0, SEEK_SET);
//    i = fread (pBinaryOut, 1, 5000, m_pFP);
//
//    return true;
//}

//bool CDALFile::writeTest (unsigned char *pBinaryIn){
//    int i = -1;
//    unsigned char *pBuf = (unsigned char *)malloc (5000);
//    memset (pBuf, 0, 5000);
//
//    memcpy (pBuf, pBinaryIn, 4801);
//    fseek (m_pFP, 0, SEEK_SET);
//    i = fwrite (pBuf, 1, 5000, m_pFP);
//
//    free (pBuf);
//    pBuf = NULL;
//    return true;
//
//}