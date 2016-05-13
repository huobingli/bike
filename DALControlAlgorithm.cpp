#include"stdafx.h"
#include "DALControlAlgorithm.h"

CControlAlgorithm::CControlAlgorithm(const CDALFile *objTargetFileIn, const CDALFile *objRelationFileIn){
    m_objTargetFile = (CDALFile *)objTargetFileIn;
    m_objRelationFile = (CDALFile *)objRelationFileIn;
}

/**
˵��������������ͱ���ת�ɶ���������
��������ת���ͱ���������ת����Ķ������������ݵ��ַ�������(���ڲ������ڴ�)
����ֵ���Ƿ�ת���ɹ�
����ʱ�䣺2015/10/21*/
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
˵����������Ķ���������ת�����ͱ���
�������������������ݵ��ַ�������(���ڲ������ڴ�)
����ֵ��ת���ɹ������ͱ��� 
����ʱ�䣺2015/10/21*/
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
˵������ȡ����������-
�����������Ƽ���
����ֵ��������
����ʱ�䣺2015/10/23*/
int CControlAlgorithm::getTotalNum(const unsigned char *chBufferIn){

    //��ȡ��������;
    int *iLength = new int();
    int iNum = 0;

    memcpy ((unsigned char *)iLength, chBufferIn, 4);
    iNum = *iLength + CONTRL_STATUS_FILELD + 1;

    delete iLength;
    iLength = NULL;
    return iNum;
}

/**
˵������ȡ����ɷ�����
��������¼��
����ֵ���ɷ�����
����ʱ�䣺2015/10/8*/
int CControlAlgorithm::getGroupNum(const unsigned char *chBufferIn){

    //��ȡ����������
    int iTotalNum = getTotalNum(chBufferIn);

    //��ȡ�ɷ�����
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
˵������ȡʱ��Ƭ�������ݶ���
������ʱ��Ƭ���������ƶ���Ϳ�ʼλ��
����ֵ���Ƿ�ɹ�
����ʱ�䣺2015/10/5*/
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
˵����д��������ݶ���
�������������ݶ����ƶ���Ϳ�ʼλ��
����ֵ���Ƿ�ɹ�
����ʱ�䣺2015/10/5*/
bool CControlAlgorithm::writeTimeSliceRelatedBinaryObject(const unsigned char *chBufferIn, int iPosStartIn){
    bool isSuccessed = false;

    //��ȡ��Ч������
    int iTotalLength = this->getTotalNum(chBufferIn);
    //��ȡ�ɷ�����
    int iGroupNum = this->getGroupNum(chBufferIn);
    unsigned char *chData = (unsigned char *)malloc (iTotalLength);
    unsigned char *chTemp = (unsigned char *)malloc (sizeof (int));
    memset (chData, 0, iTotalLength);
    memset (chTemp, 0, sizeof (int));

    //�������Ч������
    isSuccessed = IntegerIntoBinary(iTotalLength, chTemp);
    if (!isSuccessed){
        return false;
    }
    memcpy (chData, chTemp, 4);

    //��ӿ���
    isSuccessed = IntegerIntoBinary(iGroupNum, chTemp);
    if (!isSuccessed){
        return false;
    }
    memcpy (chData+4, chTemp, 4);  
    memcpy (chData+12, chBufferIn, iTotalLength-13);
    memset (chData+iTotalLength-1, '\0', 1);        //��ӻ��з�У���

    this->m_objRelationFile->writeToFile(chData,iPosStartIn);

    free (chData);
    chData = NULL;
    free (chTemp);
    chTemp = NULL;
    return true;
}

/**
˵������ȡʱ��Ƭ�������ݶ���
��ڲ�����ʱ��Ƭ���������ƶ���Ϳ�ʼλ��
����ֵ���Ƿ�ɹ�
����ʱ�䣺2015/10/8*/
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
