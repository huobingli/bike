#include"stdafx.h"
#include "FrameDAL.h"

CFrameDAL::CFrameDAL ()
:
m_objSourceFile(0),
m_objTargetFile(0),
m_objRelationFile(0),
m_objPreControl(0),
m_objAlgorithmControl(0){
    init();
}

CFrameDAL::~CFrameDAL (){

    if (m_objSourceFile != 0 && m_objTargetFile != 0 &&
        m_objRelationFile != 0 && m_objAlgorithmControl != 0 &&
        m_objPreControl != 0){
    delete m_objSourceFile;
    delete m_objTargetFile;
    delete m_objRelationFile;
    delete m_objAlgorithmControl;
    delete m_objPreControl;
    m_objSourceFile = NULL;
    m_objTargetFile = NULL;
    m_objRelationFile = NULL;
    m_objAlgorithmControl = NULL;
    m_objPreControl = NULL;
    }
}

/**
˵������ʼ�����ݷ��ʲ���
����ʱ�䣺2015/10/5*/
bool CFrameDAL::init (){
    m_objSourceFile = new CDALOriginalFile("Divvy_Trips_2013.csv", "ios::app");
    m_objTargetFile = new CDALFile("TargetFile.txt", "a+");
    m_objRelationFile = new CDALFile("RelationFile.txt", "a+");

    //�ж��ļ������Ƿ��ʼ���ɹ�
    if (m_objSourceFile==0 || m_objTargetFile==0|| m_objRelationFile ==0||
        m_objAlgorithmControl==0 || m_objPreControl==0){
        return false;
    }
    return true;
}


/**
��ڲ�������ʼλ�ã��軹���ݼ��϶����ַ, ���ζ�ȡ����
����ֵ ���Ƿ��ȡ�ɹ�
����ʱ�䣺2015/10/5*/
bool CFrameDAL::getUseRecord (CEntityTripDataSet *&pBorrowDataOut, int iNumIn, int iPosIn){

    if (iPosIn ==-1){
        return m_objPreControl->readSourceData(pBorrowDataOut, iNumIn);
    }
}
	
/** 
��ڲ�������ʼλ�ã�ͳ�����ݼ��϶����ַ
����ֵ���Ƿ�д��ɹ�
����ʱ�䣺2015/10/8*/
bool CFrameDAL::putPreprocessedData ( CEntityTimeSliceCountSet *pStatisticalDataRecordSetIn, int iPosIn){

    bool isSuccesed = false;

    //������ת���ɶ���������ʽ
    unsigned char *strBuf = pStatisticalDataRecordSetIn->getBinary();

    //��ȡ�����������ݳ���
    int iDataLength = pStatisticalDataRecordSetIn->getBinaryLength();

    //��������������д��Ŀ���ļ�
    isSuccesed = m_objPreControl->writeTimeSliceStatisticalBinaryObject(strBuf, iPosIn);
    if (isSuccesed){
        return true;
    }else{
        return false;
    }
}

/**
��������ʼλ�ã�ͳ�����ݼ��϶����ַ�������������ҵ���߼����з�����ڴ�ģ�����ҵ���߼������ͷţ�����¼��
����ֵ ���Ƿ��ȡ�ɹ�
����ʱ�䣺2015/9/30*/
bool CFrameDAL::getPreprocessedData (CEntityTimeSliceCountSet *&pStatisticalDataRecordSetOut, int iPos, int iNumIn){

    //�����������ֽ�����
    unsigned char *chBuffer = NULL;

    //�����㷨������ƶ���Ķ�ȡ����������ȡ�����ݴ洢�ڶ������ֽ�������
    m_objAlgorithmControl->readTimeSliceStatisticalBinaryObject(chBuffer, iNumIn);
    if (chBuffer == NULL){
        return false;
    }else{
        //���������ֽ�����ת����ʱ��Ƭ�������ݼ��϶���
        pStatisticalDataRecordSetOut->update(chBuffer);
        if (pStatisticalDataRecordSetOut == 0){
            free (chBuffer);//���ٶ������ֽ�����
            chBuffer = NULL;
            return false;
        }else{
            free (chBuffer); //���ٶ������ֽ�����
            chBuffer = NULL;
            return true;
        }
    }
}

/**
��������ʼλ�ã��������ݼ��϶���ָ�루�����������ҵ���߼����з�����ڴ�ģ�����ҵ���߼������ͷţ�
����ֵ ���Ƿ�д��ɹ�
����ʱ�䣺2015/9/30*/
bool CFrameDAL::putRelatedData (CListWriteRelationSet *pRelatedDataRecordSetIn, int iPosIn){
    bool isSuccesed = false;
    //������ת���ɶ���������ʽ
    unsigned char *strBuf = pRelatedDataRecordSetIn->getBinary();

    //��ȡ�����������ݳ���
    int iDataLength = pRelatedDataRecordSetIn->getBinaryLength();

    //��������������д��Ŀ���ļ�
    isSuccesed = m_objAlgorithmControl->writeTimeSliceRelatedBinaryObject(strBuf, iPosIn);
	free(strBuf);
	strBuf = NULL;
    if (isSuccesed){
        return true;
    }else{
        return false;
    }
}

