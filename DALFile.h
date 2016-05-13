#pragma once
#include "DALConfiguration.h"
#include "DALBlock.h"
#include "stdio.h"
/**
���ƣ�CDALFile
˵������װblock��ʵ�����ݵĶ�д
����ʱ�䣺2015/10/8*/
class CDALFile{
    CDALBlock *m_pBlock;    //�������ݿ�
    FILE *m_pFP;            //�ļ���������ָ��
    char *m_chFileName;     //�洢���ļ���
    char *m_chFlag;         //�ļ��Ĵ򿪷�ʽ

    /**
    ���ƣ�moveSeek
    ˵�������µ�ǰ����ָ��λ��
    ����ֵ���Ƿ��ƶ��ɹ�
    ����ʱ�䣺2015/10/11*/
    bool moveSeek(int iPosIn);

   /**
    ���ƣ�write
    ˵����д��
    ��������ŵ�ַ
    ����ֵ������д����
    ����ʱ�䣺2015/10/11*/
    int write(const CDALBlock *pBlockIn);

    /**
    ���ƣ�read
    ˵������ȡ
    ��������ŵ�ַ
    ����ֵ�����ζ�ȡ��
    ����ʱ�䣺2015/10/11*/
    int read(CDALBlock *&pBlock);

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
    ˵������ȡ����������-
    �����������Ƽ���
    ����ֵ��������
    ����ʱ�䣺2015/10/23*/
    int getTotalNum(const unsigned char *chBufferIn);

    /**
    ˵������ȡ����ɷ�����
    ��������¼��
    ����ֵ���ɷ�����
    ����ʱ�䣺2015/10/8*/
    int getGroupNum(const unsigned char *chBufferIn);

public:
    /**
    ���ƣ�����*/
    CDALFile(const char *chFileName, const char *chFlag);

    /**
    ����*/
    ~CDALFile();

    /**
    ˵������ʼ�����ļ�����
    ����ֵ���Ƿ��ʼ���ɹ�
    ����ʱ�䣺2015/7/20*/
    bool init (char *chFileName);

    /**
    ˵�������ļ�
    ����ֵ���Ƿ�򿪳ɹ�
    ����ʱ�䣺2015/10/8*/
    bool openFile();

    /**
    ˵�����ر��ļ�
    ����ֵ���Ƿ�رճɹ�
    ����ʱ�䣺2015/10/8*/
    bool closeFile();
	
    /**
    ����:���������ݣ�д���λ��
    ����ֵ���Ƿ�д��ɹ�
    ����ʱ�䣺2015/10/8*/
    bool writeToFile(const unsigned char *pBinaryIn, int iBlockPos);

    /**
    ����:���飬��ȡλ��
    ����ֵ���Ƿ��ȡ�ɹ�
    ����ʱ�䣺2015/10/8*/
    bool readFromFile(unsigned char *&pBinaryOut, int iBlockPos);
	
};
