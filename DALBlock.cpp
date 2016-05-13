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
���ƣ�����*/
CDALBlock::~CDALBlock(){
    m_iBinaryLength = 0;
    free (m_pchBinaryArrary);
    m_pchBinaryArrary = NULL;
}

bool CDALBlock::init(){
    m_pchBinaryArrary = new unsigned char [BLOCK_SIZE_DATA];//�涨һ�����СΪ500�ֽ�
    memset (m_pchBinaryArrary, 0, BLOCK_SIZE_DATA);
    return 0;
}

/**
˵������ȡ��Ч����
����:���������ݵ�ַ,��Ч������
����ֵ���Ƿ��ȡ�ɹ�
����ʱ�䣺2015/10/8*/
bool CDALBlock::getValidData(unsigned char*& pchBinary, int &iLength){
    pchBinary = m_pchBinaryArrary;
    iLength = m_iBinaryLength;

    if (pchBinary != NULL){
        return true;
    }
    return false;
}

/**
˵������ȡ��Ч���ݳ���
����ֵ����Ч���ݳ���
����ʱ�䣺2015/10/9*/
int CDALBlock::getVailDataLength(){
    return m_iBinaryLength; 
}

/**
˵���������ݷ�����Ч�����ֶ�
����ֵ���Ƿ���óɹ�
����ʱ�䣺2015/10/8*/
bool CDALBlock::putValidData(unsigned char* pchBinary,  int iLength){

    if (pchBinary != NULL || iLength != 0){
        memcpy (m_pchBinaryArrary, pchBinary, iLength);
        m_iBinaryLength = iLength; 
        return true;
    }
    return false;
}

/**
������Ҫ��������ݣ�Ҫ�����������
˵���������ݷ�����Ч�����ֶ�
����ֵ���Ƿ���óɹ�
����ʱ�䣺2015/10/25*/
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
˵������block����������
����ֵ���Ƿ����óɹ�
����ʱ�䣺2015/10/8*/
bool CDALBlock::resetBlock(){
    m_iBinaryLength = 0;
    memset (m_pchBinaryArrary, 0, BLOCK_SIZE_DATA);
    return true;
}


/**
˵������ȡ��������
��ڲ���:���������ݵ�ַ,��Ч������
����ֵ���Ƿ��ȡ�ɹ�
����ʱ�䣺2015/10/23*/
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
˵��������������ͱ���ת�ɶ���������
��������ת���ͱ���������ת����Ķ������������ݵ��ַ�������(���ڲ������ڴ�)
����ֵ���Ƿ�ת���ɹ�
����ʱ�䣺2015/10/21*/
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
˵����������Ķ���������ת�����ͱ���
�������������������ݵ��ַ�������(���ڲ������ڴ�)
����ֵ��ת���ɹ������ͱ��� 
����ʱ�䣺2015/10/21*/
int CDALBlock::BinaryIntoInteger(const unsigned char *chBinaryIn){
    int iNum = 0;
    long int *iNumNew = new long int();

    memcpy ((unsigned char *)iNumNew, chBinaryIn, 4);
    iNum = *iNumNew;

    delete iNumNew;
    iNumNew = NULL;
    return iNum;
}