#pragma once
#include <stdlib.h>
#include "DALFile.h"
#include "DALOriginalFile.h"

/**
˵����Ԥ�������
����ʱ��:2015/9/30*/
class CControlPre{
    CDALOriginalFile *m_objSourceFile;   //Դ�ļ�����(��ܿ���)��������
    CDALFile *m_objTargetFile;        //Ŀ���ļ�����(��ܿ���)��������
private:
    /**
    ˵��������������ͱ���ת�ɶ���������
    ��������ת���ͱ���������ת����Ķ������������ݵ��ַ�������
    ����ֵ���Ƿ�ת���ɹ�
    ����ʱ�䣺2015/10/21*/
    bool IntegerIntoBinary(const int iNumIn, unsigned char *chBinaryOut);

    /**
    ˵����������Ķ���������ת�����ͱ���
    �������������������ݵ��ַ�������(���ڲ������ڴ�)
    ����ֵ��ת���ɹ������ͱ��� 
    ����ʱ�䣺2015/10/21*/
    int BinaryIntoInteger(const unsigned char *chBinaryIn);
    /**
    ˵������ȡ����������
    �����������Ƽ���
    ����ֵ��������
    ����ʱ�䣺2015/10/23*/
    int getTotalNum(const unsigned char *chBufferIn);

    /**
    ˵������ȡ����ɷ�����
    �����������Ƽ���
    ����ֵ���ɷ�����
    ����ʱ�䣺2015/10/8*/
    int getGroupNum(const unsigned char *chBufferIn);
public:
    CControlPre(const CDALOriginalFile *objSourceFileIn, const CDALFile *objTargetFileIn);
    ~CControlPre();

    /**
    ˵������ȡԴ����
    �������ַ������ϺͿ�ʼλ��
    ����ֵ���Ƿ�ɹ�
    ����ʱ�䣺2015/10/5*/
    bool readSourceData(CEntityTripDataSet *&pBorrowDataOut, int iStartPosIn);
    
    /**
    ˵����д��ʱ��Ƭͳ�ƶ����ƶ���
    �����������ƶ���Ϳ�ʼλ��
    ����ֵ���Ƿ�ɹ�
    ����ʱ�䣺2015/10/5*/
    bool writeTimeSliceStatisticalBinaryObject(const unsigned char *chBufferIn, int iPosStartIn);
};

