#pragma once

#include <iostream>
#include <fstream>
#include <string.h>
#include <strstream>
#include "EntityTripDataSet.h"
#include "DALConfiguration.h"

using namespace std;

struct BitFied{
    unsigned char chFlag:1;
};

/**
˵����ԭ���ݶ�ȡ
����ʱ��:2015/10/16*/
class CDALOriginalFile{
    char *m_chFileName;                //Դ�ļ���
    float m_fReadAreadyPos;            //�ļ���ǰ��ȡλ��
    struct BitFied *m_WriteReadFlag;   //�ļ���д��־
    ifstream m_inputFile;              //����� 
    ofstream m_outputFile;             //������ 

public:
    CDALOriginalFile(const char *chFileName, const char *chFlag);
    ~CDALOriginalFile();
public:
    /**
    ˵������ȡ�軹��¼����
    �������軹���󼯺ϣ����ζ�ȡ��¼��
    ����ֵ���Ƿ��ȡ�ɹ�
    ����ʱ�䣺2015/10/16*/
    bool readTripRecord(CEntityTripDataSet *&pcsStationSetOut, int iNumIn);

    /**
    ˵�������ļ�
    ����ֵ���Ƿ�򿪳ɹ�
    ����ʱ�䣺2015/10/16*/
    bool openFile(int iFlag);

    /**
    ˵�����ر��ļ�
    ����ֵ���Ƿ�رճɹ�
    ����ʱ�䣺2015/10/16*/
    bool closeFile();

    /**
    ˵����������д���ļ� 
    ������Ҫд����ַ���
    ����ֵ���Ƿ�д��ɹ�
    ����ʱ�䣺2015/11/5*/
    bool writeStdCheck (char *chTest);
};
