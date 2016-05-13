#pragma once
#include <string.h>
#include <stdlib.h>
#include "DALConfiguration.h"
/**
���ƣ�CDALBLock
˵������װ�˵������ݣ��������󼯺�ת����������ģ��
     �Լ�����������ת���󼯺�ģ�� 
����ʱ�䣺2015/7/20*/
class CDALBlock{
    unsigned char* m_pchBinaryArrary;   //���������ݿ�
    int m_iBinaryLength;                //���������ݳ���

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
public:
    /**
    ���ƣ�����*/
    CDALBlock();
    CDALBlock(CDALBlock *&p);
    
    /**
    ���ƣ�����*/
    ~CDALBlock();

    /**
    ˵������ʼ��block����
    ����ֵ���Ƿ��ʼ���ɹ�
    ����ʱ�䣺2015/7/20*/
    bool init();

    /**
    ˵������ȡ��Ч����
    ����:���������ݵ�ַ,��Ч������
    ����ֵ���Ƿ��ȡ�ɹ�
    ����ʱ�䣺2015/10/8*/
    bool getValidData(unsigned char*& pchBinary, int &iLength);

    /**
    ˵������ȡ��������
    ����:���������ݵ�ַ,��Ч������
    ����ֵ���Ƿ��ȡ�ɹ�
    ����ʱ�䣺2015/10/8*/
    bool getBlockData(unsigned char*& pchBinary, int &iLength);

    /*
    ˵������ȡ��Ч���ݳ���
    ����ֵ����Ч���ݳ���
    ����ʱ�䣺2015/10/9*/
    int getVailDataLength();

    /**
    ������Ҫ�������Ч���ݣ�Ҫ�������Ч������
    ˵���������ݷ�����Ч�����ֶ�
    ����ֵ���Ƿ���óɹ�
    ����ʱ�䣺2015/10/8*/
    bool putValidData(unsigned char* pchBinary,  int iLength);

    /**
    ������Ҫ��������ݣ�Ҫ�����������
    ˵���������ݷ�����Ч�����ֶ�
    ����ֵ���Ƿ���óɹ�
    ����ʱ�䣺2015/10/25*/
    bool putBlockData(unsigned char* pchBinary,  int iLength);

    /**
    ˵������block����������
    ����ֵ���Ƿ����óɹ�
    ����ʱ�䣺2015/10/8*/
    bool resetBlock();
};
