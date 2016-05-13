#include"stdafx.h"

#include "DALOriginalFile.h"

CDALOriginalFile::CDALOriginalFile(const char *chFileName, const char *chFlag)
:
m_fReadAreadyPos(0),
m_chFileName(0),
m_WriteReadFlag(0){

    //��ʼ��
    m_WriteReadFlag = (struct BitFied *) malloc (sizeof (struct BitFied));
    memset (m_WriteReadFlag, 0, sizeof (struct BitFied));
    m_chFileName = (char *)malloc (20);

    strcpy (m_chFileName, chFileName);   //�����ļ���
}

CDALOriginalFile::~CDALOriginalFile(){
    free (m_chFileName);
    m_chFileName = NULL;
}

/**
˵������txt�ļ��ж�ȡ��Ӧ������
��������ǰ�Ѷ�ȡ������������ʱ��ȡ�����ݱ���λ��
����ֵ���Ƿ��ȡ�ɹ� 
����ʱ�䣺2015/10/16*/
bool CDALOriginalFile::readTripRecord(CEntityTripDataSet *&pRecordSetOut, int iNumIn){
    /*��ʼ������ģ��*/
    string temp;
    int iLineAready = 0;//���δ��Ѷ�ȡ�������������мƣ���ȷ���ֿ��ȡ��������

    /*δ��ȷ��ȡ�ļ�*/
    if (!m_inputFile){
        return false;
    }

    /*���ͷ��ȱ*/
    if (m_fReadAreadyPos == 0){
        iNumIn += 1;
    }

    /*ѭ����ȡ����ģ��*/ 
    /*˵����
    ���ζ�ȡ������ΪEACH_TIME_READ*/
    m_inputFile.seekg(m_fReadAreadyPos);//��ԭ�ϴζ�ȡ��λ��

    while (iLineAready < iNumIn){
        getline(m_inputFile,temp);
        /*��ȡ�ļ���ĩβ*/
        if (m_inputFile.eof()){
            return false;
        }
        iLineAready ++;
	
        /*˵��*/
        /*����վ�㼯�ϵ�biggerStationSet()������������*/
        if (pRecordSetOut->isEnd()){
            pRecordSetOut->biggerRecordSet();
        }
        /*˵��*/
        /*ͨ��linkRecord()����ֱ�ӻ�ȡ��¼���������׵�ַ����ͨ��CEntityTripData->getSize()ȷ����ǰ�洢λ���±꣬���ͨ�����õ�ǰ�洢λ��
        ������¼��Ӧ��updatteRecord�������������ַ������ͼ�¼��Ϣ���������Ӧ�ĵ���վ���˽������ֵ*/
        if (pRecordSetOut->linkRecord()[pRecordSetOut->gettingSize()].update(temp)){
            (pRecordSetOut->gettingSize()) ++;//վ�㼯�ϴ洢λ������
            cout << temp << endl;
        }
    }

    m_fReadAreadyPos = m_inputFile.tellg();//���汾�ζ�ȡ��λ����Ϣ

    return true;
}

/**
˵�������ļ�
����ֵ���Ƿ�򿪳ɹ�
����ʱ�䣺2015/10/16*/
bool CDALOriginalFile::openFile(int iFlag){

    m_WriteReadFlag->chFlag = iFlag;

    if (m_WriteReadFlag->chFlag != ORIGIN_FILE_OPEN_MODE_OUT){
        m_inputFile.open(m_chFileName,ios::app);
    }else{
        m_outputFile.open(m_chFileName,ios::out);
    }
    return true;
}


/**
˵�����ر��ļ�
����ֵ���Ƿ�رճɹ�
����ʱ�䣺2015/10/16*/
bool CDALOriginalFile::closeFile(){

    if (m_WriteReadFlag->chFlag != ORIGIN_FILE_OPEN_MODE_OUT){
        m_inputFile.close();
    }else{
        m_outputFile.close();
    }
    return true;
}

/**
˵����������д���ļ� 
������Ҫд����ַ���
����ֵ���Ƿ�д��ɹ�
����ʱ�䣺2015/11/5*/
bool CDALOriginalFile::writeStdCheck (char *chTest){
    
    m_outputFile << chTest;
    return true;
}
