#pragma once

#include "DALFile.h"

/**
˵�����㷨����
����ʱ�䣺2015/9/30*/
class CControlAlgorithm{
    CDALFile *m_objTargetFile;      //Ŀ���ļ�����(��ܿ���)��������
    CDALFile *m_objRelationFile;   //�����ļ�����(��ܿ���)��������

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
    ��ڲ����������Ƽ���
    ����ֵ���ɷ�����
    ����ʱ�䣺2015/10/8*/
    int getGroupNum(const unsigned char *chBufferIn);

public:
    CControlAlgorithm(const CDALFile *objTargetFileIn, const CDALFile *objRelationFileIn);
    ~CControlAlgorithm();

    /**
    ˵������ȡʱ��Ƭͳ�����ݶ���
    ��ڲ�����ʱ��Ƭͳ�ƶ����ƶ���Ϳ�ʼλ��
    ����ֵ���Ƿ�ɹ�
    ����ʱ�䣺2015/10/8*/
    bool readTimeSliceStatisticalBinaryObject(unsigned char *&chBufferOut, int iPosStartIn);
    
    /**
    ˵����д��ʱ��Ƭ�����������ݶ���
    ��ڲ�����ʱ��Ƭ������������ƶ���Ϳ�ʼλ��
    ����ֵ���Ƿ�ɹ�
    ����ʱ�䣺2015/10/8*/
    bool writeTimeSliceRelatedBinaryObject(const unsigned char *chBufferIn, int iPosStartIn);

    /**
    ˵������ȡʱ��Ƭ�������ݶ���
    ��ڲ�����ʱ��Ƭ���������ƶ���Ϳ�ʼλ��
    ����ֵ���Ƿ�ɹ�
    ����ʱ�䣺2015/10/8*/
    bool readTimeSliceRelatedBinaryObject(unsigned char *&chBufferOut, int iPosStartIn);
};