/**
���ƣ�getRelatedData
��ڲ�������ʼλ�ã�ͳ�����ݼ��϶����ַ�������������ҵ���߼����з�����ڴ�ģ�����ҵ���߼������ͷţ�����¼��
����ֵ���Ƿ��ȡ�ɹ�
����ʱ�䣺2015/11/6*/
bool CFrameDAL::getRelatedData(CListWriteRelationSet *&pRelatedDataRecordSetOut, int iPos, int iNumIn){

    //�����������ֽ�����
    unsigned char *chBuffer = NULL;

    //�����㷨������ƶ���Ķ�ȡ����������ȡ�����ݴ洢�ڶ������ֽ�������
    m_objAlgorithmControl->readTimeSliceRelatedBinaryObject(chBuffer, iNumIn);
    if (chBuffer == NULL){
        return false;
    }else{
        //���������ֽ�����ת����ʱ��Ƭ�������ݼ��϶���
        pRelatedDataRecordSetOut->update(chBuffer);
        if (pRelatedDataRecordSetOut == 0){
            free (chBuffer);//���ٶ������ֽ�����
            chBuffer = NULL;
            return false;
        }else{
            free (chBuffer); //���ٶ������ֽ�����
            chBuffer = NULL;
            return true;
        }
    }
}

/**
������Դ�ļ����ƺ�Ŀ���ļ�����
����ֵ ���Ƿ�Ԥ��ʼ���ɹ�
����ʱ�䣺2015/10/8*/
bool CFrameDAL::initPreProcessControl (){

    //��ԭ�ļ�
    if (!m_objSourceFile->openFile(ORIGIN_FILE_OPEN_MODE_APP)){
        return false;
    }

    //��Ŀ���ļ�
    if (!m_objTargetFile->openFile()){
        return false;
    }
    
    //��̬����Ԥ������ƶ���
    m_objPreControl = new CControlPre(m_objSourceFile, m_objTargetFile);
    if (m_objPreControl == 0){
        return false;
    }

    return true;
}

/**
˵����Ԥ�����ƺ�
����ֵ ���Ƿ�Ԥ�����ƺ�ɹ�
����ʱ�䣺2015/10/8*/
bool CFrameDAL::doPreprocessRehabilitation (){

    //�ر�ԭ�ļ�
    if (!m_objSourceFile->closeFile()){
        return false;
    }

    //�ر�Ŀ���ļ�
    if (!m_objTargetFile->closeFile()){
        return false;
    }

    //�����봦����ƶ���
    if (m_objPreControl != 0){
        delete m_objPreControl;
        m_objPreControl = NULL;
        return true;
    }else{
        return false;
    }
}

/**
������Դ�ļ����ƺ�Ŀ���ļ�����
����ֵ ���Ƿ��㷨��ʼ���ɹ�
����ʱ�䣺2015/10/8*/
bool CFrameDAL::initAlgorithmControl (){

    //��Ŀ���ļ�
    if (!m_objTargetFile->openFile()){
        return false;
    }

    //�򿪹����ļ�
    if (!m_objRelationFile->openFile()){
        return false;
    }
    
    //��̬�����㷨������ƶ���
    m_objAlgorithmControl = new CControlAlgorithm(m_objTargetFile, m_objRelationFile);
    if (m_objAlgorithmControl == 0){
        return false;
    }

    return true;
}

/**
˵�����㷨�ƺ�
����ֵ ���Ƿ��㷨�����ƺ�ɹ�
����ʱ�䣺2015/10/8*/
bool CFrameDAL::doAlgorithmRehabilitation (){

    //�ر�Ŀ���ļ�
    if (!m_objTargetFile->closeFile()){
        return false;
    }

    //�رչ����ļ�
    if (!m_objRelationFile->closeFile()){
        return false;
    }

    //�����㷨���ƶ���
    if (m_objAlgorithmControl != 0){
        delete m_objAlgorithmControl;
        m_objAlgorithmControl = NULL;
        return true;
    }else{
        return false;
    }
}

/**
����:writeStdFile
˵�����ļ������ھʹ������ļ����ھ��������
��ڲ�����Ҫд����ַ���
����ֵ���Ƿ�д��ɹ�
����ʱ�䣺2015/11/5*/
bool CFrameDAL::writeStdFile(char *chTest){ 

    if (chTest == NULL){
        return false;
    }

    CDALOriginalFile *objFile = new CDALOriginalFile ("checkFile.txt", "ios::out");
    objFile->openFile(ORIGIN_FILE_OPEN_MODE_OUT);
    objFile->writeStdCheck(chTest);
    objFile->closeFile();

    return true;
}

/**
����:writemaxMinStdFile
˵�����ļ������ھʹ������ļ����ھ��������
��ڲ�����Ҫд����ַ���
����ֵ���Ƿ�д��ɹ�
����ʱ�䣺2015/1/15*/
bool CFrameDAL::writeMaxMinStdFile(char *chTest){

	if (chTest == NULL){
		return false;
	}

	CDALOriginalFile *objFile = new CDALOriginalFile("checkMaxMinFile.txt", "ios::out");
	objFile->openFile(ORIGIN_FILE_OPEN_MODE_OUT);
	objFile->writeStdCheck(chTest);
	objFile->closeFile();

	return true;
}

/**
����:writeRelationStdFile
˵�����ļ������ھʹ������ļ����ھ��������
��ڲ�����Ҫд����ַ���
����ֵ���Ƿ�д��ɹ�
����ʱ�䣺2015/1/26*/
bool CFrameDAL::writeRelationStdFile(char *chTest){

	if (chTest == NULL){
		return false;
	}

	CDALOriginalFile *objFile = new CDALOriginalFile("checkRelationArray.txt", "ios::out");
	objFile->openFile(ORIGIN_FILE_OPEN_MODE_OUT);
	objFile->writeStdCheck(chTest);
	objFile->closeFile();

	return true;
}

bool CFrameDAL::writeClusterStdFile(char *chTest)
{
	if (chTest == NULL)
	{
		return false;
	}

	CDALOriginalFile *objFile = new CDALOriginalFile("checkClusterArray.txt", "ios::out");
	objFile->openFile(ORIGIN_FILE_OPEN_MODE_OUT);
	objFile->writeStdCheck(chTest);
	objFile->closeFile();
	return true;
}