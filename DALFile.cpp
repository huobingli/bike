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
˵�������µ�ǰ����ָ��λ��
����ֵ���Ƿ��ƶ��ɹ�
����ʱ�䣺2015/10/11*/
bool CDALFile::moveSeek(int iPosIn){
    return true;
}

/**
˵������ȡ
��������ŵ�ַ
����ֵ�����ζ�ȡ��
����ʱ�䣺2015/10/11*/
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
˵����д��
��������ŵ�ַ
����ֵ������д����
����ʱ�䣺2015/10/11*/
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
˵�������ļ�
����ֵ���Ƿ�򿪳ɹ�
����ʱ�䣺2015/10/8*/
bool CDALFile::openFile(){
    m_pFP = fopen (m_chFileName, m_chFlag);

    if (m_pFP != 0){
        return true;
    }
    
    return false;
}

/**
˵�����ر��ļ�
����ֵ���Ƿ�رճɹ�
����ʱ�䣺2015/10/8*/
bool CDALFile::closeFile(){
    if (fclose (m_pFP) == 0){
        return true;
    }
    return false;
}

/**
˵������ȡ����������-
�����������Ƽ���
����ֵ��������
����ʱ�䣺2015/10/23*/
int CDALFile::getTotalNum(const unsigned char *chBufferIn){

    //��ȡ��������;
    int *iLength = new int();
    int iNum = 0;

    memcpy ((unsigned char *)iLength, chBufferIn, 4);
    iNum = *iLength;

    delete iLength;
    iLength = NULL;
    return iNum;
}

/**
˵������ȡ����ɷ�����
��������¼��
����ֵ���ɷ�����
����ʱ�䣺2015/10/8*/
int CDALFile::getGroupNum(const unsigned char *chBufferIn){
    
    //��ȡ������;
    int *iGroupNum = new int();
    int iNum = 0;

    memcpy ((unsigned char *)iGroupNum, chBufferIn+4, 4);
    iNum = *iGroupNum;

    delete iGroupNum;
    iGroupNum = NULL;

    return iNum;
}

/**
����:���飬д��λ��
����ֵ���Ƿ�д��ɹ�
����ʱ�䣺2015/10/8*/
bool CDALFile::writeToFile(const unsigned char *pBinaryIn, int iBlockPos){
    if (iBlockPos != DEFAULT_POS){
        moveSeek(iBlockPos);
    }

    int iTotalNum = this->getTotalNum(pBinaryIn);  //��������
    int iGroupNum = this->getGroupNum(pBinaryIn);  //�ܷ�����
    int iPos = 0;                                  //��ǰ�з�λ��
    int iBlockDataLength = 0;                      //������Ч������
    int iBlockLength = 0;                          //��������������
    CDALBlock *objBlock = new CDALBlock();
    unsigned char *chBlockData;                              //������Ч����
    chBlockData= (unsigned char *)malloc (BLOCK_SIZE_DATA);  
    unsigned char *chBlock = NULL;                           //������������
    memset (chBlockData, 0, BLOCK_SIZE_DATA);

    //���飬�ӿ�ͷ��д��
    while (iGroupNum > 0){
       
        iBlockDataLength = (iTotalNum-iPos)/BLOCK_SIZE_DATA>=1? BLOCK_SIZE_DATA: iTotalNum-iPos;//��ʵ�ı�����Ч������
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
����:���飬��ȡλ��
����ֵ���Ƿ��ȡ�ɹ�
����ʱ�䣺2015/10/8*/
bool CDALFile::readFromFile(unsigned char *&pBinaryOut, int iBlockPos){
    if (iBlockPos != DEFAULT_POS){
        moveSeek(iBlockPos);
    }

    //fseek (m_pFP,0 ,SEEK_SET);

    bool isSuccessed = false;
    int iTotalNum = 0;  //��������
    int iGroupNum = 0;  //�ܷ�����
    int iPos = 0;       //��ǰ�з�λ��
    int iBlockDataLength = 0;                      //������Ч������
    unsigned char *chBlockData = NULL;             //������Ч����
    chBlockData= (unsigned char *)malloc (BLOCK_SIZE_DATA);  
    memset (chBlockData, 0, BLOCK_SIZE_DATA);

    //��ȡ�׿�����
    CDALBlock *objBlock = new CDALBlock();
    if (this->read(objBlock) == -1){
        free (chBlockData);
        chBlockData = NULL;
        return false;
    }
    isSuccessed = objBlock->getValidData(chBlockData, iBlockDataLength);
    iTotalNum = this->getTotalNum(chBlockData);  //��ȡ��������
    iGroupNum = this->getGroupNum(chBlockData);  //��ȡ�ܷ�����
    iGroupNum --;
    pBinaryOut = (unsigned char *)malloc (iTotalNum);  
    memset (pBinaryOut, 0, iTotalNum);

    //��װ������
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
˵��������������ͱ���ת�ɶ���������
��������ת���ͱ���������ת����Ķ������������ݵ��ַ�������(���ڲ������ڴ�)
����ֵ���Ƿ�ת���ɹ�
����ʱ�䣺2015/10/21*/
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
˵����������Ķ���������ת�����ͱ���
�������������������ݵ��ַ�������(���ڲ������ڴ�)
����ֵ��ת���ɹ������ͱ���
����ʱ�䣺2015/10/21*/
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